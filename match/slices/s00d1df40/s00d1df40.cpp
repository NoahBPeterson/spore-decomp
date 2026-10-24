// Slice s00d1df40 -- SP:: UI-panel / creature-social helper cluster
// (0x00d1df40..0x00d1e920).
//
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same family as the sibling
// Simulator/UI slices.
//
// Contents:
//   d1df40  refresh the six civilization stat labels in the mission-summary layout.
//   d1e140  $E207 destructor -- reset the vtable, release the window (+4) and the city (+8),
//           then conditionally free.
//   d1e180  $E207 (constructor body): allocate+construct the connection dialog, assign it to
//           +4, Init/SetParentWin the layout, recolour six label windows, toggle six button
//           pairs and mark the correct one visible for the city's vehicle specialty.
//   d1e4b0  helper: compare a VU/tuning scalar against the tuned bound, returning 2 when under.
//   d1e530  predicate: gate on game mode and relation then ask the d1e4b0 helper.
//   d1e5c0  index-of: scan a manager's element list backwards for a matching handle.
//   d1e610  game-mode switch returning the avatar (create/mission) or the tribe leader.
//   d1e670  clear the four current terrain-sphere markers.
//   d1e6c0  SP::AbilityIsBeingTaughtToBaby -- check the current baby-training record.
//   d1e720  SP::CanSocial -- decide if two creatures may start a social interaction.
//   d1e7f0  manager element -> associated float (0 when out of range).
//   d1e830  manager/inline-table index lookup by editor species.
//   d1e8d0  predicate: element flag "detached" (value != 1.0 and bit set in the +0xbf8 set).
//
// Result (this session): see manifest.txt / nonmatching.txt / partial.txt.
// Every function below is a complete definition.
//
// Notes / decisions:
//  * ABI: thiscall methods are reproduced as `__fastcall(T* self, void* edx, ...)` free
//    functions; external thiscall callees are called through small struct types (ecx = the
//    receiver) or virtual interfaces whose declaration order equals the vtable order.
//  * Field offsets use named members on typed structs only (no raw-offset pointer casts).
//    The overlaps the original really has (the tag/index words at +0x1d8/+0x1dc that sit inside
//    the first 0xac-stride record) are modelled by naming the fields on the record.
#include "types.h"
#include <math.h>
#include <wchar.h>

typedef unsigned int uint;
typedef unsigned int uintptr_t;

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16

// ---------------------------------------------------------------------------------------------
// Interfaces / object layouts.
// ---------------------------------------------------------------------------------------------

// cSPUILayout window object (cSPUIWindow-like): vtable slots used by this slice.
struct IWin {
    PV8 PV4 PV                                   // 0x00..0x30
    virtual float* Slot34();                     // 0x34  (returns a pointer to a rect/vector)
    PV8 PV                                       // 0x38..0x58
    virtual void   Slot5c(uint argb);            // 0x5c  (set colour)
    PV                                           // 0x60
    virtual void   Slot64(float a, float b);     // 0x64  (set range)
    PV4 PV                                       // 0x68..0x78
    virtual void   Slot7c(int a, int b);         // 0x7c  (set visible/toggle)
    virtual void   Slot80(const wchar_t* text);  // 0x80  (set caption)
};

// Ref-counted object with AddRef at slot 4 and Release at slot 8.
struct IRefS {
    PV                                           // 0x00
    virtual void Slot4();                        // 0x04
    virtual void Slot8();                        // 0x08
};

// Broad manager / creature / vehicle vtable: the slots this slice reaches.
struct IVtbl {
    PV PV                                        // 0x00, 0x04
    virtual int   Slot8(int a);                  // 0x08
    virtual void* SlotC();                       // 0x0c
    PV8 PV4 PV2 PV                               // 0x10..0x48
    virtual int   Slot4c();                      // 0x4c
    PV16 PV8                                     // 0x50..0xac
    virtual int   SlotB0();                      // 0xb0  (count)
    virtual int   SlotB4(int i);                 // 0xb4  (element i)
    PV4 PV2 PV                                   // 0xb8..0xd0
    virtual char  SlotD4();                      // 0xd4
};

// cCity reached through *(this+8).
struct Civ;
struct cCity {
    Civ* GetCivilization();                      // 0x00bd9bf0
    int  GetVehicleSpecialty();                  // 0x00bd81d0
};

// Civilization: the two stat getters used by the mission summary.
struct Civ {
    int FUN_00bf1fd0(int a);                     // 0x00bf1fd0
    int FUN_00bf0c60(int a, int b, int c, int d); // 0x00bf0c60
};

// Noun manager (SP::NounManager()) and its directors.
struct NounMgr {
    void* GetPlayerTribe();                      // 0x00bfc5f0
    void* GetAvatar();                           // 0x00b1fdb0
    void* GetCurrentTerrainSphere();             // 0x00f67d90
};
struct Community {
    void* GetLeader();                           // 0x00c00650
};
struct Sphere {
    void FUN_00c77320(uint id);                  // 0x00c77320
};
struct AvatarProfile;
struct SpeciesMgr {
    AvatarProfile* GetAvatarProfile();           // 0x004df420
};

// cSPUILayout non-virtual helpers (undefined externs; only ecx matters).
struct ResKey { uint a, b, c; };
struct cSPUILayout {
    void* FindWindowByID(uint id, int a);              // 0x008105b0
    bool  Init(const ResKey* key, int flag, uint id);  // 0x008120d0
    bool  SetParentWin(void* win, int flag, uint id);  // 0x008121b0
};

// Connection dialog object (what $E207 is wrapped around).
struct ConnectionDialog {
    void* ctor();                                      // 0x00810000
};

// Tuning object with a bound query.
struct TuningObj {
    float GetBound(bool flag);                         // 0x004d3d70
};

// The creature used by the social helpers (loco sub-object at +0xc0, flags at +0xb58).
struct Loco { uint32_t mDummy; };
struct cCreature {
    uint8_t  pad00[0xc0];
    Loco     mLoco;                                    // +0xc0
    uint8_t  padC4[0xb58 - (0xc0 + sizeof(Loco))];
    uint32_t mFlagsB58;                                // +0xb58
    uint8_t  padB5c[0xb5e - (0xb58 + 4)];
    uint8_t  mFlagB5e;                                 // +0xb5e
    void*    FUN_00c0bc00(void* a);                    // 0x00c0bc00
    void*    GetSocialGoal();                          // 0x00c0e6a0
};

// Element record with a float value at +4 (stride 0x10).
struct Elem {
    uint8_t pad00[4];
    float   mValue;                                    // +0x04
    uint8_t pad08[8];
};
// Object holding the 0x58-bit flag set at +0xbf8 and the element array at +0xc28.
struct FlagSetObj {
    uint8_t  pad00[0xbf8];
    uint32_t mFlags[12];                               // +0xbf8
    Elem*    mpElems;                                  // +0xc28
};

// ----- objects touched by the baby-training check ---------------------------------------------
struct BabyRec {
    int32_t  mId;                                      // +0x00 (object +0x168)
    uint8_t  pad04[0x70 - 4];
    uint32_t mTag;                                     // +0x70 (object +0x1d8)
    uint32_t mIndex;                                   // +0x74 (object +0x1dc)
    uint8_t  pad78[0xac - 0x78];
};
struct TrainData {
    uint8_t pad00[0x168];
    BabyRec mRecs[1];                                  // +0x168 (stride 0xac)
};
struct TrainObj {
    uint8_t  pad00[0x14];
    void*    mpAgent;                                  // +0x14
    uint8_t  pad18[0x6c - 0x18];
    uint32_t mFlags6c;                                 // +0x6c
};
struct AgentLink {
    uint8_t pad00[0xb4c];
    void*   mpData;                                    // +0xb4c
};

// ----- objects touched by CanSocial -----------------------------------------------------------
struct SocialData {
    uint8_t pad00[0x1d8];
    uint32_t mTag;                                     // +0x1d8
    uint8_t pad1dc[0x600 - 0x1dc];
    void*   mpInner;                                   // +0x600
};
struct InnerObj {
    uint8_t pad00[8];
    uint32_t mTag8;                                    // +0x08
    uint8_t pad0c[0x1e4 - 0xc];
    uint8_t mFlag1e4;                                  // +0x1e4
};
struct DataLink {
    uint8_t pad00[0xb4c];
    SocialData* mpData;                                // +0xb4c
};
struct OrderMgr {
    int FindSlot(int a, int b, int c, int d);          // 0x00bca0c0
};
struct OrderLink {
    uint8_t  pad00[0xb48];
    OrderMgr* mpOrder;                                 // +0xb48
};
// Result of the relation helper chain; slot 0x000 can answer the social query.
struct SocialProbe {
    int FUN_00ba3f90(void* b, void* c);                // 0x00ba3f90
};

// Avatar profile reached through GetSetting9()->GetAvatarProfile().
struct AvatarProfile {
    uint8_t   pad00[0x6d4];
    uint32_t* mpIds;                                   // +0x6d4
};

// The $E207 wrapper object.
struct Wrapper {
    cSPUILayout* mpLayout;                             // +0x04
    cCity*       mpCity;                               // +0x08
};

// The object the destructor runs on (vtable at +0, two ref-counted pointers).
struct E207Obj {
    void* mpVtbl;                                      // +0x00
    void* mpA;                                         // +0x04
    void* mpB;                                         // +0x08
};

// ---------------------------------------------------------------------------------------------
// External callees (undefined externs; only the call shape matters).
// ---------------------------------------------------------------------------------------------
int   __cdecl Sprintf16(wchar_t* out, const wchar_t* fmt, ...);   // 0x009399c0
void* __cdecl OpNew(uint size, const char* name, int, int, int, int); // 0x00f473a0
void  __cdecl OpDelete(void* p);                    // 0x00f47380
uint  __cdecl FUN_00b6f0c0(uint id);                // 0x00b6f0c0
uint  __cdecl SP_ColorRGBToU32(uint rgb);           // 0x00458a40
float __cdecl FUN_00d99ac0(void* loco, int sel);    // 0x00d99ac0
void* __cdecl SP_GetCurrentGameMode();              // 0x00b5b800
char  __cdecl FUN_00c0e8d0(void* a, int b);         // 0x00c0e8d0
void* __cdecl SP_NounManager();                     // 0x00b3d300
void* __cdecl FUN_00d51660();                       // 0x00d51660
void* __cdecl FUN_00c0bc00(void* a, void* b);       // 0x00c0bc00
void* __cdecl FUN_00b3d4c0(void* a);                // 0x00b3d4c0
void* __cdecl GetSetting9();                        // 0x00401090

extern const float  gRealOne;          // 0x01485720 (_HK_REAL_ONE)
extern const float  gSignFlip13eb8b0;  // 0x013eb8b0 (0x80000000 x4)
extern const char   kEditorAllocName[];// 0x013eb430
extern void*        gVtableE207;       // 0x0147a2b0
extern const unsigned char gByte1582df5; // 0x01582df5 (byte gate)
extern uint32_t     gTable169de64[6];  // 0x0169de64

// ---------------------------------------------------------------------------------------------
// @ 0x00d1df40
// ---------------------------------------------------------------------------------------------
void __fastcall FUN_00d1df40(Wrapper* self, void* edx)
{
    (void)edx;
    Civ* civ = self->mpCity->GetCivilization();
    int a0 = civ->FUN_00bf1fd0(0);
    int b0 = civ->FUN_00bf0c60(0, -1, -1, 0);
    int a1 = civ->FUN_00bf1fd0(1);
    int b1 = civ->FUN_00bf0c60(1, -1, -1, 0);
    int a2 = civ->FUN_00bf1fd0(2);
    int b2 = civ->FUN_00bf0c60(2, -1, -1, 0);
    cSPUILayout* layout = self->mpLayout;
    wchar_t buf[32];
    IWin* w;
    w = (IWin*)layout->FindWindowByID(0x6256701, 1);
    if (w) { Sprintf16(buf, L"%d / %d", b0, a0); w->Slot80(buf); }
    w = (IWin*)layout->FindWindowByID(0x6256702, 1);
    if (w) { Sprintf16(buf, L"%d / %d", b0, a0); w->Slot80(buf); }
    w = (IWin*)layout->FindWindowByID(0x6256705, 1);
    if (w) { Sprintf16(buf, L"%d / %d", b1, a1); w->Slot80(buf); }
    w = (IWin*)layout->FindWindowByID(0x6256706, 1);
    if (w) { Sprintf16(buf, L"%d / %d", b1, a1); w->Slot80(buf); }
    w = (IWin*)layout->FindWindowByID(0x6256703, 1);
    if (w) { Sprintf16(buf, L"%d / %d", b2, a2); w->Slot80(buf); }
    w = (IWin*)layout->FindWindowByID(0x6256704, 1);
    if (w) { Sprintf16(buf, L"%d / %d", b2, a2); w->Slot80(buf); }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d1e140
// ---------------------------------------------------------------------------------------------
void* __fastcall FUN_00d1e140(E207Obj* self, void* edx, unsigned int flags)
{
    (void)edx;
    self->mpVtbl = (void*)&gVtableE207;
    void* p2 = self->mpB;
    if (p2) ((IRefS*)p2)->Slot4();
    void* p1 = self->mpA;
    if (p1) ((IRefS*)p1)->Slot8();
    if (flags & 1)
        OpDelete(self);
    return self;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d1e180
// ---------------------------------------------------------------------------------------------
bool __fastcall FUN_00d1e180(Wrapper* self, void* edx, void* param_2)
{
    (void)edx;
    Wrapper* wself = self;
    ConnectionDialog* d = (ConnectionDialog*)OpNew(0x18, kEditorAllocName, 0, 0, 0, 0);
    if (d)
        d = (ConnectionDialog*)d->ctor();
    void* old = wself->mpLayout;
    if (d != old) {
        if (d) ((IRefS*)d)->Slot4();
        wself->mpLayout = (cSPUILayout*)d;
        if (old) ((IRefS*)old)->Slot8();
    }
    cSPUILayout* layout = wself->mpLayout;
    ResKey key;
    key.a = 0x996e6398;
    key.b = 0x0510a95b;
    key.c = 0x40464100;
    if (!layout->Init(&key, 1, 0x5b598fa))
        return false;
    layout->SetParentWin(param_2, 1, 0x5b598fa);
    IWin* w;
    w = (IWin*)layout->FindWindowByID(0x53439d0, 1);
    if (w) {
        float* r = w->Slot34();
        w->Slot64(-(r[2] - r[0]), 0.0f);
    }
    uint color = SP_ColorRGBToU32(FUN_00b6f0c0(0x53dbcf1));
    w = (IWin*)layout->FindWindowByID(0x6256751, 1); if (w) w->Slot5c(color);
    w = (IWin*)layout->FindWindowByID(0x6256752, 1); if (w) w->Slot5c(color);
    w = (IWin*)layout->FindWindowByID(0x6256755, 1); if (w) w->Slot5c(color);
    w = (IWin*)layout->FindWindowByID(0x6256756, 1); if (w) w->Slot5c(color);
    w = (IWin*)layout->FindWindowByID(0x6256753, 1); if (w) w->Slot5c(color);
    w = (IWin*)layout->FindWindowByID(0x6256754, 1); if (w) w->Slot5c(color);
    w = (IWin*)layout->FindWindowByID(0x62583c0, 1); if (w) w->Slot7c(1, 1);
    w = (IWin*)layout->FindWindowByID(0x62583c1, 1); if (w) w->Slot7c(1, 0);
    w = (IWin*)layout->FindWindowByID(0x62583c4, 1); if (w) w->Slot7c(1, 1);
    w = (IWin*)layout->FindWindowByID(0x62583c5, 1); if (w) w->Slot7c(1, 0);
    w = (IWin*)layout->FindWindowByID(0x62583c2, 1); if (w) w->Slot7c(1, 1);
    w = (IWin*)layout->FindWindowByID(0x62583c3, 1); if (w) w->Slot7c(1, 0);
    uint show;
    switch (wself->mpCity->GetVehicleSpecialty()) {
    case 0:
        w = (IWin*)layout->FindWindowByID(0x62583c0, 1); if (w) w->Slot7c(1, 0);
        show = 0x62583c1;
        break;
    case 1:
        w = (IWin*)layout->FindWindowByID(0x62583c4, 1); if (w) w->Slot7c(1, 0);
        show = 0x62583c5;
        break;
    case 2:
        w = (IWin*)layout->FindWindowByID(0x62583c2, 1); if (w) w->Slot7c(1, 0);
        show = 0x62583c3;
        break;
    default:
        return true;
    }
    w = (IWin*)layout->FindWindowByID(show, 1);
    if (w)
        w->Slot7c(1, 1);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d1e4b0
// ---------------------------------------------------------------------------------------------
int __cdecl FUN_00d1e4b0(TuningObj* param_1, cCreature* param_2, IVtbl* param_3)
{
    if (gByte1582df5 != 1) {
        Loco* loco = param_2 ? &param_2->mLoco : 0;
        int sel = param_3->Slot8(1);
        float v = FUN_00d99ac0(loco, sel);
        bool flag = ((param_2->mFlagsB58 >> 9) & 1u) != 0;
        float bound = param_1->GetBound(flag);
        if (v < bound)
            return 2;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d1e530
// ---------------------------------------------------------------------------------------------
int __cdecl FUN_00d1e530(TuningObj* param_1, IVtbl* param_2, cCreature* param_3, IVtbl* param_4)
{
    if (param_4 == 0)
        return 3;
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) {
        IVtbl* x = (IVtbl*)param_4->SlotC();
        int a = x->Slot4c();
        int b = param_2->Slot4c();
        if (a == b)
            return 0xc;
    }
    if (param_3 != 0) {
        if (param_3->mFlagB5e != 0)
            return 7;
        if (FUN_00c0e8d0(param_2, 6) != 0)
            return 0xc;
    }
    return FUN_00d1e4b0(param_1, param_3, param_4);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d1e5c0
// ---------------------------------------------------------------------------------------------
int __cdecl FUN_00d1e5c0(IVtbl* param_1, int param_2)
{
    int i = param_1->SlotB0() - 1;
    while (i >= 0) {
        if (param_1->SlotB4(i) == param_2)
            return i;
        --i;
    }
    return -1;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d1e610
// ---------------------------------------------------------------------------------------------
void* __cdecl FUN_00d1e610(void)
{
    switch ((uintptr_t)SP_GetCurrentGameMode()) {
    case 0x1654c01:
    case 0x1654c10:
        return ((NounMgr*)SP_NounManager())->GetAvatar();
    case 0x1654c02: {
        void* c = ((NounMgr*)SP_NounManager())->GetPlayerTribe();
        if (c)
            return ((Community*)c)->GetLeader();
        return 0;
    }
    default:
        return 0;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d1e670
// ---------------------------------------------------------------------------------------------
void __cdecl FUN_00d1e670(void)
{
    Sphere* s = (Sphere*)((NounMgr*)SP_NounManager())->GetCurrentTerrainSphere();
    if (s) {
        s->FUN_00c77320(0x5ff7927);
        s->FUN_00c77320(0x5ff7928);
        s->FUN_00c77320(0x5ff7baf);
        s->FUN_00c77320(0x5ff7bb6);
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d1e6c0
// ---------------------------------------------------------------------------------------------
bool SP_AbilityIsBeingTaughtToBaby(int param_1)
{
    if (param_1 == -1)
        return false;
    TrainObj* o = (TrainObj*)FUN_00d51660();
    if (((o->mFlags6c >> 4) & 1u) == 0)
        return false;
    o = (TrainObj*)FUN_00d51660();
    AgentLink* a = (AgentLink*)o->mpAgent;
    if (a == 0)
        return false;
    TrainData* d = (TrainData*)a->mpData;
    if (d->mRecs[0].mTag != 0xb413edc5)
        return false;
    unsigned idx = d->mRecs[0].mIndex;
    return param_1 == d->mRecs[idx].mId;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d1e720
// ---------------------------------------------------------------------------------------------
int __cdecl SP_CanSocial(cCreature* param_1, cCreature* param_2)
{
    if (param_2 == 0)
        return 4;
    void* r = param_2->FUN_00c0bc00(param_1);
    void* q = FUN_00b3d4c0(r);
    int res = ((SocialProbe*)q)->FUN_00ba3f90(param_2, param_1);
    if (res == 5 && ((OrderLink*)param_2)->mpOrder->FindSlot(2, 1, 0, 0) == -1)
        return 1;
    if (param_2->mFlagB5e != 0)
        return 1;
    if (param_2->GetSocialGoal() == 0 && ((IVtbl*)param_2)->SlotD4() != 0)
        return 6;
    if (((DataLink*)param_1)->mpData->mTag == 0x941bd4bf) {
        SocialData* p = ((DataLink*)param_2)->mpData;
        if (p->mTag != 0x341bd4be)
            return 5;
        InnerObj* in = (InnerObj*)p->mpInner;
        if (in && in->mTag8 == 0x14fcf96e && in->mFlag1e4 == 0)
            return 5;
        return 0;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d1e7f0
// ---------------------------------------------------------------------------------------------
float __cdecl FUN_00d1e7f0(FlagSetObj* param_1, int param_2)
{
    int i = FUN_00d1e5c0((IVtbl*)param_1, param_2);
    int n = ((IVtbl*)param_1)->SlotB0();
    if (i >= 0 && i < n)
        return param_1->mpElems[i].mValue;
    return 0.0f;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d1e830
// ---------------------------------------------------------------------------------------------
void* __cdecl FUN_00d1e830(int param_1)
{
    if (param_1 == -1)
        return 0;
    IVtbl* p = (IVtbl*)FUN_00d1e610();
    if (p != 0) {
        int n = p->SlotB0();
        if (param_1 < n)
            return (void*)(uintptr_t)p->SlotB4(param_1);
        if (SP_GetCurrentGameMode() == (void*)0x1654c02) {
            int d = param_1 - n;
            if (d >= 6)
                return 0;
            return (void*)(uintptr_t)gTable169de64[d];
        }
    }
    if (SP_GetCurrentGameMode() != (void*)0x1654c01 && SP_GetCurrentGameMode() != (void*)0x1654c10)
        return 0;
    AvatarProfile* profile = ((SpeciesMgr*)GetSetting9())->GetAvatarProfile();
    return (void*)(uintptr_t)profile->mpIds[param_1];
}

// ---------------------------------------------------------------------------------------------
// @ 0x00d1e8d0
// ---------------------------------------------------------------------------------------------
bool __cdecl FUN_00d1e8d0(FlagSetObj* param_1, uint param_2)
{
    float f = param_1->mpElems[param_2].mValue;
    if (f == gRealOne)
        return false;
    if (param_2 >= 0x58)
        return false;
    uint mask = 1u << (param_2 & 0x1f);
    bool b = (param_1->mFlags[param_2 >> 5] & mask) != 0;
    if (b)
        return true;
    return false;
}