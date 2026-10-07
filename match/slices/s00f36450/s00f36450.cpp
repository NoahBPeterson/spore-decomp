// Slice s00f36450 (op3_mid slice 140): this file holds
//   0x00F368B0  FUN_00f368b0   (2545 bytes, __thiscall, ret)
//
// Reads an effect/graphics template's parameters from its property list (+0x0c):
//   - clears its ten EASTL vectors (vector::clear() == erase(begin(), end()));
//   - Vector3 parameters with defaults (0x3a23f98, 0xb208b41, 0x3a23f99, 0xb6929c95,
//     0xb6929c94, 0x968c496a, 0x968c496b), two uint32s (0x536250d/c, default 11) and two
//     bools (0x8e390196 default true, 0x7b18058 default false);
//   - a Vector3 array (0xb6929c93, default one {0.4,0.4,0.4}) and a float array
//     (0xb6929c92, default one 0.5);
//   - the key array 0x2a907b5 and its per-key arrays (transforms 0x2a907b6, floats
//     0x3a23f97 / 0x3dd8e5a / 0x7a6aa70b, uint32s 0x3dd8e59), each padded to the key
//     count with a default when missing;
//   - a second key/transform pair (0x3a90c57 / 0x3a90c5f), the uint32 0x56b14f05
//     (seeded from the first entry of 0x40cf84f and written back when absent) and the
//     key 0x48c74c5c.
// Class and member names are descriptive only (the class is not identified).
// Build flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

#pragma warning(disable: 4100)

inline void* operator new(unsigned int, void* p) throw() { return p; }
inline void operator delete(void*, void*) throw() {}
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    void Set(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
struct Key16 { uint32_t a, b, c, d; };
struct cSPTransform { char data[0x38]; };
struct cSPTransform2 {
    char data[0x38];
    cSPTransform2& operator=(const cSPTransform2& o);    // 0x00537dc0 (cSPTransform::operator=)
};

// ---------------------------------------------------------------- property list
struct Property {
    union {
        uint32_t mValueUInt32;
        void* mpData;
    };
    uint32_t pad04[3];
    uint16_t mnFlags;                                   // +0x10
    uint16_t mnType;                                    // +0x12
    Property() : mnFlags(0), mnType(0) {}
    ~Property() { if (mnFlags & 4) Destruct(0); }
    void Destruct(int);                                 // 0x0093db80 (EA::Variant::Destruct)
    uint32_t* GetUInt();                                // 0x0041ea00 (Property::GetUInt)
    bool* GetBool();                                    // 0x0041e920 (Property::GetBool)
    uint32_t GetValueUInt32() const
    {
        const uint32_t* p = (mnFlags & 0x30) ? (const uint32_t*)mpData : &mValueUInt32;
        return *p;
    }
    void SetValueUInt32(uint32_t v) { mValueUInt32 = v; mnFlags = 0; mnType = 10; }
};

struct PropertyList {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void SetProperty(uint32_t id, const Property* p);   // +0x14
    virtual void v18();
    virtual bool HasProperty(uint32_t id);                      // +0x1c
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& p);        // +0x24
};

bool GetPropertyAsVector3(PropertyList* p, uint32_t id, Vector3& dst);            // 0x006a1110
bool GetPropertyAsKey(PropertyList* p, uint32_t id, ResourceKey& dst);            // 0x006a1250
bool GetPropertyAsFloatArray(PropertyList* p, uint32_t id, int& count, float*& dst);        // 0x006a08b0
bool GetPropertyAsVector3Array(PropertyList* p, uint32_t id, int& count, Vector3*& dst);    // 0x006a0990
bool GetPropertyAsUInt32Array(PropertyList* p, uint32_t id, int& count, uint32_t*& dst);    // 0x006a0ae0
void* EffectsManager();                                                           // 0x0067ddd0

inline bool ReadUInt(PropertyList* pl, uint32_t id, uint32_t& dst)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 10) {
        dst = *p->GetUInt();
        return true;
    }
    return false;
}
inline bool ReadBool(PropertyList* pl, uint32_t id, bool& dst)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 1) {
        dst = *p->GetBool();
        return true;
    }
    return false;
}
inline bool ReadUIntInline(PropertyList* pl, uint32_t id, uint32_t& dst)
{
    Property* p;
    if (pl && pl->GetProperty(id, p) && p->mnType == 10) {
        dst = p->GetValueUInt32();
        return true;
    }
    return false;
}

// ---------------------------------------------------------------- vectors (EASTL layout, 20 bytes)
// eastl::copy for non-trivially-assignable element types (inlined loop).
template <class InputIterator, class OutputIterator>
inline OutputIterator CopyRange(InputIterator first, InputIterator last, OutputIterator result)
{
    for (; first != last; ++result, ++first)
        *result = *first;
    return result;
}

struct sp_vector_allocator { const char* mpName; uint32_t mFlags; };

template <class T> struct PodVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T* erase(T* first, T* last)
    {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
    void DoInsertValue(T* pos, const T& value);                    // 0x00455660 (float)
    void DoInsertValues(T* pos, unsigned n, const T& value);       // 0x004b0a10 (float)
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void resize(unsigned n, const T& value)
    {
        if (n > (unsigned)(mpEnd - mpBegin))
            DoInsertValues(mpEnd, n - (unsigned)(mpEnd - mpBegin), value);
        else
            erase(mpBegin + n, mpEnd);
    }
};

struct KeyVector {                  // eastl::vector<ResourceKey>
    ResourceKey* mpBegin; ResourceKey* mpEnd; ResourceKey* mpCapacity; sp_vector_allocator mAllocator;
    ResourceKey* erase(ResourceKey* first, ResourceKey* last);    // 0x0050f740
    void clear() { erase(mpBegin, mpEnd); }
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct InlineKeyVector {            // eastl::vector<ResourceKey>, erase inlined
    ResourceKey* mpBegin; ResourceKey* mpEnd; ResourceKey* mpCapacity; sp_vector_allocator mAllocator;
    __forceinline ResourceKey* erase(ResourceKey* first, ResourceKey* last)
    {
        CopyRange(last, mpEnd, first);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};
struct Vector3Vector {              // eastl::vector<Vector3>
    Vector3* mpBegin; Vector3* mpEnd; Vector3* mpCapacity; sp_vector_allocator mAllocator;
    Vector3* erase(Vector3* first, Vector3* last);                // 0x0050f740 (ICF with the key vector)
    void clear() { erase(mpBegin, mpEnd); }
    void DoInsertValue(Vector3* pos, const Vector3& value);       // 0x004b5ad0
    void push_back(const Vector3& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) Vector3(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
Key16* CopyKey16(Key16* first, Key16* last, Key16* dest);         // 0x007c8b70
struct Key16Vector {
    Key16* mpBegin; Key16* mpEnd; Key16* mpCapacity; sp_vector_allocator mAllocator;
    void DestroyRange(Key16* first, Key16* last);                 // 0x006a4950
    void clear()
    {
        Key16* first = mpBegin;
        Key16* last = mpEnd;
        Key16* pNewEnd = CopyKey16(last, mpEnd, first);
        DestroyRange(pNewEnd, mpEnd);
        mpEnd -= (last - first);
    }
};
cSPTransform* CopyTransforms(cSPTransform* first, cSPTransform* last, cSPTransform* dest);   // 0x00f339d0
struct TransformVector {
    cSPTransform* mpBegin; cSPTransform* mpEnd; cSPTransform* mpCapacity; sp_vector_allocator mAllocator;
    void resize(unsigned n);                                      // 0x00f36730
    bool empty() const { return mpBegin == mpEnd; }
    void clear()
    {
        cSPTransform* first = mpBegin;
        cSPTransform* last = mpEnd;
        CopyTransforms(last, mpEnd, first);
        mpEnd -= (last - first);
    }
};
struct InlineTransformVector {
    cSPTransform2* mpBegin; cSPTransform2* mpEnd; cSPTransform2* mpCapacity; sp_vector_allocator mAllocator;
    cSPTransform2* erase(cSPTransform2* first, cSPTransform2* last)
    {
        CopyRange(last, mpEnd, first);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

void ReadKeyArray(PropertyList* p, uint32_t id, int type, KeyVector* dst);              // 0x00f34d40
void ReadKeyArray(PropertyList* p, uint32_t id, int type, InlineKeyVector* dst);        // 0x00f34d40
void ReadTransformArray(PropertyList* p, uint32_t id, int type, TransformVector* dst);  // 0x00f36810
void ReadTransformArray(PropertyList* p, uint32_t id, int type, InlineTransformVector* dst); // 0x00f36810
void ReadFloatArray(PropertyList* p, uint32_t id, int type, PodVector<float>* dst);     // 0x00bb15d0
void ReadUIntArray(PropertyList* p, uint32_t id, int type, PodVector<uint32_t>* dst);   // 0x00fea840

class cTemplateF368B0 {
public:
    void ReadParameters();
    void FillUIntDefaults(uint32_t value);              // 0x00f35be0

    char pad00[0xc];
    PropertyList* mpPropList;                           // +0x0c
    uint32_t pad10;
    KeyVector mKeys;                                    // +0x14
    TransformVector mTransforms;                        // +0x28
    PodVector<float> mFloats3C;                         // +0x3c
    PodVector<float> mFloats50;                         // +0x50
    PodVector<uint32_t> mUInts64;                       // +0x64
    Key16Vector mVec78;                                 // +0x78
    PodVector<float> mFloats8C;                         // +0x8c
    InlineKeyVector mKeys2;                             // +0xa0
    InlineTransformVector mTransforms2;                 // +0xb4
    Vector3 mVecC8;                                     // +0xc8
    Vector3 mVecD4;                                     // +0xd4
    Vector3 mVecE0;                                     // +0xe0
    uint32_t mUIntEC;                                   // +0xec
    uint32_t mUIntF0;                                   // +0xf0
    ResourceKey mKeyF4;                                 // +0xf4
    char pad100[4];
    bool mbFlag104;                                     // +0x104
    char pad105[3];
    Vector3Vector mVec3s;                               // +0x108
    PodVector<float> mFloats11C;                        // +0x11c
    Vector3 mVec130;                                    // +0x130
    Vector3 mVec13C;                                    // +0x13c
    Vector3 mVec148;                                    // +0x148
    Vector3 mVec154;                                    // +0x154
    uint32_t mUInt160;                                  // +0x160
    char pad164[0x18d - 0x164];
    bool mbFlag18D;                                     // +0x18d
};

void cTemplateF368B0::ReadParameters()
{
    mKeys.clear();
    mFloats50.clear();
    mVec78.clear();
    mTransforms.clear();
    mUInts64.clear();
    mFloats3C.clear();
    mFloats8C.clear();

    mVecC8.Set(0.5f, 0.5f, 0.5f);
    GetPropertyAsVector3(mpPropList, 0x3a23f98, mVecC8);
    mVecD4.Set(0.5f, 0.0f, 0.0f);
    GetPropertyAsVector3(mpPropList, 0xb208b41, mVecD4);
    mVecE0.Set(33.0f, 37.0f, 500.0f);
    mUIntEC = 11;
    mUIntF0 = 11;
    GetPropertyAsVector3(mpPropList, 0x3a23f99, mVecE0);
    ReadUInt(mpPropList, 0x536250d, mUIntEC);
    ReadUInt(mpPropList, 0x536250c, mUIntF0);
    mbFlag18D = true;
    ReadBool(mpPropList, 0x8e390196, mbFlag18D);
    mbFlag104 = false;
    ReadBool(mpPropList, 0x7b18058, mbFlag104);

    mVec130 = Vector3(0.4f, 0.4f, 0.4f);
    GetPropertyAsVector3(mpPropList, 0xb6929c95, mVec130);
    mVec13C = Vector3(0.4f, 0.4f, 0.4f);
    GetPropertyAsVector3(mpPropList, 0xb6929c94, mVec13C);
    mVec148 = Vector3(0.4f, 0.4f, 0.4f);
    GetPropertyAsVector3(mpPropList, 0x968c496a, mVec148);
    mVec154 = Vector3(0.4f, 0.4f, 0.4f);
    GetPropertyAsVector3(mpPropList, 0x968c496b, mVec154);

    mVec3s.clear();
    mFloats11C.clear();

    int count = 0;
    Vector3* vecs;
    GetPropertyAsVector3Array(mpPropList, 0xb6929c93, count, vecs);
    if (count > 0) {
        for (int i = 0; i < count; i++)
            mVec3s.push_back(vecs[i]);
    }
    else {
        mVec3s.push_back(Vector3(0.4f, 0.4f, 0.4f));
    }

    int floatCount = 0;
    float* floats;
    GetPropertyAsFloatArray(mpPropList, 0xb6929c92, floatCount, floats);
    if (floatCount > 0) {
        for (int i = 0; i < floatCount; i++)
            mFloats11C.push_back(floats[i]);
    }
    else {
        mFloats11C.push_back(0.5f);
    }

    ReadKeyArray(mpPropList, 0x2a907b5, 0x20, &mKeys);
    EffectsManager();
    ReadTransformArray(mpPropList, 0x2a907b6, 0x38, &mTransforms);
    if (mTransforms.empty())
        mTransforms.resize(mKeys.size());

    ReadFloatArray(mpPropList, 0x3a23f97, 0xd, &mFloats50);
    if (mFloats50.empty())
        mFloats50.resize(mKeys.size(), 0.0f);

    ReadUIntArray(mpPropList, 0x3dd8e59, 0xa, &mUInts64);
    if (mUInts64.empty()) {
        uint32_t value = 0;
        ReadUIntInline(mpPropList, 0x2a907b7, value);
        FillUIntDefaults(value);
    }

    ReadFloatArray(mpPropList, 0x3dd8e5a, 0xd, &mFloats3C);
    if (mFloats3C.empty())
        mFloats3C.resize(mKeys.size(), 1.0f);

    ReadFloatArray(mpPropList, 0x7a6aa70b, 0xd, &mFloats8C);
    if (mFloats8C.empty() || mFloats8C.size() != (unsigned)mKeys.size())
        mFloats8C.resize(mKeys.size(), mVecC8.x);

    mKeys2.clear();
    mTransforms2.clear();
    ReadKeyArray(mpPropList, 0x3a90c57, 0x20, &mKeys2);
    ReadTransformArray(mpPropList, 0x3a90c5f, 0x38, &mTransforms2);

    mUInt160 = 0;
    if (!mpPropList->HasProperty(0x56b14f05)) {
        int n = 0;
        uint32_t* values = 0;
        GetPropertyAsUInt32Array(mpPropList, 0x40cf84f, n, values);
        if (n > 0) {
            mUInt160 = values[0];
            Property prop;
            prop.SetValueUInt32(values[0]);
            mpPropList->SetProperty(0x56b14f05, &prop);
        }
    }
    ReadUIntInline(mpPropList, 0x56b14f05, mUInt160);

    mKeyF4.instanceID = 0;
    mKeyF4.typeID = 0;
    mKeyF4.groupID = 0;
    GetPropertyAsKey(mpPropList, 0x48c74c5c, mKeyF4);
}
