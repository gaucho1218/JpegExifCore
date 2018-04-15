// JpegParserSampleWin.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include "JpegParser.h"

int main()
{
	FILE *pFile = fopen("sample_beer.jpg", "rb");
	if (pFile == nullptr)
	{
		printf("Open Failed\n");
	}

	auto nSize = 1024;
	auto pBufStart = malloc(nSize);
	if (pBufStart == nullptr)
	{
		printf("Couldn't allocate memory!!!\n");
		return -1;
	}

	char *pCurBuf = reinterpret_cast<char *>(pBufStart);
	auto bEOI{ false };

	while (!bEOI)
	{
		auto nReadSize = fread(pBufStart, 1, nSize, pFile);

		while (bEOI == false)
		{
			auto outTuple = ParseJpegData(pCurBuf, static_cast<int>(nReadSize));

			if (std::get<EJI_HDR>(outTuple) != EJPEG_NONE)
			{
				printf("Type: 0x%02X\t", std::get<EJI_HDR>(outTuple));
				printf("Offset: %d\t", std::get<EJI_OFFSET>(outTuple));
				printf("Size: %d\n", std::get<EJI_SIZE>(outTuple));

				if (std::get<EJI_HDR>(outTuple) == EJPEG_EOI)
				{
					bEOI = true;
					break;
				}

				if (std::get<EJI_SIZE>(outTuple) == 0)
				{
					pCurBuf += 2;
					nReadSize -= 2;
				}
				else if (std::get<EJI_SIZE>(outTuple) > (nReadSize + 2))
				{
					//! need to read more data from file
					pCurBuf += nReadSize;
					nReadSize = 0;
					break;
				}
				else
				{
					auto nCurDataSize = std::get<EJI_SIZE>(outTuple) + 2;
					pCurBuf += nCurDataSize;
					nReadSize -= nCurDataSize;
				}
			}
			else
			{
				bEOI = true;
				break;
			}
		}   //! end of while ParseJpegData()
	}   //! end of while fread()

	return 0;
}