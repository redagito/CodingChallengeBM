#pragma once

#include "EncodingRunner.h"
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>

class MyEncodingRunner : public EncodingRunner {
public:
	MyEncodingRunner(const int nrVCPUCores, const int memoryInMegabytes);

	// NOTE Assumption this call blocks until encoding is done
	void runEncoding(const BitrateLadder& bitrateLadder);

	int getMemoryAvailableKB();

private:
	std::vector<std::thread> threads;

	// locks everything but "threads"
	std::mutex mtx;
	std::list<Rendition> tasks;
	// NOTE doc says mem per core, assuming its globally shared instead
	// probably meant to sim different ram amounts per core?
	int memoryUsedInKB{};
	int cpuUsed{};
};
