#include "JKJsonCPPHelper.h"

USING_JK_NAMESPACE






//void JKJsonCPPBase::ToWriteEvery(Json::Value  &writer, int32_t &val)
//{
//	//writer[];
//}
//void JKJsonCPPBase::ToWriteEvery(Writer<StringBuffer>  &writer, int64_t &val)
//{
//	writer.Int64(val);
//}
//void JKJsonCPPBase::ToWriteEvery(Writer<StringBuffer>  &writer, uint32_t &val)
//{
//	writer.Uint(val);
//}
//void JKJsonCPPBase::ToWriteEvery(Writer<StringBuffer>  &writer, uint64_t &val)
//{
//	writer.Uint64(val);
//}
//void JKJsonCPPBase::ToWriteEvery(Writer<StringBuffer>  &writer, double &val)
//{
//	writer.Double(val);
//}
//void JKJsonCPPBase::ToWriteEvery(Writer<StringBuffer>  &writer, bool &val)
//{
//	writer.Bool(val);
//}
//void JKJsonCPPBase::ToWriteEvery(Writer<StringBuffer>  &writer, std::string &val)
//{
//	writer.String(val.data());
//}
//void JKJsonCPPBase::ToWriteEvery(Writer<StringBuffer>  &writer, char * val)
//{
//	writer.String(val, strlen(val));
//}
//
//

//
//
//void JKJsonCPPBase::ToParseEvery(const Value &val, int32_t &t)
//{
//	t = val.GetInt();
//}
//void JKJsonCPPBase::ToParseEvery(const Value &val, int64_t &t)
//{
//	t = val.GetInt64();
//}
//void JKJsonCPPBase::ToParseEvery(const Value &val, uint32_t &t)
//{
//	t = val.GetUint();
//}
//void JKJsonCPPBase::ToParseEvery(const Value &val, uint64_t &t)
//{
//	t = val.GetUint64();
//}
//void JKJsonCPPBase::ToParseEvery(const Value &val, double &t)
//{
//	t = val.GetDouble();
//}
//void JKJsonCPPBase::ToParseEvery(const Value &val, bool &t)
//{
//	t = val.GetBool();
//}
//void JKJsonCPPBase::ToParseEvery(const Value &val, std::string &t)
//{
//	t = val.GetString();
//}
//void JKJsonCPPBase::ToParseEvery(const Value &val, char t[])
//{
//	int size = ARRAY_SIZE(t);
//	const char *s = val.GetString();
//	int len = strlen(s);
//	strncpy(t, s, std::min(size, len));
//}
//
//
//
//
//std::string JKJsonCPPBase::ToJson() {
//	StringBuffer s;
//	Writer<StringBuffer> writer(s);
//	this->ToWrite(writer);
//	return s.GetString();
//}
//
//void JKJsonCPPBase::FromJson(JKJsonCPPBase *p, const std::string &json) {
//	Document document;
//	document.Parse(json.data());
//	const Value &val = document;
//	p->ParseJson(val);
//}


//void	JKJsonCPPBase::ToWrite(Writer<StringBuffer>  &writer)
//{
//
//}
//void JKJsonCPPBase::ParseJson(const Value& val)
//{
//
//
//
//}