// Slice s00491b40: the vertical (stacking) alignment pass of the editor's block alignment code,
// called by GetAlignmentPosition (0x490a70) as FUN_00491b40(self, piles, v, m, &out, &flag, true, k).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), editor /Od region.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
#include <math.h>                           // fabs(float) overload -> fabsf -> intrinsic fabs

// ---- rw::math / cSP math types ----
struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0> (inline copy)
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
// Vector with the out-of-line copy constructor @ 0x4098a0.
struct RwVec3 : Vector3T {
    RwVec3() {}
    RwVec3(const RwVec3& v);                                // @ 0x4098a0
    RwVec3(const Vector3T& v) : Vector3T(v) {}
    RwVec3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
// cSPVector3: copy goes through the rw::math base copy constructor.
struct cSPVector3 : RwVec3 {
    cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3(const cSPVector3& v) : RwVec3(v) {}
};
struct Matrix3 {
    Vector3T xAxis, yAxis, zAxis;
    Matrix3() {}
    Matrix3(const Matrix3& m) { Assign(m); }
    Matrix3& Assign(const Matrix3& m);                      // @ 0x41cb40
};
struct cSPBoundingBox {
    Vector3T mMin, mMax;
};

Vector3T operator*(const Vector3T& v, const float& s);      // @ 0x41dca0
Vector3T operator+(const Vector3T& a, const Vector3T& b);   // @ 0x41dc10
Vector3T operator-(const Vector3T& a, const Vector3T& b);   // @ 0x41db10
Vector3T operator-(const Vector3T& v);                      // @ 0x422020
float VectorLength(const Vector3T& v);                      // @ 0x40ae50

extern const RwVec3 kZeroVector;                            // @ 0x15d64d8
extern const Vector3T kUpVector;                            // @ 0x15d6324

// ---- editor types ----
struct RefObj {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};

template<class T> struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    AutoRefCount(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~AutoRefCount() { if (mp) mp->Release(); }
    operator T*() const { return mp; }
    T* operator->() const { return mp; }
};

struct cSPEditorBlock;
struct cMWModel : RefObj {};
struct hkRigidBody;
struct cSPEditorModelPhysics {
    char pad0[0xc];
    hkRigidBody* mGroundBody;                               // +0xc
    hkRigidBody* GetGroundBody() const { return mGroundBody; }
};
struct cSPEditorModel {
    int GetBlockCount();                                    // @ 0x4accf0
    cSPEditorBlock* GetBlock(int i);                        // @ 0x4accb0
    cSPEditorModelPhysics* GetPhysics();                    // @ 0x4ad450
};

struct BlockList {                                          // eastl::vector<AutoRefCount<cSPEditorBlock>>
    AutoRefCount<cSPEditorBlock>* mpBegin;
    AutoRefCount<cSPEditorBlock>* mpEnd;
    AutoRefCount<cSPEditorBlock>* mpCap;
    uint32_t mAlloc[2];
    BlockList(const BlockList& x);                          // @ 0x4a9da0
    ~BlockList();                                           // @ 0x453eb0
    void push_back(const AutoRefCount<cSPEditorBlock>& v);  // @ 0x4541f0
    AutoRefCount<cSPEditorBlock>* begin() { return mpBegin; }
    AutoRefCount<cSPEditorBlock>* end() { return mpEnd; }
};

struct cSPEditorBlock : RefObj {
    char pad0[0x28 - 4];
    cSPEditorModel* mEditorModel;                           // +0x28
    char pad1[0x48 - 0x2c];
    RwVec3 mPosition;                                      // +0x48
    char pad2[0x33c - 0x54];
    cMWModel* mSocketConnector;                             // +0x33c
    char pad3[0xdc8 - 0x340];
    uint32_t mFlags[2];                                     // +0xdc8 (eastl::bitset<60>)
    cSPEditorModel* GetEditorModel() const { return mEditorModel; }
    cMWModel* GetSocketConnector() const { return mSocketConnector; }
    const RwVec3& GetPosition() const { return mPosition; }
    uint32_t Word(uint32_t i) const { return mFlags[i >> 5]; }
    // __forceinline: plain inline runs out of cl's /Ob1 inlining budget in this large function
    __forceinline bool TestFlag(uint32_t i) const {
        if (i < 0x3c) return (Word(i) & (1u << (i % 32))) != 0;
        return false;
    }
    bool IsFlag16Set() const { return TestFlag(0x16); }
    bool IsFlag17Set() const { return TestFlag(0x17); }
    bool IsSnapFlagSet(int type);                                   // @ 0x4385e0
    bool IsSnappedTo(cSPEditorBlock* other, int type);              // @ 0x438440
    bool FUN_0043bbc0(int x);                                       // @ 0x43bbc0
    void FUN_00448e90(const Vector3T& v, bool b);                   // @ 0x448e90
    cSPBoundingBox GetBBox(int type, bool a, bool b);               // @ 0x44ae00
};

hkRigidBody* MoveBlockLowAngleStacking(cSPEditorBlock* block, BlockList& piles, Vector3T position,
                                       Vector3T direction, Vector3T& outPosition, Matrix3 orientation,
                                       bool unused);                // @ 0x48d010
// Same function; the second call site copies the position with the out-of-line copy ctor.
hkRigidBody* MoveBlockLowAngleStacking(cSPEditorBlock* block, BlockList& piles, cSPVector3 position,
                                       Vector3T direction, Vector3T& outPosition, Matrix3 orientation,
                                       bool unused);                // @ 0x48d010

template<class I, class T> inline I find(I first, I last, const T& value)
{
    while (first != last && !(*first == value))
        ++first;
    return first;
}

// Local names reproduce the /Od frame-slot order (cl orders a scope's locals by a hash of their names);
// found with work/match/scratch_s00491b40_odsearch.py. Roles: n12/t38 = flag 0x17/0x16 set, n21 = result
// offset, n11/n10 = snap flags 0x17/0x16, right = start position, t19/to = block lists for 0x17/0x16,
// t39 = own bbox, n9 = "all lists agree", n13 = bbox height, owner = position, f = dz, n28/v14 = cast
// start/direction, t37/v15 = landing positions (0x16/0x17), n2/p11 = hit bodies, t30 = drop, base = eps,
// v34 = moved; loop: tmp/t14 = index/count, len = other block, offset = its bbox, where = above,
// p24/t24 = added to the 0x16/0x17 list.
// @ 0x00491b40
float FUN_00491b40(cSPEditorBlock* self, const BlockList& piles, Vector3T v, Matrix3 m, RwVec3* out,
                   bool* outFlag, bool addSocket, float k)
{
    bool t38 = self->IsFlag16Set();
    bool n12 = self->IsFlag17Set();
    *out = self->mPosition;
    if (!t38 && !n12)
        return -1.0f;
    RwVec3 n21(kZeroVector);
    *outFlag = false;
    if (self->GetEditorModel() != 0) {
        bool n11 = self->IsSnapFlagSet(0x17);
        bool n10 = self->IsSnapFlagSet(0x16);
        if (self->FUN_0043bbc0(0) && (self->TestFlag(0x16) || n10)) {
            float h = self->GetBBox(1, false, false).mMin[2] + (*out)[2];
            (*out)[2] -= h;
            *outFlag = true;
            return fabs(h);
        }
        RwVec3 right(self->mPosition);
        BlockList t19(piles);
        if (addSocket && self->GetSocketConnector() != 0)
            t19.push_back(AutoRefCount<cSPEditorBlock>((cSPEditorBlock*)self->GetSocketConnector()));
        ScratchSlots<2>();
        BlockList to(piles);
        if (addSocket && self->GetSocketConnector() != 0)
            to.push_back(AutoRefCount<cSPEditorBlock>((cSPEditorBlock*)self->GetSocketConnector()));
        ScratchSlots<2>();
        self->FUN_00448e90(v, true);
        cSPBoundingBox t39 = self->GetBBox(0, false, false);
        self->FUN_00448e90(right, true);
        bool n9 = true;
        for (int tmp = 0, t14 = self->GetEditorModel()->GetBlockCount(); tmp < t14; tmp++) {
            cSPEditorBlock* len = self->GetEditorModel()->GetBlock(tmp);
            cSPBoundingBox offset = len->GetBBox(0, false, false);
            bool t24 = false;
            bool p24 = false;
            bool where = offset.mMin[2] >= t39.mMin[2];
            if (find(to.begin(), to.end(), len) == to.end()) {
                if ((self->TestFlag(0x16) && !self->IsSnappedTo(len, 0x16)) || where) {
                    to.push_back(AutoRefCount<cSPEditorBlock>(len));
                    ScratchSlots<2>();
                    p24 = true;
                }
            }
            if (find(t19.begin(), t19.end(), len) == t19.end()) {
                if ((self->TestFlag(0x17) && !self->IsSnappedTo(len, 0x17)) || where) {
                    t19.push_back(AutoRefCount<cSPEditorBlock>(len));
                    ScratchSlots<2>();
                    t24 = true;
                }
            }
            if (n9 && p24 != t24)
                n9 = false;
        }
        float n13 = fabs(self->GetBBox(1, false, false).mMin[2]);
        Vector3T owner = self->GetPosition();
        float f = v[2] - owner[2];
        cSPVector3 n28 = owner + kUpVector * (n13 + 2.0f);
        cSPVector3 v14 = -kUpVector;
        Vector3T t37 = self->GetPosition();
        Vector3T v15 = t37;
        hkRigidBody* n2 = 0;
        hkRigidBody* p11 = 0;
        if (t38)
            n2 = MoveBlockLowAngleStacking(self, to, (const Vector3T&)n28, v14, t37, m, !n10);
        if (n12)
            p11 = MoveBlockLowAngleStacking(self, t19, n28, v14, v15, m, !n11);
        float t30 = owner[2] - v15[2];
        float base = 0.1f;
        bool v34 = false;
        if (n12 && 0.8f * k > t30) {
            n21 = v15 - owner;
            v34 = true;
            if (p11 != 0 && p11 == self->GetEditorModel()->GetPhysics()->GetGroundBody())
                *outFlag = true;
        }
        if (t38 && t37[2] > owner[2]) {
            v34 = true;
            n21 = t37 - owner;
            if (n2 != 0 && n2 == self->GetEditorModel()->GetPhysics()->GetGroundBody())
                *outFlag = true;
        }
        *out = self->mPosition + n21;
        ScratchSlots<16>();
        if (v34)
            return VectorLength(n21);
        else
            return -1.0f;
    } else
        return -1.0f;
}
