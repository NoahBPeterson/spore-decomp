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

// forward decls
void FUN_00493ce0(void* a, void* b, Matrix3 m);
int ClassifyAgainstSymmetryPlane(V3* p, float width, float zmin, float zmax, Basis* out);

// @ 0x00494270
void* FUN_00494270(void* a, void* b) {
    unsigned hole[11];
    (void)hole;
    FUN_00493ce0(a, b, *(Matrix3*)((char*)b + 0xa8));
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

// @ 0x00493ce0
void FUN_00493ce0(void* a, void* b, Matrix3 m) {
    (void)a;
    (void)b;
    (void)m;
}
