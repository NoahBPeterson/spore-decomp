// Slice s01202ca0 -- Spore engine (SP) segment / edge geometry helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc).
//
//   0x01202ca0  edge-frame setup: two helper calls, then three normalised edge
//               vectors (p2-p0, p3-p2, p0-p3) with their reciprocal lengths, plus
//               four callback pointers and a back pointer to the owner.
//   0x01202fd0  segment triple: three SP::Segment constructions over the three
//               16-byte points copied out of `this`, written into an output block.
//   0x012030c0  SSE fragment: |v.x| + |v.y| + |v.z| for a vector whose address the
//               caller leaves in EAX.  See work/match/scratch_s01202ca0_fixlog.txt
//               -- it is a fragment Ghidra split out of a larger routine and no
//               MSVC x86 convention delivers an argument in EAX.
#include <xmmintrin.h>

typedef unsigned char u8;
typedef unsigned int  u32;

struct __declspec(align(16)) Vec4 { float x, y, z, w; };

// --------------------------------------------------------------------------
// Callbacks installed by the edge-frame routine (addresses only, never called).
// --------------------------------------------------------------------------
void FUN_012023f0();
void FUN_01202960();
void FUN_01202af0();
void FUN_011fb220();

// --------------------------------------------------------------------------
// SSE helpers
// --------------------------------------------------------------------------

// Horizontal sum of the four squared lanes, broadcast to every lane (SSE-1
// shuffle/add, exactly as emitted by the original).
static __forceinline __m128 LaneSum(const __m128& v)
{
    __m128 sq = _mm_mul_ps(v, v);
    __m128 hi = _mm_shuffle_ps(sq, sq, 2);
    __m128 lo = _mm_shuffle_ps(sq, sq, 1);
    lo = _mm_add_ps(lo, hi);
    sq = _mm_add_ps(sq, lo);
    return _mm_shuffle_ps(sq, sq, 0);
}

// Normalise one edge in place.  `rlen` keeps len^2 while the edge is degenerate and
// the reciprocal length otherwise (the original stores both into the same slot).
static __forceinline void NormaliseEdge(__m128& v, float& rlen)
{
    float len2 = _mm_cvtss_f32(LaneSum(v));
    rlen = len2;
    if (len2 > 1.1920929e-07f) {
        __m128 len = _mm_set1_ps(len2);
        __m128 one = _mm_set1_ps(1.0f);
        __m128 half = _mm_set1_ps(0.5f);
        __m128 r = _mm_rsqrt_ps(len);
        r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(len, _mm_mul_ps(r, r))),
                                     _mm_mul_ps(r, half)));
        r = _mm_add_ps(r, _mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(len, _mm_mul_ps(r, r))),
                                     _mm_mul_ps(r, half)));
        __m128 t = _mm_andnot_ps(_mm_cmpeq_ps(_mm_setzero_ps(), len), _mm_mul_ps(len, r));
        float recip = _mm_cvtss_f32(t);
        rlen = recip;
        v = _mm_div_ps(v, _mm_set1_ps(recip));
    }
}

// --------------------------------------------------------------------------
// 0x01202ca0 -- four-point edge frame
// --------------------------------------------------------------------------

struct SPMeshFrame {
    __m128 p0;            // +0x00
    __m128 p1;            // +0x10
    __m128 p2;            // +0x20
    __m128 p3;            // +0x30
    __m128 e0;            // +0x40  p2 - p0, normalised
    __m128 e1;            // +0x50  p3 - p2, normalised
    __m128 e2;            // +0x60  p0 - p3, normalised
    float  r0;            // +0x70  reciprocal length of e0 (len^2 when degenerate)
    float  r1;            // +0x74
    float  r2;            // +0x78
    u32    id7c;          // +0x7c
    void*  owner;         // +0x80  == this
    u32    m84;           // +0x84
    u32    live;          // +0x88  always 1
    u32    count;         // +0x8c  always 3
    void (*cb0)();        // +0x90
    void (*cb1)();        // +0x94
    void (*cb2)();        // +0x98
    void (*cb3)();        // +0x9c
};

struct EdgeBuilder {
    void BuildFrame(SPMeshFrame* o, u32 p);                     // 0x01202ca0
    void StepA(__m128& a, __m128& b, __m128& c, u32 p);         // 0x01202160
    void StepB(__m128& a, u32 p);                               // 0x01202020

    u8  pad00[0x50];      // +0x00
    u32 m50;              // +0x50
};

// @ 0x01202ca0
void EdgeBuilder::BuildFrame(SPMeshFrame* o, u32 p)
{
    StepA(o->p0, o->p3, o->p2, p);
    StepB(o->p1, p);

    o->e0 = _mm_sub_ps(o->p2, o->p0);
    NormaliseEdge(o->e0, o->r0);

    o->e1 = _mm_sub_ps(o->p3, o->p2);
    NormaliseEdge(o->e1, o->r1);

    o->e2 = _mm_sub_ps(o->p0, o->p3);
    NormaliseEdge(o->e2, o->r2);

    o->live  = 1;
    o->count = 3;
    o->owner = this;
    o->id7c  = this->m50;
    o->cb0 = FUN_012023f0;
    o->cb1 = FUN_01202960;
    o->cb2 = FUN_01202af0;
    o->cb3 = FUN_011fb220;
}

// --------------------------------------------------------------------------
// 0x01202fd0 -- three SP::Segment constructions
// --------------------------------------------------------------------------

// SP::Segment -- 16-byte aligned: three 16-byte points plus a trailing tag dword.
// Only the 0x34 live bytes are copied out (the alignment padding is not).
struct SPSegment {
    __m128 p0;            // +0x00
    __m128 p1;            // +0x10
    __m128 p2;            // +0x20
    u32    tag;           // +0x30

    SPSegment* Build(const __m128& a, const __m128& b);   // 0x012016f0
};

struct SegBlock {
    u8         pad00[0x10];   // +0x00
    SPSegment  seg0;          // +0x10
    SPSegment  seg1;          // +0x50
    SPSegment  seg2;          // +0x90
    u8         padD0[0x60];   // +0xd0
    u32        count;         // +0x130
};

struct SegSrc {
    __m128 v0;                // +0x00
    __m128 v1;                // +0x10
    __m128 v2;                // +0x20

    u32 Build3(u32 a1, u32 a2, SegBlock* out);
};

// @ 0x01202fd0
u32 SegSrc::Build3(u32 a1, u32 a2, SegBlock* out)
{
    __m128 v[3];
    v[0] = this->v0;
    v[1] = this->v1;
    v[2] = this->v2;
    SPSegment s0, s1, s2;
    SPSegment* p;

    p = s0.Build(v[0], v[1]);
    out->seg0.p0 = p->p0;
    out->seg0.p1 = p->p1;
    out->seg0.p2 = p->p2;
    out->seg0.tag = p->tag;

    p = s1.Build(v[1], v[2]);
    out->seg1.p0 = p->p0;
    out->seg1.p1 = p->p1;
    out->seg1.p2 = p->p2;
    out->seg1.tag = p->tag;

    p = s2.Build(v[2], v[0]);
    out->seg2.p0 = p->p0;
    out->seg2.p1 = p->p1;
    out->seg2.p2 = p->p2;
    out->seg2.tag = p->tag;

    out->count = 3;
    return 1;
}

// --------------------------------------------------------------------------
// 0x012030c0 -- |v.x| + |v.y| + |v.z|
//
// The original consumes a pointer left in EAX by its caller.  No MSVC x86 calling
// convention delivers an argument in EAX, so this spelling (an ordinary pointer
// parameter) is the closest C++ can get; it can never be byte-exact or ABI
// equivalent.  Logged as PARTIAL in work/match/scratch_s01202ca0_fixlog.txt.
// --------------------------------------------------------------------------

// @ 0x012030c0
float AbsSum(const __m128* v)
{
    __m128 abs = _mm_max_ps(_mm_mul_ps(_mm_set1_ps(-1.0f), *v), *v);
    float z = _mm_cvtss_f32(_mm_shuffle_ps(abs, abs, 2));
    float y = _mm_cvtss_f32(_mm_shuffle_ps(abs, abs, 1));
    float x = _mm_cvtss_f32(abs);
    return z + y + x;
}