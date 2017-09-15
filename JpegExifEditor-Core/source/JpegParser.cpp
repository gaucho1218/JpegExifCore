//
//  JpegParser.cpp
//  JpegExifEditor-Core
//
//  Created by gaucho1218 on 2017. 9. 3..
//  Copyright © 2017 gaucho1218. All rights reserved.
//

#include "JpegParser.h"

TJpegInfo ParseJpegData(const char *pBuf, const int nSize)
{
    TJpegInfo tRet = std::make_tuple(EJPEG_NONE, 0, 0);
 
    if( pBuf == nullptr || nSize <= 0 )
        return tRet;

    
    //! need effective way to parse JPEG header
    const short *pHdr = reinterpret_cast<short *>(const_cast<char *>(pBuf));
    int nOffset{0};
    
    while( true )
    {
        if( (*pHdr & EJPEG_SOI) || (*pHdr & EJPEG_EOI) )
        {
            tRet = std::make_tuple(static_cast<EJpegHdrType>(*pHdr), nOffset * 2, 0);
            break;
        }
        else if( (*pHdr & EJPEG_APP) ||
                (*pHdr & EJPEG_DQT) ||
                (*pHdr & EJPEG_SOF) ||
                (*pHdr & EJPEG_DHT) ||
                (*pHdr & EJPEG_SOS))
        {
            //! has 2 byte size
            short nDataSize{0};
            
            //! check buffer has enough to get size
            if( (char *)pHdr + 2 <= pBuf + nSize )
            {
                nDataSize = *(pHdr + 1);
            }
            
            tRet = std::make_tuple(static_cast<EJpegHdrType>(*pHdr), nOffset * 2, nDataSize);
            break;
        }
        
        ++pHdr;
        ++nOffset;
        if( (char *)pHdr >= (pBuf + nSize) )
        {
            //! exceed buffer
            tRet = std::make_tuple(EJPEG_NONE, (nOffset * 2), 0);
            break;
        }
    }

	return tRet;
}
