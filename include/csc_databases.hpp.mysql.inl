#pragma once

#ifndef __CSC_DATABASES__
#error "��(�á㧥�� ;)�� : required csc_databases.hpp"
#endif

#ifndef __CSC_STRICTHPPINL__
#include <mysql.h>
#ifdef __CSC_DEBUG__
#pragma comment (lib ,"libmysqld.lib")
#else
#pragma comment (lib ,"libmysql.lib")
#endif
#endif

#ifndef _mysql_h
#error "��(�á㧥�� ;)�� : required mysql.h"
#endif

namespace CSC {

} ;