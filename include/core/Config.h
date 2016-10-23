#ifndef INCLUDE_CORE_CONFIG_H_
#define INCLUDE_CORE_CONFIG_H_

#include <map>
#include <string>

class Config
{
private:
	std::string file;
	std::map<std::string, std::string> objects;
	bool create_config;

public:
	Config(std::string file);
	bool contains(std::string key);
	bool get_bool(std::string key, bool def);
	int get_int(std::string key, int def);
	std::string get_string(std::string key, std::string def);
	void debug_dump();
	~Config();

private:
	void parse();
	void parse_line(int line, std::string text);
};

#endif /* INCLUDE_SETTINGS_H_ */
