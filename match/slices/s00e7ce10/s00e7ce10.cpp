// Slice s00e7ce10 -- SPGonzago/SPCellGame.obj (cell stage): the cell-mode input/camera
// handlers, the active-block updater, the eat/ability helpers and the death/eaten event.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell TU; no /EHsc)
//
// Several of the originals are static helpers that cl gave a register calling convention
// (0xe7d070 takes its resource handle in EAX; 0xe7d760 takes its subject in ESI and threads
// a second input through EDI).  They are modelled here as ordinary functions whose first
// parameter is that subject, which is behaviourally identical once the whole TU is recompiled.
#include "types.h"

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define I(p,o) (*(int*)((char*)(p) + (o)))
#define U(p,o) (*(u32*)((char*)(p) + (o)))
#define F(p,o) (*(float*)((char*)(p) + (o)))
#define P(p,o) (*(void**)((char*)(p) + (o)))
#define B(p,o) (*(u8*)((char*)(p) + (o)))

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------- globals
extern char*  gspCellGame;             // 0x016b3c04
extern char*  gspCellUI;               // 0x016b3c0c
extern Vec3   gCellWorldCenter;        // 0x016b3c28
extern float  g_15a7c4c[4];            // 0x015a7c4c  (0,0,0,1)
extern int    g_keyDefaultFood;        // 0x016b3c14  (default-food resource handle)
extern int    g_levelMaxTime;          // 0x01483c2c  (clamp target for level[0x1c])
extern float  g_147b9f0;               // 0x0147b9f0
extern float  g_1440f84;               // 0x01440f84  (1/6)
extern float  g_1470f1c;               // 0x01470f1c  (2.0f)
extern float  g_half_1471064;          // 0x01471064  (0.5f)

// ---------------------------------------------------------------- pools / registry
struct Pool {
    void* GetSafe(int h);        // 0x00b721d0, thiscall ret 4
    void* Get(int h);            // 0x00b72210, thiscall ret 4
    int   Alloc();               // 0x00b72160, thiscall ret
    void  Free(int h);           // 0x00b72260, thiscall ret 4
};

static Pool* cells() { return (Pool*)(gspCellGame + 0x1c); }

struct cTriggerMgr { void setModal(int a); };                 // 0x00ad7e40 thiscall
struct cSPUILayout { void* FindWindowByID(u32 id, int flag); };// 0x008105b0 thiscall
struct cLocalInputState { int OnMouseWheel(int a, float b, float c, u32 d); }; // 0x00697b40

struct cCellMode { char OnMouseWheel(int a, float b, float c, u32 d); };

// ---------------------------------------------------------------- callees
extern "C" void  __fastcall FUN_00743b50(void* ref);                // 0x00743b50 ref ctor (ecx)
extern "C" void  __fastcall FUN_00e82130(void* ref);                // 0x00e82130 ref dtor (ecx)
extern "C" void* FUN_00e4cc40(int id, void* out);                   // 0x00e4cc40 -> 0x00e823a0
extern "C" void* FUN_00e4ce40(void* out);                           // 0x00e4ce40 LayerCatalog_ApplyA
extern "C" void* FUN_00e52910(int handle);                          // 0x00e52910 resolve handle
extern "C" int   FUN_00e4cce0(int id);                              // 0x00e4cce0 LayerCatalog_GetEntry
extern "C" int   FUN_00e4fca0(void);                                // 0x00e4fca0
extern "C" void  FUN_00e6e8c0(int a);                               // 0x00e6e8c0
extern "C" void  FUN_00e79720(void);                                // 0x00e79720 sCinematicGoldy_Start
extern "C" int   __fastcall FUN_00e51430(int level);                // 0x00e51430 level row
extern "C" float __fastcall FUN_00e4eea0(int unused, int n);        // 0x00e4eea0 CellLevel_GetFloat
extern "C" float __fastcall FUN_00e4eef0(int unused, int n);        // 0x00e4eef0 CellLevel_GetRatio
extern "C" void  FUN_00e7cd10(void);                                // 0x00e7cd10
extern "C" void  FUN_00e57170(int id, float v);                     // 0x00e57170 set
extern "C" void  FUN_00e72b40(void* self);                          // 0x00e72b40 self-cast
extern "C" float FUN_00e52b70(void);                                // 0x00e52b70
extern "C" void  FUN_00e648d0(void* self);                          // 0x00e648d0 empty stub
extern "C" void  FUN_00e51650(void);                                // 0x00e51650 emit
extern "C" void  FUN_00e53460(void);                                // 0x00e53460 mission
extern "C" void  FUN_00e62340(void* cell, int v);                   // 0x00e62340
extern "C" void  FUN_00e77d50(float dt);                            // 0x00e77d50
extern "C" char  FUN_00e5f810(void* box);                           // 0x00e5f810 sBlockIsInRange
extern "C" int   FUN_00e5fa80(void* self, float* out);              // 0x00e5fa80 collect
extern "C" void  FUN_00e7c6c0(void* a, void* b);                    // 0x00e7c6c0
extern "C" void* FUN_00b41ea0(void* first, void* last, void* key, char flag); // lower_bound
extern "C" void* FUN_00e63d60(void* self, void* pos, void* val);    // EASTL insert
extern "C" void  FUN_00e394f0(u32 id, void* a, void* b, void* c, void* d); // 0x00e394f0
extern "C" void  FUN_00e780a0(int id, int a, float b, int c);       // 0x00e780a0
extern "C" char  FUN_00e509d0(int a, void* b);                      // 0x00e509d0 mode
extern "C" void  FUN_00e5c8e0(void* self);                          // 0x00e5c8e0 spawn
extern "C" void  FUN_00e66840(void* self, u32 id);                  // 0x00e66840
extern "C" float FUN_00e6d200(void* a, int b, int c, int d);        // 0x00e6d200
extern "C" void  FUN_00e59500(int id);                              // 0x00e59500 reset
extern "C" void  FUN_00e59200(void* p);                             // 0x00e59200 remove
extern "C" int   FUN_00e58980(void* a, void* b);                    // 0x00e58980 cell-pair
extern "C" void  FUN_00e576f0(int id);                              // 0x00e576f0 apply
extern "C" void* FUN_00e62200(int id, float f);                     // 0x00e62200
extern "C" void  FUN_00e7a770(int a, int b, int c, int d, int e, float f); // 0x00e7a770
extern "C" void  FUN_00e67d30(void* out, void* p, int a);           // 0x00e67d30
extern "C" void  FUN_00e72530(void* p, int a, void* v);             // 0x00e72530
extern "C" void  FUN_00e514c0(void);                                // 0x00e514c0 emit
extern "C" void  FUN_00e72430(void* p);                             // 0x00e72430 ability-activate
extern "C" char  FUN_00b1fbf0(void);                                // 0x00b1fbf0
extern "C" void  FUN_00e50f60(int a);                               // 0x00e50f60 zoom
extern "C" void  FUN_00e51060(int a);                               // 0x00e51060 zoom
extern "C" u32   FNV1_String8(const char* s, u32 seed, int one);    // 0x00932e80
extern "C" cTriggerMgr* FUN_00b3d4d0(void);                         // 0x00b3d4d0 GetTriggerMgr
extern "C" void  FUN_00e79320(void* self, int b, float f);          // 0x00e79320 sOnEatEater
extern "C" void  FUN_00e671c0(void* cell);                          // 0x00e671c0 sBomb_Start

// forward decls
void FUN_00e7d070(int handle, int param_1, float param_2);          // 0x00e7d070 (EAX ABI)
void FUN_00e7d760(void* self, int a, int b, float f);               // 0x00e7d760 (ESI/EDI ABI)

// ------------------------------------------------------------------ 0x00e7ce10
// SP::cCellMode helper -- advance the level clock and refresh the level-dependent state.
// @ 0x00e7ce10
void FUN_00e7ce10(int add, char flag)
{
    char* lvl = *(char**)(gspCellGame + 0x5190);
    if (B(lvl, 0x68) == 0 && I(lvl, 0x1c) > 0x77 && I(lvl, 0x1c) < 0x97) {
        int cnt = 0;
        int n = 13;
        int* p = (int*)(lvl + 0x34);
        do { if (*p != 0) ++cnt; ++p; --n; } while (n != 0);
        cnt -= 4;
        if (cnt < 1 && I(lvl, 0x7c) != 2)
            FUN_00e79720();
    }
    lvl = *(char**)(gspCellGame + 0x5190);
    int old = I(lvl, 0x1c);
    I(lvl, 0x1c) = I(lvl, 0x1c) + add;
    if (I(lvl, 0x1c) > 0x3e8)
        I(lvl, 0x1c) = g_levelMaxTime;
    int delta = (old - I(lvl, 0x1c)) + add;
    if (delta > 0) {
        if (flag != 0) I(lvl, 0x24) += delta;
        else           I(lvl, 0x28) += delta;
    }
    if (old != I(lvl, 0x1c)) {
        if (flag != 0)
            I(lvl, 0x20) += I(lvl, 0x1c) - old;
        char* player = (char*)((Pool*)(gspCellGame + 0x1c))->GetSafe(I(gspCellGame, 0x411c));
        FUN_00e51430(I(lvl, 0x1c));
        FUN_00e51430(old);
        FUN_00e648d0(player);
        float f_old = FUN_00e4eea0(0, old);
        float f_new = FUN_00e4eea0(0, I(lvl, 0x1c));
        if (f_old != f_new) {
            F(gspCellGame, 0x5150) = f_new;
            FUN_00e7cd10();
        }
        float r_old = FUN_00e4eef0(0, old);
        float r_new = FUN_00e4eef0(0, I(lvl, 0x1c));
        if (f_old != f_new || r_old != r_new) {
            char* q = (char*)((Pool*)(gspCellGame + 0x1c))->Get(I(gspCellGame, 0x411c));
            if (r_new > r_old || f_new > f_old)
                FUN_00e72b40(q);
            else
                FUN_00e57170(I(q, 0), r_new);
            F(gspCellGame, 0x51bc) = FUN_00e52b70();
            B(gspCellGame, 0x51c0) = 0;
        }
        if (I(lvl, 0x1c) == 1000) {
            char ref[4];
            FUN_00743b50(ref);
            char* info = (char*)FUN_00e4ce40(ref);
            int x = I(info, 0xdc);
            FUN_00e82130(ref);
            if (x == 1 || FUN_00e4fca0() == 2)
                FUN_00e6e8c0(0);
        }
    }
}

// ------------------------------------------------------------------ 0x00e7d070
// Execute the current cell "mode" action for the resource handle in EAX.  The subject arrives
// in EAX and the two arguments on the stack (int action, float dt).
// @ 0x00e7d070
void FUN_00e7d070(int handle, int param_1, float param_2)
{
    if (I(gspCellGame, 0x411c) == 0)
        return;
    char* cell = (char*)((Pool*)(gspCellGame + 0x1c))->Get(I(gspCellGame, 0x411c));
    char ref[4];
    FUN_00743b50(ref);
    char* ent = 0;
    if (handle != g_keyDefaultFood)
        ent = (char*)FUN_00e4cc40(handle, ref);
    if (ent != 0) {
        if (B(ent, 0x314) != 0)
            FUN_00e671c0(cell);
        if (B(ent, 0x315) != 0)
            FUN_00e77d50(param_2);
    }
    int* pi = (int*)(cell + 0x244);
    int v = *pi;
    if (v < 6) {
        if (ent == 0) {
            if (I(gspCellGame, 0x411c) == I(cell, 0))
                FUN_00e62340(cell, v);
            *pi += 2;
        } else if (I(ent, 0x310) > 0) {
            if (I(gspCellGame, 0x411c) == I(cell, 0))
                FUN_00e62340(cell, v);
            char* lvl = *(char**)(gspCellGame + 0x5190);
            if (I(lvl, 0x7c) == 0)
                *pi += I(ent, 0x310) * 2;
            else
                *pi += I(ent, 0x310);
        }
    }
    int six = 6;
    if (*pi < 6) six = *pi;
    *pi = six;
    int a;
    if (ent == 0) {
        a = 10;
    } else {
        a = I(ent, 0x30c);
        if (a == 0) {
            FUN_00e82130(ref);
            return;
        }
    }
    B(*(char**)(gspCellGame + 0x5190), 0xe1) = 1;
    FUN_00e51650();
    char* lvl = *(char**)(gspCellGame + 0x5190);
    if (B(lvl, 0x69) == 0 && I(lvl, 0x1c) > 0x95) {
        F(gspCellGame, 0x51d0) = g_147b9f0;
        B(lvl, 0x69) = 1;
    }
    lvl = *(char**)(gspCellGame + 0x5190);
    if (I(lvl, 0x80) == 1) {
        int* pi2 = (int*)(lvl + 0x84);
        if (*pi2 != 5) {
            *pi2 += 1;
            int cap = 5;
            if (*pi2 < 6) cap = *pi2;
            *pi2 = cap;
            if (cap == 5)
                FUN_00e53460();
        }
    }
    int first;
    if (ent == 0) first = 1;
    else if ((B(ent, 0xb0) & 1) == 0) first = (I(ent, 0xb4) == 3) ? 1 : 0;
    else if (param_1 == 2) first = 0;
    else if (param_1 == 3) first = 1;
    else if (param_1 == 4) first = 0;
    else first = (I(ent, 0xb4) == 3) ? 1 : 0;
    FUN_00e7ce10(a, (char)first);
    char* lvl2 = *(char**)(gspCellGame + 0x5190);
    int buf[10];
    for (int i = 0; i < 10; ++i) buf[i] = 0;
    if (first)
        FUN_00e394f0(0x9ef61113, lvl2 + 0x10, buf + 7, buf + 4, buf + 1);
    else
        FUN_00e394f0(0xac7161b5, lvl2 + 0x10, buf + 1, buf + 4, buf + 7);
    FUN_00e82130(ref);
}

// ------------------------------------------------------------------ 0x00e7d370
// SP::sUpdateActiveBlocks -- drop blocks that fell out of range and register the ones that
// entered it.
// @ 0x00e7d370
void FUN_00e7d370(int param_1, int* vec, char param_3)
{
    int* cur = (int*)vec[0];
    if (cur != (int*)vec[1]) {
        int* el = cur + 2;
        do {
            int handle = el[-1];
            char* blk = (char*)((Pool*)(gspCellGame + 0x38))->Get(handle);
            if (I(blk, 8) != -1) {
                if (FUN_00e5f810(blk + 4) == 0) {
                    blk = (char*)((Pool*)(gspCellGame + 0x38))->Get(handle);
                    void* sub = P(blk, 0x300);
                    if (sub != 0) {
                        ((void(__thiscall*)(void*, int))(*(void***)sub)[3])(sub, 1);
                        sub = P(blk, 0x300);
                        if (sub != 0) {
                            P(blk, 0x300) = 0;
                            ((void(__thiscall*)(void*))(*(void***)sub)[1])(sub);
                        }
                    }
                    ((Pool*)(gspCellGame + 0x38))->Free(handle);
                    int* gend = *(int**)(gspCellGame + 0x412c);
                    int* src = el;
                    int* dst = el - 2;
                    while (src != gend) {
                        dst[0] = src[0];
                        dst[1] = src[1];
                        src += 2;
                        dst += 2;
                    }
                    I(gspCellGame, 0x412c) = I(gspCellGame, 0x412c) - 8;
                } else {
                    cur += 2;
                    el += 2;
                }
            }
        } while (cur != (int*)vec[1]);
    }

    float recbuf[2560];
    int n = FUN_00e5fa80((void*)(long)param_1, recbuf);
    int hit = 0;
    int idx = 0;
    if (n > 0) {
        char* rd = (char*)recbuf;
        do {
            u32 k = (((u32)*(u32*)(rd) << 8) | (u8)rd[4]);
            k = (k << 8) | (u8)rd[8];
            k = (k << 8) | (u8)rd[0xc];
            int* pb = (int*)vec[0];
            int* pe = (int*)vec[1];
            int cnt = ((char*)pe - (char*)pb) >> 3;
            while (cnt > 0) {
                int half = cnt >> 1;
                if (pb[half * 2] < (int)k) {
                    pb += half * 2 + 2;
                    cnt += -1 - half;
                } else {
                    cnt = half;
                }
            }
            if (pb == pe || (int)k < pb[0]) {
                // not present: register the block and insert its key
                u8 flag = (param_3 == 0 || *(u32*)rd == 0) ? 0 : 1;
                rd[0x10] = (char)flag;
                int h = ((Pool*)(gspCellGame + 0x38))->Alloc();
                char* nb = (char*)((Pool*)(gspCellGame + 0x38))->Get(h);
                I(nb, 4)    = *(int*)(rd + 0x00);
                I(nb, 8)    = *(int*)(rd + 0x04);
                I(nb, 0xc)  = *(int*)(rd + 0x08);
                I(nb, 0x10) = *(int*)(rd + 0x0c);
                I(nb, 0x14) = *(int*)(rd + 0x10);
                FUN_00e7c6c0(nb, (void*)(char)param_3);
                int stored = I(nb, 0);
                int keyv = (int)k;
                int* pos = (int*)FUN_00b41ea0((void*)vec[0], (void*)pe, &keyv, (char)vec[0x406]);
                if (pos == pe || (int)k < pos[0]) {
                    int* r;
                    if (pos == pe)
                        r = (int*)FUN_00b41ea0((void*)vec[0], (void*)pe, &keyv, (char)vec[0x406]);
                    else
                        r = (int*)FUN_00b41ea0((void*)vec[0], (void*)pos, &keyv, (char)vec[0x406]);
                    if (r == pe || (int)k < r[0]) {
                        int* base = (int*)vec[0];
                        if (r == pe && pe != (int*)vec[2]) {
                            vec[1] = (int)(pe + 2);
                            pe[0] = keyv;
                            pe[1] = 0;
                        } else {
                            FUN_00e63d60(vec, r, &keyv);
                        }
                        pos = (int*)((char*)vec[0] + (((char*)r - (char*)base) >> 3) * 8);
                    }
                }
                pos[1] = stored;
                ++hit;
                if (hit > 0x32 && param_3 == 0)
                    return;
            }
            ++idx;
            rd += 0x14;
        } while (idx < n);
    }
}

// ------------------------------------------------------------------ 0x00e7d660
// SP::cCellMode::OnMouseWheel -- zoom / mode switch.
// @ 0x00e7d660
char cCellMode::OnMouseWheel(int param_1, float param_2, float param_3, u32 param_4)
{
    ((cLocalInputState*)gspCellUI)->OnMouseWheel(param_1, param_2, param_3, param_4);
    if ((param_4 & 1) != 0 && FUN_00b1fbf0() == 0) {
        FUN_00e50f60(param_1 / 0x78);
        return 1;
    }
    if ((param_4 & 2) != 0 && FUN_00b1fbf0() == 0) {
        if (((Pool*)(gspCellGame + 0x1c))->GetSafe(I(gspCellGame, 0x411c)) == 0)
            return 0;
        if (param_1 >= 0)
            return 1;
        FUN_00e7d070(g_keyDefaultFood, 3, 0.0f);
        return 1;
    }
    FUN_00e51060(param_1);
    return 1;
}

// ------------------------------------------------------------------ 0x00e7d720
// @ 0x00e7d720
void FUN_00e7d720(u8 param_1)
{
    if (param_1 == 0)
        FUN_00e7ce10(0x32, 1);
    char* ui = gspCellUI;
    void* w = ((cSPUILayout*)P(ui, 0x90))->FindWindowByID(0x5af4ae3, 1);
    if (w != 0)
        ((void(__thiscall*)(void*, int, int))(*(void***)w)[0x7c / 4])(w, 1, 0);
}

// ------------------------------------------------------------------ 0x00e7d760
// SP::sOnEatAI -- subject in ESI, first arg on the stack, the mode handle threaded in EDI.
// @ 0x00e7d760
void FUN_00e7d760(void* self, int a, int b, float f)
{
    if (I(self, 0) == I(gspCellGame, 0x411c)) {
        FUN_00e7d070(a, b, f);
        return;
    }
    char ref[4];
    FUN_00743b50(ref);
    void* ent = (void*)FUN_00e4cc40(I(self, 0x108), ref);
    int* e = (int*)FUN_00e52910((int)ent);
    switch (*e) {
    case 0x1006:
        FUN_00e79320(self, b, f);
        break;
    }
    FUN_00e82130(ref);
}

// ------------------------------------------------------------------ 0x00e7d800
// @ 0x00e7d800
void FUN_00e7d800(int hCell, int a2, int a3, char a4, float dt)
{
    char* c = (char*)((Pool*)(gspCellGame + 0x1c))->GetSafe(hCell);
    if (c == 0 || a4 == 0)
        return;
    FUN_00e7d760(c, a3, a2, dt);
    char* p = (char*)((Pool*)(gspCellGame + 0x1c))->Get(hCell);
    int e = FUN_00e4cce0(0x17);
    if (I(p, 0x108) == e) {
        e = FUN_00e4cce0(0x16);
        if (a3 == e)
            FUN_00e72430(c);
    }
}

// ------------------------------------------------------------------ 0x00e7d880
// SP::sKillCell / eaten event -- respawn the avatar predator or run the death-eaten sequence.
// @ 0x00e7d880
void FUN_00e7d880(int* a1, int* a2, int a3)
{
    char* ui = gspCellUI;
    if (*a2 == I(gspCellGame, 0x411c)) {
        char* lvl = *(char**)(gspCellGame + 0x5190);
        if (B(lvl, 0xe8) != 0) {
            I(gspCellGame, 0x411c) = *a1;
            lvl = *(char**)(gspCellGame + 0x5190);
            int old = I(lvl, 0x1c);
            I(lvl, 0x1c) = I(lvl, 0x1c) + 0x96;
            float f_new = FUN_00e4eea0(0, I(lvl, 0x1c));
            float f_old = FUN_00e4eea0(0, old);
            if (f_old != f_new) {
                F(gspCellGame, 0x5150) = f_new;
                FUN_00e7cd10();
            }
            FUN_00e780a0(*a2, 1, 0.0f, 0);
            lvl = *(char**)(gspCellGame + 0x5190);
            I(lvl, 0x10) = a1[0x3f];
            I(lvl, 0x14) = a1[0x40];
            I(lvl, 0x18) = a1[0x41];
            return;
        }
        I(ui, 0xe0) = *a1;
        I(ui, 0x54) = I(ui, 0x48);
        I(ui, 0x58) = I(ui, 0x4c);
        I(ui, 0x5c) = I(ui, 0x50);
        I(ui, 0x60) = I(ui, 0x48);
        I(ui, 0x64) = I(ui, 0x4c);
        I(ui, 0x68) = I(ui, 0x50);
    }
    B(a2, 0x114) = 1;
    if (*a1 == I(gspCellGame, 0x411c) && B(a2, 0x112) == 0) {
        FUN_00e514c0();
        char ref[4];
        FUN_00743b50(ref);
        void* ent = (void*)FUN_00e4cc40(I(a2, 0x108), ref);
        if (FUN_00e509d0(a3, ent) == 0)
            I(*(char**)(gspCellGame + 0x5190), 0x6c) += 1;
        FUN_00e82130(ref);
    }
    if (*a2 == I(gspCellGame, 0x411c))
        FUN_00e5c8e0((void*)*a1);
    if (a2[0x3f] == 0) {
        FUN_00e780a0(*a2, 1, 0.0f, 0);
        return;
    }
    u32 id = FNV1_String8("cell_death_eaten", 0x811c9dc5, 1);
    FUN_00e66840(a2, id);
    char* rec = (char*)((Pool*)(gspCellGame + 0x1c))->Get(*a2);
    float f = FUN_00e6d200(rec, 0, 9, I(rec, 0x1b0));
    int self = *a2;
    int h = ((Pool*)(gspCellGame + 0x54))->Alloc();
    char* m = (char*)((Pool*)(gspCellGame + 0x54))->Get(h);
    F(m, 0x1c) = f;
    F(m, 0x20) = f;
    I(m, 0x24) = 7;
    I(m, 0x28) = self;
    I(m, 0x2c) = 0;
    I(m, 0x30) = -1;
    I(m, 0x34) = -1;
    I(m, 0x38) = 0;
    I(m, 0x3c) = 0;
    F(m, 0x40) = 0.0f;
    F(m, 0x44) = 0.0f;
    I(m, 0x48) = I(&gCellWorldCenter, 0);
    I(m, 0x4c) = I(&gCellWorldCenter, 4);
    I(m, 0x50) = I(&gCellWorldCenter, 8);
    I(m, 0x54) = I(&gCellWorldCenter, 0);
    I(m, 0x58) = I(&gCellWorldCenter, 4);
    I(m, 0x5c) = I(&gCellWorldCenter, 8);
    I(m, 0x60) = I(g_15a7c4c, 0);
    I(m, 0x64) = I(g_15a7c4c, 4);
    I(m, 0x68) = I(g_15a7c4c, 8);
    I(m, 0x6c) = I(g_15a7c4c, 0xc);
    I(m, 0x70) = 0;
    B(m, 0x74) = 0;
    I(m, 0x78) = 0;
    I(m, 4) = 0;
    B(m, 8) = 0;
    if (I(gspCellGame, 0x411c) == *a2) {
        FUN_00b3d4d0()->setModal(1);
        B(gspCellUI, 0x936) = 1;
        I(gspCellGame, 0x5194) = h;
    }
    FUN_00e59500(*a2);
}

// ------------------------------------------------------------------ 0x00e7db80
// @ 0x00e7db80
char FUN_00e7db80(int rec)
{
    char* a = (char*)cells()->GetSafe(I(rec, 0x28));
    int h2 = I(rec, 0x2c);
    char* b = (char*)cells()->GetSafe(h2);
    if (a == 0)
        return 0;
    if (b == 0)
        return 0;
    FUN_00e7d880((int*)a, (int*)b, I(rec, 0x38));
    return 1;
}

// ------------------------------------------------------------------ 0x00e7dbd0
// @ 0x00e7dbd0
void FUN_00e7dbd0(int a1, int a2, int a3, int a4, float dt)
{
    char* p = (char*)((Pool*)(gspCellGame + 0x1c))->GetSafe(a1);
    if (p == 0)
        return;
    FUN_00e7d760(p, a4, 4, dt);
    if (P(p, 0x168) != 0) {
        FUN_00e59200(P(p, 0x168));
        P(p, 0x168) = 0;
    }
    char* q = (char*)((Pool*)(gspCellGame + 0x1c))->GetSafe(a2);
    if (q == 0)
        return;
    if (P(q, 0x168) != 0) {
        FUN_00e59200(P(q, 0x168));
        P(p, 0x168) = 0;
    }
    if ((I(gspCellGame, 0x411c) == a1 || I(gspCellGame, 0x411c) == a2) && I(q, 0x248) != 0) {
        float f = (float)I(q, 0x244) * g_1440f84;
        void* r = FUN_00e62200(I(q, 0), f);
        if (r != 0)
            F(r, 0x24) = g_half_1471064;
    }
    int* pi = (int*)(q + 0x244);
    int d = FUN_00e58980(p, q);
    *pi -= d;
    int zero = 0;
    if (*pi > 0) zero = *pi;
    *pi = zero;
    FUN_00e576f0(a1);
    FUN_00e7a770(a2, I(p, 0), I(p, 0x108), I(gspCellGame, 0x411c) == a1, 6, dt);
    float v[3];
    FUN_00e67d30(v, p, a3);
    v[0] = v[0] * g_1470f1c;
    v[1] = v[1] * g_1470f1c;
    v[2] = v[2] * g_1470f1c;
    FUN_00e72530(q, a3, v);
}
