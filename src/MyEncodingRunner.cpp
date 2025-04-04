#include "MyEncodingRunner.h"
#include "EncodeRendition.h"

#include <iostream>
#include <algorithm>

// cout sync
static std::mutex ioMtx;

MyEncodingRunner::MyEncodingRunner(const int nrVCPUCores,
    const int memoryInMegabytes)
    : EncodingRunner(nrVCPUCores, memoryInMegabytes) {
}

// NOTE task selection based on largest task first, then try to fill up available resources with
// progressively smaller tasks. For low CPU this should be optimal
// Ideal solution would simulate all possible task orderings and pick fastest,
// then enqueue for workers to pick up (branch-bound?)
// Best feasable solution due to data transfer and task grouping might be worker owned queues + task stealing
void MyEncodingRunner::runEncoding(const BitrateLadder& bitrateLadder) {
    // create task list
    for (const auto& rend : bitrateLadder)
    {
        // sanity check
        if (calcMemoryUsageKB(rend) > memoryInMegabytes * 1024)
        {
            std::cout << "found unschedulable rendition, not enough ram: " << rend << "\n";
            throw std::exception("unschedulable rendition");
        }
        tasks.push_back(rend);
    }

    // higher ram usage first
    tasks.sort([](const Rendition& a, const Rendition& b) {
        return calcMemoryUsageKB(a) > calcMemoryUsageKB(b);
        });

    // spawn threads
    auto workerCount = std::min(nrVCPUCores / 2, (int)std::thread::hardware_concurrency());
    std::cout << "spawning " << workerCount << " workers\n";
    for (int i = 0; i < workerCount; ++i)
    {
        threads.emplace_back([this]() {
            while (true)
            {
                bool found = false;
                int availableMem = 0;
                int cpuUsed = 0;
                Rendition rendition;
                {
                    std::scoped_lock<std::mutex> lock{ this->mtx };
                    if (tasks.empty()) {
                        std::lock_guard lck{ ioMtx };
                        std::cout << "Task list empty, stopping worker\n";
                        return;
                    }

                    availableMem = getMemoryAvailableKB();
                    for (auto iter = tasks.begin(); iter != tasks.end(); ++iter)
                    {
                        auto memRequ = calcMemoryUsageKB(*iter);
                        if (memRequ > availableMem)
                            continue;
                        {
                            std::lock_guard lck{ ioMtx };
                            std::cout << "Found task\n";
                        }

                        rendition = *iter;
                        tasks.erase(iter);
                        found = true;
                        this->memoryUsedInKB += memRequ;
                        this->cpuUsed += 2;
                        cpuUsed = this->cpuUsed;
                        break;
                    }
                }

                if (found)
                {
                    auto memUsed = calcMemoryUsageKB(rendition);
                    {
                        std::lock_guard lck{ ioMtx };
                        std::cout << "Start encoding of rendition " << rendition << "\n";
                        std::cout << "Memory used " << memUsed << " kb\n";
                        std::cout << "Memory remaining " << availableMem << " kb\n";
                        std::cout << "VCPU used " << cpuUsed << "\n";
                    }
                    
                    encodeRendition(rendition);

                    {
                        std::lock_guard lck{ ioMtx };
                        std::cout << "Finished encoding of rendition " << rendition << "\n";
                        std::cout << "Memory freed " << memUsed << " kb\n";
                        std::cout << "CPUs freed 2" << "\n";
                    }

                    std::scoped_lock<std::mutex> lock{ this->mtx };
                    this->memoryUsedInKB -= memUsed;
                    this->cpuUsed -= 2;
                }
                else
                {
                    {
                        // Floods io
                        //std::lock_guard lck{ ioMtx };
                        //std::cout << "Failed to find task: not enough memory\n";
                    }
                    std::this_thread::yield();
                }
            }
            });
    }
    {
        std::lock_guard lck{ ioMtx };
        std::cout << "Workers spawned, waiting until done\n";
    }

    // block until complete
    for (std::thread& t : threads)
        t.join();
}

int MyEncodingRunner::getMemoryAvailableKB()
{
    return memoryInMegabytes * 1024 - memoryUsedInKB;
}