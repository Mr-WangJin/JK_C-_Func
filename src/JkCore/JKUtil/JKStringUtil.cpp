#include "JKStringUtil.h"
#include <algorithm>

using namespace JK_NAMESPACE;

bool JKStringUtil::to_bool( string value )
{
	if ( "True" == value || "true" == value )
	{
		return true;
	}

	return false;
}

int	JKStringUtil::to_int( string value )
{
	return atoi( value.c_str() );
}

dword	JKStringUtil::to_dword( string value )
{
	unsigned long total_value = 0;

	for ( int i = 0; i < (int)value.size(); i++ )
	{
		char a_char = value[i];

		long inter_result = 0;

		char upper_a = 'A';

		char lower_a = 'a';

		if ( !isdigit(a_char) )
		{
			if ( !islower(a_char) )
			{
				inter_result =  a_char + 10;

				inter_result -= upper_a;
			}
			else
			{
				inter_result =  a_char + 10;

				inter_result -=  lower_a;
			}				
		}
		else
		{
			inter_result = a_char - '0';
		}

		total_value *= 16;

		total_value += inter_result;
	}

	return total_value;
}

float	JKStringUtil::to_float( string value )
{
	return (float)atof( value.c_str() );
}

double	JKStringUtil::to_double( string value )
{
	return atof( value.c_str() );
}

interior_index JKStringUtil::to_int64( string value )
{
	interior_index ret;

	string str_tmp = "0x" + value;

#ifdef LINUX26
	sscanf ( str_tmp.c_str(), "%llx" , &ret );
#else
	sscanf_s ( str_tmp.c_str(), "%I64x" , &ret );
#endif //LINUX26

		return ret;
}

wstring	JKStringUtil::to_wstring( string value )
{
	setlocale ( LC_ALL, ".ACP" );
	int required_size = mbstowcs ( NULL, value.c_str(), (size_t)0 );
	wchar_t* wide_string = new wchar_t[ required_size + 1 ];
	mbstowcs ( wide_string, value.c_str(), required_size + 1 );

	wstring ret_string = wide_string;

	AUTO_DELETE ( wide_string );

	return ret_string;
}

// from
string	JKStringUtil::from_bool( bool value )
{
	if ( value )
	{
		return string( "true" );
	}

	return string( "false" );
}

string	JKStringUtil::from_int( int value )
{
	char value_text[16];
	memset( value_text, 0, 16 );

#ifdef LINUX26
	sprintf ( value_text, "%d", value );

	return string ( value_text );
#else
	return ltoa( value, value_text, 10 );
#endif //LINUX26
}

string	JKStringUtil::from_dword( dword value )
{
	char value_text[16];
	memset( value_text, 0, 16 );

#ifdef LINUX26
	sprintf ( value_text, "%x", value );

	return string ( value_text );
#else
	return ultoa( value, value_text , 16 );
#endif //LINUX26
}

string	JKStringUtil::from_float( float value )
{
	char value_text[64];
	memset( value_text, 0, 64 );

	sprintf( value_text, "%f", value );

	return string( value_text );
}

string	JKStringUtil::from_double( double value )
{
	char value_text[128];
	memset( value_text, 0, 128 );

	sprintf( value_text, "%.16f", value );

	return string( value_text );
}

string JKStringUtil::from_int64( interior_index value )
{
	char str_i64[64];
	memset( str_i64, 0, 64 );

#ifdef LINUX26
	sprintf ( str_i64, "%llx", value );

	return string ( str_i64 );
#else
	return _i64toa( value, str_i64, 16 );
#endif //LINUX26
}


string	JKStringUtil::from_wstring( wstring value )
{
	setlocale ( LC_ALL, ".ACP" );

	int required_size = wcstombs ( NULL, value.c_str(), 0 );
	char* mb_str = new char[ required_size + 1 ];
	wcstombs ( mb_str, value.c_str(), required_size + 1 );

	string ret_string = mb_str;

	AUTO_DELETE ( mb_str );

	return ret_string;
}

bool JKStringUtil::wto_bool( wstring value )
{
	if ( L"True" == value || L"true" == value )
	{
		return true;
	}

	return false;
}

int JKStringUtil::wto_int( wstring value )
{
	string mb_str = JKStringUtil::from_wstring ( value );

	return JKStringUtil::to_int ( mb_str );
}

dword JKStringUtil::wto_dword( wstring value )
{
	string mb_str = JKStringUtil::from_wstring ( value );

	return JKStringUtil::to_dword ( mb_str );
}

float JKStringUtil::wto_float( wstring value )
{
	string mb_str = JKStringUtil::from_wstring ( value );

	return JKStringUtil::to_float( mb_str );
}

double JKStringUtil::wto_double( wstring value )
{
	string mb_str = JKStringUtil::from_wstring ( value );

	return JKStringUtil::to_double( mb_str );
}

interior_index	JKStringUtil::wto_int64( wstring value )
{
	__int64 idx = 0;

	const wchar_t* buf = value.c_str();

	size_t size = value.size();
	unsigned short tmp = 0;
	for( int ni = 0; ni < size; ni++ )
	{
		tmp = (unsigned short)(buf[ni]);
		if ( tmp > 47 && tmp < 58 )
		{
			tmp -= '0';
		}
		else if ( tmp > 64 && tmp < 71 )
		{
			tmp -= 55;
		}
		else if ( tmp > 96 && tmp < 103 )
		{
			tmp -= 87;
		}
		else 
		{
			return 0;
		}

		idx += ((__int64)tmp)<<((size-ni-1)*4);
	}

	return idx;
}

// w from
wstring	JKStringUtil::wfrom_bool( bool value )
{
	if ( value )
	{
		return wstring( L"true" );
	}

	return wstring( L"false" );
}

wstring	JKStringUtil::wfrom_int( int value )
{
	string mb_str = JKStringUtil::from_int ( value );

	return JKStringUtil::to_wstring( mb_str );
}

   wstring JKStringUtil::wfrom_dword ( dword value )
{
	string mb_str = JKStringUtil::from_dword( value );

	return JKStringUtil::to_wstring( mb_str );
}

   wstring JKStringUtil::wfrom_float ( float value )
{
	string mb_str = JKStringUtil::from_float( value );

	return JKStringUtil::to_wstring( mb_str );
}

wstring	JKStringUtil::wfrom_double( double value )
{
	string mb_str = JKStringUtil::from_double( value );

	return JKStringUtil::to_wstring( mb_str );
}

   wstring JKStringUtil::wfrom_int64 ( interior_index value )
{
	string mb_str = JKStringUtil::from_int64( value );

	return JKStringUtil::to_wstring( mb_str );
}

