// src/game/SPBake/_at_004e0000.cpp -- migrated from slice(s) s004e88a0, s004e7990, s004e6c60, s004e5d00 by tools/migrate/rewrite.py
// Object file: SPBake/_at_004e0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorVerbIconData.h"
#include <math.h>
#include "SP/cSpeciesProfile.h"

// ---- items of slice s004e5d00 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int size, const char* pName, int flags = 0, unsigned debugFlags = 0, const char* pFile = 0, int line = 0); // 0xf473a0
struct PropertyList {
    virtual void AddRef();   // +0
    virtual void Release();  // +4
};
template <class T> struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    AutoRefCount(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~AutoRefCount() { if (mp) mp->Release(); }
    T** AsPPVoidParam() { if (mp) { T* t = mp; mp = 0; t->Release(); } return &mp; }
};
struct PropListRef {
    PropertyList* mp;
    PropListRef(PropertyList* p) : mp(p) { if (mp) mp->AddRef(); }
    ~PropListRef() { if (mp) mp->Release(); }
    PropertyList** AsPPVoidParam();   // 0x0041d870
};
struct PropertyManager {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
    virtual bool GetPropertyList(uint32_t propID, uint32_t groupID, void* out); // +0x2c
};
PropertyManager* GetPropertyManager();   // 0x0067de30 (SP::PropertyManager)
struct CapabilityManager {
    static uint32_t __cdecl GetPropIDForAbility(uint32_t id, int flag);  // 0x00459370
};
struct cSPEditorVerbIconData {
    cSPEditorVerbIconData();        // 0x005e5a70
    virtual void AddRef();          // +0
    virtual void Release();         // +4
    virtual void v2();
    virtual void v3();
    virtual void SetPropertyList(PropertyList* pl); // +0x10
    char pad[0x14];
    float mLevel;                   // +0x18
    float mMaxLevel;                // +0x1c
    char pad2[0xc4 - 0x20];
};
typedef AutoRefCount<cSPEditorVerbIconData> VerbIconRef;
struct IconVec {                    // eastl::vector<AutoRefCount<cSPEditorVerbIconData>>
    void* mpBegin; void* mpEnd; void* mpCap; uint32_t mAlloc;
    void push_back(const VerbIconRef& r);   // 0x004b54b0
};
struct VerbFlags {
    uint32_t mBits;
    VerbFlags() { mBits = 0; mBits = 0; }
    bool test(uint32_t n) const {
        if (n < 3) {
            uint32_t w = mBits;
            return (w & (1u << (n % 32))) != 0;
        }
        return false;
    }
};
struct AllocTag { AllocTag() {} };
struct sp_vector_allocator {
    uint32_t m;
    sp_vector_allocator(const AllocTag&);   // 0x00429360
};
struct IdVec {
    typedef int T;
    int* mpBegin;
    int* mpEnd;
    int* mpCap;
    sp_vector_allocator mAlloc;
    IdVec() : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(AllocTag()) {}
    int* begin() { return mpBegin; }
    int* end() { return mpEnd; }
    ~IdVec() { DoDestroy(mpBegin, mpEnd); DoFree(); }
    static void DoDestroy(int* first, int* last) { for (; first < last; ++first) first->~T(); }
    void DoFree();                          // 0x00425990
    void push_back(const int& v);      // 0x00454860
};
template <class It, class T> inline It find(It first, It last, const T& v) {
    while (first != last && *first != v) ++first;
    return first;
}
void __cdecl AddVerbIcons(PropertyList* pl, IconVec* out, VerbFlags* flags);  // 0x004e5960
struct VerbEntry {                  // 0x1d8-byte records at owner+0x98
    uint32_t mGroupID;              // +0
    uint32_t mPropID;               // +4
    uint32_t pad8;
    int mAltIndex;                  // +0xc
    char pad[0x1d8 - 0x10];
};
struct EntryVec {
    VerbEntry* mpBegin;
    VerbEntry* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
    VerbEntry& operator[](int i) { return mpBegin[i]; }
};
struct EntryOwner {
    char pad[0x98];
    EntryVec mEntries;              // +0x98
};
struct RefVec {
    void* mBegin;
    void* mEnd;
    void* mCap;
    RefVec() { mBegin = 0; mEnd = 0; mCap = 0; }
    ~RefVec();
};
struct VerbSink {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void Deliver(RefVec* v); // vtable +0x14
};
void FillRefVec6720(void* owner, RefVec* out); // 0x004e6720
void BuildVerbCapabilities(IconVec* out, VerbFlags* flags); // 0x004e5d00
// ---- items of slice s004e5d00 end

// ---- items of slice s004e6c60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kZero;   // 0x01485378
struct PctItem {
    char  pad[0x18];
    float amount;     // +0x18
    float pad2;
    float pct;        // +0x20
};
void* __cdecl operator new(unsigned int size, const char* tag, int a, int b, int c, int d) throw();  // 0x00f473a0
struct IRefObj {
    virtual int AddRef();
    virtual int Release();
};
template <class T> struct AutoRefCount_s004e_6c60 {
    T* mpObject;
    AutoRefCount_s004e_6c60(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s004e_6c60() { if (mpObject) mpObject->Release(); }
    T** GetAddress()
    {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};
struct cSPEditorVerbIconData_s004e_6c60 : IRefObj {
    virtual void v02();
    virtual void v03();
    virtual void SetIcon(IRefObj* icon);     // vtable +0x10
    char mPad04[0x18 - 4];                   // +0x04
    float mValue;                            // +0x18
    float mMax;                              // +0x1c
    uint32_t mPad20;                         // +0x20
    uint32_t mKind;                          // +0x24
    char mPad28[0x4d - 0x28];                // +0x28
    bool mClamp;                             // +0x4d
    char mPad4e[0xc4 - 0x4e];                // +0x4e
    cSPEditorVerbIconData_s004e_6c60();                 // 0x005e5a70
};
struct RefVec_s004e_6c60 {
    AutoRefCount_s004e_6c60<cSPEditorVerbIconData_s004e_6c60>* mBegin;   // +0
    AutoRefCount_s004e_6c60<cSPEditorVerbIconData_s004e_6c60>* mEnd;     // +4
    AutoRefCount_s004e_6c60<cSPEditorVerbIconData_s004e_6c60>* mCap;     // +8
    uint32_t mAlloc[2];
    void push_back(const AutoRefCount_s004e_6c60<cSPEditorVerbIconData_s004e_6c60>& r);   // 0x004b54b0
};
struct IPropertyManager {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
    virtual void GetProperty(uint32_t propId, uint32_t typeId, IRefObj** out);   // vtable +0x2c
};
IPropertyManager* __cdecl PropertyManager();   // 0x0067de30
struct CapabilityManager_s004e_6c60 {
    static uint32_t GetPropIDForAbility(uint32_t abilityId, int flag);   // 0x00459370
};
struct Entry8 {
    uint32_t mID;        // +0
    float mAmount;       // +4
};
struct EntryVec_s004e_6c60 {
    Entry8* mBegin;      // +0
    Entry8* mEnd;        // +4
    Entry8* mCap;        // +8
    uint32_t mAlloc[2];
};
void FillRefVec18(RefVec_s004e_6c60* out, uint32_t key);   // 0x004e7990
// ---- items of slice s004e6c60 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void NormalizePercents(PctItem* a, PctItem* b, PctItem* c);  // 0x004e6c60 (stays in the slice: not this object's)

// ---- items of slice s004e7990 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
template <class T> struct AutoRefCount_s004e_7990 {
    T* mpObject;
    AutoRefCount_s004e_7990(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s004e_7990() { if (mpObject) mpObject->Release(); }
    // Releases any held object and returns the out-param slot (0x0041d870).
    T** GetAddress()
    {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
    AutoRefCount_s004e_7990& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};
struct cSPEditorVerbIconData_s004e_7990 {
    virtual int AddRef();
    virtual int Release();
    virtual void v02();
    virtual void v03();
    virtual void SetIcon(IRefObj* icon);     // vtable +0x10
    char pad04[0x18 - 4];
    float mValue;                            // +0x18
    char pad1c[0xc4 - 0x1c];
    cSPEditorVerbIconData_s004e_7990();                 // 0x005e5a70
};
struct RefVec_s004e_7990 {
    AutoRefCount_s004e_7990<cSPEditorVerbIconData_s004e_7990>* mBegin; // +0
    AutoRefCount_s004e_7990<cSPEditorVerbIconData_s004e_7990>* mEnd;   // +4
    AutoRefCount_s004e_7990<cSPEditorVerbIconData_s004e_7990>* mCap;   // +8
    uint32_t mAlloc[2];                          // uninitialised allocator dwords (vector is 0x14 bytes)
    RefVec_s004e_7990() { mBegin = 0; mEnd = 0; mCap = 0; }
    ~RefVec_s004e_7990();                                            // 0x004b5440
    void push_back(const AutoRefCount_s004e_7990<cSPEditorVerbIconData_s004e_7990>& r);   // 0x004b54b0
    void resize(int n);                                   // 0x00421bf0 (IPtrVec::resize)
    AutoRefCount_s004e_7990<cSPEditorVerbIconData_s004e_7990>& operator[](int i) { return mBegin[i]; }
};
void FillRefVec18(RefVec_s004e_7990* out, uint32_t key); // 0x004e7990
struct VerbSink_s004e_7990 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void Deliver(RefVec_s004e_7990* v); // vtable +0x14
};
struct EntryOwner_s004e_7990 {
    char pad[0x18];
    uint32_t mKey;                                        // +0x18
    uint32_t GetKey() { return mKey; }
};
// ---- items of slice s004e7990 end

// ---- items of slice s004e88a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float    g_015da588; // 0x015da588
extern float    g_015da58c; // 0x015da58c
extern float    g_015da590; // 0x015da590
void* AllocNodeMem(void* alloc, uint32_t size, uint32_t align, uint32_t extra);
struct Key5 {
    int m0, m1, m2, m3, m4;
};
struct NodeAlloc {
    char pad[0x18];
    Key5* Allocate(const Key5* rp); // @ 0x004e8d30
};
struct Vector3 { float x, y, z; };
struct Matrix33 {
    float m[9];
    void Assign(const void* src); // 0x0041cb40
};
struct RefVtbl {
    void (__thiscall* mAddRef)(void* self);              // +0x00
    void (__thiscall* mRelease)(void* self);             // +0x04
    void (__thiscall* mSlot08)(void* self);              // +0x08
    void (__thiscall* mGetBasis)(void* self, void* out); // +0x0c
};
struct RefObj {
    RefVtbl* mVtbl; // +0x00
};
struct BuildVtbl {
    void* mSlots[0x114 / 4];                                                   // +0x00..+0x110
    char (__thiscall* mBuild)(void* self, void* a, int b, void** out, char c); // +0x114
};
struct RenderObj {
    BuildVtbl* mVtbl;      // +0x00
    uint32_t   mPad04[3];  // +0x04
    void*      mp10;       // +0x10
    uint32_t   mPad14;     // +0x14
    void*      mp18;       // +0x18
    uint32_t   mPad1c[11]; // +0x1c
    Vector3    mVec48;     // +0x48
    uint32_t   mPad54[97]; // +0x54
    float      mf1d8;      // +0x1d8
};
extern Matrix33 g_015da458; // 0x015da458
struct RWXform {
    RenderObj* mp00;   // +0x00  (render object)
    void*      mp04;   // +0x04  (refcounted object)
    Vector3    mVec08; // +0x08
    Vector3    mVec14; // +0x14
    Matrix33   mMat20; // +0x20
    int        mInt44; // +0x44
    char       mChar48;// +0x48

    RWXform();                                                                              // @ 0x004e8f70
    void Build(RenderObj* a0, void* a1, float fx, float fy, float fz, void* a5, void* a6);  // @ 0x004e9050
    char Attach(RenderObj* a0, int a1, char a2);                                            // @ 0x004e9500
};
// ---- items of slice s004e88a0 end

// @ 0x004e5d00
void BuildVerbCapabilities(IconVec* out, VerbFlags* flags)
{
    uint32_t id1 = CapabilityManager::GetPropIDForAbility(0x4d18efd, 0);
    PropListRef plist((PropertyList*)0);
    if (id1 != 0) {
        GetPropertyManager()->GetPropertyList(id1, 0x1b68db4, plist.AsPPVoidParam());
    }
    cSPEditorVerbIconData* icon = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData();
    icon->SetPropertyList(plist.mp);
    icon->mLevel = 3.0f;
    icon->mMaxLevel = 3.0f;
    {
        VerbIconRef r(icon);
        out->push_back(r);
    }

    cSPEditorVerbIconData* icon2 = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData();
    AutoRefCount<PropertyList> plist2;
    uint32_t id2;
    if (!flags->test(2) && !flags->test(0) && !flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x4d192a14, 0);
    } else if (!flags->test(2) && !flags->test(0) && flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x4d192a2, 0);
    } else if (!flags->test(2) && flags->test(0) && !flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x4d192a1, 0);
    } else if (!flags->test(2) && flags->test(0) && flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x177209ee, 0);
    } else if (flags->test(2) && !flags->test(0) && !flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x4d192a3, 0);
    } else if (flags->test(2) && !flags->test(0) && flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x64e7222b, 0);
    } else if (flags->test(2) && flags->test(0) && !flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0xf613df04, 0);
    } else if (flags->test(2) && flags->test(0) && flags->test(1)) {
        id2 = CapabilityManager::GetPropIDForAbility(0x50c34699, 0);
    }
    GetPropertyManager()->GetPropertyList(id2, 0x1b68db4, plist2.AsPPVoidParam());
    icon2->SetPropertyList(plist2.mp);
    icon2->mLevel = 0.0f;
    {
        VerbIconRef r(icon2);
        out->push_back(r);
    }
}

// @ 0x004e6920
uint32_t GetPropIDForAbilityHash(uint32_t id)
{
    switch (id) {
    case 0xab97cd36: return 0x66783b4;
    case 0x91c3bf70: return 0x11b79302;
    case 0x9052db45: return 0x4d18efd;
    case 0x8a30ddc4: return 0x11b79a71;
    case 0xefd1720c: return 0x11b79a72;
    case 0x2d94dcd7: return 0x32f92e6;
    case 0xb40fb63b: return 0x11b79a75;
    case 0x6701d2bb: return 0x11b79a76;
    case 0x2b2d090b: return 0x11b79a77;
    case 0x2bfee57a: return 0xb3e30313;
    }
    return 0;
}

// @ 0x004e6a10
void UpdateEntry6a10(EntryOwner* owner, IconVec* out)
{
    if (owner != 0) {
        VerbFlags flags;
        IdVec seen;
        int i = 0;
        int n = owner->mEntries.size();
        for (; i < n; ++i) {
            if (find(seen.begin(), seen.end(), i) == seen.end()) {
                VerbEntry* e = &owner->mEntries[i];
                AutoRefCount<PropertyList> pl;
                GetPropertyManager()->GetPropertyList(e->mPropID, e->mGroupID, pl.AsPPVoidParam());
                AddVerbIcons(pl.mp, out, &flags);
                seen.push_back(i);
                if (e->mAltIndex != -1) {
                    int alt = e->mAltIndex;
                    seen.push_back(alt);
                }
            }
        }
        BuildVerbCapabilities(out, &flags);
    }
}

// @ 0x004e6bc0
void BuildDispatch6bc0(void* owner, VerbSink* sink)
{
    RefVec vec;
    FillRefVec6720(owner, &vec);
    sink->Deliver(&vec);
}

// @ 0x004e7460
void ScaleColorForKind(int kind, float r, float g, float b, float* pR, float* pG, float* pB)
{
    *pR = 1.0f;
    *pG = 1.0f;
    *pB = 1.0f;

    if (kind == 0) {
        *pR = *pR * 10.0f + r * 20.0f;
        *pG = *pG * 150.0f + g * 300.0f;
        *pB = *pB * 5.0f + b * 20.0f;
    }
    if (kind == 1) {
        *pR = *pR * 15.0f + r * 30.0f;
        *pG = *pG * 200.0f + g * 400.0f;
        *pB = *pB * 5.0f + b * 20.0f;
    }
    if (kind == 2) {
        *pR = *pR * 10.0f + r * 20.0f;
        *pG = *pG * 150.0f + g * 300.0f;
        *pB = *pB * 10.0f + b * 40.0f;
    }
}

// @ 0x004e7610
void BuildVerbIcons(EntryVec_s004e_6c60* entries, RefVec_s004e_6c60* out, int key)
{
    int nCount = (int)(entries->mEnd - entries->mBegin);
    cSPEditorVerbIconData_s004e_6c60* a = 0;
    cSPEditorVerbIconData_s004e_6c60* b = 0;
    cSPEditorVerbIconData_s004e_6c60* c = 0;
    uint32_t nMatch = CapabilityManager_s004e_6c60::GetPropIDForAbility(key, 0);
    for (int i = 0; i < nCount; ++i) {
        AutoRefCount_s004e_6c60<IRefObj> prop(0);
        const Entry8& entry = entries->mBegin[i];
        uint32_t propID = CapabilityManager_s004e_6c60::GetPropIDForAbility(entry.mID, 0);
        IPropertyManager* pManager = PropertyManager();
        pManager->GetProperty(propID, 0x1b68db4, prop.GetAddress());
        cSPEditorVerbIconData_s004e_6c60* pIcon = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData_s004e_6c60();
        pIcon->SetIcon(prop.mpObject);
        pIcon->mValue = entries->mBegin[i].mAmount;
        if (pIcon->mClamp && pIcon->mValue > pIcon->mMax)
            pIcon->mValue = pIcon->mMax;
        if (pIcon->mKind == nMatch)
            a = pIcon;
        else if (pIcon->mKind == 0x34d6bd1e)
            b = pIcon;
        else if (pIcon->mKind == 0x5979cecb)
            c = pIcon;
        out->push_back(AutoRefCount_s004e_6c60<cSPEditorVerbIconData_s004e_6c60>(pIcon));
    }
    NormalizePercents((PctItem*)a, (PctItem*)b, (PctItem*)c);
    int nKind = 0;
    switch (key) {
    case 0xbc1041e6:    // Colony_Land
    case 0x9ad7d4aa:    // Religious_Land
    case 0xf670aa43:    // Economic_Land
    case 0x7d433fad:    // Military_Land
        nKind = 0;
        break;
    case 0x8f963dcb:    // Military_Sea
    case 0xc15695da:    // Colony_Sea
    case 0x1f2a25b6:    // Religious_Sea
    case 0x2a5147a9:    // Economic_Sea
        nKind = 1;
        break;
    case 0x1a4e0708:    // Economic_Air
    case 0x98e03c0d:    // UFO
    case 0x441cd3e6:    // Military_Air
    case 0x2090a11b:    // Colony_Air
    case 0x449c040f:    // Religious_Air
        nKind = 2;
        break;
    }
    float fR = kZero;
    float fG = kZero;
    float fB = kZero;
    ScaleColorForKind(nKind, a->mValue * 0.1f, b->mValue * 0.1f, c->mValue * 0.1f,
                      &fR, &fG, &fB);
    a->mValue = fR;
    b->mValue = fG;
    c->mValue = fB;
    FillRefVec18(out, key);
}

// @ 0x004e7e50
void BuildAndDispatch18(void* owner, VerbSink_s004e_7990* sink)
{
    uint32_t scratch[1];
    RefVec_s004e_7990 vec;
    FillRefVec18(&vec, ((EntryOwner_s004e_7990*)owner)->GetKey());
    ScratchSlots<5>();
    sink->Deliver(&vec);
}

// @ 0x004e8c80
void** Body8c80(void** first, void** last, void** dest)
{
    void** d = dest;
    for (void** s = first; s != last; ++s, ++d) {
        if (d != 0 && (*d = *s) != 0)
            (*(void(__thiscall**)(void*))*d)(*d);
    }
    return d;
}

// @ 0x004e8d30
Key5* NodeAlloc::Allocate(const Key5* rp)
{
    void* foo = AllocNodeMem((char*)this + 0x18, 0x24, 4, 0);
    Key5* cc = (Key5*)((char*)foo + 0x10);
    // Retail copies through a discarded conditional expression: the copy happens when the key slot
    // is non-null and the (unused) result is the key pointer, else null; the node is returned.
    cc != 0 ? &(*cc = *rp) : (Key5*)0;
    return (Key5*)foo;
}

// @ 0x004e8ee0
void** ApplyCopyLoop8ee0(void** out, void** first, void** last, void** dest)
{
    void** d = dest;
    for (void** s = first; s != last; ++s, ++d) {
        if (d != 0 && (*d = *s) != 0)
            (*(void(__thiscall**)(void*))*d)(*d);
    }
    *out = d;
    return out;
}

// @ 0x004e8f70
RWXform::RWXform()
{
    mp00 = 0;
    mp04 = 0;
    if (mp04 != 0)
        ((RefObj*)mp04)->mVtbl->mAddRef(mp04);
    mVec08.x = g_015da588;
    mVec08.y = g_015da58c;
    mVec08.z = g_015da590;
    mVec14.x = g_015da588;
    mVec14.y = g_015da58c;
    mVec14.z = g_015da590;
    mMat20.Assign(&g_015da458);
    mInt44 = -1;
    mChar48 = 0;
}
