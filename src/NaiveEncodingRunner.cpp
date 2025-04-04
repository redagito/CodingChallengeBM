#include "NaiveEncodingRunner.h"
#include "EncodeRendition.h"

#include <iostream>

NaiveEncodingRunner::NaiveEncodingRunner(const int nrVCPUCores,
                                         const int memoryInMegabytes)
    : EncodingRunner(nrVCPUCores, memoryInMegabytes) {}

void NaiveEncodingRunner::runEncoding(const BitrateLadder &bitrateLadder) {
  // Not checking memory
  // Only using 2 cpu cores

  for (const auto &rendition : bitrateLadder) {
    std::cout << "Start encoding of rendition " << rendition << "\n";
    encodeRendition(rendition);
    std::cout << "Finished encoding of rendition " << rendition << "\n";
  }
}
