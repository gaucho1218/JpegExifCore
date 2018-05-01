//
//  JpegParser.cpp
//  JpegExifEditor-Core
//
//  Created by gaucho1218 on 2017. 9. 3..
//  Copyright © 2017 gaucho1218. All rights reserved.
//

#include "JpegParser.h"

short ChangeEndian16(short nData)
{
	return (nData << 8 | ((nData >> 8) & 0x00FF));
}

TJpegInfo ParseJpegData(const char *pBuf, const int nSize, const int nOffset) noexcept
{
	TJpegInfo tRet = std::make_tuple(EJPEG_NONE, 0, 0);

	if (pBuf == nullptr || nSize <= 0)
		return tRet;


	//! need effective way to parse JPEG header
	// const unsigned short *pHdr = reinterpret_cast<unsigned short *>(const_cast<char *>(pBuf));
	const unsigned short *pHdr = nullptr;
	int nHdrOffset{ nOffset };

	while (true)
	{
		pHdr = reinterpret_cast<unsigned short *>(const_cast<char *>(pBuf));

		if ((*pHdr == EJPEG_SOI) || (*pHdr == EJPEG_EOI))
		{
			tRet = std::make_tuple(static_cast<EJpegHdrType>(*pHdr), nHdrOffset, 0);
			break;
		}
		else if ((*pHdr >= EJPEG_APP && *pHdr <= EJPEG_APPMAX) ||
			(*pHdr == EJPEG_DQT) ||
			(*pHdr >= EJPEG_SOF && *pHdr <= EJPEG_SOFMAX) ||
			(*pHdr == EJPEG_DHT) ||
			(*pHdr == EJPEG_SOS))
		{
			//! has 2 byte size
			short nDataSize{ 0 };

			//! check buffer has enough to get size
			if ((char *)pHdr + 2 <= pBuf + nSize)
			{
#if defined __LITTLE_ENDIAN__ || defined _WIN32
				nDataSize = ChangeEndian16(*(pHdr + 1));
#else
				nDataSize = *(pHdr + 1);
#endif
			}

			tRet = std::make_tuple(static_cast<EJpegHdrType>(*pHdr), nHdrOffset, nDataSize);
			break;
		}

		++pBuf;
		++nHdrOffset;
		if ((char *)pHdr >= (pBuf + nSize))
		{
			//! exceed buffer
			tRet = std::make_tuple(EJPEG_NONE, (nOffset * 2), 0);
			break;
		}
	}

	return tRet;
}

char const *GetJpegName(EJpegHdrType nJpegHdr)
{
	char const *pRet = nullptr;

	switch (nJpegHdr)
	{
	case EJPEG_SOI:
		pRet = "Start Of Image";
		break;
	case EJPEG_DQT:
		pRet = "Define Quantization Table";
		break;
	case EJPEG_DHT:
		pRet = "Define Huffman Table";
		break;
	case EJPEG_SOS:
		pRet = "Start Of Scan";
		break;
	case EJPEG_EOI:
		pRet = "End Of Image";
		break;
	default:
		if (nJpegHdr >= EJPEG_APP && nJpegHdr <= EJPEG_APPMAX)
			pRet = "App Data";
		else if (nJpegHdr >= EJPEG_SOF && nJpegHdr <= EJPEG_SOFMAX)
			pRet = "Start Of Frame";
		else
			pRet = "Unknown JPEG Type";
		break;
	}

	return pRet;
}
