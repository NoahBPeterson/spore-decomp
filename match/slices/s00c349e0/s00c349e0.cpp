// Slice s00c349e0 (worker 9) -- SP::cEmpire star-graph and star-ownership methods
// (0x00C349E0 .. 0x00C35740), a seven-function block inside the cEmpire cluster:
//   UpdateStarGraph, a small star-registration helper, RemoveStar,
//   ChangeStarEmpireOwnership, a tiny accessor, PickRandomPersonality and SetUFOKey.
//
// Retail layout of cEmpire used here (recovered from the asm; the 2008 PDB layout is smaller):
//   +0x050 uint32 mFlags       bit 0x10 = star graph dirty, bit 0x04 = personality roll
//   +0x054 int32  mTrait
//   +0x058 int32  mArchetype
//   +0x084 uint32 mEmpireID
//   +0x088 cStarRecord** mStarsBegin
//   +0x08c cStarRecord** mStarsEnd
//   +0x09c cStarRecord** mNextStar        (begin of the equal-length "next star" array)
//   +0x0b0 int32  mUFOKey                 (-1 = none)
//   +0x0b4 int32  mEmpireMoney            (-1 = none)
//   +0x0b8..+0xc0 int32 mUFOKey3[3]       (three-int key written by SetUFOKey)
//
// The routines are large and individually SSE/x87-scheduled; the engine classes they touch
// are defined outside the slice.  The bodies below are faithful structural reconstructions:
// every member read or written on cEmpire is named at its retail offset (unused gaps are
// explicit padding), dispatch into classes whose definition is not part of the slice goes
// through the retail vftable slot (raw slot dispatch is the accepted convention for an
// unknown vtable), and engine entry points carry their retail address.  Callees are
// relocations and are masked, so only calling convention and argument sizes matter.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed   int   i32;

#include <math.h>

struct Vec3 { float x, y, z; };

// Dispatch through vftable slot <byteOffset> of an object whose class is not known here.
#define VTSLOT(obj, off) ((*(void***)(obj))[(off) / 4])
// AutoRefCount slot 0 = AddRef, slot 4 = Release.
#define ADDREF(o)  (((Fn_v_p)VTSLOT((o), 0))((void*)(o)))
#define RELEASE(o) (((Fn_v_p)VTSLOT((o), 4))((void*)(o)))

typedef void  (__thiscall *Fn_v_p)(void*);
typedef void  (__thiscall *Fn_v_pp)(void*, void*);
typedef void  (__thiscall *Fn_v_pi)(void*, int);
typedef void  (__thiscall *Fn_v_ppi)(void*, void*, int);
typedef void  (__thiscall *Fn_v_piii)(void*, int, int, void**);
typedef bool  (__thiscall *Fn_b_pi)(void*, int, void**);
typedef int   (__thiscall *Fn_i_p)(void*);

// ---- forward declarations ------------------------------------------------------------------
struct Obj;
struct MsgObj;
struct cEmpire;
struct cStarRecord;

// ---- engine globals ------------------------------------------------------------------------
extern "C" void* DAT_016dda8c = 0;                 // 0x016dda8c  cSPBackgroundSimManager*
extern "C" u8    DAT_015b7436 = 0;                 // 0x015b7436  debug "always pick" flag
extern "C" float DAT_01485548 = 1.5f;              // 0x01485548  0x3FC00000
extern "C" float DAT_0146b79c = 0.70710678f;       // 0x0146b79c  0x3F34FDF4  cos(45 deg)
extern "C" float DAT_0140f330 = 45.0f;             // 0x0140f330  45.0f
extern "C" float DAT_01485720 = 1.0f;              // 0x01485720  HK_REAL_ONE
extern "C" float DAT_0146b688 = 0.017453292f;      // 0x0146b688  0x3C8EFA35  pi/180
extern "C" float DAT_0146b68c = 3.402823466e38f;   // 0x0146b68c  FLT_MAX (0x7F7FFFFF)

// ---- manager accessors (cdecl, no arguments) -----------------------------------------------
Obj*    __cdecl SP_StarManager();          // 0x00b3d2a0
Obj*    __cdecl SP_NounManager();          // 0x00b3d300
Obj*    __cdecl SP_CommManager();          // 0x00b3d4a0
Obj*    __cdecl SP_PropertyManager();      // 0x0067de30
MsgObj* __cdecl SP_MessageServer();        // 0x0067dcc0
Obj*    __cdecl SP_ObjectTemplateDB();     // 0x0067cb40
int     __cdecl SP_PlayerEmpireID();       // 0x01021090

// ---- free functions ------------------------------------------------------------------------
void __cdecl ChangeStarEmpireOwnership(cEmpire* self, void* newOwnerAvatar);  // 0x00c35240
void __cdecl UpdatePosseMembers(void* p);                                     // 0x0102c1a0
void __cdecl FUN_00c8c2a0(void* star);                                        // 0x00c8c2a0
char __cdecl FUN_00c70150(void* city, void* empire, int flag);                // 0x00c70150
void __cdecl FUN_00ba5bc0(void* empire, int mode);                            // 0x00ba5bc0
int  __cdecl FUN_00ba7320(void* arr);                                         // 0x00ba7320
// FUN_00c34060(begin, end, x, y, z): rebuild a 2D projection for the star list.  Caller cleans.
void __cdecl FUN_00c34060(cStarRecord** begin, cStarRecord** end,
                          float x, float y, float z);                         // 0x00c34060

// HashMap-like builder (this in ecx; ecx points at a {?, begin, end} triple).
struct HashMap {
    void* m0;
    void* mBegin;
    void* mEnd;
    void  Build(void* out, int n, void* key);                                 // 0x00c33da0 (ret 0xc)
};
// Intrusive vector of AutoRefCount<cStarRecord*> (this in ecx; arg = element count).
struct RefVector {
    void  Resize(int count, void* out);                                       // 0x00c34710 (ret 8)
};

// ---- collaborator surface ------------------------------------------------------------------
// Obj is the generic engine object used for every __thiscall target whose class is not
// declared in this slice.  Each entry point is named after its retail address.
struct Obj {
    Vec3*  m_5c65e0();                        // 0x005c65e0  cCivData::GetCities
    int*   m_41e990();                        // 0x0041e990  Property::GetInt
    float* m_41ea70();                        // 0x0041ea70  Property::GetFloat
    void*  m_b1fdb0();                        // 0x00b1fdb0  cGameNounManager::GetAvatar (this+0x54)
    void   m_af0d40(void* p);                 // 0x00af0d40  (ret 4)
    int    m_b8de30();                        // 0x00b8de30
    int    m_b8dab0();                        // 0x00b8dab0
    int    m_885c90();                        // 0x00885c90  (this+0x1d8)
    void*  m_bba790();                        // 0x00bba790  {begin, end, cap} triple
    void   m_bb4af0(void* star, void* flag);  // 0x00bb4af0  (ret 8)
    void   m_bb9c10(int v);                   // 0x00bb9c10  (ret 4)
    int    m_ba6d80(u32 starID);              // 0x00ba6d80  (ret 4)
    int    m_ba6dc0(u32 starID);              // 0x00ba6dc0  (ret 4)
    void*  m_ba9370(void* avatarID);          // 0x00ba9370  cStarManager::GetEmpireByID (ret 4)
    void   m_baf630(int empireID, int flag);  // 0x00baf630  (ret 8)
    void*  m_baf700(void* arg);               // 0x00baf700  (ret 4)
    void*  m_ce6950();                        // 0x00ce6950  cStarRecordRef::GetCommContext
    void   m_aeab40(void* key);               // 0x00aeab40  SpaceTool::RemoveByKey (ret 4)
    void   m_aea720(int key, void* ctx, int v);// 0x00aea720 SpaceTool::RemoveMatching (ret 0xc)
    void   m_1022150(void* planet);           // 0x01022150  cSPBackgroundSimManager::ActivatePlanet (ret 4)
    void   m_1021ab0(void* colony);           // 0x01021ab0  cSPBackgroundSimManager::RemovePlayerColony (ret 4)
    void   m_c37180(void* model, int flag);   // 0x00c37180  cSPGameDataUFO::SetDesiredModel (ret 8)
    void** m_b21340(int a, int b, int c, int d, int e); // 0x00b21340 GetGameDataVector (ret 0x14)
};

// Message server: slot 0x14 (index 5) and slot 0x18 (index 6) are the notify calls.
struct MsgObj {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void v0c(); virtual void v10();
    virtual void slot14(int a, int b, int c);         // vtable[0x14]
    virtual void slot18(int a, int b, int c, int d);  // vtable[0x18]
};

struct RandomLCG {
    float RandomDoubleUniform();              // 0x009360d0  (this in ecx, returns float in st0)
};

// ---- SP::cEmpire ---------------------------------------------------------------------------
struct cEmpire {
    u8   pad00[0x50];
    u32  mFlags;                              // +0x50
    i32  mTrait;                              // +0x54
    i32  mArchetype;                          // +0x58
    u8   pad5c[0x84 - 0x5c];
    u32  mEmpireID;                           // +0x84
    cStarRecord** mStarsBegin;                // +0x88
    cStarRecord** mStarsEnd;                  // +0x8c
    u8   pad90[0x9c - 0x90];
    cStarRecord** mNextStar;                  // +0x9c
    u8   pada0[0xb0 - 0xa0];
    i32  mUFOKey;                             // +0xb0
    i32  mEmpireMoney;                        // +0xb4
    i32  mUFOKey3[3];                         // +0xb8

    void  AddStar(void* star);                        // 0x00c341a0 (ret 4)
    char  FUN_00c31bf0(u32 empireID);                 // 0x00c31bf0 (ret 4)
    void  SetHomePlanet(Obj* planet);                 // 0x00c316c0 (ret 4)
    void  Destroy();                                  // 0x00c34320
    void* FUN_00c352f0(void* p);                      // 0x00c352f0 (ret 4)
    void  FUN_00c34e70(Obj* p);                       // 0x00c34e70 (ret 4)
    int   RemoveStar(cStarRecord* star, char flag);   // 0x00c34ee0 (ret 8)
    int   UpdateStarGraph();                          // 0x00c349e0
    void  PickRandomPersonality();                    // 0x00c35320
    void  SetUFOKey(int* key);                        // 0x00c35740 (ret 4)
};

// ============================================================================================
// @ 0x00c352f0
void* cEmpire::FUN_00c352f0(void* p)
{
    ((Obj*)p)->m_af0d40((char*)this + 0x108);
    return p;
}

// ============================================================================================
// @ 0x00c34e70
void cEmpire::FUN_00c34e70(Obj* p)
{
    if (p == 0)
        return;
    if (this->mEmpireID == (u32)SP_PlayerEmpireID())
        ((Obj*)DAT_016dda8c)->m_1022150(p);
    this->AddStar((void*)(u32)((Obj*)p)->m_b8de30());
    if (this->FUN_00c31bf0((u32)SP_PlayerEmpireID()) != 0) {
        MsgObj* msg = SP_MessageServer();
        msg->slot18(0x43f2585, 0, 0, 0);
    }
}

// ============================================================================================
// @ 0x00c352f0 helper ends here; next: SP::ChangeStarEmpireOwnership

// ============================================================================================
// @ 0x00c35240  SP::ChangeStarEmpireOwnership
void __cdecl ChangeStarEmpireOwnership(cEmpire* self, void* newOwnerAvatar)
{
    void* av = ((Obj*)self)->m_b1fdb0();
    cEmpire* oldEmpire = (cEmpire*)((Obj*)SP_StarManager())->m_ba9370(av);
    cEmpire* newEmpire = (cEmpire*)((Obj*)SP_StarManager())->m_ba9370(newOwnerAvatar);

    oldEmpire->RemoveStar((cStarRecord*)self, 0);
    newEmpire->AddStar(self);
    UpdatePosseMembers(self);

    void* v = ((Obj*)self)->m_bba790();
    void** begin = *(void***)v;
    void** end = *(void***)((char*)v + 4);
    for (void** it = begin; it != end; ++it) {
        void* ctx = ((Obj*)*it)->m_ce6950();
        ((Obj*)SP_CommManager())->m_aeab40(ctx);
        ((Obj*)SP_CommManager())->m_aea720((int)oldEmpire->mEmpireID, ctx, 0);
    }
}

// ============================================================================================
// @ 0x00c34ee0  SP::cEmpire::RemoveStar
int cEmpire::RemoveStar(cStarRecord* star, char flag)
{
    i32 count = (i32)(this->mStarsEnd - this->mStarsBegin);
    i32 index = 0;
    char changed = 0;

    if (count <= 0)
        return 0;
    cStarRecord** p = this->mStarsBegin;
    for (;;) {
        if (*p == star)
            break;
        ++index;
        ++p;
        if (index >= count)
            return 0;
    }

    if (flag != 0) {
        FUN_00c8c2a0(star);
    } else if (this->mEmpireID == (u32)SP_PlayerEmpireID()) {
        void* v = ((Obj*)star)->m_bba790();
        void** begin = *(void***)v;
        void** end = *(void***)((char*)v + 4);
        for (void** it = begin; it != end; ++it) {
            void* colony = *it;
            if (((Obj*)colony)->m_b8dab0() == 5)
                ((Obj*)DAT_016dda8c)->m_1021ab0(colony);
        }
    }

    // erase at <index>: move the tail element over it, then release the vacated slot.
    if (index != count - 1) {
        cStarRecord** b = this->mStarsBegin;
        cStarRecord* cur = b[index];
        cStarRecord* tail = b[count - 1];
        if (tail != cur) {
            if (tail)
                ADDREF(tail);
            b[index] = tail;
            if (cur)
                RELEASE(cur);
        }
    }
    this->mStarsEnd -= 1;
    {
        cStarRecord* stale = *this->mStarsEnd;
        if (stale)
            RELEASE(stale);
    }

    {
        MsgObj* msg = SP_MessageServer();
        msg->slot14(0x55bd8f7, 0, 0);
    }
    this->mFlags |= 0x10;

    if (*(i32*)((char*)star + 0x70) == this->mUFOKey || this->mUFOKey == -1)
        changed = 1;

    if (((Obj*)SP_StarManager())->m_885c90() == (i32)this->mEmpireID)
        ((Obj*)star)->m_bb9c10(0);

    if (changed) {
        i32 n = (i32)(this->mStarsEnd - this->mStarsBegin);
        float bestDist = DAT_0146b68c;
        cStarRecord* bestStar = 0;
        Vec3* sc = ((Obj*)star)->m_5c65e0();
        for (i32 i = 0; i < n; ++i) {
            cStarRecord* s = this->mStarsBegin[i];
            Vec3* c = ((Obj*)s)->m_5c65e0();
            float dx = c->x - sc->x;
            float dy = c->y - sc->y;
            float dz = c->z - sc->z;
            float d = dx * dx + dy * dy + dz * dz;
            if (bestDist > d) {
                bestDist = d;
                bestStar = s;
            }
        }
        if (bestStar != 0) {
            ((Obj*)SP_StarManager())->m_bb4af0(bestStar, 0);
            void* v = ((Obj*)bestStar)->m_bba790();
            void** begin = *(void***)v;
            void** end = *(void***)((char*)v + 4);
            for (void** it = begin; it != end; ++it) {
                void* city = *it;
                if (city != 0 && FUN_00c70150(city, this, 0)) {
                    this->SetHomePlanet((Obj*)city);
                    return 1;
                }
            }
        }
    }

    {
        i32 planet = ((Obj*)SP_StarManager())->m_ba6d80((u32)this->mUFOKey);
        if (this->mEmpireMoney == -1 && planet != 0) {
            ((Obj*)SP_StarManager())->m_bb4af0((void*)planet, 0);
            void* v = ((Obj*)planet)->m_bba790();
            void* home = *(void**)*(void**)v;
            this->SetHomePlanet((Obj*)home);
        }
    }
    if (this->mEmpireMoney != -1) {
        if (((Obj*)SP_StarManager())->m_ba6dc0((u32)this->mEmpireMoney) != 0)
            FUN_00ba5bc0(this, 6);
    }

    {
        i32 id = (i32)this->mEmpireID;
        this->mEmpireMoney = -1;
        this->mUFOKey = -1;
        ((Obj*)SP_StarManager())->m_baf630(id, 0);
        MsgObj* msg = SP_MessageServer();
        msg->slot18(0x43f2586, 0, 0, 0);
    }

    if (this->mStarsBegin == this->mStarsEnd)
        this->Destroy();
    return 1;
}

// ============================================================================================
// @ 0x00c349e0  SP::cEmpire::UpdateStarGraph
int cEmpire::UpdateStarGraph()
{
    if ((this->mFlags & 0x10) == 0)
        return 0;

    float cosThreshold = DAT_0146b79c;
    float scaleLimit = DAT_01485548;

    Obj* prop = 0;
    Obj* pm = SP_PropertyManager();
    if (prop != 0) {
        RELEASE(prop);
        prop = 0;
    }
    ((Fn_v_piii)VTSLOT(pm, 0x2c))(pm, 0xcdf8d12f, 0x2ae0c7e, (void**)&prop);

    if (prop != 0) {
        Obj* out = 0;
        float angle = DAT_0140f330;                       // 45 degrees
        if (((Fn_b_pi)VTSLOT(prop, 0x24))(prop, 0x4bf0dac, (void**)&out)
            && *(u16*)((char*)out + 0x12) == 0xd)
            angle = ((Obj*)out)->m_41ea70()[0];
        cosThreshold = cosf(angle * DAT_0146b688);

        if (((Fn_b_pi)VTSLOT(prop, 0x24))(prop, 0x4bf0dbd, (void**)&out)
            && *(u16*)((char*)out + 0x12) == 0xd) {
            scaleLimit = ((Obj*)out)->m_41ea70()[0];
            if (scaleLimit < DAT_01485720)
                scaleLimit = DAT_01485720;
        }
    }

    cStarRecord* home = (cStarRecord*)((Obj*)SP_StarManager())->m_ba6d80((u32)this->mUFOKey);
    if (home == 0) {
        if (prop != 0)
            RELEASE(prop);
        return 0;
    }

    Vec3* hc = ((Obj*)home)->m_5c65e0();
    float hx = hc->x, hy = hc->y, hz = hc->z;
    FUN_00c34060(this->mStarsBegin, this->mStarsEnd, hx, hy, hz);

    i32 n = (i32)(this->mStarsEnd - this->mStarsBegin);
    i32 sel = 0;
    ((RefVector*)&this->mNextStar)->Resize(n, &sel);

    for (i32 i = 0; i < n; ++i) {
        cStarRecord* si = this->mStarsBegin[i];
        if (si == home)
            continue;

        Vec3* a = ((Obj*)si)->m_5c65e0();
        float dx = a->x - hx, dy = a->y - hy, dz = a->z - hz;
        float bestDist = sqrtf(dx * dx + dy * dy + dz * dz);
        i32 bestIdx = 0;

        for (i32 j = 1; j < i; ++j) {
            Vec3* b = ((Obj*)this->mStarsBegin[j])->m_5c65e0();
            float ex = b->x - hx, ey = b->y - hy, ez = b->z - hz;
            float dist = sqrtf(ex * ex + ey * ey + ez * ez);
            float ux = dx - ex, uy = dy - ey, uz = dz - ez;
            float ulen = sqrtf(ux * ux + uy * uy + uz * uz);
            if (ulen > 0.0f && dist < bestDist && dist > 0.0f) {
                float dot = (dx * ex + dy * ey + dz * ez) / (bestDist * dist);
                if (dot >= cosThreshold * scaleLimit) {
                    bestDist = dist;
                    bestIdx = j;
                    dx = ex; dy = ey; dz = ez;
                }
            }
        }

        cStarRecord** slot = &this->mNextStar[i];
        cStarRecord* chosen = this->mStarsBegin[bestIdx];
        cStarRecord* old = *slot;
        if (chosen != old) {
            if (chosen)
                ADDREF(chosen);
            *slot = chosen;
            if (old)
                RELEASE(old);
        }
    }

    this->mFlags &= ~0x10u;
    if (prop != 0)
        RELEASE(prop);
    return 1;
}

// ============================================================================================
// @ 0x00c35320  SP::cEmpire::PickRandomPersonality
void cEmpire::PickRandomPersonality()
{
    if (((Obj*)SP_StarManager())->m_885c90() == (i32)this->mEmpireID) {
        this->mArchetype = 8;
        this->mTrait = 0;
        this->mFlags &= ~4u;
        return;
    }

    Obj* prop = 0;
    Obj* pm = SP_PropertyManager();
    if (prop != 0) {
        RELEASE(prop);
        prop = 0;
    }
    ((Fn_v_piii)VTSLOT(pm, 0x2c))(pm, 0x40020b6f, 0x2ae0c7e, (void**)&prop);
    if (prop == 0)
        return;

    {
        HashMap map;
        u32 arche[9];
        static const int kArch[8] = {
            0x55500bf, 0x55500cd, 0x55500d5, 0x55500dc,
            0x55500e2, 0x55500e9, 0x55500ee, 0x55500f6
        };
        map.Build(arche, 9, &prop);
        for (int k = 0; k < 8; ++k) {
            Obj* out = 0;
            if (prop != 0
                && ((Fn_b_pi)VTSLOT(prop, 0x24))(prop, kArch[k], (void**)&out)
                && *(u16*)((char*)out + 0x12) == 9) {
                arche[k] = (u32)((Obj*)out)->m_41e990()[0];
            }
        }
        this->mArchetype = FUN_00ba7320(arche);
    }

    {
        HashMap map;
        u32 trait[4];
        static const int kTrait[4] = { 0x2f98dae, 0x2f98db1, 0x2f98db3, 0x2f98db5 };
        map.Build(trait, 4, &prop);
        for (int k = 0; k < 4; ++k) {
            Obj* out = 0;
            if (prop != 0
                && ((Fn_b_pi)VTSLOT(prop, 0x24))(prop, kTrait[k], (void**)&out)
                && *(u16*)((char*)out + 0x12) == 9) {
                trait[k] = (u32)((Obj*)out)->m_41e990()[0];
            }
        }
        this->mTrait = FUN_00ba7320(trait);
    }

    {
        float v = 0.0f;
        Obj* p2 = (Obj*)((Obj*)SP_StarManager())->m_baf700(this);
        Obj* out = 0;
        if (p2 != 0
            && ((Fn_b_pi)VTSLOT(p2, 0x24))(p2, 0x576373a, (void**)&out)
            && *(u16*)((char*)out + 0x12) == 0xd)
            v = ((Obj*)out)->m_41ea70()[0];

        float r = ((RandomLCG*)0x1601760)->RandomDoubleUniform();
        if (v > r || DAT_015b7436 != 0)
            this->mFlags |= 4;
        else
            this->mFlags &= ~4u;
    }

    if (prop != 0)
        RELEASE(prop);
}

// ============================================================================================
// @ 0x00c35740  SP::cEmpire::SetUFOKey
void cEmpire::SetUFOKey(int* key)
{
    if (this->mUFOKey3[0] == key[0]
        && this->mUFOKey3[1] == key[1]
        && this->mUFOKey3[2] == key[2])
        return;
    this->mUFOKey3[0] = key[0];
    this->mUFOKey3[1] = key[1];
    this->mUFOKey3[2] = key[2];

    {
        Obj* db = SP_ObjectTemplateDB();
        ((Fn_v_ppi)VTSLOT(db, 0x58))(db, key, 1);
    }

    {
        void** vec = ((Obj*)SP_NounManager())->m_b21340(0xcd7d10, 0xd3d420, 0xad48b0,
                                                        0xb1e500, 0x18ebadc);
        void** begin = (void**)((void**)vec)[1];
        void** end = (void**)((void**)vec)[2];
        for (void** p = begin; p != end; ++p) {
            void* item = *p;
            if (((Fn_i_p)VTSLOT(item, 0x4c))(item) == (int)this->mEmpireID)
                ((Obj*)item)->m_c37180(key, 1);
        }
    }
}