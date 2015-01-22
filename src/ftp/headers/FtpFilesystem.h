/*
 * FtpFilesystem.h
 *
 *  Created on: 15/1/2015
 *      Author: carlos
 */

#ifndef FTPFILESYSTEM_H_
#define FTPFILESYSTEM_H_

#include "filesync.h"
#include <memory>
#include <vector>
#include <Poco/Path.h>
#include <Poco/Net/FTPClientSession.h>

class FtpFilesystem: public Filesystem{
private:
	Poco::Path _path;
	std::unique_ptr<Poco::Net::FTPClientSession> _ftp;

	void walk(Performer & performer, const  std::string & path);

public:

	FtpFilesystem();

	virtual ~FtpFilesystem();

    virtual void walk(Performer & performer);
};


// the class factories

extern "C" Filesystem* create() {
    return new FtpFilesystem;
}

extern "C" void destroy(Filesystem * p) {
    delete p;
}

#endif /* FTPFILESYSTEM_H_ */
