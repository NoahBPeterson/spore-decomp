// slice s00770320: one very large function at 0x00770320 (15,415 bytes).
//
// The skinning-matrix bake job of the runtime model builder.  0x007740f0 is the
// job thunk: it calls this method on the global object at 0x01630b68 and is
// registered as a job callback at 0x00775cf9.
//
// For each bone i (this->mCount bones) it:
//   * fetches the bone's local transform from a strided source array (0x30-byte
//     {rot, pos, scale} records, or 0x20-byte {rot, pos4} records with unit scale);
//   * inverts the bind matrix binds[i] (affine 4x4 cofactor inverse; the result
//     is kept from the previous bone when the determinant is 0), and multiplies
//     it by the current state matrix B;
//   * if mParent[i] != -1 it writes an attachment transform (rotation, position
//     and scale) and the current job record to slot mParent[i]; otherwise it
//     composes scale * rotation * inverse-parent-scale * translation with the
//     accumulated parent matrix A;
//   * writes bind[i] * T, transposed to 3x4, to this->mSkin[i];
//   * applies the bone's push/pop flag (job->flags[i] & 3) to the state stacks
//     (A, inverse scale V, job record, B, C).
//
// The math is SSE "SIMD scalar" code (every scalar is splatted to all lanes),
// written here with intrinsics and small inline helpers.  Vector3 values keep
// their x in lane 3, as the original's constructor does.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (scalar divss/subss, no x87).
// Complete but not byte-exact (see nonmatching.txt).
#include "types.h"
#include <xmmintrin.h>
#include <string.h>
#include <new>

// ------------------------------------------------------------------ math helpers
struct __declspec(align(16)) Mat4 {
    __m128 r[4];        // rows; rows 0-2 are the 3x3 part, row 3 the translation
    Mat4() {}
    Mat4(const Mat4& o) { r[0] = o.r[0]; r[1] = o.r[1]; r[2] = o.r[2]; r[3] = o.r[3]; }
    Mat4& operator=(const Mat4& o) { r[0] = o.r[0]; r[1] = o.r[1]; r[2] = o.r[2]; r[3] = o.r[3]; return *this; }
};

static __forceinline __m128 SplatX(__m128 v) { return _mm_shuffle_ps(v, v, 0x00); }
static __forceinline __m128 SplatY(__m128 v) { return _mm_shuffle_ps(v, v, 0x55); }
static __forceinline __m128 SplatZ(__m128 v) { return _mm_shuffle_ps(v, v, 0xaa); }
static __forceinline __m128 SplatW(__m128 v) { return _mm_shuffle_ps(v, v, 0xff); }

// Vector3 from three scalars: (x, y, z, x).
static __forceinline __m128 MakeVec3(float x, float y, float z)
{
    __m128 vx = _mm_set1_ps(x);
    __m128 vy = _mm_set1_ps(y);
    __m128 vz = _mm_set1_ps(z);
    return _mm_unpacklo_ps(_mm_unpacklo_ps(vx, vz), _mm_unpacklo_ps(vy, vx));
}

// Vector4 from four splatted scalars: (x, y, z, w).
static __forceinline __m128 MakeVec4(const __m128& x, const __m128& y, const __m128& z, const __m128& w)
{
    return _mm_shuffle_ps(_mm_shuffle_ps(x, y, 0x10), _mm_shuffle_ps(z, w, 0x32), 0x88);
}

// Vector4 from four scalars, built the way the Vector4(x, y, z, w) constructor does.
static __forceinline __m128 MakeVec4u(float x, float y, float z, float w)
{
    return _mm_unpacklo_ps(_mm_unpacklo_ps(_mm_set1_ps(x), _mm_set1_ps(z)),
                           _mm_unpacklo_ps(_mm_set1_ps(y), _mm_set1_ps(w)));
}

// xyz part of a Vector4 as a Vector3: (x, y, z, x).
static __forceinline __m128 Vec3Of(__m128 v)
{
    return _mm_shuffle_ps(_mm_shuffle_ps(v, v, 0x10), v, 0x28);
}

// Affine product a * b: rows 0-2 of a have an implicit w of 0, row 3 a w of 1.
static __forceinline void Mul(Mat4& o, const Mat4& a, const Mat4& b)
{
    const __m128 one = _mm_set1_ps(1.0f);
    __m128 r0 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(SplatX(a.r[0]), b.r[0]), _mm_mul_ps(SplatY(a.r[0]), b.r[1])),
                           _mm_mul_ps(SplatZ(a.r[0]), b.r[2]));
    __m128 r1 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(SplatX(a.r[1]), b.r[0]), _mm_mul_ps(SplatY(a.r[1]), b.r[1])),
                           _mm_mul_ps(SplatZ(a.r[1]), b.r[2]));
    __m128 r2 = _mm_add_ps(_mm_add_ps(_mm_mul_ps(SplatX(a.r[2]), b.r[0]), _mm_mul_ps(SplatY(a.r[2]), b.r[1])),
                           _mm_mul_ps(SplatZ(a.r[2]), b.r[2]));
    __m128 r3 = _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_mul_ps(SplatX(a.r[3]), b.r[0]),
                                                 _mm_mul_ps(SplatY(a.r[3]), b.r[1])),
                                      _mm_mul_ps(SplatZ(a.r[3]), b.r[2])),
                           _mm_mul_ps(one, b.r[3]));
    o.r[0] = r0; o.r[1] = r1; o.r[2] = r2; o.r[3] = r3;
}

// Diagonal scale matrix from the xyz lanes of s (row 3 zero).
static __forceinline void ScaleMat(Mat4& o, __m128 s)
{
    const __m128 z = _mm_setzero_ps();
    o.r[0] = _mm_shuffle_ps(_mm_shuffle_ps(z, s, 0x05), z, 0xe2);
    o.r[1] = _mm_shuffle_ps(_mm_shuffle_ps(z, s, 0x50), z, 0xe8);
    o.r[2] = _mm_shuffle_ps(z, _mm_shuffle_ps(z, s, 0xaf), 0x24);
    o.r[3] = z;
}

// Translation matrix: identity 3x3, row 3 = t.
static __forceinline void TranslateMat(Mat4& o, __m128 t)
{
    ScaleMat(o, _mm_set1_ps(1.0f));
    o.r[3] = t;
}

// Rotation matrix of a unit quaternion (computed on q * sqrt(2)); row 3 zero.
static __forceinline void RotationMat(Mat4& o, __m128 q)
{
    const __m128 z = _mm_setzero_ps();
    const __m128 half = _mm_set1_ps(0.5f);
    __m128 q2 = _mm_mul_ps(_mm_set1_ps(1.41421354f), q);
    __m128 d = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(z, q2), q2), half);            // 0.5 - q*q
    __m128 xy = _mm_mul_ps(_mm_shuffle_ps(q2, q2, 0x09), q2);                  // (yx, zy, xz)
    __m128 wv = _mm_mul_ps(SplatW(q2), _mm_shuffle_ps(q2, q2, 0x12));          // (wz, wx, wy)
    __m128 p = _mm_add_ps(wv, xy);
    __m128 m = _mm_sub_ps(xy, wv);
    __m128 l = _mm_add_ps(_mm_shuffle_ps(d, d, 0x09), d);                      // 1 - 2(a^2 + b^2)
    o.r[0] = _mm_shuffle_ps(_mm_shuffle_ps(l, p, 0x01), m, 0x28);
    o.r[1] = _mm_shuffle_ps(_mm_shuffle_ps(m, l, 0x20), p, 0x18);
    o.r[2] = _mm_shuffle_ps(_mm_shuffle_ps(p, m, 0x12), l, 0x08);
    o.r[3] = z;
}

// Quaternion product a * b.
static __forceinline __m128 QuatMul(__m128 a, __m128 b)
{
    __m128 a3 = Vec3Of(a);
    __m128 b3 = Vec3Of(b);
    __m128 cross = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(b3, b3, 0x12), _mm_shuffle_ps(a3, a3, 0x09)),
                              _mm_mul_ps(_mm_shuffle_ps(b3, b3, 0x09), _mm_shuffle_ps(a3, a3, 0x12)));
    __m128 v = _mm_add_ps(cross, _mm_add_ps(_mm_mul_ps(SplatW(a), b3), _mm_mul_ps(SplatW(b), a3)));
    __m128 pr = _mm_mul_ps(b3, a3);
    __m128 dot = SplatX(_mm_add_ps(_mm_add_ps(_mm_shuffle_ps(pr, pr, 0x02), _mm_shuffle_ps(pr, pr, 0x01)), pr));
    __m128 w = _mm_sub_ps(_mm_mul_ps(SplatW(a), SplatW(b)), dot);
    return MakeVec4(SplatX(v), SplatY(v), SplatZ(v), w);
}

static __forceinline __m128 QuatConjugate(__m128 q)
{
    const __m128 z = _mm_setzero_ps();
    return MakeVec4(_mm_sub_ps(z, SplatX(q)), _mm_sub_ps(z, SplatY(q)), _mm_sub_ps(z, SplatZ(q)), SplatW(q));
}

// Cofactor inverse of the affine matrix m (16 floats, column 3 taken as
// (0,0,0,1)).  Returns false and leaves o untouched when the 3x3 determinant is 0.
static __forceinline bool AffineInverse(Mat4& o, const float* m)
{
    const __m128 Z = _mm_set1_ps(0.0f);
    const __m128 O = _mm_set1_ps(1.0f);
#define E(k) _mm_set1_ps(m[k])
#define MUL _mm_mul_ps
#define SUB _mm_sub_ps
#define ADD _mm_add_ps
    __m128 det = ADD(ADD(MUL(SUB(MUL(E(5), E(10)), MUL(E(6), E(9))), E(0)),
                         MUL(SUB(MUL(E(6), E(8)), MUL(E(10), E(4))), E(1))),
                     MUL(SUB(MUL(E(9), E(4)), MUL(E(5), E(8))), E(2)));
    if (_mm_movemask_ps(_mm_cmpeq_ps(det, Z)) == 0xf)
        return false;

    __m128 i32 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(5), E(2)), MUL(E(6), E(1))), E(12)),
                                    MUL(SUB(MUL(E(6), E(0)), MUL(E(4), E(2))), E(13))),
                                MUL(SUB(MUL(E(4), E(1)), MUL(E(5), E(0))), E(14))), det);
    __m128 i31 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(13), E(2)), MUL(E(14), E(1))), E(8)),
                                    MUL(SUB(MUL(E(14), E(0)), MUL(E(12), E(2))), E(9))),
                                MUL(SUB(MUL(E(12), E(1)), MUL(E(13), E(0))), E(10))), det);
    __m128 i30 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(13), E(10)), MUL(E(9), E(14))), E(4)),
                                    MUL(SUB(MUL(E(14), E(8)), MUL(E(10), E(12))), E(5))),
                                MUL(SUB(MUL(E(9), E(12)), MUL(E(13), E(8))), E(6))), det);
    __m128 i22 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(1), Z), MUL(E(5), Z)), E(12)),
                                    MUL(SUB(MUL(E(5), E(0)), MUL(E(4), E(1))), O)),
                                MUL(SUB(MUL(E(4), Z), MUL(E(0), Z)), E(13))), det);
    __m128 i21 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(1), O), MUL(E(13), Z)), E(8)),
                                    MUL(SUB(MUL(E(13), E(0)), MUL(E(12), E(1))), Z)),
                                MUL(SUB(MUL(E(12), Z), MUL(E(0), O)), E(9))), det);
    __m128 i20 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(13), E(8)), MUL(E(9), E(12))), Z),
                                    MUL(SUB(MUL(E(9), O), MUL(E(13), Z)), E(4))),
                                MUL(SUB(MUL(E(12), Z), MUL(E(8), O)), E(5))), det);
    __m128 i12 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(4), E(2)), MUL(E(6), E(0))), O),
                                    MUL(SUB(MUL(E(0), Z), MUL(E(4), Z)), E(14))),
                                MUL(SUB(MUL(E(6), Z), MUL(E(2), Z)), E(12))), det);
    __m128 i11 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(12), E(2)), MUL(E(14), E(0))), Z),
                                    MUL(SUB(MUL(E(0), O), MUL(E(12), Z)), E(10))),
                                MUL(SUB(MUL(E(14), Z), MUL(E(2), O)), E(8))), det);
    __m128 i10 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(10), E(12)), MUL(E(14), E(8))), Z),
                                    MUL(SUB(MUL(E(8), O), MUL(E(12), Z)), E(6))),
                                MUL(SUB(MUL(E(14), Z), MUL(E(10), O)), E(4))), det);
    __m128 i02 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(2), Z), MUL(E(6), Z)), E(13)),
                                    MUL(SUB(MUL(E(5), Z), MUL(E(1), Z)), E(14))),
                                MUL(SUB(MUL(E(6), E(1)), MUL(E(5), E(2))), O)), det);
    __m128 i01 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(2), O), MUL(E(14), Z)), E(9)),
                                    MUL(SUB(MUL(E(13), Z), MUL(E(1), O)), E(10))),
                                MUL(SUB(MUL(E(14), E(1)), MUL(E(13), E(2))), Z)), det);
    __m128 i00 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(10), O), MUL(E(14), Z)), E(5)),
                                    MUL(SUB(MUL(E(13), Z), MUL(E(9), O)), E(6))),
                                MUL(SUB(MUL(E(9), E(14)), MUL(E(13), E(10))), Z)), det);
#undef E
#undef MUL
#undef SUB
#undef ADD
    o.r[0] = _mm_unpacklo_ps(_mm_unpacklo_ps(i00, i02), _mm_unpacklo_ps(i01, i00));
    o.r[1] = _mm_unpacklo_ps(_mm_unpacklo_ps(i10, i12), _mm_unpacklo_ps(i11, i10));
    o.r[2] = _mm_unpacklo_ps(_mm_unpacklo_ps(i20, i22), _mm_unpacklo_ps(i21, i20));
    o.r[3] = _mm_unpacklo_ps(_mm_unpacklo_ps(i30, i32), _mm_unpacklo_ps(i31, i30));
    return true;
}

// ------------------------------------------------------------------ data types
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o);          // @ 0x004098a0 (out of line, fld/fstp copy)
};
// Component-wise division; both operands are taken by value, so each is copied
// through the out-of-line copy constructor.
static __forceinline Vector3 operator/(Vector3 a, Vector3 b)
{
    return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
}

// Bone transform record (0x30 bytes): source format and the attachment array.
struct __declspec(align(16)) BoneXform {
    __m128  rot;        // +0x00 quaternion
    Vector3 pos;        // +0x10
    Vector3 scale;      // +0x1c
    float   f28, f2c;   // +0x28
};
// The 0x20-byte source format: rotation and a Vector4 position, no scale.
struct __declspec(align(16)) BoneXform20 {
    __m128 rot;         // +0x00
    __m128 pos;         // +0x10
};

// 0xb0-byte job record (same layout as JobRecordI in s0076ed30).
struct __declspec(align(16)) BakeRecord {
    char   c;               // +0x00  set once a hierarchy transform was applied
    float  a, b, d;         // +0x04  offset
    __m128 v[8];            // +0x10  forward matrix (v[0..3]) and inverse matrix (v[4..7])
    float  x, y, z;         // +0x90  scale
    float  w, p, q;         // +0x9c  inverse scale
    BakeRecord() {}
    BakeRecord(const BakeRecord& o);    // @ 0x0076f580
};

struct StridedArray {
    char  pad0[8];
    char* mpData;           // +0x08
    int   pad0c;
    int   mStride;          // +0x10
    void* At(int i);        // @ 0x011fda50: mpData + mStride * i
};

template <class T> struct VecView { T* mpBegin; };

struct BakeJob {
    StridedArray*   mpSource;   // +0x00 local bone transforms
    int             pad04, pad08;
    VecView<int>*   mpFlags;    // +0x0c push/pop flags per bone
    VecView<Mat4>*  mpBinds;    // +0x10 bind matrices per bone
};

// Quaternion of a rotation matrix (eps = trace threshold vector).
extern "C" void MatrixToQuat(__m128* out, const Mat4* m, const __m128* eps);   // @ 0x0075ad80

struct Unk770320 {
    int          pad00;
    int          mCount;        // +0x04 bones
    int          pad08;
    int*         mpParent;      // +0x0c attachment slot per bone, or -1
    char*        mpSkin;        // +0x10 3x4 skin matrices, 0x30 bytes each
    BoneXform*   mpAttach;      // +0x14
    BakeRecord*  mpRecords;     // +0x18

    // @ 0x00770320
    int Method(int unused, BakeJob* job);
};

enum { kStackDepth = 64 };

int Unk770320::Method(int unused, BakeJob* job)
{
    (void)unused;
    StridedArray* src = job->mpSource;

    const Vector3 zero3(0.0f, 0.0f, 0.0f);
    const Vector3 ones(1.0f, 1.0f, 1.0f);
    Vector3 V(1.0f, 1.0f, 1.0f);            // current inverse parent scale

    Mat4 identity;
    identity.r[0] = MakeVec4u(1.0f, 0.0f, 0.0f, 0.0f);
    identity.r[1] = MakeVec4u(0.0f, 1.0f, 0.0f, 0.0f);
    identity.r[2] = MakeVec4u(0.0f, 0.0f, 1.0f, 0.0f);
    identity.r[3] = _mm_setzero_ps();
    Mat4 A = identity;                      // accumulated parent transform
    Mat4 B = identity;                      // bind matrix of the current parent
    Mat4 C = identity;                      // rotation applied to attachment positions

    BakeRecord next;                        // record built for this bone
    BakeRecord cur;                         // record of the current parent
    memset(&next, 0, sizeof(next));
    memset(&cur, 0, sizeof(cur));
    cur.c = 0;

    Mat4 stackA[kStackDepth];
    Mat4 stackB[kStackDepth];
    Mat4 stackC[kStackDepth];
    Vector3 stackV[kStackDepth];
    BakeRecord stackRec[kStackDepth];
    Mat4* pA = stackA;
    Mat4* pB = stackB;
    Mat4* pC = stackC;
    Vector3* pV = stackV;
    BakeRecord* pRec = stackRec;

    // Inverses kept across bones (a singular matrix keeps the previous result).
    Mat4 invBind;
    Mat4 invM1;
    Mat4 invM0;

    BoneXform local;
    const __m128 zeroSplat = _mm_set1_ps(0.0f);

    for (int i = 0; i < mCount; ++i) {
        if (src->mStride == 0x30) {
            const BoneXform* p = (const BoneXform*)src->At(i);
            local.rot = p->rot;
            local.pos.x = p->pos.x;
            local.pos.y = p->pos.y;
            local.pos.z = p->pos.z;
            local.scale.x = p->scale.x;
            local.scale.y = p->scale.y;
            local.scale.z = p->scale.z;
            local.f28 = p->f28;
            local.f2c = p->f2c;
        } else {
            const BoneXform20* p = (const BoneXform20*)src->At(i);
            local.rot = p->rot;
            __m128 pos = p->pos;
            local.pos.x = pos.m128_f32[0];
            local.pos.y = pos.m128_f32[1];
            local.pos.z = pos.m128_f32[2];
            local.scale.x = ones.x;
            local.scale.y = ones.y;
            local.scale.z = ones.z;
        }

        const Mat4& bind = job->mpBinds->mpBegin[i];
        float* skin = (float*)(mpSkin + i * 0x30);

        AffineInverse(invBind, (const float*)&bind);
        Mat4 M;
        Mul(M, invBind, B);

        Mat4 T;                             // this bone's accumulated transform
        Mat4 Cnext;
        Vector3 Vnext;

        int parent = mpParent[i];
        if (parent != -1) {
            // Attachment: rotation and offset relative to M, recorded in slot `parent`.
            __m128 q;
            __m128 eps = zeroSplat;
            MatrixToQuat(&q, &M, &eps);

            BoneXform& att = mpAttach[parent];
            att.rot = QuatMul(QuatConjugate(q), local.rot);
            __m128 mt = M.r[3];
            att.pos.x = local.pos.x - mt.m128_f32[0];
            att.pos.y = local.pos.y - mt.m128_f32[1];
            att.pos.z = local.pos.z - mt.m128_f32[2];
            att.scale.x = local.scale.x;
            att.scale.y = local.scale.y;
            att.scale.z = local.scale.z;

            __m128 ap = MakeVec3(att.pos.x, att.pos.y, att.pos.z);
            __m128 rp = _mm_add_ps(_mm_add_ps(_mm_mul_ps(SplatY(ap), C.r[1]), _mm_mul_ps(SplatX(ap), C.r[0])),
                                   _mm_mul_ps(SplatZ(ap), C.r[2]));
            att.pos.x = rp.m128_f32[0];
            att.pos.y = rp.m128_f32[1];
            att.pos.z = rp.m128_f32[2];

            Cnext = identity;
            new (&mpRecords[parent]) BakeRecord(cur);

            att.scale.x = ones.x;
            att.scale.y = ones.y;
            att.scale.z = ones.z;

            next.c = 0;
            next.a = zero3.x;
            next.b = zero3.y;
            next.d = zero3.z;
            next.v[0] = identity.r[0];
            next.v[1] = identity.r[1];
            next.v[2] = identity.r[2];
            next.v[3] = identity.r[3];
            next.x = local.scale.x;
            next.y = local.scale.y;
            next.z = local.scale.z;
            next.w = ones.x;
            next.p = ones.y;
            next.q = ones.z;

            Mat4 S;
            ScaleMat(S, MakeVec3(local.scale.x, local.scale.y, local.scale.z));
            Mul(T, S, invBind);

            Vnext.x = 1.0f / local.scale.x;
            Vnext.y = 1.0f / local.scale.y;
            Vnext.z = 1.0f / local.scale.z;
        } else {
            Mat4 MC;
            Mul(MC, M, C);
            Cnext = MC;

            __m128 scale;
            if (cur.c != 0) {
                scale = MakeVec3(local.scale.x, local.scale.y, local.scale.z);
                // Child of a hierarchy record: compose with the record's matrices.
                Mat4 S, R, SR, S2, SRS2, Tr, X;
                ScaleMat(S, scale);
                RotationMat(R, local.rot);
                Mul(SR, S, R);
                ScaleMat(S2, MakeVec3(cur.w, cur.p, cur.q));
                Mul(SRS2, SR, S2);
                TranslateMat(Tr, MakeVec3(local.pos.x, local.pos.y, local.pos.z));
                Mul(X, SRS2, Tr);

                Mat4 W, curV;
                curV.r[0] = cur.v[0]; curV.r[1] = cur.v[1]; curV.r[2] = cur.v[2]; curV.r[3] = cur.v[3];
                Mul(W, X, curV);
                next.v[0] = W.r[0];
                next.v[1] = W.r[1];
                next.v[2] = W.r[2];
                next.v[3] = W.r[3];
                next.c = 1;
                next.a = cur.a;
                next.b = cur.b;
                next.d = cur.d;

                AffineInverse(invM1, (const float*)&M);
                Mat4 curI, WI;
                curI.r[0] = cur.v[4]; curI.r[1] = cur.v[5]; curI.r[2] = cur.v[6]; curI.r[3] = cur.v[7];
                Mul(WI, curI, invM1);
                next.v[4] = WI.r[0];
                next.v[5] = WI.r[1];
                next.v[6] = WI.r[2];
                next.v[7] = WI.r[3];
            } else {
                // First hierarchy level: offset scaled by the record's scale.
                next.c = 1;
                next.a = local.pos.x * cur.x;
                next.b = cur.y * local.pos.y;
                next.d = cur.z * local.pos.z;
                scale = MakeVec3(local.scale.x, local.scale.y, local.scale.z);

                Mat4 S, R, SR;
                RotationMat(R, local.rot);
                ScaleMat(S, scale);
                Mul(SR, S, R);
                next.v[0] = SR.r[0];
                next.v[1] = SR.r[1];
                next.v[2] = SR.r[2];
                next.v[3] = SR.r[3];

                AffineInverse(invM0, (const float*)&M);
                next.v[4] = invM0.r[0];
                next.v[5] = invM0.r[1];
                next.v[6] = invM0.r[2];
                next.v[7] = invM0.r[3];
            }

            next.x = ones.x;
            next.y = ones.y;
            next.z = ones.z;
            Vector3 invScale = ones / local.scale;
            next.w = invScale.x;
            next.p = invScale.y;
            next.q = invScale.z;

            // T = scale * rotation * inverse parent scale * translation * A
            Mat4 S, R, SR, SV, SRV, Tr, X;
            ScaleMat(S, scale);
            RotationMat(R, local.rot);
            Mul(SR, S, R);
            ScaleMat(SV, MakeVec3(V.x, V.y, V.z));
            Mul(SRV, SR, SV);
            TranslateMat(Tr, MakeVec3(local.pos.x, local.pos.y, local.pos.z));
            Mul(X, SRV, Tr);
            Mul(T, X, A);

            Vnext = invScale;
        }

        // Skin matrix: bind * T, stored transposed as 3x4.
        Mat4 K;
        Mul(K, bind, T);
        skin[0]  = K.r[0].m128_f32[0];
        skin[1]  = K.r[1].m128_f32[0];
        skin[2]  = K.r[2].m128_f32[0];
        skin[3]  = K.r[3].m128_f32[0];
        skin[4]  = K.r[0].m128_f32[1];
        skin[5]  = K.r[1].m128_f32[1];
        skin[6]  = K.r[2].m128_f32[1];
        skin[7]  = K.r[3].m128_f32[1];
        skin[8]  = K.r[0].m128_f32[2];
        skin[9]  = K.r[1].m128_f32[2];
        skin[10] = K.r[2].m128_f32[2];
        skin[11] = K.r[3].m128_f32[2];

        switch (job->mpFlags->mpBegin[i] & 3) {
        case 2:     // push the current state, then descend into this bone
            *pA = A;
            *pV = V;
            ++pV;
            new (pRec) BakeRecord(cur);
            ++pRec;
            *pB = B;
            *pC = C;
            ++pA;
            ++pB;
            ++pC;
            // fall through
        case 0:     // this bone becomes the current parent
            A = T;
            V = Vnext;
            new (&cur) BakeRecord(next);
            B = bind;
            C = Cnext;
            break;
        case 1:     // pop the saved state
            --pA;
            A = *pA;
            --pV;
            V = *pV;
            --pRec;
            new (&cur) BakeRecord(*pRec);
            --pB;
            --pC;
            B = *pB;
            C = *pC;
            break;
        default:
            break;
        }
    }
    return 1;
}
