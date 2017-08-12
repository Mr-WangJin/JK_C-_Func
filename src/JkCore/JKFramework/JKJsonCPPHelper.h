#pragma once

#include <JKCommon\JKCommon.h>
#include <JKFramework\SmartPtr\JKRef_Ptr.h>

BEGIN_JK_NAMESPACE


//template<typename T>
//class JK_API JKJsonValue
//{
//public:
//	JKJsonValue();
//	virtual ~JKJsonValue();
//
//public:
//	T value;
//
//};
//
//template<typename T>
//JKJsonValue<T>::JKJsonValue()
//{
//
//}
//
//template<typename T>
//JKJsonValue<T>::~JKJsonValue()
//{
//
//}

#define JsonCppWriteValue(obj, XXX) obj[#XXX] = XXX;
		
//#define JsonCppParseBegin(val) for (Value::ConstMemberIterator itr = val.MemberBegin(); itr != val.MemberEnd(); ++itr){
//#define JsonCppParseEnd()  }

#define JsonCppParseToString(obj, XXX) if (obj.isMember(#XXX)) XXX = obj[#XXX].asString();
#define JsonCppParseToInt(obj, XXX) if (obj.isMember(#XXX)) XXX = obj[#XXX].asInt();
#define JsonCppParseToInt64(obj, XXX) if (obj.isMember(#XXX)) XXX = obj[#XXX].asInt64();
#define JsonCppParseToUInt(obj, XXX)  if (obj.isMember(#XXX)) XXX = obj[#XXX].asUint();
#define JsonCppParseToUint64(obj, XXX) if (obj.isMember(#XXX)) XXX = obj[#XXX].asUint64();
#define JsonCppParseToDouble(obj, XXX) if (obj.isMember(#XXX)) XXX = obj[#XXX].asDouble();
#define JsonCppParseToClass(obj, XXX) if (obj.isMember(#XXX)) XXX->ParseJson(obj[#XXX]);
//#define JsonCppParseToChar(obj, XXX) if (strcmp(itr->name.GetString(), #XXX) == 0)\
//{\
//	int size = ARRAY_SIZE(XXX);\
//	const char *s = itr->value.GetString();\
//	int len = strlen(s);\
//	strncpy(XXX, s, std::min(size, len));\
//}\


template<typename T>
class JK_API JKJsonCPPBase
{
public:
	virtual void ParseJson(const T& val) {};

};

/*

class JK_API JKJsonCPPBase
{
public:

	JKJsonCPPBase() {}
	~JKJsonCPPBase() {}

	std::string ToJson();
	static void FromJson(JKJsonCPPBase *p, const std::string &json);


protected:

	//template<typename T>
	//static	void ToWriteEvery(Writer<StringBuffer>  &writer, T &val) {
	//	JKJsonCPPBase *p = &val;
	//	p->ToWrite(writer);
	//}
	static	void ToWriteEvery(Json::Value  &writer, int32_t &val);
	//static	void ToWriteEvery(Writer<StringBuffer>  &writer, int64_t &val);
	//static	void ToWriteEvery(Writer<StringBuffer>  &writer, uint32_t &val);
	//static	void ToWriteEvery(Writer<StringBuffer>  &writer, uint64_t &val);
	//static	void ToWriteEvery(Writer<StringBuffer>  &writer, double &val);
	//static	void ToWriteEvery(Writer<StringBuffer>  &writer, bool &val);
	//static	void ToWriteEvery(Writer<StringBuffer>  &writer, std::string &val);
	//static	void ToWriteEvery(Writer<StringBuffer>  &writer, char * val);


	template<typename T>
	static	void ToParseEvery(const Value &val, T &t)
	{
		JKJsonCPPBase *p = &t;
		p->ParseJson(val);
	}

	//static	void ToParseEvery(const Value &val, int32_t &t);
	//static	void ToParseEvery(const Value &val, int64_t &t);
	//static	void ToParseEvery(const Value &val, uint32_t &t);
	//static	void ToParseEvery(const Value &val, uint64_t &t);
	//static	void ToParseEvery(const Value &val, double &t);
	//static	void ToParseEvery(const Value &val, bool &t);
	//static	void ToParseEvery(const Value &val, std::string &t);
	//static	void ToParseEvery(const Value &val, char t[]);







public:
	//virtual void ToWrite(Writer<StringBuffer>  &writer);
	//virtual void ParseJson(const Value& val);
};

template<typename T>
class JsonArray :public JKJsonCPPBase
{
public:

	std::list<T> arr;
	JsonArray() {}
	~JsonArray() {}



public:
	virtual void ToWrite(Writer<StringBuffer>  &writer)
	{
		writer.StartArray();
		for each (T ent in arr)
		{
			ToWriteEvery(writer, ent);
		}
		writer.EndArray();
	}

	virtual void ParseJson(const Value& val)
	{
		SizeType len = val.Size();
		for (size_t i = 0; i < len; i++)
		{
			const Value &f = val[i];
			T t;
			ToParseEvery(f, t);
			arr.push_back(t);
		}
	}
};
*/



END_JK_NAMESPACE



