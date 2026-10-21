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

static inline float fabsf_(float x) { return x < 0.0f ? -x : x; }

// --- external engine entry points ------------------------------------------
extern void* FUN_00fb65b0(void*, void*, void*);            // 0x00fb65b0
extern void  FUN_00fa2620(void*, void*);                   // 0x00fa2620
extern void  BoneVector_erase(void*, void*, void*);        // 0x009c69f0
extern void* EAAllocate(unsigned int, const char*, int, int, int, int); // 0x00f473a0
extern void  FUN_00fb4c90(void*);                          // 0x00fb4c90
extern void  FUN_00fb71c0(void*);                          // 0x00fb71c0 (thiscall, 1 arg)
extern void  FUN_00fb71c0_2(void*, void*);                 // 0x00fb71c0 (thiscall, 2 args)
extern void  FUN_00fb75b0(void*);                          // 0x00fb75b0 (thiscall)
extern void  FUN_00fb6fb0(void*, void*, void*, void*);     // 0x00fb6fb0
extern void  FUN_00fb7640(void*, void*);                   // 0x00fb7640
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

void TC1::QuadReset(int arg)
{
    int* self = (int*)this;
    FUN_00fb71c0_2((void*)((uint8_t*)self + 0x18c), (void*)arg);
    if (*(int*)((uint8_t*)self + 8) != 0)
        FUN_00fb75b0(self);
}

// ===========================================================================
// @ 0x00fb7920  add ribbon polygons to the quad (thiscall, ret 4)
// ===========================================================================
void TC1::QuadAddRibbonPolys(int* p)
{
    int* self = (int*)this;
    FUN_00fb6fb0((void*)*(int*)((uint8_t*)self + 0x190),
                 (void*)p[0], (void*)p[1], (void*)p);
    if (*(int*)((uint8_t*)self + 8) != 0)
        FUN_00fb7640(self, (void*)p);
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
    if (0.001f < fabsf_(*(float*)((uint8_t*)self + 0x2c) - v)) {
        *(float*)((uint8_t*)self + 0x2c) = v;
        int* o = (int*)self[0];
        ((void (*)(int*, int))*(void**)(*o + 0x48))(o, 2);
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
    if (0.001f <= fabsf_(*(float*)((uint8_t*)self + 0x18) - p)) {
        *(float*)((uint8_t*)self + 0x18) = p;
        float v = p * *(float*)0x01470f1c - *(float*)0x01485720;
        FUN_00ff03c0(v);
        int* o = (int*)self[0];
        ((void (*)(int*, int))*(void**)(*o + 0x48))(o, 10);
        SP_cTerrainSphere_Relevel((void*)self[0], 0, 1);
    }
}

// ===========================================================================
// @ 0x00fb7c70  bilinear sample into a 256x256 RGBA tile (variant A)
// ===========================================================================
void SampleTileA(uint8_t* dst, uint8_t* src, int row)
{
    const float step = *(float*)0x014911dc;
    const float one  = *(float*)0x01485720;
    uint8_t* out = dst + 0x3fc02 + row * 4;

    for (int i = 0; i < 0x100; ++i) {
        float f  = (float)i * step;
        int   fi = (int)f;
        if (f < (float)fi) --fi;
        float frac = f - (float)fi;

        int idx = fi * 0x40 + row;
        int c0 = src[idx * 4 - 0x100];
        int c1 = src[idx * 4];
        int c2 = src[idx * 4 + 1];
        int c3 = src[idx * 4 - 0xff];
        int c4 = src[idx * 4 + 2];
        int c5 = src[idx * 4 - 0xfe];

        float r = (float)c0 * frac + (float)c1 * (one - frac);
        float g = (float)c3 * (one - frac) + (float)c2 * frac;
        float b = (float)c5 * (one - frac) + (float)c4 * frac;

        out[-2] = (uint8_t)(int)r;
        out[-1] = (uint8_t)(int)g;
        out[0]  = (uint8_t)(int)b;
        out[1]  = 0;
        out += 4;
    }
}

// ===========================================================================
// @ 0x00fb7dc0  sample a tile with a different edge offset (variant B)
// ===========================================================================
void SampleTileB(uint8_t* dst, uint8_t* src, int row, int col)
{
    const float step = *(float*)0x014911dc;
    const float one  = *(float*)0x01485720;
    uint8_t* out = dst + 0x3fc00 + (row + col) * 4;

    for (int i = 0; i < 0x100; ++i) {
        float f  = (float)i * step;
        int   fi = (int)f;
        if (f < (float)fi) --fi;
        float frac = f - (float)fi;

        int idx = fi * 0x40 + col;
        out[0] = src[idx * 4];
        out[1] = (uint8_t)i;
        out[2] = 0;
        out += 4;
        (void)one; (void)frac;
    }
}

// ===========================================================================
// @ 0x00fb7f00  bilinear sample into a 256x256 tile (variant C)
// ===========================================================================
void SampleTileC(uint8_t* dst, uint8_t* src, int a, int b)
{
    const float step = *(float*)0x014911dc;
    const float one  = *(float*)0x01485720;
    uint8_t* p1 = dst + a + b * 4 + 0x3fc02;
    uint8_t* p0 = dst + a + b * 4 + 0x3fc00;

    for (int i = 0; i < 0x100; ++i) {
        float f  = (float)i * step;
        int   fi = (int)f;
        if (f < (float)fi) --fi;
        float frac = f - (float)fi;

        int idx = fi * 0x40 + b;
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
    (void)dst; (void)a; (void)b; (void)c;
}

// ===========================================================================
// @ 0x00fb8410  copy a source sub-buffer, keeping rows aligned
// ===========================================================================
void CopySubBuffer(uint8_t* dst, uint8_t* src, int a, int b, int c)
{
    (void)dst; (void)src; (void)a; (void)b; (void)c;
}
