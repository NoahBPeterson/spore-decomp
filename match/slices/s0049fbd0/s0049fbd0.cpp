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
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
};
struct cSPMatrix3 : Matrix33T {
    cSPMatrix3() {}
    cSPMatrix3(const Matrix33T& m) : Matrix33T(m) {}
};
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
struct cSPEditorBlock {
    virtual void _v0();
    char pad0[0xdc8 - 4];
    bitset<60> mFlags;                           // +0xdc8
};
struct cSPEditorModel {
    cSPEditorBlock* GetBlock(int i);             // @ 0x4accb0
    int GetBlockCount();                         // @ 0x4accf0
};

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
void RepinBlockToTorso(cSPEditorBlock* block, cSPVector3 t, cSPMatrix3 r, int flags)
{ (void)block; (void)t; (void)r; (void)flags; }

// @ 0x49fee0
void FUN_49fee0(cSPEditorBlock* block) { (void)block; }

// @ 0x4a0020
void FUN_4a0020(cSPEditorBlock* block) { (void)block; }

// @ 0x4a02b0
void FUN_4a02b0(cSPEditorBlock* block) { (void)block; }

// @ 0x4a06c0
void FUN_4a06c0(cSPEditorBlock* block) { (void)block; }

// @ 0x4a0900
void FUN_4a0900(cSPEditorBlock* block) { (void)block; }
