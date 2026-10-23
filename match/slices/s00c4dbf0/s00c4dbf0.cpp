// Slice s00c4dbf0 -- SPGonzago/SPMission.obj (Simulator::cMissionChangeArchetype / cMissionColonize
// constructors plus a family of cSPMission message/update/UI helpers and event-log helpers).
//
// The shared src/game/include headers carry the 2008 dev-PDB layout; the retail offsets of these
// classes are shifted, so offsets below come from the disassembly and are reached through
// byte-offset accessors on locally declared stub classes and raw vtable calls.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

typedef unsigned int u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------------------------
// retail callees / globals
// ---------------------------------------------------------------------------------------------
extern "C" {
int   __cdecl FUN_00f47380(void* p);                     // operator delete
void* __cdecl FUN_01021300();
void* __cdecl FUN_01021230();
int   __cdecl FUN_01021240();
void* __cdecl FUN_01021260();
void* __cdecl FUN_010212a0();
void* __cdecl FUN_01021370();
void  __cdecl FUN_01041c50(const char* name, int key, int flag);
int   __cdecl FUN_00b8de30(int a);
int   __cdecl FUN_00b8dab0();                            // (this-shaped, unused directly)
int   __cdecl FUN_00bb9ae0();
char  __cdecl FUN_00bb9af0(int a);
char  __cdecl FUN_00bb9c90();
void* __cdecl FUN_00bba790();
void  __cdecl FUN_00b3d2a0();
void  __cdecl FUN_00bb1080();
void  __cdecl FUN_00bb4af0();
void  __cdecl FUN_00fefe90();
void  __cdecl FUN_00ffbe50();
float __cdecl FUN_00ffbfc0();
u32   __cdecl FUN_00a68fb0(int n);                       // RandomUint32Uniform
void  __cdecl FUN_00ae6970(void* p);
void  __cdecl FUN_00c344f0();
void  __cdecl FUN_00ba7bd0(void* p);
void  __cdecl FUN_00ba8220(void* p);
void* __stdcall FUN_00b3d3e0(int a, int b);              // SP::EventLog (2-arg, stdcall)
void* __stdcall FUN_00b3d3e0a(int a);                     // SP::EventLog (1-arg, stdcall)
void* __cdecl FUN_00ba6310(void* self, int a, int b);
char  __cdecl FUN_00c4db00(void* self, u32 key);
void  __cdecl FUN_00c4db90(void* a, void* b);
void  __cdecl FUN_00c4dbe0(void* vec, void* val);        // eastl push_back
void  __cdecl FUN_00c4db30(void* self, int a);
void  __cdecl FUN_00c4e070(void* out, void* fmt, int val);   // WStr_Format
int   __cdecl FUN_00c491c0(void* self, int tag, void* out);  // cSPMission::GetTagString
int   __cdecl FUN_01021080();
int   __cdecl FUN_00ce6950(int ctx);
int   __cdecl FUN_00c4a6b0(void* self, int a, int b);
void  __cdecl FUN_00c4b760(void* self);
void  __cdecl FUN_00c46160(void* self);
void  __cdecl FUN_00c472e0(void* self);
void  __cdecl FUN_00c471c0(void* self);
float __cdecl FUN_00c44d00(int a, int b);
int   __cdecl FUN_00bb9ae0x(int p);
int   __cdecl FUN_00801920(int p);
int   __cdecl FUN_00b1fdb0(int p);
int   __cdecl FUN_00b8dab0x(int p);
char  __cdecl FUN_00fefe90x(int p);
void  __cdecl FUN_00b3d430x(int p);
char  __cdecl FUN_00bbe5c0x(int p);
void  __cdecl FUN_00dd6d10(void* log, int id, int a);
char  __cdecl FUN_00dd6b20(void* log, int id);
void  __cdecl FUN_00c44b80(void* self);
void  __cdecl FUN_00c44bd0(void* self);
void  __cdecl FUN_00c47d80(void* self);
void  __cdecl FUN_00c4a0c0(void* self);
int   __cdecl FUN_00c5c5e0x(int p);                        // cCivData::GetCities -> float[3]
void  __cdecl FUN_00b3d2a0x(void* a, void* b, void* c);
void  __cdecl FUN_00bb1080x(void* a, void* b, void* c);
char  __cdecl FUN_00bb9af0x(int a);
int   __cdecl FUN_00bb9ae0x2(int p);                       // (reuse below)
char  __cdecl FUN_00bb9c90x(void* p);
void* __cdecl FUN_00bba790x(int p);
void  __cdecl FUN_00bb4af0x(void* a, void* b);
void  __cdecl FUN_00ba6310x(void* self, u32 a, int b);
int   __cdecl FUN_00b8dab0x2(int p);
int   __cdecl FUN_00c45b40x(void* self);
void* __cdecl FUN_00c474b0x(void* self, int a);
void* __cdecl FUN_00970b30x(void* self);
int   __cdecl FUN_0041e920();
int   __cdecl FUN_0041ea00();
void  __cdecl FUN_00c4ad50(void* self);
void  __cdecl FUN_00c47180(void* self, void* a);
void  __cdecl FUN_00b3d2a0y(void* a, void* b);
int   __cdecl FUN_00c478b0(void* self, int a, int b);
void  __cdecl FUN_00c55500(void* self);
void  __cdecl FUN_00c5ed90(void* self, int a);
int   __cdecl FUN_00c70b20(int a, int b);
int   __cdecl FUN_00c487d0(void* self, int key, void* out);
void  __cdecl FUN_00c48d40(void* self, void* out);
void  __cdecl FUN_0057cb60(void* a, void* b);
}

// ---------------------------------------------------------------------------------------------
// Globals (float constants / hashed ids)
// ---------------------------------------------------------------------------------------------
extern float gNegOneF;   // 0x013eb1bc  -1.0f
extern float gPosOneF;   // 0x01485720   1.0f
extern float gZeroF;     // 0x01485378   0.0f
extern float gHugeF;     // 0x0146dfa0   3.4028235e+38f
extern u32   gHashA;     // 0x01622184

namespace SP {

// thiscall helpers reached via ecx only (no edx); modelled as member calls so MSVC emits a bare
// `mov ecx, obj; call` (the call relocation is masked, so the symbol name is irrelevant).
class ThisStubs
{
  public:
    void  A();               // 0x00c48e90 cGenericPressureEvent ctor
    void  B();               // 0x00c47680 cSPMission dtor
    bool  Init();            // 0x00c4ad50
    bool  IsActive();        // 0x00c44c80
    u32   ReadTargetType();  // 0x00c45b40
    void* GetPlanetRec(int); // 0x00c474b0
    float ReadMinRange();    // 0x00c45b80
    float ReadMaxRange();    // 0x00c45bd0
    int   ReadNumJumps();    // 0x00c45c20
    int   CalcDuration();    // 0x00c45a10
    void  BaseInitA();       // 0x00c44b80
    void  BaseInitB();       // 0x00c44bd0
    void  SetSerializer();   // 0x00c2e4e0
    void  GetText(int key, void* out);   // 0x00c487d0
    void  GetUITitle(void* out);         // 0x00c48d40
    void  TriggerUIUpdate();             // 0x00c47d80
    void* PickPlanet(void* a);           // 0x00c47e20
    void* GetTargetPlanet();             // 0x00970b30
    int   Update(int a);                 // 0x00c478b0
    void  SetText(void* a);              // 0x0057cb60 eastl wstring operator=
    void  vt14c(int a);                  // mission list register
    void  vt150(int a);                  // mission list register
    void  RemoveEvent();                 // 0x00dd6d10 cSPUIEventLog::RemoveEvent
    bool  RegisterCallback();            // 0x00dd6b20 cSPUIEventLog::RegisterCallback
    void  MoveNestInit(void* a, void* b);  // 0x00c4db90
    void  PostInit();                    // 0x00c4a0c0
};

class cMission
{
  public:
    unsigned char pad000[0x44];
    u32    mField44;               // 0x44
    unsigned char pad048[0x78 - 0x48];
    u32    mField78;               // 0x78
    unsigned char pad07c[0x80 - 0x7c];
    int    mDuration80;            // 0x80
    unsigned char pad084[0x14c - 0x84];
    void*  mp14c;                  // 0x14c  eastl wstring (UI text)
    unsigned char pad150[0x180 - 0x150];
    void*  mp180;                  // 0x180  property list
    unsigned char pad184[0x1bc - 0x184];
    int    mField1bc;              // 0x1bc
    unsigned char pad1c0[0x1c4 - 0x1c0];
    int    mField1c4;              // 0x1c4
    int    mCounter1c8;            // 0x1c8
    unsigned char pad1cc[0x1f0 - 0x1cc];
    int    mField1f0;              // 0x1f0
    unsigned char pad1f4[0x1f8 - 0x1f4];
    int    mCount1f8;              // 0x1f8
    int    mCount1fc;              // 0x1fc
    unsigned char pad200[0x204 - 0x200];
    int    mNum204;                // 0x204
    int    mNum208;                // 0x208
    unsigned char pad20c[0x218 - 0x20c];
    int    mNum218;                // 0x218 (=-1 sentinel)
    int    mNum21c;                // 0x21c (=-1 sentinel)

    void* vtbl() { return *(void**)this; }
};

}  // namespace SP

// ---------------------------------------------------------------------------------------------
// 0x00c4dbf0 -- Simulator::cMissionChangeArchetype::cMissionChangeArchetype
// ---------------------------------------------------------------------------------------------
// @ 0x00c4dbf0
void __fastcall FUN_00c4dbf0(void* ecx_this, void* edx)
{
    ((SP::ThisStubs*)ecx_this)->A();
    int zero = 0;
    *(int*)((char*)ecx_this + 0x1f0) = zero;
    *(int*)((char*)ecx_this + 0x1f4) = zero;
    *(int*)((char*)ecx_this + 0x1f8) = zero;
    *(int*)((char*)ecx_this + 0x1fc) = zero;
    *(void**)ecx_this = (void*)0x146dd58;
    *(void**)((char*)ecx_this + 4) = (void*)0x146dd44;
    *(void**)((char*)ecx_this + 0x34) = (void*)0x146dd34;
    *(int*)((char*)ecx_this + 0x200) = zero;
    *(int*)((char*)ecx_this + 0x204) = zero;
    *(int*)((char*)ecx_this + 0x208) = zero;
}

// ---------------------------------------------------------------------------------------------
// 0x00c4dca0 -- FUN_00c4dca0 (cMissionChangeArchetype scalar deleting destructor, ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4dca0
void* __fastcall FUN_00c4dca0(void* ecx_this, void* edx, u8 flags)
{
    void* p = *(void**)((char*)ecx_this + 0x200);
    if (p && *(int*)((char*)p - 4) != 0)
        FUN_00f47380(p);
    ((SP::ThisStubs*)ecx_this)->B();
    if (flags & 1)
        FUN_00f47380(ecx_this);
    return ecx_this;
}

// ---------------------------------------------------------------------------------------------
// 0x00c4dce0 -- FUN_00c4dce0 (cMissionChangeArchetype::Init)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4dce0
char __fastcall FUN_00c4dce0(void* ecx_this, void* edx)
{
    if (!((SP::ThisStubs*)ecx_this)->Init())
        return 0;
    ((SP::ThisStubs*)ecx_this)->MoveNestInit((char*)ecx_this + 0x1f4, (char*)ecx_this + 0x1f8);
    ((SP::ThisStubs*)ecx_this)->PostInit();
    return 1;
}

// ---------------------------------------------------------------------------------------------
// 0x00c4dd10 -- FUN_00c4dd10 (cMissionChangeArchetype::HandleMessage, ret 8)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4dd10
void __fastcall FUN_00c4dd10(void* ecx_this, void* edx, u32 msg, void* arg)
{
    SP::cMission* self = (SP::cMission*)ecx_this;
    if (msg < 0x4446534u) {
        if (msg != 0x4446533u && msg != 0x4445d43u) {
            FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
            return;
        }
    } else if (msg != 0xf46092c1u && msg != 0xf46092d4u && msg != 0xf46092d5u &&
               msg != 0xf46092d8u && msg != 0xf46092dau && msg != 0xf46092dbu) {
        FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
        return;
    }
    if (msg == 0xf46092d4u) {
        u32 key = *(u32*)((char*)arg + 8);
        if (FUN_00c4db00(ecx_this, key))
            return;  // fallthrough to HandleMessage
        FUN_00c4dbe0((char*)ecx_this + 0x1cc, &key);   // push_back
        goto LAB_INC;
    }
    if (msg == 0xf46092dau) {
        int v = *(int*)((char*)arg + 8);
        if (v < 1) {
            FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
            return;
        }
        self->mCounter1c8 += v;
        goto LAB_COMPARE;
    }
    if (msg == 0xf46092dbu) {
        if (FUN_01021080() != 0)
            goto LAB_CASE_DEFAULT;
        if (FUN_010212a0() == 0)
            goto LAB_CASE_DEFAULT;
        int ctx = (int)FUN_010212a0();
        u32 found = FUN_00ce6950(ctx);
        (void)found;
        if (FUN_00c4db00(ecx_this, found))
            goto LAB_CASE_DEFAULT;
        FUN_00c4dbe0((char*)ecx_this + 0x1cc, &found);
        goto LAB_INC;
    }
    if (msg == 0xf46092c1u) {
        int a0 = *(int*)((char*)arg + 0x20);
        int a1 = *(int*)((char*)arg + 0x28);
        if (*(int*)((char*)arg + 8) == 0) {
            int ctx = (int)FUN_01021300();
            int found = FUN_00ce6950(ctx);
            if (a1 != found)
                goto LAB_ADD_A0;
            goto LAB_INC;
        }
        int v = *(int*)((char*)arg + 0x10);
        if (v == (int)0xb978c47a || v == 0x7ecbe6f5)
            self->mCounter1c8 -= a0;
        goto LAB_CASE_DEFAULT;
    }
LAB_INC:
    FUN_00c4db30(ecx_this, 1);
    self->mCounter1c8 += 1;
LAB_COMPARE:
    if ((u32)self->mField1c4 > (u32)self->mCounter1c8) {
        FUN_00c47d80(ecx_this);          // TriggerUIUpdate
        FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
        return;
    }
    FUN_00c4b760(ecx_this);
    FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
    return;
LAB_ADD_A0:
    {
        int a0 = *(int*)((char*)arg + 0x20);
        self->mCounter1c8 += a0;
    }
    goto LAB_COMPARE;
LAB_CASE_DEFAULT:
    FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
}

// ---------------------------------------------------------------------------------------------
// 0x00c4deb0 -- FUN_00c4deb0 (cMissionChangeArchetype::GetTagString, ret 8)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4deb0
int __fastcall FUN_00c4deb0(void* ecx_this, void* edx, int tag, void* out)
{
    if ((u32)tag == 0x649ad9deu) {
        int diff = *(int*)((char*)ecx_this + 0x1f8) - *(int*)((char*)ecx_this + 0x1fc);
        FUN_00c4e070(out, (void*)0x13f01bc, diff);   // WStr_Format
        return 1;
    }
    return FUN_00c491c0(ecx_this, tag, out);         // cSPMission::GetTagString
}

// ---------------------------------------------------------------------------------------------
// 0x00c4def0 -- Simulator::cMissionColonize::cMissionColonize
// ---------------------------------------------------------------------------------------------
// @ 0x00c4def0
void* __fastcall FUN_00c4def0(void* ecx_this, void* edx)
{
    ((SP::ThisStubs*)ecx_this)->A();
    int zero = 0;
    *(int*)((char*)ecx_this + 0x1f0) = zero;
    *(char*)((char*)ecx_this + 0x1f4) = 0;
    *(char*)((char*)ecx_this + 0x1f5) = 0;
    *(void**)ecx_this = (void*)0x146dfc8;
    *(void**)((char*)ecx_this + 4) = (void*)0x146dfb4;
    *(void**)((char*)ecx_this + 0x34) = (void*)0x146dfa4;
    return ecx_this;
}

// ---------------------------------------------------------------------------------------------
// 0x00c4e0f0 -- FUN_00c4e0f0 (cMissionColonize::HandleMessage, ret 8)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4e0f0
void __fastcall FUN_00c4e0f0(void* ecx_this, void* edx, u32 msg, void* arg)
{
    SP::cMission* self = (SP::cMission*)ecx_this;
    bool runTail = false;
    if (msg < 0x248976bu) {
        if (msg == 0x248976au) {
            runTail = true;
        } else if (msg == 0x248975fu) {
            if (self->mField44 != 0x398aca5eu) { FUN_00c4a6b0(ecx_this, (int)msg, (int)arg); return; }
            if (self->mField1bc == 0)
                FUN_00c46160(ecx_this);
            runTail = true;
        } else if (msg == 0x2489766u) {
            runTail = true;
        } else {
            FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
            return;
        }
    } else if (msg == 0x490d429u) {
        runTail = true;
    } else {
        FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
        return;
    }
    if (runTail) {
        if (self->mField44 == 0x398aca5eu && self->mField1bc == 0)
            FUN_00c47d80(ecx_this);              // TriggerUIUpdate
    }
    FUN_00c4a6b0(ecx_this, (int)msg, (int)arg);
}

// ---------------------------------------------------------------------------------------------
// 0x00c4e1a0 -- FUN_00c4e1a0 (cMissionColonize::DisplayMessage, ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4e1a0
void __fastcall FUN_00c4e1a0(void* ecx_this, void* edx, int which)
{
    if (which == 1) {
        if (((SP::ThisStubs*)ecx_this)->IsActive()) {
            void* tp = ((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
            if (tp == (void*)FUN_01021260())
                FUN_01041c50("SPG_ColonizeMissionPlanet", (int)0xb1a88fd1, 1);
        }
    } else if (which == 3) {
        if (((SP::ThisStubs*)ecx_this)->IsActive()) {
            void* tp = ((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
            if (tp) {
                void* a = FUN_01021230();
                int x = *(int*)((char*)a + 0x48);
                void* tp2 = ((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
                int y = FUN_00b8de30(*(int*)((char*)tp2 + 0x13c));
                if (x == y)
                    FUN_01041c50("SPG_ColonizeMissionSolar", (int)0x45a6efc2, 1);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c4e230 -- FUN_00c4e230 (cMissionColonize::SomeDismiss)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4e230
void __fastcall FUN_00c4e230(void* ecx_this, void* edx)
{
    ((SP::ThisStubs*)ecx_this)->SetSerializer();
    if (*(int*)((char*)ecx_this + 0x1f0) == 2)
        return;
    ((SP::ThisStubs*)ecx_this)->BaseInitA();
    if (*(int*)((char*)ecx_this + 0x1f0) != 2) {
        *(int*)((char*)ecx_this + 0x1f0) = 2;
        FUN_00c47d80(ecx_this);
    }
    FUN_00c472e0(ecx_this);
    FUN_00c471c0(ecx_this);
}

// ---------------------------------------------------------------------------------------------
// 0x00c4e280 -- FUN_00c4e280 (float evaluator, ret 8)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4e280
float __fastcall FUN_00c4e280(void* ecx_this, void* edx, int a2, int a3)
{
    float r = FUN_00c44d00(a2, a3);
    if (0.0f >= r)
        return r;
    int p = FUN_00b8de30(a2);
    if (FUN_00bb9ae0x(p) != 1 && FUN_00801920(p) != 0)
        return gNegOneF;
    if (FUN_00b1fdb0(p) != -1)
        return gNegOneF;
    if (FUN_00b8dab0x(a2) != 1)
        return gNegOneF;
    if (((*(u32*)((char*)ecx_this + 0x130) >> 3) & 1) != 0) {
        if (!FUN_00fefe90x(a2))
            return gNegOneF;
    }
    FUN_00b3d430x(a2);
    char c = FUN_00bbe5c0x(a2);
    if (*(char*)((char*)ecx_this + 0x1f4) != 0)
        return c ? gPosOneF : gNegOneF;
    return c ? gNegOneF : gPosOneF;
}

// ---------------------------------------------------------------------------------------------
// 0x00c4e390 -- SP::cSPMissionColonize::ReadPlanetNeedsFullRow (ret 0xc)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4e390
void __fastcall FUN_00c4e390(void* ecx_this, void* edx, u8* pb, u32* pu, int* pflag)
{
    // pb = *this+0x1f4? no: caller passes (this+0x1f4, &local, this+0x1f5) reversed; here pb/pu/pflag
    // map to the three property reads in order.
    void* pl = *(void**)((char*)ecx_this + 0x180);
    if (pl) {
        void* prop = 0;
        char ok = (*(char(__thiscall**)(void*, u32, void**))(*(char**)pl + 0x24))(pl, 0x36758b07u, &prop);
        if (ok && *(short*)((char*)prop + 0x12) == 1) {
            u8* v = (u8*)FUN_0041e920();
            *pb = *v;
        }
    }
    pl = *(void**)((char*)ecx_this + 0x180);
    if (pl) {
        void* prop = 0;
        char ok = (*(char(__thiscall**)(void*, u32, void**))(*(char**)pl + 0x24))(pl, 0x1f707861u, &prop);
        if (ok && *(short*)((char*)prop + 0x12) == 10) {
            u32* v = (u32*)FUN_0041ea00();
            *pu = *v;
        }
    }
    pl = *(void**)((char*)ecx_this + 0x180);
    if (pl) {
        void* prop = 0;
        char ok = (*(char(__thiscall**)(void*, u32, void**))(*(char**)pl + 0x24))(pl, 0xf924ebf9u, &prop);
        if (ok && *(short*)((char*)prop + 0x12) == 1) {
            u8* v = (u8*)FUN_0041e920();
            *pflag = *v;
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c4e440 -- FUN_00c4e440 (cMissionColonize::Init)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4e440
char __fastcall FUN_00c4e440(void* ecx_this, void* edx)
{
    char ok = (char)((int(__fastcall*)(void*, void*))FUN_00c4ad50)(ecx_this, 0);
    if (!ok)
        return 0;
    int localFlag = 0;
    FUN_00c4e390(ecx_this, 0, (u8*)((char*)ecx_this + 0x1f4), (u32*)((char*)ecx_this + 0x1f5), &localFlag);
    u32 type = (u32)FUN_00c45b40x(ecx_this);
    if (type != 0x2ca33dbdu) {
        void* rec = FUN_00c474b0x(ecx_this, (int)type);
        if (rec)
            FUN_00c47180(ecx_this, rec);
        if (FUN_00970b30x(ecx_this) == 0) {
            FUN_00ba7bd0((char*)ecx_this + 8);
            u32 flags = 0;
            switch (localFlag) {
            case 3: flags |= 0x20;
            case 2: flags |= 0x10;
            case 1: flags |= 8;
            case 0: flags |= 4;
            }
            int rec2[13];
            rec2[0] = (int)flags;
            rec2[1] = 2;
            rec2[2] = 2;
            if (*(u8*)((char*)ecx_this + 0x1f4))
                rec2[4] &= ~1;
            else
                rec2[4] = 1;
            int r = (*(int(__thiscall**)(void*, int*))(*(char**)ecx_this + 0x1a4))(ecx_this, rec2);
            if (r == 0) {
                FUN_00ba8220((char*)ecx_this + 8);
                return 0;
            }
            FUN_00c47180(ecx_this, (void*)r);
            FUN_00ba8220((char*)ecx_this + 8);
        }
    }
    char c = (*(char(__thiscall**)(void*))(*(char**)ecx_this + 0x128))(ecx_this);
    if (!c)
        return 0;
    FUN_00c4a0c0(ecx_this);
    (*(void(__thiscall**)(void*))(*(char**)ecx_this + 0x170))(ecx_this);
    return 1;
}

// ---------------------------------------------------------------------------------------------
// 0x00c4e570 -- FUN_00c4e570 (cMissionColonize::PickTarget, ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4e570
void* __fastcall FUN_00c4e570(void* ecx_this, void* edx, u32* a)
{
    SP::ThisStubs* self = (SP::ThisStubs*)ecx_this;
    u32* p = a;
    void* chosen = 0;
    if (*(u32*)((char*)ecx_this + 0x78) != 0x398aca5eu)
        goto LAB_PICK;

    float minR = self->ReadMinRange();
    float maxR = self->ReadMaxRange();
    int numJumps = self->ReadNumJumps();
    u32 r1 = p[1];

    // query block (0x1ff1 / r1 / 4 / -1,-1,-1 / jumps)
    int   q0 = 0x1ff1;
    u32   q1 = r1;
    int   q2 = 4;
    float qmin = gNegOneF, qmax = gNegOneF, qtravel = gNegOneF;
    int   qjumps = 0;
    (void)qjumps;
    if (0.0f <= minR)
        qmin = minR;
    if (maxR > gZeroF)
        qmax = maxR;
    FUN_00ffbe50();
    qtravel = (float)FUN_00ffbfc0();
    qjumps = numJumps;

    float hostPos[3];      // esp+0x30/34/38
    void* civ = (void*)self->GetPlanetRec(0);      // esp+0x54
    (void)civ;
    float* cp = (float*)FUN_00c5c5e0x((int)p);     // GetCities -> float[3]
    hostPos[0] = cp[0];
    hostPos[1] = cp[1];
    hostPos[2] = cp[2];

    // build the star-record vector
    struct Vec { void* b; void* e; void* c; };
    Vec planetVec;
    planetVec.b = 0; planetVec.e = 0; planetVec.c = 0;
    FUN_00b3d2a0x(hostPos, &q0, &planetVec);
    FUN_00bb1080x(hostPos, &q0, &planetVec);

    void** pv = (void**)planetVec.b;
    void** endv = (void**)planetVec.e;
    int n = (int)((char*)endv - (char*)pv) / 4;
    float bestTravel = gHugeF;
    float bestDist = gNegOneF;
    void* bestStar = 0;
    for (int i = 0; i < n; ++i) {
        void* star = pv[i];
        if (FUN_00bb9af0x(1))
            continue;
        int bit = FUN_00bb9ae0x((int)star) & 0x1f;
        if ((p[1] & (1u << bit)) == 0)
            continue;
        if (bestStar == star)
            continue;
        float* sp = (float*)FUN_00c5c5e0x((int)star);
        float dx = hostPos[0] - sp[0];
        float dy = hostPos[1] - sp[1];
        float dz = hostPos[2] - sp[2];
        float dist = dz * dz + dy * dy + dx * dx;
        if (!FUN_00bb9c90x(star)) {
            FUN_00b3d2a0y(star, p);
            FUN_00bb4af0x(star, p);
        }
        void** pl = (void**)FUN_00bba790x((int)star);
        int m = (int)((char*)pl[1] - (char*)pl[0]) / 4;
        for (int j = 0; j < m; ++j) {
            int planet = *(int*)((char*)pl[0] + j * 4);
            int pb = (*(int*)(planet + 0x28)) & 0x1f;
            if ((*p & (1u << pb)) == 0)
                continue;
            int pb2 = FUN_00b8dab0x(planet) & 0x1f;
            if ((p[2] & (1u << pb2)) == 0)
                continue;
            int t1 = 0, t2 = 0;
            float travel = (*(float(__thiscall**)(void*, int, void*))(*(char**)ecx_this + 0x184))(ecx_this, planet, &t1);
            (void)t2;
            if (travel <= 0.0f)
                continue;
            bool better;
            if (travel == bestDist)
                better = (dist < bestTravel);
            else
                better = (bestDist < travel);
            if (better) {
                bestTravel = dist;
                bestDist = travel;
                bestStar = star;
            }
        }
    }

    // tear down the vector
    for (void** it = pv; it < endv; ++it) {
        if (*it)
            (*(void(__thiscall**)(void*))(*(char**)*it + 4))(*it);
    }
    if (planetVec.b && *((int*)planetVec.b - 1) != 0)
        FUN_00f47380(planetVec.b);

    chosen = bestStar;
    if (chosen)
        goto LAB_TAIL;
LAB_PICK:
    chosen = self->PickPlanet(a);
LAB_TAIL:
    if (*(u32*)((char*)ecx_this + 0x78) == 0x398aca5eu && chosen) {
        u32 keys[13];
        keys[0] = 0xb4fe6c1d; keys[1] = 0xef9a0e5d; keys[2] = 0x6c836e17; keys[3] = 0x6fbf28c4;
        keys[4] = 0x09f1a11b; keys[5] = 0x7fb9baf3; keys[6] = 0xcb3c5ecb; keys[7] = 0x524a8dc4;
        keys[8] = 0xd84910a0; keys[9] = 0xdf5be6d5; keys[10] = 0x4c7c77a7; keys[11] = 0x618e762a;
        keys[12] = 0x1b917be2;
        u32 idx = FUN_00a68fb0(13);
        u32 key = keys[idx];
        FUN_00b3d2a0y(chosen, (void*)key);
        FUN_00ba6310x(chosen, key, 0xa6);
    }
    return chosen;
}

// ---------------------------------------------------------------------------------------------
// 0x00c4e9a0 -- FUN_00c4e9a0 (cMissionColonize::Update2, ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4e9a0
int __fastcall FUN_00c4e9a0(void* ecx_this, void* edx, int a)
{
    int r = (int)((int(__fastcall*)(void*, void*, int))FUN_00c478b0)(ecx_this, 0, a);
    if (r != 3)
        return r;
    void* owner = *(void**)((char*)ecx_this + 0x1f0);   // placeholder per decompile: param_1[1].mpOwnerEmpire
    (void)owner;
    if (owner == 0) {
        bool ok;
        if (*(u32*)((char*)ecx_this + 0x78) == 0x398aca5eu) {
            void* v[3];
            v[0] = 0; v[1] = 0; v[2] = 0;
            FUN_01021300();
            FUN_00c344f0();
            int cnt = (int)((char*)v[1] - (char*)v[0]) / 4;
            ok = cnt > 1;
            FUN_00ae6970(&v[0]);
        } else {
            FUN_01021300();
            ((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
            ok = FUN_00c70b20(0, 0) != 0;
        }
        if (!ok)
            return 3;
        if (*(u8*)((char*)ecx_this + 0x1f5) != 0) {
            FUN_00c5ed90(ecx_this, 1);
            return 3;
        }
    } else if (owner != (void*)1) {
        return 3;
    } else {
        FUN_01021300();
        ((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
        if (!FUN_00c70b20(0, 0))
            return 3;
    }
    FUN_00c55500(ecx_this);
    return 3;
}

// ---------------------------------------------------------------------------------------------
// 0x00c4ea70 -- FUN_00c4ea70 (cSPMissionFetch::GetUIShortDescription, ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4ea70
void __fastcall FUN_00c4ea70(void* ecx_this, void* edx, void* out)
{
    void* textPtr = (char*)ecx_this + 0x14c;
    if (*(void**)((char*)ecx_this + 0x14c) != *(void**)((char*)ecx_this + 0x150) ||
        *(int*)((char*)ecx_this + 0x1f0) != 0 ||
        *(u32*)((char*)ecx_this + 0x78) != 0x398aca5eu)
        goto LAB_DEFAULT;

    if (FUN_01021080() == 1) {
        void* rec = FUN_010212a0();
        if (rec) {
            void* tp = ((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
            int tpv = tp ? *(int*)((char*)tp + 0x13c) : 0;
            if ((int)rec == tpv) {
                FUN_00c487d0(ecx_this, (int)0x791cfa76, out);
                FUN_0057cb60(textPtr, out);
                return;
            }
        }
        int isArchived = FUN_01021240();
        void* tp2 = ((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
        int tpv2 = tp2 ? FUN_00b8de30(*(int*)((char*)tp2 + 0x13c)) : 0;
        if (isArchived != 0 && isArchived == tpv2) {
            FUN_00c487d0(ecx_this, (int)0x639f0b00, out);
            FUN_0057cb60(textPtr, out);
            return;
        }
    } else if (FUN_01021080() == 0) {
        void* rec = FUN_010212a0();
        if (rec) {
            void* tp = ((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
            int tpv = tp ? *(int*)((char*)tp + 0x13c) : 0;
            if ((int)rec == tpv) {
                FUN_00c487d0(ecx_this, (int)0x6f9c8bf3, out);
                FUN_0057cb60(textPtr, out);
                return;
            }
        }
    }
LAB_DEFAULT:
    FUN_00c48d40(ecx_this, out);
}

// ---------------------------------------------------------------------------------------------
// 0x00c4ec90 -- FUN_00c4ec90 (remove event 0x218)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4ec90
void __fastcall FUN_00c4ec90(void* ecx_this, void* edx)
{
    int id = *(int*)((char*)ecx_this + 0x218);
    if (id != -1) {
        void* log = FUN_00b3d3e0(id, 0);
        ((SP::ThisStubs*)log)->RemoveEvent();
        *(int*)((char*)ecx_this + 0x218) = -1;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c4ecc0 -- FUN_00c4ecc0 (remove event 0x21c)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4ecc0
void __fastcall FUN_00c4ecc0(void* ecx_this, void* edx)
{
    int id = *(int*)((char*)ecx_this + 0x21c);
    if (id != -1) {
        void* log = FUN_00b3d3e0(id, 0);
        ((SP::ThisStubs*)log)->RemoveEvent();
        *(int*)((char*)ecx_this + 0x21c) = -1;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c4ecf0 -- FUN_00c4ecf0 (register callback 0x218)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4ecf0
void __fastcall FUN_00c4ecf0(void* ecx_this, void* edx)
{
    int id = *(int*)((char*)ecx_this + 0x218);
    if (id != -1) {
        void* log = FUN_00b3d3e0a(id);
        if (!((SP::ThisStubs*)log)->RegisterCallback())
            *(int*)((char*)ecx_this + 0x218) = -1;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c4ed20 -- FUN_00c4ed20 (register callback 0x21c)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4ed20
void __fastcall FUN_00c4ed20(void* ecx_this, void* edx)
{
    int id = *(int*)((char*)ecx_this + 0x21c);
    if (id != -1) {
        void* log = FUN_00b3d3e0a(id);
        if (!((SP::ThisStubs*)log)->RegisterCallback())
            *(int*)((char*)ecx_this + 0x21c) = -1;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c4ed50 -- FUN_00c4ed50 (compare two counters, bool-ish)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4ed50
int __fastcall FUN_00c4ed50(void* ecx_this, void* edx)
{
    int a = *(int*)((char*)ecx_this + 0x208);
    int b = *(int*)((char*)ecx_this + 0x204);
    int ge = (a >= b) ? 1 : 0;
    int r = (ge - 1) & 0x2ee1aa4e;
    r = r + (int)0xa2b7bfa8;
    return r;
}

// ---------------------------------------------------------------------------------------------
// 0x00c4edd0 -- FUN_00c4edd0 (register message ids via slot 0x14c)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4edd0
void __fastcall FUN_00c4edd0(void* ecx_this, void* edx)
{
    FUN_00c44b80(ecx_this);
    void** vt = *(void***)ecx_this;
    (*(void(__thiscall**)(void*, u32))(*(char**)ecx_this + 0x14c))(ecx_this, 0x1622184);
    (*(void(__thiscall**)(void*, u32))(*(char**)ecx_this + 0x14c))(ecx_this, 0x5e37a53);
    (*(void(__thiscall**)(void*, u32))(*(char**)ecx_this + 0x14c))(ecx_this, 0x2489760);
    (*(void(__thiscall**)(void*, u32))(*(char**)ecx_this + 0x14c))(ecx_this, 0x3029f11);
    (*(void(__thiscall**)(void*, u32))(*(char**)ecx_this + 0x14c))(ecx_this, 0x3337cbb);
    (void)vt;
}

// ---------------------------------------------------------------------------------------------
// 0x00c4ee30 -- FUN_00c4ee30 (register message ids via slot 0x150)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4ee30
void __fastcall FUN_00c4ee30(void* ecx_this, void* edx)
{
    FUN_00c44bd0(ecx_this);
    (*(void(__thiscall**)(void*, u32))(*(char**)ecx_this + 0x150))(ecx_this, 0x1622184);
    (*(void(__thiscall**)(void*, u32))(*(char**)ecx_this + 0x150))(ecx_this, 0x5e37a53);
    (*(void(__thiscall**)(void*, u32))(*(char**)ecx_this + 0x150))(ecx_this, 0x2489760);
    (*(void(__thiscall**)(void*, u32))(*(char**)ecx_this + 0x150))(ecx_this, 0x3029f11);
    (*(void(__thiscall**)(void*, u32))(*(char**)ecx_this + 0x150))(ecx_this, 0x3337cbb);
}

// ---------------------------------------------------------------------------------------------
// 0x00c4ee90 -- FUN_00c4ee90 (DoesMissionPreventRelationshipChange, ret 8)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4ee90
int __fastcall FUN_00c4ee90(void* ecx_this, void* edx, int planet, int b)
{
    (void)b;
    if (*(int*)((char*)ecx_this + 0x1f0) == 0x1e8763) {
        int tp = (int)((SP::ThisStubs*)ecx_this)->GetTargetPlanet();
        if (planet == tp)
            return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00c4eec0 -- FUN_00c4eec0 (set field 0x1f4, ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4eec0
void __fastcall FUN_00c4eec0(void* ecx_this, void* edx, int v)
{
    if (*(int*)((char*)ecx_this + 0x1f4) != v) {
        *(int*)((char*)ecx_this + 0x1f4) = v;
        ((SP::ThisStubs*)ecx_this)->TriggerUIUpdate();
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c4eee0 -- FUN_00c4eee0 (recompute duration)
// ---------------------------------------------------------------------------------------------
// @ 0x00c4eee0
void __fastcall FUN_00c4eee0(void* ecx_this, void* edx)
{
    int d = ((SP::ThisStubs*)ecx_this)->CalcDuration();
    *(int*)((char*)ecx_this + 0x80) = d * *(int*)((char*)ecx_this + 0x204);
}
