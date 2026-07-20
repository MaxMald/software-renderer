#pragma once

// DX Graphics export macros
#if GE_PLATFORM == GE_PLATFORM_WIN32
# if GE_COMPILER == GE_COMPILER_MSVC || GE_COMPILER == GE_COMPILER_GNUC || GE_COMPILER == GE_COMPILER_INTEL
#   if defined(GE_STATIC_LIB)
#     define GE_DX_GRAPHICS_EXPORT
#   else
#     if defined(geDXGraphics_EXPORTS)
#       define GE_DX_GRAPHICS_EXPORT __declspec(dllexport)
#     else
#       define GE_DX_GRAPHICS_EXPORT __declspec(dllimport)
#     endif
#   endif
# endif
# define GE_DX_GRAPHICS_HIDDEN
#else // Linux / Mac
# if defined(GE_STATIC_LIB)
#  define GE_DX_GRAPHICS_EXPORT
#  define GE_DX_GRAPHICS_HIDDEN
# else
#  define GE_DX_GRAPHICS_EXPORT __attribute__ ((visibility("default")))
#  define GE_DX_GRAPHICS_HIDDEN __attribute__ ((visibility("hidden")))
# endif
#endif

// DLL export for plug-ins
#if GE_PLATFORM == GE_PLATFORM_WIN32
# if GE_COMPILER == GE_COMPILER_MSVC || GE_COMPILER == GE_COMPILER_GNUC || GE_COMPILER == GE_COMPILER_INTEL
#   define GE_PLUGIN_EXPORT __declspec(dllexport)
# endif
# define GE_PLUGIN_HIDDEN
#else // Linux / Mac
# define GE_PLUGIN_EXPORT __attribute__ ((visibility("default")))
# define GE_PLUGIN_HIDDEN __attribute__ ((visibility("hidden")))
#endif

#include "hc/utilities/hcUtilities.h"

// Windows
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// Direct X Interfaces Switch
#define DX_VERSION_11_0 NOT_IN_USE
#define DX_VERSION_11_1 NOT_IN_USE
#define DX_VERSION_11_2 NOT_IN_USE
#define DX_VERSION_11_3 IN_USE
#define DX_VERSION_11_4 NOT_IN_USE

#if USING(DX_VERSION_11_0)
#include <d3d11.h>

using D3DDevice         = ID3D11Device;
using D3DDeviceContext  = ID3D11DeviceContext;
using SwapChain         = IDXGISwapChain;
using DXGIFactory       = IDXGIFactory1;
using DXGIDevice        = IDXGIDevice1;
using RenderTargetView  = ID3D11RenderTargetView;
using RasterizerState   = ID3D11RasterizerState;
using BlendState        = ID3D11BlendState;

#elif USING(DX_VERSION_11_1)
#include <d3d11_1.h>

using D3DDevice         = ID3D11Device1;
using D3DDeviceContext  = ID3D11DeviceContext1;
using SwapChain         = IDXGISwapChain1;
using DXGIFactory       = IDXGIFactory2;
using DXGIDevice        = IDXGIDevice2;
using RenderTargetView  = ID3D11RenderTargetView;
using RasterizerState   = ID3D11RasterizerState1;
using BlendState        = ID3D11BlendState1;

#elif USING(DX_VERSION_11_2)
#include <d3d11_2.h>

using D3DDevice         = ID3D11Device2;
using D3DDeviceContext  = ID3D11DeviceContext2;
using SwapChain         = IDXGISwapChain1;
using DXGIFactory       = IDXGIFactory2;
using DXGIDevice        = IDXGIDevice3;
using RenderTargetView  = ID3D11RenderTargetView;
using RasterizerState   = ID3D11RasterizerState1;
using BlendState        = ID3D11BlendState1;

#elif USING(DX_VERSION_11_3)
#include <d3d11_3.h>

using D3DDevice         = ID3D11Device3;
using D3DDeviceContext  = ID3D11DeviceContext3;
using SwapChain         = IDXGISwapChain2;
using DXGIFactory       = IDXGIFactory2;
using DXGIDevice        = IDXGIDevice3;
using RenderTargetView  = ID3D11RenderTargetView1;
using RasterizerState   = ID3D11RasterizerState2;
using BlendState        = ID3D11BlendState1;

#elif USING(DX_VERSION_11_4)
#include <d3d11_4.h>

using D3DDevice         = ID3D11Device3;
using D3DDeviceContext  = ID3D11DeviceContext3;
using SwapChain         = IDXGISwapChain2;
using DXGIFactory       = IDXGIFactory2;
using DXGIDevice        = IDXGIDevice3;
using RenderTargetView  = ID3D11RenderTargetView1;
using RasterizerState   = ID3D11RasterizerState2;
using BlendState        = ID3D11BlendState1;

#else
#error "No DirectX version defined."
#endif

