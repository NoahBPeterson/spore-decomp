// Slice s007b19c0 — SP::cTexturePreload / cThumbnailManager helpers and small accessor/setter
// routines in the texture/thumbnail subsystem. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
// (007b2600 and 007b1f40 need /fp:fast for the original's inline x87 fsqrt)
#include "../../include/types.h"
#include <intrin.h>
#include <math.h>
#include <string.h>
#include <new>

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
void* __cdecl FUN_0067dd60();                       // 0x0067DD60 (RTT manager / factory)
void* __cdecl FUN_0067dcc0();                       // 0x0067DCC0 MessageServer()

struct S3 { int a, b, c; };

struct IFac {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void* v7(S3 s, int z);                  // +0x1C
    virtual void* v8(int,int);                      // +0x20 (RTT create)
};
struct IMsg {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    virtual void v5(void*,int,int);                 // +0x14
};

// ---------------------------------------------------------------------------
// @ 0x007b1e70  (forwarder: m(0,a,b))
// ---------------------------------------------------------------------------
struct W1e70 {
    void helper(int, void*, void*);
    void f(void* a, void* b);
};
void W1e70::f(void* a, void* b) { helper(0, a, b); }

// ---------------------------------------------------------------------------
// @ 0x007b1da0
// ---------------------------------------------------------------------------
struct W1da0 {
    void Handler(void* r);                          // 0x007B1AF0 __thiscall
    void f(S3* p);
};
void W1da0::f(S3* p)
{
    IFac* fac = (IFac*)FUN_0067dd60();
    Handler(fac->v7(*p, 0));
}

// ---------------------------------------------------------------------------
// @ 0x007b2680  SP::cThumbnailManager::GetThumbRectID
// ---------------------------------------------------------------------------
struct RectID { int page, alloc; };
struct ThumbMgr {
    char pad0[0x14];
    RectID mThumbRectID;                            // +0x14
    void GetThumbRectID(RectID* out);
};
void ThumbMgr::GetThumbRectID(RectID* out)
{
    out->page = mThumbRectID.page;
    out->alloc = mThumbRectID.alloc;
}

// ---------------------------------------------------------------------------
// @ 0x007b27a0  (setter block A)
// ---------------------------------------------------------------------------
struct W27a0 {
    char pad[0x82];
    unsigned char m82;                              // +0x82
    char pad2[0x15];
    int m98, m9c, ma0, ma4;
    void f(int, int, int, int);
};
void W27a0::f(int a, int b, int c, int d)
{
    m98 = a; m9c = b; ma0 = c; m82 = 1; ma4 = d;
}

// ---------------------------------------------------------------------------
// @ 0x007b27e0  (setter block B)
// ---------------------------------------------------------------------------
struct W27e0 {
    char pad[0x83];
    unsigned char m83;                              // +0x83
    int m84, m88, m8c, m90, m94;
    void f(int, int, int, int, int);
};
void W27e0::f(int a, int b, int c, int d, int e)
{
    m84 = a; m88 = b; m8c = c; m83 = 1; m90 = d; m94 = e;
}

// ---------------------------------------------------------------------------
// @ 0x007b2820  (setter block C: four 2-dword values + float)
// ---------------------------------------------------------------------------
struct Pair { int x, y; };
struct W2820 {
    char pad[0xac];
    Pair a, b, c, d;                                // +0xac .. +0xc8
    float f;                                        // +0xcc
    void set(Pair*, Pair*, Pair*, Pair*, float);
};
void W2820::set(Pair* pa, Pair* pb, Pair* pc, Pair* pd, float v)
{
    a.x = pa->x; a.y = pa->y;
    b.x = pb->x; b.y = pb->y;
    c.x = pc->x; c.y = pc->y;
    d.x = pd->x; d.y = pd->y;
    f = v;
}

// ---------------------------------------------------------------------------
// @ 0x007b2890  (destructor: release member +0x10, restore base vtable)
// ---------------------------------------------------------------------------
struct IObj2 { virtual int AddRef(); virtual int Release(); };
struct B2890 { virtual int AddRef(); virtual int Release(); };
struct D2890 : B2890 {
    void* mObj;                                     // +0x10? (relative to +0x10 of full object)
    char pad[0xc];
    virtual int AddRef();
    virtual ~D2890();
};
D2890::~D2890() { if (mObj) ((IObj2*)mObj)->Release(); }

// ---------------------------------------------------------------------------
extern void* g_vtblB2900;                           // 0x13ef094
struct B2900 { virtual int AddRef(); virtual int Release(); ~B2900() { *(void**)this = &g_vtblB2900; } };
struct D2900 : B2900 {
    char pad[0x20];
    void* mObj;                                     // +0x24
    virtual int AddRef();
    virtual ~D2900();
};
// @ 0x007b2900  (destructor: release member +0x24, restore base vtable)
D2900::~D2900() { if (mObj) ((IObj2*)mObj)->Release(); }

// ---------------------------------------------------------------------------
// @ 0x007b2970  (send a message then clear a flag)
// ---------------------------------------------------------------------------
struct Node2900 { char pad[0xc]; unsigned char mFlag; };   // +0xc
struct P2970 { char pad[8]; Node2900* mNode; char pad2[4]; void* mArg; };
void __stdcall FUN_007b2970(P2970* p)
{
    Node2900* node = p->mNode;
    void* arg = p->mArg;
    IMsg* s = (IMsg*)FUN_0067dcc0();
    s->v5(arg, 0, 0);
    if (node->mFlag)
        node->mFlag = 0;
}

// ---------------------------------------------------------------------------
// externals used by the texture/thumbnail blit + conversion helpers
// ---------------------------------------------------------------------------
void* __cdecl eastl_alloc(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00F473A0
static inline void* shallow_new_layout(unsigned size) { return eastl_alloc(size, "Graphics", 0, 0, 0, 0); }
void  __cdecl eastl_dealloc(void* p);                                                    // 0x00F47380
void  __cdecl operator_delete__(void* p);                                                // 0x00F47380
void* __cdecl operator_new__(void* dst, int val, int count);                             // 0x011E073E

void __cdecl ConvertDXT1ToARGB8888(unsigned int*, int, unsigned short*, int, int, int);  // 0x007C2880
void __cdecl ConvertDXT3ToARGB8888(unsigned char*, int, unsigned char*, int, int, int);  // 0x007C2AB0
void __cdecl ConvertDXT5ToARGB8888(unsigned char*, int, unsigned char*, int, int, int);  // 0x007C2EE0

struct Raster      // rw::graphics::Raster (0x0c=width u16, 0x0e=height u16)
{
    unsigned D3D9GetMipLevelSize(int level);                     // 0x011F0000
    void     FillSpriteTexture(void* data, unsigned size, int a); // 0x011F0440
};

#pragma pack(push,1)
struct RasterHdr {
    unsigned int   m_format;        // +0x00 (FOURCC)
    unsigned int   m_type;          // +0x04
    void*          m_d3dTexture;    // +0x08
    unsigned short m_width;         // +0x0c
    unsigned short m_height;        // +0x0e
    unsigned char  m_depth;         // +0x10
    unsigned char  pad11;           // +0x11
    unsigned char  m_face;          // +0x12
    unsigned char  pad13;           // +0x13
};
#pragma pack(pop)

#define FORMAT_DXT1 0x31545844
#define FORMAT_DXT3 0x33545844
#define FORMAT_DXT5 0x35545844

// viewport-descriptor / image-writer helpers (anonymous namespace in SP)
void __cdecl InitViewportDesc(void* out, void* data, int width, int height, int depth, int fmt);  // 0x007C5A40
int  __cdecl WriteImageFile(const char* path, void* desc);                               // 0x007C5F00

// ---------------------------------------------------------------------------
// @ 0x007b1f40  Raster -> ARGB8888 conversion dispatch (DXT1/3/5 + raw)
// ---------------------------------------------------------------------------
struct D3DSurf;
struct D3DTex;

struct D3DTex {                          // IDirect3DTexture9-ish
    virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
    virtual void t04(); virtual void t05(); virtual void t06(); virtual void t07();
    virtual void t08(); virtual void t09(); virtual void t10(); virtual void t11();
    virtual void t12(); virtual void t13();
    virtual void Unlock();                                            // +0x38
    virtual void t15(); virtual void t16(); virtual void t17();
    virtual void GetSurfaceLevel(int face, int level, D3DSurf** out); // +0x48
};

struct D3DSurf {                         // IDirect3DSurface9-ish
    virtual void s00(); virtual void s01();
    virtual void Release();                                           // +0x08
    virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06();
    virtual void s07(); virtual void s08(); virtual void s09(); virtual void s10();
    virtual void s11();
    virtual void GetDesc(void* out);                                  // +0x30
    virtual void Lock(void* out, int a, int size);                    // +0x34
};

struct D3DDevice {                       // IDirect3DDevice9-ish
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void SetSamplerState(int a, void* b);                     // +0x80
    virtual void d33(); virtual void d34(); virtual void d35();
    virtual void CreateTexture(int w, int h, void* a, int b, void* c, int d);  // +0x90
};

extern D3DDevice* g_d3d9Device;                    // 0x016f89d0
void __cdecl DoInsertValue(void* dst, void* src, unsigned size);   // 0x011e0744 (memcpy-like)

void* FUN_007b1f40(RasterHdr* r)
{
    unsigned width  = r->m_width;
    unsigned height = r->m_height;
    unsigned fourcc = r->m_format;

    if (fourcc == FORMAT_DXT1) {
        void* p = shallow_new_layout(height * width * 4);
        void* q = shallow_new_layout(((Raster*)r)->D3D9GetMipLevelSize(0));
        ((Raster*)r)->FillSpriteTexture(q,
            ((Raster*)r)->D3D9GetMipLevelSize(0), 0);
        ConvertDXT1ToARGB8888((unsigned int*)p, (int)(width * 4),
            (unsigned short*)q, (int)(((width + 3) >> 2) * 8),
            (int)width, (int)height);
        eastl_dealloc(q);
        return p;
    }
    if (fourcc == FORMAT_DXT3) {
        void* p = shallow_new_layout(height * width * 4);
        void* q = shallow_new_layout(((Raster*)r)->D3D9GetMipLevelSize(0));
        ((Raster*)r)->FillSpriteTexture(q,
            ((Raster*)r)->D3D9GetMipLevelSize(0), 0);
        ConvertDXT3ToARGB8888((unsigned char*)p, (int)(width * 4),
            (unsigned char*)q, (int)(((width + 3) >> 2) << 4),
            (int)width, (int)height);
        eastl_dealloc(q);
        return p;
    }
    if (fourcc == FORMAT_DXT5) {
        void* p = shallow_new_layout(height * width * 4);
        void* q = shallow_new_layout(((Raster*)r)->D3D9GetMipLevelSize(0));
        ((Raster*)r)->FillSpriteTexture(q,
            ((Raster*)r)->D3D9GetMipLevelSize(0), 0);
        ConvertDXT5ToARGB8888((unsigned char*)p, (int)(width * 4),
            (unsigned char*)q, (int)(((width + 3) >> 2) << 4),
            (int)width, (int)height);
        eastl_dealloc(q);
        return p;
    }

    unsigned depth = r->m_depth;
    if (((Raster*)r)->D3D9GetMipLevelSize(0) != (depth * height * width >> 3))
        return 0;

    unsigned size = (depth * height * width) >> 3;
    if (depth < 0x20)
        size = ((((depth * width) >> 3) + 3) >> 2) * depth * height;

    unsigned char* p = (unsigned char*)shallow_new_layout(size);
    if ((r->m_type & 0x1009) == 0x1009) {
        D3DTex*  tex  = (D3DTex*)r->m_d3dTexture;
        D3DSurf* surf = 0;
        unsigned char desc[0x14];
        unsigned char surfDesc[0x14];
        unsigned int  pitch = 0;

        tex->GetSurfaceLevel(r->m_face, 0, &surf);
        surf->GetDesc(surfDesc);
        g_d3d9Device->CreateTexture((int)width, (int)height, surf, 2, desc, 0);
        g_d3d9Device->SetSamplerState((int)surf, surfDesc);

        unsigned int n = height * pitch;
        surf->Lock(desc, 0, 0x10);
        DoInsertValue(p, desc, n);
        tex->Unlock();
        surf->Release();
        ((D3DSurf*)surf)->Release();
        return p;
    }

    ((Raster*)r)->FillSpriteTexture(p, size, 0);
    return p;
}

// ---------------------------------------------------------------------------
// @ 0x007b2270  32-bit-per-pixel row blit with destination pitch
// ---------------------------------------------------------------------------
void FUN_007b2270(unsigned char* dst, int x, int y, int dstPitch, int /*unused*/,
                  const unsigned char* src, int w, int h)
{
    if (h <= 0)
        return;
    unsigned char* d = dst + y * dstPitch * 4;
    const unsigned char* s = src;
    for (int j = 0; j < h; ++j) {
        for (int i = x; i < x + w; ++i)
            memcpy(d + i * 4, s + i * 4, 4);
        s += w * 4;
        d += dstPitch * 4;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007b2320  8-bit-per-pixel row blit with destination pitch
// ---------------------------------------------------------------------------
void FUN_007b2320(unsigned char* dst, int x, int y, int dstPitch, int /*unused*/,
                  const unsigned char* src, int w, int h)
{
    if (h <= 0)
        return;
    unsigned char* d = dst + y * dstPitch;
    const unsigned char* s = src;
    for (int j = 0; j < h; ++j) {
        if (x < x + w) {
            d += x;
            s += x;
            for (int i = 0; i < w; ++i)
                d[i] = s[i];
            d -= x;
            s -= x;
        }
        s += w;
        d += dstPitch;
    }
}

// ---------------------------------------------------------------------------
// @ 0x007b2380  build a thumbnail raster from a Raster (per-face mip blit)
// ---------------------------------------------------------------------------
struct RasterFace {
    unsigned char  m_format[4];     // +0x00
    unsigned int   m_flags;         // +0x04
    unsigned int   m_unk08;         // +0x08
    unsigned short m_width;         // +0x0c
    unsigned short m_height;        // +0x0e
    unsigned char  m_depth;         // +0x10
    unsigned char  pad11[1];        // +0x11
    unsigned char  m_face;          // +0x12
    unsigned char  pad13[1];
};

// lens/offset table for the six cube faces (pairs of ints per face)
struct FaceOffset { int x, y; };
extern const FaceOffset g_faceOffsets[6];    // 0x0140fcb8

bool FUN_007b2380(void* mgr, RasterFace* r)
{
    if (r->m_unk08 == 0)
        return false;

    unsigned fourcc = *(unsigned*)r->m_format;
    unsigned width  = r->m_width;
    unsigned height = r->m_height;
    unsigned depth  = r->m_depth;

    if (fourcc == FORMAT_DXT1 || fourcc == FORMAT_DXT3 || fourcc == FORMAT_DXT5)
        depth = 0x20;

    if (r->m_flags & 0x1000) {
        unsigned pitch = width * 4;
        unsigned rows  = height * 3;
        void* dst = 0;

        if (depth == 0x20) {
            dst = eastl_alloc(rows * pitch * 4, "Graphics", 0, 0, 0, 0);
            if (rows != 0) {
                unsigned char* p = (unsigned char*)dst + 2;
                unsigned char* rowStart = p;
                unsigned nrows = rows;
                do {
                    unsigned npix = width;
                    while (npix != 0) {
                        p[-2] = 0x7f; p[-1] = 0x7f; p[0] = 0x7f; p[1] = 0xff;
                        p += 4;
                        npix--;
                    }
                    p = rowStart + width * 0x10;
                    rowStart = p;
                } while (--nrows != 0);
            }
            for (int i = 0; i < 6; ++i) {
                r->m_face = (unsigned char)i;
                void* src = FUN_007b1f40((RasterHdr*)r);
                FUN_007b2270((unsigned char*)dst,
                             g_faceOffsets[i].x * width, g_faceOffsets[i].y * height,
                             (int)pitch, (int)rows, (const unsigned char*)src,
                             (int)width, (int)height);
                operator_delete__(src);
            }
        } else if (depth == 8) {
            dst = eastl_alloc(rows * pitch, "Graphics", 0, 0, 0, 0);
            unsigned char* p = (unsigned char*)dst;
            if (rows != 0) {
                unsigned nrows = rows;
                do {
                    if (width != 0)
                        operator_new__(p, 0x7f, (int)pitch);
                    p += pitch;
                } while (--nrows != 0);
            }
            for (int i = 0; i < 6; ++i) {
                r->m_face = (unsigned char)i;
                void* src = FUN_007b1f40((RasterHdr*)r);
                FUN_007b2320((unsigned char*)dst,
                             g_faceOffsets[i].x * width, g_faceOffsets[i].y * height,
                             (int)pitch, (int)rows, (const unsigned char*)src,
                             (int)width, (int)height);
                operator_delete__(src);
            }
        }

        unsigned char desc[0x14];
        InitViewportDesc(desc, dst, (int)pitch, (int)rows, (int)depth, 0);
        desc[2] = (unsigned char)((depth == 8) + 2);
        int rc = WriteImageFile((const char*)mgr, desc);
        operator_delete__(dst);
        return rc == 0;
    }

    void* src = FUN_007b1f40((RasterHdr*)r);
    unsigned char desc[0x14];
    InitViewportDesc(desc, src, (int)width, (int)height, (int)depth, 0);
    desc[2] = (unsigned char)((depth == 8) + 2);
    int rc = WriteImageFile((const char*)mgr, desc);
    operator_delete__(src);
    return rc == 0;
}

// ---------------------------------------------------------------------------
// @ 0x007b2600  spherical angles + length from a direction vector
// ---------------------------------------------------------------------------
#pragma intrinsic(acos)
#pragma intrinsic(asin)
#pragma intrinsic(sqrt)

void FUN_007b2600(float x, float y, float z, float* outTheta, float* outPhi, float* outLen)
{
    double dx = x, dy = y, dz = z;
    double len = sqrt(dz * dz + (dy * dy + dx * dx));
    double r   = sqrt(dx * dx + dy * dy);
    double d   = len + 1e-08;
    double d2  = r + 1e-08;

    *outLen   = (float)d;
    *outTheta = (float)acos(dz / d);
    if (x < 0.0f)
        *outPhi = 3.14159274f - (float)asin(dy / d2);
    else
        *outPhi = (float)asin(dy / d2);
}

// ---------------------------------------------------------------------------
// @ 0x007b26a0  SP::cThumbnailManager::SetupThumbnailRTTs  (thiscall)
// ---------------------------------------------------------------------------
struct cRenderTargetRectID { int mPageID; int mAllocID; };

struct cIRTTManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual cRenderTargetRectID* CreateRTT(void* a, int b, int c, int d, int e, int f, int g);  // +0x10
    virtual void* v5();                                             // +0x14
    virtual void* GetRaster(int page, int alloc);                   // +0x18
    virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17();
    virtual void RegisterRTT(int page, int alloc, const char* name);         // +0x48
};

struct ThumbMgr2 {
    char pad0[0x10];
    void* mThumbRaster;                      // +0x10
    cRenderTargetRectID mThumbRectID;        // +0x14
    cRenderTargetRectID mBlurThumbRectID1;   // +0x1c
    cRenderTargetRectID mBlurThumbRectID2;   // +0x24
    char pad1[0x10b4 - 0x2c];
    cIRTTManager* mRTTMgr;                   // +0x10b4

    void SetupThumbnailRTTs(void* job, char alsoBlur);
};

void ThumbMgr2::SetupThumbnailRTTs(void* job, char alsoBlur)
{
    cRenderTargetRectID* id;
    int desc[2];

    if (alsoBlur) {
        id = mRTTMgr->CreateRTT(desc, (int)job, (int)job, 0x15, 0, -1, 0);
        mBlurThumbRectID1.mPageID  = id->mPageID;
        mBlurThumbRectID1.mAllocID = id->mAllocID;
        mRTTMgr->RegisterRTT(id->mPageID, id->mAllocID, "ThumbnailBlurRTT");

        id = mRTTMgr->CreateRTT(desc, (int)job, (int)job, 0x15, 0, -1, 0);
        mBlurThumbRectID2.mPageID  = id->mPageID;
        mBlurThumbRectID2.mAllocID = id->mAllocID;
        mRTTMgr->RegisterRTT(id->mPageID, id->mAllocID, "ThumbnailBlurRTT");
    }

    id = mRTTMgr->CreateRTT(desc, (int)job, (int)job, 0x15, 0, -1, 0);
    mThumbRectID.mPageID  = id->mPageID;
    mThumbRectID.mAllocID = id->mAllocID;
    mRTTMgr->RegisterRTT(id->mPageID, id->mAllocID, "ThumbnailRTT");

    mThumbRaster = mRTTMgr->GetRaster(mThumbRectID.mPageID, mThumbRectID.mAllocID);
}

// ---------------------------------------------------------------------------
// intrusive texture-instance pointers (same shape as TexPtr in s00776730)
// ---------------------------------------------------------------------------
static __forceinline long AtomicAdd(volatile long* p, long v)
{
    return _InterlockedExchangeAdd(p, v);
}
struct cTexInst {
    void* vt; unsigned flags; volatile long refCount;
    void AddRef() { AtomicAdd(&refCount, 1); }
    void Release()
    {
        volatile long* rc = &refCount;
        AtomicAdd(rc, -1);
        long v = AtomicAdd(rc, 0);
        if (v < 1)
            AtomicAdd(rc, 1);
        else
            AtomicAdd(rc, 0);
    }
};
struct TexRef {
    cTexInst* p;
    TexRef() : p(0) {}
    TexRef(cTexInst* o) : p(o) { if (o) o->AddRef(); }
    TexRef(const TexRef& o) : p(o.p) { if (p) p->AddRef(); }
    ~TexRef() { if (p) p->Release(); }
};
struct TexRefVec {
    TexRef* mpBegin; TexRef* mpEnd; TexRef* mpCap;
    void DoInsertValue(TexRef* pos, const TexRef* v);   // 0x00425a80
    void push_back(cTexInst* raw, const TexRef& v) {
        if (mpEnd < mpCap) {
            TexRef* d = mpEnd;
            mpEnd = d + 1;
            if (d) {
                d->p = raw;
                raw->AddRef();
            }
        } else {
            DoInsertValue(mpEnd, &v);
        }
    }
    void push_back(const TexRef& v) {
        if (mpEnd < mpCap) {
            TexRef* d = mpEnd;
            mpEnd = d + 1;
            if (d) new (d) TexRef(v);
        } else {
            DoInsertValue(mpEnd, &v);
        }
    }
};

struct IPropList { virtual void v0(); virtual void Release(); };
struct PropListRef {
    IPropList* p;
    PropListRef() : p(0) {}
    ~PropListRef() { if (p) p->Release(); }
    void reset() { if (p) { IPropList* q = p; p = 0; q->Release(); } }
};
struct IPropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropertyList(unsigned grp, unsigned inst, PropListRef* out);   // +0x2c
};
IPropMgr* __cdecl PropertyManager();                 // 0x0067DE30
bool __cdecl GetPropArray(void* list, unsigned id, int* count, char** data);   // 0x006A0AE0
struct PropKey { unsigned group, x, inst; };

struct TexPreload {
    char pad0[0xc];
    TexRefVec mQueue;                               // +0x0c
    char pad1[8];
    TexRefVec mReady;                               // +0x20
    bool MoveReady();                               // 0x007B19C0
    void Push(cTexInst* t);                         // 0x007B1AF0
    void PreloadTextureList(void* list);            // 0x007B1DE0
    void PreloadTextureList(PropKey* key);          // 0x007B1E90
};

// @ 0x007b19c0
bool TexPreload::MoveReady()
{
    while (mQueue.mpBegin != mQueue.mpEnd) {
        cTexInst* raw = mQueue.mpEnd[-1].p;
        if (!(raw->flags & 1))
            return false;
        {
            TexRef t(raw);
            mReady.push_back(raw, t);
        }
        --mQueue.mpEnd;
        mQueue.mpEnd->~TexRef();
    }
    return true;
}

// @ 0x007b1af0
void TexPreload::Push(cTexInst* raw)
{
    if (raw) {
        TexRef t(raw);
        mQueue.push_back(raw, t);
    }
}

// @ 0x007b1de0
void TexPreload::PreloadTextureList(void* list)
{
    char* data = 0;
    int count = 0;
    if (GetPropArray(list, 0x85155a0c, &count, &data)) {
        int off = 0;
        for (int i = 0; i < count; i++) {
            S3* e = (S3*)(data + off);
            IFac* fac = (IFac*)FUN_0067dd60();
            Push((cTexInst*)fac->v7(*e, 0));
            off += 12;
        }
    }
}

// @ 0x007b1e90
void TexPreload::PreloadTextureList(PropKey* key)
{
    unsigned id = key->inst;
    if (id == 0x40464100) id = 0x40464200;
    PropListRef list;
    IPropMgr* mgr = PropertyManager();
    list.reset();
    if (mgr->GetPropertyList(key->group, id, &list))
        PreloadTextureList((void*)list.p);
}

// ---------------------------------------------------------------------------
// 0x007b1bb0 rectangle-packing tree node placement (returns node index or -1)
// ---------------------------------------------------------------------------
struct Span { int d[8]; Span* Init(int, int, int, int, int); };   // 0x007AE920
struct PackNode {                                   // 0x20 bytes
    int x0, y0, x1, y1;
    int unk;
    int c1, c2;
    unsigned char used; char padn[3];
    void Set(Span*);                                // 0x0076D9A0
};
struct PackTree {
    PackNode* nodes;
    int Alloc();                                    // 0x007B10A0
    int Place(int idx, int w, int h);               // 0x007B1BB0
};
// @ 0x007b1bb0
int PackTree::Place(int idx, int w, int h)
{
    PackNode* n = &nodes[idx];
    if (n->x1 - n->x0 >= w) {
        while (n->y1 - n->y0 >= h) {
            if (n->c1 >= 0) {
                int r = Place(nodes[idx].c1, w, h);
                if (r < 0)
                    r = Place(nodes[idx].c2, w, h);
                return r;
            }
            if (n->used)
                return -1;
            if (n->x1 - n->x0 == w && n->y1 - n->y0 == h) {
                nodes[idx].used = 1;
                return idx;
            }
            int a = Alloc();
            int b = Alloc();
            nodes[idx].c1 = a;
            nodes[idx].c2 = b;
            PackNode* base = nodes;
            int dw = (base[idx].x1 - base[idx].x0) - w;
            int dh = (base[idx].y1 - base[idx].y0) - h;
            Span sp;
            int ex, ey, ew, eh;
            if (dh < dw) {
                base[a].Set(sp.Init(base[idx].x0, base[idx].y0, w, base[idx].y1 - base[idx].y0, idx));
                base = nodes;
                ex = base[idx].x0 + w; ey = base[idx].y0; ew = dw; eh = base[idx].y1 - base[idx].y0;
            } else {
                base[a].Set(sp.Init(base[idx].x0, base[idx].y0, base[idx].x1 - base[idx].x0, h, idx));
                base = nodes;
                ex = base[idx].x0; ey = base[idx].y0 + h; ew = base[idx].x1 - base[idx].x0; eh = dh;
            }
            base[b].Set(sp.Init(ex, ey, ew, eh, idx));
            idx = nodes[idx].c1;
            n = &nodes[idx];
            if (n->x1 - n->x0 < w)
                return -1;
        }
    }
    return -1;
}
