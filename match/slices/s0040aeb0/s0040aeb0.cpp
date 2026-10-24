// Slice s0040aeb0: one very large unoptimized (/Od /Ob1) editor member function.
//
// It processes the editor's current part-list entry (index at +0x10f4): resolves the part's
// model resource, composes the rig/ability transforms, builds the ability's key list, appends
// per-part bookkeeping (ability vector, transform vector, enabled byte, baked-animation block,
// material/ability map entries) and, in editor mode, walks the model's material streams to
// create ShaderState/ability objects for every material.  It finally restores the model
// transform and advances the index.
//
// The original expands a great many inline EASTL / resource helpers (vector growth, smart
// pointer copies, hash-map nodes) whose exact original spelling is not recovered.  This is a
// COMPLETE behaviour-oriented port: every branch and every callee of the original appears, but
// it is not byte-exact (see nonmatching.txt).  Built like its neighbours:
//   /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast   (no /EHsc)
#include "types.h"
#include <intrin.h>

// ===========================================================================
// Small math / resource types (layouts from the surrounding /Od editor slices)
// ===========================================================================
struct Vector3 { float x, y, z; };
struct Matrix3 { float m[9]; };

struct Modifier {
    uint16_t flags;      // +0x00
    uint16_t count;      // +0x02
    Vector3  pos;        // +0x04
    float    scale;      // +0x10
    Matrix3  rot;        // +0x14
    // 0x38 bytes total

    void AssignCopy(const Modifier& o);   // 0x0040ce80  (copy constructor)
    void Accumulate(const Modifier& o);   // 0x0040ccb0  (pos/rot/scale accumulate)
    void AccumulateScaled(const Modifier& o); // 0x0040cd80
    void PreRotateY(float angle);         // 0x006baa70
    void AssignFrom(const Modifier& o);   // 0x00537dc0  (cSPTransform::operator=)
};

// ===========================================================================
// Property system
// ===========================================================================
class Property {
public:
    bool*  GetBool();         // 0x0041e920
    int*   GetUIntValue();    // 0x0041ea00 (PDB: GetUInt)
    float* GetFloat();        // 0x0041ea70

    uint16_t pad[9];          // +0x00
    uint16_t mnType;          // +0x12  (1 = bool, 0xa = int, 0xd = float)
};

class PropertyList {
public:
    virtual int  AddRef();                                    // +0x00
    virtual int  Release();                                   // +0x04
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);  // +0x24
};

// ===========================================================================
// Ref-counted holders / vectors
// ===========================================================================
extern const char kEditorAllocName[];   // 0x013eb430
extern const float kPartYaw;            // 0x015d1318

// EA's six-argument operator new used by the editor.
void* __cdecl FUN_00f473a0(int size, const char* tag, int a, int b, int c, int d);

struct EditorRefSlot {               // { object pointer, released via its vtable or 0x453540 }
    void* mpObject;                  // +0x00
    void* GetRaw();                  // 0x0041d900
    void* GetParam();                // 0x0041d870
    void  Release();                 // 0x00453540
};

struct AutoRefPair {                 // { int id; void* object; } used by 0x0041cc20
    int   mId;
    void* mpObject;
};

// A vector of ref-counted pointers (eastl::vector with sp_vector_allocator, 0x14 bytes).
struct RefVector {
    void*  mpBegin;                  // +0x00
    void*  mpEnd;                    // +0x04
    void*  mpCapacity;               // +0x08
    void*  mAllocator;               // +0x0c

    void  Construct(const void* tag);          // 0x00540470  (VSet ctor)
    bool  empty() const;                       // 0x00526430
    void  erase(void* first, void* last);      // 0x00426280
    void  resize(int n);                       // 0x0041ee90
    void  push_back(void* const& value);       // 0x0041ef20
    int   size() const { return ((char*)mpEnd - (char*)mpBegin) >> 2; }
    void* at(int i) const { return ((void**)mpBegin)[i]; }
};

struct ByteVector {
    uint8_t* mpBegin; uint8_t* mpEnd; uint8_t* mpCapacity; void* mAllocator;
    void push_back(const uint8_t& value);      // 0x00421080
};

struct ModifierVector {
    Modifier* mpBegin; Modifier* mpEnd; Modifier* mpCapacity; void* mAllocator;
    void push_back(const Modifier& value);     // 0x0041e460
};

struct Item7cVector {                          // baked-animation block, 0x7c bytes each
    void* mpBegin; void* mpEnd; void* mpCapacity; void* mAllocator;
    void push_back(const void* value);         // 0x0041f650
    int  size() const { return ((char*)mpEnd - (char*)mpBegin) / 0x7c; }
};

struct TripleVector {                          // three-float elements
    void* mpBegin; void* mpEnd; void* mpCapacity; void* mAllocator;
    void push_back(const Vector3& value);      // 0x004206f0
    int   size() const { return ((char*)mpEnd - (char*)mpBegin) / 0xc; }
};

struct IntVector {
    int* mpBegin; int* mpEnd; int* mpCapacity; void* mAllocator;
    void push_back(const int& value);          // 0x00422380
    int  size() const { return mpEnd - mpBegin; }
};

struct PartAbilitySlot;                        // forward (ability object built per material)

struct Item24 {                                // element of the +0x3c8 vector
    RefVector mKeys;                           // +0x00
    uint32_t  mExtra;                          // +0x14
    void Destroy();                            // 0x00421190
};

struct Item24Vector {
    Item24* mpBegin; Item24* mpEnd; Item24* mpCapacity; void* mAllocator;
    void push_back(const Item24& value);       // 0x004215f0
};

struct IntMap {                                // eastl hash map, 0x18 bytes
    int* mpBuckets;                            // +0x00
    int* mpEndNode;                            // +0x04
    int  mBucketCount;                         // +0x08
    int  mPad0c;
    int  mPad10;
    int  mPad14;

    int* operator[](int* key);                 // 0x004210f0
};

struct AbilityMap {                            // map<PartAbilitySlot*, int> at +0x10d4
    int* mpBuckets; int* mpEndNode; int mBucketCount; int mPad0c; int mPad10; int mPad14;
    void Find(int** out, PartAbilitySlot** value);        // 0x00420b50
    int* operator[](PartAbilitySlot** key);               // 0x0041d1f0
};

struct PairIter { int* mpNode; int* mpEnd; };

struct PairMap {                               // intrusive node map used for materials
    int  mPad00;
    int* mpEndNode;                            // +0x04
    void Find(PairIter* out, int key);         // 0x00426d90
};

struct PartKeyVec {
    void* mpBegin; void* mpEnd; void* mpCapacity; void* mAllocator;
    void Init(int count);                      // 0x0041d0c0
    void Done();                               // 0x004209b0
};

struct TransformVec2 {                         // 0x30-byte transform array (0x41d510)
    void* mpBegin; void* mpEnd; void* mpCapacity; void* mAllocator;
    void Init(int count);                      // 0x0041d510
    void Done();                               // 0x004222a0
};

// ===========================================================================
// Model / part / editor-side objects
// ===========================================================================
class MaterialManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual void* GetMaterial(int key);        // +0x28
};

struct EmbeddedState {
    uint32_t mPad00;
    uint32_t mPad04;
    uint32_t mFlags;                           // +0x08
    int D3D9GetShaderData(int which);          // 0x011edcf0
};

struct Material {
    uint32_t mPad00;
    EmbeddedState* mpState;                    // +0x04
};

struct StreamInfo {                            // copied by 0x401b80 (0x10 bytes)
    uint32_t mCount;                           // +0x00
    int*     mpBase;                           // +0x04
    uint16_t mStride0;                         // +0x08
    uint16_t mStride;                          // +0x0a
    void*    mpRef;                            // +0x0c

    void Init(const void* src);                // 0x00401b80
    int* Slot(int i) const { return (int*)((char*)mpBase + (uint32_t)mStride * i); }
};

struct TagEntry {
    uint32_t mPad00;
    uint32_t mPad04;
    void*    mpData;                           // +0x08
};

struct TagObject {
    uint32_t   mPad00;
    uint32_t   mPad04;
    TagEntry** mEntries;                       // +0x08
    int  FindTag(int tag);                     // 0x0077cad0
};

// The 0x1c-byte per-material ability object.
struct PartAbilitySlot {
    uint32_t  mPad00;                          // +0x00 (vptr)
    uint32_t  mPad04;                          // +0x04
    RefVector mAbilities;                      // +0x08
    void Ctor();                               // 0x0077d1d0
    void Push(int value);                      // 0x0077d970
};

// The 0x58-byte standalone ability list built when a part has no keys.
struct ListAbility {
    uint32_t  mPad00;                          // +0x00 (vptr)
    uint32_t  mRefCount;                       // +0x04
    void Ctor();                               // 0x0040d160
};

struct SlotAbility {                           // 0x70-byte shader/ability wrapper
    uint32_t mPad[0x1c];
    void Ctor();                               // 0x0040d010
    void SetResource(int a, void* b);          // 0x0077cb10
    void SetSlot0(int a, int b);               // 0x00777a60
    void SetSlot1(int a, int b);               // 0x00777a80
};

class ResourceManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void* Create(uint32_t a, uint32_t b, uint32_t c, int flag); // +0x1c
};

struct ResourceKey {                           // 12-byte rw resource key
    uint32_t mName;                            // +0x00
    uint32_t mType;                            // +0x04
    uint32_t mFlags;                           // +0x08
};

struct RefCounted {
    void Release();                            // 0x00402420
};

// Creature-ability object (vtable 0x013ef094); its constructors live in slice s0040ccb0.
struct CreatureAbility {
    uint32_t mPad00;
    uint16_t mId;                              // +0x04
    uint16_t mValue;                           // +0x06
    void*    mpData;                           // +0x08
    void Ctor(uint16_t id, uint16_t value, void* data);  // 0x0040cfd0
};

struct Ability20 : CreatureAbility {           // 0x20-byte ability built for a stream entry
    uint32_t mField0c, mField10, mField14, mField18, mField1c;
};

struct AbilityData {                           // 0x2c-byte ability-data block
    void Ctor(const void* twoEntries);         // 0x0041d490
};

struct ColorKey {                              // 0x14-byte default colour key
    uint8_t type, r, g, b;
    float   a, b2, c, d;
    void Ctor();                               // 0x0040cf60
};

void  __cdecl VectorCtorIterator(void* dst, int elems, int count, void* ctor); // 0x00401930

// ===========================================================================
// Creatures / simulation helpers
// ===========================================================================
struct PartModel;
struct EditorPart;

class PartManager {
public:
    virtual void v0(); virtual void v1();
    virtual int  GetPartCount(PartModel* model);                        // +0x84
    virtual void GetData3(PartModel* model, int* out, int index);       // +0x88
    virtual void GetData2(PartModel* model, int* out);                  // +0x8c
    virtual void GetPartKeys(PartModel* model, int* out);               // +0x90
    virtual void* CreateInstance(PartModel* model, int arg);            // +0xa8
    virtual void GetKeys(PartModel* model, RefVector* keys, Modifier* xf); // +0xf0
    virtual bool BuildKeys(PartModel* model, RefVector* keys, void* a, void* b,
                           Modifier* xf);                               // +0x100
    virtual Modifier* GetKeyType(PartModel* model);                     // +0x108
};

// ===========================================================================
// Editor layout (field offsets from the disassembly)
// ===========================================================================
struct EditorPart {
    uint32_t    mPad00[4];
    PartModel*  mpModel;                       // +0x10
    uint32_t    mPad14;
    PartManager* mpManager;                    // +0x18
    uint8_t     mPad1c[0x1d8 - 0x1c];
    float       mScale;                        // +0x1d8
    uint8_t     mPad1dc[0x3e0 - 0x1dc];
    int         mField3e0;                     // +0x3e0
    uint8_t     mPad3e4[0xdc8 - 0x3e4];
    uint32_t    mFlagsBits;                    // +0xdc8
    uint32_t    mFlagsDcc;                     // +0xdcc

    bool GetResourceKey(uint32_t* out);        // 0x0043bf20 (this = part)
};

struct PartModel {
    uint32_t   mPad00[2];
    Modifier   mTransform;                     // +0x08  (0x38 bytes)
    uint8_t    mPad40[0x90 - 0x40];
    PropertyList* mpProperties;                // +0x90
};

struct Editor;

struct EditorArg {
    void Finish(Editor* self);                 // 0x00422280
};

struct Editor {
    uint32_t   mPad000[0x238 / 4];
    uint16_t   mFlags238;                      // +0x238
    uint8_t    mPad23a[0x338 - 0x23a];
    RefVector  mAbilities;                     // +0x338  (index -> ability pointer)
    RefVector  mPartKeys;                      // +0x34c
    ByteVector mEnabledFlags;                  // +0x360
    ModifierVector mComposedXforms;            // +0x374
    Item7cVector mBakedAnims;                  // +0x388
    RefVector  mInstances;                     // +0x39c  (model instances)
    IntMap     mAbilityIndexMap;               // +0x3b0
    Item24Vector mEntries;                     // +0x3c8
    IntVector  mEntryIndices;                  // +0x3dc
    uint8_t    mPad3f0[0x438 - 0x3f0];
    TripleVector mVarA;                        // +0x438
    uint8_t    mPad44c[0x510 - 0x44c];
    ModifierVector mVarB;                      // +0x510
    uint8_t    mPad524[0x8a8 - 0x524];
    ModifierVector mVarC;                      // +0x8a8
    uint8_t    mPad8bc[0x980 - 0x8bc];
    TripleVector mVarD;                        // +0x980
    uint8_t    mPad994[0xd18 - 0x994];
    IntVector  mVarE;                          // +0xd18
    uint8_t    mPadd2c[0xd70 - 0xd2c];
    int        mThreshold;                     // +0xd70
    float      mScaleLimit;                    // +0xd74
    float      mScaleUsed;                     // +0xd78
    uint8_t    mPadd7c[0xd84 - 0xd7c];
    int        mTotalCost;                     // +0xd84
    int        mFirstFlag;                     // +0xd88
    RefVector  mParts;                         // +0xd8c
    uint8_t    mPadd9c[0x10d4 - 0xd9c];
    AbilityMap mSlotIndexMap;                  // +0x10d4
    uint8_t    mPad10ec[0x10f4 - 0x10ec];
    uint32_t   mCurIndex;                      // +0x10f4
    int        mCounterA;                      // +0x10f8
    int        mCounterB;                      // +0x10fc

    void ProcessCurrentPart(void* arg);
    void ProcessSkipped(void* arg);             // 0x0040d2d0
};

// ===========================================================================
// Free callees (calling conventions from each call site)
// ===========================================================================
int   __cdecl FUN_0071dd80(int key, int flag);                       // 0x0071dd80
void  __cdecl FUN_007387f0(int key);                                 // 0x007387f0
bool  __cdecl FUN_00756860(void* entry, PartManager* mgr, PartModel* model, void* instance);
                                                                      // 0x00756860
void  __cdecl FUN_00401990(void* ability);                            // 0x00401990
int   __cdecl FUN_0071ddc0(void* ability, int a, int b, int c, int d); // 0x0071ddc0
void* __cdecl FUN_0067dd70();                                         // 0x0067dd70 (MaterialManager)
int   __cdecl FUN_00932e80(const char* name, uint32_t seed, int flag);  // 0x00932e80 (FNVHash)
int   __cdecl FUN_0077d710(int tagEntry);                             // 0x0077d710
ResourceManager* __cdecl FUN_0067dd60();                              // 0x0067dd60
void  __cdecl FUN_006c1ae0(void* baker, void* param);                 // 0x006c1ae0
void  __cdecl FUN_00409930(void* p);                                  // 0x00409930
void  __cdecl FUN_00472540(void* p);                                  // 0x00472540
void  __cdecl FUN_004a9b10(void* p);                                  // 0x004a9b10
void  __cdecl FUN_0041cc20(void* p, void* value);                     // 0x0041cc20
void  __cdecl FUN_0041ccc0(void* p, void* value);                     // 0x0041ccc0
bool  __cdecl FUN_006a0ae0(PropertyList* props, uint32_t id, int* count, void** base);
                                                                      // 0x006a0ae0
bool  __cdecl FUN_006a0c30(PropertyList* props, uint32_t id, int* count, void** base);
                                                                      // 0x006a0c30
bool  __cdecl FUN_006a1250(PropertyList* props, uint32_t id, float* out); // 0x006a1250
bool  __cdecl FUN_0040cf10(PropertyList* props, uint32_t id, float* out); // 0x0040cf10
void  __cdecl FUN_0041eb80(void* p);                                  // 0x0041eb80
void  __cdecl FUN_00732270(void* src, void* out);                     // 0x00732270
Modifier* __cdecl FUN_0043d220(EditorPart* part);                     // 0x0043d220

// ===========================================================================
// @ 0x0040aeb0
// ===========================================================================
void Editor::ProcessCurrentPart(void* arg)
{
    if (mCurIndex >= (uint32_t)mParts.size()) {
        ProcessSkipped(arg);
        return;
    }

    const bool editorMode = (mFlags238 & 0x100) != 0;

    EditorPart* part = (EditorPart*)mParts.at((int)mCurIndex);
    PartModel*  model = part->mpModel;
    PartManager* mgr  = part->mpManager;

    // ------------------------------------------------------------------
    // "disabled" property (bool, id 0x065fc9ab) on the part's model
    // ------------------------------------------------------------------
    bool enabled = true;
    PropertyList* props = model->mpProperties;
    if (props != 0) {
        Property* prop = 0;
        Property* check = 0;
        if (props != 0 && props->GetProperty(0x065fc9ab, check) && check->mnType == 1) {
            prop = check;
        }
        if (prop != 0) {
            enabled = !*prop->GetBool();
        }
    }

    // ------------------------------------------------------------------
    // save the model transform, rotate it for this placement, instantiate
    // ------------------------------------------------------------------
    Modifier savedXf;
    savedXf.AssignCopy(model->mTransform);
    model->mTransform.PreRotateY(kPartYaw);

    void* instance = mgr->CreateInstance(model, -1);

    RefVector keys;
    keys.Construct(&savedXf);                    // tag argument is a dummy local in the original
    EditorRefSlot baker;                         // [ebp-0x60]: filled by BuildKeys (animation baker)
    baker.mpObject = 0;
    EditorRefSlot other;                         // [ebp-0xb0]: filled by BuildKeys
    other.mpObject = 0;

    Modifier composedXf;
    composedXf.AssignCopy(model->mTransform);
    composedXf.Accumulate(*mgr->GetKeyType(model));   // ComposeTransforms(key)

    Modifier keyXf;
    keyXf.AssignCopy(composedXf);

    void* bakerSlot = baker.GetParam();          // 0x0041d870: release, return &mpObject
    void* otherSlot = other.GetRaw();            // 0x0041d900: release, return &mpObject

    bool built = mgr->BuildKeys(model, &keys, bakerSlot, otherSlot, &keyXf);
    if (!built) {
        mgr->GetKeys(model, &keys, &keyXf);
        for (int i = 0; i < keys.size(); i++) {
            FUN_007387f0((int)keys.at(i));
        }
    }
    else {
        int cost = 0;
        if (!keys.empty()) {
            cost = FUN_0071dd80((int)keys.at(0), 5);
        }
        if (mTotalCost + cost <= 0x40) {
            if (mCurIndex == 0) {
                mFirstFlag = 1;
            }
            mTotalCost += cost;
        }
        else {
            if (baker.mpObject != 0) {
                void** vt = *(void***)baker.mpObject;
                ((void (__thiscall*)(void*))vt[1])(baker.mpObject);   // Release
                baker.mpObject = 0;
            }
            if (other.mpObject != 0) {
                other.Release();                 // 0x00453540
                other.mpObject = 0;
            }
            keys.erase(keys.mpBegin, keys.mpEnd);
            mgr->GetKeys(model, &keys, &keyXf);
            for (int i = 0; i < keys.size(); i++) {
                FUN_007387f0((int)keys.at(i));
            }
        }
    }

    // ------------------------------------------------------------------
    // a part always carries at least one ability: an empty key list gets a
    // fresh ListAbility, a non-empty one is truncated to its first entry
    // ------------------------------------------------------------------
    if (keys.empty()) {
        ListAbility* listAbility = (ListAbility*)FUN_00f473a0(
            0x58, kEditorAllocName, 0, 0, 0, 0);
        if (listAbility != 0) {
            listAbility->Ctor();                 // 0x0040d160 ListAbility ctor
            _InterlockedIncrement((volatile long*)&listAbility->mRefCount);
        }
        keys.push_back(listAbility);
        if (listAbility != 0) {
            ((void (__thiscall*)(void*))0x00404f90)(listAbility);  // drop temp ref
        }
    }
    else {
        if (keys.size() > 1) {
            keys.resize(1);
        }
    }
    keys.resize(1);

    void* ability = keys.at(0);
    mInstances.push_back(instance);
    int instanceIndex = mInstances.size() - 1;
    mAbilities.push_back(ability);
    mComposedXforms.push_back(keyXf);
    mEnabledFlags.push_back(*(const uint8_t*)&enabled);

    // ------------------------------------------------------------------
    // baked-animation block (+0x388): either the animations published by the
    // baker object, or an empty transform pair
    // ------------------------------------------------------------------
    if (baker.mpObject != 0 && FUN_0071dd80((int)ability, 5) > 0) {
        void* b = baker.mpObject;
        void** vt = *(void***)b;
        ((void (__thiscall*)(void*))vt[0])(b);                   // AddRef
        FUN_006c1ae0(b, baker.GetParam());                       // GetBakedAnimations
        baker.mpObject = 0;

        uint8_t block[0x7c];
        FUN_00409930(block);                                     // Transform ctor
        *(Modifier*)(block + 0x38) = keyXf;                      // copy ctor in the original
        AutoRefPair refA;                                        // [ebp-0x106c] { -1, baker }
        refA.mId = -1;
        refA.mpObject = 0;
        FUN_0041cc20(&refA, b);                                  // 0x0041cc20 ctor
        EditorRefSlot refB;
        refB.mpObject = 0;
        FUN_0041ccc0(&refB, other.mpObject);                     // 0x0041ccc0 init
        mBakedAnims.push_back(block);
        FUN_00472540(&refB);                                     // ~EditorRefSlot
        FUN_004a9b10(&refA);                                     // ~AutoRefCount

        vt = *(void***)b;
        ((void (__thiscall*)(void*))vt[1])(b);                   // Release
    }
    else {
        uint8_t block[0x7c];
        FUN_00409930(block);                                     // Transform ctor
        FUN_00409930(block + 0x38);                              // second Transform ctor
        AutoRefPair refA;
        refA.mId = 0;
        refA.mpObject = 0;
        EditorRefSlot refB;
        refB.mpObject = 0;
        mBakedAnims.push_back(block);
        FUN_00472540(&refB);
        FUN_004a9b10(&refA);
    }

    // ------------------------------------------------------------------
    // ability-index bookkeeping
    // ------------------------------------------------------------------
    int abilitySlot = mAbilities.size() - 1;
    *mAbilityIndexMap[&abilitySlot] = instanceIndex;

    Item24 entry;
    entry.mKeys.Construct(&savedXf);
    entry.mExtra = 0;
    mEntries.push_back(entry);
    entry.Destroy();

    Item24* lastEntry = (Item24*)((char*)mEntries.mpEnd - 0x18);
    FUN_00756860(lastEntry, mgr, model, instance);

    // ------------------------------------------------------------------
    // editor mode: material streams -> per-material ability/shader objects
    // ------------------------------------------------------------------
    if (editorMode) {
        FUN_00401990(ability);

        int streamIdxA = FUN_0071ddc0(ability, 0x14, 0, 6, 8);
        int streamIdxB = FUN_0071ddc0(ability, 0x15, 0, 6, 8);
        if (streamIdxA >= 0 && streamIdxB >= 0) {
            StreamInfo streamA;
            StreamInfo streamB;
            streamA.Init((char*)ability + 8 + streamIdxA * 0x20 + 0x10);
            streamB.Init((char*)ability + 8 + streamIdxB * 0x20 + 0x10);

            MaterialManager* materialMgr = (MaterialManager*)FUN_0067dd70();
            PairMap* pairMap = (PairMap*)((char*)mEntries.mpEnd - 0x18);

            for (int i = 0; i < (int)streamA.mCount; i++) {
                Material* material = (Material*)materialMgr->GetMaterial(*streamB.Slot(i));
                EmbeddedState* state = material->mpState;
                int shader244 = 0;
                if (state != 0 && (state->mFlags & 8) != 0) {
                    shader244 = state->D3D9GetShaderData(0x244);
                }
                state = material->mpState;
                int shader217 = 0;
                if (state != 0 && (state->mFlags & 8) != 0) {
                    shader217 = state->D3D9GetShaderData(0x217);
                }

                PairIter found;
                pairMap->Find(&found, *streamA.Slot(i));
                int* node = found.mpNode;
                if (node == found.mpEnd) {
                    node = pairMap->mpEndNode;
                }
                TagObject* tagObj = 0;
                if (node != pairMap->mpEndNode) {
                    tagObj = (TagObject*)node[1];
                }

                PartAbilitySlot* slot = (PartAbilitySlot*)FUN_00f473a0(
                    0x1c, kEditorAllocName, 0, 0, 0, 0);
                if (slot != 0) {
                    slot->Ctor();                  // 0x0077d1d0
                    _InterlockedIncrement((volatile long*)&slot->mPad04);
                }

                int idx212 = tagObj != 0 ? tagObj->FindTag(0x212) : -1;
                TagEntry* entry212 = (idx212 >= 0) ? tagObj->mEntries[idx212] : 0;
                void* data212 = entry212 != 0 ? entry212->mpData : 0;

                int idx213 = tagObj != 0 ? tagObj->FindTag(0x213) : -1;
                TagEntry* entry213 = (idx213 >= 0) ? tagObj->mEntries[idx213] : 0;
                void* data213 = entry213 != 0 ? entry213->mpData : 0;

                int idx20d = tagObj != 0 ? tagObj->FindTag(0x20d) : -1;

                if (data212 == 0) {
                    if (data213 != 0) {
                        ColorKey color;
                        color.Ctor();                // 0x0040cf60
                        Ability20* a = (Ability20*)FUN_00f473a0(
                            0x20, kEditorAllocName, 0, 0, 0, 0);
                        if (a != 0) {
                            a->Ctor(0x210, 0x14, 0);
                            a->mField0c = 2;
                            a->mField10 = *(uint32_t*)((char*)data213 + 0x20);
                            a->mField14 = *(uint32_t*)((char*)data213 + 0x24);
                            a->mField18 = *(uint32_t*)((char*)data213 + 0x28);
                            a->mField1c = *(uint32_t*)((char*)data213 + 0x2c);
                            slot->Push((int)a);
                        }
                        uint32_t twoEntries[8];
                        VectorCtorIterator(twoEntries, 0x10, 2, (void*)0x00402ab0);
                        for (int k = 0; k < 8; k++) {
                            twoEntries[k] = *(uint32_t*)((char*)data213 + k * 4);
                        }
                        AbilityData* data = (AbilityData*)FUN_00f473a0(
                            0x2c, kEditorAllocName, 0, 0, 0, 0);
                        if (data != 0) {
                            data->Ctor(twoEntries);  // 0x0041d490
                            slot->Push((int)data);
                        }
                    }
                }
                else {
                    ColorKey color;
                    color.Ctor();                    // 0x0040cf60
                    Ability20* a = (Ability20*)FUN_00f473a0(
                        0x20, kEditorAllocName, 0, 0, 0, 0);
                    if (a != 0) {
                        a->Ctor(0x210, 0x14, 0);
                        a->mField0c = 2;
                        a->mField10 = *(uint32_t*)((char*)data212 + 0x1c);
                        a->mField14 = *(uint32_t*)((char*)data212 + 0x0c);
                        a->mField18 = 0x3f800000;
                        a->mField1c = 0x3e99999a;
                        slot->Push((int)a);
                    }
                    uint32_t twoEntries[8];
                    VectorCtorIterator(twoEntries, 0x10, 2, (void*)0x00402ab0);
                    twoEntries[0] = *(uint32_t*)((char*)data212 + 0x00);
                    twoEntries[1] = *(uint32_t*)((char*)data212 + 0x04);
                    twoEntries[2] = *(uint32_t*)((char*)data212 + 0x08);
                    twoEntries[3] = 0x3f800000;
                    twoEntries[4] = *(uint32_t*)((char*)data212 + 0x10);
                    twoEntries[5] = *(uint32_t*)((char*)data212 + 0x14);
                    twoEntries[6] = *(uint32_t*)((char*)data212 + 0x18);
                    twoEntries[7] = 0x3f800000;
                    AbilityData* data = (AbilityData*)FUN_00f473a0(
                        0x2c, kEditorAllocName, 0, 0, 0, 0);
                    if (data != 0) {
                        data->Ctor(twoEntries);      // 0x0041d490
                        slot->Push((int)data);
                    }
                }

                // shader/state selection
                if (shader244 == 0) {
                    if (shader217 == 0) {
                        if (idx20d >= 0) {
                            int* tagged = (int*)((char*)tagObj->mEntries + idx20d * 4);
                            slot->Push(FUN_0077d710(*tagged));  // 0x0077d710
                        }
                    }
                    else {
                        ResourceKey key;
                        key.mName = 0;
                        if (!part->GetResourceKey(&key.mName)) {   // 0x0043bf20
                            key.mName = 0xffffffff;
                        }
                        key.mType  = 0x2f4e681c;
                        key.mFlags = 0x40602100;

                        ResourceManager* resMgr = FUN_0067dd60();
                        RefCounted* res = (RefCounted*)resMgr->Create(
                            key.mName, key.mType, key.mFlags, 2);
                        if (res != 0) {
                            _InterlockedIncrement((volatile long*)((char*)res + 8));
                        }
                        bool have = (res != 0) &&
                                    (((*(uint8_t*)((char*)res + 4)) & 4) == 0);
                        if (!have) {
                            key.mName = FUN_00932e80("black", 0x811c9dc5, 1);
                            resMgr = FUN_0067dd60();
                            RefCounted* other = (RefCounted*)resMgr->Create(
                                key.mName, key.mType, key.mFlags, 0);
                            if (other != res) {
                                RefCounted* old = res;
                                if (other != 0) {
                                    _InterlockedIncrement((volatile long*)((char*)other + 8));
                                }
                                res = other;
                                if (old != 0) {
                                    old->Release();
                                }
                            }
                        }
                        if (res != 0) {
                            SlotAbility* sa = (SlotAbility*)FUN_00f473a0(
                                0x70, kEditorAllocName, 0, 0, 0, 0);
                            if (sa != 0) {
                                sa->Ctor();               // 0x0040d010
                                sa->SetResource(0, res);  // 0x0077cb10
                                sa->SetSlot0(0, 1);       // 0x00777a60
                                sa->SetSlot1(0, 2);       // 0x00777a80
                                slot->Push((int)sa);
                            }
                        }
                        if (res != 0) {
                            res->Release();               // 0x00402420
                        }
                    }
                }

                // publish the ability index into the stream slot, or -1
                if (!slot->mAbilities.empty()) {
                    mCounterA++;
                    int* foundNode = 0;
                    mSlotIndexMap.Find(&foundNode, &slot);
                    int* endNode = (int*)((char*)mSlotIndexMap.mpEndNode
                                          + mSlotIndexMap.mBucketCount * 4);
                    if (foundNode[0] == *endNode) {
                        int newIndex = mEntryIndices.size();
                        mEntryIndices.push_back(newIndex);
                        *mSlotIndexMap[&slot] = newIndex;
                        *streamA.Slot(i) = newIndex;
                        mCounterB++;
                    }
                    else {
                        *streamA.Slot(i) = foundNode[1];
                    }
                }
                else {
                    *streamA.Slot(i) = -1;
                }

                if (slot != 0) {
                    ((void (__thiscall*)(void*))0x00404f90)(slot);
                }
            }

            if (streamA.mpRef != 0) {
                ((void (__thiscall*)(void*))((void**)streamA.mpRef)[1])(streamA.mpRef);
            }
            if (streamB.mpRef != 0) {
                ((void (__thiscall*)(void*))((void**)streamB.mpRef)[1])(streamB.mpRef);
            }
        }
    }

    // ------------------------------------------------------------------
    // per-part property tables
    // ------------------------------------------------------------------
    props = model->mpProperties;
    if (props != 0) {
        int count = 0;
        void* base = 0;
        if (FUN_006a0ae0(props, 0x32f4549, &count, &base)) {
            uint32_t bits = part->mFlagsDcc;
            if ((bits & 0x80) != 0) {
                Modifier* partXf = FUN_0043d220(part);
                Modifier tmp;
                tmp.AssignCopy(model->mTransform);
                tmp.Accumulate(*partXf);
                Modifier out;
                out.AssignCopy(tmp);
                for (int i = 0; i < count; i++) {
                    mVarA.push_back(*(Vector3*)((char*)base + i * 0xc));
                    mVarB.push_back(out);
                }
            }
            else {
                int have = 0;
                void* table = 0;
                FUN_006a0c30(props, 0x2a907b6, &have, &table);
                for (int i = 0; i < count; i++) {
                    mVarA.push_back(*(Vector3*)((char*)base + i * 0xc));
                    if (i < have) {
                        Modifier tmp;
                        tmp.AssignCopy(model->mTransform);
                        tmp.Accumulate(*(Modifier*)((char*)table + i * 0x38));
                        mVarB.push_back(tmp);
                    }
                    else {
                        mVarB.push_back(model->mTransform);
                    }
                }
            }
        }

        float keyPos[3] = { 0.0f, 0.0f, 0.0f };
        if (FUN_006a1250(props, 0xf1fae962, keyPos)) {
            const int kPartTag = (int)0xc045a9a3;
            int partCount = mgr->GetPartCount(model);        // vtable +0x84
            PartKeyVec keyVec;
            keyVec.Init(partCount);                          // 0x0041d0c0
            int* partKeys = (int*)keyVec.mpBegin;
            mgr->GetPartKeys(model, partKeys);               // vtable +0x90

            Modifier partXf;                                 // [ebp-0x3b4]
            FUN_00409930(&partXf);
            for (int i = 0; i < partCount; i++) {
                if (partKeys[i] != kPartTag) {
                    continue;
                }
                Modifier secondXf;                           // [ebp-0x1048]
                FUN_00409930(&secondXf);
                TransformVec2 tvec;
                tvec.Init(partCount);                        // 0x0041d510
                void* keyData = tvec.mpBegin;
                mgr->GetData2(model, (int*)keyData);         // vtable +0x8c
                FUN_00732270((char*)keyData + i * 0x30, &partXf);
                mgr->GetData3(model, (int*)keyData, 0);      // vtable +0x88
                FUN_00732270((char*)keyData + i * 0x30, &secondXf);
                partXf.Accumulate(secondXf);                 // 0x0040ccb0
                partXf.AccumulateScaled(*mgr->GetKeyType(model)); // 0x0040cd80
                tvec.Done();                                 // 0x004222a0
                break;
            }

            int newIndex = -1;
            if (!keys.empty()) {
                newIndex = mBakedAnims.size() - 1;
            }
            Modifier tmp;
            tmp.AssignCopy(model->mTransform);
            tmp.Accumulate(partXf);
            Modifier out;
            out.AssignCopy(tmp);
            mVarD.push_back(*(Vector3*)keyPos);
            mVarB.push_back(out);
            mVarE.push_back(newIndex);
            if (part->mField3e0 == 0) {
                mVarD.push_back(*(Vector3*)keyPos);
                mVarB.push_back(out);
                mVarE.push_back(newIndex);
            }
            keyVec.Done();                                   // 0x004209b0
        }

        float thresholdValue = 0.0f;
        int haveInt = 0;
        Property* p = 0;
        if (props != 0 && props->GetProperty(0x46d0560, p) && p->mnType == 0xa) {
            thresholdValue = (float)*p->GetUIntValue();
            haveInt = 1;
        }
        float scaled = 0.0f;
        if (haveInt && FUN_0040cf10(props, 0x46d0572, &scaled)) {
            float s = scaled * part->mScale;
            if (mScaleLimit <= s && s != mScaleLimit) {
                mThreshold = (int)thresholdValue;
                mScaleUsed = part->mScale;
            }
        }
    }

    model->mTransform.AssignFrom(savedXf);
    FUN_00472540(&other);
    FUN_004a9b10(&baker);
    FUN_0041eb80(&keys);

    mCurIndex++;
    ((EditorArg*)arg)->Finish(this);
}
