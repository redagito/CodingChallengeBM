#pragma once

#include "BitrateLadder.h"

#include <chrono>
#include <thread>

inline void encodeRendition(const Rendition& rendition) {
	int durationInMs = calcDurationMs(rendition);
	std::this_thread::sleep_for(std::chrono::milliseconds(durationInMs));
}
