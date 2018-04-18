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

int64_t CJpgPasrseSample::ParseJpegData(TJpegInfo &kParseInfo)
{
	if (m_pFile == nullptr)
		return -1;

	//! skip data if exist
	if (m_nSkipSize > 0)
	{

	}

	//! read if need more data
	if (m_nReadSize < 4)
	{
		m_nReadSize = fread(m_pBuf + m_nReadSize,
			1, static_cast<size_t>(m_nBufSize - m_nReadSize),
			m_pFile);
	}

	//! parse

	return m_nOffset;
}

int64_t CJpgPasrseSample::ParseJpegData(int nOffset, TJpegInfo &kParseInfo)
{
	if (m_pFile == nullptr)
		return -1;

	//! move offset to nOffset and parse its data
	return m_nOffset;
}