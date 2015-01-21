/*
 * FtpFilesystem.cpp
 *
 *  Created on: 15/1/2015
 *      Author: carlos
 */

#include "../../ftp/headers/FtpFilesystem.h"

#include <map>
#include <iostream>

using namespace Poco::Net;
using namespace std;

FtpFilesystem::FtpFilesystem()
{
	map<string, string> cfgMap;
	loadConfig("conf/ftp.cfg", cfgMap);

	for (auto& kv : cfgMap)
	{
	    cout << kv.first << " = " << kv.second << endl;
	}

    cout << "Cfg read" << endl;


	_ftp = unique_ptr<FTPClientSession>(new FTPClientSession(cfgMap["host"]));

	_ftp->login(cfgMap["username"], cfgMap["password"]);

	_ftp->setWorkingDirectory(cfgMap["working_directory"]);
}

FtpFilesystem::~FtpFilesystem()
{
}

void FtpFilesystem::walk(Performer & performer)
{

	performer.onDir(_ftp->getWorkingDirectory().c_str());
	istream & is = _ftp->beginList();
	string line;
	while (std::getline(is, line))
	{
		performer.onDir(line.c_str());
	}

	_ftp->endList();
}

