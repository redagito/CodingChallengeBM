#include <MyEncodingRunner.h>
#include <chrono>
#include <gtest/gtest.h>

template<typename T>
void printEncodingTime(std::chrono::time_point<T> start, std::chrono::time_point<T> end)
{
	std::cout << "Encoding took "
		<< std::chrono::duration_cast<std::chrono::seconds>(end -
			start)
		.count()
		<< "s" << std::endl;
}

// NOTE testing mostly done via console output
// For proper testing would need callbacks
// or synchronized single-step solution
// NOTE mark tasks as done and check completion
TEST(MyEncodingRunnerTest, RunEncoding_Default) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(4, 1000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	printEncodingTime(startTime, endTime);
}

TEST(MyEncodingRunnerTest, RunEncoding_NoTasks) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(4, 1000);
	runner.runEncoding({});

	const auto endTime = std::chrono::steady_clock::now();
	printEncodingTime(startTime, endTime);
}

TEST(MyEncodingRunnerTest, RunEncoding_NoCPU) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(0, 1000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	printEncodingTime(startTime, endTime);
}

TEST(MyEncodingRunnerTest, RunEncoding_NotEnoughCPU) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(1, 1000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	printEncodingTime(startTime, endTime);
}

TEST(MyEncodingRunnerTest, RunEncoding_LowCPU) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(2, 1000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	printEncodingTime(startTime, endTime);
}

TEST(MyEncodingRunnerTest, RunEncoding_InsufficientMem) {
	MyEncodingRunner runner(4, 10);
	EXPECT_ANY_THROW(runner.runEncoding(PREDEFINED_BITRATE_LADDER));
}

TEST(MyEncodingRunnerTest, RunEncoding_LowMem) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(4, 500);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	printEncodingTime(startTime, endTime);
}

TEST(MyEncodingRunnerTest, RunEncoding_HighCPUMedMem) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(16, 1000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	printEncodingTime(startTime, endTime);
}

TEST(MyEncodingRunnerTest, RunEncoding_HighCPUHighMem) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(16, 4000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	printEncodingTime(startTime, endTime);
}

TEST(MyEncodingRunnerTest, RunEncoding_ExtremeCPUHighMem) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(512, 4000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	printEncodingTime(startTime, endTime);
}

TEST(MyEncodingRunnerTest, RunEncoding_ExtremeCPULowMem) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(512, 500);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	printEncodingTime(startTime, endTime);
}

// Basically stresstest
TEST(MyEncodingRunnerTest, RunEncoding_ExtremeCPUExtremeMem_HighTaskCount) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(512, 16000);

	BitrateLadder ladder;
	for (int i = 0; i < 10; ++i)
		ladder.insert(ladder.end(), PREDEFINED_BITRATE_LADDER.begin(), PREDEFINED_BITRATE_LADDER.end());
	
	runner.runEncoding(ladder);

	const auto endTime = std::chrono::steady_clock::now();
	printEncodingTime(startTime, endTime);
}