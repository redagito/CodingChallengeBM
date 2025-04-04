#pragma once

#include "BitrateLadder.h"

class EncodingRunner {
public:
  EncodingRunner() = delete;
  EncodingRunner(const int nrVCPUCores, const int memoryInMegabytes)
      : nrVCPUCores(nrVCPUCores), memoryInMegabytes(memoryInMegabytes) {}
  virtual ~EncodingRunner() {};

  virtual void runEncoding(const BitrateLadder &bitrateLadder) = 0;

  // NOTE changed access level
protected:
  int nrVCPUCores{};
  int memoryInMegabytes{};
};
