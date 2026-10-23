// Slice s00ef16a0 -- SP::Simulator scenario-mode key handler, initialiser and teardown.
//
//   0x00ef16a0  Sim::HandleKey                  (key/state dispatch, scenario modes)
//   0x00ef1930  Sim::FUN_00ef1930               (forward to sub-object +0x70)
//   0x00ef1990  FUN_00ef1990                    (count hash entries of stride 0x238)
//   0x00ef19f0  FUN_00ef19f0                    (zero a global record, return it)
//   0x00ef1a50  FUN_00ef1a50                    (create + register the record factory)
//   0x00ef1ad0  Sim::FUN_00ef1ad0               (destroy owned containers)
//   0x00ef1b70  Sim::FUN_00ef1b70               (hash insert helper)
//   0x00ef1c40  Sim::FUN_00ef1c40               (flush dirty input list)
//   0x00ef1ca0  Sim::FUN_00ef1ca0               (reset scenario systems)
//   0x00ef1e00  Sim::FUN_00ef1e00               (full scenario init)
//   0x00ef2370  Sim::FUN_00ef2370               (register message handlers)
//   0x00ef24d0  Sim::FUN_00ef24d0               (unregister + teardown)
//   0x00ef25a0  Sim::FUN_00ef25a0               (enter scenario mode)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"
#include <intrin.h>

typedef unsigned char u8;
typedef unsigned int  u32;

#define VFN(o, off, T) ((T)(*(void***)(o))[((off) >> 2)])

typedef void  (__thiscall *TC_v)(void*);
typedef void  (__thiscall *TC_vi)(void*, int);
typedef void  (__thiscall *TC_vii)(void*, int, int);
typedef void  (__thiscall *TC_vpii)(void*, int, void*, int);
typedef void  (__thiscall *TC_vpp)(void*, void*, void*);
typedef void  (__thiscall *TC_vp)(void*, void*);
typedef void  (__thiscall *TC_vpiii)(void*, void*, int, int, int, int);
typedef void  (__thiscall *TC_viii)(void*, int, int, int);
typedef u8    (__thiscall *TC_c)(void*);
typedef u8    (__thiscall *TC_ci)(void*, int);
typedef u8    (__thiscall *TC_cii)(void*, int, int);
typedef u8    (__thiscall *TC_cc)(void*, int, int);
typedef void* (__thiscall *TC_p)(void*);
typedef void* (__thiscall *TC_pi)(void*, int);
typedef void  (__thiscall *TC_vf)(void*, float);
typedef float (__thiscall *TC_pf)(void*);

// ------------------------------------------------------------- cdecl callees
extern "C" void* __cdecl EAAllocate(u32 size, const char* name, int, int, int, int); // 0xf473a0
extern "C" void* __cdecl ZoneObject_new(u32 size, const char* name, int, int, int, int); // 0x926020
extern "C" void  __cdecl op_delete(void* p);                                          // 0xf47380
extern "C" int   __cdecl FUN_00ef1990_c(u32* a, u32* b);                              // 0xef1990
extern "C" void  __cdecl eastl_vector_insert(void* dst, const void* src, u32 bytes);  // 0x11e0744
extern "C" int*  __cdecl FUN_00b18e00(u32);                                           // 0xb18e00
extern "C" /* +0x98 */ void* __cdecl FUN_00c77680(void*, void*);                      // 0xc77680
extern "C" void  __cdecl FUN_008dfcd0(void*, void*, u32);                             // 0x8dfcd0
extern "C" u8    __cdecl FUN_00401d90(void*);                                         // 0x401d90
extern "C" void  __cdecl FUN_00b96600(void*, void*);                                  // 0xb96600
extern "C" void  __cdecl FUN_0093dc70(void** buckets, u32 n);                         // 0x93dc70
extern "C" void  __cdecl FUN_00d01790(int);                                           // 0xd01790
extern "C" void  __cdecl FUN_0041e4d0(int);                                           // 0x41e4d0
extern "C" void  __cdecl FUN_0050f740(void*, void*, void*);                           // 0x50f740
extern "C" int   __cdecl FUN_00ff3f00(int);                                           // 0xff3f00
extern "C" int*  __cdecl FUN_00eec0d0(int);                                           // 0xeec0d0
extern "C" int   __fastcall FUN_00f3be30(void*);                                      // 0xf3be30 (thiscall)
extern "C" int   __cdecl FUN_00efc520(void);                                          // 0xefc520
extern "C" void  __cdecl FUN_00efc8c0(int);                                           // 0xefc8c0
extern "C" int   __cdecl GetRecorderState(void);                                      // 0x435e90
extern "C" void  __cdecl KillSetiEffects(int, int);                                   // 0x435ed0
extern "C" int*  __fastcall FUN_006c0200(void*);                                      // 0x6c0200 (thiscall)
extern "C" void  __fastcall FUN_00ee31d0(void*);                                      // 0xee31d0 (thiscall)
extern "C" int   __cdecl FUN_00f924e0(float);                                         // 0xf924e0
extern "C" void  __fastcall FUN_00ef72c0(void*);                                      // 0xef72c0 (thiscall, no args)
extern "C" int   __cdecl VerbTray_HandleKeyPress(int key);                            // 0xd4a4a0
extern "C" void  __cdecl FUN_00ebf160(void);                                          // 0xebf160
extern "C" void* __cdecl FUN_00b60a50(int);                                           // 0xb60a50
// --- scenario init (00ef1e00) callees (only the ones not declared elsewhere) ---
extern "C" void  __cdecl FUN_00f09580(void);                                          // 0xf09580  CreateBubblePanels
extern "C" void  __cdecl FUN_00f08ef0(void);                                          // 0xf08ef0  CreateMarkerTextDialogs
extern "C" int   __fastcall FUN_00f1e620(void*);                                      // 0xf1e620
// thiscall with stack arguments: modelled as never-defined member functions.
struct Stub37f { void F(void* p); };            // 0xf37f20
struct Stub447 { void F(u8 b); };               // 0xf447f0
struct Stub660 { void F(const void* p); };      // 0x6609a0  KeyVec assign
struct Stub466 { u8 F(const void* p); };        // 0xf46630
struct Stub425 { void F(void* p); };            // 0xf42580
struct Stub12d { void F(int v); };              // 0xef12d0
struct Stub697a { void F(u32 key, u32 state); };// 0x697a50  cLocalInputState::OnKeyDown
struct StubED9E { u8 F(int a); };               // 0xed9e60
struct StubF069 { void F(int a); };             // 0xf069a0  BeginRecording
struct StubC776 { void* F(void* out, void* key); }; // 0xc77680  hashtable find
struct Stub8DF  { void F(void* a, void* b, u32 c); }; // 0x8dfcd0  insertNode3
struct Stub4E19 { void F(void* p); };           // 0x4e19a0  SpVector<FillEntry>::push_back
struct StubB966 { void F(void* pos, void* val); }; // 0xb96600  vector insert
struct HashFindOut { u32 a, b, c; };
// --- ctors (thiscall, return this in eax) ---
extern "C" void* __fastcall FUN_00f33f90_c(void*);                                    // 0xf33f90
extern "C" void* __fastcall FUN_00f1e450_c(void*);                                    // 0xf1e450
extern "C" void* __fastcall FUN_00f3fad0_c(void*);                                    // 0xf3fad0
extern "C" void* __fastcall FUN_00f0fef0_c(void*);                                    // 0xf0fef0
extern "C" void* __fastcall FUN_00f11b60_c(void*);                                    // 0xf11b60
extern "C" void* __fastcall FUN_00ef9d90_c(void*);                                    // 0xef9d90
extern "C" void* __fastcall FUN_00f04740_c(void*);                                    // 0xf04740
extern "C" void* __fastcall FUN_00edaa80_c(void*);                                    // 0xedaa80
extern "C" void* __fastcall FUN_00ed5220_c(void*);                                    // 0xed5220
extern "C" void* __fastcall FUN_00ebc120_c(void*);                                    // 0xebc120
extern "C" void  __fastcall FUN_00b5cde0(void*);                                      // 0xb5cde0 (thiscall)
extern "C" void  __cdecl CreateBubblePanels(void);                                    // 0xf09580
extern "C" void  __cdecl CreateMarkerTextDialogs(void);                               // 0xf08ef0
extern "C" void  __cdecl FUN_00ec92b0(void);                                          // 0xec92b0
extern "C" int*  __cdecl FUN_010408b0(void);                                          // 0x10408b0
extern "C" void  __fastcall FUN_01041bc0(void*);                                      // 0x1041bc0 (thiscall)
extern "C" void  __cdecl FUN_00f02c10(void);                                          // 0xf02c10
extern "C" void  __cdecl FUN_00f20fe0(void);                                          // 0xf20fe0
extern "C" void  __cdecl FUN_00f24d30(void);                                          // 0xf24d30
extern "C" void  __cdecl FUN_00eed090(void);                                          // 0xeed090
extern "C" void  __cdecl FUN_00ec4650(void*);                                         // 0xec4650
extern "C" void  __cdecl FUN_00ec51a0(void*);                                         // 0xec51a0
extern "C" void  __cdecl LoadCreatureGameplayTuning(int, int);                        // 0xd3d870
extern "C" void* __stdcall GetTriggerMgr(int);                                        // 0xb3d4d0
extern "C" void  __cdecl FUN_00adf390(int);                                           // 0xadf390 (thiscall TriggerMgr) UNUSED
extern "C" int   __stdcall GetSetting5(int);                                          // 0x401050
extern "C" void  __cdecl FUN_0045b150(int);                                           // 0x45b150 (thiscall)
extern "C" void  __cdecl RemoveHandler(void*, void*, void*, int, int);                // 0x571db0
extern "C" void* __fastcall FUN_00ec4bb0_r(void*);                                    // 0xec4bb0 (ctor)
extern "C" void* __fastcall FUN_00f391c0_r(void*);                                    // 0xf391c0 (ctor)
extern "C" void  __fastcall FUN_00ec4650_f(void*);                                    // 0xec4650 (thiscall, no args)
extern "C" void  __fastcall FUN_00ec51a0_f(void*);                                    // 0xec51a0 (thiscall, no args)
extern "C" int   __fastcall FUN_00ff3f00_f(void*);                                    // 0xff3f00 (thiscall, no args)
extern "C" int   __cdecl LAB_00ef2330(void);                                          // 0xef2330

// ------------------------------------------------------------- accessor thunks (cdecl, no args)
extern "C" void* __cdecl FUN_00b3d310(void);        // 0xb3d310
extern "C" void* __cdecl FUN_00b3d330(void);        // 0xb3d330  SimTicker
extern "C" void* __cdecl FUN_00b3d230(int);         // 0xb3d230
extern "C" void* __cdecl FUN_00b3d380(void);        // 0xb3d380  GameTimeManager
extern "C" void* __cdecl FUN_00d539d0(void);        // 0xd539d0  cPosseSimulator::Instance
extern "C" void* __cdecl FUN_00675250(void);        // 0x675250  AchievementsController
extern "C" void* __cdecl FUN_00b3d300(void);        // 0xb3d300  NounManager
extern "C" void* __fastcall FUN_00b1fdb0(void*);     // 0xb1fdb0  cGameNounManager::GetAvatar (thiscall)
extern "C" void* __cdecl FUN_0067ddd0(void);        // 0x67ddd0  EffectsManager
extern "C" void* __cdecl FUN_0067dcd0(void);        // 0x67dcd0  GetManager
extern "C" void* __cdecl FUN_0067dd10(void);        // 0x67dd10  SP::App
extern "C" void* __cdecl FUN_0067dcc0(void);        // 0x67dcc0  SP::MessageServer
extern "C" void* __cdecl FUN_0067dd50(void);        // 0x67dd50
extern "C" void* __cdecl FUN_0067de40(void);        // 0x67de40
extern "C" void* __cdecl FUN_00b3d250(void);        // 0xb3d250  GameInputManager

// ------------------------------------------------------------- raw thiscall callees (this in ecx)
struct Sub70 { void FUN_00ebdc20(int a, float b); };  // 0xebdc20 (thiscall)
extern "C" void __fastcall FUN_00697980(void*);                      // 0x697980  cLocalInputState::Reset
extern "C" void __fastcall FUN_00676f20(void*);                      // 0x676f20  DecrementAccumulatorValue
extern "C" void __fastcall FUN_00d272e0(void*);                      // 0xd272e0  ToggleFreeCamera
extern "C" int  __fastcall FUN_00d20940(void*);                      // 0xd20940
extern "C" void __fastcall FUN_00b32220(void*, int);                 // 0xb32220  IncPauseGate
extern "C" void __fastcall FUN_00b316d0(void*, float, float, float, float); // 0xb316d0
extern "C" void __fastcall FUN_00ef9e40(void*);                      // 0xef9e40  cScenarioTutorials::Reset
extern "C" void __fastcall FUN_00f06ce0(void*);                      // 0xf06ce0  RegisterMessageHandlers
extern "C" void __fastcall FUN_00ed5d70(void*);                      // 0xed5d70
extern "C" void __fastcall FUN_00ebd220(void*);                      // 0xebd220
extern "C" void __fastcall FUN_0041e4d0_(void*);                     // 0x41e4d0  Reserve

struct TriggerMgr { void FUN_00adf390(); };                           // 0xadf390 (thiscall, no args)
struct Setter    { void FUN_0045b150(); };                            // 0x45b150 (thiscall, no args)
struct GTM       { void FUN_00b316d0(float, float, float, float); void FUN_00b32220(int); };   // 0xb316d0/0xb32220 (thiscall)

struct Vec2v {                                                        // eastl vector of 4-byte elems
    void* mpBegin; void* mpEnd; void* mpCapacity; u32 mAlloc;
    void Reserve(int n);                  // 0xd01790 (thiscall, ret 4)
    void Reserve4(int n);                 // 0x41e4d0 (thiscall, ret 4)
    void Erase(void* first, void* last);  // 0x50f740 (thiscall, ret 8)
};

// ------------------------------------------------------------- globals
extern "C" char  G_15acc30[];      // 0x15acc30  the Sim singleton
extern "C" char  G_15accc8[];      // 0x15accc8  the scenario record
extern "C" int   G_15acc34;        // 0x15acc34  active mode
extern "C" int   G_15acc2c;        // 0x15acc2c
extern "C" int   G_15accec;        // 0x15accec
extern "C" int   G_15accf0;        // 0x15accf0
extern "C" int   G_15acce0;        // 0x15acce0
extern "C" char  G_15accf8[];      // 0x15accf8
extern "C" int*  G_16c7aa4;        // 0x16c7aa4
extern "C" void* G_16c7b30;        // 0x16c7b30  record factory RefPtr
extern "C" void* G_13effa8[];      // 0x13effa8  base record vtbl
extern "C" void* G_148b0b4[];      // 0x148b0b4  derived record vtbl
extern "C" float G_14853e0;        // 0x14853e0
extern "C" float G_1470f1c;        // 0x1470f1c
extern "C" void* G_148b018[];      // 0x148b018  listener id table (8 entries)
extern "C" void* G_13ebc58[];      // 0x13ebc58  "App"

// ------------------------------------------------------------- container models
struct HT3 {                       // eastl hashtable, 0x20 bytes
    u32   mHead;       // +0x00
    void* mpBuckets;   // +0x04
    u32   mnElements;  // +0x08
    u32   mAlloc;      // +0x0c
    u32   pad1[4];
    void DoFreeNodes(void* buckets, u32 n);   // 0x93dc70 (thiscall, ret 8)
};

struct ModelVector {               // eastl::vector<AutoRefCount<cMWModel>>
    void* mpBegin; void* mpEnd; void* mpCapacity; u32 mAlloc;
    void DoDestroyValues(void* first, void* last);   // 0x5f3680
};

// ------------------------------------------------------------- the singleton
struct cSim {
    u8    b00;         // +0x00
    u8    bDirty;      // +0x01
    char  pad02[0xe];  // +0x02
    void* p10;         // +0x10
    void* p14;         // +0x14
    void* p18;         // +0x18
    void* p1c;         // +0x1c
    char  input[0xc];  // +0x20
    HT3   ht;          // +0x2c
    char  pad4c[0x14]; // +0x4c
    void* p60;         // +0x60
    char  pad64[4];    // +0x64
    void* p68;         // +0x68
    void* p6c;         // +0x6c
    void* p70;         // +0x70
    void* v74;         // +0x74
    void* v78;         // +0x78
    void* p7c;         // +0x7c
    void* p80;         // +0x80
    void* p84;         // +0x84
    void* p88;         // +0x88
    int   n8c;         // +0x8c
    int   n90;         // +0x90
    void* p94;         // +0x94
    void* p98;         // +0x98
    void* p9c;         // +0x9c
    int   nA0;         // +0xa0
    int   nA4;         // +0xa4
    char  padA8[0x24]; // +0xa8
    int   nCC;         // +0xcc
    int   nD0;         // +0xd0
    void* pD4;         // +0xd4
    void* pD8;         // +0xd8
    u8    bDC;         // +0xdc

    u8   FUN_00ef16a0(u32 key, int state);   // 0xef16a0
    void FUN_00ef1930(int a, float b);       // 0xef1930
    void FUN_00ef1ad0(void);                 // 0xef1ad0
    void FUN_00ef1b70(u32 v);                // 0xef1b70
    void FUN_00ef1c40(void);                 // 0xef1c40
    void FUN_00ef1ca0(void);                 // 0xef1ca0
    void FUN_00ef1e00(void);                 // 0xef1e00
    u8   FUN_00ef2370(int);                 // 0xef2370
    u8   FUN_00ef24d0(void);                 // 0xef24d0
    u8   FUN_00ef25a0(void);                 // 0xef25a0
};

#define SIM ((cSim*)G_15acc30)

// ------------------------------------------------------------- raw offsets view
struct SimRaw {
    char raw[0x1000];
};

// The +0x2c hashtable is indexed through these helpers.
struct Hashtable {                 // at Sim + 0x2c
    u32   mHead;       // +0x00 (= +0x2c)
    void* mpBuckets;   // +0x04 (= +0x30)
    u32   mnElements;  // +0x08 (= +0x34)
    u32   mAlloc;      // +0x0c (= +0x38)
};

// The 0x238-byte hash node bucket walker (root and end-pointer probe).
struct HashTable238 {              // at (node - 1) ... offset-relative view
    u32* Begin() { return *(u32**)this; }
};

// ================================================================================================
// @ 0x00ef16a0
u8 cSim::FUN_00ef16a0(u32 key, int state)
{
    if (G_15acc34 != 4)
        return 1;
    ((Stub697a*)((char*)this + 0x20))->F(key, state);
    void* gim = FUN_00b3d250();
    if (VFN(gim, 0x44, TC_cii)(gim, (int)key, state)) {
        if ((key == 0x48 || key == 0x42 || key == 0xbf) && *(int*)((char*)this + 0xd4))
            FUN_00ef72c0(*(void**)((char*)this + 0xd4));
        return 1;
    }
    if (*(int*)((char*)this + 0xcc) == 2) {
        bool b = false;
        switch (state) {
        case 0: b = true; break;
        case 1: b = (key == 0x10); break;
        case 2: b = (key == 0x11); break;
        case 4: b = (key == 0x12); break;
        default: b = false; break;
        }
        if (b) {
            if (VerbTray_HandleKeyPress((int)key))
                return 1;
        }
        if (key == 0x48) {
            if (state == 6) {
                void* ac = FUN_00675250();
                FUN_00676f20(ac);
                void* av = FUN_00b1fdb0(FUN_00b3d300());
                void* sub = (char*)av + 0x5a8;
                float f = VFN(sub, 0x58, TC_pf)(sub);
                FUN_00f924e0(f);
                *(float*)((char*)av + 0xe58) = *(float*)((char*)av + 0xe5c);
                return 1;
            }
        } else if (key == 0x1b) {
            int m = *(int*)((char*)*(void**)((char*)this + 0x78) + 0x90);
            if (m == 6 || m == 5 || m == 2 || m == 0)
                return 1;
        }
        if (*(int*)((char*)this + 0xd0) != 0)
            goto L1900;
        if (key == 0x43 && state == 6) {
            void* p1 = VFN(FUN_0067dd10(), 0x50, TC_p)(FUN_0067dd10());
            u32 s = (u32)VFN(p1, 0x58, TC_p)(p1);
            void* p2 = VFN(FUN_0067dd10(), 0x50, TC_p)(FUN_0067dd10());
            void* c = VFN(p2, 0x4c, TC_pi)(p2, (int)s);
            void* cam = (void*)FUN_00b60a50((int)c);
            FUN_00d272e0(cam);
            void* d = *(void**)((char*)this + 0x68);
            u32 st = (u32)FUN_00d20940(cam);
            *(u8*)((char*)d + 0x54) = (st != 2);
            return 1;
        }
    } else if (*(int*)((char*)this + 0xcc) == 1) {
        if (key == 0x53) {
            if (state == 2) {
                void* ms = FUN_0067dcc0();
                VFN(ms, 0x14, TC_viii)(ms, 0x101, 0, 0);
                return 1;
            }
        } else if (key > 0x30 && key < 0x3a && *(int*)((char*)this + 0x10) &&
                   ((StubED9E*)*(void**)((char*)this + 0x10))->F(1)) {
            u32 n1 = (u32)FUN_00f3be30(*(void**)((char*)this + 0x74));
            u32 n2 = (u32)FUN_00efc520();
            u32 k = key - 0x31;
            if (k < n1 && k != n2) {
                FUN_00efc8c0((int)k);
                KillSetiEffects(0xe10deda0, GetRecorderState());
                FUN_00ee31d0(FUN_006c0200(*(void**)((char*)this + 0x14)));
            }
        }
    }
    if (*(int*)((char*)this + 0xd0) == 0 && key == 0x43 && state == 0) {
        ((StubF069*)*(void**)((char*)this + 0xd8))->F(1);
        return 1;
    }
L1900:
    void* gim2 = FUN_00b3d250();
    return VFN(gim2, 0x4c, TC_cii)(gim2, (int)key, state);
}

// ================================================================================================
// @ 0x00ef19f0
int* FUN_00ef19f0(void)
{
    int* p = (int*)G_15accc8;
    int z = 0;
    p[0] = z; p[1] = z; p[2] = z; p[3] = z; p[4] = z;
    p[5] = z; p[6] = z; p[7] = z; p[8] = z;
    p[10] = z; p[12] = z; p[13] = z; p[14] = z;
    p[9] = 1;
    return p;
}

// ================================================================================================
// @ 0x00ef1990
int FUN_00ef1990(u32* param_1, u32* param_2, u32* unused)
{
    (void)unused;
    int n = 0;
    if (param_2 != param_1) {
        do {
            u32* q;
            do {
                q = param_1;
                param_1 = q + 0x8e;
                if ((unsigned char)(*q >> 0x1e) & 1)
                    break;
            } while ((unsigned char)(*param_1 >> 0x1f) & 1);
            n++;
        } while (param_2 != param_1);
    }
    return n;
}

// ================================================================================================
// @ 0x00ef1a50
u8 FUN_00ef1a50(void)
{
    u8* raw = (u8*)ZoneObject_new(8, "App", 0, 0, 0, 0);
    int* p;
    if (raw) {
        *(void**)raw = &G_13effa8;
        _InterlockedExchange((volatile long*)(raw + 4), 0);
        *(void**)raw = &G_148b0b4;
        p = (int*)raw;
    } else {
        p = 0;
    }
    int* old = (int*)G_16c7b30;
    if (p != old) {
        if (p)
            VFN(p, 4, TC_v)(p);
        *(int**)&G_16c7b30 = p;
        if (old)
            VFN(old, 8, TC_v)(old);
    }
    void* mgr = FUN_0067dcd0();
    VFN(mgr, 0x44, TC_vpii)(mgr, 1, G_16c7b30, 0);
    return 1;
}

// ================================================================================================
// @ 0x00ef1930
void cSim::FUN_00ef1930(int a, float b)
{
    ((Sub70*)p70)->FUN_00ebdc20(a, b);
}

// ================================================================================================
// @ 0x00ef1ad0
void cSim::FUN_00ef1ad0(void)
{
    ModelVector* mv = (ModelVector*)&v74;
    mv->DoDestroyValues(v74, v78);
    if (v74 && *(int*)((char*)v74 - 4) != 0)
        op_delete(v74);
    if (p60 && *(int*)((char*)p60 - 4) != 0)
        op_delete(p60);
    void* p4c = *(void**)((char*)this + 0x4c);
    if (p4c && *(int*)((char*)p4c - 4) != 0)
        op_delete(p4c);
    ht.DoFreeNodes(ht.mpBuckets, ht.mnElements);
    ht.mAlloc = 0;
    if (ht.mnElements > 1)
        op_delete(ht.mpBuckets);
    if (p18 && *(int*)((char*)p18 - 4) != 0)
        op_delete(p18);
}

// ================================================================================================
// @ 0x00ef1c40
void cSim::FUN_00ef1c40(void)
{
    if (bDirty) {
        int i = 0;
        do {
            if (*(char*)(i + *(int*)((char*)this + 0x18))) {
                void* s = FUN_0067dd50();
                VFN(s, 0x5c, TC_vii)(s, i, 1);
            }
        } while (++i <= 0x1b);
        char* end = *(char**)((char*)this + 0x1c);
        char* begin = *(char**)((char*)this + 0x18);
        eastl_vector_insert(begin, end, (u32)(end - end));
        *(int*)((char*)this + 0x1c) += (int)(begin - end);
        bDirty = 0;
    }
}

// ================================================================================================
// @ 0x00ef1ca0
void cSim::FUN_00ef1ca0(void)
{
    *(u32*)((char*)this + 4) = 0;
    *(u32*)((char*)this + 8) = 0xffffffff;
    *(u32*)((char*)this + 0xc) = 0xffffffff;
    *(u32*)((char*)this + 0x10) = 0;
    FUN_00ef1c40();
    *(u32*)((char*)this + 4) = 0;
    void* a = *(void**)((char*)G_16c7aa4 + 0x74);
    *(void**)((char*)this + 0x14) = a;
    char* b = (char*)*(void**)((char*)a + 0x10);
    u32 cnt = *(u32*)(b + 0x2c24);
    u32* e = (u32*)*(u32*)(b + 0x2c14);
    u32* bp;
    if (cnt < 0x3fffffff)
        bp = (u32*)(cnt * 0x238 + *(u32*)(b + 0x2c10));
    else
        bp = e;
    int n = FUN_00ef1990(bp, e, 0);
    Vec2v* v60 = (Vec2v*)((char*)this + 0x60);
    v60->Reserve(n);
    char* e60 = (char*)v60->mpEnd;
    char* b60 = (char*)v60->mpBegin;
    eastl_vector_insert(b60, e60, (u32)(e60 - e60));
    v60->mpEnd = (char*)v60->mpEnd + (int)(b60 - e60);
    Vec2v* v4c = (Vec2v*)((char*)this + 0x4c);
    v4c->Reserve4(n);
    v4c->Erase(v4c->mpBegin, v4c->mpEnd);
    ht.DoFreeNodes(ht.mpBuckets, ht.mnElements);
    ht.mAlloc = 0;
    int* v = (int*)FUN_00ff3f00_f(*(void**)((char*)this + 0x14));
    if (v) {
        void* k = FUN_00eec0d0((int)v);
        FUN_00ef1b70((u32)k);
    }
    u32 cnt2 = *(u32*)(b + 0x2c24);
    u32* end2 = (u32*)*(u32*)(b + 0x2c14);
    u32* cur;
    if (cnt2 < 0x3fffffff)
        cur = (u32*)(cnt2 * 0x238 + *(u32*)(b + 0x2c10));
    else
        cur = end2;
    u32* e2 = (u32*)*(u32*)(b + 0x2c14);
    while (e2 != cur) {
        FUN_00ef1b70((u32)FUN_00eec0d0((int)(cur + 1)));
        u32* q;
        do {
            q = cur;
            cur = q + 0x8e;
            if ((*q >> 0x1e) & 1)
                break;
        } while ((*cur >> 0x1f) & 1);
    }
}

// ================================================================================================
// @ 0x00ef1b70
void cSim::FUN_00ef1b70(u32 v)
{
    if (!v)
        return;
    int* rec = (int*)FUN_00b18e00(v);
    int* p98v = (int*)VFN(rec, 0x98, TC_p)(rec);
    char* ht = (char*)this + 0x2c;
    int* bucket = (int*)*(int*)((char*)this + 0x30);
    int key = bucket[*(u32*)((char*)this + 0x34)];
    HashFindOut tmp;
    if (*(int*)((StubC776*)ht)->F(&tmp, p98v) == key) {
        v &= 0xffffff00;
        ((Stub8DF*)ht)->F(&tmp, p98v, v);
        if (*p98v && !FUN_00401d90(p98v))
            ((Stub4E19*)((char*)this + 0x4c))->F(p98v);
        void** end = *(void***)((char*)this + 0x64);
        u32 cap = *(u32*)((char*)this + 0x68);
        if ((u32)end < cap) {
            void** p = end;
            *(void***)((char*)this + 0x64) = p + 1;
            if (p)
                *p = rec;
        } else {
            ((StubB966*)((char*)this + 0x60))->F(end, &rec);
        }
    }
}

// ------------------------------------------------------------- scenario-init ref assignment
// new = ctor(alloc) ; if (new != *slot) { vtbl+add(new+sub) ; *slot = new ; vtbl+rel(old+sub) }
#define SETREF(slotExpr, sz, nm, ctor, suboff, addoff, reloff)                          \
    do {                                                                                \
        void* pNew_ = EAAllocate((sz), (nm), 0, 0, 0, 0);                               \
        pNew_ = pNew_ ? ctor(pNew_) : 0;                                                \
        char* pOld_ = (char*)(slotExpr);                                                \
        if (pNew_ != pOld_) {                                                           \
            if (pNew_) VFN((char*)pNew_ + (suboff), (addoff), TC_v)((char*)pNew_ + (suboff)); \
            slotExpr = pNew_;                                                           \
            if (pOld_) VFN(pOld_ + (suboff), (reloff), TC_v)(pOld_ + (suboff));         \
        }                                                                               \
    } while (0)

// ================================================================================================
// @ 0x00ef1e00
void cSim::FUN_00ef1e00(void)
{
    void* tick = FUN_00b3d310();
    *(u8*)((char*)tick + 0x24) = 0;
    char* base = (char*)this;
    void* self = base ? base + 4 : 0;
    void* server = FUN_0067dcc0();
    *(void**)(base + 0x80) = server;
    *(void**)(base + 0x84) = self;
    *(void**)(base + 0x88) = (void*)G_148b018;
    *(u32*)(base + 0x8c) = 8;
    *(u32*)(base + 0x90) = 0;
    if (server && self) {
        for (u32 off = 0; off < 0x20; off += 4)
            VFN(server, 0x24, TC_vpp)(server, self, *(void**)((char*)G_148b018 + off));
    }
    *(int*)(base + 0xd0) = G_15accf0;
    SETREF(*(void**)(base + 0x18), 0x1cc, "Simulator", FUN_00f33f90_c, 0, 8, 0xc);
    ((Stub37f*)*(void**)(base + 0x18))->F(G_15accc8);
    FUN_00f02c10();
    SETREF(*(void**)(base + 0x78), 0x108, "Simulator", FUN_00f1e450_c, 4, 4, 8);
    FUN_00f1e620(*(void**)(base + 0x78));
    if (*(int*)(base + 0xcc) == 0) {
        if (G_15accf0 != 0) {
            if ((u32)(G_15accf0 - 1) <= 1)
                *(int*)(base + 0xcc) = 2;
        } else {
            *(int*)(base + 0xcc) = 1;
        }
    }
    u8 empty = (*(int*)G_15accc8 == 0);
    SETREF(*(void**)(base + 0x74), 0x1fc, "Simulator", FUN_00f3fad0_c, 8, 4, 8);
    ((Stub447*)*(void**)(base + 0x74))->F(empty);
    FUN_00f20fe0();
    FUN_00f24d30();
    if (!empty) {
        ((Stub660*)((char*)*(void**)(base + 0x74) + 0x128))->F(G_15accf8);
        if (((Stub466*)*(void**)(base + 0x74))->F(G_15accc8)) {
            if (G_15acce0)
                ((Stub425*)*(void**)(base + 0x74))->F(&G_15acce0);
            ((cSim*)G_15acc30)->FUN_00ef1ca0();
        }
    }
    LoadCreatureGameplayTuning(G_15acc2c, 0x2980610e);
    FUN_00ebf160();
    void* mgr2 = FUN_00b3d230(0);
    FUN_00b5cde0(mgr2);
    FUN_00f09580();
    SETREF(*(void**)(base + 0x6c), 0x308, "Simulator", FUN_00f0fef0_c, 0x38, 0, 4);
    SETREF(*(void**)(base + 0x68), 0x120, "Simulator", FUN_00f11b60_c, 0x3c, 4, 8);
    VFN(*(void**)(base + 0x68), 4, TC_v)(*(void**)(base + 0x68));
    if (*(int*)(base + 0xd0) == 0) {
        SETREF(*(void**)(base + 0xd4), 0x740, "Simulator/cScenarioTutorials",
               FUN_00ef9d90_c, 4, 4, 8);
        FUN_00ef9e40(*(void**)(base + 0xd4));
        SETREF(*(void**)(base + 0xd8), 0x120, "Simulator/cScenarioYouTube",
               FUN_00f04740_c, 0, 0, 4);
        FUN_00f06ce0(*(void**)(base + 0xd8));
        SETREF(*(void**)(base + 0x10), 0x70, "Simulator/cScenarioEditModeInputStrategy",
               FUN_00edaa80_c, 0x3c, 4, 8);
        VFN(*(void**)(base + 0x10), 4, TC_v)(*(void**)(base + 0x10));
        SETREF(*(void**)(base + 0x14), 0x98, "Simulator/cScenarioEditModeDisplayStrategy",
               FUN_00ed5220_c, 0, 4, 8);
        FUN_00ed5d70(*(void**)(base + 0x14));
        FUN_00f08ef0();
        FUN_00ec92b0();
    }
    if (*(int*)(base + 0x70) == 0) {
        FUN_01041bc0(FUN_010408b0());
        SETREF(*(void**)(base + 0x70), 0x68, "Simulator", FUN_00ebc120_c, 0, 4, 8);
    }
    FUN_00ebd220(*(void**)(base + 0x70));
    *(int*)(base + 0xcc) = 0;
    ((Stub12d*)base)->F(G_15accec);
    void* posse = FUN_00d539d0();
    VFN(posse, 0x1c, TC_v)(posse);
    void* ticker = FUN_00b3d330();
    void** slot = *(void***)ticker + 0x14;
    void* arg = FUN_00d539d0();
    ((TC_vp)*slot)(ticker, arg);
}

// ================================================================================================
// @ 0x00ef2370
u8 cSim::FUN_00ef2370(int unused)
{
    (void)unused;
    void* o = EAAllocate(0xa8, "Simulator", 0, 0, 0, 0);
    void* n = o ? FUN_00ec4bb0_r(o) : 0;
    void* old = p1c;
    if (n != old) {
        if (n)
            VFN(n, 4, TC_v)(n);
        p1c = n;
        if (old)
            VFN(old, 8, TC_v)(old);
    }
    FUN_00ec4650_f(p1c);
    FUN_00eed090();
    void* o2 = EAAllocate(0x64, "Simulator", 0, 0, 0, 0);
    void* n2 = o2 ? FUN_00f391c0_r(o2) : 0;
    void* old2 = p7c;
    if (n2 != old2) {
        if (n2)
            VFN(n2, 4, TC_v)(n2);
        p7c = n2;
        if (old2)
            VFN(old2, 8, TC_v)(old2);
    }
    void* a = FUN_0067de40();
    void* b = VFN(a, 0x20, TC_p)(a);
    VFN(b, 0x1c, TC_vp)(b, p7c);
    void* ms = FUN_0067dcc0();
    VFN(ms, 0x28, TC_vpiii)(ms, (void*)&LAB_00ef2330, 0, 0x212d3e7, 0, -1);
    void* local[2];
    local[0] = (void*)0x4249453;
    local[1] = (void*)0x7fb11b4;
    void* self = (char*)this + 4;
    void* server = FUN_0067dcc0();
    p94 = server;
    p98 = self;
    p9c = &local[0];
    nA0 = 2;
    nA4 = 0;
    if (server && self) {
        for (u32 i = 0; i < 2; i++)
            VFN(server, 0x24, TC_vpp)(server, self, local[i]);
    }
    return 1;
}

// ================================================================================================
// @ 0x00ef24d0
u8 cSim::FUN_00ef24d0(void)
{
    void* h = p94;
    if (h) {
        p94 = 0;
        RemoveHandler(h, p98, p9c, nA0, nA4);
    }
    void* ms = FUN_0067dcc0();
    VFN(ms, 0x30, TC_viii)(ms, (int)&LAB_00ef2330, 0x212d3e7, 0xffffd8f1);
    void* a = FUN_0067de40();
    void* b = VFN(a, 0x20, TC_p)(a);
    VFN(b, 0x20, TC_vp)(b, p7c);
    if (p7c) {
        void* r = p7c;
        p7c = 0;
        VFN(r, 8, TC_v)(r);
    }
    FUN_00ec51a0_f(p1c);
    if (p1c) {
        void* r = p1c;
        p1c = 0;
        VFN(r, 8, TC_v)(r);
    }
    void* mgr = FUN_0067dcd0();
    VFN(mgr, 0x44, TC_vpii)(mgr, 0, G_16c7b30, 0);
    if (G_16c7b30) {
        void* r = G_16c7b30;
        G_16c7b30 = 0;
        VFN(r, 8, TC_v)(r);
    }
    return 1;
}

// ================================================================================================
// @ 0x00ef25a0
u8 cSim::FUN_00ef25a0(void)
{
    FUN_00697980((char*)this + 0x20);
    void* t = GetTriggerMgr(1);
    ((TriggerMgr*)t)->FUN_00adf390();
    int s = GetSetting5(0x4cf52822);
    ((Setter*)s)->FUN_0045b150();
    void* em = FUN_0067ddd0();
    VFN(em, 0x98, TC_vii)(em, 8, 1);
    ((GTM*)FUN_00b3d380())->FUN_00b316d0(1.0f, G_1470f1c, G_14853e0, G_14853e0);
    bDC = 1;
    GTM* g = (GTM*)FUN_00b3d380();
    g->FUN_00b32220(0x4bf38a7);
    ((cSim*)G_15acc30)->FUN_00ef1ca0();
    return 1;
}
