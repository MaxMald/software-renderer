#pragma once

#include "ge/geCorePrerequisites.h"

namespace ge
{
  class GE_CORE_EXPORT IGraphics
  {
  public:
    virtual ~IGraphics();

  protected:
    IGraphics();
  };
}