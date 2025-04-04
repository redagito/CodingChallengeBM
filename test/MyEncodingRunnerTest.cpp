#include <MyEncodingRunner.h>
#include <chrono>
#include <gtest/gtest.h>

// NOTE testing mostly done via console output
// For proper testing would need callbacks
// or synchronized single-step solution
TEST(MyEncodingRunnerTest, RunEncoding_Default) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(4, 1000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	std::cout << "Encoding took "
		<< std::chrono::duration_cast<std::chrono::seconds>(endTime -
			startTime)
		.count()
		<< "s" << std::endl;
}

TEST(MyEncodingRunnerTest, RunEncoding_NoTasks) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(4, 1000);
	runner.runEncoding({});

	const auto endTime = std::chrono::steady_clock::now();
	std::cout << "Encoding took "
		<< std::chrono::duration_cast<std::chrono::seconds>(endTime -
			startTime)
		.count()
		<< "s" << std::endl;
}

TEST(MyEncodingRunnerTest, RunEncoding_NoCPU) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(0, 1000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	std::cout << "Encoding took "
		<< std::chrono::duration_cast<std::chrono::seconds>(endTime -
			startTime)
		.count()
		<< "s" << std::endl;
}

TEST(MyEncodingRunnerTest, RunEncoding_NotEnoughCPU) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(1, 1000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	std::cout << "Encoding took "
		<< std::chrono::duration_cast<std::chrono::seconds>(endTime -
			startTime)
		.count()
		<< "s" << std::endl;
}

TEST(MyEncodingRunnerTest, RunEncoding_LowCPU) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(2, 1000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	std::cout << "Encoding took "
		<< std::chrono::duration_cast<std::chrono::seconds>(endTime -
			startTime)
		.count()
		<< "s" << std::endl;
}

TEST(MyEncodingRunnerTest, RunEncoding_InsufficientMem) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(4, 10);
	EXPECT_ANY_THROW(runner.runEncoding(PREDEFINED_BITRATE_LADDER));
}

TEST(MyEncodingRunnerTest, RunEncoding_LowMem) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(4, 500);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	std::cout << "Encoding took "
		<< std::chrono::duration_cast<std::chrono::seconds>(endTime -
			startTime)
		.count()
		<< "s" << std::endl;
}

TEST(MyEncodingRunnerTest, RunEncoding_HighCPUMedMem) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(16, 1000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	std::cout << "Encoding took "
		<< std::chrono::duration_cast<std::chrono::seconds>(endTime -
			startTime)
		.count()
		<< "s" << std::endl;
}

TEST(MyEncodingRunnerTest, RunEncoding_HighCPUHighMem) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(16, 4000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	std::cout << "Encoding took "
		<< std::chrono::duration_cast<std::chrono::seconds>(endTime -
			startTime)
		.count()
		<< "s" << std::endl;
}

TEST(MyEncodingRunnerTest, RunEncoding_ExtremeCPUHighMem) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(512, 4000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	std::cout << "Encoding took "
		<< std::chrono::duration_cast<std::chrono::seconds>(endTime -
			startTime)
		.count()
		<< "s" << std::endl;
}

TEST(MyEncodingRunnerTest, RunEncoding_ExtremeCPULowMem) {
	const auto startTime = std::chrono::steady_clock::now();

	MyEncodingRunner runner(512, 500);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	std::cout << "Encoding took "
		<< std::chrono::duration_cast<std::chrono::seconds>(endTime -
			startTime)
		.count()
		<< "s" << std::endl;
}