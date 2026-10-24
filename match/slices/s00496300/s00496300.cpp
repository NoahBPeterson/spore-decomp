// Slice s00496300 (batch w1g0, slice 93), 0x00496300..0x00496d2c.
// /Od editor-region code: limb-structure helpers.
// Completed 00496300 (stack a block along a bounding box) and 00496760 (blend a deform parameter
// between two editor vectors).  00496b60 / 00496bb0 were completed earlier (see nonmatching.txt).

#include "types.h"

struct Vector3 {
    float x, y, z;
};

Vector3* Vector3_Sub(Vector3* out, const Vector3* a, const Vector3* b);   // 0x0041db10
Vector3* Vector3_Add(Vector3* out, const Vector3* a, const Vector3* b);   // 0x0041dc10
Vector3* Vector3_Mul(Vector3* out, const Vector3* v, const float* s);     // 0x0041dca0
Vector3* Vector3_Normalize(Vector3* out, const Vector3* v);               // 0x00436ce0
float    VectorLength(const Vector3* v);                                  // 0x0040ae50
void* GetBoneForHandle(void* h);                                          // 0x004aa030
void     FUN_004a02b0(void* blk, Vector3 a, Vector3 b);                   // 0x004a02b0

struct Bone {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual int v4();
    void* Get();                          // 0x0047e6c0
    int GetSomething();                   // 0x0047e680
    int Check();                          // 0x0044f220
};

struct LimbStructure {
    char pad[0x5c];
    void Ctor();                          // 0x00488850
    void Init(void* limb, int a, int b);  // 0x004891a0
    void UpdateScaleRange(void* limb, float f); // 0x0048b370
    void F();                             // 0x00488980
    ~LimbStructure();                     // 0x00488900
};

struct HolderA {
    void* Get();                          // 0x0047e6c0
};

struct HolderB {
    char pad[0x64];
};

struct BBox {
    Vector3 mMin;                         // +0x00
    Vector3 mMax;                         // +0x0c
};

struct Block {
    char pad00[0x48];
    Vector3 mPos48;                       // +0x48 (mPos48.z is +0x50)
    char pad54[0x1d8 - 0x54];
    float mF1d8;                          // +0x1d8
    char pad1dc[0x3f4 - 0x1dc];
    Vector3 mVec3f4;                      // +0x3f4
    Vector3 mVec400;                      // +0x400
    char pad40c[0xdc8 - 0x40c];
    uint32_t mBitsDc8;                    // +0xdc8

    BBox* GetBBox(BBox* out, int a, bool b, int* c);        // 0x0044ae00
    void  SetPosition(const Vector3& v, bool b);            // 0x00448e90
    Vector3* F3e080(Vector3* out);                          // 0x0043e080
    void* F_43c1a0();                                       // 0x0043c1a0
    bool  F_43c450(void* handle, float a, float* b, bool c); // 0x0043c450
    void  F_449ce0();                                       // 0x00449ce0
};

struct BlockList {
    Block** mpBegin;                      // +0x00
    Block** mpEnd;                        // +0x04
};

// @ 0x00496b60
void FUN_00496b60(HolderA* a, float f) {
    void* limb = a->Get();
    LimbStructure ls;
    ls.Ctor();
    ls.Init(limb, 0, 0);
    ls.UpdateScaleRange(limb, f);
    ls.F();
    ls.~LimbStructure();
}

// @ 0x00496bb0
int FUN_00496bb0(char* p, float f) {
    Bone* bone = (Bone*)GetBoneForHandle(p + 100);
    int c = 0;
    if (bone != 0)
        c = (int)bone->Get();
    if (bone != 0 && bone->v4() == 0x50e8e23 && c != 0 &&
        *(int*)(c + 0x3e0) != 0) {
        int t = bone->GetSomething();
        if (t != 0 && p != 0) {
            Vector3 d;
            Vector3_Sub(&d, (Vector3*)(t + 0xc), (Vector3*)(p + 0xc));
            float len = VectorLength(&d);
            if (len < 0.01f) {
                float s = f >= 0.0f ? 1.0f : -1.0f;
                int n = ((Bone*)c)->Check();
                if (s != (float)n)
                    c = *(int*)(c + 0x3e0);
            }
        }
    }
    return c;
}

// @ 0x00496300
bool FUN_00496300(Block* blk, BlockList* list, uint32_t u10, uint32_t u14, uint32_t u18,
                  Vector3 posA, Vector3 posB, bool flag) {
    Vector3 rel;
    Vector3_Sub(&rel, &blk->mPos48, &posB);
    bool placed = false;
    int count = (int)(list->mpEnd - list->mpBegin);
    if (flag) {
        Block* best = blk;
        BBox box;
        blk->GetBBox(&box, 0, false, 0);
        float bestY = posB.z + rel.z + box.mMin.z;
        for (int i = 0; i < count; i++) {
            Block* b = list->mpBegin[i];
            BBox bb;
            b->GetBBox(&bb, 1, false, 0);
            float y = b->mPos48.z + rel.z + bb.mMin.z;
            if (y < bestY) {
                bestY = y;
                best = b;
            }
        }
        if (bestY < -0.0001f) {
            float k = -1.0f;
            Vector3 t;
            Vector3_Mul(&t, &posA, &k);
            float scale = -bestY / t.z;
            Vector3 t2;
            Vector3_Mul(&t2, &t, &scale);
            Vector3 r2;
            Vector3_Add(&r2, &rel, &t2);
            rel = r2;
            placed = true;
        }
    }
    Vector3 p;
    Vector3_Add(&p, &posB, &rel);
    blk->SetPosition(p, true);
    for (int i = 0; i < count; i++) {
        Block* b = list->mpBegin[i];
        Vector3 np;
        Vector3_Add(&np, &b->mPos48, &rel);
        b->SetPosition(np, true);
    }
    return placed;
}

// @ 0x00496760
float FUN_00496760(Block* p, float target, char flag) {
    if (p == 0)
        return -1.0f;
    if ((p->mBitsDc8 & 0x800) == 0)
        return -1.0f;

    float f = p->mF1d8;
    Vector3 ta;
    Vector3_Mul(&ta, &p->mVec3f4, &f);
    float lenA = VectorLength(&ta);

    Vector3 tb;
    Vector3_Mul(&tb, &p->mVec400, &f);
    float lenB = VectorLength(&tb);

    float ratio = (target - lenA) / (lenB - lenA);
    if (ratio < 0.0f)
        ratio = 0.0f;
    float len = (lenB - lenA) * ratio + lenA;

    Vector3 buf;
    Vector3* e = p->F3e080(&buf);
    Vector3 nrm;
    Vector3_Normalize(&nrm, e);
    Vector3 sc;
    Vector3_Mul(&sc, &nrm, &len);
    Vector3 a1;
    Vector3_Add(&a1, &sc, &p->mPos48);

    Vector3 buf2;
    Vector3* e2 = p->F3e080(&buf2);
    Vector3 a2;
    Vector3_Add(&a2, e2, &p->mPos48);

    void* handle = p->F_43c1a0();
    float v = *(float*)((char*)handle + 0x180);

    float t = ratio;
    if ((p->mBitsDc8 & 0x400) == 0) {
        t = (t > 0.0f) ? t : 0.0f;
        t = (t < 1.0f) ? t : 1.0f;
    }
    if (t != v) {
        void* h = p->F_43c1a0();
        p->F_43c450(h, t, 0, true);
        FUN_004a02b0(p, a2, a1);
        if (flag)
            p->F_449ce0();
    }
    return len;
}