//
//  JpegParser.cpp
//  JpegExifEditor-Core
//
//  Created by gaucho1218 on 2017. 9. 3..
//  Copyright © 2017 gaucho1218. All rights reserved.
//

#include "JpegParser.h"

TJpegInfo ParseJpegData(const char *const pBuf, const int nSize)
{
    TJpegInfo tRet = std::make_tuple(EJpegHdrType::EJPEG_NONE, 0);
 
    if( pBuf == nullptr || nSize <= 0 )
        return tRet;

    
    //! need effective way to parse JPEG header
    const short *const pHdr = reinterpret_cast<short *>(const_cast<char *>(pBuf));
    
    
	return tRet;
}
