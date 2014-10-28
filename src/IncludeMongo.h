#pragma once

#if defined(_WIN32)
#include <winsock2.h>
#include <windows.h>
#endif

#pragma warning(push, 0)        
#include <mongo/client/dbclient.h>
#include <mongo/bson/bson.h>
#pragma warning(pop)
