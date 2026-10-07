// Slice 11: nSPSkinner paint-request setters/factories and related helpers.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

void* EA_alloc(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void* FUN_00507c70(void* p);              // 0x00507c70
void* FUN_00529d30(void* p);              // 0x00529d30
void  FUN_00523690(void* self);           // 0x00523690
void  RefCountTemplate_Release(void* p);  // 0x00453540

extern float g_userColors[3];             // 0x015df0f0
extern float g_userColors2[3];            // 0x015df204

struct PaintReq {
    void Set(int a2, int a3, int a4, int a5, char a6, char a7, char a8);
};
struct Factory {
    void* Make();
};

// @ 0x00522ad0
void PaintReq::Set(int a2, int a3, int a4, int a5, char a6, char a7, char a8)
{
    *(int*)((char*)this + 0x68) = a2;
    *(int*)((char*)this + 0x6c) = a3;
    *(int*)((char*)this + 0x70) = a4;
    *(int*)((char*)this + 0x74) = a5;
    *(char*)((char*)this + 0x78) = a6;
    *(char*)((char*)this + 0x79) = a7;
    *(char*)((char*)this + 0x7a) = a8;
}

// @ 0x00523570
void* Factory::Make()
{
    void* mem = EA_alloc(0x1d0, "Skinner", 0, 0, 0, 0);
    void* result;
    if (mem != 0)
        result = FUN_00507c70(this);
    else
        result = 0;
    return result;
}

// @ 0x005229c0
void FUN_005229c0(int idx, float* v)
{
    int* g1 = (int*)((char*)g_userColors + idx * 0xc);
    g1[0] = *(int*)&v[0];
    g1[1] = *(int*)&v[1];
    g1[2] = *(int*)&v[2];
    float tmp[3];
    tmp[0] = v[0];
    tmp[1] = v[1];
    tmp[2] = v[2];
    int* r = (int*)FUN_00529d30(tmp);
    int* g2 = (int*)((char*)g_userColors2 + idx * 0xc);
    g2[0] = r[0];
    g2[1] = r[1];
    g2[2] = r[2];
}

// @ 0x00522800 -- PARTIAL skeleton (444-byte /Od body not reconstructed)
void FUN_00522800(void* self) { (void)self; }
// @ 0x005235c0 -- PARTIAL skeleton (203-byte /Od body not reconstructed)
void FUN_005235c0(void* self) { (void)self; }
// @ 0x00522a40 -- PARTIAL skeleton (135-byte /Od body: request complete + release)
void FUN_00522a40(void* self) { (void)self; }

// ---------------------------------------------------------------------------
// nSPSkinner::cPaintSystem::SetCreatureSkin (0x00522b40)
// ---------------------------------------------------------------------------
#pragma intrinsic(fabs)
extern "C" double __cdecl fabs(double);

namespace nSPSkinner {

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& Set(const Vector3& o);                       // 0x004098a0
};
struct Matrix3 { float m[9]; };

Vector3 operator+(const Vector3& a, const Vector3& b);   // 0x0041dc10
Vector3 operator*(const Vector3& v, const float& s);     // 0x0041dca0
Vector3& operator*=(Vector3& v, const float& s);         // 0x0041dba0
Vector3 operator*(const Vector3& v, const Matrix3& m);   // 0x0041daf0
Vector3& operator+=(Vector3& v, const Vector3& o);       // 0x0041ddb0

inline float Fabsf(float f) { return (float)fabs(f); }
inline float Abs(float f) { return Fabsf(f); }

template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

class RefCounted {
public:
    virtual ~RefCounted();
    int AddRef() { return mnRefCount++ + 1; }
    int Release();                                        // 0x00453540
    int mnRefCount;
};

template<class T> class AutoRefCount {
public:
    T* mpObject;
    T* operator->() const { return mpObject; }
    AutoRefCount& Assign(T* pObject);                     // 0x0041cc60
    AutoRefCount& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

struct cMesh : RefCounted {
    cMesh* Clone();                                       // 0x00523570
};
struct cMeshAORender {
    void Rebuild();                                       // 0x00516eb0
};

struct cBone {                                            // size 0x8c
    uint32_t pad0;
    short mParent;                                        // +0x04
    uint8_t pad6[5];
    uint8_t mType;                                        // +0x0b
    uint32_t padc[2];
    Vector3 mStart;                                       // +0x14
    Vector3 mEnd;                                         // +0x20
    float mfScale;                                        // +0x2c
    Matrix3 mRotation;                                    // +0x30
    Vector3 mPosition;                                    // +0x54
    uint32_t pad60[4];
    float mfLength;                                       // +0x70
    uint32_t pad74[6];
};

template<class T> struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    void* mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int n) { return mpBegin[n]; }
    void resize(int n);
};

struct cCreatureResource {
    uint32_t pad[0x26];
    sp_vector<cBone> mBones;                              // +0x98
};

struct cPropertyList {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t id);                // 0x1c
    bool GetBool(uint32_t id);                            // 0x006a25a0
};

struct cSkinObject {
    uint32_t pad[2];
    AutoRefCount<cCreatureResource> mpResource;          // +0x08
    sp_vector<cPropertyList*> mBlockProps;                // +0x0c
    uint32_t pad1c[6];
    AutoRefCount<cMesh> mpMesh;                           // +0x34
};

struct cBoneInfo {                                        // size 0x40
    char mParent;                                         // +0x00
    char mChain;                                          // +0x01
    char mNumChildren;                                    // +0x02
    char mFlags;                                          // +0x03
    Vector3 mPosition;                                    // +0x04
    Matrix3 mRotation;                                    // +0x10
    float mfWeight;                                       // +0x34
    float mfStart;                                        // +0x38
    float mfEnd;                                          // +0x3c
};

extern sp_vector<cBoneInfo> g_boneInfos;                 // 0x015de470
struct ChainWeight { float operator()(int bone); };       // 0x005235c0

struct cPaintOutput {
    uint32_t pad[5];
    int mnPending;                                        // +0x14
    uint32_t pad18;
    int mnDone;                                           // +0x1c
    void Reset();                                         // 0x006909b0
};

extern AutoRefCount<cPropertyList> g_appProperties;      // 0x015fd918

class cPaintSystem {
public:
    void SetCreatureSkin(cSkinObject* skin, bool keepMesh);
    bool ShouldTick();                                    // 0x00522720
    void FinishTick();                                    // 0x00523690
    void RebuildBones();                                  // 0x005241e0

    uint32_t pad0[4];
    AutoRefCount<cMesh> mpBakedMesh;                      // +0x10
    AutoRefCount<cMeshAORender> mpMeshAORender;           // +0x14
    uint32_t pad18[2];
    cSkinObject* mpEditorSkinPart;                        // +0x20
    uint32_t pad24[0x11];
    int mOutputDiffuseGroup;                              // +0x68
    int mOutputNormSpecGroup;                             // +0x6c
    int mDXTQuality;                                      // +0x70
    int mOutputIndex;                                     // +0x74
    bool mb78;                                            // +0x78
    bool mb79;                                            // +0x79
    bool mb7a;                                            // +0x7a
    bool mb7b;                                            // +0x7b
    bool mb7c;                                            // +0x7c
    bool mb7d;                                            // +0x7d
    bool mbHighQuality;                                   // +0x7e
    uint8_t pad7f;
    uint32_t pad80[0x1f];
    AutoRefCount<cPaintOutput> mpOutput;                  // +0xfc
};

// @ 0x00522b40
void cPaintSystem::SetCreatureSkin(cSkinObject* skin, bool keepMesh)
{
    if (ShouldTick())
        FinishTick();
    mOutputDiffuseGroup = 0;
    mOutputNormSpecGroup = 0;
    mDXTQuality = 0;
    mOutputIndex = -1;
    mb78 = false;
    mb7a = false;
    mb7b = false;
    mpEditorSkinPart = skin;

    if (skin) {
        if (keepMesh) {
            mpBakedMesh.Assign(skin->mpMesh.mpObject);
            skin->mpMesh = 0;
        } else {
            cMesh* pMesh = skin->mpMesh.mpObject;
            mpBakedMesh = pMesh->Clone();
        }

        int lastChain = -1;
        int lastLeaf = -1;
        cBone* bones = skin->mpResource->mBones.mpBegin;
        int count = skin->mpResource->mBones.size();
        g_boneInfos.resize(count);

        for (int i = 0; i < count; ++i) {
            cBone* b = &bones[i];
            if (b->mType != 5 && b->mType != 3)
                break;
            g_boneInfos.mpBegin[i].mFlags = 0;
            g_boneInfos.mpBegin[i].mfStart = 0.0f;
            g_boneInfos.mpBegin[i].mfEnd = 0.0f;
            if (b->mType == 5) {
                Vector3 v = (b->mStart + b->mEnd) * 0.5f;
                v *= b->mfScale;
                v.Set(v * b->mRotation);
                v += b->mPosition;
                g_boneInfos.mpBegin[i].mParent = (char)(i - 1);
                g_boneInfos.mpBegin[i].mChain = (char)i;
                g_boneInfos.mpBegin[i].mNumChildren = -1;
                g_boneInfos.mpBegin[i].mfWeight = 1.0f;
                g_boneInfos.mpBegin[i].mPosition = v;
                g_boneInfos.mpBegin[i].mRotation = b->mRotation;
                lastChain = i;
            } else {
                int parent = b->mParent;
                if (parent != -1 && parent < i && bones[parent].mType == 3) {
                    g_boneInfos[parent].mNumChildren++;
                    g_boneInfos.mpBegin[i].mParent = (char)parent;
                } else {
                    g_boneInfos.mpBegin[i].mParent = -1;
                }
                g_boneInfos.mpBegin[i].mChain =
                    (lastChain != -1 && parent != -1) ? g_boneInfos.mpBegin[parent].mChain : -1;
                g_boneInfos.mpBegin[i].mNumChildren = 0;
                g_boneInfos.mpBegin[i].mfWeight = Abs(b->mfLength) + 1e-08f;
                g_boneInfos.mpBegin[i].mPosition = b->mPosition;
                g_boneInfos.mpBegin[i].mRotation = b->mRotation;
                lastLeaf = i;
            }
        }

        const int& last = Max(lastChain, lastLeaf);
        g_boneInfos.resize(last + 1);

        for (int j = g_boneInfos.size(); j < count; ++j) {
            cPropertyList* props = skin->mBlockProps[j];
            if (props->HasProperty(0xb00f0fef)) {
                for (int k = bones[j].mParent; k != -1; k = bones[k].mParent) {
                    if (bones[k].mType == 3)
                        g_boneInfos[k].mFlags |= 1;
                }
            } else if (props->HasProperty(0xb00f0fe2) || props->HasProperty(0xb00f0ff4)
                       || props->HasProperty(0xb00f0ff7) || props->HasProperty(0xb00f0ff2)) {
                for (int k = bones[j].mParent; k != -1; k = bones[k].mParent) {
                    if (bones[k].mType == 3)
                        g_boneInfos[k].mFlags |= 2;
                }
            }
        }

        RebuildBones();

        if (lastChain < g_boneInfos.size()) {
            float inv = 1.0f / (float)(lastChain + 1);
            for (int k = 0; k <= lastChain; ++k) {
                g_boneInfos.mpBegin[k].mfStart = (float)k * inv;
                g_boneInfos.mpBegin[k].mfEnd = (float)(k + 1) * inv;
            }
        }

        for (int k = 0, n = g_boneInfos.size(); k < n; ++k) {
            if (g_boneInfos.mpBegin[k].mNumChildren == -1)
                continue;
            ChainWeight weight;
            int parent = g_boneInfos.mpBegin[k].mParent;
            float start = (parent < 0) ? 0.0f : g_boneInfos.mpBegin[parent].mfEnd;
            g_boneInfos.mpBegin[k].mfStart = start;
            g_boneInfos[k].mfEnd = start + (1.0f - start) * (g_boneInfos[k].mfWeight / weight(k));
        }

        mpOutput->mnPending = 1;
        mpOutput->mnDone = 0;
        mpOutput->Reset();
        mb7c = false;
        mb7d = false;
        mbHighQuality = g_appProperties->GetBool(0x2853e342);
    } else {
        mpBakedMesh = 0;
        mpMeshAORender->Rebuild();
        mb7c = false;
        mb7d = false;
        mbHighQuality = false;
    }
}

} // namespace nSPSkinner
