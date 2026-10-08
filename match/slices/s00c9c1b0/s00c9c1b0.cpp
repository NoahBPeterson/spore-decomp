// Slice s00c9c1b0 - SP::cTribeHut::TakeHit (VA 0x00c9c8a0, 1565 bytes): the cCombatant::TakeHit override of the
// tribe hut. `this` is the cCombatant subobject (hut + 0x120); the cGameData is at this-0x120, the
// cSpatialObject at this-0xec, and this+0x110 is the hut's tribe pointer (ModAPI cTribeHut::mpTribe +0x230).
// Retail offsets follow the ModAPI cTribeHut/cCombatant/cSpatialObject headers, not the 2008 PDB.
//   mode 0x1654c02 (tribe game): record relationship events, report the hit to the attacker's helpers and
//     flag the hut as damaged below the health fraction 0.9;
//   modes 0x1654c05/0x1654c04 (a hit that destroyed the hut): spawn the destruction effect, post a
//     "hut destroyed" message and remove the tribe noun.
// Virtual calls use VT(obj, byteOffset) with typed thiscall pointers; slot numbers come from the asm.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc).
#include "types.h"
#include <math.h>

#define VT(obj, off) ((*(void***)(obj))[(off) / 4])

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct Matrix3 { float m[9]; };

typedef void*    (__thiscall *FnP)(void*);
typedef float    (__thiscall *FnF)(void*);
typedef bool     (__thiscall *FnB)(void*);
typedef uint32_t (__thiscall *FnU)(void*);
typedef void*    (__thiscall *FnCast)(void*, uint32_t);
typedef bool     (__thiscall *FnMonster)(void*, void*, float, float);

// Transform message (ctor 0x434040): u16 flags (|4 position, |2 rotation), u16 count, offset, scale, matrix.
struct XformMsg {
    uint16_t flags;
    uint16_t count;
    Vector3  pos;
    float    scale;
    Matrix3  rot;
    XformMsg();                                       // 0x434040
};

Matrix3 Matrix3FromQuaternion(const Quaternion* q);   // 0x59c190 (sret, cdecl)

// MessageBasicRC<5> built inline (vtable pair 0x13eb90c base / 0x13eb844 derived), 0x3c bytes.
extern void* vtbl_MsgBase[];       // 0x013eb90c
extern void* vtbl_Msg[];           // 0x013eb844
struct Msg5 {
    void*    vptr;                 // +0x00
    long     refcount;             // +0x04
    uint32_t slot0;                // +0x08
    uint32_t slot1;                // +0x0c
    uint32_t slot2;                // +0x10
    uint32_t pad[0x30 / 4 - 5];    // up to +0x2c
    uint32_t id;                   // +0x30
    uint32_t pad34;
    uint32_t pad38;
    void SetIRefCount(int idx, void* p);              // 0x5726e0 (ret 8)
    void Destruct();                                  // 0x421cf0
};
struct MessageServerT {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void Post(uint32_t type, Msg5* msg, int flag);   // +0x14
};

struct IVisualEffect {
    virtual int AddRef();
    virtual int Release();
    virtual void Start(int hardStart);                // 0x08
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void SetSourceTransform(const XformMsg* t);   // 0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44();
    virtual bool SetIntParams(int param, const int* data, int count);   // 0x48
};
struct IEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, IVisualEffect** dst);   // 0x2c
};

struct RelationshipMgr {
    float RecordEvent(int pid1, int pid2, uint32_t event, float scale);   // 0xd06240 (ret 0x10)
};
struct NounManagerT { void RemoveNoun(void* noun); };    // 0xb225d0 (ret 4)
struct TribeHelper { bool FUN_00ae3d40(void* tribe); };   // 0xae3d40 (ret 4), on FUN_00b26930()'s result
struct Planet {
    void FUN_00c71370(void* x);          // ret 4
    int  FUN_00c70e00();
    int  FUN_00c71120();
    void FUN_00c70de0(int);              // ret 4
};
struct Tribe { void* FUN_00c8ea40(); };  // 0xc8ea40: returns [this+0x2d8]
struct Citizen { void* GetTribe(); };    // 0xc22f50 (cSPCreatureCitizen, returns [this+0x1014])
struct HitHelper { uint32_t FUN_00bc8400(uint32_t id, const Vector3* pos, float a, float b, void* gd, void* hut); };   // ret 0x18
struct HitFx { void FUN_00bc97f0(int a, uint32_t b, float c, void* d); };                                      // ret 0x10
struct Member {                          // an element of the tribe's member list
    bool FUN_00c0d560(void* y, float a, float b);     // ret 0xc
    bool FUN_00c11480(const Vector3* pos, float a, float b);   // ret 0xc
};

RelationshipMgr* GetRelationshipMgr(void);   // 0xb3d2c0
NounManagerT*    GetNounManager(void);       // 0xb3d300
IEffectsManager* GetEffectsManager(void);    // 0x67ddd0
MessageServerT*  GetMessageServer(void);     // 0x67dcc0
HitHelper*       FUN_00bc8000(void);         // 0xbc8000
TribeHelper*     FUN_00b26930(void);         // 0xb26930
Planet*          GetActivePlanet(void);      // 0x1021260
uint32_t         GetCurrentGameMode(void);   // 0xb5b800
void*            FUN_00ac80d0(void* gd, uint32_t typeId);   // 0xac80d0 (cdecl): gd if gd->vtbl[0x20]() == typeId, else 0
void __stdcall   FUN_00c8e720(int id);       // 0xc8e720 (ret 4)

struct HutCombatant
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void TakeHit(float damage, int attackerID, int damageType, const Vector3* dir, void* attacker);   // 0x18
    uint32_t pad04[(0x34 - 4) / 4];
    int      mDeathState;        // +0x34
    float    mHealthPoints;      // +0x38
    uint32_t pad3c[(0x110 - 0x3c) / 4];
    void*    mpTribe;            // +0x110

    void  TakeHitBase(float damage, int attackerID, int damageType, const Vector3* dir, void* attacker);   // 0xbfcdd0
    float FUN_00bfc490();        // 0xbfc490: health fraction
};

// @ 0x00c9c8a0
void HutCombatant::TakeHit(float damage, int attackerID, int damageType, const Vector3* dir, void* attacker)
{
    bool wasAlive = mHealthPoints > 1.5258789e-05f;
    uint32_t mode = GetCurrentGameMode();
    if (mode == 0x1654c05)
        damage *= 20.0f;
    TakeHitBase(damage, attackerID, damageType, dir, attacker);

    if (mode == 0x1654c02) {
        void* tribe = mpTribe;
        if (!tribe) return;
        if (mHealthPoints > 0.0f) {
            if (attackerID != -1) {
                FUN_00c8e720(attackerID);
                int pid = ((FnU)VT(tribe, 0x4c))(tribe);
                GetRelationshipMgr()->RecordEvent(pid, attackerID, 0x530cf04, 1.0f);
            }
            if (attacker) {
                void* A = ((FnP)VT(attacker, 8))(attacker);
                void* B = ((FnP)VT(attacker, 0xc))(attacker);
                char* hut = (char*)this - 0x120;
                void* HS = (char*)this - 0xec;
                float rA = ((FnF)VT(A, 0x74))(A);
                float rH = ((FnF)VT(HS, 0x74))(HS);
                float sum = rH + rA;
                const Vector3* pos = (const Vector3*)((FnP)VT(HS, 0x2c))(HS);
                FUN_00bc8000()->FUN_00bc8400(0xb9d14c31, pos, sum, 5.0f, B, hut);

                uint32_t** members = (uint32_t**)((FnP)VT(tribe, 0x90))(tribe);
                void* x = ((FnCast)VT(attacker, 0x5c))(attacker, 0xee3f516e);
                void* y = ((FnCast)VT(attacker, 0x5c))(attacker, 0xce9f6639);
                void* A2 = ((FnP)VT(attacker, 8))(attacker);
                uint32_t** it = (uint32_t**)members[0];
                uint32_t** end = (uint32_t**)members[1];
                for (; it != end; ++it) {
                    char* obj = (char*)*it;
                    void* sp = obj + 0xc0;
                    bool hit;
                    if (!((FnB)VT(sp, 0x58))(sp)) {
                        hit = true;
                    } else if (y) {
                        hit = ((FnMonster)VT(obj, 0xc0))(obj, y, 1.0f, 0.0f);
                        if (!hit)
                            hit = ((Member*)obj)->FUN_00c0d560(y, 1.0f, 0.0f);
                    } else {
                        const float* pa = (const float*)((FnP)VT(A2, 0x2c))(A2);
                        const float* pb = (const float*)((FnP)VT(sp, 0x2c))(sp);
                        float dx = pb[0] - pa[0];
                        float dy = pb[1] - pa[1];
                        float dz = pb[2] - pa[2];
                        float dist = sqrtf(dx * dx + dy * dy + dz * dz);
                        float t = dist - ((FnF)VT(sp, 0x74))(sp);
                        float v = ((FnF)VT(A2, 0x74))(A2) + t;
                        if (v < 0.0f) v = 0.0f;
                        const Vector3* ap = (const Vector3*)((FnP)VT(A2, 0x2c))(A2);
                        hit = ((Member*)obj)->FUN_00c11480(ap, v, 1.0f);
                    }
                    if (hit) {
                        HitFx* fx = (HitFx*)(*(char**)(obj + 0xb4c) + 8);
                        fx->FUN_00bc97f0(0, 0x20000, 5.0f, x);
                    }
                }
            }
            if (FUN_00bfc490() < 0.9f)
                mDeathState = 1;
        } else if (wasAlive) {
            if (attackerID != -1) {
                int pid = ((FnU)VT(tribe, 0x4c))(tribe);
                GetRelationshipMgr()->RecordEvent(pid, attackerID, 0x530cf05, 1.0f);
            }
            void* gd = attacker ? ((FnP)VT(attacker, 0xc))(attacker) : 0;
            void* citizen = FUN_00ac80d0(gd, 0x18eb4b7);
            void* attackerTribe = 0;
            if (citizen)
                attackerTribe = ((Citizen*)citizen)->GetTribe();
            Msg5 msg;
            msg.id = 0x58baddd;
            msg.vptr = vtbl_MsgBase;
            msg.refcount = 0;
            msg.vptr = vtbl_Msg;
            msg.pad38 = 0;
            msg.SetIRefCount(0, mpTribe);
            msg.SetIRefCount(1, (char*)this - 0x120);
            msg.SetIRefCount(2, attackerTribe);
            GetMessageServer()->Post(msg.id, &msg, 0);
            msg.Destruct();
        }
    } else if (mode == 0x1654c05 || mode == 0x1654c04) {
        if (mHealthPoints > 0.0f) return;
        void* tribe = mpTribe;
        if (!tribe) return;
        if (mode == 0x1654c04) {
            if (!FUN_00b26930()->FUN_00ae3d40(tribe)) return;
        }
        IVisualEffect* vfx = 0;
        IEffectsManager* em = GetEffectsManager();
        if (vfx) {
            IVisualEffect* old = vfx;
            vfx = 0;
            old->Release();
        }
        if (em->CreateVisualEffect(0x87d89ca9, 0, &vfx)) {
            void* HS = (char*)this - 0xec;
            const uint32_t* key = (const uint32_t*)((FnP)VT(HS, 0x98))(HS);
            int ids[2];
            ids[0] = key[0];
            ids[1] = key[2];
            vfx->SetIntParams(6, ids, 2);
            XformMsg m;
            const Vector3* p = (const Vector3*)((FnP)VT(HS, 0x2c))(HS);
            m.pos = *p;
            m.flags |= 4;
            m.count++;
            const Quaternion* q = (const Quaternion*)((FnP)VT(HS, 0x30))(HS);
            m.rot = Matrix3FromQuaternion(q);
            m.flags |= 2;
            m.count++;
            vfx->SetSourceTransform(&m);
            vfx->Start(0);
        }
        if (mode == 0x1654c05) {
            Planet* planet = GetActivePlanet();
            if (planet) {
                void* x = ((Tribe*)mpTribe)->FUN_00c8ea40();
                if (x) {
                    planet->FUN_00c71370(x);
                    if (planet->FUN_00c70e00() == 2 && planet->FUN_00c71120() == 0)
                        planet->FUN_00c70de0(1);
                }
            }
            Msg5 msg;
            msg.id = 0x4b3370f;
            msg.vptr = vtbl_MsgBase;
            msg.refcount = 0;
            msg.vptr = vtbl_Msg;
            msg.pad38 = 0;
            msg.slot0 = (uint32_t)mpTribe;
            GetMessageServer()->Post(msg.id, &msg, 0);
            msg.Destruct();
        }
        GetNounManager()->RemoveNoun(mpTribe);
        if (vfx) vfx->Release();
    }
}
