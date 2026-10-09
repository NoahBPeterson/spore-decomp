// Slice s00fd90c0 -- rw::movie::VideoRenderer_Rw4 / cMovieSystem init and the
// SP::cAppModeSpace key/mode helpers (0x00fd90c0..0x00fd9f6c).
// Module flags: /O2 /MD /Gy /TP
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
extern u32   DAT_01493980;
extern u32   DAT_01493990;
extern u32   DAT_01493d20;
extern u32   DAT_01493d80;
extern u32   DAT_01485720;    // 1.0f
extern float DAT_014007f4;
extern float DAT_016077c4;
extern float DAT_016077c8;
extern void* DAT_016e61a8;
extern void* DAT_016f4b10;
extern void* DAT_01654c05;
extern u8    DAT_013eb8a4[];  // "Graphics"
extern u8    DAT_013ebc58[];  // "App"
extern u8    DAT_01493dcc[];  // "VideoRenderable data buffer"

// ---------------------------------------------------------------------------
// free callees
// ---------------------------------------------------------------------------
void* __cdecl  FUN_0067dd70();                       // SP::MaterialManager
void* __cdecl  FUN_0067dd60();                       // 0x0067dd60
void* __cdecl  FUN_0067dcc0();                       // SP::MessageServer
void* __cdecl  FUN_0067de20();                       // SP::CheatManager
void* __cdecl  FUN_0067caa0();                       // SP::WindowManager
void* __cdecl  FUN_00925cb0();                       // EA::Allocator::ICoreAllocator::GetDefaultAllocator
void* __cdecl  FUN_011e58c0();                       // 0x011e58c0
void  __cdecl  FUN_011e5cd0(void*);                  // 0x011e5cd0
int   __stdcall FUN_011ef750(int, int, void*);       // 0x011ef750
char  __cdecl  FUN_006ddcc0(int, int, void*, void*); // 0x006ddcc0
void  __cdecl  FUN_006ddd80(int, void*, void*, void*); // 0x006ddd80
u32   __cdecl  FUN_00932e80(const char*, u32, int);  // FNV1_String8
void  __cdecl  FUN_00fceb30(int, int, int, int, int, int, int, int, int);
void* __cdecl  FUN_00f473a0(int, const char*, int, int, int, int); // operator new
void  __cdecl  FUN_00fcdf40(int, int, int, int, void*); // VideoRenderable::GetDataBufSizes
void* __cdecl  FUN_00b2f740();                       // returns char
void* __cdecl  FUN_00805180();                       // returns char
void* __cdecl  FUN_00b3d250();                       // SP::GameInputManager
void* __cdecl  FUN_00b3d2c0();                       // SP::RelationshipManager
void* __cdecl  FUN_00b3d4a0();                       // CommManager
void* __stdcall FUN_00b3d3f0(int);                   // 0x00b3d3f0 -> void*
void* __stdcall FUN_00b3d470(void*);                 // 0x00b3d470 -> void*
void* __cdecl  FUN_00b5b800();                       // SP::GetCurrentGameMode
void* __cdecl  FUN_010212a0();                       // GetActivePlanetRecord
int   __stdcall FUN_01021230(int);                   // 0x01021230
int   __stdcall FUN_01021230_0();                    // 0x01021230 (no-arg call site)
void  __cdecl  FUN_010213b0(int);                    // 0x010213b0
int   __cdecl  FUN_01021080();                       // GetUniverseContext
void* __cdecl  FUN_01021240();                       // SP::cSPMission::IsArchived
int   __cdecl  FUN_01021090();                       // GetPlayerEmpireID
void* __cdecl  FUN_010407c0(float);                  // GetSpaceRelationshipTuning
void  __cdecl  FUN_01041c50(const char*, u32, int);  // 0x01041c50
void* __cdecl  FUN_010666a0();                       // 0x010666a0
void* __cdecl  FUN_00d06400();                       // 0x00d06400
void* __cdecl  FUN_00fcd940_(void);                  // placeholder

// ---------------------------------------------------------------------------
// thiscall callees on foreign objects
// ---------------------------------------------------------------------------
struct Ext {
    void* FUN_00fcd940(int);                  // 0x00fcd940 ctor helper
    void* FUN_00fd9680();                     // 0x00fd9680 ctor
    void* FUN_00fc7dd0(void*);                // 0x00fc7dd0 ctor
    void* FUN_00fc8080();                     // 0x00fc8080 ctor
    void* FUN_00fd95e0();                     // 0x00fd95e0 ctor
    void* FUN_00fcde80();                     // 0x00fcde80 ctor
    void* FUN_00fc7f30();                     // 0x00fc7f30 ctor
    void* FUN_011e64a0(int, void*);           // 0x011e64a0
    void  FUN_011ef880(void*);                // 0x011ef880
    void* FUN_00fd8c40(void*);                // 0x00fd8c40 cMovieCheat ctor
    void* FUN_00576650(void*);                // GetImageResource (0x00576650)
    void* FUN_00ae9390();                     // 0x00ae9390 -> char
    void  FUN_00e190c0(int);                  // 0x00e190c0
    void* FUN_00e18c70(void*);                // 0x00e18c70 -> char
    int   FUN_00bb9ae0();                     // 0x00bb9ae0
    void* FUN_00b1fdb0();                     // GetAvatar
    void  FUN_00d00a10(void*, int);           // returns float
    void* FUN_01040820();                     // returns float
    void* FUN_00c8b770();                     // cStar::GetSolarSystem
    void  FUN_00c86c70();                     // cSolarSystem::ActivateGraphics
    void  FUN_01034b90();                     // 0x01034b90
    void  FUN_00d06400();                     // 0x00d06400
    char  FUN_00d09660();                     // 0x00d09660 -> char
    void* FUN_01065e20();                     // 0x01065e20 -> char
    void  FUN_01067b60();                     // 0x01067b60
};
static inline Ext* E(void* p) { return (Ext*)p; }
static inline void** VTP(void* o) { return *(void***)o; }

// ---------------------------------------------------------------------------
// cMovieSystem (0x00fd90c0)
// ---------------------------------------------------------------------------
struct MovieSys {
    u8 raw[0x400];
    bool Init();
};
// @ 0x00fd90c0
bool MovieSys::Init() {
    void* mm = FUN_0067dd70();
    ((void(__thiscall*)(void*, u32, void*, void*))VTP(mm)[0x2c / 4])(
        mm, 4, &DAT_01493980, raw + 0x24);

    void* p;
    p = FUN_00f473a0(0x20, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fcd940(4) : 0;
    *(void**)(raw + 0x0c) = p;

    p = FUN_00f473a0(0x3c, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fd9680() : 0;
    *(void**)(raw + 0x10) = p;

    p = FUN_00f473a0(0x1c, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fc7dd0(FUN_00925cb0()) : 0;
    *(void**)(raw + 0x18) = p;

    p = FUN_00f473a0(0x24, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fc8080() : 0;
    *(void**)(raw + 0x1c) = p;

    p = FUN_00f473a0(0x0c, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fd95e0() : 0;
    *(void**)(raw + 0x14) = p;

    if (DAT_016f4b10 == 0) {
        void* x = FUN_011e58c0();
        void* tmp;
        E(&tmp)->FUN_011e64a0(0, x);
        FUN_011e5cd0(&tmp);
    }

    p = FUN_00f473a0(0x3c, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fcde80() : 0;
    *(void**)(raw + 0x64) = p;
    ((void(__thiscall*)(void*, float))VTP(p)[0x34 / 4])(p, DAT_014007f4);
    ((void(__thiscall*)(void*, int))VTP(*(void**)(raw + 0x64))[0x44 / 4])(*(void**)(raw + 0x64), 0x2328);
    ((void(__thiscall*)(void*, int))VTP(*(void**)(raw + 0x64))[0x24 / 4])(*(void**)(raw + 0x64), 0x140);
    ((void(__thiscall*)(void*, int))VTP(*(void**)(raw + 0x64))[0x2c / 4])(*(void**)(raw + 0x64), 0xf0);

    if (DAT_016e61a8 != 0) {
        u32 v = (u32)(int)*(float*)((char*)DAT_016e61a8 + 0xc0);
        *(u32*)(raw + 0x328) = v;
        if (v > 0x5622) *(u32*)(raw + 0x328) = v >> 1;
    }

    p = FUN_00f473a0(0x20, (const char*)DAT_013eb8a4, 0, 0, 0, 0);
    if (p) {
        E(p)->FUN_00fc7f30();
        *(void**)p = &DAT_01493990;
    }
    *(void**)(raw + 0x68) = p;
    void** vt = (void**)(*(void**)p) ;
    ((void(__thiscall*)(void*, void*))vt[1])(p, FUN_00925cb0());
    ((void(__thiscall*)(void*, u32))VTP(*(void**)(raw + 0x68))[0x24 / 4])(*(void**)(raw + 0x68), *(u32*)(raw + 0x328));
    ((void(__thiscall*)(void*, int))VTP(*(void**)(raw + 0x68))[0x2c / 4])(*(void**)(raw + 0x68), 2);

    p = FUN_00f473a0(0x110, (const char*)DAT_013ebc58, 0, 0, 0, 0);
    p = p ? E(p)->FUN_00fd8c40(this) : 0;
    void* cheat = FUN_0067de20();
    ((void(__thiscall*)(void*, const char*, void*, int))VTP(cheat)[0x18 / 4])(
        cheat, "movie", p, 0);

    void* param = raw + 8;
    void* ms;
    ms = FUN_0067dcc0();
    ((void(__thiscall*)(void*, void*, u32))VTP(ms)[0x24 / 4])(ms, param, 0x1ee1008);
    ms = FUN_0067dcc0();
    ((void(__thiscall*)(void*, void*, u32))VTP(ms)[0x24 / 4])(ms, param, 0x1ee100e);
    ms = FUN_0067dcc0();
    ((void(__thiscall*)(void*, void*, u32))VTP(ms)[0x24 / 4])(ms, param, 0x1ee100f);
    ms = FUN_0067dcc0();
    ((void(__thiscall*)(void*, void*, u32))VTP(ms)[0x24 / 4])(ms, param, 0x44edd9a);
    ms = FUN_0067dcc0();
    ((void(__thiscall*)(void*, void*, u32))VTP(ms)[0x24 / 4])(ms, param, 0x44edd9c);
    return true;
}

// ---------------------------------------------------------------------------
// rw::movie::VideoRenderer_Rw4
// ---------------------------------------------------------------------------
struct Vid {
    u32 x;
    void  f9460(void* p);
    u8    f9480(int param_2);
    void  f9610(int param_2);
    Vid*  f9680();
    void  f96d0();    void  f9750(int, int, int);
    void  f97c0(void* param_2);
    void  f9b70(int, int, int, int, u32);
};
// @ 0x00fd9460
void Vid::f9460(void* p) {
    *(void**)((char*)this + 4) = p;
    *(void**)((char*)this + 8) = FUN_011e58c0();
}

// @ 0x00fd9480
u8 Vid::f9480(int param_2) {
    char* s = (char*)this;
    u8 result = 0;
    if (*(int*)(param_2 + 0x30) == 0) {
        int iVar3 = *(int*)(s + 8);
        result = *(u8*)(param_2 + 0x51);
        if ((*(u8*)(iVar3 + 4) & 1) == 0) {
            void* p = FUN_0067dd60();
            ((void(__thiscall*)(void*, int))VTP(p)[0x34 / 4])(p, iVar3);
        }
        void* local_1c[3];
        if (FUN_011ef750(2, 0, local_1c) != 0) {
            int iVar1 = *(int*)(s + 0x2c);
            int iVar3b = *(int*)(s + 0x30);
            int iVar4 = iVar1 * iVar3b + *(int*)(param_2 + 4);
            FUN_00fceb30(*(int*)(param_2 + 4), iVar4,
                         (iVar1 >> 1) * (iVar3b >> 1) + iVar4,
                         iVar1, iVar1, iVar3b, (int)local_1c[0],
                         *(int*)(s + 0x34) * 4, 1);
            iVar3b = *(int*)(s + 8);
            if ((*(u8*)(iVar3b + 4) & 1) == 0) {
                void* p = FUN_0067dd60();
                ((void(__thiscall*)(void*, int))VTP(p)[0x34 / 4])(p, iVar3b);
            }
            E(local_1c)->FUN_011ef880(local_1c);
        }
    } else if (*(int*)(param_2 + 0x30) == 3) {
        int iVar3 = *(int*)(s + 8);
        if ((*(u8*)(iVar3 + 4) & 1) == 0) {
            void* p = FUN_0067dd60();
            ((void(__thiscall*)(void*, int))VTP(p)[0x34 / 4])(p, iVar3);
        }
        void* local_1c[3];
        if (FUN_011ef750(2, 0, local_1c) != 0) {
            void* src = *(void**)(param_2 + 4);
            int size = *(int*)(s + 0x2c) * 4;
            int n = 0;
            void* dst = local_1c[0];
            while (n < *(int*)(s + 0x30)) {
                FUN_00fceb30(0, 0, 0, 0, 0, 0, 0, 0, 0); // placeholder (memmove)
                (void)dst; (void)src; (void)size;
                n++;
            }
            iVar3 = *(int*)(s + 8);
            if ((*(u8*)(iVar3 + 4) & 1) == 0) {
                void* p = FUN_0067dd60();
                ((void(__thiscall*)(void*, int))VTP(p)[0x34 / 4])(p, iVar3);
            }
            E(local_1c)->FUN_011ef880(local_1c);
            return 0;
        }
    }
    return result;
}

// @ 0x00fd9610
void Vid::f9610(int param_2) {
    char* s = (char*)this;
    int n = *(int*)(param_2 + 0x38);
    if (n != 0) {
        int* pu = (int*)(param_2 + 4);
        do {
            u32 stack[4];
            stack[0] = pu[0];
            stack[1] = 0;
            stack[2] = 0;
            stack[3] = 0;
            void* p = *(void**)(s + 8);
            ((void(__thiscall*)(void*, void*))VTP(p)[8 / 4])(p, stack);
            pu[0] = 0;
            pu[3] = 0;
            pu++;
            n--;
        } while (n != 0);
    }
    *(int*)(param_2 + 0x28) = 0;
    *(int*)(param_2 + 0x2c) = 0;
    *(int*)(param_2 + 0x30) = 4;
}

// @ 0x00fd9680
Vid* Vid::f9680() {
    char* a = (char*)this;
    *(void**)a = &DAT_01493d80;
    *(int*)(a + 4) = 0;
    *(int*)(a + 8) = 0;
    *(float*)(a + 0x18) = 0.0f;
    *(float*)(a + 0x1c) = 0.0f;
    *(float*)(a + 0x20) = 0.0f;
    float one = *(float*)&DAT_01485720;
    *(int*)(a + 0x0c) = 0;
    *(int*)(a + 0x10) = 0;
    *(int*)(a + 0x14) = 0;
    *(float*)(a + 0x24) = one;
    *(float*)(a + 0x28) = one;
    *(int*)(a + 0x2c) = 0;
    *(int*)(a + 0x30) = 0;
    *(int*)(a + 0x34) = 0;
    *(int*)(a + 0x38) = 0;
    return this;
}

// @ 0x00fd96d0
void Vid::f96d0() {
    char* a = (char*)this;
    *(void**)a = &DAT_01493d80;
    volatile int* r1 = *(volatile int**)(a + 8);
    if (r1) {
        int* pi = (int*)(a + 8);
        *pi = 0;
        // intrusive refcount release (interlocked)
        volatile int* c = (volatile int*)(*(int*)(a + 8) + 8);
        (void)c; (void)r1;
    }
    *(void**)a = &DAT_01493d20;
}

// @ 0x00fd9750
void Vid::f9750(int param_2, int param_3, int param_4) {
    (void)param_2;
    char* s = (char*)this;
    *(int*)(s + 0x2c) = param_3;
    *(int*)(s + 0x30) = param_4;
    void* mm = FUN_0067dd60();
    void* img = ((void*(__thiscall*)(void*, int, int, int, int, int, int))VTP(mm)[0x40 / 4])(
        mm, param_3, param_4, 1, 8, 0x15, 0);
    E(s + 8)->FUN_00576650(img);
    *(int*)(s + 0x34) = param_3;
    *(int*)(s + 0x38) = param_4;
    void* mat = FUN_0067dd70();
    u32 h = FUN_00932e80("Generic2D", 0x811c9dc5, 1);
    void* r = ((void*(__thiscall*)(void*, u32))VTP(mat)[0x28 / 4])(mat, h);
    *(void**)(s + 4) = r;
}

// @ 0x00fd97c0
void Vid::f97c0(void* param_2) {
    char* s = (char*)this;
    float* p = (float*)param_2;
    char c = (char)f9480((int)param_2);
    if (*(void**)(s + 0x10)) {
        ((void(__cdecl*)(void*, void*))*(void**)(s + 0x10))(param_2, *(void**)(s + 0x14));
    }
    void* pv = param_2;
    void* local_38[4];
    char c3 = FUN_006ddcc0(1, 4, &pv, local_38);
    if (c3 == 0) return;

    float fStack_24 = (float)(int)p[10];
    float fVar4 = (float)((int)*(float*)(s + 0x18) & 0xffff);
    float fVar5 = (float)((int)*(float*)(s + 0x1c) & 0xffff);
    float fStack_10 = (float)((int)((float)*(int*)(s + 0x30) * *(float*)(s + 0x28) + *(float*)(s + 0x1c)) & 0xffff);
    float fStack_c = (float)((int)((float)*(int*)(s + 0x2c) * *(float*)(s + 0x24) + *(float*)(s + 0x18)) & 0xffff);
    if ((int)p[10] < 0) fStack_24 = fStack_24 + 4294967296.0f;
    fStack_24 = fStack_24 / (float)*(int*)(s + 0x34);
    float fStack_28 = (float)(int)p[0xb];
    if ((int)p[0xb] < 0) fStack_28 = fStack_28 + 4294967296.0f;
    fStack_28 = fStack_28 / (float)*(int*)(s + 0x38);

    float fVar6 = fVar5 + DAT_016077c8;
    if (c == 0) {
        p[0] = fVar4 + DAT_016077c4;
        p[1] = fVar6;
        p[2] = 0.0f; p[3] = 0.0f; p[4] = 0.0f;
        fVar6 = fStack_10 + DAT_016077c8;
        p[5] = fVar4 + DAT_016077c4;
        p[6] = fVar6;
        p[7] = 0.0f; p[8] = 0.0f; p[9] = fStack_28;
        fVar5 = fVar5 + DAT_016077c8;
        p[10] = fStack_c + DAT_016077c4;
        p[0xb] = fVar5;
        p[0xc] = 0.0f; p[0xd] = fStack_24; p[0xe] = 0.0f;
        fStack_c = fStack_c + DAT_016077c4;
        float fStack_8 = fStack_10 + DAT_016077c8;
        p[0xf] = fStack_c;
        p[0x10] = fStack_8;
        p[0x11] = 0.0f;
        fVar4 = fStack_28;
    } else {
        p[0] = fVar4 + DAT_016077c4;
        p[1] = fVar6;
        p[2] = 0.0f; p[3] = 0.0f; p[4] = fStack_28;
        fVar6 = fStack_10 + DAT_016077c8;
        p[5] = fVar4 + DAT_016077c4;
        p[6] = fVar6;
        p[7] = 0.0f; p[8] = 0.0f; p[9] = 0.0f;
        fVar5 = fVar5 + DAT_016077c8;
        p[10] = fStack_c + DAT_016077c4;
        p[0xb] = fVar5;
        p[0xc] = 0.0f; p[0xd] = fStack_24; p[0xe] = fStack_28;
        fStack_c = fStack_c + DAT_016077c4;
        float fStack_8 = fStack_10 + DAT_016077c8;
        p[0xf] = fStack_c;
        p[0x10] = fStack_8;
        p[0x11] = 0.0f;
        fVar4 = 0.0f;
    }
    p[0x12] = fStack_24;
    p[0x13] = fVar4;
    FUN_006ddd80(4, *(void**)(s + 4), *(void**)(s + 8), *(void**)(s + 0xc));
}

// @ 0x00fd9b70
void Vid::f9b70(int param_2, int param_3, int param_4, int param_5, u32 param_6) {
    char* s = (char*)this;
    *(u32*)(param_2 + 0x38) = param_6;
    u32 stack[8];
    FUN_00fcdf40(param_3, param_4, param_5, param_6, stack);
    if (param_6 != 0) {
        int* pu = (int*)(param_2 + 0x10);
        for (u32 i = 0; i < param_6; ++i) {
            u32 buf[8];
            buf[0] = stack[i];
            buf[1] = 0; buf[2] = 0; buf[3] = 0;
            buf[4] = 4; buf[5] = 1; buf[6] = 1; buf[7] = 1;
            void* alloc = *(void**)(s + 8);
            void* vt2 = *(void**)(alloc);
            ((void(__thiscall*)(void*, u32*, u32*, const char*))VTP(alloc)[1])(
                alloc, &buf[1], buf, (const char*)DAT_01493dcc);
            (void)vt2;
            pu[-3] = buf[1];
            *pu = stack[i];
            pu++;
        }
    }
    *(int*)(param_2 + 0x28) = param_3;
    *(int*)(param_2 + 0x2c) = param_4;
    *(int*)(param_2 + 0x30) = param_5;
}

// ===========================================================================
// cAppModeSpace helpers
// ===========================================================================
struct AppMode {
    u8 raw[0x200];
    void f9c90(int a);
    char f9ce0(int a, int b);
    int  f9d00();
    void f9d30();
    void f9d90();
    void f9de0();
    void f9ea0(int key, int param3);
};
char f9e80(int a, int* p);   // free callback

// @ 0x00fd9c90
void AppMode::f9c90(int a) {
    (void)a;
    char c = (char)(int)FUN_00b2f740();
    void* wm = FUN_0067caa0();
    int iv = ((int(__thiscall*)(void*))VTP(wm)[0x84 / 4])(wm);
    char flag = iv != 0;
    char c2 = (char)(int)FUN_00805180();
    if (c2 && !c && !flag) return;
    void* gi = FUN_00b3d250();
    ((void(__thiscall*)(void*, int))VTP(gi)[0x48 / 4])(gi, a);
}

// @ 0x00fd9ce0
char AppMode::f9ce0(int a, int b) {
    (void)a; (void)b;
    unsigned u = (unsigned)FUN_01021080();
    if (u <= 2u) {
        void* gi = FUN_00b3d250();
        return ((char(__thiscall*)(void*, int, int))VTP(gi)[0x50 / 4])(gi, a, b);
    }
    return 0;
}

// @ 0x00fd9d00
int AppMode::f9d00() {
    void* gi = FUN_00b3d250();
    int r = ((int(__thiscall*)(void*))VTP(gi)[0x34 / 4])(gi);
    if (r == 1) return 1;
    gi = FUN_00b3d250();
    r = ((int(__thiscall*)(void*))VTP(gi)[0x34 / 4])(gi);
    if (r == 2) return 1;
    return 0;
}

// @ 0x00fd9d30
void AppMode::f9d30() {
    void* gm = FUN_00b5b800();
    if (gm != &DAT_01654c05) return;
    int u = FUN_01021080();
    if (u == 1) {
        void* star = (void*)FUN_01021230(0);
        void* ss = (void*)E(star)->FUN_00c8b770();
        E(ss)->FUN_00c86c70();
        void* rm = FUN_00b3d2c0();
        E(rm)->FUN_00d06400();
        return;
    }
    u = FUN_01021080();
    if (u == 2) FUN_010213b0(-1);
    void* rm = FUN_00b3d2c0();
    E(rm)->FUN_00d06400();
}

// @ 0x00fd9d90
void AppMode::f9d90() {
    void* gm = FUN_00b5b800();
    if (gm != &DAT_01654c05) return;
    int u = FUN_01021080();
    if (u == 1) {
        void* star = (void*)FUN_01021230(1);
        void* ss = (void*)E(star)->FUN_00c8b770();
        E(ss)->FUN_00c86c70();
        void* x = (void*)FUN_01021230_0();
        void* y = FUN_00b3d470(x);
        E(y)->FUN_01034b90();
        return;
    }
    u = FUN_01021080();
    if (u == 2) FUN_010213b0(2);
}

// @ 0x00fd9de0
void AppMode::f9de0() {
    void* m = FUN_01021240();
    char* es = (char*)m;
    int t = E(es)->FUN_00bb9ae0();
    if (t != 5) return;
    void* av = E(es)->FUN_00b1fdb0();
    int eid = FUN_01021090();
    if (av == (void*)eid) return;
    int eid2 = FUN_01021090();
    void* av2 = E(es)->FUN_00b1fdb0();
    void* rm = FUN_00b3d2c0();
    float f = ((float(__thiscall*)(void*, void*, int))VTP(rm)[0x00 + 0]) (rm, av2, eid2);
    (void)f;
}

// @ 0x00fd9e80
char f9e80(int a, int* p) {
    if (*p != 0) {
        void* q = (void*)*p;
        ((void(__thiscall*)(void*, int))VTP((char*)q + 8)[0x1c / 4])((char*)q + 8, a);
    }
    return 1;
}

// @ 0x00fd9ea0
void AppMode::f9ea0(int key, int param3) {
    char* s = (char*)this;
    if (*(int*)(s + 0x15c) != 0 && *(int*)(*(int*)(s + 0x15c) + 0x20) != 0) {
        char c = (char)(int)E((void*)*(int*)(*(int*)(s + 0x15c) + 0x20))->FUN_00d09660();
        if (c) goto done;
    }
    if (key == 0x4c) {
        if (param3 != 0) goto done;
        void* cm = FUN_00b3d4a0();
        char c = (char)(int)E(cm)->FUN_00ae9390();
        if (c) goto done;
        void* t = FUN_00b3d3f0(-0xe);
        E(t)->FUN_00e190c0(-0xe);
    } else if (key == 0x52) {
        if (param3 != 0) goto done;
        void* cm = FUN_00b3d4a0();
        char c = (char)(int)E(cm)->FUN_00ae9390();
        if (c) goto done;
        void* t = FUN_00b3d3f0(-0xd);
        E(t)->FUN_00e190c0(-0xd);
    } else if (key == 0x59) {
        void* x = FUN_010666a0();
        char c = (char)(int)E(x)->FUN_01065e20();
        if (!c) {
            void* y = FUN_010666a0();
            E(y)->FUN_01067b60();
        }
    }
done:
    void* t2 = FUN_00b3d3f0(0);
    char c2 = (char)(int)E(t2)->FUN_00e18c70(0);
    if (c2) return;
    void* gi = FUN_00b3d250();
    char c3 = ((char(__thiscall*)(void*, int, int))VTP(gi)[0x44 / 4])(gi, key, param3);
    if (c3) return;
    gi = FUN_00b3d250();
    ((void(__thiscall*)(void*, int, int))VTP(gi)[0x4c / 4])(gi, key, param3);
}
