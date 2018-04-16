//
//  main.cpp
//  JpegParserSample
//
//  Created by gaucho1218 on 2017. 9. 17..
//  Copyright © 2017년 gaucho1218. All rights reserved.
//

#include <iostream>

#include "JpegParser.h"
#include "DebugPrint.h"

int main(int argc, const char * argv[])
{
    FILE *pFile = fopen("../sample_beer.jpg", "rb");
    if( pFile == nullptr )
    {
        printf("Open Failed\n");
        return -1;
    }
    
    auto nSize = 1024;
    auto nSkipSize = 0;
    auto nCurOffset{0};
    size_t nReadSize{0};
    auto pBufStart = malloc(nSize);
    if( pBufStart == nullptr )
    {
        printf("Couldn't allocate memory!!!\n");
        return -1;
    }
    
    char *pCurBuf = reinterpret_cast<char *>(pBufStart);
    auto bEOI{false};
    auto bSOS{false};
    
    while(!bEOI)
    {
        nReadSize = fread((char *)(pBufStart) + nReadSize, 1, nSize - nReadSize, pFile);
        pCurBuf = reinterpret_cast<char *>(pBufStart);
        
        if( nSkipSize >= nSize )
        {
            nReadSize -= nSize;
            nSkipSize -= nSize;
            nCurOffset += nSize;
            continue;
        }
        else if( nSkipSize > 0 )
        {
            nReadSize -= nSkipSize;
            pCurBuf += nSkipSize;
            nCurOffset += nSkipSize;
            nSkipSize = 0;
        }

        while(bEOI == false)
        {
            auto outTuple = ParseJpegData(pCurBuf, static_cast<int>(nReadSize), static_cast<int>(nCurOffset));
            
            if( bSOS == true && std::get<EJI_HDR>(outTuple) != EJPEG_EOI )
            {
                if( nReadSize <= 1 )
                    break;
                
                pCurBuf += 2;
                nReadSize -= 2;
                nCurOffset += 2;
                continue;
            }
            else if( std::get<EJI_HDR>(outTuple) == EJPEG_SOS )
            {
                printf("Found SOS\n");
                bSOS = true;
                pCurBuf += 2;
                nReadSize -= 2;
                nCurOffset += 2;
                continue;
            }
            
            if( std::get<EJI_HDR>(outTuple) != EJPEG_NONE )
            {
				printf("Type: %s(0x%02X)\t", GetJpegName(std::get<EJI_HDR>(outTuple)), std::get<EJI_HDR>(outTuple));
                printf("Offset: %d\t", std::get<EJI_OFFSET>(outTuple));
                printf("Size: %d\n", std::get<EJI_SIZE>(outTuple));
                
                if( std::get<EJI_HDR>(outTuple) == EJPEG_EOI )
                {
                    bEOI = true;
                    break;
                }
                
                if( std::get<EJI_SIZE>(outTuple) == 0 )
                {
                    pCurBuf += 2;
                    nReadSize -= 2;
                    nCurOffset += 2;
                }
                else if( std::get<EJI_SIZE>(outTuple) > (nReadSize +2) )
                {
                    //! need to read more data from file
                    nSkipSize = std::get<EJI_SIZE>(outTuple) - static_cast<int>(nReadSize);
                    nCurOffset += (nReadSize + 2);
                    nReadSize = 0;
                    break;
                }
                else
                {
                    auto nCurDataSize = std::get<EJI_SIZE>(outTuple) + 2;
                    pCurBuf += nCurDataSize;
                    nCurOffset += nCurDataSize;
                    nReadSize -= nCurDataSize;
                }
            }
            else
            {
                bEOI = true;
                break;
            }
        }   //! end of while ParseJpegData()

    }   //! end of while fread()
    
    return 0;
}
