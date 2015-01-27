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
#include <csignal>

using namespace std;

class PerformerImpl : public Performer
{
public:
	PerformerImpl(){}
	virtual ~PerformerImpl() {
		cout << " ~PerformerImpl" << endl;
	}

	virtual void onFile(const char * path)
	{
		cout << "file:\t" << path << endl;
	}
	virtual void onDir(const char * path)
	{
		cout << "dir:\t" << path << endl;
	}
};

class App
{
private:
	void * _lib;
	Filesystem * _fs;

public:
	App(const char * libName)
	{
		_lib = dlopen(libName, RTLD_LAZY);
		if (_lib)
		{
			create_t* create_filesystem= (create_t*) dlsym(_lib, "create");
			if (dlerror())
			{
				_fs = nullptr;
			}else
			{
				_fs = create_filesystem();
			}
		}else
		{
			_lib = nullptr;
		}
	}

	virtual ~App()
	{
		if (_lib)
		{
			destroy_t* destroy_filesystem = (destroy_t*) dlsym(_lib, "destroy");
			char * dlsym_error = dlerror();
			if (dlerror()) {
				cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
			}else if (_fs)
			{
				destroy_filesystem(_fs);
			}
		}
		cout << "~App" << endl;
	}

	void start()
	{
		PerformerImpl performer;
		_fs->walk(performer);
	}
};



void onStop (int signal)
{
	cout << "Caught SIGINT" << endl;
}


int main(void)
{
	signal(SIGINT, onStop);

	App app {"lib/libftp.so"};
	app.start();


	return 0;
}


