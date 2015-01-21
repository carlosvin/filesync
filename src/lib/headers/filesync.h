#ifndef filesync_H
#define filesync_H

#include <sstream>
#include <fstream>
#include <string>
#include <map>

class Performer
{
public:
	virtual ~Performer() = default;
	virtual void onFile(const char * path) = 0;
	virtual void onDir(const char * path) = 0;
};

class Filesystem
{
public:
    virtual ~Filesystem() = default;

    virtual void walk(Performer & performer) = 0;
};

// the types of the class factories
typedef Filesystem* create_t();
typedef void destroy_t(Filesystem*);

#include <iostream>

extern const void loadConfig(const char * cfgPath,
		std::map<std::string, std::string> & cfg) {
	std::cout << "reading " << cfgPath << std::endl;

	std::fstream iStreamFile(cfgPath);

	std::string line;
	while (std::getline(iStreamFile, line)) {
		std::istringstream is_line(line);
		std::string key;
		if (std::getline(is_line, key, '=')) {
			std::string value;
			if (std::getline(is_line, value))
				cfg[key] = value;
		}
	}
}

#endif
