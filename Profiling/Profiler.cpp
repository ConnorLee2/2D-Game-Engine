#include "Profiler.hpp"

namespace GameEngine
{
	Profiler::Profiler()
	{
	}

	Profiler::~Profiler()
	{
	}

	void Profiler::getFrameRate()
	{
		time = clock.getElapsedTime();
		std::cout << "FPS: " << 1.0f / time.asSeconds() << std::endl;
		clock.restart();
	}

	void Profiler::PrintMemoryInfo()
	{
		// Prints out memory usage of program
		uint64_t currentUsedRAM(0);

		PROCESS_MEMORY_COUNTERS info;
		GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
		currentUsedRAM = info.WorkingSetSize;

		//std::cout << "Current RAM used: " << currentUsedRAM << " Bytes " << "\n";
		//std::cout << "Current RAM used: " << currentUsedRAM / 1024 << " kilobytes " << "\n";
		std::cout << "Memory usage: " << currentUsedRAM / 1024 / 1024 << " MBs " << "\n";
	}
}