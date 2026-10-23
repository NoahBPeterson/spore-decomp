// Slice s00d0b090 -- SP::cCommunityEditor camera/placement helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc: no iterator/EH frames in this region).
#include "types.h"
#include <math.h>
#include <float.h>

// ---- basic types used here -------------------------------------------------
struct V3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct Matrix33 { float m[9]; void Assign(const Matrix33* src); };
struct ResourceKey { uint32_t instanceID; uint32_t typeID; uint32_t groupID; };

// Transform block handed to cEffect::ApplyOrientation (flags/counter/pos/w + 3x3).
struct EffectTransform {
    uint16_t flags;      // +0x00
    uint16_t counter;    // +0x02
    float    x, y, z;    // +0x04
    float    w;          // +0x10
    Matrix33 m;          // +0x14
};

// ---- helper prototypes (real mangled names come from the call sites) -------
uint32_t __cdecl FNVHash(const char* s, uint32_t seed, int lowercase);   // 0x00932e80
static inline uint32_t id(const char* s) { return FNVHash(s, 0x811c9dc5, 1); }
uint32_t __cdecl SPIDFromName(const char* name);                        // 0x00571cf0

float GetPropertyF(uint32_t group, int, uint32_t prop, float def);       // 0x00bcea30

// EA allocator new: new("App", 0, 0, 0, 0) T(...)
void* operator new(unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                   const char* pFile, int line);                         // 0x00f473a0

// ---- messaging -------------------------------------------------------------
struct IMessageServer {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void PostMSG(uint32_t msgID, void* msg, int flags);          // +0x14
};
IMessageServer* MessageServer();                                        // 0x0067dcc0

extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
#pragma intrinsic(_InterlockedExchange)

struct cEffectsManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual bool GetEffect(uint32_t id, int group, void** out);          // +0x2c
};
cEffectsManager* EffectsManager();                                       // 0x0067ddd0

// One-shot effect instance: generic "apply transform" style interface.
class cEffect { public:
    virtual void v00();
    virtual void v01();
    virtual int  Release();                              // +0x08
    virtual void v03(); virtual void v04(); virtual void v05();
    virtual void ApplyOrientation(void* orient);         // +0x18
};

class cSpatialObject;

// ---------------------------------------------------------------------------
// cCommunityEditor -- retail layout taken from the disassembly (offsets below).
// ---------------------------------------------------------------------------
class cCommunity;
class cEditorEconomy;
class cSPEditorBudget;

class cCommunity {
public:
    virtual void AddRef();
    virtual void Release();
    virtual void v02();
    virtual void* Cast(uint32_t typeID);   // +0x0c
};

class cEditorEconomy {
public:
    virtual void Dtor(int flags);
    uint32_t mnRefCount;                   // +0x4
};
class cSPEditorBudget {
public:
    virtual void Dtor();
    uint32_t mnRefCount;                   // +0x4
    void Shutdown();                       // 0x004581d0
};

template <class T> class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};

class cSpatialObject { public:
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual void* Cast(uint32_t typeID);   // +0x0c
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26();
    virtual cSpatialObject* GetMode();     // +0x6c
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void* CastB(uint32_t typeID);  // +0xb8
};

class cCommunityEditor { public:
    virtual void v00();
    uint32_t pad04[4];
    uint32_t pad14[11];
    AutoRefCount<cCommunity> mpCommunity;          // +0x40
    uint32_t pad44[9];
    AutoRefCount<cEditorEconomy>  mEconomy;        // +0x68
    AutoRefCount<cSPEditorBudget> mBudget;         // +0x6c
    uint32_t pad70[19];
    uint32_t mpRotationNoun;                       // +0xbc
    cSpatialObject* mpRotationAnchor;              // +0xc0
    cSpatialObject* mpSelectedObject;              // +0xc4
    uint32_t padc8[12];
    int mSnapIndices[4];                           // +0xf8
    uint32_t pad108[15];
    void** mpNounBegin;                            // +0x144
    void** mpNounEnd;                              // +0x148
    uint32_t mNounCap;                             // +0x14c
    uint32_t pad150[75];
    uint32_t mEffectID;                            // +0x27c

    const V3* GetCommunityCenter();                // 0x00d09960
    void SetManipulatedObject(cSpatialObject* o);  // 0x00d09f60
    void FUN_00d0b010(bool b);                     // 0x00d0b010
    float GetMaxCameraAnchorDistanceFromCommunityCenter();
    float GetDefaultCameraDistance();
    void  SetDefaultCamera(bool b);
    bool  IsPositionInsideCommunityBounds(V3 pos);
    void  BoundPositionInsideCommunity(V3* out, float x, float y, float z);
    int   GetIndexOfClosestSnapPoint(void* a, void* snapPoints, void* c, void* d, bool b, void** out);
    void* CreateOneShotEffect(int id, float x, float y, float z);
    void  FUN_00d0bbd0(void** effect, float x, float y, float z);
    void  SetSelectedObject(cSpatialObject* o);
    void  ClearResources();
};

// Intrusive ordered tree keyed by a two-int key. Header: sentinel at +4, root at +0xc.
struct cIntPairTree {
    uint32_t pad[4];          // +0x00
    uint32_t* lower_bound(int* key, void** out);  // 0x00d0bd60
};

// Ridgeline / camera-controller helpers.
struct cCameraCtl {
    uint32_t pad00[4];
    void FUN_00b10340(float a, float b, float c);  // 0x00b10340
    void FUN_00b10540(float a, float b, float c);  // 0x00b10540
    void GetAnglesA(float* a, float* b, float* c); // 0x00b0f210
    void GetAnglesB(float* a, float* b, float* c); // 0x00b0f240
    void GetTargetOrientation(Quat* out);          // 0x00b137d0
    float* GetTargetPosition();                    // 0x00b10200
    void FUN_00b13bb0(const V3* target, bool snap); // 0x00b13bb0
};
cCameraCtl* GetCameraCtl();                        // 0x00b3d280

class cPlanetModel {
public:
    float DistanceBetweenPoints(const V3* a, const V3* b);   // 0x00b81470
    const Matrix33* BuildSurfaceOrientation(const V3* pos, const V3* dir); // 0x00b7f190
};
cPlanetModel* PlanetModel();                        // 0x00b3d350

const Matrix33* Matrix3FromQuaternion(Matrix33* out, const Quat* q);       // 0x0059c190
void Matrix3_Assign(Matrix33* out, const Matrix33* in);                    // 0x0041cb40
void QuaternionSlerp(Quat* out, const Quat* a, const Quat* b, float t);    // 0x00698b30

class cGameNounManager { public: void RemoveNoun(void* noun); };           // 0x00b225d0
cGameNounManager* NounManager();                                           // 0x00b3d300

// snap-point element helpers
void* FUN_00fcc210(void* elem);            // 0x00fcc210
bool  FUN_00c3f540(void* obj);             // 0x00c3f540
int   GetFileCount(void* obj);             // 0x008e7f80 (cCombatant::GetDamageState shape)
bool  FUN_00d096e0(void* obj);             // 0x00d096e0
int   FUN_00bd7f40(void* obj);             // 0x00bd7f40
bool  FUN_00bda000(void* obj, int idx);    // 0x00bda000

enum { kTypeCity = 0xee9b2232, kTypeTribe = 0x4f396a66,
       kCastCombatant = 0xe9cb8ba, kCastSnap = 0x436f315, kCastSnapOut = 0x1186577 };

// ---------------------------------------------------------------------------
// @ 0x00d0b090
float cCommunityEditor::GetMaxCameraAnchorDistanceFromCommunityCenter()
{
    float smallDist = GetPropertyF(id("CommunityEditor"), 0,
                                   id("CameraMaxDistanceFromCenterSmallCity"), 155.0f);
    if (mpCommunity.mpObject) {
        cSpatialObject* city = mpCommunity.mpObject
            ? (cSpatialObject*)mpCommunity.mpObject->Cast(kTypeCity) : 0;
        cSpatialObject* tribe = mpCommunity.mpObject
            ? (cSpatialObject*)mpCommunity.mpObject->Cast(kTypeTribe) : 0;
        if (city) {
            if (city->GetMode()) {
                if (city->GetMode()->GetMode()) {
                    if ((int)city->GetMode()->GetMode() != 2) {
                        return GetPropertyF(SPIDFromName("CommunityEditor"), 0,
                                            SPIDFromName("CameraMaxDistanceFromCenterLargeCity"),
                                            45.0f);
                    }
                }
                return GetPropertyF(id("CommunityEditor"), 0,
                                    id("CameraMaxDistanceFromCenterSmallCity"), 30.0f);
            }
        }
        else if (tribe) {
            return GetPropertyF(id("CommunityEditor"), 0,
                                id("CameraMaxDistanceFromCenterTribe"), 15.0f);
        }
    }
    return smallDist;
}

// @ 0x00d0b220
float cCommunityEditor::GetDefaultCameraDistance()
{
    float smallDist = GetPropertyF(id("CommunityEditor"), 0,
                                   id("CameraDefaultZoomSmallCity"), 155.0f);
    if (mpCommunity.mpObject) {
        cSpatialObject* city = mpCommunity.mpObject
            ? (cSpatialObject*)mpCommunity.mpObject->Cast(kTypeCity) : 0;
        cSpatialObject* tribe = mpCommunity.mpObject
            ? (cSpatialObject*)mpCommunity.mpObject->Cast(kTypeTribe) : 0;
        if (city) {
            if (city->GetMode()) {
                if (city->GetMode()->GetMode()) {
                    if ((int)city->GetMode()->GetMode() != 2) {
                        return GetPropertyF(SPIDFromName("CommunityEditor"), 0,
                                            SPIDFromName("CameraDefaultZoomLargeCity"),
                                            190.0f);
                    }
                }
                return GetPropertyF(id("CommunityEditor"), 0,
                                    id("CameraDefaultZoomSmallCity"), 155.0f);
            }
        }
        else if (tribe) {
            return GetPropertyF(id("CommunityEditor"), 0,
                                id("CameraDefaultZoomTribe"), 100.0f);
        }
    }
    return smallDist;
}

// @ 0x00d0b3b0
void cCommunityEditor::SetDefaultCamera(bool b)
{
    const V3* center = GetCommunityCenter();
    V3 pos = *center;
    if (GetCameraCtl()) {
        GetCameraCtl()->FUN_00b13bb0(&pos, b);
    }
    cCameraCtl* cam = GetCameraCtl();
    if (cam) {
        V3 angles;
        Quat q1, q2;
        cam->GetAnglesB(&angles.x, &q1.x, &q2.x);
        float phi = GetPropertyF(id("CommunityEditor"), 0, id("CameraDefaultPhi"), 0.8f);
        float dist = GetDefaultCameraDistance();
        cam->FUN_00b10340(angles.x, phi, dist);
        if (b) {
            cam->GetAnglesA(&angles.x, &q1.x, &q2.x);
            cam->FUN_00b10540(angles.x, angles.y, angles.z);
        }
    }
}

// @ 0x00d0b4d0
bool cCommunityEditor::IsPositionInsideCommunityBounds(V3 pos)
{
    V3 center = *GetCommunityCenter();
    float dist = PlanetModel()->DistanceBetweenPoints(&pos, &center);
    return dist <= GetMaxCameraAnchorDistanceFromCommunityCenter();
}

// @ 0x00d0b540
void cCommunityEditor::BoundPositionInsideCommunity(V3* out, float x, float y, float z)
{
    V3 in;
    in.x = x; in.y = y; in.z = z;
    if (IsPositionInsideCommunityBounds(in)) {
        out->x = x; out->y = y; out->z = z;
        return;
    }
    const V3* c1 = GetCommunityCenter();
    float radius = sqrtf(c1->x * c1->x + c1->y * c1->y + c1->z * c1->z);
    const V3* c2 = GetCommunityCenter();
    float dx = x - c2->x;
    float dy = y - c2->y;
    float dz = z - c2->z;
    float maxDist = GetMaxCameraAnchorDistanceFromCommunityCenter();
    float inv = 1.0f / sqrtf(dz * dz + dy * dy + dx * dx);
    const V3* c3 = GetCommunityCenter();
    V3 p;
    p.z = c3->z + (dz * inv) * maxDist;
    p.y = c3->y + (dy * inv) * maxDist;
    p.x = c3->x + (inv * dx) * maxDist;
    float inv2 = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z);
    out->x = (inv2 * p.x) * radius;
    out->y = (p.y * inv2) * radius;
    out->z = (p.z * inv2) * radius;
}

// @ 0x00d0b710
int cCommunityEditor::GetIndexOfClosestSnapPoint(void* a, void* snapPoints, void* c, void* d,
                                                 bool b, void** out)
{
    bool excludeAnchor = false;
    if (mpRotationAnchor) {
        cSpatialObject* obj = (cSpatialObject*)mpRotationAnchor->CastB(kCastCombatant);
        if (obj && FUN_00c3f540(obj)) excludeAnchor = true;
    }
    if (mpRotationAnchor) {
        cSpatialObject* snap = (cSpatialObject*)mpRotationAnchor->CastB(kCastSnap);
        if (snap) {
            void** it = mpNounBegin;
            while (it != mpNounEnd && *it != (void*)snap) ++it;
            if (it != mpNounEnd && GetFileCount((uint8_t*)snap + 0x588) != 2)
                excludeAnchor = true;
        }
    }
    int best = -1;
    int bestIdx = -1;
    if (mpCommunity.mpObject) {
        cSpatialObject* city = (cSpatialObject*)mpCommunity.mpObject->Cast(kTypeCity);
        float maxDist = FLT_MAX;
        if (!b && GetCameraCtl()) {
            float zoom = GetPropertyF(id("CommunityEditor"), 0, id("SnapDistanceZoomFactor"), 0.1f);
            cCameraCtl* cam = GetCameraCtl();
            Quat orient;
            cam->GetTargetOrientation(&orient);
            float dist = PlanetModel()->DistanceBetweenPoints((const V3*)cam->GetTargetPosition(),
                                                              (const V3*)&orient);
            maxDist = zoom * dist;
        }
        if (snapPoints) {
            int count = ((int*)((uint8_t*)snapPoints + 0x54))[0] - ((int*)((uint8_t*)snapPoints + 0x50))[0];
            float bestDist = FLT_MAX;
            for (int i = 0; i < count; i += 0x18) {
                uint8_t* elem = *(uint8_t**)((uint8_t*)snapPoints + 0x50) + i;
                // scoring loop (see card disassembly)
                (void)elem; (void)bestDist;
            }
            best = bestIdx;
        }
    }
    if (out) {
        *out = 0;
        if (bestIdx != -1) {
            uint8_t* elem = *(uint8_t**)((uint8_t*)snapPoints + 0x50) + bestIdx * 0x18;
            cSpatialObject* o = (cSpatialObject*)FUN_00fcc210(elem);
            if (o) { *out = o->Cast(kCastSnapOut); return bestIdx; }
            *out = 0;
        }
    }
    return bestIdx;
}

// @ 0x00d0ba80
void* cCommunityEditor::CreateOneShotEffect(int id, float x, float y, float z)
{
    cEffect* effect = 0;
    EffectsManager()->GetEffect(0, id, (void**)&effect);
    if (effect) {
        V3 pos;
        pos.x = x; pos.y = y; pos.z = z;
        EffectTransform t;
        t.m.Assign((const Matrix33*)0x0169d5f0);
        const Matrix33* orient = PlanetModel()->BuildSurfaceOrientation(&pos, &pos);
        Matrix3FromQuaternion(&t.m, (const Quat*)orient);
        effect->ApplyOrientation(&t);
        effect->Release();
    }
    return effect;
}

// @ 0x00d0bbd0
void cCommunityEditor::FUN_00d0bbd0(void** effectOut, float x, float y, float z)
{
    EffectsManager()->GetEffect(mEffectID, 0, effectOut);
    if (*effectOut) {
        V3 pos;
        pos.x = x; pos.y = y; pos.z = z;
        EffectTransform t;
        t.m.Assign((const Matrix33*)0x0169d5f0);
        const Matrix33* orient = PlanetModel()->BuildSurfaceOrientation(&pos, &pos);
        Matrix3FromQuaternion(&t.m, (const Quat*)orient);
        ((cEffect*)*effectOut)->ApplyOrientation(&t);
        ((cEffect*)*effectOut)->Release();
    }
}

// @ 0x00d0bcf0
void cCommunityEditor::SetSelectedObject(cSpatialObject* o)
{
    mpSelectedObject = o;
    if (o) {
        cSpatialObject* anchor = (cSpatialObject*)o->Cast(0xe89adf71);
        if (anchor) {
            if (((bool(__thiscall*)(void*))((*(void***)anchor)[5]))(anchor)) {
                FUN_00d0b010(true);
                return;
            }
        }
    }
    if (mpRotationNoun) {
        NounManager()->RemoveNoun((void*)mpRotationNoun);
        mpRotationNoun = 0;
    }
}

// @ 0x00d0bd60
uint32_t* cIntPairTree::lower_bound(int* key, void** out)
{
    uint32_t* node = *(uint32_t**)((uint8_t*)this + 0xc);
    uint32_t* head = (uint32_t*)((uint8_t*)this + 4);
    uint32_t* prev = head;
    if (node) {
        int k0 = key[0];
        do {
            if ((int)node[4] < k0 || ((int)node[4] <= k0 && (int)node[5] < key[1])) {
                node = (uint32_t*)node[0];
            } else {
                prev = node;
                node = (uint32_t*)node[1];
            }
        } while (node);
    }
    if (prev != head) {
        int k0 = key[0];
        if ((int)prev[4] <= k0 && ((int)prev[4] < k0 || (int)prev[5] <= key[1])) {
            *out = prev;
            return prev;
        }
    }
    *out = head;
    return head;
}

// @ 0x00d0bf80
void cCommunityEditor::ClearResources()
{
    SetManipulatedObject(0);
    mpSelectedObject = 0;
    if (mpRotationNoun) {
        NounManager()->RemoveNoun((void*)mpRotationNoun);
        mpRotationNoun = 0;
    }
    if (mBudget.mpObject) {
        mBudget.mpObject->Shutdown();
        cSPEditorBudget* b = mBudget.mpObject;
        if (b) {
            mBudget.mpObject = 0;
            b->Dtor();
        }
    }
    if (mEconomy.mpObject) {
        cEditorEconomy* e = mEconomy.mpObject;
        mEconomy.mpObject = 0;
        if (--e->mnRefCount == 0) {
            e->mnRefCount = 1;
            e->Dtor(1);
        }
    }
    cCommunity* c = mpCommunity.mpObject;
    if (c) {
        mpCommunity.mpObject = 0;
        c->Release();
    }
}

// ---------------------------------------------------------------------------
// Behavior-message thunks: new ("App",0,0,0,0) T; set fields; post; release.
// The header (with mMessageID) is a non-polymorphic base constructed before the
// polymorphic base's vtable store -- hence the ID store precedes the vptr store.
// ---------------------------------------------------------------------------
class cBehaviorMessage { public:      // +0x00 (vptr)
    virtual void _v00();
    virtual int  AddRef();
    virtual int  Release();
    volatile long mnRefCount;         // +0x04
    cBehaviorMessage() { _InterlockedExchange(&mnRefCount, 0); }
};
struct cMessageHeader {
    int      mField8;                 // +0x08
    uint32_t field_C[9];              // +0x0c
    uint32_t mMessageID;              // +0x30
    uint32_t field_34;                // +0x34
    cMessageHeader() : mMessageID(0) {}
};

class cEditorBehaviorMessage1 : public cMessageHeader, public cBehaviorMessage { public:
    uint32_t mField38;                // +0x38
    uint32_t pad3c;
    cEditorBehaviorMessage1() : mField38(0) {}
    virtual void _v00();
};
class cEditorBehaviorMessage2 : public cMessageHeader, public cBehaviorMessage { public:
    uint32_t mField38;
    uint32_t pad3c;
    cEditorBehaviorMessage2() : mField38(0) {}
    virtual void _v00();
};
class cEditorBehaviorMessage3 : public cMessageHeader, public cBehaviorMessage { public:
    uint32_t mField38;
    uint32_t pad3c;
    cEditorBehaviorMessage3() : mField38(0) {}
    virtual void _v00();
};

// @ 0x00d0bdd0
void __cdecl PostEditorBehaviorMessage1(uint32_t a, uint32_t msgID)
{
    if (msgID == (uint32_t)-0xf || msgID == 0x1511161) {
        cEditorBehaviorMessage1* msg = new ("App", 0, 0, 0, 0) cEditorBehaviorMessage1();
        AutoRefCount<cEditorBehaviorMessage1> ref(msg);
        msg->mMessageID = 0x63bdfbe;
        msg->mField8 = msgID;
        MessageServer()->PostMSG(msg->mMessageID, msg, 0);
    }
}

// @ 0x00d0be60
void __cdecl PostEditorBehaviorMessage2(uint32_t a, uint32_t msgID)
{
    if (msgID == (uint32_t)-0xf || msgID == 0x1511161) {
        cEditorBehaviorMessage2* msg = new ("App", 0, 0, 0, 0) cEditorBehaviorMessage2();
        AutoRefCount<cEditorBehaviorMessage2> ref(msg);
        msg->mMessageID = 0x63c0504;
        msg->mField8 = msgID;
        MessageServer()->PostMSG(msg->mMessageID, msg, 0);
    }
}

// @ 0x00d0bef0
void __cdecl PostEditorBehaviorMessage3(uint32_t a, uint32_t msgID)
{
    if (msgID == (uint32_t)-0xf || msgID == 0x1511161) {
        cEditorBehaviorMessage3* msg = new ("App", 0, 0, 0, 0) cEditorBehaviorMessage3();
        AutoRefCount<cEditorBehaviorMessage3> ref(msg);
        msg->mMessageID = 0x63c0580;
        msg->mField8 = msgID;
        MessageServer()->PostMSG(msg->mMessageID, msg, 0);
    }
}
