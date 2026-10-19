// Slice s00493640 (batch w1g0, slice 90), 0x00493640..0x004942a3.
// /Od editor-region code (compiled /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS-).
// 00494270 is a small wrapper; 00493ce0 (MoveBlockAndTranslateSnappedBlocks) is still a skeleton.

#include "types.h"

struct Matrix3 {
    float m[9];
    Matrix3(const Matrix3& src) { Assign(&src); }
    void Assign(const Matrix3* src);      // 0x0041cb40
};

// Result type of operator- and operator* (user copy ctor, copied into V3 member-wise with movss)
struct X3 {
    float x, y, z;
    X3() {}
    X3(const X3& o) : x(o.x), y(o.y), z(o.z) {}
};

// Local vector type. Assigning from an X3 goes through the user operator= (movss); assigning from
// another V3 (Normalize / Cross results, globals, basis rows) is the implicit dword copy.
struct V3 {
    float x, y, z;
    V3() {}
    V3(float a, float b, float c) : x(a), y(b), z(c) {}
    V3& operator=(const X3& o) { x = o.x; y = o.y; z = o.z; return *this; }
    float& operator[](int i) { return (&x)[i]; }
    void SetX(float v) { x = v; }
    void SetY(float v) { y = v; }
};

// three basis vectors: out[0] = binormal, out[1] = axis, out[2] = normal
struct Basis {
    V3 rows[3];
    V3& operator[](int i) { return rows[i]; }
};

// declined-inline callee frames: reserves N dwords at the call site
template<int N> __forceinline void Scratch() { unsigned pad[N]; (void)pad; }

X3 operator-(const V3& v);                         // 0x00422020
V3 Normalize(const V3& v);                         // 0x00436ce0
V3 Cross(const V3& a, const V3& b);                // 0x0044e460
X3 operator*(const V3& v, const float& s);         // 0x0041dca0
float VectorLength(const V3* v);                   // 0x0040ae50
extern V3 kVecA;                                   // 0x015d6324
extern V3 kVecB;                                   // 0x015d63f4
extern V3 kVecB2;                                  // 0x015d6370

X3 Cross2(const V3& a, const V3& b);               // 0x00454c00 (returns a member-wise-copied triple)
void MulAssign(V3* v, const float* s);             // 0x0041dba0 (cdecl)
extern float kNegOne;                              // 0x013eb1bc

struct RwVec3 {                                    // rw::math::fpu::Vector3Template<float,0>
    float v[3];
    RwVec3(const void* src);                       // 0x004098a0 (thiscall, ret 4)
    float& operator[](int i) { return v[i]; }
};

// bitset<60> as inlined at /Od: bounds check, word fetch, mask by pos % 32
struct Bits60 {
    unsigned w[2];
    unsigned GetWord(unsigned pos) const { return w[pos >> 5]; }
    bool test(unsigned pos) const {
        if (pos < 60)
            return (GetWord(pos) & (1u << (pos % 32))) != 0;
        return false;
    }
};

struct cSPEditorBlock {
    char pad[0x138];
    char pos138[0xc];
    char pad144[0xdc8 - 0x144];
    Bits60 flags;                                  // +0xdc8
    void GetDirectionIndices(int& a, int& b, int& c);   // 0x0044c0e0 (thiscall, ret 12)
};

// forward decls
Matrix3* FUN_00493ce0(Matrix3* a, cSPEditorBlock* b, Matrix3 m);
int ClassifyAgainstSymmetryPlane(V3* p, float width, float zmin, float zmax, Basis* out);

// @ 0x00494270
void* FUN_00494270(void* a, void* b) {
    unsigned hole[11];
    (void)hole;
    FUN_00493ce0((Matrix3*)a, (cSPEditorBlock*)b, *(Matrix3*)((char*)b + 0xa8));
    return a;
}

// @ 0x00493640  SP::EditorUtils::ClassifyAgainstSymmetryPlane
// (local names are chosen for the /Od frame slot order: p30=changed p18=state p4=len n31=flat v1=half;
//  per block t25/v16/chunk, v13/v37/buf, v34/hash/mem are normal/axis/binormal triples, v26=clamped rim)
// Clamps the point *p into the slab zmin..zmax and the disc of diameter `width` around the Z axis;
// when it moved the point and `out` is given, fills the contact frame (binormal, axis, normal).
// Returns 2 (hit the bottom), 0 (top), 1 (radial side) or 3 (inside, unchanged).
int ClassifyAgainstSymmetryPlane(V3* p, float width, float zmin, float zmax, Basis* out) {
    bool p30 = false;
    int p18 = 3;
    if (zmin > (*p)[2]) {
        (*p)[2] = zmin;
        p30 = true;
        p18 = 2;
        if (out) {
            V3 t25;
            if ((*p)[0] != 0.0f || (*p)[1] != 0.0f) {
                t25 = -*p;
                t25[2] = 0.0f;
                Scratch<5>();
                t25 = Normalize(t25);
            } else {
                t25 = -kVecB;
            }
            V3 v16;
            v16 = kVecA;
            V3 chunk;
            chunk = Cross(v16, t25);
            (*out)[0] = chunk;
            (*out)[1] = v16;
            (*out)[2] = t25;
        }
    }
    if ((*p)[2] > zmax) {
        (*p)[2] = zmax;
        p30 = true;
        p18 = 0;
        if (out) {
            V3 v13;
            if ((*p)[0] != 0.0f || (*p)[1] != 0.0f) {
                v13 = -*p;
                v13[2] = 0.0f;
                Scratch<5>();
                v13 = Normalize(v13);
            } else {
                v13 = kVecB;
            }
            V3 v37;
            v37 = -kVecA;
            V3 buf;
            buf = Cross(v37, v13);
            (*out)[0] = buf;
            (*out)[1] = v37;
            (*out)[2] = v13;
        }
    }
    V3 n31(p->x, p->y, 0.0f);
    float p4 = VectorLength(&n31);
    float v1 = width / 2.0f;
    if (p4 > v1) {
        V3 v26;
        Scratch<6>();
        v26 = Normalize(n31) * v1;
        p->SetX(v26.x);
        p->SetY(v26.y);
        p30 = true;
        p18 = 1;
        if (out) {
            V3 hash;
            if ((*p)[0] != 0.0f || (*p)[1] != 0.0f) {
                hash = -*p;
                hash[2] = 0.0f;
                Scratch<5>();
                hash = Normalize(hash);
            } else {
                hash = kVecB;
            }
            V3 v34;
            v34 = kVecA;
            V3 mem;
            mem = Cross(hash, v34);
            (*out)[0] = mem;
            (*out)[1] = hash;
            (*out)[2] = v34;
        }
    }
    (void)p30;
    return p18;
}

// @ 0x00493ce0  SP::EditorUtils::MoveBlockAndTranslateSnappedBlocks
// Builds the block's orientation basis (binormal, axis, normal rows) into the by-value matrix and
// returns a copy of it through the hidden return slot.
Matrix3* FUN_00493ce0(Matrix3* a, cSPEditorBlock* b, Matrix3 m) {
    bool flag = false;
    if (b->flags.test(0x13) || b->flags.test(0x28))
        flag = true;
    bool f1;
    f1 = b->flags.test(0x11);
    V3 u;
    V3 t;
    V3 w;
    if (f1 && flag) {
        u = -kVecB;
        w = kVecB2;
        t = kVecA;
    } else if (f1) {
        u = kVecB2;
        w = kVecB;
        t = kVecA;
    } else {
        w = ((Basis*)&m)->operator[](1);
        w[0] = 0.0f;
        if (VectorLength(&w) == 0.0f)
            w = -kVecA;
        w = Normalize(w);
        if (flag) {
            t = kVecB2;
            V3 c;
            c = Cross2(w, t);
            u = Normalize(c);
        } else {
            u = kVecB2;
            V3 c;
            c = Cross2(u, w);
            t = Normalize(c);
        }
    }
    Basis* mb = (Basis*)&m;
    (*mb)[0] = u;
    (*mb)[1] = w;
    (*mb)[2] = t;
    if (!flag) {
        if (!b->flags.test(0x34)) {
            RwVec3 pos(b->pos138);
            if (pos[1] > 0.0f) {
                int i0, i1, i2;
                b->GetDirectionIndices(i0, i1, i2);
                float k1 = kNegOne;
                MulAssign(&(*mb)[i0], &k1);
                float k2 = kNegOne;
                MulAssign(&(*mb)[i2], &k2);
            }
        }
    }
    a->Assign(&m);
    return a;
}
