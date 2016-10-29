#ifndef INCLUDE_SETTINGS_H_
#define INCLUDE_SETTINGS_H_

#include <string>

namespace Settings
{
	bool parse_args(int argc, char* argv[]);

	std::string get_rom();
	bool save_rom();
};


#endif /* INCLUDE_SETTINGS_H_ */
