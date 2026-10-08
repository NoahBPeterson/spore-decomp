// w1g1 slice s00508400 -- anim container teardown plus a tiny two-float setter.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE (movss for the float stores).

typedef unsigned int uint32_t;

// @ 0x00508780
struct TwoFloats {
    float a, b;
    TwoFloats* Set(float x, float y);
};
TwoFloats* TwoFloats::Set(float x, float y)
{
    a = x;
    b = y;
    return this;
}

// ---------------------------------------------------------------------------
// Helpers used by the 0x508400 teardown (all masked relocations).
// ---------------------------------------------------------------------------
void DestroyKeyRange(void* begin, void* end);        // eastl::copy_impl do_copy
void DestroyPairRange(void* begin, void* end);       // vector<pair<int,float>>::erase
void DestroyRangeA(void* begin, void* end);          // 0x0050e690
void DestroyRangeB(void* begin, void* end);          // 0x004769b0 (DwordVector::erase)

struct BigContainer {
    char pad[0x200];

    int Count() const { return (*(int*)((char*)this + 0xe8) - *(int*)((char*)this + 0xe4)) >> 2; }
    int* At(int i) const { return *(int**)((char*)this + 0xe4) + i; }
    void* Sub(int off) const { return *(void**)((char*)this + off); }
    void Clear();    // 0x00508400
};

// @ 0x00508400  (container teardown)
void BigContainer::Clear()
{
    char* b = (char*)this;
    DestroyKeyRange(b + 8, b + 0xc);
    DestroyKeyRange(b + 0x1c, b + 0x20);
    DestroyPairRange(b + 0x30, b + 0x34);
    DestroyRangeA(b + 0x44, b + 0x48);
    DestroyRangeB(b + 0x58, b + 0x5c);
    DestroyRangeB(b + 0x6c, b + 0x70);
    DestroyRangeB(b + 0x80, b + 0x84);
    DestroyRangeB(b + 0x94, b + 0x98);
    DestroyRangeB(b + 0xa8, b + 0xac);
    DestroyRangeB(b + 0xbc, b + 0xc0);
    DestroyRangeB(b + 0x110, b + 0x114);
    DestroyRangeB(b + 0x138, b + 0x13c);
    DestroyPairRange(b + 0x124, b + 0x128);
    for (int i = 0; i < Count(); ++i) {
        int* p = At(i);
        if (p) { /* destroy *p then free */ DestroyRangeB(p, p); }
        *At(i) = 0;
    }
}

// ---------------------------------------------------------------------------
// Per-triangle tangent / bitangent builder (function at VA 005087b0, defined below)
// For every triangle corner (pairs[i] = {first, corner}) it derives a tangent frame from the
// UV edge vectors; when the UV determinant is degenerate it falls back to a cross-product frame
// built from the vertex normal.  Results go to tangents[i] = {tangent, bitangent}.
// ---------------------------------------------------------------------------
struct Vec2 {
    float x, y;
    Vec2() {}
    Vec2(float a, float b) { x = a; y = b; }
    Vec2& operator=(const Vec2& o) { x = o.x; y = o.y; return *this; }
    float& operator[](int i) { return ((float*)this)[i]; }
};
Vec2 Vec2Sub_0050cfb0(const Vec2& a, const Vec2& b);        // 0x0050cfb0
Vec2 Vec2Mul_0050e190(const Vec2& v, const float& s);       // 0x0050e190

struct V3Base { float x, y, z; };
struct Vec3 : V3Base {                                // movss member-wise assignment
    Vec3() {}
    Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float& operator[](int i) { return ((float*)this)[i]; }
};
struct V3Out : V3Base {                               // rw Vector3: out-of-line copy ctor
    V3Out() {}
    V3Out(const V3Out& o);                            // 0x004098a0
    V3Out(const Vec3& o) { x = o.x; y = o.y; z = o.z; }
};
struct VecC : V3Out {};                               // plain (trivial) assignment
Vec3 operator-(const V3Base& a, const V3Base& b);     // 0x0041db10
Vec3 operator+(const V3Base& a, const V3Base& b);     // 0x0041dc10
Vec3 operator*(const float& s, const V3Base& v);      // 0x0041de40
V3Out Cross(const V3Out& a, const V3Out& b);          // 0x0044e460
VecC Normalize(const V3Out& v);                       // 0x00436ce0

struct TanPair {
    V3Out t, b;
    TanPair(const V3Out& a, const V3Out& c) : t(a), b(c) {}
};

struct IntVec {
    int* b; int* e; int* c; int pad0, pad1;
    int& operator[](unsigned i) { int* q = b + i; return *q; }
};
struct V3Vec {
    V3Out* b; V3Out* e; V3Out* c; int pad0, pad1;
    V3Out& operator[](int i) { V3Out* q = b + i; return *q; }
};
struct V2Vec {
    Vec2* b; Vec2* e; Vec2* c; int pad0, pad1;
    unsigned size() const { return e - b; }
};
struct TanVec {
    TanPair* b; TanPair* e; TanPair* c; int pad0, pad1;
    void resize(unsigned n);                          // 0x0050d3c0
};
struct CornerRef { int first; unsigned corner; };

static inline float DotV(const V3Base& a, const V3Base& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

static const signed char kNextOff[3] = { 1, 1, -2 };
static const signed char kPrevOff[3] = { 2, -1, -1 };

inline void Neighbors(unsigned c, unsigned& nx, unsigned& pv) {
    uint32_t hole[8];
    unsigned m = c - c / 3 * 3;
    nx = c + kNextOff[m];
    pv = c + kPrevOff[m];
}

struct TangentBuilder {
    char pad0[8];
    V3Vec pos;       // +0x08
    V3Vec nrm;       // +0x1c
    V2Vec uv;        // +0x30
    TanVec       tan;       // +0x44
    IntVec posIdx;    // +0x58
    IntVec nrmIdx;    // +0x6c
    IntVec uvIdx;     // +0x80
    char pad1[0x124 - 0x94];
    CornerRef*   pairs;     // +0x124
    void BuildTangents();
};

// @ 0x005087b0
void TangentBuilder::BuildTangents()
{
    unsigned n = uv.size();
    tan.resize(n);
    for (unsigned i = 0; i < n; i++) {
        Vec2* p9;
        float n6;
        unsigned mid;
        unsigned t2;
        float t23;
        float v8;
        unsigned n17;
        CornerRef owner;
        Vec2 elem;
        Vec2* p40;
        Vec2 t33;
        Vec2* p1;
        float n5;
        float s;
        owner = pairs[i];
        if (owner.first == -1)
            continue;
        t2 = owner.corner;
        Neighbors(t2, mid, n17);
        p40 = uv.b + uvIdx[t2];
        p1 = uv.b + uvIdx[mid];
        p9 = uv.b + uvIdx[n17];
        t33 = Vec2Sub_0050cfb0(*p1, *p40);
        elem = Vec2Sub_0050cfb0(*p9, *p40);
        n5 = t33[0];
        n6 = t33[1];
        v8 = elem[0];
        t23 = elem[1];
        s = n5 * t23 - v8 * n6;
        if (s > 1e-7f) {
            float pNode = 1.0f / s;
            Vec2 v24;
            v24 = Vec2Mul_0050e190(Vec2(t23, -n6), pNode);
            V3Out* t11 = pos.b + posIdx[t2];
            V3Out* t7 = pos.b + posIdx[mid];
            V3Out* z = pos.b + posIdx[n17];
            Vec3 v30;
            v30 = *t7 - *t11;
            Vec3 t20;
            t20 = *z - *t11;
            Vec3 mem;
            mem = v24[0] * v30 + v24[1] * t20;
            V3Out res(nrm[nrmIdx[t2]]);
            VecC t12 = Normalize(mem - DotV(res, mem) * res);
            V3Out node = Cross(res, t12);
            tan.b[i] = TanPair(t12, node);
            ScratchSlots<5>();
        } else {
            V3Out* data = pos.b + posIdx[t2];
            V3Out* t34 = pos.b + posIdx[mid];
            V3Out* v4 = pos.b + posIdx[n17];
            V3Out* t20 = nrm.b + nrmIdx[t2];
            VecC left;
            VecC size;
            size = Normalize(Cross(*v4 - *data, *t20));
            left = Normalize(Cross(*t20, size));
            tan.b[i] = TanPair(size, left);
            ScratchSlots<10>();
        }
    }
}
