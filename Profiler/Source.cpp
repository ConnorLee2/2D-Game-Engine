#include <iostream>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;

void init() {
	FILE* file = fopen_s("/proc/stat", "r");
	fscanf_s(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow,
		&lastTotalSys, &lastTotalIdle);
	fclose(file);
}

double getCurrentValue() {
	double percent;
	FILE* file;
	unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

	file = fopen("/proc/stat", "r");
	fscanf_s(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
		&totalSys, &totalIdle);
	fclose(file);

	if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
		totalSys < lastTotalSys || totalIdle < lastTotalIdle) {
		//Overflow detection. Just skip this value.
		percent = -1.0;
	}
	else {
		total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
			(totalSys - lastTotalSys);
		percent = total;
		total += (totalIdle - lastTotalIdle);
		percent /= total;
		percent *= 100;
	}

	lastTotalUser = totalUser;
	lastTotalUserLow = totalUserLow;
	lastTotalSys = totalSys;
	lastTotalIdle = totalIdle;

	return percent;
}

int main()
{
	//Profiler* profile = new Profiler();
	//profile->init();
	//double cpuX = profile->getCurrentValue();
	//std::cout << cpuX << std::endl;
	
	init();
	double cpuT = getCurrentValue();
	std::cout << cpuT << std::endl;

	int input;
	std::cin >> input;
	

	return 0;
}