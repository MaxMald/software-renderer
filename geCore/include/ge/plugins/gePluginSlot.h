#pragma once

#include <Windows.h>
#include <libloaderapi.h>

#include "ge/geCorePrerequisites.h"
#include "ge/plugins/geIPlugin.h"

namespace ge
{
  class PluginSlot
  {
  public:
    PluginSlot();
    ~PluginSlot();

    bool connect(
      const String& key,
      const String& libraryName,
      const String& constructorFunctionName,
      const String& destructorFunctionName
    );
    const String& getKey() const;
    const String& getLibraryName() const;
    const String& getConstructorFunctionName() const;
    const String& getDestructorFunctionName() const;
    IPlugin& getPlugin();
    void close();

  private:
    /**
    * The name of the constructor function.
    */
    String m_constructorFunctionName;

    /**
    * The name of the destructor function.
    */
    String m_destructorFunctionName;

    /**
    * The Plug-in's key.
    */
    String m_key;

    /**
    * The library name of the plug-in.
    */
    String m_libraryName;

    /**
    * The instance of the plug-in.
    */
    HINSTANCE m_pluginHandler;

    /**
    * Pointer of the Plug-in interface.
    */
    IPlugin* m_pluginPtr;

    /**
    * Indicates if the plug-in slot is connected.
    */
    bool m_isConnected;

    /**
     * Checks if the specified library contains a destructor function with the
     * given name. Returns true if the function is found, otherwise returns false.
     *
     * @param destructorFunctionName The name of the destructor function to check for.
     * @param pluginHandle The handle to the loaded library.
     *
     * @return true if the destructor function is found in the library, otherwise false.
     */
    bool checkLibraryHasDestructorFunction(
      const String& destructorFunctionName,
      HINSTANCE pluginHandle
    ) const;
  };
}
