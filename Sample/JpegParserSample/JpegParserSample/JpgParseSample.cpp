//
//  JpgParseSample.cpp
//  JpegParserSample
//
//  Created by gaucho1218 on 2017. 9. 24..
//  Copyright © 2017년 gaucho1218. All rights reserved.
//

#include "JpgParseSample.h"
#include "JpegParser.h"
#include "DebugPrint.h"

using namespace std;

CJpgPasrseSample::CJpgPasrseSample(void)
	: m_pFile(nullptr), m_nOffset(0), m_nReadSize(0), m_nSkipSize(0), m_nBufSize(4 * 1024)
{
}

CJpgPasrseSample::CJpgPasrseSample(int nBufSize)
	: m_pFile(nullptr), m_nOffset(0), m_nReadSize(0), m_nSkipSize(0), m_nBufSize(nBufSize)
{
}

CJpgPasrseSample::~CJpgPasrseSample(void)
{
	Close();
}

bool CJpgPasrseSample::Open(const char *pJpeg)
{
	m_pBuf = reinterpret_cast<char *>(malloc(m_nBufSize));
	if (m_pBuf != nullptr)
		memset(m_pBuf, 0, m_nBufSize);
	else
	{
		JPDebugPrint("Could not allocate memory!\n");
		return false;
	}

	if (pJpeg != nullptr)
	{
		m_pFile = fopen(pJpeg, "rb");
		if (m_pFile != nullptr)
			return true;
		JPDebugPrint("File is Invalid: %s\n", pJpeg);
	}

	return false;
}

bool CJpgPasrseSample::Close(void)
{
	if (m_pFile != nullptr)
	{
		fclose(m_pFile);
		m_pFile = nullptr;
	}

	if (m_pBuf != nullptr)
	{
		free(m_pBuf);
		m_pBuf = NULL;
	}

	return true;
}

int64_t CJpgPasrseSample::ParseJpg(TJpegInfo &kParseInfo)
{
	if (m_pFile == nullptr)
	{
		JPDebugPrint("Not Open yet\n");
		return -1;
	}

	//! read and skip
	auto bRead{ true };
	while (bRead == true)
	{
		auto nSize = fread(m_pBuf + m_nReadSize,
			1, static_cast<size_t>(m_nBufSize - m_nReadSize),
			m_pFile);

		if (nSize <= 0)
		{
			JPDebugPrint("EOF or error: %d\n", nSize);
			break;
		}

		m_nReadSize += nSize;

		//! check skip is exist
		if (m_nSkipSize > 0)
		{
			auto nSkip = nSize > m_nSkipSize ? m_nSkipSize : nSize;
			m_nOffset += nSkip;
			m_nReadSize -= nSkip;
			m_nSkipSize -= nSkip;
		}
		else
			bRead = false;
	}

	//! parse
	kParseInfo = ParseJpegData(m_pBuf, static_cast<int>(m_nReadSize),
		static_cast<int>(m_nOffset));

	if (get<EJI_HDR>(kParseInfo) != EJPEG_NONE)
	{
		//! check size

	}

	return m_nOffset;
}

int64_t CJpgPasrseSample::ParseJpg(int nOffset, TJpegInfo &kParseInfo)
{
	if (m_pFile == nullptr)
	{
		JPDebugPrint("Not Open yet\n");
		return -1;
	}
	if (nOffset < 0)
	{
		JPDebugPrint("Invalid target offset(%d)\n", nOffset);
		return -1;
	}

	//! move offset to nOffset
	m_nOffset = nOffset;
	fseek(m_pFile, static_cast<long>(m_nOffset), SEEK_SET);

	//! clear buffer
	memset(m_pBuf, 0, m_nBufSize);
	m_nReadSize = 0;
	m_nSkipSize = 0;
	
	//! parse it
	ParseJpg(kParseInfo);

	return m_nOffset;
}