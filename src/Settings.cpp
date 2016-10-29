#include "Settings.h"
#include <string>
#include <map>
#include <iostream>

#define TAG "Settings"

#define SWITCH(name, _short, nargs, handler) {(name), {(nargs), (handler)}}, {(_short), {(nargs), (handler)}}

namespace Settings
{
	namespace
	{
		std::string rom = "rom.bin";
		bool saverom = true;

		typedef bool (*switch_handler)(char* argv[]);
		struct switch_t
		{
			int arguments;
			switch_handler handler;
		};

		bool switch_help(char* argv[])
		{
			std::cout << "Pico80 fantasy emulator" << std::endl;
			std::cout << "Usage: Pico80 [arguments]" << std::endl;
			std::cout << std::endl;
			std::cout << "Available arguments:" << std::endl;
			std::cout << "-h,--help       - Print this message." << std::endl;
			std::cout << "-r,--rom <path> - Specify rom file location. (default: rom.bin)" << std::endl;
			std::cout << "-n,--dont-save  - Do not save changes back to the rom file on quit." << std::endl;
			return false;
		}

		bool switch_rom(char* argv[])
		{
			rom = std::string(argv[1]);
			return true;
		}

		bool switch_dont_save_rom(char* argv[])
		{
			saverom = false;
			return true;
		}

		std::map<std::string, switch_t> switches =
		{
			SWITCH("--help", "-h", 0, &switch_help),
			SWITCH("--rom", "-r", 1, &switch_rom),
			SWITCH("--dont-save", "-n", 0, &switch_dont_save_rom),
		};
	}

	bool parse_args(int argc, char* argv[])
	{
		for (int i=1; i<argc; i++)
		{
			std::string sw = std::string(argv[i]);
			if (switches.find(sw) == switches.end())
			{
				std::cout << "Error: Unknown switch " << sw << std::endl;
				switch_help(NULL);
				return false;
			}

			switch_t& s = switches[sw];

			if (i + s.arguments >= argc)
			{
				std::cout << "Error: Missing arguments for switch " << argv[i] << std::endl;
				switch_help(NULL);
				return false;
			}

			if (!s.handler(&argv[i]))
				return false;
			i += s.arguments;
		}

		return true;
	}

	std::string get_rom()
	{
		return rom;
	}

	bool save_rom()
	{
		return saverom;
	}
}
