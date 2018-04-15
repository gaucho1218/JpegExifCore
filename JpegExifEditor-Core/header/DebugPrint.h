//
//  DebugPrint.h
//  JpegExifEditor-Core
//
//  Created by gaucho1218 on 2017. 12. 21..
//  Copyright © 2017년 gaucho1218. All rights reserved.
//

#ifndef DebugPrint_h
#define DebugPrint_h

#if defined(DEBUG) || defined(_DEBUG)
#include <stdio.h>
#define JPDebugPrint(fmt, args, ...)  fprintf(stderr, "[%s, %d]: " fmt, __FILE__, __LINE__, ##args)
#else
DebugPrint(...)
#endif

#endif /* DebugPrint_h */
