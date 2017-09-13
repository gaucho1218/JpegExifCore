//
//  JpegParser.h
//  JpegExifEditor-Core
//
//  Created by gaucho1218 on 2017. 9. 3..
//  Copyright © 2017 gaucho1218. All rights reserved.
//

#ifndef JPEG_PARSER_H
#define JPEG_PARSER_H

#include <tuple>

enum class EJpegHdrType
{
	EJPEG_NONE = 0,
#ifdef __LITTLE_ENDIAN__
	EJPEG_SOI = 0xD8FF,		//! FFD8
	EJPEG_APP = 0xE0FF,		//! FFE0 ~ FFEF
	EJPEG_DQT = 0xDBFF,		//! FFDB
	EJPEG_SOF = 0xC0FF,		//! FFC0 ~ FFC2
	EJPEG_DHT = 0xC4FF,		//! FFC4
	EJPEG_SOS = 0xDAFF,		//! FFDA
	EJPEG_EOI = 0xD9FF		//! FFD9
#else
    EJPEG_SOI = 0xFFD8,		//! FFD8
    EJPEG_APP = 0xFFE0,		//! FFE0 ~ FFEF
    EJPEG_DQT = 0xFFDB,		//! FFDB
    EJPEG_SOF = 0xFFC0,		//! FFC0 ~ FFC2
    EJPEG_DHT = 0xFFC4,		//! FFC4
    EJPEG_SOS = 0xFFDA,		//! FFDA
    EJPEG_EOI = 0xFFD9		//! FFD9
#endif
};

//! attribute, offset
using TJpegInfo = std::tuple<EJpegHdrType, int>;

//! parse jpeg data and return its attributes and offset when it founds something for it
TJpegInfo ParseJpegData(const char *const pBuf, const int nSize);

#endif
