#include "ge/plugins/gePluginManager.h"
#include "ge/plugins/gePluginSlot.h"
#include "ge/plugins/geIPlugin.h"

namespace ge
{
  PluginManager::PluginManager() :
    m_pluginSlots()
  {}

  PluginManager::~PluginManager()
  {
    closeAll();
  }

  void PluginManager::initialize()
  {
    // Intentionally left empty. Initialization logic can be added here if needed in the
    // future.
  }

  bool PluginManager::connectPlugin(
    const String& _key,
    const String& _libraryName,
    const String& _constructorFunctionName,
    const String& _destructorFunctionName
  )
  {
    if (hasPlugin(_key))
    {
      LogService::Error(
        String::Format(
          "Cannot connect to plugin. Plugin with key '%s' already exists.",
          _key.c_str()
        )
      );

      return false;
    }

    UniquePtr<PluginSlot> pluginSlot = hc::MakeUnique<PluginSlot>();
    bool connected = pluginSlot->connect
    (
      _key,
      _libraryName,
      _constructorFunctionName,
      _destructorFunctionName
    );

    if (!connected)
      return false;

    m_pluginSlots.insert({ _key, std::move(pluginSlot) });
    return connected;
  }

  bool PluginManager::closePlugin(const String& _key)
  {
    auto it = m_pluginSlots.find(_key);
    if (it == m_pluginSlots.end())
      return false;

    PluginSlot* pluginSlotPtr = it->second.get();
    if (pluginSlotPtr)
      pluginSlotPtr->close();

    m_pluginSlots.erase(it);
    return true;
  }

  void PluginManager::closeAll()
  {
    for (auto& [key, pPluginSlot] : m_pluginSlots)
    {
      if (pPluginSlot)
        pPluginSlot->close();
    }

    m_pluginSlots.clear();
  }

  bool PluginManager::hasPlugin(const String& _key)
  {
    return m_pluginSlots.find(_key) != m_pluginSlots.end();
  }

  IPlugin& PluginManager::getPlugin(const String& _key)
  {
    auto it = m_pluginSlots.find(_key);
    if (it == m_pluginSlots.end())
      throw RuntimeErrorException("Plugin with key '" + _key + "' not found.");

    PluginSlot* pluginSlotPtr = it->second.get();
    if (!pluginSlotPtr)
      throw RuntimeErrorException("Plugin slot for key '" + _key + "' is null.");

    return pluginSlotPtr->getPlugin();
  }
}
