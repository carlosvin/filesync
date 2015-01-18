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
	loadConfig("cfg/ftp.cfg", cfgMap);

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
}

