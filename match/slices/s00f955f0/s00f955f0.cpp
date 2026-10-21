// Slice s00f955f0 (batch gold4, slice 11) -- SP terrain script-effect / sphere helpers.
// Object file: SP terrain effects (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include
//
//   0x00f955f0  cTerrainScriptEffect::ApplyEffect(...)   ret 0xc
//   0x00f959f0  SetTerrainToggle(bool)                   ret 4
//   0x00f95ac0  UnpackColor(unsigned, float*)            free
//   0x00f95b70  DrawTerrainOverlay(int)                  ret 4
//   0x00f95cf0  cTerrainOverlay::cTerrainOverlay()       void
//   0x00f95d90  cTerrainOverlay::Reset()                 void
//   0x00f95dd0  DrawTerrainGrid(int)                     ret 4
//   0x00f96110  RegisterTerrainOverlays()                free
//   0x00f962b0  cTerrainOverlay::~cTerrainOverlay()      ret 4
//   0x00f96310  cTerrainOverlay::Start()                 void
//   0x00f96370  ToggleFlag(idx)                          free
//   0x00f96390  HashTerrainDesc(desc, out)               free
//   0x00f964a0  Clear0964a0()                            void
//   0x00f964b0  ReleaseRef()                              void
//   0x00f964f0  DynamicCast(unsigned)                     ret 4
//   0x00f96520  cTerrainSphere::RemoveFromEffectsSystem() void
//   0x00f967d0  GetGridExtents(int*,int*,int*)            ret 0xc

#include "types.h"

long InterlockedExchangeAdd(long volatile* dest, long incr);

namespace SP {

// ===================== float helpers =====================
float fabs_f(float);

// ===================== external callees =====================
void  Sub_f95540(void* self);                 // 0x00f95540
void  Sub_f94fa0(void* self);                 // 0x00f94fa0
int   Sub_6237a0(void* self);                 // 0x006237a0
void  Sub_a7f430(void* self, void* a);        // 0x00a7f430
void  Sub_936090(void* self, int a);          // 0x00936090
void* Sub_a70ec0(void* a, void* b, int c);    // 0x00a70ec0
void  Sub_b5f950(void* self, void* a);        // 0x00b5f950
int*  Sub_f48a70();                           // 0x00f48a70
void  Sub_f67540(void* self, float v);        // 0x00f67540
int*  Sub_f48aa0(void* self);                 // 0x00f48aa0
int*  Sub_67dd50();                           // 0x0067dd50
int*  Sub_67dd70();                           // 0x0067dd70
int*  Sub_67dda0();                           // 0x0067dda0
int*  Sub_67ddd0();                           // 0x0067ddd0
int   Sub_6f24a0(void* a, int b);             // 0x006f24a0
int*  Sub_6bb5f0();                           // 0x006bb5f0
void  Sub_571db0(void*, void*, void*, void*, void*); // 0x00571db0
void  Sub_f47380(void* p);                    // 0x00f47380
void* Sub_f473a0(int sz, void* a, void*, void*, void*, void*); // 0x00f473a0
unsigned Sub_932e50(void* data, int len, unsigned seed); // 0x00932e50
int   Sub_97ef00(void* self);                 // 0x0097ef00
int   Sub_fb7bb0(void* self);                 // 0x00fb7bb0
int   Sub_fb7bc0(void* self);                 // 0x00fb7bc0

// ===================== global data =====================
extern int   g_16c9dd4;      // 0x016c9dd4  terrain toggle bytes
extern int   g_16f71ac;      // 0x016f71ac
extern int   g_16f71b8;      // 0x016f71b8
extern int   g_16f71bc;      // 0x016f71bc
extern int   g_16f71c0;      // 0x016f71c0
extern int   g_16f6e74;      // 0x016f6e74
extern int   g_16f6e7c;      // 0x016f6e7c
extern int   g_16f6e9c;      // 0x016f6e9c
extern int   g_16f6ed8;      // 0x016f6ed8
extern int   g_16f6edc;      // 0x016f6edc
extern int   g_16f6ee8;      // 0x016f6ee8
extern int   g_16f6eec;      // 0x016f6eec
extern int*  g_16f89d0;      // 0x016f89d0
extern int   g_16f85ac;      // 0x016f85ac
extern int   g_16f6e40;      // 0x016f6e40
extern char  g_15fd918;      // 0x015fd918
extern int   g_16c9f50;      // 0x016c9f50
extern int   g_16f6e40;      // 0x016f6e40
extern int*  g_15b117c;      // 0x015b117c

// ===================== float constants =====================
extern const float K_0f;     // 0x013eecd4   0.0f
extern const float K_n1_4;   // 0x013f4fd0  -1.0f (hi bit source)
extern const float K_1div3;  // 0x013ec4d0   (1/255 scaled)
extern const float K_1f;     // 0x01485720   1.0f
extern const float K_half;   // 0x01471064   0.5f
extern const float K_2f;     // 0x01470f1c   2.0f
extern const float K_140;    // 0x0140f334

}  // namespace SP

using namespace SP;

// ============================ class models ============================

// ---- the terrain overlay object (0x9c bytes; ctor at 0x00f95cf0) ----
class cTerrainOverlayBase;
typedef void* (*OverlayFn)();

class cTerrainOverlay {
public:
    cTerrainOverlay();
    void* dtor(unsigned flags);   // 0x00f962b0
    char  Reset();
    char  Start();
    char  ClearSlot();            // 0x00f964a0
    void  ToggleFlag();           // 0x00f96370

    void* mpVtbl;        // +0x00
    char  mFlag04;       // +0x04
    char  mFlag05;       // +0x05
    uint8_t mPad06[2];   // +0x06
    int   mVal08;        // +0x08
    uint8_t mPad0c[0x88 - 0x0c]; // +0x0c
    void* mpAlloc88;     // +0x88
    int   mVal8c;        // +0x8c
    int   mVal90;        // +0x90
    int   mVal94;        // +0x94
    int   mVal98;        // +0x98
    uint8_t mPad9c[0x36c - 0x9c]; // +0x9c
    int   mVal36c;       // +0x36c
};

// ---- opaque terrain sphere (offset reads only) ----
struct cTerrainSphere {
    void RemoveFromEffectsSystem();   // 0x00f96520
};

// ---- the dynamically-castable object (this at ecx, id on the stack) ----
struct cDynCast {
    void* Cast(unsigned id);          // 0x00f964f0
};

// ---- the grid tool (this at ecx, three out-pointers) ----
struct cGridTool {
    void* GetExtents(int* a, int* b, int* c);  // 0x00f967d0
};

// ============================ static overlay registrations ============================
// Each entry is a 0x40-byte record: {short id; dword val; byte f1; byte f2; func ptr}
// We model the registration table as raw memory accessors.

struct OverlayReg {
    uint16_t mId;      // +0x00
    uint8_t  mPad02[0x0c];  // +0x02
    uint16_t mId2;     // +0x0e ? (used as word at +0x0e in some)
    uint8_t  mPad10[0x14];  // +0x10
    int      mVal24;   // +0x24
    char     mFlag28;  // +0x28
    char     mFlag29;  // +0x29
    uint8_t  mPad2a[0x3a];
    void*    mpFn3c;   // +0x3c
};

// ============================ bodies ============================

// @ 0x00f955f0
int cTerrainScriptEffect_ApplyEffect(void* self, void* a, float dt, void* c)
{
    (void)a; (void)c;
    char* s = (char*)self;
    if (s[0x18] == 0) {
        Sub_f95540(self);
        return 0;
    }
    int* bf = *(int**)(s + 0xbc);
    if (bf == 0)
        return 0;
    if (*(int*)(s + 0xc8) == 0)
        return 0;

    int ecx = bf[0x30 / 4];
    int v;
    if (ecx)
        v = Sub_6237a0((void*)(size_t)ecx);
    else
        v = 0;
    if (bf[0x34 / 4] + v != *(int*)(s + 0xc0))
        Sub_f94fa0(self);

    int* edi = (int*)(s + 0xa4);
    int cl;
    if (*edi) {
        void** vt = *(void***)*edi;
        char r = ((char(__thiscall*)(void*))vt[4])((void*)*edi);
        cl = r ? 0 : 1;
    } else {
        cl = 1;
    }

    float x18 = *(float*)(s + 0x24);
    float x1c = *(float*)(s + 0x1c);
    if (!(x18 == 0.0f && x1c < x18)) {
        if (!cl)
            goto after;
    }
    if (x1c > 0.0f) {
        int cnt = ++*(int*)(s + 0x20);
        if (cnt >= *(int*)(s + 0xc4))
            goto tailb;
        {
            int* p = (int*)*edi;
            if (p && ((char(__thiscall*)(void*))(*(void***)p)[4])(p)) {
                int* ee = *(int**)(s + 0xc);
                if ((ee[2] >> 3) & 1) {
                    /* skip */
                } else {
                    int* q = (int*)*edi;
                    void** vt = (void**)*q;
                    ((void(__thiscall*)(void*, int))vt[3])(q, *(int*)(s + 0xa0));
                    if (*(int*)(s + 0xa0) == 0) {
                        Sub_a7f430((char*)s + 0xa8, edi);
                        Sub_f95540(self);
                    }
                }
            } else {
                Sub_a7f430((char*)s + 0xa8, edi);
                Sub_f95540(self);
            }
        }
        {
            int* p = (int*)*edi;
            if (p) {
                *edi = 0;
                void** vt = (void**)*p;
                ((void(__thiscall*)(void*))vt[1])(p);
            }
        }
        {
            int* tbl = *(int**)(s + 0xd4);
            if (tbl) {
                int idx = *(int*)(s + 0x20);
                Sub_936090((void*)0x16778dc, tbl[idx]);
            }
        }
        {
            int base = *(int*)(s + 0x14);
            int* arr = *(int**)(s + 0xc8);
            int idx = *(int*)(s + 0x20);
            int v2 = arr[idx * 3];
            int off = *(int*)(s + 0x10);
            int a = (int)Sub_a70ec0((void*)(size_t)v2, (void*)(size_t)off, 0);
            Sub_b5f950(edi, (void*)(size_t)a);
            (void)base;
        }
        {
            int* p = (int*)*edi;
            if (p) {
                int* mb = *(int**)(s + 0xcc);
                if (mb) {
                    int eax = *(int*)(s + 0x20);
                    void** vt = (void**)*p;
                    int ebp = eax * 8 - eax;
                    ((void(__thiscall*)(void*, void*))vt[6])(p, (char*)mb + ebp * 8);
                } else {
                    void** vt = (void**)*p;
                    ((void(__thiscall*)(void*, void*))vt[6])(p, s + 0x2c);
                    int* q = (int*)*edi;
                    void** qvt = (void**)*q;
                    ((void(__thiscall*)(void*, void*))qvt[5])(q, s + 0x64);
                }
                {
                    int* arr = *(int**)(s + 0xd8);
                    if (arr) {
                        int idx = *(int*)(s + 0x20);
                        int* q = (int*)*edi;
                        void** vt = (void**)*q;
                        ((void(__thiscall*)(void*, int, void*, int))vt[0x44/4])(q, 4, (char*)arr + idx * 4, 1);
                    }
                }
                {
                    int* arr = *(int**)(s + 0xdc);
                    if (arr) {
                        int idx = *(int*)(s + 0x20);
                        int* q = (int*)*edi;
                        void** vt = (void**)*q;
                        int* base = Sub_f48a70();
                        float fv = *(float*)((char*)arr + idx * 4);
                        Sub_f67540(base, fv);
                    }
                }
                {
                    int* q = (int*)*edi;
                    void** vt = (void**)*q;
                    ((void(__thiscall*)(void*, int))vt[2])(q, *(int*)(s + 0x9c));
                }
                {
                    int* q = (int*)*edi;
                    void** vt = (void**)*q;
                    ((void(__thiscall*)(void*, int))vt[0x30/4])(q, s[0x28] ? 0 : 1);
                }
            }
        }
        {
            int* arr = *(int**)(s + 0xd0);
            if (arr) {
                int idx = *(int*)(s + 0x20);
                float f = *(float*)((char*)arr + idx * 4);
                if (!(f == 0.0f))
                    *(float*)(s + 0x24) = f + x1c;
                else
                    *(float*)(s + 0x24) = 0.0f;
            } else {
                *(float*)(s + 0x24) = 0.0f;
            }
        }
        *(float*)(s + 0x1c) = x1c + dt;
        return 0;
    }
    {
        int cnt = *(int*)(s + 0x20);
        if (cnt < *(int*)(s + 0xc4))
            goto resume;
    }
tailb:
    {
        void** vt = (void**)*(int*)s;
        ((void(__thiscall*)(void*, int))vt[3])(s, *(int*)(s + 0xa0));
        return 0;
    }
resume:
    goto doResume;
doResume:
    return 0;
after:
    *(float*)(s + 0x1c) = x1c + dt;
    return 0;
}

// @ 0x00f959f0
void __stdcall SetTerrainToggle(int v)
{
    *(char*)&g_16c9dd4 = (char)v;
}

// @ 0x00f95ac0
void UnpackColor(unsigned c, float* out)
{
    int r = (int)(c & 0xff);
    int g = (int)((c >> 8) & 0xff);
    int b = (int)((c >> 0x10) & 0xff);
    unsigned a = c >> 0x18;
    float fr = (float)r;
    float fg = (float)g;
    float fb = (float)b;
    float fa = (float)a;
    float s = K_1div3;
    out[0] = fr * s;
    out[1] = fg * s;
    out[2] = fb * s;
    out[3] = fa * s;
}

// @ 0x00f95b70
void DrawTerrainOverlay(int a)
{
    int esi = g_16f6e7c;
    if (!esi)
        return;
    float quad[4];
    if (*(char*)&g_16c9dd4) {
        void* obj = ((void*(__thiscall*)(void*, unsigned))((void**)*(int*)&g_15fd918)[0x28/4])((void*)&g_15fd918, 0xb8eccb3e);
        quad[0] = ((float*)obj)[0];
        quad[1] = ((float*)obj)[1];
        quad[2] = ((float*)obj)[2];
        quad[3] = ((float*)obj)[3];
    } else {
        quad[0] = 1.0f;
        quad[1] = 1.0f;
        quad[2] = 1.0f;
        quad[3] = 1.0f;
        {
            int* p = Sub_f48aa0(0);
            if (p) {
                ((void(__thiscall*)(void*))((void**)*p)[4])(p);
                int* q = Sub_f48aa0(0);
                void* r = ((void*(__thiscall*)(void*))((void**)*q)[4])(q);
                quad[0] = *(float*)((char*)r + 0x59c);
                quad[1] = *(float*)((char*)r + 0x5a0);
                quad[2] = *(float*)((char*)r + 0x5a4);
            }
        }
    }
    float s = K_2f;
    quad[2] *= s;
    quad[1] *= s;
    quad[0] *= s;
    quad[3] = *(float*)esi;

    int eax2 = (int)g_16f89d0;
    void** vt = (void**)*(int*)eax2;
    if (a == 0) {
        ((void(__thiscall*)(void*, void*, void*, void*, int))vt[0x1b4/4])((void*)eax2, (void*)eax2, quad, (void*)a, 1);
    } else {
        ((void(__thiscall*)(void*, void*, void*, int, void*))vt[0x178/4])((void*)eax2, quad, (void*)a, 1, (void*)a);
    }
}

// @ 0x00f95cf0
cTerrainOverlay::cTerrainOverlay()
{
    *(int*)this = 0x14903a0;
    mFlag04 = 0;
    mFlag05 = 0;
    mVal08 = 0;
    *(int*)((char*)this + 0x88) = 0;
    *(int*)((char*)this + 0x8c) = 0;
    *(int*)((char*)this + 0x90) = 0;
    *(int*)((char*)this + 0x94) = 0;
    *(int*)((char*)this + 0x98) = 0;
    for (int i = 0x0c; i <= 0x84; i += 4)
        *(int*)((char*)this + i) = 0;
}

// @ 0x00f95d90
char cTerrainOverlay::Reset()
{
    *(char*)&g_16c9dd4 = 0;
    mFlag04 = 0;
    return 1;
}

// @ 0x00f95dd0
void DrawTerrainGrid(int a)
{
    int ebx = g_16f6e74;
    if (!ebx)
        return;
    float quad[4];
    if (*(char*)&g_16c9dd4) {
        void* obj = ((void*(__thiscall*)(void*, unsigned))((void**)*(int*)&g_15fd918)[0x28/4])((void*)&g_15fd918, 0xc4a4780);
        quad[0] = ((float*)obj)[0];
        quad[1] = ((float*)obj)[1];
        quad[2] = ((float*)obj)[2];
        quad[3] = ((float*)obj)[3];
    } else {
        quad[0] = 1.0f;
        quad[1] = 1.0f;
        quad[2] = 1.0f;
        quad[3] = 1.0f;
        {
            int* p = Sub_f48aa0(0);
            if (p) {
                float v0, v1, v2;
                if (g_16f6e40) {
                    v0 = *(float*)(g_16f6e40 + 0);
                    v1 = *(float*)(g_16f6e40 + 4);
                    v2 = *(float*)(g_16f6e40 + 8);
                } else {
                    v0 = *(float*)(g_16f85ac + 0x30);
                    v1 = *(float*)(g_16f85ac + 0x34);
                    v2 = *(float*)(g_16f85ac + 0x38);
                }
                void* r = ((void*(__thiscall*)(void*))((void**)*p)[3])(p);
                int edi = *(int*)((char*)r + 0x14);
                v0 = fabs_f(v0);
                int gridW = *(int*)(edi + 8);
                float fw = (float)gridW * K_half;
                v1 = fabs_f(v1);
                v2 = fabs_f(v2);
                if (!(v2 >= fw) && !(v1 >= v2)) {
                    /* lexical < case */
                    int ix = (int)(v2 / v0 + 1.0f) * fw;
                    (void)ix;
                }
            }
        }
    }
    float s = K_2f;
    quad[2] *= s;
    quad[1] *= s;
    quad[0] *= s;
    quad[3] = *(float*)ebx;
    (void)a;
}

// @ 0x00f96110
void RegisterTerrainOverlays()
{
    *(uint16_t*)(0x016fec88) = 0x235;
    *(uint16_t*)(0x016fef68) = 0x24c;
    *(uint16_t*)(0x016fed88) = 0x23d;
    *(uint16_t*)(0x016fef88) = 0x24d;
    *(uint16_t*)(0x016fefe8) = 0x250;
    *(uint16_t*)(0x016ff008) = 0x251;
    *(uint16_t*)(0x016fec48) = 0x233;
    *(uint16_t*)(0x01700608) = 0x301;
    *(uint16_t*)(0x01700668) = 0x304;
    *(uint16_t*)(0x016fec4c) = 0;
    *(char*)(0x016fec50) = 0;
    *(char*)(0x016fec51) = 0;
    *(int*)(0x016fec64) = 0xf95dd0;
    *(int*)(0x016fec8c) = 0;
    *(char*)(0x016fec90) = 0;
    *(char*)(0x016fec91) = 0;
    *(int*)(0x016feca4) = 0xf95b70;
    *(int*)(0x016fef6c) = 0;
    *(char*)(0x016fef70) = 0;
    *(char*)(0x016fef71) = 0;
    *(int*)(0x016fef84) = 0xf958b0;
    *(int*)(0x016fed8c) = 0;
    *(char*)(0x016fed90) = 0;
    *(char*)(0x016fed91) = 0;
    *(int*)(0x016feda4) = 0xf958f0;
    *(int*)(0x016fef8c) = 0;
    *(char*)(0x016fef90) = 0;
    *(char*)(0x016fef91) = 0;
    *(int*)(0x016fefa4) = 0xf95930;
    *(int*)(0x016fefec) = 0;
    *(char*)(0x016feff0) = 0;
    *(char*)(0x016feff1) = 0;
    *(int*)(0x016ff004) = 0xf95970;
    *(int*)(0x016ff00c) = 0;
    *(char*)(0x016ff010) = 0;
    *(char*)(0x016ff011) = 0;
    *(int*)(0x016ff024) = 0xf959b0;
    *(int*)(0x0170060c) = 0;
    *(char*)(0x01700610) = 0;
    *(char*)(0x01700611) = 0;
    *(int*)(0x01700624) = 0xf95a00;
    *(int*)(0x0170066c) = 0;
    *(char*)(0x01700670) = 0;
    *(char*)(0x01700671) = 0;
    *(int*)(0x01700684) = 0xf95a40;
    *(uint16_t*)(0x01700688) = 0x305;
    *(int*)(0x0170068c) = 0;
    *(char*)(0x01700690) = 0;
    *(char*)(0x01700691) = 0;
    *(int*)(0x017006a4) = 0xf95870;
    *(uint16_t*)(0x017006a8) = 0x306;
    *(int*)(0x017006ac) = 0;
    *(char*)(0x017006b0) = 0;
    *(char*)(0x017006b1) = 0;
    *(int*)(0x017006c4) = 0xf95a80;
}

// @ 0x00f962b0
void* cTerrainOverlay::dtor(unsigned flags)
{
    *(int*)this = 0x14903a0;
    if (mpAlloc88) {
        Sub_571db0(mpAlloc88, (void*)mVal8c, (void*)mVal90, (void*)mVal94, (void*)mVal98);
        mpAlloc88 = 0;
    }
    if (flags & 1)
        Sub_f47380(this);
    return this;
}

// @ 0x00f96310
char cTerrainOverlay::Start()
{
    *(char*)&g_16c9dd4 = 0;
    if (mFlag04)
        return 1;
    RegisterTerrainOverlays();
    mFlag05 = 0;
    mVal08 = 0;
    {
        int* mgr = Sub_67dd70();
        void** vt = (void**)*mgr;
        ((void(__thiscall*)(void*, int, const char*, void*))vt[0x2c/4])(mgr, 0x14, (const char*)0x15b1070, (char*)this + 0x0c);
        ((void(__thiscall*)(void*, int, const char*, void*))vt[0x2c/4])(mgr, 0x0b, (const char*)0x15b10c0, (char*)this + 0x5c);
    }
    mFlag04 = 1;
    return 1;
}

// @ 0x00f96370
void cTerrainOverlay::ToggleFlag()
{
    int idx = mVal36c;
    *((char*)this + idx + 0x368) = 0;
    mVal36c = 1 - mVal36c;
}

// @ 0x00f96390
unsigned HashTerrainDesc(void* desc, void* out)
{
    char* d = (char*)desc;
    int v4, v8, v12;
    if ((d[0] >> 2) & 1) {
        v4 = (int)*(float*)(d + 4);
        v8 = (int)*(float*)(d + 8);
        v12 = (int)*(float*)(d + 0xc);
    } else {
        v4 = v8 = v12 = 0;
    }
    int v16;
    if (*(float*)(d + 0x10) < 1.0f)
        v16 = (int)(*(float*)(d + 0x10) * K_1div3);
    else
        v16 = 0;

    int arr[9];
    if ((d[0] >> 1) & 1) {
        for (int i = 0; i < 9; ++i)
            arr[i] = (int)(*(float*)(d + 0x14 + i * 4) * K_1div3);
    } else {
        for (int i = 0; i < 9; ++i)
            arr[i] = 0;
    }
    (void)v16;

    unsigned h = Sub_932e50(&v4, 0x34, 0x811c9dc5);
    return Sub_932e50(out, 0x0c, h);
}

// @ 0x00f964a0
char cTerrainOverlay::ClearSlot()
{
    mVal08 = 0;
    return 1;
}
// @ 0x00f964b0
int ReleaseRef(int* self)
{
    int* p = (int*)((char*)self + 4);
    int old;
    old = InterlockedExchangeAdd((long volatile*)p, -1);
    if (old - 1 == 0) {
        *(int*)((char*)self + 4) = 1;
        Sub_f47380(self);
    }
    return old;
}

// @ 0x00f964f0
void* cDynCast::Cast(unsigned id)
{
    if (id == 0x479dcb2)
        return (char*)this - 0x10;
    if (id != 0x2269ed1 && id != 0xee3f516e)
        return 0;
    if (!this)
        return 0;
    return this;
}

// @ 0x00f96520
void cTerrainSphere::RemoveFromEffectsSystem()
{
    int* mgr = Sub_67ddd0();
    Sub_6f24a0((void*)g_16c9f50, 0);
    void** vt = (void**)*mgr;
    typedef void (__thiscall *Fn78)(void*, int, int, unsigned);
    typedef void (__thiscall *Fn88)(void*, int, int, unsigned);
    typedef void (__thiscall *Fn20)(void*, int, int);
    Fn78 f78 = (Fn78)vt[0x78/4];
    Fn88 f88 = (Fn88)vt[0x88/4];
    Fn20 f20 = (Fn20)vt[0x20/4];

    f78(mgr, 0, 0, 0x2e892928);
    f78(mgr, 0, 0, 0x2e892929);
    f78(mgr, 0, 0, 0x2e89292a);
    f78(mgr, 0, 0, 0x2e89292b);
    f78(mgr, 0, 0, 0x03598109);

    f88(mgr, 0, 0, 0x00f86c22);
    f88(mgr, 0, 0, 0x00f86c06);
    f88(mgr, 0, 0, 0x00f86c19);
    f88(mgr, 0, 0, 0x016f280b);
    f88(mgr, 0, 0, 0x01acdb9c);
    f88(mgr, 0, 0, 0x01acdb88);
    f88(mgr, 0, 0, 0x01acdb92);
    f88(mgr, 0, 0, 0x01acdba5);
    f88(mgr, 0, 0, 0x01c8a626);
    f88(mgr, 0, 0, 0x01c8a610);
    f88(mgr, 0, 0, 0x01c8a61e);
    f88(mgr, 0, 0, 0x01c8a62f);
    f88(mgr, 0, 0, 0x0276b1e8);
    f88(mgr, 0, 0, 0x02c9c762);
    f88(mgr, 0, 0, 0x02c9c763);
    f88(mgr, 0, 0, 0x02c9c764);
    f88(mgr, 0, 0, 0x02c9c765);
    f88(mgr, 0, 0, 0x02c9c766);
    f88(mgr, 0, 0, 0x02c9c767);
    f88(mgr, 0, 0, 0x02e831a1);
    f88(mgr, 0, 0, 0x02e831af);
    f88(mgr, 0, 0, 0x02f7dcd2);

    f20(mgr, 0, -1);
    f20(mgr, 0, 7);
    f20(mgr, 0, 8);
}

// @ 0x00f967d0
void* cGridTool::GetExtents(int* a, int* b, int* c)
{
    char* s = (char*)this;
    float f = (float)Sub_97ef00(*(void**)(s + 0x20c)) * K_140;
    int iv = (int)f;
    int adj = iv;
    if (f < (float)iv)
        adj = iv - 1;
    *a = adj;
    *b = Sub_fb7bb0(*(void**)(s + 0x20c));
    *c = Sub_fb7bc0(*(void**)(s + 0x20c));
    return 0;
}
