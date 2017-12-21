//
//  JpgParseSample.h
//  JpegParserSample
//
//  Created by gaucho1218 on 2017. 9. 24..
//  Copyright © 2017년 gaucho1218. All rights reserved.
//

#ifndef JpgParseSample_h
#define JpgParseSample_h

#include <stdint.h>
#include <stdio.h>

class CJpgPasrseSample
{
public:
    CJpgPasrseSample(void);
    virtual ~CJpgPasrseSample(void);
    
    //! supports FILE first (do HTTP later?)
    bool Open(const char *pJpeg);
    bool Close(void);
    
    //! returns last offset
    int64_t ParseJpegData(void);
    
protected:
    FILE    *m_pFile;
    int64_t m_nOffset;
};

#endif /* JpgParseSample_h */