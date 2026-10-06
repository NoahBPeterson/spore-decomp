// Slice s00490a70: SP::EditorUtils::GetAlignmentPosition and a pile-weight counter.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
    float operator[](int i) const { return (&x)[i]; }
};
// Vector with an out-of-line copy constructor (@ 0x4098a0).
struct RwVec3 : Vec3 {
    RwVec3() {}
    RwVec3(const RwVec3& v);        // @ 0x4098a0
};
struct Matrix3 {
    Vec3 xAxis, yAxis, zAxis;
    Matrix3() {}
    Matrix3(const Matrix3& m) { Assign(m); }
    Matrix3& Assign(const Matrix3& m);   // @ 0x41cb40
};

struct AllocTag { AllocTag() {} };

struct cSPEditorBlock;
struct RefObj {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};

template<class T> struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    AutoRefCount(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~AutoRefCount() { if (mp) mp->Release(); }
    operator T*() const { return mp; }
    T* operator->() const { return mp; }
};

struct cSPEditorBlock : RefObj {
    char pad0[0x48 - 4];
    Vec3 mPosition;                    // +0x48
    char pad1[0x3e0 - 0x54];
    cSPEditorBlock* mLink3e0;          // +0x3e0
    cSPEditorBlock* mLink3e4;          // +0x3e4
    char pad2[0x5e4 - 0x3e8];
    int mWeight;                       // +0x5e4
    char pad3[0xdc8 - 0x5e8];
    uint32_t mFlags[2];                // +0xdc8
    cSPEditorBlock* GetLink3e0() const { return mLink3e0; }
    cSPEditorBlock* GetLink3e4() const { return mLink3e4; }
    int GetWeight() const { return mWeight; }
    void FUN_0044e7c0(int x);          // @ 0x44e7c0
    uint32_t Word(uint32_t i) const { return mFlags[i >> 5]; }
    bool TestFlag(uint32_t i) const {
        if (i < 0x3c) return (Word(i) & (1u << (i % 32))) != 0;
        return false;
    }
};

struct Mgr;

// Pile list used by the alignment code: inline ctor, allocator built out of line.
struct SPAlloc { uint32_t a, b; SPAlloc(const AllocTag&); };      // @ 0x429360
struct EdList {
    AutoRefCount<cSPEditorBlock>* mpBegin;
    AutoRefCount<cSPEditorBlock>* mpEnd;
    AutoRefCount<cSPEditorBlock>* mpCap;
    SPAlloc mAlloc;
    EdList(const AllocTag& t = AllocTag()) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(t) {}
    ~EdList();                                      // @ 0x453eb0
};

float FUN_00491b40(cSPEditorBlock* self, Mgr* mgr, Vec3 v, Matrix3 m, Vec3* out, bool* flag, int n, float k);   // @ 0x491b40
void FUN_004904a0(cSPEditorBlock* self, Mgr* mgr, EdList* list, int type);                                       // @ 0x4904a0
float FUN_0048fee0(cSPEditorBlock* self, EdList* list, Vec3* out, float k);                                      // @ 0x48fee0
float GetLateralAlignmentPosition(cSPEditorBlock* self, EdList* list, Vec3* pos, Matrix3* m, float k);          // @ 0x48ef30
float GetLowAngleOffset(cSPEditorBlock* self, EdList* list, Vec3* out, float k);                                 // @ 0x48e590
float FUN_00492e70(cSPEditorBlock* self, Vec3* pos, Matrix3* m, int* neg, float k, int flag);                    // @ 0x492e70

// Local names in GetAlignmentPosition were chosen to reproduce the /Od frame slot order (names hash-ordered);
// role -> name: scale=bucket, list1=p18, align=value, neg=n23, outVec=dst, localFlag=v35, pos3=t29, list3=u, b1=t34, list2=n16, latAlign=idx, lat=t13, outA=pNode, bestB=t23, pos=size, bestA=t38, outB=p35, lowOut=p37, mat1=n39, result=p21, mat2=t16, basis=hi, off=v25, a2=p40, k=t4
// @ 0x00490a70
float GetAlignmentPosition(cSPEditorBlock* self, Mgr* mgr, Vec3 v, Matrix3 m, RwVec3* outPos, Matrix3* outBasis,
                           bool* outFlag, uint8_t flag, Matrix3 m2)
{
    if (self != 0) {
    float t4 = 1.2f;
    RwVec3 size((RwVec3&)self->mPosition);
    float value = -1.0f;
    bool v35 = false;
    Vec3 pNode;
    value = FUN_00491b40(self, mgr, v, m2, &pNode, &v35, 1, t4);
    RwVec3 dst(size);
    Matrix3 hi(m);
    float t38 = -1.0f;
    float t23 = -1.0f;
    EdList p18;
    FUN_004904a0(self, mgr, &p18, 0x1b);
    float p40 = -1.0f;
    Vec3 p35;
    p40 = FUN_0048fee0(self, &p18, &p35, t4);
    Vec3 t13(size);
    Matrix3 n39(m);
    float idx = -1.0f;
    EdList n16;
    FUN_004904a0(self, mgr, &n16, 0x1a);
    idx = GetLateralAlignmentPosition(self, &n16, &t13, &n39, t4);
    float t34 = -1.0f;
    EdList u;
    FUN_004904a0(self, mgr, &u, 0x35);
    float bucket = self->TestFlag(8) ? 10.0f : 1.2f;
    Vec3 p37;
    t34 = GetLowAngleOffset(self, &u, &p37, t4 * bucket);
    Vec3 t29(size);
    Matrix3 t16(m);
    float v25 = -1.0f;
    int n23 = -2;
    self->FUN_0044e7c0(n23);
    v25 = FUN_00492e70(self, &t29, &t16, &n23, t4, flag);

    if (p40 != -1.0f || value != -1.0f) {
        if (p40 == -1.0f) {
            dst.z = pNode[2];
            t38 = value;
            *outFlag = v35;
        } else if (value == -1.0f) {
            dst.z = p35[2];
            t38 = p40;
        } else if (value > p40) {
            dst.z = p35[2];
            t38 = p40;
        } else {
            dst.z = pNode[2];
            t38 = value;
            *outFlag = v35;
        }
    }
    if (idx != -1.0f || v25 != -1.0f || t34 != -1.0f) {
        if (t34 != -1.0f) {
            dst.y = p37[1];
            dst.x = p37[0];
            t23 = t34;
        }
        if (idx == -1.0f && v25 != -1.0f) {
            dst.y = t29[1];
            dst.x = t29[0];
            self->FUN_0044e7c0(n23);
            hi = t16;
            t23 = v25;
        } else if (v25 == -1.0f && idx != -1.0f) {
            dst.y = t13[1];
            dst.x = t13[0];
            hi = n39;
            t23 = idx;
        } else if (idx != -1.0f && v25 != -1.0f) {
            if (v25 > idx) {
                dst.y = t13[1];
                dst.x = t13[0];
                hi = n39;
                t23 = idx;
            } else {
                dst.y = t29[1];
                dst.x = t29[0];
                hi = t16;
                t23 = v25;
            }
        }
    }
    float p21 = -1.0f;
    if (t23 != -1.0f || t38 != -1.0f) {
        if (t23 == -1.0f)
            p21 = t38;
        else if (t38 == -1.0f)
            p21 = t23;
        else
            p21 = t23 + t38;
    }
    *outPos = dst;
    *outBasis = hi;
    ScratchSlots<15>();
    return p21;
    }
    return -1.0f;
}

struct BlockVec {
    AutoRefCount<cSPEditorBlock>* mpBegin;
    AutoRefCount<cSPEditorBlock>* mpEnd;
    AutoRefCount<cSPEditorBlock>* mpCap;
    uint32_t mAlloc[2];
    BlockVec(const AllocTag&);                              // @ 0x540470
    ~BlockVec();                                            // @ 0x453eb0
    void push_back(const AutoRefCount<cSPEditorBlock>& v);  // @ 0x4541f0
    AutoRefCount<cSPEditorBlock>& operator[](uint32_t i) { return mpBegin[i]; }
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    AutoRefCount<cSPEditorBlock>* begin() { return mpBegin; }
    AutoRefCount<cSPEditorBlock>* end() { return mpEnd; }
};
struct VisitedVec {
    AutoRefCount<cSPEditorBlock>* mpBegin;
    AutoRefCount<cSPEditorBlock>* mpEnd;
    AutoRefCount<cSPEditorBlock>* mpCap;
    uint32_t mAlloc[2];
    VisitedVec(const AllocTag&);                            // @ 0x540470
    ~VisitedVec() { DestroyRange(mpBegin, mpEnd); Free(); }
    void DestroyRange(AutoRefCount<cSPEditorBlock>* b, AutoRefCount<cSPEditorBlock>* e);   // @ 0x454e90
    void Free();                                            // @ 0x425990
    void push_back(const AutoRefCount<cSPEditorBlock>& v);  // @ 0x4541f0
    AutoRefCount<cSPEditorBlock>* begin() { return mpBegin; }
    AutoRefCount<cSPEditorBlock>* end() { return mpEnd; }
};

void BuildPileList(cSPEditorBlock* block, BlockVec* list, bool b);   // @ 0x48c790

template<class I, class T> inline I find(I first, I last, const T& value)
{
    while (first != last && !(*first == value))
        ++first;
    return first;
}

// @ 0x00491350
int CountPileWeight(cSPEditorBlock* self, int mode)
{
    int n8 = 0;
    BlockVec list((AllocTag()));
    VisitedVec v20((AllocTag()));
    ScratchSlots<2>();
    BuildPileList(self, &list, 0);
    list.push_back(AutoRefCount<cSPEditorBlock>(self));
    if (self->GetLink3e0() != 0) {
        BuildPileList(self->GetLink3e0(), &list, 0);
        list.push_back(AutoRefCount<cSPEditorBlock>(self->GetLink3e0()));
    }
    ScratchSlots<2>();
    for (uint32_t i = 0; i < list.size(); ++i) {
        if (find(v20.begin(), v20.end(), list[i]) != v20.end())
            continue;
        if (list[i]->TestFlag(0x39)) {
            if (list[i]->GetLink3e4() != 0) {
                if (mode == 2) {
                    n8 += list[i]->GetWeight();
                    v20.push_back(AutoRefCount<cSPEditorBlock>(list[i]->GetLink3e4()));
                    ScratchSlots<2>();
                } else if (mode == 1) {
                    if (find(list.begin(), list.end(), list[i]->GetLink3e4()) != list.end()) {
                        n8 += list[i]->GetWeight();
                        v20.push_back(AutoRefCount<cSPEditorBlock>(list[i]->GetLink3e4()));
                        ScratchSlots<2>();
                    }
                }
            } else if (mode == 1) {
                n8 += list[i]->GetWeight();
            } else if (mode == 2) {
                n8 = n8;
            }
        } else {
            n8 += list[i]->GetWeight();
            if (list[i]->GetLink3e0() != 0)
                v20.push_back(AutoRefCount<cSPEditorBlock>(list[i]->GetLink3e0()));
        }
    }
    ScratchSlots<2>();
    return n8;
}
