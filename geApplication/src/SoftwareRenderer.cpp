// SoftwareRenderer.cpp : Defines the entry point for the application.
//

#define NOMINMAX

#include <DirectXMath.h>
#include <iostream>
#include <filesystem>

using namespace DirectX;

#include "framework.h"
#include "SoftwareRenderer.h"
#include "Image.h"
#include "Texture.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND g_hWnd = nullptr;

// Render Target
Image g_renderTargetImage;
Texture g_renderTargetTexture;

// Loaded image
Image g_loadedImage;
Texture g_loadedImageTexture;

Vector3 RotatePointAround(const Vector3& point, const Vector3& pivot, float angleRad)
{
  float s = std::sin(angleRad);
  float c = std::cos(angleRad);
  Vector3 position = point - pivot;
  Vector3 rotatedPosition;

  rotatedPosition.x = position.x * c - position.y * s;
  rotatedPosition.y = position.x * s + position.y * c;
  rotatedPosition.z = position.z;
  return rotatedPosition + pivot;
}

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPWSTR    lpCmdLine,
  _In_ int       nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  // TODO: Place code here.

  // Initialize global strings
  LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW(hInstance, IDC_SOFTWARERENDERER, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  // Perform application initialization:
  if (!InitInstance(hInstance, nCmdShow))
  {
    return FALSE;
  }

  HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SOFTWARERENDERER));

  // Load Image and create texture

  std::filesystem::path path = std::filesystem::current_path();
  std::filesystem::path imagePath = path / "akira.bmp";

  g_loadedImage.load(imagePath.string().c_str());
  g_loadedImageTexture.create(g_loadedImage);

  // Create Shaders

  auto ps_shader = [](float u, float v) -> FColor
    {
      return g_loadedImageTexture.Sample(
        u,
        v,
        SAMPLE_FILTER::LINEAR,
        TEXTURE_ADDRESS_MODE::CLAMP
      );
    };

  auto ps_shader_white = [](float u, float v) -> FColor
    {
      return FColor(1.0f, 1.0f, 1.0f);
    };

  // Create Render Target with the same dimensions as the window

  RECT rc;
  GetClientRect(g_hWnd, &rc);

  g_renderTargetImage.create(rc.right - rc.left, rc.bottom - rc.top, 32);
  g_renderTargetTexture.create(g_renderTargetImage);
  auto& rtSurface = g_renderTargetTexture.getImage();

  // Rotation angle
  //float rotationAngle = XM_PI * 0.25f;
  float rotationAngle = 0;

  // Draw on render target

  Triangle tri;
  tri.v0.position = { 0.0f, 0.0f, 0.0f };
  tri.v0.uv = { 0.0f, 0.0f };
  tri.v1.position = { float(rtSurface.getWidth() - 1), 0.0f, 0.0f };
  tri.v1.uv = { 1.0f, 0.0f };
  tri.v2.position = { 0.0f, float(rtSurface.getHeight() - 1), 0.0f };
  tri.v2.uv = { 0.0f, 1.0f };

  // Rotate the triangle around the center of the render target
  Vector3 pivot = { float(rtSurface.getWidth()) / 2.0f, float(rtSurface.getHeight()) / 2.0f, 0.0f };
  tri.v0.position = RotatePointAround(tri.v0.position, pivot, rotationAngle);
  tri.v1.position = RotatePointAround(tri.v1.position, pivot, rotationAngle);
  tri.v2.position = RotatePointAround(tri.v2.position, pivot, rotationAngle);

  rtSurface.drawFilledTriangle(tri, ps_shader);

  Triangle tri2;
  tri2.v0.position = { float(rtSurface.getWidth() - 1), 0.0f, 0.0f };
  tri2.v0.uv = { 1.0f, 0.0f };
  tri2.v2.position = { float(rtSurface.getWidth() - 1), float(rtSurface.getHeight() - 1), 0.0f };
  tri2.v2.uv = { 1.0f, 1.0f };
  tri2.v1.position = { 0.0f, float(rtSurface.getHeight() - 1), 0.0f };
  tri2.v1.uv = { 0.0f, 1.0f };

  // Rotate the triangle around the center of the render target
  tri2.v0.position = RotatePointAround(tri2.v0.position, pivot, rotationAngle);
  tri2.v1.position = RotatePointAround(tri2.v1.position, pivot, rotationAngle);
  tri2.v2.position = RotatePointAround(tri2.v2.position, pivot, rotationAngle);

  rtSurface.drawFilledTriangle(tri2, ps_shader);

  ////////////////
  // operaciones con direct x, pero usa lo que quieras

  XMVECTOR v0 = XMVectorSet(0.0f, 0.5f, 0.0f, 1.0f);
  XMVECTOR v1 = XMVectorSet(0.5f, -0.5f, 0.0f, 1.0f);
  XMVECTOR v2 = XMVectorSet(-0.5f, -0.5f, 0.0f, 1.0f);

  // Convert to NCD

  XMVECTOR half = XMVectorSet(0.5f, 0.5f, 0.0f, 1.0f);
  XMVECTOR pv0 = XMVectorMultiplyAdd(v0, half, half);
  XMVECTOR pv1 = XMVectorMultiplyAdd(v1, half, half);
  XMVECTOR pv2 = XMVectorMultiplyAdd(v2, half, half);


  Vector3 fv0, fv1, fv2;
  fv0.x = XMVectorGetX(pv0) * rtSurface.getWidth();
  fv0.y = XMVectorGetY(pv0) * rtSurface.getHeight();
  fv0.y = 1.0f - fv0.y;
  fv0.z = XMVectorGetZ(pv0);

  fv1.x = XMVectorGetX(pv1) * rtSurface.getWidth();
  fv1.y = XMVectorGetY(pv1) * rtSurface.getHeight();
  fv1.y = 1.0f - fv1.y;
  fv1.z = XMVectorGetZ(pv1);

  fv2.x = XMVectorGetX(pv2) * rtSurface.getWidth();
  fv2.y = XMVectorGetY(pv2) * rtSurface.getHeight();
  fv2.y = 1.0f - fv2.y;
  fv2.z = XMVectorGetZ(pv2);

  // Dibujar un triángulo con los vértices transformados

  rtSurface.drawFilledTriangle({ {fv0, {0.0f, 0.0f}, Color(255, 0, 0)},
                                {fv1, {0.0f, 0.0f}, Color(0, 255, 0)},
                                {fv2, {0.0f, 0.0f}, Color(0, 0, 255)} }, ps_shader);
  //tri.v0.position = fv0;

  //////////////

  MSG msg;

  // Main message loop:
  while (GetMessage(&msg, nullptr, 0, 0))
  {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOFTWARERENDERER));
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SOFTWARERENDERER);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

  return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  hInst = hInstance; // Store instance handle in our global variable

  HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

  if (!hWnd)
  {
    DWORD err = GetLastError();
    std::wcerr << L"CreateWindowW failed. GetLastError=" << err << L"\n";
    return FALSE;
  }

  g_hWnd = hWnd;
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

void Render()
{
  HDC hdc = GetDC(g_hWnd);

  int32 xScale = 1;
  int32 yScale = 1;

  int32 scaledWidth = g_renderTargetImage.getWidth() * xScale;
  int32 scaledHeight = g_renderTargetImage.getHeight() * yScale;

  for (int32 y = 0; y < scaledHeight; ++y)
  {
    for (int32 x = 0; x < scaledWidth; ++x)
    {
      FColor fcolor = g_renderTargetTexture.Sample(
        static_cast<float>(x) / scaledWidth,
        static_cast<float>(y) / scaledHeight,
        SAMPLE_FILTER::LINEAR,
        TEXTURE_ADDRESS_MODE::CLAMP
      );

      Color color = fcolor.ToColor();
      SetPixel(hdc, x, y, RGB(color.color.r, color.color.g, color.color.b));
    }
  }

  ReleaseDC(g_hWnd, hdc);
}

POINT g_mousePos;
POINT g_mousePosIni;
bool g_isMouseDown = false;

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_LBUTTONDOWN:
  {
    g_isMouseDown = true;
    g_mousePosIni.x = LOWORD(lParam);
    g_mousePosIni.y = HIWORD(lParam);
  }
  break;

  case WM_LBUTTONUP:
  {
    if (g_isMouseDown)
    {
      g_mousePos.x = LOWORD(lParam);
      g_mousePos.y = HIWORD(lParam);

      if (g_isMouseDown)
      {
        g_renderTargetImage.line(
          g_mousePosIni.x,
          g_mousePosIni.y,
          g_mousePos.x,
          g_mousePos.y,
          Color(255, 0, 0)
        );
      }

      g_isMouseDown = false;
    }
  }
  break;

  case WM_MOUSEMOVE:
  {
  }

  break;
  case WM_COMMAND:
  {
    int wmId = LOWORD(wParam);
    // Parse the menu selections:
    switch (wmId)
    {
    case IDM_ABOUT:
      DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
      break;
    case IDM_EXIT:
      DestroyWindow(hWnd);
      break;
    case ID_RENDER_UPDATE:
      Render();
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
    }
  }
  break;
  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    // TODO: Add any drawing code that uses hdc here...
    EndPaint(hWnd, &ps);
  }
  break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  UNREFERENCED_PARAMETER(lParam);
  switch (message)
  {
  case WM_INITDIALOG:
    return (INT_PTR)TRUE;

  case WM_COMMAND:
    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
    {
      EndDialog(hDlg, LOWORD(wParam));
      return (INT_PTR)TRUE;
    }
    break;
  }
  return (INT_PTR)FALSE;
}
