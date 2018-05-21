#pragma once

/** 
 *	编码Base58 同 Base64 的区别点
 *  1. Base58 不会出现看起来很难区分的字符 0OIl
 *  2. 
 */

#include "JKCommon/JKCommon.h"

BEGIN_JK_NAMESPACE

/**
 * 编码字节
 */
std::string EncodeBase58(const unsigned char* pbegin, const unsigned char* pend);
std::string EncodeBase58(const std::vector<unsigned char>& vch);

/**
 * 解码psz到vchRet中，返回是否解码成功
 */
bool DecodeBase58(const char* psz, std::vector<unsigned char>& vchRet);

/**
 * 解码str到vchRet中
 */
bool DecodeBase58(const std::string& str, std::vector<unsigned char>& vchRet);

/**
 * Encode a byte vector into a base58-encoded string, including checksum
 */
//std::string EncodeBase58Check(const std::vector<unsigned char>& vchIn);

/**
 * Decode a base58-encoded string (psz) that includes a checksum into a byte
 * vector (vchRet), return true if decoding is successful
 */
//bool DecodeBase58Check(const char* psz, std::vector<unsigned char>& vchRet);

/**
 * Decode a base58-encoded string (str) that includes a checksum into a byte
 * vector (vchRet), return true if decoding is successful
 */
bool DecodeBase58Check(const std::string& str, std::vector<unsigned char>& vchRet);

END_JK_NAMESPACE