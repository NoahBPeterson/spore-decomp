// Slice s00ad33d0: FUN_00ad33d0 (cdecl), the per-frame update of a scripted "move object to a
// target position" action (action type 0x0446E38F). The action names a cinematic target
// (data +0x0C), whose game object is cast to the locomotion interface (0x0116DD1B).
//   arrive == false: just reports whether the object is near its goal (or true if the
//                    action is flagged "don't wait").
//   arrive == true : places the object. With the +0x3D flag it teleports it to the computed
//                    position (SetPositionAndOrientation + SnapToGround, water check); without,
//                    it sends a navigation goal (walk to the position, facing the second one).
// Class/member names are Claude-coined from usage.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc, same module as s00ad4b60 / s00ad2ae0).
#include "types.h"
#include <intrin.h>

struct Vector3 {
    float x, y, z;
    __forceinline Vector3() {}
    __forceinline Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    __forceinline Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    __forceinline void Set(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
};
struct Quaternion {
    float x, y, z, w;
    __forceinline Quaternion() {}
    __forceinline Quaternion(const Quaternion& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};

extern Vector3 kInvalidPosition;   // 0x0167A4BC
extern float kEpsilon;             // 0x0145A5CC (1.5258789e-05)

bool Vector3_NotEqual(const Vector3* a, const Vector3* b);         // 0x0041DD30 (cdecl)
void normalized_safe(Vector3* dst, const Vector3* src);            // 0x00449C20 (cdecl)
void Vector3_Normalize(Vector3* dst, const Vector3* src);          // 0x00436CE0 (cdecl)

#define V(n) virtual void v##n()

// Scale/position source embedded in a creature at +0xC0 (also carries the object flags at +0x50).
struct cXform {
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c); V(20); V(24); V(28);
    virtual const Vector3* GetPosition();                          // +0x2C
    V(30); V(34); V(38); V(3c); V(40); V(44); V(48); V(4c); V(50); V(54); V(58); V(5c);
    V(60); V(64); V(68); V(6c); V(70);
    virtual float GetScale();                                      // +0x74
    uint32_t pad_04[(0x50 - 0x04) / 4];
    uint32_t mFlags;                                               // +0x50
};
struct cCreature {
    uint8_t pad_00[0xC0];
    cXform mXform;                                                 // +0xC0
    uint8_t pad_114[0x137 - 0x114];
    bool mbCanSwim;                                                // +0x137
    uint8_t pad_138[0x2B0 - 0x138];
    int mMovementMode;                                             // +0x2B0
};

struct NoInit {};
struct cNavigationGoal {
    uint32_t* mpData;
    uint32_t pad_04[(0x74 - 0x04) / 4];
    cNavigationGoal(NoInit) {}
    // The two original constructors are called out of line on the same frame slot.
    void InitToward(const Vector3* pos, const Vector3* dir, float a, float b);   // 0x00AD2A50
    void InitAt(const Vector3* pos, float a, float b);                           // 0x00AD29D0
    ~cNavigationGoal();                                                          // 0x007A41A0
};

struct cStat {
    uint32_t pad_00[0x70 / 4];
    uint32_t mFlags;                                               // +0x70
};

// Locomotion interface (cast id 0x0116DD1B).
struct cLocomotive {
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c); V(20); V(24); V(28);
    virtual const Vector3* GetPosition();                          // +0x2C
    virtual const Quaternion* GetOrientation();                    // +0x30
    V(34); V(38); V(3c); V(40);
    virtual void SetPositionAndOrientation(const Vector3* pos, const Quaternion* q);   // +0x44
    V(48); V(4c); V(50); V(54); V(58); V(5c); V(60); V(64); V(68); V(6c); V(70);
    virtual float GetScale();                                      // +0x74
    V(78); V(7c); V(80); V(84); V(88); V(8c); V(90); V(94); V(98); V(9c); V(a0); V(a4);
    V(a8); V(ac); V(b0); V(b4); V(b8); V(bc);
    virtual void v_c0();
    virtual void SetSpeed(float v);                                // +0xC4
    V(c8);
    virtual float GetSpeed(int mode);                              // +0xCC
    V(d0); V(d4); V(d8);
    virtual void Request(const cNavigationGoal* goal);             // +0xDC
    V(e0); V(e4); V(e8);
    virtual void SnapToGround();                                   // +0xEC
    uint32_t pad_04[(0x50 - 0x04) / 4];
    uint32_t mFlags;                                               // +0x50
    uint8_t pad_54[0x1F0 - 0x54];
    int mField1F0;                                                 // +0x1F0
    cStat* GetStat();                                              // 0x00C41EC0
    bool IsNearGoal();                                             // 0x00C42E20
};

// The object the action targets (cast type 0x0116DD1B for the locomotion interface).
struct cGameObject {
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c); V(20); V(24); V(28);
    virtual const Vector3* GetPosition();                          // +0x2C
    V(30); V(34); V(38); V(3c); V(40); V(44); V(48); V(4c); V(50); V(54); V(58); V(5c);
    V(60); V(64); V(68); V(6c); V(70); V(74); V(78); V(7c); V(80); V(84); V(88); V(8c);
    V(90); V(94); V(98); V(9c); V(a0); V(a4); V(a8); V(ac); V(b0); V(b4);
    virtual void* Cast(uint32_t typeID);                           // +0xB8
};

struct cActionTarget {
    uint8_t pad_00[0x2C];
    cGameObject* mpObject;                                         // +0x2C
    cActionTarget();                                               // 0x00AD7940
    ~cActionTarget();                                              // 0x00AD7AD0
};

struct cCinematicManager {
    uint32_t pad[0x148 / 4];
    bool LookupTarget(uint32_t id, cActionTarget* out);            // 0x00ADB2A0
};
cCinematicManager* CinematicManager();                             // 0x00B3D4D0

struct cPlanetModel {
    Quaternion BuildSurfaceOrientation(const Vector3& pos, const Vector3& dir);   // 0x00B7F250
    bool IsInWater(const Vector3& pos);                                           // 0x00B7E3E0
    float GetRadiusAt(const Vector3* pos);                                        // 0x00B7EF70
    float GetWaterHeight();                                                       // 0x00B7E390
    Vector3 ProjectToSurface(const Vector3& src, int flag);                       // 0x00B82B40
};
cPlanetModel* PlanetModel();                                       // 0x00B3D350

cCreature* CastCreature(cLocomotive* obj);                         // 0x00AE66F0 (Cast 0xCE9F6639, null-safe)

void ComputeTargetPosition(Vector3& dst, cActionTarget& target, int placement, int arg1, int arg2,
                           const Vector3& offset);                 // 0x00AD2AE0

struct cMoveData {
    uint32_t pad_00[3];
    uint32_t mTargetID;                                            // +0x0C
    Vector3 mOffsetA;                                              // +0x10
    Vector3 mOffsetB;                                              // +0x1C
    float mDistance;                                               // +0x28
    int mPlacementA, mArgA;                                        // +0x2C, +0x30
    int mPlacementB, mArgB;                                        // +0x34, +0x38
    bool mbDontWait;                                               // +0x3C
    bool mbTeleport;                                               // +0x3D
    uint8_t pad_3e[2];
    int mArgC;                                                     // +0x40
    Vector3 mResult;                                               // +0x44
};
struct cAction {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cMoveData* Cast(uint32_t typeID);                      // +0x0C
};

// @ 0x00AD33D0
bool UpdateMoveAction(cAction* pAction, bool bArrive)
{
    if (!pAction)
        return true;
    cMoveData* data = pAction->Cast(0x0446E38F);
    if (!data)
        return true;

    cActionTarget target;
    if (!CinematicManager()->LookupTarget(data->mTargetID, &target))
        return true;

    cLocomotive* loco = target.mpObject ? (cLocomotive*)target.mpObject->Cast(0x0116DD1B) : 0;
    if (!loco)
        return true;

    if (!bArrive) {
        if (!data->mbDontWait)
            return loco->IsNearGoal() != 0;
        return true;
    }

    // vA/vB are scratch vectors reused through the function (the original shares these stack slots).
    cCreature* creature;
    Vector3 vA, vB, pos1, pos2;
    if (data->mbTeleport) {
        creature = CastCreature(loco);
        vA.Set(data->mOffsetA.x, data->mOffsetA.y, data->mOffsetA.z);
        vB.Set(data->mOffsetB.x, data->mOffsetB.y, data->mOffsetB.z);
        if (creature && data->mArgC == 0) {
            float s = creature->mXform.GetScale();
            vA.x = vA.x * s; vA.y = vA.y * s; vA.z = s * vA.z;
            s = creature->mXform.GetScale();
            vB.x = vB.x * s; vB.y = vB.y * s; vB.z = s * vB.z;
        }
        ComputeTargetPosition(pos1, target, data->mPlacementA, data->mArgA, data->mArgC, vA);
        ComputeTargetPosition(pos2, target, data->mPlacementB, data->mArgB, data->mArgC, vB);
        if (data->mDistance > kEpsilon) {
            const Vector3* p = loco->GetPosition();
            vB.Set(p->x - pos1.x, p->y - pos1.y, p->z - pos1.z);
            normalized_safe(&vA, &vB);
            float d = data->mDistance;
            vB.Set(vA.x * d + pos1.x, vA.y * d + pos1.y, vA.z * d + pos1.z);
            pos1 = PlanetModel()->ProjectToSurface(vB, 0);
        }
        Quaternion q = *loco->GetOrientation();
        if (Vector3_NotEqual(&pos2, &kInvalidPosition) && Vector3_NotEqual(&pos2, &pos1)) {
            vB.Set(pos2.x - pos1.x, pos2.y - pos1.y, pos2.z - pos1.z);
            normalized_safe(&vA, &vB);
            q = PlanetModel()->BuildSurfaceOrientation(pos1, vA);
        }
        loco->SetPositionAndOrientation(&pos1, &q);
        loco->SnapToGround();
        if (PlanetModel()->IsInWater(pos1))
            loco->mFlags |= 0x1000;
        if (creature && (creature->mXform.mFlags & 0x1000)) {
            float radius = PlanetModel()->GetRadiusAt(creature->mXform.GetPosition());
            float water = PlanetModel()->GetWaterHeight();
            if (radius < water) {
                creature->mbCanSwim = false;
                creature->mMovementMode = 3;
            }
        }
        return true;
    }

    creature = CastCreature(loco);
    vA.Set(data->mOffsetA.x, data->mOffsetA.y, data->mOffsetA.z);
    vB.Set(data->mOffsetB.x, data->mOffsetB.y, data->mOffsetB.z);
    if (creature && data->mArgC == 0) {
        float s = creature->mXform.GetScale();
        vA.x = vA.x * s; vA.y = vA.y * s; vA.z = s * vA.z;
        s = creature->mXform.GetScale();
        vB.x = vB.x * s; vB.y = vB.y * s; vB.z = s * vB.z;
    }
    ComputeTargetPosition(pos1, target, data->mPlacementA, data->mArgA, data->mArgC, vA);
    ComputeTargetPosition(pos2, target, data->mPlacementB, data->mArgB, data->mArgC, vB);
    float scale = data->mDistance;
    if (!(scale > kEpsilon))
        scale = 1.0f;
    {
    cNavigationGoal goal((NoInit()));
    if (Vector3_NotEqual(&pos2, &kInvalidPosition) && Vector3_NotEqual(&pos2, &pos1)) {
        vA.Set(pos2.x - pos1.x, pos2.y - pos1.y, pos2.z - pos1.z);
        normalized_safe(&vB, &vA);
        if (loco->mField1F0 == 0 && Vector3_NotEqual(&pos1, &kInvalidPosition)) {
            Vector3_Normalize(&vA, &pos2);
            float d = vA.z * vB.z + vA.y * vB.y + vB.x * vA.x;
            vA.Set(vB.x - vA.x * d, vB.y - vA.y * d, vB.z - vA.z * d);
            if (Vector3_NotEqual(&vA, &kInvalidPosition))
                vB = vA;
        }
        float r = scale + loco->GetScale();
        goal.InitToward(&pos1, &vB, scale, r);
        loco->Request(&goal);
        loco->SetSpeed(loco->GetSpeed(1));
        loco->GetStat()->mFlags |= 2;
    } else {
        float r = loco->GetScale() + scale;
        goal.InitAt(&pos1, scale, r);
        loco->Request(&goal);
        loco->GetStat()->mFlags |= 2;
        loco->SetSpeed(loco->GetSpeed(1));
    }
    }
    data->mResult = pos1;
    return data->mbDontWait != 0;
}

// ---- editor/model helper functions in this slice -------------------------------------------------
void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags,
                  const char* file, int line);                         // 0x00F473A0

struct EditorAction {
    V(00); V(04); V(08);
    virtual void* Cast(uint32_t typeId);                               // +0x0c
};

struct EditorFrame {
    void* volatile mpVtable0;  // +0x00
    uint32_t mField04;         // +0x04
    uint32_t mField08;         // +0x08
    uint32_t mField0c;         // +0x0c
    uint32_t mField10;         // +0x10
    uint32_t mField14;         // +0x14
    uint32_t mField18;         // +0x18
};

struct WorldManager {
    void*    mpVtable0;        // +0x00
};

void* GetWorldManager();                                           // 0x0067DDB0
void* __stdcall GonzagoModelWorld(EditorFrame* frame);             // 0x00B3D520

// @ 0x00ad3b70
int FUN_00ad3b70(EditorAction* action, bool enabled)
{
    if (action == 0)
        return 1;
    if (action->Cast(0x491fa87) == 0)
        return 1;
    if (!enabled)
        return 0;

    EditorFrame* frame = (EditorFrame*)operator new(0x1c, "Editor", 0, 0, 0, 0);
    if (frame != 0) {
        frame->mField04 = 0;
        frame->mpVtable0 = (void*)0x145a69c;
        ((void (__thiscall*)(void*))((void**)frame->mpVtable0)[1])(frame);
    }
    frame->mField08 = 0x200;
    frame->mField14 = 0x490cec8;
    frame->mField0c = 0x490e141;
    frame->mField10 = 0x490e140;
    frame->mField18 = 0;
    WorldManager* world = (WorldManager*)GetWorldManager();
    void* managerVtbl = world->mpVtable0;
    void* gonzago = GonzagoModelWorld(frame);
    ((void (__thiscall*)(void*, void*))((void**)managerVtbl)[0x28 / 4])(world, gonzago);
    ((void (__thiscall*)(void*))((void**)frame->mpVtable0)[2])(frame);
    return 0;
}

struct ContentValidationSummarizer {
    void* volatile mpVtable0;  // +0x00
    void* volatile mpVtable4;  // +0x04
    uint32_t mField08;         // +0x08
};

struct BehaviorMessage {
    void* volatile mpVtable0;  // +0x00
    void* volatile mpVtable4;  // +0x04
    void*    mpField08;        // +0x08
    uint32_t mField0c;         // +0x0c
    uint32_t mField10;         // +0x10
    uint32_t mField14;         // +0x14
    uint32_t mField18;         // +0x18
    uint32_t mField1c;         // +0x1c
    uint32_t mField20;         // +0x20
    uint32_t mField24;         // +0x24
    uint32_t mField28;         // +0x28
    uint32_t mField2c;         // +0x2c
    uint32_t mField30;         // +0x30
    uint32_t mField34;         // +0x34
    uint32_t mField38;         // +0x38
    uint32_t mField3c;         // +0x3c
};

struct EditorRes {
    uint32_t mPad00[2];        // +0x00
    void*    mpField08;        // +0x08 (sub-object whose first virtual slot is called)
    void*    mpField0c;        // +0x0c
    void*    mpHandler;        // +0x10
    EditorRes* Init();         // 0x00AD7C30
};

struct AppState {
    void AddMessage(void* arg, void* message, int mode);              // 0x007E4190 (thiscall, ret 0xc)
};

struct BehaviorOwner {
    uint32_t mPad00[3];        // +0x00
    AppState* mpAppState;      // +0x0c
    void FUN_00ad3c30(void* arg); // 0x00AD3C30
};

// @ 0x00ad3c30
void BehaviorOwner::FUN_00ad3c30(void* arg)
{
    ContentValidationSummarizer* summarizer =
        (ContentValidationSummarizer*)operator new(0xc, "Simulator", 0, 0, 0, 0);
    if (summarizer != 0) {
        summarizer->mpVtable4 = (void*)0x13ec458;
        summarizer->mField08 = 0;
        summarizer->mpVtable0 = (void*)0x145a6c0;
        summarizer->mpVtable4 = (void*)0x149bad8;
        ((void (__thiscall*)(void*))((void**)summarizer->mpVtable0)[0])(summarizer);
    }

    BehaviorMessage* message = (BehaviorMessage*)operator new(0x40, "Simulator", 0, 0, 0, 0);
    if (message != 0) {
        message->mField30 = 0;
        message->mpVtable0 = (void*)0x13eb90c;
        message->mpVtable4 = 0;
        message->mpVtable0 = (void*)0x13eb844;
        message->mField38 = 0;
        ((void (__thiscall*)(void*))((void**)message->mpVtable0)[1])(message);
    }
    message->mField30 = 0x4470a41;

    EditorRes* resource = (EditorRes*)operator new(0x14, "Simulator", 0, 0, 0, 0);
    if (resource != 0) {
        resource = resource->Init();
        if (resource != 0) {
            void* sub = &resource->mpField08;
            void* subVtbl = *(void**)sub;
            ((void (__thiscall*)(void*))((void**)subVtbl)[0])(sub);
        }
    }

    void* sub = &resource->mpField08;
    void* previous = resource->mpField0c;
    if (summarizer != previous) {
        if (summarizer != 0) {
            void* sv = summarizer->mpVtable0;
            ((void (__thiscall*)(void*))((void**)sv)[0])(summarizer);
        }
        resource->mpField0c = summarizer;
        if (previous != 0) {
            void* pv = *(void**)previous;
            ((void (__thiscall*)(void*))((void**)pv)[1])(previous);
        }
    }
    resource->mpHandler = (void*)&FUN_00ad3b70;

    if ((message->mField38 & 1) != 0 && message->mpField08 != 0) {
        void* old = message->mpField08;
        void* ov = *(void**)old;
        ((void (__thiscall*)(void*))((void**)ov)[1])(old);
    }
    message->mpField08 = sub;
    if (sub != 0) {
        void* sv = *(void**)sub;
        ((void (__thiscall*)(void*))((void**)sv)[0])(sub);
    }
    message->mField38 |= 1;

    mpAppState->AddMessage(arg, message, 0);

    {
        void* sv = *(void**)sub;
        ((void (__thiscall*)(void*))((void**)sv)[1])(sub);
    }
    {
        void* mv = message->mpVtable0;
        ((void (__thiscall*)(void*))((void**)mv)[2])(message);
    }

    if (summarizer != 0) {
        void* sv = summarizer->mpVtable0;
        ((void (__thiscall*)(void*))((void**)sv)[1])(summarizer);
    }
}

namespace Simulator {

struct ContentValidationBase {
    void*    mpVtable0;        // +0x00
    void*    mpVtable4;        // +0x04
};

class cVignetteContext {
public:
    void*    mpVtable0;        // +0x00
    uint32_t mPad04;           // +0x04
    void* volatile mpVtable8;  // +0x08
    volatile uint32_t mField0c; // +0x0c
    uint32_t mField10;         // +0x10
    uint32_t mField14;         // +0x14
    uint32_t mField18;         // +0x18
    uint32_t mField1c;         // +0x1c
    volatile float mField20;   // +0x20
    float    mField24;         // +0x24
    uint32_t mField28;         // +0x28
    cVignetteContext();        // 0x00AD3E00
};

// @ 0x00ad3e00
cVignetteContext::cVignetteContext()
{
    mpVtable8 = (void*)0x13ec458;
    mField0c = 0;
    mpVtable0 = (void*)0x145a6e0;
    mpVtable8 = (void*)0x145a6d0;
    mField20 = 1.0f;
    mField24 = 2.0f;
    mField18 = 1;
    mField14 = 0x154df28;
    mField1c = 0;
    mField28 = 0;
}

}  // namespace Simulator

struct ForwardBase {
    void* FUN_00ad72c0(uint32_t typeId);                               // 0x00AD72C0
};

struct CastInterface : public ForwardBase {
    void* FUN_00ad3e50(uint32_t typeId);                               // 0x00AD3E50
};

// @ 0x00ad3e50
void* CastInterface::FUN_00ad3e50(uint32_t typeId)
{
    void* self = this;
    if (typeId == 0xee3f516e)
        return self;
    if (typeId == 0x055116da)
        return self;
    return FUN_00ad72c0(typeId);
}

struct HashNode {
    uint32_t mPad00;           // +0x00
    void*    mpValue;          // +0x04
    HashNode* mpNext;          // +0x08
};

struct NodeReleaser {
    void ReleaseValue(void* value);                                   // 0x00BC5040
};

struct HashFreeStub {
    uint32_t mField00;         // +0x00
    void**   mpBuckets;        // +0x04
    uint32_t mBucketCount;     // +0x08
    uint32_t mElementCount;    // +0x0c
    void DoFreeNodes(void** buckets, uint32_t count);                 // 0x005687D0
};

struct HashOwner {
    uint32_t mPad00[4];        // +0x00
    HashFreeStub mTable;       // +0x10
    NodeReleaser* PrepareClear();                                     // 0x00B3D4E0
    void FUN_00ad3e90();                                              // 0x00AD3E90
};

// @ 0x00ad3e90
void HashOwner::FUN_00ad3e90()
{
    NodeReleaser* releaser = PrepareClear();
    void** bucket = &mTable.mpBuckets[0];
    HashNode* node = (HashNode*)*bucket;
    if (node == 0) {
        do {
            bucket++;
            node = (HashNode*)*bucket;
        } while (node == 0);
    }
    HashNode* end = (HashNode*)mTable.mpBuckets[mTable.mBucketCount];
    while (node != end) {
        releaser->ReleaseValue(node->mpValue);
        node = node->mpNext;
        while (node == 0) {
            bucket++;
            node = (HashNode*)*bucket;
        }
    }
    mTable.DoFreeNodes(mTable.mpBuckets, mTable.mBucketCount);
    mTable.mElementCount = 0;
}
