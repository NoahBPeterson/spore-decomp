// Slice s007c1c10 — DXT/bump-map helpers in the texture subsystem.
// /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"

// ---------------------------------------------------------------------------
// @ 0x007c2730  anonymous-namespace::expand_2_32
// Expand a packed 2-bit-per-channel value into 4 ARGB dwords per iteration.
// ---------------------------------------------------------------------------
void __stdcall expand_2_32(uint32_t* dst, int stride, uint32_t src, uint32_t* table)
{
    for (int i = 4; i != 0; --i) {
        dst[0] = table[src & 3];
        dst[1] = *(uint32_t*)((char*)table + (src & 0xc));
        src >>= 4;
        dst[2] = table[src & 3];
        dst[3] = *(uint32_t*)((char*)table + (src & 0xc));
        src >>= 4;
        dst = (uint32_t*)((char*)dst + stride);
    }
}

// ---------------------------------------------------------------------------
// @ 0x007c24a0  SP::cBumpMapTable::cBumpMapTable(this, float)
// ---------------------------------------------------------------------------
struct F2I { float f; int i; };

struct cBumpMapTable {
    float fastnorm[0x4001];
    cBumpMapTable(float param);
};

cBumpMapTable::cBumpMapTable(float param)
{
    float k = 1020.0f / param;
    fastnorm[0] = k;
    float kk = k * k;
    for (int i = 0; i < 0x4000; ++i) {
        float v = (float)i * 64.0f + kk;
        F2I u;
        u.f = v;
        u.i = 0x5f400000 - (u.i >> 1);
        float w = u.f;
        fastnorm[i + 1] = ((1.5f - (w * w) * (v * 0.5f)) * w) * 127.5f;
    }
}

// ===========================================================================
// @ 0x007c1c10  SP::cThumbnailManager bake-info / normal-spec splat setup.
// Resets the render-target flags, loads the viewer's camera transform from the
// app, then initialises the splat job at +0x10e4 with the splatter viewer. If
// the second / third target rects are valid it also builds a 4-pass blur
// filter chain for jobs +0x10e8 (viewer +0x7c) and +0x10ec (viewer +0x80).
// Finally installs a callback object on job 0 and queues its layer.
// ===========================================================================
#include <intrin.h>
#include <string.h>

namespace SPL {

struct RectID { int mPageID; int mAllocID; };

inline void* AllocGraphics(size_t size, const char* name, int a, int b, int c, int d);
}  // namespace SPL

void* SPL_AllocGraphics(size_t size, const char* name, int a, int b, int c, int d);   // 0x00F473A0 operator new
inline void* operator new(size_t size, const char* name, int a, int b, int c, int d)
{
    return SPL_AllocGraphics(size, name, a, b, c, d);
}

namespace SPL {

struct Mat3 { float m[9]; void Assign(const void* src); };      // 0x0041CB40 (thiscall, ret 4)
extern const float kMat3Src[9];                                  // 0x01635788
extern const float kTransPos[3];                                 // 0x01635648
extern const float kOne;                                         // 0x01485720

struct Xform {
    unsigned short mFlags;
    unsigned short mCount;
    float mPos[3];
    float mScale;
    Mat3 mBasis;
    Xform()
    {
        mFlags = 0;
        mCount = 0;
        mPos[0] = kTransPos[0];
        mPos[1] = kTransPos[1];
        mPos[2] = kTransPos[2];
        mScale = kOne;
        mBasis.Assign(kMat3Src);
    }
};

struct cViewer {
    void SetBasis(Xform* x);                                    // 0x007C4D00
    void SetRenderMode(int mode, int flags);                    // 0x007C3CE0
};

struct XformSource { void GetXform(Xform* out); };              // 0x007C40F0 (thiscall, ret 4)

struct IScene {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06();
    virtual XformSource* GetTransform();                        // +0x1C
    virtual void s08(); virtual void s09(); virtual void s10();
    virtual void SetMode(int mode);                             // +0x2C
};
struct IApp {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
    virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
    virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
    virtual IScene* GetScene();                                 // +0x50
};
IApp* App();                                                    // 0x0067DD10

struct IRenderTargetManager {
    virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03(); virtual void r04();
    virtual void r05(); virtual void r06(); virtual void r07(); virtual void r08();
    virtual void SetFlag(int on);                               // +0x24
    virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13(); virtual void r14();
    virtual void r15(); virtual void r16(); virtual void r17(); virtual void r18(); virtual void r19();
    virtual void r20(); virtual void r21(); virtual void r22(); virtual void r23(); virtual void r24();
    virtual void r25(); virtual void r26(); virtual void r27(); virtual void r28(); virtual void r29();
    virtual void r30(); virtual void r31(); virtual void r32(); virtual void r33(); virtual void r34();
    virtual void r35(); virtual void r36(); virtual void r37(); virtual void r38(); virtual void r39();
    virtual void r40(); virtual void r41(); virtual void r42(); virtual void r43(); virtual void r44();
    virtual void r45(); virtual void r46(); virtual void r47(); virtual void r48(); virtual void r49();
    virtual void r50(); virtual void r51(); virtual void r52(); virtual void r53(); virtual void r54();
    virtual void r55();
    virtual void FreeRect(RectID* rect, bool b);                // +0xE0
};
IRenderTargetManager* RenderTargetManager();                    // 0x0067DD40

struct LayerInfo {
    int mFlags;                                                 // +0x00
    int mField04;                                               // +0x04
    bool mbField08;                                             // +0x08
    int mField0C;                                               // +0x0C
    int mField10;                                               // +0x10
    unsigned int mDoneMessageID;                                // +0x14
    void* mpDoneMessage;                                        // +0x18
    int mField1C, mField20, mField24, mField28;                 // +0x1C
    LayerInfo()
    {
        mFlags = 1;
        mField04 = 0;
        mbField08 = true;
        mField0C = 0;
        mField10 = 0;
        mDoneMessageID = 0;
        mpDoneMessage = 0;
        mField1C = 0;
        mField20 = 0;
        mField24 = 0;
        mField28 = 0;
    }
};

struct ILayerManager {
    virtual void l00(); virtual void l01(); virtual void l02(); virtual void l03(); virtual void l04();
    virtual void l05(); virtual void l06(); virtual void l07(); virtual void l08(); virtual void l09();
    virtual void l10(); virtual void l11(); virtual void l12(); virtual void l13(); virtual void l14();
    virtual void l15(); virtual void l16(); virtual void l17(); virtual void l18(); virtual void l19();
    virtual void l20(); virtual void l21(); virtual void l22(); virtual void l23(); virtual void l24();
    virtual void l25(); virtual void l26(); virtual void l27(); virtual void l28(); virtual void l29();
    virtual void AddLayer(void* layer);                         // +0x78
};
ILayerManager* LayerManager();                                  // 0x0067DD50

class cJobPostFilter {
public:
    virtual int AddRef();                                       // +0x00
    virtual int Release();                                      // +0x04
    cJobPostFilter();                                           // 0x007B8550
    void Init(int materialID, const RectID* src, const RectID* dst, int raster);   // 0x007B9510
    char pad04[0xe4 - 0x04];
};
struct FilterPtr {
    cJobPostFilter* mpObject;
    FilterPtr(cJobPostFilter* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~FilterPtr() { if (mpObject) mpObject->Release(); }
};

// Local filter chain (0x34 bytes): ILayer vptr at +0, RefCountVTemplate<int> at +4.
struct cILayer { virtual int AddRef(); virtual int Release(); virtual void l2(); };
struct RefCountVTemplateInt {
    virtual void rc0();
    int mnRefCount;                                             // +0x08
    RefCountVTemplateInt() : mnRefCount(0) {}
};
struct cFilterChainJob : cILayer, RefCountVTemplateInt {
    void* mFilters[3];                                          // +0x0C
    int mAllocator;                                             // +0x18
    int pad1c;
    bool mbActive;                                              // +0x20
    int pad24;
    int mFilterIndex;                                           // +0x28
    int pad2c, pad30;
    cFilterChainJob()
    {
        mFilters[0] = 0;
        mFilters[1] = 0;
        mFilters[2] = 0;
        mbActive = false;
        pad24 = 0;
        mFilterIndex = 0;
        pad2c = 0;
        pad30 = 0;
    }
    void Start() { if (!mbActive) { mbActive = true; mFilterIndex = 0; } }
    void AddFilter(cJobPostFilter* filter);                     // 0x007B9750
};
struct ChainPtr {
    cFilterChainJob* mpObject;
    ChainPtr(cFilterChainJob* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~ChainPtr() { if (mpObject) mpObject->Release(); }
};

// Callback object installed on the splat job (RefBaseA22 -> DrvBA22, 0x30 bytes).
struct RefBaseA22 {
    virtual ~RefBaseA22();
    virtual int AddRef();                                       // +0x04
    virtual int Release();                                      // +0x08
    volatile long mnRefCount;                                   // +0x04
    RefBaseA22() { _InterlockedExchange(&mnRefCount, 0); }
};
struct DrvBA22 : RefBaseA22 {
    int mField08, pad0c;                                        // +0x08
    int mField10, pad14;                                        // +0x10
    int mField18, pad1c;                                        // +0x18
    int mField20, pad24;                                        // +0x20
    int mField28, pad2c;                                        // +0x28
    DrvBA22() : mField28(0) {}
    virtual ~DrvBA22();
};
struct DrvPtr {
    RefBaseA22* mpObject;
    DrvPtr& operator=(RefBaseA22* p)
    {
        if (p != mpObject) {
            RefBaseA22* const old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};

// Splat job objects at +0x10e4 / +0x10e8 / +0x10ec.
struct cSplatJob {
    virtual void j00(); virtual void j01(); virtual void j02(); virtual void j03();
    virtual void* GetLayer(int a, LayerInfo* info);             // +0x10
    char pad04[0x90 - 0x04];
    DrvPtr mEffect;                                             // +0x90
    void Reset();                                               // 0x007B39D0
    void Init(int c1, int c2, int c3, int c4, int c5, const RectID* c6, cViewer* viewer, int c8,
              cFilterChainJob* chain);                          // 0x007C1B70 (ret 0x24)
};

struct cThumbnailManagerSplat {
    char pad0[0x78];
    cViewer* mSplatterViewer;                                   // +0x78
    cViewer* mBakeInfoSplatterViewer;                           // +0x7C
    cViewer* mNMapSpecSplatterViewer;                           // +0x80
    char pad84[0x10e4 - 0x84];
    cSplatJob* mJob0;                                           // +0x10E4
    cSplatJob* mJob1;                                           // +0x10E8
    cSplatJob* mJob2;                                           // +0x10EC

    void SetupSplat(int a1, const RectID* a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9,
                    const RectID* a10, const RectID* a11, int a12);
};

// @ 0x007c1c10
void cThumbnailManagerSplat::SetupSplat(int a1, const RectID* a2, int a3, int a4, int a5, int a6, int a7,
                                        int a8, int a9, const RectID* a10, const RectID* a11, int a12)
{
    const bool haveRect2 = a11->mAllocID != -1;
    const bool haveRect1 = a10->mAllocID != -1;
    RectID tmp;

    RenderTargetManager()->SetFlag(0);
    RenderTargetManager()->SetFlag(1);
    IScene* scene = App()->GetScene();
    scene->SetMode(0);

    Xform xf;
    scene->GetTransform()->GetXform(&xf);
    mSplatterViewer->SetBasis(&xf);
    mSplatterViewer->SetRenderMode(3, 0);
    ILayerManager* layerManager = LayerManager();
    mJob0->Reset();
    mJob0->Init(a3, a8, a4, a5, a6, a2, mSplatterViewer, a12, 0);

    if (haveRect1) {
        mBakeInfoSplatterViewer->SetBasis(&xf);
        mBakeInfoSplatterViewer->SetRenderMode(3, 1);
        ChainPtr chain(new("Graphics", 0, 0, 0, 0) cFilterChainJob());
        chain.mpObject->Start();
        FilterPtr f1(new("Graphics", 0, 0, 0, 0) cJobPostFilter());
        FilterPtr f2(new("Graphics", 0, 0, 0, 0) cJobPostFilter());
        FilterPtr f3(new("Graphics", 0, 0, 0, 0) cJobPostFilter());
        FilterPtr f4(new("Graphics", 0, 0, 0, 0) cJobPostFilter());
        tmp.mPageID = -1;
        tmp.mAllocID = -1;
        RenderTargetManager()->FreeRect(&tmp, false);
        f1.mpObject->Init(0xd2, a10, &tmp, 0);
        f2.mpObject->Init(0xd2, &tmp, a10, 0);
        f3.mpObject->Init(0xd2, a10, &tmp, 0);
        f4.mpObject->Init(0xd2, &tmp, a10, 0);
        chain.mpObject->AddFilter(f1.mpObject);
        chain.mpObject->AddFilter(f2.mpObject);
        chain.mpObject->AddFilter(f3.mpObject);
        chain.mpObject->AddFilter(f4.mpObject);
        mJob1->Reset();
        mJob1->Init(a3, a8, a4, a5, a6, a10, mBakeInfoSplatterViewer, a12, chain.mpObject);
    }

    if (haveRect2) {
        ChainPtr chain(new("Graphics", 0, 0, 0, 0) cFilterChainJob());
        chain.mpObject->Start();
        mNMapSpecSplatterViewer->SetBasis(&xf);
        mNMapSpecSplatterViewer->SetRenderMode(3, 2);
        FilterPtr f1(new("Graphics", 0, 0, 0, 0) cJobPostFilter());
        FilterPtr f2(new("Graphics", 0, 0, 0, 0) cJobPostFilter());
        FilterPtr f3(new("Graphics", 0, 0, 0, 0) cJobPostFilter());
        FilterPtr f4(new("Graphics", 0, 0, 0, 0) cJobPostFilter());
        tmp.mPageID = -1;
        tmp.mAllocID = -1;
        RenderTargetManager()->FreeRect(&tmp, false);
        f1.mpObject->Init(0xd2, a11, &tmp, 0);
        f2.mpObject->Init(0xd2, &tmp, a11, 0);
        f3.mpObject->Init(0xd2, a11, &tmp, 0);
        f4.mpObject->Init(0xd3, &tmp, a11, 0);
        chain.mpObject->AddFilter(f1.mpObject);
        chain.mpObject->AddFilter(f2.mpObject);
        chain.mpObject->AddFilter(f3.mpObject);
        chain.mpObject->AddFilter(f4.mpObject);
        mJob2->Reset();
        mJob2->Init(a3, a8, a4, a5, a6, a11, mNMapSpecSplatterViewer, a12, chain.mpObject);
    }

    DrvBA22* drv = new("Graphics", 0, 0, 0, 0) DrvBA22();
    drv->mField08 = a7;
    drv->mField10 = 0;
    drv->mField18 = a9;
    drv->mField20 = 0;
    cSplatJob* job = mJob0;
    job->mEffect = drv;
    LayerInfo info;
    layerManager->AddLayer(mJob0->GetLayer(0, &info));
}

}  // namespace SPL

// ---------------------------------------------------------------------------
// remaining routines (skeletons)
// ---------------------------------------------------------------------------
void FUN_007c2540(void* a) { (void)a; }

// ---------------------------------------------------------------------------
// ColorReduce (0x007c2790): quantise a 32bpp image to a palette (Wu), fill the
// destination palette table and remap the pixels.
// ---------------------------------------------------------------------------
struct WuContext;
WuContext* WU_open();                                                        // 0x006e1d10
int  __stdcall WU_read(int ctx, int desc, int pixels, int stride);                     // 0x006e1d50
void* __stdcall WU_close(int ctx, int nColors, int* outPal, int* outCount);            // 0x006e1db0
void __stdcall CRAPI_remap(unsigned char* dst, int ctx, int dstStride, unsigned char* src, int srcStride,
                 int wide, unsigned mode, int diffuse, unsigned count, unsigned rows); // 0x006e25f0
extern "C" unsigned char __stdcall gfree(void* p);                           // 0x0087d4c0

struct cDirectPropertyListCR { int GetIntProperty(unsigned id) const; };     // 0x006a2660
extern cDirectPropertyListCR* g_sAppProperties_CR;                           // 0x015fd918

struct ColorReduceDst { char pad[0x24]; int mCount; unsigned char mPalette[1]; };

struct WuImageDesc { int pad[4]; int width; int height; int bpp; uint32_t tail[0xa95]; };

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// @ 0x007c2790
void ColorReduce(unsigned char* src, unsigned char* dst, ColorReduceDst* out, int width,
                 unsigned height, int bytesPerPixel)
{
    WuContext* ctx = WU_open();
    WuImageDesc desc;
    desc.height = height;
    int stride = (width * 32) / 8;
    desc.width = width;
    desc.bpp = 32;
    WU_read((int)ctx, (int)&desc, (int)src, stride);
    int* pal;
    void* colors = WU_close((int)ctx, 0xff, (int*)&pal, 0);
    memcpy(out->mPalette, colors, out->mCount * 4);
    gfree(colors);
    unsigned mode = g_sAppProperties_CR->GetIntProperty(0x5d2c085);
    CRAPI_remap(dst, (int)out, (unsigned)(width * bytesPerPixel) >> 3, src, stride, desc.bpp,
                (unsigned)pal, mode, width, height);
    gfree(pal);
    
}

// ---------------------------------------------------------------------------
// ConvertDXT1ToARGB8888 (0x007c2880): decode DXT1 4x4 blocks to ARGB8888.
// ---------------------------------------------------------------------------
static inline uint32_t Expand565(uint16_t c)
{
    uint32_t v = c;
    uint32_t t = (v & 0xf800) * 0x20 + (v & 0x1f);
    t = t * 8;
    t = t + (t >> 5);
    uint32_t g = v & 0x7e0;
    return ((((g * 0x20) + (g >> 1)) ^ t) & 0xff00) ^ t;
}

// @ 0x007c2880
void ConvertDXT1ToARGB8888(uint32_t* dst, int stride, uint16_t* src, int srcPitch, int width, int height)
{
    int bw = (width + 3) >> 2;
    int bh = (height + 3) >> 2;
    if (bw != 0 && bh != 0) {
        int x = bw;
        uint32_t* d = dst;
        int srcAdv = srcPitch - bw * 8;
        int dstAdv = (stride - bw * 4) * 4;
        do {
            do {
                uint16_t c0 = src[0];
                uint32_t t0 = Expand565(c0);
                uint16_t c1 = src[1];
                uint32_t t1 = Expand565(c1);
                uint32_t cols[4];
                cols[1] = t1 | 0xff000000;
                cols[0] = t0 | 0xff000000;
                if (c0 > c1) {
                    uint32_t h1 = (cols[1] >> 8) & 0xff00ff;
                    uint32_t h0 = (cols[0] >> 8) & 0xff00ff;
                    uint32_t A = h0 * 0xab + h1 * 0x55;
                    uint32_t B = h1 * 0xab + h0 * 0x55;
                    uint32_t l0 = cols[0] & 0xff00ff;
                    uint32_t l1 = cols[1] & 0xff00ff;
                    cols[2] = ((((l0 * 0xab + 0x800080 + l1 * 0x55) >> 8) ^ (A - 0x7fff80)) & 0xff00ff) ^ (A + 0x800080);
                    cols[3] = ((((l1 * 0xab + 0x800080 + l0 * 0x55) >> 8) ^ (B - 0x7fff80)) & 0xff00ff) ^ (B + 0x800080);
                } else {
                    cols[2] = (cols[1] | cols[0]) - (((cols[1] ^ cols[0]) >> 1) & 0x7f7f7f7f);
                    cols[3] = 0;
                }
                expand_2_32(d, stride, *(uint32_t*)(src + 2), cols);
                d += 4;
                src += 4;
                --x;
            } while (x != 0);
            src = (uint16_t*)((char*)src + srcAdv);
            d = (uint32_t*)((char*)d + dstAdv);
            --bh;
            x = bw;
        } while (bh != 0);
    }
}
