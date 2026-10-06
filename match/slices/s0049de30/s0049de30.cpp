// Slice s0049de30: SP editor block scale / transform helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vec3 { float x, y, z; };          // raw struct (implicit copies = dword moves)
struct Vector3T : Vec3 {
    Vector3T() {}
    Vector3T(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    float& operator[](int i) { return (&x)[i]; }
    float GetZ() const { return z; }
};
struct Matrix33T {
    Vector3T xAxis, yAxis, zAxis;
    Matrix33T() {}
    Matrix33T(const Matrix33T& m);        // 0x41cb40 (Matrix3::Assign)
};
struct Matrix33Const { float f[9]; };
extern Matrix33Const g_DefaultMatrix;    // 0x15d63a8
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3& operator=(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPMatrix3 : Matrix33T {
    cSPMatrix3() {}
    cSPMatrix3(const cSPMatrix3& m) : Matrix33T(m) {}
    cSPMatrix3(const Matrix33Const& g);   // 0x449cc0
};
struct RawMat { float f[9]; };            // implicit-copy 36 bytes (rep movsd)

namespace eastl { struct sp_vector_allocator { sp_vector_allocator() {} }; struct bitset60 {
    uint32_t mWord[2];
    bool test(uint32_t i) const {
        if (i < 60) {
            uint32_t w = mWord[i >> 5];
            return (w & (1u << (i % 32))) != 0;
        }
        return false;
    }
}; }

struct cSPEditorBlock;
namespace EA {
template <class T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
}
struct BlockVector {   // eastl::vector<EA::AutoRefCount<cSPEditorBlock>, sp_vector_allocator>
    EA::AutoRefCount<cSPEditorBlock>* mpBegin;
    EA::AutoRefCount<cSPEditorBlock>* mpEnd;
    EA::AutoRefCount<cSPEditorBlock>* mpCapacity;
    int mAllocator;
    BlockVector(const eastl::sp_vector_allocator& a);                    // 0x00540470
    BlockVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~BlockVector();                                                      // 0x00453eb0
    EA::AutoRefCount<cSPEditorBlock>& operator[](int i) { return mpBegin[i]; }
    void erase(EA::AutoRefCount<cSPEditorBlock>* first, EA::AutoRefCount<cSPEditorBlock>* last);  // 0x00454280
};

struct RefCountTemplate {                // EA::RefCountTemplate<int> (at +4 of the owner)
    virtual ~RefCountTemplate() {}
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    // Contains `delete this`, so cl declines to inline it, yet callers still reserve its frame.
    int Release()                                                        // 0x00453540
    {
        int r = mnRefCount-- - 1;
        if (r)
            return r;
        mnRefCount = 1;
        delete this;
        return 0;
    }
};
struct cSPEditorModel {
    int vt;
    RefCountTemplate rc;                 // +4
    int GetBlockCount();                 // 0x004accf0
    cSPEditorBlock* GetBlock(int i);     // 0x004accb0
    bool IsSymmetryEnabled();            // 0x004adc40
};
struct ModelRef {                        // EA::AutoRefCount<cSPEditorModel>
    cSPEditorModel* mp;
    ModelRef(cSPEditorModel* p) : mp(p) { if (mp) mp->rc.AddRef(); }
    ~ModelRef() { if (mp) mp->rc.Release(); }
    cSPEditorModel* operator->() const { return mp; }
};

struct cSPEditorLimbStructure {
    char pad[0x58];
    cSPEditorLimbStructure();                                            // 0x00488850
    ~cSPEditorLimbStructure();                                           // 0x00488900
    void Init(cSPEditorBlock* block, bool isBase, bool b);               // 0x004891a0
    void FixAllJoints();                                                 // 0x00489ae0
    void Clear();                                                        // 0x00488980
};

struct cSPEditorBlock {
    virtual int _v0();
    char pad04[0x28 - 4];
    cSPEditorModel* mEditorModel;                // +0x28
    char pad2c[0x48 - 0x2c];
    cSPVector3 mPosition;                        // +0x48
    Vec3 mPrevPosition;                          // +0x54
    RawMat mOrientation;                         // +0x60
    RawMat mPrevOrientation;                     // +0x84
    RawMat mBaseOrientation;                     // +0xa8
    RawMat mPrevBaseOrientation;                 // +0xcc
    char pad0f0[0x1d8 - 0xf0];
    float mScale;                                // +0x1d8
    char pad1dc[0x33c - 0x1dc];
    cSPEditorBlock* mSymmetricBlock;             // +0x33c
    BlockVector mChildren;                       // +0x340
    char pad350[0x3e0 - 0x350];
    cSPEditorBlock* mLinkedBlock;                // +0x3e0
    char pad3e4[0xdc8 - 0x3e4];
    eastl::bitset60 mFlags;                      // +0xdc8

    cSPEditorModel* GetEditorModel() { return mEditorModel; }
    cSPEditorBlock* GetLinkedBlock() { return mLinkedBlock; }
    cSPEditorBlock* GetSymmetricBlock() { return mSymmetricBlock; }
    bool HasAnyBlockFlag();                                              // 0x00435d40
    void FUN_44c0e0(int* a, int* b, int* c);                             // 0x0044c0e0
};

// ---- helpers ----
void FUN_4942b0(cSPEditorBlock* block, float* out, uint32_t scale, cSPVector3 pos, int a, int b);  // @ 0x4942b0
cSPMatrix3 FUN_49e880(cSPEditorBlock* block, cSPMatrix3 m);                                       // @ 0x49e880
void FUN_49de30(cSPEditorBlock* block, float newScale, float oldScale, BlockVector* blocks, bool flag);  // @ 0x49de30
float ClampAndSetScale(cSPEditorBlock* block, float value, bool clamp);                           // @ 0x49dca0
bool FUN_49dd20(cSPEditorBlock* block, BlockVector* out, int flags);                              // @ 0x49dd20
void BuildPileList(cSPEditorBlock* block, BlockVector* out, int flags);                           // @ 0x48c790
void RepinBlockToTorso(cSPEditorBlock* block, cSPVector3 pos, cSPMatrix3 orient, int a);           // @ 0x49fbd0
bool FUN_4a6120(cSPEditorBlock* block);                                                           // @ 0x4a6120
cSPEditorBlock* GetLimbRoot(cSPEditorBlock* block);                                               // @ 0x4a5e10
cSPVector3 FUN_4a06c0(cSPEditorBlock* block);                                                     // @ 0x4a06c0
cSPVector3 operator-(const Vec3& a, const Vec3& b);                                   // 0x41db10
cSPVector3 operator+(const Vec3& a, const Vec3& b);                                   // 0x41dc10
cSPVector3 operator*(const Vec3& a, const float& s);                                        // 0x41dca0
cSPVector3 operator/(const Vec3& a, const float& s);                                        // 0x453880
cSPVector3 operator*(const Vec3& v, const cSPMatrix3& m);                                   // 0x41daf0
cSPMatrix3 Transposed(const cSPMatrix3& m);                                                       // 0x41ded0
cSPVector3 normalized_safe(const Vec3& v);                                                              // 0x449c20
cSPVector3 Cross(const Vec3& a, const Vec3& b);                                                   // 0x44e460

// @ 0x49ec40
void FUN_49ec40(cSPEditorBlock* block, float* out, uint32_t scale, cSPMatrix3* mat, bool flag)
{
    if (flag) {
        FUN_4942b0(block, out, scale, block->mPosition, 1, 0);
        *mat = FUN_49e880(block, *mat);
    }
    out[0] = 0.0f;
}

// @ 0x49de30
// Rescale the child blocks in `blocks` about `block` by newScale/oldScale: each child's offset from
// block is divided by oldScale, scaled (and rotated by the child's base orientation if it is flag 7),
// and the child is re-pinned; then the limb structure of block / its linked block are re-fixed.
void FUN_49de30(cSPEditorBlock* block, float newScale, float oldScale, BlockVector* blocks, bool flag)
{
    if (newScale != oldScale) {
    float fDelta = newScale - oldScale;
    int unused;   // reserved frame slot (unused local in the original)
    BlockVector pile((eastl::sp_vector_allocator()));
    int num = (int)(blocks->mpEnd - blocks->mpBegin);
    for (int i = 0; i < num; i++) {
        if (!((cSPEditorBlock*)(*blocks)[i])->mFlags.test(7)) {
            pile.erase(pile.mpBegin, pile.mpEnd);
            BuildPileList((*blocks)[i], &pile, 0);
            cSPVector3 d;
            d = ((*blocks)[i]->mPrevPosition - block->mPrevPosition) / oldScale;
            cSPVector3 newPos;
            if (block->mFlags.test(7)) {
                cSPVector3 tmp;
                tmp = d * Transposed(*(cSPMatrix3*)&block->mPrevOrientation);
                tmp[0] *= newScale;
                tmp[1] *= oldScale;
                tmp[2] *= newScale;
                d = tmp * *(cSPMatrix3*)&block->mOrientation;
                newPos = block->mPosition + d;
            } else {
                newPos = block->mPosition + d * newScale;
            }
            RepinBlockToTorso((*blocks)[i], newPos, *(cSPMatrix3*)&(*blocks)[i]->mBaseOrientation, 0);
        }
    }
    if (FUN_4a6120(block)) {
        cSPEditorBlock* limb = GetLimbRoot(block);
        if (flag && limb) {
            if (!block->mFlags.test(7)) {
                if (limb->mFlags.test(7) || (limb->GetSymmetricBlock() && limb->GetSymmetricBlock()->mFlags.test(7))) {
                    cSPEditorLimbStructure a;
                    cSPEditorLimbStructure b;
                    a.Init(block, 0, 0);
                    if (block->GetLinkedBlock()) b.Init(block->GetLinkedBlock(), 0, 0);
                    a.FixAllJoints();
                    if (block->GetLinkedBlock()) {
                        b.FixAllJoints();
                        b.Clear();
                    }
                    a.Clear();
                }
            }
        }
        if (block->mFlags.test(0x2d) && !block->HasAnyBlockFlag()) {
            cSPVector3 g = FUN_4a06c0(block);
            cSPVector3 pos2;
            pos2 = block->mPosition;
            pos2.z = g.GetZ();
            RepinBlockToTorso(block, pos2, *(cSPMatrix3*)&block->mOrientation, 0);
        }
    }
    }
}

// @ 0x49e6a0
// SetBlockScale: snapshot current positions/orientations of the model's blocks, clamp+apply the new
// scale, then rescale the child blocks (and the linked block's children if symmetry is enabled).
void SetBlockScale(cSPEditorBlock* block, float scale, bool clamp, bool flag)
{
    float oldScale = block->mScale;
    ModelRef model(block->GetEditorModel());
    int n = model->GetBlockCount();
    for (int i = 0; i < n; i++) {
        cSPEditorBlock* b = model->GetBlock(i);
        b->mPrevPosition = *(Vec3*)&b->mPosition;
        b->mPrevOrientation = b->mOrientation;
        b->mPrevBaseOrientation = b->mBaseOrientation;
    }
    scale = ClampAndSetScale(block, scale, clamp);
    FUN_49de30(block, scale, oldScale, &block->mChildren, flag);
    BlockVector vec;
    if (block->GetLinkedBlock()) {
        if (block->GetEditorModel()->IsSymmetryEnabled()) {
            if (FUN_49dd20(block->GetLinkedBlock(), &vec, 0))
                FUN_49de30(block->GetLinkedBlock(), scale, oldScale, &vec, flag);
        }
    }
}


// @ 0x49e880
// Re-orthonormalize a basis in place: the axis ordering (a,b,c) comes from block->FUN_44c0e0; the
// other two rows are normalized and the remaining ones rebuilt by cross products.
cSPMatrix3 FUN_49e880(cSPEditorBlock* block, cSPMatrix3 m)
{
    cSPMatrix3 orig(m);
    int a, b, c;
    block->FUN_44c0e0(&a, &b, &c);
    Vec3 v0 = ((Vec3*)&m)[c];
    Vec3 v1 = ((Vec3*)&m)[b];
    Vec3 v2 = ((Vec3*)&m)[a];
    ((float*)&v0)[a] = 0.0f;
    ((float*)&v1)[a] = 0.0f;
    v1 = normalized_safe(v1);
    v0 = normalized_safe(v0);
    if (v0.x * v0.x + v0.y * v0.y + v0.z * v0.z > 0.9f && v1.x * v1.x + v1.y * v1.y + v1.z * v1.z > 0.9f) {
        switch (a) {
        case 0: v2 = normalized_safe(Cross(v1, v0)); break;
        case 1: v2 = normalized_safe(Cross(v0, v1)); break;
        case 2: v2 = normalized_safe(Cross(v0, v1)); break;
        }
        switch (c) {
        case 0: v0 = normalized_safe(Cross(v1, v2)); break;
        case 1: v0 = normalized_safe(Cross(v1, v2)); break;
        case 2:
            if (b < a) v0 = normalized_safe(Cross(v1, v2));
            else v0 = normalized_safe(Cross(v2, v1));
            break;
        }
        ((Vec3*)&m)[a] = v2;
        ((Vec3*)&m)[b] = v1;
        ((Vec3*)&m)[c] = v0;
        return cSPMatrix3(m);
    }
    return cSPMatrix3(g_DefaultMatrix);
}
