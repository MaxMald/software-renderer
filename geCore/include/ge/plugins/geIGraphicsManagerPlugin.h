#pragma once

#include "ge/plugins/geIPlugin.h"

namespace ge
{
  class IGraphicsManager;

  class GE_CORE_EXPORT IGraphicsManagerPlugin : public IPlugin
  {
  public:
    virtual bool createGraphicsManager() = 0;
    virtual IGraphicsManager& getGraphicsManager() = 0;
  };
}
