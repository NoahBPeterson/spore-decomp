// src/game/UTFSpore_Win32/_at_00980000.cpp -- migrated from slice(s) s009873a0, s0097f390 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00980000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/Window.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/Stopwatch.h"
#include "EA/UTFWin/cDropShadowDescriptor.h"
#include <math.h>

// unnamed retail callees and globals (address in the comment)
extern "C" unsigned __cdecl wcslen(const wchar_t*);
#pragma intrinsic(wcslen)

// ---- items of slice s0097f390 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(_p, __COUNTER__)();
#define VP4 VP VP VP VP
namespace EA {
namespace UTFWinControls {
struct IObj;
}
}
namespace EA {
namespace UTFWinControls {
struct IObj {
    VP VP VP VP                                       // 0x00..0x0c
    virtual IObj* v10();                               // 0x10
    virtual IObj* v14(int x = 0);                      // 0x14
    VP4 VP4 VP4                                       // 0x18..0x44
    virtual IObj* v48(int x);                          // 0x48
    VP4 VP4 VP4 VP4 VP VP VP                          // 0x4c..0x94
    virtual void  v98();                               // 0x98
};
}
}
namespace EA {
namespace UTFWinControls {
struct Arg2;
}
}
namespace EA {
namespace UTFWinControls {
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
}
}
namespace EA {
namespace UTFWinControls {
struct FloatSink {
    void Set(float v);                                 // 0x0095ee40
};
}
}
namespace EA {
namespace UTFWinControls {
struct FloatHolder {
    char  pad0[0x10];
    float m10;
    void Apply(FloatSink* sink);
};
}
}
namespace EA {
namespace UTFWinControls {
struct Arg2 {
    char  pad0[8];
    int   m08;                     // +0x08
    int   m0c;                     // +0x0c
    int   m10;                     // +0x10
    int   m14;                     // +0x14
    void* m18;                     // +0x18
};
}
}
// ---- items of slice s0097f390 end

// ---- items of slice s009873a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(sqrt)
struct ShadowDesc32;
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
struct StdDrawableBase0 {
    void* v[4];                     // +0x00 vtable ptrs (0,4,8,c)
    StdDrawableBase0()
    {
        *(void* volatile*)&v[1] = (void*)0x13fa72c;
        v[2] = 0;
        *(void* volatile*)&v[3] = (void*)0x1445200;
    }
};
struct StdDrawableBase : StdDrawableBase0 {
    StdDrawableBase()
    {
        *(void* volatile*)&v[0] = (void*)0x1445298;
        *(void* volatile*)&v[1] = (void*)0x1445280;
        *(void* volatile*)&v[3] = (void*)0x1445240;
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
// ---- items of slice s009873a0 end

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

// @ 0x00987900
void StdDrawable::FUN_00987900()
{
    SetSerializerX();
    ((ShadowDesc32*)((char*)this + 0x54))->SetMode1(*(int*)((char*)this + 0x54));
    ((ShadowDesc32*)((char*)this + 0x54))->SetMode2(*(int*)((char*)this + 0x58));
}
