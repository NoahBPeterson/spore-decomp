// Slice s005567e0: SP model-summarizer resource setup. Unoptimized /Od module.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

#pragma warning(disable: 4100 4189)

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
#include <math.h>

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

namespace eastl {
struct allocator_tag { allocator_tag() {} };
struct allocator {
    allocator() {}
    allocator(const allocator_tag& tag);
    const char* mpName;
    uint32_t mFlags;
};
struct sp_vector_allocator : public allocator { sp_vector_allocator() {} };
template<typename T, typename A>
struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator() {}
};
template<typename T, typename A>
class vector : public VectorBase<T, A> {
public:
    vector() { ScratchSlots<1>(); }
    void push_back(const T& value);             // 0x004e19a0, thiscall ret 4
};
}

struct ResourceKey {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
};
struct Hash128 { uint32_t mData[4]; };

namespace SP {
struct ResourceObject {
    virtual int AddRef();
    virtual int Release();
};
}
struct IResourceManager {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual bool GetResource(const ResourceKey& key, SP::ResourceObject** ppResource, int a, int b, int c, int d);
};
namespace EA { namespace ResourceMan { IResourceManager* GetManager(); }}      // 0x0067dcd0

namespace EA {
template<typename T> struct RefCountTemplate { T mnRefCount; int Release(); };  // 0x00453540
}
struct cSummaryBase { virtual void f(); };
struct cSummaryData : public cSummaryBase, public EA::RefCountTemplate<int> {};

template<typename T>
struct IntrusivePtr {
    T* mpObject;
    IntrusivePtr() : mpObject(0) {}
    ~IntrusivePtr() { if (mpObject) mpObject->Release(); }
};
template<> struct IntrusivePtr<SP::ResourceObject> {
    SP::ResourceObject* mpObject;
    IntrusivePtr() : mpObject(0) {}
    ~IntrusivePtr() { if (mpObject) mpObject->Release(); }
    SP::ResourceObject* get() const { return mpObject; }
    SP::ResourceObject** GetAddressForUpdate();                                  // 0x0041d870
    SP::ResourceObject** AsPPTypeParam() { return GetAddressForUpdate(); }
};
typedef IntrusivePtr<SP::ResourceObject> ResourceObjectPtr;

namespace SP {
namespace FunctionalMatch {
enum eType { kInteger = 48342877, kFloat = 48343039 };
struct DeclareParam {
    unsigned int mParameter;
    eType mType;
    union { int mIntVal; float mFloatVal; };
    DeclareParam(unsigned int param, float value);      // 0x00558b90, thiscall ret 8
    DeclareParam(unsigned int param, int value);        // 0x00558bc0, thiscall ret 8
};
}
using namespace FunctionalMatch;

struct Vector3 {
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
};
struct BBox { Vector3 mMin, mMax; };

// One owner entry (id, weight); the owner's list is walked by ApplyOwnerEntries (0x00433210).
struct OwnerEntry { uint32_t mID; float mValue; };
struct Alloc { Alloc() {} };
struct VSet {
    OwnerEntry* mpBegin;
    OwnerEntry* mpEnd;
    OwnerEntry* mpCapacity;
    eastl::sp_vector_allocator mAllocator;               // not initialised by the out-of-line ctor
    VSet(const Alloc& a);                                // 0x00540470, thiscall ret 4
    ~VSet();                                             // 0x004cddd0, thiscall
    int size() const { return (int)(mpEnd - mpBegin); }
    OwnerEntry& operator[](int i) { return mpBegin[i]; }
};

struct cCreationResource {
    uint32_t pad[0x18 / 4];
    int mModelType;                                      // +0x18
    int GetModelType() { ScratchSlots<8>(); return mModelType; }   // frame of the original's (non-trivial) accessor
    // 0x004bac30, thiscall ret 0x18: (sret, availability hash, flag)
    Hash128 GetRequiredValidity(Hash128 available, bool flag);
};
bool FUN_004f3d60(Hash128 a, Hash128 b);                 // cdecl, by-value hashes
void ApplyOwnerEntries(cCreationResource* owner, VSet* out);          // 0x00433210, cdecl
void FUN_00471ec0(BBox* out, cCreationResource* owner, float* pValue); // cdecl
float FUN_005565e0(float a, float b, float c, float d);   // cdecl, float result in st0
}

extern Hash128 kVehicleHash;                              // 0x015da9c8 (used as both args)
extern const float kZeroF;                                // 0x01485378
extern const float kNegOneF;                              // 0x013eb1bc
extern const float kNoValueF;                             // 0x015e3c44
extern const float kScale02F;                             // 0x013ec480

namespace SP {

// @ 0x00556E10
class cBuildingModelSummarizer {
public:
    uint32_t GetResType(int arg);
};
uint32_t cBuildingModelSummarizer::GetResType(int arg) {
    if (arg == 0)
        return 0x2399be55;
    return 0xffffffff;
}

class cVehicleModelSummarizer {
public:
    bool ExtractParameters(const ResourceKey& key, eastl::vector<DeclareParam, eastl::sp_vector_allocator>& params);
};

// @ 0x005567E0
bool cVehicleModelSummarizer::ExtractParameters(const ResourceKey& key, eastl::vector<DeclareParam, eastl::sp_vector_allocator>& params) {
    IntrusivePtr<cSummaryData> spMeta;
    IResourceManager* pResourceManager = EA::ResourceMan::GetManager();
    ResourceObjectPtr resource;
    if (!pResourceManager || !pResourceManager->GetResource(key, resource.AsPPTypeParam(), 0, 0, 0, 0))
        return false;

    cCreationResource* editorResource = (cCreationResource*)resource.get();
    if (!FUN_004f3d60(editorResource->GetRequiredValidity(kVehicleHash, true), kVehicleHash))
        return true;

    VSet stats((Alloc()));
    ApplyOwnerEntries(editorResource, &stats);

    float fTotalValue = kZeroF;
    float headSum = kNegOneF;
    for (int i = 0, num = stats.size(); i < num; i++) {
        if (stats[i].mValue != kNoValueF) {
            float currentValue = stats[i].mValue * kScale02F;
            switch (stats[i].mID) {
            case 0x11b78a71:
                params.push_back(DeclareParam(0x429d47d, currentValue));
                fTotalValue += currentValue;
                break;
            case 0x06329468:
            case 0x06329469:
            case 0x0632946a:
            case 0x11b78a72:
                if (kZeroF > headSum)
                    headSum = currentValue;
                else
                    headSum += currentValue;
                fTotalValue += currentValue;
                break;
            case 0x11b78a70:
                params.push_back(DeclareParam(0x429d47e, currentValue));
                fTotalValue += currentValue;
                break;
            }
        }
    }
    if (headSum >= kZeroF)
        params.push_back(DeclareParam(0x429d47c, headSum));
    params.push_back(DeclareParam(0x5b950d7, fTotalValue));

    switch (editorResource->GetModelType()) {
    case 0x9ad7d4aa: case 0xbc1041e6: case 0xf670aa43: case 0x7d433fad:
        params.push_back(DeclareParam(0x5c96ff0, 0x5c972ea));
        break;
    case 0x1f2a25b6: case 0xc15695da: case 0x8f963dcb: case 0x2a5147a9:
        params.push_back(DeclareParam(0x5c96ff0, 0x5c972ee));
        break;
    case 0x1a4e0708: case 0x441cd3e6: case 0x2090a11b: case 0x449c040f:
        params.push_back(DeclareParam(0x5c96ff0, 0x5c972f1));
        break;
    }

    float partTotalVolume = kZeroF;
    BBox resourceBBox;
    ScratchSlots<6>();                                   // reserved frame of the declined-inline bounds helper
    FUN_00471ec0(&resourceBBox, editorResource, &partTotalVolume);
    float width = fabs(resourceBBox.mMax[0] - resourceBBox.mMin[0]);
    float depth = fabs(resourceBBox.mMax[1] - resourceBBox.mMin[1]);
    float height = fabs(resourceBBox.mMax[2] - resourceBBox.mMin[2]);
    float volume = width * depth * height;
    float quotient = partTotalVolume / volume;
    ScratchSlots<8>();                                   // reserved frame of the declined-inline FUN_005565e0
    float computed = FUN_005565e0(quotient, width, height, depth);
    params.push_back(DeclareParam(0x5e62409, computed));
    params.push_back(DeclareParam(0x5de94ea, resourceBBox.mMax[2]));
    return true;
}

namespace W1G2_56 {

// @ 0x00556E30 — partial: building summarizer parameter setup.
class c56e30 {
public:
    uint32_t pad[0x80];
    void sub(int a, int b);   // @ 0x00556E30
};
void c56e30::sub(int a, int b) {
}

}
}
