#ifndef _JK_STRING_H_
#define _JK_STRING_H_

#include "lib_jk.h"
#include <string>
#include <vector>


using namespace std;

typedef __int64 interior_index;
typedef unsigned long dword;

namespace JK_CPP_FUNC
{

	class JKAPI JK_String
	{
	public:
		JK_String( void );
		~JK_String( void );

	public:
		static bool		to_bool( string value );

		static int		to_int ( string value );// base = 10

		static dword    to_dword ( string value );// base = 16

		static float	to_float( string value );

		static double	to_double( string value );

		static interior_index  to_int64( string value );// base = 16

		static wstring  to_wstring ( string value );

	public:
		static string	from_bool( bool value );

		static string   from_int ( int value );// base = 10

		static string   from_dword ( dword value );// base = 16

		static string	from_float( float value );

		static string	from_double( double value );

		static string   from_int64 ( interior_index value );// base = 16

		static string   from_wstring ( wstring value );


	public:
		static bool		wto_bool( wstring value );

		static int		wto_int( wstring value );

		static dword	wto_dword( wstring value );

		static float	wto_float( wstring value );

		static double	wto_double( wstring value );

		static interior_index	wto_int64( wstring value );

	public:
		static wstring	wfrom_bool( bool value );

		static wstring	wfrom_int( int value );

		static wstring	wfrom_dword( dword value );

		static wstring	wfrom_float( float value );

		static wstring	wfrom_double( double value );

		static wstring	wfrom_int64( interior_index value );

	};


}



#endif  //_JK_STRING_H_