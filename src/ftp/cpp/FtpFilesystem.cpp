/*
 * FtpFilesystem.cpp
 *
 *  Created on: 15/1/2015
 *      Author: carlos
 */

#include "../../ftp/headers/FtpFilesystem.h"

#include <map>
#include <iostream>
#include <vector>
#include <Poco/Net/NetException.h>

using namespace Poco::Net;
using namespace std;

FtpFilesystem::FtpFilesystem() {
	map<string, string> cfgMap;
	loadConfig("conf/ftp.cfg", cfgMap);

	for (auto& kv : cfgMap) {
		cout << kv.first << " = " << kv.second << endl;
	}

	cout << "Cfg read" << endl;

	_ftp = unique_ptr<FTPClientSession>(new FTPClientSession(cfgMap["host"]));

	_ftp->login(cfgMap["username"], cfgMap["password"]);

	_ftp->setWorkingDirectory(cfgMap["working_directory"]);

	//_ftp->setFileType(FTPClientSession::TYPE_TEXT);

}

FtpFilesystem::~FtpFilesystem() {
}

void FtpFilesystem::walk(Performer & performer) {

	walk(performer, _ftp->getWorkingDirectory());
}

void FtpFilesystem::walk(Performer & performer, const string & path) {
	vector<string> fileList = getFiles(path);

	if (isDir(path, fileList))
	{
		performer.onDir(path.c_str());
		for (auto file : fileList)
		{
			walk(performer, file);
		}
	}else{
		performer.onFile(path.c_str());
	}
}

vector<string> FtpFilesystem::getFiles(const string & path)
{
	vector<string> fileList{};
	try
	{
		istream & is = _ftp->beginList(path, false);
		string line;
		while (getline(is, line)) {
			size_t pos = line.find('\r');
			if (pos ==  string::npos)
			{
				fileList.push_back(line);
			}else
			{
				fileList.push_back(line.substr(0, pos));
			}
		}

		_ftp->endList();
	}
	catch (Poco::Net::FTPException & e)
	{
		cout << "reading " << path << " <- " << e.what() << endl;
		_ftp->endList();
	}

	return fileList;
}

bool FtpFilesystem::isDir(const string & path, vector<string> filesInside)
{
	return filesInside.size() != 1 || filesInside.front() != path;
}

