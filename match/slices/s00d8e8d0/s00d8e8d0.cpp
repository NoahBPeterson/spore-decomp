// Decompiled from SporeApp.exe (gold6 batch, worker 33).
// Slice s00d8e8d0: behaviour-tree action implementations for the creature
// "tribe baby play" tick, the locating-call tick, its deactivate handler and
// two decision helpers (ally-in-need-fight and a nearby-object picker).

typedef unsigned int  u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------
// Shared external helpers (all __cdecl free functions unless noted).
// ---------------------------------------------------------------------------
extern "C" void* __cdecl FUN_00b3d240();
extern "C" void  __cdecl FUN_00b3d4c0();
extern "C" void  __cdecl FUN_00b3d4e0(void* a, int b);
extern "C" void* __cdecl FUN_00bc7610(void* a, int b);
extern "C" int   __cdecl FUN_00c6acc0b();
extern "C" void* __cdecl FUN_00bc30b0(void* a);
extern "C" bool  __cdecl FUN_00c0b7a0b();
extern "C" bool  __cdecl FUN_00c0b780b();
extern "C" void  __cdecl FUN_00c072f0(void* a);
extern "C" void* __cdecl FUN_00ac80d0(u32 a);
extern "C" int   __cdecl FUN_00d99980(void* a);
extern "C" void* __cdecl FUN_00d999d0(u32 a);
extern "C" float __cdecl FUN_00d99ac0(void* a, void* b, int c);
extern "C" void* __cdecl FUN_00b3d300();
extern "C" void  __cdecl FUN_007a41a0b();
extern "C" bool  __cdecl FUN_0041dd30(void* a, void* b);
extern "C" bool  __cdecl FUN_004232c0(void* a, void* b);
extern "C" int   __cdecl FUN_00a1ad10();
extern "C" int   __cdecl FUN_00d39f70(u32 tag, void* out);
extern "C" int   __cdecl FUN_00d39dc0(u32 tag, void* out);
extern "C" void  __cdecl FUN_00d7a070(void* a, void* b);
extern "C" void  __stdcall FUN_00bf3420(void* a);
extern "C" void* __cdecl FUN_00bc9b00(u32 id, void* fn, void* arg);
extern "C" void* __cdecl FUN_00d38840();
extern "C" void* __cdecl FUN_00d40b40(int a);
extern "C" void  __cdecl op_del_array(void* p);

// ---------------------------------------------------------------------------
// Random generator singleton at 0x01601760.
// ---------------------------------------------------------------------------
struct RandomLCG {
    u32    UniformU32(u32 n);            // 0x00a68fb0
    double UniformDouble();              // 0x009360d0
};

// ---------------------------------------------------------------------------
// Behaviour tree / stimulus interfaces.
// ---------------------------------------------------------------------------
struct BehaviorStimuli {
    u32   mnStimulusID;      // +0x00
    u32   mn04;              // +0x04
    u8    mPad08[0x10];      // +0x08
    void* mp18;              // +0x18
    void* mp1C;              // +0x1c

    void GetAny();           // 0x00d997e0
};

struct BehaviorTree {
    int  Play(u32 flags, u32 arg);                    // 0x00bc96a0
    void Stim(u32 a, u32 b, float value, void* self); // 0x00bc97f0
    void ClearAll(u32 flags, u32 value);              // 0x00bc98f0
};

struct OrderManager {
    int  FindNode(u32 id, void* fn, void* arg);                       // 0x00bca620
    void Activate(int a, int b, void* c, float f, void* p, void* q);  // 0x00bca810
    int  FindSlot(int a, int b, int c, int d);                        // 0x00bca0c0
    void DeactivateSlot(int slot);                                    // 0x00bca040
};

struct BehaviorData {
    u8     mPad000[0x184];   // +0x000
    void** mpBegin;          // +0x184
    void** mpEnd;            // +0x188
    u8     mPad18C[0x4c];    // +0x18c
    u32    mn1D8;            // +0x1d8
    u32    mn1DC;            // +0x1dc
};

// One indexed block inside a BehaviorData: the child-object vector starts at
// byte 0x160 of the block, its begin/end pointers at +0x24/+0x28.
struct BtChild {
    u8     mPad00[0x24];     // +0x00
    void** mpBegin;          // +0x24
    void** mpEnd;            // +0x28
};

// ---------------------------------------------------------------------------
// Creature (cSPCreatureBase).  Only the fields this slice touches are named.
// ---------------------------------------------------------------------------
struct cCreature;

struct CreatureContext {                 // object returned by cCreature::Get()
    u8           mPad000[0x15c];  // +0x000
    u32          mn15C;           // +0x15c
    u8           mPad160[4];      // +0x160
    cCreature*   mp164;           // +0x164
    void*        mp168;           // +0x168
    u8           mPad16C[0x44];   // +0x16c

    void* GetPosition();          // 0x00c6acc0
};

struct Herd {
    void* GetPosition();          // 0x00c6acc0
};

struct TimeOfDay {
    int Get();                    // 0x00bc2b80
};

struct DramaMgr {
    void Trigger();               // 0x00d4d790
};

struct cCreature {
    void*          mpVftable;      // +0x000
    u8             mPad004[0x09c]; // +0x004
    u32            mn0A0;          // +0x0a0
    u8             mPad0A4[4];     // +0x0a4
    float          mf0A8;          // +0x0a8
    u8             mPad0AC[0x14];  // +0x0ac
    u8             mSpatial[0x40]; // +0x0c0
    u8             mPad100[0xa20]; // +0x100
    void*          mpB20;          // +0xb20 (interaction target object)
    u8             mPadB24[0x24];  // +0xb24
    OrderManager*  mpOrderMgr;     // +0xb48
    BehaviorData*  mpBt;           // +0xb4c
    u8             mPadB50[8];     // +0xb50
    u32            mnFlags;        // +0xb58
    u8             mPadB5C[2];     // +0xb5c
    u8             mbB5E;          // +0xb5e
    u8             mPadB5F[0x21];  // +0xb5f
    float          mfTurnRate;     // +0xb80
    u8             mPadB84[0x40c]; // +0xb84
    u8             mbF90;          // +0xf90

    // thiscall helpers (resolved by the linker).
    void             FUN_c196a0(void* a, u32 b, u32 c);          // 0x00c196a0
    u32              InterruptAnimation(u32 guid, int a, u32 b); // 0x00c12310
    u8               AnimationFinished(u32 anim);                // 0x00c12400
    double           GetTime();                                  // 0x00c0e480
    void*            GetCurrentAnimationGUID();                  // 0x00c0e040
    void             PlayAnimation(u32 guid, int a, u32 b);      // 0x00c11e90
    void             SetStealthed(int a, int b);                 // 0x00c1aed0
    void             CreateBodyEffect(void* a, u32 b, u32 c);    // 0x00c1b0c0
    CreatureContext* Get();                                      // 0x00c04590
    void*            Drama();                                    // 0x00d51660
    void*            Drama(int a, int b);                        // 0x00d51660
    cCreature*       GetTargetAsCreature();                      // 0x00c0ee70
    u32*             FUN_c0bc00();                               // 0x00c0bc00
    bool             Flag388();                                  // 0x00c0c0e0
    bool             FUN_c0bb90();                               // 0x00c0bb90
    bool             FUN_c0b810(void* a);                        // 0x00c0b810
    bool             FUN_c0b770();                               // 0x00c0b770
    bool             FUN_c0b7a0();                               // 0x00c0b7a0
    bool             FUN_c0b780();                               // 0x00c0b780
    void*            FUN_c0c1a0();                               // 0x00c0c1a0
    bool             FUN_c0e8d0(void* a, int b);                 // 0x00c0e8d0
    void             FUN_c15150(void* a, int b);                 // 0x00c15150
};

// Tuning / profile object returned by vtable slot 0xb4 of a creature.
struct TuningProfile {
    u8     mPad00[8];        // +0x00
    u32    mnType;           // +0x08
    u8     mPad0C[0x3c];     // +0x0c
    void** mpItemBegin;      // +0x48
    void** mpItemEnd;        // +0x4c
    u8     mPad50[0x50];     // +0x50
    float  mfA0;             // +0xa0
    u8     mPadA4[4];        // +0xa4
    float  mfA8;             // +0xa8
    u8     mPadAC[0x48];     // +0xac
    float  mfF4;             // +0xf4

    u32 GetAt(u32 index);    // 0x004d3cd0
};

// Spatial-object vector with an inline 8-pointer buffer.
struct SpatialVec {
    void** mpBegin;          // +0x00
    void** mpEnd;            // +0x04
    void** mpCap;            // +0x08
    void Destroy();          // 0x00ad92d0
};

// eastl::fixed_vector<int,16> local.
struct IntVec16 {
    int* mpBegin;            // +0x00
    int* mpEnd;              // +0x04
    int* mpCap;              // +0x08
    int  mInline[16];        // +0x0c

    void push_back(int value); // 0x00422380
    void Release();            // 0x007a41a0
};

struct Stock {
    void** mpBegin;
    void** mpEnd;
};

struct NodeQuery {
    void*      mpTarget;     // watched object + 0x5a8, or null
    cCreature* mpSelf;       // creature running the decide
};

// ---------------------------------------------------------------------------
// Per-action state blocks.
// ---------------------------------------------------------------------------
struct TickStatePlay {       // FUN_00d8e8d0 state
    void* mpOwner;           // +0x00
    u32   mnPhase;           // +0x04
    u32   mnAnim;            // +0x08
};

struct TickStateLocate {     // LOCATING_CALL_Tick state
    u32   mnPhase;           // +0x00
    u32   mn04;              // +0x04
    float mf08;              // +0x08
    float mf0C;              // +0x0c
    float mf10;              // +0x10
    u32   mn14;              // +0x14
    u8    mPad18[4];         // +0x18
    u8    mb1C;              // +0x1c
    u8    mPad1D[3];         // +0x1d
    u32   mn20;              // +0x20
    u32   mn24;              // +0x24
    u32   mn28;              // +0x28
    u8    mPad2C[0x14];      // +0x2c
    u32   mn40;              // +0x40
    u32   mn44;              // +0x44
    u32   mn48;              // +0x48
    u8    mPad4C[0x0c];      // +0x4c
    u32   mn58;              // +0x58
    u32   mn5C;              // +0x5c
    u32   mn60;              // +0x60
    u8    mPad64[0x0c];      // +0x64
    float mf70;              // +0x70
    float mf74;              // +0x74
    float mf78;              // +0x78
};

struct TickStateRelease {    // FUN_00d8f170 state
    u8          mPad00[0x0c]; // +0x00
    void*       mp0C;         // +0x0c
    void*       mp10;         // +0x10
    cCreature*  mp14;         // +0x14
    u32         mn18;         // +0x18
};

// ===========================================================================
// 0x00d8e8d0 -- SP::TRIBE_BABY_PLAY_Tick
// ===========================================================================
// @ 0x00d8e8d0
bool __cdecl FUN_00d8e8d0(cCreature* c, u32 a2, u32 a3, u32 a4, u32 a5,
                          TickStatePlay* st)
{
    if (st->mnPhase == 0) {
        TuningProfile* prof = (TuningProfile*)
            ((u32(__fastcall*)(cCreature*, void*))(*(void***)c)[0xb4 / 4])(c, st->mpOwner);
        c->FUN_c196a0(st->mpOwner, 1, 0);

        int count = (int)((char*)prof->mpItemEnd - (char*)prof->mpItemBegin) >> 2;
        u32 pick;
        if (count > 0)
            pick = ((RandomLCG*)0x01601760)->UniformU32((u32)count);
        else
            pick = 0;
        u32 guid = prof->GetAt(pick);
        st->mnAnim = c->InterruptAnimation(guid, -1, 0);
        st->mnPhase = 2;

        SpatialVec vec;
        void* inlineBuf[8];
        vec.mpBegin = (void**)inlineBuf;
        vec.mpEnd   = (void**)inlineBuf;
        vec.mpCap   = (void**)inlineBuf + 8;

        u32 kind = prof->mnType;
        if (kind == 0x31 || kind == 0x32) {
            FUN_00b3d4c0();
            u32* holder = (u32*)FUN_00b3d240();
            void* mgr = (void*)*holder;
            float radius = prof->mfF4 + prof->mfA8;
            u32 handle = ((u32(__fastcall*)(void*, float, SpatialVec*, int, void*, cCreature*))
                          (*(void***)c->mSpatial)[0x2c / 4])(c->mSpatial, radius, &vec,
                                                            0, (void*)0x00d9a9c0, c);
            ((void(__fastcall*)(void*, u32))(*(void***)mgr)[0x48 / 4])(mgr, handle);

            u32 n = (u32)(vec.mpEnd - vec.mpBegin);
            for (u32 i = 0; i < n; ++i) {
                void* sp = vec.mpBegin[i];
                if (sp == 0)
                    continue;
                cCreature* cr = (cCreature*)
                    ((void*(__fastcall*)(void*, u32))(*(void***)sp)[0xb8 / 4])(sp, 0xd0036e08);
                if (cr == 0)
                    continue;

                if (kind == 0x31) {
                    if (((u8(__fastcall*)(void*))(*(void***)cr->mSpatial)[0x58 / 4])(cr->mSpatial))
                        continue;
                    if (cr->mbB5E != 0)
                        continue;
                    if (cr->mpB20 == c->mpB20)
                        continue;
                    if (cr->Flag388())
                        continue;
                    ((BehaviorTree*)((char*)cr->mpBt + 8))->Stim(0, 0x4000000, 3.402823466e38F, c);
                    cr->mpOrderMgr->Activate(1, 1, 0, prof->mfA0, 0, cr);
                    ((BehaviorTree*)((char*)cr->mpBt + 8))->ClearAll(0x400, 0);
                    int slot = cr->mpOrderMgr->FindSlot(2, 1, 0, 0);
                    if (slot != -1)
                        cr->mpOrderMgr->DeactivateSlot(slot);
                } else {
                    if (((u8(__fastcall*)(void*))(*(void***)cr->mSpatial)[0x58 / 4])(cr->mSpatial) == 0 &&
                        cr->mbB5E == 0 &&
                        cr->mpB20 != c->mpB20 &&
                        cr->Flag388() == 0) {
                        ((BehaviorTree*)((char*)cr->mpBt + 8))->Stim(0, 0x4000000, 3.402823466e38F, c);
                        ((BehaviorTree*)((char*)cr->mpBt + 8))->Stim(0x400000, 0, 3.402823466e38F, c);
                        ((BehaviorTree*)((char*)cr->mpBt + 8))->Stim(0, 0x10000, 5.0f, c);
                        FUN_00d7a070(cr, c->mpB20);
                        float tmp = 0.0f;
                        cr->mpOrderMgr->Activate(2, 1, 0, 3.402823466e38F, &tmp, cr);
                        ((BehaviorTree*)((char*)cr->mpBt + 8))->ClearAll(0x400, 0);
                        int slot = cr->mpOrderMgr->FindSlot(1, 1, 0, 0);
                        if (slot != -1)
                            cr->mpOrderMgr->DeactivateSlot(slot);
                    } else if (cr->mpB20 == c->mpB20) {
                        ((BehaviorTree*)((char*)cr->mpBt + 8))->Stim(0, 0x10000, 5.0f, 0);
                        FUN_00d7a070(cr, 0);
                    }
                }
            }
            vec.Destroy();
            return true;
        }

        if (kind - 0x33 == 0) {
            DramaMgr* drama = (DramaMgr*)c->Drama(8, 0);
            drama->Trigger();
        }
        vec.Destroy();
        return true;
    }

    if (st->mnPhase == 2) {
        if (c->AnimationFinished(st->mnAnim))
            st->mnPhase = 3;
        return true;
    }
    if (st->mnPhase == 3)
        return false;
    return true;
}

// ===========================================================================
// 0x00d8ed40 -- SP::LOCATING_CALL_Tick
// ===========================================================================
// @ 0x00d8ed40
u32 __cdecl SP_LOCATING_CALL_Tick(cCreature* c, u32 a2, u32 a3, u8 flags,
                                  u32 a5, TickStateLocate* st)
{
    u32 handle = ((u32(__fastcall*)(void*))(*(void***)c->mSpatial)[0x2c / 4])(c->mSpatial);
    u32 phase = st->mnPhase;

    if (phase == 0) {
        if ((c->mnFlags >> 9 & 1) == 0)
            ((void(__fastcall*)(void*))(*(void***)c->mSpatial)[0xec / 4])(c->mSpatial);

        if (st->mb1C != 0) {
            st->mn14 = 0xe1b24ddb;
            c->CreateBodyEffect((void*)st->mn04, 0xe1b24ddb, 0xe1b24ddb);
        }

        st->mnPhase = 1;
        c->InterruptAnimation(0x265d18b, -1, 0);
        c->PlayAnimation(0x265d18c, 1, -1);
        return 1;
    }

    if (phase == 1) {
        c->GetTime();
        c->SetStealthed(0, 0);
        void* drama = c->Drama();
        float now = (float)c->GetTime();
        if (0.1f < now - st->mf10) {
            SpatialVec vec;
            u8 buf[1024];
            vec.mpBegin = (void**)buf;
            vec.mpEnd   = (void**)buf;
            vec.mpCap   = (void**)(buf + 1024);

            u32* holder = (u32*)FUN_00b3d240();
            void* mgr = (void*)*holder;
            ((void(__fastcall*)(void*, u32, float, SpatialVec*, int, int, int))
             (*(void***)mgr)[0x48 / 4])(mgr, handle, c->mfTurnRate, &vec, 0, 0, 0);

            u32 n0 = st->mn20, n1 = (st->mn28 - st->mn24) >> 2;
            u32 n2 = st->mn40, n3 = (st->mn48 - st->mn44) >> 2;
            u32 n4 = st->mn58, n5 = (st->mn60 - st->mn5C) >> 2;

            u32 count = (u32)(vec.mpEnd - vec.mpBegin);
            for (u32 i = 0; i < count; ++i) {
                void* sp = vec.mpBegin[i];
                if (sp == 0)
                    continue;
                cCreature* cr = (cCreature*)
                    ((void*(__fastcall*)(void*, u32))(*(void***)sp)[0xb8 / 4])(sp, 0xd0036e08);
                if (cr == 0 || cr == c)
                    continue;

                u32* pa = c->FUN_c0bc00();
                u32* pb = cr->FUN_c0bc00();
                if ((pa[0] == pb[0] && pa[1] == pb[1] &&
                     (pa[2] == pb[2] && (n1 != n0))) ||
                    (n3 != n2 || n5 != n4)) {
                    ((BehaviorTree*)((char*)cr->mpBt + 8))->Stim(0x800, 0, 0.5f, c);
                }
            }

            if ((c->mnFlags >> 9 & 1) != 0 && drama != 0) {
                int x = FUN_00a1ad10();
                if (x == 0) {
                    if (c->FUN_c0b770())
                        *(float*)((char*)drama + 0x3c) = 0.0f;
                } else {
                    ((BehaviorTree*)((char*)c->mpBt + 8))->Stim(0x800, 0, 2.0f, c);
                }
            }

            st->mf10 = (float)c->GetTime();
            vec.Destroy();
        }

        void* strategy = FUN_00d38840();
        if ((c->mnFlags >> 9 & 1) != 0 && st->mb1C != 0 && strategy != 0 &&
            (flags & 8) != 0) {
            Herd* herd = (Herd*)FUN_00d40b40(0);
            void* pos = herd->GetPosition();
            u32 src[3];
            src[0] = ((u32*)pos)[0];
            src[1] = ((u32*)pos)[1];
            src[2] = ((u32*)pos)[2];
            if (FUN_0041dd30(src, (void*)0x0169f03c)) {
                if (FUN_004232c0(&st->mf70, (void*)0x0169f03c)) {
                    float vis[3];
                    vis[0] = 0.0f;
                    vis[1] = 0.0f;
                    vis[2] = 0.0f;
                    void* res = ((void*(__fastcall*)(void*, void*, void*, float))
                                 (*(void***)strategy)[0x00 / 4])(strategy, vis, &st->mf70, 30.0f);
                    st->mf70 = ((float*)res)[0];
                    st->mf74 = ((float*)res)[1];
                    st->mf78 = ((float*)res)[2];
                }
                if (st->mf0C * 0.45f + st->mf08 < (float)c->GetTime() &&
                    ((st->mn28 - st->mn24) & 0xfffffffc) == 0) {
                    FUN_00d39f70(0x2f5e1db4, &st->mf70);
                }
                u32 tag = (*(u32*)((char*)c->mpB20 + 0x618) == 0) ? 0x4b6d9fa0 : 0xdf70858a;
                FUN_00d39dc0(tag, &st->mf70);
            }
        }

        float now2 = (float)c->GetTime();
        if (st->mf0C + st->mf08 < now2 ||
            (c->GetCurrentAnimationGUID() != (void*)0x265d18c &&
             c->GetCurrentAnimationGUID() != (void*)0x265d18b)) {
            st->mnPhase = 2;
            ((BehaviorTree*)((char*)c->mpBt + 8))->ClearAll(0x800, 0);
            return 1;
        }
        return 1;
    }

    if (phase == 2 && c->AnimationFinished(0)) {
        st->mnPhase = 3;
        c->PlayAnimation(0x265d18d, 1, -1);
        return 0;
    }
    return 1;
}

// ===========================================================================
// 0x00d8f170 -- SP::LOCATING_CALL_RESPOND_Deactivate
// ===========================================================================
// @ 0x00d8f170
void __cdecl FUN_00d8f170(cCreature* c, u32 a2, u32 a3, u32 a4, u32 a5,
                          TickStateRelease* st)
{
    c->mpOrderMgr->DeactivateSlot(st->mn18);

    if (st->mp10 != 0) {
        c->FUN_c15150(st->mp0C, 0);
        void* obj = st->mp10;
        if (obj != 0) {
            st->mp10 = 0;
            ((void(__fastcall*)(void*))(*(void***)obj)[1])(obj);
        }
    }

    if (st->mp14 != 0) {
        BehaviorData* bt = st->mp14->mpBt;
        if (bt != 0 && bt->mn1D8 == 0x2d852ed) {
            int idx = (int)bt->mn1DC * 0xac;
            BtChild* child = (BtChild*)((char*)bt + idx + 0x160);
            if (child->mpBegin != child->mpEnd) {
                void** it = child->mpBegin;
                do {
                    if ((cCreature*)*it == c)
                        break;
                    ++it;
                } while (it != child->mpEnd);
                if (it != child->mpEnd)
                    FUN_00bf3420(it);
            }
        }
    }

    void* guid = c->GetCurrentAnimationGUID();
    if (guid == (void*)0x265d18b || c->GetCurrentAnimationGUID() == (void*)0x265d18c)
        c->PlayAnimation(0x265d18d, 1, -1);

    if (st->mp10 != 0)
        ((void(__fastcall*)(void*))(*(void***)st->mp10)[1])(st->mp10);
}

// ===========================================================================
// 0x00d8f250 -- SP::ALLY_IN_NEED_FIGHT_Decide
// ===========================================================================
// @ 0x00d8f250
float __cdecl SP_ALLY_IN_NEED_FIGHT_Decide(cCreature* c, u32 a2, u32 a3, u32 a4,
                                           BehaviorStimuli* bs, u8* out)
{
    int stim = ((BehaviorTree*)((char*)c->mpBt + 8))->Play(0x200, 0);
    if (stim == 0)
        return 0.0f;

    cCreature* animal = (cCreature*)FUN_00d99980((void*)stim);
    int kind = *(int*)((char*)stim + 0x14);
    if (animal == 0 || *(int*)((char*)stim + 0x0c) != 1)
        return 0.0f;

    void* watched = *(void**)((char*)stim + 0x10);
    if (watched == 0) {
        u32 anim = ((BehaviorTree*)((char*)animal->mpBt + 8))->Play(0x400, 0);
        watched = FUN_00d999d0(anim);
        if (watched != 0) {
            u8 hidden = ((u8(__fastcall*)(void*))(*(void***)((char*)watched + 0xc0))[0x58 / 4])
                            ((char*)watched + 0xc0);
            if (hidden != 0 && (a4 & 0x6000000) != 0)
                return 0.0f;
        }
    } else {
        u8 hidden = ((u8(__fastcall*)(void*))(*(void***)((char*)watched + 0xc0))[0x58 / 4])
                        ((char*)watched + 0xc0);
        if (hidden != 0 && (a4 & 0x6000000) != 0)
            return 0.0f;
    }

    {
        CreatureContext* ctx = c->Get();
        if (watched == 0 || *(u8*)((char*)watched + 0xb5e) != 0)
            return 0.0f;
        if (ctx != 0 && ctx->mp164 == c && ctx->mp168 != (void*)((char*)ctx + 0x168))
            return 0.0f;

        void* iface = *(void**)((char*)watched + 0x5a8);
        u32 id = ((u32(__fastcall*)(void*, void*))(*(void***)iface)[0xc / 4])
                     (iface, (void*)0x018eb45e);
        cCreature* target = (cCreature*)FUN_00ac80d0(id);

        if (kind != 1) {
            if (c->FUN_c0bb90())
                return 0.0f;
            if (!c->FUN_c0b810(watched))
                return 0.0f;
            float d = FUN_00d99ac0((char*)watched + 0xc0, (char*)c + 0xc0, 1);
            if (*(float*)0x01582ebc <= d)
                return 0.0f;
        }

        bool picked = false;
        if ((*(u32*)((char*)watched + 0xb58) >> 9 & 1) != 0) {
            if (target->GetTargetAsCreature() != c) {
                IntVec16 cand;
                cand.mpBegin = cand.mInline;
                cand.mpEnd   = cand.mInline;
                cand.mpCap   = cand.mInline + 16;

                void* nouns = FUN_00b3d300();
                Stock* stock = (Stock*)((void*(__fastcall*)(void*))(*(void***)nouns)[0])(nouns);

                for (void** it = stock->mpBegin; it != stock->mpEnd; ++it) {
                    void* item = *it;
                    if (c->FUN_c0e8d0(item, 4))
                        continue;
                    void* itemPos = (item == 0) ? 0 : (void*)((char*)item + 0xc0);
                    float d = FUN_00d99ac0((char*)c + 0xc0, itemPos, 1);
                    if (d < *(float*)0x01582ebc)
                        cand.push_back((int)item);
                }

                if (cand.mpBegin != cand.mpEnd) {
                    int cnt = (int)(cand.mpEnd - cand.mpBegin);
                    u32 r = ((RandomLCG*)0x01601760)->UniformU32((u32)(cnt + 1));
                    if ((int)r != cnt) {
                        watched = (void*)cand.mpBegin[r];
                        picked = true;
                    }
                }
                cand.Release();
                if (picked)
                    goto stim_path;
            }
        }

        {
            NodeQuery arg;
            arg.mpTarget = (watched == 0) ? 0 : (void*)((char*)watched + 0x5a8);
            arg.mpSelf = c;

            const u32 kId = 0x60995fc;
            void* mgr = FUN_00bc9b00(kId, (void*)0x00d995c0, &arg);
            int node = ((OrderManager*)mgr)->FindNode(kId, (void*)0x00d995c0, &arg);

            u32 threshold = *(u32*)0x01582ee8;
            if ((*(u32*)((char*)c + 0xb58) >> 8 & 1) == 0) {
                void* x = c->FUN_c0c1a0();
                if (x != 0)
                    threshold = *(u32*)((char*)x + 0x3f0);
            } else {
                threshold = 0x20;
            }

            if (node != 0) {
                if (*(u32*)(node + 0x10) < threshold)
                    goto stim_path;
                return 0.0f;
            }
            if (c->FUN_c0b770())
                return 0.0f;
        }

stim_path:
        if (bs != 0)
            bs->GetAny();
        *out = 1;
        if (watched != 0) {
            *(u32*)((char*)bs + 4) = (u32)watched + 0x5a8;
            return 1.0f;
        }
        *(u32*)((char*)bs + 4) = 0;
        return 1.0f;
    }
}

// ===========================================================================
// 0x00d8f560 -- pick a nearby stock item / position for a behaviour stimulus
// ===========================================================================
// @ 0x00d8f560
float __cdecl FUN_00d8f560(cCreature* c, u32 a2, u32 a3, u32 flags,
                           BehaviorStimuli* bs, u8* out)
{
    if (c->mbF90 == 0 || (flags & 0x40000) != 0)
        return 0.0f;

    const u32 kId = 0x564c368;
    void* mgr = FUN_00bc9b00(kId, (void*)0x00d7b310, c);
    int node = ((OrderManager*)mgr)->FindNode(kId, (void*)0x00d7b310, c);
    if (node != 0) {
        if (bs != 0)
            bs->GetAny();
        *out = 1;
        bs->mnStimulusID = (u32)node;
        return 1.0f;
    }

    double r = ((RandomLCG*)0x01601760)->UniformDouble();
    if (r <= 0.25) {
        CreatureContext* ctx = c->Get();
        void* set = (void*)(((ctx->mn15C != 7) ? 0u : 0x26u) + 0x564c4afu);
        FUN_00b3d4e0(set, 0);
        int* vec = (int*)FUN_00bc7610(set, 0);
        if (vec[0] != vec[1]) {
            void* pos = ctx->GetPosition();
            void* tod = FUN_00bc30b0(pos);
            int height = ((TimeOfDay*)tod)->Get();
            u32 hi = *(u32*)((char*)ctx + 0x44);
            u32 lo = *(u32*)((char*)ctx + 0x40);
            u32 mask = c->FUN_c0b7a0() ? 1u : 0u;
            if (c->FUN_c0b780())
                mask |= 2u;

            int n = (vec[1] - vec[0]) / 0x7b4;
            IntVec16 cand;
            cand.mpBegin = cand.mInline;
            cand.mpEnd   = cand.mInline;
            cand.mpCap   = cand.mInline + 16;
            for (int i = 0; i < n; ++i) {
                int entry = i * 0x7b4 + vec[0];
                if ((*(int*)(entry + 0x7a0) == 0 ||
                     *(int*)(entry + 0x7a0) == 2 - (height != 0 ? 1 : 0)) &&
                    *(int*)(entry + 4) <= (int)((hi - lo) >> 2) &&
                    (*(u32*)(entry + 0x7a8) == 0 ||
                     (mask & *(u32*)(entry + 0x7a8)) != 0)) {
                    cand.push_back(i);
                }
            }

            if (cand.mpBegin != cand.mpEnd) {
                u32 cnt = (u32)(cand.mpEnd - cand.mpBegin);
                u32 pick = ((RandomLCG*)0x01601760)->UniformU32(cnt);
                void* chosen = (void*)cand.mpBegin[pick];
                if (bs != 0)
                    bs->GetAny();
                bs->mp18 = chosen;
                bs->mp1C = set;
                *out = 1;
                cand.Release();
                return 1.0f;
            }
            cand.Release();
        }
        return 0.0f;
    }
    return 0.0f;
}
