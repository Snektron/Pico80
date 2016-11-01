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
		std::string opt_rom = "rom.bin";
		bool opt_save_rom = true;
		bool opt_quiet = false;
		bool opt_log_to_file = false;

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
			std::cout << "-q,--quiet      - Do not output log messages to console." << std::endl;
			std::cout << "-s,--save-log   - Output log to a file." << std::endl;
			return false;
		}

		bool switch_rom(char* argv[])
		{
			opt_rom = std::string(argv[1]);
			return true;
		}

		bool switch_dont_save_rom(char* argv[])
		{
			opt_save_rom = false;
			return true;
		}

		bool switch_quiet(char* argv[])
		{
			opt_quiet = true;
			return true;
		}

		bool switch_log_to_file(char* argv[])
		{
			opt_log_to_file = true;
			return true;
		}

		std::map<std::string, switch_t> switches =
		{
			SWITCH("--help", "-h", 0, &switch_help),
			SWITCH("--rom", "-r", 1, &switch_rom),
			SWITCH("--dont-save", "-n", 0, &switch_dont_save_rom),
			SWITCH("--quiet", "-q", 0, &switch_quiet),
			SWITCH("--save-log", "-s", 0, &switch_log_to_file),
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

	std::string rom()
	{
		return opt_rom;
	}

	bool save_rom()
	{
		return opt_save_rom;
	}

	bool quiet()
	{
		return opt_quiet;
	}

	bool log_to_file()
	{
		return opt_log_to_file;
	}
}
