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
#include "JpgExDll.h"

enum EJpegHdrType
{
	EJPEG_NONE = 0,
#if defined __LITTLE_ENDIAN__ || defined _WIN32
	EJPEG_SOI =		0xD8FF,		//! FFD8
	EJPEG_APP =		0xE0FF,		//! FFE0 ~ FFEF
	EJPEG_APPMAX =	0xEFFF,
	EJPEG_DQT =		0xDBFF,		//! FFDB
	EJPEG_SOF =		0xC0FF,		//! FFC0 ~ FFC2
	EJPEG_SOFMAX =	0xC2FF,
	EJPEG_DHT =		0xC4FF,		//! FFC4
	EJPEG_SOS =		0xDAFF,		//! FFDA
	EJPEG_EOI =		0xD9FF		//! FFD9
#else
	EJPEG_SOI =		0xFFD8,		//! FFD8
	EJPEG_APP =		0xFFE0,		//! FFE0 ~ FFEF
	EJPEG_APPMAX =	0xFFEF,
	EJPEG_DQT =		0xFFDB,		//! FFDB
	EJPEG_SOF =		0xFFC0,		//! FFC0 ~ FFC2
	EJPEG_SOFMAX =	0xFFC2,
	EJPEG_DHT =		0xFFC4,		//! FFC4
	EJPEG_SOS =		0xFFDA,		//! FFDA
	EJPEG_EOI =		0xFFD9		//! FFD9
#endif
};

//! enum for easy to get data from tuple
enum EJpegInfo
{
	EJI_HDR = 0,
	EJI_OFFSET,
	EJI_SIZE
};
//! attribute, offset, size
using TJpegInfo = std::tuple<EJpegHdrType, int, short>;

//! parse jpeg data and return its attributes, offset, size
//! check TJpegInfo's size part if header type has additional size
JPGEXFDLL TJpegInfo ParseJpegData(const char *pBuf, const int nSize, const int nOffset) noexcept;

//! return jpeg header name for testing or debugging
JPGEXFDLL char const *GetJpegName(EJpegHdrType nJpegHdr);

#endif
