// Slice s00ef07d0 (gold4 #87).
// SP::Simulator::cScenarioEditModeInputStrategy - the scenario-edit input strategy.
// The strategy owns the edit-mode state: +0xcc is the mode (0 = off, 1 = edit, 2 = view),
// +0x10/+0x14/+0x18 hold simulator objects, +0x20 is an embedded SP::cLocalInputState,
// +0x68..+0xd8 a bank of held references handed to other simulator parts.
// Offsets come from the disassembly; only fields that are read are named.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

struct Strategy;

// ---------------------------------------------------------------------------
// external data (address in the comment)
extern u32         DAT_015acc34;      // 0x15acc34 game mode (4 == in-game)
extern void*       DAT_015ad298;      // 0x15ad298 input manager singleton
extern u8          DAT_015acd18;      // 0x15acd18 mouse-wheel dedup valid flag
extern u32         DAT_015acd14;      // 0x15acd14 last wheel x (float bits)
extern u32         DAT_015acd10;      // 0x15acd10 last wheel y (float bits)
extern u32         DAT_015acd0c;      // 0x15acd0c last wheel arg
extern u8          DAT_016c7b34;      // 0x16c7b34
extern u8          DAT_016c7b35;      // 0x16c7b35
extern u8          DAT_016c7b36;      // 0x16c7b36
extern u32         DAT_016c7aa8;      // 0x16c7aa8
extern u32         DAT_016c7aac;      // 0x16c7aac
extern u32         DAT_016c7b44;      // 0x16c7b44
extern u32         DAT_016c7b48;      // 0x16c7b48
extern void*       DAT_016c7aa4;      // 0x16c7aa4 app/message context
extern u32         DAT_013f6b68;      // 0x13f6b68 (float bits)
extern u32         DAT_014007f4;      // 0x14007f4 (float bits)
extern u8          DAT_0169e37c;      // 0x169e37c
extern void*       DAT_0167a690;      // 0x167a690 cCitySimulator singleton
extern void*       DAT_0168d824;      // 0x168d824 SimSingleton

// ---------------------------------------------------------------------------
// engine helpers (address in the comment)
extern "C" void*  FUN_0067dd10();                                       // 0x67dd10 SP::App
extern "C" void*  FUN_0067dcc0();                                       // 0x67dcc0 SP::MessageServer
extern "C" void*  FUN_0067ddd0();                                       // 0x67ddd0 SP::EffectsManager
extern "C" void*  FUN_0067cab0();                                       // 0x67cab0
extern "C" u8     FUN_00805180();                                       // 0x805180 WinB0
extern "C" void   FUN_008013d0(void* a, u8 b);                          // 0x8013d0 Set40
extern "C" void   FUN_00801980(void* a, u8 b);                          // 0x801980 Set
extern "C" void*  FUN_00b3d330();                                       // 0xb3d330 SP::SimTicker
extern "C" void*  FUN_00b3d250();                                       // 0xb3d250 SP::GameInputManager
extern "C" void*  FUN_00b3d300();                                       // 0xb3d300 SP_NounManager
extern "C" void*  FUN_00b3d350(u32 a);                                  // 0xb3d350 SP::PlanetModel
extern "C" void*  FUN_00b3d230(u32 a);                                  // 0xb3d230
extern "C" void*  FUN_00b3d240(u32 a);                                  // 0xb3d240
extern "C" void*  FUN_00b3d400();                                       // 0xb3d400
extern "C" void*  FUN_00b3d4c0();                                       // 0xb3d4c0
extern "C" void   FUN_00b5cde0(void* a);                                // 0xb5cde0
extern "C" u32    FUN_0093b6c0(void* a);                                // 0x93b6c0 (thiscall: arg in ecx)
extern "C" u32    FUN_0093b6c0_tc(void* a, int);                        // 0x93b6c0 thiscall form
extern "C" void*  FUN_00d539d0();                                       // 0xd539d0 SP::cPosseSimulator::Instance
extern "C" void   FUN_00ec94d0();                                       // 0xec94d0
extern "C" void   FUN_00f0c290();                                       // 0xf0c290
extern "C" void   FUN_00ed63a0();                                       // 0xed63a0
extern "C" void   FUN_00f03d80();                                       // 0xf03d80
extern "C" void   FUN_00ef8dc0();                                       // 0xef8dc0
extern "C" void   FUN_00f24d90();                                       // 0xf24d90
extern "C" void   FUN_00f21040();                                       // 0xf21040
extern "C" void   FUN_00ebfad0();                                       // 0xebfad0
extern "C" void   FUN_00f19010();                                       // 0xf19010
extern "C" void   FUN_00f02dd0();                                       // 0xf02dd0
extern "C" void   FUN_00f094d0();                                       // 0xf094d0
extern "C" void   FUN_00f32030();                                       // 0xf32030
extern "C" void   FUN_00f41cf0();                                       // 0xf41cf0
extern "C" void   FUN_00ebd340();                                       // 0xebd340
extern "C" void   FUN_00b0f6f0();                                       // 0xb0f6f0
extern "C" void   FUN_00d491b0(int a);                                  // 0xd491b0
extern "C" void   FUN_00d48a00();                                       // 0xd48a00
extern "C" void   FUN_00f084a0();                                       // 0xf084a0
extern "C" void   FUN_00f10030(void* a, int b);                         // 0xf10030 CreatureHud::Init
extern "C" void   FUN_00f1f180(void* a);                                // 0xf1f180
extern "C" void*  FUN_00f67d90(void* a);                                // 0xf67d90 GetCurrentTerrainSphere
extern "C" void   FUN_00b20fb0(void* a);                                // 0xb20fb0
extern "C" void   FUN_00e180d0(void* a);                                // 0xe180d0
extern "C" void   FUN_00ba3310(void* a);                                // 0xba3310 clear
extern "C" void   FUN_00f311c0(void* a);                                // 0xf311c0 ImpactList_Clear
extern "C" void*  FUN_00f30bc0(void* p);                                // 0xf30bc0 SimSingleton::SimSingleton
extern "C" void   FUN_00ae6a70(void* p);                                // 0xae6a70 cCitySimulator::cCitySimulator
extern "C" void*  FUN_00f473a0(u32 size, const char* name, int, int, int, int); // 0xf473a0 EAAllocate
extern "C" void   FUN_00b33ce0(void* p);                                // 0xb33ce0
extern "C" void   FUN_00b33cf0(void* p);                                // 0xb33cf0
extern "C" void   FUN_00b5e9a0(void* a);                                // 0xb5e9a0
extern "C" void   FUN_00ed4e90(void* a);                                // 0xed4e90
extern "C" void   FUN_00ed6a10(void* a);                                // 0xed6a10
extern "C" void   FUN_00ed6b00(void* a);                                // 0xed6b00
extern "C" void   FUN_00eda130(void* a);                                // 0xeda130
extern "C" void   FUN_00eda9a0(void* a);                                // 0xeda9a0
extern "C" void   FUN_00f20440();                                       // 0xf20440
extern "C" void   FUN_00ebfc20();                                       // 0xebfc20
extern "C" void   FUN_00f039a0(int a);                                  // 0xf039a0
extern "C" void   FUN_00b2f7b0(void* a);                                // 0xb2f7b0
extern "C" void   FUN_00b2f7e0(void* a, u32 b);                         // 0xb2f7e0
extern "C" void   FUN_00b18dd0();                                       // 0xb18dd0
extern "C" void*  FUN_00b1fdb0(void* mgr);                              // 0xb1fdb0 GetAvatar
extern "C" void   FUN_00f31830(void* out, void* a, void* b);            // 0xf31830
extern "C" void   FUN_00b6c280();                                       // 0xb6c280
extern "C" void   FUN_00b7e1d0(u32 a);                                  // 0xb7e1d0
extern "C" void   FUN_00f32440(u32 a);                                  // 0xf32440
extern "C" void   FUN_00ef72b0();                                       // 0xef72b0
extern "C" void   FUN_00eff790(u32 a);                                  // 0xeff790
extern "C" void   FUN_00eeff80();                                       // 0xeeff80
extern "C" void   FUN_00ef0060();                                       // 0xef0060
extern "C" void   FUN_00eeffc0(u32 a, u32 b);                           // 0xeeffc0
extern "C" void   FUN_00571db0(void* h, u32 a, u32 b, u32 c, u32 d);    // 0x571db0 EA::Messaging::RemoveHandler
extern "C" void*  FUN_00b3d3c0_0();                                     // 0xb3d3c0 (no-arg query)
extern "C" void   FUN_00b3d3c0_1(float* v, float r);                    // 0xb3d3c0 (translate helper)
extern "C" void   FUN_00b76d20(float* v, float r, int a, int b, int c); // 0xb76d20
extern u8          DAT_0169e380;      // 0x169e380
extern u8          DAT_0169e381;      // 0x169e381
extern float       DAT_0169e384;      // 0x169e384


// ---------------------------------------------------------------------------
// tiny stubs for the thiscall callees (methods called with the receiver in ecx)
struct CInputState {
    void __thiscall ResetIf(u32 k);                            // 0x697a10
    void __thiscall OnKeyUp(u32 a, u32 b);                     // 0x697a80
    void __thiscall OnMouseWheel(float x, float y, u32 arg);   // 0x697b20
    void __thiscall OnMouseMove(float a, float b, u32 c, u32 d); // 0x697b40
    void __thiscall Reset();                                   // 0x697980
};

struct SHandle {
    void __thiscall B2F7B0();      // 0xb2f7b0
    void __thiscall Ed4e90();      // 0xed4e90
    void __thiscall Ed6b00();      // 0xed6b00
    void __thiscall Eda9a0();      // 0xeda9a0
    void __thiscall F19010();      // 0xf19010
    void __thiscall F41cf0();      // 0xf41cf0
    void __thiscall Ebd340();      // 0xebd340
    void __thiscall Eda130();      // 0xeda130
    void __thiscall Ed6a10();      // 0xed6a10
    void __thiscall B2F7E0(u32 tag);  // 0xb2f7e0
    void __thiscall B7E1D0();      // 0xb7e1d0
    void __thiscall F32440(int a); // 0xf32440
    void __thiscall Ef72b0();      // 0xef72b0
};

struct SCtrl {
    void __thiscall SetMode(int a, int b, int c);      // 0xf45fd0
    void __thiscall ResetProgress();                   // 0xf190a0
};

struct SMovie {
    u8    m00[0x5c];
    void* mp5c;                        // +0x5c inner buffer
};

struct SWriter {
    u32 __thiscall GetBuffer2();       // 0x93b6c0
};

// ---------------------------------------------------------------------------
// the strategy object
class Strategy {
public:
    u8        pad00[0x10];
    void*     mp10;                 // +0x10 held simulation object
    void*     mp14;                 // +0x14
    void*     mp18;                 // +0x18
    u8        pad1c[4];
    u8        mInputState[0x48];    // +0x20 embedded SP::cLocalInputState
    void*     mp68;                 // +0x68
    void*     mp6c;                 // +0x6c
    void*     mp70;                 // +0x70
    void*     mp74;                 // +0x74
    void*     mp78;                 // +0x78
    void*     mp7c;                 // +0x7c
    void*     mp80;                 // +0x80
    u32       m84, m88, m8c, m90;   // +0x84.. handler args
    u8        pad94[0x18];
    u32       mac;                  // +0xac
    u32       mb0, mb4;             // +0xb0, +0xb4
    u32       mb8, mbc, mc0, mc4;   // +0xb8.. +0xc4
    u8        padc8[4];
    u32       mcc;                  // +0xcc mode (0/1/2)
    u32       md0;                  // +0xd0
    void*     mpd4;                 // +0xd4
    void*     mpd8;                 // +0xd8

    void __thiscall FUN_00ef07d0(u32 k);
    u8   __thiscall FUN_00ef08b0(u32 a, u32 b);
    u8   __thiscall FUN_00ef0900(u32 x, u32 y, u32 arg);
    u8   __thiscall FUN_00ef09f0(u32 a, u32 b, u32 c, u32 d);
    void __thiscall FUN_00ef0a70(u32 a);
    void __thiscall FUN_00ef0b80();
    void __thiscall FUN_00ef0c80();
    void __thiscall FUN_00ef0cd0();
    u32  __thiscall FUN_00ef0dc0();
    void __thiscall FUN_00ef0de0(u32 a);
    void __thiscall FUN_00ef0ee0();
    void __thiscall FUN_00ef10c0();
    void __thiscall FUN_00ef12d0(int mode);
    void __thiscall FUN_00ef1360();
    void __thiscall FUN_00ef13b0(int dummy);
    void __thiscall FUN_00ef1400();
    void __thiscall FUN_00ef1460();
    void __thiscall FUN_00ef1660();
};


// ===========================================================================
// @ 0x00ef07d0
void __thiscall Strategy::FUN_00ef07d0(u32 k)
{
    Strategy* this_ = this;
    if (DAT_015acc34 != 4)
        return;

    ((CInputState*)((char*)this_ + 0x20))->ResetIf(k);

    void* im = DAT_015ad298;
    ((void(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)im + 0x44))))(im, k);

    void* wm = FUN_0067dcc0();
    u8 has = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)wm + 0x84))))(wm) != 0;
    u8 b = FUN_00805180();
    void* w2 = FUN_0067dcc0();
    void* p = ((void*(__thiscall*)(void*, int))(*((char**)((char*)*(void**)w2 + 0x48))))(w2, 0);
    bool hit = false;
    if (p != 0 &&
        ((u32(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)p + 0xc))))(p, 0xcf428691) != 0)
        hit = true;
    if (hit || !(u8)k || b) {
        void* gm = FUN_00b3d250();
        ((void(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)gm + 0x48))))(gm, k);
    }

    if ((u8)k)
        return;

    void* im2 = DAT_015ad298;
    if (((u8(__thiscall*)(void*))(*((char**)((char*)*(void**)im2 + 0x3c))))(im2)) {
        void* im3 = DAT_015ad298;
        ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)im3 + 0x28))))(im3);
        void* gm = FUN_00b3d250();
        ((void(__thiscall*)(void*, int))(*((char**)((char*)*(void**)gm + 0x38))))(gm, 3);
    }
    FUN_00eeff80();
    FUN_00ef0060();
}

// ===========================================================================
// @ 0x00ef08b0
u8 __thiscall Strategy::FUN_00ef08b0(u32 a, u32 b)
{
    Strategy* this_ = this;
    if (DAT_015acc34 != 4)
        return 1;
    ((CInputState*)((char*)this_ + 0x20))->OnKeyUp(a, b);
    void* im = DAT_015ad298;
    ((void(__thiscall*)(void*, u32, u32))(*((char**)((char*)*(void**)im + 0x4c))))(im, a, b);
    void* gm = FUN_00b3d250();
    return ((u32(__thiscall*)(void*, u32, u32))(*((char**)((char*)*(void**)gm + 0x50))))(gm, a, b);
}

// ===========================================================================
// @ 0x00ef0900
u8 __thiscall Strategy::FUN_00ef0900(u32 x, u32 y, u32 arg)
{
    Strategy* this_ = this;
    if (DAT_015acc34 != 4)
        return 1;

    if (DAT_015acd18 != 0) {
        if (*(float*)&x == *(float*)&DAT_015acd14 &&
            *(float*)&y == *(float*)&DAT_015acd10 &&
            arg == DAT_015acd0c)
            return 0;
    }

    DAT_015acd14 = x;
    DAT_015acd10 = y;
    DAT_015acd0c = arg;

    ((CInputState*)((char*)this_ + 0x20))->OnMouseWheel(x, y, arg);
    void* im = DAT_015ad298;
    ((void(__thiscall*)(void*, u32, u32, u32))(*((char**)((char*)*(void**)im + 0x58))))(im, x, y, arg);
    FUN_00eeffc0(arg, 0);
    void* gm = FUN_00b3d250();
    return ((u32(__thiscall*)(void*, u32, u32, u32))(*((char**)((char*)*(void**)gm + 0x5c))))(gm, x, y, arg);
}

// ===========================================================================
// @ 0x00ef09f0
u8 __thiscall Strategy::FUN_00ef09f0(u32 a, u32 b, u32 c, u32 d)
{
    Strategy* this_ = this;
    if (DAT_015acc34 != 4)
        return 1;
    ((CInputState*)((char*)this_ + 0x20))->OnMouseMove(a, b, c, d);
    void* im = DAT_015ad298;
    ((void(__thiscall*)(void*, u32, u32, u32, u32))(*((char**)((char*)*(void**)im + 0x5c))))(im, a, b, c, d);
    void* gm = FUN_00b3d250();
    return ((u32(__thiscall*)(void*, u32, u32, u32, u32))(*((char**)((char*)*(void**)gm + 0x60))))(gm, a, b, c, d);
}

// ===========================================================================
// shared by the edit-mode entry points
static __forceinline void FUN_00ef0bkey()
{
    void* app = FUN_0067dd10();
    void* a2 = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)app + 0x50))))(app);
    void* a3 = ((void*(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)a2 + 0x40))))(a2, 0xebb801);
    if (a3 != 0) {
        void* r = (void*)((u32(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)a3 + 0xc))))(a3, 0x11966ed);
        if (r != 0)
            FUN_00b0f6f0();
    }
}

// ===========================================================================
// @ 0x00ef0a70
void __thiscall Strategy::FUN_00ef0a70(u32 a)
{
    Strategy* this_ = this;
    void* gm = FUN_00b3d250();
    *(u32*)((char*)gm + 0x110) += 1;

    FUN_00eff790(a);
    ((SHandle*)this_->mp10)->Eda130();
    ((SHandle*)this_->mp14)->Ed6a10();

    ((SHandle*)((char*)this_ + 0xc8))->B2F7E0(0x5e51bb6);
    FUN_00b6c280();
    ((SHandle*)FUN_00b3d350(0x8000000))->B7E1D0();
    ((SHandle*)this_->mp18)->F32440(1);
    ((SHandle*)*(void**)((char*)DAT_016c7aa4 + 0xd4))->Ef72b0();
    FUN_00ef0bkey();

    ((CInputState*)((char*)this_ + 0x20))->Reset();
}

// ===========================================================================
// @ 0x00ef0b30
void __cdecl FUN_00ef0b30()
{
    FUN_00ef0bkey();
    void* gm = FUN_00b3d250();
    return ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)gm + 0x1c))))(gm);
}

// ===========================================================================
// @ 0x00ef0b80
void __thiscall Strategy::FUN_00ef0b80()
{
    Strategy* this_ = this;
    FUN_00ef0bkey();
    ((CInputState*)((char*)this_ + 0x20))->Reset();

    void* gm = FUN_00b3d250();
    ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)gm + 0x1c))))(gm);
    gm = FUN_00b3d250();
    ((void(__thiscall*)(void*, int))(*((char**)((char*)*(void**)gm + 0x38))))(gm, 0);
    gm = FUN_00b3d250();
    FUN_00b18dd0();

    if (DAT_016c7b34 != 0) {
        void* wm = FUN_0067dcc0();
        void* r1 = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)wm + 4))))(wm);
        void* r2 = ((void*(__thiscall*)(void*, int))(*((char**)((char*)*(void**)wm + 0x54))))(wm, 1);
        if (r2 == r1)
            ((void(__thiscall*)(void*, int, void*))(*((char**)((char*)*(void**)wm + 0x5c))))(wm, 1, r1);
        DAT_016c7b34 = 0;
    }
    if (DAT_016c7b35 != 0) {
        if (DAT_016c7b36 != 0) {
            void* c1 = FUN_0067cab0();
            FUN_008013d0(c1, 1);
        }
        void* c2 = FUN_0067cab0();
        FUN_00801980(c2, 0);
        DAT_016c7b44 = DAT_016c7aa8;
        DAT_016c7b48 = DAT_016c7aac;
        DAT_016c7b35 = 0;
    }
}

// ===========================================================================
// @ 0x00ef0c80
void __thiscall Strategy::FUN_00ef0c80()
{
    Strategy* this_ = this;
    ((SHandle*)((char*)this_ + 0xc8))->B2F7B0();
    ((SHandle*)this_->mp14)->Ed4e90();
    ((SHandle*)this_->mp14)->Ed6b00();
    ((SHandle*)this_->mp10)->Eda9a0();
    FUN_00f20440();
    FUN_00ebfc20();
    FUN_00f039a0(0);
    void* gm = FUN_00b3d250();
    *(u32*)((char*)gm + 0x110) -= 1;
}

// ===========================================================================
// @ 0x00ef0cd0
void __thiscall Strategy::FUN_00ef0cd0()
{
    Strategy* this_ = this;
    float cam[4];
    float facing[4];
    float up[4];
    float q[4];

    void* app = FUN_0067dd10();
    void* a2 = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)app + 0x50))))(app);
    void* viewer = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)a2 + 0x1c))))(a2);

    ((void(__thiscall*)(void*, void*, void*, void*, int))(*((char**)((char*)*(void**)viewer + 0xc))))
        (viewer, cam, facing, up, 0);
    FUN_00f31830(q, facing, up);

    void* p = FUN_00b3d230(0xb03af999);
    FUN_00b5cde0(p);

    app = FUN_0067dd10();
    a2 = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)app + 0x50))))(app);
    void* cam2 = ((void*(__thiscall*)(void*))(*((char**)((char*)*(void**)a2 + 0x38))))(a2);
    void* creature = 0;
    if (cam2 != 0)
        creature = ((void*(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)cam2 + 0xc))))(cam2, 0x2a7ecd2);

    if (viewer != 0 && creature != 0) {
        ((void(__thiscall*)(void*, void*, void*, int, int, int))(*((char**)((char*)*(void**)creature + 0x44))))
            (creature, cam, q, 0, 0, 0);
        ((void(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)creature + 0x28))))(creature, DAT_013f6b68);
        ((void(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)creature + 0x2c))))(creature, DAT_014007f4);
        ((void(__thiscall*)(void*, int, void*))(*((char**)((char*)*(void**)creature + 0x20))))(creature, 0, viewer);
    }
}

// ===========================================================================
// @ 0x00ef0dc0
u32 __thiscall Strategy::FUN_00ef0dc0()
{
    Strategy* this_ = this;
    void* p = this_->mp6c;
    if (p != 0)
        return ((SWriter*)((SMovie*)p)->mp5c)->GetBuffer2();
    return 0;
}

// ===========================================================================
// @ 0x00ef0de0
void __thiscall Strategy::FUN_00ef0de0(u32 a)
{
    Strategy* this_ = this;
    void* nm = FUN_00b3d300();
    void* avatar = FUN_00b1fdb0(nm);

    void* p = this_->mp68;
    if (p != 0)
        ((void(__thiscall*)(void*, u32))(*((char**)((char*)*(void**)p + 0x10))))(p, a);

    if (this_->mp68 != 0) {
        if (DAT_0169e381 != 0 && DAT_0169e380 != 0) {
            void* q = (char*)avatar + 0xc0;
            DAT_0169e384 = ((float(__thiscall*)(void*))(*((char**)((char*)*(void**)q + 0xc8))))(q);
        } else {
            DAT_0169e384 = 0.0f;
        }
    }

    if (avatar != 0) {
        void* s = FUN_00b3d3c0_0();
        if (s != 0) {
            void* base = (char*)avatar + 0xc0;
            float v[3];
            ((void(__thiscall*)(void*, float*))(*((char**)((char*)*(void**)base + 0x6c))))(base, v);
            float r = ((float(__thiscall*)(void*, int, int, int))(*((char**)((char*)*(void**)base + 0x70))))(base, 7, 1, 0);
            FUN_00b3d3c0_1(v, r);
            FUN_00b76d20(v, r, 7, 1, 0);
        }
    }
}

// ===========================================================================
// singleton helpers (the EAAllocate / Placement-new idiom)
static void* FUN_00ef0ee0_alloc64(void** slot)
{
    if (*slot == 0) {
        void* p = FUN_00f473a0(0x40, "Simulator/SimSingleton", 0, 0, 0, 0);
        if (p == 0)
            *slot = 0;
        else {
            FUN_00ae6a70(p);
            *slot = p;
        }
    }
    return *slot;
}

static void* FUN_00ef0ee0_alloc24(void** slot)
{
    if (*slot == 0) {
        void* p = FUN_00f473a0(0x24, "Simulator/SimSingleton", 0, 0, 0, 0);
        if (p == 0)
            *slot = 0;
        else
            *slot = FUN_00f30bc0(p);
    }
    return *slot;
}

// ===========================================================================
// @ 0x00ef0ee0
void __thiscall Strategy::FUN_00ef0ee0()
{
    Strategy* this_ = this;
    void* nm = FUN_00b3d300();
    if (FUN_00f67d90(nm) == 0) {
        void* nm2 = FUN_00b3d300();
        FUN_00b20fb0(nm2);
    }

    FUN_00ef0cd0();

    ((SHandle*)((char*)this_ + 0xc8))->B2F7E0(0x5e51bb6);
    FUN_00d48a00();
    FUN_00f084a0();
    ((SCtrl*)this_->mp78)->ResetProgress();

    { void* p = this_->mp68; ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)p + 0x1c))))(p); }

    FUN_00f10030(this_->mp6c, 0);
    FUN_00f1f180(this_->mp78);

    void* q = FUN_00b3d230(0);
    FUN_00b5e9a0(q);
    FUN_00d491b0(1);

    void* tick = FUN_00b3d330();
    void* city = FUN_00ef0ee0_alloc64(&DAT_0167a690);
    void* sim = FUN_00ef0ee0_alloc24(&DAT_0168d824);
    ((void(__thiscall*)(void*, void*))(*((char**)((char*)*(void**)tick + 0x50))))(tick, city);

    FUN_00b3d4c0();
    void* r = FUN_00b3d240(0xd39010);
    FUN_00b33ce0(r);
    r = FUN_00b3d240(0xef00e0);
    FUN_00b33cf0(r);

    FUN_00ef0bkey();

    (void)sim;
    ((CInputState*)((char*)this_ + 0x20))->Reset();
}

// ===========================================================================
// @ 0x00ef10c0
void __thiscall Strategy::FUN_00ef10c0()
{
    Strategy* this_ = this;
    (void)this_;
    void* a = FUN_00b3d240(0);
    FUN_00b33ce0(a);
    a = FUN_00b3d240(0);
    FUN_00b33cf0(a);

    DAT_0169e37c = 0;

    void* b = FUN_00b3d400();
    FUN_00e180d0(b);
    FUN_00b6c280();
    void* c = FUN_00b3d4c0();
    FUN_00ba3310(c);

    void* tick = FUN_00b3d330();

    void* sim = FUN_00ef0ee0_alloc24(&DAT_0168d824);
    FUN_00f311c0(sim);
    ((void(__thiscall*)(void*, void*))(*((char**)((char*)*(void**)tick + 0x54))))(tick, sim);

    void* city = FUN_00ef0ee0_alloc64(&DAT_0167a690);
    ((void(__thiscall*)(void*, void*))(*((char**)((char*)*(void**)tick + 0x54))))(tick, city);
}

// ===========================================================================
// @ 0x00ef12d0
void __thiscall Strategy::FUN_00ef12d0(int mode)
{
    Strategy* this_ = this;
    int cur = (int)this_->mcc;
    if (cur == mode)
        return;
    if (cur == 1 && mode == 2) {
        FUN_00ef0c80();
        this_->mcc = 2;
        ((SCtrl*)this_->mp74)->SetMode(2, 0, 0);
        FUN_00ef0ee0();
        return;
    }
    if (cur == 2 && mode == 1) {
        FUN_00ef10c0();
        this_->mcc = 1;
        ((SCtrl*)this_->mp74)->SetMode(1, 0, 0);
        FUN_00ef0a70(0);
        return;
    }
    this_->mcc = (u32)mode;
}

// ===========================================================================
// @ 0x00ef1360
void __thiscall Strategy::FUN_00ef1360()
{
    Strategy* this_ = this;
    if (this_->mcc == 1)
        return;
    if (this_->mcc == 2) {
        FUN_00ef10c0();
        this_->mcc = 1;
        ((SCtrl*)this_->mp74)->SetMode(1, 0, 0);
        FUN_00ef0a70(0);
        return;
    }
    this_->mcc = 1;
}

// ===========================================================================
// @ 0x00ef13b0
void __thiscall Strategy::FUN_00ef13b0(int dummy)
{
    Strategy* this_ = this;
    (void)dummy;
    if (this_->mcc == 2)
        return;
    if (this_->mcc == 1) {
        FUN_00ef0c80();
        this_->mcc = 2;
        ((SCtrl*)this_->mp74)->SetMode(2, 0, 0);
        FUN_00ef0ee0();
        return;
    }
    this_->mcc = 2;
}

// ===========================================================================
// @ 0x00ef1400
void __thiscall Strategy::FUN_00ef1400()
{
    Strategy* this_ = this;
    FUN_00ef10c0();
    ((SCtrl*)this_->mp74)->SetMode(2, 0, 0);
    ((SCtrl*)this_->mp78)->ResetProgress();
    FUN_00ef0ee0();
}

// ===========================================================================
// @ 0x00ef1430
u8 __stdcall FUN_00ef1430(u32 a, u32 pev)
{
    (void)a;
    if (*(int*)(pev + 8) == 0x287259f6 &&
        *(int*)(pev + 0xc) >= (int)0xbbbb0000 &&
        *(int*)(pev + 0xc) <= (int)0xbbbb0003)
        return 1;
    return 0;
}

// ===========================================================================
// @ 0x00ef1460
void __thiscall Strategy::FUN_00ef1460()
{
    Strategy* this_ = this;
    void* tick = FUN_00b3d330();
    void* ps = FUN_00d539d0();
    ((void(__thiscall*)(void*, void*))(*((char**)((char*)*(void**)tick + 0x54))))(tick, ps);

    ps = FUN_00d539d0();
    ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)ps + 0x20))))(ps);

    if (this_->mcc != 0)
        this_->mcc = 0;
    if (this_->md0 == 0) {
        FUN_00ec94d0();
        FUN_00f0c290();
    }
    FUN_00f24d90();
    FUN_00f21040();
    FUN_00ebfad0();

    if (this_->mp10 != 0) {
        ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)this_->mp10 + 8))))(this_->mp10);
        if (this_->mp10 != 0) {
            void* o = this_->mp10;
            this_->mp10 = 0;
            ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 0x3c))))((char*)o + 0x3c);
        }
    }
    if (this_->mp14 != 0) {
        FUN_00ed63a0();
        void* o = this_->mp14;
        this_->mp14 = 0;
        ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 8))))(o);
    }
    if (this_->mpd8 != 0) {
        FUN_00f03d80();
        void* o = this_->mpd8;
        this_->mpd8 = 0;
        ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 4))))(o);
    }
    if (this_->mpd4 != 0) {
        FUN_00ef8dc0();
        if (this_->mpd4 != 0) {
            void* o = this_->mpd4;
            this_->mpd4 = 0;
            ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 0xc))))((char*)o + 4);
        }
    }
    FUN_00f24d90();
    FUN_00f21040();
    FUN_00ebfad0();

    {
        void* w = this_->mp78;
        u32 x = *(u32*)((char*)w + 0x90);
        this_->mb8 = this_->mac;
        this_->mbc = this_->mb0;
        this_->mc0 = this_->mb4;
        this_->mc4 = x;
        if (w != 0) {
            FUN_00f19010();
            if (this_->mp78 != 0) {
                void* o = this_->mp78;
                this_->mp78 = 0;
                ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 0xc))))((char*)o + 4);
            }
        }
    }
    if (this_->mp6c != 0) {
        void* o = this_->mp6c;
        this_->mp6c = 0;
        ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 4))))((char*)o + 0x38);
    }
    {
        void* o = this_->mp68;
        ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 0xc))))(o);
        if (this_->mp68 != 0) {
            o = this_->mp68;
            this_->mp68 = 0;
            ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 8))))((char*)o + 0x3c);
        }
    }
    FUN_00f02dd0();
    FUN_00f094d0();
    {
        void* o = this_->mp18;
        FUN_00f32030();
        if (this_->mp18 != 0) {
            o = this_->mp18;
            this_->mp18 = 0;
            ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 0xc))))(o);
        }
    }
    {
        void* o = this_->mp74;
        FUN_00f41cf0();
        if (o != 0) {
            this_->mp74 = 0;
            ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 8))))((char*)o + 8);
        }
    }
    {
        void* o = this_->mp70;
        FUN_00ebd340();
        if (this_->mp70 != 0) {
            o = this_->mp70;
            this_->mp70 = 0;
            ((void(__thiscall*)(void*))(*((char**)((char*)*(void**)o + 8))))(o);
        }
    }
    if (this_->mp80 != 0) {
        u32 x = this_->m90;
        u32 y = this_->m8c;
        u32 z = this_->m88;
        u32 w = this_->m84;
        void* o = this_->mp80;
        this_->mp80 = 0;
        FUN_00571db0(o, w, z, y, x);
    }
}

// ===========================================================================
// @ 0x00ef1660
void __thiscall Strategy::FUN_00ef1660()
{
    Strategy* this_ = this;
    switch (this_->mcc) {
    case 1:
        FUN_00ef0c80();
        break;
    case 2:
        FUN_00ef10c0();
        break;
    }

    void* em = FUN_0067ddd0();
    ((void(__thiscall*)(void*, int, int))(*((char**)((char*)*(void**)em + 0x98))))(em, 8, 0);
}
