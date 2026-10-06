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
    virtual void* v0C(int id);      // +0x0C
    char pad0[0x10 - 4];
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

    void  FUN_00f3b290(char p);
    void  FUN_00f3b7c0(int p);
    int   FUN_00f3b920();
    int   FUN_00f3b420();
    bool  FUN_00f3b950();
    void  FUN_00f3b990();
    void  FUN_00f3bd90(int idx, char val);
    bool  FUN_00f3bde0(int idx);
    int   FUN_00f3be30();
    int   FUN_00f3be60(int idx);
    int   FUN_00f3bec0(int idx);
    int   FUN_00f3bf00(int a, int b);
    int   FUN_00f3bf70();
    int   FUN_00f3bfa0(int idx);
    void  FUN_00f3bfc0(int a, int* b, char c, int d);
    void  FUN_00f3bce0(int idx, int* v);
    void  FUN_00f3bcc0(int v);
    void  FUN_00f3bc20(int param);
};

// ---------------------------------------------------------------------------
// Externals / globals.
// ---------------------------------------------------------------------------
struct cChecklist { void ToggleHint(int, int); };
struct cManager14 { void FUN_00ed4e80(); };
struct cGlobalUI {
    char pad0[0x14];
    cManager14* f14;            // +0x14
    char pad1[0xcc - 0x18];
    int  fcc;                   // +0xcc
    char pad2[0xd4 - 0xd0];
    cChecklist* mpChecklist;    // +0xd4
};
extern cGlobalUI* g_pGlobalUI;                  // 0x016c7aa4
extern uint32_t g_016065f0;                     // 0x016065f0

void FUN_00f3b0c0();
void FUN_00f3b710(int* v);
void FUN_00f3b5e0(cSim* self, float x);
void FUN_00f253f0();
void FUN_00f21850();
void FUN_00eed0b0();
void FUN_00eed280();
int FUN_00552300(int);
char SP_EditorUtils_GetCreatorType(int);
int FUN_00d539d0();
int  FUN_00b3d300();
void FUN_00b225d0();
int  FUN_00b18e00(int);

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
    if (x < 2) return 0;
    if (x < 4) return 0xb1d38c08;
    if (x == 4) return 0xfa14571d;
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
    FUN_00b3d300();
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
        return *(char*)((char*)inner->p178 + 0x20 + idx * 0x38) != 0;
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
void cSim::FUN_00f3bfc0(int a, int* b, char c, int d) {
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
}

// ---------------------------------------------------------------------------
// @ 0x00f3bce0
// ---------------------------------------------------------------------------
void cSim::FUN_00f3bce0(int idx, int* v) {
    int iVar2 = (int)mpInner;
    if (idx >= 0 && idx < (*(int*)(iVar2 + 0x17c) - *(int*)(iVar2 + 0x178)) / 0x38) {
        if (f8c != 0) {
            FUN_00f3b710((int*)(*(int*)(iVar2 + 0x178) + idx * 0x38));
            FUN_00f3b5e0((cSim*)f8c, *(float*)((char*)f8c + 0x20));
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
    cInner* inner = mpInner;
    int n = ((int)inner->p240 - (int)inner->p23c) / 0x534;
    for (int i = 0; i < n; i++) {
        char* base = (char*)inner->p23c + i * 0x534;
        int* p = *(int**)(base + 0x84);
        int* end = (int*)(base + 0x88);
        while (p != end) {
            if (p[1] == param) p[1] = -1;
            if (p[2] == param) p[2] = -1;
            p = (int*)((char*)p + 0x188);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3b590  Random value in [min,max] (x87).
// ---------------------------------------------------------------------------
struct RandomLinearCongruential {
    double RandomDoubleUniform();
};
extern RandomLinearCongruential g_sMathRandom;   // 0x01601760

float FUN_00f3b590(float a, float b) {
    double r = g_sMathRandom.RandomDoubleUniform();
    float d = a - b;
    float v = (float)(r * (double)((b + a) - d)) + d;
    return v;
}

// ---------------------------------------------------------------------------
// Skeleton for the remaining large functions (listed in partial.txt).
// ---------------------------------------------------------------------------
// @ 0x00f3b0c0
void FUN_00f3b0c0() {}

// @ 0x00f3b440
void FUN_00f3b440(float f) { (void)f; }

// @ 0x00f3b520
float FUN_00f3b520() { return 0.0f; }

// @ 0x00f3b5e0
void FUN_00f3b5e0(cSim* self, float x) { (void)self; (void)x; }

// @ 0x00f3b800
void FUN_00f3b800() {}

// @ 0x00f3b9e0
void FUN_00f3b9e0() {}
