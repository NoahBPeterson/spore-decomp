// Slice s00dc96f0: vehicle behaviour-tree node (0x00dc96f0).
// Drops the current order (done-order predicate at slot 0x2c, then Release at slot 4), clears the
// attack target, stops the locomotion object, re-targets the path to the current position and
// consumes the vehicle timer.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define PAD1 virtual void CAT(pad, __COUNTER__)();
#define PAD4 PAD1 PAD1 PAD1 PAD1
#define PAD8 PAD4 PAD4
#define PAD16 PAD8 PAD8

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

// Spatial-object interface embedded at +0x34 of vehicles.
struct cSpatialObject {
    PAD8 PAD1 PAD1 PAD1                                            // slots 0..10
    virtual const Vector3& GetPosition();                          // +0x2c
    PAD16 PAD16 PAD4 PAD1                                          // slots 12..48
    virtual void Stop(float speed, int mode);                      // +0xc4
};

struct cGameData {      // embedded at +0x508 of the vehicle
    PAD16 PAD4
    virtual void SetAttackTarget(void* target);                    // +0x50
};

struct cVehicle {
    PAD16 PAD1 PAD1 PAD1
    char           pad4[0x30];
    cSpatialObject mLoco;                                          // +0x34
    char           pad38[0x508 - 0x38];
    cGameData      mGameData;                                      // +0x508

    void SetPathTarget(const Vector3& pos);                        // 0x00ca33b0
    void ConsumeTimer();                                           // 0x00c9ee50
};

// The order object the behaviour-tree tick context points at (context+0x04).
struct cVehicleOrder {
    PAD1                                                           // +0x00
    virtual void Release();                                        // +0x04
    PAD8 PAD1                                                      // slots 2..10
    virtual bool IsDone();                                         // +0x2c
    void Cancel(cVehicle* owner);                                  // 0x00dc8c50
};

// @ 0x00dc96f0
void Node96f0(cVehicle* self, int, int, int, int, cVehicleOrder** ppOrder)
{
    cVehicleOrder* pOrder = *ppOrder;
    if (pOrder && !pOrder->IsDone())
        pOrder->Cancel(self);
    if (*ppOrder)
        (*ppOrder)->Release();
    self->mGameData.SetAttackTarget(0);
    self->mLoco.Stop(0.0f, 0);
    self->SetPathTarget(self->mLoco.GetPosition());
    self->ConsumeTimer();
}
