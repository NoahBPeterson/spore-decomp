// Slice s00fb7720 -- SP::cTerrainSphereQuad (terrain sphere quad-tree) helpers.
//
// Reconstructed from annotated disassembly + Ghidra decompiles
// (work/match/scratch_s00fb7720_cards.txt). MSVC 2008 /O2, x86.
//
// Layout notes (from the disassembly):
//   +0x008..+0x014 : four child cTerrainSphereQuad* slots
//   +0x02c         : float split/height parameter
//   +0x18c         : eastl::vector (3 dwords)
//   +0x1a0         : eastl::vector (3 dwords)
//   +0x600..       : float/byte parameters
//   +0x628, +0x7c0, +0x940, +0xac0 : 0x194/0x180/0x180/0x180-byte sub-buffers

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

#include <math.h>
static inline float fabsf_impl(float x) { return fabs(x); }

// --- external engine entry points ------------------------------------------
extern void* FUN_00fb65b0(void*, void*, void*);            // 0x00fb65b0
extern void  FUN_00fa2620(void*, void*);                   // 0x00fa2620
extern void  BoneVector_erase(void*, void*, void*);        // 0x009c69f0
extern void* EAAllocate(unsigned int, const char*, int, int, int, int); // 0x00f473a0
extern void  FUN_00fb4c90(void*);                          // 0x00fb4c90
extern void  FUN_00fb71c0(void*);                          // 0x00fb71c0 (thiscall, 1 arg)
extern void  FUN_00fb71c0_2(void*, void*);                 // 0x00fb71c0 (thiscall, 2 args)
struct TCVec { void Set(int arg); void Release(); void ReleaseArg(void* p); };  // 0x00fb71c0 / 0x00fb75b0 / 0x00fb7640
extern void  FUN_00fb75b0(void*);                          // 0x00fb75b0 (thiscall)
extern void  FUN_00fb6fb0(void*, void*, void*, void*);     // 0x00fb6fb0
extern void  FUN_00fb7640(void*, void*);                   // 0x00fb7640
struct TCVec2 { void Add(void* a, void* b, void* c, void* d); }; // 0x00fb6fb0
struct TC1Self { void Append(void* p); void Release(); void Set2(void* arg); };
extern void* operator_delete(void*);                       // 0x00f47380
extern void  eastl_vector_insert(void*, void*, void*, int); // 0x011e0744
extern void  FUN_00fb79b0_impl(uint8_t*);                  // defined below (thiscall)
extern void  operator_new_arr(void*, int, int);            // 0x011e073e
extern void  FUN_00ff03c0(float);                          // 0x00ff03c0
extern void  SP_cTerrainSphere_Relevel(void*, int, int);   // 0x00fa43e0
extern void  FUN_00fb8410(void*, int, int, int, int);      // 0x00fb8410

// ===========================================================================
// @ 0x00fb7720  destroy/free the quad's vectors and recurse into the 4 children
// ===========================================================================
void __fastcall QuadFree(int* self)
{
    int  a = *(int*)((uint8_t*)self + 0x18c);
    int  b = *(int*)((uint8_t*)self + 0x190);
    int* vec = (int*)((uint8_t*)self + 0x18c);

    void* r = FUN_00fb65b0((void*)b, (void*)b, (void*)a);
    FUN_00fa2620(r, (void*)b);

    int n = (int)(((long long)(b - a) * -0x78787879LL) >> 32);
    vec[1] += ((n >> 7) - (n >> 31)) * 0x110;

    BoneVector_erase(
        *(void**)((uint8_t*)self + 0x1a0),
        *(void**)((uint8_t*)self + 0x1a4),
        (void*)0);

    for (int i = 0; i < 4; ++i) {
        int child = *(int*)((uint8_t*)self + 8 + i * 4);
        if (child != 0)
            QuadFree((int*)child);
    }
}

// ===========================================================================
// @ 0x00fb77b0  build the quad's 4 children (subdividing the sphere region)
// ===========================================================================
void __fastcall QuadSubdivide(int* self)
{
    float half = *(float*)0x01471064;                       // 0.5f
    float px = (*(float*)((uint8_t*)self + 0x20) + *(float*)((uint8_t*)self + 0x28)) * half;
    float py = (*(float*)((uint8_t*)self + 0x24) + *(float*)((uint8_t*)self + 0x2c)) * half;

    int* slot = (int*)((uint8_t*)self + 8);
    for (int i = 0; i < 4; ++i) {
        uint8_t* o = (uint8_t*)EAAllocate(
            0x1b8, "Terrain/SphereQuad/cTerrainSphereQuad", 0, 0, 0, 0);
        if (o != 0) {
            FUN_00fb4c90(o);
        } else {
            o = 0;
        }
        slot[i] = (int)o;

        float x0 = *(float*)((uint8_t*)self + 0x20);
        float y0 = *(float*)((uint8_t*)self + 0x24);
        float dx = px - x0;
        float dy = py - y0;

        float lx = x0, rx = px;
        float ly = y0, ry = py;
        if (i & 1) { lx = x0 + dx; rx = x0; }
        if (i & 2) { ly = y0 + dy; ry = y0; }
        (void)rx; (void)ry;
    }
}

// ===========================================================================
// @ 0x00fb78f0  reset the quad (thiscall, ret 4)
// ===========================================================================
struct TC1 { void QuadReset(int arg); void QuadSetSplit(float p);
             void QuadSetPair(int* p); void QuadSetHeight(float p);
             void QuadAddRibbonPolys(int* p); };

// Vtable view of the object referenced by *this (slot +0x48 == virtual #18).
struct VNode {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();  virtual void v7();
    virtual void v8();  virtual void v9();  virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(int arg);
};
// 0x00ff03c0 -- __thiscall(float), receiver is the quad's 2nd sub-object.
struct QuadSub { void SetValue(float v); };
// 0x00fa43e0 -- SP::cTerrainSphere::Relevel, __thiscall(int, int).
struct QuadSphere { void Relevel(int a, int b); };

void TC1::QuadReset(int arg)
{
    int* self = (int*)this;
    ((TCVec*)((uint8_t*)self + 0x18c))->Set(arg);
    if (*(int*)((uint8_t*)self + 8) != 0)
        ((TCVec*)self)->Release();
}

// ===========================================================================
// @ 0x00fb7920  add ribbon polygons to the quad (thiscall, ret 4)
// ===========================================================================
void TC1::QuadAddRibbonPolys(int* p)
{
    int* self = (int*)this;
    ((TCVec2*)((uint8_t*)self + 0x18c))->Add(
        (void*)*(int*)((uint8_t*)self + 0x190),
        (void*)p[0], (void*)p[1], (void*)p);
    if (*(int*)((uint8_t*)self + 8) != 0)
        ((TCVec*)self)->ReleaseArg((void*)p);
}

// ===========================================================================
// @ 0x00fb7960  free each 0x2c-stride element in [first,last)
// ===========================================================================
void __stdcall FreeQuadRange(uint8_t* first, uint8_t* last)
{
    for (; first < last; first += 0x2c) {
        int p0 = *(int*)(first + 0x10);
        if (*(int*)(first + 0x18) - p0 > 1 && p0 != 0)
            operator_delete((void*)p0);

        int q0 = *(int*)(first + 0);
        if (*(int*)(first + 8) - q0 > 1 && q0 != 0)
            operator_delete((void*)q0);
    }
}

// ===========================================================================
// @ 0x00fb79b0  free every element of the pointer vector and truncate it
// ===========================================================================
void FUN_00fb79b0_impl(uint8_t* self)
{
    int* v = (int*)self;
    int  n = (v[3] - v[2]) >> 2;
    for (int i = 0; i < n; ++i) {
        uint8_t* e = *(uint8_t**)(v[2] + i * 4);
        if (e == 0)
            continue;
        FreeQuadRange(e + 0x10, *(uint8_t**)(e + 0x14));
        uint8_t* p = *(uint8_t**)(e + 0x10);
        if (p != 0 && *(int*)(p - 4) != 0)
            operator_delete(p);
        uint8_t* q = *(uint8_t**)e;
        if (*(int*)(e + 8) - (int)q > 1 && q != 0)
            operator_delete(q);
        operator_delete(e);
    }
    int used = (v[3] - v[2]) >> 2;
    eastl_vector_insert((void*)self, (void*)v[3], (void*)v[3], 0);
    (void)used;
    v[3] -= ((v[3] - v[2]) >> 2) * 4;
}
// ===========================================================================
// @ 0x00fb7a60  release the quad element vector then free its storage
// ===========================================================================
void __fastcall QuadReleaseVec(int** self)
{
    if (self[0] != 0) {
        void* o = (void*)self[0];
        ((void (*)(void*))*(void**)(*(int*)o + 0xc))(o);
        int* o2 = self[0];
        if (o2 != 0) {
            self[0] = 0;
            ((void (*)(int*))*(void**)(*o2 + 4))(o2);
        }
    }
    FUN_00fb79b0_impl((uint8_t*)(self + 1));
}

// ===========================================================================
// @ 0x00fb7a90  initialise the quad's scalar parameters and sub-buffers
// ===========================================================================
void __fastcall QuadInitParams(int* self)
{
    uint8_t* s = (uint8_t*)self;
    *(float*)(s + 0x600) = *(float*)0x013eb1bc;             // -1.0f
    *(float*)(s + 0x604) = *(float*)0x01471064;             // 0.5f
    *(float*)(s + 0x608) = 0.0f;
    *(float*)(s + 0x60c) = *(float*)0x01485720;             // 1.0f
    *(uint8_t*)(s + 0x5ad) = 0;
    *(uint8_t*)(s + 0x7bc) = 0;
    operator_new_arr(s + 0x628, 0, 0x194);
    operator_new_arr(s + 0x7c0, 0, 0x180);
    operator_new_arr(s + 0x940, 0, 0x180);
    operator_new_arr(s + 0xac0, 0, 0x180);
}

// ===========================================================================
// @ 0x00fb7b30  set the quad's split parameter (thiscall, ret 4)
// ===========================================================================
void TC1::QuadSetSplit(float p)
{
    int* self = (int*)this;
    float v = (1.0f - p) - *(float*)((uint8_t*)self + 0x624);
    if (0.001f < fabs(*(float*)((uint8_t*)self + 0x2c) - v)) {
        *(float*)((uint8_t*)self + 0x2c) = v;
        ((VNode*)((void*)self[0]))->v18(2);
    }
}

// ===========================================================================
// @ 0x00fb7b90  return 1 - quad[0x2c]
// ===========================================================================
float __fastcall QuadOneMinusSplit(int self)
{
    return 1.0f - *(float*)((uint8_t*)self + 0x2c);
}

// ===========================================================================
// @ 0x00fb7bd0  store a 2-float pair at +0x610 (thiscall, ret 4)
// ===========================================================================
void TC1::QuadSetPair(int* p)
{
    int* self = (int*)this;
    *(int*)((uint8_t*)self + 0x610) = p[0];
    *(int*)((uint8_t*)self + 0x614) = p[1];
}

// ===========================================================================
// @ 0x00fb7bf0  set the quad's height parameter (thiscall, ret 4)
// ===========================================================================
void TC1::QuadSetHeight(float p)
{
    int* self = (int*)this;
    if (0.001f <= fabs(*(float*)((uint8_t*)self + 0x18) - p)) {
        *(float*)((uint8_t*)self + 0x18) = p;
        p = p * *(float*)0x01470f1c;
        p = p - *(float*)0x01485720;
        ((QuadSub*)(*(void**)((uint8_t*)self + 4)))->SetValue(p);
        ((VNode*)((void*)self[0]))->v18(10);
        ((QuadSphere*)((void*)self[0]))->Relevel(0, 1);
    }
}

// ===========================================================================
// @ 0x00fb7c70  bilinear sample into a 256x256 RGBA tile (variant A)
// ===========================================================================
void SampleTileA(uint8_t* dst, uint8_t* src, int row)
{
    int iVar11 = 0;
    uint8_t* puVar10 = dst + 0x3fc02;

    do {
        float f = (float)iVar11 * *(float*)0x014911dc;
        int   fi = (int)f;
        if (f < (float)fi) --fi;
        int iVar8 = row + (0x3f - fi) * 0x40;

        uint8_t b1 = src[iVar8 * 4 - 0x100];
        uint8_t b2 = src[iVar8 * 4];
        float frac = f - (float)fi;
        uint8_t b3 = src[iVar8 * 4 + 1];
        float om = *(float*)0x01485720 - frac;
        uint8_t b4 = src[iVar8 * 4 - 0xff];
        uint8_t b5 = src[iVar8 * 4 + 2];
        uint8_t b6 = src[iVar8 * 4 - 0xfe];

        int      n = 0x100;
        uint8_t* puVar9 = puVar10;
        do {
            puVar9[-2] = (uint8_t)(int)((float)b1 * frac + (float)b2 * om);
            puVar9[-1] = (uint8_t)(int)((float)b3 * om + (float)b4 * frac);
            puVar9[0]  = (uint8_t)(int)((float)b5 * om + (float)b6 * frac);
            puVar9[1]  = 0;
            puVar9 += 4;
            --n;
        } while (n != 0);

        ++iVar11;
        puVar10 -= 0x400;
    } while (iVar11 < 0x100);
}

// ===========================================================================
// @ 0x00fb7dc0  sample a tile with a different edge offset (variant B)
// ===========================================================================
void SampleTileB(uint8_t* dst, uint8_t* src, int row, int col)
{
    int iVar9 = 0;
    uint8_t* puVar8 = dst + 0x3fc02 + col * 4;
    uint8_t* puVar7 = dst + 0x3fc00 + col * 4;

    do {
        float f = (float)iVar9 * *(float*)0x014911dc;
        int   fi = (int)f;
        if (f < (float)fi) --fi;
        int iVar6 = fi * 0x40 + row;
        float frac = f - (float)fi;

        uint8_t b1 = src[1 + iVar6 * 4];
        float   om = *(float*)0x01485720 - frac;
        uint8_t b2 = src[0x101 + iVar6 * 4];
        uint8_t b3 = src[2 + iVar6 * 4];
        uint8_t b4 = src[0x102 + iVar6 * 4];

        *puVar7     = (uint8_t)(int)((float)src[0x100 + iVar6 * 4] * frac +
                                     (float)src[iVar6 * 4] * om);
        puVar8[-1]  = (uint8_t)(int)((float)b1 * om + (float)b2 * frac);
        *puVar8     = (uint8_t)(int)((float)b3 * om + (float)b4 * frac);
        puVar8[1]   = 0;

        ++iVar9;
        puVar7 -= 0x400;
        puVar8 -= 0x400;
    } while (iVar9 < 0x100);
}

// ===========================================================================
// @ 0x00fb7f00  bilinear sample into a 256x256 tile (variant C)
// ===========================================================================
void SampleTileC(uint8_t* dst, uint8_t* src, int a, int b)
{
    uint8_t* p1 = dst + 0x3fc02 + b * 4;
    uint8_t* p0 = dst + 0x3fc00 + b * 4;

    for (int i = 0; i < 0x100; ++i) {
        float f  = (float)i * *(float*)0x014911dc;
        int   fi = (int)f;
        if (f < (float)fi) --fi;
        float frac = f - (float)fi;
        float one = *(float*)0x01485720;

        int idx = fi * 0x40 + a;
        int c0 = src[idx * 4 + 0x100];
        int c1 = src[idx * 4];
        int c2 = src[idx * 4 + 1];
        int c3 = src[idx * 4 + 0x101];
        int c4 = src[idx * 4 + 2];
        int c5 = src[idx * 4 + 0x102];
        int c6 = src[idx * 4 + 3];
        int c7 = src[idx * 4 + 0x103];

        float r = (float)c0 * frac + (float)c1 * (one - frac);
        float g = (float)c3 * (one - frac) + (float)c2 * frac;
        float bl= (float)c5 * (one - frac) + (float)c4 * frac;
        float al= (float)c7 * (one - frac) + (float)c6 * frac;

        p0[0]   = (uint8_t)(int)r;
        p1[-1]  = (uint8_t)(int)g;
        p1[0]   = (uint8_t)(int)bl;
        p1[1]   = (uint8_t)(int)al;
        p0 -= 0x400;
        p1 -= 0x400;
    }
}

// ===========================================================================
// @ 0x00fb8060  replicate rows into the 3x3 neighbourhood of a tile
// ===========================================================================
void ReplicateRows(uint8_t* dst, int col)
{
    uint8_t* p1 = dst + col * 4 + 0x3fc04;
    int      n  = 0xfc;
    uint8_t* p0 = dst + col * 4 + 0x3ec02;

    if (n <= 0)
        return;
    do {
        uint8_t* s = p0 - 2;
        uint8_t* d = p1 + 2;
        uint8_t* e = p0;
        int      k = n;
        uint8_t* t = p1;
        do {
            *t = *s;
            d[-1] = e[-1];
            *d = *e;
            d[1] = e[1];
            s -= 0x400;
            t -= 0x400;
            e -= 0x400;
            d -= 0x400;
        } while (--k != 0);
        p1 += 4;
        n  -= 4;
        p0 -= 0x1000;
    } while (n > 0);
}

// ===========================================================================
// @ 0x00fb8100  build the full quad tile set (large)
// ===========================================================================
void BuildQuadTiles(uint8_t* dst, int a, int b, int c)
{
    // Faithful port of the retail lerp/unroll loop (param_1 = base buffer,
    // param_2 = row base index).  The retail body is hand-unrolled by 4.
    uint8_t* base = dst;
    int row = a;
    (void)b; (void)c;

    int local_8 = 0;
    int local_c = 0xfe00;
    unsigned uVar2 = 1;
    int iVar3;
    do {
        // --- (uVar2 - 1) ---
        iVar3 = 0x40 - ((int)(uVar2 - 1) >> 2);
        int iVar5 = 4 - (int)((uVar2 - 1) & 3);
        int iVar4 = (iVar3 - local_8) + row;
        uint8_t* pb = (uint8_t*)(base + 0x400 + (local_c + iVar3 + row) * 4);
        int t = 4 - iVar5;
        *pb = (uint8_t)(((unsigned)*(uint8_t*)(base + 0x3fbfc + iVar4 * 4) * iVar5 +
                         (unsigned)*pb * t) >> 2);
        *(uint8_t*)(base + 0x3fc01 + iVar4 * 4) = (uint8_t)(
            ((unsigned)*(uint8_t*)(base + 0x3fbfd + iVar4 * 4) * iVar5 +
             (unsigned)*(uint8_t*)(base + 0x3fc01 + iVar4 * 4) * t) >> 2);
        pb = (uint8_t*)(base + 0x3fc02 + iVar4 * 4);
        *pb = (uint8_t)(((unsigned)*(uint8_t*)(base + 0x3fbfe + iVar4 * 4) * iVar5 +
                         (unsigned)*pb * t) >> 2);

        // --- (uVar2) ---
        iVar3 = 0x40 - ((int)uVar2 >> 2);
        iVar5 = 4 - (int)(uVar2 & 3);
        iVar4 = (iVar3 - local_8) + row;
        pb = (uint8_t*)(base + (local_c + iVar3 + row) * 4);
        t = 4 - iVar5;
        *pb = (uint8_t)(((unsigned)*(uint8_t*)(base + 0x3f7fc + iVar4 * 4) * iVar5 +
                         (unsigned)*pb * t) >> 2);
        *(uint8_t*)(base + 0x3f801 + iVar4 * 4) = (uint8_t)(
            ((unsigned)*(uint8_t*)(base + 0x3f7fd + iVar4 * 4) * iVar5 +
             (unsigned)*(uint8_t*)(base + 0x3f801 + iVar4 * 4) * t) >> 2);
        pb = (uint8_t*)(base + 0x3f802 + iVar4 * 4);
        *pb = (uint8_t)(((unsigned)*(uint8_t*)(base + 0x3f7fe + iVar4 * 4) * iVar5 +
                         (unsigned)*pb * t) >> 2);

        // --- (uVar2 + 1) ---
        iVar3 = 0x40 - ((int)(uVar2 + 1) >> 2);
        iVar5 = 4 - (int)((uVar2 + 1) & 3);
        iVar4 = (iVar3 - local_8) + row;
        pb = (uint8_t*)(base - 0x400 + (local_c + iVar3 + row) * 4);
        t = 4 - iVar5;
        *pb = (uint8_t)(((unsigned)*(uint8_t*)(base + 0x3f3fc + iVar4 * 4) * iVar5 +
                         (unsigned)*pb * t) >> 2);
        *(uint8_t*)(base + 0x3f401 + iVar4 * 4) = (uint8_t)(
            ((unsigned)*(uint8_t*)(base + 0x3f3fd + iVar4 * 4) * iVar5 +
             (unsigned)*(uint8_t*)(base + 0x3f401 + iVar4 * 4) * t) >> 2);
        pb = (uint8_t*)(base + 0x3f402 + iVar4 * 4);
        *pb = (uint8_t)(((unsigned)*(uint8_t*)(base + 0x3f3fe + iVar4 * 4) * iVar5 +
                         (unsigned)*pb * t) >> 2);

        // --- (uVar2 + 2) ---
        iVar3 = 0x40 - ((int)(uVar2 + 2) >> 2);
        int iVar6 = 4 - (int)((uVar2 - 2) & 3);
        iVar4 = (iVar3 - local_8) + row;
        t = 4 - iVar6;
        pb = (uint8_t*)(base - 0x800 + (local_c + iVar3 + row) * 4);
        *pb = (uint8_t)(((unsigned)*(uint8_t*)(base + 0x3effc + iVar4 * 4) * iVar6 +
                         (unsigned)*pb * t) >> 2);
        *(uint8_t*)(base + 0x3f001 + iVar4 * 4) = (uint8_t)(
            ((unsigned)*(uint8_t*)(base + 0x3effd + iVar4 * 4) * iVar6 +
             (unsigned)*(uint8_t*)(base + 0x3f001 + iVar4 * 4) * t) >> 2);
        pb = (uint8_t*)(base + 0x3f002 + iVar4 * 4);
        *pb = (uint8_t)(((unsigned)*(uint8_t*)(base + 0x3effe + iVar4 * 4) * iVar6 +
                         (unsigned)*pb * t) >> 2);

        local_c = local_c - 0x400;
        local_8 = local_8 + 0x400;
        iVar3 = (int)(uVar2 + 3);
        uVar2 = uVar2 + 4;
    } while (iVar3 < 0x100);
}

// ===========================================================================
// @ 0x00fb8410  copy a source sub-buffer, keeping rows aligned
// ===========================================================================
void CopySubBuffer(uint8_t* dst, uint8_t* src, int a, int b, int c)
{
    // Faithful port of the retail stride-4 row copy/expansion (param_1 = base
    // buffer, param_2 = starting row index).
    uint8_t* base = dst;
    int startRow = a;
    (void)src; (void)b; (void)c;

    int local_8 = startRow;
    int iVar4 = 1;
    int local_4 = 4;
    int iVar3 = 0xfb00;
    do {
        local_8 = local_8 - 0x400;
        if (local_4 < 0x100) {
            uint8_t* puVar2 = (uint8_t*)(base + 0x3fc02 + (local_8 - iVar4) * 4);
            uint8_t* puVar1 = (uint8_t*)(base + 0x3fc01 + startRow * 4);
            uint8_t* puVar6 = (uint8_t*)(base + ((iVar3 - iVar4) + startRow) * 4);
            int iVar5 = 0x100 - local_4;
            do {
                puVar6[0]  = puVar1[-1];
                puVar2[-1] = puVar1[0];
                puVar2[0]  = puVar1[1];
                puVar2[1]  = puVar1[2];
                puVar6 = (uint8_t*)((uint8_t*)puVar6 - 0x400);
                puVar1 = (uint8_t*)((uint8_t*)puVar1 - 0x400);
                puVar2 = (uint8_t*)((uint8_t*)puVar2 - 0x400);
                iVar5 = iVar5 - 1;
            } while (iVar5 != 0);
        }
        local_4 = local_4 + 4;
        iVar3 = iVar3 - 0x400;
        iVar4 = iVar4 + 1;
    } while (-0x100 < iVar3);
}
