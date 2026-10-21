// Slice s00a76cf0 — EA::Swarm "MapInfo" component, part 2 (Swarm::MapInfo class,
// kind 6 object = MapInfoD7 in the neighbouring slice's spelling).
// Object file Swarm/Maps.obj.  Source rebuilt from the retail disassembly; the
// class layouts are the ones already established in match/slices/s00a75000 and
// match/slices/s00a77c80.
// flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

// Class layout note: the vtable pointer at this+0x00 belongs to IRefObj; the
// second vtable slot (??_7GmeRefCount, stored at +0x04 in the original) is not
// reproduced by the C++ base-class layout, so the constructor stores it
// explicitly through a volatile pointer.// ------------------------------------------------------------------ referenced data
extern "C" {
extern float g_1676d7c;   // Vector3 zero-init (dynamic initializer 0x013094a0)
extern float g_1676d80;
extern float g_1676d84;
extern float g_1676da0;
extern float g_1676da4;
extern float g_1676da8;
extern float g_1676dac;
extern const float g_13f6a28;   // -4.0f
extern const float g_14853e0;   //  4.0f
extern const float g_13eeda0;   //  8.0f
}

// ------------------------------------------------------------------ interfaces
struct IRefObj { virtual void AddRef(); virtual void Release(); };   // slots 0 / 4

// A refcounted Swarm value object reached through +0x70/+0x74/+0x78; slot
// offsets from the call sites (Update +8, ReleaseTemps +0xc, SumCounts +0x10,
// ContainsPoint +0x18, IsEmpty +0x1c, Eval +0x20, EvalVec* +0x24/28/2c).
struct IValue {
    virtual void  v00();
    virtual void  v04();
    virtual void  AddRef();                                   // +0x08
    virtual void  Release();                                  // +0x0c
    virtual int   Count();                                    // +0x10
    virtual void  v14();
    virtual bool  Test(float* p);                             // +0x18
    virtual bool  Empty();                                    // +0x1c
    virtual float Scale(float x);                             // +0x20
    virtual float* EvalVec3(float* out, int id);              // +0x24
    virtual float* EvalVec4(float* out, int id);              // +0x28
    virtual float* EvalVec4b(float* out, int id);             // +0x2c
};

// Grid-owner interface reached through +0x38 (same as cMapInfo's).
struct IcOwner {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual bool RequestGrid(void* src, int* a, int* b, uint32_t** out);   // slot 0x18
};

// The pixel-source object reached through +0x7c: a refcounted object with a
// packed-colour fetch (slot 0x2c).
struct IPxSource : IRefObj {
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual IValue* Fetch(uint32_t a, uint32_t b);   // slot 0x2c
};

// ------------------------------------------------------------------ MapInfo object family
struct SwarmRef : IRefObj {
    int      mRefCount;     // +0x04
    SwarmRef() { mRefCount = 0; }
};

// EA::Swarm::MapInfo, grid-kind 6 variant (0x80 bytes).
// Member names/offsets follow match/slices/s00a75000 (cMapInfo) where the offset
// coincides; this variant stores four Vec4 "point"/"colour" tuples and a
// packed-colour source object.
struct MapInfo : SwarmRef {
    uint32_t m08;                       // +0x08
    uint32_t m0c;                       // +0x0c
    uint32_t m10;                       // +0x10  nesting counter (AddRef/Release)
    uint32_t m14;                       // +0x14  operation kind (0..6)
    float    m18;                       // +0x18  rect min X
    float    m1c;                       // +0x1c  rect min Y
    float    m20;                       // +0x20  rect max X
    float    m24;                       // +0x24  rect max Y
    uint32_t m28;                       // +0x28  packed colour 0 (grid source a)
    uint32_t m2c;                       // +0x2c  packed colour 0 (grid source b)
    uint32_t m30;                       // +0x30
    uint32_t m34;                       // +0x34
    uint32_t m38;                       // +0x38
    uint32_t m3c;                       // +0x3c
    float    m40, m44, m48, m4c;        // +0x40  tuple 0 (point or colour)
    float    m50, m54, m58, m5c;        // +0x50  tuple 1
    float    m60, m64, m68, m6c;        // +0x60  tuple 2
    IValue* mp70;                       // +0x70
    IValue* mp74;                       // +0x74
    IValue* mp78;                       // +0x78
    IPxSource* mp7c;                    // +0x7c

    MapInfo();                                                        // 0x00a76cf0
    void Update();                                                    // 0x00a76df0
    void ReleaseTemps();                                              // 0x00a76ef0
    int  SumCounts();                                                 // 0x00a76f70
    void GetRect(float* out);                                         // 0x00a76fb0
    bool ContainsPoint(float* p);                                     // 0x00a77020
    bool IsEmpty();                                                   // 0x00a770a0
    float Eval(float x);                                              // 0x00a77100
    float* EvalVec3(float* out, int id);                              // 0x00a77250
    float* EvalVec4(float* out, int id);                              // 0x00a775a0
    float* EvalVec4b(float* out, int id);                             // 0x00a77830
    void Set(int kind, float* rect, IPxSource* src);                  // 0x00a77b70
};

// ------------------------------------------------------------------ free helpers (another slice, declared for the call sites)
void  cMapInfo_SortRect2(float* out, const float* a, const float* b);    // 0x00a753b0
void  cMapInfo_SortRect3(float* out, const float* b, const float* a);    // 0x00a75410
void  cMapInfo_SortRect3R(float* out, const float* b, const float* a);   // 0x00a75480
void  Swarm_Normalize(float* out, const float* v);                       // 0x006e6df0
void  Swarm_Min(float* out, const float* a, const float* b);             // 0x006e6e30
void  __cdecl MapRectMin(float* out, const float* a, const float* b);    // 0x00a753b0

// ---------------------------------------------------------------------------
// @ 0x00a76cf0
// ---------------------------------------------------------------------------
MapInfo::MapInfo()
{
    *(void* volatile*)this = 0;      // placeholder for the GmeRefCount vtable
    *(void* volatile*)((char*)this + 4) = 0;   // second store of the same vtable
    m08 = 0;
    m0c = 0;
    m10 = 1;
    m28 = 0xffffffff;
    m2c = 0xffffffff;
    m30 = 0xffffffff;
    m34 = 0xffffffff;
    m38 = 0xffffffff;
    m3c = 0xffffffff;
    m40 = g_1676da0;
    m44 = g_1676da4;
    m48 = g_1676da8;
    m4c = g_1676dac;
    m50 = g_1676da0;
    m54 = g_1676da4;
    m58 = g_1676da8;
    m5c = g_1676dac;
    m60 = g_1676da0;
    m64 = g_1676da4;
    m68 = g_1676da8;
    m6c = g_1676dac;
    mp70 = 0;
    mp74 = 0;
    mp78 = 0;
    mp7c = 0;}

// ---------------------------------------------------------------------------
// @ 0x00a76df0
// ---------------------------------------------------------------------------
void MapInfo::Update()
{
    if (m10 == 0) {
        uint32_t a = m28, b = m2c;
        if ((a & b) != 0xffffffff) {
            IValue* pNew = mp7c->Fetch(a, b);
            IValue* pOld = mp70;
            if (pNew != pOld) {
                if (pNew) ((IRefObj*)pNew)->AddRef();
                mp70 = pNew;
                if (pOld) ((IRefObj*)pOld)->Release();
            }
        }
        a = m30; b = m34;
        if ((a & b) != 0xffffffff) {
            IValue* pNew = mp7c->Fetch(a, b);
            IValue* pOld = mp74;
            if (pNew != pOld) {
                if (pNew) ((IRefObj*)pNew)->AddRef();
                mp74 = pNew;
                if (pOld) ((IRefObj*)pOld)->Release();
            }
        }
        a = m38; b = m3c;
        if ((a & b) != 0xffffffff) {
            IValue* pNew = mp7c->Fetch(a, b);
            IValue* pOld = mp78;
            if (pNew != pOld) {
                if (pNew) ((IRefObj*)pNew)->AddRef();
                mp78 = pNew;
                if (pOld) ((IRefObj*)pOld)->Release();
            }
        }
    }
    m10++;
    if (mp70) mp70->AddRef();
    if (mp74) mp74->AddRef();
    if (mp78) mp78->AddRef();
}

// ---------------------------------------------------------------------------
// @ 0x00a76ef0
// ---------------------------------------------------------------------------
void MapInfo::ReleaseTemps()
{
    if (mp70) mp70->Release();
    if (mp74) mp74->Release();
    if (mp78) mp78->Release();
    if (--m10 == 0) {
        if (mp70) { IValue* p = mp70; mp70 = 0; ((IRefObj*)p)->Release(); }
        if (mp74) { IValue* p = mp74; mp74 = 0; ((IRefObj*)p)->Release(); }
        if (mp78) { IValue* p = mp78; mp78 = 0; ((IRefObj*)p)->Release(); }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a76f70
// ---------------------------------------------------------------------------
int MapInfo::SumCounts()
{
    int n = 0;
    IValue* p = mp70;
    if (p) n = p->Count();
    p = mp74;
    if (p) n += p->Count();
    p = mp78;
    if (p) n += p->Count();
    return n;
}

// ---------------------------------------------------------------------------
// @ 0x00a76fb0
// ---------------------------------------------------------------------------
void MapInfo::GetRect(float* out)
{
    float v[6];
    v[0] = m18;
    v[1] = m20;
    v[2] = m1c;
    v[3] = m24;
    v[4] = 0.0f;
    v[5] = 0.0f;

    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];
    out[3] = v[3];
    out[4] = v[4];
    out[5] = v[5];
}

// ---------------------------------------------------------------------------
// @ 0x00a77020
// ---------------------------------------------------------------------------
bool MapInfo::ContainsPoint(float* p)
{
    IValue* v = mp70;
    if (v && !v->Test(p)) return false;
    v = mp74;
    if (v && !v->Test(p)) return false;
    v = mp78;
    if (v && !v->Test(p)) return false;
    return m18 <= p[0] && p[0] < m20 && m1c <= p[1] && p[1] < m24;
}

// ---------------------------------------------------------------------------
// @ 0x00a770a0
// ---------------------------------------------------------------------------
bool MapInfo::IsEmpty()
{
    if (mp70 == 0 && mp74 == 0 && mp78 == 0) return false;
    IValue* v = mp70;
    if (v && !v->Empty()) return false;
    v = mp74;
    if (v && !v->Empty()) return false;
    v = mp78;
    if (v && !v->Empty()) return false;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00a77100
// ---------------------------------------------------------------------------
float MapInfo::Eval(float x)
{
    float a, b, c;
    if (mp70) a = (float)mp70->Scale(x);
    else       a = m40;
    if (mp74) b = (float)mp74->Scale(x);
    else       b = m50;
    if (mp78) c = (float)mp78->Scale(x);
    else       c = m60;

    switch (m14) {
    case 0: return a;
    case 1: return b + a;
    case 2: return b * a;
    case 3: return a - b;
    case 4: return a < b ? a : b;
    case 5: return a <= b ? b : a;
    case 6: return c + b * a;
    default: return 0.0f;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a77250
// ---------------------------------------------------------------------------
float* MapInfo::EvalVec3(float* out, int id)
{
    int a[3], b[3], c[3];
    if (mp70) {
        int* r = (int*)mp70->EvalVec3((float*)a, id);
        a[0] = r[0]; a[1] = r[1]; a[2] = r[2];
    } else if (m14 == 6 || m14 == 2) {
        float x = m40;
        ((float*)a)[0] = x;
        ((float*)a)[1] = x;
        ((float*)a)[2] = 1.0f;
    } else {
        ((float*)a)[0] = m40; ((float*)a)[1] = m44; ((float*)a)[2] = m48;
    }
    if (mp74) {
        int* r = (int*)mp74->EvalVec3((float*)b, id);
        b[0] = r[0]; b[1] = r[1]; b[2] = r[2];
    } else if (m14 == 6 || m14 == 2) {
        float x = m50;
        ((float*)b)[0] = x;
        ((float*)b)[1] = x;
        ((float*)b)[2] = 1.0f;
    } else {
        ((float*)b)[0] = m50; ((float*)b)[1] = m54; ((float*)b)[2] = m58;
    }
    if (mp78) {
        int* r = (int*)mp78->EvalVec3((float*)c, id);
        c[0] = r[0]; c[1] = r[1]; c[2] = r[2];
    } else {
        ((float*)c)[0] = m60; ((float*)c)[1] = m64; ((float*)c)[2] = m68;
    }
    float* fa = (float*)a; float* fb = (float*)b; float* fc = (float*)c;
    switch (m14) {
    case 0:
        out[0] = fa[0]; out[1] = fa[1]; out[2] = fa[2];
        break;
    case 1: {
        float t[3];
        t[0] = fb[0] + fa[0]; t[1] = fb[1] + fa[1]; t[2] = fb[2] + fa[2];
        Swarm_Normalize(out, t);
        break; }
    case 2: {
        float t[3];
        t[0] = fb[0] * fa[0]; t[1] = fb[1] * fa[1]; t[2] = fb[2] * fa[2];
        Swarm_Normalize(out, t);
        break; }
    case 3: {
        float t[3];
        t[0] = fa[0] - fb[0]; t[1] = fa[1] - fb[1]; t[2] = fa[2] - fb[2];
        Swarm_Normalize(out, t);
        break; }
    case 4:
        cMapInfo_SortRect2(out, fb, fa);
        break;
    case 5:
        Swarm_Min(out, fb, fa);
        break;
    case 6: {
        float t[3];
        t[0] = fb[0] * fa[0] + fc[0];
        t[1] = fc[1] + fb[1] * fa[1];
        t[2] = fc[2] + fb[2] * fa[2];
        Swarm_Normalize(out, t);
        break; }
    default:
        out[0] = g_1676d7c;
        out[1] = g_1676d80;
        out[2] = g_1676d84;
        break;
    }
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00a775a0
// ---------------------------------------------------------------------------
float* MapInfo::EvalVec4(float* out, int id)
{
    float a[3], b[3], c[3];
    if (mp70) {
        float tmp[3];
        float* r = (float*)mp70->EvalVec4(tmp, id);
        a[0] = r[0]; a[1] = r[1]; a[2] = r[2];
    } else {
        a[0] = m40; a[1] = m44; a[2] = m48;
    }
    if (mp74) {
        float tmp[3];
        float* r = (float*)mp74->EvalVec4(tmp, id);
        b[0] = r[0]; b[1] = r[1]; b[2] = r[2];
    } else {
        b[0] = m50; b[1] = m54; b[2] = m58;
    }
    if (mp78) {
        float tmp[3];
        float* r = (float*)mp78->EvalVec4(tmp, id);
        c[0] = r[0]; c[1] = r[1]; c[2] = r[2];
    } else {
        c[0] = m60; c[1] = m64; c[2] = m68;
    }
    switch (m14) {
    case 0:
        out[0] = a[0]; out[1] = a[1]; out[2] = a[2];
        break;
    case 1:
        out[0] = b[0] + a[0]; out[1] = b[1] + a[1]; out[2] = b[2] + a[2];
        break;
    case 2:
        out[0] = b[0] * a[0]; out[1] = b[1] * a[1]; out[2] = b[2] * a[2];
        break;
    case 3:
        out[0] = a[0] - b[0]; out[1] = a[1] - b[1]; out[2] = a[2] - b[2];
        break;
    case 4:
        cMapInfo_SortRect2(out, b, a);
        break;
    case 5:
        Swarm_Min(out, b, a);
        break;
    case 6:
        out[0] = b[0] * a[0] + c[0];
        out[1] = c[1] + b[1] * a[1];
        out[2] = c[2] + b[2] * a[2];
        break;
    default:
        out[0] = g_1676d7c;
        out[1] = g_1676d80;
        out[2] = g_1676d84;
        break;
    }
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00a77830
// ---------------------------------------------------------------------------
float* MapInfo::EvalVec4b(float* out, int id)
{
    float a[4], b[4], c[4];
    if (mp70) {
        float tmp[4];
        float* r = (float*)mp70->EvalVec4b(tmp, id);
        a[0] = r[0]; a[1] = r[1]; a[2] = r[2]; a[3] = r[3];
    } else {
        a[0] = m40; a[1] = m44; a[2] = m48; a[3] = m4c;
    }
    if (mp74) {
        float tmp[4];
        float* r = (float*)mp74->EvalVec4b(tmp, id);
        b[0] = r[0]; b[1] = r[1]; b[2] = r[2]; b[3] = r[3];
    } else {
        b[0] = m50; b[1] = m54; b[2] = m58; b[3] = m5c;
    }
    if (mp78) {
        float tmp[4];
        float* r = (float*)mp78->EvalVec4b(tmp, id);
        c[0] = r[0]; c[1] = r[1]; c[2] = r[2]; c[3] = r[3];
    } else {
        c[0] = m60; c[1] = m64; c[2] = m68; c[3] = m6c;
    }
    switch (m14) {
    case 0:
        out[0] = a[0]; out[1] = a[1]; out[2] = a[2]; out[3] = a[3];
        break;
    case 1:
        out[0] = b[0] + a[0]; out[1] = b[1] + a[1]; out[2] = b[2] + a[2]; out[3] = b[3] + a[3];
        break;
    case 2:
        out[0] = b[0] * a[0]; out[1] = b[1] * a[1]; out[2] = b[2] * a[2]; out[3] = b[3] * a[3];
        break;
    case 3:
        out[0] = a[0] - b[0]; out[1] = a[1] - b[1]; out[2] = a[2] - b[2]; out[3] = a[3] - b[3];
        break;
    case 4:
        cMapInfo_SortRect3(out, b, a);
        break;
    case 5:
        cMapInfo_SortRect3R(out, b, a);
        break;
    case 6:
        out[0] = b[0] * a[0] + c[0];
        out[1] = c[1] + b[1] * a[1];
        out[2] = c[2] + b[2] * a[2];
        out[3] = c[3] + b[3] * a[3];
        break;
    default:
        out[0] = g_1676da0;
        out[1] = g_1676da4;
        out[2] = g_1676da8;
        out[3] = g_1676dac;
        break;
    }
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00a77b70
// ---------------------------------------------------------------------------
void MapInfo::Set(int kind, float* rect, IPxSource* src)
{
    m14 = kind;
    m18 = rect[0];
    m1c = rect[1];
    m20 = rect[2];
    m24 = rect[3];
    IPxSource* pOld = mp7c;
    if (src != pOld) {
        if (src) src->AddRef();
        mp7c = src;
        if (pOld) pOld->Release();
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a77bd0  MapInfoD7 default rect (-4,-4,4,4) with z/w zero
// ---------------------------------------------------------------------------
void __stdcall MapInfo_DefaultRect44(float* out)
{
    float v[6];
    v[0] = -4.0f;
    v[2] = -4.0f;
    v[1] = 4.0f;
    v[3] = 4.0f;
    v[4] = 0.0f;
    v[5] = 0.0f;

    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];
    out[3] = v[3];
    out[4] = v[4];
    out[5] = v[5];
}

// ---------------------------------------------------------------------------
// @ 0x00a77c40  MapInfoD7: point is inside the [0,8) x [0,8) tile
// ---------------------------------------------------------------------------
bool __stdcall MapInfo_TileContains(float* p)
{
    return 0.0f <= p[0] && p[0] < g_13eeda0 && 0.0f <= p[1] && p[1] < g_13eeda0;
}
