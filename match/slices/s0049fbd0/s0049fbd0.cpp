// Slice s0049fbd0: SP::EditorUtils limb / repin helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Matrix33T {
    Vector3T xAxis, yAxis, zAxis;
    Matrix33T() {}
    Matrix33T(const Matrix33T& m) : xAxis(m.xAxis), yAxis(m.yAxis), zAxis(m.zAxis) {}
};
struct cSPVector3 : Vector3T {               // out-of-line copy ctor @ 0x4098a0
    cSPVector3() {}
    cSPVector3(const Vector3T& v);
    cSPVector3(const cSPVector3& v);
};
struct cSPMatrix3 : Matrix33T {              // out-of-line copy ctor @ 0x41cb40 (Matrix3::Assign)
    cSPMatrix3() {}
    cSPMatrix3(const Matrix33T& m);
    cSPMatrix3(const cSPMatrix3& m);
};
struct PodVec { float x, y, z; };
struct Mat3Id : Matrix33T { Mat3Id(); };      // @ 0x402ab0 default ctor
struct Mat3B { char d[36]; Mat3B(const Matrix33T&); };  // @ 0x449cc0 by-value matrix wrapper
template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};
template<class T> struct LimbVec {
    T* b; T* e; T* c; int allocPair[2];
    LimbVec() { b = 0; e = 0; c = 0; }
    LimbVec(char& a);                            // @ 0x540470
    void push_back(const T& v);                  // @ 0x454860
    ~LimbVec() { for (T* p = b; p < e; ++p) {} Free(); }
    void Free();                                 // @ 0x425990
    T* at(int i) { return b + i; }
    T& operator[](int i) { return *(b + i); }
};
struct cSPEditorModel;
struct cSPEditorBlock {
    virtual void _v0();
    char pad0[0x28 - 4];
    cSPEditorModel* mEditorModel;                // +0x28
    char pad1[0x48 - 0x2c];
    Vector3T mPosition;                          // +0x48
    char pad2[0x60 - 0x54];
    Matrix33T mOrientation;                      // +0x60
    char pad3[0xa8 - 0x84];
    Matrix33T mTorsoMat;                         // +0xa8
    char pad4[0x33c - 0xcc];
    void* mSocketConnector;                      // +0x33c
    LimbVec<cSPEditorBlock*> mChildren;          // +0x340 (begin,end)
    char pad5[0x3e0 - 0x354];
    cSPEditorBlock* mParent;                     // +0x3e0
    char pad6[0xdc8 - 0x3e4];
    bitset<60> mFlags;                           // +0xdc8
    cSPEditorModel* GetEditorModel() { return mEditorModel; }
    void FUN_448e90(cSPVector3* v, int a);       // @ 0x448e90
    void FUN_449420(Matrix33T* m, int a);        // @ 0x449420
    void FUN_43ffa0(cSPMatrix3 m);               // @ 0x43ffa0
    float* GetBBox(float* out, int, int, int);   // @ 0x44ae00
};
struct cSPEditorModel {
    cSPEditorBlock* GetBlock(int i);             // @ 0x4accb0
    int GetBlockCount();                         // @ 0x4accf0
    bool FUN_4adc40();                           // @ 0x4adc40
    float FUN_4adaa0();                          // @ 0x4adaa0
};
struct cSPEditorLimbStructure { char d[0x58]; cSPEditorLimbStructure(); ~cSPEditorLimbStructure();
    void FUN_4891a0(cSPEditorBlock*, int, int); void FixAllJoints(); void FUN_488980(); };

cSPEditorBlock* FUN_4a5a70(cSPEditorModel* m);
cSPEditorBlock* FUN_4a5970(cSPEditorBlock* b);
Vector3T* FUN_41db10(Vector3T* out, const Vector3T* a, const Vector3T* b);   // a - b
Vector3T* FUN_41dc10(Vector3T* out, const Vector3T* a, const Vector3T* b);   // a - b
Vector3T* FUN_41dca0(Vector3T* out, const Vector3T* a, const float* s);      // a * s
float VectorLength(const Vector3T* v);
void Vector3_Normalize(Vector3T* out, const Vector3T* in);
void FUN_49efc0(cSPEditorBlock*, cSPVector3, cSPVector3, cSPMatrix3, cSPMatrix3, LimbVec<cSPEditorBlock*>*);
void FUN_49efc0(cSPEditorBlock*, Vector3T, Vector3T, Mat3Id, Matrix33T, LimbVec<cSPEditorBlock*>*);
bool FUN_49dd20(cSPEditorBlock*, LimbVec<cSPEditorBlock*>*, int);
void RepinBlockToTorso(cSPEditorBlock* block, cSPVector3 t, cSPMatrix3 r, bool flag);
void* FUN_4a3dc0(cSPEditorBlock*, void*, cSPVector3, cSPVector3, Vector3T*);
void FUN_4a1070(cSPEditorBlock*);
void FUN_4a29a0(cSPEditorBlock*, void*, void*);
extern float g_zero;                 // 0x1485378
extern PodVec g_vec015d64d8;         // 0x15d64d8
void GetAllLimbs(cSPEditorBlock* block, LimbVec<cSPEditorBlock*>* out, bool unique);

// @ 0x4a0ac0
bool FUN_4a0ac0(cSPEditorModel* model)
{
    bool h = 0;
    int v1 = 0;
    int idx = model->GetBlockCount();
    for (; v1 < idx; v1++) {
        cSPEditorBlock* p1 = model->GetBlock(v1);
        if (p1 && p1->mFlags.test(0x2d)) {
            h = 1;
        }
    }
    return h;
}

// @ 0x49fbd0
void RepinBlockToTorso(cSPEditorBlock* block, cSPVector3 t, cSPMatrix3 r, bool flag)
{
    cSPVector3 oldPos(block->mPosition);
    cSPMatrix3 oldMat(block->mOrientation);
    Mat3Id parentMat;
    Vector3T parentPos;
    if (block->mParent) {
        cSPEditorBlock* p = block->mParent;
        parentPos = p->mPosition;
        parentMat = *(Mat3Id*)&block->mParent->mOrientation;
    }
    block->FUN_448e90(&t, 1);
    if (flag) {
        block->FUN_43ffa0(r);
        block->FUN_449420(&block->mTorsoMat, 1);
    } else {
        block->FUN_449420(&r, 1);
    }
    FUN_49efc0(block, oldPos, block->mPosition, oldMat, block->mOrientation, &block->mChildren);
    Vector3T zero;
    zero.x = 0; zero.y = 0; zero.z = 0;
    char alloc;
    LimbVec<cSPEditorBlock*> touched(alloc);
    if (block->mParent) {
        if (block->mEditorModel->FUN_4adc40()) {
            if (FUN_49dd20(block->mParent, &touched, 0)) {
                FUN_49efc0(block->mParent, parentPos, block->mParent->mPosition,
                           parentMat, block->mParent->mOrientation, &touched);
            }
        }
    }
}

// @ 0x49fee0
void FUN_49fee0(cSPEditorBlock* block, bool unique)
{
    LimbVec<cSPEditorBlock*> limbs;
    GetAllLimbs(block, &limbs, unique);
    int i = 0;
    int n = limbs.e - limbs.b;
    for (; i < n; i++) {
        if (limbs.b[i]->mFlags.test(0xb)) {
            cSPEditorLimbStructure ls;
            ls.FUN_4891a0(limbs[i], 0, 0);
            ls.FixAllJoints();
            ls.FUN_488980();
        }
    }
}

// @ 0x4a0020
void GetAllLimbs(cSPEditorBlock* block, LimbVec<cSPEditorBlock*>* out, bool unique)
{
    char a1;
    LimbVec<cSPEditorBlock*> all(a1);
    cSPEditorBlock* cur = FUN_4a5a70(block->GetEditorModel());
    while (cur) {
        all.push_back(cur);
        cur = FUN_4a5970(cur);
    }
    char a2;
    LimbVec<cSPEditorBlock*> seen(a2);
    int i = 0;
    int n = all.e - all.b;
    for (; i < n; i++) {
        LimbVec<cSPEditorBlock*>* kids = &all[i]->mChildren;
        int j = 0;
        int m = kids->e - kids->b;
        for (; j < m; j++) {
            cSPEditorBlock* child = (*kids)[j];
            if (child->mFlags.test(0xb)) {
                if (unique) {
                    cSPEditorBlock** it = seen.b;
                    cSPEditorBlock** end = seen.e;
                    cSPEditorBlock* want = (*kids)[j];
                    while (it != end && *it != want) ++it;
                    if (it != seen.e) continue;
                }
                cSPEditorBlock* v = (*kids)[j];
                out->push_back(v);
                if (unique) {
                    cSPEditorBlock* pv = (*kids)[j]->mParent;
                    seen.push_back(pv);
                }
            }
        }
    }
}

// @ 0x4a02b0
void FUN_4a02b0(cSPEditorBlock* block, cSPVector3 p, cSPVector3 q)
{
    cSPVector3 c(block->mPosition);
    Vector3T tmp1, tmp2, tmp3;
    PodVec v1 = *(PodVec*)FUN_41db10(&tmp1, &p, &c);
    float len1 = VectorLength((Vector3T*)&v1);
    PodVec v2 = *(PodVec*)FUN_41db10(&tmp2, &q, &c);
    float len2 = VectorLength((Vector3T*)&v2);
    PodVec v3 = *(PodVec*)FUN_41db10(&tmp3, &p, &c);
    Vector3T n;
    Vector3_Normalize(&n, (Vector3T*)&v3);
    LimbVec<cSPEditorBlock*>* kids = &block->mChildren;
    int i = 0;
    int cnt = kids->e - kids->b;
    for (; i < cnt; i++) {
        cSPEditorBlock* blk = (*kids)[i];
        if (blk->mFlags.test(0xc)) {
            PodVec q2;
            q2.x = q.x; q2.y = q.y; q2.z = q.z;
            RepinBlockToTorso(blk, *(cSPVector3*)&q2, cSPMatrix3(blk->mTorsoMat), false);
        } else if (block->mFlags.test(0xa)) {
            cSPVector3 bp(blk->mPosition);
            Vector3T tmp4, tmp5, tmp6;
            PodVec d = *(PodVec*)FUN_41db10(&tmp4, &bp, &c);
            float dot = d.x * n.x + d.y * n.y + d.z * n.z;
            float ratio = dot / len1;
            float scaled = ratio * len2;
            float diff = scaled - dot;
            cSPVector3 w(*FUN_41dca0(&tmp5, &n, &diff));
            PodVec r = *(PodVec*)FUN_41dc10(&tmp6, &bp, &w);
            RepinBlockToTorso(blk, *(cSPVector3*)&r, *(cSPMatrix3*)&Mat3B(blk->mTorsoMat), false);
        }
    }
}

// @ 0x4a06c0
Vector3T* FUN_4a06c0(Vector3T* ret, cSPEditorBlock* block)
{
    if (block == 0) {
        ret->x = g_zero;
        ret->y = g_zero;
        ret->z = g_zero;
        return ret;
    } else if (block->mFlags.test(0x14)) {
        float z = 0.05f;
        if (block->GetEditorModel()) {
            z = block->GetEditorModel()->FUN_4adaa0() / 20.0f;
        }
        ret->x = g_zero;
        ret->y = g_zero;
        ret->z = z;
        return ret;
    } else if (block->mFlags.test(0x1f)) {
        Vector3T pos;
        pos.x = block->mPosition.x; pos.y = block->mPosition.y; pos.z = block->mPosition.z;
        Vector3T bb;
        float* pb = block->GetBBox((float*)&bb, 0, 0, 0);
        bb.x = pb[0]; bb.y = pb[1]; bb.z = pb[2];
        Vector3T tmp;
        Vector3T* r = FUN_41db10(&tmp, &pos, &bb);
        *ret = *r;
        return ret;
    } else {
        ret->x = g_zero;
        ret->y = g_zero;
        ret->z = g_zero;
    }
    return ret;
}

// @ 0x4a0900
bool FUN_4a0900(cSPEditorBlock* block, void* p2, cSPVector3 a, cSPVector3 b, Vector3T* out)
{
    cSPEditorModel* model = block->mEditorModel;
    bool result = false;
    Vector3T pos;
    pos.x = block->mPosition.x; pos.y = block->mPosition.y; pos.z = block->mPosition.z;
    Vector3T off;
    void* hit = FUN_4a3dc0(block, p2, a, b, &off);
    if (hit == 0) {
        if (block->mFlags.test(0xc)) {
            FUN_4a1070(block);
            return result;
        }
    }
    if (hit != 0) {
        result = true;
        void* sock = block->mSocketConnector;
        if (hit != sock) {
            FUN_4a29a0(block, p2, hit);
            Vector3T tmp;
            Vector3T* r = FUN_41db10(&tmp, &block->mPosition, &off);
            *out = *r;
        } else {
            *(PodVec*)out = g_vec015d64d8;
        }
    }
    return result;
}
