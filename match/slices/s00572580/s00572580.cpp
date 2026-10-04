// slice s00572580
// Mostly /O2. RandomRange/RandomSigned, GetComplexityFraction and the editor ground samplers
// are /arch:SSE /fp:fast (see manifest).
#include <new>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <intrin.h>
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

// ---------------------------------------------------------------------------
// Small containers / smart pointers
// ---------------------------------------------------------------------------
struct UintArray {
    uint32_t mData[1];
    // @ 0x00572580
    uint32_t* At(int i);
    // @ 0x00572590
    UintArray* Self();
};

uint32_t* UintArray::At(int i) { return &mData[i]; }
UintArray* UintArray::Self() { return this; }

struct AtomicRefCounted {
    void* mpVtbl;
    uint32_t mPad;
    long mnRefCount;       // +0x08
    inline void AddRef() { _InterlockedIncrement(&mnRefCount); }
};

struct AtomicRefPtr {
    AtomicRefCounted* mp;
    AtomicRefPtr(AtomicRefCounted* p);
};

// @ 0x005725b0
AtomicRefPtr::AtomicRefPtr(AtomicRefCounted* p) : mp(p)
{
    if (mp)
        mp->AddRef();
}

struct IRefCount {
    virtual int AddRef();     // +0x00
    virtual int Release();    // +0x04
};

struct IObject {
    virtual void* Cast(uint32_t id);   // +0x00
    virtual int AddRef();              // +0x04
    virtual int Release();             // +0x08
};

struct ObjectPtr {
    IObject* mp;
    ObjectPtr(const ObjectPtr& x);
};

// @ 0x005725d0
ObjectPtr::ObjectPtr(const ObjectPtr& x) : mp(x.mp)
{
    if (mp)
        mp->AddRef();
}

struct IRefCountPtr {
    IRefCount* mp;
    IRefCountPtr(IRefCount* p);
};

// @ 0x00572660
IRefCountPtr::IRefCountPtr(IRefCount* p) : mp(p)
{
    if (mp)
        mp->AddRef();
}

namespace EA {
template <typename T>
struct RectT {
    T mLeft, mTop, mRight, mBottom;
    RectT& operator=(const RectT& r);
};

// @ 0x00572600
template <typename T>
RectT<T>& RectT<T>::operator=(const RectT<T>& r)
{
    mLeft = r.mLeft;
    mTop = r.mTop;
    mRight = r.mRight;
    mBottom = r.mBottom;
    return *this;
}
template struct RectT<float>;
}

struct RefCounted {
    virtual ~RefCounted();
    int mnRefCount;        // +0x04
    inline void AddRef() { ++mnRefCount; }
    inline void Release() {
        if (--mnRefCount == 0) {
            mnRefCount = 1;
            delete this;
        }
    }
};

struct RefCountedPtr {
    RefCounted* mp;
    RefCountedPtr& operator=(RefCounted* p);
};

// @ 0x00572680
RefCountedPtr& RefCountedPtr::operator=(RefCounted* p)
{
    if (p != mp) {
        RefCounted* const old = mp;
        if (p)
            p->AddRef();
        mp = p;
        if (old)
            old->Release();
    }
    return *this;
}

struct String16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void clear();
};

// @ 0x005726c0
void String16::clear()
{
    if (mpBegin != mpEnd) {
        *mpBegin = 0;
        mpEnd = mpBegin;
    }
}

namespace SP {
template <int N>
struct MessageBasicRC {
    union Data {
        void* mpVoid;
        IRefCount* mpRC;
        uint64_t mUint64;
    };
    void* mpVtbl;
    int mnRefCount;
    Data mData[N];        // +0x08
    uint32_t mId;
    uint32_t mPad;
    uint32_t mRCFlags;

    void SetIRefCount(int i, IRefCount* p);
};

// @ 0x005726e0
template <int N>
void MessageBasicRC<N>::SetIRefCount(int i, IRefCount* p)
{
    const uint32_t mask = 1 << i;
    if ((mRCFlags & mask) && mData[i].mpRC)
        mData[i].mpRC->Release();
    mData[i].mpRC = p;
    if (p)
        p->AddRef();
    mRCFlags |= mask;
}
template struct MessageBasicRC<5>;
}

// ---------------------------------------------------------------------------
// Serialization
// ---------------------------------------------------------------------------
struct IStream;
namespace EA { namespace IO {
uint32_t __cdecl WriteUint32(IStream* s, const uint32_t* p, uint32_t n, int endian);
} }

struct IStreamHolder {
    PV4 PV2
    virtual IStream* GetStream();     // +0x18
};
struct ISerializer {
    PV8
    virtual IStreamHolder* GetHolder();   // +0x20
};

inline uint32_t WriteUint32(IStream* st, uint32_t v) { return EA::IO::WriteUint32(st, &v, 1, 0); }

// @ 0x00572840
bool __cdecl WriteUint32Value(ISerializer* s, const uint32_t* v)
{
    WriteUint32(s->GetHolder()->GetStream(), *v);
    return true;
}

// @ 0x00572880
bool __cdecl WriteUint32Array6(ISerializer* s, const uint32_t* v)
{
    const int count = 6;
    WriteUint32(s->GetHolder()->GetStream(), count);
    for (int i = 0; i < count; ++i) {
        WriteUint32(s->GetHolder()->GetStream(), *v);
        ++v;
    }
    return true;
}

// ---------------------------------------------------------------------------
// String16 helpers
// ---------------------------------------------------------------------------

// @ 0x005728f0  find_first_of over reverse iterators (find_last_of helper)
const wchar_t* __cdecl FindLastOf(const wchar_t* pEnd, const wchar_t* pBegin, const wchar_t* p2Begin, const wchar_t* p2End)
{
    for (; pEnd != pBegin; --pEnd) {
        for (const wchar_t* p = p2Begin; p != p2End; ++p) {
            if (pEnd[-1] == *p)
                return pEnd;
        }
    }
    return pBegin;
}

inline wchar_t ToLower16(wchar_t c)
{
    if (c <= 0xff)
        return (wchar_t)tolower((uint8_t)c);
    return c;
}

// @ 0x00572930
int __cdecl CompareI16(const wchar_t* a, const wchar_t* b, uint32_t n)
{
    for (; n > 0; ++a, ++b, --n) {
        const wchar_t c1 = ToLower16(*a);
        const wchar_t c2 = ToLower16(*b);
        if (c1 != c2)
            return (c1 < c2) ? -1 : 1;
    }
    return 0;
}

struct Vec3 { float x, y, z; };

struct VecPair {
    Vec3 mA;
    Vec3 mB;
    inline VecPair& operator=(const VecPair& o) {
        mB = o.mB;
        mA = o.mA;
        return *this;
    }
};

// @ 0x005729b0
VecPair* __cdecl CopyVecPairs(VecPair* first, VecPair* last, VecPair* dest)
{
    for (; first != last; ++dest, ++first)
        *dest = *first;
    return dest;
}

// ---------------------------------------------------------------------------
// Random (/arch:SSE /fp:fast)
// ---------------------------------------------------------------------------
namespace EA { namespace Random {
class RandomLinearCongruential {
public:
    uint32_t mnSeed;
    double RandomDoubleUniform();
};
} }
extern EA::Random::RandomLinearCongruential sMathRandom;

inline float RandomRangeInline(float a, float b)
{
    const double lo = a;
    const double hi = b;
    const double r = sMathRandom.RandomDoubleUniform();
    const double d = lo + (hi - lo) * r;
    if (d >= hi)
        return (float)hi;
    if (d < lo)
        return (float)lo;
    return (float)d;
}

// @ 0x00572a10
float __cdecl RandomRange(float a, float b)
{
    return RandomRangeInline(a, b);
}

// @ 0x00572a60
float __cdecl RandomSigned(float x)
{
    return RandomRangeInline(-x, x);
}

// ---------------------------------------------------------------------------
// Messaging
// ---------------------------------------------------------------------------
namespace EA { namespace Messaging {
struct IHandler;
struct IServer;
bool RemoveHandler(IServer* server, IHandler* handler, const uint32_t* ids, uint32_t count, int priority);

struct HandlerRegistration {
    IServer* mpServer;
    IHandler* mpHandler;
    const uint32_t* mpIds;
    uint32_t mnCount;
    int mnPriority;
    void Unregister();
};

// @ 0x00572ab0
void HandlerRegistration::Unregister()
{
    if (mpServer) {
        IServer* const server = mpServer;
        mpServer = 0;
        RemoveHandler(server, mpHandler, mpIds, mnCount, mnPriority);
    }
}
} }

namespace Simulator {
class cThemeMusicManagerBase {
public:
    cThemeMusicManagerBase() : mField04(0) {}
    virtual ~cThemeMusicManagerBase();
    uint32_t mField04;
};

class cThemeMusicManager : public cThemeMusicManagerBase {
public:
    cThemeMusicManager();
    virtual ~cThemeMusicManager();
    uint32_t mField08;
    uint32_t mField0C;
    uint32_t mField10;
    bool mbField14;
    bool mbField15;
    uint32_t mField18;
    uint32_t mField1C;
    uint32_t mField20;
    uint32_t mField24;
    uint32_t mField28;
};

// @ 0x00572ae0
cThemeMusicManager::cThemeMusicManager()
    : mField08(0), mField0C(0), mField10(0), mbField14(false), mbField15(false),
      mField18(0), mField1C(0), mField20(0), mField24(0), mField28(0)
{
}
}

// ---------------------------------------------------------------------------
// Complexity meter
// ---------------------------------------------------------------------------
struct ComplexityEntry {      // 0x8c bytes
    int mCost;                // +0x00
    uint32_t pad04[3];
    int mBakeCost;            // +0x10
    uint32_t pad14[(0x8c - 0x14) / 4];
};

struct EntryVector {
    ComplexityEntry* mpBegin;
    ComplexityEntry* mpEnd;
    int size() const { return mpEnd - mpBegin; }
    const ComplexityEntry& operator[](int i) const { return mpBegin[i]; }
};

struct ComplexityBlock {
    char pad0[0x1c];
    EntryVector mEntries;         // +0x1c
    int GetEntryCount();
};

// @ 0x00572b10
int ComplexityBlock::GetEntryCount()
{
    return mEntries.mpEnd - mEntries.mpBegin;
}

struct BlockPtrVector {
    ComplexityBlock** mpBegin;
    ComplexityBlock** mpEnd;
    ComplexityBlock** mpCapacity;
    int size() const { return mpEnd - mpBegin; }
    ComplexityBlock* operator[](int i) const { return mpBegin[i]; }
    int GetSize();
};

template <typename T> inline const T& max_alt(const T& a, const T& b) { return (a < b) ? b : a; }

// @ 0x00572b30  (/arch:SSE /fp:fast)
float __cdecl GetComplexityFraction(const BlockPtrVector& blocks)
{
    int bake = 0, cost = 0;
    for (int i = 0; i < blocks.size(); ++i) {
        const EntryVector& entries = blocks[i]->mEntries;
        for (int j = 0; j < entries.size(); ++j) {
            bake += blocks[i]->mEntries[j].mBakeCost;
            cost += blocks[i]->mEntries[j].mCost;
        }
    }
    const float fBake = (float)bake * 0.001f;
    const float fCost = (float)cost * 0.0002f;
    return max_alt(fBake, fCost);
}

namespace EA { namespace Hash { uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int lowercase); } }

// @ 0x00572c50
uint32_t __cdecl IDFromName16(const wchar_t* name)
{
    return EA::Hash::FNV1_String16(name, 0x811c9dc5, 1);
}

// @ 0x00572c90
int BlockPtrVector::GetSize()
{
    return mpEnd - mpBegin;
}

struct cEditorLimitsCheat {
    const char* GetDescription(int mode) const;
};

// @ 0x00572cd0
const char* cEditorLimitsCheat::GetDescription(int mode) const
{
    return mode ? 0 : "[on | off], toggles, disables (on) or re-enables (off) editor complexity limits. Creations that break the limits will not be pollinated!";
}

// ---------------------------------------------------------------------------
// Editor ground sampling (/arch:SSE /fp:fast)
// ---------------------------------------------------------------------------
struct Vector2 { float x, y; };
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Point3 { float x, y, z; };
extern const Vector3 kDefaultNormal;   // 0x15e5024

struct CollisionFilter {
    uint32_t mTypes[2];
    uint32_t mA, mB, mC;
    uint8_t mMode;
    bool mbFlag;
    CollisionFilter() { mTypes[0] = 0; mTypes[1] = 0; mA = 0; mB = 0; mC = 0; mbFlag = false; }
    void SetType(uint32_t i) { if (i < 64) mTypes[i >> 5] |= 1u << (i & 31); }
};

struct ICollider {
    PV8 PV
    virtual int Raycast(const Vector3* start, const Vector3* end, int a, Vector3* hit, Vector3* normal,
                        CollisionFilter* filter, int b, int c);   // +0x24
};
struct IModelManager {
    PV8 PV2
    virtual uint32_t GetTypeIndex(uint32_t id, int flags);   // +0x28
};
struct cCreature { void SetVisible(int); };      // 0xa04a90
namespace SP {
IModelManager* ModelManager();
struct cSPPlayMode { float GetHeightOffset(); };
struct cCreatureStructure { char pad0[0x2c]; Point3 mOffset; };
struct cSPEditorAnimatedCreatureManager {
    cCreatureStructure* GetCreatureStructure(uint32_t id);
    ::cCreature* GetCreature(uint32_t id);
};
}

struct cEditorGround {
    char pad0[0x7c];
    SP::cSPPlayMode* mpPlayMode;     // +0x7c
    char pad80[4];
    ICollider* mpCollider84;         // +0x84
    char pad88[4];
    ICollider* mpCollider8C;         // +0x8c
    char pad90[0x31c - 0x90];
    int mEditorMode;                 // +0x31c
    char pad320[0x360 - 0x320];
    SP::cSPEditorAnimatedCreatureManager* mpCreatureMgr;   // +0x360
    uint32_t mCreatureId;            // +0x364
};

// @ 0x00572cf0
float __cdecl EditorGroundSampler(cEditorGround* editor, uint32_t unused, const Vector2& pos, Vector3* pNormal)
{
    float height = 0.0f;
    Vector3 normal = kDefaultNormal;
    if (editor) {
        ICollider* collider = editor->mpCollider84;
        if (collider) {
            Vector3 hit;
            CollisionFilter filter;
            Vector3 start(pos.x, pos.y, 500.0f);
            Vector3 end(pos.x, pos.y, -10.0f);
            filter.mMode = 4;
            if (editor->mEditorMode == 2) {
                filter.SetType(SP::ModelManager()->GetTypeIndex(0x26f3933, 0));
                float offset = editor->mpPlayMode->GetHeightOffset();
                if (collider->Raycast(&start, &end, 0, &hit, &normal, &filter, 0, 0))
                    height = hit.z + offset;
            } else {
                if (pNormal)
                    *pNormal = kDefaultNormal;
                SP::cCreatureStructure* cs = editor->mpCreatureMgr->GetCreatureStructure(editor->mCreatureId);
                if (cs) {
                    Point3 v = cs->mOffset;
                    return v.z;
                }
                return 0.0f;
            }
        }
        const float inv = 1.0f / sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
        normal.x *= inv;
        normal.y *= inv;
        normal.z *= inv;
        if (pNormal)
            *pNormal = normal;
    }
    return height;
}

// @ 0x00572f00
float __cdecl EditorGroundHeight(cEditorGround* editor, const Vector2& pos)
{
    float height = 0.0f;
    Vector3 normal = kDefaultNormal;
    if (editor) {
        ICollider* collider = editor->mpCollider8C;
        if (collider) {
            CollisionFilter filter;
            Vector3 start(pos.x, pos.y, 500.0f);
            Vector3 end(pos.x, pos.y, -10.0f);
            float offset = 0.0f;
            filter.mMode = 4;
            if (editor->mEditorMode == 2) {
                filter.SetType(SP::ModelManager()->GetTypeIndex(0x223e8e0, 0));
                offset = editor->mpPlayMode->GetHeightOffset();
            }
            Vector3 hit;
            if (collider->Raycast(&start, &end, 0, &hit, &normal, &filter, 0, 0))
                height = hit.z + offset;
        }
    }
    return height;
}

// ---------------------------------------------------------------------------
// cAppModeEditorBase-ish methods
// ---------------------------------------------------------------------------
struct cLimitsData { char pad0[0x34]; bool mbAllow; char pad35[0x6f - 0x35]; bool mbCheckLimits; };
struct cEditorModel { char pad0[0xc]; uint32_t mKey; };
struct cPropertyList { bool GetBool(uint32_t id); };
extern cPropertyList* sAppProperties;
bool __cdecl IsKeyDown(int a, int b);            // 0x8d3200
bool __cdecl IsSpecialKey(const void* key);      // 0x5bf0a0
bool __cdecl IsModelLocked(void* model);         // 0x4a0ac0
uint32_t __cdecl RemapTypeId(uint32_t type);     // 0x432f10
struct ResourceKeyRec { uint32_t pad0[2]; uint32_t mKey8; uint32_t mGroupC; uint32_t pad10[2]; uint32_t mModelType; };
bool __cdecl HasProperty(const ResourceKeyRec* rec, uint32_t id, int flags);   // 0x5580e0

struct IWindowManager {
    PV16 PV16 PV
    virtual int IsModal();                        // +0x84
};
namespace SP { IWindowManager* WindowManager(); }

struct cCursorMgr {
    uint32_t GetCursor();        // 0x8013c0
    void SetCursor(uint32_t id); // 0x801bb0
};
cCursorMgr* __cdecl CursorManager();   // 0x67cab0

struct cUIManager { void Show(uint32_t id); };
cUIManager* __cdecl UIManager();       // 0x67cac0

struct cPaletteUI { bool IsActive(); };    // 0x5dc450
struct cUndoMgr { bool HasPending(); };    // 0x4c58b0
struct cSymmetry { bool IsReady(); };      // 0x5ca920
struct IRelease {
    PV
    virtual void Release();      // +0x04
};

struct cEditor {
    virtual void v00();
    char pad04[0x3c - 4];
    uint32_t mStateFlags;            // +0x3c
    char pad40[4];
    int mSymmetryMode;               // +0x44
    char pad48[0x78 - 0x48];
    cPaletteUI* mpPalette;           // +0x78
    char pad7c[0x98 - 0x7c];
    cEditorModel* mpModel;           // +0x98
    char pad9c[0x150 - 0x9c];
    cUndoMgr* mpUndo;                // +0x150
    char pad154[0x1cc - 0x154];
    cLimitsData* mpLimits;           // +0x1cc
    char pad1d0[0x2a8 - 0x1d0];
    uint32_t mGroup;                 // +0x2a8
    char pad2ac[0x2f6 - 0x2ac];
    bool mbLimitsDisabled;           // +0x2f6
    char pad2f7[0x308 - 0x2f7];
    IRelease* mpRef308;              // +0x308
    IRelease* mpRef30C;              // +0x30c
    char pad310[0x360 - 0x310];
    SP::cSPEditorAnimatedCreatureManager* mpCreatureMgr;   // +0x360
    uint32_t mCreatureId;            // +0x364
    char pad368[0x3c4 - 0x368];
    cSymmetry* mpSymmetry;           // +0x3c4
    char pad3c8[0x4d4 - 0x3c8];
    bool mbFading;                   // +0x4d4

    virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16();
    virtual int GetEditorConfig();   // +0x44

    bool IsLimitAllowed();
    bool CanUseModel(const ResourceKeyRec* rec);
    void ReleaseRefs();
    void HideCreature();
    void ShowCreature();
    void UpdateCursor();
    void SetSymmetryMode(int mode);
};

// @ 0x00573050
bool cEditor::IsLimitAllowed()
{
    if (mpLimits)
        return mpLimits->mbAllow;
    return true;
}

// @ 0x00573070
bool cEditor::CanUseModel(const ResourceKeyRec* rec)
{
    const uint32_t modelType = rec->mModelType;
    bool result = false;
    const uint32_t config = RemapTypeId(modelType);
    if (config != (uint32_t)GetEditorConfig()) {
        result = true;
        switch (GetEditorConfig()) {
        case (int)0xa56567f7:
            if (modelType == 0x9ea3031a || modelType == 0x372e2c04 || modelType == 0xccc35c46 ||
                modelType == 0x65672ade || modelType == 0x4178b8e8)
                result = false;
            break;
        case (int)0x9adf00a9:
            if (modelType == 0x9ea3031a || modelType == 0x372e2c04 || modelType == 0xccc35c46)
                result = false;
            break;
        case (int)0xbc1041e6:
            if (modelType == 0x7d433fad || modelType == 0xf670aa43 || modelType == 0x9ad7d4aa ||
                modelType == 0xbc1041e6)
                result = false;
            break;
        case (int)0xc15695da:
            if (modelType == 0x8f963dcb || modelType == 0x2a5147a9 || modelType == 0x1f2a25b6 ||
                modelType == 0xc15695da)
                result = false;
            break;
        case (int)0xe46c381e:
        case (int)0xfd4902bd:
            if (modelType == 0x9ea3031a && HasProperty(rec, 0xe46c381e, 0))
                result = false;
            break;
        case 0x2090a11b:
            if (modelType == 0x441cd3e6 || modelType == 0x1a4e0708 || modelType == 0x449c040f ||
                modelType == 0x2090a11b)
                result = false;
            break;
        case 0x156276d1:
            if (modelType == 0x9ea3031a || modelType == 0x372e2c04)
                result = false;
            break;
        case 0x37e82da1:
            if (modelType == 0x9ea3031a || modelType == 0x372e2c04 || modelType == 0xccc35c46 ||
                modelType == 0x65672ade)
                result = false;
            break;
        }
    }
    bool bypass = false;
    if (mpLimits && mpLimits->mbCheckLimits && sAppProperties->GetBool(0x677d3ea) && IsKeyDown(0x10, 0x3ff)) {
        const uint32_t group = rec->mGroupC;
        const uint32_t current = mGroup;
        bool same = (group == current);
        if (current == 0x476a98c7 && group == 0x24682294)
            same = true;
        else if (current == 0x24682294 && group == 0x476a98c7)
            same = true;
        if (!mbLimitsDisabled && same)
            bypass = true;
    }
    if (!bypass && result)
        return true;
    if (IsSpecialKey(&mpModel->mKey) || IsSpecialKey(&rec->mKey8))
        return true;
    return false;
}

// @ 0x005732f0
void cEditor::ReleaseRefs()
{
    if (mpRef308) {
        IRelease* p = mpRef308;
        mpRef308 = 0;
        p->Release();
    }
    if (mpRef30C) {
        IRelease* p = mpRef30C;
        mpRef30C = 0;
        p->Release();
    }
}

// @ 0x00573330
void cEditor::HideCreature()
{
    if (mpModel && !IsModelLocked(mpModel) && mpCreatureMgr) {
        if (mpCreatureMgr->GetCreature(mCreatureId)) {
            SP::cSPEditorAnimatedCreatureManager* mgr = mpCreatureMgr;
            mgr->GetCreature(mCreatureId)->SetVisible(0);
        }
    }
}

// @ 0x00573390
void cEditor::ShowCreature()
{
    if (mpCreatureMgr) {
        if (mpCreatureMgr->GetCreature(mCreatureId)) {
            SP::cSPEditorAnimatedCreatureManager* mgr = mpCreatureMgr;
            mgr->GetCreature(mCreatureId)->SetVisible(1);
        }
    }
}

// @ 0x005733d0
void cEditor::UpdateCursor()
{
    const uint32_t current = CursorManager()->GetCursor();
    if (current == 0x1001 || (current > 0x1011 && current <= 0x101a))
        return;
    uint32_t cursor;
    if (!mpPalette->IsActive())
        cursor = 0x1003;
    else if (SP::WindowManager()->IsModal())
        cursor = 0x1002;
    else if (mStateFlags & 0x10)
        cursor = 0x1010;
    else if (mStateFlags & 1)
        cursor = 0x100f;
    else if (mpUndo && mpUndo->HasPending())
        cursor = 0x1024;
    else
        cursor = 0x1002;
    if (cursor != current)
        CursorManager()->SetCursor(cursor);
    mbFading = false;
}

// @ 0x00573480
void cEditor::SetSymmetryMode(int mode)
{
    if (mpSymmetry && mpSymmetry->IsReady()) {
        if (mpPalette && mode != mSymmetryMode)
            mSymmetryMode = mode;
        switch (mode) {
        case 0:
            UIManager()->Show(0x2671afcc);
            mStateFlags += 0x60;
            break;
        case 1:
            UIManager()->Show(0x7f4de3ba);
            mStateFlags = (mStateFlags & ~0x40) + 0x20;
            break;
        case 2:
            UIManager()->Show(0x33c35a06);
            mStateFlags = (mStateFlags & ~0x20) + 0x40;
            break;
        }
    }
}
