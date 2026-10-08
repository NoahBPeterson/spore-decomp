// Slice s0048e590: SP::EditorUtils::GetLowAngleOffset (0x48e590, 2459 bytes, cdecl).
//
// Given an editor block, the list of candidate neighbour blocks and a tolerance scale, it
// works in the parent's local frame: the block position is moved into the parent's rotated
// frame (pos - parent.offset) * Transposed(parent.rotation). Each candidate that lies within
// 0.2*scale on the X and/or Y axis snaps the position onto it and is scored (|snap| * |cand|
// length product). The lowest scoring snap is rotated back to world space and returned
// through `out`; an optional "low angle" check (bit 30 of the block's attribute bitset, no
// parent) can instead yield a Z-only offset. Returns the winning score, or -1.0 if none.
//
// Module flags: editor /Od region, `/Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast` (no /EHsc).
#include "types.h"
#include <math.h>
#include <float.h>
#pragma intrinsic(fabs)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    float& operator[](int i) { return (&x)[i]; }
};

// cSPVector3R: what the vector operators return; a Vector3 built from one goes through the copy ctor.
struct Vector3R : Vector3 {};

// rw::math::fpu::Vector3Template<float,0> (out-of-line copy ctor, fld/fstp)
struct RwVector3 {
    float x, y, z;
    RwVector3(const RwVector3& o);  // 0x004098a0
};

struct Matrix33 {
    float m[9];
};

struct Matrix3 {
    Vector3 m[3];
    Matrix3() {}
    Matrix3(const Matrix33& other);  // 0x0041cb40
};

Vector3R operator-(const Vector3& a, const RwVector3& b);  // 0x0041db10
Vector3R operator-(const Vector3& a, const Vector3& b);    // 0x0041db10
Vector3R operator+(const Vector3& a, const RwVector3& b); // 0x0041dc10
Vector3R operator*(const Vector3& v, const Matrix3& m);    // 0x0041daf0
Matrix3 Transposed(const Matrix3& m);                     // 0x0041ded0
float VectorLength(const Vector3& v);                     // 0x0040ae50

extern const Matrix33 kIdentity33;  // 0x015d63a8
extern const RwVector3 kZero3;      // 0x015d64d8

inline float Abs(float x)
{
    float r = (float)fabs((double)x);
    return r;
}

template <int N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    __forceinline bool test(uint32_t n) const
    {
        if (n < N) {
            uint32_t word = mWord[n >> 5];
            return (word & (1u << (n % 32))) != 0;
        }
        return false;
    }
};

struct AllocTag {
    AllocTag() {}
};

// One candidate: score followed by the snapped position (16 bytes).
struct Candidate {
    float score;
    Vector3 pos;
};

// eastl::vector<Candidate, sp_vector_allocator> (trivially destructible elements)
struct CandVec {
    Candidate* mpBegin;
    Candidate* mpEnd;
    Candidate* mpCapacity;

    CandVec(const AllocTag&);            // 0x00540470
    ~CandVec()
    {
        for (Candidate* p = mpBegin; p < mpEnd; ++p)
            p->~Candidate();
        DoFree();
    }
    void DoFree();                       // 0x00554b10
    bool empty() const;                  // 0x00526430
    void push_back(const Candidate& c);  // 0x004a9e40
};

struct EditorBlock;

// SP::FixedVectorRef<SP::cSPEditorBlock*>
struct BlockList {
    EditorBlock** mpBegin;
    EditorBlock** mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const;  // 0x00526430
    EditorBlock** at(int i) { return mpBegin + i; }
};

struct Parent {
    uint32_t pad00[0x12];
    Vector3 mOffset;  // +0x48
    uint32_t pad54[3];
    Matrix3 mRotation;  // +0x60
};

struct Block {
    char pad00[0x28];
    struct SrcObj { float Get(); } *mpSource;  // +0x28 (thiscall getter, 0x004adaa0)
    char pad2c[0x48 - 0x2c];
    Vector3 mPosition;                         // +0x48
    char pad54[0x33c - 0x54];
    Parent* mpParent;                          // +0x33c
    Parent* GetParent() { return mpParent; }
    char pad340[0xdc8 - 0x340];
    bitset<60> mFlags;                         // +0xdc8
};

// @ 0x48e590
float F_48e590(Block* self, BlockList* blocks, Vector3* out, float scale)
{
    Matrix3 xform(kIdentity33);
    RwVector3 origin(kZero3);
    if (self->GetParent()) {
        Parent* parent = self->GetParent();
        xform = parent->mRotation;
        parent = self->GetParent();
        origin = *(RwVector3*)&parent->mOffset;
    }
    Vector3 rel = (self->mPosition - origin) * Transposed(xform);
    *out = self->mPosition;

    bool lowAngle = false;
    if (self->mFlags.test(30) && self->GetParent() == 0)
        lowAngle = true;
    bool haveBlocks = self->mFlags.test(53) && !blocks->empty();
    if (!haveBlocks && !lowAngle)
        return -1.0f;

    float bestScore = -1.0f;
    float lenZ = -1.0f;
    Vector3 resultPos;
    Vector3 zOnly;

    CandVec cands((AllocTag()));
    for (int i = 0, n = blocks->size(); i < n; ++i) {
        Block* blk = (Block*)*blocks->at(i);
        Vector3 candRel = (blk->mPosition - origin) * Transposed(xform);
        float dx = candRel[0] - rel[0];
        float dy = candRel[1] - rel[1];
        bool hit = false;
        Vector3 tgt = rel;
        float adx = Abs(dx);
        if (adx < 0.2f * scale) {
            tgt[0] += dx;
            hit = true;
        }
        float ady = Abs(dy);
        if (ady < 0.2f * scale) {
            tgt[1] += dy;
            hit = true;
        }
        if (hit) {
            Candidate c;
            c.score = 0.0f;
            Vector3 a = tgt - rel;
            Vector3 b = candRel - rel;
            c.score = VectorLength(a) * VectorLength(b);
            c.pos = tgt;
            cands.push_back(c);
        }
    }

    if (!cands.empty()) {
        float best = FLT_MAX;
        Vector3 bestPos = rel;
        for (int j = 0, m = (int)(cands.mpEnd - cands.mpBegin); j < m; ++j) {
            if (best > cands.mpBegin[j].score) {
                best = cands.mpBegin[j].score;
                bestPos = cands.mpBegin[j].pos;
            }
        }
        resultPos = (bestPos * xform) + origin;
        bestScore = best;
    }

    if (lowAngle) {
        Vector3 w = self->mPosition;
        w[2] = 0.0f;
        float thr = self->mpSource->Get() * 0.04f * scale;
        if (VectorLength(w) < thr) {
            w = self->mPosition;
            w[0] = 0.0f;
            w[1] = 0.0f;
            zOnly = w;
            lenZ = VectorLength(w);
        }
    }

    if (lenZ == -1.0f && bestScore == -1.0f)
        return -1.0f;
    if (lenZ != -1.0f) {
        *out = zOnly;
        return lenZ;
    }
    *out = resultPos;
    return bestScore;
}
