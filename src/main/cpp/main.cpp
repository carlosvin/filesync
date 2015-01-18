/*
 ============================================================================
 Name        : exampleProgram.c
 Author      : Carlos Martin
 Version     :
 Copyright   : CC
 Description : Uses shared library to print greeting
 To run the resulting executable the LD_LIBRARY_PATH must be
 set to ${project_loc}/libFileSync/.libs
 Alternatively, libtool creates a wrapper shell script in the
 build directory of this program which can be used to run it.
 Here the script will be called exampleProgram.
 ============================================================================
 */

#include "filesync.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <dlfcn.h>

using namespace std;

class Config {
public:
	vector<tuple<string, string>> mappings;
	Config() {
		mappings = {make_tuple("a", "b"), make_tuple("c", "d")};
	};
};

class PerformerImpl : public Performer
{
public:
	PerformerImpl(){}
	virtual ~PerformerImpl() {
		cout << " ~PerformerImpl" << endl;
	}

	virtual void onFile(const char * path)
	{
		cout << "file: " << path << endl;
	}
	virtual void onDir(const char * path)
	{
		cout << "dir: " << path << endl;
	}
};



int loadLibrary(const char * libName) {
	void* lib = dlopen(libName, RTLD_LAZY);
	if (!lib) {
		cerr << "Cannot load library " <<  libName << ": " << dlerror() << '\n';
		return 1;
	}

	// reset errors
	dlerror();

	// load the symbols
	create_t* create_filesystem= (create_t*) dlsym(lib, "create");
	const char* dlsym_error = dlerror();
	if (dlsym_error) {
		cerr << "Cannot load symbol create: " << dlsym_error << '\n';
		return 1;
	}

	destroy_t* destroy_filesystem = (destroy_t*) dlsym(lib, "destroy");
	dlsym_error = dlerror();
	if (dlsym_error) {
		cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
		return 1;
	}

	// create an instance of the class
	Filesystem * fs = create_filesystem();

	// use the class
	// TODO
	PerformerImpl performer;
	fs->walk(performer);

	// destroy the class
	destroy_filesystem(fs);

	// unload the triangle library
	dlclose(lib);

	return 0;
}

int main(void) {

	Config cfg { };
	for (auto x : cfg.mappings) {
		string from, to;
		std::tie(from, to) = x;
		cout << from << "->" << to << endl;
	}

	loadLibrary("lib/libftp.so");

	return 0;
}


