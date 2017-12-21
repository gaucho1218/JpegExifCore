//
//  JpgParseSample.cpp
//  JpegParserSample
//
//  Created by gaucho1218 on 2017. 9. 24..
//  Copyright © 2017년 gaucho1218. All rights reserved.
//

#include "JpgParseSample.h"
#include "DebugPrint.h"

CJpgPasrseSample::CJpgPasrseSample(void)
: m_pFile(nullptr), m_nOffset(0)
{
}

CJpgPasrseSample::~CJpgPasrseSample(void)
{
    Close();
}

bool CJpgPasrseSample::Open(const char *pJpeg)
{
    if( pJpeg != nullptr )
    {
        m_pFile = fopen(pJpeg, "rb");
        if( m_pFile != nullptr )
            return true;
        JPDebugPrint("File is Invalid: %s\n", pJpeg);
    }
    
    return false;
}

bool CJpgPasrseSample::Close(void)
{
    if( m_pFile != nullptr )
    {
        fclose(m_pFile);
        m_pFile = nullptr;
    }
    
    return true;
}

int64_t CJpgPasrseSample::ParseJpegData(void)
{
    return m_nOffset;
}
