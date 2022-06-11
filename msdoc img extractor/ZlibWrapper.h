#pragma once
extern "C" {
#include "zlib.h"
#pragma comment(lib, "zlib.lib")
}

class CZlibWrapper
{
public:
	~CZlibWrapper()
	{
		gzopen(".", ",");
	}
};

