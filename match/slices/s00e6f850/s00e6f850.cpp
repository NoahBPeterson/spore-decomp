// Slice s00e6f850 -- SP cell TU: orients a cell toward the avatar cell (0x00e70650, 371 bytes).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (cell TU; no /EHsc). Self arrives in EAX, the float
// argument on the stack (static register convention of the original TU; the static is emitted with a
// non-static stand-in caller).
#include "types.h"
#include <math.h>
typedef uint32_t uint32;

struct cObjectPool {
    void* GetSafe(int index);                 // 0x00b721d0 (thiscall, ret 4)
};

struct cGameStub {                            // gspCellGame (only the fields this function touches)
    char pad0[0x1c];
    cObjectPool mCells;                       // +0x1c
    char pad1[0x411c - 0x1d];
    int mAvatarCellIndex;                     // +0x411c
};
extern cGameStub* gspCellGame;                // 0x016b3c04

struct cEntity {
    int mIndex;                               // +0x00
    char mbFlag;                              // +0x04
    char pad5[3];
    float mPosA;                              // +0x08
    float mPosB;                              // +0x0c
    float mPosC;                              // +0x10
    uint32 mQuat[4];                          // +0x14..+0x20
    char pad24[0x4c - 0x24];
    float mX;                                 // +0x4c
    float mY;                                 // +0x50
    float mZ;                                 // +0x54
    char pad58[0x108 - 0x58];
    uint32 field_108;                         // +0x108 (key passed to GetCellKey)
};

struct CellRecord {                           // 0x00e52910 result
    char pad0[4];
    float radius;                             // +0x04
    char pad8[0x18 - 8];
    float f18;                                // +0x18
    char pad1c[0x40 - 0x1c];
    float f40;                                // +0x40
};

struct cHandleRef {                           // 4-byte handle holder (ctor 0x00743b50, dtor 0x00e82130)
    int mp;
    cHandleRef();                             // 0x00743b50
    ~cHandleRef();                            // 0x00e82130
};

extern const float kCellUp[3];                // 0x015a7c40
uint32 GetCellKey(uint32 value, cHandleRef* tmp);                       // 0x00e4cc40 (-> 0x00e823a0)
const CellRecord* GetCellRecord(uint32 key);                            // 0x00e52910 (cdecl)
uint32 FUN_00e67c40(cEntity* self, uint32 key);                         // 0x00e67c40 (cdecl, 2 args)
void FUN_00e6eec0(float a, float b, float c, uint32 d, int e);          // 0x00e6eec0 (cdecl, 5 args)
const uint32* QuaternionFromFacingAndUp(uint32* out, const float* facing, const float* up); // 0x0069b600

// OrientToAvatar @ 0x00e70650
static void OrientToAvatar(cEntity* self, float p)   // self in EAX
{
    cEntity* av = (cEntity*)gspCellGame->mCells.GetSafe(gspCellGame->mAvatarCellIndex);
    if (av) {
        cHandleRef tmp;
        uint32 R = GetCellKey(self->field_108, &tmp);
        float dx = av->mX - self->mX;
        float dy = av->mY - self->mY;
        float dz = av->mZ - self->mZ;
        const CellRecord* rec = GetCellRecord(R);
        float d2 = (dy * dy + dx * dx) + dz * dz;
        if (d2 <= rec->radius * rec->radius) {
            float inv = (float)(1.0 / sqrt((double)d2));
            float facing[3] = { -(inv * dx), -(inv * dy), -(inv * dz) };
            uint32 out[4];
            const uint32* q = QuaternionFromFacingAndUp(out, facing, kCellUp);
            self->mQuat[0] = q[0];
            self->mQuat[1] = q[1];
            self->mQuat[2] = q[2];
            self->mQuat[3] = q[3];
            self->mPosA = av->mX;
            self->mPosB = av->mY;
            self->mPosC = av->mZ;
            self->mbFlag = 0;
            uint32 X = FUN_00e67c40(self, R);
            FUN_00e6eec0(p, GetCellRecord(R)->f18, GetCellRecord(R)->f40, X, 0);
        }
    }
}

// Stand-in caller so the static helper is emitted with its register convention.
void OrientToAvatarEntry(cEntity* self, float p)
{
    OrientToAvatar(self, p);
}
