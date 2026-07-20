#include "ge/graphics/geDXGraphics.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace ge
{  
  DXGraphics::DXGraphics(void* source)
  {
    auto hwnd = static_cast<HWND>(source);

    RECT rc;
    GetClientRect(hwnd, &rc);

    Int32 width = rc.right - rc.left;
    Int32 height = rc.bottom - rc.top;

    Vector<IDXGIAdapter1*> adapters = getAdapters();
    adapters.size();
  }

  DXGraphics::~DXGraphics()
  {}

  Vector<IDXGIAdapter1*> DXGraphics::getAdapters()
  {
    Vector<IDXGIAdapter1*> adapters;

    IDXGIFactory1* dxgiFactory = nullptr;
    IDXGIAdapter1* adapter = nullptr;

    // Enumerate adapters
    CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&dxgiFactory);
    UInt32 adapterIndex = 0;

    while (dxgiFactory->EnumAdapters1(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND)
    {
      DXGI_ADAPTER_DESC1 desc;
      adapter->GetDesc1(&desc);

      adapters.push_back(adapter);
      ++adapterIndex;
    }

    return adapters;
  }
}