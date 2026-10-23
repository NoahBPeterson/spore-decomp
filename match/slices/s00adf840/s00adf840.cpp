// Slice s00adf840 -- simulator-screen reset / mode-transition / per-frame tick,
// a cinematic object-context constructor and a tribe/noun manager update.
//
//   0x00adf840  Sim::reset          (large screen teardown/reset)
//   0x00adfd60  Sim::enterMode      (mode transition, message post)
//   0x00adffd0  Sim::resetAll       (reset + effects/message)
//   0x00ae0080  Sim::start          (mode start)
//   0x00ae00d0  SimB::tick         (per-frame screen update)
//   0x00ae0640  Simulator::cObjectContext::cObjectContext
//   0x00ae0700  TribeMgr::update    (noun/tribe iteration)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include <intrin.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed char    i8;

#define VFN(o, off, T) ((T)(*(void***)(o))[((off) >> 2)])

// ------------------------------------------------------------- thiscall thunk types
typedef void  (__thiscall *TC_v0)(void*);
typedef void* (__thiscall *TC_p0)(void*);
typedef char  (__thiscall *TC_c0)(void*);
typedef int   (__thiscall *TC_i0)(void*);
typedef void  (__thiscall *TC_i1)(void*, int);
typedef void  (__thiscall *TC_ii)(void*, int, int);
typedef void  (__thiscall *TC_iii)(void*, int, int, int);
typedef void* (__thiscall *TC_pi)(void*, int);
typedef void* (__thiscall *TC_pii)(void*, int, int);
typedef void* (__thiscall *TC_piii)(void*, int, int, int);
typedef void  (__thiscall *TC_v2)(void*, void*, void*);
typedef void  (__thiscall *TC_ps)(void*, const char*);
typedef void  (__thiscall *TC_iiiv)(void*, int, void*, int);
typedef void  (__thiscall *TC_piv)(void*, int, void*);
typedef void  (__thiscall *TC_pvi)(void*, void*, int);
typedef void* (__thiscall *TC_psr)(void*, const char*);

// ------------------------------------------------------------- literals / vtables
extern "C" float KF_15664a8;      // 0x015664a8  (tiny timer sentinel)
extern "C" float KF_13f9428;      // 0x013f9428  (0.001f)
extern "C" float KF_13f4fd0;      // 0x013f4fd0  (4294967296.0f)
extern "C" float KF_1485720;      // 0x01485720  (1.0f)
extern "C" float KF_1470f1c;      // 0x01470f1c  (2.0f)
extern "C" float KF_167a548;      // 0x0167a548
extern "C" float KF_167a54c;      // 0x0167a54c
extern "C" float KF_167a550;      // 0x0167a550
extern "C" char  D_154df28[];     // 0x0154df28
extern "C" char  VT_13ec458[];    // 0x013ec458
extern "C" char  VT_145b918[];    // 0x0145b918
extern "C" char  VT_145b908[];    // 0x0145b908
extern "C" char  VT_13eb90c[];    // 0x013eb90c
extern "C" char  VT_13eb844[];    // 0x013eb844
extern "C" char  S_switchExit[];  // 0x0145b004  "switchToExitState"
extern "C" int*  g_pModeFlags;    // 0x016f6ee0

// ------------------------------------------------------------- cdecl callees
extern "C" void* __cdecl SP_MessageServer();      // 0x0067dcc0
extern "C" void* __cdecl SP_App();                // 0x0067dd10
extern "C" void* __cdecl SP_EffectsManager();     // 0x0067ddd0
extern "C" void* __cdecl SP_EventLog();           // 0x00b3d3e0
extern "C" void* __cdecl SP_GameInputManager();   // 0x00b3d250
extern "C" void* __cdecl SP_BehaviorManager();    // 0x00b3d260
extern "C" void* __cdecl SP_GameTimeManager();    // 0x00b3d380
extern "C" void* __cdecl SP_NounManager();        // 0x00b3d300
extern "C" void* __cdecl FUN_00b3d310();          // 0x00b3d310
extern "C" void* __cdecl FUN_00b3d240();          // 0x00b3d240
extern "C" void* __cdecl FUN_00b3d280();          // 0x00b3d280
extern "C" void* __cdecl FUN_00b3d230(void*);     // 0x00b3d230
extern "C" void* __cdecl EA_Audio_GetSystemAT();  // 0x00a206f0
extern "C" void* __cdecl EA_UTFWin_GetManager();  // 0x00957f30
extern "C" void* __cdecl FUN_00c83c90(void*, void*, void*); // 0x00c83c90
extern "C" void  __cdecl SPUIHelpers_EndModal(void*, void*, void*); // 0x00809c50
extern "C" void  __cdecl FUN_00d2ca90(void*);     // 0x00d2ca90
extern "C" void  __cdecl FUN_00b3d3c0(void*, int, int, int, int); // 0x00b3d3c0
extern "C" void  __cdecl FUN_00b76d20(void*, int, int, int, int); // 0x00b76d20
extern "C" void  __cdecl eastl_vec_insert(void*, void*, int);     // 0x011e0744
extern "C" void  __cdecl FUN_00b7c810(int);       // 0x00b7c810  HideUTFMenu
extern "C" char  __cdecl FUN_00b7c780();          // 0x00b7c780
extern "C" char  __cdecl FUN_00ad71f0(void*);     // 0x00ad71f0
extern "C" void** __cdecl FUN_00ad81b0(void**, void**, void**, char (__cdecl*)(void*)); // 0x00ad81b0

// ------------------------------------------------------------- thiscall callee stubs
struct Ops {
    void  decPauseGate(int);         // 0x00b32250
    int   pauseGates(int);           // 0x00b320d0
    void  togglePause(int);          // 0x00b32280
    void  vecErase(void*, void*);    // 0x0103c4f0
    void  vecDestroy(void*, void*);  // 0x00adb680
    void  vecRelease(void*, void*);  // 0x0093dc70
    void  vecEraseAuto(void*, void*);// 0x00b48e40
    void* opAddFA0(void*, void*);    // 0x00addfa0
    void  op8E80();                  // 0x00ad8e80
    void  opDE00(int);               // 0x00adde00
    void  op5CDE0();                 // 0x00b5cde0
    void  op0F6F0();                 // 0x00b0f6f0
    char  op5C0DD0();                // 0x005c0dd0
    void  setVisible(int);           // 0x00dd8da0
    void  setupB10(int, int);        // 0x00ad8b10
    int   fnD1A0();                  // 0x00add1a0
    int   fnC490();                  // 0x00adc490
    void  fnDC60();                  // 0x00addc60
    void  fnDB50();                  // 0x00addb50
    char  fnB2A0(void*, void*);      // 0x00adb2a0
    void  fnD2C9B0();                // 0x00d2c9b0
    void* getTribe();                // 0x00c22f50
    int   fnC14750(int);             // 0x00c14750
    char  fnC232C0();                // 0x00c232c0
    void  fnC26C80();                // 0x00c26c80
    void  fnB453A0(void*);           // 0x00b453a0
    void  removeNoun(void*);         // 0x00b225d0
    void  htBegin(void*);            // 0x00594410
    void  copyViewer(void*, char, char); // 0x007c50b0
    void* camLoc(void*);             // 0x00ad7b90
};

// ------------------------------------------------------------- message object
struct Msg {                                         // SP::MessageBasicRC<5>, 0x40 bytes
    void* vtbl;                                      // +0x00
    volatile long rc;                                // +0x04
    u32 f08, f0c, f10, f14, f18, f1c;                // +0x08
    u32 pad20[4];                                    // +0x20
    u32 id;                                          // +0x30
    u32 pad34;                                       // +0x34
    u32 f38;                                         // +0x38
    u32 f3c;                                         // +0x3c
    void Destruct();                                 // 0x00421cf0
};

// ------------------------------------------------------------- support types
struct Screen {
    void show(char);                                 // 0x00ad87d0
};

struct EditorRes {                                   // 0x34 bytes
    void* vt0; int f4; void* vt8; void* fC;
    float f10, f14, f18, f1c, f20, f24;
    u8 b28, b29, b2a, b2b, b2c, b2d, b2e;
    int f30;
    EditorRes* copyCtor(EditorRes*);                 // 0x00ad7ca0
};

struct CamData { float f[0x0d]; };                   // 0x34-byte camera placement

// ------------------------------------------------------------- the simulator object
struct Sim {
    char raw[0x200];

    void reset();                                    // 0x00adf840
    int  enterMode(int, u8, u8, u8, int);            // 0x00adfd60
    void resetAll();                                 // 0x00adffd0
    void start();                                    // 0x00ae0080
    void step(int);                                  // 0x00adb0b0
    void stopCinematic();                            // 0x00ad7d60
};

// The per-frame tick runs on a sibling sub-object four bytes above Sim.
struct SimB {
    char raw[0x200];
    void tick(int, int);                             // 0x00ae00d0
};

// ------------------------------------------------------------- cinematic object context
namespace Simulator {
struct cObjectContext {
    void* vt0;      // +0x00
    int   f04;      // +0x04
    void* vt08;     // +0x08
    int   f0c;      // +0x0c
    int   f10;      // +0x10
    void* f14;      // +0x14
    int   f18;      // +0x18
    int   f1c;      // +0x1c
    float f20;      // +0x20
    float f24;      // +0x24
    int   f28;      // +0x28
    int   f2c;      // +0x2c
    void* f30;      // +0x30
    void* f34;      // +0x34
    void* f38;      // +0x38
    int   f3c;      // +0x3c
    int   f40;      // +0x40
    int   f44;      // +0x44
    char  buf[0x10];// +0x48
    cObjectContext();
};
}

// ------------------------------------------------------------- tribe / noun manager
struct TribeMgr {
    char raw[0x40];
    void update();                                   // 0x00ae0700
};

// ================================================================================================
// @ 0x00adf840
void Sim::reset()
{
    *(float*)(raw + 0x34) = 0.0f;
    *(u8*)(raw + 0x38) = 0;
    *(u8*)(raw + 0x3a) = 0;
    *(u8*)(raw + 0x3b) = 0;
    *(u8*)(raw + 0x3c) = 0;
    *(float*)(raw + 0x30) = KF_15664a8;
    *(u8*)(raw + 0x3d) = 0;
    *(int*)(raw + 0x14c) = 0;
    *(int*)(raw + 0x174) = 0;
    *(float*)(raw + 0x178) = 0.0f;
    *(u8*)(raw + 0x17c) = 0;

    {
        int end = *(int*)(raw + 0x184);
        int begin = *(int*)(raw + 0x180);
        eastl_vec_insert((void*)begin, (void*)end, 0);
        *(int*)(raw + 0x184) += ((end - begin) >> 2) * -4;
    }

    if (*(int*)(raw + 0x160) != 0) {
        Ops* gt = (Ops*)SP_GameTimeManager();
        if (*(int*)(raw + 0x160) == 2)
            gt->decPauseGate(0x600c4ae);
        else
            gt->decPauseGate(0x4bf38a5);
        *(int*)(raw + 0x160) = 0;
        stopCinematic();
    }

    {
        void* ms = SP_MessageServer();
        VFN(ms, 0x14, TC_iii)(ms, 0x533b6aa4, 0, 0);
    }

    {
        void* scr = *(void**)(raw + 0x44);
        if (*(u8*)((char*)scr + 0x54) != 0) {
            SPUIHelpers_EndModal(*(void**)((char*)scr + 0x4c), 0, 0);
            *(u8*)((char*)scr + 0x54) = 0;
        }
    }
    ((Screen*)*(void**)(raw + 0x44))->show(0);
    {
        void* w = *(void**)((char*)*(void**)(raw + 0x44) + 0x24);
        VFN(w, 0x7c, TC_ii)(w, 1, 0);
    }
    ((Ops*)(raw + 0x7c))->vecErase(*(void**)(raw + 0x7c), *(void**)(raw + 0x80));

    // --- hashtable at +0xb4 (buckets) / +0xb8 (bucket count)
    {
        int* b = (int*)*(int*)(raw + 0xb4);
        int node = *b;
        while (node == 0) node = *++b;
        int end = *(int*)(*(int*)(raw + 0xb4) + *(int*)(raw + 0xb8) * 4);
        while (node != end) {
            EditorRes local;
            EditorRes* cp = local.copyCtor((EditorRes*)((char*)node + 4));
            void* obj = *(void**)((char*)cp + 0xc);
            if (obj && VFN(obj, 0x10, TC_c0)(obj)) {
                if (*(u8*)((char*)cp + 0x2c) != 0) {
                    Ops* r = (Ops*)((Ops*)(raw + 0xd0))->opAddFA0((void*)node, cp);
                    r->op8E80();
                } else {
                    VFN(obj, 0xc, TC_i1)(obj, *(u8*)((char*)cp + 0x2a) ? 1 : 0);
                    VFN(obj, 4, TC_v0)(obj);
                    obj = 0;
                }
            }
            node = *(int*)((char*)node + 0x38);
            while (node == 0) node = *++b;
            if (obj) VFN(obj, 4, TC_v0)(obj);
        }
    }

    // --- hashtable at +0x94 (buckets) / +0x98 (bucket count)
    {
        int* b = (int*)*(int*)(raw + 0x94);
        int node = *b;
        while (node == 0) node = *++b;
        int end = *(int*)(*(int*)(raw + 0x94) + *(int*)(raw + 0x98) * 4);
        while (node != end) {
            EditorRes local;
            EditorRes* cp = local.copyCtor((EditorRes*)((char*)node + 4));
            void* obj = *(void**)((char*)cp + 0xc);
            if (obj && VFN(obj, 0x10, TC_c0)(obj)) {
                VFN(obj, 0xc, TC_i1)(obj, *(u8*)((char*)cp + 0x2a) ? 1 : 0);
                VFN(obj, 4, TC_v0)(obj);
                obj = 0;
            }
            node = *(int*)((char*)node + 0x38);
            while (node == 0) node = *++b;
            if (obj) VFN(obj, 4, TC_v0)(obj);
        }
    }

    ((Ops*)(raw + 0x90))->vecDestroy(*(void**)(raw + 0x94), *(void**)(raw + 0x98));
    *(int*)(raw + 0x9c) = 0;
    ((Ops*)(raw + 0xb0))->vecDestroy(*(void**)(raw + 0xb4), *(void**)(raw + 0xb8));
    *(int*)(raw + 0xbc) = 0;
    step(0);

    // --- hashtable at +0xf4 (buckets) / +0xf8 (bucket count)
    {
        int* b = (int*)*(int*)(raw + 0xf4);
        int node = *b;
        while (node == 0) node = *++b;
        int end = *(int*)(*(int*)(raw + 0xf4) + *(int*)(raw + 0xf8) * 4);
        while (node != end) {
            int id = *(int*)((char*)node + 4);
            void* sys = EA_Audio_GetSystemAT();
            if (sys) VFN(sys, 0x2c, TC_i1)(sys, id);
            node = *(int*)((char*)node + 0xc);
            while (node == 0) node = *++b;
        }
    }
    ((Ops*)(raw + 0xf0))->vecRelease(*(void**)(raw + 0xf4), *(void**)(raw + 0xf8));
    *(int*)(raw + 0xfc) = 0;
    ((Ops*)this)->opDE00(*(int*)(raw + 0x148));

    if (*(u8*)(raw + 0x2a) != 0) {
        void* app = SP_App();
        if (*(int*)(raw + 0x158) == VFN(app, 0x38, TC_i0)(app)) {
            void* o = *(void**)(raw + 0x168);
            *(u8*)((char*)o + 0x10b) = 1;
            VFN(o, 0x58, TC_p0)(o);
            if (*(u8*)(raw + 0x171) != 0) {
                void* app2 = SP_App();
                void* r = VFN(app2, 0x58, TC_pii)(app2, 0, 0);
                ((Ops*)*(void**)(raw + 0x40))->copyViewer(r, 0, 0);
            }
            void* app3 = SP_App();
            void* v = *(void**)(raw + 0x40);
            void* r2 = VFN(app3, 0x58, TC_piii)(app3, (int)v, 0, 0);
            ((Ops*)r2)->copyViewer(v, 0, 0);
            void* q = FUN_00b3d230(*(void**)(raw + 0x144));
            ((Ops*)q)->op5CDE0();
            void* cam = FUN_00b3d280();
            if (cam) ((Ops*)cam)->op0F6F0();
        }
    }

    {
        u32 u = *(u8*)(raw + 0x170);
        *(u8*)(raw + 0x171) = 0;
        void* el = SP_EventLog();
        ((Ops*)el)->setVisible((int)u);
    }
    *(int*)(raw + 0x2c) = 0;
    *(u8*)(raw + 0x15d) = 0;
    *(u8*)(raw + 0x2a) = 0;
    *(int*)(raw + 0x154) = -1;
    *(u8*)(raw + 0x15c) = 0;
    {
        void* o = *(void**)(raw + 0x140);
        VFN(o, 0x28, TC_i1)(o, *(int*)(raw + 0x14c));
    }
    {
        void* bm = SP_BehaviorManager();
        VFN(bm, 0x2c, TC_v0)(bm);
    }
    {
        void** p = *(void***)(raw + 0x1ac);
        while (p != *(void***)(raw + 0x1b0)) {
            void* o = *p;
            if (o && VFN(o, 0xac, TC_p0)(o)) {
                void* r = VFN(o, 0xac, TC_p0)(o);
                *(int*)((char*)r + 4) |= 1;
            }
            p++;
        }
    }
    {
        void* begin = *(void**)(raw + 0x1ac);
        void* end = *(void**)(raw + 0x1b0);
        char* r = (char*)FUN_00c83c90(end, end, begin);
        while (r < (char*)end) {
            void* o = *(void**)r;
            if (o) VFN(o, 0xc0, TC_v0)(o);
            r += 4;
        }
        *(int*)(raw + 0x1b0) += (((int)end - (int)begin) >> 2) * -4;
    }
    {
        void* ms = SP_MessageServer();
        VFN(ms, 0x14, TC_iii)(ms, 0x604c6f4, 0, 0);
    }
}

// ================================================================================================
// @ 0x00adfd60
int Sim::enterMode(int mode, u8 a2, u8 a3, u8 a4, int a5)
{
    if (mode == -1)
        return 0;

    if (*(int*)(raw + 0x2c) != 0) {
        if (a3 == 0)
            return 0;
        int* p = *(int**)(raw + 0x128);
        int pair[2];
        pair[0] = mode;
        *(u8*)&pair[1] = a2;
        if (p + 2 != *(int**)(raw + 0x130)) {
            *(int**)(raw + 0x128) = p + 2;
            if (p) {
                p[0] = pair[0];
                p[1] = pair[1];
            }
        } else {
            FUN_00d2ca90(pair);
        }
        return mode;
    }

    *(int*)(raw + 0x2c) = 1;
    *(u8*)(raw + 0x28) = 0;
    *(u8*)(raw + 0x29) = 0;
    *(u8*)(raw + 0x2b) = 0;
    *(int*)(raw + 0x174) = 0;
    *(float*)(raw + 0x178) = 0.0f;
    *(u8*)(raw + 0x17c) = 0;
    {
        int end = *(int*)(raw + 0x184);
        int begin = *(int*)(raw + 0x180);
        eastl_vec_insert((void*)begin, (void*)end, 0);
        *(int*)(raw + 0x184) += ((end - begin) >> 2) * -4;
    }
    {
        void* em = SP_EffectsManager();
        VFN(em, 0x98, TC_ii)(em, 6, 1);
    }
    *g_pModeFlags |= 4;

    {
        void** p = *(void***)(raw + 0x1ac);
        while (p != *(void***)(raw + 0x1b0)) {
            void* o = *p;
            if (o && VFN(o, 0xac, TC_p0)(o)) {
                void* r = VFN(o, 0xac, TC_p0)(o);
                *(int*)((char*)r + 4) |= 1;
            }
            p++;
        }
    }
    ((Ops*)(raw + 0x1ac))->vecEraseAuto(*(void**)(raw + 0x1ac), *(void**)(raw + 0x1b0));

    {
        void* el = SP_EventLog();
        *(u8*)(raw + 0x170) = (u8)((Ops*)el)->op5C0DD0();
        ((Ops*)el)->setVisible(0);
    }
    if (FUN_00b7c780())
        FUN_00b7c810(1);

    ((Ops*)this)->setupB10((int)a2, a5);
    *(int*)(raw + 0x154) = -1;
    *(int*)(raw + 0x148) = mode;
    {
        void* o = *(void**)(raw + 0x140);
        if (!VFN(o, 0x24, TC_c0)(o)) {
            const char* s = (const char*)VFN(o, 0x38, TC_psr)(o, S_switchExit);
            VFN(o, 0x28, TC_i1)(o, (int)s);
        } else {
            VFN(o, 0x28, TC_i1)(o, mode);
        }
    }
    {
        void* gim = SP_GameInputManager();
        ++*(int*)((char*)gim + 0x110);
    }
    *(u8*)(raw + 0x171) = 0;

    if (a4 != 0) {
        Msg msg;
        msg.id = 0;
        msg.vtbl = VT_13eb90c;
        _InterlockedExchange(&msg.rc, 0);
        msg.vtbl = VT_13eb844;
        msg.f38 = 0;
        msg.id = 0x46ac0ac;
        msg.f08 = 0;
        msg.f10 = 0;
        msg.f18 = 0;
        void* ms = SP_MessageServer();
        VFN(ms, 0x14, TC_iiiv)(ms, 0x46ac0ac, &msg, 0);
        msg.Destruct();
    }
    {
        void* ms = SP_MessageServer();
        VFN(ms, 0x14, TC_iii)(ms, 0x604c6e0, 0, 0);
    }
    return mode;
}

// ================================================================================================
// @ 0x00adffd0
void Sim::resetAll()
{
    if (*(int*)(raw + 0x2c) == 0)
        return;
    reset();
    {
        void* em = SP_EffectsManager();
        VFN(em, 0x98, TC_ii)(em, 6, 0);
        *g_pModeFlags &= ~4;
        void* gim = SP_GameInputManager();
        --*(int*)((char*)gim + 0x110);
    }
    {
        Msg msg;
        msg.id = 0;
        msg.vtbl = VT_13eb90c;
        _InterlockedExchange(&msg.rc, 0);
        msg.vtbl = VT_13eb844;
        msg.f38 = 0;
        msg.f08 = *(int*)(raw + 0x148);
        *(int*)(raw + 0x148) = 0;
        void* ms = SP_MessageServer();
        VFN(ms, 0x14, TC_iiiv)(ms, 0x44f1189, &msg, 0);
        msg.Destruct();
    }
}

// ================================================================================================
// @ 0x00ae0080
void Sim::start()
{
    if (*(int*)(raw + 0x2c) == 0)
        return;
    step(1);
    if (*(int*)(raw + 0x154) == -1) {
        resetAll();
        return;
    }
    *(int*)(raw + 0x150) = *(int*)(raw + 0x154);
    *(u8*)(raw + 0x15d) = 1;
    void* p = *(void**)(raw + 0x16c);
    if (p)
        *(u8*)((char*)p + 0x3c) = 0;
    *(u8*)(raw + 0x3d) = 1;
}

// ================================================================================================
// @ 0x00ae00d0
void SimB::tick(int a1, int a2)
{
    {
        void* o = *(void**)(raw + 0x13c);
        VFN(o, 0x18, TC_v0)(o);
    }
    Sim* sim = (Sim*)(raw - 4);
    ((Ops*)sim)->fnDC60();

    if (*(int*)(raw + 0x28) == 0) {
        if (*(int*)(raw + 0x114) == *(int*)(raw + 0x124))
            return;
        if (*(u8*)(raw + 0x15b) == 0)
            return;
        int* e = *(int**)(raw + 0x114);
        sim->enterMode(e[0], (u8)e[1], 0, 0, 0);
        ((Ops*)(raw + 0x10c))->fnD2C9B0();
        return;
    }
    if (*(int*)(raw + 0x28) == 1)
        return;

    {
        void* gt = SP_GameTimeManager();
        if (((Ops*)gt)->pauseGates(0x4bf38a8) > 0)
            ((Ops*)gt)->togglePause(0x4bf38a8);
    }

    float f = (float)a2;
    if (a2 < 0) f += KF_13f4fd0;
    if (f == 0.0f) {
        float f2 = (float)a1;
        if (a1 < 0) f2 += KF_13f4fd0;
        if (f2 > 0.0f) f = f2;
    }
    float delta = f * KF_13f9428;

    if (*(u8*)(sim->raw + 0x38) != 0 && *(u8*)(sim->raw + 0x3a) == 0) {
        float v = *(float*)(sim->raw + 0x34) - delta;
        *(float*)(sim->raw + 0x34) = v;
        if (!(v > 0.0f))
            *(u8*)(sim->raw + 0x38) = 0;
    }

    int b4 = ((Ops*)sim)->fnD1A0();
    int c490 = ((Ops*)sim)->fnC490();

    // --- vector of slots at +0x7c/+0x80
    void** begin = *(void***)(raw + 0x7c);
    int count = (int)((*(int*)(raw + 0x80) - *(int*)(raw + 0x7c)) >> 2);
    for (int i = 0; i < count; i++) {
        char* elem = (char*)begin[i];
        if (!elem) continue;
        int f0c = *(int*)(elem + 0xc);
        int (*fn)(int, int) = *(int(__cdecl**)(int, int))(elem + 0x10);
        if (fn(f0c, 0) == 1) {
            begin[i] = 0;
            void* vt = *(void**)(elem + 8);
            VFN(vt, 4, TC_v0)((void*)elem);
        }
    }
    {
        void** end = *(void***)(raw + 0x80);
        void** p = begin;
        while (p != end) {
            if (*p == 0) {
                if (p != end)
                    p = FUN_00ad81b0(p + 1, end, p, FUN_00ad71f0);
                break;
            }
            p++;
        }
        ((Ops*)(raw + 0x7c))->vecErase(p, *(void**)(raw + 0x80));
    }

    bool b5;
    if (*(float*)(sim->raw + 0x30) == KF_15664a8) {
        b5 = false;
    } else {
        float v = *(float*)(sim->raw + 0x30) - delta;
        *(float*)(sim->raw + 0x30) = v;
        b5 = true;
        if (v > 0.0f)
            b5 = false;
    }

    bool al = (*(int*)(raw + 0x7c) == *(int*)(raw + 0x80)) && (b4 == 1) && (c490 == 1);
    bool bl = (*(u8*)(sim->raw + 0x34) == 0) && al;

    if (al) {
        if (*(u8*)(sim->raw + 0x37) == 1 &&
            !(VFN(*(void**)((char*)*(void**)(sim->raw + 0x44) + 0x20), 0x28, TC_i0)
                  (*(void**)((char*)*(void**)(sim->raw + 0x44) + 0x20)) & 1)) {
            char* w = (char*)*(void**)(sim->raw + 0x44);
            VFN(*(void**)(w + 0x20), 0x7c, TC_ii)(*(void**)(w + 0x20), 1, 1);
            VFN(*(void**)(w + 0x2c), 0x7c, TC_ii)(*(void**)(w + 0x2c), 1, 1);
            VFN(*(void**)(w + 0x28), 0x7c, TC_ii)(*(void**)(w + 0x28), 1, 0);
            void* mgr = EA_UTFWin_GetManager();
            VFN(mgr, 0x4c, TC_ii)(mgr, 0, (int)*(void**)(w + 0x20));
        } else if (*(u8*)(sim->raw + 0x38) == 1 &&
                   (VFN(*(void**)((char*)*(void**)(sim->raw + 0x44) + 0x28), 0x28, TC_i0)
                        (*(void**)((char*)*(void**)(sim->raw + 0x44) + 0x28)) & 1)) {
            char* w = (char*)*(void**)(sim->raw + 0x44);
            VFN(*(void**)(w + 0x28), 0x7c, TC_ii)(*(void**)(w + 0x28), 1, 1);
            VFN(*(void**)(w + 0x2c), 0x7c, TC_ii)(*(void**)(w + 0x2c), 1, 1);
            VFN(*(void**)(w + 0x20), 0x7c, TC_ii)(*(void**)(w + 0x20), 1, 0);
            void* mgr = EA_UTFWin_GetManager();
            VFN(mgr, 0x4c, TC_ii)(mgr, 0, (int)*(void**)(w + 0x28));
        }
    }

    if (b5 || bl || *(u8*)(sim->raw + 0x39) != 0)
        ((Ops*)sim)->fnDB50();

    if (*(int*)(raw + 0x170) != 0) {
        if (*(u8*)(raw + 0x178) != 0) {
            CamData loc;
            void* m = FUN_00b3d240();
            VFN(m, 0x44, TC_pvi)(m, (void*)loc.f, 1);
            FUN_00b3d3c0(loc.f, *(int*)(raw + 0x174), *(int*)(raw + 0x170), 0, 0);
            FUN_00b76d20(loc.f, *(int*)(raw + 0x174), *(int*)(raw + 0x170), 0, 0);
        }
        int cnt = (int)((*(int*)(raw + 0x180) - *(int*)(raw + 0x17c)) >> 2);
        for (int i = 0; i < cnt; i++) {
            CamData cd;
            cd.f[0] = KF_167a548;
            cd.f[1] = KF_167a54c;
            cd.f[2] = KF_167a550;
            cd.f[4] = 0.0f;
            cd.f[5] = 0.0f;
            cd.f[6] = 0.0f;
            cd.f[7] = 0.0f;
            cd.f[8] = KF_1485720;
            cd.f[9] = KF_1485720;
            cd.f[10] = KF_1485720;
            cd.f[11] = KF_1485720;
            cd.f[12] = 0.0f;
            void* elem = *(void**)(*(int*)(raw + 0x17c) + i * 4);
            if (((Ops*)sim)->fnB2A0(elem, cd.f)) {
                CamData out;
                ((Ops*)sim)->camLoc(out.f);
                FUN_00b3d3c0(out.f, *(int*)(raw + 0x174), *(int*)(raw + 0x170), 1, 0);
                FUN_00b76d20(out.f, *(int*)(raw + 0x174), *(int*)(raw + 0x170), 1, 0);
            }
        }
    }
}

// ================================================================================================
// @ 0x00ae0640
Simulator::cObjectContext::cObjectContext()
{
    *(void**)((char*)this + 8) = (void*)VT_13ec458;
    this->f0c = 0;
    this->vt0 = (void*)VT_145b918;
    this->vt08 = (void*)VT_145b908;
    this->f20 = KF_1485720;
    this->f24 = KF_1470f1c;
    this->f1c = 0;
    this->f28 = 0;
    this->f18 = 1;
    this->f14 = (void*)D_154df28;
    this->f44 = 0;
    char* p = (char*)this + 0x48;
    this->f30 = p;
    this->f34 = p;
    this->f38 = p + 0x10;
}

// ================================================================================================
// @ 0x00ae0700
void TribeMgr::update()
{
    void* nm = SP_NounManager();
    void* other = FUN_00b3d310();

    if (nm && other) {
        int it[2];
        ((Ops*)(raw + 0x10))->htBegin(it);
        int end = *(int*)(*(int*)(raw + 0x14) + *(int*)(raw + 0x18) * 4);
        int node = it[0];
        int* b = (int*)it[1];
        if (node != end) {
            do {
                void* o30 = *(void**)((char*)node + 0x30);
                if (o30) {
                    char* e = (char*)VFN(o30, 0xb8, TC_pi)(o30, 0xce9f6639);
                    if (e && *(int*)(e + 0xb54) != 0) {
                        if (*(u8*)(e + 0xb5e) == 0)
                            ((Ops*)e)->fnC14750(1);
                        if (((*(u32*)(e + 0xb58) >> 9) & 1) == 0) {
                            void* slot = *(void**)(e + 0xb54);
                            void* p = VFN(slot, 0x70, TC_p0)(slot);
                            VFN(p, 0x40, TC_iii)(p, (int)slot, 4, 1);
                        }
                        ((Ops*)other)->fnB453A0((void*)(e + 0xc0));
                        if (VFN(e, 0x20, TC_p0)(e) == (void*)0x18eb4b7 &&
                            ((Ops*)e)->fnC232C0())
                            ((Ops*)e)->fnC26C80();
                    }
                }
                node = *(int*)((char*)node + 0x34);
                while (node == 0) {
                    b++;
                    node = *b;
                }
            } while (node != end);
        }
    }

    void** p = *(void***)(raw + 0x30);
    void** pend = *(void***)(raw + 0x34);
    for (; p != pend; p++) {
        void* noun = *p;
        char* cit = 0;
        if (noun)
            cit = (char*)VFN(noun, 0xc, TC_pi)(noun, 0xce9f6639);
        if (!cit) {
            ((Ops*)nm)->removeNoun(noun);
        } else if (*(u8*)(cit + 0x135) != 0) {
            if (VFN(cit, 0x20, TC_p0)(cit) == (void*)0x18eb4b7 &&
                ((Ops*)cit)->getTribe() != 0) {
                void* tribe = ((Ops*)cit)->getTribe();
                VFN(tribe, 0x9c, TC_ii)(tribe, (int)cit, 1);
            } else {
                VFN(cit, 0xc8, TC_i1)(cit, 0);
            }
        }
    }
}
