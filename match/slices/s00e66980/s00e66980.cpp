// Slice s00e66980 -- SPGonzago/SPCellGame.obj (cell stage): cell-gfx shutdown, cell-pair
// pool/map helpers, the bomb/sound-event helpers and the effect registration tail.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell TU; no /EHsc)
#include "types.h"

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

#define I(p,o) (*(int*)((char*)(p) + (o)))
#define U(p,o) (*(u32*)((char*)(p) + (o)))
#define F(p,o) (*(float*)((char*)(p) + (o)))
#define P(p,o) (*(void**)((char*)(p) + (o)))
#define B(p,o) (*(u8*)((char*)(p) + (o)))

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------- globals
extern char*  gspCellGame;         // 0x016b3c04
extern char*  gspCellGfx;          // 0x016b3c08
extern Vec3   gCellWorldCenter;    // 0x016b3c28
extern float  g_15a7c4c[4];        // 0x015a7c4c  (0,0,0,1)
extern float  g_minus1;            // 0x013eb1bc  -1.0f
extern float  g_signmask;          // 0x013eb8b0  -0.0f
extern float  g_half;              // 0x01471064  0.5f
extern float  g_one_1485720;       // 0x01485720  1.0f
extern float  g_0p1_1488874;       // 0x01488874  0.1f
extern float  g_neg0p1_13eb964;    // 0x013eb964  -0.1f
extern float  gCellGameExtents;    // 0x016b3c88  minX,minY,minZ,maxX,maxY,maxZ
extern char   g_16b42b8[];         // 0x016b42b8  (ctor target in sShutdownGfx)

// ---------------------------------------------------------------- pools / maps
struct Pool {
    int   Begin();            // 0x00e31100
    void* Next(int* it);      // 0x00b72230, ret 4
    void* GetSafe(int h);     // 0x00b721d0, ret 4
    void* Get(int h);         // 0x00b72210, ret 4
    int   Alloc();            // 0x00b72160, ret
    void  Free(int h);        // 0x00b72260, ret 4
    void  Reset();            // 0x00b720e0
};

struct KPair { int key; int val; };
struct KeyMap {                        // at gspCellGame + 0xe0
    KPair* mpBegin;
    KPair* mpEnd;
    char   pad08[0x4018 - 8];
    u8     mbFlag;                     // +0x4018
    int    erase(KPair* key);          // 0x00e64fc0
    KPair* insertAt(KPair* pos, KPair* val);
    int*   operatorIndex(KPair* key);  // 0x00e65730
};
struct SoundMap {                      // at gspCellGfx + 0x184
    KPair* mpBegin;
    KPair* mpEnd;
    char   pad08[0x16018 - 8];
    u8     mbFlag;                     // +0x16018
    int*   operatorIndex(KPair* key);  // 0x00e65790
    KPair* insertAt(KPair* pos, KPair* val);
};

// ---------------------------------------------------------------- callees
extern "C" void  FUN_007c3ba0(void* self);                        // 0x007c3ba0 (ecx ctor)
extern "C" void  FUN_00e65ad0(void* self, int a);                 // 0x00e65ad0 (ecx) cPartGfx::Clear
extern "C" int   FUN_00e31100(void* self);                        // 0x00e31100 (ecx) pool begin
extern "C" void* FUN_0067dd90();                                  // 0x0067dd90 LightingManager
extern "C" void* FUN_0067dd80();                                  // 0x0067dd80 ModelManager
extern "C" void* FUN_0067ddd0();                                  // 0x0067ddd0 EffectsManager
extern "C" void  FUN_00e82750(void* p);                           // 0x00e82750
extern "C" void  FUN_007b1950(void* self);                        // 0x007b1950 (ecx)
extern "C" void  FUN_00e65180(void* first, void* last);           // 0x00e65180 vector erase
extern "C" void* __cdecl FUN_00b41ea0(void* first, void* last, void* key, u8 flag); // lower_bound
extern "C" void* __cdecl FUN_00e61830(void* first, void* last, void* key, u8 flag); // lower_bound
extern "C" void* __cdecl FUN_00b72230(void* self, int* it);       // (decl above via Pool)
extern "C" void* __cdecl FUN_00e65730(void* self, void* key);     // KeyMap::operator[]
extern "C" void* __cdecl FUN_00e65790(void* self, void* key);     // SoundMap::operator[]
extern "C" void* __cdecl FUN_00e65840(void* self, void* key);     // KeyMap4::operator[]
extern "C" int   FUN_00e66280(u32 id, int flag);                  // 0x00e66280
extern "C" int   FNV1_String8(const char* s, u32 seed, int one);  // 0x00932e80
extern "C" void* __cdecl operator_new(u32 size, const char* name, int, int, int, int); // 0xf473a0
extern "C" void* FUN_00e4cc40(int id, void* out);                 // 0x00e4cc40 -> 0x00e823a0
extern "C" void* FUN_00e4ce40(void* out);                         // 0x00e4ce40 LayerCatalog_ApplyA
extern "C" void  __fastcall FUN_00743b50(void* self);             // 0x00743b50 (ecx init)
extern "C" void  __fastcall FUN_00e82130(void* self);             // 0x00e82130 (ecx release)
extern "C" void* FUN_00e58c50(void* h);                           // 0x00e58c50 follow handle -> object
extern "C" int   FUN_00e66e50(int a, int b);
extern "C" int   FUN_00e66dd0(int a, int b);
extern "C" void  FUN_00e66f30(int a, int b, void* pos, float p4, float p5, float p6,
                              float p7, float p8);
extern "C" void  FUN_00e61b90(int flag, int zero, void* pos, int* key); // custom ABI (eax/edx)
extern "C" void* CreateEffectSafe(void* world, u32 id, int flags, void* out); // 0x00628450
extern "C" void  FUN_00e84150(int a, int b, void* out);           // 0x00e84150
extern "C" void  FUN_00e63480(void* a, int b, void* out);         // 0x00e63480 sPartIntersectTarget
extern "C" void  FUN_0041cb40(void* self, void* src);             // 0x0041cb40 Matrix33 ctor (ecx)
extern "C" void  FUN_00e65a00(int* param);                        // 0x00e65a00
extern "C" void  FUN_00e65480(u32 a, u32 b);                      // 0x00e65480 map erase pair

// forward decls
void FUN_00e671c0(void* cell);                                    // SP::sBomb_Start

typedef void (__thiscall *PFN_i)(void*, int);
#define VT(p) (*(void***)(p))
static inline void VCall_v(void* p, int slot) { ((void(__thiscall*)(void*))VT(p)[slot / 4])(p); }
static inline void VCall_i(void* p, int slot, int a) { ((PFN_i)VT(p)[slot / 4])(p, a); }

static inline void ReleaseSlot(char* base, int off) {
    void* p = *(void**)(base + off);
    if (p) { *(void**)(base + off) = 0; VCall_v(p, 4); }
}

struct Pair16 { u16 lo, hi; };
static inline int MakeKey(int a, int b) {
    Pair16 k;
    if (a < b) { k.hi = (u16)a; k.lo = (u16)b; }
    else       { k.hi = (u16)b; k.lo = (u16)a; }
    return *(int*)&k;
}

// ------------------------------------------------------------------ 0x00e66980
// SP::sShutdownGfx -- tear down the cell renderer: drain the part pool, destroy the
// object vector and the per-slot gfx objects, then release every managed sub-system.
// @ 0x00e66980
void FUN_00e66980(void)
{
    FUN_007c3ba0(g_16b42b8);
    char* g = gspCellGfx;
    int it = ((Pool*)(g + 0x168))->Begin();
    void* o = ((Pool*)(g + 0x168))->Next(&it);
    while (o != 0) {
        FUN_00e65ad0(o, 1);            // SP::cPartGfx::Clear(1)
        g = gspCellGfx;
        o = ((Pool*)(g + 0x168))->Next(&it);
    }
    ((Pool*)(g + 0x168))->Reset();
    g = gspCellGfx;
    int n = (I(g, 0x161e0) - I(g, 0x161dc)) / 0x74;
    for (int i = 0; i < n; ++i) {
        void** slot = (void**)(I(g, 0x161dc) + i * 0x74 + 0x70);
        void* p = *slot;
        VCall_i(p, 0xc, 1);
        p = *slot;
        if (p) { *slot = 0; VCall_v(p, 4); }
    }
    FUN_00e65180(P(g, 0x161dc), P(g, 0x161e0));
    for (int off = 0x5c; off < 0x15c; off += 4) {
        void** slot = (void**)(g + off);
        if (*slot != 0) {
            VCall_i(*slot, 0xc, 1);
            void* p = *slot;
            if (p) { *slot = 0; VCall_v(p, 4); }
        }
    }
    VCall_i(FUN_0067dd90(), 0x20, 0x4a4d97f);
    ReleaseSlot(g, 0x161a0);
    VCall_i(FUN_0067ddd0(), 0x50, 0x1010000);
    ReleaseSlot(g, 0x161b4);
    FUN_00e82750(P(g, 0x161b0));
    ReleaseSlot(g, 0x161b0);
    VCall_v(P(g, 0x161c4), 0x20);
    ReleaseSlot(g, 0x161c4);
    VCall_i(FUN_0067ddd0(), 0x50, 0x1010011);
    ReleaseSlot(g, 0x161bc);
    FUN_00e82750(P(g, 0x161b8));
    ReleaseSlot(g, 0x161b8);
    VCall_i(FUN_0067dd80(), 0x18, 0x1010010);
    ReleaseSlot(g, 0x161c0);
    VCall_i(FUN_0067dd80(), 0x18, 0x1010015);
    ReleaseSlot(g, 0x161a8);
    VCall_i(FUN_0067ddd0(), 0x50, 0x1010016);
    ReleaseSlot(g, 0x161ac);
    FUN_00e82750(P(g, 0x161a4));
    ReleaseSlot(g, 0x161a4);
    VCall_v(P(g, 0x161d0), 0x20);
    ReleaseSlot(g, 0x161d0);
    VCall_i(FUN_0067ddd0(), 0x50, 0x1010021);
    ReleaseSlot(g, 0x161c8);
    VCall_i(FUN_0067dd80(), 0x18, 0x1010020);
    ReleaseSlot(g, 0x161cc);
    VCall_i(FUN_0067ddd0(), 0x50, 0x1010031);
    ReleaseSlot(g, 0x161d4);
    FUN_00e82750(P(g, 0x161d8));
    ReleaseSlot(g, 0x161d8);
    if (I(g, 0x3c) != 0) {
        FUN_007b1950(P(g, 0x3c));
        ReleaseSlot(g, 0x3c);
    }
}

// ------------------------------------------------------------------ 0x00e66dd0
// Allocate a cell-pair record and claim its slot in the pair map.  Returns the record.
// @ 0x00e66dd0
int FUN_00e66dd0(int a, int b)
{
    int h = ((Pool*)(gspCellGame + 0xc4))->Alloc();
    char* obj = (char*)((Pool*)(gspCellGame + 0xc4))->Get(h);
    *(int*)(obj + 4) = a;
    *(int*)(obj + 8) = b;
    *(float*)(obj + 0x24) = 0.0f;
    int key = MakeKey(a, b);
    int* r = ((KeyMap*)(gspCellGame + 0xe0))->operatorIndex((KPair*)&key);
    *r = h;
    return (int)obj;
}

// ------------------------------------------------------------------ 0x00e66e50
// Look up the cell-pair record for (a,b); return the record iff it matches, else erase it.
// @ 0x00e66e50
int FUN_00e66e50(int a, int b)
{
    int key = MakeKey(a, b);
    KeyMap* map = (KeyMap*)(gspCellGame + 0xe0);
    KPair* e = (KPair*)FUN_00b41ea0(map->mpBegin, map->mpEnd, &key, map->mbFlag);
    if (e == map->mpEnd || key < e->key) e = map->mpEnd;
    if (e != map->mpEnd) {
        int* slot = ((KeyMap*)(gspCellGame + 0xe0))->operatorIndex((KPair*)&key);
        char* obj = (char*)((Pool*)(gspCellGame + 0xc4))->GetSafe(*slot);
        if (obj != 0 && *(int*)(obj + 4) == a && *(int*)(obj + 8) == b)
            return (int)obj;
        ((KeyMap*)(gspCellGame + 0xe0))->erase((KPair*)&key);
    }
    return 0;
}

// ------------------------------------------------------------------ 0x00e66f30
// Register/refresh a collision sound for the cell pair (a,b) with the given world
// position (pos), direction vector (p4,p5,p6) and two scalars (p7,p8).
// @ 0x00e66f30
void FUN_00e66f30(int a, int b, void* pos, float p4, float p5, float p6, float p7, float p8)
{
    if ((u32)a < (u32)b) {
        p4 = p4 * g_minus1;
        p5 = p5 * g_minus1;
        p6 = p6 * g_minus1;
    }
    int lo = a < b ? a : b;
    int hi = a < b ? b : a;
    char* esi = (char*)FUN_00e58c50(&hi);
    char* edi = (char*)FUN_00e58c50(&lo);
    int* rec = (int*)FUN_00e66e50(hi, lo);
    float dot = (F(esi, 0x50) - F(edi, 0x50)) * p8
              + (F(esi, 0x54) - F(edi, 0x54)) * p7
              + (F(esi, 0x4c) - F(edi, 0x4c)) * p6;
    if (dot > 0.0f) {
        if (rec != 0) {
            ((Pool*)(gspCellGame + 0xc4))->Free(*rec);
            FUN_00e65480(hi, lo);
            return;
        }
    } else {
        if (rec == 0)
            rec = (int*)FUN_00e66dd0(hi, lo);
        float s0 = F(esi, 0xbc);
        float s1 = F(edi, 0xbc);
        rec[3] = I(pos, 0);
        rec[4] = I(pos, 4);
        rec[5] = I(pos, 8);
        rec[6] = *(int*)&p4;
        rec[7] = *(int*)&p5;
        rec[8] = *(int*)&p6;
        int v = I(gspCellGame, 0x5160);
        float inv = 1.0f / (s1 + s0);
        rec[0xc] = *(int*)&inv;
        rec[0xd] = *(int*)&inv;
        rec[0xf] = v;
        float n7 = -p7;
        rec[9] = *(int*)&n7;
        float adj = n7 + g_0p1_1488874;
        float pick = (0.0f <= adj) ? 0.0f : adj;
        float res = (pick / p8) * g_neg0p1_13eb964;
        rec[0xe] = *(int*)&res;
    }
}

// ------------------------------------------------------------------ 0x00e67100
// Original: cell A on the stack, cell B in EDI.  Gate the pair and forward to 0xe66f30.
// @ 0x00e67100
void FUN_00e67100(int hA, int hB, void* pos, float p2, float p3, float p4, float p5, float p6)
{
    char* A = (char*)((Pool*)(gspCellGame + 0x1c))->GetSafe(hA);
    char* B = (char*)((Pool*)(gspCellGame + 0x1c))->GetSafe(hB);
    if (A == 0) return;
    if (B == 0) return;
    if (B(A, 0x179) == 1) return;
    if (B(B, 0x179) == 1) return;
    if (I(A, 0x36c) == hB) return;
    if (I(B, 0x36c) == hA) return;
    if (I(A, 0x184) == hB) return;
    if (I(B, 0x184) == hA) return;
    if (B(A, 0x114) == 1) return;
    if (B(B, 0x114) == 1) return;
    FUN_00e66f30((int)B, (int)A, pos, p2, p3, p4, p5, p6);
}

// ------------------------------------------------------------------ 0x00e671c0
// SP::sBomb_Start -- spawn the bomb object for a cell and post its type-0x10 message.
// @ 0x00e671c0
void FUN_00e671c0(void* cellp)
{
    char* cell = (char*)cellp;
    char* obj = (char*)operator_new(0x202c, "Simulator/Cell/Bomb", 0, 0, 0, 0);
    if (obj != 0) {
        *(void**)(obj + 0x20) = obj + 0x28;
        *(void**)(obj + 0x14) = obj + 0x28;
        *(void**)(obj + 0x10) = obj + 0x28;
        *(void**)(obj + 0x18) = obj + 0x28 + 0x2000;
    } else {
        obj = 0;
    }
    *(int*)(obj + 0) = I(cell, 0x35c);
    *(int*)(obj + 4) = I(cell, 0x4c);
    *(int*)(obj + 8) = I(cell, 0x50);
    *(int*)(obj + 0xc) = I(cell, 0x54);
    int* slot = (int*)FUN_00e65840(obj + 0x10, cell);
    *slot = I(cell, 0);
    int h = ((Pool*)(gspCellGame + 0x54))->Alloc();
    char* m = (char*)((Pool*)(gspCellGame + 0x54))->Get(h);
    *(int*)(m + 0x28) = I(cell, 0);
    *(float*)(m + 0x1c) = g_half;
    *(float*)(m + 0x20) = g_half;
    *(int*)(m + 0x24) = 0x10;
    *(int*)(m + 0x2c) = 0;
    *(int*)(m + 0x30) = -1;
    *(int*)(m + 0x34) = -1;
    *(int*)(m + 0x38) = 0;
    *(int*)(m + 0x3c) = 0;
    *(float*)(m + 0x40) = 0.0f;
    *(float*)(m + 0x44) = 0.0f;
    char* src = cell + 0x4c;
    float* sp = (float*)src;
    if (sp == 0) sp = &gCellWorldCenter.x;
    *(int*)(m + 0x48) = I(sp, 0);
    *(int*)(m + 0x4c) = I(sp, 4);
    *(int*)(m + 0x50) = I(sp, 8);
    *(int*)(m + 0x54) = I(&gCellWorldCenter, 0);
    *(int*)(m + 0x58) = I(&gCellWorldCenter, 4);
    *(int*)(m + 0x5c) = I(&gCellWorldCenter, 8);
    *(int*)(m + 0x60) = I(g_15a7c4c, 0);
    *(int*)(m + 0x64) = I(g_15a7c4c, 4);
    *(int*)(m + 0x68) = I(g_15a7c4c, 8);
    *(int*)(m + 0x6c) = I(g_15a7c4c, 0xc);
    *(void**)(m + 0x70) = obj;
    *(u8*)(m + 0x74) = 0;
    *(int*)(m + 0x78) = 0;
    *(int*)(m + 4) = 0;
    *(u8*)(m + 8) = 0;
    int key = 0x62a981ec;
    int flag = (I(cell, 0x35c) != I(gspCellGame, 0x40fc));
    FUN_00e61b90(flag, 0, src, &key);
}

// ------------------------------------------------------------------ 0x00e67330
// SP::sAddSoundEvent -- record a collision sound for cell pair (a,b) at position pos.
// @ 0x00e67330
void FUN_00e67330(int a, int b, float* pos, float radius, int soundId)
{
    if (!(pos[0] >= F(&gCellGameExtents, 0x00) && pos[0] <= F(&gCellGameExtents, 0x0c) &&
          pos[1] >= F(&gCellGameExtents, 0x04) && pos[1] <= F(&gCellGameExtents, 0x10) &&
          pos[2] >= F(&gCellGameExtents, 0x08) && pos[2] <= F(&gCellGameExtents, 0x14)))
        return;
    char ref[4];
    FUN_00743b50(ref);
    char* info = (char*)FUN_00e4ce40(ref);
    if (radius < F(info, 0x6c)) {
        FUN_00e82130(ref);
        return;
    }
    int key = MakeKey(a, b);
    SoundMap* map = (SoundMap*)(gspCellGfx + 0x184);
    KPair* e = (KPair*)FUN_00e61830(map->mpBegin, map->mpEnd, &key, map->mbFlag);
    if (e == map->mpEnd || key < e->key) e = map->mpEnd;
    if (e != *(KPair**)(gspCellGfx + 0x188)) {
        int* rec = (int*)((SoundMap*)(gspCellGfx + 0x184))->operatorIndex((KPair*)&key);
        rec[3] = soundId;
        rec[4] = I(pos, 0);
        rec[5] = I(pos, 4);
        rec[6] = I(pos, 8);
        FUN_00e82130(ref);
        return;
    }
    int* rec = (int*)((SoundMap*)(gspCellGfx + 0x184))->operatorIndex((KPair*)&key);
    rec[1] = b;
    rec[2] = soundId;
    rec[3] = soundId;
    rec[0] = a;
    *(u8*)((char*)rec + 0x1c) = radius < F(info, 0x70) ? 1 : 0;
    rec[4] = I(pos, 0);
    rec[5] = I(pos, 4);
    rec[6] = I(pos, 8);
    rec[9] = 0;
    rec[8] = 0;
    FUN_00e82130(ref);
}

// ------------------------------------------------------------------ 0x00e67510
// Create/refresh (or destroy) the "cell_eyegoo_flow" effect on a cell part.
// @ 0x00e67510
struct Mat3 { float m[9]; void Assign(const void* src); };  // 0x0041cb40
struct EffDesc {
    u16   a;        // +0x00
    u16   b;        // +0x02
    Vec3  pos;      // +0x04
    float scale;    // +0x10
    Mat3  rot;      // +0x14
};
void FUN_00e67510(int world, int* ppEffect, int a3, int a4, int a5, int a6, char create)
{
    if (create != 0) {
        if (*ppEffect == 0) {
            u32 id = FNV1_String8("cell_eyegoo_flow", 0x811c9dc5, 1);
            CreateEffectSafe((void*)world, id, 0, ppEffect);
            void* e = (void*)*ppEffect;
            ((PFN_i)VT(e)[8 / 4])(e, 0);
        }
        EffDesc d;
        d.a = 0;
        d.b = 0;
        d.pos.x = gCellWorldCenter.x;
        d.pos.y = gCellWorldCenter.y;
        d.pos.z = gCellWorldCenter.z;
        d.scale = g_one_1485720;
        d.rot.Assign((void*)0x16b3dac);
        FUN_00e84150(a5, a6, &d);
        FUN_00e63480((void*)*ppEffect, a3, &d);
        return;
    }
    if (*ppEffect != 0)
        FUN_00e65a00(ppEffect);
}

// ------------------------------------------------------------------ 0x00e675f0
// @ 0x00e675f0
void FUN_00e675f0(void)
{
    char* c = (char*)((Pool*)(gspCellGame + 0x1c))->GetSafe(I(gspCellGame, 0x411c));
    if (c != 0)
        FUN_00e671c0(c);
}

// ------------------------------------------------------------------ 0x00e67610
// @ 0x00e67610
void FUN_00e67610(int id)
{
    char ref[4];
    FUN_00743b50(ref);
    int* list = (int*)FUN_00e4cc40(id, ref);
    for (int i = 0; i < *list; ++i)
        FUN_00e66280(*(int*)(list[1] + i * 0x1c), 0);
    FUN_00e82130(ref);
}

// ------------------------------------------------------------------ 0x00e67670
// @ 0x00e67670
void FUN_00e67670(void)
{
    u32 h;
    h = FNV1_String8("cell_dof_distort_blind", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_dof_distort_blind", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_background_color", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_propulsionJet", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_propulsionCilia", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_propulsionFlagella", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_attack_electrical_charged", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_attack_electrical_charged_multiple", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_call_avatar", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_call_mate", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("EDT_currency_text_cell_sellItem", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("EDT_currency_text_cell_buyItem", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_egg_L0_autohatch", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_attack_electrical_secondaryBeam", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_attack_electrical_primaryBeam", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_death_continuous", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_death_oneshot_small", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_death_oneshot_large", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_death_oneshot", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_death_break", 0x811c9dc5, 1); FUN_00e66280(h, 0);
    h = FNV1_String8("cell_death_eaten", 0x811c9dc5, 1); FUN_00e66280(h, 0);
}
