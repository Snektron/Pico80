#ifndef INCLUDE_SETTINGS_H_
#define INCLUDE_SETTINGS_H_

#include <string>

namespace Settings
{
	bool parse_args(int argc, char* argv[]);

	std::string rom();
	bool save_rom();
	bool quiet();
	bool log_to_file();
};


#endif /* INCLUDE_SETTINGS_H_ */
