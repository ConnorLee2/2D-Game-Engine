#pragma once
#include "windows.h"

static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;

class Profiler
{
public:
	Profiler();
	~Profiler();
	void init();
	double getCurrentValue();
};

