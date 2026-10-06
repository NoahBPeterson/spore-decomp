// Slice s0048ef30: SP::EditorUtils::GetLateralAlignmentPosition (0x48ef30) and the recursive
// symmetry update SP::UpdateSymmetryRec (0x48f790).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc).
//
// GetLateralAlignmentPosition(block, nearbyBlocks, outPos, outBasis, k): scores neighbouring blocks
// that are laterally aligned with `block` (their relative offset along the lateral axis is small and the
// two lateral axes are nearly parallel), builds a candidate pose per neighbour, and returns the best
// (lowest) score with its position/basis; -1.0f when there are no candidates.
// UpdateSymmetryRec(block, sign): when the block has no symmetric partner yet, mirrors it (Split(1)),
// links the partner both ways, mirrors its children recursively and re-parents the clones.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

extern "C" double __cdecl fabs(double);
extern "C" double __cdecl acos(double);
#pragma intrinsic(fabs, acos)
inline float Abs(float x) { return (float)fabs(x); }

// ---------------------------------------------------------------- math
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v);                           // 0x4098a0 (out of line)
    float& operator[](int i) { return (&x)[i]; }
};
struct Matrix3 {
    Vector3 xAxis, yAxis, zAxis;
    Matrix3() {}
    Matrix3(const Matrix3& m) { Assign(m); }
    Matrix3& Assign(const Matrix3& m);                   // 0x41cb40 (out of line)
    Vector3& operator[](int i) { return (&xAxis)[i]; }
};
struct Mat3Id : Matrix3 {
    Mat3Id();                                            // 0x402ab0 (identity)
    Mat3Id& operator=(const Matrix3& m) { Matrix3::operator=(m); return *this; }
};

Vector3 operator-(const Vector3& a, const Vector3& b);   // 0x41db10
Vector3 operator*(const Vector3& v, const Matrix3& m);   // 0x41daf0
Vector3& operator+=(Vector3& a, const Vector3& b);       // 0x41ddb0
Matrix3 Inverse(const Matrix3& m);                       // 0x41ded0
Vector3 Normalize(const Vector3& v);                     // 0x436ce0
float VectorLength(const Vector3& v);                    // 0x40ae50
extern Vector3 g_UpAxis;                                 // 0x15d6324
extern const float kFloatMax;                            // 0x13ef4c0

struct BoundingBox {
    Vector3 mMin, mMax;
    Vector3& GetCenter(Vector3& out) const;              // 0x409b90
};

struct Transform {                                       // cSPTransform, 0x38 bytes
    unsigned short mFlags, mVersion;
    Vector3 mPos;
    float mScale;
    Mat3Id mRot;
    Transform();                                         // 0x409930
    void SetRotation(const Matrix3& m) { mRot = m; mFlags |= 2; mVersion++; }
    void PreRotate(const Vector3& axis, float angle);    // 0x6baba0
};

Matrix3 AlignBasis(Matrix3 m, Vector3 a, Vector3 b);     // 0x4906e0 (cdecl, hidden out ptr)
struct PosRot { Mat3Id mRot; Vector3 mPos; };            // 0x30
struct Candidate { PosRot pr; float score; };            // 0x34 (OrientedPoint)

struct AllocTag { AllocTag() {} };

// ---------------------------------------------------------------- EA / EASTL stand-ins
struct RefObj {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};

template <class T> struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    AutoRefCount(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~AutoRefCount() { if (mp) mp->Release(); }
    operator T*() const { return mp; }
    T* operator->() const { return mp; }
};

template <unsigned N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(unsigned i) const {
        if (i < N) {
            const uint32_t word = mWord[i / 32];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

struct cSPEditorBlock;
struct cSPEditorModel;

// eastl::fixed_vector<AutoRefCount<cSPEditorBlock>, 8>
struct BlockRefVec {
    AutoRefCount<cSPEditorBlock>* mpBegin;
    AutoRefCount<cSPEditorBlock>* mpEnd;
    AutoRefCount<cSPEditorBlock>* mpCapacity;
    char mAllocator[0xc];
    void* mBuffer[8];
    BlockRefVec(const AllocTag& a = AllocTag()) { BaseInit(a); FixedInit(); }
    ~BlockRefVec();                                              // 0x00453eb0
    void BaseInit(const AllocTag& a);                            // 0x00540470
    void FixedInit();                                            // 0x00453770
    void push_back(const AutoRefCount<cSPEditorBlock>& v);       // 0x004541f0
    int size() const { return mpEnd - mpBegin; }
    AutoRefCount<cSPEditorBlock>& operator[](int i) { return mpBegin[i]; }
};

// eastl::vector<cSPEditorBlock*> (plain pointers), fill-constructed
template <class T> void uninitialized_fill_n_ptr(T* p, uint32_t n, const T& value);   // 0x004fc960
struct PtrVecBase {
    cSPEditorBlock** mpBegin;
    cSPEditorBlock** mpEnd;
    cSPEditorBlock** mpCapacity;
    uint32_t mAlloc[2];
    PtrVecBase(uint32_t n, const AllocTag& a);                   // 0x004aa350
    ~PtrVecBase();                                               // 0x00425990
};
struct PtrVec : PtrVecBase {
    explicit PtrVec(uint32_t n, const AllocTag& a = AllocTag()) : PtrVecBase(n, a)
    {
        uninitialized_fill_n_ptr<cSPEditorBlock*>(mpBegin, n, (cSPEditorBlock*)0);
        mpEnd = mpBegin + n;
    }
    ~PtrVec()
    {
        for (cSPEditorBlock** p = mpBegin; p < mpEnd; ++p) {
        }
    }
    cSPEditorBlock*& operator[](uint32_t i) { return mpBegin[i]; }
};

// child list of a block (vector of AutoRefCount<cSPEditorBlock>)
struct ChildList {
    AutoRefCount<cSPEditorBlock>* mpBegin;
    AutoRefCount<cSPEditorBlock>* mpEnd;
    AutoRefCount<cSPEditorBlock>* mpCapacity;
    int size() const { return mpEnd - mpBegin; }
    AutoRefCount<cSPEditorBlock>& operator[](int i) { return mpBegin[i]; }
};

// list of nearby blocks handed to the alignment code (raw pointers)
struct BlockList {
    cSPEditorBlock** mpBegin; cSPEditorBlock** mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const;                                          // 0x526430
    cSPEditorBlock*& operator[](int i) { return mpBegin[i]; }
};

// vector<OrientedPoint>
struct CandVec {
    Candidate* mpBegin; Candidate* mpEnd; Candidate* mpCap; uint32_t mAlloc[2];
    CandVec(const AllocTag&);                                    // 0x540470
    void push_back(const Candidate& c);                          // 0x4a9f30
    ~CandVec() { for (Candidate* p = mpBegin; p < mpEnd; ++p) {} Free(); }
    void Free();                                                 // 0x547c90
    int size() const { return (int)(mpEnd - mpBegin); }
    Candidate& operator[](int i) { return mpBegin[i]; }
    bool empty() const;                                          // 0x526430
};

// ---------------------------------------------------------------- editor classes
struct cSPEditorModel : RefObj {
    bool IsActive();                                    // 0x004adc40
    void SetColliding(int v);                           // 0x004adc20
    void AddBlock(cSPEditorBlock* block, int notify);   // 0x004abaf0
};

struct cSPEditorBlock : RefObj {
    char pad0[0x28 - 4];
    AutoRefCount<cSPEditorModel> mpEditorModel;         // +0x28
    char pad2c[0x48 - 0x2c];
    Vector3 mPosition;                                  // +0x48
    char pad54[0xa8 - 0x54];
    Matrix3 mOrientation;                               // +0xa8
    char padcc[0xf0 - 0xcc];
    Matrix3 mUserOrientation;                           // +0xf0
    char pad114[0x33c - 0x114];
    AutoRefCount<cSPEditorBlock> mParentBlock;          // +0x33c
    ChildList mChildren;                                // +0x340
    char pad34c[0x3e0 - 0x34c];
    AutoRefCount<cSPEditorBlock> mSymmetricBlock;       // +0x3e0
    char pad3e4[0xdc8 - 0x3e4];
    bitset<60> mFlags;                                  // +0xdc8

    cSPEditorBlock* Split(int type);                    // 0x0044f420
    bool Func453520();                                  // 0x00453520
    void Func453500(bool v);                            // 0x00453500
    void SetSymmetricBlock(cSPEditorBlock* b);          // 0x00438cc0
    void SetAsymmetricBlock(cSPEditorBlock* b);         // 0x00438df0
    void SetPosition(const Vector3& pos, bool flag);    // 0x00448e90
    void SetUserOrientation(Matrix3 m);                 // 0x0043ffa0
    void SetOrientation(const Matrix3& m, bool flag);   // 0x00449420
    void SetBaseJointScale(int v);                      // 0x0044e980
    int  CalculateSymmetrySign();                       // 0x0044f240
    void LinkChild(cSPEditorBlock* b);                  // 0x00438700
    BoundingBox GetBBox(int a, int b, int c);           // 0x0044ae00
};

inline bool IsNaN(float f) { uint32_t bits = *(uint32_t*)&f; return 0x7f800000 < (bits & 0x7fffffff); }

// @ 0x48ef30
float GetLateralAlignmentPosition(cSPEditorBlock* self, BlockList* list, Vector3* outPos,
                                  Matrix3* outBasis, float k)
{
    Vector3 pos(self->mPosition);
    *outPos = pos;
    *outBasis = self->mOrientation;
    if (list->empty())
        return -1.0f;

    Vector3 center;
    self->GetBBox(0, 0, 0).GetCenter(center);
    center[1] = self->mPosition[1];
    Vector3 lat(self->mOrientation[1]);
    lat[2] = 0.0f;
    lat = Normalize(lat);
    CandVec cands((AllocTag()));
    for (int i = 0, n = list->size(); i < n; ++i) {
        cSPEditorBlock* other = (*list)[i];
        Vector3 center2;
        other->GetBBox(0, 0, 0).GetCenter(center2);
        center2[1] = (*list)[i]->mPosition[1];
        Matrix3 m((*list)[i]->mOrientation);
        Vector3 rel = (center - center2) * Inverse(m);
        float off = rel[0];
        Vector3 axis2(m[1]);
        axis2[2] = 0.0f;
        axis2 = Normalize(axis2);
        float dot = lat.x * axis2.x + lat.y * axis2.y + lat.z * axis2.z;
        Vector3 d2(center2);
        d2[0] = d2[0] - off;
        if (0.95 < dot) {
            if (0.2f * k > Abs(off)) {
                Candidate cand;
                cand.score = 0.0f;
                PosRot b;
                Vector3 v3 = center2 - center;
                cand.score = VectorLength(v3) * Abs(off) * dot;
                Vector3 v4(rel);
                v4[0] = v4[0] - off;
                v4 = v4 * m;
                v4 += center2;
                Transform xf;
                xf.SetRotation(self->mOrientation);
                b.mPos = v4;
                if (dot != 1.0f) {
                    float ang = (float)acos(dot);
                    if (!IsNaN(ang))
                        xf.PreRotate(g_UpAxis, ang);
                }
                b.mRot = xf.mRot;
                cand.pr = b;
                cands.push_back(cand);
            }
        }
    }
    if (cands.empty()) {
        return -1.0f;
    } else {
        float best = kFloatMax;
        PosRot bestPr;
        bestPr.mPos = pos;
        bestPr.mRot = self->mOrientation;
        for (int i = 0, n = cands.size(); i < n; ++i) {
            if (best > cands[i].score) {
                best = cands[i].score;
                bestPr = cands[i].pr;
            }
        }
        *outBasis = AlignBasis(Matrix3(self->mOrientation), bestPr.mRot[1], bestPr.mRot[2]);
        *outPos = bestPr.mPos;
        return best;
    }
}

// @ 0x48f790
void UpdateSymmetryRec(cSPEditorBlock* block, int sign)
{
    if (block->mpEditorModel != 0) {
        if (block->mpEditorModel->IsActive() && block != 0 && block->mSymmetricBlock == 0) {
            if (!block->mFlags.test(0x39)) {
                cSPEditorBlock* t14 = block->Split(1);                     // sym
                t14->Func453500(!block->Func453520());
                block->SetSymmetricBlock(t14);
                t14->SetSymmetricBlock(block);
                block->SetAsymmetricBlock(t14);
                t14->SetAsymmetricBlock(block);
                block->SetPosition(block->mPosition, 0);
                block->SetUserOrientation(block->mUserOrientation);
                block->SetOrientation(block->mOrientation, 0);
                t14->SetBaseJointScale(-2);
                block->mpEditorModel->AddBlock(t14, 1);
                block->SetBaseJointScale(sign);
                t14->SetBaseJointScale(-sign);
                if (block->mParentBlock != 0) {
                    block->mpEditorModel->SetColliding(0);
                    block->mParentBlock->LinkChild(t14);
                    block->mpEditorModel->SetColliding(1);
                }
                if (block->mSymmetricBlock != 0) {
                    ChildList* len = &block->mChildren;
                    PtrVec v33(len->size());                               // copy of the child pointers
                    for (int p38 = 0, p17 = len->size(); p38 < p17; ++p38)
                        v33[p38] = (*len)[p38];
                    BlockRefVec n40;                         // blocks whose symmetric partner must be linked
                    for (int p38 = 0, p17 = (int)(v33.mpEnd - v33.mpBegin); p38 < p17; ++p38) {
                        int t40 = v33[p38]->CalculateSymmetrySign();       // cs
                        bool t32 = (t40 == sign) || (t40 == 0 && sign == -1);   // match
                        if (v33[p38]->mSymmetricBlock == 0) {
                            UpdateSymmetryRec(v33[p38], sign);
                            if (v33[p38]->mSymmetricBlock != 0 && t32)
                                n40.push_back(AutoRefCount<cSPEditorBlock>(v33[p38]->mSymmetricBlock));
                        }
                        if (!t32)
                            n40.push_back(AutoRefCount<cSPEditorBlock>(v33[p38]));
                    }
                    block->mpEditorModel->SetColliding(0);
                    if (block->mSymmetricBlock != 0) {
                        for (int p38 = 0, p17 = n40.size(); p38 < p17; ++p38)
                            block->mSymmetricBlock->LinkChild(n40[p38]);
                    }
                    block->mpEditorModel->SetColliding(1);
                }
                ChildList* tmp = &block->mChildren;
                for (int p38 = 0, p17 = tmp->size(); p38 < p17; ++p38)
                    UpdateSymmetryRec((*tmp)[p38], sign);
            }
        }
    }
}
