#pragma once

#include "ge/plugins/geIPlugin.h"

namespace ge
{
  class IGraphics;

  class GE_CORE_EXPORT IGraphicsPlugin : public IPlugin
  {
  public:
    virtual ~IGraphicsPlugin();
    virtual bool createGraphicsModule() = 0;
    virtual IGraphics& getGraphicsModule() = 0;

  protected:
    IGraphicsPlugin();
  };
}
