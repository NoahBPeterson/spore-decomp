// src/game/Swarm/Help.cpp -- migrated from slice(s) s00a74260, s00a73110 by tools/migrate/rewrite.py
// Object file: Swarm/Help.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Swarm/cTransform.h"
#include "EA/ArgScript/cArgumentSpec.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/Swarm/cIVisualEffect.h"
#include "EA/Swarm/cVisualEffect.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);   // E8 call (0x011e0744)
extern char gEmptyString[];                     // 0x01667bac

// ---- items of slice s00a73110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);   // E8 call (0x011e0744)
void __cdecl operator_delete__(void* p);                                        // 0x00f47380
struct sp_vector_allocator { sp_vector_allocator() {} };
extern char gEmptyString[];                     // 0x01667bac
struct string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    unsigned int mAlloc;
    string() { mpBegin = &gEmptyString[0]; mpEnd = &gEmptyString[0]; mpCapacity = &gEmptyString[1]; }
    string(const string& x);                                   // 0x0057cb10
    ~string()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator_delete__(mpBegin);
    }
    string& operator=(const string& x);                        // 0x00579c60
    unsigned int rfind(char c, unsigned int pos) const;        // 0x00609f40
    string& erase(unsigned int pos, unsigned int n);           // 0x0061e200
    struct string_tmp substr(unsigned int pos, unsigned int n) const;   // 0x006082a0
    bool empty() const { return mpBegin == mpEnd; }
    const char* c_str() const { return mpBegin; }
};
struct string_tmp : string {
    ~string_tmp();                                             // 0x00530670
};
template <class T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned int mAlloc;
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](int i) { return mpBegin[i]; }
    T* erase(T* first, T* last)
    {
        memmove(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};
struct IntVector {                 // eastl::vector<int, sp_vector_allocator>, owned buffer
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    unsigned int mAlloc;
    IntVector(unsigned int n, const sp_vector_allocator& a = sp_vector_allocator());   // 0x006a6310
    ~IntVector()
    {
        if (mpBegin && mpBegin[-1] != 0)
            operator_delete__(mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    int* data() { return mpBegin; }
    int& operator[](int i) { return mpBegin[i]; }
};
string* __cdecl copy_strings(string* first, string* last, string* dest);   // 0x007c8b70 eastl::copy<string*>
struct StringVector {
    string* mpBegin;
    string* mpEnd;
    string* mpCapacity;
    unsigned int mAlloc;
    void destruct(string* first, string* last);                // 0x006a4950
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    string& operator[](int i) { return mpBegin[i]; }
    string* erase(string* first, string* last)
    {
        string* position = copy_strings(last, mpEnd, first);
        destruct(position, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
inline Vector3 operator*(const Vector3& v, float s) { return Vector3(s * v.x, s * v.y, s * v.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
struct Matrix3 {
    float m[3][3];
    Matrix3() {}
    Matrix3(const Matrix3& o);                                 // 0x0041cb40
};
inline Vector3 operator*(const Vector3& v, const Matrix3& r)
{
    return Vector3(v.x * r.m[0][0] + v.y * r.m[1][0] + v.z * r.m[2][0],
                   v.x * r.m[0][1] + v.y * r.m[1][1] + v.z * r.m[2][1],
                   v.x * r.m[0][2] + v.y * r.m[1][2] + v.z * r.m[2][2]);
}
extern const Vector3 kVector3Zero;                             // 0x01676c5c
extern const Matrix3 kMatrix3Identity;                         // 0x01676d08
struct Transform {
    enum { kScale = 1, kRotation = 2, kOffset = 4 };
    short mnFlags;                 // +0x00
    short mnTransformCount;        // +0x02
    Vector3 mOffset;               // +0x04
    float mfScale;                 // +0x10
    Matrix3 mRotation;             // +0x14
    Transform();                                               // 0x00434040
    Transform(const Vector3& offset, float scale, const Matrix3& rot)
        : mnFlags(0), mnTransformCount(0), mOffset(offset), mfScale(scale), mRotation(rot) {}
    void SetOffset(const Vector3& v) { mOffset = v; mnFlags |= kOffset; ++mnTransformCount; }
    void SetOffset(float x, float y, float z) { mOffset.x = x; mOffset.y = y; mOffset.z = z; mnFlags |= kOffset; ++mnTransformCount; }
    void SetScale(float s) { mfScale = s; ++mnTransformCount; }
};
struct BoundingBox {
    Vector3 mMin;
    Vector3 mMax;
    BoundingBox();                                             // 0x006e9530
};
struct EffectKey { unsigned int instanceID; unsigned int groupID; };
struct cIVisualEffect {
    virtual int AddRef();
    virtual int Release();
    virtual void Start(int hardStart);
    virtual int Stop(int hardStop);
    virtual int IsRunning();
    virtual void SetRigidTransform(const Transform& t);
    virtual void SetSourceTransform(const Transform& t);
    virtual void v1c();
    virtual void v20();
    virtual void SetBone(void* bone, int type);
    virtual void* GetBone(int type);
    virtual void SetIsPaused(bool paused);
    virtual void SetIsHidden(bool hidden);
    virtual bool GetIsPaused();
    virtual bool GetIsHidden();
    virtual void SetSeed(int seed);
    virtual bool SetVectorParams(int param, const Vector3* data, int count);
    virtual bool SetFloatParams(int param, const float* data, int count);
    virtual bool SetIntParams(int param, const int* data, int count);
};
struct EffectPtr {
    cIVisualEffect* mpObject;
    operator cIVisualEffect*() const { return mpObject; }
    cIVisualEffect* operator->() const { return mpObject; }
    void reset()
    {
        if (mpObject) {
            cIVisualEffect* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
};
struct EffectVector : vector<EffectPtr> {
    void resize(int n);                                        // 0x00a730c0
};
struct cIEffectWorld {
    virtual void v00();
    virtual void v04();
    virtual bool CreateEffect(EffectKey key, EffectPtr* out);
};
struct cITerrainQuery {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void GetBoundingBox(BoundingBox* box);
    virtual bool HasHeightAt(const Vector3* p);
    virtual void v1c();
    virtual float GetHeightAt(const Vector3* p);
};
struct cIEffectResources {
    virtual void v00();
    virtual void v04();
    virtual bool FindKey(int type, const char* name, EffectKey* out);
};
struct EffectFileInfo {            // description record filled in by the manager
    string mName;
    string mFile;
    int mFlags;
    EffectFileInfo() : mFlags(0) {}
    ~EffectFileInfo();                                         // 0x007e1a80
};
struct cEffectsManagerVT {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual bool HasEffect(EffectKey key);                     // +0x28
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88();
    virtual cITerrainQuery* GetTerrainQuery(int a, int b);     // +0x8c
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4();
    virtual bool GetEffectFileInfo(EffectFileInfo* info, const char* name);   // +0xb8
};
struct cEffectsManager : cEffectsManagerVT {
    unsigned int pad04[(0x48 - 4) / 4];
    cIEffectResources* mpResources;                            // +0x48
    cIEffectWorld* GetWorld(const char* name);                 // 0x00a6d840
};
bool __cdecl OpenEffectsFile(const char* file, const char* subName);   // 0x00a72cd0 EA::Swarm::OpenEffectsFile
struct RandomLinearCongruential {
    void SetSeed(unsigned int seed);                           // 0x00936090
};
extern RandomLinearCongruential sRandom;                       // 0x016778dc
struct cFormatParser;
void __cdecl Output(cFormatParser* p, const char* fmt, ...);   // 0x00841000 EA::ArgScript::Output
struct cArguments {
    int NumArguments() const;                                  // 0x00837f30
};
struct cArgumentSpec {
    void Parse(const cArguments& args, cFormatParser* parser); // 0x0083b9d0
    unsigned int pad[(0x70) / 4];
    unsigned int mFlags;                                       // +0x70 (cheat +0x98)
};
struct cEffectCheat {
    enum tFlags {
        kHasPosition = 0, kPositionHasHeight = 1, kHasScale = 2, kStart = 3, kStop = 4,
        kSoft = 5, kHard = 6, kClear = 7, kEdit = 8, kModelOverride = 9, kTextureOverride = 10,
        kSetFrame = 11, kSetState = 12, kSetFloatParams = 13, kSetIntParams = 14,
        kSetPaused = 15, kSetHidden = 16, kSetSeed = 17
    };
    void* vftable;                                 // +0x00
    cFormatParser* mpFormatParser;                 // +0x04
    unsigned int pad08[2];
    cEffectsManager* mManager;                     // +0x10
    EffectVector mTestEffects;                     // +0x14
    unsigned int pad24;
    cArgumentSpec mArgSpec;                        // +0x28 (flags at +0x98)
    unsigned int padspec[(0xf0 - 0x9c) / 4];
    const char* mWorldName;                        // +0xf0
    const char* mEffectName;                       // +0xf4
    const char* mModel;                            // +0xf8
    const char* mTexture;                          // +0xfc
    Vector3 mPosition;                             // +0x100
    float mScale;                                  // +0x10c
    int mID;                                       // +0x110
    int mFrame;                                    // +0x114
    int mStateIndex;                               // +0x118
    bool mHidden;                                  // +0x11c
    bool mPaused;                                  // +0x11d
    int mSeed;                                     // +0x120
    int mOverrideSet;                              // +0x124
    unsigned int pad128[4];                        // +0x128 mColour
    StringVector mOverrideNames;                   // +0x138
    unsigned int pad148;
    vector<int> mOverrideSets;                     // +0x14c
    unsigned int pad15c;
    vector<float> mOverrideRanges;                 // +0x160
    unsigned int pad170;
    int mFloatParam;                               // +0x174
    vector<float> mFloatParams;                    // +0x178
    unsigned int pad188;
    int mIntParam;                                 // +0x18c
    vector<int> mIntParams;                        // +0x190

    bool Flag(int bit) const { return ((mArgSpec.mFlags >> bit) & 1) != 0; }
    void ParseLine(const cArguments& args);
};
static const char kDebug[] = "debug";              // 0x0140b5d4
// ---- items of slice s00a73110 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern const Vector3 kVector3Zero;                             // 0x01676c5c
extern const Matrix3 kMatrix3Identity;                         // 0x01676d08
extern RandomLinearCongruential sRandom;                       // 0x016778dc

// ---- items of slice s00a74260 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memset(void* p, int c, unsigned int n);                // 0x011e073e
extern const char* const kComponentTypeNames[];                                   // 0x01456334 (kFXCmptVisualEffect, ...)
extern const char kAllWorlds[];                                                   // 0x01401b58 "*"
#pragma function(memset)
void operator delete[](void* p);                                                  // 0x00f47380
namespace EA {
namespace ArgScript {
struct ArgParser;
}
}
namespace EA {
namespace ArgScript {
struct Line;
}
}
namespace EA {
namespace ArgScript {
void __cdecl Output_s00a7_4260(ArgParser* parser, const char* fmt, ...);                     // 0x00841000
}
}
using EA::ArgScript::ArgParser;
struct EAString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
    EAString() { mpBegin = mpEnd = gEmptyString; mpCapacity = gEmptyString + 1; }
    ~EAString() { DeallocateSelf(); }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(char* p) { if (p) operator delete[](p); }
    const char* c_str() const { return mpBegin; }
    bool empty() const { return mpBegin == mpEnd; }
};
namespace EA {
namespace ArgScript {
void __cdecl Sprintf(EAString* out, const char* fmt, ...);                        // 0x00840c20
}
}
struct EnumName { const char* mpName; int mValue; };
const char* __cdecl GetEnumName(int value, const EnumName* table);               // 0x00840810
extern const EnumName kWorldStateNames[];                                         // 0x01554938 (active, paused, ...)
bool __cdecl OpenEffectFile(const char* path);                                    // 0x00a72f70
struct cEffectStats {                       // 0x4c bytes, filled by IEffectStats::GetStats
    int m00;
    int mNumEffects;                        // +0x04
    int mNumComponents;                     // +0x08
    int m0c;
    int mNumQuads;                          // +0x10 (column "quad")
    int m14;
    int mNumModels;                         // +0x18
    int m1c;
    int m20;
    int mNumMeta;                           // +0x24 (column "meta")
    int mNumDecals;                         // +0x28
    int m2c;
    int mNumRibbons;                        // +0x30
    int pad[(0x4c - 0x34) / 4];
};
struct IEffectStats {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void GetStats(float t, float dt, cEffectStats* stats);               // +0x14
};
struct cVisualEffect_s00a7_4260 {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void Stop(int hard);                                                  // +0x0c 0x00a82050
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual bool IsPaused();                                                      // +0x34
    virtual bool IsHidden();                                                      // +0x38
    IEffectStats mStats;                                                          // +0x04
    char pad8[0x10 - 8];
    int mRefCount;                                                                // +0x10
    char pad14[0x2c - 0x14];
    uint32_t mFlags;                                                              // +0x2c
    bool HasFlag(int bit) const { return (mFlags >> bit) & 1; }
};
struct cEffectInfo {                        // 0x24 bytes
    EAString mName;                         // +0x00
    EAString mDescription;                  // +0x10
    cVisualEffect_s00a7_4260* mpEffect;                // +0x20
    ~cEffectInfo();                                                               // 0x007e1a80
};
cEffectInfo* __cdecl CopyEffectInfos(cEffectInfo* first, cEffectInfo* last, cEffectInfo* dest);   // 0x00a6d8c0
struct EffectAllocator {
    void deallocate(void* p) { if (((int*)p)[-1] != 0) operator delete[](p); }
};
struct EffectList {
    cEffectInfo* mpBegin;
    cEffectInfo* mpEnd;
    cEffectInfo* mpCapacity;
    EffectAllocator mAllocator;
    EffectList() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~EffectList() {
        DoDestroyValues(mpBegin, mpEnd);
        DoFree(mpBegin);
    }
    void DoDestroyValues(cEffectInfo* first, cEffectInfo* last);                 // 0x007e2be0
    void DoFree(cEffectInfo* p) { if (p) mAllocator.deallocate(p); }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    cEffectInfo* erase(cEffectInfo* first, cEffectInfo* last) {
        cEffectInfo* const pPosition = CopyEffectInfos(last, mpEnd, first);
        DoDestroyValues(pPosition, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};
struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};
struct cEffectFileInfo {
    EAString mName;
    EAString mPath;
    IRefCounted* mpObject;
    cEffectFileInfo() : mpObject(0) {}
    ~cEffectFileInfo() { if (mpObject) mpObject->Release(); }
};
struct cEffectsWorld {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void SetTarget(int v);                                                // +0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16();
    virtual void GetEffects(EffectList* out, const char* filter, int mode);       // +0x44
    char pad4[0x20 - 4];
    int mState;                                                                   // +0x20
    char pad24[0x90 - 0x24];
    int mNumEffects;                                                              // +0x90
};
struct WorldNode {
    uint32_t mKey;
    cEffectsWorld* mpWorld;
    WorldNode* mpNext;
};
struct WorldIterator {
    WorldNode* mpNode;
    WorldNode** mpBucket;
    WorldIterator(WorldNode** pBucket) : mpNode(*pBucket), mpBucket(pBucket) {}
    void increment_bucket() {
        ++mpBucket;
        while (*mpBucket == 0)
            ++mpBucket;
        mpNode = *mpBucket;
    }
    void increment() {
        mpNode = mpNode->mpNext;
        while (mpNode == 0)
            mpNode = *++mpBucket;
    }
    bool operator!=(const WorldIterator& x) const { return mpNode != x.mpNode; }
};
struct WorldTable {
    uint32_t m0;
    WorldNode** mpBucketArray;                                                    // +0x04
    uint32_t mnBucketCount;                                                       // +0x08
    WorldIterator begin() {
        WorldIterator i(mpBucketArray);
        if (!i.mpNode)
            i.increment_bucket();
        return i;
    }
    WorldIterator end() { return WorldIterator(mpBucketArray + mnBucketCount); }
};
struct PtrVector {                          // eastl::vector<T*>, 0x14 bytes
    void** mpBegin; void** mpEnd; void** mpCapacity; uint32_t mAlloc[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
struct cEffectDescription { char data[0x58]; };
struct DescVector {                         // eastl::vector<cEffectDescription>
    cEffectDescription* mpBegin; cEffectDescription* mpEnd; cEffectDescription* mpCapacity; uint32_t mAlloc[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};
struct cCollection {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual bool IsCompiled();                                                    // +0x38
    char pad4[0xc - 4];
    PtrVector* mComponentDescriptions;                                            // +0x0c (begin of a vector<PtrVector>)
    char pad10[0x34 - 0x10];
    DescVector mEffectDescriptions;                                               // +0x34
};
struct CollectionVector {
    cCollection** mpBegin;
    cCollection** mpEnd;
    cCollection** mpCapacity;
    uint32_t mAlloc[2];
    int size() const { return (int)(mpEnd - mpBegin); }
    cCollection*& operator[](int i) { return mpBegin[i]; }
};
struct ResourceKey { uint32_t mInstance, mGroup; };
struct cCollectionDirectory {
    virtual void v0(); virtual void v1();
    virtual bool FindKey(int type, const char* name, ResourceKey* key);           // +0x08
};
struct cResourceCache {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual IRefCounted* GetResource(ResourceKey key);                            // +0x10
};
struct cEffectsManager_s00a7_4260 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual cResourceCache* GetResourceCache();                                   // +0x14
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13();
    virtual void SetQuality(float q, int which);                                  // +0x38
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void StartRecording(int id, const char* source);                      // +0x4c
    virtual void StopRecording(int id);                                           // +0x50
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void LoadCollection(IRefCounted* c);                                  // +0x64
    virtual bool UnloadCollection(IRefCounted* c);                                // +0x68
    virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36();
    virtual void v37();
    virtual void SetDebugMode(int mode, bool on);                                 // +0x98
    virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42();
    virtual const char* GetStatusString();                                        // +0xac
    virtual void v44();
    virtual void GetEffects(EffectList* out, const char* world, bool all);        // +0xb4
    virtual bool GetEffectFile(cEffectFileInfo* out, const char* world);          // +0xb8
    virtual void GetEffectNames(EffectList* out, const char* world);              // +0xbc
    char pad4[0x2c - 4];
    CollectionVector mCollections;                                                // +0x2c
    char pad40[0x48 - 0x40];
    cCollectionDirectory* mpDirectory;                                            // +0x48
    char pad4c[0x1e0 - 0x4c];
    uint8_t mParams[3];                                                           // +0x1e0
    char pad1e3[0x1e8 - 0x1e3];
    uint8_t mParam1e8;                                                            // +0x1e8
    char pad1e9[0x224 - 0x1e9];
    WorldTable mWorlds;                                                           // +0x224
    char pad230[0x244 - 0x230];
    cEffectsWorld* mpDefaultWorld;                                                // +0x244
    void StopAllEffects();                                                        // 0x00a6d480
    cEffectsWorld* FindWorld(const char* name);                                   // 0x00a6d840
};
namespace EA {
namespace ArgScript {
struct cArgumentSpec_s00a7_4260 {
    void Parse(const Line& line, ArgParser* parser);                              // 0x0083b9d0
};
}
}
namespace EA {
namespace Swarm {
class cEffectsManagerCheat {
public:
    virtual void v0();
    void Execute(const EA::ArgScript::Line& line);
    bool IsSet(int bit) const { return (mOptionBits >> bit) & 1; }

    ArgParser* mpParser;                    // +0x04
    char pad8[0x10 - 8];
    cEffectsManager_s00a7_4260* mpManager;             // +0x10
    EA::ArgScript::cArgumentSpec_s00a7_4260 mArgSpec;  // +0x14
    char pad15[0x84 - 0x15];
    uint32_t mOptionBits;                   // +0x84
    char pad88[0xdc - 0x88];
    const char* mpWorldName;                // +0xdc
    uint8_t mParams[4];                     // +0xe0
    int mDebugMode;                         // +0xe4
    bool mDebugOn;                          // +0xe8
    float mQuality;                         // +0xec
    int mTarget;                            // +0xf0
    int mRecordId;                          // +0xf4
    const char* mpSource;                   // +0xf8
    const char* mpCollectionName;           // +0xfc
};
}
}
// ---- items of slice s00a74260 end

// @ 0x00a73110
void cEffectCheat::ParseLine(const cArguments& args)
{
    mEffectName = 0;
    mModel = kDebug;
    mTexture = kDebug;
    mPosition = kVector3Zero;
    mID = 0;
    mWorldName = 0;
    mOverrideSet = -1;
    mOverrideNames.clear();
    mOverrideSets.clear();
    mFloatParams.clear();
    mIntParams.clear();

    mArgSpec.Parse(args, mpFormatParser);

    cIEffectWorld* world = mManager->GetWorld(mWorldName);
    cITerrainQuery* terrain = mManager->GetTerrainQuery(0, 0);

    if (mEffectName) {
        if (mID >= mTestEffects.size()) {
            mTestEffects.resize(mID + 1);
        } else if (mTestEffects[mID]) {
            mTestEffects[mID]->SetIsPaused(false);
            if (Flag(kHard))
                mTestEffects[mID]->Stop(1);
            else if (Flag(kSoft))
                mTestEffects[mID]->Stop(0);
            else
                mTestEffects[mID]->Stop(0);
            mTestEffects[mID].reset();
        }

        EffectKey key;
        if (mManager->mpResources && mManager->mpResources->FindKey(0x12, mEffectName, &key) &&
            mManager->HasEffect(key)) {
            EffectPtr& slot = mTestEffects[mID];
            slot.reset();
            world->CreateEffect(key, &slot);
        }

        if (mTestEffects[mID] && !Flag(kHasPosition) && terrain) {
            BoundingBox box;
            terrain->GetBoundingBox(&box);
            mPosition.x = (box.mMin.x + box.mMax.x) * 0.5f;
            mPosition.y = (box.mMin.y + box.mMax.y) * 0.5f;
            mArgSpec.mFlags |= 1 << kHasPosition;
        }
    }

    if (Flag(kHasPosition) && mID < mTestEffects.size() && mTestEffects[mID]) {
        if (!Flag(kPositionHasHeight) && terrain && terrain->HasHeightAt(&mPosition))
            mPosition.z = terrain->GetHeightAt(&mPosition);
        Transform t;
        t.SetOffset(mPosition);
        mTestEffects[mID]->SetSourceTransform(t);
    }

    if (Flag(kHasScale) && mTestEffects[mID]) {
        Transform t(kVector3Zero, 1.0f, kMatrix3Identity);
        float scale = mScale;
        t.SetScale(scale);
        Vector3 offset = (mPosition - (mPosition * scale) * t.mRotation) + t.mOffset;
        t.SetOffset(offset.x, offset.y, offset.z);
        mTestEffects[mID]->SetRigidTransform(t);
    }

    if (Flag(kEdit) && mEffectName) {
        EffectFileInfo info;
        if (mManager->GetEffectFileInfo(&info, mEffectName) && !info.mFile.empty()) {
            string fileName(info.mFile);
            string subName;
            unsigned int pos = fileName.rfind(':', (unsigned int)-1);
            if (pos != (unsigned int)-1) {
                subName = fileName.substr(pos + 1, (unsigned int)-1);
                fileName.erase(pos, (unsigned int)-1);
            }
            if (!OpenEffectsFile(fileName.c_str(), subName.c_str()))
                Output(mpFormatParser, "Couldn't open '%s'\n", fileName.c_str(), subName.c_str());
        }
    }

    if (mID >= mTestEffects.size())
        return;
    cIVisualEffect* effect = mTestEffects[mID];
    if (!effect)
        return;

    if (Flag(kSetFloatParams))
        effect->SetFloatParams(mFloatParam, mFloatParams.mpBegin, mFloatParams.size());
    if (Flag(kSetIntParams))
        mTestEffects[mID]->SetIntParams(mIntParam, mIntParams.mpBegin, mIntParams.size());

    if (Flag(kModelOverride)) {
        if (!mManager->mpResources)
            return;
        if (!mOverrideNames.empty()) {
            if (mOverrideNames.size() != mOverrideSets.size())
                return;
            IntVector data(mOverrideNames.size() * 2);
            int n = mOverrideNames.size();
            for (int i = 0; i < n; i++) {
                EffectKey key;
                key.instanceID = (unsigned int)-1;
                key.groupID = (unsigned int)-1;
                mManager->mpResources->FindKey(2, mOverrideNames[i].c_str(), &key);
                data[i * 2] = key.instanceID;
                data[i * 2 + 1] = mOverrideSets[i];
            }
            mTestEffects[mID]->SetIntParams(0, data.data(), data.size());
        } else {
            EffectKey key;
            key.instanceID = (unsigned int)-1;
            key.groupID = (unsigned int)-1;
            mManager->mpResources->FindKey(2, mModel, &key);
            int data[2];
            data[0] = key.instanceID;
            data[1] = mOverrideSet;
            mTestEffects[mID]->SetIntParams(0, data, (mOverrideSet >= 0) + 1);
        }
    }

    if (Flag(kTextureOverride)) {
        if (!mManager->mpResources)
            return;
        if (!mOverrideNames.empty()) {
            if (mOverrideNames.size() != mOverrideSets.size())
                return;
            IntVector data(mOverrideNames.size() * 2);
            int n = mOverrideNames.size();
            for (int i = 0; i < n; i++) {
                EffectKey key;
                key.instanceID = (unsigned int)-1;
                key.groupID = (unsigned int)-1;
                mManager->mpResources->FindKey(0, mOverrideNames[i].c_str(), &key);
                data[i * 2] = key.instanceID;
                data[i * 2 + 1] = mOverrideSets[i];
            }
            mTestEffects[mID]->SetIntParams(1, data.data(), data.size());
        } else {
            EffectKey key;
            key.instanceID = (unsigned int)-1;
            key.groupID = (unsigned int)-1;
            mManager->mpResources->FindKey(0, mTexture, &key);
            int data[2];
            data[0] = key.instanceID;
            data[1] = mOverrideSet;
            mTestEffects[mID]->SetIntParams(1, data, (mOverrideSet >= 0) + 1);
        }
    }

    if (Flag(kSetFrame))
        mTestEffects[mID]->SetIntParams(2, &mFrame, 1);
    if (Flag(kSetState))
        mTestEffects[mID]->SetIntParams(3, &mStateIndex, 1);
    if (Flag(kSetHidden))
        mTestEffects[mID]->SetIsHidden(mHidden);
    if (Flag(kSetPaused))
        mTestEffects[mID]->SetIsPaused(mPaused);

    if (mEffectName || Flag(kStart)) {
        if (Flag(kSetSeed))
            sRandom.SetSeed(mSeed);
        if (Flag(kHard))
            mTestEffects[mID]->Start(1);
        else if (Flag(kSoft))
            mTestEffects[mID]->Start(0);
        else
            mTestEffects[mID]->Start(0);
    }

    if (args.NumArguments() < 2 || Flag(kStop)) {
        if (Flag(kHard))
            mTestEffects[mID]->Stop(1);
        else if (Flag(kSoft))
            mTestEffects[mID]->Stop(0);
        else
            mTestEffects[mID]->Stop(0);
    }

    if (Flag(kClear))
        mTestEffects[mID].reset();
}

// @ 0x00a74260
namespace EA { namespace Swarm {
void cEffectsManagerCheat::Execute(const EA::ArgScript::Line& line)
{
    mpWorldName = 0;
    mpCollectionName = 0;
    mRecordId = 0;
    mpSource = 0;
    mArgSpec.Parse(line, mpParser);

    if (IsSet(0))
        Output_s00a7_4260(mpParser, "%s\n", mpManager->GetStatusString());

    if (IsSet(3) || IsSet(4)) {
        EffectList effects;
        int mode = 0;
        if (IsSet(5))
            mode = 1;
        if (IsSet(6))
            mode = 2;
        WorldIterator it = mpManager->mWorlds.begin();
        WorldIterator itEnd = mpManager->mWorlds.end();
        for (; it != itEnd; it.increment()) {
            cEffectsWorld* world = it.mpNode->mpWorld;
            if (world->mState != 0 && !IsSet(4))
                continue;
            effects.clear();
            world->GetEffects(&effects, mpWorldName, mode);
            if (effects.mpBegin != effects.mpEnd || IsSet(4)) {
                Output_s00a7_4260(mpParser, "world 0x%08x [%s]%s:\n", it.mpNode->mKey,
                       GetEnumName(world->mState, kWorldStateNames),
                       world != mpManager->mpDefaultWorld ? "" : " [default]");
                Output_s00a7_4260(mpParser, " %-60.60s  %-5s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n", "effect name",
                       "sim_ms", "effects", "cmpts", "meta", "quad", "model", "decal", "ribbon");
            }
            for (uint32_t i = 0; i < effects.size(); i++) {
                cVisualEffect_s00a7_4260* effect = effects.mpBegin[i].mpEffect;
                cEffectStats stats;
                memset(&stats, 0, sizeof(stats));
                effect->mStats.GetStats(0.0f, 0.0f, &stats);
                const char* paused = "";
                const char* hidden = "";
                const char* stopping = "";
                const char* orphan = "";
                const char* kind = "";
                if (effect->IsPaused())
                    paused = "[Paused]";
                if (effect->IsHidden())
                    hidden = "[Hidden]";
                if (effect->HasFlag(10))
                    stopping = "[Stopping]";
                if (effect->mRefCount <= 2)
                    orphan = "[Orphan]";
                if (effect->HasFlag(6))
                    kind = "[Internal]";
                else if (effect->HasFlag(5))
                    kind = "[Child]";
                Output_s00a7_4260(mpParser, "  %-60.60s %1.3f %5d %5d %5d %5d %5d %5d %5d %s%s%s%s%s\n",
                       effects.mpBegin[i].mName.c_str(), 0.0, stats.mNumEffects, stats.mNumComponents,
                       stats.mNumMeta, stats.mNumQuads, stats.mNumModels, stats.mNumDecals, stats.mNumRibbons,
                       paused, hidden, stopping, orphan, kind);
            }
        }
    }

    if (IsSet(7) || IsSet(8)) {
        bool verbose = IsSet(8);
        EffectList effects;
        mpManager->GetEffectNames(&effects, mpWorldName);
        for (uint32_t i = 0; i < effects.size(); i++) {
            Output_s00a7_4260(mpParser, " %s\n", effects.mpBegin[i].mName.c_str());
            if (verbose && !effects.mpBegin[i].mDescription.empty())
                Output_s00a7_4260(mpParser, "    %s\n", effects.mpBegin[i].mDescription.c_str());
        }
        if (effects.size() > 1)
            Output_s00a7_4260(mpParser, "%d total effects\n", effects.size());
    }

    if (IsSet(9)) {
        cEffectFileInfo info;
        if (mpManager->GetEffectFile(&info, mpWorldName) && !info.mPath.empty() &&
            !OpenEffectFile(info.mPath.c_str()))
            Output_s00a7_4260(mpParser, "Couldn't open '%s'\n", info.mPath.c_str());
    }

    if (IsSet(1)) {
        if (mpWorldName == 0)
            mpManager->StopAllEffects();
        else {
            EffectList effects;
            mpManager->GetEffects(&effects, mpWorldName, true);
            for (uint32_t i = 0; i < effects.size(); i++)
                effects.mpBegin[i].mpEffect->Stop(1);
        }
    }

    if (IsSet(2)) {
        if (mpWorldName == 0)
            mpManager->StopAllEffects();
        else {
            EffectList all;
            EffectList inWorld;
            mpManager->GetEffects(&all, kAllWorlds, true);
            mpManager->GetEffects(&inWorld, mpWorldName, true);
            for (uint32_t i = 0; i < all.size(); i++) {
                bool found = false;
                for (uint32_t j = 0; j < inWorld.size(); j++) {
                    if (all.mpBegin[i].mpEffect == inWorld.mpBegin[j].mpEffect) {
                        found = true;
                        break;
                    }
                }
                if (!found)
                    all.mpBegin[i].mpEffect->Stop(1);
            }
        }
    }

    if (IsSet(25))
        mpManager->mParams[0] = mParams[0];
    if (IsSet(26))
        mpManager->mParams[1] = mParams[1];
    if (IsSet(27))
        mpManager->mParams[2] = mParams[2];
    if (IsSet(24))
        mpManager->mParam1e8 = mParams[3];
    if (IsSet(12))
        mpManager->SetDebugMode(mDebugMode, mDebugOn);
    if (IsSet(13))
        mpManager->SetQuality(mQuality, 5);

    if (IsSet(15)) {
        WorldIterator it = mpManager->mWorlds.begin();
        WorldIterator itEnd = mpManager->mWorlds.end();
        for (; it != itEnd; it.increment()) {
            cEffectsWorld* world = it.mpNode->mpWorld;
            Output_s00a7_4260(mpParser, "world 0x%08x, %d effects, %s %s\n", it.mpNode->mKey, world->mNumEffects,
                   GetEnumName(world->mState, kWorldStateNames),
                   world != mpManager->mpDefaultWorld ? "" : "[default]");
        }
    }

    if (IsSet(11)) {
        cEffectsWorld* world = mpManager->FindWorld(mpSource);
        if (world)
            world->SetTarget(mTarget);
    }
    if (IsSet(16))
        mpManager->StartRecording(mRecordId, mpSource ? mpSource : "CommandLine");
    if (IsSet(17))
        mpManager->StopRecording(mRecordId);

    if (IsSet(18)) {
        int n = mpManager->mCollections.size();
        for (int i = 0; i < n; i++) {
            if (mpManager->mCollections[i]) {
                for (int type = 0; type < 64; type++) {
                    uint32_t count;
                    if (type >= 1)
                        count = mpManager->mCollections[i]->mComponentDescriptions[type - 1].size();
                    else if (type == 0)
                        count = mpManager->mCollections[i]->mEffectDescriptions.size();
                    else
                        count = 0;
                    if (count > 0) {
                        if ((uint32_t)type < 15)
                            Output_s00a7_4260(mpParser, "%-20.20s descriptions = %4d\n", kComponentTypeNames[type], count);
                        else
                            Output_s00a7_4260(mpParser, "cmpt%02d               descriptions = %4d\n", type, count);
                    }
                }
            }
        }
    }

    if (IsSet(19)) {
        EAString s;
        EA::ArgScript::Sprintf(&s, "Manager version: %d,  Script version: %d", 1, 1);
        Output_s00a7_4260(mpParser, "%s\n", s.c_str());
    }

    if (IsSet(20)) {
        int n = mpManager->mCollections.size();
        for (int i = 0; i < n; i++) {
            if (mpManager->mCollections[i] && mpManager->mCollections[i]->IsCompiled())
                Output_s00a7_4260(mpParser, "compiled 0x%08x\n", mpManager->mCollections[i]);
        }
    }

    if (IsSet(21)) {
        ResourceKey key;
        if (mpManager->mpDirectory && mpManager->mpDirectory->FindKey(0x11, mpCollectionName, &key)) {
            IRefCounted* collection = mpManager->GetResourceCache()->GetResource(key);
            if (collection) {
                collection->AddRef();
                mpManager->LoadCollection(collection);
                collection->Release();
            } else
                Output_s00a7_4260(mpParser, "Couldn't load effect collection: %s\n", mpCollectionName);
        } else
            Output_s00a7_4260(mpParser, "No such collection: %s\n", mpCollectionName);
    }

    if (IsSet(22)) {
        ResourceKey key;
        if (mpManager->mpDirectory && mpManager->mpDirectory->FindKey(0x11, mpCollectionName, &key)) {
            IRefCounted* collection = mpManager->GetResourceCache()->GetResource(key);
            if (collection) {
                collection->AddRef();
                if (!mpManager->UnloadCollection(collection))
                    Output_s00a7_4260(mpParser, "Collection not loaded: %s\n", mpCollectionName);
                collection->Release();
            } else
                Output_s00a7_4260(mpParser, "Couldn't unload collection: %s\n", mpCollectionName);
        } else
            Output_s00a7_4260(mpParser, "No such collection: %s\n", mpCollectionName);
    }

    if (IsSet(23)) {
        int n = mpManager->mCollections.size();
        for (int i = 0; i < n; i++) {
            if (mpManager->mCollections[i])
                Output_s00a7_4260(mpParser, "collection 0x%08x\n", mpManager->mCollections[i]);
        }
    }
}
}}  // namespace EA::Swarm
