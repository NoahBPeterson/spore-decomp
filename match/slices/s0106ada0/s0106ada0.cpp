// s0106ada0 - SP::cSPUISpace seti / badge-window helper functions.
#include "types.h"

// ---------------------------------------------------------------------------
// generic vtable access
// ---------------------------------------------------------------------------
struct Vtbl { void* mSlots[0x120 / 4]; };

typedef void  (__thiscall *VFn_v)(void*);
typedef void* (__thiscall *VFn_p)(void*);
typedef char  (__thiscall *VFn_c)(void*);
typedef int   (__thiscall *VFn_i)(void*);
typedef float (__thiscall *VFn_f)(void*);
typedef void  (__thiscall *VFn_vi)(void*, int);
typedef void* (__thiscall *VFn_pi)(void*, int);
typedef char  (__thiscall *VFn_ci)(void*, int);
typedef void  (__thiscall *VFn_vii)(void*, int, int);
typedef void* (__thiscall *VFn_pii)(void*, int, int);
typedef void  (__thiscall *VFn_vp)(void*, void*);
typedef void* (__thiscall *VFn_pp)(void*, void*);
typedef void  (__thiscall *VFn_vpp)(void*, void*, void*);
typedef void  (__thiscall *VFn_vff)(void*, float, float);
typedef void  (__thiscall *VFn_vpp4)(void*, void*, void*, int, int, int);
typedef void  (__thiscall *VFn_vpp4f)(void*, void*, void*, float);

#define VSLOT(o, n) (((Vtbl*)*(void**)(o))->mSlots[(n) / 4])

// ---------------------------------------------------------------------------
// engine data
// ---------------------------------------------------------------------------
extern uint32_t DAT_015b9108;   // 0x015b9108
extern void*    DAT_01667bac;   // 0x01667bac  eastl::gEmptyString16
extern uint32_t DAT_01667bae;   // 0x01667bae

// ---------------------------------------------------------------------------
// free-function callees (targets are relocation-masked by the checker)
// ---------------------------------------------------------------------------
extern void* FUN_00805ea0(void* out);                                   // 0x805ea0 SPUIHelpers::GetMainWindowArea
extern void* FUN_01002bd0();                                            // 0x1002bd0 SP::SpaceGameGet
extern void* FUN_00b3d3d0();                                            // 0xb3d3d0
extern void* FUN_00b3d3f0(int a, int b);                                // 0xb3d3f0
extern void* FUN_00b3d3e0(int,int,int,int,int,int);                     // 0xb3d3e0 SP::EventLog
extern void* FUN_00a206f0();                                            // 0xa206f0 EA::Audio::GetSystemAT
extern void  FUN_00435ed0(int a, void* b);                              // 0x435ed0 SP::cSPUISpace::KillSetiEffects
extern void  FUN_00807cb0(void* a, void* b);                            // 0x807cb0
extern void* FUN_008099a0(void* a, int b, int c);                       // 0x8099a0 SPUIHelpers::BeginModal
extern void* FUN_0067cac0(int a, int b);                                // 0x67cac0
extern void* FUN_0067de30();                                            // 0x67de30 SP::PropertyManager
extern void  FUN_006a1360(void* prop, int key, void* out);              // 0x6a1360 SP::GetPropertyAsText
extern void  FUN_006a12a0(void* prop, int key, void* out);              // 0x6a12a0 SP::GetPropertyAsKeyInstance
extern void  FUN_00f47380(void* p);                                     // 0xf47380 operator_delete_array
extern void* FUN_00f473a0(int size, const char* name, int a, int b, void* alloc, int line);  // 0xf473a0 operator_new
extern void  FUN_00806230(void* res, void** out, int a, int b, int c);  // 0x806230 CreateImageFromResource2
extern void* FUN_0067dcd0();                                            // 0x67dcd0 EA::ResourceMan::GetManager
extern void* FUN_00a3b2c0(void* h, void* outIt, void* key);             // 0xa3b2c0 hashtable::find
extern void* FUN_009512c0();                                            // 0x9512c0
extern void* FUN_009512d0(int a, int b, const char* name, void* c);     // 0x9512d0
extern void* FUN_00c37230(void* a, void* b, void* c);                     // 0xc37230
extern void* FUN_00ffbe50(int a, int b);                                // 0xffbe50 SP::GetUFOSimulator
extern int   FUN_01021080();                                            // 0x1021080 SP::cSPLivingUniverse::GetUniverseContext
extern void* FUN_00b3d380();                                            // 0xb3d380 SP::GameTimeManager
extern void* FUN_01021240(void* a);                                     // 0x1021240
extern float FUN_010434e0(void* a);                                     // 0x10434e0
extern void  FUN_00572020(void* a, int b);                              // 0x572020
extern void  FUN_00434040(void* msg);                                   // 0x434040 XformMsg::XformMsg
extern void  FUN_00571d40(void* msg, void* cities);                     // 0x571d40
extern void* FUN_0067ddd0();                                            // 0x67ddd0 SP::EffectsManager
extern void* FUN_00b3d4d0();                                            // 0xb3d4d0 GetTriggerMgr

// ---------------------------------------------------------------------------
// thiscall member callees (receiver in ecx)
// ---------------------------------------------------------------------------
struct Engine {
    void* FUN_00e19350();                 // 0xe19350
    void* FUN_00bfc5f0();                 // 0xbfc5f0  cGameNounManager::GetPlayerTribe
    char  FUN_00fe3df0(int a);            // 0xfe3df0
    void* FUN_00fe54d0(int a);            // 0xfe54d0
    void* FUN_00fe5520(int a, int b, void* out);   // 0xfe5520 GetBadgeImageKey
    void  FUN_00fe4710(int a, void* out);          // 0xfe4710 GetBadgeName
    void  FUN_00fe4830(int a, void* out);          // 0xfe4830 GetBadgeHintActionString
    void  FUN_00fe49a0(int a, void* out);          // 0xfe49a0
    int   FUN_0067c420(int a, int b);              // 0x67c420 cUIHints::SetFlag
    char  FUN_0103a040();                          // 0x103a040
    void* FUN_0103a060();                          // 0x103a060
    void  FUN_01068230();                          // 0x1068230
    void* FUN_00e012b0(int id);                    // 0xe012b0 cSPUIGlobalUI::FindWindowByID
    void* FUN_00fe24c90(int item);                 // 0xe24c90 cSPUIPosse::FindItem
    void* FUN_00e259d0(void* arg);                 // 0xe259d0 cSPUIPosseItemSpace ctor
    char  FUN_00bb9fb0();                          // 0xbb9fb0
    void* FUN_00a1ad60();                          // 0xa1ad60 GetPlayerInventory
    float FUN_00ffbfd0();                          // 0xffbfd0 Simulator::cSpatialObject::GetMaxZ
    void  FUN_00c389c0(int a, int b);              // 0xc389c0
    char  FUN_00d09660();                          // 0xd09660
    void* FUN_005c65e0();                          // 0x5c65e0 SP::cCivData::GetCities
    void  FUN_00e01350();                          // placeholder holder, unused
};

// ---------------------------------------------------------------------------
// small local data objects
// ---------------------------------------------------------------------------
struct Node { Node* mNext; Node* mPrev; void* mData; };

struct Hashtable {
    uint32_t mPad00;        // +0x00
    int*     mpBuckets;     // +0x04
    uint32_t mBucketCount;  // +0x08
    int*     find(void* itOut, void* key);   // 0xa3b2c0  eastl hashtable find (thiscall)
};

struct BadgeHashNode { int mField00; int mValues[1]; };

struct ResourceDesc { void* mResource; uint32_t mKey; uint32_t mType; };

struct BadgeNameBuf {
    uint32_t mBegin;    // +0x00
    uint32_t mField04;  // +0x04
    uint32_t mEnd;      // +0x08
    uint32_t mField0c;  // +0x0c
    uint32_t mTag;      // +0x10
};

struct Vec4 { float mX; float mY; float mZ; float mW; };

struct MsgHeader { int mType; int mId; };

struct XformMsg { uint8_t mBytes[0x40]; };

// named views over engine objects whose own methods are reached through Engine
struct SpaceGame       { uint8_t mPad00[0x20]; void*    mOwner; };        // +0x20
struct GameTimeManager { uint8_t mPad00[0x48]; uint32_t mState; };        // +0x48
struct TriggerManager  { uint8_t mPad00[0x2c]; int      mMode; };         // +0x2c
struct GameNounManager { uint8_t mPad00[0xa0]; uint8_t  mHasSetiBadge; }; // +0xa0
struct ResourceList    { uint8_t mPad00[0x178]; uint8_t* mBegin; uint8_t* mEnd; }; // +0x178

// ---------------------------------------------------------------------------
// SP::cSPUISpace
// ---------------------------------------------------------------------------
struct cSPUISpace {
    uint8_t   mPad000[0x224];
    void*     mGlobalUI;            // +0x224
    uint8_t   mPad228[0x2a0 - 0x228];
    Hashtable mBadgeTable;          // +0x2a0
    uint8_t   mPad2ac[0x594 - 0x2ac];
    void*     mSetiEffect;          // +0x594
    uint8_t   mPad598[0x5b8 - 0x598];
    void*     mSetiId;              // +0x5b8
    void*     mSetiHandle;          // +0x5bc
    void*     mSetiFX;              // +0x5c0
    void*     mPosse;               // +0x5c4

    void FUN_0106ada0();
    void FUN_0106b220(void* badge);
    void ManageSeti(void* civ, int arg2);
    void FUN_0106b500(void* item);
    void FUN_0106b630();
    int  FUN_0106b9b0(int key, int index);
    void FUN_01068230();            // 0x1068230 thiscall callee used by ManageSeti
};

// ---------------------------------------------------------------------------
// 0x0106ada0 - rebuild the seti / badge window contents
// ---------------------------------------------------------------------------
// @ 0x0106ada0
void cSPUISpace::FUN_0106ada0()
{
    void* r = FUN_00b3d3f0(-0xc, (int)this->mSetiId);
    ((Engine*)r)->FUN_00e19350();

    void* tribe = ((Engine*)FUN_01002bd0())->FUN_00bfc5f0();

    void* mgr = FUN_00b3d3d0();
    char  ok  = ((Engine*)mgr)->FUN_0103a040();

    void* win = ((Engine*)this->mGlobalUI)->FUN_00e012b0(0x664c270);
    if (win == 0 || ok == 0)
        return;

    if (((Engine*)tribe)->FUN_00fe3df0((int)this->mSetiId) != 0)
        return;

    void* audio = FUN_00a206f0();
    void* audiofx = audio != 0 ? ((VFn_p)VSLOT(audio, 0x20))(audio) : 0;
    FUN_00435ed0(0xed858785, audiofx);

    Vec4 area;
    FUN_00805ea0(&area);
    float f = (area.mZ - area.mX) * 0.5f;
    Vec4* rect = (Vec4*)((VFn_p)VSLOT(win, 0x34))(win);
    f -= (rect->mZ - rect->mX) * 0.5f;
    Vec4* rect2 = (Vec4*)((VFn_p)VSLOT(win, 0x34))(win);
    ((VFn_vff)VSLOT(win, 0x64))(win, f, rect2->mY);

    void* child;
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d6, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 0);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d7, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 0);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d8, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 0);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d9, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 0);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9da, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 0);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d0, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 0);
    ((VFn_vii)VSLOT(win, 0x7c))(win, 1, 1);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x674aa78, 1); ((VFn_vii)VSLOT(child, 0x7c))(child, 1, 1);
    void* icon = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d4, 1); ((VFn_vii)VSLOT(icon, 0x7c))(icon, 1, 1);

    void* imgKey = 0;
    void* key = ((Engine*)tribe)->FUN_00fe5520((int)this->mSetiId, 0, &imgKey);
    FUN_00807cb0(icon, key);

    BadgeNameBuf name;
    name.mBegin   = (uint32_t)(int)&DAT_01667bac;
    name.mField04 = (uint32_t)(int)&DAT_01667bac;
    name.mTag     = DAT_01667bae;
    ((Engine*)tribe)->FUN_00fe4710((int)this->mSetiId, &name);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x664a9d3, 1);
    ((VFn_vi)VSLOT(child, 0x80))(child, (int)name.mBegin);

    ((Engine*)tribe)->FUN_00fe4830((int)this->mSetiId, &name);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x6779ee0, 1);
    ((VFn_vi)VSLOT(child, 0x80))(child, (int)name.mBegin);

    ((Engine*)tribe)->FUN_00fe49a0((int)this->mSetiId, &name);
    child = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x678cd68, 1);
    ((VFn_vi)VSLOT(child, 0x80))(child, (int)name.mBegin);

    FUN_008099a0(win, 0, 0);
    ((VFn_vi)VSLOT(win, 0x104))(win, (int)this);

    void* hints = FUN_0067cac0(0, 1);
    ((Engine*)hints)->FUN_0067c420(0, 1);

    for (int i = 0; i < 5; ++i) {
        if (!((Engine*)mgr)->FUN_0103a040())
            break;
        void* slot = ((Engine*)mgr)->FUN_0103a060();
        void* prop = 0;
        void* pmgr = FUN_0067de30();
        if (prop != 0) {
            void* t = prop; prop = 0;
            ((VFn_v)VSLOT(t, 4))(t);
        }
        ((VFn_vpp4)VSLOT(pmgr, 0x2c))(pmgr, slot, (void*)0x34d97fa, (int)&prop, 0, 0);
        if (prop != 0) {
            BadgeNameBuf str;
            FUN_006a1360(prop, 0x3068d95d, &str);
            void* c = ((VFn_pii)VSLOT(win, 0xf0))(win, i + 0x664a9d6, 1);
            ((VFn_vii)VSLOT(c, 0x7c))(c, 1, 1);
            ((VFn_vi)VSLOT(c, 0x80))(c, (int)str.mBegin);
            void* inst = 0;
            FUN_006a12a0(prop, 0x35d5cb4, &inst);
            void* r2 = FUN_00b3d3f0(-0xb, (int)inst);
            ((Engine*)r2)->FUN_00e19350();
            if (prop) {
                void* t = prop; prop = 0;
                ((VFn_v)VSLOT(t, 4))(t);
            }
        }
    }

    void* evt = FUN_00b3d3e0(0x2e7b3501, 0x131a9f54, 0, 0, 1, 0);
    ((Engine*)evt)->FUN_00fe49a0(0, 0);   // PostFeedbackEvent
    if (((name.mEnd - name.mBegin) & 0xfffffffeu) > 2 && name.mBegin != 0)
        FUN_00f47380((void*)(int)name.mBegin);
}

// ---------------------------------------------------------------------------
// 0x0106b220 - apply a new seti badge
// ---------------------------------------------------------------------------
// @ 0x0106b220
void cSPUISpace::FUN_0106b220(void* badge)
{
    void* tribe = ((Engine*)FUN_01002bd0())->FUN_00bfc5f0();
    char  haveEffect = ((Engine*)tribe)->FUN_00fe3df0((int)badge);
    void* fx = ((Engine*)tribe)->FUN_00fe54d0((int)badge);

    if (haveEffect == 0) {
        if (fx != 0) {
            void* emgr = FUN_0067ddd0();
            if (this->mSetiEffect != 0) {
                void* t = this->mSetiEffect; this->mSetiEffect = 0;
                ((VFn_v)VSLOT(t, 4))(t);
            }
            ((VFn_vpp4)VSLOT(emgr, 0x2c))(emgr, fx, (void*)0, (int)&this->mSetiEffect, 0, 0);
            if (this->mSetiEffect != 0)
                ((VFn_vi)VSLOT(this->mSetiEffect, 8))(this->mSetiEffect, 0);
        }
    } else {
        void* inv = ((Engine*)FUN_00ffbe50(4, 1))->FUN_00a1ad60();
        ((Engine*)inv)->FUN_00c389c0(4, 1);
    }

    void* inv2 = ((Engine*)FUN_00ffbe50(6, 1))->FUN_00a1ad60();
    ((Engine*)inv2)->FUN_00c389c0(6, 1);

    this->mSetiId = badge;
    if (haveEffect == 0 && fx == 0)
        this->FUN_0106ada0();
    *(uint8_t*)((char*)tribe + 0xa0) = 1;
}

// ---------------------------------------------------------------------------
// 0x0106b310 - SP::cSPUISpace::ManageSeti
// ---------------------------------------------------------------------------
// @ 0x0106b310
void cSPUISpace::ManageSeti(void* civ, int arg2)
{
    (void)arg2;

    if (FUN_01021080() != 2) {
        this->FUN_01068230();
        return;
    }
    void* inv = ((Engine*)FUN_01002bd0())->FUN_00a1ad60();
    if (((VFn_ci)VSLOT(inv, 0x74))(inv, 0x16e2368) == 0) {
        this->FUN_01068230();
        return;
    }
    if ((((GameTimeManager*)FUN_00b3d380())->mState >> 1) & 1) {
        this->FUN_01068230();
        return;
    }

    if (civ != 0) {
        float z    = FUN_010434e0(FUN_01021240(((Engine*)civ)->FUN_005c65e0()));
        float maxz = ((Engine*)FUN_00ffbe50(0, 0))->FUN_00ffbfd0();
        if (maxz >= z) {
            char  ok = ((Engine*)civ)->FUN_00bb9fb0();
            void* h  = this->mSetiHandle;
            void* audio = FUN_00a206f0();
            bool  playing = false;
            if (audio != 0)
                playing = ((VFn_ci)VSLOT(audio, 0x28))(audio, (int)h) != 0;
            if (!playing) {
                void* p = audio != 0 ? ((VFn_p)VSLOT(audio, 0x20))(audio) : 0;
                int msg = ok != 0 ? 0x40ffb740 : 0x61fcea3d;
                this->mSetiHandle = p;
                FUN_00435ed0(msg, p);
            }
            if (ok != 0 && this->mSetiFX == 0) {
                void* emgr = FUN_0067ddd0();
                if (this->mSetiFX != 0) {
                    void* t = this->mSetiFX; this->mSetiFX = 0;
                    ((VFn_v)VSLOT(t, 4))(t);
                }
                ((VFn_vpp4)VSLOT(emgr, 0x2c))(emgr, (void*)0x28115ab8, (void*)0, (int)&this->mSetiFX, 0, 0);
                if (this->mSetiFX != 0) {
                    XformMsg msg;
                    FUN_00434040(&msg);
                    FUN_00571d40(&msg, ((Engine*)civ)->FUN_005c65e0());
                    ((VFn_vp)VSLOT(this->mSetiFX, 0x14))(this->mSetiFX, &msg);
                    ((VFn_vi)VSLOT(this->mSetiFX, 8))(this->mSetiFX, 0);
                }
            }
            return;
        }
    }

    // ---- shared tail --------------------------------------------------------
    void* h = this->mSetiHandle;
    void* audio = FUN_00a206f0();
    if (audio != 0 && ((VFn_ci)VSLOT(audio, 0x28))(audio, (int)h) != 0) {
        FUN_00572020(h, 1);
        void* sys = FUN_00a206f0();
        void* v = sys != 0 ? ((VFn_p)VSLOT(sys, 0x20))(sys) : 0;
        FUN_00435ed0(0x17b6fd56, v);
    }
    this->FUN_01068230();
}

// ---------------------------------------------------------------------------
// 0x0106b500 - add a posse item
// ---------------------------------------------------------------------------
// @ 0x0106b500
void cSPUISpace::FUN_0106b500(void* item)
{
    if (this->mPosse == 0)
        return;
    if (((Engine*)this->mPosse)->FUN_00fe24c90((int)item) != 0)
        return;

    void* found = ((Engine*)this->mPosse)->FUN_00fe24c90(0);
    while (found != 0) {
        ((VFn_vii)VSLOT(this->mPosse, 0xa8))(this->mPosse, (int)found, 1);
        found = ((Engine*)this->mPosse)->FUN_00fe24c90(0);
    }

    void* res   = FUN_009512c0();
    void* p     = FUN_009512d0(0x14c, 4, "UI/PosseItem", res);
    void* space = p != 0 ? ((Engine*)p)->FUN_00e259d0(item) : 0;
    ((VFn_vi)VSLOT(this->mPosse, 0xa4))(this->mPosse, (int)space);
    ((VFn_vi)VSLOT(this->mPosse, 0xc0))(this->mPosse, 1);

    uint32_t handle[3];
    handle[0] = 0;
    handle[1] = 0;
    handle[2] = 0;
    FUN_00c37230(space, handle, &space);

    uint32_t resHandle[2];
    resHandle[0] = 0;
    resHandle[1] = 0x2f7d0004;
    void* img = 0;
    FUN_00806230(resHandle, &img, 0, -1, -1);
    if (img != 0) {
        ((VFn_vii)VSLOT(space, 0x94))(space, (int)img, 0);
        if (img != 0)
            ((VFn_v)VSLOT(img, 4))(img);
    }
}

// ---------------------------------------------------------------------------
// 0x0106b630 - refresh the seti badge window
// ---------------------------------------------------------------------------
// @ 0x0106b630
void cSPUISpace::FUN_0106b630()
{
    ((Engine*)FUN_00b3d3d0())->FUN_0103a040();
    void* win = ((Engine*)this->mGlobalUI)->FUN_00e012b0(0x664c270);

    if (this->mSetiEffect != 0) {
        void* fx = this->mSetiEffect;
        char alive = ((VFn_c)VSLOT(fx, 0x10))(fx);
        if (alive == 0) {
            void* game = FUN_01002bd0();
            if (((Engine*)((SpaceGame*)game)->mOwner)->FUN_00d09660() == 0) {
                int state = ((TriggerManager*)FUN_00b3d4d0())->mMode;
                if (state != 1 && state != 2) {
                    if (this->mSetiEffect != 0) {
                        void* t = this->mSetiEffect; this->mSetiEffect = 0;
                        ((VFn_v)VSLOT(t, 4))(t);
                    }
                    if (this->mSetiId != 0) {
                        this->FUN_0106ada0();
                        this->mSetiId = 0;
                    }
                }
            }
        }
    }

    void* tribe = ((Engine*)FUN_01002bd0())->FUN_00bfc5f0();
    if (((GameNounManager*)tribe)->mHasSetiBadge == 0)
        return;

    void* panel = ((VFn_pii)VSLOT(win, 0xf0))(win, 0x674aa78, 1);
    if (panel != 0) {
        void* inner = ((VFn_p)VSLOT(panel, 0x14))(panel);
        MsgHeader hdr;
        hdr.mId = 0;
        hdr.mType = 0x10002;
        ((VFn_vpp4)VSLOT(inner, 0x10))(inner, panel, (void*)&hdr, 0, 0, 0);
    }
    if (this->mSetiEffect != 0)
        return;
    if (((VFn_i)VSLOT(win, 0x28))(win) & 1)
        return;

    void* tribe2 = ((Engine*)FUN_01002bd0())->FUN_00bfc5f0();
    ((GameNounManager*)tribe2)->mHasSetiBadge = 0;
    FUN_008099a0(win, 0, 0);
    void* hints = FUN_0067cac0(1, 1);
    ((Engine*)hints)->FUN_0067c420(1, 1);

    void* audio = FUN_00a206f0();
    void* value = audio ? ((VFn_p)VSLOT(audio, 0x20))(audio) : 0;

    void* sys = FUN_00a206f0();
    if (sys == 0)
        return;
    ((VFn_vi)VSLOT(sys, 0x38))(sys, 0x3475365);
    ((VFn_vii)VSLOT(sys, 0x40))(sys, 0x3475381, 0x67687b73);
    ((VFn_vii)VSLOT(sys, 0x40))(sys, 0x3475385, (int)value);
    ((VFn_v)VSLOT(sys, 0x58))(sys);
}

// ---------------------------------------------------------------------------
// 0x0106b7e0 - attach an image resource to a window
// ---------------------------------------------------------------------------
// @ 0x0106b7e0
char __stdcall FUN_0106b7e0(void* self, void* icon)
{
    if (self == 0)
        return 0;
    void* w = ((VFn_p)VSLOT(self, 0xa8))(self);
    if (w == 0)
        return 0;
    void* h = ((VFn_pi)VSLOT(w, 0x0c))(w, 0xef3c47cf);
    if (h == 0)
        return 0;
    void* img = 0;
    FUN_00806230(icon, &img, 0, -1, -1);
    if (img == 0)
        return 0;
    ((VFn_vp)VSLOT(h, 0x14))(h, img);
    if (img != 0)
        ((VFn_v)VSLOT(img, 4))(img);
    return 1;
}

// ---------------------------------------------------------------------------
// 0x0106b860 - count empty tribe resources of a type
// ---------------------------------------------------------------------------
// @ 0x0106b860
int FUN_0106b860(void* res)
{
    int count = 3;
    if (res == 0)
        return count;

    ResourceDesc desc;
    desc.mResource = res;
    desc.mKey      = 0x366a930d;
    desc.mType     = DAT_015b9108;

    void* out = 0;
    void* mgr = FUN_0067dcd0();
    if (out != 0) {
        void* t = out; out = 0;
        ((VFn_v)VSLOT(t, 4))(t);
    }
    ((VFn_vpp4)VSLOT(mgr, 0x0c))(mgr, &desc, (void*)&out, 0, 0, 0);

    if (out != 0) {
        void* list = ((VFn_pi)VSLOT(out, 0x0c))(out, 0xe742574a);
        if (list != 0) {
            ResourceList* rl = (ResourceList*)list;
            int n = (int)(rl->mEnd - rl->mBegin) / 0x38;
            int empty = 0;
            if (n > 0) {
                uint8_t* p = rl->mBegin + 0x20;
                do {
                    if (*p == 0)
                        ++empty;
                    p += 0x38;
                } while (--n);
                if (empty < count)
                    count = empty;
            }
        }
        if (out != 0) {
            void* t = out; out = 0;
            ((VFn_v)VSLOT(t, 4))(t);
        }
    }
    return count;
}

// ---------------------------------------------------------------------------
// 0x0106b950 - insert a copy of a node range into a list
// ---------------------------------------------------------------------------
// @ 0x0106b950
void __stdcall FUN_0106b950(Node* head, Node* begin, Node* end, int unused)
{
    (void)unused;
    for (; begin != end; begin = begin->mNext) {
        Node* n = (Node*)FUN_00f473a0(0xc, "Simulator", 0, 0, (void*)0x13ebb38, 0xd1);
        if (&n->mData != 0)
            n->mData = begin->mData;
        n->mNext = head;
        n->mPrev = head->mPrev;
        head->mPrev->mNext = n;
        head->mPrev = n;
    }
}

// ---------------------------------------------------------------------------
// 0x0106b9b0 - look up a badge-table entry by id
// ---------------------------------------------------------------------------
// @ 0x0106b9b0
int cSPUISpace::FUN_0106b9b0(int key, int index)
{
    Hashtable* h = &this->mBadgeTable;
    uint32_t it[2];
    int result = 0x1002;
    int* found = h->find(it, &key);
    int v = *found;
    if (h->mpBuckets[h->mBucketCount] != v)
        result = ((BadgeHashNode*)(int)v)->mValues[index];
    return result;
}