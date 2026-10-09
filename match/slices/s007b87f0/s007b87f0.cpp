// Slice s007b87f0 - cThumbnailManager filter-chain/large-image helpers.

void operator delete[](void*);   // 0x00f47380

struct Pair2 { int a, b; };

struct RawVec {
    Pair2* begin;
    Pair2* end;
    Pair2* cap;
    void push_back(Pair2* p);
    void DoInsertValue(Pair2* pos, Pair2* p);   // out-of-line vector grow (006ec390)
};

struct VecPair {
    char pad0[0x24];
    RawVec v;                           // +0x24
    void Push(Pair2* p);
};

void RawVec::push_back(Pair2* p)
{
    Pair2* e = end;
    if (e < cap) {
        end = e + 1;
        if (e)
            *e = *p;
    } else {
        DoInsertValue(e, p);
    }
}

// @ 0x007b9690
void VecPair::Push(Pair2* p)
{
    v.push_back(p);
}

// ---------------------------------------------------------------------------
// Remaining functions are large cThumbnailManager filter-chain helpers;
// recorded as partial skeletons in partial.txt.
// ---------------------------------------------------------------------------

struct ShutdownViewer {
    void Destroy1();                    // 007c3ba0
    void Destroy2();                    // 007c4000
};


struct PostFilterVec {
    void* b; void* e; void* c;
    void erase(void* first, void* last);   // 00d018d0
    void* begin() { return b; }
    void* end() { return e; }
    bool empty() const { return b == e; }
    void clear() { erase(begin(), end()); }
};

struct cJobPostFilter {
    virtual void v0();
    virtual void Release();             // vtbl+4
    char pad0[0x18 - 4];
    int* m_p18;                         // +0x18
    char pad1[0x24 - 0x1c];
    PostFilterVec m_vec;                // +0x24
    char pad2[0x38 - 0x30];
    ShutdownViewer* m_viewer;           // +0x38
    char pad3[0x80 - 0x3c];
    bool m_flag;                        // +0x80
    bool m_b81;                         // +0x81
    void Shutdown();
    void Init(bool b81);
    void Init(int a, const int* p, const int* q, bool b81);
};

// @ 0x007b9620
void cJobPostFilter::Shutdown()
{
    if (!m_flag)
        return;
    if (m_viewer) {
        m_viewer->Destroy1();
        ShutdownViewer* v = m_viewer;
        if (v) {
            v->Destroy2();
            operator delete[](v);
        }
        m_viewer = 0;
    }
    if (m_p18)
        m_p18 = 0;
    if (!m_vec.empty())
        m_vec.clear();
    m_flag = false;
}

void operator delete[](void*);   // 0x00f47380


// ---------------------------------------------------------------------------
#include <float.h>
#include <math.h>
#include <string.h>

typedef unsigned int uint;
#define VSLOT(obj, idx) ((*(void***)(obj))[idx])

void* operator new(unsigned int, const char*, int, int, int, int);
void operator delete(void*, const char*, int, int, int, int);

// @ 0x007b8b30 : constructor of a two-vtable resource object (vtables at +0 and +4)
extern void* g_vtbl_1410024[];
extern void* g_vtbl_1410014[];
extern void* g_vtbl_13ec458[];
extern void* g_vtbl_13eb938[];

struct RefVec { void* b; void* e; void* c; void Destroy(); };   // 0041eb80 = ~RefVector

struct IRel { virtual void v0(); virtual void Release(); };

struct cFilterRes {
    void** vtbl0;                       // +0
    void** vtbl1;                       // +4
    int m08, m0c, m10;
    char pad14[0x94 - 0x14];
    int m94, m98, m9c, ma0;             // -1
    IRel* ma4;                          // +0xa4
    IRel* ma8;                          // +0xa8
    RefVec mac;                         // +0xac..0xb7
    char padb8[0xc0 - 0xb8];
    int mc0;
    char mc4;
    char padc5[0xd8 - 0xc5];
    char md8;
    cFilterRes* Ctor();
    void Dtor();
};

// @ 0x007b8b30
cFilterRes* cFilterRes::Ctor()
{
    vtbl1 = g_vtbl_13ec458;
    m08 = 0;
    vtbl0 = g_vtbl_1410024;
    vtbl1 = g_vtbl_1410014;
    m0c = 0;
    m10 = 0;
    m94 = m98 = m9c = ma0 = -1;
    ma4 = 0;
    ma8 = 0;
    mac.b = 0; mac.e = 0; mac.c = 0;    // RefVector at +0xac
    mc0 = 0;
    mc4 = 0;
    md8 = 0;
    return this;
}

// @ 0x007b8be0
void cFilterRes::Dtor()
{
    vtbl0 = g_vtbl_1410024;
    vtbl1 = g_vtbl_1410014;
    mac.Destroy();
    if (ma8) ma8->Release();
    if (ma4) ma4->Release();
    vtbl0 = g_vtbl_13eb938;
    vtbl1 = g_vtbl_13ec458;
}

// ---------------------------------------------------------------------------
// cViewer creation shared by the three Init helpers (cSPEditorPhysicsWorld, 0x174 bytes)
struct cViewer {
    char pad[0x174];
    cViewer();                          // 007c3f70
    void Init(int);                     // 007c4dd0
    void Fn3cc0(int);                   // 007c3cc0
};


static __forceinline cViewer* NewViewer()
{
    return new ("Graphics", 0, 0, 0, 0) cViewer();
}

// @ 0x007b9420
void cJobPostFilter::Init(bool b)
{
    if (m_flag)
        return;
    cViewer* v = NewViewer();
    m_viewer = (ShutdownViewer*)v;
    v->Init(0);
    ((cViewer*)m_viewer)->Fn3cc0(0);
    m_b81 = b;
    if (!m_vec.empty())
        m_vec.clear();
    int* z = (int*)((char*)this + 0x3c);
    for (int i = 0; i < 16; i++) z[i] = 0;
    m_flag = true;
}

// @ 0x007b9510
void cJobPostFilter::Init(int a, const int* p, const int* q, bool b)
{
    if (m_flag)
        return;
    cViewer* v = NewViewer();
    m_viewer = (ShutdownViewer*)v;
    v->Init(0);
    ((cViewer*)m_viewer)->Fn3cc0(0);
    int* me = (int*)this;
    me[3] = a;
    me[4] = p[0];
    me[5] = p[1];
    me[7] = q[0];
    me[8] = q[1];
    if (!m_vec.empty())
        m_vec.clear();
    int* z = (int*)((char*)this + 0x3c);
    for (int i = 0; i < 16; i++) z[i] = 0;
    m_b81 = b;
    m_flag = true;
}

// ---------------------------------------------------------------------------
// @ 0x007b96d0 : cFilterChainJob::Shutdown
struct IRC2 { virtual void AddRef(); virtual void Release(); };
struct ARC {
    IRC2* p;
    ARC(IRC2* q) : p(q) { if (p) p->AddRef(); }
    ~ARC() { if (p) p->Release(); }
};
struct FilterRef {
    cJobPostFilter* mpObject;
    void reset() { cJobPostFilter* p = mpObject; if (p) { mpObject = 0; p->Release(); } }
};
struct FilterVec {
    FilterRef* mpBegin;
    FilterRef* mpEnd;
    FilterRef* mpCap;
    FilterRef& operator[](uint i) { return mpBegin[i]; }
    void clear() { erase(mpBegin, mpEnd); }
    bool empty() const { return mpBegin == mpEnd; }
    uint size() const { return (uint)(mpEnd - mpBegin); }
    void push_back(const ARC& v);                                // 007a6ac0
    void erase(FilterRef* first, FilterRef* last);   // eastl::vector<AutoRefCount<..>>::erase
};
struct cFilterChainJob {
    char pad0[0xc];
    FilterVec mFilters;                 // +0xc
    char pad18[0x20 - 0x18];   // allocator
    bool mInitialized;                  // +0x20
    void Shutdown();
    int  AddFilter(IRel* p);
};

void cFilterChainJob::Shutdown()
{
    if (!mInitialized)
        return;
    if (!mFilters.empty()) {
        uint n = mFilters.size();
        for (uint i = 0; i < n; i++) {
            mFilters[i].mpObject->Shutdown();
            mFilters[i].reset();
        }
        mFilters.clear();
    }
    mInitialized = false;
}

// @ 0x007b9750 : append a refcounted filter, return its index
int cFilterChainJob::AddFilter(IRel* p)
{
    {
        ARC tmp((IRC2*)p);
        mFilters.push_back(tmp);
    }
    return (int)mFilters.size() - 1;
}

// ---------------------------------------------------------------------------
// @ 0x007b87f0 : bounding sphere of the visible, enabled elements of a scene object
struct PtrFixedVec {
    void** begin;
    void** end;
    void** cap;
    void*  buf[14];
    PtrFixedVec() { begin = end = buf; cap = buf + 14; }
    ~PtrFixedVec() { if (begin && begin != buf) operator delete[](begin); }
};
struct BBox6 { float mn[3]; float mx[3]; };

// @ 0x007b87f0
void __stdcall ComputeBoundingSphere(void* obj, float* outCenter, float* outRadius)
{
    PtrFixedVec vec;
    BBox6 bb;
    bb.mn[0] = bb.mn[1] = bb.mn[2] = 0.0f;
    bb.mx[0] = bb.mx[1] = 0.0f;
    ((unsigned char*)&bb.mx[2])[0] = 0;
    ((unsigned char*)&bb.mx[2])[1] = 0;

    typedef bool (__thiscall* GetFn)(void*, PtrFixedVec*, BBox6*);
    if (!((GetFn)VSLOT(obj, 11))(obj, &vec, &bb))
        return;

    bb.mn[0] = bb.mn[1] = bb.mn[2] = FLT_MAX;
    bb.mx[0] = bb.mx[1] = bb.mx[2] = -FLT_MAX;

    uint n = (uint)(vec.end - vec.begin);
    for (uint i = 0; i < n; i++) {
        void* e = vec.begin[i];
        uint flags = *(uint*)((char*)e + 4);
        if (((flags >> 15) & 1) && (flags & 1)) {
            typedef const float* (__thiscall* BoundsFn)(void*, void*);
            const float* b = ((BoundsFn)VSLOT(obj, 24))(obj, e);
            const float* p = (const float*)((char*)e + 0xc);
            float lo0 = p[0] + b[0], lo1 = p[1] + b[1], lo2 = p[2] + b[2];
            float hi0 = p[0] + b[3], hi1 = p[1] + b[4], hi2 = p[2] + b[5];
            if (bb.mn[0] > bb.mx[0]) {
                bb.mn[0] = lo0; bb.mn[1] = lo1; bb.mn[2] = lo2;
                bb.mx[0] = hi0; bb.mx[1] = hi1; bb.mx[2] = hi2;
            } else {
                if (bb.mn[0] > lo0) bb.mn[0] = lo0;
                if (hi0 > bb.mx[0]) bb.mx[0] = hi0;
                if (bb.mn[1] > lo1) bb.mn[1] = lo1;
                if (hi1 > bb.mx[1]) bb.mx[1] = hi1;
                if (bb.mn[2] > lo2) bb.mn[2] = lo2;
                if (hi2 > bb.mx[2]) bb.mx[2] = hi2;
            }
        }
    }
    if (!(bb.mn[0] > bb.mx[0])) {
        float dx = bb.mx[0] - bb.mn[0];
        float dy = bb.mx[1] - bb.mn[1];
        float dz = bb.mx[2] - bb.mn[2];
        outCenter[0] = (bb.mx[0] + bb.mn[0]) * 0.5f;
        outCenter[1] = (bb.mx[1] + bb.mn[1]) * 0.5f;
        outCenter[2] = (bb.mx[2] + bb.mn[2]) * 0.5f;
        *outRadius = sqrtf((dz * dz + dy * dy) + dx * dx) * 0.5f + 1.0f;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007b91f0 : set up the planet-capture viewer and kick off a capture
// The original inlines atan2 as fpatan (fast float model): this section only.
#pragma float_control(precise, off, push)
struct CaptureCam {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
    int pad[2];
    float radius;                       // +0xc
};
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct CapBox { Vec3 mn; Vec3 mx; };
struct CapBoxVec {
    CapBox* b; CapBox* e; CapBox* c;
    void DoInsertValue(CapBox* pos, const CapBox* v);                  // 00424010
    ~CapBoxVec() { if (b && ((int*)b)[-1]) operator delete[](b); }
};
unsigned int __cdecl FNV1_String8(const char* s, unsigned int h, int n);   // 00932e80
void* LightingManager();                                                  // 0067dd90
void* CaptureService();                                                   // 0067ddb0

struct cPlanetCapture {
    char pad0[0xc];
    bool mInit;                         // +0xc
    char pad1[3];
    cViewer* mViewer;                   // +0x10
    CaptureCam* mCam;                   // +0x14
    void Setup(CaptureCam* cam);
};

// @ 0x007b91f0
void cPlanetCapture::Setup(CaptureCam* cam)
{
    if (mInit)
        return;
    CaptureCam* old = mCam;
    if (cam != old) {
        if (cam) cam->AddRef();
        mCam = cam;
        if (old) old->Release();
    }
    cViewer* v = NewViewer();
    mViewer = v;
    v->Init(0);
    mInit = true;

    CapBox bb;
    bb.mn = Vec3(FLT_MAX, FLT_MAX, FLT_MAX);
    bb.mx = Vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
    float r = mCam->radius;
    bb.mn.x -= r; bb.mn.y -= r; bb.mn.z -= r;
    bb.mx.x += r; bb.mx.y += r; bb.mx.z += r;

    CapBoxVec boxes;
    boxes.b = 0; boxes.e = 0; boxes.c = 0;
    boxes.DoInsertValue(0, &bb);

    unsigned int key = FNV1_String8("PlanetCapture", 0x811c9dc5u, 1);
    Vec3 sun;
    typedef void (__thiscall* GetDirFn)(void*, Vec3*);
    void* lm = LightingManager();
    ((GetDirFn)VSLOT(lm, 9))(lm, &sun);

    typedef void (__thiscall* CaptureFn)(void*, CapBoxVec*, cViewer*, unsigned int, Vec3*, float, float);
    void* svc = CaptureService();
    Vec3 origin(0.0f, 0.0f, 0.0f);
    ((CaptureFn)VSLOT(svc, 20))(svc, &boxes, mViewer, key, &origin, 30.0f, (float)atan2((double)sun.y, (double)sun.x));
}
#pragma float_control(pop)

// ---------------------------------------------------------------------------
// @ 0x007b8cb0 : cCSAThumbnailJob::RenderLargeTiledImage
// Renders an n x n grid of tiles through the job's viewer, stitches them into one big
// raster, wraps it in an image object and saves it as "CRE_<name>-<id>_ful.png".
struct ResKey { unsigned int a, b, c; };
struct cCSAJobParams {
    char pad0[8];
    int m8, mc;                         // +8, +0xc
    char pad10[0x28 - 0x10];
    unsigned int mTileCount;            // +0x28
    unsigned int mId;                   // +0x2c
    int m30;                            // +0x30
    char pad34[0x40 - 0x34];
    struct cTileSink* mSink;            // +0x40
    const wchar_t* mName;               // +0x44
    char pad48[0x54 - 0x48];
    void* m54;                          // +0x54
};
struct cTileSink { char pad[0xc]; int** mpData; void Flush(int, int, void*, int);   /* 007b49f0 */ };

struct cTileViewer {
    void Copy(int, int, int);                       // 007c50b0
    void Fn3c20(void*);                             // 007c3c20
    void Fn40c0(float*, float*);                    // 007c40c0
    void Fn4b00(float, float);                      // 007c4b00
    void SetPos(float, float);                      // 007c4ad0
    void SetRaster(void*, int);                     // 007c4be0
    void Fn3c50(int);                               // 007c3c50
};
struct cImageObj {
    virtual void AddRef();
    virtual void Release();
    int m08, m0c, m10;
    char pad[0x38 - 0x14];
    cImageObj* Ctor(int w, int h, void* pixels, unsigned id, unsigned fmt);  // 007b4e10
};
struct WStr {
    wchar_t* b; wchar_t* e; wchar_t* c;
    WStr() { b = e = (wchar_t*)0x1667bac; c = (wchar_t*)0x1667bae; }
    ~WStr() { if ((((int)c - (int)b) & ~1) > 2 && b) operator delete[](b); }
};
void  WStr_Format(WStr*, const wchar_t*, ...);                // 0041e050
void* GetRTTManager();                                        // 0067dda0
void* GetRenderer();                                          // 0067dd50
void* GetSaveArea(int);                                       // 006b1f90
void* GetResourceMan();                                       // 0067dcd0
void  AsyncSave(cImageObj*, void*, int, ResKey*);             // 006b4b60

struct cCSAThumbnailJob {
    char pad0[0x10];
    void* mA;                           // +0x10
    void* mB;                           // +0x14
    cTileViewer* mViewer;               // +0x18
    char pad1c[4];
    cCSAJobParams* mP;                  // +0x20
    void RenderLargeTiledImage(int a0, int a1, int* a2, int a3);
};

void cCSAThumbnailJob::RenderLargeTiledImage(int a0, int a1, int* a2, int a3)
{
    cCSAJobParams* P = mP;
    mViewer->Copy(*a2, 0, 0);
    int rect[4] = { 0, 0, 0, 0 };
    mViewer->Fn3c20(rect);

    unsigned int n = P->mTileCount;
    float s1, s2;
    mViewer->Fn40c0(&s1, &s2);
    float inv = 1.0f / (float)n;
    s1 = s1 * inv;
    s2 = s2 * inv;
    mViewer->Fn4b00(s1, s2);

    int dA, dB, tw, th;
    typedef void (__thiscall* QueryFn)(void*, int, int, int*, int*, int*, int*);
    void* rtt = GetRTTManager();
    ((QueryFn)VSLOT(rtt, 9))(rtt, P->m8, P->mc, &dB, &dA, &th, &tw);

    typedef unsigned char* (__thiscall* RasterFn)(void*, int, int);
    rtt = GetRTTManager();
    unsigned char* raster = ((RasterFn)VSLOT(rtt, 6))(rtt, P->m8, P->mc);
    int bpp = raster[0x10] >> 3;
    int tileBytes = bpp * th * tw;

    unsigned char* big  = (unsigned char*)operator new(tileBytes * n * n, "Graphics", 0, 0, 0, 0);
    unsigned char* tile = (unsigned char*)operator new(tileBytes, "Graphics", 0, 0, 0, 0);

    if (n != 0) {
        float nm1 = (float)(n - 1);
        for (unsigned int i = 0; i < n; i++) {
            for (unsigned int j = 0; j < n; j++) {
                float x = (nm1 - (float)i * 2.0f) * s1;
                float y = -(nm1 - (float)j * 2.0f) * s2;
                mViewer->SetPos(x, y);
                mViewer->SetRaster(&P->m8, 1);
                mViewer->Fn3c50(7);

                struct { cTileViewer* v; int z0, z1, z2; } q = { mViewer, 0, 0, 0 };
                typedef void* (__thiscall* GetLayerFn)(void*);
                typedef void  (__thiscall* DrawFn)(void*, int, int, void*, int);
                void* l = ((GetLayerFn)VSLOT(mB, 0x13c / 4))(mB);
                ((DrawFn)VSLOT(l, 3))(l, a0, a1, &q, a3);
                l = ((GetLayerFn)VSLOT(mA, 0x13c / 4))(mA);
                ((DrawFn)VSLOT(l, 3))(l, a0, a1, &q, a3);
                if (P->m54)
                    ((DrawFn)VSLOT(P->m54, 3))(P->m54, a0, a1, &q, a3);

                typedef void (__thiscall* RenderFn)(void*, int, int, int, void*, int, int);
                void* rd = GetRenderer();
                ((RenderFn)VSLOT(rd, 0x40 / 4))(rd, a3, 0x12, 0x12, &q, 1, 0);

                if (i == n - 1 && j == n - 1 && P->mSink) {
                    int* t = *P->mSink->mpData;
                    t[7] = P->m8;
                    t[8] = P->mc;
                    P->mSink->Flush(a0, a1, &q, a3);
                }

                typedef void (__thiscall* ReadFn)(void*, int, int, void*);
                rtt = GetRTTManager();
                ((ReadFn)VSLOT(rtt, 0xc))(rtt, P->m8, P->mc, tile);

                unsigned char* dst = big + ((((int)j * tw * (int)n) + (int)i) * bpp * th);
                unsigned char* src = tile;
                int rowBytes = bpp * th;
                int stride = rowBytes * (int)n;
                for (int k = 0; k < tw; k++) {
                    memcpy(dst, src, rowBytes);
                    src += rowBytes;
                    dst += stride;
                }
            }
        }
    }

    int totalW = tw * (int)n;
    int totalH = th * (int)n;
    cImageObj* img = 0;
    void* mem = operator new(0x38, "Graphics", 0, 0, 0, 0);
    if (mem)
        img = ((cImageObj*)mem)->Ctor(totalH, totalW, big, P->mId, 0x417b3a7);
    if (img) img->AddRef();

    ResKey key;
    key.a = P->mId;
    key.b = (unsigned)P->m30;
    key.c = 0x41602b00;
    img->m08 = key.a;
    img->m0c = key.b;
    img->m10 = key.c;

    void* area = GetSaveArea(0x11ac196);
    void* mgr = GetResourceMan();
    WStr path;
    WStr_Format(&path, L"CRE_%s-%08x_ful.png", P->mName, P->mId);
    typedef void (__thiscall* MakeKeyFn)(void*, ResKey*, const wchar_t*);
    ((MakeKeyFn)VSLOT(mgr, 0x80 / 4))(mgr, &key, path.b);
    AsyncSave(img, area, 0, &key);
    operator delete[](tile);
    operator delete[](big);
    img->Release();
}
// --- equivalence checker address annotations
    void operator delete[](void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
