//
//  main.cpp
//  JpegParserSample
//
//  Created by gaucho1218 on 2017. 9. 17..
//  Copyright © 2017년 gaucho1218. All rights reserved.
//

#include <iostream>

#include "JpgParseSample.h"
#include "DebugPrint.h"

int main(int argc, const char * argv[])
{
	CJpgPasrseSample kParser;
	
	if (kParser.Open("../sample_beer.jpg") == false)
		return -1;

	TJpegInfo kInfo;
    
    while( std::get<EJI_HDR>(kInfo) != EJPEG_EOI )
    {
        kParser.ParseJpg(kInfo);
        
        if( std::get<EJI_HDR>(kInfo) != EJPEG_NONE )
            printf("%s, offset:%d, size: %d\n",
				GetJpegName(std::get<EJI_HDR>(kInfo)), std::get<EJI_OFFSET>(kInfo),
				std::get<EJI_SIZE>(kInfo));
    }
	
	return 0;
}
