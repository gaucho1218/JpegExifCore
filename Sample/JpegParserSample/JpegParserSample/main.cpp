//
//  main.cpp
//  JpegParserSample
//
//  Created by gaucho1218 on 2017. 9. 17..
//  Copyright © 2017년 gaucho1218. All rights reserved.
//

#include <vector>

#include "JpgParseSample.h"
#include "DebugPrint.h"
#include "JpgTime.h"

#include <chrono>
using namespace std::chrono;

int main(int argc, const char * argv[])
{
	CJpgPasrseSample kParser;
	
	if (kParser.Open("../sample_beer.jpg") == false)
		return -1;

	std::vector<TJpegInfo> arrJpgInfo;
	TJpegInfo kInfo;
    
	auto nBefore = getJpgTimeMSecond();

    while( std::get<EJI_HDR>(kInfo) != EJPEG_EOI )
    {
        kParser.ParseJpg(kInfo);
        
		if (std::get<EJI_HDR>(kInfo) != EJPEG_NONE)
		{
			auto nAfter = getJpgTimeMSecond();

			printf("%s, offset:%d, size: %d, time: %llu\n",
				GetJpegName(std::get<EJI_HDR>(kInfo)), std::get<EJI_OFFSET>(kInfo),
				std::get<EJI_SIZE>(kInfo), (nAfter - nBefore));

			//! store it
			arrJpgInfo.push_back(kInfo);

			//! time
			nBefore = nAfter;
		}
    }

	printf("==================================================================\n");

	for (TJpegInfo kJI : arrJpgInfo)
	{
		//! offset read and check validality
		kParser.ParseJpg(std::get<EJI_OFFSET>(kJI), kInfo);
		printf("%s - %s\n", GetJpegName(std::get<EJI_HDR>(kJI)),
			GetJpegName(std::get<EJI_HDR>(kInfo)));
	}
	
	return 0;
}
