// Slice s004974e0 (batch w1g0, slice 95), 0x004974e0..0x0049846d.
// /Od editor-region code.

#include "types.h"
#include <math.h>
#include <new>

struct Matrix3 {
    float m[9];
    Matrix3(const Matrix3& src) { Assign(&src); }
    void Assign(const Matrix3* src);      // 0x0041cb40
};

// Vector3 flavour with an inline member-wise copy (movss pairs at /Od)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    float& operator[](int i) { return (&x)[i]; }
};

// Vector3 flavour with an out-of-line copy ctor (0x004098a0)
struct Vec3O {
    float v[3];
    Vec3O(const Vec3O& o);
    float& operator[](int i) { return v[i]; }
};

struct FlagOwner {
    void SetFlag(int flag, char v);       // 0x00435a10
};

void FUN_00498230(int p, char flag);
void* __stdcall FUN_00401050(int key, int a, int p, int b);
struct X5ae40 {
    void F();                             // 0x0045ae40
};

struct cSPEditorBlock {
    virtual void pv0();
    virtual int AddRef();                  // +0x4
    virtual int Release();                 // +0x8
};

// an AutoRefCount<cSPEditorBlock> local (AddRef/Release through the vtable, both left inline)
struct BlockRef {
    cSPEditorBlock* mp;
    BlockRef(cSPEditorBlock* p) : mp(p) { if (mp) mp->AddRef(); }
    ~BlockRef() { if (mp) mp->Release(); }
};

struct BlockVector {
    BlockRef** mpBegin;
    BlockRef** mpEnd;
    BlockRef** mpCapacity;
    char mAllocator[4];
    BlockVector() : mpBegin(0), mpEnd(0), mpCapacity(0) { Init(); }
    ~BlockVector();                        // 0x00453eb0
    void Init();                           // 0x00429360 (allocator)
    void reserve(unsigned n);              // 0x004e0880
    void push_back(const BlockRef& r);     // 0x004541f0
};

struct DirVector {                         // vector<Vector3>: 12-byte elements
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    char mAllocator[4];
    DirVector() : mpBegin(0), mpEnd(0), mpCapacity(0) { Init(); }
    ~DirVector();                          // 0x00540520
    void Init();                           // 0x00429360
    void push_back(const Vector3& v);      // 0x004739d0
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct EString {                           // eastl::basic_string<char>, empty
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    EString() : mpBegin(0), mpEnd(0), mpCapacity(0) {
        mpBegin = gEmpty;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    ~EString();                            // 0x00530670
    static char gEmpty[2];                 // 0x01667bac
};

struct X982;
struct Vec3P { float a, b, c; };
Vec3O normalized_safe(const Vec3O& in);                              // 0x00449c20
Vector3* Vec_Mul(Vector3* out, Vec3O* in, const float* scale);      // 0x0041dca0
Vector3* Vec_Sub(Vector3* out, Vector3* a, Vector3* b);             // 0x0041db10
void Vec_AddAssign(Vector3* a, Vector3* b);                          // 0x0041ddb0
Vector3* Vec_Negate(Vector3* out, Vector3* in);                      // 0x00422020
Vector3* Vec_NegateO(Vector3* out, Vec3O* in);                       // 0x00422020
Vector3 Vec_Normalize(const Vector3& in);                            // 0x00436ce0
float VectorLength(Vector3* v);                                      // 0x0040ae50
Vec3O Vec_Normalize2(const Vec3O& in);                               // 0x00436ce0
bool FUN_004a7e60(X982* p);
int PickBlocks(BlockVector* blocks, Vector3 a, Vector3 b, Vector3* hitPos, Vector3* hitNormal,
               int* hitBlock, bool* flag, int c);                    // 0x004a4840

struct X982 : cSPEditorBlock {
    char pad0[0x138 - 4];
    float dir[3];                          // 0x138
    char pad144[0x33c - 0x144];
    X982* parent;                          // 0x33c
    X982* Parent() const { return parent; }
    void** begin;                          // 0x340
    void** end;                            // 0x344
    char pad2[0xdc8 - 0x348];
    uint32_t bits[1];                      // 0xdc8
    bool GetFlag(unsigned i) const {
        if (i < 0x3c) {
            uint32_t w = bits[i >> 5];
            return (w & (1u << (i % 32))) != 0;
        }
        return false;
    }
    bool FUN_00435c80();                   // 0x00435c80
    bool FUN_0043bd50(Vec3O v, float f);   // 0x0043bd50
    bool FUN_0043bd50(Vector3 v, float f); // 0x0043bd50 (inline-copied argument)
    bool FUN_0043bc70(float a, float b);   // 0x0043bc70
    void FUN_0043ffa0(Matrix3 m);          // 0x0043ffa0
    void MoveTo(int a, Vector3 b, Vector3 c, char d);  // 0x00436fa0
};

void RepinBlockToTorso(X982* p, Vector3 v, Matrix3 m, int a);        // 0x0049fbd0

// @ 0x00498230
void FUN_00498230(int p, char flag) {
    ((FlagOwner*)p)->SetFlag(0xf, flag);
    int* pv = (int*)(p + 0x340);
    int n = (pv[1] - pv[0]) >> 2;
    for (int i = 0; i < n; ++i) {
        int child;
        int* slot = (int*)(pv[0] + i * 4);
        child = *slot;
        FUN_00498230(child, flag);
    }
}

// @ 0x004983d0
void FUN_004983d0(X982* p, uint8_t flag) {
    if (p->GetFlag(0xf)) {
        if (flag == 0)
            ((X5ae40*)FUN_00401050(0x3f1bf55, 0, (int)p, 0))->F();
    } else {
        if (flag != 0)
            ((X5ae40*)FUN_00401050(0x3f1bf56, 0, (int)p, 0))->F();
    }
}

// @ 0x004982b0
bool FUN_004982b0(X982* p, char a, float b, char c);
bool FUN_00498470(X982* p, Vector3* v, Matrix3* m1, Matrix3* m2, char a, float b, char c, int d);

bool FUN_004982b0(X982* p, char a, float b, char c) {
    Vector3 v(*(Vector3*)((char*)p + 0x48));
    Matrix3 m1(*(Matrix3*)((char*)p + 0xa8));
    Matrix3 m2(*(Matrix3*)((char*)p + 0xf0));
    bool r = FUN_00498470(p, &v, &m1, &m2, a, b, c, 1);
    if (r) {
        p->FUN_0043ffa0(m2);
        RepinBlockToTorso(p, v, m1, 0);
    }
    return r;
}

// @ 0x004974e0
bool FUN_004974e0(X982* p, Vec3O v, Vec3O* outHit, bool* outFlag, float tol, char force) {
    bool r = false;
    *outFlag = true;
    *outHit = v;
    if (p) {
        if (p->FUN_00435c80()) {
            if (!p->GetFlag(0x1f) || !p->Parent()) return false;
            if (!p->Parent()->GetFlag(0x1f)) return false;
            if (p->Parent()->FUN_00435c80()) return false;
        }
        Vec3O cur(v);
        r = false;
        if (p->FUN_0043bd50(cur, tol)) {
            bool ok = true;
            if (p->Parent()) {
                if (!p->Parent()->GetFlag(0xf)) ok = false;
            }
            if (ok) {
                r = true;
                Vec3O d(*(Vec3O*)p->dir);
                if (d[0] != 0.0f || d[1] != 0.0f || d[2] != 0.0f) {
                    d[0] = 0.0f;
                    d = normalized_safe(d);
                    if (d.v[0] * d.v[0] + d.v[1] * d.v[1] + d.v[2] * d.v[2] > 0.9f) {
                        bool f2 = p->Parent() != 0;
                        if (p->GetFlag(0x1f) && f2) {
                            if (p->GetFlag(0x20)) f2 = false;
                        }
                        if (f2) {
                            if (p->Parent()->GetFlag(0xa)) {
                                Vec3O t(*(Vec3O*)p->dir);
                                Vec3O nrm = Vec_Normalize2(t);
                                float a0 = nrm[0];
                                if (tol * 0.5f > (float)fabs(a0)) {
                                    r = true;
                                    Vector3 copy(*(Vector3*)&d);
                                    *(Vec3P*)p->dir = *(Vec3P*)&copy;
                                } else {
                                    r = false;
                                }
                            } else {
                                BlockVector blocks;
                                blocks.reserve(1);
                                {
                                    BlockRef blk(p->Parent());
                                    blocks.push_back(blk);
                                }
                                Vector3 start(*(Vector3*)&cur);
                                start[0] = 0.0f;
                                Vector3 end(start);
                                const float scale = 4.0f;
                                Vector3 mulTmp;
                                Vec_AddAssign(&end, Vec_Mul(&mulTmp, &d, &scale));
                                Vector3 negTmp;
                                Vector3 negd = *Vec_NegateO(&negTmp, &d);
                                bool flag = false;
                                int hitBlock;
                                Vector3 hitPos;
                                Vector3 hitNormal;
                                int pick = PickBlocks(&blocks, end, negd, &hitPos, &hitNormal, &hitBlock, &flag, 0);
                                if (pick) {
                                    Vector3 subTmp;
                                    Vector3 dv = *Vec_Sub(&subTmp, &hitPos, &start);
                                    float len = VectorLength(&dv);
                                    if (p->FUN_0043bc70(len, tol)) {
                                        Vector3 nn(hitNormal);
                                        *(Vec3P*)p->dir = *(Vec3P*)&nn;
                                        *(Vec3P*)outHit = *(Vec3P*)&hitPos;
                                        Vector3 negTmp2;
                                        p->MoveTo(hitBlock, hitPos, *Vec_Negate(&negTmp2, &hitNormal), flag);
                                        r = true;
                                    } else {
                                        r = false;
                                    }
                                }
                            }
                        }
                    }
                }
                if (r) {
                    if (p->GetFlag(0)) {
                        if (FUN_004a7e60(p) || force)
                            r = true;
                        else
                            r = false;
                    }
                }
            }
            if (!r) {
                Vector3 again(*(Vector3*)&cur);
                if (p->FUN_0043bd50(again, 0.2f)) {
                    r = true;
                    *outFlag = false;
                }
            } else {
                *outFlag = true;
            }
        }
    }
    if (r) (*outHit)[0] = 0.0f;
    return r;
}

// @ 0x00497f20
bool FUN_00497f20(Vector3 v, Vec3O* out, float step) {
    DirVector dirs;
    EString name;
    for (float x = -1.0f; x <= 1.0f; x = x + step) {
        for (float y = -1.0f; y <= 1.0f; y = y + step) {
            for (float z = -1.0f; z <= 1.0f; z = z + step) {
                if ((x != 0.0f || y != 0.0f || z != 0.0f) && (x != 1.0f || y != 1.0f || z != 1.0f)) {
                    Vector3 t(x, y, z);
                    dirs.push_back(Vec_Normalize(t));
                }
            }
        }
    }
    const float threshold = 0.1f;
    const float vlen = VectorLength(&v);
    Vector3 nv = Vec_Normalize(v);
    float best = 10.0f;
    const int n = dirs.size();
    for (int i = 0; i < n; ++i) {
        Vector3 subTmp;
        Vector3 dv = *Vec_Sub(&subTmp, &nv, &dirs.mpBegin[i]);
        float dlen = VectorLength(&dv);
        if (dlen < threshold) {
            Vector3 mulTmp;
            const float vl = vlen;
            new (out) Vec3O(*(Vec3O*)Vec_Mul(&mulTmp, (Vec3O*)&dirs.mpBegin[i], &vl));
            return true;
        }
        if (dlen < best) best = dlen;
    }
    return false;
}
