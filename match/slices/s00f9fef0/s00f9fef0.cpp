// Slice s00f9fef0 -- 16 functions of SPTerrain/SPTerrainSphere.obj and its neighbours.
//   00f9fef0  cTerrainSphere-ish: re-register RTT textures + property list setup (thiscall, ret 4)
//   00fa0010  bool: copy a face image rect to a surface (A faces, +0x160)
//   00fa0070  same for the B faces (+0x148)
//   00fa00d0  same for the C faces (+0x178)
//   00fa0130  BuildSurfaceOrientation(from a direction vector)
//   00fa01e0  build a decal box (TerrainEditor/DecalBoxBuilder)
//   00fa0360  static shutdown of the RTT textures / terrain sphere globals
//   00fa0400  static init of the RTT textures / terrain sphere globals
//   00fa0560  post a terrain-geometry-changed message
//   00fa0670  a 16-byte-element Hoare partition (sort helper)
//   00fa06e0  insertion pass of a 16-byte-element sort
//   00fa0780  the terrain sphere resource destructor (GmeEditorResBase-derived)
//   00fa0dc0  placement-construct a 0x80 buffer at +0x6d8
//   00fa0e10/0e40/0e60  a padding-backed dirty-flag byte at +0x368/+0x369
//   00fa0f10  AutoRefCount-holding job release (+0x10/+0x14)
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>
#include <string.h>

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement, _InterlockedExchange)

// ---- the refcount release template the original uses everywhere ------------
struct AtomicRef {
    char pad00[8];
    volatile long mnRefCount;
    int Release()
    {
        _InterlockedDecrement(&mnRefCount);
        if (_InterlockedExchangeAdd(&mnRefCount, 0) < 1) {
            _InterlockedIncrement(&mnRefCount);
            return 1;
        }
        return _InterlockedExchangeAdd(&mnRefCount, 0);
    }
};

// ---- EAAllocate / free -----------------------------------------------------
void* __cdecl EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void  __cdecl operator_delete(void* p);                                                     // 0x00f47380
void* __cdecl operator_new_arr(void* dst, unsigned int zero, unsigned int size);            // 0x011e073e

// A service object (the texture/resource factory).  vtbl +0x34 = Release(ptr).
struct ServiceObj {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void Release(void* p);   // +0x34
};
ServiceObj* FUN_0067dd60();          // 0x0067dd60
ServiceObj* FUN_0067dd50();          // 0x0067dd50
ServiceObj* FUN_0067dda0();          // 0x0067dda0

// A texture-ish instance: [0] = data pointer, [+4] = flags (bit0 = resident).
struct TexInst {
    uint32_t* mpData;   // +0x00
    uint32_t  mFlags;   // +0x04
};

// CopyImageRectToSurface (0x00f9f200) and its two siblings.  All plain cdecl,
// (void* data, int other, int face, const float* rect).
char __cdecl CopyImageRectToSurface(void* data, int other, int face, const float* rect);    // 0x00f9f200
char __cdecl FUN_00f9f360(void* data, int other, int face, const float* rect);              // 0x00f9f360
char __cdecl FUN_00f9f4c0(void* data, int other, int face, const float* rect);              // 0x00f9f4c0

// The terrain sphere object that owns the three 6-entry texture arrays.
struct TerrainSphereLike {
    char pad00[0x2c];
    void* mpSurfaces;            // +0x2c -> +8 / +0xc / +0x10 are the three surfaces
    char pad30[0x148 - 0x30];
    TexInst* mFacesB[6];         // +0x148
    TexInst* mFacesA[6];         // +0x160
    TexInst* mFacesC[6];         // +0x178

    bool CopyFaceA(int face, const float* rect);
    bool CopyFaceB(int face, const float* rect);
    bool CopyFaceC(int face, const float* rect);
};

struct SurfaceHolder {
    char pad0[8];
    void* mSurface8;
    void* mSurfaceC;
    void* mSurface10;
};

// @ 0x00fa0010
bool TerrainSphereLike::CopyFaceA(int face, const float* rect)
{
    if (!mpSurfaces)
        return false;
    void* other = ((SurfaceHolder*)mpSurfaces)->mSurface8;
    if (!other)
        return false;
    TexInst* t = mFacesA[face];
    if (!(t->mFlags & 1))
        FUN_0067dd60()->Release(t);
    bool ok = CopyImageRectToSurface((void*)t->mpData, (int)other, face, rect) != 0;
    return ok;
}

// @ 0x00fa0070
bool TerrainSphereLike::CopyFaceB(int face, const float* rect)
{
    if (!mpSurfaces)
        return false;
    void* other = ((SurfaceHolder*)mpSurfaces)->mSurfaceC;
    if (!other)
        return false;
    TexInst* t = mFacesB[face];
    if (!(t->mFlags & 1))
        FUN_0067dd60()->Release(t);
    bool ok = FUN_00f9f360((void*)t->mpData, (int)other, face, rect) != 0;
    return ok;
}

// @ 0x00fa00d0
bool TerrainSphereLike::CopyFaceC(int face, const float* rect)
{
    if (!mpSurfaces)
        return false;
    void* other = ((SurfaceHolder*)mpSurfaces)->mSurface10;
    if (!other)
        return false;
    TexInst* t = mFacesC[face];
    if (!(t->mFlags & 1))
        FUN_0067dd60()->Release(t);
    bool ok = FUN_00f9f4c0((void*)t->mpData, (int)other, face, rect) != 0;
    return ok;
}

// ---- the padding-backed dirty-flag bytes.  Offset +0x368 is reached as
//      `this + *(this+0x36c) + 0x368`; +0x369 as `this - *(this+0x36c) + 0x369`.
struct DirtyFlag {
    char pad000[0x368];
    char pad368[2];
    char pad36a[2];
    int  mBackOffset;            // +0x36c
    char pad370[0x6d8 - 0x370];
    char mBuffer[0x80];          // +0x6d8

    char& Flag0() { return *(char*)(mBackOffset + (char*)this + 0x368); }
    char& Flag1() { return *(char*)((char*)this - mBackOffset + 0x369); }

    void InitBuffer();           // 0x00fa0dc0
    void SetFlag(bool which);    // 0x00fa0e10
    char* OrFlag(unsigned char bits);  // 0x00fa0e40
    bool TestFlag(unsigned char bits); // 0x00fa0e60
};

// @ 0x00fa0dc0
void DirtyFlag::InitBuffer()
{
    operator_new_arr(&mBuffer[0], 0, 0x80);
}

// @ 0x00fa0e10
void DirtyFlag::SetFlag(bool which)
{
    if (which)
        Flag0() = 0;
    else
        Flag1() = 0;
}

// @ 0x00fa0e40
char* DirtyFlag::OrFlag(unsigned char bits)
{
    int off = mBackOffset;
    char* base = (char*)this;
    char* p = base - off + 0x369;
    *p |= bits;
    return p;
}

// @ 0x00fa0e60
bool DirtyFlag::TestFlag(unsigned char bits)
{
    return (Flag0() & bits) != 0;
}

// ---- a job holder: an AutoRefCount<SP::cJob> embedded at +0x10 ------------
struct VtblHolder {
    virtual void v00();
    virtual void v04();
    virtual void v08(int);   // +0x08
};

struct AutoRefLike {
    VtblHolder* mpObject;      // +0x00 (so +0x10 in JobHolder)
    volatile long mnRef;       // +0x04 (so +0x14 in JobHolder)

    int Release();
};

struct JobHolder {
    char pad00[0x10];
    AutoRefLike mObj;          // +0x10

    int Release();             // 0x00fa0f10
};

// @ 0x00fa0f10
int JobHolder::Release()
{
    VtblHolder* p = mObj.mpObject;
    long v = _InterlockedDecrement(&mObj.mnRef);
    if (v == 0) {
        _InterlockedExchange(&mObj.mnRef, 1);
        if (p)
            p->v08(1);
    }
    return v;
}

// ---- quaternion / vector helpers -------------------------------------------
struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

void __cdecl QuaternionFromDirections(Quat* out, const Vec3* a, const Vec3* b);  // 0x00698180
extern const Vec3 kUpDir;                 // 0x016ca404
extern const float kOneSquared;           // 0x01485720 = 1.0f
extern const Quat kDefaultQuat;           // 0x015b11c8

// The cTerrainSphere members this slice calls.
struct TerrainSphereQ {
    Quat BuildSurfaceOrientationFromDir(const Vec3& dir) const;                   // 0x00fa0130
    Quat BuildSurfaceOrientation(const Vec3& dir, const Quat& q) const;           // 0x00f9c960
};

// @ 0x00fa0130
Quat TerrainSphereQ::BuildSurfaceOrientationFromDir(const Vec3& dir) const
{
    if (dir.x * dir.x + dir.y * dir.y + dir.z * dir.z > 1.0f) {
        Quat q;
        QuaternionFromDirections(&q, &kUpDir, &dir);
        return BuildSurfaceOrientation(dir, q);
    }
    return kDefaultQuat;
}

// ---- a 16-byte element with an unsigned key at +8, sorted by the key --------
struct Elem16 {
    uint32_t w0, w1, key, w3;    // key at +8 (unsigned)
};

// Generic sort helpers of this object (16-byte elements, key at +8).
void __cdecl FUN_00f9f7b0(Elem16* first, Elem16* last, unsigned key);   // 0x00f9f7b0
void __cdecl FUN_00f9f810(Elem16* first, Elem16* last, unsigned key);   // 0x00f9f810
void __cdecl FUN_00f9af30(Elem16* first, int a, int n, int b,
                          Elem16 tmp, unsigned key); // 0x00f9af30

// @ 0x00fa0670
void __cdecl PartitionElem16(Elem16* lo, Elem16* hi, void* a2, void* a4, unsigned key)
{
    for (;;) {
        for (; lo->key < key; lo = lo + 1) { }
        for (; key < (hi - 1)->key; hi = hi - 1) { }
        if (lo >= hi)
            return;
        Elem16 tmp = *lo;
        *lo = *hi;
        *hi = tmp;
        lo = lo + 1;
    }
}

// @ 0x00fa06e0
void __cdecl SortElem16Pass(Elem16* first, Elem16* last, Elem16* end, unsigned key)
{
    FUN_00f9f7b0(first, last, key);
    for (Elem16* p = last; p < end; ++p) {
        if (p->key < first->key) {
            Elem16 tmp = *p;
            *p = *first;
            FUN_00f9af30(first, 0, (int)(last - first), 0, tmp, key);
        }
    }
    FUN_00f9f810(first, last, key);
}

// ---- the terrain RTT texture globals ---------------------------------------
struct RTTVtbl {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void FreeRTT(unsigned a, unsigned b);   // +0x14
};
struct RTTMgr { RTTVtbl* mpVtbl; };              // FUN_0067dda0 result

extern unsigned g_rttHandles[6];        // 0x016c9e44
extern unsigned g_rttNames[6][2];       // 0x016ca3d4
extern unsigned char g_rttActive;       // 0x016c9e60
extern void* g_pRTT0;                   // 0x016c9f58
extern void* g_pRTT1;                   // 0x016c9f5c
extern unsigned g_texTerrain;           // 0x016c9e40
extern void* g_pSomeTex;                // 0x016c9e6c
extern unsigned g_colorMap[2];          // 0x015b1218
extern unsigned char g_sphereActive;    // 0x016c9e5c
extern int g_rttRefCount;               // 0x016c9e88

extern void* g_viewerObj;               // 0x016ca410 (a cViewer)

void FUN_00f9e1f0();                    // 0x00f9e1f0
void FUN_00f9e350();                    // 0x00f9e350
void FUN_007c3ba0();                    // 0x007c3ba0
void FUN_00762a00(void* p);             // 0x00762a00

// @ 0x00fa0360
void ShutdownRTTSphere()
{
    if (!g_rttActive)
        return;
    RTTMgr* mgr = (RTTMgr*)FUN_0067dda0();
    if (g_pRTT0)
        FUN_00f9e1f0();
    if (g_pRTT1)
        FUN_00f9e350();
    unsigned* h = g_rttHandles;
    unsigned* n = (unsigned*)g_rttNames;
    do {
        mgr->mpVtbl->FreeRTT(n[0], n[1]);
        *h = 0;
        n += 2;
        ++h;
    } while ((int)n < 0x16ca404);
    mgr->mpVtbl->FreeRTT(g_colorMap[0], g_colorMap[1]);
    g_texTerrain = 0;
    FUN_007c3ba0();
    FUN_00762a00(g_pSomeTex);
}

// ---- more service slots needed by the RTT init -----------------------------
struct RTTVtbl2 {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual unsigned* CreateTex(unsigned* out, unsigned w, unsigned h, int fmt, int a, int b, int c); // +0x10
    virtual void v14();
    virtual unsigned MakeTexFromRes(unsigned a, unsigned b);   // +0x18
    virtual unsigned MakeTexFromRes2(unsigned a, unsigned b);  // +0x1c
    virtual void pad20();
    virtual void pad24();
    virtual void pad28();
    virtual void pad2c();
    virtual void pad30();
    virtual void pad34();
    virtual void pad38();
    virtual void pad3c();
    virtual void pad40();
    virtual void pad44();
    virtual void SetName(unsigned a, unsigned b, const char* name);  // +0x48
};
struct RTTMgr2 { RTTVtbl2* mpVtbl; };

bool __cdecl ViewerInit(void* viewer, bool b);              // 0x007c4dd0
void __cdecl ViewerClear(void* viewer, unsigned a);         // 0x007c3cc0
void __cdecl ViewerSetTex(void* viewer, unsigned a);        // 0x007c3cb0
void __cdecl ViewerSetRect(void* viewer, unsigned short* p); // 0x007c4a60

// @ 0x00fa0400
void InitRTTSphere()
{
    RTTMgr2* mgr = (RTTMgr2*)FUN_0067dda0();
    for (int i = 0; i < 6; ++i) {
        unsigned out[2];
        g_rttHandles[i] = 0;
        mgr->mpVtbl->CreateTex(out, 0x100, 0x100, 0x15, 0, -1, 0);
        g_rttNames[i][0] = out[0];
        g_rttNames[i][1] = out[1];
        mgr->mpVtbl->SetName(out[0], out[1], "TerrainRTTs");
        g_rttHandles[i] = mgr->mpVtbl->MakeTexFromRes2(out[0], out[1]);
    }
    {
        unsigned out[2];
        mgr->mpVtbl->CreateTex(out, 0x100, 0x100, 0x15, 0, 0x956a72c0, 0);
        g_colorMap[0] = out[0];
        g_colorMap[1] = out[1];
        mgr->mpVtbl->SetName(out[0], out[1], "TerrainColorMap");
        g_texTerrain = mgr->mpVtbl->MakeTexFromRes(out[0], out[1]);
    }
    ViewerInit(g_viewerObj, true);
    ViewerClear(g_viewerObj, 0);
    ViewerSetTex(g_viewerObj, g_texTerrain);
    unsigned short v[4];
    v[0] = 0; v[1] = 0; v[2] = 0x100; v[3] = 0x100;
    ViewerSetRect(g_viewerObj, v);
}

// ---- the geometry-changed message object -----------------------------------
struct MsgVtbl { virtual void v00(); virtual int AddRef(); virtual void v08(); virtual void v0c(); };
struct MsgObj {
    MsgVtbl* mpVtbl;    // +0x00
    volatile long mRef; // +0x04
    int f08;            // +0x08
    char pad0c[4];
    int f10;            // +0x10
    char pad14[0x1c];
    MsgVtbl* mpVtbl30;  // +0x30
    char pad34[4];
    int f38;            // +0x38
};
void __cdecl FUN_00f99f20(int self, int a2, int a3, int a4);  // 0x00f99f20

// The class that carries AddGeometryChangeMessage (its +0x8a0 member is the handler).
struct GeomMsgOwner {
    char pad000[0x8a0];
    void* mpHandler;    // +0x8a0
    int   mMsgId;       // +0x8a4

    void AddGeometryChangeMessage(int a2, int a3);   // 0x00fa0560
};

// @ 0x00fa0560
void GeomMsgOwner::AddGeometryChangeMessage(int a2, int a3)
{
    if (!mpHandler)
        return;
    MsgObj* p = (MsgObj*)EAAllocate(0x40, "Terrain/Sphere/kMessageTerrainGeometryChange", 0, 0, 0, 0);
    if (p) {
        p->f38 = 0;
        p->mpVtbl = (MsgVtbl*)0x013eb90c;
        _InterlockedExchange((volatile long*)&p->mRef, 0);
        p->mpVtbl = (MsgVtbl*)0x013eb844;
        p->mpVtbl30 = 0;
        p->mpVtbl->AddRef();
    } else {
        p = 0;
    }
    p->mpVtbl30 = (MsgVtbl*)0x0182c582;
    p->f08 = a2;
    p->f10 = a3;
    FUN_00f99f20((int)this, a3, a2, (int)this + 0x898);
    ServiceObj* m = FUN_0067dd50();
    (void)m;
    mMsgId = 0;
    p->mpVtbl30->v08();
}

// ---- decal-box construction (uses the editor's decal box builder) -----------
unsigned __cdecl GetImageResourceImpl(void* dst, unsigned id);   // 0x00576650
void*    __cdecl TerrainEditorImpl(void* a, void* b, void* c, void* d, void* e, void* f,
                                   int, int, int, int);          // 0x00f48a70
void*    __cdecl DecalBoxBuilderImpl(void* a, void* b, void* c, void* d, void* e, void* f,
                                     int, int, int, int);        // 0x00f6c940
void*    __cdecl QuaternionFromMatrix33(void* out, const void* m, int a);  // 0x00472b80

struct ImageResHeader {                    // 0x78-byte block used by GetImageResource
    char pad000[0x78];
};
struct BuilderParam {                      // 0x7c-byte block
    char pad000[0x7c];
};

// @ 0x00fa01e0
void __cdecl BuildDecalBox(void* xform /*arg0*/, void* data /*arg1*/,
                           unsigned id /*arg2*/, void* a3 /*arg3*/)
{
    ImageResHeader res;
    BuilderParam    bp;
    Quat   q;
    unsigned v[4];

    operator_new_arr(&res, 0, 0x78);
    GetImageResourceImpl(&res, id);
    v[0] = (id == 0);
    v[1] = 0x3f800000;
    v[2] = (unsigned)data;
    v[3] = 0;

    operator_new_arr(&bp, 0, 0x7c);
    memcpy(&bp, (const void*)0x01490428, 0x44);

    QuaternionFromMatrix33(&q, (const char*)xform + 0x14, 0);

    TerrainEditorImpl((char*)xform + 4, &q, v, &res, &bp, a3, 0, 0, 0, 0);
    DecalBoxBuilderImpl((char*)xform + 4, &q, v, &res, &bp, a3, 0, 0, 0, 0);

    if (v[0] != 0)
        ((AtomicRef*)(v[0] + 8))->Release();
}

// ---- the terrain-sphere resource destructor ---------------------------------
// The class has five vtables (multiple inheritance) followed by a large set of
// refcounted members, eastl vectors and a couple of virtual-owning pointers.
struct ResVtables {
    void* pv00; void* pv04; void* pv08; void* pv0c; void* pv10;
};
inline void RelPtr(void* p) { if (p) ((AtomicRef*)((char*)p + 8))->Release(); }
inline void VirtualRelease(void* p, int slot, int arg)
{
    if (!p) return;
    void** vt = *(void***)p;
    ((void(__thiscall*)(void*, int))vt[slot])(p, arg);
}
inline void FreeVector(void* begin, void* end)
{
    if (begin) {
        unsigned n = (unsigned)((char*)end - (char*)begin) >> 2;
        (void)n;
    }
}
void __cdecl DestroyRangeFree(void** first, void** last);  // 0x0070f520
void __cdecl FreeBlock(void* p);                            // 0x005c3dc0

// A stub owner class so the destructor can be a real member (thiscall).
struct TerrainSphereRes { void Dtor(); };

// @ 0x00fa0780
void TerrainSphereRes::Dtor()
{
    char* p = (char*)this;
    *(void**)(p + 0x00) = (void*)0x01490be8;
    *(void**)(p + 0x04) = (void*)0x01490bd4;
    *(void**)(p + 0x08) = (void*)0x01490bc4;
    *(void**)(p + 0x0c) = (void*)0x01490ba0;
    *(void**)(p + 0x10) = (void*)0x01490b8c;
    _InterlockedDecrement((volatile long*)0x016c9e88);
    _InterlockedExchange((volatile long*)0x016c9e5c, 0);

    VirtualRelease(*(void**)(p + 0x28), 1, 1);
    VirtualRelease(*(void**)(p + 0x214), 1, 1);

    RelPtr(*(void**)(p + 0x2c));
    RelPtr(*(void**)(p + 0x308));

    *(void**)(p + 0x30) = (void*)0x01490b80;
    *(void**)(p + 0x74) = (void*)0x01490b80;
    *(void**)(p + 0xb8) = (void*)0x01490b80;

    for (int i = 0; i < 6; ++i)
        RelPtr(*(void**)(p + 0x178 - i * 4));
    for (int i = 0; i < 6; ++i)
        RelPtr(*(void**)(p + 0x190 - i * 4));
    for (int i = 0; i < 6; ++i)
        RelPtr(*(void**)(p + 0x160 - i * 4));

    *(void**)(p + 0x00) = (void*)0x013eb938;
    *(void**)(p + 0x04) = (void*)0x013eb394;
}

// ---- RTT re-registration on the active terrain sphere -----------------------
bool __cdecl AppPropertyGetDescription(unsigned id);        // 0x006a25a0 (this = _sAppProperties)
void __cdecl InitializeStaticRTTTextures();                 // 0x00f96b40
void __cdecl FUN_00f9e3a0(void* self);                      // 0x00f9e3a0
void* __cdecl ModelManagerGet();                            // 0x0067dd80
void* __cdecl EffectsManagerGet();                          // 0x0067ddd0

// A registration object whose vtable is called by slot index.
struct RegObj { void** mpVtbl; };
struct PropList {
    char pad[8];
    unsigned char GetDescription(unsigned id);
};
struct ModelMgrObj { void** mpVtbl; };
struct ModelInstObj { void** mpVtbl; };
struct EffectMgrObj { void** mpVtbl; };
struct EffectInstObj { void** mpVtbl; };
struct TerrainSphereReg : RegObj { void Register(RegObj* obj); };

// @ 0x00f9fef0
void TerrainSphereReg::Register(RegObj* obj)
{
    void* self = this;
    void* handle = (self == 0) ? 0 : (char*)self + 4;

    if (((void*(__thiscall*)(RegObj*, int))obj->mpVtbl[0x58 / 4])(obj, 8) != handle) {
        PropList* props = (PropList*)0x015fd918;   // _sAppProperties
        unsigned char cVar2 = props->GetDescription(0x201a4e50);
        unsigned char cVar3 = props->GetDescription(0xe13ce337);
        if (cVar2) {
            InitializeStaticRTTTextures();
            if (cVar3)
                FUN_00f9e3a0(self);
        }
        ((void(__thiscall*)(RegObj*, void*, int, int))obj->mpVtbl[0x4c / 4])(obj, handle, 7, 0);
        ((void(__thiscall*)(RegObj*, void*, int, int))obj->mpVtbl[0x4c / 4])(obj, handle, 8, 0);
        ((void(__thiscall*)(RegObj*, void*, int, int))obj->mpVtbl[0x4c / 4])(obj, handle, 0x21, 0);
        ModelMgrObj* mm = (ModelMgrObj*)ModelManagerGet();
        ModelInstObj* mi = (ModelInstObj*)((void*(__thiscall*)(ModelMgrObj*, void*))mm->mpVtbl[0x1c / 4])(mm, (void*)0x03fbae24);
        void* h = ((void*(__thiscall*)(ModelInstObj*, int, int))mi->mpVtbl[0x13c / 4])(mi, 10, 0);
        ((void(__thiscall*)(RegObj*, void*))obj->mpVtbl[0x4c / 4])(obj, h);
        ((void(__thiscall*)(ModelInstObj*, int))mi->mpVtbl[0x134 / 4])(mi, 1);
        EffectMgrObj* em = (EffectMgrObj*)EffectsManagerGet();
        EffectInstObj* ei = (EffectInstObj*)((void*(__thiscall*)(EffectMgrObj*, void*))em->mpVtbl[0x54 / 4])(em, (void*)0x03fbae24);
        ((void(__thiscall*)(EffectInstObj*, int))ei->mpVtbl[0x0c / 4])(ei, 0);
    }
}

