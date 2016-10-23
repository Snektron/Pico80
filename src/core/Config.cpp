#include "core/Config.h"
#include <map>
#include <string>
#include <fstream>
#include <cstdlib>
#include "core/Logger.h"

#define TAG "Config"
#define IS_LETTER(x) ('a' <= (x) && (x) <= 'z')
#define IS_WS(x) ((x) == '\t' || (x) == ' ')
#define IS_NUMBER(x) ('0' <= (x) && (x) <= '9')

Config::Config(std::string file):
	file(file),
	create_config(true)
{
	parse();
}

bool Config::contains(std::string key)
{
	return objects.find(key) != objects.end();
}

bool Config::get_bool(std::string key, bool def)
{
	auto item = objects.find(key);
	if (item != objects.end())
	{
		if(item->second == "true")
			return true;
		else if(item->second == "false")
			return false;
	}
	objects[key] = def ? "true" : "false";
	return def;
}

int Config::get_int(std::string key, int def)
{
	auto item = objects.find(key);
	if (item != objects.end())
	{

		int n = 0, i = 0;
		while(IS_NUMBER(item->second[i]))
		{
			n *= 10;
			n += item->second[i] - '0';
			i++;
		}

		if (i != item->second.length())
			return def;
		return i;
	}
	objects[key] = std::to_string(def);
	return def;
}

std::string Config::get_string(std::string key, std::string def)
{
	auto item = objects.find(key);
	if (item != objects.end())
		return item->second;
	objects[key] = def;
	return def;
}

Config::~Config()
{
	if (!create_config)
		return;
	std::ofstream stream(file);
	if (!stream)
	{
		Logger::error(TAG) << "Failed creating default config file!" << Logger::endl;
		return;
	}

	Logger::debug(TAG) << "Creating default config file..." << Logger::endl;
	for (auto i = objects.begin(); i != objects.end(); i++)
		stream << i->first << " = " << i->second << std::endl;
	stream.close();
}

void Config::parse()
{
	std::ifstream stream(file);
	Logger::debug(TAG) << "Reading config file: " << file << Logger::endl;
	if (!stream)
	{
		Logger::info(TAG) << "Config file " << file << " not found, will be created on exit" <<Logger::endl;
		create_config = true;
		return;
	}

	std::string text;
	int line = 0;

	 while(getline(stream, text))
		 parse_line(++line, text);
	 stream.close();
}

void Config::debug_dump()
{
	for (auto i = objects.begin(); i != objects.end(); i++)
		Logger::debug(TAG) << "Key: " << i->first << " value: " << i->second << Logger::endl;
}

void Config::parse_line(int line, std::string text)
{
	std::string key = "";
	std::string value = "";

	int i = 0;

	while(IS_LETTER(text[i]))
	{
		key += text[i];
		i++;
	}

	if (key == "")
		Logger::error(TAG) << "Expecting key (line " << line << ")" << Logger::endl;

	while(IS_WS(text[i++]));

	if (text[i++] != '=')
	{
		Logger::error(TAG) << "Expecting '=' (line " << line << ")" << Logger::endl;
		return;
	}

	while(IS_WS(text[i++]));

	while(text[i])
	{
		value += text[i];
		i++;
	}

	if (value == "")
		Logger::error(TAG) << "Expecting value (line " << line << ")" << Logger::endl;

	Logger::debug(TAG) << "Key: " << key << " value: " << value << Logger::endl;
	if (contains(key))
		Logger::warn(TAG) << "Duplicate object " << key << Logger::endl;

	objects[key] = value;

}
