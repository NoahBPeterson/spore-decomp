// src/game/UTFSpore_Win32/_at_00980000.cpp
// Object file: UTFSpore_Win32/_at_00980000.obj.

#include "game/types.h"
#include "EA/UTFWin/Window.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/Stopwatch.h"
#include "EA/UTFWin/cDropShadowDescriptor.h"
#include <math.h>
#include <xmmintrin.h>

// Filler vtable slots: each VP expands to one `virtual void _pN();` declaration,
// VP4 to four of them.
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(_p, __COUNTER__)();
#define VP4 VP VP VP VP

// unnamed retail callees and globals (address in the comment)
extern "C" unsigned __cdecl wcslen(const wchar_t*);
#pragma intrinsic(wcslen)
#pragma intrinsic(sqrt)

namespace EA {
namespace UTFWinControls {

// Local stand-ins: the canonical headers declare none of these classes, so the
// layout and the vtable slots this module needs are spelled out here.
struct IObj {
    VP VP VP VP                                       // 0x00..0x0c
    virtual IObj* v10();                               // 0x10
    virtual IObj* v14(int x = 0);                      // 0x14
    VP4 VP4 VP4                                       // 0x18..0x44
    virtual IObj* v48(int x);                          // 0x48
    VP4 VP4 VP4 VP4 VP VP VP                          // 0x4c..0x94
    virtual void  v98();                               // 0x98
};

struct Arg2 {
    char  pad0[8];
    int   m08;                     // +0x08
    int   m0c;                     // +0x0c
    int   m10;                     // +0x10
    int   m14;                     // +0x14
    void* m18;                     // +0x18
};

struct IOwner {
    VP VP VP VP VP                                    // 0x00..0x10
    virtual int  v14();                                // 0x14
    VP4 VP4 VP4 VP4 VP4 VP4                           // 0x18..0x78
    VP VP                                             // 0x7c
    virtual void v80(void* p);                         // 0x80 (slot 32)
    char pad04[0xc];                                   // +0x04..0x0f
    int  m10;                                          // +0x10
    int  m14;                                          // +0x14
    bool Process(IObj* arg1, Arg2* arg2);
    bool Process2(IObj* arg1, Arg2* arg2);
};

// A one-argument sink for a float value: Apply() pushes m10 through it.
struct FloatSink {
    void Set(float v);                                 // 0x0095ee40
};

struct FloatHolder {
    char  pad0[0x10];
    float m10;
    void Apply(FloatSink* sink);
};

}  // namespace UTFWinControls
}  // namespace EA

// The retail shadow descriptor; SetMode1/SetMode2 are its two mode setters.
struct ShadowDesc32 {
    int   m00;      // +0x00 mode
    int   m04;      // +0x04
    int   m08;      // +0x08
    float f0c;
    float f10;
    float f14;
    float f18;
    int   m1c;
    int   m20;
    int   m24;
    void SetMode1(int);   // 0x830280
    void SetMode2(int);   // 0x830150
};
struct ShadowDescC : ShadowDesc32 {
    void Init()
    {
        m00 = 0;
        m04 = 2;
        m08 = 3;
        f14 = 0.0f;
        f18 = 0.0f;
        f0c = 0.0f;
        f10 = 0.0f;
        m24 = 0;
        SetMode2(2);
    }
};

// Vtable addresses the StdDrawable constructors install, in the order they are written.
static const unsigned int kVtblBase0_04 = 0x013fa72c;
static const unsigned int kVtblBase0_0C = 0x01445200;
static const unsigned int kVtblStd_00   = 0x01445298;
static const unsigned int kVtblStd_04   = 0x01445280;
static const unsigned int kVtblStd_0C   = 0x01445240;

struct StdDrawableBase0 {
    void* v[4];                     // +0x00 vtable ptrs (0,4,8,c)
    StdDrawableBase0()
    {
        *(void* volatile*)&v[1] = (void*)kVtblBase0_04;
        v[2] = 0;
        *(void* volatile*)&v[3] = (void*)kVtblBase0_0C;
    }
};
struct StdDrawableBase : StdDrawableBase0 {
    StdDrawableBase()
    {
        *(void* volatile*)&v[0] = (void*)kVtblStd_00;
        *(void* volatile*)&v[1] = (void*)kVtblStd_04;
        *(void* volatile*)&v[3] = (void*)kVtblStd_0C;
    }
};
struct StdDrawable : StdDrawableBase {
    void* mpImage[8];               // +0x10
    int   mScalingType;             // +0x30
    float mAreaL, mAreaT, mAreaR, mAreaB;  // +0x34
    float mScaleX, mScaleY;         // +0x44
    void* mHitMask;                 // +0x4c
    float mBevelWidth;              // +0x50
    ShadowDescC  mShadow;           // +0x54

    void  SetSerializerX();                        // 0xc2e4e0
    void  FUN_00987900();                          // 0x987900
    void  SetImageAt(unsigned idx, void* img);     // 0x987970
    void* GetImageAt(unsigned idx);                // 0x9879b0
    void* GetImageForState(unsigned st);           // 0x9879f0
    ~StdDrawable();                                // 0x987b10
    void  draw_with_image(int* sink, void* p3, void* p4);   // 0x987bf0
    void  CreateRenderables(void* ctx, float* rect, unsigned* flags);  // 0x987d40
    bool  HitTest(float* rect, int* pt, int unused);                   // 0x9880e0
    bool  QueryAttribute(int id, unsigned* out);                       // 0x9883c0
    bool  GetNaturalSize(float* out, int state, int unused);           // 0x9883f0
    StdDrawable();                                                     // 0x988420
};

// ---- items of slice s00980760 begin (TODO(rewrite): local stubs, replace by canonical classes)
void __fastcall Navigator_dtor(void* p);                               // 00980420
struct XCM {
    void SetX(float v);                                                // 0095eb00
    void SetY(float v);                                                // 0095ec30
    void SetZ(float v);                                                // 0095ed60
    void SetRotationAtLeast2(float* face, float v);                    // 0095f5c0
};
namespace EA {
namespace UTFWinControls {
extern void* vt_1444368[];
}
}
namespace EA {
namespace UTFWinControls {
extern void* vt_1444350[];
}
}
namespace EA {
namespace UTFWinControls {
extern void* vt_1444314[];
}
}
namespace EA {
namespace UTFWinControls {
extern void* vt_gme_13eb938[];
}
}
namespace EA {
namespace UTFWinControls {
class RotateEffect { public:
    void* vt0;                                                         // +0x00
    void* vt4;                                                         // +0x04
    int   f08;                                                         // +0x08
    void* vtc;                                                         // +0x0c
    int   f10;                                                         // +0x10
    int   f14;                                                         // +0x14
    int   f18;                                                         // +0x18
    int   f1c;                                                         // +0x1c
    char  pad20[0x60 - 0x20];
    void* vt60;                                                        // +0x60
    float fx;                                                          // +0x64
    float fy;                                                          // +0x68
    float fz;                                                          // +0x6c
    float scale;                                                       // +0x70
    RotateEffect();                                                    // 00980e30
    ~RotateEffect();                                                   // 00980c00
    void SetRotation(void* unused, XCM* cm, float deg);               // 00980cf0
};
}
}
// ---- items of slice s00980760 end

// @ 0x00980520
namespace EA { namespace UTFWinControls {
bool IOwner::Process2(IObj* arg1, Arg2* arg2)
{
    switch (arg2->m08) {
    case 0x15:
        if (v14() & 0x200)
            v80(arg2->m18);
        break;
    case 0xc:
        if (v14() & 0x200)
            arg1->v98();
        break;
    }
    return false;
}
}}  // namespace EA::UTFWinControls

// @ 0x00980580
namespace EA { namespace UTFWinControls {
void FloatHolder::Apply(FloatSink* sink)
{
    sink->Set(m10);
}
}}  // namespace EA::UTFWinControls

// @ 0x00980c00
EA::UTFWinControls::RotateEffect::~RotateEffect()
{
    *(void**)this = EA::UTFWinControls::vt_1444368;
    *(void**)((char*)this + 4) = EA::UTFWinControls::vt_1444350;
    *(void**)((char*)this + 0xc) = EA::UTFWinControls::vt_1444314;
    *(void**)((char*)this + 0x60) = EA::UTFWinControls::vt_gme_13eb938;
    Navigator_dtor(this);
}

// @ 0x00987900
void StdDrawable::FUN_00987900()
{
    SetSerializerX();
    ((ShadowDesc32*)((char*)this + 0x54))->SetMode1(*(int*)((char*)this + 0x54));
    ((ShadowDesc32*)((char*)this + 0x54))->SetMode2(*(int*)((char*)this + 0x58));
}
