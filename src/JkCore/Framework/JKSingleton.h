#pragma once

#include "Common/JKCommon.h"

BEGIN_JK_NAMESPACE

template <class T>
class JKSingleton
{
public:
  static T & GetInstance()
  {
    static T instance;

    return instance;
  }

protected:
	JKSingleton(){}

};


END_JK_NAMESPACE
