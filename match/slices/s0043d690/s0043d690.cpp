// SP::cSPEditorBlock (ModAPI Editors::EditorRigblock) morph-handle code, editor /Od region.
// 0x0043D690 SetMorphHandleWeight is complete; the other functions of the slice are still
// partial approximations on the stub struct cSPEditorBlockStub (see partial.txt).
#include "types.h"

namespace SP {

struct Vec3 { float x, y, z; };
struct Blk {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void SetState(int a, int b);      // +0x30
    virtual void Refresh();                    // +0x14
};

struct cSPEditorBlockStub {
    char     pad00[0x10];
    void*    mModel;        // +0x10
    char     pad14[0x18 - 0x14];
    void*    p18;           // +0x18
    char     pad1c[0x154 - 0x1c];
    Blk*     slots[3];      // +0x154
    char     pad160[0x1A8 - 0x160];
    uint8_t  f1a8;          // +0x1A8
    char     pad1a9[0x1B0 - 0x1A9];
    int      f1b0;          // +0x1B0
    char     pad1b4[0x330 - 0x1B4];
    int      f330;          // +0x330
    char     pad334[0x3F0 - 0x334];
    void*    p3f0;          // +0x3F0
    char     pad3f4[0x40C - 0x3F4];
    Vec3     v40c;          // +0x40C
    char     pad418[0x43C - 0x418];
    int      f43c;          // +0x43C
    float    f440;          // +0x440
    float    f444;          // +0x444
    char     pad448[0x6CC - 0x448];
    void**   vec6cc;        // +0x6CC
    void**   vec6d0;        // +0x6D0
    char     pad6d4[0xDC8 - 0x6D4];
    uint32_t flags0;        // +0xDC8
    uint32_t flags1;        // +0xDCC

    int  F3d690(int idx, int a3, int a4, char a5, char a6);  // 0043D690
    Vec3* F3e080(Vec3* out);                                 // 0043E080
    bool F3e0f0(int* out);                                   // 0043E0F0
    void F3e2b0();                                           // 0043E2B0
};

bool  Sub_401060(void);                        // 00401060
void  Sub_4809A0(int x);                       // 004809A0
void  Sub_435a10(int a, int b);                // 00435A10
void  Sub_4D570();
void  Sub_37400(int x);
void  Sub_37310(int x, int y);
int   Sub_3c3d0(void* p);
void  Sub_85650();
void* Sub_41DCA0(void* out, void* table, const float* key);
void* Sub_41DAF0(void* out, void* v);
void  Sub_4_85650();

// @ 0x0043E080
Vec3* cSPEditorBlockStub::F3e080(Vec3* out)
{
    void* r = Sub_41DCA0(&v40c, (char*)this + 0x1D8, &v40c.x);
    Vec3* p = (Vec3*)Sub_41DAF0(out, r);
    out->x = p->x;
    out->y = p->y;
    out->z = p->z;
    return out;
}

// @ 0x0043E0F0
bool cSPEditorBlockStub::F3e0f0(int* out)
{
    int n = 0;
    (void)n;
    int count = (int)(vec6d0 - vec6cc);
    if (out == 0 || count <= 0) return false;
    return false;
}

// @ 0x0043E2B0
void cSPEditorBlockStub::F3e2b0()
{
    int count = (int)(vec6d0 - vec6cc);
    f440 = 0.4f;
    f444 = -0.35f;
    if (count > 0) {
        f43c = 0;
        for (int i = 0; i < count; i++) {
            if ((flags0 & 0x800u) == 0 || i != 0) {
                Blk* b = *(Blk**)((char*)vec6cc + i * 4);
                F3d690(i, *(int*)((char*)b + 0xA8), 0, 0, 1);
            }
        }
    }
}


// ======================================================================
// Complete: 0x0043D690 cSPEditorBlock::SetMorphHandleWeight
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (editor /Od region).
// Types follow slice s00441440 (cSPEditorBlock::BuildBlock), retail layout.
// ======================================================================
// Reserves N dwords of /Od frame where the original reserved the frame of an inline
// helper that cl declined to inline.
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }

// Math vector used by the out-of-line operators; user operator= (fld/fstp per component).
struct Vector3 {
    float x, y, z;
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
// Plain vector stored in transforms; converting ctor (movss copies), implicit operator=.
struct Vector3P {
    float x, y, z;
    Vector3P(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
Vector3 operator*(const float& s, const Vector3& v);           // 0x0041DE40
Vector3 operator-(const Vector3& a, const Vector3& b);         // 0x0041DB10
Vector3 operator+(const Vector3& a, const Vector3& b);         // 0x0041DC10

struct Matrix3 { float m[9]; };

// cSPTransform (0x38 bytes)
struct Transform {
    uint16_t mFlags;        // +0x00
    uint16_t mChangeCount;  // +0x02
    Vector3P mOffset;       // +0x04
    float mScale;           // +0x10
    Matrix3 mRotation;      // +0x14

    Transform();                                   // 0x00409930
    Transform& operator=(const Transform& other);  // 0x00537DC0
    void Accumulate(const Transform& other);       // 0x0040CCB0
    void AccumulateScaled(const Transform& other); // 0x0040CD80
    void SetOffset(const Vector3P& offset)
    {
        mOffset = offset;
        mFlags |= 4;
        mChangeCount++;
    }
};

// RenderWare::cMDBoneTransform (0x30 bytes)
struct BoneTransform { float m[12]; };
void BoneTransformToTransform(const BoneTransform* src, Transform* dst);  // 0x00732270

template <int N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    __forceinline bool test(uint32_t n) const
    {
        if (n < N) {
            const uint32_t word = mWord[n >> 5];
            return (word & (1u << (n % 32))) != 0;
        }
        return false;
    }
};

// eastl::fixed_vector<T, N>: three pointers, the overflow allocator, then the inline buffer.
template <class T, int N>
struct fixed_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[3];
    uint32_t mBuffer[(N * sizeof(T)) / 4];

    explicit fixed_vector(unsigned int n);  // 0x0041D510
    ~fixed_vector()
    {
        for (T* p = mpBegin; p < mpEnd; ++p)
            p->~T();
        DoFree();
    }
    void DoFree();                          // 0x00428130
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const;                     // 0x00526430 (ICF-shared)
    T& operator[](int i) { return mpBegin[i]; }
    T* data() { return mpBegin; }
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

class cMWModel;
class IModelWorld {
public:
    virtual int AddRef(); virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60(); virtual void v64();
    virtual void v68(); virtual void v6c(); virtual void v70();
    virtual void MoveToTime(cMWModel* model, uint32_t animID, float time, int animationGroup);   // 0x74
    virtual void v78(); virtual void v7c();
    virtual void GetAnimationRange(cMWModel* model, uint32_t animID, float* start, float* end, int animationGroup);  // 0x80
    virtual int GetNumBones(cMWModel* model);                              // 0x84
    virtual void v88();
    virtual int GetBoneTransforms(cMWModel* model, BoneTransform* dst);    // 0x8c
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4(); virtual void vf8(); virtual void vfc();
    virtual void v100(); virtual void v104();
    virtual Transform* GetMeshTransform(cMWModel* model);                  // 0x108
};

// Graphics::Model
class cMWModel {
public:
    IModelWorld* mpWorld;   // +0x00
    uint32_t mFlags;        // +0x04
    Transform mTransform;   // +0x08
};

class cSPEditorBlock;

class cSPEditorHandle {
public:
    virtual int AddRef();          // 0x00
    virtual int Release();         // 0x04
    virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void Update();         // 0x14
    void UpdatePosition();         // 0x00485650
};

class cSPEditorHandleDeform : public cSPEditorHandle {
public:
    uint32_t pad04[(0x8c - 4) / 4];
    uint32_t mAnimID;               // +0x8c
    uint32_t pad90[(0xb4 - 0x90) / 4];
    cSPEditorHandleDeform* mpSymmetricHandle;  // +0xb4
    uint32_t padb8[(0x180 - 0xb8) / 4];
    float mWeight;                  // +0x180
    void SetWeight(float weight);   // 0x004809A0
};

class cSPEditorBlock {
public:
    uint32_t pad00[0x10 / 4];
    AutoRefCount<cMWModel> mpModel;                  // +0x10
    uint32_t pad14;
    AutoRefCount<IModelWorld> mpModelWorld;          // +0x18
    uint32_t pad1c[(0x48 - 0x1c) / 4];
    Vector3 mPosition;                               // +0x48
    uint32_t pad54[(0x154 - 0x54) / 4];
    AutoRefCount<cSPEditorHandle> mAxisHandles[3];   // +0x154
    uint32_t pad160[(0x1a8 - 0x160) / 4];
    bool field_1A8;                                  // +0x1a8
    uint8_t pad1a9[3];
    uint32_t pad1ac;
    int mSelectedMorphHandle;                        // +0x1b0
    uint32_t pad1b4[(0x2c0 - 0x1b4) / 4];
    Transform mCSnapBoneTransform1;                  // +0x2c0
    Transform mCSnapBoneTransform2;                  // +0x2f8
    int mCSnapBoneIndex;                             // +0x330
    uint32_t pad334[(0x340 - 0x334) / 4];
    fixed_vector<AutoRefCount<cSPEditorBlock>, 8> mChildren;  // +0x340
    uint32_t pad378[(0x3f0 - 0x378) / 4];
    AutoRefCount<cMWModel> mpSocketConnectorModel;   // +0x3f0
    Vector3 mModelMinSocketConnectorOffset;          // +0x3f4
    Vector3 mModelMaxSocketConnectorOffset;          // +0x400
    Vector3 mSocketConnectorOffset;                  // +0x40c
    uint32_t pad418[(0x6cc - 0x418) / 4];
    fixed_vector<AutoRefCount<cSPEditorHandleDeform>, 8> mMorphHandles;  // +0x6cc
    uint32_t pad704[(0xdc8 - 0x704) / 4];
    bitset<60> mBooleanAttributes;                   // +0xdc8

    bool SetMorphHandleWeight(int index, float weight, int arg3, bool updateChildren, bool updateSymmetric);
    void UpdateMorphs();                                   // 0x0043D420
    Vector3 GetSocketConnectorPosition();                  // 0x0043E080
    void SetBooleanAttribute(int index, bool value);       // 0x00435A10
    void UpdateBoundingBox();                              // 0x0044D570
    void SyncTransform(bool b);                            // 0x00437400 (on a child block)
    void UpdateOthers(int index, bool b);                  // 0x00437310
    int FindMorphHandleIndex(cSPEditorHandleDeform* handle);   // 0x0043C3D0
};

// @ 0x0043D690
// /Od frame: local names are chosen for cl's name-hash slot order (q_p = handle count,
// q_n23 = animation time / bone count, q_p7/q_t13 = animation range start/end,
// q_t20 = bone transforms, q_v36 = csnap transform). ScratchSlots<N> reproduce the frames
// the original reserved for helpers cl declined to inline (Transform/fixed_vector ctors,
// Accumulate, AccumulateScaled, GetSocketConnectorPosition).
bool cSPEditorBlock::SetMorphHandleWeight(int index, float weight, int arg3, bool updateChildren, bool updateSymmetric)
{
    int q_p = mMorphHandles.size();
    if (index < q_p) {
        mMorphHandles[index]->SetWeight(weight);
        mMorphHandles[index]->Update();
        float q_p7 = 0.0f;
        float q_t13 = 0.0f;
        mpModelWorld->GetAnimationRange(mpModel, mMorphHandles[index]->mAnimID, &q_p7, &q_t13, 0);
        float q_n23 = (q_t13 - q_p7) * mMorphHandles[index]->mWeight + q_p7;
        mpModelWorld->MoveToTime(mpModel, mMorphHandles[index]->mAnimID, q_n23, 0);
        UpdateMorphs();

        if (mpModel && mBooleanAttributes.test(0x36) && mCSnapBoneIndex != -1) {
            int q_n23 = mpModelWorld->GetNumBones(mpModel);
            Transform q_v36;
            ScratchSlots<3>();
            fixed_vector<BoneTransform, 64> q_t20(q_n23);
            mpModelWorld->GetBoneTransforms(mpModel, q_t20.data());
            BoneTransformToTransform(q_t20.mpBegin + mCSnapBoneIndex, &q_v36);
            ScratchSlots<17>();
            q_v36.Accumulate(mCSnapBoneTransform1);
            q_v36.AccumulateScaled(*mpModelWorld->GetMeshTransform(mpModel));
            ScratchSlots<15>();
            q_v36.mScale = 1.0f;
            q_v36.mChangeCount++;
            mCSnapBoneTransform2 = q_v36;
        }

        if (mBooleanAttributes.test(0xb) && index == mSelectedMorphHandle) {
            mSocketConnectorOffset = mModelMinSocketConnectorOffset +
                weight * (mModelMaxSocketConnectorOffset - mModelMinSocketConnectorOffset);
            if (mpSocketConnectorModel) {
                ScratchSlots<6>();
                Vector3P position = mPosition + GetSocketConnectorPosition();
                ScratchSlots<6>();
                mpSocketConnectorModel->mTransform.SetOffset(mPosition + GetSocketConnectorPosition());
            }
            if (mBooleanAttributes.test(0xa))
                SetBooleanAttribute(9, true);
        }

        UpdateBoundingBox();
        if (updateChildren) {
            if (!mChildren.empty()) {
                for (int i = 0, n = mChildren.size(); i < n; i++)
                    mChildren[i]->SyncTransform(true);
            }
            if (!mMorphHandles.empty())
                UpdateOthers(index, true);
        }
        field_1A8 = true;

        if (updateSymmetric && mMorphHandles[index]->mpSymmetricHandle != 0) {
            int other = FindMorphHandleIndex(mMorphHandles[index]->mpSymmetricHandle);
            if (other != index)
                SetMorphHandleWeight(other, weight, arg3, updateChildren, false);
        }

        for (int j = 0; j < 3; j++) {
            if (mAxisHandles[j]) {
                mAxisHandles[j]->UpdatePosition();
                mAxisHandles[j]->Update();
            }
        }
        return true;
    }
    return false;
}

} // namespace SP
