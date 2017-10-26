#include "JKGuid.h"
#include <iostream>

#ifdef _WIN32
#include <objbase.h>
#else
#include <uuid/uuid.h>
#endif

USING_JK_NAMESPACE

GUID JKGuid::CreateGuid()
{
	GUID guid;
#ifdef _WIN32
	CoCreateGuid(&guid);
#else
	uuid_generate(reinterpret_cast<unsigned char *>(&guid));
#endif
	return guid;
}

JKString JKGuid::GuidToString(const GUID &guid)
{
	char buf[64] = { 0 };
#ifdef __GNUC__
	snprintf(
#else // MSVC
	_snprintf_s(
#endif
		buf,
		sizeof(buf),
		"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	return JKString(buf);
}
