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
	EJPEG_SOI,		//! FFD8
	EJPEG_APP,		//! FFE0 ~ FFEF
	EJPEG_DQT,		//! FFDB
	EJPEG_SOF,		//! FFC0 ~ FFC2
	EJPEG_DHT,		//! FFC4
	EJPEG_SOS,		//! FFDA
	EJPEG_EOI		//! FFD9
};

//! attribute, offset
using TJpegInfo = std::tuple<EJpegHdrType, int>;

//! parse jpeg data and return its attributes and offset when it founds something for it
TJpegInfo ParseJpegData(char *pBuf, int nSize);

#endif
