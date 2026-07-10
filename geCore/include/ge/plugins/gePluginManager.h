#pragma once

#include "ge/geCorePrerequisites.h"

namespace ge
{
  class IPlugin;
  class PluginSlot;

  /**
   * Central manager for dynamically loading, connecting, and unloading plugin
   * modules.Each plugin is identified by a unique key and must provide factory functions
   * for instantiation and destruction.
   */
  class GE_CORE_EXPORT PluginManager : public NonCopyable
  {
  public:
    PluginManager();
    ~PluginManager();

    /**
     * Initializes the PluginManager.
     */
    void initialize();

    /**
     * Attempts to connect to the specified plug-in.
     *
     * @param _key The plug-in key.
     * @param _libraryName The library name of the plug-in.
     * @param _constructorFunctionName The name of the function that builds the plug-in.
     * @param _destructorFunctionName The name of the function that destroys the plug-in.
     *
     * @return True if the plug-in was successfully connected, otherwise returns false.
     */
    bool connectPlugin(
      const String& _key,
      const String& _libraryName,
      const String& _constructorFunctionName,
      const String& _destructorFunctionName
    );

    /**
     * Unload a plug-in.
     *
     * @param _key The plug-in key.
     *
     * @return True if the plug-in was successfully closed, otherwise returns false.
     */
    bool closePlugin(const String& _key);

    /**
     * Disconnect all plug-ins.
     */
    void closeAll();

    /**
     * Indicates if a plug-in exists in this plug-in manager.
     *
     * @param _key Plug-in key.
     *
     * @return True if the plug-in exists, otherwise returns false.
     */
    bool hasPlugin(const String& _key);

    /**
     * Retrieves a reference to the plugin with the specified key.
     *
     * @param _key The unique identifier of the plugin to retrieve.
     *
     * @return A reference to the IPlugin instance.
     *
     * @throws RuntimeErrorException if no plugin with the given key exists or
     * if the plugin slot is null.
     */
    IPlugin& getPlugin(const String& _key);

  private:
    UnorderedMap<String, UniquePtr<PluginSlot>> m_pluginSlots;
  };
}
