// Slice s00bcd2a0 -- UpdateFromSubobject (0x00bcdd00, 177 bytes, ret 8).
//
// Takes the sub-object's offset vector (vslot 0x5c, out parameter) and its position (vslot 0x2c),
// scales the offset by (vslot 0x70 + 10.0f), writes pos + offset * scale to the first output and
// 10.0f to the second output.
#include "types.h"

struct Vector3 {
    float x, y, z;
};

class cSubObject {
public:
    virtual void VS00();
    virtual void VS04();
    virtual void VS08();
    virtual void VS0c();
    virtual void VS10();
    virtual void VS14();
    virtual void VS18();
    virtual void VS1c();
    virtual void VS20();
    virtual void VS24();
    virtual void VS28();
    virtual Vector3* GetPosition();                 // +0x2c
    virtual void VS30();
    virtual void VS34();
    virtual void VS38();
    virtual void VS3c();
    virtual void VS40();
    virtual void VS44();
    virtual void VS48();
    virtual void VS4c();
    virtual void VS50();
    virtual void VS54();
    virtual void VS58();
    virtual void ComputeOffset(Vector3* pOut);      // +0x5c
    virtual void VS60();
    virtual void VS64();
    virtual void VS68();
    virtual void VS6c();
    virtual float GetScale();                       // +0x70
};

class cUpdater {
public:
    char pad00[0x34];
    cSubObject mSub;           // +0x34

    void UpdateFromSubobject(Vector3* pOut, float* pScaleOut);   // 0x00bcdd00 (thiscall, ret 8)
};

void cUpdater::UpdateFromSubobject(Vector3* pOut, float* pScaleOut) {
    Vector3 local;
    mSub.ComputeOffset(&local);
    Vector3* pPos = mSub.GetPosition();
    float px = pPos->x;
    float py = pPos->y;
    float pz = pPos->z;
    float k = mSub.GetScale() + 10.0f;
    *pScaleOut = 10.0f;
    pOut->x = local.x * k + px;
    pOut->y = local.y * k + py;
    pOut->z = local.z * k + pz;
}
