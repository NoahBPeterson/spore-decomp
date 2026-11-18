// Slice s00c84950: SP::cSolarSystem celestial-body refresh (0x00c84950 - 0x00c84b40).
//   RefreshPlanetBody  recomposes one planet's render item (reference position, body colour,
//                      orbit matrix, radius) and hands it to every listener attached to the
//                      planet, once per frame, when the planet is not the active one.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define PAD1 virtual void CAT(pad, __COUNTER__)();
#define PAD4 PAD1 PAD1 PAD1 PAD1
#define PAD8 PAD4 PAD4
#define PAD16 PAD8 PAD8

struct Vector3 {
    float x, y, z;
};

struct cSPMatrix3 {                                 // 36-byte 3x3 matrix
    float m[9];
    void Assign(const void* pSource);               // 0x0041cb40
};

struct cPlanet;

// ------------------------------------------------------------------ universe context
namespace SP {

class cSPLivingUniverse {
public:
    static int      GetUniverseContext();           // 0x01021080 (1 = galaxy view)
    static cPlanet* GetActivePlanet();              // 0x01021260
};

}

// ------------------------------------------------------------------ camera side (galaxy view)
struct ICameraPoint {                               // object reached through the view
    PAD4 PAD1 PAD1 PAD1                             // slots 0..6 (0x00..0x18)
    virtual ICameraPoint* GetFocus();               // vtable +0x1c
    void GetWorldOrigin(Vector3* pOut, int, int, int);   // 0x007c3d30
};

struct IUniverseView {                              // object behind 0x0067dd10()
    PAD16 PAD4                                      // slots 0..19 (0x00..0x4c)
    virtual ICameraPoint* GetCamera();              // vtable +0x50
};

extern void* __cdecl FUN_0067dd10();                // 0x0067dd10 (universe view provider)

// ------------------------------------------------------------------ planet
struct IRenderer;

struct cPlanet {
    PAD8 PAD1 PAD1 PAD1                             // slots 0..10 (0x00..0x28)
    virtual const Vector3& GetPosition();           // vtable +0x2c
    virtual void*          GetTransform();          // vtable +0x30
    int GetPlanetType();                            // 0x00c70880
    uint8_t   pad04[0x16c];                         // +0x04 .. +0x16f
    IRenderer** mpBodies170;                        // +0x170
    IRenderer** mpBodies174;                        // +0x174
    uint8_t   pad178[0x0c];                         // +0x178 .. +0x183
    float     mRadius184;                           // +0x184
};

// ------------------------------------------------------------------ render item
struct RenderItem {                                 // 0x38 bytes, filled in below
    uint16_t mFlags;                                // +0x00
    uint16_t mCount;                                // +0x02
    union {
        Vector3 mColor;                             // +0x04 default body colour (0x01694c94/98/9c)
        Vector3 mAnchor;                            // +0x04 reference position, written just after
    };
    float      mRadius;                             // +0x10
    cSPMatrix3 mMatrix;                             // +0x14 body orientation
};

struct IRenderer {
    PAD4                                            // slots 0..3
    virtual bool IsActive();                        // vtable +0x10
    PAD1                                            // slot 5
    virtual void SetItem(RenderItem* pItem);        // vtable +0x18
};

// ------------------------------------------------------------------ misc externs
extern void* __cdecl FUN_01034680(cPlanet* planet);             // 0x01034680 (body size source)
extern float __cdecl FUN_01034630(void* pSizeSource, float fDistance,
                                  bool bGalaxyView);            // 0x01034630 (on-screen size)
extern void  __cdecl FUN_0059c190(cSPMatrix3* pOut, void* pTransform);   // 0x0059c190

extern float gBodyColorR;                                       // 0x01694c94
extern float gBodyColorG;                                       // 0x01694c98
extern float gBodyColorB;                                       // 0x01694c9c
extern float g_f01485720;                                       // 0x01485720 (default body radius)
extern cSPMatrix3 g_mtx01694c70;                                // 0x01694c70 (identity basis)

// @ 0x00c84950
// Rebuilds the render item of one planet and passes it to the planet's listeners.
void __stdcall FUN_00c84950(cPlanet* planet)
{
    // Reference point the body is positioned against: in the galaxy view the camera focus,
    // otherwise the planet the player is currently on.
    Vector3 target;
    if (SP::cSPLivingUniverse::GetUniverseContext() == 1) {
        ICameraPoint* view = ((IUniverseView*)FUN_0067dd10())->GetCamera();
        ICameraPoint* focus = view->GetFocus();
        focus->GetWorldOrigin(&target, 0, 0, 0);
    } else {
        target = SP::cSPLivingUniverse::GetActivePlanet()->GetPosition();
    }

    const Vector3& pos = planet->GetPosition();
    Vector3 delta;
    delta.x = target.x - pos.x;
    delta.y = target.y - pos.y;
    delta.z = target.z - pos.z;

    void* sizeSource = FUN_01034680(planet);
    float scale = FUN_01034630(sizeSource,
                               sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z),
                               SP::cSPLivingUniverse::GetUniverseContext() == 0);

    const Vector3& anchor = planet->GetPosition();
    cSPMatrix3 bodyMatrix;
    FUN_0059c190(&bodyMatrix, planet->GetTransform());

    scale = planet->mRadius184 * scale;

    RenderItem item;
    item.mFlags = 0;
    item.mCount = 0;
    item.mColor.x = gBodyColorR;
    item.mColor.y = gBodyColorG;
    item.mColor.z = gBodyColorB;
    item.mRadius = g_f01485720;
    item.mMatrix.Assign(&g_mtx01694c70);

    item.mAnchor = anchor;
    item.mFlags |= 4;
    item.mCount += 1;

    if (planet->GetPlanetType() != 0) {             // sun: take the body matrix and the size
        item.mMatrix = bodyMatrix;
        item.mCount++;
        item.mFlags |= 2;
        item.mRadius = scale;
        item.mCount++;
    }

    for (IRenderer** it = planet->mpBodies170; it != planet->mpBodies174; ++it) {
        IRenderer* renderer = *it;
        if (renderer->IsActive())
            renderer->SetItem(&item);
    }
}
