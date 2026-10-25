// Slice s00f3b0c0: a simulator-side UI/catalog helper class and its accessors.
// Optimized module: /O2 /MD /Gy /EHsc /TP (x87 for float args/returns, SSE copies).
//
// `this` layout recovered from the accessors below:
//   +0x10  Inner*   mpInner
//   +0x3c  char     f3c
//   +0x7c  int      f7c
//   +0x80  uint32   f80
//   +0x84  char     f84
//   +0x85  char     f85
//   +0x8c  void*    f8c
//   +0xe8  Vector3  vE8
//   +0xf4  Vector3  vF4[N]
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
#include <math.h>

struct Vector3 { float x, y, z; };

struct IRefObj {
    virtual void v00();
    virtual void v04();
};
struct IObjAC {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0C();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1C();
    virtual void a20(); virtual void a24(); virtual void a28(); virtual void a2C();
    virtual void a30(); virtual void a34(); virtual void a38(); virtual void a3C();
    virtual void a40(); virtual void a44(); virtual void a48(); virtual void a4C();
    virtual void a50(); virtual void a54(); virtual void a58(); virtual void a5C();
    virtual void a60(); virtual void a64(); virtual void a68(); virtual void a6C();
    virtual void a70(); virtual void a74(); virtual void a78(); virtual void a7C();
    virtual void a80(); virtual void a84(); virtual void a88(); virtual void a8C();
    virtual void a90(); virtual void a94(); virtual void a98(); virtual void a9C();
    virtual void aA0(); virtual void aA4(); virtual void aA8(); virtual int aAC();
};

struct cInner {
    char pad0[0x68];
    int  f68[0x44];   // +0x68 (indexed)
    void* p178;       // +0x178
    void* p17c;       // +0x17c
    char pad1[0x238 - 0x180];
    void* p238;       // +0x238
    void* p23c;       // +0x23c
    void* p240;       // +0x240
};

struct cSim {
    virtual void* v00();
    virtual void  v04();
    virtual void  v08();
    virtual void* v0C(int id);      // vtable slot +0x0C
    char padVt1[4];    // +0x04
    char padVt2[4];    // +0x08
    void* mWindowMgr;  // +0x0c
    cInner* mpInner;   // +0x10
    char pad1[0x3c - 0x14];
    char f3c;          // +0x3c
    char pad2[0x7c - 0x3d];
    int  f7c;          // +0x7c
    uint32_t f80;      // +0x80
    char f84;          // +0x84
    char f85;          // +0x85
    char pad3[0x8c - 0x86];
    void* f8c;         // +0x8c
    char pad4[0xe8 - 0x90];
    Vector3 vE8;       // +0xe8
    Vector3 vF4[5];    // +0xf4

    void  FUN_00f3b0c0();
    void  m00f3a4e0(int id, int value);
    void  m00f3a540(int arg);
    void  m00f3aa30();
    void  FUN_00f3b290(char p);
    void  FUN_00f3b7c0(int p);
    int   FUN_00f3b920();
    int   FUN_00f3b420();
    bool  FUN_00f3b950();
    void  FUN_00f3b990();
    int   FUN_00f3b5e0(float x);
    void  FUN_00f3bd90(int idx, char val);
    bool  FUN_00f3bde0(int idx);
    int   FUN_00f3be30();
    int   FUN_00f3be60(int idx);
    int   FUN_00f3bec0(int idx);
    int   FUN_00f3bf00(int a, int b);
    int   FUN_00f3bf70();
    int   FUN_00f3bfa0(int idx);
    int*  FUN_00f3bfc0(int a, int* b, char c, int d);
    void  FUN_00f3bce0(int idx, int* v);
    void  FUN_00f3bcc0(int v);
    void  FUN_00f3bc20(int param);
    char  f253f0();
};

// ---------------------------------------------------------------------------
// Externals / globals.
// ---------------------------------------------------------------------------
struct cChecklist { void ToggleHint(int, int); };
struct cManager14 { void FUN_00ed4e80(); };
struct cGlobalUI {
    char pad0[0x14];
    cManager14* f14;            // +0x14
    void* f18;                  // +0x18  game state (cGameState*)
    char pad1[0xcc - 0x1c];
    int  fcc;                   // +0xcc
    char pad2[0xd4 - 0xd0];
    cChecklist* mpChecklist;    // +0xd4
};
extern cGlobalUI* g_pGlobalUI;                  // 0x016c7aa4
extern uint32_t g_016065f0;                     // 0x016065f0

// Object at g_pGlobalUI->f18: the per-frame game/UI state the HUD reads.
struct cGameState {
    char  pad0[0xcc];
    float fcc;                  // +0xcc
    float fd0;                  // +0xd0
    char  pad1[0xdc - 0xd4];
    float fdc;                  // +0xdc
    char  pad2[0x18d - 0xe0];
    unsigned char f18d;         // +0x18d
    float f31e60();             // 0x00f31e60
};

#define VTOF(p) (*(void***)(p))
typedef void* (__thiscall *PF_FindWindow)(void*, int, int);
typedef void* (__thiscall *PF_GetChild)(void*, unsigned);
typedef void  (__thiscall *PF_SetTwo)(void*, int, int);
typedef void  (__thiscall *PF_Void1f)(void*, float);
typedef void  (__thiscall *PF_Void2pi)(void*, void*, int);
typedef void  (__thiscall *PF_Void1p)(void*, void*);
typedef void* (__thiscall *PF_Get0)(void*);
typedef int   (__thiscall *PF_Int0)(void*);
typedef void* (__thiscall *PF_Get1u)(void*, unsigned);
typedef void* (__thiscall *PF_Get2ii)(void*, int, int);

int FUN_00f3a160(float v);
void FUN_00f3b710(int* v);
void FUN_00f21850(cSim* self, float* a, float* b, float* c, float* d, float* e);
void FUN_00eed0b0(cSim* self, float* a, float* b);
float FUN_00eed280(cSim* self, int zero);
int FUN_00552300(int);
char SP_EditorUtils_GetCreatorType(int);
int FUN_00d539d0();
void*         FUN_00b3d300(int a, int b);
void FUN_00b225d0();
int  FUN_00b18e00(int);

struct CPlanet {
    int f4df550();                                      // 0x004df550
};
struct CPlanetModel {
    void  f81780(float* pos, float x, float a, float b); // 0x00b81780
    float f7e500();                                      // 0x00b7e500
};
struct CNounManager {
    int f989360();                                      // 0x00989360
};
struct CPosse {
    void AddMember(int noun);                           // 0x00d54330
    void f53b50(int noun, float* v);                    // 0x00d53b50
};
struct CPlacement {
    int   unk0;         // +0x00
    float x;            // +0x04
    float y;            // +0x08
    float z;            // +0x0c
    char  pad0[0x209 - 0x10];
    unsigned char f209; // +0x209
    char  pad1[0x220 - 0x20a];
    float f220;         // +0x220
};
CPlanet*      FUN_00401090(void* self);
CPlanetModel* FUN_00b3d350();
void*         FUN_00b3d300(int a, int b);
int           FUN_00c099e0(float* out, int thing, int one, int u);
double        FUN_00f3b590(float a, float b);
void          FUN_00eed720(CPlacement* p, int a1, int* cfg);
float*        FUN_00eec2b0(void* out, float* pos, unsigned flag, void* one, int a2);
void          FUN_00eec8e0(CPlacement* p, char* a, char* b);
extern unsigned char g_15acb40;                       // 0x015acb40

// ---------------------------------------------------------------------------
// @ 0x00f3b290
// ---------------------------------------------------------------------------
void cSim::FUN_00f3b290(char p) {
    if (p != 0) {
        f3c = 0;
        FUN_00f3b0c0();
        g_pGlobalUI->mpChecklist->ToggleHint(0x9f, 0xa0);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3b2c0  (symbol $E366)
// ---------------------------------------------------------------------------
int __stdcall _E366(int x) {
    switch (x) {
    case 2:
    case 3:
        return 0xb1d38c08;
    case 4:
        return 0xfa14571d;
    }
    return 0;
}

// @ 0x00f3b2f0
bool FUN_00f3b2f0(int x) {
    if (x == 1 || x == 2 || x == 6 || x == 7 || x == 10) return true;
    return false;
}

// @ 0x00f3b320
int FUN_00f3b320(int x) {
    if (x == 9 || x == 6 || x == 10) return 1;
    return 0;
}

// @ 0x00f3b340
int FUN_00f3b340(int x) {
    if (x == 9 || x == 6 || x == 10 || x == 2 || x == 8) return 0;
    return 1;
}

// @ 0x00f3b370
int FUN_00f3b370(int x) {
    if (x == 4 || x == 5 || x == 0xb) return 0;
    return 1;
}

// @ 0x00f3b390
int FUN_00f3b390(int x) {
    if (x == 6 || x == 8 || x == 5) return 1;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f3b3b0
// ---------------------------------------------------------------------------
bool __stdcall FUN_00f3b3b0(int* a, int* b) {
    int type = *a;
    bool r = false;
    if (type == *b) {
        if (a[1] == b[1]) {
            r = true;
            if (type == 9 || type == 6 || type == 10) {
                if (a[2] != b[2] || a[2] == -1) r = false;
            }
        } else if (type == 9 || type == 6 || type == 10) {
            if (a[1] == b[2] && a[2] == b[1]) r = true;
        }
    }
    return r;
}

// ---------------------------------------------------------------------------
// @ 0x00f3b7c0
// ---------------------------------------------------------------------------
void cSim::FUN_00f3b7c0(int p) {
    if (p == 0x24720859) p = 0x20790816;
    if (f7c != p) {
        f7c = p;
        f84 = 1;
    }
    cManager14* m = g_pGlobalUI->f14;
    if (m != 0) {
        m->FUN_00ed4e80();
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3b920
// ---------------------------------------------------------------------------
int cSim::FUN_00f3b920() {
    if (g_016065f0 <= f80 && f84 == 0 && f85 == 0) return 0;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00f3b420
// ---------------------------------------------------------------------------
int cSim::FUN_00f3b420() {
    if (g_016065f0 <= f80 && f84 == 0) return 0;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00f3b950
// ---------------------------------------------------------------------------
bool cSim::FUN_00f3b950() {
    int iVar1 = (int)mpInner;
    if (iVar1 != 0 && *(int*)(iVar1 + 8) != 0) {
        if (FUN_00552300(iVar1 + 8) == 1) {
            if (!SP_EditorUtils_GetCreatorType(iVar1 + 8)) return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00f3b990
// ---------------------------------------------------------------------------
void cSim::FUN_00f3b990() {
    if (this == 0) return;
    int iVar2 = (int)v0C(0x175cdc9);
    if (iVar2 == 0) return;
    int* pi = *(int**)(iVar2 + 0x54);
    if (pi == 0) return;
    FUN_00b3d300(0, 0);
    FUN_00b225d0();
    pi = *(int**)(iVar2 + 0x54);
    if (pi != 0) {
        *(int*)(iVar2 + 0x54) = 0;
        ((IRefObj*)pi)->v04();
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3bbd0
// ---------------------------------------------------------------------------
void __stdcall FUN_00f3bbd0(int param, char flag) {
    if (param == 0) return;
    int* pi = (int*)FUN_00b18e00(param);
    *(char*)((char*)pi + 0x6e) = (flag == 0);
    int iVar2 = ((IObjAC*)pi)->aAC();
    if (iVar2 != 0) {
        if (flag == 0) {
            *(uint32_t*)(iVar2 + 4) |= 8;
            *(char*)(iVar2 + 0x5c) = 1;
            return;
        }
        *(uint32_t*)(iVar2 + 4) &= 0xfffffff7;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3bcc0
// ---------------------------------------------------------------------------
void cSim::FUN_00f3bcc0(int v) {
    cInner* inner = mpInner;
    *(int*)((char*)inner + 0x238) = v;
    int r = FUN_00d539d0();
    *(int*)(r + 0x18) = v;
}

// ---------------------------------------------------------------------------
// @ 0x00f3bd90
// ---------------------------------------------------------------------------
void cSim::FUN_00f3bd90(int idx, char val) {
    cInner* inner = mpInner;
    int count = (int)(((int)inner->p17c - (int)inner->p178) / 0x38);
    if (idx >= 0 && idx < count) {
        *(char*)((char*)inner->p178 + 0x20 + idx * 0x38) = val;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3bde0
// ---------------------------------------------------------------------------
bool cSim::FUN_00f3bde0(int idx) {
    cInner* inner = mpInner;
    int count = (int)(((int)inner->p17c - (int)inner->p178) / 0x38);
    if (idx >= 0 && idx < count) {
        return *(bool*)((char*)inner->p178 + 0x20 + idx * 0x38);
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00f3be30
// ---------------------------------------------------------------------------
int cSim::FUN_00f3be30() {
    cInner* inner = mpInner;
    int* p = (int*)((char*)inner + 0x23c);
    return (p[1] - p[0]) / 0x534;
}

// ---------------------------------------------------------------------------
// @ 0x00f3be60
// ---------------------------------------------------------------------------
int cSim::FUN_00f3be60(int idx) {
    if (idx < 0) return 0;
    cInner* inner = mpInner;
    if (idx < ((int)inner->p240 - (int)inner->p23c) / 0x534) {
        return idx * 0x534 + (int)inner->p23c;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f3bec0
// ---------------------------------------------------------------------------
int cSim::FUN_00f3bec0(int idx) {
    int iVar1 = FUN_00f3be60(idx);
    if (iVar1 != 0) {
        return (*(int*)(iVar1 + 0x88) - *(int*)(iVar1 + 0x84)) / 0x188;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f3bf00
// ---------------------------------------------------------------------------
int cSim::FUN_00f3bf00(int a, int b) {
    int iVar1 = FUN_00f3be60(a);
    if (iVar1 != 0 && b >= 0 &&
        b < (*(int*)(iVar1 + 0x88) - *(int*)(iVar1 + 0x84)) / 0x188) {
        return b * 0x188 + *(int*)(iVar1 + 0x84);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f3bf70
// ---------------------------------------------------------------------------
int cSim::FUN_00f3bf70() {
    cInner* inner = mpInner;
    int* p = (int*)((char*)inner + 0x178);
    return (p[1] - p[0]) / 0x38;
}

// ---------------------------------------------------------------------------
// @ 0x00f3bfa0
// ---------------------------------------------------------------------------
int cSim::FUN_00f3bfa0(int idx) {
    return (int)mpInner->p178 + idx * 0x38;
}

// ---------------------------------------------------------------------------
// @ 0x00f3bfc0
// ---------------------------------------------------------------------------
int* cSim::FUN_00f3bfc0(int a, int* b, char c, int d) {
    if (a == 2) {
        if (c == 0) {
            vE8.x = *(float*)&b[0];
            vE8.y = *(float*)&b[1];
            vE8.z = *(float*)&b[2];
        } else {
            vF4[d].x = *(float*)&b[0];
            vF4[d].y = *(float*)&b[1];
            vF4[d].z = *(float*)&b[2];
        }
    }
    if (a != mpInner->f68[d] || vF4[d].x != *(float*)&b[0] ||
        vF4[d].y != *(float*)&b[1] || vF4[d].z != *(float*)&b[2]) {
        f84 = 1;
    }
    mpInner->f68[d] = a;
    return b;
}

// ---------------------------------------------------------------------------
// @ 0x00f3bce0
// ---------------------------------------------------------------------------
void cSim::FUN_00f3bce0(int idx, int* v) {
    int iVar2 = (int)mpInner;
    if (idx >= 0 && idx < (*(int*)(iVar2 + 0x17c) - *(int*)(iVar2 + 0x178)) / 0x38) {
        if (f8c != 0) {
            FUN_00f3b710((int*)(*(int*)(iVar2 + 0x178) + idx * 0x38));
            ((cSim*)f8c)->FUN_00f3b5e0(*(float*)((char*)f8c + 0x20));
        }
        int* p = (int*)(*(int*)((int)mpInner + 0x178) + idx * 0x38);
        p[0] = v[0];
        p[1] = v[1];
        p[2] = v[2];
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3b710
// ---------------------------------------------------------------------------
int FUN_00b3d300_cm();
void FUN_00b225d0_cm();

void FUN_00f3b710(int* key) {
    if (g_pGlobalUI->fcc == 1) return;
    int* items = (int*)FUN_00b3d300_cm();
    int* begin = (int*)items[0];
    int* end = (int*)items[1];
    for (int* it = begin; it != end; ++it) {
        int* p = (int*)*it;
        if (p != 0) {
            ((IRefObj*)p)->v00();
        }
        int inner = p[0xb20 / 4];
        int* v = (int*)(inner + 0x504);
        if (v[0] == key[0] && v[1] == key[1] && v[2] == key[2]) {
            FUN_00d539d0();
            FUN_00b225d0_cm();
            ((IRefObj*)p)->v04();
            return;
        }
        ((IRefObj*)p)->v04();
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3bc20
// ---------------------------------------------------------------------------
void cSim::FUN_00f3bc20(int param) {
    int n = (*(int*)(*(int*)((char*)this + 0x10) + 0x240) -
             *(int*)(*(int*)((char*)this + 0x10) + 0x23c)) / 0x534;
    if (n == 0) return;
    int off = 0;
    do {
        int base = *(int*)(*(int*)((char*)this + 0x10) + 0x23c);
        int p = *(int*)(base + 0x84 + off);
        int end = base + off + 0x88;
        if (p != end) {
            do {
                if (*(int*)(p + 4) == param) *(int*)(p + 4) = -1;
                if (*(int*)(p + 8) == param) *(int*)(p + 8) = -1;
                p += 0x188;
            } while (p != end);
        }
        off += 0x534;
        n--;
    } while (n != 0);
}

// ---------------------------------------------------------------------------
// @ 0x00f3b590  Random value in [min,max] (x87).
// ---------------------------------------------------------------------------
struct RandomLinearCongruential {
    double RandomDoubleUniform();                 // 0x009360d0
};
extern RandomLinearCongruential g_sMathRandom;   // 0x01601760

double FUN_00f3b590(float a, float b) {
    double r = g_sMathRandom.RandomDoubleUniform();
    double lo = (double)a - (double)b;
    double hi = (double)a + (double)b;
    double v = r * (hi - lo) + lo;
    if (v >= hi) v = hi;
    else if (v < lo) v = lo;
    return v;
}

// ---------------------------------------------------------------------------
// Skeleton for the remaining large functions (listed in partial.txt).
// ---------------------------------------------------------------------------
// @ 0x00f3b0c0
void cSim::FUN_00f3b0c0()
{
    cGameState* state = (cGameState*)g_pGlobalUI->f18;
    if (state != 0) {
        void* wm = mWindowMgr;
        void* w = ((PF_Get2ii)VTOF(wm)[0xf0 / 4])(wm, 0x74261f8, 1);
        if (w != 0) {
            void* c = ((PF_Get1u)VTOF(w)[0xc / 4])(w, 0x8ed27e7a);
            ((PF_SetTwo)VTOF(c)[0x28 / 4])(c, 4, state->fdc != 0.0f ? 1 : 0);
        }
        int v = (int)(state->f31e60() * 100.0f);
        wm = mWindowMgr;
        if (wm != 0) {
            void* a = ((PF_Get2ii)VTOF(wm)[0xf0 / 4])(wm, 0x72ff8e8, 1);
            if (a != 0) {
                void* b = ((PF_Get1u)VTOF(a)[0xc / 4])(a, 0xf00a8a0);
                if (b != 0)
                    ((PF_SetTwo)VTOF(b)[0x1c / 4])(b, v, 0);
            }
        }
        m00f3a4e0(0x73a55a0, v);
        v = (int)(state->fd0 * 100.0f);
        wm = mWindowMgr;
        if (wm != 0) {
            void* a = ((PF_Get2ii)VTOF(wm)[0xf0 / 4])(wm, 0x71842d8, 1);
            if (a != 0) {
                void* b = ((PF_Get1u)VTOF(a)[0xc / 4])(a, 0xf00a8a0);
                if (b != 0)
                    ((PF_SetTwo)VTOF(b)[0x1c / 4])(b, v, 0);
            }
        }
        m00f3a4e0(0x73a5550, v);
        v = FUN_00f3a160(state->fcc);
        wm = mWindowMgr;
        if (wm != 0) {
            void* a = ((PF_Get2ii)VTOF(wm)[0xf0 / 4])(wm, 0x7183c38, 1);
            if (a != 0) {
                void* b = ((PF_Get1u)VTOF(a)[0xc / 4])(a, 0xf00a8a0);
                if (b != 0)
                    ((PF_SetTwo)VTOF(b)[0x1c / 4])(b, v, 0);
            }
        }
        m00f3a4e0(0x73a5598, v);
    }
    m00f3a540(state->f18d);
    m00f3aa30();
}

// @ 0x00f3b440
// The retail body keeps its object pointer in ESI (live-in); reconstructed here
// with an explicit self argument.
float FUN_00f3b440(cSim* self, float x)
{
    float v[5];
    if (self->f253f0()) {
        FUN_00f21850(self, &v[0], &v[1], &v[2], &v[3], &v[4]);
    } else {
        v[0] = FUN_00eed280(self, 0);
        FUN_00eed0b0(self, &v[2], &v[1]);
        v[3] = v[1];
        v[4] = v[1];
    }
    float t = x;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    if (t < 0.5f)
        return v[0] + (v[3] - v[0]) * (t * 1.99993896484375f);
    return v[0] + (v[4] - v[0]) * ((t - 0.5f) * 1.99993896484375f);
}

// @ 0x00f3b520
float FUN_00f3b520(cSim* self)
{
    float v[5];
    if (self->f253f0()) {
        FUN_00f21850(self, &v[0], &v[1], &v[2], &v[3], &v[4]);
        return v[0];
    }
    FUN_00eed0b0(self, &v[1], &v[2]);
    return FUN_00eed280(self, 0);
}

// @ 0x00f3b5e0
int cSim::FUN_00f3b5e0(float x)
{
    if (g_pGlobalUI->fcc == 1) return 0;
    CPlanet* planet = FUN_00401090(this);
    int thing = planet->f4df550();
    if (thing == 0) return 0;

    float pos[3];
    CPlanetModel* pm = FUN_00b3d350();
    pm->f81780(pos, x, 3.0f, 20.0f);

    float v = (float)(FUN_00f3b590(1.0f, 0.05f) * (double)x);

    CNounManager* nm = (CNounManager*)FUN_00b3d300(0, 0);
    int u = nm->f989360();
    int noun = FUN_00c099e0(pos, thing, 1, u);

    void* iface = (void*)((char*)noun + 0xc0);
    ((PF_Void1f)VTOF(iface)[0x40 / 4])(iface, v);
    int q = ((PF_Int0)VTOF(iface)[0x30 / 4])(iface);
    ((PF_Void2pi)VTOF(iface)[0x44 / 4])(iface, &v, q);

    if (g_pGlobalUI->fcc == 1) *(char*)(noun + 0x12f) = 0;

    CPosse* posse = (CPosse*)FUN_00d539d0();
    posse->AddMember(noun);
    posse->f53b50(noun, &v);

    q = ((PF_Int0)VTOF(iface)[0x30 / 4])(iface);
    ((PF_Void2pi)VTOF(iface)[0x44 / 4])(iface, &v, q);
    return noun;
}

// @ 0x00f3b800
void __stdcall FUN_00f3b800(CPlacement* p, int a1, int a2)
{
    int cfg[4] = { 2, 0, 1, 0 };
    unsigned flag = 0;
    FUN_00eed720(p, a1, cfg);

    float x = p->x, y = p->y, z = p->z;
    float scale = p->f220;
    float inv = 1.0f / sqrtf(x * x + y * y + z * z);
    float nx = x * inv;
    float ny = y * inv;
    float nz = z * inv;

    int one = 1;
    float out[3];
    float* r = FUN_00eec2b0(out, &p->x, (flag >> 4) & 1, &one, a2);

    p->x = nx * scale + r[0];
    p->y = r[1] + ny * scale;
    p->z = r[2] + nz * scale;
    p->f209 = 1;
}

// @ 0x00f3b9e0
bool __stdcall FUN_00f3b9e0(CPlacement* p, void* bounds, char edge)
{
    float bb[6];
    ((PF_Void1p)VTOF(bounds)[0x6c / 4])(bounds, bb);
    float a = bb[0], b = bb[1], c = bb[2], d = bb[3], e = bb[4], f = bb[5];
    float corners[8][3] = {
        { a, b, c }, { d, b, c }, { a, e, c }, { d, e, c },
        { a, b, f }, { d, b, f }, { a, e, f }, { d, e, f }
    };

    float r = FUN_00b3d350()->f7e500();
    float r2 = r * r;
    for (int i = 0; i < 8; i++) {
        if (corners[i][0] * corners[i][0] +
            corners[i][1] * corners[i][1] +
            corners[i][2] * corners[i][2] > r2)
            return false;
    }

    if (edge) {
        char flagA, flagB;
        FUN_00eec8e0(p, &flagA, &flagB);
        float* v = &p->x;
        float out[3];
        FUN_00eec2b0(out, v, 0, &r2, g_15acb40 == 0);
        if (flagA == 0) {
            float d0 = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
            float d1 = sqrtf(out[0] * out[0] + out[1] * out[1] + out[2] * out[2]);
            if (d0 < d1 - 0.001f) return false;
        }
    }
    return true;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct cChecklist {
    void ToggleHint();   // 0x00efbbe0 (equiv t2)
};
}
