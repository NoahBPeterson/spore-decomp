// Slice s006ee1f0 -- SP::cEffectsRenderer ctor/dtor and dispatch helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE (SSE float code, EH frames, no cookie).
//
// Retail layout (`this` = cEffectsRenderer, a 0x388-byte multiply-derived
// object).  Only the fields this slice touches are named; gaps are pads.
//   +0x00..+0x1c  seven vtable pointers (re-based twice during the ctor)
//   +0x40,+0x48,+0x5c,+0x70,+0x104,+0x174,+0x188,+0x19c,+0x1b8,+0x1cc,
//   +0x1e0,+0x224,+0x238,+0x35c,+0x360,+0x364  sub-objects / vectors
#include "types.h"

extern "C" void* memcpy(void* dst, const void* src, unsigned int n);

// 0x006e7020 scaled-matrix writer (local 13 floats + out).
static void FUN_006e7020(float f0, float f1, float f2, float f3, float f4, float f5,
                         float f6, float f7, float f8, float f9, float f10,
                         float f11, float f12, float* out);
static void FUN_006e7020(float f0, float f1, float f2, float f3, float f4, float f5,
                         float f6, float f7, float f8, float f9, float f10,
                         float f11, float f12, float* out)
{
    out[0] = f4 * f3;  out[1] = f5 * f3;
    out[4] = f7 * f3;  out[2] = f6 * f3;  out[5] = f8 * f3;  out[6] = f9 * f3;
    out[8] = f10 * f3; out[9] = f11 * f3; out[10] = f12 * f3;
    out[12] = f0; out[13] = f1; out[14] = f2;
}

// --------------------------------------------------------------------------
// Minimal interface stubs (vtable-only types used through base pointers).
// --------------------------------------------------------------------------
struct IRefObj {                       // refcount at slot 1 (vtable+4)
    virtual void v0();
    virtual int  Release();            // slot 1
};
struct IWeakObj {                      // weak-release at slot 2 (vtable+8)
    virtual void v0();
    virtual void v1();
    virtual void Release();            // slot 2
};

struct cTextRenderer {                 // SP::cTextRenderer at +0x204
    char pad[0x100];
    cTextRenderer();                   // 0x7a8390
    ~cTextRenderer();                  // 0x7a8790
};

// Generic scalar vector<T> (eastl sp_vector_allocator).  4 dwords.
template<class T>
struct evec {
    T*   mpBegin;      // +0x00
    T*   mpEnd;        // +0x04
    T*   mpCapacity;   // +0x08
    char mAllocator[4];// +0x0c
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    void DoInsertValue(T* pos, const T& v);   // 0x4558a0
};

// --------------------------------------------------------------------------
// cEffectsRenderer retail view.
// --------------------------------------------------------------------------
class cEffectsRenderer {
public:
    // --- base vptrs (-0x00..-0x1c) ---
    void* vptr00;                     // +0x000
    void* vptr04;                     // +0x004
    void* vptr08;                     // +0x008
    void* vptr0c;                     // +0x00c
    uint32_t f10;                     // +0x010
    void* vptr14;                     // +0x014
    void* vptr18;                     // +0x018
    void* vptr1c;                     // +0x01c
    uint32_t f20, f24, f28, f2c, f30, f34;   // +0x020..+0x037
    IRefObj* p40;                     // +0x040
    uint32_t f44, f48, f4c, f50;      // +0x044..+0x053
    uint32_t f54;                     // +0x054
    uint32_t f58;                     // +0x058
    void*   p5c;                      // +0x05c
    uint32_t f60, f64;                // +0x060,+0x064
    uint32_t pad68;                   // +0x068
    void*   p70;                      // +0x070
    uint32_t f74, f78;                // +0x074,+0x078
    uint8_t  pad7c[0x104 - 0x7c];

    uint8_t  mVec104[0x50];           // +0x104  EH vector: 4 x 0x14 bytes

    uint32_t pad154_0;                // +0x154
    uint8_t  b158;                    // +0x158
    uint8_t  b159;                    // +0x159
    uint8_t  pad15a[2];
    uint32_t n15c;                    // +0x15c = 3000
    uint32_t n160;                    // +0x160 = 10
    uint32_t n164;                    // +0x164
    int32_t  n168;                    // +0x168 = -1
    void*    p16c;                    // +0x16c (vtable)
    uint32_t f170, f174, f178, f17c;  // +0x170..+0x17f
    uint32_t pad180;                  // +0x180
    uint32_t f184;                    // +0x184
    uint32_t f188, f18c, f190;        // +0x188..+0x193
    uint32_t pad194;                  // +0x194
    uint32_t f198;                    // +0x198
    uint32_t f19c, f1a0, f1a4;        // +0x19c..+0x1a7
    uint32_t pad1a8[2];               // +0x1a8,+0x1ac
    uint32_t f1b0, f1b4, f1b8, f1bc, f1c0;   // +0x1b0..+0x1c3
    uint32_t pad1c4, pad1c8;
    uint32_t f1cc, f1d0, f1d4;        // +0x1cc..+0x1d7
    uint32_t pad1d8[2];               // +0x1d8,+0x1dc
    IRefObj* p1e0;                    // +0x1e0
    uint8_t  b1e4;                    // +0x1e4
    uint8_t  b1e5;                    // +0x1e5
    uint8_t  pad1e6[2];
    float    f1e8, f1ec, f1f0;        // +0x1e8..+0x1f3
    uint8_t  b1f4;                    // +0x1f4
    uint8_t  pad1f5[3];
    uint32_t f1f8, f1fc, f200;        // +0x1f8..+0x203

    cTextRenderer mText;              // +0x204

    void*    p224;                    // +0x224 (vector<inner> begin)
    uint32_t f228;                    // +0x228
    uint32_t f22c;                    // +0x22c
    uint32_t pad230[2];               // +0x230,+0x234
    evec<unsigned int> mVec238;       // +0x238

    uint32_t pad244[2];               // +0x244,+0x248
    uint32_t f24c, f250, f254, f258, f25c;  // +0x24c..+0x25f
    uint8_t  mFrustumCull[0x100];     // +0x260 (cFrustumCull, >= 0x100 bytes)

    uint8_t  pad360_0[0x350 - 0x360 + 0x360];
    float    f350;                    // +0x350 = 0.5f
    float    f354;                    // +0x354 = 200.0f
    void*    p358;                    // +0x358
    IWeakObj* p35c;                   // +0x35c
    IWeakObj* p360;                   // +0x360
    IWeakObj* p364;                   // +0x364
    uint8_t  b368;                    // +0x368
    uint8_t  b369;                    // +0x369
    uint8_t  pad36a[2];
    uint32_t f36c, f370, f374, f378, f37c, f380, f384;  // +0x36c..+0x387

    cEffectsRenderer();                                            // 0x6ee1f0
    ~cEffectsRenderer();                                           // 0x6ee4f0
    void AddActive(unsigned int id);                               // 0x6ee940
    void DispatchWithAdditionalMaterial(void* ctx, int mat, int extra);  // 0x6ee6f0
};

// --- a 2-byte-element vector<bool> used by 6eea80 --------------------------
struct vbvec {
    unsigned short* mpBegin;      // +0x00
    unsigned short* mpEnd;        // +0x04
    unsigned short* mpCapacity;   // +0x08
    void resize(unsigned int n);  // 0x6eea80
};

// --- a 0x70-stride record vector (cTextureParticleSet vector) --------------
struct Elem70 { uint8_t b[0x70]; };
struct Vector70 {
    Elem70* mpBegin;      // +0x00
    Elem70* mpEnd;        // +0x04
    Elem70* mpCapacity;   // +0x08
    // 0x6eeb60: insert `count` (always 1 here) copies of `val` at `pos`.
    void insert(Elem70* pos, const Elem70* val);
};
extern "C" void   FUN_006e9230(Elem70* src, const Elem70* val);   // copy-construct
extern "C" Elem70* FUN_006e93d0(Elem70* first, Elem70* last, Elem70* dst);  // uninit copy
extern "C" void   FUN_006eba30(Elem70* first, Elem70* last, Elem70* dst);   // destroy range
extern "C" void   FUN_006ebf10(Elem70* first, Elem70* last, Elem70* dst);   // move-backward
extern "C" Elem70* FUN_006ebb80(Elem70* dst, const Elem70* val);            // assign

// --- free callees ----------------------------------------------------------
extern "C" void  __stdcall _eh_vector_ctor(void* p, unsigned sz, unsigned n,
                                           void (__stdcall* ctor)(void*),
                                           void (__stdcall* dtor)(void*));   // ??_L
extern "C" void  __stdcall _eh_vector_dtor(void* p, unsigned sz, unsigned n,
                                           void (__stdcall* dtor)(void*));   // ??_M
extern "C" void  __cdecl operator_delete(void* p);                          // 0xf47380
extern "C" void  FUN_006eca50(void* first, void* last);                     // vector<inner> dt
extern "C" void  FUN_006ec1f0(void* self);                                  // +0x48 subobject
extern "C" void  FUN_006ebcb0(void* self);                                  // +0x1b8 subobject
extern "C" void  FUN_006ebc50(void* self);                                  // +0x174 subobject
extern "C" void  FUN_006e9990(void* self);                                  // subobject at +0x1c
extern "C" void  FUN_006ec730(void* out);                                   // temp build into [esp+4]
extern "C" void  FUN_006ecfc0(void* dst, void* src);                        // temp assign
extern "C" void  FUN_006ecb40(void* end, unsigned extra, const void* val);  // vector<bool> grow

// dispatch-loop callees
struct cViewer { char pad[0x100]; bool Update(); };            // 0x7c4fd0
extern "C" bool  FUN_007c4fd0(cViewer* v);                                 // cViewer::Update
extern "C" void  FUN_007c3c10(cViewer* v);                                 // cViewer::PostUpdate
extern "C" void  FUN_006ee140(void* model);                                // model Update
struct cFrustumCull { char pad[0x100]; };
extern "C" char  FUN_00700120(void* self, const void* sphere, void* planes, unsigned flags);
extern "C" void  FUN_006e95a0(const void* sphere, void* out);              // cSphere from +0x50
extern "C" void  pushShaderDataNull();                                     // 0x777bf0
extern "C" void  FUN_00538000(void* dst, const void* src);                 // cSPTransform ctor
extern "C" void  FUN_007789d0(void* state);                                // ShaderDataState_Push
extern "C" void  FUN_00777ae0(unsigned id, void* shader, int a);           // shader push
extern "C" void  FUN_005291f0(void* matrix, unsigned mode);                // EffectsDispatch
extern "C" void  FUN_006e7110(void* model, void* extra);                   // dispatch (no mat)
extern "C" void  FUN_006e73d0(void* model, void* mat, void* extra);        // dispatch (mat)
extern "C" void  shaderPop();                                              // 0x777c10
extern "C" void* operator_new_graphics(unsigned n, const char* name,
                                       int a, int b, const char* file, int line);

// globals
extern "C" uint32_t g_sAppProperties;         // 0x15fd918 (SP::_sAppProperties)
extern "C" uint32_t g_softStateDirty;         // 0x16f9528
extern "C" uint32_t g_shaderColorA;           // 0x16f96a8
extern "C" uint32_t g_shaderColorB;           // 0x16f96ac
extern "C" uint32_t g_shaderColorC;           // 0x16f96b0
extern "C" uint32_t g_shaderColorD;          // 0x16f96b4

// Logo/window helper used by dtor tail.
extern "C" void  FUN_007a8390(void);          // cTextRenderer::cTextRenderer (this=ecx)
extern "C" void  FUN_007a8790(void);          // cTextRenderer::~cTextRenderer (this=ecx)

// ==========================================================================
// 0x006ee1f0 -- cEffectsRenderer::cEffectsRenderer
// ==========================================================================
// @ 0x006ee1f0
cEffectsRenderer::cEffectsRenderer()
{
    // First vtable pass (bases laid out in derived order, pre-icons).
    vptr04 = (void*)0x144934c;
    vptr08 = (void*)0x140af70;
    f10    = 0;
    vptr0c = (void*)0x13ef094;
    vptr14 = (void*)0x13eb384;
    vptr18 = (void*)0x13f1ab0;
    vptr1c = (void*)0x140af90;
    f20 = f24 = f28 = f2c = f30 = f34 = 0;

    // Second (final) vtable pass.
    vptr00 = (void*)0x140b1f0;
    vptr04 = (void*)0x140b1e0;
    vptr08 = (void*)0x140b1d8;
    vptr0c = (void*)0x140b1d4;
    vptr14 = (void*)0x140b1c4;
    vptr18 = (void*)0x140b1b4;
    vptr1c = (void*)0x140b190;

    p40 = 0;
    f44 = 0;
    f48 = 0;
    f4c = 0;
    f50 = 0;
    f54 = 0;
    f58 = 0;
    p5c = 0;
    f60 = 0;
    f64 = 0;
    p70 = 0;
    f74 = 0;
    f78 = 0;

    // EH vector at +0x104: 4 elements of 0x14 bytes.
    _eh_vector_ctor(mVec104, 0x14, 4, (void(__stdcall*)(void*))0x6e5790,
                    (void(__stdcall*)(void*))0x7a41a0);

    pad154_0 = 0;
    b158 = 0;
    b159 = 1;
    n15c = 3000;
    n160 = 10;
    n164 = 0;
    n168 = -1;
    p16c = (void*)0x140af78;
    f170 = f174 = f178 = f17c = 0;
    f188 = f18c = f190 = 0;
    f19c = f1a0 = f1a4 = 0;
    f1b0 = f1b4 = f1b8 = f1bc = f1c0 = 0;
    f1cc = f1d0 = f1d4 = 0;
    p1e0 = 0;
    b1e4 = 0;
    b1e5 = 0;
    f1e8 = 0.0f;
    f1ec = 0.0f;
    f1f0 = 0.0f;
    b1f4 = 0;
    f1f8 = f1fc = f200 = 0;

    mText = cTextRenderer();

    p224 = 0;
    f228 = 0;
    f22c = 0;
    mVec238.mpBegin = 0;
    mVec238.mpEnd = 0;
    mVec238.mpCapacity = 0;

    f350 = 0.5f;
    f24c = f250 = f254 = f258 = f25c = 0;
    f354 = 200.0f;

    p35c = 0;
    p360 = 0;
    p364 = 0;
    b368 = 0;
    b369 = 0;
    f36c = f370 = f374 = f378 = f37c = f380 = f384 = 0;
}

// ==========================================================================
// 0x006ee4f0 -- cEffectsRenderer::~cEffectsRenderer
// ==========================================================================
// @ 0x006ee4f0
cEffectsRenderer::~cEffectsRenderer()
{
    // First vtable pass (destruction order).
    vptr00 = (void*)0x140b1f0;
    vptr04 = (void*)0x140b1e0;
    vptr08 = (void*)0x140b1d8;
    vptr0c = (void*)0x140b1d4;
    vptr14 = (void*)0x140b1c4;
    vptr18 = (void*)0x140b1b4;
    vptr1c = (void*)0x140b190;

    if (p364) p364->Release();                 // weak release? (vtable+8)
    if (p360) p360->Release();

    if (mVec238.mpBegin && *(uint32_t*)((char*)mVec238.mpBegin - 4) != 0)
        operator_delete(mVec238.mpBegin);

    FUN_006eca50((void*)f228, p224);
    if (p224 && *(uint32_t*)((char*)p224 - 4) != 0)
        operator_delete(p224);

    FUN_007a8790();                            // ~cTextRenderer on &mText (this=ecx)

    if (p1e0) p1e0->Release();                 // vtable+4

    if (f1cc && *(uint32_t*)(f1cc - 4) != 0)
        operator_delete((void*)f1cc);

    FUN_006ebcb0(&f1b8);
    if (f19c && *(uint32_t*)(f19c - 4) != 0)
        operator_delete((void*)f19c);
    if (f188 && *(uint32_t*)(f188 - 4) != 0)
        operator_delete((void*)f188);

    FUN_006ebc50(&f174);

    _eh_vector_dtor(mVec104, 0x14, 4, (void(__stdcall*)(void*))0x7a41a0);

    if (p70 && *(uint32_t*)((char*)p70 - 4) != 0)
        operator_delete(p70);
    if (p5c && *(uint32_t*)((char*)p5c - 4) != 0)
        operator_delete(p5c);

    FUN_006ec1f0(&f48);

    if (p40) p40->Release();                   // vtable+4

    FUN_006e9990(&vptr1c);

    // Final vtable re-base to most-derived bases.
    vptr18 = (void*)0x13eb938;
    vptr14 = (void*)0x13eb394;
    vptr0c = (void*)0x13ef094;
}

// ==========================================================================
// 0x006ee940 -- cEffectsRenderer::AddActive(unsigned id)
// ==========================================================================
// @ 0x006ee940
void cEffectsRenderer::AddActive(unsigned int id)
{
    // temp 0xa0-byte scratch built at [esp+8], then released.
    uint8_t scratch[0xa0];
    FUN_006ec730(scratch);
    FUN_006ecfc0(scratch, &id);                 // scratch.assign(ptr id)

    // destroy scratch phases (mirrors the EH cleanup in the original)
    uint32_t* end = *(uint32_t**)(scratch + 0x10);
    uint32_t* begin = *(uint32_t**)(scratch + 0x08);
    int diff = (int)((char*)end - (char*)begin) & 0xfffffffe;
    if (diff > 2 && begin != 0 && begin != *(uint32_t**)(scratch + 0x18))
        operator_delete(begin);

    // append id (duplicates allowed) to the +0x238 vector.
    if (mVec238.mpEnd < (unsigned int*)mVec238.mpCapacity) {
        unsigned int* slot = mVec238.mpEnd;
        mVec238.mpEnd = slot + 1;
        if (slot)
            *slot = id;
    } else {
        mVec238.DoInsertValue(mVec238.mpEnd, id);
    }
}

// ==========================================================================
// 0x006ee6f0 -- SP::cEffectsModel::DispatchWithAdditionalMaterial
// ==========================================================================
// @ 0x006ee6f0
void cEffectsRenderer::DispatchWithAdditionalMaterial(void* ctx, int mat, int extra)
{
    cViewer* viewer = *(cViewer**)ctx;
    if (!FUN_007c4fd0(viewer))
        return;

    int count = (int)((f1bc - f1b8) / 0x68);
    if (count <= 0) {
        FUN_007c3c10(viewer);
        return;
    }

    int off = 0;
    do {
        uint8_t* rec = (uint8_t*)f1b8 + off;
        void* model = *(void**)rec;
        if (model != 0) {
            FUN_006ee140(model);
            if (*(uint8_t*)(rec + 0x50) != 0 &&
                *(float*)(*(uint32_t*)(g_sAppProperties + 0x3c) + 0xe0) <
                    *(float*)(rec + 0x10)) {
                // source sphere (6 floats at model+0x50)
                float sphere[6];
                uint8_t* m = (uint8_t*)model;
                sphere[0] = *(float*)(m + 0x50);
                sphere[1] = *(float*)(m + 0x54);
                sphere[2] = *(float*)(m + 0x58);
                sphere[3] = *(float*)(m + 0x5c);
                sphere[4] = *(float*)(m + 0x60);
                sphere[5] = *(float*)(m + 0x64);

                float xform[3];               // FUN_006e95a0(rec+0x18) -> 3 floats
                FUN_006e95a0(rec + 0x18, xform);

                float query[6];
                query[0] = sphere[3];
                query[1] = sphere[4];
                query[2] = sphere[5];
                query[3] = sphere[0];
                query[4] = sphere[1];
                query[5] = sphere[2];

                char vis = FUN_00700120(mFrustumCull, xform, query, 0x200);
                if ((vis & 0x40) == 0) {
                    pushShaderDataNull();

                    float color[4];
                    color[0] = *(float*)(rec + 0x04);
                    color[1] = *(float*)(rec + 0x08);
                    color[2] = *(float*)(rec + 0x0c);
                    color[3] = *(float*)(rec + 0x10);

                    float transform[0x38 / 4];
                    FUN_00538000(transform, rec + 0x18);

                    int outMat[0x10];
                    FUN_006e7020(*(float*)&transform[0], *(float*)&transform[1],
                                 *(float*)&transform[2], *(float*)&transform[3],
                                 *(float*)&transform[4], *(float*)&transform[5],
                                 *(float*)&transform[6], *(float*)&transform[7],
                                 *(float*)&transform[8], *(float*)&transform[9],
                                 *(float*)&transform[10], *(float*)&transform[11],
                                 *(float*)&transform[12], (float*)outMat);

                    if (*(void**)(rec + 0x58) != 0)
                        FUN_007789d0(*(void**)(rec + 0x58));
                    if (*(void**)(rec + 0x5c) != 0)
                        FUN_00777ae0(0x219, *(void**)*(void**)(rec + 0x5c), 0);

                    FUN_005291f0(outMat, 2);

                    g_softStateDirty |= 0x10;
                    g_shaderColorA = *(uint32_t*)(&color[0]);
                    g_shaderColorB = *(uint32_t*)(&color[1]);
                    g_shaderColorC = *(uint32_t*)(&color[2]);
                    g_shaderColorD = *(uint32_t*)(&color[3]);

                    if (*(void**)(rec + 0x54) != 0)
                        FUN_006e73d0(model, *(void**)(rec + 0x54), ctx);
                    else
                        FUN_006e7110(model, ctx);

                    shaderPop();
                }
            }
        }
        off += 0x68;
    } while (--count != 0);

    FUN_007c3c10(viewer);
}

// ==========================================================================
// 0x006eea80 -- vector<bool,fixed_vector_allocator>::resize
// (value type is 2 bytes wide; grow path copies and re-links the tail)
// ==========================================================================
// @ 0x006eea80
void vbvec::resize(unsigned int n)
{
    unsigned short* cur = mpEnd;
    unsigned int sz = (unsigned int)((char*)cur - (char*)mpBegin) >> 1;
    if (n > sz) {
        unsigned int extra = n - sz;
        unsigned short zero = 0;
        FUN_006ecb40(cur, extra, &zero);
        return;
    }
    // Shrink: the original memmoves zero bytes at the cut point (a no-op for
    // the 2-byte element) and then re-links the end pointer.
    unsigned short* dst = mpBegin + n;
    memcpy(dst, cur, 0);
    unsigned int removed = (unsigned int)((char*)cur - (char*)dst) >> 1;
    mpEnd = cur - removed;
}

// ==========================================================================
// 0x006eeb60 -- eastl vector<cTextureParticleSet>::insert (stride 0x70)
// ==========================================================================
// @ 0x006eeb60
void Vector70::insert(Elem70* pos, const Elem70* val)
{
    if (mpEnd != mpCapacity) {
        Elem70* slot = pos;
        if (pos < val || pos >= mpEnd)
            slot = pos + 1;                    // encoded as +0x70 bytes

        Elem70* last = mpEnd;
        // copy-construct the tail element, then move the range up by one.
        if (last != 0)
            FUN_006e9230(last - 1, (const Elem70*)(last - 1));   // ctor last from last
        FUN_006ebf10((Elem70*)val, last - 1, last);
        FUN_006ebb80(slot, val);
        mpEnd = (Elem70*)((char*)mpEnd + 0x70);
        return;
    }

    // --- reallocate: new capacity = 2 * size (or 1) ---
    unsigned int count = (unsigned int)((char*)mpEnd - (char*)mpBegin) / 0x70;
    unsigned int cap = count ? count * 2 : 1;

    Elem70* raw;
    if (cap != 0)
        raw = (Elem70*)operator_new_graphics(cap * 0x70, "Graphics", 0, 0,
                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                 0xd1);
    else
        raw = 0;

    Elem70* first = FUN_006e93d0(mpBegin, pos, raw);
    FUN_006eba30(mpBegin, pos, raw);
    Elem70* mid = first;
    if (mid != 0)
        FUN_006e9230(mid, val);

    Elem70* tail = (Elem70*)FUN_006e93d0(pos, mpEnd, mid + 1);
    FUN_006eba30(pos, mpEnd, mid + 1);

    if (mpBegin && *(uint32_t*)((char*)mpBegin - 4) != 0)
        operator_delete(mpBegin);

    mpCapacity = (Elem70*)((char*)raw + cap * 0x70);
    mpBegin = raw;
    mpEnd = tail;
}
