// Slice s0049a2a0: SP::EditorUtils::MoveBlockOrientToSurfaces (4241 bytes, /Od).
// Flags region: editor /Od module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
//
// Moves an editor block along a pick ray onto the surfaces of the other blocks:
// intersects the ray with the block's horizontal plane (or the symmetry plane),
// asks FindPinningBlock (0x00498f10) for a parent block under the ray, falls
// back to the stacking position when nothing is hit, re-pins/re-parents the
// block and finally moves it.
//
// Name from the dev-build PDB (caller-scored candidate); the retail signature
// matches the dev mangled name ?MoveBlockOrientToSurfaces@EditorUtils@SP@@YA_N
// PAVcSPEditorBlock@2@AAV?$vector@...@@UcSPVector3@@2V?$AutoRefCount@
// VcSPEditorSkinManager@SP@@@EA@@AAU6@PAU6@_N6@Z. Retail field offsets follow the
// ModAPI EditorRigblock layout.
#include "types.h"
#pragma pack(push, 4)

// Frame filler: reserves N dwords where the original reserved the frame of an
// inline helper that cl declined to expand (see docs/matching.md, /Od holes).
template<int N> inline void ScratchSlots() { uint32_t s[N]; }


// ---- math -----------------------------------------------------------------

// rw::math::fpu::Vector3Template<float,0>: its copy constructor is out of line.
struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);                                    // 0x004098A0
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};

struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) : Vector3T(v) {}
    cSPVector3(const Vector3T& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    cSPVector3& operator=(const Vector3T& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }
};

// Plain math vector taken by value by the block movers (inline copies).
struct Vector3 {
    float x, y, z;
    Vector3(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
};

// rw::math::fpu::Matrix33Template<float,0>: copy constructor out of line.
struct Matrix33T {
    Vector3T xAxis;
    Vector3T yAxis;
    Vector3T zAxis;
    Matrix33T() {}
    Matrix33T(const Matrix33T& m);                                  // 0x0041CB40
};

struct cSPMatrix3 : Matrix33T {
    cSPMatrix3() {}
    cSPMatrix3(const cSPMatrix3& m) : Matrix33T(m) {}
};

struct Plane {
    float a, b, c, d;
    Plane() {}
    Plane(float a, float b, float c, float d);                      // 0x0044E410
};

Vector3T operator-(const Vector3T& v);                              // 0x00422020
Vector3T operator*(const Vector3T& v, const float& s);              // 0x0041DCA0
Vector3T operator*(const float& s, const Vector3T& v);              // 0x0041DE40
Vector3T operator+(const Vector3T& a, const Vector3T& b);           // 0x0041DC10
Vector3T operator-(const Vector3T& a, const Vector3T& b);           // 0x0041DB10
float Dot3(const Vector3T& a, const Vector3T& b);                   // 0x00455CC0
cSPVector3 Normalize(const Vector3T& v);                            // 0x00436CE0
float VectorLength(const cSPVector3& v);                            // 0x0040AE50
bool IntersectRayPlane(const Vector3T& origin, const Vector3T& dir,
                       const Plane& plane, float& t);               // 0x0044E640

// Plane through a point with the given normal.
struct cSPPlane : Plane {
    cSPPlane(const cSPVector3& normal, const cSPVector3& point)
        : Plane(normal[0], normal[1], normal[2], -Dot3(point, normal)) {}
};

extern cSPVector3 gSymmetryPlaneNormal;                             // 0x015D6370
extern cSPVector3 gSymmetryPlanePoint;                              // 0x015D64D8

// ---- EASTL ----------------------------------------------------------------

struct allocator {
    allocator() {}
};

template<int N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const
    {
        if (i < N) {
            uint32_t w = mWord[i >> 5];
            return (w & (1 << (i % 32))) != 0;
        }
        return false;
    }
};

// eastl::sp_vector_allocator is 8 bytes (name + flags), so these vectors are 0x14.
struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
};

struct cSPVector3Vector {
    cSPVector3* mpBegin;
    cSPVector3* mpEnd;
    cSPVector3* mpCapacity;
    sp_vector_allocator mAllocator;
    cSPVector3Vector(const allocator& a = allocator());             // 0x00540470
    ~cSPVector3Vector()
    {
        for (cSPVector3* p = mpBegin; p < mpEnd; ++p) {}
        DeallocateSelf();
        ScratchSlots<3>();      // VectorBase::DeallocateSelf frame
    }
    void DeallocateSelf();                                          // 0x005156B0
    void push_back(const cSPVector3& v);                            // 0x004739D0
};

struct cSPMatrix3Vector {
    cSPMatrix3* mpBegin;
    cSPMatrix3* mpEnd;
    cSPMatrix3* mpCapacity;
    sp_vector_allocator mAllocator;
    cSPMatrix3Vector(const allocator& a = allocator());             // 0x00540470
    ~cSPMatrix3Vector()
    {
        for (cSPMatrix3* p = mpBegin; p < mpEnd; ++p) {}
        DeallocateSelf();
        ScratchSlots<3>();      // VectorBase::DeallocateSelf frame
    }
    void DeallocateSelf();                                          // 0x004AB0D0
    void push_back(const cSPMatrix3& m);                            // 0x004AA080
};

// ---- refcounting ----------------------------------------------------------

// EA::RefCountTemplate<int> (vptr + count); Release contains `delete this`,
// so cl never expands it inline but still reserves its frame.
struct RefCountTemplate {
    virtual ~RefCountTemplate();
    int mRefCount;
    int AddRef() { return mRefCount++ + 1; }
    int Release()                                                   // 0x00453540
    {
        int n = mRefCount - 1;
        mRefCount = mRefCount - 1;
        if (n == 0) {
            mRefCount = 1;
            delete this;
            return 0;
        }
        return n;
    }
};

namespace SP {

struct cSPEditorModelBase {
    virtual ~cSPEditorModelBase();
};

struct cSPEditorModel : cSPEditorModelBase, RefCountTemplate {     // RefCountTemplate at +4
    float GetGridSize();                                            // 0x004ADAA0
    float GetSize1();                                               // 0x004ADB00
    float GetSize2();                                               // 0x004ADB40
    bool IsUsingSymmetry();                                         // 0x004ADC40
};

struct cSPEditorSkinManager {
    virtual int AddRef();
    virtual int Release();
};

template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) { mpObject = x.mpObject; if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

enum eSkinIdentifier {};

struct cSPEditorBlock {
    uint32_t pad00[0x28 / 4];
    cSPEditorModel* mEditorModel;                                   // +0x028
    uint32_t pad2c[(0x48 - 0x2c) / 4];
    cSPVector3 mPosition;                                           // +0x048
    uint32_t pad54[(0xa8 - 0x54) / 4];
    cSPMatrix3 mBaseOrientation;                                    // +0x0a8
    uint32_t padcc[(0x138 - 0xcc) / 4];
    Vector3 mSurfaceNormal;                                         // +0x138
    uint32_t pad144[(0x33c - 0x144) / 4];
    AutoRefCount<cSPEditorBlock> mParentBlock;                      // +0x33c
    uint32_t pad340[(0x3c8 - 0x340) / 4];
    bool mIsPinningAntiAliased;                                     // +0x3c8
    bool mIsOnGround;                                               // +0x3c9
    cSPVector3 mBlockPickDirection;                                 // +0x3cc
    uint32_t pad3d8[(0x3e0 - 0x3d8) / 4];
    AutoRefCount<cSPEditorBlock> mSymmetricBlock;                   // +0x3e0
    uint32_t pad3e4[(0xdc8 - 0x3e4) / 4];
    bitset<60> mFlags;                                              // +0xdc8

    int AddRef();
    int Release();
    cSPEditorModel* GetEditorModel() { return mEditorModel; }
    cSPEditorBlock* GetParent() { return mParentBlock.get(); }
    void SetSurfaceNormal(Vector3 normal) { mSurfaceNormal = normal; }
    eSkinIdentifier GetSkinIdentifierForPicking();                  // 0x0043A870
    float GetStackingDistance();                                    // 0x00448380
    void AttachChild(cSPEditorBlock* child);                        // 0x00438700
    void DetachChild(cSPEditorBlock* child);                        // 0x00438A40
    void MoveTo(int snapIndex, Vector3 position, Vector3 direction, bool snapped);  // 0x00436FA0
};

struct BlockVector {
    AutoRefCount<cSPEditorBlock>* mpBegin;
    AutoRefCount<cSPEditorBlock>* mpEnd;
    AutoRefCount<cSPEditorBlock>* mpCapacity;
    uint32_t mAllocator;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    AutoRefCount<cSPEditorBlock>& operator[](int i) { return mpBegin[i]; }
};

struct cMessageManager {
    void PostBlockMessage(uint32_t id, int a, cSPEditorBlock* block, int b);          // 0x0045AE40
    void PostTransformMessage(uint32_t id, int a, cSPVector3* pos, cSPMatrix3* orient); // 0x0045AED0
};
cMessageManager* MessageManager();                                  // 0x00401050

namespace EditorUtils {

cSPEditorBlock* FindPinningBlock(cSPEditorBlock* block, cSPVector3 origin, cSPVector3 dir,
                                 AutoRefCount<cSPEditorSkinManager> skinManager,
                                 cSPVector3* pPosition, cSPVector3* pNormal, BlockVector& blocks,
                                 int* pSnapIndex, bool* pSnapped);  // 0x00498F10
bool GetMissStackingPosition(cSPEditorBlock* block, BlockVector& blocks, cSPVector3 origin,
                             cSPVector3 dir, cSPMatrix3 orientation, cSPVector3& position);  // 0x0048DCD0
int ClassifyAgainstSymmetryPlane(cSPVector3& position, float gridSize, float size1,
                                 float size2, int* pOut);           // 0x00493640
cSPMatrix3 GetOrientationForNormal(cSPEditorBlock* block, Vector3 normal);  // 0x0049C210
void RepinBlockToTorso(cSPEditorBlock* block, Vector3 position, cSPMatrix3 orientation,
                       bool b);                                     // 0x0049FBD0

// /Od frame: locals are laid out by a hash of their names, so the local names
// below were chosen (searched) to reproduce the original slot order; several are
// therefore odd (bNewPos is the new position, pinned means "skip pinning",
// localBMissed is the return value, bMaxRange the stacking distance). snappedResult
// is declared before newTarget only for the same reason. ScratchSlots<N>() marks
// where the original reserved frames of inline helpers that cl declined.
// @ 0x0049a2a0
bool MoveBlockOrientToSurfaces(cSPEditorBlock* block, BlockVector& blocks, cSPVector3 rayOrigin,
                               cSPVector3 rayDir, AutoRefCount<cSPEditorSkinManager> skinManager,
                               cSPVector3& outPosition, cSPVector3* outNormal, bool b1, bool b2)
{
    bool localBMissed = false;
    AutoRefCount<cSPEditorModel> pModel(block->GetEditorModel());
    cSPVector3 origPos(block->mPosition);
    cSPMatrix3 origOrient(block->mBaseOrientation);
    cSPVector3Vector posArray;
    cSPMatrix3Vector vOrients;
    eSkinIdentifier mySkinIdentifier = block->GetSkinIdentifierForPicking();

    int theNumParts = blocks.size();
    for (int i = 0; i < theNumParts; i++) {
        posArray.push_back(blocks[i]->mPosition);
        ScratchSlots<2>();      // push_back frame
        vOrients.push_back(blocks[i]->mBaseOrientation);
        ScratchSlots<2>();
    }

    cSPEditorBlock* prevParent = block->GetParent();
    cSPVector3 finalDir_(rayDir);
    cSPVector3 bNewPos;
    cSPVector3 up;
    bool snappedResult;
    cSPEditorBlock* newTarget = 0;
    int myIndex = -1;
    snappedResult = false;
    newTarget = FindPinningBlock(block, rayOrigin, rayDir, skinManager, &bNewPos, &up, blocks,
                               &myIndex, &snappedResult);

    bool bSkipMove = false;
    bool pinned = false;
    cSPVector3 theProjected(origPos);
    cSPVector3 refPosTmp(origPos);
    cSPVector3 toSurface(block->mBlockPickDirection);

    cSPPlane curPlane(-rayDir, origPos);
    if (pModel->IsUsingSymmetry() && block->mFlags.test(15)) {
        curPlane = cSPPlane(gSymmetryPlaneNormal, gSymmetryPlanePoint);
        theProjected[0] = 0.0f;
        toSurface[0] = 0.0f;
        toSurface = Normalize(toSurface);
        ScratchSlots<5>();      // Normalize frame
        refPosTmp[0] = 0.0f;
    }

    float curT;
    ScratchSlots<2>();          // IntersectRayPlane frame
    if (IntersectRayPlane(rayOrigin, rayDir, curPlane, curT))
        theProjected = rayOrigin + curT * rayDir;

    float minZ = 0.03f;
    bool myHitGround = false;
    if (theProjected[2] < minZ) {
        theProjected[2] = minZ;
        myHitGround = true;
    }

    if (block->mParentBlock.get()) {
        float offset = pModel->GetGridSize() * 0.01f;
        cSPVector3 toBlock = origPos + origOrient.yAxis * offset - theProjected;
        if (myHitGround)
            toBlock[2] = 0.0f;
        toSurface = Normalize(toBlock);
        ScratchSlots<5>();
    }

    bool found = false;
    if (!newTarget) {
        bool stacked = GetMissStackingPosition(block, blocks, rayOrigin, rayDir,
                                               block->mBaseOrientation, outPosition);
        if (stacked) {
            float backoff = pModel->GetGridSize() / 20.0f;
            cSPVector3 posOutVal;
            cSPVector3 normalOutVal;
            cSPEditorBlock* thePCandidate = FindPinningBlock(block, theProjected - toSurface * backoff, toSurface,
                                                    skinManager, &posOutVal, &normalOutVal, blocks,
                                                    &myIndex, &snappedResult);
            float bMaxRange = block->GetStackingDistance();
            if (thePCandidate) {
                if (bMaxRange < 0.0f || VectorLength(posOutVal - theProjected) < bMaxRange) {
                    ScratchSlots<1>();  // VectorLength frame
                    bNewPos = posOutVal;
                    up = normalOutVal;
                    newTarget = thePCandidate;
                    finalDir_ = toSurface;
                    found = true;
                }
            } else if (block->mParentBlock.get()) {
                myIndex = -1;
                newTarget = block->GetParent();
                up = -origOrient.yAxis;
                bNewPos = origPos;
            }
        } else {
            localBMissed = true;
        }
    }

    up = Normalize(up);
    ScratchSlots<5>();
    if (outNormal)
        *outNormal = up;

    if (newTarget && !block->mFlags.test(51)) {
        cSPVector3 posCopy(bNewPos);
        int r1 = ClassifyAgainstSymmetryPlane(posCopy, pModel->GetGridSize(), pModel->GetSize1(),
                                                pModel->GetSize2(), 0);
        if (r1 != 3) {
            newTarget = 0;
            bool newBOk = GetMissStackingPosition(block, blocks, rayOrigin, rayDir,
                                                   block->mBaseOrientation, outPosition);
            posCopy = outPosition;
            if (ClassifyAgainstSymmetryPlane(posCopy, pModel->GetGridSize(), pModel->GetSize1(),
                                             pModel->GetSize2(), 0) == 3) {
                if (r1 == 0 || r1 == 0) {
                    outPosition[2] = bNewPos[2];
                } else {
                    outPosition[0] = bNewPos[0];
                    outPosition[1] = bNewPos[1];
                }
            }
            localBMissed = !newBOk;
        }
    }

    if (newTarget || pinned) {
        block->SetSurfaceNormal(up);
        cSPMatrix3 orientation = GetOrientationForNormal(block, up);
        RepinBlockToTorso(block, bNewPos, orientation, false);
    }

    if (!pinned) {
        if (newTarget) {
            block->mIsOnGround = false;
            if (block->mSymmetricBlock.get())
                block->mSymmetricBlock->mIsOnGround = false;
        }
        if (block->mParentBlock.get() != newTarget) {
            if (newTarget) {
                if (!block->mParentBlock.get())
                    MessageManager()->PostBlockMessage(0x3f1bf58, 0, block, 0);
                newTarget->AttachChild(block);
            } else if (block->mParentBlock.get()) {
                block->mParentBlock->DetachChild(block);
                MessageManager()->PostTransformMessage(0x3f1bf59, 0, &origPos, &origOrient);
            }
        }
    }

    if (!bSkipMove && block->mParentBlock.get() && block->mParentBlock.get() == newTarget)
        block->MoveTo(myIndex, bNewPos, finalDir_, snappedResult);

    if (!b2 && !newTarget && !pinned)
        return localBMissed;
    return localBMissed;
}

}  // namespace EditorUtils
}  // namespace SP
