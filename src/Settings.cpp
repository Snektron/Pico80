#include "Settings.h"
#include <string>
#include <map>
#include <iostream>

#define TAG "Settings"

#define SWITCH(name, nargs, handler) {name, {nargs, handler}}

namespace Settings
{
	namespace
	{
		std::string rom = "rom.bin";

		typedef void (*switch_handler)(char* argv[]);
		struct switch_t
		{
			int arguments;
			switch_handler handler;
		};

		void switch_rom(char* argv[]);

		std::map<std::string, switch_t> switches =
		{
				SWITCH("--rom", 1, &switch_rom),
				SWITCH("-r", 1, &switch_rom)
		};

		void switch_rom(char* argv[])
		{
			rom = std::string(argv[1]);
		}
	}

	bool parse_args(int argc, char* argv[])
	{
		for (int i=1; i<argc; i++)
		{
			std::string sw = std::string(argv[i]);
			if (switches.find(sw) == switches.end())
			{
				std::cout << "Error: Unknown switch " << sw << std::endl;
				return false;
			}

			switch_t& s = switches[sw];

			if (i + s.arguments >= argc)
			{
				std::cout << "Error: Not enough arguments for " << argv[i] << std::endl;
				return false;
			}

			s.handler(&argv[i]);
			i += s.arguments;
		}

		return true;
	}

	std::string get_rom()
	{
		return rom;
	}
}
