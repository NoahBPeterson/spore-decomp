// Slice s00eef810: FUN_00eef810 -- picks a random ResourceKey (template id) for a game-object kind.
// Two families of ids:
//  * four "verb/theme" ids: a verb list is fetched (FUN_00661900), its entry ids are collected into a
//    uint vector, wrapped in a query object (FUN_00669360, id 0xd87454e6) and resolved through the
//    resource manager (vtable +0x38); a random result is returned.
//  * other ids: a list of property values (fixed_vector<uint,5>) is chosen from the id (and from the
//    type field of the optional object p4), turned into FunctionalMatch::Constraints (a single Equal, or
//    an Any-of-Equals compound), then ObjectTemplateDB (vtable +0x30) is asked for templates matching them,
//    and the first one that the resource manager (vtable +0x0c) accepts is returned.
// Flags: /O2 /MD /Gy /TP (no /EHsc: the original has no EH frame).
#include "types.h"
#include <math.h>

void* operator new(unsigned int size, void* p) { return p; }
void operator delete[](void* p);        // 0x00F47380

inline void SpFree(void* p)
{
    if (p && ((int*)p)[-1])
        delete[] (char*)p;
}

struct Key3 { uint32_t mInstance, mType, mGroup; };

struct UintVec {   // eastl::vector<uint32_t, sp_vector_allocator>
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator[2];
    UintVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~UintVec() { SpFree(mpBegin); }
    void reserve(uint32_t n);                                  // 0x004E0880
    void DoInsertValue(uint32_t* pos, const uint32_t& v);      // 0x004558A0
    void push_back(const uint32_t& v)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd++;
            if (p)
                *p = v;
        } else
            DoInsertValue(mpEnd, v);
    }
};

struct KeyVec {    // eastl::vector<ResourceKey>
    Key3* mpBegin;
    Key3* mpEnd;
    Key3* mpCapacity;
    uint32_t mAllocator[2];
    KeyVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~KeyVec() { SpFree(mpBegin); }
};

// eastl::fixed_vector<uint32_t, 5, true>: buffer lives inside the object, header word before it is 0.
struct FixedUintVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mHeader[3];
    uint32_t mBuffer[5];
    FixedUintVec()
    {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 5;
        mHeader[2] = 0;
    }
    ~FixedUintVec() { SpFree(mpBegin); }
    void push_back(const uint32_t& v);                         // 0x0062DEE0
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    uint32_t& operator[](uint32_t i) { return mpBegin[i]; }
};

// ---- the verb list used by the four theme ids (0x34-byte entries) ----
struct VerbEntry { uint32_t mId; uint32_t pad[12]; };
struct VerbVec {
    VerbEntry* mpBegin;
    VerbEntry* mpEnd;
    VerbEntry* mpCapacity;
    uint32_t mAllocator[2];
    VerbVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoDestroyValues(VerbEntry* first, VerbEntry* last);   // 0x00646D70
    ~VerbVec()
    {
        DoDestroyValues(mpBegin, mpEnd);
        SpFree(mpBegin);
    }
};
void FillVerbList(uint32_t id, VerbVec* out);                  // 0x00661900 (cdecl)

class IMsgHandler { public: virtual ~IMsgHandler() {} };      // vtable 0x013EB394

class IdQuery : public IMsgHandler {    // constructed at 0x00669360
public:
    IdQuery(uint32_t id, const UintVec& ids);
    UintVec mIds;       // 0x04
    uint32_t pad[1];
    uint32_t mId;       // 0x18
};

struct IResourceManager {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual bool Accept(const Key3* pKey, int a, int b, int c, int d, int e);    // 0x0C
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34();
    virtual void ResolveQuery(KeyVec* out, IdQuery* pQuery, int flags);          // 0x38
};
IResourceManager* GetManager();                                // 0x0067DCD0

class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t n);   // 0x00A68FB0
};
extern RandomLinearCongruential sMathRandom;                   // 0x01601760

namespace SP {
namespace FunctionalMatch {
enum EqualConstraint { kEquals = 0 };
enum AnyConstraint { kAny = 0 };
struct Constraint;

struct ConstraintVec {   // eastl::vector<Constraint, sp_vector_allocator>
    Constraint* mpBegin;
    Constraint* mpEnd;
    Constraint* mpCapacity;
    uint32_t mAllocator[2];
    ConstraintVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ConstraintVec(const ConstraintVec& x);                     // 0x004E38D0
    ~ConstraintVec();                                          // 0x004E1780
    void push_back(const Constraint& c);                       // 0x004E18E0
    void DoInsertValue(Constraint* pos, const Constraint& c);  // 0x004E39D0
    uint32_t size() const;
};

struct Constraint {
    uint32_t mParameter;
    uint32_t mType;
    int mMin, mMax;
    ConstraintVec mConstraints;
    Constraint(uint32_t param, EqualConstraint, int value);    // 0x00558960
    Constraint(AnyConstraint, ConstraintVec subs);             // 0x00558AE0
    Constraint(const Constraint& x);                           // 0x00606880
    ~Constraint();                                             // 0x006066F0
};

__forceinline void PushBackInline(ConstraintVec& v, const Constraint& c)
{
    if (v.mpEnd < v.mpCapacity) {
        Constraint* p = v.mpEnd;
        v.mpEnd = p + 1;
        if (p)
            new (p) Constraint(c);
    } else
        v.DoInsertValue(v.mpEnd, c);
}
}
}
using namespace SP::FunctionalMatch;

struct IObjectTemplateDB {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C();
    virtual bool FindTemplates(KeyVec* out, int count, ConstraintVec* pConstraints);   // 0x30
};
IObjectTemplateDB* ObjectTemplateDB();                         // 0x0067CB40

struct TypedObject { char pad[0x18]; int mType; };

// @ 0x00EEF810
Key3* FUN_00eef810(Key3* out, uint32_t id, int param3, TypedObject* pObj)
{
    if (id == 0x6031c03a || id == 0xe137ff08 || id == 0x7998ce71 || id == 0xcf56099a) {
        uint32_t listId = 0;
        if (id <= 0xcf56099a) {
            if (id == 0xcf56099a)
                listId = 0x41b55d34;
            else if (id == 0x6031c03a)
                listId = 0x61265923;
            else if (id == 0x7998ce71)
                listId = 0x1cccd45b;
        } else if (id == 0xe137ff08)
            listId = 0x0ffc2cee;

        VerbVec verbs;
        FillVerbList(listId, &verbs);
        UintVec ids;
        ids.reserve((uint32_t)(verbs.mpEnd - verbs.mpBegin));
        for (VerbEntry* e = verbs.mpBegin; e != verbs.mpEnd; ++e)
            ids.push_back(e->mId);
        IdQuery query(0xd87454e6, ids);
        KeyVec found;
        GetManager()->ResolveQuery(&found, &query, 0);
        if (found.mpBegin == found.mpEnd) {
            out->mInstance = 0;
            out->mType = 0;
            out->mGroup = 0;
            return out;
        } else {
            uint32_t idx = sMathRandom.RandomUint32Uniform((uint32_t)(found.mpEnd - found.mpBegin));
            *out = found.mpBegin[idx];
            return out;
        }
    }

    FixedUintVec values;
    uint32_t extra = 0;
    uint32_t key;

    if (id <= 0xd37c1045) {
        if (id == 0xd37c1045 || id == 0x5b3d1d0d) {
            if (!pObj)
                goto groupC;
            switch (pObj->mType) {
            case 0x7d433fad: case (int)0xbc1041e6: case (int)0xf670aa43: case (int)0x9ad7d4aa:
            groupC:
                key = 0x7d433fad; values.push_back(key);
                key = 0xf670aa43; values.push_back(key);
                key = 0x9ad7d4aa; values.push_back(key);
                key = 0xbc1041e6; values.push_back(key);
                break;
            case (int)0x8f963dcb: case (int)0xc15695da: case 0x1f2a25b6: case 0x2a5147a9:
                key = 0x8f963dcb; values.push_back(key);
                key = 0x2a5147a9; values.push_back(key);
                key = 0x1f2a25b6; values.push_back(key);
                key = 0xc15695da; values.push_back(key);
                break;
            case 0x441cd3e6: case 0x1a4e0708: case 0x449c040f: case 0x2090a11b: case (int)0x98e03c0d:
                key = 0x441cd3e6; values.push_back(key);
                key = 0x1a4e0708; values.push_back(key);
                key = 0x449c040f; values.push_back(key);
                key = 0x2090a11b; values.push_back(key);
                key = 0x98e03c0d; values.push_back(key);
                break;
            default:
                goto fail;
            }
            if (values.empty())
                goto fail;
        } else if (id == 0xb10e526f)
            extra = 0x2399be55;
        else
            goto fail;
    } else {
        if (id != 0xe34e8a60)
            goto fail;
        if (param3 != -2)
            extra = 0x2b978c46;
        else {
            key = 0x4178b8e8; values.push_back(key);
            if (values.empty())
                goto fail;
        }
    }

    {
        ConstraintVec constraints;
        if (!values.empty()) {
            if (values.size() == 1)
                constraints.push_back(Constraint(0x2dc9d1e, kEquals, values[0]));
            else {
                ConstraintVec alternatives;
                for (uint32_t i = 0; i < values.size(); ++i)
                    alternatives.push_back(Constraint(0x2dc9d1e, kEquals, values[i]));
                constraints.push_back(Constraint(kAny, alternatives));
            }
        }
        if (extra != 0)
            constraints.push_back(Constraint(0x2dd90af, kEquals, extra));
        PushBackInline(constraints, Constraint(0x54a32960, kEquals, 1));

        KeyVec results;
        if (ObjectTemplateDB()->FindTemplates(&results, 0x1e, &constraints) && results.mpBegin != results.mpEnd) {
            for (uint32_t i = 0; i < (uint32_t)(results.mpEnd - results.mpBegin); ++i) {
                Key3* pKey = &results.mpBegin[i];
                if (GetManager()->Accept(pKey, 0, 0, 0, 0, 0)) {
                    *out = *pKey;
                    return out;
                }
            }
        }
    }
fail:
    out->mInstance = 0;
    out->mType = 0;
    out->mGroup = 0;
    return out;
}

// ---------------------------------------------------------------- editor tool module (0x00EEFF40..)
typedef unsigned int uint;
// The small tool-state object lives at 0x016C7B34; the big editor object at 0x016C7AA4.
#define ED_CAT2(a, b) a##b
#define ED_CAT(a, b) ED_CAT2(a, b)
#define V virtual void ED_CAT(ed_v, __COUNTER__)();
#define V2 V V
#define V3 V2 V
#define V4 V2 V2
#define V8 V4 V4

struct IObj {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};
struct IObj4  { uint pad0; IObj m; };                 // IObj's vptr at +0x04
struct IObj8  { uint pad0[2]; IObj m; };              // +0x08
struct IObj38 { uint pad0[0x38 / 4]; IObj m; };       // +0x38
struct IObj3c { uint pad0[0x3c / 4]; IObj m; };       // +0x3c

struct LocalInputState {
    uint mData[0x48 / 4];                              // 0x20..0x67 of the editor
    void OnMouseDown(uint id, float x, float y, uint flags);   // 0x00697AB0
    void OnMouseUp(uint id, float x, float y, uint flags);     // 0x00697AF0
};
void __fastcall InitLocalInputState(LocalInputState* p);       // 0x00697960

class CEditor {
public:
    const void* volatile mpVtbl0;                      // +0x00
    const void* volatile mpVtbl1;                      // +0x04
    const void* volatile mpVtbl2;                      // +0x08
    uint volatile mField0c;                            // +0x0c
    IObj3c* mpField10;                                 // +0x10
    IObj* mpField14;                                   // +0x14
    IObj* mpField18;                                   // +0x18
    IObj* mpField1c;                                   // +0x1c
    LocalInputState mInput;                            // +0x20
    IObj3c* mpField68;                                 // +0x68
    IObj38* mpField6c;                                 // +0x6c
    IObj* mpField70;                                   // +0x70
    IObj8* mpField74;                                  // +0x74
    IObj4* mpField78;                                  // +0x78
    IObj* mpField7c;                                   // +0x7c
    void* mpServer80;                                  // +0x80
    uint mHandler84;                                   // +0x84
    uint mMsg88;                                       // +0x88
    uint mPrio8c;                                      // +0x8c
    uint mFlags90;                                     // +0x90
    void* mpServer94;                                  // +0x94
    uint mHandler98;                                   // +0x98
    uint mMsg9c;                                       // +0x9c
    uint mPrioA0;                                      // +0xa0
    uint mFlagsA4;                                     // +0xa4
    uint8_t mFlagA8;                                   // +0xa8
    uint mFieldAc;                                     // +0xac
    uint mFieldB0;                                     // +0xb0
    uint mFieldB4;                                     // +0xb4
    uint mFieldB8;                                     // +0xb8
    uint mFieldBc;                                     // +0xbc
    uint mFieldC0;                                     // +0xc0
    int  mFieldC4;                                     // +0xc4
    uint mFieldC8;                                     // +0xc8
    uint mFieldCc;                                     // +0xcc
    uint mFieldD0;                                     // +0xd0
    IObj4* mpFieldD4;                                  // +0xd4
    IObj* mpFieldD8;                                   // +0xd8
    uint8_t mFlagDc;                                   // +0xdc

    CEditor* Construct();                              // 0x00EF02F0
    void Destroy();                                    // 0x00EF0400
    bool OnMouseDown(uint id, float x, float y, uint flags);   // 0x00EF0670
    bool OnMouseUp(uint id, float x, float y, uint flags);     // 0x00EF0730
};

// Touch/contact list owner: separate class from CEditor (its own +0x4c/+0x60 vectors).
struct Entry12 { uint m0, m4, m8; };
struct ItemFlags { uint pad0; uint mFlags; };          // flags at +0x04
struct InputItem {
    V8 V8 V8 V8 V8 V2 V
    virtual ItemFlags* v0xac();                        // +0xac
};
class CUpdater {
public:
    uint8_t pad00[0x4c];
    Entry12* mpBegin;                                  // +0x4c
    Entry12* mpEnd;                                    // +0x50
    uint8_t pad54[0x0c];
    InputItem** mpItems;                               // +0x60
    InputItem** mpItemsEnd;                            // +0x64
    void UpdateTransforms();                           // 0x00EF0220
    bool CheckAll();                                   // 0x00EF02A0
};

class CToolState {
public:
    uint8_t mFlag0;                                    // +0x00
    uint8_t mActive;                                   // +0x01
    uint8_t mRelative;                                 // +0x02
    uint8_t pad03;
    uint pad04;
    float mX;                                          // +0x08
    float mY;                                          // +0x0c
    union { float f; uint u; } mDX;                    // +0x10
    union { float f; uint u; } mDY;                    // +0x14
    __declspec(noinline) void Enable();                // 0x00EEFF40
    __declspec(noinline) void Disable();               // 0x00EEFF80
    void Drag(float x, float y);                       // 0x00EEFFC0
    __declspec(noinline) void Reset();                 // 0x00EF0060
};

struct IWindowManager {
    V
    virtual void* GetActive();                         // +0x04
    V8 V8 V2 V
    virtual void* QueryPanel(int a);                   // +0x54
    virtual void SetPanel(int a, void* v);             // +0x58
    virtual void SetPanel2(int a, void* v);            // +0x5c
};
IWindowManager* WindowManager();                       // 0x0067CAA0

struct C_SomethingCtl {
    void Set40(bool b);                                // 0x008013D0
    void Set(bool b);                                  // 0x00801980
};
C_SomethingCtl* GetSomethingCtl();                     // 0x0067CAB0

struct ObjDD20 {
    V8 V2
    virtual void v28(uint id);                         // +0x28
};
ObjDD20* FUN_0067dd20();                               // 0x0067DD20

struct ObjDD50 {
    V8 V4 V2 V
    virtual void v38();                                // +0x38
};
ObjDD50* FUN_0067dd50();                               // 0x0067DD50

void FUN_00804f10(float x, float y);                   // 0x00804F10

struct IProp {
    uint8_t pad[0x12];
    uint16_t mType;                                    // +0x12
    bool*  GetBool();                                  // 0x0041E920
    float* GetFloat();                                 // 0x0041EA70
};
struct DirectPropertyList {
    V8 V
    virtual bool Get(uint id, IProp** out);            // +0x24
};
extern DirectPropertyList* g_15fd918;                  // 0x015FD918
extern uint8_t g_15acb40;                              // 0x015ACB40
extern uint8_t g_1569ab8;                              // 0x01569AB8
extern float g_1688270;                                // 0x01688270
extern float g_156b5d4;                                // 0x0156B5D4
extern float g_156b5d8;                                // 0x0156B5D8
void FUN_00eed090();                                   // 0x00EED090

struct Obj401010 {
    V4 V2
    virtual bool v18(void* entry);                     // +0x18
    V8 V4
    virtual void v4c(void* entry, const void* data);   // +0x4c
};
Obj401010* FUN_00401010();                             // 0x00401010

struct IInputHost {
    V8 V2
    virtual void v28();                                // +0x28
    V4
    virtual bool v3c();                                // +0x3c
    V4
    virtual void v50(uint id, float x, float y, uint flags);  // +0x50
    virtual bool v54(uint id, float x, float y, uint flags);  // +0x54
};
struct IInputMgr {
    V8 V8 V4 V
    virtual bool v54(uint id, float x, float y, uint flags);  // +0x54
    virtual bool v58(uint id, float x, float y, uint flags);  // +0x58
};
IInputMgr* GameInputManager();                         // 0x00B3D250
extern IInputHost* g_15ad298;                          // 0x015AD298
extern int g_15acc34;                                  // 0x015ACC34
extern CToolState g_16c7b34;                           // 0x016C7B34
extern CEditor* g_16c7aa4;                             // 0x016C7AA4
extern uint g_16c7aa8;                                 // 0x016C7AA8
extern uint g_16c7aac;                                 // 0x016C7AAC

struct RayB;
struct RayA {
    uint pad00[0x60 / 4];
    uint mField60;                                     // +0x60
    uint pad64;
    RayB* mpB;                                         // +0x64
};
struct RayOwner {
    uint pad00[0x17c / 4];
    void* mpField17c;                                  // +0x17c
};
struct RayObj;
struct RayB {
    V3
    virtual RayObj* v0c(uint id);                      // +0x0c
    V4
    virtual void* v20();                               // +0x20
};
struct RayObj {
    uint pad04[(0xb54 - 4) / 4];
    RayOwner* mpOwner;                                 // +0xb54
    uint mFlags;                                       // +0xb58
    V8
    virtual uint v20();                                // +0x20
};
struct RaySource {
    RayA* mpA;                                         // +0x00
    uint pad04;
    float m08, m0c, m10, m14, m18, m1c;
};
struct Vec3 { float x, y, z; };
extern "C" Vec3* normalized_safe(Vec3* pOut, const Vec3* pIn);   // 0x00449C20
bool RayCastParts(const float* org, const float* dir, RayOwner* owner,
                  uint* pIndex, float* pT, float* pHit, float* pNormal, int extra); // 0x009B6450
void RemoveHandler(void* server, uint handler, uint msg, uint prio, uint flags); // 0x00571DB0

// @ 0x00EEFF40
void CToolState::Enable()
{
    if (mFlag0)
        return;
    IWindowManager* wm = WindowManager();
    if (wm->QueryPanel(1) == 0) {
        mFlag0 = 1;
        wm->SetPanel(1, wm->GetActive());
    }
}

// @ 0x00EEFF80
void CToolState::Disable()
{
    if (!mFlag0)
        return;
    IWindowManager* wm = WindowManager();
    void* active = wm->GetActive();
    if (wm->QueryPanel(1) == active)
        wm->SetPanel2(1, active);
    mFlag0 = 0;
}

// @ 0x00EEFFC0
void CToolState::Drag(float x, float y)
{
    if (!mActive)
        return;
    float dx = x - mX;
    float dy = y - mY;
    bool moved = (dx != 0.0f) || (dy != 0.0f);
    if (!mRelative) {
        mDX.f = dx;
        mDY.f = dy;
    } else if (moved) {
        mDX.f = mDX.f + dx;
        mDY.f = mDY.f + dy;
        FUN_00804f10(mX, mY);
        FUN_0067dd50()->v38();
    }
}

// @ 0x00EF0060
void CToolState::Reset()
{
    if (!mActive)
        return;
    if (mRelative)
        GetSomethingCtl()->Set40(true);
    GetSomethingCtl()->Set(false);
    mDX.u = g_16c7aa8;
    mDY.u = g_16c7aac;
    mActive = 0;
}

// @ 0x00EF00B0
void FUN_00ef00b0()
{
    FUN_0067dd20()->v28(0x2ccda9c);
}

// @ 0x00EF00D0
bool FUN_00ef00d0()
{
    return g_15acc34 != 4;
}

// @ 0x00EF0220
void CUpdater::UpdateTransforms()
{
    Obj401010* obj = FUN_00401010();
    Entry12* begin = mpBegin;
    int count = (int)(mpEnd - begin);
    if (count == 0)
        return;
    int off = 0;
    do {
        char* e = (char*)begin + off;
        if (!obj->v18(e)) {
            struct { uint volatile id; uint16_t volatile a; uint16_t volatile b; } data;
            data.a = 0;
            data.b = 1;
            data.id = 0x2ea8fb98;
            obj->v4c(e, &data);
        }
        off += 12;
        --count;
    } while (count != 0);
}

// @ 0x00EF02A0
bool CUpdater::CheckAll()
{
    uint count = (uint)(mpItemsEnd - mpItems);
    for (uint i = 0; i < count; ++i) {
        ItemFlags* p = mpItems[i]->v0xac();
        if (!p)
            return false;
        uint f = p->mFlags;
        uint8_t a = (uint8_t)(f >> 0xe);
        if ((a & 1) == 0)
            return false;
        uint8_t b = (uint8_t)(f >> 0x12);
        if ((b & 1) != 0)
            return false;
    }
    return true;
}

// @ 0x00EF02F0
CEditor* CEditor::Construct()
{
    mpVtbl1 = (const void*)0x13eb394;
    mpVtbl2 = (const void*)0x13ec458;
    mField0c = 0;
    mpVtbl0 = (const void*)0x148b058;
    mpVtbl1 = (const void*)0x148b050;
    mpVtbl2 = (const void*)0x148b040;
    mpField10 = 0;
    mpField14 = 0;
    mpField18 = 0;
    mpField1c = 0;
    InitLocalInputState(&mInput);
    mpField68 = 0;
    mpField6c = 0;
    mpField70 = 0;
    mpField74 = 0;
    mpField78 = 0;
    mpField7c = 0;
    mpServer80 = 0;
    mHandler84 = 0;
    mMsg88 = 0;
    mPrio8c = 0;
    mFlags90 = 0;
    mpServer94 = 0;
    mHandler98 = 0;
    mMsg9c = 0;
    mPrioA0 = 0;
    mFlagsA4 = 0;
    mFlagA8 = 0;
    mFieldAc = 0;
    mFieldB0 = 0;
    mFieldB4 = 0;
    mFieldB8 = 0;
    mFieldBc = 0;
    mFieldC0 = 0;
    mFieldC4 = 2;
    mFieldCc = 0;
    mpFieldD4 = 0;
    mpFieldD8 = 0;
    mFlagDc = 0;
    g_16c7aa4 = this;
    return this;
}

// @ 0x00EF0400
void CEditor::Destroy()
{
    mpVtbl0 = (const void*)0x148b058;
    mpVtbl1 = (const void*)0x148b050;
    mpVtbl2 = (const void*)0x148b040;
    g_16c7aa4 = 0;
    if (mpFieldD8)
        mpFieldD8->v1();
    if (mpFieldD4)
        mpFieldD4->m.v2();
    if (mpServer94) {
        void* s = mpServer94;
        mpServer94 = 0;
        RemoveHandler(s, mHandler98, mMsg9c, mPrioA0, mFlagsA4);
    }
    if (mpServer80) {
        void* s = mpServer80;
        mpServer80 = 0;
        RemoveHandler(s, mHandler84, mMsg88, mPrio8c, mFlags90);
    }
    if (mpField7c)
        mpField7c->v2();
    if (mpField78)
        mpField78->m.v2();
    if (mpField74)
        mpField74->m.v2();
    if (mpField70)
        mpField70->v2();
    if (mpField6c)
        mpField6c->m.v1();
    if (mpField68)
        mpField68->m.v2();
    if (mpField1c)
        mpField1c->v2();
    if (mpField18)
        mpField18->v3();
    if (mpField14)
        mpField14->v2();
    if (mpField10)
        mpField10->m.v2();
    mpVtbl2 = (const void*)0x13ec458;
    mpVtbl1 = (const void*)0x13eb394;
    mpVtbl0 = (const void*)0x13eb938;
}

// @ 0x00EF0570
void FUN_00ef0570()
{
    union { IProp* p; float f; } u;
    if (g_15fd918 && g_15fd918->Get(0x7f2231b, &u.p) && u.p->mType == 1)
        g_15acb40 = *u.p->GetBool();
    g_1569ab8 = (g_15acb40 == 0);
    if (g_15fd918 && g_15fd918->Get(0xe2598dcf, &u.p) && u.p->mType == 0xd)
        g_1688270 = *u.p->GetFloat();
    u.f = 1.0f;
    IProp* prop;
    if (g_15fd918 && g_15fd918->Get(0x5908481, &prop) && prop->mType == 0xd)
        u.f = *prop->GetFloat();
    float cur = g_1688270;
    if (cur != g_156b5d4)
        g_156b5d8 = sqrtf(g_1688270 / g_156b5d4) * u.f;
    return FUN_00eed090();
}

// @ 0x00EF00E0
bool FUN_00ef00e0(RaySource* s)
{
    RayA* a = s->mpA;
    if (!a->mpB)
        return true;
    RayObj* obj = a->mpB->v0c(0x17f243b);
    if (!obj)
        return true;
    if (obj->v20() != 0x18eb45e)
        return true;
    if (a->mField60 == 0x2e72cae)
        return true;
    RayOwner* owner = obj->mpOwner;
    if (!owner)
        return true;
    if (!owner->mpField17c)
        return true;
    if (obj->mFlags & 0x200)
        return false;
    Vec3 origin;
    origin.x = s->m08;
    origin.y = s->m0c;
    origin.z = s->m10;
    Vec3 dir;
    dir.x = s->m14 - s->m08;
    dir.y = s->m18 - s->m0c;
    dir.z = s->m1c - s->m10;
    Vec3 norm;
    normalized_safe(&norm, &dir);
    uint index = 0;
    return RayCastParts(&origin.x, &norm.x, owner, &index, 0, 0, 0, 0);
}

// @ 0x00EF0670
bool CEditor::OnMouseDown(uint id, float x, float y, uint flags)
{
    if (g_15acc34 != 4)
        return 1;
    if (g_15ad298->v3c())
        g_15ad298->v28();
    mInput.OnMouseDown(id, x, y, flags);
    g_15ad298->v50(id, x, y, flags);
    bool r = GameInputManager()->v54(id, x, y, flags);
    if (flags & 0x38)
        g_16c7b34.Enable();
    return r;
}

// @ 0x00EF0730
bool CEditor::OnMouseUp(uint id, float x, float y, uint flags)
{
    if (g_15acc34 != 4)
        return 1;
    mInput.OnMouseUp(id, x, y, flags);
    g_15ad298->v54(id, x, y, flags);
    bool r = GameInputManager()->v58(id, x, y, flags);
    if ((flags & 0x38) == 0) {
        g_16c7b34.Disable();
        g_16c7b34.Reset();
    }
    return r;
}
