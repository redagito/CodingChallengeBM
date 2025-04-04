#include <NaiveEncodingRunner.h>
#include <MyEncodingRunner.h>
#include <chrono>
#include <gtest/gtest.h>

TEST(NaiveEncodingRunnerTest, RunEncoding) {
	const auto startTime = std::chrono::steady_clock::now();

	NaiveEncodingRunner runner(4, 1000);
	runner.runEncoding(PREDEFINED_BITRATE_LADDER);

	const auto endTime = std::chrono::steady_clock::now();
	std::cout << "Encoding took "
		<< std::chrono::duration_cast<std::chrono::seconds>(endTime -
			startTime)
		.count()
		<< "s" << std::endl;
}