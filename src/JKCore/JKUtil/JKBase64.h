#pragma once

#include "JKCommon/JKCommon.h"
#include <iostream>
#include <string>

BEGIN_JK_NAMESPACE

    
static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(const char c)
{
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(const char * bytes_to_encode, unsigned int in_len);

std::string base64_decode(std::string const & encoded_string);

END_JK_NAMESPACE