/*
 * FtpFilesystem.h
 *
 *  Created on: 15/1/2015
 *      Author: carlos
 */

#ifndef FTPFILESYSTEM_H_
#define FTPFILESYSTEM_H_

#include "filesync.h"

class FtpFilesystem: public Filesystem {

public:
	FtpFilesystem();
	virtual ~FtpFilesystem();

	virtual void list();
};


// the class factories

extern "C" Filesystem* create() {
    return new FtpFilesystem;
}

extern "C" void destroy(Filesystem * p) {
    delete p;
}

#endif /* FTPFILESYSTEM_H_ */
