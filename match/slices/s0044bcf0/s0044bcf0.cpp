// Slice s0044bcf0: /Od /Ob1 SP::cSPEditorBlock helpers (cl 15.00, frame pointer kept).
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy
//
// These are dev-PDB-named retail methods.  The /Od code keeps ebp but moves floats with SSE
// scalar loads (`movss`), so the float compares below avoid x87.
#include "types.h"
#include <xmmintrin.h>

// Flag indices.  TestFlag(i) reads bit i%32 of word i/32 of the eastl::bitset<54> at +0xdc8:
// `(*(unsigned*)((char*)this + 0xdc8 + 4 * (i/32)) >> (i%32)) & 1`.
// Word 0 lives at +0xdc8, word 1 at +0xdcc.
enum {
    kFlagSkinNeedsUpdating  = 0x09,   // +0xdc8 & 0x00000200   (retail: FUN_00435a10(9, 1))
    kFlagOrientToSurfaces   = 0x0a,   // +0xdc8 & 0x00000400
    kFlagSnapDown           = 0x0b,   // +0xdc8 & 0x00000800
    kFlagUpDirection        = 0x11,   // +0xdc8 & 0x00020000
    kFlagUseSurfaceNormal   = 0x13,   // +0xdc8 & 0x00080000
    kFlagHasNoSurfaceNormal = 0x28,   // +0xdcc & 0x000000100  (word 1, bit 8)
    kFlagDirSelect          = 0x30,   // +0xdcc & 0x000010000  (word 1, bit 16)
    kFlagConnectorVisible   = 0x05,   // +0xdc8 & 0x00000020
};

// Three-float vector.
struct Vec3 {
    float x;                    // +0x00
    float y;                    // +0x04
    float z;                    // +0x08
};

// A 3x3 row-major float matrix; retail keeps one at +0x60 and copies it by value into loops.
struct Matrix33 {
    Vec3 rows[3];               // +0x00
};

// The renderable model hung off the block (retail member at +0x10).  Its +4 word holds the
// "visible in the editor" bit that the blocker walk clears.
struct MWModel {
    unsigned int mFlags;        // +0x00
    unsigned int mBits;         // +0x04  bit 0 = visible in the editor
};

// The editor model (retail member at +0x0c); the selection queries go through its vtbl slot 0x1c.
struct EditorModel {
    virtual void V00();         // 0x00
    virtual void V04();         // 0x04
    virtual void V08();         // 0x08
    virtual void V0c();         // 0x0c
    virtual void V10();         // 0x10
    virtual void V14();         // 0x14
    virtual void V18();         // 0x18
    virtual bool HasSelectionId(unsigned int id);   // slot 0x1c, index 7
};

// The ball-connector handle (retail member at +0x3ec); RefreshBlockedState calls vtbl slot 0x30.
struct HandleBallConnector {
    virtual void V00();         // 0x00
    virtual void V04();         // 0x04
    virtual void V08();         // 0x08
    virtual void V0c();         // 0x0c
    virtual void V10();         // 0x10
    virtual void V14();         // 0x14
    virtual void V18();         // 0x18
    virtual void V1c();         // 0x1c
    virtual void V20();         // 0x20
    virtual void V24();         // 0x24
    virtual void V28();         // 0x28
    virtual void V2c();         // 0x2c
    virtual void V30();         // 0x30
};

// The rotation handle (retail member at +0x3f0); bit 0 of +4 is its "visible" bit.
struct Handle {
    unsigned int mFlags;        // +0x00
    unsigned int mVisibleBits;  // +0x04
};

struct Blk {
    unsigned int mFlags0;       // +0x00
    unsigned int mFlags4;       // +0x04
    unsigned int mFlags8;       // +0x08
    EditorModel* mEditorModel;  // +0x0c
    MWModel* mModel;            // +0x10
    unsigned int mFlags14;      // +0x14
    char pad18[0x1c];           // +0x18..+0x34
    bool mPainted;              // +0x34  remembered Paint() state
    char pad35[0x13];           // +0x35..+0x48
    float mDirComponents[3];    // +0x48  selected direction vector (x,y,z)
    char pad54[0xc];            // +0x54..+0x60
    Matrix33 mSnapAxes;         // +0x60  cached orientation matrix (copied by value)
    char pad84[0x140];          // +0x84..+0x1c4
    unsigned int mSelection;    // +0x1c4  broadcast selection value
    char pad1c8[0x178];         // +0x1c8..+0x340
    int* mChildIds;             // +0x340  begin of child-id vector
    int* mChildIdsEnd;          // +0x344  end of child-id vector
    char pad348[0x98];          // +0x348..+0x3e0
    Blk* mChild;                // +0x3e0
    char pad3e4[8];             // +0x3e4..+0x3ec
    HandleBallConnector* mBallConnector; // +0x3ec
    Handle* mRotationHandle;    // +0x3f0
    char pad3f4[0x9d4];         // +0x3f4..+0xdc8
    unsigned int mFlagsBits[2]; // +0xdc8  eastl::bitset<54> words (0xdc8, 0xdcc)

    bool TestFlag(int index) const
    {
        return (mFlagsBits[index >> 5] & (1u << (index & 0x1f))) != 0;
    }

    bool Paint();
    int C050();
    void C0e0(int& kind, int& primary, int& secondary);
    int C270(Matrix33 dirs);
    int C450();
    bool C4d0(int selection);
    bool C5a0(int selection);
    void C480(int selection);
    void Abcf0(bool first, bool recurse);

    // Retail 0x00435a10: `this` in ecx, (index, value) on the stack.  Declared only; the call
    // shape matters, not the body.
    void RuntimeFlag(int index, int value);
};

// Free helpers from the editor-model TU (0x004a7e60 / 0x00435c80).
bool BlockBlocked(Blk* block);          // 0x004A7E60
bool IsSnappedEquiv(Blk* block);        // 0x00435C80

// @ 0x0044c030  (byte-exact: `mov al, [ecx+0x34]; ret`)
bool Blk::Paint()
{
    return mPainted;
}

// ---------------------------------------------------------------------------
// @ 0x0044c050  returns the sign (-1/0/1) of the float at this+0x48.
// ---------------------------------------------------------------------------
int Blk::C050()
{
    float f = mDirComponents[0];
    if (f < -0.001f)
        return -1;
    if (f > 0.001f)
        return 1;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x0044c0e0  fills (kind, primary, secondary) for the block's next surface selection.
// kind 1 = a real direction hit, 2 = diagonal fallback; primary/secondary select the surface.
// a = flag 0x13 (use surface normal) OR flag 0x28 (no cached surface normal)
// b = flag 0x11 (up-direction override)
// ---------------------------------------------------------------------------
void Blk::C0e0(int& kind, int& primary, int& secondary)
{
    bool a = TestFlag(kFlagUseSurfaceNormal) || TestFlag(kFlagHasNoSurfaceNormal);
    bool b = TestFlag(kFlagUpDirection);

    if (b && a) {
        primary = 0;
        secondary = 2;
        kind = 1;
        return;
    }

    primary = 1;
    secondary = 0;
    if (!a)
        secondary = 2;
    kind = 0;
    if (primary == 0)
        kind = 1;
    else if (secondary == 0)
        kind = 2;
}

// ---------------------------------------------------------------------------
// @ 0x0044c270  picks the sign of an axis of the supplied direction matrix.
// flag 0x30 set => returns 0.  Otherwise primary selects a row; if its first component is
// non-zero (|x| >= 0.001) the result is sign(-x/|x|) folded onto {-1,0,1}; a zero result then
// retries with the secondary row.
// ---------------------------------------------------------------------------
int Blk::C270(Matrix33 dirs)
{
    int result = 0;
    if (TestFlag(kFlagDirSelect))
        return 0;

    int primary = 0, secondary = 0, kind = 0;
    C0e0(kind, primary, secondary);

    float f = dirs.rows[primary].x;
    float mag = f < 0.0f ? -f : f;
    if (mag >= 0.001f) {
        float r = -f;
        if (r < -0.001f)
            result = -1;
        else if (r > 0.001f)
            result = 1;
        else
            result = 0;
    } else {
        result = 0;
    }

    if (result == 0) {
        float g = dirs.rows[secondary].x;
        if (g < -0.001f)
            result = -1;
        else if (g > 0.001f)
            result = 1;
        else
            result = 0;
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x0044c450  copies the block's cached orientation matrix, then asks SnapAxes for the sign
// of the selected row's first component.
// ---------------------------------------------------------------------------
int Blk::C450()
{
    Matrix33 copy = mSnapAxes;
    return C270(copy);
}

// ---------------------------------------------------------------------------
// @ 0x0044c4d0  true when the editor model reports the given selection id.
// ---------------------------------------------------------------------------
bool Blk::C4d0(int selection)
{
    EditorModel* em = mEditorModel;
    if (em == 0)
        return false;
    if (selection == -1) {
        if (em->HasSelectionId(0xf48eb09))
            return true;
        return false;
    }
    if (selection == 1) {
        if (em->HasSelectionId(0xf48eb09))
            return true;
        return false;
    }
    if (selection == 0) {
        if (em->HasSelectionId(0x3a3b9d21))
            return true;
        return false;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0044c5a0  same query with a different id table.
// ---------------------------------------------------------------------------
bool Blk::C5a0(int selection)
{
    if (selection == -1) {
        if (mEditorModel->HasSelectionId(0x18c1dbe0))
            return true;
    }
    if (selection == 1) {
        if (mEditorModel->HasSelectionId(0xf48eb09))
            return true;
    }
    if (selection == 0) {
        if (mEditorModel->HasSelectionId(0x3a3b9d21))
            return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0044c480  broadcast a selection value to this block and its child.
// ---------------------------------------------------------------------------
void Blk::C480(int selection)
{
    mSelection = (unsigned int)selection;
    Blk* tmp = mChild;
    Blk* t14;
    if (tmp != 0) {
        t14 = mChild;
        t14->mSelection = (unsigned int)selection;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0044bcf0  recursive "unblocked" walk (`first` drives the child recursion context).
// ---------------------------------------------------------------------------
void Blk::Abcf0(bool first, bool recurse)
{
    if (mModel == 0)
        return;

    if (!Paint()) {
        RuntimeFlag(9, 1);
        if (!TestFlag(kFlagOrientToSurfaces) || !TestFlag(kFlagSnapDown))
            mModel->mBits |= 1u;
        if (mRotationHandle != 0 && !TestFlag(kFlagConnectorVisible))
            mRotationHandle->mVisibleBits |= 1u;
        mPainted = true;
    }

    int n = (int)(mChildIdsEnd - mChildIds);
    for (int i = 0; i < n; ++i) {
        if (BlockBlocked(this)) {
            Blk* child = (Blk*)(unsigned int)mChildIds[i];
            if (IsSnappedEquiv(child))
                child->Abcf0(first, true);
            else if (recurse)
                child->Abcf0(first, recurse);
        } else if (recurse) {
            Blk* child = (Blk*)(unsigned int)mChildIds[i];
            child->Abcf0(first, recurse);
        }
    }

    if (first && mChild != 0)
        mChild->Abcf0(false, false);
}
