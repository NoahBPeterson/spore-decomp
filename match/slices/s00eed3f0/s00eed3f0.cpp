// Slice s00eed3f0 -- 0x00eed3f0..0x00eedc10  (/O2 /MD /Gy /TP /arch:SSE /fp:fast)
//
// Scenario-edit-mode property helpers (spin-control callbacks).
#include "types.h"
#include <algorithm>
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define VTP(p)          (*(void***)(p))
#define VC0(p,off)      (((int (__thiscall*)(void*))       VTP(p)[(off)/4])((void*)(p)))
#define VC1(p,off,a)    (((int (__thiscall*)(void*,int))   VTP(p)[(off)/4])((void*)(p),(int)(a)))
#define VC4(p,off,a,b,c,d) (((int(__thiscall*)(void*,int,int,int,int))VTP(p)[(off)/4])((void*)(p),(int)(a),(int)(b),(int)(c),(int)(d)))
#define VCF(p,off)      (((float (__thiscall*)(void*))     VTP(p)[(off)/4])((void*)(p)))
#define VCP(p,off)      (((float* (__thiscall*)(void*))    VTP(p)[(off)/4])((void*)(p)))

// ---------------------------------------------------------------------------
// Shared data
// ---------------------------------------------------------------------------
extern int   DAT_016c7a28;
extern int   DAT_016c7a38;
extern int   DAT_015ac948;
extern int   DAT_015ac94c;
extern char  DAT_015acb40;

extern float g_1485720;     // 1.0f
extern float g_148ad98;     // 1.5258789e-05f
extern float g_1471064;     // 0.5f
extern float g_16c7924;
extern float g_16c7934, g_16c7944, g_16c7954, g_16c7964, g_16c7974, g_16c7984;
extern float g_16c7994, g_16c79a4, g_16c79b4, g_16c79c4, g_16c79d4, g_16c79e4;
extern float g_15ac950;     // planet radius
extern void* g_167ecd0;     // hkWorld

struct ResourceKey {
    unsigned mInstanceID;   // +0x00
    unsigned mTypeID;       // +0x04
    unsigned mGroupID;      // +0x08
};

// A noun / game-data object: its first three words are its resource key.
struct cNoun {
    unsigned mInstanceID;   // +0x00
    unsigned mTypeID;       // +0x04
    unsigned mGroupID;      // +0x08
    void*    mPropList;     // +0x0c
    char     pad10[0x210];
    float    mField220;     // +0x220

    char fn255d0();         // 0x00f255d0
    char fn25680();         // 0x00f25680
    char fn256e0();         // 0x00f256e0
    char fn256a0();         // 0x00f256a0
};

// Object that owns the property list at +0x0c (returned by cNounManager::Find).
struct cPropertyOwner {
    char pad00[0x0c];
    void* mPropList;        // +0x0c
};

struct Mgr {
    cNoun* fn3f00();            // 0x00ff3f00
    cNoun* fn3e8a0(int key);    // 0x00f3e8a0
    void*  fn3d780(void* a);    // 0x00f3d780
};
struct GlobalObj {
    char pad00[0x74];
    Mgr* mManager;              // +0x74
};
extern GlobalObj* DAT_016c7aa4;

// ---------------------------------------------------------------------------
// Property list / property manager
// ---------------------------------------------------------------------------
namespace EA {
struct Variant {
    unsigned       mData[4];    // +0x00
    unsigned short mFlags;      // +0x10
    unsigned short mTypeId;     // +0x12
    Variant() : mFlags(0), mTypeId(0) {}
    void SetU32(const unsigned& v);     // 0x00427fd0
    void SetInt(const int& v);          // 0x00422eb0
    void Destruct(bool b);              // 0x0093db80
};
}

struct IPropList {
    virtual int  AddRef();                          // +0x00
    virtual int  Release();                         // +0x04
    virtual void s2();                              // +0x08
    virtual void s3();                              // +0x0c
    virtual void s4();                              // +0x10
    virtual void SetProperty(unsigned hash, EA::Variant* value);   // +0x14
};

namespace SP {
struct cPropertyList : IPropList {
    char pad04[0x34];
    cPropertyList();                                // 0x006a1c40
};
}

struct PropMgr {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10();
    virtual bool GetPropertyList(unsigned instance, unsigned group, IPropList** out);  // +0x2c
};

struct PropRef38 {
    char pad00[0x38];
    int  mType;                 // +0x38
};

template<typename T>
struct IntrusivePtr {
    T* mpObject;
    IntrusivePtr() : mpObject(0) {}
    ~IntrusivePtr() { if (mpObject) mpObject->Release(); }
    IntrusivePtr& operator=(T* pNew) {
        if (pNew != mpObject) {
            T* const pOld = mpObject;
            if (pNew) pNew->AddRef();
            mpObject = pNew;
            if (pOld) pOld->Release();
        }
        return *this;
    }
    T** operator&() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

struct IRefObj {
    virtual int AddRef();       // +0x00
    virtual int Release();      // +0x04
};
struct cPropertyBag : IRefObj {
    bool GetInt32(unsigned key, int* out);          // 0x00613660
};
struct cPollinatorLookup {
    bool LookupByKey(const ResourceKey* key, IRefObj** out, bool touch);   // 0x006138b0
};
struct PollinatorHolder {
    char pad00[0x5c];
    cPollinatorLookup* mLookup; // +0x5c
};

// ---------------------------------------------------------------------------
// Havok ray structures
// ---------------------------------------------------------------------------
class __declspec(align(16)) hkVector4 {
public:
    float x, y, z, w;
    hkVector4() {}
};

struct RadialRay {
    hkVector4 mPos;             // +0x00
    float     mH0;              // +0x10
    float     mH1;              // +0x14
};

struct RayHitResult {
    int       mStatus;          // +0x00
    unsigned  mPad04[3];
    hkVector4 mPos;             // +0x10
    hkVector4* mNormalOut;      // +0x20
    float*    mDistOut;         // +0x24
    void*     mUserData;        // +0x28
    void*     mEntity;          // +0x2c
};

class hkWorld;
struct cPlanetModel;
struct RayObj;

// ---------------------------------------------------------------------------
// Callees
// ---------------------------------------------------------------------------
struct NounMgr {
    void* FUN_00b21000(unsigned type, unsigned inst);   // 0x00b21000
};

extern "C" bool      FUN_005bf120(const void* key, IPropList* list, int a, void* b);
extern "C" bool      FUN_005bf7c0(int*, int);
extern "C" bool      FUN_00eebfc0(int*, int);
extern "C" int       FUN_00eec760(int*, int);
extern "C" unsigned  FUN_00eec870(int);
extern "C" void*     FUN_00eeca60(void* out, const void* in);
extern "C" unsigned  FUN_00eece20(const void* p);
extern "C" float     FUN_00eed280(cNoun* key, int extra);
extern "C" NounMgr*  FUN_00b3d300();
extern "C" PropMgr*  FUN_0067de30();
extern "C" PollinatorHolder* FUN_0067cb30();
extern "C" bool      GetPropertyT(void* list, unsigned hash, void* out);   // 0x0040cf10
extern "C" cPlanetModel* FUN_00b3d350();
extern "C" void*     FUN_00b18e00(void* p);
extern "C" void      FUN_00b668c0(RadialRay* r, cPlanetModel* planet, hkWorld* world,
                                  RayObj* obj, bool useWorld, RayHitResult* out, bool adjust);

void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);     // 0x00f473a0

extern const char aSimulator_013f09b4[];            // 0x013f09b4 "Simulator"

struct Prop { char pad[4]; int* GetInt(); };
struct RefObj { virtual void v0(); virtual void Release(); };

extern "C" bool FUN_005bf0e0(int, int**);

// ============================================================ 0x00eed920
// @ 0x00eed920
bool __cdecl f00eed920(int param1, int param2)
{
    int* local = 0;
    bool ok = FUN_005bf0e0(param1, &local) && FUN_005bf7c0(local, param2);
    if (local != 0)
        VC0(local, 4);
    return ok;
}

// ============================================================ 0x00eed970
// @ 0x00eed970
bool __cdecl f00eed970(int param1, int param2)
{
    int* local = 0;
    bool ok = FUN_005bf0e0(param1, &local) && FUN_00eebfc0(local, param2);
    if (local != 0)
        VC0(local, 4);
    return ok;
}

// ============================================================ 0x00eed9c0
// @ 0x00eed9c0
bool __cdecl f00eed9c0(int param1, int param2)
{
    int* local = 0;
    if (FUN_005bf0e0(param1, &local)) {
        FUN_00eec760(local, param2);
        if (local != 0)
            VC0(local, 4);
        return true;
    }
    if (local != 0)
        VC0(local, 4);
    return false;
}

// ============================================================ 0x00eed840
// @ 0x00eed840
bool __cdecl f00eed840(int param)
{
    int* local = 0;
    int out;
    bool ok;
    if (!FUN_005bf0e0(param, &local))
        goto fail;
    if (local == 0)
        goto fail;
    if (!((char(__thiscall*)(void*,int,int*))VTP(local)[0x24 / 4])(local, 0x5888ef41, &out))
        goto fail;
    if (*(short*)(out + 0x12) != 9)
        goto fail;
    if (*((Prop*)out)->GetInt() == DAT_016c7a28)
        ok = true;
    else
        goto fail;
    goto done;
fail:
    ok = false;
done:
    if (local != 0)
        ((RefObj*)local)->Release();
    return ok;
}

// ============================================================ 0x00eed3f0
// @ 0x00eed3f0
float __cdecl f00eed3f0(cNoun* key, float value, char flagA, char flagB, float* out)
{
    float lo = g_1485720;
    float hi = g_1485720;

    switch (key->mTypeID) {
    case 0x24682294:
    case 0x476a98c7:
        lo = g_16c79a4;
        hi = g_16c79b4;
        break;
    case 0x2399be55:
        lo = g_16c79d4;
        hi = g_16c79e4;
        break;
    case 0xb1b104: {
        ResourceKey k;
        FUN_00eeca60(&k, key);
        switch (k.mTypeID) {
        case 0x2a8fb3f:
        case 0x3a2511e: {
            cPropertyOwner* n = (cPropertyOwner*)FUN_00b3d300()->FUN_00b21000(k.mTypeID, k.mInstanceID);
            if (n != 0) {
                GetPropertyT(n->mPropList, 0x7611549, &lo);
                GetPropertyT(n->mPropList, 0x761154f, &hi);
            }
            break;
        }
        case 0x74e0069:
        case 0x7b38ba7: {
            IntrusivePtr<IPropList> list;
            PropMgr* pm = FUN_0067de30();
            if (pm->GetPropertyList(key->mInstanceID, key->mGroupID, &list)) {
                GetPropertyT(list, 0x7611549, &lo);
                GetPropertyT(list, 0x761154f, &hi);
            }
            break;
        }
        }
        break;
    }
    case 0x2b978c46:
        if (flagB) {
            lo = g_16c7954;
            hi = g_16c7964;
        } else if (flagA) {
            if (value < g_16c7944) {
                lo = g_16c7934;
                hi = g_16c7944;
            } else if (value < g_16c7964) {
                lo = g_16c7954;
                hi = g_16c7964;
            } else {
                lo = g_16c7974;
                hi = g_16c7984;
            }
        } else {
            if (value > g_16c7974) {
                lo = g_16c7974;
                hi = g_16c7984;
            } else if (value > g_16c7954) {
                lo = g_16c7954;
                hi = g_16c7964;
            } else {
                lo = g_16c7934;
                hi = g_16c7944;
            }
        }
        break;
    }

    float clamped = value;
    clamped = std::min(std::max(clamped, lo), hi);

    float v = FUN_00eed280(key, 0);
    if (out != 0) {
        if (clamped < v) {
            *out = ((value - lo) / ((v - lo) + 1.5258789e-05f)) * 0.5f;
            return clamped;
        }
        *out = ((value - v) / ((hi - v) + 1.5258789e-05f)) * 0.5f + 0.5f;
    }
    return clamped;
}

// ============================================================ 0x00eed720
// Spin state (0..3) + visibility flags for the spin control of the selected noun.
struct SpinOwner {
    void** mVtable;             // +0x00
    char   pad04[0x6d];
    char   mField71;            // +0x71
};

struct SpinOut {
    unsigned mFlags;            // +0x00
    int      mField04;          // +0x04
    int      mState;            // +0x08
    float    mValue;            // +0x0c
    unsigned mFlags2;           // +0x10
};

// @ 0x00eed720
void __cdecl f00eed720(cNoun* noun, SpinOwner* owner, SpinOut* out)
{
    char cVar1 = DAT_015acb40;
    Mgr* mgr = DAT_016c7aa4->mManager;
    int  uVar8;
    bool bVar9;
    int  state = 1;

    if (noun != mgr->fn3f00()) {
        cNoun* asset = mgr->fn3e8a0(noun->mInstanceID);
        if (FUN_00eece20(asset) != 0xe34e8a60) {
            if (owner->mField71 == 0) {
                uVar8 = 1;
                bVar9 = true;
            } else {
                uVar8 = 0;
                bVar9 = false;
            }
            PropRef38* prop = (PropRef38*)VC1(owner, 0xb8, 0x175cdc9);
            if (prop != 0 && prop->mType == 9)
                bVar9 = true;
            state = asset->fn255d0() == 0;
            if (asset != 0 && asset->fn25680()) {
                uVar8 = 0;
                bVar9 = false;
                if (asset->fn256e0())
                    state = 0;
                else if (asset->fn256a0())
                    state = 3;
            }
        } else {
            uVar8 = 0;
            bVar9 = true;
        }
    } else {
        uVar8 = 0;
        bVar9 = true;
    }

    out->mFlags |= 2;
    if (cVar1)
        out->mFlags |= 0x10;
    else
        out->mFlags &= ~0x10u;
    out->mField04 = uVar8;
    out->mState = state;
    out->mValue = noun->mField220;
    out->mFlags2 = 0;
    if (bVar9)
        out->mFlags2 |= 0x10;
    else
        out->mFlags2 &= ~0x10u;
    out->mFlags2 &= ~4u;
    out->mFlags2 |= 2;
}

// ============================================================ 0x00eed8c0
// @ 0x00eed8c0
int __cdecl f00eed8c0(const ResourceKey* key)
{
    int result = DAT_016c7a38;
    IRefObj* bag = 0;
    cPollinatorLookup* lookup = FUN_0067cb30()->mLookup;
    if (lookup->LookupByKey(key, &bag, false))
        ((cPropertyBag*)bag)->GetInt32(0x5bd7a6a4, &result);
    int value = result;
    if (bag != 0)
        bag->Release();
    return value;
}

// ============================================================ 0x00eeda20
// @ 0x00eeda20
void __cdecl f00eeda20(const void* key, int* props)
{
    IntrusivePtr<IPropList> list;
    if (!FUN_005bf0e0((int)key, (int**)&list))
        list = new (aSimulator_013f09b4, 0, 0, 0, 0) SP::cPropertyList();

    if (list) {
        if (props[0] != -1) {
            EA::Variant v;
            v.SetU32(*(const unsigned*)&props[0]);
            list->SetProperty(0x1f0372ed, &v);
            if (v.mFlags & 4)
                v.Destruct(false);
        }
        if (props[1] != 0x7fffffff) {
            EA::Variant v;
            v.SetInt(props[1]);
            list->SetProperty(0xd6a4ff43, &v);
            if (v.mFlags & 4)
                v.Destruct(false);
        }
        if (props[2] != 0x7fffffff) {
            EA::Variant v;
            v.SetInt(props[2]);
            list->SetProperty(0xb55857d7, &v);
            if (v.mFlags & 4)
                v.Destruct(false);
        }
        FUN_005bf120(key, list, 0, 0);
    }
}

// ============================================================ 0x00eedba0
// @ 0x00eedba0
void __cdecl f00eedba0(float* out, unsigned key)
{
    unsigned c = FUN_00eec870(key);
    c = (c == (unsigned)DAT_015ac948) ? (unsigned)DAT_015ac94c : c;
    out[0] = (float)((c >> 16) & 0xff) * 0.003921569f;
    out[1] = (float)((c >> 8) & 0xff) * 0.003921569f;
    out[2] = (float)(c & 0xff) * 0.003921569f;
}

// ============================================================ 0x00eedc10
// @ 0x00eedc10
struct cSpinPoint {
    int   mField00;             // +0x00
    float mX;                   // +0x04
    float mY;                   // +0x08
    float mZ;                   // +0x0c
};

bool __cdecl f00eedc10(cSpinPoint* point, void* view)
{
    Mgr* mgr = DAT_016c7aa4->mManager;
    void* obj = mgr->fn3d780(point);
    if (obj == 0)
        return false;
    int* hit = (int*)VC1(obj, 0x0c, 0x1186577);
    if (hit == 0)
        return false;

    float* pos = VCP(view, 0x2c);
    float dx = point->mX - pos[0];
    float dy = point->mY - pos[1];
    float dz = point->mZ - pos[2];
    float radius = g_15ac950;
    float rsum = VCF(view, 0x70) + radius;

    if (dx * dx + dy * dy + dz * dz <= rsum * rsum &&
        (void*)hit != view &&
        (((unsigned)hit[0xa8] >> 1) & 1) &&
        fabs(*(float*)((char*)hit + 0xb4)) <= radius) {
        hkVector4 normal;
        RadialRay ray;
        ray.mPos.x = point->mX;
        ray.mPos.y = point->mY;
        ray.mPos.z = point->mZ;
        ray.mPos.w = 0.0f;
        ray.mH0 = 0.05f;
        ray.mH1 = -radius;
        RayHitResult res;
        res.mNormalOut = &normal;
        res.mDistOut = 0;
        res.mUserData = 0;
        res.mEntity = 0;
        FUN_00b668c0(&ray, FUN_00b3d350(), (hkWorld*)g_167ecd0, 0, true, &res, false);
        return view == FUN_00b18e00(res.mUserData);
    }
    return false;
}
