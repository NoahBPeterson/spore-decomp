// Slice s004a5970: SP::EditorUtils block helpers (symmetry / limb roots / skin radius).
// Module flags: /Od /Ob1 /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---- rw::math / cSP math types ----
struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T {                              // rw::math::fpu::Matrix33Template<float,0>
    Vector3T xAxis, yAxis, zAxis;
};
struct cSPMatrix3 : Matrix33T {
    static const cSPMatrix3 IDENTITY;           // @ 0x15d5908
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPBoundingBox {
    cSPVector3 mMin, mMax;
    bool IsEmpty() const { return mMin[0] > mMax[0]; }
};

Vector3T operator*(const Vector3T& v, const Matrix33T& m);   // @ 0x41daf0
Vector3T operator-(const Vector3T& v);                       // @ 0x422020
Vector3T operator+(const Vector3T& a, const Vector3T& b);    // @ 0x41dc10
Vector3T& operator+=(Vector3T& a, const Vector3T& b);        // @ 0x41ddb0
float VectorLength(const Vector3T& v);                       // @ 0x40ae50
inline float Length(const Vector3T& v) { return VectorLength(v); }

inline const float& Max(const float& a, const float& b) { return (a > b) ? a : b; }
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { float r = (float)fabs(x); return r; }

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    cSPVector3 mTranslation;
    float mScale;
    cSPMatrix3 mRotation;
    cSPTransform();                                          // @ 0x409930
    const cSPMatrix3& GetRotation() const { return mRotation; }
    void SetRotation(const cSPMatrix3& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void PreRotate(const Vector3T& axis, float angle);       // @ 0x6baba0
};

// ---- EASTL-style containers ----
template<class T> struct AutoRefCount {
    T* mpObject;
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T& operator*() const { return *mpObject; }
    T* get() const { return mpObject; }
    operator T*() const { return mpObject; }
};

// Layout helper: the AutoRefCount vector's inline constructor reserves one unused /Od slot.
template<class T> struct CtorSlots { static void Reserve() {} static void ReserveClear() {} };
template<class T> struct AutoRefCount;
template<class T> struct CtorSlots<AutoRefCount<T> > { static void Reserve() { ScratchSlots<1>(); } static void ReserveClear() { ScratchSlots<3>(); } };

template<class T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) { CtorSlots<T>::Reserve(); }
    ~VectorBase();                                           // @ 0x425990 (shared)
};
template<class T> struct vector : VectorBase<T> {
    vector() {}
    ~vector() { DoDestroyValues(mpBegin, mpEnd); ScratchSlots<3>(); }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    T* erase(T* first, T* last);                             // @ 0x4769b0 / 0x454280
    void clear() { erase(mpBegin, mpEnd); ScratchSlots<4>(); CtorSlots<T>::ReserveClear(); }
    bool empty() const;                                      // @ 0x526430
    void DoDestroyValues(T* first, T* last) { for (; first < last; ++first) first->~T(); }
};

template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

namespace SP {

#define PV(n) virtual void _v##n();
struct cSkinMesh {
    virtual int AddRef();
    PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    virtual void Rebuild(int mode, int flags);               // 0x30
};
struct cSkinOwner {
    virtual int AddRef();
};
template<class T> struct ArgRef {           // AutoRefCount passed by value (callee releases)
    T* mpObject;
    ArgRef(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
};

struct cSPEditorModel;

struct cSPEditorBlock {
    virtual void _v0();
    virtual int Release();
    char pad0[0x48 - 4];
    cSPVector3 mPosition;                       // +0x48
    char pad1[0x60 - 0x54];
    struct { Vector3T mRow[3]; const Vector3T& GetRow(int i) const { return mRow[i]; } } mOrientation;  // +0x60 (cSPMatrix3)
    char pad2[0x1d8 - 0x84];
    float mScale;                               // +0x1d8
    char pad3[0x33c - 0x1dc];
    AutoRefCount<cSPEditorBlock> mParentBlock;  // +0x33c
    vector<AutoRefCount<cSPEditorBlock> > mSymmetricBlocks;   // +0x340
    char pad4[0x3e0 - 0x354];
    int mUIState;                               // +0x3e0
    char pad5[0x3ec - 0x3e4];
    AutoRefCount<cSkinMesh> mSkin;              // +0x3ec
    char pad6[0xdc8 - 0x3f0];
    bitset<60> mFlags;                          // +0xdc8

    float GetScale() const { return mScale; }
    int GetUIState() const { return mUIState; }
    cSPEditorBlock* GetParent() const { return mParentBlock; }
    int GetSymmetryCount();                                  // @ 0x44f220
};

struct cSPEditorModel {
    cSPEditorBlock* GetBlock(int i);                         // @ 0x4accb0
    int GetBlockCount();                                     // @ 0x4accf0
};

Vector3T operator*(const Vector3T& v, const float& s);                    // @ 0x41dca0
void SetBlockScale(cSPEditorBlock* block, float scale, bool a, bool b);   // @ 0x49e6a0
bool SkinUsesModel(cSkinMesh* skin, ArgRef<cSkinOwner> owner);            // @ 0x498850

namespace EditorUtils {

cSPEditorBlock* GetLimbRoot(cSPEditorBlock* block);
bool IsLimbConnected(cSPEditorBlock* block);
void RebuildSkins(cSPEditorBlock* block, cSkinOwner* owner);
void RefreshSkins(cSPEditorBlock* block, cSPEditorBlock* except);
float GetExactSkinRadiusFromVertebra(float scale);
float GetSkinRadiusFromVertebra(float scale);
cSPVector3 GetSkinPoint(const cSPVector3& pos, const cSPVector3& dir, float scale);

// @ 0x4a5970
cSPEditorBlock* FindSymmetricSpine(cSPEditorBlock* block)
{
    if (block) {
        vector<AutoRefCount<cSPEditorBlock> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++) {
            if (syms[i] && syms[i]->mFlags.test(7))
                return syms[i];
        }
    }
    return 0;
}

// @ 0x4a5a70
cSPEditorBlock* FindRootSpine(cSPEditorModel* model)
{
    for (int i = 0, n = model->GetBlockCount(); i < n; i++) {
        cSPEditorBlock* block = model->GetBlock(i);
        if (block && block->mFlags.test(7) && !block->GetParent())
            return block;
    }
    return 0;
}

// @ 0x4a5b30
void AddBlockScale(cSPEditorBlock* block, float delta)
{
    SetBlockScale(block, block->GetScale() + delta, true, true);
}

// @ 0x4a5b70
float GetExactSkinRadiusFromVertebra(float scale)
{
    float t14 = 0.70710677f;
    float tmp = scale * 0.37802768f * 0.7f * 1.2f * t14;
    if (0.04f > tmp) tmp = 0.04f;
    return tmp;
}

// @ 0x4a5bd0
float GetExactSkinRadius(cSPEditorBlock* block)
{
    return GetExactSkinRadiusFromVertebra(block->GetScale());
}

// @ 0x4a5c00
float GetSkinRadiusFromVertebra(float scale)
{
    float r = scale * 0.37802768f * 0.7f;
    if (0.04f > r) r = 0.04f;
    return r;
}

// @ 0x4a5c40
float GetSkinRadius(cSPEditorBlock* block)
{
    return GetSkinRadiusFromVertebra(block->GetScale());
}

// @ 0x4a5c70
cSPVector3 GetSkinPoint(const cSPVector3& pos, const cSPVector3& dir, float scale)
{
    float t = -0.15993178f * scale;
    cSPVector3 r = pos + dir * t;
    return r;
}

// @ 0x4a5d10
cSPVector3 GetSkinTip(cSPEditorBlock* block)
{
    cSPVector3 pos = block->mPosition;
    cSPVector3 dir = block->mOrientation.GetRow(2);
    return GetSkinPoint(pos, dir, block->GetScale());
}

// @ 0x4a5db0
cSPEditorBlock* GetRootBlock(cSPEditorBlock* block)
{
    if (!block) return 0;
    else {
        cSPEditorBlock* p = block->GetParent();
        if (!p) p = block;
        else {
            while (p->GetParent()) p = p->GetParent();
        }
        return p;
    }
}

// @ 0x4a5e10
cSPEditorBlock* GetLimbRoot(cSPEditorBlock* block)
{
    if (!block) return 0;
    else {
        cSPEditorBlock* p = block->GetParent();
        if (!p || (!p->mFlags.test(0xb) && !p->mFlags.test(8))) p = block;
        else {
            while (p->GetParent() && (p->GetParent()->mFlags.test(0xb) || p->GetParent()->mFlags.test(8)))
                p = p->GetParent();
        }
        return p;
    }
}

// @ 0x4a5fe0
bool HasSymmetricLimb(cSPEditorBlock* block)
{
    if (block) {
        vector<AutoRefCount<cSPEditorBlock> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++) {
            if (syms[i]->mFlags.test(0xb))
                return true;
        }
    }
    return false;
}

// @ 0x4a60a0
bool AreInSameLimb(cSPEditorBlock* a, cSPEditorBlock* b)
{
    if (!a || !b) return false;
    if (IsLimbConnected(a) && IsLimbConnected(b)) {
        cSPEditorBlock* ra = GetLimbRoot(a);
        cSPEditorBlock* rb = GetLimbRoot(b);
        return ra == rb;
    } else {
        return false;
    }
}

// @ 0x4a6120
bool IsLimbConnected(cSPEditorBlock* block)
{
    if (block && block->mFlags.test(8)) return true;
    if (!block || !block->mFlags.test(0x1f)) return false;
    if (block->mFlags.test(0xb)) return true;
    else if (block->GetParent() != block) return IsLimbConnected(block->GetParent());
    else return false;
}

// @ 0x4a6270
bool IsLimbPart(cSPEditorBlock* block)
{
    if (!block) return false;
    if (block->mFlags.test(0xb)) return true;
    else if (block->GetParent() != block) return IsLimbPart(block->GetParent());
    else return false;
}

// @ 0x4a6310
cSPEditorBlock* GetSymmetryRoot(cSPEditorBlock* block)
{
    if (!block || !block->GetParent()) return block;
    if (block->GetUIState() || !block->GetSymmetryCount()) return block;
    else if (block->GetParent()->GetUIState() || !block->GetParent()->GetSymmetryCount()) return block;
    else return GetSymmetryRoot(block->GetParent());
}

// @ 0x4a63c0
void RebuildSkins(cSPEditorBlock* block, cSkinOwner* owner)
{
    if (block && (block->mSkin || block->mFlags.test(8))) {
        if (block->mSkin) {
            if (!SkinUsesModel(block->mSkin, owner))
                (*block->mSkin).Rebuild(3, 1);
        }
        vector<AutoRefCount<cSPEditorBlock> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++) {
            cSPEditorBlock* sym = syms[i];
            if (sym) RebuildSkins(sym, owner);
        }
    }
}

// @ 0x4a6520
void RefreshSkins(cSPEditorBlock* block, cSPEditorBlock* except)
{
    if (block && (block->mSkin || block->mFlags.test(8))) {
        if (except != block && block->mSkin)
            block->mSkin.get()->Rebuild(1, 1);
        vector<AutoRefCount<cSPEditorBlock> >& syms = block->mSymmetricBlocks;
        for (int i = 0, n = syms.size(); i < n; i++) {
            cSPEditorBlock* sym = syms[i];
            if (sym) RefreshSkins(sym, except);
        }
    }
}

// @ 0x4a6640
void RebuildLimbSkins(cSPEditorBlock* block, cSkinOwner* owner)
{
    RebuildSkins(GetLimbRoot(block), owner);
}

// @ 0x4a6660
void RefreshLimbSkins(cSPEditorBlock* block, bool includeSelf)
{
    cSPEditorBlock* except = includeSelf ? block : 0;
    RefreshSkins(GetLimbRoot(block), except);
}

}  // namespace EditorUtils
}  // namespace SP
