// src/game/UTFSpore_Win32/GlideEffect.cpp -- migrated from slice(s) s0096f3f0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/GlideEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/UTFWinControls/WinGrid.h"
#include <intrin.h>

// ---- items of slice s0096f3f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWinControls {
int   __cdecl FUN_009512c0();                                                  // 0x009512c0
}
}
namespace EA {
namespace UTFWinControls {
void* __cdecl FUN_009512d0(int size, int align, const char* type, void* fac);  // 0x009512d0
}
}
namespace EA {
namespace UTFWinControls {
void  __fastcall FadeEffect_ctor(void*);                                       // 0x00963db0
}
}
namespace EA {
namespace UTFWinControls {
struct FloatSink {
    void Push(float* v);          // 0x0095e890
};
}
}
namespace EA {
namespace UTFWinControls {
class GlideEffect { public:
    char  pad00[0x60];
    void* field60;         // +0x60
    float field64;         // +0x64
    float field68;         // +0x68

    void Set(float* src);                              // 0x00970060
    void Scale(void* a, FloatSink* obj, float scale);  // 0x00970010
};
}
}
namespace EA {
namespace UTFWinControls {
class BasicFactory_GlideEffect { public:
    void* CreateInstance(int param1, void* param2);
};
}
}
// ---- items of slice s0096f3f0 end

// @ 0x00970010
namespace EA { namespace UTFWinControls {
void GlideEffect::Scale(void*, FloatSink* obj, float scale)
{
    float local[3];
    local[0] = *(float*)((char*)this + 0x64) * scale;
    local[1] = *(float*)((char*)this + 0x68) * scale;
    local[2] = 0.0f;
    obj->Push(local);
}
}}  // namespace EA::UTFWinControls

// @ 0x00970060
namespace EA { namespace UTFWinControls {
void GlideEffect::Set(float* src)
{
    *(float*)((char*)this + 4) = src[0];
    *(float*)((char*)this + 8) = src[1];
}
}}  // namespace EA::UTFWinControls

// @ 0x009700b0
namespace EA { namespace UTFWinControls {
void* __fastcall FUN_009700b0(char* param_1)
{
    FadeEffect_ctor(param_1);
    const float zero = 0.0f;
    *(void* volatile*)(param_1 + 0x60) = (void*)0x014426a0;
    *(void**)(param_1 + 0) = (void*)0x014425d8;
    *(void**)(param_1 + 4) = (void*)0x014425c0;
    *(void**)(param_1 + 0x0c) = (void*)0x01442584;
    *(void* volatile*)(param_1 + 0x60) = (void*)0x014426bc;
    *(float*)(param_1 + 0x64) = zero;
    *(float*)(param_1 + 0x68) = zero;
    return param_1;
}
}}  // namespace EA::UTFWinControls

// @ 0x00970100
namespace EA { namespace UTFWinControls {
void* BasicFactory_GlideEffect::CreateInstance(int, void* param2)
{
    if (param2 == 0)
        param2 = (void*)FUN_009512c0();
    char* obj = (char*)FUN_009512d0(0x70, 8,
                                    "UTFWin/EA::UTFWinControls::GlideEffect", param2);
    if (obj != 0) {
        FadeEffect_ctor(obj);
        const float zero = 0.0f;
        *(void* volatile*)(obj + 0x60) = (void*)0x014426a0;
        *(void**)(obj + 0) = (void*)0x014425d8;
        *(void**)(obj + 4) = (void*)0x014425c0;
        *(void**)(obj + 0x0c) = (void*)0x01442584;
        *(void* volatile*)(obj + 0x60) = (void*)0x014426bc;
        *(float*)(obj + 0x64) = zero;
        *(float*)(obj + 0x68) = zero;
        return obj;
    }
    return 0;
}
}}  // namespace EA::UTFWinControls
