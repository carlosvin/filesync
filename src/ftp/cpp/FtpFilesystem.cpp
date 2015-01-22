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
	istream & is = _ftp->beginList(path, false);

	string line;
	vector<string> fileList;
	while (std::getline(is, line)) {
		fileList.push_back(line);
		cout << line << ",";
	}

	_ftp->endList();
	cout << endl;


	if (fileList.size() == 1) {
		string d = fileList.front();

		cout << d.size() << " == " << path.size() << endl;

		if (d == path) {
			cout << "'" << d << "'" << " == " << "'" << path << "'" << endl;
			// is a file
			performer.onFile(path.c_str());
		} else {
			cout << "'" << d << "'" << " != " << "'" << path << "'" << endl;
			// current file is a directory
			performer.onDir(path.c_str());
			walk(performer, d);
		}
	} else {
		// current file is a directory
		performer.onDir(path.c_str());

		for (auto file : fileList) {
			walk(performer, file);
			//performer.onDir(d.c_str());
			//_ftp->setWorkingDirectory(d);
			//walk(performer);
		}

	}

}

