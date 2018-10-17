#pragma once

/** 
 *	����Base58 ͬ Base64 �������
 *  1. Base58 ������ֿ������������ֵ��ַ� 0OIl
 *  2. 
 */

#include "JKCommon/JKCommon.h"

BEGIN_JK_NAMESPACE

/**
 * �����ֽ�
 */
std::string EncodeBase58(const unsigned char* pbegin, const unsigned char* pend);
std::string EncodeBase58(const std::vector<unsigned char>& vch);

/**
 * ����psz��vchRet�У������Ƿ����ɹ�
 */
bool DecodeBase58(const char* psz, std::vector<unsigned char>& vchRet);

/**
 * ����str��vchRet��
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