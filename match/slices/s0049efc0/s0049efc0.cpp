// Slice s0049efc0: SP editor rigid move of a block set (with symmetric partners).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// 0x49efc0 (cdecl): every block of `blocks` (skipping ones already handled through a symmetric
// partner) is moved from the frame (oldPos, oldRot) to (newPos, newRot): its position is re-expressed
// relative to the old frame and rotated by delta = Inverse(oldRot) * newRot, its orientation is
// multiplied by delta.  The pile below each block follows (rigidly with the same transform, or by plain
// offset when the block has boolean attribute 12 "move by offset"), and the pile under the symmetric
// partner gets the mirrored (x -> -x) transform.  When the root block has a socket-connector model
// and the block carries attribute 12, the block is snapped to that model's offset instead.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---------------------------------------------------------------- math
// rw::math::fpu::Vector3Template<float,0>: copy ctor out of line (0x004098a0)
struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);                         // 0x004098a0
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
};
// rw::math::fpu::Matrix33Template<float>: default ctor out of line (0x00402ab0), trivial copy
struct Matrix33T {
    float m[3][3];
    Matrix33T();                                         // 0x00402ab0
};
// local matrix flavour: assigned after default construction
struct Matrix3L : Matrix33T {
    Matrix3L(const Matrix33T& o) { Matrix33T::operator=(o); }
};
// cSPMatrix3: copy-constructed from the base
struct cSPMatrix3 : Matrix33T {
    cSPMatrix3(const Matrix33T& o) : Matrix33T(o) {}
};

Vector3T operator-(const Vector3T& a, const Vector3T& b);     // 0x0041db10
Vector3T operator+(const Vector3T& a, const Vector3T& b);     // 0x0041dc10
Vector3T operator*(const Vector3T& v, const Matrix33T& m);    // 0x0041daf0
Matrix33T operator*(const Matrix33T& a, const Matrix33T& b);  // 0x0041de20
Matrix33T Inverse(const Matrix33T& m);                        // 0x0041ded0
Vector3T Mirror(const Vector3T& v);                           // 0x004a8f40 (x -> -x)
Matrix33T MirrorMatrix(const Matrix33T& m, int axis);         // 0x004a8e10

extern const Vector3T kZeroVector;                            // 0x015d64d8

// ---------------------------------------------------------------- EA / EASTL
struct AllocTag { AllocTag() {} };

struct RefObj {
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};

template<class T> struct AutoRefCount {
    T* mp;
    AutoRefCount(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~AutoRefCount() { if (mp) mp->Release(); }
    operator T*() const { return mp; }
    T* operator->() const { return mp; }
};

template<unsigned N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(unsigned i) const {
        if (i < N) {
            const uint32_t word = mWord[i / 32];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

namespace eastl {
template<class InputIterator, class T>
inline InputIterator find(InputIterator first, InputIterator last, const T& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}
}

struct cSPEditorBlock;
typedef AutoRefCount<cSPEditorBlock> BlockRef;

struct SPAlloc {
    uint32_t a, b;
    SPAlloc(const AllocTag& t);                          // 0x00429360
};
// eastl::vector<AutoRefCount<cSPEditorBlock>, sp_vector_allocator>
struct BlockVec {
    BlockRef* mpBegin;
    BlockRef* mpEnd;
    BlockRef* mpCapacity;
    SPAlloc mAllocator;
    BlockVec(const AllocTag& t = AllocTag()) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(t) {}
    ~BlockVec();                                         // 0x00453eb0
    void push_back(const BlockRef& v);                   // 0x004541f0
    BlockRef* begin() { return mpBegin; }
    BlockRef* end() { return mpEnd; }
    int size() const { return (int)(mpEnd - mpBegin); }
    BlockRef& operator[](int i) { return mpBegin[i]; }
};
// the same vector type constructed through its out-of-line allocator ctor
struct BlockVecX : BlockVec {
    BlockVecX(const AllocTag& t);                        // 0x00540470
};

// ---------------------------------------------------------------- editor classes
struct cSPEditorModel : RefObj {
    bool IsSymmetryEnabled();                            // 0x004adc40
};
struct cMWModel : RefObj {
    char pad4[0xc - 4];
    Vector3T mOffset;                                    // +0x0c
};

struct cSPEditorBlock : RefObj {
    char pad0[0x28 - 4];
    AutoRefCount<cSPEditorModel> mpEditorModel;          // +0x28
    char pad2c[0x48 - 0x2c];
    cSPVector3 mPosition;                                // +0x48
    char pad54[0xa8 - 0x54];
    Matrix33T mOrientation;                              // +0xa8
    char padcc[0x3e0 - 0xcc];
    AutoRefCount<cSPEditorBlock> mpSymmetricBlock;       // +0x3e0
    char pad3e4[0x3f0 - 0x3e4];
    AutoRefCount<cMWModel> mpSocketConnectorModel;       // +0x3f0
    char pad3f4[0xdc8 - 0x3f4];
    bitset<60> mFlags;                                   // +0xdc8

    int GetSymmetryIndex();                              // 0x0044f220
    void SetPosition(const Vector3T& pos, bool notify);  // 0x00448e90
    void SetOrientation(const Matrix33T& m, bool notify);   // 0x00449420
};

void BuildPileList(cSPEditorBlock* block, BlockVec* list, bool b);            // 0x0048c790
bool GetSymmetricPile(cSPEditorBlock* block, BlockVec* list, bool b);         // 0x0049dd20

// @ 0x49efc0
void MoveBlocks(cSPEditorBlock* root, Vector3T oldPos, Vector3T newPos, Matrix33T oldRot,
                Matrix33T newRot, BlockVec* blocks)
{
    Matrix3L invOld = Inverse(oldRot);
    Matrix3L deltaRot = invOld * newRot;
    bool haveSocket = false;
    Vector3T socketPos(kZeroVector);
    if (root->mpSocketConnectorModel) {
        socketPos = root->mpSocketConnectorModel->mOffset;
        haveSocket = true;
    }
    BlockVecX processed((AllocTag()));
    int nBlocks = blocks->size();
    for (int i = 0; i < nBlocks; i++) {
        cSPEditorBlock* block = (*blocks)[i];
        if (eastl::find(processed.begin(), processed.end(), (*blocks)[i]) != processed.end())
            continue;
        if (root->GetSymmetryIndex() == 0 && block->mpSymmetricBlock) {
            if (eastl::find(blocks->begin(), blocks->end(), (cSPEditorBlock*)block->mpSymmetricBlock) != blocks->end()) {
                processed.push_back(BlockRef((cSPEditorBlock*)block->mpSymmetricBlock));
                ScratchSlots<2>();
            }
        }
        cSPVector3 curPos(block->mPosition);
        if (haveSocket && block->mFlags.test(12)) {
            block->SetPosition(socketPos, true);
        } else {
            cSPVector3 local = (curPos - oldPos) * deltaRot;
            block->SetPosition(cSPVector3(newPos + local), true);
            cSPVector3 unused = local * Inverse(newRot);
            block->SetOrientation(cSPMatrix3(block->mOrientation * deltaRot), true);
        }
        cSPVector3 shift = block->mPosition - curPos;
        BlockVec pile;
        BuildPileList(block, &pile, 0);
        for (int j = 0, cnt = pile.size(); j < cnt; j++) {
            cSPEditorBlock* child = pile[j];
            curPos = child->mPosition;
            if (block->mFlags.test(12)) {
                child->SetPosition(cSPVector3(curPos + shift), false);
            } else {
                cSPVector3 local = (curPos - oldPos) * deltaRot;
                child->SetOrientation(cSPMatrix3(child->mOrientation * deltaRot), false);
                child->SetPosition(cSPVector3(newPos + local), true);
            }
        }
        BlockVec mirrorPile;
        if (block->mpSymmetricBlock && block->mpEditorModel->IsSymmetryEnabled()
            && GetSymmetricPile(block->mpSymmetricBlock, &mirrorPile, true)) {
            for (int k = 0, cnt = mirrorPile.size(); k < cnt; k++) {
                cSPEditorBlock* child = mirrorPile[k];
                curPos = child->mPosition;
                if (block->mFlags.test(12)) {
                    child->SetPosition(cSPVector3(curPos + Mirror(shift)), false);
                } else {
                    cSPVector3 local = (curPos - Mirror(oldPos)) * MirrorMatrix(deltaRot, 0);
                    child->SetOrientation(cSPMatrix3(child->mOrientation * MirrorMatrix(deltaRot, 0)), false);
                    child->SetPosition(cSPVector3(Mirror(newPos) + local), true);
                }
            }
        }
    }
    ScratchSlots<12>();
}
