#include "jk_string.h"
#include "jk_common.h"
#include <string>
#include <algorithm>

using namespace jk_cpp;


bool JK_String::to_bool( string value )
{
	if ( "True" == value || "true" == value )
	{
		return true;
	}

	return false;
}

int	JK_String::to_int( string value )
{
	return atoi( value.c_str() );
}

dword	JK_String::to_dword( string value )
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

float	JK_String::to_float( string value )
{
	return (float)atof( value.c_str() );
}

double	JK_String::to_double( string value )
{
	return atof( value.c_str() );
}

interior_index JK_String::to_int64( string value )
{
	interior_index ret;

	string str_tmp = "0x" + value;

#ifdef LINUX26
	sscanf ( str_tmp.c_str(), "%llx" , &ret );
#else
	sscanf ( str_tmp.c_str(), "%I64x" , &ret );
#endif //LINUX26

		return ret;
}

wstring	JK_String::to_wstring( string value )
{
	setlocale ( LC_ALL, ".ACP" );
	int required_size = mbstowcs ( NULL, value.c_str(), 0 );
	wchar_t* wide_string = new wchar_t[ required_size + 1 ];
	mbstowcs ( wide_string, value.c_str(), required_size + 1 );

	wstring ret_string = wide_string;

	AUTO_DELETE ( wide_string );

	return ret_string;
}

// from
string	JK_String::from_bool( bool value )
{
	if ( value )
	{
		return string( "true" );
	}

	return string( "false" );
}

string	JK_String::from_int( int value )
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

string	JK_String::from_dword( dword value )
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

string	JK_String::from_float( float value )
{
	char value_text[64];
	memset( value_text, 0, 64 );

	sprintf( value_text, "%f", value );

	return string( value_text );
}

string	JK_String::from_double( double value )
{
	char value_text[128];
	memset( value_text, 0, 128 );

	sprintf( value_text, "%.16f", value );

	return string( value_text );
}

string JK_String::from_int64( interior_index value )
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


string	JK_String::from_wstring( wstring value )
{
	setlocale ( LC_ALL, ".ACP" );

	int required_size = wcstombs ( NULL, value.c_str(), 0 );
	char* mb_str = new char[ required_size + 1 ];
	wcstombs ( mb_str, value.c_str(), required_size + 1 );

	string ret_string = mb_str;

	AUTO_DELETE ( mb_str );

	return ret_string;
}

bool JK_String::wto_bool( wstring value )
{
	if ( L"True" == value || L"true" == value )
	{
		return true;
	}

	return false;
}

int JK_String::wto_int( wstring value )
{
	string mb_str = JK_String::from_wstring ( value );

	return JK_String::to_int ( mb_str );
}

dword JK_String::wto_dword( wstring value )
{
	string mb_str = JK_String::from_wstring ( value );

	return JK_String::to_dword ( mb_str );
}

float JK_String::wto_float( wstring value )
{
	string mb_str = JK_String::from_wstring ( value );

	return JK_String::to_float( mb_str );
}

double JK_String::wto_double( wstring value )
{
	string mb_str = JK_String::from_wstring ( value );

	return JK_String::to_double( mb_str );
}

interior_index	JK_String::wto_int64( wstring value )
{
	__int64 idx = 0;

	const wchar_t* buf = value.c_str();

	int size = value.size();
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
wstring	JK_String::wfrom_bool( bool value )
{
	if ( value )
	{
		return wstring( L"true" );
	}

	return wstring( L"false" );
}

wstring	JK_String::wfrom_int( int value )
{
	string mb_str = JK_String::from_int ( value );

	return JK_String::to_wstring( mb_str );
}

   wstring JK_String::wfrom_dword ( dword value )
{
	string mb_str = JK_String::from_dword( value );

	return JK_String::to_wstring( mb_str );
}

   wstring JK_String::wfrom_float ( float value )
{
	string mb_str = JK_String::from_float( value );

	return JK_String::to_wstring( mb_str );
}

wstring	JK_String::wfrom_double( double value )
{
	string mb_str = JK_String::from_double( value );

	return JK_String::to_wstring( mb_str );
}

   wstring JK_String::wfrom_int64 ( interior_index value )
{
	string mb_str = JK_String::from_int64( value );

	return JK_String::to_wstring( mb_str );
}

