## uriparse ##

[![Build Status](https://travis-ci.org/whiler/uriparse.svg?branch=master)](https://travis-ci.org/whiler/uriparse) [![Coverage Status](https://coveralls.io/repos/github/whiler/uriparse/badge.svg?branch=master&service=github)](https://coveralls.io/github/whiler/uriparse?branch=master)

URI parsing implementation in C. parse URI fields like urlparse.urlparse in Python.

### usage ###
	#include <assert.h>
	#include <string.h>
	#include "uriparse.h"
	
	int main(int argc, const char *argv[]) {
		struct uri uri = {0};
		int rc = 0;
	
		rc = uriparse("mysql://root:e4D8F6z3f2b1@localhost:3306/account?charset=utf8mb4#debug", &uri);
	
		assert(0 == rc);
		assert(0 == strcmp("mysql", uri.scheme));
		assert(0 == strcmp("root", uri.user));
		assert(0 == strcmp("e4D8F6z3f2b1", uri.passwd));
		assert(0 == strcmp("localhost", uri.host));
		assert(0 == strcmp("3306", uri.port));
		assert(0 == strcmp("/account", uri.path));
		assert(0 == strcmp("charset=utf8mb4", uri.query));
		assert(0 == strcmp("debug", uri.fragment));
	
		return 0;
	}

### syntax ###
*scheme:[//[user[:password]@]host[:port]][/path][?query][#fragment]*

### tests ###
see [test.c](src/test.c) .

### license ###
This project is licensed under the MIT License.
