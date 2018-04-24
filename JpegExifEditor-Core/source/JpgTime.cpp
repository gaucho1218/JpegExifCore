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

auto getJpgTimeMSecond(void)
{
	return duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
}