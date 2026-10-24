// Slice s00bfcc80: SP::cCombatant (ctor/dtor/TakeHit/PartialRepair, hostile-entry copy
// helpers) and two Simulator::cGameData definition-id helpers.
// Targets: 00BFCC80 FUN_00bfcc80   00BFCD00 SP::cCombatant::~cCombatant
//          00BFCDD0 SP::cCombatant::TakeHit   00BFD1A0 SP::cCombatant::PartialRepair
//          00BFD2B0 FUN_00bfd2b0   00BFD3E0 FUN_00bfd3e0   00BFD430 FUN_00bfd430
//          00BFD490 FUN_00bfd490   00BFD4E0 SP::cCombatant::cCombatant
//          00BFD610 FUN_00bfd610   00BFD800 Simulator::cGameData::SetDefinitionID
//          00BFD840 Simulator::cGameData::SetGameDataOwner
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "s00bfcc80.h"
#include <stddef.h>

// ---------------------------------------------------------------------------
// 0x00bfcc80  FUN_00bfcc80: find the first unused slot (of three at +0xbc) and have
// the effects manager instantiate into it. Returns the new handle (or 0).
// ---------------------------------------------------------------------------
typedef char (*VCfn)(void*);
typedef float (*VFfn)(void*);

// @ 0x00bfcc80
void* __fastcall FUN_00bfcc80(Combatant* self, int, unsigned param_2)
{
    unsigned i = 0;
    void** slot = self->mSlotsBc;
    while (*slot != 0 && ((RcSlot*)*slot)->IsActive()) {
        ++i;
        ++slot;
        if (i > 2)
            return 0;
    }
    if (i > 2)
        return 0;
    RcEffectMgr* mgr = (RcEffectMgr*)EffectsManagerPtr();
    void** cur = self->mSlotsBc + i;
    RcSlot* old = (RcSlot*)*cur;
    if (old != 0) {
        *cur = 0;
        old->Release4();
    }
    if (mgr->AddSlot(param_2, 0, cur) == 0)
        return 0;
    return *cur;
}

// ---------------------------------------------------------------------------
// 0x00bfd3e0  FUN_00bfd3e0: copy-construct one 0x28-byte hostile-entry record.
// ---------------------------------------------------------------------------
// @ 0x00bfd3e0
HostileEntry* __fastcall FUN_00bfd3e0(HostileEntry* self, int, const HostileEntry* src)
{
    self->vftable = (void*)0x1465d54;
    self->mRefCount4 = 0;
    self->mField08 = src->mField08;
    self->mField0c = src->mField0c;
    self->mField10 = src->mField10;
    self->mField14 = src->mField14;
    self->mByte18 = src->mByte18;
    self->mField1c = src->mField1c;
    self->vftable = (void*)0x1464450;
    self->mField20 = src->mField20;
    return self;
}

// ---------------------------------------------------------------------------
// 0x00bfd430  FUN_00bfd430: forward-copy a range of hostile-entry records.
// ---------------------------------------------------------------------------
// @ 0x00bfd430
void FUN_00bfd430(const HostileEntry* first, const HostileEntry* last, HostileEntry* out)
{
    if (out != 0 || first != last) {
        for (; first != last; first += 1, out += 1) {
            if (out != 0) {
                out->vftable = (void*)0x1465d54;
                out->mRefCount4 = 0;
                out->mField08 = first->mField08;
                out->mField0c = first->mField0c;
                out->mField10 = first->mField10;
                out->mField14 = first->mField14;
                out->mByte18 = first->mByte18;
                out->mField1c = first->mField1c;
                out->vftable = (void*)0x1464450;
                out->mField20 = first->mField20;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00bfd490  FUN_00bfd490: backward-copy a range of hostile-entry records.
// ---------------------------------------------------------------------------
// @ 0x00bfd490
void FUN_00bfd490(HostileEntry* first, HostileEntry* last, HostileEntry* out)
{
    while (last != first) {
        last -= 1;
        out -= 1;
        out->mField08 = last->mField08;
        out->mField0c = last->mField0c;
        out->mField10 = last->mField10;
        out->mField14 = last->mField14;
        out->mByte18 = last->mByte18;
        out->mField1c = last->mField1c;
        out->mField20 = last->mField20;
    }
}

// ---------------------------------------------------------------------------
// 0x00bfd4e0  SP::cCombatant::cCombatant
// ---------------------------------------------------------------------------
// @ 0x00bfd4e0
Combatant* __fastcall Combatant_ctor(Combatant* self)
{
    self->vftable = (void**)0x14698f0;
    self->mIgnoreCombatLineTest = 0;
    self->mLineTestIgnoresFriendlies = 0;
    CombatantListHead* head = (CombatantListHead*)((char*)self + 0x10);
    head->mPrev = 0;
    head->mLive = 0;
    head->mField0c = 0;
    head->mNext = head;
    self->mList14 = head;
    self->mList18 = 0;
    self->mByte1c = 0;
    self->mField20 = 0;
    self->mNextTarget28 = 0;
    self->mField2c = 10.0f;
    self->mField30 = 0;
    self->mHealth38 = 10.0f;
    self->mField34 = 0;
    self->mDamageState3c = 0xffffffff;
    self->mField40 = 0.5f;
    self->mField44 = 0;
    self->mField48 = 0;
    self->mField4c = *(float*)0x168cb6c;
    self->mField50 = *(float*)0x168cb70;
    self->mField54 = *(float*)0x168cb74;
    self->mHostileBegin58 = 0;
    self->mHostileEnd5c = 0;
    self->mHostileCap60 = 0;
    self->mStunFlag6c = 1;
    self->mStunTimer70 = 0;
    self->mField74 = *(float*)0x168cb6c;
    self->mField78 = *(float*)0x168cb70;
    self->mField7c = *(float*)0x168cb74;
    self->mByte80 = 0;
    self->mByte81 = 0;
    self->mVec84Begin = 0;
    self->mVec84End = 0;
    self->mVec84Cap = 0;
    ((RcTimer*)((char*)self + 0x98))->Ctor();
    self->mSlotsBc[0] = 0;
    self->mSlotsBc[1] = 0;
    self->mSlotsBc[2] = 0;
    return self;
}

// ---------------------------------------------------------------------------
// 0x00bfcd00  SP::cCombatant::~cCombatant
// ---------------------------------------------------------------------------
// @ 0x00bfcd00
void __fastcall Combatant_dtor(Combatant* self)
{
    self->vftable = (void**)0x14698f0;
    // The three effect handles at +0xbc..+0xc8, released back-to-front.
    void** slot = self->mSlotsBc + 3;
    int n = 2;
    do {
        --slot;
        void* h = *slot;
        if (h != 0)
            ((RcSlot*)h)->Release4();
        --n;
    } while (n >= 0);
    ((RcTimer*)((char*)self + 0x98))->Dtor();
    // The mVec84 vector of 0x28-byte cGonzagoTimer elements.
    char* end = (char*)self->mVec84End;
    char* begin = (char*)self->mVec84Begin;
    while (begin < end) {
        ((RcTimer*)begin)->Dtor();
        begin += 0x28;
    }
    if (self->mVec84Begin != 0 && ((RcVecStore*)self->mVec84Begin)[-1].mElemCount != 0)
        operator_delete__(self->mVec84Begin);
    if (self->mHostileBegin58 != 0 && ((RcVecStore*)self->mHostileBegin58)[-1].mElemCount != 0)
        operator_delete__(self->mHostileBegin58);
    void* p;
    if ((p = self->mField48) != 0)
        ((RcSlot*)p)->Release64();
    if ((p = self->mField44) != 0)
        ((RcSlot*)p)->Release64();
    if ((p = self->mField30) != 0)
        ((RcSlot*)p)->Release4();
    if ((p = self->mNextTarget28) != 0)
        ((RcSlot*)p)->Release64();
    self->mMap0c.NukeSubtree(self->mList18);
}

// Local views for the remaining helpers.
#pragma pack(push, 1)
struct RcSlotList {                                         // object at cGameData + an accessor result
    void** vftable;                                         // +0x00
    unsigned char pad04[0x8c];                              // +0x04..+0x90
    void*  mData90;                                         // +0x90
};
struct WorldTransform {                                     // filled by cSpatialObject::LocalToWorldTransform
    unsigned short flags;                                   // +0x00
    unsigned char pad02[0x12];                              // +0x02..+0x14
    Matrix3 m;                                              // +0x14
};
struct Msg5 {                                               // MessageBasicRC<5>-shaped message
    void** vftable;                                         // +0x00
    uint32_t mField04;                                      // +0x04
    void*  mData08;                                         // +0x08
    uint32_t mField0c;                                      // +0x0c
    uint32_t mField10;                                      // +0x10
};
struct SubFlagsView {                                       // opaque sub-object; its state flags word sits at +0xb58
    uint32_t padB58[0x2d6];                                 // +0x00..+0xb58
    uint32_t mFlagsB58;                                     // +0xb58
};
#pragma pack(pop)

// +0x08 vtable slot: the spatial/orient accessor shared by several helpers.
typedef void* (*GetAccessor)(void*);
typedef void* (*GetAccessor2)(void*, void*);
typedef void* (*GetAccessor3)(void*, void*, void*);
typedef void  (*GetHandle)(void*);
typedef char  (*GetChar)(void*);
typedef float (*GetFloat)(void*);
typedef void* (*GetVector)(void*);

// ---------------------------------------------------------------------------
// 0x00bfd2b0  FUN_00bfd2b0: compose a placement from the object's position and
// orientation and hand it to the effect handle at +0x30.
// ---------------------------------------------------------------------------
// @ 0x00bfd2b0
void __fastcall FUN_00bfd2b0(OrientObject* self)
{
    if (self->mEffectHandle30 == 0)
        return;
    Placement p;
    p.flags = 0;
    p.count = 0;
    p.pos.x = *(float*)0x168d174;
    p.pos.y = *(float*)0x168d178;
    p.pos.z = *(float*)0x168d17c;
    p.scale = 1.0f;
    Matrix3_Assign(&p.basis, (const void*)0x168d150);

    void* a = ((GetAccessor)(*(void***)self)[2])(self);
    p.pos = *((Vector3*)((GetVector)(*(void***)a)[0xb])(a));
    p.flags |= 4;
    ++p.count;

    a = ((GetAccessor)(*(void***)self)[2])(self);
    Vector3* dir = (Vector3*)((GetVector)(*(void***)a)[0xb])(a);
    Vector3 normal;
    PlanetModelGet(&normal, dir);
    Vector3 side;
    OrthogonalVector(&side, &normal);
    Matrix3 basis;
    Matrix3FromFacingAndUp(&basis, &side, &normal);
    for (int i = 0; i < 9; ++i)
        p.basis.m[i] = basis.m[i];
    p.flags |= 2;
    ++p.count;

    a = ((GetAccessor)(*(void***)self)[2])(self);
    p.scale = ((GetFloat)(*(void***)a)[0x1d])(a);
    ++p.count;

    ((RcHandle*)self->mEffectHandle30)->Apply(&p);
}

// ---------------------------------------------------------------------------
// 0x00bfd610  GameData::Cleanup: clear the definition-id vector, refill it from
// the owner's resolved definition list, and fall back to a bounding-box centre.
// ---------------------------------------------------------------------------
// @ 0x00bfd610
void GameData::Cleanup()
{
    mDefs.erase(mDefs.begin, mDefs.end);
    void* obj = ((GetAccessor)(*(void***)this)[2])(this);
    void* slot = ((GetAccessor)(*(void***)obj)[0x2b])(obj);
    if (slot != 0) {
        void* src = ((RcSlotList*)slot)->mData90;
        if (src != 0) {
            float count = 0;
            void* arr = 0;
            char ok = FUN_006a0990(src, 0x519e304, &count, &arr);
            if (ok) {
                for (int i = 0; i < (int)count; ++i) {
                    Vector3 val = ((Vector3*)arr)[i];
                    if (mDefs.end < mDefs.cap) {
                        *mDefs.end = val;
                        ++mDefs.end;
                    } else {
                        mDefs.DoInsertValue(mDefs.end, &val);
                    }
                }
            }
            mFlag6c = 0;
        }
    }
    if (mDefs.begin == mDefs.end) {
        void* o2 = ((GetAccessor)(*(void***)this)[2])(this);
        float t = ((GetFloat)(*(void***)o2)[0xd])(o2);
        Vector3 v;
        if (t <= 0.01f) {
            v.x = *(float*)0x168cb6c;
            v.y = *(float*)0x168cb70;
            v.z = *(float*)0x168cb74;
        } else {
            void* o3 = ((GetAccessor)(*(void***)this)[2])(this);
            float* m = ((float* (*)(void*))(*(void***)o3)[0x1a])(o3);
            float inv = 1.0f / t;
            v.x = ((m[3] + m[0]) * 0.5f) * inv;
            v.y = ((m[4] + m[1]) * 0.5f) * inv;
            v.z = ((m[5] + m[2]) * 0.5f) * inv;
        }
        if (mDefs.end < mDefs.cap) {
            *mDefs.end = v;
            ++mDefs.end;
        } else {
            mDefs.DoInsertValue(mDefs.end, &v);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00bfd800  GameData::SetDefinitionID: refill the list if empty or dirty, then
// pick a uniform random index into it.
// ---------------------------------------------------------------------------
// @ 0x00bfd800
void GameData::SetDefinitionID()
{
    if (mDefs.begin == mDefs.end || mFlag6c != 0)
        Cleanup();
    RandomLCG* rng = &gRandomLCG;
    int n = (int)((char*)mDefs.end - (char*)mDefs.begin) / 12;
    rng->RandomUint32Uniform(n);
}

// ---------------------------------------------------------------------------
// 0x00bfd840  GameData::SetGameDataOwner: read definition record `index` into the
// caller's vector, transform it into world space, and return it.
// ---------------------------------------------------------------------------
// @ 0x00bfd840
float* GameData::SetGameDataOwner(float* out, int index)
{
    if (mDefs.begin == mDefs.end || mFlag6c != 0)
        Cleanup();
    int count = (int)((char*)mDefs.end - (char*)mDefs.begin) / 12;
    if (index > count || index == -1)
        index = 0;
    Vector3 v = ((Vector3*)mDefs.begin)[index];
    out[0] = v.x;
    out[1] = v.y;
    out[2] = v.z;

    Matrix3 basis;
    Matrix3_Assign(&basis, (const void*)0x168d12c);

    WorldTransform wt;
    wt.flags = 0;
    void* sp = ((GetAccessor)(*(void***)this)[2])(this);
    cSpatialObject_LocalToWorldTransform(sp, &wt);
    sp = ((GetAccessor)(*(void***)this)[2])(this);
    float scale = ((GetFloat)(*(void***)sp)[0xd])(sp);
    if (wt.flags & 2) {
        float x = out[0], y = out[1], z = out[2];
        out[0] = x * wt.m.m[0] + y * wt.m.m[3] + z * wt.m.m[6];
        out[1] = x * wt.m.m[1] + y * wt.m.m[4] + z * wt.m.m[7];
        out[2] = x * wt.m.m[2] + y * wt.m.m[5] + z * wt.m.m[8];
    }
    out[0] = out[0] * scale + basis.m[0];
    out[1] = out[1] * scale + basis.m[1];
    out[2] = out[2] * scale + basis.m[2];
    return out;
}

// ---------------------------------------------------------------------------
// 0x00bfcdd0  Combatant::TakeHit: retarget, run the player-tool intercept when the
// source is destroyed, then apply the hit to the health/state and notify.
// ---------------------------------------------------------------------------
// @ 0x00bfcdd0
void __fastcall Combatant_TakeHit(Combatant* self, int, float amount, void* source,
                                  int type, Vector3* dir, void* flags)
{
    void* prev = self->mNextTarget28;
    if (source != prev) {
        if (source != 0)
            ((GetHandle)(*(void***)source)[0x18])(source);          // vtable +0x60
        self->mNextTarget28 = source;
        if (prev != 0)
            ((GetHandle)(*(void***)prev)[0x19])(prev);              // vtable +0x64
    }
    if (source != 0) {
        void* o = ((GetAccessor)(*(void***)source)[3])(source);     // vtable +0x0c
        char destroyed = ((GetChar)(*(void***)o)[0xb])(o);          // +0x2c
        if (destroyed == 0) {
            if (GetCurrentGameMode() == (void*)0x1654c05) {
                void* inv = GetPlayerInventory(SpaceGameGet());
                if (((char (*)(void*, void*))(*(void***)inv)[0x1d])(inv, (void*)0x168d064)) {
                    int tool = GetToolFromToolID(GetPlayerInventory(SpaceGameGet()), (void*)0x168d064);
                    int id = FUN_0104bde0((void*)(char*)tool);
                    if (id != -1 && TimerIsRunning((void*)((char*)tool + 0x88))) {
                        int elapsed = TimerGetElapsedTime((void*)((char*)tool + 0x88));
                        if (id != elapsed && id - elapsed > 0) {
                            void* sim = FUN_0108db30(GetUFOSimulator());
                            int emp = ((int (*)(void*))(*(void***)source)[4])(source);  // +0x10
                            if (emp != GetPlayerEmpireID()) {
                                void* key = ((GetAccessor)(*(void***)source)[4])(source);
                                void* hit = FUN_00d61ce0(&key, (unsigned)(uintptr_t)sim, sim, &key);
                                if (*(void**)hit == sim)
                                    goto after_source;
                            }
                            amount = FUN_0104bdc0((void*)(char*)tool) * amount;
                        }
                    }
                }
            }
        } else {
            source = 0;
        }
    }
after_source:
    if (self->mByte80 != 0)
        return;
    if (GetCurrentGameMode() == (void*)0x1654c10) {
        void* gd = ((GetAccessor2)(*(void***)self)[0x17])(self, (void*)0x17f243b);   // +0x5c
        if (gd != 0) {
            void* d = FUN_00b18530(gd);
            if (d != 0 && !FUN_00f25370(d))
                return;
        }
    }
    if (self->mField34 == 2)
        return;

    if (GetCurrentGameMode() != (void*)0x1654c05 || type != 10) {
        self->mDamageState3c = (uint32_t)(uintptr_t)source;
        self->mField74 = dir->x;
        self->mField78 = dir->y;
        self->mField7c = dir->z;
    }

    switch (type) {
    case 3: case 4: case 0xc: case 0xe: case 0xf: case 0x10:
        return;
    }

    int active = 0;
    {
        void* o = ((GetAccessor)(*(void***)self)[3])(self);
        if (o != 0) {
            void* sub = ((GetAccessor2)(*(void***)o)[3])(o, (void*)0xd0036e08);
            if (sub != 0) {
                unsigned v = ((SubFlagsView*)sub)->mFlagsB58;
                if ((v >> 9) & 1)
                    active = (v & 0x2000) ? 1 : 0;
            }
        }
    }
    FUN_00bfca80(((GetAccessor3)(*(void***)self)[3])(self, source, (void*)(uintptr_t)active));
    if (type == 10) {
        if (self->mField34 != 2)
            self->mHealth38 += amount;
        float mx = ((GetFloat)(*(void***)self)[0x16])(self);         // +0x58
        if (self->mHealth38 <= mx)
            return;
        self->mHealth38 = ((GetFloat)(*(void***)self)[0x16])(self);
        return;
    }
    if (type == 0xb)
        return;
    float h = self->mHealth38 - amount;
    self->mHealth38 = h;
    if (h < *(float*)0x14698e8) {
        self->mHealth38 = 0.0f;
        self->mField34 = 2;
        Msg5 msg;
        SlotMessage_Construct(&msg, 0);
        msg.mData08 = self;
        msg.mField10 = (uint32_t)(uintptr_t)source;
        ((RcMsg*)MessageServer())->Send(0x1622184, &msg, 0);
        FUN_00f24b30(((GetAccessor2)(*(void***)self)[3])(self, (void*)(uintptr_t)type));
        SlotMessage_Destruct(&msg);
    }
}

// ---------------------------------------------------------------------------
// 0x00bfd1a0  Combatant::PartialRepair: top up the hit-point reservoir; when the
// matching tool is present, also heal the attacker's target and notify on a state
// change.
// ---------------------------------------------------------------------------
// @ 0x00bfd1a0
void __fastcall Combatant_PartialRepair(Combatant* self, int, float amount)
{
    if (!(0.0f < amount))
        return;
    if (self->mHealth38 < ((GetFloat)(*(void***)self)[0x16])(self)) {
        void* a = ((GetAccessor)(*(void***)self)[3])(self);
        void* b = ((GetAccessor)(*(void***)a)[0x13])(a);            // +0x4c
        void* c = ((GetAccessor)(*(void***)self)[3])(self);
        if (FUN_00bfc900(b) && FUN_00b673c0(c)) {
            float f = FUN_00b685e0(c);
            FUN_00b69930(c, f);
        }
    }
    int oldState = self->mField34;
    self->mField34 = 0;
    self->mHealth38 += amount;
    float mx = ((GetFloat)(*(void***)self)[0x16])(self);
    if (self->mHealth38 > mx)
        self->mHealth38 = mx;
    if (oldState != self->mField34) {
        Msg5 msg;
        msg.vftable = (void**)0x13eb90c;
        msg.mField04 = 0;
        msg.mData08 = self;
        msg.vftable = (void**)0x13eb844;
        msg.mField0c = 0;
        ((RcMsg*)MessageServer())->Send(0x1622184, &msg, 0);
        SlotMessage_Destruct(&msg);
    }
}
