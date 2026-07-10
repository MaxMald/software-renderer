#pragma once

#include <ge/plugins/geIGraphicsPlugin.h>
#include "ge/geDXGraphicsPrerequisites.h"
#include "ge/graphics/geDXGraphics.h"

namespace ge
{
  extern "C"
  {
    GE_DX_GRAPHICS_EXPORT IPlugin* createGraphicsPlugin();
    GE_DX_GRAPHICS_EXPORT void destroyGraphicsPlugin(IPlugin* plugin);
  }

  class DXGraphicsPlugin : public IGraphicsPlugin
  {
  public:
    DXGraphicsPlugin();
    virtual ~DXGraphicsPlugin();

    virtual void onConnect() override;
    virtual void onClose() override;
    virtual bool createGraphicsModule() override;
    virtual IGraphics& getGraphicsModule() override;

  private:
    UniquePtr<DXGraphics> m_dxGraphics;

    void destroyGraphicsModule();
  };
}