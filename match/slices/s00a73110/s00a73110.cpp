// s00a73110 -- EA::Swarm::cEffectCheat::ParseLine (the "effect" console cheat: start/stop/edit a
// test visual effect, with position/scale/override/param options). /O2 /arch:SSE module.
// Retail layout differs from the 2008 PDB (+0x1c shift, plus an extra int-param pair at +0x18c).
#include "types.h"

extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);   // E8 call (0x011e0744)
void __cdecl operator_delete__(void* p);                                        // 0x00f47380

// ---------------------------------------------------------------------------
// EASTL pieces
// ---------------------------------------------------------------------------
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
// substr's temporary is destroyed out of line in the original (0x00530670)
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

// ---------------------------------------------------------------------------
// math / transform
// ---------------------------------------------------------------------------
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
// row vector times matrix
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

// ---------------------------------------------------------------------------
// Swarm interfaces
// ---------------------------------------------------------------------------
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

// EA::AutoRefCount<cIVisualEffect>
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

// ---------------------------------------------------------------------------
// ArgScript
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x00a73110
// ---------------------------------------------------------------------------
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
