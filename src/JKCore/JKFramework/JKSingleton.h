#pragma once

#include "Common/JKCommon.h"

BEGIN_JK_NAMESPACE

template <class T>
class JK_API JKSingleton
{
public:
  static T & GetInstance()
  {
    static T instance;

    return instance;
  }

protected:
	JK_DISABLE_COPY(JKSingleton)
	JKSingleton(){}

};


END_JK_NAMESPACE
