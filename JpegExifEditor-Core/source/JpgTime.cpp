//
//  JpgTime.cpp
//  JpegExifEditor-Core
//
//  Created by gaucho1218 on 2018. 4. 24..
//  Copyright © 2017 gaucho1218. All rights reserved.
//

#include "JpgTime.h"
#include <chrono>

using namespace std::chrono;


uint64_t getJpgTimeMSecond(void)
{
	return static_cast<uint64_t>(duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count());
}
