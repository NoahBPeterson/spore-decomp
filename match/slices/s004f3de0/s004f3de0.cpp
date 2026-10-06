// w1g1 slice s004f3de0 -- SP::cSPEditorModelValidity::CalculateValidity
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (editor /Od region, no /EHsc).
//
// Runs every validity test selected in `tests` (an eastl::bitset<128> indexed by
// cSPEditorModelValidity::eValidityTests) against an editor model, accumulating the
// failed tests in a result bitset. With bStopOnFirstFailure set it returns as soon as
// one selected test fails. Name from the dev PDB (caller-single match, dev 0x00c09620).

typedef unsigned int uint32_t;

// eastl::bitset<128, uint32_t>: only the members this TU uses, written as the inline
// EASTL bodies (test/set are inlined at /Ob1 with their range checks).
template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];

    bitset() { reset(); }
    __forceinline void reset() {
        for (uint32_t i = 0; i < (N + 31) / 32; i++)
            mWord[i] = 0;
    }
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    uint32_t DoGetWord(uint32_t i) const { return mWord[i >> 5]; }
    __forceinline bool test(uint32_t i) const {
        if (i < N)
            return (DoGetWord(i) & (1u << (i % 32))) != 0;
        return false;
    }
    __forceinline bitset& set(uint32_t i, bool value) {
        if (i < N) {
            if (value)
                DoGetWord(i) |= (1u << (i % 32));
            else
                DoGetWord(i) &= ~(1u << (i % 32));
        }
        return *this;
    }
};

typedef bitset<128> ValidityBits;

namespace EA { namespace ResourceMan {
struct Key {
    uint32_t instanceID;   // +0
    uint32_t typeID;       // +4
    uint32_t groupID;      // +8
    Key() : instanceID(0), typeID(0), groupID(0) {}
};
}}

// Ref-counted objects: AddRef in vtable slot 0, Release in slot 1.
struct RefCounted {
    virtual int AddRef();
    virtual int Release();
};

// EA::AutoRefCount<T>: the inline members used here.
template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    // Releases the held object, then hands out the slot for an out-parameter.
    T** AsPPointer() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};

namespace SP {

struct cPropertyList : RefCounted {
    bool HasProperty(uint32_t propID);                       // @ 0x6a25a0
};

// SP::PropertyManager(): vtable slot 11 (+0x2c) = GetPropertyList(id, group, &out).
struct cPropertyManager {
    virtual void _v00(); virtual void _v01(); virtual void _v02(); virtual void _v03();
    virtual void _v04(); virtual void _v05(); virtual void _v06(); virtual void _v07();
    virtual void _v08(); virtual void _v09(); virtual void _v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** ppOut);  // +0x2c
};
cPropertyManager* PropertyManager();                         // @ 0x67de30
bool GetPropertyAsKey(const cPropertyList* pList, uint32_t propID, EA::ResourceMan::Key* pKey);  // @ 0x6a1250

namespace Editor {
uint32_t GetConfigFromModelType(uint32_t modelType);         // @ 0x432f10
}

// Retail editor model layout (differs from the 2008 PDB): key at +8, model type at +0x18.
struct cEditorModel {
    uint32_t pad0[2];
    EA::ResourceMan::Key mKey;                               // +0x08
    uint32_t pad1;
    uint32_t mModelType;                                     // +0x18
    uint32_t GetModelType() const { return mModelType; }
};

}  // namespace SP

namespace EA { namespace ResourceMan {
struct ResourceObject : RefCounted {
    virtual void* Cast(uint32_t typeID);                     // slot 3 (+0xc)
};
typedef AutoRefCount<ResourceObject> ResourceObjectPtr;
// GetManager(): vtable slot 3 (+0xc) = GetResource(key, &out, 0, 0, 0, 0).
struct IResourceManager {
    virtual void _v00(); virtual void _v01(); virtual void _v02();
    virtual bool GetResource(const Key& key, ResourceObject** ppOut, int a, int b, int c, int d);  // +0xc
};
IResourceManager* GetManager();                              // @ 0x67dcd0
}}

// The editor-model resource (type 0x030bdee3) that carries the creation's name.
struct cEditorResource {
    uint32_t pad[0x78 / 4];
    void* mName;                                             // +0x78
    void* GetName();                                         // @ 0x414e10 (returns mName)
};
cEditorResource* object_cast_cEditorResource(EA::ResourceMan::ResourceObjectPtr& p);  // @ 0x421f60

// Global property IDs (relocated, masked).
extern SP::cPropertyList* sAppProperties;                    // 0x15fd918
extern uint32_t kEditorConfigGroup;                          // 0x15daa00
extern uint32_t kMinBlockCount;                              // 0x15da6e0

namespace SP {
struct cSPEditorModelValidity {
    enum eValidityTests {
        kValidityTooComplex = 0,
        kValidityOverBudget = 1,
        kValidityIncomplete = 2,
        kValidityUnloadableTextures = 3,
        kValidityInvalidName = 4,
        kValidityInvalidParts = 5,
        kValidityInvalidParents = 6,
        kValidityInvalidScales = 7,
        kValidityOutOfBounds = 8,
        kValidityTooSmall = 9,
        kValidityNoMouth = 10,
        kValidityNotPainted = 11,
        kValidityStatsOutOfRange = 12,
        kValidityHasFloatingParts = 13,
        kValidityUnloadableBlocks = 14,
        kValidityInvalidSymmetry = 15,
        kValidityMissingPacks = 16,
        kValidityHasZeroBlocks = 17,
        kValidityInvalidPaint = 18,
        kValidityIntersectingEndEffectors = 19,
        kValidityBlankName = 20,
        kValidityBadCharacters = 21,
        kValidityTooSmallX = 22,
        kValidityTooSmallY = 23,
        kValidityTooSmallZ = 24,
        kValidityTooSmallAbsoluteZ = 25,
        kValidityFailedLoad = 26,
        kValidityInvalidLimb = 27,
        kValidityNoReason = 28
    };

    static ValidityBits CalculateValidity(cEditorModel* model, ValidityBits tests, bool bStopOnFirstFailure);
};
}  // namespace SP

// Individual tests (cdecl statics); each sets/clears its own bit in `validity`.
void TestMissingPacks(SP::cEditorModel* model, ValidityBits& validity);         // @ 0x4edeb0
void TestUnloadableBlocks(SP::cEditorModel* model, ValidityBits& validity);     // @ 0x4ee3b0
void TestUnloadableTextures(SP::cEditorModel* model, ValidityBits& validity);   // @ 0x4ecec0
void TestSymmetry(SP::cEditorModel* model, ValidityBits& validity);             // @ 0x4ed7f0
void TestParents(SP::cEditorModel* model, ValidityBits& validity);              // @ 0x4ed320
void TestLimbs(SP::cEditorModel* model, ValidityBits& validity);                // @ 0x4ee9b0
void TestScales(SP::cEditorModel* model, ValidityBits& validity);               // @ 0x4ee560
void TestParts(SP::cEditorModel* model, uint32_t partsListID, ValidityBits& validity);  // @ 0x4ef880
void TestPaint(SP::cEditorModel* model, uint32_t paintListID, ValidityBits& validity);  // @ 0x4efb20
bool HasEnoughBlocks(SP::cEditorModel* model, uint32_t minBlocks, int flags);   // @ 0x4eda30
void TestComplexity(SP::cEditorModel* model, ValidityBits& validity);           // @ 0x4f1350
void TestName(void* name, ValidityBits& validity);                              // @ 0x4edf40
void TestBounds(SP::cEditorModel* model, ValidityBits& validity);               // @ 0x4ef190
void TestSize(SP::cEditorModel* model, ValidityBits& validity);                 // @ 0x4f01f0
void TestVehicleStatsInRange(SP::cEditorModel* model, ValidityBits& validity);  // @ 0x4f2610
void TestBudget(SP::cEditorModel* model, ValidityBits& validity);               // @ 0x4f2210
void TestFloatingParts(SP::cEditorModel* model, ValidityBits& validity);        // @ 0x4f3650
void TestEndEffectors(SP::cEditorModel* model, ValidityBits& validity);         // @ 0x4f31c0

inline SP::cPropertyList* AppProperties() { return sAppProperties; }

using SP::cSPEditorModelValidity;

// @ 0x004f3de0  (MATCH)
ValidityBits SP::cSPEditorModelValidity::CalculateValidity(cEditorModel* model, ValidityBits tests, bool bStopOnFirstFailure)
{
    ValidityBits validity;

    if (AppProperties()->HasProperty(0x055d7ca1))   // validation disabled by app property
        return validity;

    if (tests.test(kValidityMissingPacks)) {
        TestMissingPacks(model, validity);
        if (validity.test(kValidityMissingPacks) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityUnloadableBlocks)) {
        TestUnloadableBlocks(model, validity);
        if (validity.test(kValidityUnloadableBlocks) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityUnloadableTextures)) {
        TestUnloadableTextures(model, validity);
        if (validity.test(kValidityUnloadableTextures) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidSymmetry)) {
        TestSymmetry(model, validity);
        if (validity.test(kValidityInvalidSymmetry) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidParents)) {
        TestParents(model, validity);
        if (validity.test(kValidityInvalidParents) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidLimb)) {
        TestLimbs(model, validity);
        if (validity.test(kValidityInvalidLimb) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidScales)) {
        TestScales(model, validity);
        if (validity.test(kValidityInvalidScales) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidParts)) {
        uint32_t modelConfig = Editor::GetConfigFromModelType(model->GetModelType());
        AutoRefCount<cPropertyList> propList;
        if (PropertyManager()->GetPropertyList(modelConfig, kEditorConfigGroup, propList.AsPPointer())) {
            EA::ResourceMan::Key partsKey;
            if (GetPropertyAsKey(propList.get(), 0xf5cbe065, &partsKey))
                TestParts(model, partsKey.instanceID, validity);
            else
                validity.set(kValidityInvalidParts, true);
        } else {
            validity.set(kValidityInvalidParts, true);
        }
        if (validity.test(kValidityInvalidParts) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidPaint)) {
        uint32_t modelConfig = Editor::GetConfigFromModelType(model->GetModelType());
        AutoRefCount<cPropertyList> propList;
        if (PropertyManager()->GetPropertyList(modelConfig, kEditorConfigGroup, propList.AsPPointer())) {
            EA::ResourceMan::Key paintKey;
            if (GetPropertyAsKey(propList.get(), 0x7a926123, &paintKey))
                TestPaint(model, paintKey.instanceID, validity);
            else
                validity.set(kValidityInvalidPaint, true);
        } else {
            validity.set(kValidityInvalidPaint, true);
        }
        if (validity.test(kValidityInvalidPaint) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityHasZeroBlocks)) {
        validity.set(kValidityHasZeroBlocks, !HasEnoughBlocks(model, 1, 0));
        if (validity.test(kValidityHasZeroBlocks) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityIncomplete)) {
        validity.set(kValidityIncomplete, !HasEnoughBlocks(model, kMinBlockCount, 0));
        if (validity.test(kValidityIncomplete) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityTooComplex)) {
        TestComplexity(model, validity);
        if (validity.test(kValidityTooComplex) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityInvalidName)) {
        EA::ResourceMan::Key nameKey = model->mKey;
        nameKey.typeID = 0x030bdee3;
        EA::ResourceMan::ResourceObjectPtr resource(0);
        if (EA::ResourceMan::GetManager()->GetResource(nameKey, resource.AsPPointer(), 0, 0, 0, 0)) {
            cEditorResource* pResource = object_cast_cEditorResource(resource);
            TestName(pResource->GetName(), validity);
        } else {
            validity.set(kValidityInvalidName, true);
        }
        if (validity.test(kValidityInvalidName) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityOutOfBounds)) {
        TestBounds(model, validity);
        if (validity.test(kValidityOutOfBounds) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityTooSmall)) {
        TestSize(model, validity);
        if (validity.test(kValidityTooSmall) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityStatsOutOfRange)) {
        TestVehicleStatsInRange(model, validity);
        if (validity.test(kValidityStatsOutOfRange) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityOverBudget)) {
        TestBudget(model, validity);
        if (validity.test(kValidityOverBudget) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityHasFloatingParts)) {
        TestFloatingParts(model, validity);
        if (validity.test(kValidityHasFloatingParts) && bStopOnFirstFailure)
            return validity;
    }
    if (tests.test(kValidityIntersectingEndEffectors)) {
        TestEndEffectors(model, validity);
        if (validity.test(kValidityIntersectingEndEffectors) && bStopOnFirstFailure)
            return validity;
    }
    return validity;
}
