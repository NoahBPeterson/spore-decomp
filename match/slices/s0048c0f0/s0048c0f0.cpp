// Slice s0048c0f0: SP::cSPEditorLimbStructure joint building / pile list / model size.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <float.h>

inline void* operator new(unsigned int, void* p) { return p; }

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T { Vector3T xAxis, yAxis, zAxis; };
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPBoundingBox { cSPVector3 mMin, mMax; };

Vector3T operator+(const Vector3T& a, const Vector3T& b);    // @ 0x41dc10
Vector3T operator-(const Vector3T& v);                       // @ 0x422020

inline float Abs(float x) { return (x < 0.0f) ? -x : x; }

template<class T> struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    bool empty() const;                          // @ 0x526430
    void push_back(const T& v);                  // @ 0x454860
    void eraseOne(T* it);                        // @ 0x48c720
    void eraseAll(T* first, T* last);            // @ 0x454280
};

template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) return (mWord[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
};

// @ 0x48c720
template<class T>
void vector<T>::eraseOne(T* it)
{
    if (it + 1 < mpEnd) {
        T* p = it;
        for (; p + 1 < mpEnd; ++p) *p = *(p + 1);
    }
    mpEnd = mpEnd - 1;
}

namespace SP {

class cSPEditorBlock;
class cSPEditorLimbJoint;

class cSPEditorBlock { public:
    virtual void _v0();
    virtual void AddRef();                      // vtable slot 1
    virtual void Release();                     // vtable slot 2
    char pad0[0x48 - 4];
    cSPVector3 mPosition;                       // +0x48
    char pad1[0x33c - 0x54];
    cSPEditorBlock* mLink33c;                   // +0x33c
    vector<cSPEditorBlock*> mSymmetricBlocks;   // +0x340
    char pad3[0xdc8 - 0x354];
    bitset<60> mFlags;                          // +0xdc8

    cSPVector3 F_43e080();                      // @ 0x43e080
    void GetBBox(cSPBoundingBox* out, int a, int b, int c); // @ 0x44ae00
    bool F_4513e0();                            // @ 0x4513e0
    cSPVector3* F_4513a0(cSPVector3* out);      // @ 0x4513a0
    bool F_44c030();                            // @ 0x44c030
};

class cSPEditorLimbJoint { public:
    cSPEditorBlock* mJointBlock;                // +0x00
    cSPEditorLimbJoint* mUpperJoint;            // +0x04
    vector<cSPEditorLimbJoint*> mLowerJoints;   // +0x08
    cSPVector3 mTargetPosition;                 // +0x1c
    cSPVector3 mOriginalPosition;               // +0x28
    cSPVector3 mPositionAtCreation;             // +0x34
    char pad40[0x64 - 0x40];                    // +0x40
    int mJointType;                             // +0x64
    char pad68[0x6c - 0x68];                    // +0x68
};

class cSPEditorModel { public:
    char pad0[0x58];
    int mResourceId;                            // +0x58
    int GetNumParts();                          // @ 0x4accf0
    cSPEditorBlock* GetPart(int i);             // @ 0x4accb0
};

class cSPEditorLimbStructure { public:
    vector<cSPEditorBlock*> mPileList;          // +0x00
    cSPEditorBlock* mBaseBlock;                 // +0x14
    cSPEditorLimbJoint* mBaseJoint;             // +0x18
    cSPEditorBlock* mLastBone;                  // +0x1c
    cSPEditorBlock* mEndBlock;                  // +0x20
    float mLimbOriginalScale;                   // +0x24
    float mSymmetrySign;                        // +0x28
    vector<cSPEditorLimbJoint*> mFeet;          // +0x2c
    vector<cSPEditorLimbJoint*> mHands;         // +0x40

    cSPEditorLimbJoint* BuildJoints(cSPEditorBlock* block, cSPEditorLimbJoint* upper, bool b); // @ 0x48c0f0
    void GetLimbOriginalPosition(cSPVector3* out);   // @ 0x48c610
};

void* EA_alloc(unsigned size, const char* name, int a, int b, int c, int d); // @ 0xf473a0
extern const char kEditorAllocName[];                           // @ 0x13eb430
struct VAlloc {};
struct VSet { char pad[0x14]; VSet(const VAlloc& a); };          // @ 0x540470

cSPEditorBlock* GetFirstFootBlock(cSPEditorBlock* block);       // @ 0x4a9840
cSPEditorBlock* FUN_004a9920(cSPEditorBlock* block);            // @ 0x4a9920
bool FUN_004a7e60(cSPEditorBlock* block);                       // @ 0x4a7e60
float FUN_004a5c40(cSPEditorBlock* block);                      // @ 0x4a5c40
void FUN_004956b0(cSPEditorBlock* block, vector<cSPEditorBlock*>* list); // @ 0x4956b0
extern float DAT_015d6290;                                      // @ 0x15d6290

void BuildPileList(cSPEditorBlock* block, vector<cSPEditorBlock*>* list, bool b); // @ 0x48c790
void GetSymmetricBlocks(cSPEditorBlock* block, vector<cSPEditorBlock*>& out);      // @ 0x48c8d0
bool CollectPartsRec(cSPEditorBlock* block, vector<cSPEditorBlock*>& out);         // @ 0x48ccf0

namespace EditorUtils {
float CalculateModelSize(cSPEditorModel* model);               // @ 0x48ca10
int CountModelParts(cSPEditorModel* model);                    // @ 0x48cc20
float GetModelMinZ(cSPEditorModel* model);                     // @ 0x48cf00
}

// @ 0x48c0f0
cSPEditorLimbJoint* cSPEditorLimbStructure::BuildJoints(cSPEditorBlock* block, cSPEditorLimbJoint* upper, bool b)
{
    if (block == 0) return 0;

    void* mem = EA_alloc(0x6c, kEditorAllocName, 0, 0, 0, 0);
    cSPEditorLimbJoint* joint;
    if (mem != 0) {
        VAlloc alloc;
        new ((char*)mem + 8) VSet(alloc);
        joint = (cSPEditorLimbJoint*)mem;
    } else {
        joint = 0;
    }

    joint->mJointBlock = block;
    joint->mUpperJoint = upper;
    cSPVector3 pos;
    cSPVector3* src;
    if (b && block->F_4513e0()) {
        cSPVector3 tmp;
        src = block->F_4513a0(&tmp);
    } else {
        src = (cSPVector3*)((char*)block + 0x48);
    }
    pos = *src;
    joint->mTargetPosition = pos;
    joint->mOriginalPosition = pos;
    joint->mPositionAtCreation = pos;

    bool flagged = false;
    cSPVector3 limbPos;
    GetLimbOriginalPosition(&limbPos);
    (void)limbPos;

    if (block->mFlags.test(0x2d)) {
        joint->mJointType = 0;
        flagged = true;
        mFeet.push_back(joint);
    }
    if (block->mFlags.test(0x2c)) {
        mHands.push_back(joint);
        if (!flagged) {
            joint->mJointType = 1;
            flagged = true;
        }
    }
    if (!flagged) {
        bool b2 = !(block->mLink33c != 0 && block->mLink33c->mFlags.test(0xb));
        cSPEditorBlock* foot = GetFirstFootBlock(block);
        if (foot == 0) foot = FUN_004a9920(block);
        if (foot == 0) foot = FUN_004a9920(block);
        if (foot == 0)
            joint->mJointType = (-(int)b2 & 2) + 3;
        else if (foot->mFlags.test(0x2c))
            joint->mJointType = (-(int)b2 & 2) + 3;
        else if (foot->mFlags.test(0x2d))
            joint->mJointType = (-(int)b2 & 2) + 2;
    }

    for (int i = 0, n = block->mSymmetricBlocks.size(); i < n; i++) {
        cSPEditorBlock* sb = block->mSymmetricBlocks[i];
        if (sb != 0 && sb->mFlags.test(0x1f)) {
            cSPEditorLimbJoint* child = BuildJoints(sb, joint, b);
            if (child) joint->mLowerJoints.push_back(child);
        }
    }
    return joint;
}

// @ 0x48c610
void cSPEditorLimbStructure::GetLimbOriginalPosition(cSPVector3* out)
{
    if (mEndBlock != 0) {
        *out = mEndBlock->mPosition;
    } else if (mLastBone != 0) {
        *out = mLastBone->mPosition + mLastBone->F_43e080();
    } else {
        out->x = 0.0f; out->y = 0.0f; out->z = 0.0f;
    }
}

// @ 0x48c790
void BuildPileList(cSPEditorBlock* block, vector<cSPEditorBlock*>* list, bool b)
{
    int n = block->mSymmetricBlocks.empty() ? 0 : (int)block->mSymmetricBlocks.size();
    for (int i = 0; i < n; i++) {
        cSPEditorBlock* sb = block->mSymmetricBlocks[i];
        cSPEditorBlock** it = list->begin();
        while (it != list->end() && *it != sb) ++it;
        if (it == list->end()) {
            list->push_back(sb);
            BuildPileList(sb, list, b);
            if (b) FUN_004956b0(sb, list);
        }
    }
}

// @ 0x48c8d0
void GetSymmetricBlocks(cSPEditorBlock* block, vector<cSPEditorBlock*>& out)
{
    for (int i = 0, n = block->mSymmetricBlocks.size(); i < n; i++) {
        cSPEditorBlock* sb = block->mSymmetricBlocks[i];
        sb->AddRef();
        out.push_back(sb);
        sb->Release();
        if (!sb->mFlags.test(0xb))
            GetSymmetricBlocks(sb, out);
    }
}

// @ 0x48ccf0
bool CollectPartsRec(cSPEditorBlock* block, vector<cSPEditorBlock*>& out)
{
    bool found = block->mFlags.test(9);
    for (int i = 0, n = block->mSymmetricBlocks.size(); i < n; i++) {
        cSPEditorBlock* sb = block->mSymmetricBlocks[i];
        if (sb->mFlags.test(0xb) && sb->mFlags.test(0xa) && sb->F_44c030()) {
            out.push_back(sb);
            bool r = CollectPartsRec(sb, out);
            if (found || r) found = true;
            else found = sb->mFlags.test(9);
        }
    }
    return found;
}

// @ 0x48ca10
namespace EditorUtils {
float CalculateModelSize(cSPEditorModel* model)
{
    float size = 0.0f;
    if (model != 0) {
        int n = model->GetNumParts();
        for (int i = 0; i < n; i++) {
            cSPEditorBlock* block = model->GetPart(i);
            bool match = false;
            int id = model->mResourceId;
            if (id < 0x47c10954) {
                if (id == 0x47c10953 || id == (int)0x99e92f05 || id == (int)0xbdd15f3d) match = true;
            } else {
                if (id == 0x4e3f7777 || id == (int)0x72c49181) match = true;
            }
            if (!match && !FUN_004a7e60(block)) continue;
            if (!block->mFlags.test(9)) {
                cSPBoundingBox box;
                block->GetBBox(&box, 0, 0, 0);
                size += Abs(box.mMax.x - box.mMin.x) * Abs(box.mMax.y - box.mMin.y)
                      * Abs(box.mMax.z - box.mMin.z);
            } else {
                float r = FUN_004a5c40(block);
                size += DAT_015d6290 * r * r;
            }
        }
    }
    return size;
}

// @ 0x48cc20
int CountModelParts(cSPEditorModel* model)
{
    int count = 0;
    if (model != 0) {
        int n = model->GetNumParts();
        for (int i = 0; i < n; i++) {
            cSPEditorBlock* block = model->GetPart(i);
            bool match = false;
            int id = model->mResourceId;
            if (id < 0x47c10954) {
                if (id == 0x47c10953 || id == (int)0x99e92f05 || id == (int)0xbdd15f3d) match = true;
            } else {
                if (id == 0x4e3f7777 || id == (int)0x72c49181) match = true;
            }
            if (match || FUN_004a7e60(block)) count++;
        }
    }
    return count;
}

// @ 0x48cf00
float GetModelMinZ(cSPEditorModel* model)
{
    float result = 0.0f;
    if (model != 0) {
        float minZ = FLT_MAX;
        int n = model->GetNumParts();
        for (int i = 0; i < n; i++) {
            cSPEditorBlock* block = model->GetPart(i);
            if (block->mFlags.test(7)) {
                cSPBoundingBox box;
                block->GetBBox(&box, 0, 1, 0);
                if (box.mMax.z < minZ) minZ = box.mMax.z;
            }
        }
        result = minZ;
    }
    return result;
}
}  // namespace EditorUtils

}  // namespace SP

// force emission of the single-element erase helper instance used by the joint tree
template void vector<SP::cSPEditorLimbJoint*>::eraseOne(SP::cSPEditorLimbJoint**);
