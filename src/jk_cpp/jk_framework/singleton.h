#pragma once

#include "jk_common.h"

BEGIN_JK_NAMESPACE

template <class T>
class Singleton
{
public:
  static T & theInstance()
  {
    static T instance;

    return instance;
  }

protected:
	Singleton(){}

};


END_JK_NAMESPACE
