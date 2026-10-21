// SP::cSPEditorBlock — scale/transform plumbing (unoptimized /Od /Ob1 /arch:SSE).
#include "types.h"

namespace SP {

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
struct Matrix3 { float m[9]; Matrix3() {} Matrix3(const Matrix3&); };

// 28-byte transform-ish record used by the +0x4C8 element list.
struct Trans {
    uint32_t flag;   // +0x00
    Vec3     a;      // +0x04
    Vec3     b;      // +0x10
    Trans();
    Trans(const Trans& o);
};

// ---- types for F40520 (uniform scale setter), retail layout; follows slice s0043d690 ----
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }

struct Vector3 {
    float x, y, z;
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct Vector3P {
    float x, y, z;
    Vector3P(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
Vector3 operator+(const Vector3& a, const Vector3& b);         // 0x0041DC10

// cSPTransform head (0x38 bytes in full; only the leading fields are used here)
struct Transform {
    uint16_t mFlags;        // +0x00
    uint16_t mChangeCount;  // +0x02
    Vector3P mOffset;       // +0x04
    float mScale;           // +0x10
    void SetOffset(const Vector3P& offset)
    {
        mOffset = offset;
        mFlags |= 4;
        mChangeCount++;
    }
    void SetScale(float scale)
    {
        mScale = scale;
        mChangeCount++;
    }
};

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

template <class T>
struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// SSE clamp helper of the editor module (maxss/minss against the memory params)
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

// Fraction of value between lo and hi.
inline float InverseLerp(float value, float lo, float hi) { return (value - lo) / (hi - lo); }

struct cMWModel;
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
    virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual void vf0(); virtual void vf4(); virtual void vf8(); virtual void vfc();
    virtual void v100(); virtual void v104(); virtual void v108();
    virtual void UpdateModel(cMWModel* model, int arg);                   // 0x10C
    virtual void ApplyModel(cMWModel* model, int arg);                    // 0x110
};

struct cMWModel { private:
public:
    IModelWorld* mpWorld;   // +0x00
    uint32_t mFlags;        // +0x04
    Transform mTransform;   // +0x08
};

// Property-list interface at block+0xC; slot 0x1C takes an int key
class IPropList {
public:
    virtual int AddRef(); virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasKey(uint32_t key);                                    // 0x1C
};

class cSPEditorHandle {
public:
    virtual int AddRef();          // 0x00
    virtual int Release();         // 0x04
    virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void Update();         // 0x14
    bool IsFlagSet();              // 0x0047F290
};

class cSPEditorHandleRotationRing : public cSPEditorHandle {
public:
    void UpdateAnimTime();         // 0x00485650
    void ApplyAnimTime();          // 0x00485550
};

// +0x3EC object: only vtable slot 0x20 is used here
struct IScale {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void SetScale(float f);   // 0x20
};

// Trans with operator=-style Vec3 copies (F40c40 element store)
struct V3 { uint32_t x, y, z; };
struct TransB { uint32_t flag; V3 a; V3 b; };
struct Range { void* a; void* b; };
struct Vec4Ptr {
    void** mpBegin; void** mpEnd; void** mpCap;
    void** At(int i) { return mpBegin + i; }
    int Size() { return (int)(mpEnd - mpBegin); }
    void Free();                                   // 0x00425990
};
// map at block+0x4C8: [0] begin, [1] end; nodes are {key, Trans}
struct TransMap {
    void* mpBegin; void* mpEnd;
    char* end() const { char* e = (char*)mpEnd; return e; }
    void   Find(Range* out, const uint32_t* key);  // 0x004553B0 (ret 8)
    TransB* Index(const int* key);                 // 0x00454420 (ret 4)
};

class cSPEditorBlock { public:
    char        pad00[0xC];
    AutoRefCount<IPropList> mPropList;  // +0x0C
    union {
        void*       mModel;      // +0x10
        AutoRefCount<cMWModel> mpModel;
    };
    char        pad14[0x18 - 0x14];
    union {
        void*       p18;         // +0x18
        AutoRefCount<IModelWorld> mpModelWorld;
    };
    char        pad1c[0x2C - 0x1c];
    bool        mIsFullInit;     // +0x2C
    char        pad2d[0x48 - 0x2D];
    Vector3     mPosition;       // +0x48
    char        pad54[0x154 - 0x54];
    AutoRefCount<cSPEditorHandleRotationRing> mRotationRingHandles[3]; // +0x154
    AutoRefCount<cSPEditorHandle> mRotationBallHandle;                 // +0x160
    char        pad164[0x168 - 0x164];
    uint32_t    mVertebraAnimID; // +0x168
    char        pad16c[0x1A8 - 0x16C];
    bool        field_1A8;       // +0x1A8
    char        pad1a9[0x1D4 - 0x1A9];
    float       mDefaultMouseOffset; // +0x1D4
    float       mUniformScale;   // +0x1D8
    char        pad1dc[4];
    float       mMinUniformScale; // +0x1E0
    float       mMaxUniformScale; // +0x1E4
    char        pad1e8[0x218 - 0x1E8];
    float       mMinScale218;    // +0x218
    float       mMaxScale21c;    // +0x21C
    char        pad220[0x33C - 0x220];
    AutoRefCount<cSPEditorBlock> link33c; // +0x33C
    char        pad340[0x3EC - 0x340];
    AutoRefCount<IScale> p3ec;        // +0x3EC
    AutoRefCount<cMWModel> mpSocketConnectorModel; // +0x3F0
    char        pad3f4[0x40C - 0x3F4];
    char        pad40c[0x4C8 - 0x40C];
    void*       list4c8;     // +0x4C8
    void*       list4cc;     // +0x4CC
    char        pad4d0[0x5F8 - 0x4D0];
    Vec3        v5f8;        // +0x5F8
    char        pad604[0xDC8 - 0x604];
    bitset<60>  mBooleanAttributes; // +0xDC8

    Vector3 GetSocketConnectorPosition();       // 0x0043E080
    Vec3* F40b90(Vec3* out);                    // 00440B90
    void  F40bc0(const Vec3* v);                // 00440BC0
    void  F40c00(float f);                      // 00440C00
    void  F40c40(void* item, int flag);         // 00440C40
    bool  F40d80(void* out, uint32_t key);      // 00440D80
    void  F40e00(cSPEditorBlock* o);            // 00440E00
    void  F40e60(uint32_t key);                 // 00440E60
    bool  F43ebc0();                            // 0043EBC0
    bool  F43ecb0();                            // 0043ECB0
    void  F4a070();                             // 0044A070
    TransMap* Map() { return (TransMap*)&list4c8; }
    void  F40390(float f);                      // 00440390
    void  F40420(float f, char b);              // 00440420
    void  F404f0(Matrix3 m);                    // 004404F0
    void  F40110(float f);                      // 00440110
    void  SetUniformScale(float scale, bool b, bool force);   // 00440520
    void  SetFlag(int a, int b);                // 00435A10
};

void  Sub_4B8750(cMWModel* a, IModelWorld* b, Vec4Ptr* out, int flag);     // 0x004B8750 (cdecl)
void  Sub_4B8180(Trans t, void* world, void* model, uint32_t key);   // 0x004B8180 (cdecl)
void  Sub_698650(void* m);

extern const Vec3 g_v3_241c;   // 015D241C

// @ 0x00440B90
Vec3* cSPEditorBlock::F40b90(Vec3* out)
{
    *out = v5f8;
    return out;
}

// @ 0x00440BC0
void cSPEditorBlock::F40bc0(const Vec3* v)
{
    if (mModel != 0) {
        void* m = mModel;
        *(Vec3*)((char*)m + 0x4C) = *v;
    }
}

// @ 0x00440C00
void cSPEditorBlock::F40c00(float f)
{
    if (mModel != 0) {
        void* m = mModel;
        *(float*)((char*)m + 0x58) = f;
    }
}

// @ 0x00440390
void cSPEditorBlock::F40390(float f)
{
    float lo = 0.0f, hi = 1.0f;
    float v = f;
    if (v < lo) v = lo;
    if (v > hi) v = hi;
    if (v != *(float*)((char*)this + 0x1D0)) {
        *(float*)((char*)this + 0x1D0) = v;
        SetFlag(9, 1);
    }
}

// @ 0x00440420
void cSPEditorBlock::F40420(float f, char b)
{
    float old = *(float*)((char*)this + 0x1DC);
    *(float*)((char*)this + 0x1DC) = f;
    if (*(float*)((char*)this + 0x1DC) > *(float*)((char*)this + 0x1E4)) {
        *(float*)((char*)this + 0x1DC) = *(float*)((char*)this + 0x1E4);
    } else if (*(float*)((char*)this + 0x1E0) > *(float*)((char*)this + 0x1DC)) {
        *(float*)((char*)this + 0x1DC) = *(float*)((char*)this + 0x1E0);
    }
    if (b != 0 && p3ec != 0) {
        F40110((*(float*)((char*)this + 0x1DC) / old) * *(float*)((char*)this + 0x1D4));
    }
}

// @ 0x004404F0
void cSPEditorBlock::F404f0(Matrix3 m)
{
    Sub_698650(&m);
    uint32_t* dst = (uint32_t*)((char*)this + 0xF0);
    uint32_t* src = (uint32_t*)&m;
    for (int i = 0; i < 9; i++) dst[i] = src[i];
}

// @ 0x00440F60
Trans::Trans()
{
    flag = 0;
    a = g_v3_241c;
    b = g_v3_241c;
}

// @ 0x00440FF0
Trans::Trans(const Trans& o)
{
    flag = o.flag;
    a = o.a;
    b = o.b;
}

// @ 0x00440C40
void cSPEditorBlock::F40c40(void* item, int flag)
{
    Vec4Ptr found = { 0, 0, 0 };
    Sub_4B8750(mpModel, mpModelWorld, &found, flag);
    int n = found.Size();
    for (int i = 0; i < n; i++) {
        int* key = (int*)found.At(i);
        TransB* dst = Map()->Index(key);
        dst->flag = ((TransB*)item)->flag;
        dst->a = ((TransB*)item)->a;
        dst->b = ((TransB*)item)->b;
        F40e60((uint32_t)found.mpBegin[i]);
    }
    for (void** p = found.mpBegin; p < found.mpEnd; p++) {
    }
    found.Free();
}

// @ 0x00440D80
bool cSPEditorBlock::F40d80(void* out, uint32_t key)
{
    Range r;
    ScratchSlots<5>();
    TransMap* m = Map();
    m->Find(&r, &key);
    char* it;
    if (r.a != r.b)
        it = (char*)r.a;
    else
        it = m->end();
    if (it != Map()->end()) {
        if (out)
            *(Trans*)out = *(Trans*)(it + 4);
        return true;
    }
    return false;
}

// @ 0x00440E00
void cSPEditorBlock::F40e00(cSPEditorBlock* o)
{
    char* it = (char*)o->list4c8;
    char* end = (char*)o->list4cc;
    for (; it != end; it += 0x20) {
        F40c40(it + 4, *(int*)it);
    }
}

// @ 0x00440E60
void cSPEditorBlock::F40e60(uint32_t key)
{
    static Trans sDefault;
    TransMap* m = Map();
    Range r;
    m->Find(&r, &key);
    char* it;
    if (r.a != r.b)
        it = (char*)r.a;
    else
        it = m->end();
    Trans* t = (it == Map()->end()) ? &sDefault : (Trans*)(it + 4);
    Trans* t2 = t;
    if (mpModel && mpModelWorld) {
        void* model = mpModel;
        void* world = mpModelWorld;
        Sub_4B8180(*t2, world, model, key);
    }
}

// @ 0x00440110
void cSPEditorBlock::F40110(float f)
{
    if (mMinScale218 > f)
        f = mMinScale218;
    else if (f > mMaxScale21c)
        f = mMaxScale21c;
    if (f != mDefaultMouseOffset) {
        mDefaultMouseOffset = f;
        if (mBooleanAttributes.test(10))
            SetFlag(9, 1);
        if (link33c && link33c->mBooleanAttributes.test(11) && link33c->mBooleanAttributes.test(10))
            link33c->SetFlag(9, 1);
        if (p3ec)
            p3ec->SetScale(mDefaultMouseOffset);
        bool a = F43ebc0();
        if (a)
            F4a070();
        if (link33c && link33c->p3ec) {
            bool b = link33c->F43ecb0();
            if (b)
                link33c->F4a070();
        }
    }
}

// @ 0x00440520
// cSPEditorBlock::SetUniformScale(scale, b, force): clamps and stores mUniformScale, drives the
// model's scale morph (or its transform scale), optionally rescales the mouse offset, then
// refreshes the socket connector, the rotation-ring handles and the ball handle.
void cSPEditorBlock::SetUniformScale(float scale, bool b, bool force)
{
    if (mUniformScale != scale || force) {
        float oldScale = mUniformScale;
        scale = Clamp(scale, mMinUniformScale, mMaxUniformScale);
        mUniformScale = scale;
        if (mpModel) {
            if (mBooleanAttributes.test(7) && mVertebraAnimID) {
                float end;
                float start;
                mpModelWorld->GetAnimationRange(mpModel, mVertebraAnimID, &start, &end, 0);
                float t = InverseLerp(scale, mMinUniformScale, mMaxUniformScale);
                mpModelWorld->MoveToTime(mpModel, mVertebraAnimID, (end - start) * t + start, 0);
                if (mIsFullInit) {
                    mpModelWorld->UpdateModel(mpModel, 0);
                    if (mPropList && mPropList->HasKey(0xF9EFC0))
                        mpModelWorld->ApplyModel(mpModel, 0);
                }
            } else {
                mpModel->mTransform.SetScale(scale);
            }
        }
        if (b) {
            if (mBooleanAttributes.test(31))
                F40110((mUniformScale / oldScale) * mDefaultMouseOffset);
            if (mpSocketConnectorModel)
                mpSocketConnectorModel->mTransform.SetScale(scale);
        }
        if (mpSocketConnectorModel) {
            ScratchSlots<7>();
            mpSocketConnectorModel->mTransform.SetOffset(mPosition + GetSocketConnectorPosition());
        }
        for (int i = 0; i < 3; i++) {
            if (mRotationRingHandles[i]) {
                mRotationRingHandles[i]->UpdateAnimTime();
                mRotationRingHandles[i]->Update();
                if (mRotationRingHandles[i]->IsFlagSet())
                    mRotationRingHandles[i]->ApplyAnimTime();
            }
        }
        if (mRotationBallHandle)
            mRotationBallHandle->Update();
        field_1A8 = true;
        SetFlag(9, 1);
    }
}

} // namespace SP
