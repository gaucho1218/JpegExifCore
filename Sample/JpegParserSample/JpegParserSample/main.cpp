//
//  main.cpp
//  JpegParserSample
//
//  Created by gaucho1218 on 2017. 9. 17..
//  Copyright © 2017년 gaucho1218. All rights reserved.
//

#include <iostream>

#include "JpegParser.h"

int main(int argc, const char * argv[]) {
    
    FILE *pFile = fopen("../sample_beer.jpg", "rb");
    if( pFile == nullptr )
    {
        printf("Open Failed\n");
    }
    
    auto temp = ParseJpegData(nullptr, 0);
    std::get<EJI_HDR>(temp);
    
    return 0;
}
