// src/game/SPBake/SPEditorStats.cpp -- migrated from slice(s) s004e88a0, s004e7990, s004e5d00, s004e5050 by tools/migrate/rewrite.py
// Object file: SPBake/SPEditorStats.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/eVerbIconCategory.h"
#include "SP/cSPEditorVerbIconData.h"
#include "SP/cSpeciesProfile.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int   __cdecl Editor_GetConfigFromModelType(int modelType);       // 0x432f10
extern "C" void* __cdecl GetPropertyManager67de30();                         // 0x67de30
extern "C" void* __cdecl GetPropertyManager();                            // 0x67de30
extern "C" void* __cdecl Func4e8850(void* self);                          // 0x4e8850
extern "C" int*  __cdecl Func4e88a0(void* self, void* key);               // 0x4e88a0
extern "C" void* __cdecl PrepareRef(void* ref);                                 // 0x41d870  releases old, returns ref
extern "C" char  __cdecl NameCompare(void* key, void* cfg);                     // 0x4bafc0
extern "C" int   __cdecl VerbIdToIconParam(int id);                             // 0x4d1370
extern "C" void  __cdecl BuildNamedIcon(void* ref, int* host, int param, float rate); // 0x4e87f0
extern "C" void  __cdecl Emit7da0(int res, int* host);                          // 0x4e7da0
extern "C" void  __cdecl Emit6c10(int res, int* host);                          // 0x4e6c10
extern "C" int   __cdecl InterfaceCastEditor(void** ref);                       // 0x421eb0
extern "C" void* __cdecl ResourceMan_GetManager2();                             // 0x67dcd0

// ---- items of slice s004e5050 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VerbObject {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual bool HasCategory(int key); // +0x1c
};
bool GetPropertyAsKeyInstance(VerbObject* p, int key, int* out); // 0x006a12a0, cdecl
struct RefCounted {                     // EA::RefCounted base: vtbl[1] = Release
    virtual void v0();
    virtual void Release();
};
struct AutoRef {
    void* mp;
    void** Prepare()
    {
        if (mp != 0) {
            void* tmp = mp;
            mp = 0;
            ((RefCounted*)tmp)->Release();
        }
        return &mp;
    }
};
extern "C" int   __cdecl Editor_GetConfigFromModelType(int modelType);       // 0x432f10
extern "C" void* __cdecl GetPropertyManager67de30();                         // 0x67de30
extern "C" char  __cdecl GetPropertyAsKey(void* list, uint32_t id, void* out);        // 0x6a1250
extern "C" char  __cdecl GetPropertyAsKeyInstance(void* list, uint32_t id, void* out); // 0x6a12a0
extern uint32_t  DAT_015d9ed8;
struct Key3 { uint32_t w[3]; };
struct PropList {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual void GetPropertyList(uint32_t id, uint32_t req, void** out);   // +0x2c
};
struct VerbHost5180;
struct RefList3 { uint32_t w[3]; };
extern "C" void* __cdecl ReserveAutoRef(void* list, uint32_t id, int* count, void** data); // 0x6a0ae0
struct PtrVector {
    int* mpBegin;                       // +0x0
    int* mpEnd;                         // +0x4
    int  mCapacity;                     // +0x8
};
extern "C" void* __cdecl GetPropertyManager();                            // 0x67de30
extern "C" void* __cdecl Func4e8850(void* self);                          // 0x4e8850
extern "C" int*  __cdecl Func4e88a0(void* self, void* key);               // 0x4e88a0
extern "C" void* __cdecl PrepareRef(void* ref);                                 // 0x41d870  releases old, returns ref
extern "C" char  __cdecl NameCompare(void* key, void* cfg);                     // 0x4bafc0
extern "C" int   __cdecl VerbIdToIconParam(int id);                             // 0x4d1370
extern "C" void  __cdecl BuildNamedIcon(void* ref, int* host, int param, float rate); // 0x4e87f0
extern "C" void  __cdecl Emit7990(RefList3* out, int id);                        // 0x4e7990
extern "C" void  __cdecl Func4b5440v(RefList3* v);                              // 0x4b5440
extern "C" void  __cdecl Emit7da0(int res, int* host);                          // 0x4e7da0
extern "C" void  __cdecl Emit6c10(int res, int* host);                          // 0x4e6c10
extern "C" int   __cdecl InterfaceCastEditor(void** ref);                       // 0x421eb0
extern "C" void* __cdecl ResourceMan_GetManager2();                             // 0x67dcd0
struct ResMan {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual char GetResource(void* key, void** out, int a, int b, int c, int d); // +0xc
};
struct IconSink {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void AcceptIconRecord(RefList3* rec);   // +0x14
};
struct BitSet60 {
    uint32_t mWords[2];
    bool test(uint32_t idx)
    {
        if (idx >= 60)
            return false;
        uint32_t word = mWords[idx / 32];
        return (word & (1u << (idx % 32))) != 0;
    }
};
struct VerbHost {
    char      pad0[0xdc8];
    BitSet60  mDisabled;                // +0xdc8
    bool      IsAvailable();            // 0x44c030
};
// ---- items of slice s004e5050 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" char  __cdecl GetPropertyAsKey(void* list, uint32_t id, void* out);        // 0x6a1250
extern "C" char  __cdecl GetPropertyAsKeyInstance(void* list, uint32_t id, void* out); // 0x6a12a0
extern uint32_t  DAT_015d9ed8;
extern "C" void* __cdecl ReserveAutoRef(void* list, uint32_t id, int* count, void** data); // 0x6a0ae0
extern "C" void  __cdecl Emit7990(RefList3* out, int id);                        // 0x4e7990
extern "C" void  __cdecl Func4b5440v(RefList3* v);                              // 0x4b5440

// ---- items of slice s004e5d00 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
PropertyManager* GetPropertyManager_s004e_5d00();   // 0x0067de30 (SP::PropertyManager)
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
struct VerbData {                   // per-verb record handed out by the owner
    char pad0[0x1c];
    uint32_t mPropID;               // +0x1c
    uint32_t mGroupID;              // +0x20
    char pad1[0x3e0 - 0x24];
    uint32_t mAbilityA;             // +0x3e0
    uint32_t mAbilityB;             // +0x3e4
    uint32_t GetPropID() const { return mPropID; }
    uint32_t GetGroupID() const { return mGroupID; }
    uint32_t GetAbilityA() const { return mAbilityA; }
    uint32_t GetAbilityB() const { return mAbilityB; }
};
struct VerbOwner {
    int GetCount();                 // 0x004accf0
    int Get(int i);                 // 0x004accb0 (VerbData* as an integer handle)
};
bool __cdecl IsVerbUsable(VerbData* v);                                       // 0x004e57f0
void __cdecl AddVerbIcons(PropertyList* pl, IconVec* out, VerbFlags* flags);  // 0x004e5960
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
void FillRefVec6a10(void* owner, RefVec* out); // 0x004e6a10
void BuildVerbCapabilities(IconVec* out, VerbFlags* flags); // 0x004e5d00
// ---- items of slice s004e5d00 end

// ---- items of slice s004e7990 begin (TODO(rewrite): local stubs, replace by canonical classes)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
extern "C" uint32_t __cdecl FNV1_String8(const char* s, uint32_t basis, int flag);   // 0x00932e80
void* __cdecl operator new(unsigned int size, const char* tag, int a, int b, int c, int d) throw();  // 0x00f473a0 (EASTL_allocator_allocate)
struct IRefObj {
    virtual int AddRef();
    virtual int Release();
};
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
template <class T> struct AutoRefCountOut {
    T* mpObject;
    AutoRefCountOut(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCountOut() { if (mpObject) mpObject->Release(); }
    T** GetAddress();                                     // 0x0041d870
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
struct cSpeciesProfile;
struct VerbAbility {
    char pad[0x130];
    int mVerbType;                           // +0x130
    int GetVerbType() { return mVerbType; }
};
struct cSPCreatureVerbIconData : cSPEditorVerbIconData_s004e_7990 {
    char pad0c4[0xd0 - 0xc4];
    cSPCreatureVerbIconData();               // 0x005e5b60
    void Init(cSpeciesProfile* profile, VerbAbility* ability, int index);   // 0x005e5950
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
IPropertyManager* __cdecl PropertyManager();                                    // 0x0067de30
void FillRefVec18(RefVec_s004e_7990* out, uint32_t key); // 0x004e7990
void FillRefVec3(void* a, RefVec_s004e_7990* out, void* b, float c); // 0x004e7eb0
struct VerbSink_s004e_7990 {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void Deliver(RefVec_s004e_7990* v); // vtable +0x14
};
struct TreeNode;
struct TreeHead {
    uint32_t        pad0;
    void*           mNext;   // +0x4
    void*           mPrev;   // +0x8
    TreeNode*       mRoot;   // +0xc
    unsigned char   mFlag;   // +0x10
    char            pad1[3];
    int             mCount;  // +0x14

    void FreeNode(TreeNode* node); // 0x004e8a30
    void Reset();                  // @ 0x004e8850
};
#define HASH_NAME(s) FNV1_String8(s, 0x811c9dc5, 1)
struct Entry8 { uint32_t a, b; };
struct EntryVec {
    Entry8* mBegin;
    Entry8* mEnd;
    Entry8* mCap;
    uint32_t mAlloc[2];
    EntryVec() { mBegin = 0; mEnd = 0; mCap = 0; }
    ~EntryVec();                                          // 0x0045daf0
};
struct EntryOwner {
    char pad[0x18];
    uint32_t mKey;                                        // +0x18
    uint32_t GetKey() { return mKey; }
};
void __cdecl ApplyOwnerEntries(EntryOwner* owner, EntryVec* out);                  // 0x00433210
void __cdecl BuildVerbIcons(EntryVec* entries, RefVec_s004e_7990* out, uint32_t key);         // 0x004e7610
struct EditorRig;
struct AbilityVec {                                       // eastl::vector<ability*>
    VerbAbility** mBegin;
    VerbAbility** mEnd;
    VerbAbility** mCap;
    int size() const { return (int)(mEnd - mBegin); }
    VerbAbility*& operator[](int i) { return mBegin[i]; }
};
struct SpeciesVecInit {
    void* a; void* b; void* c;
    SpeciesVecInit() { a = 0; b = 0; c = 0; }
};
struct cSpeciesProfile {
    char pad0[0x56c];
    float mBoundsZ;                                       // +0x56c (aabb_origin.z)
    char pad570[0x604 - 0x570];
    uint32_t carnivore_level;                             // +0x604
    uint32_t herbivore_level;                             // +0x608
    uint32_t jump_level;                                  // +0x60c
    char pad610[0x6d4 - 0x610];
    AbilityVec abilities;                                 // +0x6d4
    char pad6e0[0x73c - 0x6e0];
    AbilityVec passiveAbilities;                          // +0x73c
    char pad748[0xa18 - 0x748];
    cSpeciesProfile(SpeciesVecInit* v, int a);            // 0x004d3dd0
    ~cSpeciesProfile();                                   // 0x004d44e0
    bool Update(EditorRig* rig);                          // 0x004d5020
};
uint32_t __cdecl GetPropIDForAbility(uint32_t ability, int flags);                 // 0x00459370
float __cdecl FUN_4d12a0(void* arg);                                               // 0x004d12a0
int __cdecl GetVerbCategory(int verbType);                                         // 0x004e58c0
bool __cdecl IsDietCategory(int category);                                         // 0x004e5910
// ---- items of slice s004e7990 end

// ---- items of slice s004e88a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void AllocFree(void* p); // 0x00f47380
struct Key5 {
    int m0, m1, m2, m3, m4;
};
struct NodeAlloc {
    char pad[0x18];
    Key5* Allocate(const Key5* rp); // @ 0x004e8d30
};
struct FreeCtx {
    void FreeNodes(void* p); // @ 0x004e8a30
};
struct RBNode {
    RBNode* mLeft;   // +0
    RBNode* mRight;  // +4
    RBNode* mParent; // +8
    int     mColor;  // +0xc
    int     mKey;    // +0x10
};
struct RBSink {
    RBNode* mNode;         // +0
    void Init(void* node); // 0x00566c50
    int* Payload();        // 0x00564f50  (returns node + 0x10)
};
inline bool KeyLess(int a, int b) { return a < b; }
namespace eastl {
    void RBTreeInsert(void* node, void* parent, void* header, int side); // 0x009216a0
}
void  __fastcall FUN_005673e0(void* dst, int, const void* src);                            // 0x005673e0
void  __fastcall FUN_00422c50(void* it, int);                                              // 0x00422c50
void  __fastcall FUN_004e8da0(void* self, int, void* out, const Key5* value, char flag);   // 0x004e8da0
void* __fastcall FUN_004e8980(void* self, int, void* out, RBNode* pos, const Key5* value); // 0x004e8980
struct RBTree {
    int      pad0;    // +0
    void*    mAnchor; // +4
    void*    mAnchor2;// +8
    RBNode*  mRoot;   // +0xc
    int      pad10;   // +0x10
    int      mCount;  // +0x14

    void*   LowerBound(RBSink* out, int* key);                                      // @ 0x004e89c0
    int     FindOrInsert(const int* key);                                           // @ 0x004e88a0
    void*   InsertUnique(void* result, RBNode* pos, const Key5* value, int unused); // @ 0x004e8a80
    RBSink* InsertNode(RBSink* result, RBNode* pos, const Key5* value, char flag);  // @ 0x004e8be0
};
// ---- items of slice s004e88a0 end

// @ 0x004e5050
Key3* GetVerbIconKeyForModelType(Key3* out, int modelType)
{
    int config = Editor_GetConfigFromModelType(modelType);
    if (config == -1) {
        out->w[0] = 0;
        out->w[1] = 0;
        out->w[2] = 0;
    } else {
        AutoRef prop;
        prop.mp = 0;
        PropList* mgr = (PropList*)GetPropertyManager67de30();
        void** pp = prop.Prepare();
        mgr->GetPropertyList(config, DAT_015d9ed8, pp);
        if (prop.mp != 0) {
            Key3 local;
            local.w[0] = 0;
            local.w[1] = 0;
            local.w[2] = 0;
            if (GetPropertyAsKey(prop.mp, 0x4aa3989, &local)) {
                out->w[0] = local.w[0];
                out->w[1] = local.w[1];
                out->w[2] = local.w[2];
                if (prop.mp != 0)
                    ((RefCounted*)prop.mp)->Release();
                return out;
            }
        }
        out->w[0] = 0;
        out->w[1] = 0;
        out->w[2] = 0;
        if (prop.mp != 0)
            ((RefCounted*)prop.mp)->Release();
    }
    return out;
}

// @ 0x004e5180
bool ComputeCategoryRankImageMap(VerbHost5180* self, int category, int modelType)
{
    Key3 key;
    GetVerbIconKeyForModelType(&key, modelType);
    if (key.w[0] == 0)
        return false;
    Func4e8850(self);
    AutoRef list;
    list.mp = 0;
    PropList* mgr = (PropList*)GetPropertyManager();
    if (list.mp != 0) {
        void* tmp = list.mp;
        list.mp = 0;
        ((RefCounted*)tmp)->Release();
    }
    mgr->GetPropertyList(key.w[0], key.w[2], (void**)&list.mp);

    int count = 0;
    char ok = 0;
    PtrVector* models = 0;
    ok = (char)ReserveAutoRef(list.mp, 0x4aa3838, &count, (void**)&models);
    if (count > 0 && ok) {
        int rank = 0;
        for (int i = 0; i < count; ++i) {
            AutoRef inner;
            inner.mp = 0;
            PropList* mgr2 = (PropList*)GetPropertyManager();
            if (inner.mp != 0) {
                void* tmp = inner.mp;
                inner.mp = 0;
                ((RefCounted*)tmp)->Release();
            }
            mgr2->GetPropertyList(models->mpBegin[i * 3], 0xaf028f41, (void**)&inner.mp);

            Key3 iconKey;
            GetPropertyAsKeyInstance(inner.mp, 0x6286814, &iconKey);

            Key3 outKey;
            outKey.w[0] = 0;
            outKey.w[1] = 0;
            outKey.w[2] = 0;
            GetPropertyAsKey(inner.mp, 0x4a20fe7, &outKey);
            outKey.w[2] = 0x40464100;
            outKey.w[1] = 0x510a95b;

            int subCount = 0;
            PtrVector* subVec = 0;
            ReserveAutoRef(inner.mp, 0x4a20feb, &subCount, (void**)&subVec);
            for (int j = 0; j < subCount; ++j) {
                int rec[4];
                rec[0] = rank;
                rec[1] = outKey.w[0];
                rec[2] = outKey.w[1];
                rec[3] = outKey.w[2];
                void* entry = (void*)subVec->mpBegin[j * 3];
                int* slot = Func4e88a0(self, &entry);
                slot[0] = rec[0];
                slot[1] = rec[1];
                slot[2] = rec[2];
                slot[3] = rec[3];
                ++rank;
            }
            if (inner.mp != 0)
                ((RefCounted*)inner.mp)->Release();
        }
    }
    if (list.mp != 0)
        ((RefCounted*)list.mp)->Release();
    return true;
}

// @ 0x004e5410
char ComputeVerbIconData(Key3 key, uint32_t verbId, int* host, float rate)
{
    switch ((int)verbId) {
    // --- named-icon path: match the config name, then build by id -------------
    case 0x4178b8e8:
    case 0x372e2c04:
    case 0x65672ade:
    case (int)0x9ea3031a:
    case (int)0xccc35c46:
    {
        AutoRef cfg;
        cfg.mp = 0;
        void* cfgPtr = PrepareRef(&cfg);
        char same = NameCompare(&key, cfgPtr);
        if (same) {
            int param = VerbIdToIconParam((int)verbId);
            BuildNamedIcon(cfg.mp, host, param, rate);
            if (cfg.mp != 0)
                ((RefCounted*)cfg.mp)->Release();
            return 1;
        }
        if (cfg.mp != 0)
            ((RefCounted*)cfg.mp)->Release();
        return 0;
    }
    // --- resource path (Emit7da0), most verb ids ------------------------------
    case 0x1a4e0708:
    case (int)0xc0b74287:
    case 0x2a5147a9:
    case 0x1f2a25b6:
    case 0x2090a11b:
    case 0x441cd3e6:
    case 0x449c040f:
    case 0x7d433fad:
    case (int)0x8f963dcb:
    case (int)0x9ad7d4aa:
    case (int)0xbc1041e6:
    case (int)0xc15695da:
    case (int)0xf670aa43:
    {
        AutoRef res;
        res.mp = 0;
        ResMan* rm = (ResMan*)ResourceMan_GetManager2();
        if (res.mp != 0) {
            void* tmp = res.mp;
            res.mp = 0;
            ((RefCounted*)tmp)->Release();
        }
        if (!rm->GetResource(&key, &res.mp, 0, 0, 0, 0)) {
            if (res.mp != 0)
                ((RefCounted*)res.mp)->Release();
            return 0;
        }
        int editor = InterfaceCastEditor(&res.mp);
        if (editor == 0) {
            if (res.mp != 0)
                ((RefCounted*)res.mp)->Release();
            return 0;
        }
        Emit7da0(editor, host);
        if (res.mp != 0)
            ((RefCounted*)res.mp)->Release();
        return 1;
    }
    // --- resource path (Emit6c10) --------------------------------------------
    case (int)0xdfad9f51:
    {
        AutoRef res;
        res.mp = 0;
        ResMan* rm = (ResMan*)ResourceMan_GetManager2();
        if (res.mp != 0) {
            void* tmp = res.mp;
            res.mp = 0;
            ((RefCounted*)tmp)->Release();
        }
        if (!rm->GetResource(&key, &res.mp, 0, 0, 0, 0)) {
            if (res.mp != 0)
                ((RefCounted*)res.mp)->Release();
            return 0;
        }
        int editor = InterfaceCastEditor(&res.mp);
        if (editor == 0) {
            if (res.mp != 0)
                ((RefCounted*)res.mp)->Release();
            return 0;
        }
        Emit6c10(editor, host);
        if (res.mp != 0)
            ((RefCounted*)res.mp)->Release();
        return 1;
    }
    // --- default: emit a plain {id,0,0} record --------------------------------
    default:
    {
        RefList3 rec;
        rec.w[0] = 0;
        rec.w[1] = 0;
        rec.w[2] = 0;
        Emit7990(&rec, (int)verbId);
        ((IconSink*)host)->AcceptIconRecord(&rec);
        Func4b5440v(&rec);
        return 0;
    }
    }
}

// @ 0x004e57f0
bool IsCreatureVerbEnabled(VerbHost* self)
{
    if (self && self->IsAvailable() && !self->mDisabled.test(1) && !self->mDisabled.test(2))
        return true;
    return false;
}

// @ 0x004e58c0
int GetVerbCategory(VerbObject* p)
{
    if (p->HasCategory(0x4abbb0d)) {
        int local = 0;
        if (GetPropertyAsKeyInstance(p, 0x4abbb0d, &local))
            return local;
    }
    return 0;
}

// @ 0x004e5910
namespace SP {
namespace EditorUtils {
bool IsDietCategory(SP::eVerbIconCategory id)
{
    return (id == (int)0xa28a67e8 || id == 0x2dfb4f9f || id == (int)0xdfa0d6bf ||
            id == (int)0xd9bcb9f0 || id == 0x521a15d5);
}
}
}  // namespace SP::EditorUtils

// @ 0x004e6720
void Collect6720(VerbOwner* owner, IconVec* out)
{
    VerbFlags flags;
    IdVec seen;
    int i = 0;
    int n = owner->GetCount();
    for (; i < n; ++i) {
        int verb = owner->Get(i);
        if (find(seen.begin(), seen.end(), verb) == seen.end()) {
            if (IsVerbUsable((VerbData*)verb)) {
                seen.push_back(verb);
                if (((VerbData*)verb)->GetAbilityA() != 0) {
                    int a = ((VerbData*)verb)->GetAbilityA();
                    seen.push_back(a);
                } else if (((VerbData*)verb)->GetAbilityB() != 0) {
                    int b = ((VerbData*)verb)->GetAbilityB();
                    seen.push_back(b);
                }
                AutoRefCount<PropertyList> pl;
                GetPropertyManager_s004e_5d00()->GetPropertyList(((VerbData*)verb)->GetPropID(), ((VerbData*)verb)->GetGroupID(), pl.AsPPVoidParam());
                AddVerbIcons(pl.mp, out, &flags);
            }
        }
    }
    BuildVerbCapabilities(out, &flags);
}

// @ 0x004e6c10
void BuildDispatch6c10(void* owner, VerbSink* sink)
{
    if (owner != 0) {
        RefVec vec;
        FillRefVec6a10(owner, &vec);
        sink->Deliver(&vec);
    }
}

// @ 0x004e7990
void FillRefVec18(RefVec_s004e_7990* out, uint32_t key)
{
    uint32_t hash = 0;
    switch ((int)key) {
    case 0x7d433fad: hash = HASH_NAME("Vehicle_MilitaryLand"); break;
    case 0x8f963dcb: hash = HASH_NAME("Vehicle_MilitarySea"); break;
    case 0x441cd3e6: hash = HASH_NAME("Vehicle_MilitaryAir"); break;
    case 0xf670aa43: hash = HASH_NAME("Vehicle_EconomicLand"); break;
    case 0x2a5147a9: hash = HASH_NAME("Vehicle_EconomicSea"); break;
    case 0x1a4e0708: hash = HASH_NAME("Vehicle_EconomicAir"); break;
    case 0x9ad7d4aa: hash = HASH_NAME("Vehicle_ReligiousLand"); break;
    case 0x1f2a25b6: hash = HASH_NAME("Vehicle_ReligiousSea"); break;
    case 0x449c040f: hash = HASH_NAME("Vehicle_ReligiousAir"); break;
    case 0xbc1041e6: hash = HASH_NAME("Vehicle_ColonyLand"); break;
    case 0xc15695da: hash = HASH_NAME("Vehicle_ColonySea"); break;
    case 0x2090a11b: hash = HASH_NAME("Vehicle_ColonyAir"); break;
    case 0x98e03c0d: hash = HASH_NAME("Vehicle_UFO"); break;
    case 0x99e92f05: hash = HASH_NAME("Building_CityHall"); break;
    case 0x4e3f7777: hash = HASH_NAME("Building_House"); break;
    case 0x47c10953: hash = HASH_NAME("Building_Factory"); break;
    case 0x72c49181: hash = HASH_NAME("Building_Entertainment"); break;
    }
    if (hash != 0) {
        AutoRefCount_s004e_7990<IRefObj> k(0);
        PropertyManager()->GetProperty(hash, 0x1b68db4, k.GetAddress());
        cSPEditorVerbIconData_s004e_7990* info = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData_s004e_7990();
        info->SetIcon(k.mpObject);
        ScratchSlots<2>();
        out->push_back(AutoRefCount_s004e_7990<cSPEditorVerbIconData_s004e_7990>(info));
    }
}

// @ 0x004e7da0
void ConvertOwnerEntries(EntryOwner* owner, VerbSink_s004e_7990* sink)
{
    if (owner) {
        EntryVec entries;
        ApplyOwnerEntries(owner, &entries);
        {
            RefVec_s004e_7990 vec;
            BuildVerbIcons(&entries, &vec, owner->GetKey());
            sink->Deliver(&vec);
        }
        for (Entry8* p = entries.mBegin; p < entries.mEnd; p++) {
        }
    }
}

// @ 0x004e7eb0
void BigBuilder2368(EditorRig* rig, RefVec_s004e_7990* out, void* arg3, float minValue)
{
    if (rig) {
        SpeciesVecInit vecInit;
        cSpeciesProfile profile(&vecInit, 0);
        profile.Update(rig);
        int total = profile.abilities.size() + profile.passiveAbilities.size();
        uint32_t propId = GetPropIDForAbility(0x31c3e5b2, 0);
        AutoRefCountOut<IRefObj> carnProp(0);
        if (propId != 0) {
            IPropertyManager* pm = PropertyManager();
            pm->GetProperty(propId, 0xdd91ac58, carnProp.GetAddress());
        }
        float scale = FUN_4d12a0(arg3);
        out->resize(total + 3);
        cSPEditorVerbIconData_s004e_7990* carnIcon = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData_s004e_7990();
        carnIcon->SetIcon(carnProp.mpObject);
        carnIcon->mValue = (float)profile.carnivore_level;
        cSPEditorVerbIconData_s004e_7990* sizeIcon = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData_s004e_7990();
        AutoRefCountOut<IRefObj> sizeProp(0);
        IPropertyManager* pm2 = PropertyManager();
        pm2->GetProperty(0x5ce214c5, 0xdd91ac58, sizeProp.GetAddress());
        sizeIcon->SetIcon(sizeProp.mpObject);
        sizeIcon->mValue = scale + profile.mBoundsZ;
        if (minValue > 0.0f)
            sizeIcon->mValue = minValue;
        int idx = 0;
        (*out)[idx++] = carnIcon;
        (*out)[idx++] = sizeIcon;
        int nPassive = profile.passiveAbilities.size();
        int nAbilities = profile.abilities.size();
        bool hasJump = profile.jump_level != 0;
        bool hasHerb = profile.herbivore_level != 0;
        bool both = hasJump && hasHerb;
        AutoRefCount_s004e_7990<IRefObj> dietProp(0);
        float levelSum = (float)(profile.jump_level + profile.herbivore_level);
        uint32_t dietId;
        if (both)
            dietId = GetPropIDForAbility(0x4d18972, 0);
        else if (hasJump)
            dietId = GetPropIDForAbility(0x22e785c, 0);
        else if (hasHerb)
            dietId = GetPropIDForAbility(0x22e7847, 0);
        else
            dietId = GetPropIDForAbility(0x4d18c4c, 0);
        IPropertyManager* pm3 = PropertyManager();
        pm3->GetProperty(dietId, 0xdd91ac58, dietProp.GetAddress());
        cSPEditorVerbIconData_s004e_7990* dietIcon = new("Editor", 0, 0, 0, 0) cSPEditorVerbIconData_s004e_7990();
        dietIcon->SetIcon(dietProp.mpObject);
        dietIcon->mValue = levelSum;
        (*out)[idx++] = dietIcon;
        for (int i = idx; i < total + idx; i++) {
            int j = i - idx;
            VerbAbility* ability;
            if (j < profile.abilities.size())
                ability = profile.abilities[j];
            else
                ability = profile.passiveAbilities[j - profile.abilities.size()];
            bool isDiet = IsDietCategory(GetVerbCategory(ability->GetVerbType()));
            if (!isDiet) {
                cSPCreatureVerbIconData* cv = new("Editor", 0, 0, 0, 0) cSPCreatureVerbIconData();
                cv->Init(&profile, ability, i);
                (*out)[i] = cv;
            } else {
                (*out)[i] = 0;
            }
        }
    }
}

// @ 0x004e87f0
void BuildAndDispatch3(void* a, VerbSink_s004e_7990* sink, void* b, float c)
{
    uint32_t scratch[6];
    RefVec_s004e_7990 vec;
    FillRefVec3(a, &vec, b, c);
    sink->Deliver(&vec);
}

// @ 0x004e8850
void TreeHead::Reset()
{
    FreeNode(mRoot);
    mNext = &mNext;
    mPrev = &mNext;
    mRoot = 0;
    mFlag = 0;
    mCount = 0;
}

// @ 0x004e88a0
int RBTree::FindOrInsert(const int* key)
{
    RBSink lb;   // lower_bound result
    RBSink end;  // end() handle
    LowerBound(&lb, (int*)key);
    end.Init((char*)this + 4);
    if (lb.mNode == end.mNode || *key < *lb.Payload()) {
        Key5 value;
        value.m0 = *key;
        value.m1 = 0;
        value.m2 = 0;
        value.m3 = 0;
        value.m4 = 0;
        RBSink node;
        RBSink* r = (RBSink*)FUN_004e8980(this, 0, &node, lb.mNode, &value);
        lb.mNode = r->mNode;
    }
    return (int)((char*)lb.Payload() + 4);
}

// @ 0x004e89c0
void* RBTree::LowerBound(RBSink* out, int* key)
{
    RBNode* current = mRoot;
    RBNode* candidate = (RBNode*)&mAnchor;
    void* unused;
    while (current != 0) {
        if (KeyLess(current->mKey, *key)) {
            current = current->mLeft;
        } else {
            candidate = current;
            current = current->mRight;
        }
    }
    out->Init(candidate);
    return out;
}

// @ 0x004e8a30
void FreeCtx::FreeNodes(void* p)
{
    while (p != 0) {
        FreeNodes(*(void**)p);
        void* next;
        void* tmp = ((void**)p)[1];
        next = p;
        AllocFree(next);
        p = tmp;
    }
}

// @ 0x004e8a80
void* RBTree::InsertUnique(void* result, RBNode* pos, const Key5* value, int unused)
{
    (void)unused;
    if (pos == (RBNode*)mAnchor || pos == (RBNode*)((char*)this + 4)) {
        if (mCount != 0 && ((RBNode*)mAnchor)->mKey < value->m0) {
            InsertNode((RBSink*)result, (RBNode*)mAnchor, value, 0);
        } else {
            RBSink n;
            FUN_004e8da0(this, 0, &n, value, 0);
            FUN_005673e0(result, 0, &n);
        }
    } else {
        RBSink before;
        FUN_005673e0(&before, 0, &pos);
        FUN_00422c50(&before, 0);
        if (pos->mKey < value->m0 && value->m0 < before.mNode->mKey) {
            if (pos->mLeft == 0)
                InsertNode((RBSink*)result, pos, value, 0);
            else
                InsertNode((RBSink*)result, before.mNode, value, 1);
        } else {
            RBSink n;
            FUN_004e8da0(this, 0, &n, value, 0);
            FUN_005673e0(result, 0, &n);
        }
    }
    return result;
}

// @ 0x004e8be0
RBSink* RBTree::InsertNode(RBSink* result, RBNode* pos, const Key5* value, char flag)
{
    int side;
    if (flag == 0 && pos != (RBNode*)((char*)this + 4) && pos->mKey <= value->m0)
        side = 1;
    else
        side = 0;
    RBNode* node = (RBNode*)reinterpret_cast<NodeAlloc*>(this)->Allocate(value);
    eastl::RBTreeInsert(node, pos, (char*)this + 4, side);
    this->mCount += 1;
    result->Init(node);
    return result;
}

// @ 0x004e8da0
void Body8da0(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}
