#include "ge/plugins/geDXGraphicsPlugin.h"

namespace ge
{
  GE_DX_GRAPHICS_EXPORT IPlugin* createGraphicsPlugin()
  {
    return new DXGraphicsPlugin();
  }

  GE_DX_GRAPHICS_EXPORT void destroyGraphicsPlugin(IPlugin* plugin)
  {
    delete plugin;
  }

  DXGraphicsPlugin::DXGraphicsPlugin() :
    m_dxGraphics(nullptr)
  {}

  DXGraphicsPlugin::~DXGraphicsPlugin()
  {
    destroyGraphicsModule();
  }

  void DXGraphicsPlugin::onConnect()
  {}

  void DXGraphicsPlugin::onClose()
  {
    destroyGraphicsModule();
  }

  bool DXGraphicsPlugin::createGraphicsModule()
  {
    if (m_dxGraphics)
    {
      LogService::Warning(
        "Attempted to create graphics module, but it already exists."
      );
      return false;
    }

    m_dxGraphics = hc::MakeUnique<DXGraphics>();
    return true;
  }

  IGraphics& DXGraphicsPlugin::getGraphicsModule()
  {
    if (!m_dxGraphics)
      throw RuntimeErrorException(
        "Graphics module has not been created yet."
      );
    return *m_dxGraphics;
  }

  void DXGraphicsPlugin::destroyGraphicsModule()
  {
    if (m_dxGraphics)
      m_dxGraphics.reset();
  }
}