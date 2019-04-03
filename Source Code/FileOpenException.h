//
//  FileOpenException.h
//
//  Created by Mihika Marathe
//  Copyright © 2019 Mihika Marathe
//  All rights reserved.

#include <exception>
#include <stdexcept>
#include <iostream>
#include <cmath>        // for sqrt()
#include <cstring>
#include <cstdlib>
#include <sstream>        // for istreamstream/ostringstream
#include <climits>        // for SHRT_MAX
#include <typeinfo>
#include <string>

#ifndef FileOpenException_h
#define FileOpenException_h

using namespace std;

class FileOpenException: public exception
{
private:
    const char * filename;
public:
    FileOpenException(const char* file): filename(file) {};
    const char* what() const noexcept override
    {
        return filename;
    }
};

#endif /* FileOpenException_h */


