// Slice s00fa9d20: SP::cTerrainSphere::SetDefinition (VA 00fa9d20) (retail layout).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same module as the other cTerrainSphere slices.
//
// Stores the new definition property list (+0x28), refreshes the sphere's resource key from it, clears the
// models and the three 0xac-byte "relevel" record lists (+0x770, +0x784, +0x798), reloads the relevel
// records from the definition's key/transform arrays (0x3ad5568/9 -> list +0x798; 0x43b29e1/2 -> list
// +0x770, or +0x784 for keys whose own property list has 0xc5ae63ed == true), then pushes the terrain
// state settings (water offset, tile ranges, ...) into the state manager (+0x20c).
#include "types.h"
#include <new>

extern "C" void* __cdecl memset(void* dst, int c, unsigned int n);

namespace EA { namespace ResourceMan { struct Key { uint32_t instance, type, group; }; } }
typedef EA::ResourceMan::Key Key;

struct Allocator { const char* mpName; uint32_t mExtra; };

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
};
struct Vector2 { float x, y; };
struct Matrix3I { Vector3 row0, row1, row2; };
struct cSPTransform {
    uint16_t mFlags, mModCount;
    float mTx, mTy, mTz, mScale;
    Matrix3I mRot;
};
struct Rect { float l, t, r, b; };

struct Property {
    void* mpData;
    uint32_t pad04[3];
    uint16_t mnFlags;                       // +0x10
    uint16_t mnType;                        // +0x12
    const void* GetData() const { return (mnFlags & 0x30) ? mpData : (const void*)this; }
};

struct PropList {
    virtual void AddRef();                  // +0
    virtual void Release();                 // +4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};
struct PropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, PropList** out);   // +0x2c
};
struct PropListRef {                        // intrusive ref holder
    PropList* p;
    PropListRef() : p(0) {}
    ~PropListRef() { if (p) p->Release(); }
    PropList** AsPP() { if (p) { PropList* o = p; p = 0; o->Release(); } return &p; }
};

PropMgr* PropertyManager();                                                 // 0x0067de30
bool GetPropertyAsVector3(PropList* l, uint32_t id, Vector3& out);          // 0x006a1110
bool GetPropertyAsVector2(PropList* l, uint32_t id, Vector2& out);          // 0x006a10c0
struct AppProperties { bool GetDescription(uint32_t id); };                  // 0x006a25a0
extern AppProperties* sAppProperties;                                        // 0x015fd918
void __cdecl FreeBlock(void* p);                                             // 0x00f47380 (operator_delete__)
uint32_t __cdecl MakeRelevelExtra(const cSPTransform* t, const Key* k);     // 0x00f96390

// A relevel record (0xac bytes).
struct cRelevel {
    cSPTransform mTransform;                // +0x00
    Rect mBounds[6];                        // +0x38
    Key mKey;                               // +0x98
    uint32_t mFlagsAndBits;                 // +0xa4
    uint32_t mExtra;                        // +0xa8
    cRelevel() {}
    __forceinline cRelevel(const cSPTransform& t, const Key& k)
    {
        mTransform.mFlags = t.mFlags; mTransform.mModCount = t.mModCount;
        mTransform.mTx = t.mTx; mTransform.mTy = t.mTy; mTransform.mTz = t.mTz; mTransform.mScale = t.mScale;
        mTransform.mRot.row0 = Vector3(t.mRot.row0);
        mTransform.mRot.row1 = Vector3(t.mRot.row1);
        mTransform.mRot.row2 = Vector3(t.mRot.row2);
        mKey = k;
        mFlagsAndBits = 0;
        mExtra = MakeRelevelExtra(&t, &k);
        memset(mBounds, 0, sizeof(mBounds));
    }
    cRelevel(const cRelevel& o);                                                // 0x00f9b1e0
    cRelevel(const Key& k, const cSPTransform& t, int bFlag);                  // 0x00f9b2b0
};

cRelevel* __cdecl CopyRelevels(cRelevel* first, cRelevel* last, cRelevel* dest);   // 0x00f9f770

struct RelevelVector {
    cRelevel* mBegin; cRelevel* mEnd; cRelevel* mCap; Allocator mAlloc;
    void DoInsertValue(cRelevel* pos, const cRelevel& v);                      // 0x00fa47b0
    __forceinline void push_back(const cRelevel& v)
    {
        if (mEnd < mCap) ::new (mEnd++) cRelevel(v);
        else DoInsertValue(mEnd, v);
    }
    __forceinline void clear()
    {
        cRelevel* first = mBegin;
        cRelevel* last = mEnd;
        CopyRelevels(last, mEnd, first);
        mEnd -= (last - first);
    }
};

struct KeyVector {
    Key* mBegin; Key* mEnd; Key* mCap; Allocator mAlloc;
    KeyVector() : mBegin(0), mEnd(0), mCap(0) {}
    Key* erase(Key* first, Key* last);                                          // 0x0050f740
    ~KeyVector() { if (mBegin && ((int*)mBegin)[-1]) FreeBlock(mBegin); }
};
struct XformVector {
    cSPTransform* mBegin; cSPTransform* mEnd; cSPTransform* mCap; Allocator mAlloc;
    XformVector() : mBegin(0), mEnd(0), mCap(0) {}
    ~XformVector() { if (mBegin && ((int*)mBegin)[-1]) FreeBlock(mBegin); }
};
void __cdecl ReadKeyArray(PropList* p, uint32_t id, int type, KeyVector* dst);           // 0x00f34d40
void __cdecl ReadTransformArray(PropList* p, uint32_t id, int type, XformVector* dst);   // 0x00fa9040

struct cTerrainStateMgr {
    bool HasWaterSettings();                                // 0x00fb89f0
    void SetWaterSettings(float a, float b, int c);         // 0x00fbddb0 (ret 0xc)
    void SetTileRange(float a, float b);                    // 0x00fbd880 (ret 8)
    void SetScaleA(uint32_t v);                             // 0x00fbaf10
    void SetScaleB(uint32_t v);                             // 0x00fbaf50
    void SetVec2(Vector2* v);                               // 0x00fb7bd0
    void UpdateFromDefinition(PropList* def);               // 0x00fbc130
};
struct cTerrainMapSet { void SetValue(float v); };          // 0x00963760

struct cTerrainSphere {
    virtual void vfn0();
    char pad04[0x18 - 4];
    Key mKey;                               // +0x18
    char pad24[4];
    PropList* mpDefinition;                 // +0x28
    cTerrainMapSet* mpMapSet;               // +0x2c
    char pad30[0x20c - 0x30];
    cTerrainStateMgr* mpStateMgr;           // +0x20c
    char pad210[0x770 - 0x210];
    RelevelVector mRelevelA;                // +0x770
    RelevelVector mRelevelB;                // +0x784
    RelevelVector mRelevelC;                // +0x798
    char pad7ac[0x814 - 0x7ac];
    uint32_t mCamOffsetY;                   // +0x814
    void ClearModels();                     // 0x00fa5e40
    void SetModels();                       // 0x00fa96d0
    void SetDefinition(PropList* def);
};

static __forceinline bool GetTyped(PropList* l, uint32_t id, int type, Property*& p)
{
    return l && l->GetProperty(id, p) && p->mnType == type;
}

// @ 0x00fa9d20
void cTerrainSphere::SetDefinition(PropList* def)
{
    PropList* old = mpDefinition;
    if (def != old) {
        if (def) def->AddRef();
        mpDefinition = def;
        if (old) old->Release();
    }
    mKey.instance = ((int*)def)[2];
    mKey.type = 0x11989b7;
    mKey.group = ((int*)def)[4];

    ClearModels();
    mRelevelC.clear();
    mRelevelA.clear();
    mRelevelB.clear();
    mCamOffsetY = 0;

    if (mpDefinition) {
        SetModels();
        KeyVector keys;
        XformVector xf;
        ReadKeyArray(mpDefinition, 0x3ad5568, 0x20, &keys);
        ReadTransformArray(mpDefinition, 0x3ad5569, 0x38, &xf);
        int n = keys.mEnd - keys.mBegin;
        cSPTransform* t = xf.mBegin;
        Key* k = keys.mBegin;
        if (n != 0) {
            do {
                cRelevel r(*t, *k);
                mRelevelC.push_back(r);
                ++t; ++k;
            } while (--n != 0);
        }
        keys.erase(keys.mBegin, keys.mEnd);
        xf.mEnd = xf.mEnd - (xf.mEnd - xf.mBegin);

        ReadKeyArray(mpDefinition, 0x43b29e1, 0x20, &keys);
        ReadTransformArray(mpDefinition, 0x43b29e2, 0x38, &xf);
        n = keys.mEnd - keys.mBegin;
        t = xf.mBegin;
        k = keys.mBegin;
        if (n != 0) do {
            PropListRef list;
            Property* prop;
            if (PropertyManager()->GetPropertyList(k->instance, k->group, list.AsPP())) {
                if (GetTyped(list.p, 0xc5ae63ed, 1, prop) && *(const char*)prop->GetData() != 0) {
                    mRelevelB.push_back(cRelevel(*k, *t, 1));
                } else {
                    cRelevel r(*t, *k);
                    mRelevelA.push_back(r);
                }
            }
            ++t; ++k;
        } while (--n != 0);

        Property* prop;
        if (GetTyped(mpDefinition, 0x3ad556a, 10, prop))
            mCamOffsetY = *(const uint32_t*)prop->GetData();

        Vector3 v;
        if (GetPropertyAsVector3(mpDefinition, 0x3a23f98, v)) {
            if (!mpStateMgr->HasWaterSettings())
                mpStateMgr->SetWaterSettings(v.z, v.y, 0);
        }
        if (GetPropertyAsVector3(mpDefinition, 0x3a23f9a, v) || GetPropertyAsVector3(mpDefinition, 0x3a23f99, v)) {
            if (v.x > 0.0f && v.x <= 64.0f && v.y > 0.0f && v.y <= 64.0f)
                mpStateMgr->SetTileRange((v.x - 0.5f) * 0.015625f, (v.y - 0.5f) * 0.015625f);
            mpMapSet->SetValue(v.z);
        }
        if (GetTyped(mpDefinition, 0x536250c, 10, prop))
            mpStateMgr->SetScaleA(*(const uint32_t*)prop->GetData());
        if (GetTyped(mpDefinition, 0x536250d, 10, prop))
            mpStateMgr->SetScaleB(*(const uint32_t*)prop->GetData());
        Vector2 v2;
        if (GetPropertyAsVector2(mpDefinition, 0x536250e, v2))
            mpStateMgr->SetVec2(&v2);
        bool flag = false;
        if (GetTyped(mpDefinition, 0x5408a6c, 1, prop))
            flag = *(const bool*)prop->GetData();
        bool desc = sAppProperties->GetDescription(0x5408a93);
        bool arg = flag & desc;
        ((void (__thiscall*)(cTerrainSphere*, bool))(*(void***)this)[0xe0 / 4])(this, arg);
    }
    mpStateMgr->UpdateFromDefinition(def);
}
