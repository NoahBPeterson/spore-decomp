// match/slices/s00c9ef20/s00c9ef20.cpp
// Slice s00c9ef20 -- Simulator / cVehicle / cLocomotiveObject cluster.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS- /Isrc/game/include
#include <math.h>

typedef unsigned int   u32;
typedef signed   int   i32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long long u64;

static inline char* vpt(void* o) { return *(char**)o; }

// ---------------------------------------------------------------------------
// Free / singleton callees
// ---------------------------------------------------------------------------
void* __stdcall SP_PlanetModel(int a);                 // 0x00b3d350 ret 4
void* __stdcall SP_PlanetModel0();                     // 0x00b3d350 no-arg
void* __stdcall SP_NounManager(int id);                // 0x00b3d300 ret 4
void* __cdecl   GetCurrentGameMode();                  // 0x00b5b800
void* __cdecl   FUN_00cf74c0();                        // 0x00cf74c0 returns manager
void* __stdcall FUN_00ff0430(void* p);                 // 0x00ff0430 ret 4
void* __stdcall FUN_00b3d390(void* e);                 // 0x00b3d390 ret 4
void* __cdecl   EAAllocate(int size, const char* name, int a, int b, int c, int d);
void* __cdecl   FUN_00c9e5d0();                        // 0x00c9e5d0
void* __cdecl   FUN_00befb60(void* p);                 // 0x00befb60 ret 4
void* __stdcall FUN_00c9efc0(void* a);                 // 0x00c9efc0 ret 4

extern float  g_1485720;                               // 0x01485720 (1.0f)
extern float  g_1699b08, g_1699b0c, g_1699b10;         // 0x01699b08..
extern float  g_13ec4b8;                               // 0x013ec4b8 (1e-08)
extern float  g_1485548;                               // 0x01485548 (1.5f)
extern float  g_1474a84;                               // 0x01474a84 (0.0375f)
extern float  g_13eb8b0;                               // 0x013eb8b0 (sign mask)
extern float  g_157c70c;                               // 0x0157c70c
extern float  g_14749a8;                               // 0x014749a8 (FLT_MAX)
extern void*  g_1699ab8;                               // 0x01699ab8
extern void*  g_16c7aa4;                               // 0x016c7aa4
extern char   g_1654c10, g_1654c04;                    // 0x01654c10 / 0x01654c04
extern void*  g_1474a50[];                             // 0x01474a50 table
extern void*  g_1474a44[];                             // 0x01474a44 table
extern void*  g_1474a70[];                             // 0x01474a70 table
extern void*  g_1474a5c[];                             // 0x01474a5c table

// ---------------------------------------------------------------------------
// stub structs (thiscall members resolve to their real addresses)
// ---------------------------------------------------------------------------
struct PlanetStub {
    float* FUN_00b81630(float* out, float* src);            // 0x00b81630
    float* DirectionToSurfacePosition(float* out, float* dir); // 0x00b815a0
    int    GetContinent(float* pos);                        // 0x00b88590
    float  FUN_00b7efe0();                                  // 0x00b7efe0
    float  GetWaterHeight();                                // 0x00b7e390
};

struct NounStub {
    int FUN_00b25f40();                                     // 0x00b25f40
};

struct FieldStub {
    void* FUN_00f3f950(void* arg);                          // 0x00f3f950
};

struct CivMgrStub {
    void FUN_00cf8d60(void* self, u32 changed, u32 flags);  // 0x00cf8d60 ret 0xc
    u8   FUN_00cf7830(void* a);                             // 0x00cf7830 ret 4
};

struct ToolStub {
    u8 FUN_00bfc5d0();                                      // 0x00bfc5d0
};

struct XStub {
    u8 FUN_00c004c0(int a);                                 // 0x00c004c0 ret 4
};

struct SimSingletonStub {
    void* FUN_00dc7d70();                                   // 0x00dc7d70 ctor
    void  FUN_00dcc300(void* a);                            // 0x00dcc300 ret 4
};

struct RefStub {
    u8   FUN_0104bd50();                                    // 0x0104bd50
    void FUN_0104fa90();                                    // 0x0104fa90
};

struct EffStub {
    void* FUN_00bc97f0(int a, int b, float c, int d);       // 0x00bc97f0 ret 0x10
};

struct VStub {
    void FUN_00c3f160(void* a, float f);                    // 0x00c3f160 ret 8
};

struct TimerStub {
    u8   IsRunning();                                       // 0x00feba90
    u64  GetElapsedTime();                                  // 0x00bc3190
    void Restart();                                         // 0x00bc3130
};

struct CStub {
    // ---- 00c9ef20
    u8 FUN_00c9ef20();
    // ---- 00c9ef60
    void FUN_00c9ef60(u32 ms);
    // ---- 00c9f1c0  (free __fastcall, declared later)
    // ---- 00c9f1e0
    void* FUN_00c9f1e0();
    // ---- 00c9f250
    int FUN_00c9f250();
    // ---- 00c9f2d0
    void FUN_00c9f2d0(int a);
    // ---- 00c9f330
    float FUN_00c9f330();
    // ---- 00c9f380
    float FUN_00c9f380();
    // ---- 00c9f3d0
    void* FUN_00c9f3d0();
    // ---- 00c9f410
    u8 FUN_00c9f410();
    // ---- 00c9f490
    u8 FUN_00c9f490(void* a, void* b);
    // ---- 00c9f5c0
    void FUN_00c9f5c0();
    // ---- 00c9f650
    float* FUN_00c9f650(float* out);
    // ---- 00c9f6c0
    void FUN_00c9f6c0();
    // ---- 00c9f750
    void FUN_00c9f750(char on);
    // ---- 00c9f7c0
    void FUN_00c9f7c0();
    // ---- 00c9fa30
    void FUN_00c9fa30(void* p);
    // ---- 00c9fa70
    void SetStance(u32 stance, char b);
    // ---- 00c9fb10
    int FUN_00c9fb10(void* p);
    // ---- 00c9fb40
    void FUN_00c9fb40(float a, int b, int c, float d, float e);
    // ---- 00c9fc60
    void FUN_00c9fc60(void* p);
    // ---- 00c9fd40
    void FUN_00c9fd40(void* p);
    // ---- 00c9fdc0
    float* FUN_00c9fdc0(float* out);
    // ---- 00c9fe40
    u8 FUN_00c9fe40(void* p);
    // ---- 00c9fee0
    void* FUN_00c9fee0();
    // ---- 00c9ff40
    void FUN_00c9ff40(int a, float* out1, float* out2);
    // ---- external callees declared as members
    void  FUN_00c88670(void* p);                            // 0x00c88670 ret 4
    void  FUN_00c886d0(void* p);                            // 0x00c886d0 ret 4
    float* FUN_00d20610();                                  // 0x00d20610
    float FUN_00c9eb80();                                   // 0x00c9eb80

    char pad[4];
};

// ===========================================================================
// @ 0x00c9f0a0  (free function)
// ===========================================================================
void* __cdecl FUN_00c9f0a0(void** src, void** end, void** dst)
{
    if (src == end)
        return dst;
    do {
        if (dst != 0) {
            void* p = *src;
            *dst = p;
            if (p != 0)
                (**(void(__thiscall**)(void*))(vpt(p) + 4))(p);
            dst[1] = src[1];
            dst[2] = src[2];
            *(char*)((char*)dst + 0xc) = *(char*)((char*)src + 0xc);
        }
        src += 4;
        dst += 4;
    } while (src != end);
    return dst;
}

// ===========================================================================
// @ 0x00c9f130  (free function)
// ===========================================================================
void __cdecl FUN_00c9f130(void* pv)
{
    int* p = (int*)pv;
    PlanetStub* pm = (PlanetStub*)SP_PlanetModel0();
    float tmp[3];
    int* r = (int*)pm->FUN_00b81630(tmp, (float*)((char*)p + 0x14));
    *(int*)((char*)p + 0x14) = r[0];
    *(int*)((char*)p + 0x18) = r[1];
    *(int*)((char*)p + 0x1c) = r[2];
    int n = (p[1] - p[0]) / 0x3c;
    if (n > 0) {
        int off = 0;
        do {
            int* q = (int*)(p[0] + off);
            int* r2 = (int*)pm->FUN_00b81630(tmp, (float*)q);
            q[0] = r2[0];
            q[1] = r2[1];
            q[2] = r2[2];
            off += 0x3c;
            --n;
        } while (n != 0);
    }
}

// ===========================================================================
// @ 0x00c9ef20
// ===========================================================================
u8 CStub::FUN_00c9ef20()
{
    if (((TimerStub*)((char*)this + 0xcd8))->IsRunning()) {
        u64 t = ((TimerStub*)((char*)this + 0xcd8))->GetElapsedTime();
        if ((u32)(t >> 32) == 0 && (u32)t < *(u32*)((char*)this + 0xcf8))
            return 1;
    }
    return 0;
}

// ===========================================================================
// @ 0x00c9ef60
// ===========================================================================
void CStub::FUN_00c9ef60(u32 ms)
{
    if (((TimerStub*)((char*)this + 0xcd8))->IsRunning()) {
        u32 prev = *(u32*)((char*)this + 0xcf8);
        u64 t = ((TimerStub*)((char*)this + 0xcd8))->GetElapsedTime();
        if ((u32)(t >> 32) == 0 && (u32)t < prev) {
            *(u32*)((char*)this + 0xcf8) = prev + ms;
            return;
        }
    }
    *(u32*)((char*)this + 0xcf8) = ms;
    ((TimerStub*)((char*)this + 0xcd8))->Restart();
}

// ===========================================================================
// @ 0x00c9f1c0  (free function, __fastcall)
// ===========================================================================
void __fastcall FUN_00c9f1c0(void* self)
{
    void* f = *(void**)((char*)g_16c7aa4 + 0x74);
    ((FieldStub*)f)->FUN_00f3f950(self);
}

// ===========================================================================
// @ 0x00c9f1e0
// ===========================================================================
void* CStub::FUN_00c9f1e0()
{
    if (*(int*)((char*)this + 0x614) != 2 && *(int*)((char*)this + 0x618) == 0) {
        if (GetCurrentGameMode() != &g_1654c10) {
            int r;
            if (*(void**)((char*)this + 0x48) != 0) {
                void* c = *(void**)((char*)this + 0x48);
                if (c == 0)
                    return *(void**)((char*)this + 0x658);
                r = (**(int(__thiscall**)(void*, int))(vpt(c) + 0x5c))(c, 0x137e8e0);
            } else {
                if (*(void**)((char*)this + 0x44) == 0)
                    return *(void**)((char*)this + 0x658);
                r = (int)FUN_00befb60((char*)this + 0x44);
            }
            if (r != 0 && *(int*)(r + 0xb1c) == 2)
                return *(void**)((char*)this + 0x65c);
        }
    }
    return *(void**)((char*)this + 0x658);
}

// ===========================================================================
// @ 0x00c9f250
// ===========================================================================
int CStub::FUN_00c9f250()
{
    int n = (*(int*)((char*)this + 0xc68) - *(int*)((char*)this + 0xc64)) >> 4;
    if (n > 0) {
        int off = 0;
        int cnt = n;
        do {
            void* e = *(void**)(*(int*)((char*)this + 0xc64) + off);
            if (((RefStub*)e)->FUN_0104bd50()) {
                void* r = FUN_00b3d390(e);
                ((RefStub*)r)->FUN_0104fa90();
            }
            off += 0x10;
            --cnt;
        } while (cnt != 0);
    }
    void* p = *(void**)((char*)this + 0xb60);
    if (p != 0 && ((RefStub*)p)->FUN_0104bd50()) {
        void* r = FUN_00b3d390(*(void**)((char*)this + 0xb60));
        ((RefStub*)r)->FUN_0104fa90();
    }
    return n;
}

// ===========================================================================
// @ 0x00c9f2d0
// ===========================================================================
void CStub::FUN_00c9f2d0(int a)
{
    *(int*)((char*)this + 0xc80) -= a;
    if (*(int*)((char*)this + 0xc80) < 1) {
        if (*(int*)((char*)this + 0xb20) != 1) {
            int r = FUN_00c9f250();
            ++*(int*)((char*)this + 0xc78);
            if (r <= *(int*)((char*)this + 0xc78))
                *(int*)((char*)this + 0xc78) = 0;
        }
        *(int*)((char*)this + 0xc80) = *(int*)((char*)this + 0xc7c);
    }
    *(int*)((char*)this + 0xc84) += a;
}

// ===========================================================================
// @ 0x00c9f330
// ===========================================================================
float CStub::FUN_00c9f330()
{
    float k = g_1485720;
    if (GetCurrentGameMode() == &g_1654c10) {
        void* f = *(void**)((char*)g_16c7aa4 + 0x74);
        int r = (int)((FieldStub*)f)->FUN_00f3f950(this);
        if (r != 0)
            k = *(float*)(r + 0x494);
    }
    return *(float*)((char*)this + 0xc5c) * k;
}

// ===========================================================================
// @ 0x00c9f380
// ===========================================================================
float CStub::FUN_00c9f380()
{
    float k = g_1485720;
    if (GetCurrentGameMode() == &g_1654c10) {
        void* f = *(void**)((char*)g_16c7aa4 + 0x74);
        int r = (int)((FieldStub*)f)->FUN_00f3f950(this);
        if (r != 0)
            k = *(float*)(r + 0x490);
    }
    return *(float*)((char*)this + 0x218) * k;
}

// ===========================================================================
// @ 0x00c9f3d0
// ===========================================================================
void* CStub::FUN_00c9f3d0()
{
    void* p = *(void**)((char*)this + 0xb5c);
    if (p == 0)
        return 0;
    if ((**(u8(__thiscall**)(void*))(vpt(p) + 0x2c))(p)) {
        void* q = *(void**)((char*)this + 0xb5c);
        if (q == 0)
            return 0;
        *(void**)((char*)this + 0xb5c) = 0;
        (**(void(__thiscall**)(void*))(vpt(q) + 4))(q);
    }
    return *(void**)((char*)this + 0xb5c);
}

// ===========================================================================
// @ 0x00c9f410
// ===========================================================================
u8 CStub::FUN_00c9f410()
{
    void* p = *(void**)((char*)this + 0xb5c);
    if (p != 0 && (**(u8(__thiscall**)(void*))(vpt(p) + 0x2c))(p)) {
        void* q = *(void**)((char*)this + 0xb5c);
        if (q != 0) {
            *(void**)((char*)this + 0xb5c) = 0;
            (**(void(__thiscall**)(void*))(vpt(q) + 4))(q);
        }
    }
    void* r = *(void**)((char*)this + 0xb5c);
    if (r == 0)
        return 0;
    int a = (**(int(__thiscall**)(void*))(vpt(r) + 0x4c))(r);
    int b = (**(int(__thiscall**)(void*))(vpt(this) + 0x4c))(this);
    if (a != b)
        return 0;
    if (((XStub*)r)->FUN_00c004c0(0))
        return 1;
    if (((XStub*)r)->FUN_00c004c0(1))
        return 1;
    return 0;
}

// ===========================================================================
// @ 0x00c9f490
// ===========================================================================
u8 CStub::FUN_00c9f490(void* a, void* b)
{
    if (a == 0)
        return 0;
    if (b == 0)
        return 1;
    float* self = (float*)this;
    void* o1 = (**(void*(__thiscall**)(void*))(vpt(a) + 8))(a);
    float* p1 = (float*)(**(void*(__thiscall**)(void*))(vpt(o1) + 0x2c))(o1);
    float dx1 = self[0] - p1[0];
    float dy1 = self[1] - p1[1];
    float dz1 = self[2] - p1[2];
    float d1 = sqrtf(dz1 * dz1 + (dy1 * dy1 + dx1 * dx1));
    void* o2 = (**(void*(__thiscall**)(void*))(vpt(b) + 8))(b);
    float* p2 = (float*)(**(void*(__thiscall**)(void*))(vpt(o2) + 0x2c))(o2);
    float dx2 = self[0] - p2[0];
    float dy2 = self[1] - p2[1];
    float dz2 = self[2] - p2[2];
    float d2 = sqrtf(dz2 * dz2 + (dy2 * dy2 + dx2 * dx2));
    if (d1 < self[3]) {
        if ((**(int(__thiscall**)(void*, int))(vpt(a) + 0x5c))(a, 0x436f315) != 0 ||
            (**(int(__thiscall**)(void*, int))(vpt(a) + 0x5c))(a, 0x137e8e0) != 0)
            d1 = 0.0f;
    }
    if (d2 < self[3]) {
        if ((**(int(__thiscall**)(void*, int))(vpt(b) + 0x5c))(b, 0x436f315) != 0 ||
            (**(int(__thiscall**)(void*, int))(vpt(b) + 0x5c))(b, 0x137e8e0) != 0)
            d2 = 0.0f;
    }
    return d2 > d1;
}

// ===========================================================================
// @ 0x00c9f5c0
// ===========================================================================
void CStub::FUN_00c9f5c0()
{
    if (GetCurrentGameMode() != &g_1654c04)
        return;
    void* sub = (char*)this + 0x34;
    if (!(**(u8(__thiscall**)(void*))(vpt(sub) + 0x58))(sub))
        return;
    u32 flags = (**(u8(__thiscall**)(void*))(vpt(sub) + 0x50))(sub) != 0;
    if (((ToolStub*)((char*)this + 0x508))->FUN_00bfc5d0() ||
        (**(u8(__thiscall**)(void*))(vpt(sub) + 0x24))(sub))
        flags |= 2;
    u32 changed = (flags != *(u32*)((char*)this + 0xc38));
    if (changed)
        *(u32*)((char*)this + 0xc38) = flags;
    ((CivMgrStub*)FUN_00cf74c0())->FUN_00cf8d60(this, changed, flags);
}

// ===========================================================================
// @ 0x00c9f650
// ===========================================================================
float* CStub::FUN_00c9f650(float* out)
{
    int id = (**(int(__thiscall**)(void*))(vpt(this) + 0x4c))(this);
    void* nm = SP_NounManager(id);
    int e = ((NounStub*)nm)->FUN_00b25f40();
    float* o = out;
    if (e != 0) {
        o[0] = *(float*)(e + 0xc4);
        o[1] = *(float*)(e + 0xc8);
        o[2] = *(float*)(e + 0xcc);
        return o;
    }
    o[0] = g_1699b08;
    o[1] = g_1699b0c;
    o[2] = g_1699b10;
    return o;
}

// ===========================================================================
// @ 0x00c9f6c0
// ===========================================================================
void CStub::FUN_00c9f6c0()
{
    if (g_1699ab8 == 0) {
        void* p = EAAllocate(0x58, "Simulator/SimSingleton", 0, 0, 0, 0);
        g_1699ab8 = (p != 0) ? ((SimSingletonStub*)p)->FUN_00dc7d70() : 0;
    }
    int i1 = *(int*)((char*)this + 0xb1c);
    ((SimSingletonStub*)g_1699ab8)->FUN_00dcc300(g_1474a50[i1]);
    if (g_1699ab8 == 0) {
        void* p = EAAllocate(0x58, "Simulator/SimSingleton", 0, 0, 0, 0);
        g_1699ab8 = (p != 0) ? ((SimSingletonStub*)p)->FUN_00dc7d70() : 0;
    }
    int i2 = *(int*)((char*)this + 0xb20);
    ((SimSingletonStub*)g_1699ab8)->FUN_00dcc300(g_1474a44[i2]);
}

// ===========================================================================
// @ 0x00c9f750
// ===========================================================================
void CStub::FUN_00c9f750(char on)
{
    if (on != 0) {
        u8(__thiscall * pf)(void*) = *(u8(__thiscall**)(void*))(vpt(this) + 0x50);
        if (!pf(this) && GetCurrentGameMode() == &g_1654c04) {
            int m = (int)FUN_00cf74c0();
            if (*(char*)(m + 0x148) != 0) {
                if (!((CivMgrStub*)FUN_00cf74c0())->FUN_00cf7830((void*)0x64e6678))
                    return;
            }
            ((CStub*)((char*)this - 0x34))->FUN_00c9f6c0();
            *((char*)this + 0x6c) = on;
            FUN_00c9e5d0();
            return;
        }
    }
    *((char*)this + 0x6c) = on;
}

// ===========================================================================
// @ 0x00c9f7c0
// ===========================================================================
void CStub::FUN_00c9f7c0()
{
    int p = *(int*)((char*)this + 0xb68);
    if (p == *(int*)((char*)this + 0xb6c))
        return;
    int kind = *(int*)(p + 0x10);
    EffStub* eff = (EffStub*)((char*)*(void**)((char*)this + 0xaf0) + 8);
    eff->FUN_00bc97f0(1, 0, g_14749a8, 0);
    switch (kind) {
    case 1: eff->FUN_00bc97f0(2, 0, g_14749a8, 0); return;
    case 2: eff->FUN_00bc97f0(4, 0, g_14749a8, 0); return;
    case 3: eff->FUN_00bc97f0(0x10, 0, g_14749a8, 0); return;
    case 4: eff->FUN_00bc97f0(0x20, 0, g_14749a8, 0); return;
    case 5: eff->FUN_00bc97f0(0x40, 0, g_14749a8, 0); return;
    case 6: eff->FUN_00bc97f0(0x80, 0, g_14749a8, 0); return;
    case 7: eff->FUN_00bc97f0(0x100, 0, g_14749a8, 0); return;
    case 8: eff->FUN_00bc97f0(0x200, 0, g_14749a8, 0); return;
    case 9: eff->FUN_00bc97f0(0x400, 0, g_14749a8, 0); return;
    case 10: {
        eff->FUN_00bc97f0(0x800, 0, g_14749a8, 0);
        void* r = eff->FUN_00bc97f0(0x800, 0, g_14749a8, 0);
        if (r != 0)
            *(int*)((char*)r + 0xc) = 0;
        return;
    }
    case 11: {
        eff->FUN_00bc97f0(0x800, 0, g_14749a8, 0);
        void* r = eff->FUN_00bc97f0(0x800, 0, g_14749a8, 0);
        if (r != 0)
            *(int*)((char*)r + 0xc) = 1;
        return;
    }
    case 12:
        eff->FUN_00bc97f0(0x4000, 0, g_14749a8, 0);
        return;
    }
}

// ===========================================================================
// @ 0x00c9fa30
// ===========================================================================
void CStub::FUN_00c9fa30(void* p)
{
    if (p == 0)
        return;
    void** slot = *(void***)((char*)this + 0xb68);
    void* old = *slot;
    if (p == old)
        return;
    (**(void(__thiscall**)(void*))(vpt(p)))(p);
    *slot = p;
    if (old != 0)
        (**(void(__thiscall**)(void*))(vpt(old) + 4))(old);
}

// ===========================================================================
// @ 0x00c9fa70
// ===========================================================================
void CStub::SetStance(u32 stance, char b)
{
    *(u32*)((char*)this + 0xb24) = stance;
    u32* f = (u32*)((char*)*(void**)((char*)this + 0xaf0) + 0x5fc);
    *f &= 0xfffffcff;
    if (*(u32*)((char*)this + 0xb24) == 0) {
        *f |= 0x100;
        if (b == 0) {
            int i = *(int*)((char*)this + 0xb20);
            void* a = FUN_00c9efc0(g_1474a5c[i]);
            ((SimSingletonStub*)g_1699ab8)->FUN_00dcc300(a);
            return;
        }
    } else if (*(u32*)((char*)this + 0xb24) == 1) {
        *f |= 0x200;
        if (b == 0) {
            int i = *(int*)((char*)this + 0xb20);
            void* a = FUN_00c9efc0(g_1474a70[i]);
            ((SimSingletonStub*)g_1699ab8)->FUN_00dcc300(a);
            return;
        }
    }
}

// ===========================================================================
// @ 0x00c9fb10
// ===========================================================================
int CStub::FUN_00c9fb10(void* p)
{
    if (*(int*)this == *(int*)p &&
        *(int*)((char*)this + 0x10) == *(int*)((char*)p + 0x10) &&
        *(int*)((char*)this + 0x14) == *(int*)((char*)p + 0x14))
        return 1;
    return 0;
}

// ===========================================================================
// @ 0x00c9fb40
// ===========================================================================
void CStub::FUN_00c9fb40(float a, int b, int c, float d, float e)
{
    float* v = (float*)((char*)this + 0xc3c);
    *(int*)v = *(int*)&a;
    *(int*)((char*)this + 0xc40) = b;
    *(int*)((char*)this + 0xc44) = c;
    float len = FUN_00c9eb80();
    if (len > 0.0f) {
        float x = v[0], y = v[1], z = v[2];
        float inv = 1.0f / sqrtf(z * z + (y * y + x * x) + g_13ec4b8);
        float out[3];
        PlanetStub* pm = (PlanetStub*)SP_PlanetModel0();
        float* sp = pm->DirectionToSurfacePosition(out, v);
        float nx = (x * inv) * len;
        float ny = (y * inv) * len;
        float nz = (z * inv) * len;
        v[0] = sp[0] + nx;
        v[1] = sp[1] + ny;
        v[2] = sp[2] + nz;
    }
    *(float*)((char*)this + 0xc48) = d;
    *(float*)((char*)this + 0xc4c) = e;
}

// ===========================================================================
// @ 0x00c9fc60
// ===========================================================================
void CStub::FUN_00c9fc60(void* p)
{
    FUN_00c88670(p);
    if (*(int*)((char*)this + 0xcd8) != 0)
        FUN_00ff0430(p);
    if (*(int*)((char*)this + 0xcc8) != 0) {
        float* vel = FUN_00d20610();
        float spd = sqrtf(vel[0] * vel[0] + vel[1] * vel[1] + vel[2] * vel[2]) * g_1474a84;
        if (spd <= g_1485720)
            spd = g_1485720;
        if (spd >= g_1485548)
            spd = g_1485548;
        float m = (**(float(__thiscall**)(void*))(vpt(this) + 0x70))(this);
        ((VStub*)*(void**)((char*)this + 0xcc8))->FUN_00c3f160(p, m * spd);
    }
    int q = *(int*)((char*)this + 0xccc);
    if (q != 0) {
        *(int*)(q + 4) = *(int*)p;
        *(int*)(q + 8) = *(int*)((char*)p + 4);
        *(int*)(q + 0xc) = *(int*)((char*)p + 8);
    }
}

// ===========================================================================
// @ 0x00c9fd40
// ===========================================================================
void CStub::FUN_00c9fd40(void* p)
{
    FUN_00c886d0(p);
    int e = *(int*)((char*)this + 0xccc);
    if (e == 0)
        return;
    float x = *(float*)p;
    float y = *(float*)((char*)p + 4);
    float z = *(float*)((char*)p + 8);
    float w = *(float*)((char*)p + 0xc);
    *(u32*)(e + 0x10) = *(u32*)&y;
    *(u32*)(e + 0x14) = *(u32*)&x ^ 0x80000000u;
    *(u32*)(e + 0x18) = *(u32*)&w;
    *(u32*)(e + 0x1c) = *(u32*)&z ^ 0x80000000u;
}

// ===========================================================================
// @ 0x00c9fdc0
// ===========================================================================
float* CStub::FUN_00c9fdc0(float* out)
{
    if (*(int*)((char*)this + 0x284) == 0) {
        void* sub = (char*)this + 0x34;
        float* p = (float*)(**(void*(__thiscall**)(void*))(vpt(sub) + 0x2c))(sub);
        out[0] = p[0];
        out[1] = p[1];
        out[2] = p[2];
        return out;
    }
    if (*(int*)((char*)this + 0x228) == *(int*)((char*)this + 0x22c)) {
        out[0] = *(float*)((char*)this + 0x23c);
        out[1] = *(float*)((char*)this + 0x240);
        out[2] = *(float*)((char*)this + 0x244);
        return out;
    }
    int p = *(int*)((char*)this + 0x22c);
    out[0] = *(float*)(p - 0x3c);
    out[1] = *(float*)(p - 0x38);
    out[2] = *(float*)(p - 0x34);
    return out;
}

// ===========================================================================
// @ 0x00c9fe40
// ===========================================================================
u8 CStub::FUN_00c9fe40(void* p)
{
    int pm = (int)SP_PlanetModel0();
    if (pm == 0)
        return 0;
    void* sub = (char*)this + 0x34;
    float* pos = (float*)(**(void*(__thiscall**)(void*))(vpt(sub) + 0x2c))(sub);
    PlanetStub* planet = (PlanetStub*)pm;
    int c1 = planet->GetContinent(pos);
    int kind = *(int*)((char*)this + 0xb1c);
    if (kind == 0) {
        if (*(char*)(c1 + *(int*)(pm + 0x64)) == 0)
            return 1;
    } else if (kind == 1) {
        if (*(char*)(c1 + *(int*)(pm + 0x64)) != 0)
            return 1;
    } else {
        return 0;
    }
    void* sub2 = (char*)p + 0x34;
    float* pos2 = (float*)(**(void*(__thiscall**)(void*))(vpt(sub2) + 0x2c))(sub2);
    int c2 = planet->GetContinent(pos2);
    return c1 == c2;
}

// ===========================================================================
// @ 0x00c9fee0
// ===========================================================================
void* CStub::FUN_00c9fee0()
{
    void* p = *(void**)((char*)this + 0xb7c);
    if (p != 0) {
        void* q = *(void**)((char*)this + 0xb7c);
        if (q == 0)
            return 0;
        void* r = (**(void*(__thiscall**)(void*, int))(vpt(q) + 0xb8))(q, 0x17f243b);
        if (r != 0 && (**(u8(__thiscall**)(void*))(vpt(r) + 0x2c))(r)) {
            void* s = *(void**)((char*)this + 0xb7c);
            *(void**)((char*)this + 0xb7c) = 0;
            if (s != 0)
                (**(void(__thiscall**)(void*))(vpt(s) + 0xc0))(s);
        }
    }
    return *(void**)((char*)this + 0xb7c);
}

// ===========================================================================
// @ 0x00c9ff40
// ===========================================================================
void CStub::FUN_00c9ff40(int a, float* out1, float* out2)
{
    PlanetStub* pm = (PlanetStub*)SP_PlanetModel(a);
    float f = pm->FUN_00b7efe0();
    if (*(int*)((char*)this + 0xb1c) == 2) {
        PlanetStub* pm2 = (PlanetStub*)SP_PlanetModel0();
        float wh = pm2->GetWaterHeight();
        float base = FUN_00c9eb80() + wh;
        *out1 = base;
        if (base - g_157c70c < f)
            *out1 = g_157c70c + f;
    } else {
        *out1 = FUN_00c9eb80() + f;
    }
    *out2 = *out1 - f;
}
