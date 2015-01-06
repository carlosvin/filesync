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


using namespace std;

class Config
{
public:
	vector<tuple<string,string>> mappings;
	Config()
	{
		mappings = {make_tuple("a", "b"), make_tuple("c", "d")};
	};
};

int main(void)
{
	Config cfg {};
	for (auto x : cfg.mappings)
	{
		string from, to;
		std::tie(from, to) = x;
		cout << from << "->" <<  to << endl;
	}
	return 0;
}
