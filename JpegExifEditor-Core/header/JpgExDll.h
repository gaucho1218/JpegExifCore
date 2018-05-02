//
//  JpgExDll.h
//  JpegExifEditor-Core
//
//  Created by gaucho1218 on 2018. 4. 24..
//  Copyright © 2018 gaucho1218. All rights reserved.
//

#ifndef JpgExDll_h
#define JpgExDll_h

#ifdef _WIN32
#ifdef _WINDLL
#define JPGEXFDLL	__declspec(dllexport)
#else
#define JPGEXFDLL	__declspec(dllimport)
#endif
#else	//! other platform
#ifdef HAVE_GCCVISIBILITYPATCH
#define JPGEXFDLL __attribute__((visibility("default")))
#else
#define JPGEXFDLL
#endif
#endif

#endif /* JpgExDll_h */
