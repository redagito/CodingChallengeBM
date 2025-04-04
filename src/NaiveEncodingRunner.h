#pragma once

#include "EncodingRunner.h"

class NaiveEncodingRunner : public EncodingRunner {
public:
  NaiveEncodingRunner(const int nrVCPUCores, const int memoryInMegabytes);

  void runEncoding(const BitrateLadder &bitrateLadder);
};
