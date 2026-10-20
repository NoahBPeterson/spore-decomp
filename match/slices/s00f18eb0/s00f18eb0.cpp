#include "s00f18eb0.h"

namespace UI {

// ---------------------------------------------------------------------------
// @ 0x00f18eb0  cScenarioPlayProgressBar::cScenarioPlayProgressBar
// ---------------------------------------------------------------------------
cScenarioPlayProgressBar::cScenarioPlayProgressBar()
{
    int* i = (int*)this;
    i[1] = 0x13eb394;
    i[2] = 0x13ec458;
    i[3] = 0;
    i[0] = 0x148c180;
    i[1] = 0x148c178;
    i[2] = 0x148c168;
    i[4] = 0;
    i[5] = 0;
    *(float*)((char*)this + 0x18) = 0.0f;
    *(float*)((char*)this + 0x1c) = 0.0f;
    *(float*)((char*)this + 0x20) = 0.0f;
    *(float*)((char*)this + 0x24) = 0.0f;
    *(float*)((char*)this + 0x28) = 1.0f;
    *(float*)((char*)this + 0x2c) = 0.0f;
    *(uint8_t*)((char*)this + 0x30) = 0;
    *(uint8_t*)((char*)this + 0x31) = 0;
    ((X7f83e0*)((char*)this + 0x34))->Ctor();
    i[0x15] = 0;
    i[0x16] = 0;
    i[0x17] = 0;
    i[0x18] = 0;
    i[0x19] = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f18f50  cScenarioPlayProgressBar::~cScenarioPlayProgressBar
// ---------------------------------------------------------------------------
cScenarioPlayProgressBar::~cScenarioPlayProgressBar()
{
    int* i = (int*)this;
    *(void**)this = (void*)0x148c180;
    *(void**)((char*)this + 4) = (void*)0x148c178;
    *(void**)((char*)this + 8) = (void*)0x148c168;
    if (*(volatile int*)((char*)this + 0x54)) {
        int a = i[0x19];
        int b = i[0x18];
        int c = i[0x17];
        int d = i[0x16];
        int e = i[0x15];
        i[0x15] = 0;
        sub_571db0(e, d, c, b, a);
    }
    ((X7f8c20*)((char*)this + 0x34))->Dtor();
    if (i[5])
        ((void (__thiscall*)(void*))(*(void***)i[5])[1])((void*)i[5]);
    if (i[4])
        ((void (__thiscall*)(void*))(*(void***)i[4])[1])((void*)i[4]);
    i[2] = 0x13ec458;
    i[1] = 0x13eb394;
    i[0] = 0x13eb938;
}

// ---------------------------------------------------------------------------
// @ 0x00f19050  cScenarioPlayProgressBar::Tick
// ---------------------------------------------------------------------------
void cScenarioPlayProgressBar::Tick()
{
    int s = *(int*)((char*)this + 0x90);
    if (s - 5 > 1)
        return;
    if (*(int*)((char*)this + 0x94))
        return;
    ((X93a2e0*)((char*)this + 0x98))->Reset();
    int g = sub_b3d380();
    if (sub_b320d0(0x04bf38a7u) > 0)
        ((Xb32250*)(void*)g)->Release(0x04bf38a7u);
    ((Xefcae0*)this)->Tick();
}

// ---------------------------------------------------------------------------
// @ 0x00f190a0  cScenarioPlayProgressBar::Reset
// ---------------------------------------------------------------------------
void cScenarioPlayProgressBar::Reset()
{
    uint32_t tmp[0x12];
    for (int k = 0; k < 0x12; ++k)
        tmp[k] = 0;
    float* fp = (float*)&tmp[0x11];
    fp[0] = 0.0f;
    fp[1] = 0.0f;
    fp[2] = 0.0f;
    uint32_t* dst = (uint32_t*)((char*)this + 0xc);
    for (int k = 0; k < 0x12; ++k)
        dst[k] = tmp[k];
    *(int*)((char*)this + 0x90) = 2;
    *(int*)((char*)this + 0xc0) = 0;
    *(int*)((char*)this + 0xb8) = 0;
    *(uint8_t*)((char*)this + 0xec) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f19130  cScenarioPlayProgressBar::Release
// ---------------------------------------------------------------------------
void cScenarioPlayProgressBar::Release()
{
    void* p = *(void**)((char*)this + 0xf0);
    if (!p)
        return;
    sub_572020(p, 0);
    *(int*)((char*)this + 0xf0) = 0;
    *(int*)((char*)this + 0xf4) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f19160  cScenarioPlayProgressBar::GetProgressF
// ---------------------------------------------------------------------------
float cScenarioPlayProgressBar::GetProgressF()
{
    return (float)*(int*)((char*)this + 0xbc) * 0.001f;
}

// ---------------------------------------------------------------------------
// @ 0x00f191a0  cScenarioPlayProgressBar::IsEnabled
// ---------------------------------------------------------------------------
void* cScenarioPlayProgressBar::IsEnabled()
{
    if (*(int*)((char*)this + 0x90) == 5) {
        int* g = *(int**)0x16c7aa4;
        if (g[0xd0 / 4])
            return *(void**)((char*)this + 0xc4);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f19be0  cScenarioPlayProgressBar::GetByte
// ---------------------------------------------------------------------------
uint8_t cScenarioPlayProgressBar::GetByte(int idx)
{
    char* base = *(char**)((char*)this + 0x64);
    return *(uint8_t*)(base + (uint32_t)idx * 0x1ac + 0x34);
}

// ---------------------------------------------------------------------------
// @ 0x00f19c00  cScenarioPlayProgressBar::GetField
// ---------------------------------------------------------------------------
int cScenarioPlayProgressBar::GetField(int idx)
{
    char* base = *(char**)((char*)this + 0x64);
    return *(int*)(base + (uint32_t)idx * 0x1ac + 0x24);
}

// ---------------------------------------------------------------------------
// @ 0x00f19c20  cScenarioPlayProgressBar::GetField2
// ---------------------------------------------------------------------------
int cScenarioPlayProgressBar::GetField2(int idx)
{
    char* base = *(char**)((char*)this + 0x64);
    return *(int*)(base + (uint32_t)idx * 0x1ac + 0x4);
}

// ---------------------------------------------------------------------------
// @ 0x00f19c40  cScenarioPlayProgressBar::GetField3
// ---------------------------------------------------------------------------
int cScenarioPlayProgressBar::GetField3(int idx)
{
    char* base = *(char**)((char*)this + 0x64);
    return *(int*)(base + (uint32_t)idx * 0x1ac + 0x30);
}

// ---------------------------------------------------------------------------
// @ 0x00f19c60  cScenarioPlayProgressBar::GetDelta
// ---------------------------------------------------------------------------
int cScenarioPlayProgressBar::GetDelta(int idx)
{
    int* base = (int*)*(int*)((char*)this + 0x64);
    return base[idx * 0x6b + 0xc] - base[idx * 0x6b + 1];
}

// ---------------------------------------------------------------------------
// @ 0x00f19c80  cScenarioPlayProgressBar::GetKind
// ---------------------------------------------------------------------------
uint8_t cScenarioPlayProgressBar::GetKind(int idx)
{
    char* end = *(char**)((char*)this + 0x68);
    char* beg = *(char**)((char*)this + 0x64);
    int count = (int)(end - beg) / 0x1ac;
    if (idx >= count)
        return 0;
    return *(uint8_t*)(*(int*)((char*)this + 0x64) + idx * 0x1ac);
}

// ---------------------------------------------------------------------------
// @ 0x00f19cc0  cScenarioPlayProgressBar::IsKindAb
// ---------------------------------------------------------------------------
bool cScenarioPlayProgressBar::IsKindAb(int idx)
{
    char* end = *(char**)((char*)this + 0x68);
    char* beg = *(char**)((char*)this + 0x64);
    int count = (int)(end - beg) / 0x1ac;
    if (idx >= count)
        return false;
    int k = *(int*)(*(int*)((char*)this + 0x64) + idx * 0x1ac + 0x24);
    return k == 0xa || k == 0xb;
}

// ---------------------------------------------------------------------------
// @ 0x00f19b80  cScenarioPlayProgressBar::IsActive
// ---------------------------------------------------------------------------
bool cScenarioPlayProgressBar::IsActive()
{
    int* g = *(int**)0x16c7aa4;
    void* p = ((Xf3be60*)(void*)g[0x74 / 4])->Find(*(int*)((char*)this + 0xb8));
    if (p)
        if (*(uint8_t*)((char*)p + 0x7c))
            return *(int*)((char*)this + 0xbc) > 0;
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00f18ff0  HasFlag
// ---------------------------------------------------------------------------
bool __cdecl cScenarioPlayProgressBar_HasFlag()
{
    return sub_b320d0(0x04bf38a7u) > 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f19220  KindOk
// ---------------------------------------------------------------------------
bool __cdecl cScenarioPlayProgressBar_KindOk(void* p)
{
    if (!p)
        return false;
    void* q = ((void* (__thiscall*)(void*, uint32_t))(*(void***)p)[0xb8 / 4])(p, 0x175cdc9);
    if (!q)
        return false;
    uint32_t k = *(uint32_t*)((char*)q + 0x38) - 6;
    if (k > 9)
        return true;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00f195a0  Link
// ---------------------------------------------------------------------------
void __cdecl cScenarioPlayProgressBar_Link(void* a)
{
    void* g = sub_b3d300();
    void* h = ((Xb1fdb0*)g)->Find(0);
    if (h)
        ((Xc15d50*)h)->Add(a, 0, 0);
    if (!a)
        return;
    void* c = ((void* (__thiscall*)(void*, uint32_t))(*(void***)a)[0xb8 / 4])(a, 0xce9f6639);
    if (c)
        ((void (__thiscall*)(void*, int))(*(void***)c)[0xc8 / 4])(c, 1);
}

// ---------------------------------------------------------------------------
// @ 0x00f19640  IsReady
// ---------------------------------------------------------------------------
bool __cdecl cScenarioPlayProgressBar_IsReady()
{
    int* g = *(int**)0x16c7aa4;
    int* p = (int*)g[0x74 / 4];
    return *(uint8_t*)((char*)p + 0x14) == 0 && g[0xd0 / 4] != 0;
}

} // namespace UI
