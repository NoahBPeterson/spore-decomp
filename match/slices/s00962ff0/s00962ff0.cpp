// Slice s00962ff0 -- EA::UTFWin::* controls helpers (effects, index-buffer factories)
// plus a handful of button accessors.  Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"

extern "C" void __cdecl  FUN_0093a560(void*, int, int);   // Stopwatch::Stopwatch  0x93a560
extern "C" void __cdecl  FUN_0093a1a0(void*, int);        // Stopwatch::SetUnits   0x93a1a0
struct Stopwatch { void Init(int, int); void SetUnits(int); void Restart(); };

struct ResDesc { int a, b, c, d, e; };
extern "C" void __cdecl  FUN_011f51d0(ResDesc*, int, int, int, int);   // GetResourceDescriptor 0x11f51d0
extern "C" void* __cdecl FUN_011f36d0(int*, int, int, int);            // 0x11f36d0
extern "C" void* __cdecl FUN_011f5010(int*, int, int, int, int, int);  // 0x11f5010
extern void* g_pfnIndexBuffer;                                         // 0x16f4ae4

// ------------------------------------------------------------------ 0x962ff0
int __cdecl FUN_00962ff0(int p2, int p3, int p4, int p5)
{
    ResDesc desc;
    FUN_011f51d0(&desc + 0, p2, p3, p4, p5);
    int r = ((int (__cdecl*)(int, int))g_pfnIndexBuffer)(desc.b, desc.c);
    if (r != 0) {
        int local[4];
        local[0] = r;
        local[1] = 0;
        local[2] = 0;
        local[3] = 0;
        return (int)FUN_011f36d0(local, p2, p3, p4);
    }
    return 0;
}

// ------------------------------------------------------------------ 0x963060
// @ 0x00963060
int __cdecl FUN_00963060(int p1, int p2, int p3, int p4, int p5, int p6)
{
    ResDesc desc;
    FUN_011f51d0(&desc, p2, p3, p4, p5);
    (void)p6;
    int r = ((int (__cdecl*)(int, int))g_pfnIndexBuffer)(desc.b, desc.c);
    if (r != 0) {
        int local[4];
        local[0] = r;
        local[1] = 0;
        local[2] = 0;
        local[3] = 0;
        return (int)FUN_011f5010(local, p2, p3, p4, p5, p6);
    }
    return 0;
}

// ================================================================== controls
struct Btn {
    int   GetEventMask();                       // 0x9634c0
    void  OnlyWhenVisible(int* wnd, bool on);   // 0x963630
    void  SetFade(bool on);                     // 0x9635e0
    void  SetAlphaClamp(float a, float b);      // 0x9636f0
};

// @ 0x9634c0
int Btn::GetEventMask()
{
    uint32_t f = (*(uint32_t(__thiscall**)(void*))((char*)*(void**)this + 0x80))(this);
    uint32_t r = *(uint32_t*)((char*)this + 0x54) | 0x10459;
    if (f & 1)
        r |= 0x200;
    return (int)r;
}

struct WinButtonX {
    int   GetSlot(uint32_t i);                          // 0x964020
    void  SetSlot(uint32_t i, int v);                   // 0x963fd0
    int   GetCaptionColor();                            // 0x964000
};

// @ 0x964020
int WinButtonX::GetSlot(uint32_t i)
{
    if (i < 8)
        return *(int*)((char*)this + 0x54 + i * 4);
    return 0;
}

// @ 0x963fd0
void WinButtonX::SetSlot(uint32_t i, int v)
{
    if (i < 8 && *(int*)((char*)this + 0x54 + i * 4) != v) {
        *(int*)((char*)this + 0x54 + i * 4) = v;
        int* base = (int*)((char*)this - 0x20c);
        (*(void(__thiscall**)(int*))((char*)*base + 0xa0))(base);
    }
}

// @ 0x964000
int WinButtonX::GetCaptionColor()
{
    if (*(char*)((char*)this + 0x210) != 0)
        (*(void(__thiscall**)(void*))((char*)*(void**)this + 0xa0))(this);
    return *(int*)((char*)this + 0x224);
}

struct FlexFlag {
    int  GetEffectFlag();                       // 0x963f60
    void SetEffectFlag(uint32_t m, bool on);    // 0x963f70
};

// @ 0x963f60
int FlexFlag::GetEffectFlag()
{
    return *(int*)((char*)this - 0x160);
}

// @ 0x963f70
void FlexFlag::SetEffectFlag(uint32_t m, bool on)
{
    int v = *(int*)((char*)this - 0x160);
    if (on) {
        (*(void(__thiscall**)(void*, uint32_t))((char*)*(void**)this + 0x24))(this, (uint32_t)v | m);
    } else {
        (*(void(__thiscall**)(void*, uint32_t))((char*)*(void**)this + 0x24))(this, (uint32_t)v & ~m);
    }
}

// @ 0x9636f0
void Btn::SetAlphaClamp(float a, float b)
{
    if (0.0f > a) a = 0.0f;
    if (0.0f > b) b = 0.0f;
    if (a > 1.0f) a = 1.0f;
    if (b > 1.0f) b = 1.0f;
    if (1.0f < a + b) {
        float s = 1.0f / (a + b);
        a = s * a;
        b = s * b;
    }
    *(float*)((char*)this + 0x2c) = a;
    *(float*)((char*)this + 0x30) = b;
}

// @ 0x9635e0
void Btn::SetFade(bool on)
{
    int* p = *(int**)((char*)this + 0x58);
    if (p == 0)
        return;
    if (on) {
        if (*(int*)((char*)this + 0x54) != 0)
            return;
        *(int*)((char*)this + 0x54) = 2;
        (*(void(__thiscall**)(int*, void*))((char*)*p + 0x104))(p, this);
    } else {
        if (*(int*)((char*)this + 0x54) == 0)
            return;
        *(int*)((char*)this + 0x54) = 0;
        (*(void(__thiscall**)(int*, void*))((char*)*p + 0x104))(p, this);
    }
}

// @ 0x963630
void Btn::OnlyWhenVisible(int* wnd, bool on)
{
    float f = on ? 1.0f : 0.0f;
    *(float*)((char*)this + 0x44) = f;
    if (f != *(float*)((char*)this + 0x4c)) {
        int m = *(int*)((char*)this + 0x30);
        if (m == 0 || m == 1)
            (*(void(__thiscall**)(int*))((char*)*wnd + 0x9c))(wnd);
        ((Stopwatch*)((char*)this + 0x18))->Restart();
        int* p = *(int**)((char*)this + 0x58);
        if (p != 0 && *(int*)((char*)this + 0x54) == 0) {
            *(int*)((char*)this + 0x54) = 2;
            (*(void(__thiscall**)(int*, void*))((char*)*p + 0x104))(p, this);
        }
        struct Msg { char pad0[8]; uint32_t type; char pad1[0xc]; void* self; };
        Msg msg;
        msg.type = 0x7e1a520;
        msg.self = this;
        (*(void(__thiscall**)(int*, Msg*))((char*)*wnd + 0x114))(wnd, &msg);
    }
}

// @ 0x963db0
extern void* vtbl_FadeEffect;         // 0x1440d88
extern void* vtbl_FadeEffect2;        // 0x1440d6c
extern void* vtbl_FadeEffect3;        // 0x1440d30
void* __fastcall FadeEffect_Ctor(void* self)
{
    *(void**)((char*)self + 4) = (void*)0x13fa72c;
    *(int*)  ((char*)self + 8) = 0;
    *(void**)((char*)self + 0xc) = (void*)0x14085f0;
    *(void**)self = (void*)0x1440d88;
    *(void**)((char*)self + 4) = (void*)0x1440d6c;
    *(void**)((char*)self + 0xc) = (void*)0x1440d30;
    *(float*) ((char*)self + 0x10) = 0.0f;
    ((Stopwatch*)((char*)self + 0x18))->Init(0, 0);
    *(int*)  ((char*)self + 0x30) = 1;
    *(int*)  ((char*)self + 0x34) = 0;
    *(float*)((char*)self + 0x38) = 0.0f;
    *(float*)((char*)self + 0x3c) = 0.0f;
    *(float*)((char*)self + 0x40) = 0.1f;
    *(float*)((char*)self + 0x44) = 0.0f;
    *(float*)((char*)self + 0x48) = 0.0f;
    *(float*)((char*)self + 0x4c) = 0.0f;
    *(char*) ((char*)self + 0x50) = 0;
    *(int*)  ((char*)self + 0x54) = 2;
    *(int*)  ((char*)self + 0x58) = 0;
    ((Stopwatch*)((char*)self + 0x18))->SetUnits(5);
    return self;
}

// @ 0x964040
struct Cap { void SelectCaptionColor(); };
void Cap::SelectCaptionColor()
{
    char* self = (char*)this;
    void* obj = self + 4;
    unsigned* vtbl = *(unsigned**)obj;
    unsigned v = ((unsigned(__thiscall*)(void*))vtbl[0x28 / 4])(obj);
    unsigned xf = *(unsigned*)(self + 0xac);
    unsigned c0 = (v >> 1) & 1;
    unsigned b = (xf >> 1) & 1;
    unsigned d = (xf >> 2) & 1;
    unsigned a = (xf >> 3) & 1;
    unsigned c = (xf >> 4) & 1;
    unsigned* dst = (unsigned*)(self + 0x224);
    unsigned x;

    if (c0 == 0 && (x = *(unsigned*)(self + 0x264)) != 0) {
        *dst = x;
        goto done;
    }
    if (d != 0) {
        if (b != 0 && (x = *(unsigned*)(self + 0x278)) != 0) {
            *dst = x;
            goto done;
        }
        if (a != 0 && (x = *(unsigned*)(self + 0x274)) != 0) {
            *dst = x;
            goto done;
        }
        if ((x = *(unsigned*)(self + 0x270)) != 0) {
            *dst = x;
            goto done;
        }
    }
    if (b != 0 && (x = *(unsigned*)(self + 0x268)) != 0) {
        *dst = x;
        goto done;
    }
    if (a != 0 && (x = *(unsigned*)(self + 0x26c)) != 0) {
        *dst = x;
        goto done;
    }
    if (c != 0 && (x = *(unsigned*)(self + 0x27c)) != 0) {
        *dst = x;
        goto done;
    }
    if (c0 != 0 && (x = *(unsigned*)(self + 0x260)) != 0)
        *dst = x;
done:
    ((void(__thiscall*)(void*))vtbl[0x90 / 4])(obj);
}

// @ 0x9634f0
struct EaseFx { long double Ease(float t); };
long double EaseFx::Ease(float t)
{
    int mode = *(int*)((char*)this + 0x34);
    if (mode == 1) {
        if (t != 0.0f && t != 1.0f) {
            float a = *(float*)((char*)this + 0x38);
            float b = *(float*)((char*)this + 0x3c);
            if (a + b != 0.0f) {
                float s = 1.0f / ((2.0f - a) - b);
                if (a > t)
                    return (long double)t * ((long double)s / (long double)a * (long double)t);
                if (1.0f - b > t)
                    return ((long double)t + (long double)t - (long double)a) * (long double)s;
                long double r = 1.0 - (long double)t;
                return 1.0 - ((long double)s / (long double)b) * r * r;
            }
        }
        return t;
    }
    if (mode == 2 || mode == 0)
        return t;
    return 0.0;
}

// @ 0x9630e0  ImmediateModeEx::Init (PDB candidate)
// Full setup of the vertex description, vertex/index buffers, sampler state and
// compiled state.  The retail function is /LTCG-expanded; this is a complete
// behavioural reconstruction using the same callees.
struct VertexElement { unsigned short stream, offset; unsigned char type, method, usage, usageIndex; int rwDecl; };
struct VertexDescription {
    void*    pNextParent;      // +0x00
    void*    pNextSibling;     // +0x04
    void*    pDXDecl;          // +0x08
    unsigned short elementsCount; // +0x0c
    unsigned char  lockFlags;  // +0x0e
    unsigned char  stride;     // +0x0f
    int      elementsUsed;     // +0x10
    int      elementsHash;     // +0x14
    VertexElement elements[1]; // +0x18
    void Finalize();           // 0x011f3220
};

struct BuildState {
    unsigned m_softStateDirty;              // +0x000
    unsigned m_softStateDynamic;            // +0x004
    unsigned m_softStateDynamicShared;      // +0x008
    unsigned m_softStateExternal;           // +0x00c
    int      m_transformType;               // +0x010
    void*    m_transform;                   // +0x014
    unsigned pad018[2];                     // +0x018
    float    m_transformLocalCopy[16];      // +0x020
    void*    m_shader;                      // +0x060
    float    m_color[4];                    // +0x064
    float    m_ambient[3];                  // +0x074
    void*    m_light[8];                    // +0x080
    unsigned m_renderStateDirty[7];         // +0x0a0
    unsigned m_renderStateDynamic[7];       // +0x0bc
    unsigned m_renderState[210];            // +0x0d8
    unsigned char m_uvMapping[17];          // +0x420
    unsigned char pad431[3];                // +0x431
    unsigned m_rasterDirty;                 // +0x434
    unsigned m_rasterDynamic;               // +0x438
    void*    m_raster[17];                  // +0x43c
    unsigned m_paletteDirty;                // +0x480
    unsigned m_paletteDynamic;              // +0x484
    void*    m_palette;                     // +0x488
    unsigned m_textureStageStateDirty[17];  // +0x48c
    unsigned m_textureStageStateDynamic[17];// +0x4d0
    unsigned m_textureStageState[17][33];   // +0x514
    unsigned m_samplerStateDirty[17];       // +0xdd8
    unsigned m_samplerStateDynamic[17];     // +0xe1c
    unsigned m_samplerState[17][14];        // +0xe60
    int      m_fogType;                      // +0x1218
    float    m_fogStartDensity;             // +0x121c
    float    m_fogEnd;                      // +0x1220
    float    m_fogColor[3];                  // +0x1224
    int      m_primType;                     // +0x1230
    void*    m_vdesc;                        // +0x1234
    unsigned m_maxShaderData;                // +0x1238

    void D3D9SetVertexDescriptor(void* vdesc, int flags);        // 0x011f9e20
    void D3D9SetShaderData(int a, void* b, int c, int d, int e, int f); // 0x011f9cb0
};

extern "C" void* __cdecl FUN_011f34a0(int* a, int b, int c);      // 0x011f34a0
extern "C" void  __cdecl FUN_011f3220();                           // 0x011f3220
extern "C" int   __cdecl FUN_011f4f20(int a, int* out);            // 0x011f4f20
extern "C" void  __cdecl FUN_011f4fd0(int* p);                     // 0x011f4fd0
extern "C" void* __cdecl FUN_011f9a90(int* a, int b);              // 0x011f9a90
extern "C" void  __cdecl FUN_011f9e50(void* out, unsigned p, int b); // 0x011f9e50
extern "C" BuildState* __cdecl FUN_011f9eb0(int* a, unsigned p, int b); // 0x011f9eb0
extern "C" void  __cdecl FUN_011f9ba0(int a, int b, int c);       // 0x011f9ba0
extern "C" void  __cdecl FUN_011f9c10(int a, int b);               // 0x011f9c10
extern "C" void  __cdecl FUN_011f9b10();                           // 0x011f9b10
extern "C" void* __cdecl FUN_011ef6f0(int* a, BuildState* bs);     // 0x011ef6f0
extern "C" void  __cdecl D3D9GetResourceDescriptor(void*, BuildState*, BuildState*); // 0x011f9f00
extern void* g_pfnAlloc;             // 0x016f4ae4
extern void* g_pfnFree;              // 0x016f4aec
extern char  g_texParams;            // 0x015d07b0

int __fastcall FUN_009630e0(void* selfPtr, int, unsigned p2, int p3)
{
    char* self = (char*)selfPtr;
    int localVd[4];
    int localIb[3];
    int localDesc[2];
    int cb[5];
    int stateAlloc[4];

    VertexDescription* vd = (VertexDescription*)((void* (__cdecl*)(int, int))g_pfnIndexBuffer)(0x48, 4);
    if (vd == 0) {
        vd = 0;
    } else {
        stateAlloc[0] = (int)vd;
        stateAlloc[1] = 0;
        stateAlloc[2] = 0;
        stateAlloc[3] = 0;
        vd = (VertexDescription*)FUN_011f34a0(stateAlloc, 4, 0);
    }
    *(VertexDescription**)(self + 8) = vd;
    vd->lockFlags |= 2;
    vd->elements[0].stream = 0;            // +0x18
    vd->elements[0].offset = 0;            // +0x1a
    vd->elements[0].type = 1;              // +0x1c
    vd->elements[0].method = 0;            // +0x1d
    vd->elements[0].usage = 4;             // +0x1e
    vd->elements[0].usageIndex = 3;        // +0x1f
    vd->elements[0].rwDecl = 0;
    vd->elements[1].stream = 0;            // +0x20
    vd->elements[1].offset = 0;            // +0x22
    vd->elements[1].type = 4;              // +0x24
    vd->elements[1].method = 5;            // +0x25
    vd->elements[1].usage = 1;             // +0x26
    vd->elements[1].usageIndex = 6;        // +0x27
    vd->elements[1].rwDecl = 0;
    vd->Finalize();

    *(void**)(self + 0x18) = (void*)FUN_00962ff0((int)&g_texParams, *(int*)(self + 8), 0x1000, 1);
    *(unsigned*)(self + 0x10) = 0;
    *(void**)(self + 0x1c) = (void*)FUN_00963060((int)&g_texParams, (int)&g_texParams, 0x800, 0x1800, 8, 4);

    if (FUN_011f4f20(2, localIb) != 0) {
        short* p = (short*)(localIb[0] + 4);
        short s = 2;
        do {
            p[-2] = s - 2;
            p[1] = s - 2;
            p[0] = s;
            p[2] = s;
            p[-1] = s - 1;
            p[3] = s + 1;
            unsigned short next = s + 2;
            p += 6;
            s += 4;
            (void)next;
            if (next >= 0x1000)
                break;
        } while (1);
        FUN_011f4fd0(localIb);
    }

    void* sampler = ((void* (__cdecl*)(int, int))g_pfnIndexBuffer)(0x28, 4);
    if (sampler == 0) {
        stateAlloc[0] = 0;
        sampler = 0;
    } else {
        stateAlloc[0] = (int)sampler;
        stateAlloc[1] = 0;
        stateAlloc[2] = 0;
        stateAlloc[3] = 0;
        sampler = FUN_011f9a90(stateAlloc, 1);
    }
    *(void**)(self + 0x20) = sampler;

    FUN_011f9e50(localDesc, p2, 1);
    void* bsMem = ((void* (__cdecl*)(int, int))g_pfnIndexBuffer)(localDesc[0], localDesc[1]);
    BuildState* bs;
    if (bsMem == 0) {
        bs = 0;
    } else {
        stateAlloc[0] = (int)bsMem;
        stateAlloc[1] = 0;
        stateAlloc[2] = 0;
        stateAlloc[3] = 0;
        bs = FUN_011f9eb0(stateAlloc, p2, 1);
    }

    for (int i = 0; i < 2; ++i) {
        bs->m_samplerStateDirty[i] |= 0x10;
        bs->m_samplerStateDynamic[i] &= ~0x10u;
        bs->m_samplerState[i][5] = 2;
        bs->m_samplerStateDirty[i] |= 0x20;
        bs->m_samplerStateDynamic[i] &= ~0x20u;
        bs->m_samplerState[i][6] = 2;
        bs->m_samplerStateDirty[i] |= 0x40;
        bs->m_samplerStateDynamic[i] &= ~0x40u;
        bs->m_samplerState[i][7] = 0;
        bs->m_samplerStateDirty[i] |= 1;
        bs->m_samplerStateDynamic[i] &= ~1u;
        bs->m_samplerState[i][1] = 3;
        bs->m_samplerStateDirty[i] |= 2;
        bs->m_samplerStateDynamic[i] &= ~2u;
        bs->m_samplerState[i][2] = 3;
    }

    FUN_011f9ba0(0x13, 5, 0);
    FUN_011f9ba0(0x14, 6, 0);
    FUN_011f9ba0(0x1b, 1, 0);
    FUN_011f9ba0(0x16, 1, 0);
    FUN_011f9ba0(0x19, 8, 0);
    FUN_011f9ba0(7, 0, 0);
    FUN_011f9ba0(0x1c, 0, 0);

    bs->m_rasterDirty |= 3;
    bs->m_rasterDynamic |= 3;
    bs->m_softStateDirty |= 0x8000;
    bs->m_softStateDynamic &= 0xffff7fffu;
    bs->m_raster[0] = 0;
    bs->m_raster[1] = 0;
    bs->m_uvMapping[0] = 0;
    bs->m_uvMapping[1] = 0;

    bs->D3D9SetVertexDescriptor(*(void**)(self + 8), 0);
    if (p3 != 0) {
        cb[0] = p2 & 0xffffff00u;
        cb[1] = 0; cb[2] = 0; cb[3] = 0; cb[4] = 0;
        bs->D3D9SetShaderData(p3, cb, 1, 1, 4, 3);
    }
    FUN_011f9c10(4, 1);
    D3D9GetResourceDescriptor(localDesc, bs, bs);

    void* compiled = ((void* (__cdecl*)(int, int))g_pfnIndexBuffer)(localDesc[0], localDesc[1]);
    if (compiled == 0) {
        stateAlloc[0] = 0;
        compiled = 0;
    } else {
        stateAlloc[0] = (int)compiled;
        stateAlloc[1] = 0;
        stateAlloc[2] = 0;
        stateAlloc[3] = 0;
        compiled = FUN_011ef6f0(stateAlloc, bs);
    }
    *(void**)(self + 4) = compiled;
    FUN_011f9b10();
    ((void (__cdecl*)(BuildState*))g_pfnFree)(bs);
    return 1;
}

// @ 0x963780  (approximate: message dispatch skeleton)
int __fastcall FUN_00963780(void* self, int, void* wnd, void* msg)
{
    (void)self; (void)wnd;
    unsigned code = *(unsigned*)((char*)msg + 8);
    return (int)(code & 0xffffff00u);
}
