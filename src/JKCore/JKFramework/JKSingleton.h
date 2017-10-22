#pragma once

#include "JKCommon/JKCommon.h"

BEGIN_JK_NAMESPACE

template <typename T>
class JK_API JKSingleton
{
public:
	JKSingleton() {};

public:
  static T & GetInstance()
  {
    static T instance;

    return instance;
  }

protected:
	JK_DISABLE_COPY(JKSingleton)

};


END_JK_NAMESPACE
