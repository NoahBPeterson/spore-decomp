// Slice s004942b0 -- SP::EditorUtils::GetRotationAndPositionBasedOnBehavior (5113 bytes).
// Editor /Od region. Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Name from the dev-build PDB: the only EditorUtils function with this signature,
//   ?GetRotationAndPositionBasedOnBehavior@EditorUtils@SP@@YA_NPAVcSPEditorBlock@2@
//    AAUcSPVector3@@AAUcSPMatrix3@@U4@_N4@Z
// (bool (cSPEditorBlock*, cSPVector3& pos, cSPMatrix3& orient, cSPVector3 dir, bool, bool)),
// dev SPEditorManipulationUtilities.obj. Callers push exactly that 0x20-byte frame.
//
// Retail cSPEditorBlock offsets used here (dev PDB offset +8 from mBaseOrientation on):
//   +0x28 mEditorModel, +0x60 mOrientation, +0xa8 mBaseOrientation, +0x150 mSnapType,
//   +0x33c mSymmetricBlock, +0x450 a float, +0xdc8 eastl::bitset<60> mFlags.
#include "types.h"

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

struct cSPMatrix3;

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(const cSPVector3& o);                                     // 0x004098a0
    float& operator[](int i) { return (&x)[i]; }
};

struct cSPMatrix3 {
    cSPVector3 mRow[3];
    cSPMatrix3(const cSPMatrix3& o);                                     // 0x0041cb40
    cSPVector3& operator[](int i) { return mRow[i]; }
};

struct cSPBoundingBox {
    cSPVector3 mMin;
    cSPVector3 mMax;
    void GetCorners(cSPVector3* corners);                                // 0x00466320
};

cSPVector3 operator+(const cSPVector3& a, const cSPVector3& b);          // 0x0041dc10
cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b);          // 0x0041db10
cSPVector3 operator*(const cSPVector3& a, const float& s);               // 0x0041dca0
cSPVector3& operator*=(cSPVector3& a, const float& s);                   // 0x0041dba0
cSPVector3& operator+=(cSPVector3& a, const cSPVector3& b);              // 0x0041ddb0
cSPVector3 operator*(const cSPVector3& v, const cSPMatrix3& m);          // 0x0041daf0
cSPVector3 Cross(const cSPVector3& a, const cSPVector3& b);              // 0x00454c00
float Dot(const cSPVector3& a, const cSPVector3& b);                      // 0x00455cc0
float Length(const cSPVector3& v);                                        // 0x0040ae50
cSPVector3 Normalize(const cSPVector3& v);                                // 0x00436ce0

extern cSPVector3 g_ZAxis;         // 0x015d6324
extern cSPVector3 g_SymmetryAxis;  // 0x015d63f4

namespace EA {
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};
}

namespace eastl {
struct sp_vector_allocator {};

// eastl::bitset<60>
struct bitset60 {
    uint32_t mWord[2];
    bool test(uint32_t i) const {
        if (i < 60)
            return (mWord[i / 32] & (1 << (i % 32))) != 0;
        return false;
    }
};
}

namespace SP {
class cSPEditorBlock;

struct cSPEditorModel {
    bool IsSymmetryEnabled();                                            // 0x004adc40 (byte +0x4f)
};

// SP::cSPEditorSnapVector (0x20 bytes): normal, origin, pinning info, lock flag.
struct cSPEditorSnapVector {
    cSPVector3 mNormal;
    cSPVector3 mOrigin;
    void* mTriangleInfo;
    bool mLockToAxis;
    ~cSPEditorSnapVector();                                              // 0x004ae250
};

struct BlockVector {   // eastl::vector<EA::AutoRefCount<cSPEditorBlock>, sp_vector_allocator>
    EA::AutoRefCount<cSPEditorBlock>* mpBegin;
    EA::AutoRefCount<cSPEditorBlock>* mpEnd;
    EA::AutoRefCount<cSPEditorBlock>* mpCapacity;
    BlockVector(const eastl::sp_vector_allocator& a = eastl::sp_vector_allocator());  // 0x00540470
    ~BlockVector();                                                      // 0x00453eb0
    void push_back(const EA::AutoRefCount<cSPEditorBlock>& v);           // 0x004541f0
};

class cSPEditorBlock {
public:
    virtual void v00();
    virtual int AddRef();                                                // +0x04
    virtual int Release();                                               // +0x08

    uint32_t pad04[9];
    cSPEditorModel* mEditorModel;            // +0x28
    uint32_t pad2c[13];
    cSPMatrix3 mOrientation;                 // +0x60
    uint32_t pad84[9];
    cSPMatrix3 mBaseOrientation;             // +0xa8
    uint32_t padcc[33];
    int mSnapType;                           // +0x150
    uint32_t pad154[122];
    cSPEditorBlock* mSymmetricBlock;         // +0x33c (AutoRefCount)
    uint32_t pad340[68];
    float mSnapHeightOffset;                 // +0x450
    uint32_t pad454[605];
    eastl::bitset60 mFlags;                  // +0xdc8

    cSPEditorModel* GetEditorModel() { return mEditorModel; }
    cSPEditorBlock* GetSymmetricBlock() { return mSymmetricBlock; }

    int GetSnapType();                                                   // 0x0044e7e0
    int GetSymmetryIndex();                                              // 0x0044f220
    cSPEditorSnapVector GetSnapAxis(int index);                          // 0x0044d8f0
    cSPBoundingBox GetBBox(int type, bool a, bool b);                    // 0x0044ae00
    bool IsPinnedOrLocked(bool b);                                       // 0x0043bbc0
    bool IsSymmetryLocked();                                             // 0x00435c80
};

cSPVector3 normalized_safe(const cSPVector3& v);                          // 0x00449c20
bool IsNAN(const cSPVector3& v);                                          // 0x00481f00

namespace EditorUtils {
cSPMatrix3 GetSnapOrientation(cSPEditorBlock* symmetricBlock, cSPVector3 dir);           // 0x0049b460
cSPMatrix3 RotateOrientation(cSPMatrix3 m, cSPVector3 from, cSPVector3 to);              // 0x004906e0
cSPMatrix3 GetSymmetricOrientation(cSPEditorBlock* block, cSPMatrix3 m);                // 0x00493ce0
cSPEditorBlock* PickBlocks(BlockVector& ignore, cSPVector3 start, cSPVector3 dir,
                           cSPVector3& hitPos, cSPVector3& hitNormal, int* pIndex,
                           bool& bHit, int* pLevel);                                     // 0x004a4840

// @ 0x004942b0
bool GetRotationAndPositionBasedOnBehavior(cSPEditorBlock* block, cSPVector3& pos,
                                           cSPMatrix3& orient, cSPVector3 dir,
                                           bool bAlignToParent, bool bSnapToSymmetry)
{
    bool result = false;
    cSPMatrix3 startOrient(orient);
    bool bSymmetry = block->GetEditorModel()->IsSymmetryEnabled();
    if (!bSymmetry)
        bAlignToParent = false;
    bool bSymmetricSnaps = block->GetSymmetricBlock() && block->GetSymmetricBlock()->mFlags.test(0x37);
    bSnapToSymmetry = bSnapToSymmetry && bSymmetricSnaps;
    bool bAlignUp = (block->mFlags.test(0x11) && !bSnapToSymmetry) ||
                    (block->mFlags.test(0x32) && bSnapToSymmetry);

    // Snap onto the symmetric block's snap axis.
    if (block->GetSymmetricBlock() && bSnapToSymmetry && block->GetSnapType() != -1) {
        orient = GetSnapOrientation(block->GetSymmetricBlock(), dir);
        if (block->GetSnapType() != -2) {
            cSPEditorBlock* sym = block->GetSymmetricBlock();
            cSPEditorSnapVector axis = sym->GetSnapAxis(block->GetSnapType());
            cSPVector3 normal;
            normal = axis.mNormal * block->GetSymmetricBlock()->mOrientation;
            cSPEditorBlock* sym2 = block->GetSymmetricBlock();
            orient = RotateOrientation(orient, normal, sym2->mOrientation[2]);
        }
        result = true;
    }

    // Keep the block upright (Z up) with its forward axis horizontal.
    if (block->GetSymmetricBlock() && bAlignUp) {
        if ((bSymmetry && block->GetSymmetryIndex() == 0) || bAlignToParent) {
            orient = GetSymmetricOrientation(block, orient);
            result = true;
        } else {
            cSPVector3 forward;
            forward = orient[1];
            cSPVector3 right;
            right = orient[0];
            forward[2] = 0.0f;
            forward = normalized_safe(forward);
            cSPVector3 up = normalized_safe(Cross(right, forward));
            if (up.x * up.x + up.y * up.y + up.z * up.z < 0.9f || IsNAN(up)) {
                cSPMatrix3 base(block->mBaseOrientation);
                up = g_ZAxis;
                forward = normalized_safe(Cross(up, right));
            }
            orient[0] = right;
            orient[1] = forward;
            orient[2] = up;
        }
        result = true;
    }

    // Keep the block's right axis on the symmetry axis.
    if (block->mFlags.test(0x13) && block->GetSymmetricBlock()) {
        if ((bSymmetry && block->GetSymmetryIndex() == 0) || bAlignToParent) {
            orient = GetSymmetricOrientation(block, orient);
        } else {
            cSPVector3 forward;
            forward = orient[1];
            cSPVector3 right(g_SymmetryAxis);
            if (block->GetSymmetryIndex() == -1) {
                float flip = -1.0f;
                right *= flip;
            }
            forward[1] = 0.0f;
            forward = Normalize(forward);
            if (bAlignToParent && (float)fabs(forward[2]) > 0.0f) {
                forward[0] = 0.0f;
                forward = Normalize(forward);
            }
            cSPVector3 up = normalized_safe(Cross(right, forward));
            if (up.x * up.x + up.y * up.y + up.z * up.z < 0.9f || IsNAN(up)) {
                up = g_ZAxis;
                forward = normalized_safe(Cross(up, right));
            }
            orient[0] = right;
            orient[1] = forward;
            orient[2] = up;
        }
        result = true;
    }

    // Drop the block down onto whatever lies below it along its forward axis.
    if (block->mFlags.test(0x12) && block->GetSymmetricBlock() &&
        !block->IsPinnedOrLocked(false) && !bSnapToSymmetry) {
        cSPMatrix3 m(startOrient);
        cSPVector3 forward;
        forward = m[1];
        forward[2] = 0.0f;
        forward = normalized_safe(forward);
        if (forward.x * forward.x + forward.y * forward.y + forward.z * forward.z < 0.9f || IsNAN(forward)) {
            m = block->mBaseOrientation;
            forward = m[1];
            forward[2] = 0.0f;
            forward = normalized_safe(forward);
        }
        if (forward.x * forward.x + forward.y * forward.y + forward.z * forward.z > 0.9f) {
            cSPBoundingBox bbox = block->GetBBox(1, false, false);
            cSPVector3 corners[8];
            bbox.GetCorners(corners);
            cSPVector3 center;
            center = (corners[0] * 0.5f + corners[1] * 0.5f) * orient + pos;
            if (0.1f > center[2])
                center[2] = 0.1f;
            if (block->GetSymmetricBlock()) {
                cSPBoundingBox symBox = block->GetSymmetricBlock()->GetBBox(0, false, false);
                if (symBox.mMax[2] + 0.1f > center[2])
                    center[2] = symBox.mMax[2] + 0.1f;
            }

            BlockVector ignore;
            {
                EA::AutoRefCount<cSPEditorBlock> sym(block->GetSymmetricBlock());
                ignore.push_back(sym);
            }
            int level = 4;
            cSPVector3 hitPos;
            cSPVector3 hitNormal;
            int hitIndex;
            bool bHit;
            cSPEditorBlock* hitBlock = PickBlocks(ignore, center - forward * 20.0f, forward,
                                                  hitPos, hitNormal, &hitIndex, bHit, &level);
            if (hitBlock) {
                cSPVector3 up;
                up = orient[1];
                float offset = block->mSnapHeightOffset;
                cSPVector3 target;
                target = hitPos - up * offset;
                cSPVector3 diff = target - center;
                cSPVector3 toTarget(diff);
                float along = Dot(toTarget, up);
                if (along < 0.0f) {
                    cSPVector3 diff2 = target - center;
                    cSPVector3 delta(diff2);
                    float dist = -Length(delta);
                    pos += up * dist;
                    result = true;
                }
            }
        }
    }

    if (bSymmetry && !block->IsSymmetryLocked() &&
        (block->GetSymmetryIndex() == 0 || bAlignToParent) && !result &&
        block->mFlags.test(0) && block->GetSymmetricBlock()) {
        orient = GetSymmetricOrientation(block, orient);
        result = true;
    }

    if (!block->mFlags.test(0) && block->GetSymmetricBlock()) {
        orient = block->mBaseOrientation;
        result = true;
    }
    return result;
}
}  // namespace EditorUtils
}  // namespace SP
