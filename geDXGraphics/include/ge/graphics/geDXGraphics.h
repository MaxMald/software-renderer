#include <ge/graphics/geIGraphics.h>
#include <d3d11_2.h>

namespace ge
{
  class DXGraphics : public IGraphics
  {
  public:
    DXGraphics(void* source);
    virtual ~DXGraphics();

    Vector<IDXGIAdapter1*> getAdapters();
  private:

  };
}