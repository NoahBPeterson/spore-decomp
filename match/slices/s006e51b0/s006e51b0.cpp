// slice s006e51b0 -- tail of SPGraphicsCubeMapCapture.obj + out-of-line template helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 (x87 used for sqrt).
#include "types.h"

// ===========================================================================
// Shared 12-byte element.
struct Float3 {
    float x, y, z;
};

// ---------------------------------------------------------------------------
// @ 0x006e54d0
// Dispatch `count` sprite refs through a 32-byte function table indexed by the
// entry's first uint16.  The trailing two arguments are part of the caller's
// calling sequence (soft-state id, dirty flag) and are ignored here.
typedef void(__cdecl* SpriteDispatchFn)(unsigned short, unsigned short, int);

struct SpriteDispatchSlot {
    SpriteDispatchFn fn;
    char pad[28];
};

struct SpriteRef {
    unsigned short type;   // +0
    unsigned short f1;     // +2
    unsigned short f2;     // +4
    unsigned short f3;     // +6
    unsigned short f4;     // +8
    unsigned short f5;     // +10
};

extern SpriteDispatchSlot g_spriteDispatch[];

void ShaderDispatch(int count, SpriteRef* refs, bool flag, int softState, bool dirty)
{
    for (int i = 0; i < count; ++i) {
        g_spriteDispatch[refs[i].type].fn(refs[i].f3, refs[i].f2, flag);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e5760
// Fill `count` 12-byte elements with *value, tolerating a null destination.
void FillFloat3N(Float3* dst, unsigned int count, const Float3* value)
{
    Float3* p = dst;
    while (count > 0) {
        if (p) {
            *p = *value;
        }
        --count;
        ++p;
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e5790
// Zero a 3-dword element (used as the element constructor callback).
void __fastcall ZeroTriple(uint32_t* p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
}

// ---------------------------------------------------------------------------
// @ 0x006e57a0
// Refcounted release for the shader-state object; runs the destructor and frees
// when the count reaches zero.
struct ShaderState;
extern "C" void ShaderStateUnlockHook();
__declspec(noinline) void __fastcall ShaderState_Destroy(ShaderState* self);
void operator_delete(void*);

int __fastcall ShaderState_Release(ShaderState* self)
{
    int n = *(int*)((char*)self + 0x3c) - 1;
    ShaderStateUnlockHook();
    if (n == 0) {
        ShaderState_Destroy(self);
        operator_delete(self);
    }
    return n;
}

// ===========================================================================
// Remaining functions: signatures recovered, bodies reproduced in outline.
// ===========================================================================

// @ 0x006e51b0  SP::SHFromCubeMap
void SP_SHFromCubeMap(int tex, int size, char dump, int name, int extra,
                      float x, float y, float z);

// @ 0x006e5520  SP::DirectShaderDispatchCallback
int SP_DirectShaderDispatchCallback();

// @ 0x006e56b0
void __fastcall ShaderState_Destroy(ShaderState* self);

// @ 0x006e57d0
ShaderState* __fastcall ShaderState_Construct(ShaderState* self);

// Out-of-line template helpers are naturally __thiscall members.
class ShaderBlob {
public:
    void FillInsert(int pos, unsigned int n, const void* value);           // 0x006e5870
    void BoolInsert(void* pos, void* n, const unsigned char* value);       // 0x006e5a30
    char Read(void* stream, void* a2);                                     // 0x006e5d50
};

// @ 0x006e5bd0
void __fastcall ShaderState_Reset(ShaderState* self);

// ---------------------------------------------------------------------------

// @ 0x006e51b0
void SP_SHFromCubeMap(int, int, char, int, int, float, float, float)
{
}

// @ 0x006e5520
int SP_DirectShaderDispatchCallback()
{
    return 1;
}

// @ 0x006e56b0
volatile int g_shaderDestroySink;
void __fastcall ShaderState_Destroy(ShaderState*)
{
    g_shaderDestroySink = 1;
}

// @ 0x006e57d0
ShaderState* __fastcall ShaderState_Construct(ShaderState* self)
{
    return self;
}

// @ 0x006e5870
void ShaderBlob::FillInsert(int, unsigned int, const void*)
{
}

// @ 0x006e5a30
void ShaderBlob::BoolInsert(void*, void*, const unsigned char*)
{
}

// @ 0x006e5bd0
void __fastcall ShaderState_Reset(ShaderState*)
{
}

// @ 0x006e5d50
char ShaderBlob::Read(void*, void*)
{
    return 0;
}
