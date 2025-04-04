#pragma once

#include <ostream>
#include <vector>

struct Resolution {
  int width{};
  int height{};
};

struct Rendition {
  int bitrate{};
  Resolution resolution{};
  int fps{};
};

constexpr int VCPUS_USED_PER_ENCODING = 2;

static std::ostream &operator<<(std::ostream &stream,
                                const Rendition &rendition) {
  stream << "(" << rendition.resolution.width << "x"
         << rendition.resolution.height << ")@" << rendition.bitrate;
  return stream;
}

inline int calcPixelsPerSecond(const Rendition& rend) {
    return rend.resolution.width * rend.resolution.height * rend.fps;
}

inline int calcDurationMs(const Rendition& rend) {
    // Actual rate
    return calcPixelsPerSecond(rend) / 7000;
    // Faster for testing
    //return calcPixelsPerSecond(rend) / 70000;
}

// Result assumed to be in kb
// NOTE gets too large for int otherwise, dont want to chage to long
inline int calcMemoryUsageKB(const Rendition& rend) {
    // NOTE should be totalPixels * 8 but documentation seems to use 
    // pixels/s and total pixels interchangeably
    // Would need duration of chunk in seconds to get total pixels
    return calcPixelsPerSecond(rend) * 8 / 1024;
}

using BitrateLadder = std::vector<Rendition>;

const BitrateLadder PREDEFINED_BITRATE_LADDER = {{240, {384, 216}, 30},    //
                                                 {375, {384, 216}, 30},    //
                                                 {550, {512, 288}, 30},    //
                                                 {750, {640, 360}, 30},    //
                                                 {1000, {768, 432}, 30},   //
                                                 {1500, {1024, 576}, 30},  //
                                                 {2300, {1280, 720}, 30},  //
                                                 {3000, {1280, 720}, 30},  //
                                                 {4300, {1920, 1080}, 30}, //
                                                 {5800, {1920, 1080}, 30}};
