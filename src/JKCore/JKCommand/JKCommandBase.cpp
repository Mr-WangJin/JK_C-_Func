#include "JKCommandBase.h"

using namespace JK_NAMESPACE;

JKCommandBase::JKCommandBase( void )
{

}

JKCommandBase::~JKCommandBase( void )
{

}

bool JKCommandBase::execute( void )
{
	return true;
}

bool JKCommandBase::reverse_execute( void )
{
	return true;
}
