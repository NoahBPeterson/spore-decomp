// Slice s00f3c060 -- Simulator content-validation / scenario region (bfs2 slice 14).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>
#include <math.h>

// ---------------------------------------------------------------- globals / helpers
extern unsigned char g_16065f8;                  // 0x016065F8
extern void*         g_16065fc;                  // 0x016065FC
extern void*         g_16c7aa4;                  // 0x016C7AA4
extern int           g_15b0530;                  // 0x015B0530
void* __cdecl FUN_00ddddf0(int, int);            // 0x00DDDDF0
void* __cdecl FUN_00efc520();                    // 0x00EFC520 (ScenarioTutorials_GetActive)

struct X {
    virtual void s0();
    virtual void Release();
    virtual void* s2();
    virtual void* s3(int);
};
struct Y {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4();
};

// @ 0x00F3C060
void InitThing()
{
    if (g_16065f8 == 0) {
        if (g_16065fc) {
            Y* r = (Y*)((X*)g_16065fc)->s3(0x743bb11);
            if (r) {
                r->s4();
                if (g_16065fc) {
                    void* p = g_16065fc;
                    g_16065fc = 0;
                    ((X*)p)->Release();
                }
            }
        }
        g_16065f8 = 1;
    }
}

// @ 0x00F3C0B0
void KillThing()
{
    if (g_16065f8 == 0) {
        if (g_16065fc) {
            void* p = g_16065fc;
            g_16065fc = 0;
            ((X*)p)->Release();
        }
        g_16065f8 = 1;
    }
}

// @ 0x00F3C0E0
int GetThing()
{
    if (*(int*)((char*)g_16c7aa4 + 0xcc) == 2)
        return *(int*)(*(int*)((char*)g_16c7aa4 + 0x78) + 0xb8);
    return (int)FUN_00efc520();
}

struct TutorialList;

struct W {
    char* begin;                 // +0x00
    char  pad4[0x10-4];
    void* m10;                   // +0x10
    char  pad14[0x8c-0x14];
    int   m8c;                   // +0x8c
    int IndexOf(void* p);
    int GetAt(int* p);
    void FUN_00f3c120(void** out, int);
    int  FUN_00f3c160(int index);
    void FUN_00f3c2c0();
    bool FUN_00f3c330(int* key);
    void FUN_00f3c420();
    void FUN_00f3c610(void* arg);
    bool FUN_00f3c750(void* p1, unsigned p2);
    unsigned FUN_00f3c7f0(unsigned id);
    TutorialList* FUN_00f3be60(void* active);       // 0x00F3BE60
    bool FUN_00f3b3b0(void* p1, void* e);           // 0x00F3B3B0
};

// @ 0x00F3C100
int W::IndexOf(void* p) { return (int)((char*)p - begin) / 0x238; }

// @ 0x00F3CB30
int W::GetAt(int* p)
{
    if (*p == -2) return m8c;
    return *(int*)((char*)m10 + 0x2c10) + p[0x8a] * 0x238 + 4;
}

// @ 0x00F3C1B0
struct Z { void fn(int, int); };
extern Z g_15b0534;                              // 0x015B0534
void CallD() { g_15b0534.fn(0x55c0377, g_15b0530); }

// ---------------------------------------------------------------- helper types for the target VAs

extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* target, long value);
#pragma intrinsic(_InterlockedExchangeAdd)

// -- PropertyList / property manager ----------------------------------------
struct PropertyList {
    virtual void p0();
    virtual int  Release();            // slot 1
    virtual void p2();
    virtual void* Cast(unsigned iid);  // slot 3
};
struct IPropManager {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10();
    virtual bool GetPropertyList(unsigned instanceID, unsigned groupID, PropertyList** out);  // slot 11
};
IPropManager* PropertyManager();                        // 0x0067DE30
float GetPropertyT_float(PropertyList* list, unsigned id, float def);   // 0x004E1C70

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T** AsPPTypeParam() {
        if (mpObject) {
            T* pOld = mpObject;
            mpObject = 0;
            pOld->Release();
        }
        return &mpObject;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// -- resource manager / bitset ----------------------------------------------
struct IResourceManager {
    virtual void r0(); virtual void r1(); virtual void r2();
    virtual bool Find(unsigned* key, PropertyList** out, int a, int b, int c, int d);  // slot 3
};
IResourceManager* GetManager();                         // 0x0067DCD0

struct Ctx16 { unsigned a, b, c, d; };
extern Ctx16 g_15dab18;                                 // 0x015DAB18
struct Bitset128 {
    unsigned mWords[4];
    bool none();                    // 0x005A8EA0
};
struct Obj4b {
    void fn(Bitset128* out, Ctx16 ctx, bool flag);   // 0x004BAC30
};

// -- element list -----------------------------------------------------------
struct ElemList {
    char pad0[0x2c10];
    void* mpBase;                       // +0x2c10
    void* mpEnd;                        // +0x2c14
    char pad2c18[0x2c24 - 0x2c18];
    unsigned mCur;                      // +0x2c24
};
void __cdecl FUN_00eec440(void* p);                     // 0x00EEC440

// -- tutorial list ----------------------------------------------------------
struct TutorialList {
    char pad0[0x84];
    char* mpBegin;                      // +0x84
    char* mpEnd;                        // +0x88
};

// -- spatial / transform ----------------------------------------------------
struct cSPVector3 { float x, y, z; };
struct cSPMatrix3 { float m[9]; void Assign(const void* src); };   // 0x0041CB40
struct cSPTransform {
    unsigned short mFlags;              // +0x00
    unsigned short mModificationCount;  // +0x02
    cSPVector3 mTranslation;            // +0x04
    float mScale;                       // +0x10
    cSPMatrix3 mRotation;               // +0x14
    void BackTransformPoint(float* p);  // 0x004FF6D0
    void MakeIdentity();                        // 0x00409930 (flags/rev = 0, identity)
    void SetTranslation(const cSPVector3& v);   // 0x00571D40 (dirty flag 4, rev++)
};
#define VP1(p, n) virtual void p##n() = 0;
#define VP4(p, n) VP1(p, n##0) VP1(p, n##1) VP1(p, n##2) VP1(p, n##3)
struct cSpatialObject {
    VP4(a, 0) VP4(b, 0) VP1(c, 0) VP1(d, 0) VP1(e, 0)          // slots 0..10
    virtual cSPVector3* GetVec11() = 0;                        // slot 11 (+0x2c)
    VP4(f, 0) VP4(g, 0) VP4(h, 0) VP1(i, 0) VP1(j, 0)          // slots 12..25
    virtual const float* GetBounds26() = 0;                    // slot 26 (+0x68)
    VP1(k, 0) VP1(l, 0)                                        // slots 27..28
    virtual float Fn29(unsigned a, bool (*cb)(float*)) = 0;    // slot 29 (+0x74)
    void LocalToWorldTransform(cSPTransform* t);               // 0x00C897E0
};
extern cSpatialObject* g_16c87ec;       // 0x016C87EC
extern float g_16c87f8;                 // 0x016C87F8
extern float g_16c87fc;                 // 0x016C87FC
extern float g_16c8800;                 // 0x016C8800
extern cSPMatrix3 g_16c8850;            // 0x016C8850

// -- game-mode / planet helpers ---------------------------------------------
struct TerrainMgr { int Fn1(int mode, int flag); };     // 0x00B1DAF0
TerrainMgr* FUN_00b3d320();                             // 0x00B3D320
int GetCurrentGameMode();                               // 0x00B5B800
void GetPropertyT_40cf10(void* obj, unsigned id, float* out);   // 0x0040CF10
struct cPlanetModel {
    cSPVector3* FUN_00b81630(cSPVector3* out, const cSPVector3* in);   // 0x00B81630
    void FUN_00b83c40(const cSPVector3* v, float r);                   // 0x00B83C40
};
cPlanetModel* PlanetModel();                            // 0x00B3D350
void* __cdecl FUN_00b18e00(void* p);                    // 0x00B18E00
bool __cdecl FUN_00f3c500(float* p);                    // 0x00F3C500

struct ObjF3C610 {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void* Cast(unsigned iid);                   // slot 3
};

// -- intrusive release of a refcounted object (refcount at object+8) ---------
static __forceinline void ReleaseRef(void** slot)
{
    void* p = *slot;
    if (p) {
        long* rc = (long*)((char*)p + 8);
        *slot = 0;
        _InterlockedExchangeAdd(rc, -1);
        long c = _InterlockedExchangeAdd(rc, 0);
        if (c < 1)
            _InterlockedExchangeAdd(rc, 1);
        else
            _InterlockedExchangeAdd(rc, 0);
    }
}

// @ 0x00F3C120
void W::FUN_00f3c120(void** out, int)
{
    *out = begin;
    bool go = true;
    while (go) {
        char* p = begin;
        char* q = p + 0x238;
        begin = q;
        bool stop = (*(unsigned*)p >> 30) & 1;
        if (stop)
            return;
        go = (*(unsigned*)q >> 31) & 1;
    }
}

// @ 0x00F3C160
int W::FUN_00f3c160(int index)
{
    char* p = begin + index * 0x238;
    unsigned flags = *(unsigned*)p;
    if ((flags >> 30) & 1)
        return 0x3fffffff;
    do {
        p += 0x238;
        ++index;
        flags = *(unsigned*)p;
        if ((int)flags >= 0)
            return index;
    } while (!((flags >> 30) & 1));
    return 0x3fffffff;
}
// @ 0x00F3C1D0
void __cdecl FUN_00f3c1d0(unsigned* key, float* a, float* b, float* c)
{
    *a = 10.0f;
    *b = 10.0f;
    *c = 10.0f;
    AutoRefCount<PropertyList> propList;
    if (!PropertyManager()->GetPropertyList(key[0], key[2], propList.AsPPTypeParam()))
        return;
    *a = GetPropertyT_float(propList, 0x6219412b, 10.0f);
    *b = GetPropertyT_float(propList, 0x15321d59, 10.0f);
    *c = GetPropertyT_float(propList, 0x6219412b, 10.0f);
}

// @ 0x00F3C2C0
void W::FUN_00f3c2c0()
{
    ElemList* L = (ElemList*)m10;
    char* p = (L->mCur < 0x3fffffff) ? (char*)L->mpBase + L->mCur * 0x238 : (char*)L->mpEnd;
    char* end = (char*)L->mpEnd;
    while (p != end) {
        FUN_00eec440(p + 4);
        do {
            unsigned f = *(unsigned*)p;
            p += 0x238;
            bool stop = (f >> 30) & 1;
            if (stop)
                break;
        } while ((*(unsigned*)p >> 31) & 1);
    }
}

// @ 0x00F3C330
bool W::FUN_00f3c330(int* key)
{
    bool result = false;
    if (key[0] == 0)
        return key[1] != 0 || key[2] != 0;
    AutoRefCount<PropertyList> propList;
    if (!GetManager()->Find((unsigned*)key, propList.AsPPTypeParam(), 0, 0, 0, 0))
        result = true;
    else if (propList) {
        void* p = propList->Cast(0x3c609f8);
        if (p) {
            Bitset128 bits;
            ((Obj4b*)p)->fn(&bits, g_15dab18, 1);
            if (!bits.none())
                result = true;
        }
    }
    return result;
}

// @ 0x00F3C420
void W::FUN_00f3c420()
{
    ReleaseRef((void**)((char*)this + 0x38));
    *(unsigned*)((char*)this + 0xe8) = 0;
    *(unsigned*)((char*)this + 0xec) = 0;
    *(unsigned*)((char*)this + 0xf0) = 0;
    for (int i = 0; i < 4; ++i) {
        *(int*)(*(char**)((char*)this + 0x10) + 0x68 + i * 4) = 0;
        ReleaseRef((void**)((char*)this + 0x3c + i * 4));
        *(unsigned*)((char*)this + 0xf4 + i * 0xc) = 0;
        *(unsigned*)((char*)this + 0xf8 + i * 0xc) = 0;
        *(unsigned*)((char*)this + 0xfc + i * 0xc) = 0;
    }
}

// @ 0x00F3C500
bool __cdecl FUN_00f3c500(float* p)
{
    if (g_16c87ec == 0)
        return true;
    cSPTransform t;
    t.mFlags = 0;
    t.mModificationCount = 0;
    t.mTranslation.x = g_16c87f8;
    t.mTranslation.y = g_16c87fc;
    t.mTranslation.z = g_16c8800;
    t.mScale = 1.0f;
    t.mRotation.Assign(&g_16c8850);
    g_16c87ec->LocalToWorldTransform(&t);
    float local[3] = { p[0], p[1], p[2] };
    t.BackTransformPoint(local);
    const float* box = g_16c87ec->GetBounds26();
    if (local[0] <= box[0] - 4.0f)
        return false;
    if (box[3] + 4.0f <= local[0])
        return false;
    if (local[1] <= box[1] - 4.0f)
        return false;
    if (box[4] + 4.0f <= local[1])
        return false;
    return true;
}

// @ 0x00F3C610
void W::FUN_00f3c610(void* arg)
{
    if (!arg)
        return;
    void* a = ((ObjF3C610*)arg)->Cast(0x70704db);
    void* b = ((ObjF3C610*)arg)->Cast(0x3a25119);
    if (!a && (!b || (*(unsigned*)((char*)b + 0x84) & 0x200)))
        return;
    int r = FUN_00b3d320()->Fn1(GetCurrentGameMode(), 1);
    float fStack = 10.0f;
    if (r)
        GetPropertyT_40cf10((void*)r, 0xadbb7654, &fStack);
    cSpatialObject* edi = (cSpatialObject*)FUN_00b18e00(arg);
    cSPVector3* v1 = edi->GetVec11();
    cSPVector3 v2;
    cSPVector3* v2p = PlanetModel()->FUN_00b81630(&v2, v1);
    float d = sqrtf(v1->x * v1->x + v1->y * v1->y + v1->z * v1->z)
            - sqrtf(v2p->x * v2p->x + v2p->y * v2p->y + v2p->z * v2p->z);
    if (d < fStack) {
        g_16c87ec = edi;
        float rr = edi->Fn29(0x8000000, FUN_00f3c500);
        PlanetModel()->FUN_00b83c40(v1, rr);
        g_16c87ec = 0;
    }
}

// @ 0x00F3C750
bool W::FUN_00f3c750(void* p1, unsigned p2)
{
    TutorialList* list = FUN_00f3be60(FUN_00efc520());
    unsigned i = 0;
    char* e = list->mpBegin;
    for (; i < (unsigned)((list->mpEnd - list->mpBegin) / 0x188); ++i, e += 0x188) {
        if (e != p1 && (p2 == 0xffffffff || i != p2)) {
            if (FUN_00f3b3b0(p1, e))
                return true;
        }
    }
    return false;
}

// @ 0x00F3C7F0
unsigned W::FUN_00f3c7f0(unsigned id)
{
    unsigned count = 0;
    if (id == 0xfffffffe)
        return m8c != 0;
    ElemList* L = (ElemList*)m10;
    char* p = (L->mCur < 0x3fffffff) ? (char*)L->mpBase + L->mCur * 0x238 : (char*)L->mpEnd;
    char* end = (char*)L->mpEnd;
    while (end != p) {
        if (*(unsigned*)(p + 4) == id)
            ++count;
        do {
            unsigned f = *(unsigned*)p;
            p += 0x238;
            bool stop = (f >> 30) & 1;
            if (stop)
                break;
        } while ((*(unsigned*)p >> 31) & 1);
    }
    return count;
}

// ---------------------------------------------------------------- not yet matching

// -- overlap test between two spatial objects --------------------------------
// Both objects publish their position (vtable slot 11, +0x2c), an orientation
// quaternion (slot 12, +0x30), a uniform size (slot 13, +0x34) and a shadow proxy
// (slot 43, +0xac); the proxy carries the world bounding box at +0x70.
enum {
    kVtPosition   = 0x2c,
    kVtQuaternion = 0x30,
    kVtSize       = 0x34,
    kVtProxy      = 0xac,
    kProxyBox     = 0x70
};

static inline void* VCallPtr(void* obj, int slot)
{
    typedef void* (__thiscall* Fn)(void*);
    return ((Fn)(*(void***)obj)[slot / 4])(obj);
}

static inline float VCallFloat(void* obj, int slot)
{
    typedef float (__thiscall* Fn)(void*);
    return ((Fn)(*(void***)obj)[slot / 4])(obj);
}

char FUN_00b66b20(void* id, void* shapeOwner, float filter);           // 0x00B66B20
cSPMatrix3* Matrix3FromQuaternion(cSPMatrix3* out, const void* quat);  // 0x0059C190
bool __cdecl FUN_0069b910(const float* boxA, const cSPTransform* shapeA,
                          const float* boxB, const cSPTransform* shapeB);  // 0x0069B910

struct cSPBoundingBox {
    cSPVector3 mMin;                    // +0x00
    cSPVector3 mMax;                    // +0x0c
    cSPBoundingBox(const cSPBoundingBox& o);    // 0x00511140
};

// @ 0x00F3C870
// Broad phase (bounding spheres) then a `coarse` collision query, and finally the
// exact oriented-box test: both shapes are built from the objects' translation,
// quaternion-derived rotation and size, and the first box is grown by `pad`.
bool __stdcall FUN_00f3c870(void* a, void* b, float pad, bool coarse)
{
    if (!a || !b)
        return false;

    const cSPVector3* pa = (const cSPVector3*)VCallPtr(a, kVtPosition);
    float ra = VCallFloat(a, kVtSize) + pad;
    const cSPVector3* pb = (const cSPVector3*)VCallPtr(b, kVtPosition);
    float rb = VCallFloat(b, kVtSize);
    float reach = ra + rb;
    float dx = pa->x - pb->x;
    float dy = pa->y - pb->y;
    float dz = pa->z - pb->z;
    if (reach * reach <= dx * dx + dy * dy + dz * dz)
        return false;

    if (coarse) {
        char hit = FUN_00b66b20(a, b, 0.5f);
        if (hit)
            return hit == 2;
    }

    void* proxyA = VCallPtr(a, kVtProxy);
    void* proxyB = VCallPtr(b, kVtProxy);
    if (!proxyA || !proxyB)
        return false;

    cSPTransform ta;
    ta.MakeIdentity();
    ta.SetTranslation(*(const cSPVector3*)VCallPtr(a, kVtPosition));
    cSPMatrix3 rot;
    Matrix3FromQuaternion(&rot, VCallPtr(a, kVtQuaternion));
    ta.mRotation = rot;
    ta.mFlags |= 2;
    ta.mModificationCount++;
    ta.mScale = VCallFloat(a, kVtSize);
    ta.mModificationCount++;

    cSPTransform tb;
    tb.MakeIdentity();
    tb.SetTranslation(*(const cSPVector3*)VCallPtr(b, kVtPosition));
    Matrix3FromQuaternion(&rot, VCallPtr(b, kVtQuaternion));
    tb.mRotation = rot;
    tb.mFlags |= 2;
    tb.mModificationCount++;
    tb.mScale = VCallFloat(b, kVtSize);
    tb.mModificationCount++;

    cSPBoundingBox box = *(const cSPBoundingBox*)((char*)proxyA + kProxyBox);
    box.mMin.x -= pad;
    box.mMin.y -= pad;
    box.mMin.z -= pad;
    box.mMax.x += pad;
    box.mMax.y += pad;
    box.mMax.z += pad;

    return FUN_0069b910(&box.mMin.x, &ta, (const float*)((char*)proxyB + kProxyBox), &tb);
}

// ---------------------------------------------------------------------------
// Content-validation summarizer ("cContentValidationSummarizer").
//
// Layout recovered from the ctor/dtor:
//   +0x00  vtable          (0x0148D2EC, later 0x013EB938)
//   +0x04  vtable2         (0x013EC458, later 0x0148D2DC)
//   +0x08  unsigned        (zeroed)
//   +0x0c  unsigned        (ctor arg 1)
//   +0x10  refcounted*     (ctor arg 2)
//   +0x14  refcounted*     (ctor arg 3)
//   +0x48  wide-string map (setter 1)
//   +0x58  wide-string map (setter 2)
//   +0x68  wide-string map (setter 3)
//   +0x81  unsigned char   ("dirty" flag)
// ---------------------------------------------------------------------------

// A refcounted object whose vtable slot 0 is AddRef and slot 1 is Release.
struct RefCountedVtbl {
    virtual void AddRef();                    // slot 0
    virtual void Release();                   // slot 1
};

// The wide-string map object used at +0x48/+0x58/+0x68 is a self-contained
// 2-pointer (begin/end) wide string; reporting the two members is enough for the
// operations the setters perform.
struct WideKeyMap {
    void** mpBegin;                           // +0x00
    void** mpEnd;                             // +0x04
    char   pad08[0x10 - 0x08];                // +0x08  inline capacity / bucket storage
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
};
bool FindWideKey(const WideKeyMap* map, const wchar_t* key);  // 0x006AB760

// Message server: slot 5 (+0x14) is Send(unsigned id, const void* payload, int).
struct IMessageServer {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4();
    virtual void Send(unsigned id, const void* payload, int flag);   // slot 5 (+0x14)
};
IMessageServer* SP_MessageServer();                        // 0x0067DCC0

// The authoring/auth manager: slot 16 (+0x40) returns its 64-bit meta id.
struct AuthManager {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
    virtual void m8(); virtual void m9(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual long long GetMetaId();            // slot 16 (+0x40)
};
AuthManager* AuthManager_Get();                           // 0x00607A60

// The resource-manager Find slot returns a property list whose vtable slot 1 is
// Release and slot 3 is Cast(iid).
struct FindResult {
    virtual void f0();
    virtual void Release();                   // slot 1
    virtual void f2();
    virtual void* Cast(unsigned iid);         // slot 3
};

// The cast target of the 0x30BDEE3 id: slot 0 is a "touch", slot 1 a release and
// the non-virtual GetId reads the 64-bit id at +0x68/+0x6c (0x005508A0).
struct ContentMeta {
    virtual void Touch();                     // slot 0
    virtual void Release();                   // slot 1
    long long GetId();                        // 0x005508A0 (thiscall, no args)
};

// vtable fragments installed by the ctor/dtor (retail image literals).
extern void* g_148d2ec;                       // 0x0148D2EC
extern void* g_148d2dc;                       // 0x0148D2DC
extern void* g_13ec458;                       // 0x013EC458
extern void* g_13eb938;                       // 0x013EB938

extern void operator_delete(void* p);                     // 0x00F47380

struct cContentValidationSummarizer {
    void*    mpVtbl0;                         // +0x00
    void*    mpVtbl1;                         // +0x04
    unsigned mField08;                        // +0x08
    unsigned mField0c;                        // +0x0c
    void*    mpField10;                       // +0x10
    void*    mpField14;                       // +0x14
    char     pad18[0x48 - 0x18];
    WideKeyMap mMap48;                        // +0x48
    WideKeyMap mMap58;                        // +0x58
    WideKeyMap mMap68;                        // +0x68
    char     pad78[0x81 - 0x78];              // +0x78
    unsigned char mField81;                   // +0x81

    bool FUN_00f3cb60();                                                // 0x00F3CB60
    cContentValidationSummarizer* ctor(unsigned a, void* b, void* c);   // 0x00F3CC40
    cContentValidationSummarizer* dtor(unsigned flag);                  // 0x00F3CD10
    void FUN_00f3cd60(const wchar_t* key);                              // 0x00F3CD60
    void FUN_00f3cdf0(const wchar_t* key);                              // 0x00F3CDF0
    void FUN_00f3ce80(const wchar_t* key);                              // 0x00F3CE80
};

// ---------------------------------------------------------------------------
// Ask the resource manager for the property list described by the two ids taken
// from this+0x10, cast the result to the content-meta interface, and report
// whether its 64-bit id matches the authoring manager's current meta id.
// @ 0x00F3CB60
bool cContentValidationSummarizer::FUN_00f3cb60()
{
    char* src = (char*)mpField10;
    unsigned key[3];
    key[0] = *(unsigned*)(src + 8);
    key[1] = 0x30bdee3;
    key[2] = *(unsigned*)(src + 0x10);

    FindResult* propList = 0;
    IResourceManager* mgr = GetManager();
    mgr->Find(key, (PropertyList**)&propList, 0, 0, 0, 0);

    bool same = false;
    if (propList) {
        ContentMeta* meta = (ContentMeta*)propList->Cast(0x30bdee3);
        if (meta) {
            meta->Touch();
            AuthManager* auth = AuthManager_Get();
            long long authId = auth->GetMetaId();
            long long metaId = meta->GetId();
            same = (metaId == authId);
            meta->Release();
        }
        propList->Release();
    }
    return same;
}

// @ 0x00F3CC40
cContentValidationSummarizer* cContentValidationSummarizer::ctor(
    unsigned a, void* b, void* c)
{
    mpVtbl1 = &g_13ec458;
    mField08 = 0;
    mpVtbl0 = &g_148d2ec;
    mpVtbl1 = &g_148d2dc;
    mpField10 = 0;
    mpField14 = 0;
    mField0c = a;

    void* old = mpField10;
    if (b != old) {
        if (b)
            ((RefCountedVtbl*)b)->AddRef();
        mpField10 = b;
        if (old)
            ((RefCountedVtbl*)old)->Release();
    }
    old = mpField14;
    if (c != old) {
        if (c)
            ((RefCountedVtbl*)c)->AddRef();
        mpField14 = c;
        if (old)
            ((RefCountedVtbl*)old)->Release();
    }
    return this;
}

// @ 0x00F3CD10
cContentValidationSummarizer* cContentValidationSummarizer::dtor(unsigned flag)
{
    void* m = mpField14;
    if (m)
        ((RefCountedVtbl*)m)->Release();
    m = mpField10;
    if (m)
        ((RefCountedVtbl*)m)->Release();

    mpVtbl1 = &g_13ec458;
    mpVtbl0 = &g_13eb938;
    if (flag & 1)
        operator_delete(this);
    return this;
}

// ---------------------------------------------------------------------------
// The three wide-string setters share one body: if `key` is not already present
// in the map at +0x48 (resp. +0x58 / +0x68), assign it and broadcast a
// "changed" notification whose payload is {this, 0, map header word}, then set
// the dirty byte at +0x81.  ret 4.
// @ 0x00F3CD60
void cContentValidationSummarizer::FUN_00f3cd60(const wchar_t* key)
{
    if (FindWideKey(&mMap48, key))
        return;

    const wchar_t* end = key;
    if (*end)
        while (*++end)
            ;
    mMap48.assign(key, key + (end - key));

    unsigned payload[3];
    payload[0] = (unsigned)(uintptr_t)(this != (void*)4 ? this : 0);
    payload[1] = 0;
    payload[2] = (unsigned)(uintptr_t)mMap48.mpBegin;
    SP_MessageServer()->Send(0x7aa519dc, payload, 0);
    mField81 = 1;
}

// @ 0x00F3CDF0
void cContentValidationSummarizer::FUN_00f3cdf0(const wchar_t* key)
{
    if (FindWideKey(&mMap58, key))
        return;

    const wchar_t* end = key;
    if (*end)
        while (*++end)
            ;
    mMap58.assign(key, key + (end - key));

    unsigned payload[3];
    payload[0] = (unsigned)(uintptr_t)(this != (void*)4 ? this : 0);
    payload[1] = 0;
    payload[2] = (unsigned)(uintptr_t)mMap58.mpBegin;
    SP_MessageServer()->Send(0x14418c3f, payload, 0);
    mField81 = 1;
}

// @ 0x00F3CE80
void cContentValidationSummarizer::FUN_00f3ce80(const wchar_t* key)
{
    if (FindWideKey(&mMap68, key))
        return;

    const wchar_t* end = key;
    if (*end)
        while (*++end)
            ;
    mMap68.assign(key, key + (end - key));

    unsigned payload[3];
    payload[0] = (unsigned)(uintptr_t)(this != (void*)4 ? this : 0);
    payload[1] = 0;
    payload[2] = (unsigned)(uintptr_t)mMap68.mpBegin;
    SP_MessageServer()->Send(0x73127e6, payload, 0);
    mField81 = 1;
}
