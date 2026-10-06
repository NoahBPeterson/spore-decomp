// Slice s00e75900 (bfs3 slice 20) -- SP cell-game generation/placement helpers.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (scalar movss + x87 float calls).
#include "types.h"

struct Vec3 { float x, y, z; };

// ------------------------------------------------------------------ globals
// Names encode the original address; the verifier masks relocations, so only
// the access width/type matters.  Constants are given their known float values.
extern float g_1485378;   // 0.0f
extern float g_1485720;   // 1.0f
extern float g_13f6bf8;   // 0.033333335f
extern float g_1471064;   // 0.5f
extern float g_1486110;   // 5.0f
extern float g_13eb95c;   // 3.0f
extern float g_13f8698;   // 7.0f
extern float g_1485544;   // 0.75f
extern float g_14853e0;   // 4.0f
extern float g_1483f64;   // 8.0f
extern float g_16b3c28;
extern float g_16b3c2c;
extern float g_16b3c30;
extern float g_15a7c4c;
extern float g_15a7c50;
extern float g_15a7c54;
extern float g_15a7c58;
extern float kLevelSize[];     // 0x1483bd0
extern char  kLevelTable[];    // 0x1483c14
extern char  kLevelTableEnd[]; // 0x1483c34
extern float kLevel1000;       // 0x1483e60

// ------------------------------------------------------------------ pool objects
// Cell: object stored in the pool at cCellGame+0x1c (a cSPCell).
struct Cell {
    char  pad0[0x4c];
    Vec3  pos;           // +0x4c
    float scale;         // +0x58
    char  pad5c[0x69 - 0x5c];
    bool  f_69;          // +0x69
    char  pad6a[0xa0 - 0x6a];
    float f_a0;          // +0xa0
    float f_a4;          // +0xa4
    char  padA8[0x110 - 0xa8];
    bool  f_110;         // +0x110
    bool  f_112;         // +0x112
    bool  f_113;         // +0x113
    char  pad114[0x16c - 0x114];
    bool  f_16c;         // +0x16c
    int   f_170;         // +0x170
    char  pad174[0x178 - 0x174];
    bool  f_178;         // +0x178
    bool  f_17a;         // +0x17a
    bool  f_17b;         // +0x17b
    bool  f_17c;         // +0x17c
    bool  f_17d;         // +0x17d
    bool  f_17e;         // +0x17e
    bool  f_17f;         // +0x17f
    char  pad180[0x188 - 0x180];
    bool  f_188;         // +0x188
    bool  f_189;         // +0x189
    char  pad18a[0x18c - 0x18a];
    int   f_18c;         // +0x18c
    char  pad190[0x1b0 - 0x190];
    int   f_1b0;         // +0x1b0
    char  pad1b4[0x1c4 - 0x1b4];
    Vec3  f_1c4;         // +0x1c4
    char  pad1d0[0x248 - 0x1d0];
    int   f_248;         // +0x248
    char  pad24c[0x358 - 0x24c];
    int   f_358;         // +0x358
    int   f_35c;         // +0x35c
};

// Rec: object stored in the pool at cCellGame+0x54.
struct Rec {
    char  pad0[4];
    int   f04;           // +0x04
    bool  f08;           // +0x08
    char  pad09[0x0c - 0x09];
    float f0c;           // +0x0c
    char  pad10[0x1c - 0x10];
    float f1c;           // +0x1c
    float f20;           // +0x20
    int   f24;           // +0x24
    int   f28;           // +0x28
    int   f2c;           // +0x2c
    int   f30;           // +0x30
    int   f34;           // +0x34
    int   f38;           // +0x38
    int   f3c;           // +0x3c
    float f40;           // +0x40
    float f44;           // +0x44
    Vec3  f48;           // +0x48
    Vec3  f54;           // +0x54
    int   f60, f64, f68, f6c; // +0x60
    int   f70;           // +0x70
    bool  f74;           // +0x74
    char  pad75[0x78 - 0x75];
    int   f78;           // +0x78
};

// Ctrl: object pointed to by cCellGame+0x5190.
struct Ctrl {
    char  pad0[0x1c];
    int   f1c;           // +0x1c
    char  pad20[0x69 - 0x20];
    bool  f69;           // +0x69
    char  pad6a[0xb0 - 0x6a];
    int   f_b0;          // +0xb0
    char  padb4[0xbc - 0xb4];
    float f_bc;          // +0xbc
};

struct cCellGame {
    char         pad0[0x40fc];
    int          midPlayerCell;   // +0x40fc
    char         pad4100[0x1c];
    int          field_411c;      // +0x411c
    char         pad4120[0x514c - 0x4120];
    int          field_514c;      // +0x514c
    char         pad5150[0x8];
    int          field_5158;      // +0x5158
    char         pad515c[0x5190 - 0x515c];
    Ctrl*        field_5190;      // +0x5190
    int          field_5194;      // +0x5194
    char         pad5198[0x51b0 - 0x5198];
    int          field_51b0;      // +0x51b0
    int          field_51b4;      // +0x51b4
    char         pad51b8[4];
    float        field_51bc;      // +0x51bc
    char         pad51c0[0x51cc - 0x51c0];
    float        field_51cc;      // +0x51cc
    char         pad51d0[0x51d4 - 0x51d0];
    int          field_51d4;      // +0x51d4
    char         pad51d8[0x51dc - 0x51d8];
    bool         field_51dc;      // +0x51dc
};

struct CellModeObj {
    char  pad0[0x90];
    void* field_90;      // +0x90  (cSPUILayout*)
    char  pad94[0xe4 - 0x94];
    bool  f_e4;          // +0xe4
    Vec3  f_e8;          // +0xe8
    float f_f4;          // +0xf4
    char  padF8[0x936 - 0xf8];
    bool  f_936;         // +0x936
};

extern cCellGame*   gspCellGame;   // 0x016b3c04
extern CellModeObj* g_16b3c0c;     // 0x016b3c0c

// ------------------------------------------------------------------ callees / stubs
struct cSPUILayout {
    void* FindWindowByID(unsigned int id, int b);   // 0x8105b0
    void  SetVisibility(int v);                     // 0x810590
};
struct cSPUITimeline {
    void Show(void* p);                             // 0xe44200
};
struct UIWindow {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual UIWindow* v3(unsigned int id);          // +0x0c
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10(int a, int b);                 // +0x28
};
struct EffectHost {                                 // this == FUN_00b3d400(1)
    void m_e14c10(int v);                           // 0xe14c10
};
struct RandomLinearCongruential {
    double RandomDoubleUniform();                   // 0x9360d0
};
extern RandomLinearCongruential sMathRandom;        // 0x01601760

struct Pool {
    void* Find(int id);   // 0xb721d0
    void* Get(int id);    // 0xb72210
    int   New();          // 0xb72160
};

void  __fastcall f743b50(void* p);                  // 0x00743b50
void  __fastcall f82130(void* p);                   // 0x00e82130
int*  __cdecl    f823a0(void* a, void* b);          // 0x00e823a0
bool  __cdecl    f5d410(Cell* c, Vec3* v, float f); // 0x00e5d410
int   __cdecl    f87260(Cell* c, Vec3* v, float f, void* buf, int n, int b); // 0x00e87260
void  __cdecl    f86f70(Cell* c);                   // 0x00e86f70
int   __cdecl    f74a20_10(Cell* c, Vec3* v, int a, void* b, int d, float one,
                           int z0, int z1, int g, int h); // 0x00e74a20 (10-arg)
int   __cdecl    f74a20_4(int a, Vec3* v, float f, int b);    // 0x00e74a20 (4-arg)
void  __cdecl    f4cce0_src(int a);                 // helper not used
int   __cdecl    f4cce0_8(int a, int b, int c, int d, int e, int f, int g, int h); // 0x00e4cce0
int   __cdecl    f4cce0_2(int a, int b);            // 0x00e4cce0
int   __cdecl    f6d200(Cell* c, int a, int b, int d); // 0x00e6d200
float __cdecl    f58b60(int a, int b);              // 0x00e58b60
void  __cdecl    f82690(int a, float f);            // 0x00e82690
void  __cdecl    f68170(Cell* c, int a);            // 0x00e68170
void  __cdecl    f61e20(Cell* c, float f, int a);   // 0x00e61e20
void  __cdecl    f6f800(Cell* c, int a, int b, float f0, float f1,
                        int e, int g, int h);       // 0x00e6f800
int   __cdecl    f51690(Cell* c);                   // 0x00e51690
float __cdecl    f52b70();                          // 0x00e52b70
void  __cdecl    f4f660(int a);                     // 0x00e4f660
int   __cdecl    f53660(int a, int b);              // 0x00e53660
cSPUITimeline* __cdecl f_b3d410(int a);             // 0x00b3d410
int   __cdecl    f_b3d400();                        // 0x00b3d400
EffectHost* __cdecl f_b3d400_b(int a);              // 0x00b3d400
void  __cdecl    f_e72c80();                        // 0x00e72c80
void  __cdecl    f_e5cae0(Vec3* out);               // 0x00e5cae0
void  __cdecl    f_e53e30(Vec3* out, void* ext, Vec3* in); // 0x00e53e30
int*  __cdecl    f_e4ce40(void* h);                 // 0x00e4ce40
int   __cdecl    f_e4ee60();                        // SP::sGetSourceLevel
int   __cdecl    f_e53d50(int a, float f);          // 0x00e53d50
int   __cdecl    f_e51ee0(int a, float f, int b, int c, int d, int e,
                          int p1, int p3, int p7, float p9,
                          int p4, int p5, int p6, int p2, int z, int p11); // 0x00e51ee0

// ------------------------------------------------------------------ 0x00e75b80
void FUN_00e75b80(void)
{
    cSPUILayout* layout = (cSPUILayout*)g_16b3c0c->field_90;
    UIWindow* w = (UIWindow*)layout->FindWindowByID(0x44827b8, 1);
    if (w != 0)
        w = w->v3(0x8ed27e7a);
    w->v10(4, 0);

    f53660(2, 0);
    cSPUITimeline* t = f_b3d410(0);
    t->Show(0);
    layout->SetVisibility(1);
    if (f_b3d400() != 0) {
        EffectHost* e = f_b3d400_b(1);
        e->m_e14c10(1);
    }
    if (gspCellGame->field_5158 == 5)
        f_e72c80();
}

// ------------------------------------------------------------------ 0x00e75c20
bool FUN_00e75c20(void)
{
    FUN_00e75b80();
    return false;
}

// ------------------------------------------------------------------ 0x00e75c30
bool FUN_00e75c30(int param_1)
{
    Cell* a = (Cell*)((Pool*)((char*)gspCellGame + 0x1c))->Find(gspCellGame->field_51d4);
    Cell* b = (Cell*)((Pool*)((char*)gspCellGame + 0x1c))->Find(gspCellGame->field_411c);
    if (a == 0 || b == 0)
        return false;

    f82690(0x1e08f6a, 1.0f);

    a->f_17c = 1; a->f_17b = 1; a->f_17f = 1; a->f_178 = 1;
    a->f_17a = 1; a->f_17e = 1; a->f_188 = 1; a->f_16c = 1; a->f_189 = 1;
    a->f_170 = b->f_170;
    b->f_17c = 1; b->f_17b = 1; b->f_17f = 1; b->f_178 = 1;
    b->f_17a = 1; b->f_17e = 1; b->f_188 = 1; b->f_16c = 1; b->f_189 = 1;
    b->f_170 = a->f_170;

    f68170(a, param_1);
    f61e20(a, 1.0f, param_1);
    f68170(b, param_1);
    f61e20(b, 1.0f, param_1);

    float dx = b->pos.x - a->pos.x;
    float dy = b->pos.y - a->pos.y;
    float dz = b->pos.z - a->pos.z;
    float dist = dx * dx + dy * dy + dz * dz;
    if (4.0f < dist) {
        f6f800(b, a->f_170, param_1, 1.0f, 1.0f, 8, 0, 0);
        f6f800(a, b->f_170, param_1, 1.0f, 1.0f, 8, 0, 0);
    }

    a->f_18c = 0x41;
    b->f_18c = 0x42;
    g_16b3c0c->f_e4 = 1;
    g_16b3c0c->f_e8.x = a->pos.x + (b->pos.x - a->pos.x) * 0.5f;
    g_16b3c0c->f_e8.y = a->pos.y + (b->pos.y - a->pos.y) * 0.5f;
    g_16b3c0c->f_e8.z = a->pos.z + (b->pos.z - a->pos.z) * 0.5f;
    g_16b3c0c->f_f4 = 3.0f;
    gspCellGame->field_51dc = 1;
    return true;
}

// ------------------------------------------------------------------ 0x00e75ea0
void FUN_00e75ea0(void)
{
    Cell* a = (Cell*)((Pool*)((char*)gspCellGame + 0x1c))->Find(gspCellGame->field_51d4);
    Cell* b = (Cell*)((Pool*)((char*)gspCellGame + 0x1c))->Find(gspCellGame->field_411c);
    if (a == 0 || b == 0)
        return;
    if (a->f_112 != 0 || a->f_113 != 0 || b->f_112 != 0 || b->f_113 != 0)
        return;
    if (a->f_188 != 0 || b->f_188 != 0)
        return;

    int ib = f51690(b);
    int ia = f51690(a);
    if (ia != ib)
        return;

    if (gspCellGame->field_51b4 == 3) {
        float f = f52b70();
        gspCellGame->field_51bc = f;
        gspCellGame->field_5190->f_b0 = 3;
        gspCellGame->field_5190->f_bc = 5.0f;
        gspCellGame->field_51b4 = -1;
        gspCellGame->field_51b0 = 0;
    }

    f4f660(1);

    Cell* p = (Cell*)((Pool*)((char*)gspCellGame + 0x1c))->Get(gspCellGame->field_51d4);
    float f = (float)f6d200(p, 0, 0x41, p->f_1b0);
    Cell* q = (Cell*)((Pool*)((char*)gspCellGame + 0x1c))->Get(gspCellGame->field_411c);
    f6d200(q, 0, 0x42, q->f_1b0);

    int id = ((Pool*)((char*)gspCellGame + 0x54))->New();
    Rec* c = (Rec*)((Pool*)((char*)gspCellGame + 0x54))->Get(id);
    c->f1c = f; c->f20 = f;
    c->f24 = 0x2d;
    c->f28 = 0; c->f2c = 0; c->f30 = -1; c->f34 = -1;
    c->f38 = 0; c->f3c = 0; c->f40 = 0.0f; c->f44 = 0.0f;
    c->f48.x = g_16b3c28; c->f48.y = g_16b3c2c; c->f48.z = g_16b3c30;
    c->f54.x = g_16b3c28; c->f54.y = g_16b3c2c; c->f54.z = g_16b3c30;
    c->f60 = *(int*)&g_15a7c4c; c->f64 = *(int*)&g_15a7c50;
    c->f68 = *(int*)&g_15a7c54; c->f6c = *(int*)&g_15a7c58;
    c->f70 = 0; c->f74 = 0; c->f78 = 0; c->f04 = 0; c->f08 = 0;
    gspCellGame->field_5194 = id;
    FUN_00e75c30(0);
}

// ------------------------------------------------------------------ 0x00e760f0
void FUN_00e760f0(void)
{
    Cell* e = (Cell*)((Pool*)((char*)gspCellGame + 0x1c))->Find(gspCellGame->field_51d4);
    if (e == 0) {
        Vec3 v1, v2;
        f_e5cae0(&v1);
        f_e53e30(&v2, 0, &v1);
        f743b50(&v2);
        int* pi = f_e4ce40(&v2);
        float s = *(float*)((char*)pi + 0x110);
        f82130(&v2);
        v2.x = v1.x * s + v2.x;
        v2.y = v1.y * s + v2.y;
        v2.z = v1.z * s + v2.z;
        int src = f_e4ee60();
        int r = f4cce0_8(0x1a, src, 0x3f800000, 0, 1, 0, 0, 0);
        r = f74a20_4(gspCellGame->midPlayerCell, &v2, 0.0f, r);
        gspCellGame->field_51d4 = r;
    }

    Cell* q = (Cell*)((Pool*)((char*)gspCellGame + 0x1c))->Get(gspCellGame->field_411c);
    float fv = (float)f6d200(q, 0, 0x43, q->f_1b0);

    int id = ((Pool*)((char*)gspCellGame + 0x54))->New();
    Rec* c = (Rec*)((Pool*)((char*)gspCellGame + 0x54))->Get(id);
    c->f1c = 8.0f; c->f20 = 8.0f;
    c->f24 = 0x2e;
    c->f28 = 0; c->f2c = 0; c->f30 = -1; c->f34 = -1;
    c->f38 = 0; c->f3c = 0; c->f40 = 0.0f; c->f44 = 0.0f;
    c->f48.x = g_16b3c28; c->f48.y = g_16b3c2c; c->f48.z = g_16b3c30;
    c->f54.x = g_16b3c28; c->f54.y = g_16b3c2c; c->f54.z = g_16b3c30;
    c->f60 = *(int*)&g_15a7c4c; c->f64 = *(int*)&g_15a7c50;
    c->f68 = *(int*)&g_15a7c54; c->f6c = *(int*)&g_15a7c58;
    c->f70 = 0; c->f74 = 0; c->f78 = 0; c->f04 = 0; c->f08 = 0;
    c->f0c = fv;
    gspCellGame->field_5194 = id;
    f_e53d50(0, fv);
}

// ------------------------------------------------------------------ 0x00e76320
void FUN_00e76320(void)
{
    if (g_16b3c0c->f_936 != 0)
        return;
    if (gspCellGame->field_51cc > 0.0f)
        return;
    if (gspCellGame->field_5190->f69 == 0)
        return;
    FUN_00e760f0();
}

// ------------------------------------------------------------------ 0x00e76360
bool FUN_00e76360(int* state, int param_2, int param_3, int param_4, int param_5,
                  float* param_6, int param_7, int param_8, float param_9,
                  float param_10, int param_11, float param_12)
{
    Cell* c;
    if (*state == 0) {
        if (param_9 < param_10)
            return true;
        int id = f74a20_10((Cell*)param_3, (Vec3*)param_5, 0, (void*)param_2, param_4,
                           1.0f, 0, 0, param_7, param_11);
        *state = id;
        c = (Cell*)((Pool*)((char*)gspCellGame + 0x1c))->Get(id);
        c->f_a0 = *(float*)&param_8;
        if (0.0f < param_12) {
            float k = 1.0f / param_12;
            c->f_1c4.x += param_6[0] * k;
            c->f_1c4.y += param_6[1] * k;
            c->f_1c4.z += param_6[2] * k;
        }
    } else {
        c = (Cell*)((Pool*)((char*)gspCellGame + 0x1c))->Find(*state);
        if (c == 0)
            return false;
    }
    c->f_17b = 1;
    c->f_17d = 1;
    return true;
}

// ------------------------------------------------------------------ 0x00e76480
int FUN_00e76480(int param_1, int param_2, int param_3, int param_4, int param_5,
                 int param_6, int param_7, int param_8, float param_9, float param_10,
                 int param_11)
{
    int id = f_e51ee0(3, param_9 + param_10, 0, 0, -1, -1, param_1, param_3, param_7,
                      param_9, param_4, param_5, param_6, param_2, 0, param_11);
    Cell* c = (Cell*)((Pool*)((char*)gspCellGame + 0x54))->Get(id);
    int* state = (int*)((char*)c + 0x28);
    FUN_00e76360(state, param_1, param_2, param_3, param_4, (float*)param_5,
                 param_6, param_7, 0.0f, param_9, param_11, param_10);
    return *state;
}

// ------------------------------------------------------------------ 0x00e76540
int FUN_00e76540(Cell* cell, int param_2, int param_3, float* param_4, float param_5,
                 int param_6, int param_7)
{
    float fx = param_4[0];
    float fy = param_4[1];
    float fz = param_4[2];
    float sc = cell->scale;
    int lvl = cell->f_358;
    Vec3 local;
    local.x = fx * sc + cell->pos.x;
    local.y = fy * sc + cell->pos.y;
    local.z = fz * sc + cell->pos.z;
    if (lvl == -1)
        lvl = f_e4ee60();
    int off = lvl + param_2;
    int lo = 0x13;
    int hi = 0;
    int* p = &hi;
    if (-1 < off)
        p = &off;
    if (lo < *p)
        p = &lo;
    Vec3 dir;
    dir.x = fx * param_5;
    dir.y = fy * param_5;
    dir.z = fz * param_5;
    return f_e51ee0(param_3, cell->f_35c, *p, (int)&local, (int)&dir, 0, 0,
                    param_7, 0, param_6, -1, 0, 0, 0, 0, 0);
}

// ------------------------------------------------------------------ 0x00e76660
void FUN_00e76660(int* param_1, int param_2, int param_3)
{
    int u1 = f4cce0_8(3, 0, 0, 0, 0, 0, 0, 0);
    int u2 = f4cce0_8(4, 0, 0, 0, 0, 0, 0, 0);
    if (*param_1 != gspCellGame->field_411c)
        u1 = u2;

    int lvl = gspCellGame->field_5190->f1c;
    int* tbl;
    if (lvl == 1000) {
        tbl = (int*)&kLevel1000;
    } else {
        int idx = 0;
        if (-1 < lvl) {
            int* p = (int*)&kLevelTableEnd;
            do {
                p += 7;
                ++idx;
            } while (*p <= lvl);
        }
        tbl = (int*)(kLevelTable + idx * 0x1c);
    }

    int id = FUN_00e76480(u1, param_1[0xd7], *tbl, param_3, 0, 0, 0, 0,
                          0.0f, 0.75f, -5);
    Cell* c = (Cell*)((Pool*)((char*)gspCellGame + 0x1c))->Get(id);
    if (*param_1 == gspCellGame->field_411c)
        c->f_110 = 1;

    float f = 0.0f;
    switch (param_2) {
    case 1: f = 3.0f; break;
    case 2: f = 5.0f; break;
    case 3: f = 7.0f; break;
    }

    int id2 = ((Pool*)((char*)gspCellGame + 0x54))->New();
    Rec* c2 = (Rec*)((Pool*)((char*)gspCellGame + 0x54))->Get(id2);
    c2->f1c = f; c2->f20 = f;
    c2->f24 = 0x1a;
    c2->f28 = id; c2->f2c = 0; c2->f30 = -1; c2->f34 = -1;
    c2->f38 = 0; c2->f3c = 0; c2->f40 = 0.0f; c2->f44 = 0.0f;
    c2->f48.x = g_16b3c28; c2->f48.y = g_16b3c2c; c2->f48.z = g_16b3c30;
    c2->f54.x = g_16b3c28; c2->f54.y = g_16b3c2c; c2->f54.z = g_16b3c30;
    c2->f60 = *(int*)&g_15a7c4c; c2->f64 = *(int*)&g_15a7c50;
    c2->f68 = *(int*)&g_15a7c54; c2->f6c = *(int*)&g_15a7c58;
    c2->f70 = 0; c2->f74 = 0; c2->f78 = 0; c2->f04 = 0; c2->f08 = 0;

    Cell* c3 = (Cell*)((Pool*)((char*)gspCellGame + 0x1c))->Find(id);
    if (c3 != 0 && c3->f_248 != 0) {
        float v = f58b60(0, (int)&f);
        c3->f_a0 = v;
        c3->f_a4 = v;
    }
}

// ================================================================== 0x00e75900
namespace SP {
void sGenDistribute(int param_1, float* param_2, float param_3, float param_4,
                    float param_5, int param_6, int param_7, int param_8, char param_9)
{
    float spanX = param_2[3] - param_2[0];
    float spanY = param_2[4] - param_2[1];
    Vec3 work;
    float curZ = g_16b3c28;
    float curX = g_16b3c2c;
    float curY = g_16b3c30;

    f743b50(&work);
    int iVar2 = *f823a0((void*)param_6, &work);
    float step = *(float*)((char*)iVar2 + 0x308);
    f82130(&work);
    step = (kLevelSize[param_7] / *(float*)((char*)gspCellGame + 0x514c)) *
           step * 0.033333335f;

    float budget = param_5;
    for (;;) {
        if (budget <= 0.0f)
            return;
        double r = sMathRandom.RandomDoubleUniform();
        if ((float)r <= budget) {
            int attempts = 0;
            int placed = 1;
            float maxv = param_3;
            if (param_4 != 0.0f)
                maxv = param_4;
            float r2 = (float)sMathRandom.RandomDoubleUniform() * (maxv - param_3) + param_3;
            curY = r2;
            for (;;) {
                if (attempts >= 10)
                    break;
                ++attempts;
                curZ = (float)sMathRandom.RandomDoubleUniform() * spanX + param_2[0];
                curX = (float)sMathRandom.RandomDoubleUniform() * spanY + param_2[1];
                Vec3 v;
                v.x = curZ;
                v.y = curX;
                v.z = curY;
                bool hit = f5d410((Cell*)param_1, &v, step);
                if (!hit || param_9 != 0) {
                    if (param_1 != *(int*)((char*)gspCellGame + 0x40fc))
                        break;
                    char buf[0x200];
                    placed = f87260((Cell*)param_1, &v, step, buf, 0x200, 0);
                }
                if (placed <= 0)
                    break;
            }
            if (attempts < 10) {
                Vec3 v;
                v.x = curZ;
                v.y = curX;
                v.z = curY;
                f74a20_10((Cell*)param_1, &v, (int)curY, (void*)param_6, param_7,
                          1.0f, 0, 1, 0, 0);
                f86f70((Cell*)param_1);
            }
        }
        budget = budget - 1.0f;
    }
}
} // namespace SP
