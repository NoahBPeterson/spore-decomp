// Slice s00df9650 -- SP asset-browser / galaxy-game-entry UI state-machine
// helpers (SporeApp.exe 0x00df9650..0x00dfa5b2).  Every function here is a
// __thiscall member of one UI object whose cSPUILayout lives at +0x48, plus a
// couple of standing free helpers at the end.
//
// Frozen batch gold6.  32-bit x86, MSVC 2008 SP1, flags
// /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).

#include "types.h"
#include <intrin.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// ---------------------------------------------------------------------------
// Interfaces
// ---------------------------------------------------------------------------
struct IWindow {                          // a cSPUIWindow / cSPUILayout window
    PV2 PV
    virtual void* Slot0C(unsigned a);              // +0x0c  (id) -> sub-object
    virtual void* Slot10();                        // +0x10  -> child
    virtual void  Slot14(unsigned id, void* p, int z); // +0x14  MessageServer::Send
    PV4
    virtual void  Slot28(int a, int b);            // +0x28
    PV4 PV
    virtual void  Slot40(int a);                   // +0x40
    PV4
    virtual char  Slot54();                        // +0x54
    PV2
    virtual void  Slot60(void* v, int z);          // +0x60
    PV
    virtual void  Slot68();                        // +0x68
    PV4
    virtual void  Slot7C(int a, int b);            // +0x7c  SetVisible/flag
    virtual void  Slot80(void* p);                 // +0x80  SetText
};

struct SPUILayout {
    char pad[0x18];
    void      Shutdown(unsigned);                  // 0x00811ad0  __thiscall
    IWindow*  FindWindowByID(unsigned id, int flag); // 0x008105b0  __thiscall
};

struct GlobalUI {
    void SetVisibility(int v);                     // 0x00e01350  __thiscall
};

struct Map3C { void Fn9dc0(void* key); };          // 0x00de9dc0 (ecx = map)
struct EcB   { char Fn4320(); };                   // 0x00ec4320
struct EcA   { char pad[0x1c]; EcB* m1c; };

// kGUI_PanelIDs: the global "Simulator" panel container.
struct GGE {
    char  pad00[0x3c];
    Map3C mMap3C;                                  // +0x03c  (map passed to FUN_00de9dc0)
    char  pad3D[0xcb];                             // +0x03d..+0x107
    int   m108;                                    // +0x108
    char  pad10C[0x38];                            // +0x10c..+0x143
    SPUILayout mLayout;                            // +0x144
    char  pad15C[0x28];                            // +0x15c..+0x183
    GlobalUI* mGlobalUI;                           // +0x184
    char  pad188[0x50];                            // +0x188..+0x1d7
    int   m1D8;                                    // +0x1d8
    int   m1DC;                                    // +0x1dc
    char  pad1E0[0x18];                            // +0x1e0..+0x1f7
    int   m1F8;                                    // +0x1f8

    void Fn5260();                                 // 0x00de5260
    void Fn5300();                                 // 0x00de5300
    void Fn53d0(int);                              // 0x00de53d0
    void Fn9ec0();                                 // 0x00de9ec0
};
extern GGE* kGUI_PanelIDs;                         // 0x016a1344

extern unsigned DAT_016a0FB8;                      // swarm spawn min
extern unsigned DAT_016a0FC8;                      // swarm spawn max
extern EcA* DAT_016c7AA4;                          // -> [+0x1c] object
extern int  DAT_015da7c4, DAT_015da7c8, DAT_015da7cc, DAT_015da7d0;

// 0x0147ebc8: four 3-entry window-id rows.
extern int  kIDs[4][3];                            // 0x0147ebc8
extern char LAB_00ad0e52;                          // a code label stored as a value

struct RandomLCG { unsigned RandomUint32Uniform(unsigned n); };  // 0x00a68fb0
extern RandomLCG _sMathRandom;                     // 0x01601760

struct Stopwatch { int mUnits; void SetUnits(int u); };  // 0x0093a1a0
struct AGSwarm   { void FnB760(); void SpawnOne(); void FnBad0(void* arg); };
struct B3        { void Fn7dec0(); };              // 0x00b7dec0

// vtables referenced by FUN_00dfa460.
extern char vtbl_AddRef[];                         // 0x0147dc04
extern char vtbl_FUN_0149bad8[];                   // 0x0149bad8
extern char vtbl_ContentValidationSummarizer[];    // 0x013ec458

// 12-byte resource descriptor built for sSetWindowImage, passed to FUN_00de3f00.
struct ImgKey { int a; int tag; int c; };

// 0x48-byte launch-request used by the AdvancedLaunch wrappers (9990/9a00/9a70).
struct LaunchData {
    int   m00;                                      // +0x00
    void* m04;                                      // +0x04
    char  pad08[0x09];                              // +0x08..+0x10
    char  m11;                                      // +0x11
    char  m12;                                      // +0x12
    char  pad13[0x1d];                              // +0x13..+0x2f
    void* m30;                                      // +0x30
    char  pad34[0x04];                              // +0x34..+0x37
    void* m38;                                      // +0x38
    char  pad3C[0x0c];                              // +0x3c..+0x47

    void Fn4b10();                                  // 0x00644b10 (ctr)
    void Fn4b60();                                  // 0x00644b60 (dtor)
};

// The 0x48-byte launch descriptor used by FUN_00dfa460 (different field layout).
struct LD2 {
    int   m00;                                      // +0x00
    void* m04;                                      // +0x04
    void* m08;                                      // +0x08
    void* m0c;                                      // +0x0c
    char  pad10;                                    // +0x10
    char  m11;                                      // +0x11
    char  pad12[0x06];                              // +0x12..+0x17
    int   m18;                                      // +0x18
    int   m1c;                                      // +0x1c
    int   m20;                                      // +0x20
    unsigned char m24;                              // +0x24
    char  pad25[0x0b];                              // +0x25..+0x2f
    void* m30;                                      // +0x30
    char  pad34[0x04];                              // +0x34..+0x37
    void* m38;                                      // +0x38
    char  pad3C[0x0c];                              // +0x3c..+0x47

    void Fn4b10();                                  // 0x00644b10 (ctr)
    void Fn4b60();                                  // 0x00644b60 (dtor)
};

struct LI { unsigned LowPart; int HighPart; };     // LARGE_INTEGER
extern "C" int __stdcall QueryPerformanceCounter(LI*);  // IAT 0x013cc2b8

struct cString {                                   // SP::cString
    void* mData;                                    // +0x00
    void  FUN_006b5770(unsigned, unsigned, unsigned);  // 0x006b5770 ctor
    void  FUN_006b5240();                           // 0x006b5240 dtor
    const wchar_t* FUN_006b55c0();                  // 0x006b55c0 GetText
};

// ---------------------------------------------------------------------------
// Free helpers
// ---------------------------------------------------------------------------
void* __cdecl FUN_00dd9190();                     // 0x00dd9190 -> object*
void  __cdecl FUN_00ddb760(void*);                 // 0x00ddb760
void  __cdecl FUN_00ddbad0(void*);                 // 0x00ddbad0
void  __cdecl FUN_00ddbe40(void*);                 // 0x00ddbe40
void  __cdecl FUN_00de3f00(void* win, void* key, int z); // 0x00de3f00
char  __cdecl FUN_00eed840(void* p);               // 0x00eed840
char  __cdecl FUN_00eed920(void* a, void* b);      // 0x00eed920
char  __cdecl FUN_00eed970(void* a, void* b);      // 0x00eed970
void  __cdecl FUN_006447c0(int, void*);            // 0x006447c0
void  __cdecl FUN_0064a990(void*);                 // 0x0064a990 AdvancedLaunch
void  __cdecl FUN_00ef7d90();                      // 0x00ef7d90
void* __cdecl FUN_00b3d360();                      // 0x00b3d360 -> object*
void  __cdecl FUN_00b7dec0(void*);                 // 0x00b7dec0
void* __cdecl SP_MovieSystem();                    // 0x0067cb10
void* __cdecl SP_AppSystem();                      // 0x0067dd00
void* __cdecl SP_MessageServer();                  // 0x0067dcc0
void* __cdecl operator_new(unsigned size, const char* name, int, int, int, int); // 0x00f473a0

// ---------------------------------------------------------------------------
// The object
// ---------------------------------------------------------------------------
struct GGUI;

struct Item {                    // 0x24-byte entry of the +0x0c vector
    int  id;                     // +0x00
    char pad[0x1c];              // +0x04..+0x1f
    int  state;                  // +0x20
};

struct Slot {                    // 0x38-byte entry of the +0xc0 array
    int  x;                      // +0x00
    int  y;                      // +0x04
    int  z;                      // +0x08
    char pad[0x14];              // +0x0c..+0x1f
    char state;                  // +0x20
    char pad2[0x17];             // +0x21..+0x37
};

struct PropKey {                 // 0x18-byte property key at +0x8c
    int type;                    // +0x00
    int a1, a2, a3, a4, a5;      // +0x04..+0x17
};

struct Obj4C {                   // object filled by FUN_006447c0 (used by 00dfa460)
    virtual void FnV0();
    virtual void FnV4();
    virtual void FnV8();
    char  pad0c[0x18];           // +0x0c..+0x23
    int   m24;                   // +0x24
    int   m28;                   // +0x28
    int   m2c;                   // +0x2c
    int   m30;                   // +0x30
    char  m34;                   // +0x34
    char  pad35;                 // +0x35
    char  m36;                   // +0x36
};

struct Summ13 {                  // 0x14-byte object from operator_new (used by 00dfa460)
    int  v0;                     // +0x00
    int  v4;                     // +0x04
    int  v8;                     // +0x08
    int  vc;                     // +0x0c
    char v10;                    // +0x10
};

struct GGUI {
    void*    mVftable;           // +0x000
    char     pad04[0x04];        // +0x004..+0x007
    char     mBase8[0x04];       // +0x008..+0x00b  (second-base subobject; &mBase8 == this+8)
    Item*    mItemBegin;         // +0x00c
    Item*    mItemEnd;           // +0x010
    char     pad14[0x0c];        // +0x014..+0x01f
    Stopwatch mTimer20;          // +0x020  (mUnits doubles as the UI state)
    char     pad24[0x08];        // +0x024..+0x02b
    int      mIndex;             // +0x02c
    unsigned mCount;             // +0x030
    int      mCur;               // +0x034
    char     pad38[0x10];        // +0x038..+0x047
    SPUILayout mLayout;          // +0x048
    int      m60;                // +0x060
    int      m64;                // +0x064
    int      m68;                // +0x068
    int      m6c;                // +0x06c
    Stopwatch mTimer70;          // +0x070  (mUnits selects rdtsc vs QPC)
    char     pad74[0x04];        // +0x074
    int      m78;                // +0x078
    char     m7c;                // +0x07c
    char     m7d;                // +0x07d
    char     m7e;                // +0x07e
    char     m7f;                // +0x07f
    char     pad80[0x0c];        // +0x080..+0x08b
    PropKey  m8c;                // +0x08c..+0x0a3
    int      mA4;                // +0x0a4
    int      mA8;                // +0x0a8
    int      mAC;                // +0x0ac
    char     mB0[0x10];          // +0x0b0..+0x0bf
    Slot     mSlots[3];          // +0x0c0..+0x167
    void*    m168;               // +0x168
    void*    m16c;               // +0x16c

    void      FUN_00df95d0();                            // 0x00df95d0
    void      FUN_00df6c40();                            // 0x00df6c40
    void      FUN_00df6980();                            // 0x00df6980
    void      FUN_00df97d0();                            // 0x00df97d0
    void      FUN_00df9770();                            // 0x00df9770
    void      FUN_00df97e0();                            // 0x00df97e0
    void      FUN_00df9850(unsigned index);              // 0x00df9850
    void      FUN_00df98f0();                            // 0x00df98f0
    void      FUN_00df9ad0();                            // 0x00df9ad0
    void      FUN_00df9b30(int v);                       // 0x00df9b30
    void      FUN_00df9c80(unsigned id);                 // 0x00df9c80
    void      FUN_00df9d20(void* v);                     // 0x00df9d20
    void      FUN_00df9dc0(unsigned index, int v);       // 0x00df9dc0
    void      FUN_00df9e60();                            // 0x00df9e60
    void      FUN_00df9ef0();                            // 0x00df9ef0
    void      FUN_00df9be0();                            // 0x00df9be0
    void      FUN_00df9fc0();                            // 0x00df9fc0
    void      FUN_00dfa460(int*, unsigned char);         // 0x00dfa460
    void      FUN_00df8330();                            // 0x00df8330
    void      FUN_00df9650();                            // 0x00df9650
    void      FUN_00e00640();                            // 0x00e00640
};

// The window-ID tables (read-only, indexed by slot).
// 0x0147ebc8[i], 0x0147ebd4[i], 0x0147ebe0[i], 0x0147ebec[i]

// ===========================================================================
// 00df97d0
// ===========================================================================
// @ 0x00df97d0
void GGUI::FUN_00df97d0()
{
    mLayout.Shutdown(1);
}

// ===========================================================================
// 00df9770
// ===========================================================================
// @ 0x00df9770
void GGUI::FUN_00df9770()
{
    FUN_00e00640();
    if (kGUI_PanelIDs->m108 == 2) {
        IWindow* w = kGUI_PanelIDs->mLayout.FindWindowByID(0x615a5ff, 1);
        if (w)
            w->Slot7C(1, 1);
        kGUI_PanelIDs->mGlobalUI->SetVisibility(1);
        FUN_00df95d0();
        FUN_00df6c40();
    }
}

// ===========================================================================
// 00df97e0
// ===========================================================================
// @ 0x00df97e0
void GGUI::FUN_00df97e0()
{
    int ids[4] = { 0x7bfb2a0, 0x7bfb2a1, 0x7bfb2a2, 0x7bfb2a3 };
    for (unsigned i = 0; i < 4; ++i) {
        IWindow* w = mLayout.FindWindowByID(ids[i], 1);
        if (w)
            w->Slot7C(1, 0);
    }
}

// ===========================================================================
// 00df9ad0
// ===========================================================================
// @ 0x00df9ad0
void GGUI::FUN_00df9ad0()
{
    FUN_00df97e0();
    IWindow* w = mLayout.FindWindowByID(0x7ca16b4, 1);
    if (w)
        w->Slot7C(1, 1);
    w = mLayout.FindWindowByID(0x7bfce80, 1);
    if (w)
        w->Slot7C(1, 0);
    mTimer20.mUnits = 0;
}

// ===========================================================================
// 00df9b30   UpdateNavigationControls(int)
// ===========================================================================
// @ 0x00df9b30
void GGUI::FUN_00df9b30(int v)
{
    int ids[5] = { 0x5384d05, 0x5384d06, 0x5384d07, 0x5951103, 0x5951104 };
    for (unsigned i = 0; i < 5; ++i) {
        IWindow* w = mLayout.FindWindowByID(ids[i], 1);
        if (w)
            w->Slot7C(2, v);
    }
    ids[0] = 0x7ccda83;
    ids[1] = 0x7ccda8d;
    ids[2] = 0x7ccdaaa;
    for (unsigned i = 0; i < 3; ++i) {
        IWindow* w = mLayout.FindWindowByID(ids[i], 1);
        if (w)
            w->Slot7C(1, v);
    }
}

// ===========================================================================
// 00dfa370   swarm random spawn
// ===========================================================================
// @ 0x00dfa370
void FUN_00dfa370()
{
    AGSwarm* o = (AGSwarm*)FUN_00dd9190();
    o->FnB760();
    if (DAT_016a0FC8 > DAT_016a0FB8) {
        int n = _sMathRandom.RandomUint32Uniform(DAT_016a0FC8 - DAT_016a0FB8);
        n = n + DAT_016a0FB8;
        for (; n != 0; --n)
            ((AGSwarm*)FUN_00dd9190())->SpawnOne();
    }
}

// ===========================================================================
// 00df9850   slot -> resource image
// ===========================================================================
// @ 0x00df9850
void GGUI::FUN_00df9850(unsigned index)
{
    int x = mSlots[index].x;
    int y = mSlots[index].y;
    int z = mSlots[index].z;
    IWindow* w = mLayout.FindWindowByID((unsigned)kIDs[1][index], 1);
    if (!w)
        return;
    if (x == 0) {
        w->Slot7C(1, 0);
        return;
    }
    w->Slot7C(1, 1);
    ImgKey key = { x, y, z };
    key.tag = 0x2f7d0004;
    FUN_00de3f00(w, &key, 0);
}

// ===========================================================================
// 00df98f0   refresh the currently-selected resource image
// ===========================================================================
// @ 0x00df98f0
void GGUI::FUN_00df98f0()
{
    if (mA4 == 0)
        return;
    ImgKey key = { mA4, mA8, mAC };
    key.tag = 0x2f7d0004;
    IWindow* w = mLayout.FindWindowByID(0x7ca46c1, 1);
    if (w) {
        w->Slot7C(1, 1);
        FUN_00de3f00(w, &key, 0);
    }
    IWindow* w2 = mLayout.FindWindowByID(0x65fbfa0, 1);
    if (w2)
        FUN_00de3f00(w2, &key, 0);
}

// ===========================================================================
// 00df9990 / 00df9a00 / 00df9a70   AdvancedLaunch wrappers
// ===========================================================================
void __fastcall FUN_00df9990(GGUI* p);
void __fastcall FUN_00df9a00(GGUI* p);
void __fastcall FUN_00df9a70(GGUI* p);

// @ 0x00df9990
void __fastcall FUN_00df9990(GGUI* p)
{
    kGUI_PanelIDs->Fn53d0(0);
    LaunchData d;
    d.Fn4b10();
    d.m04 = p;
    d.m38 = p ? (void*)&p->mBase8 : 0;
    d.m00 = 0x7edf94a2;
    d.m30 = &LAB_00ad0e52;
    d.m11 = 1;
    FUN_0064a990(&d);
    d.Fn4b60();
}

// @ 0x00df9a00
void __fastcall FUN_00df9a00(GGUI* p)
{
    kGUI_PanelIDs->Fn53d0(0);
    LaunchData d;
    d.Fn4b10();
    d.m04 = p;
    d.m38 = p ? (void*)&p->mBase8 : 0;
    d.m00 = 0x7edf94a2;
    d.m30 = &LAB_00ad0e52;
    d.m11 = 0;
    d.m12 = 1;
    FUN_0064a990(&d);
    d.Fn4b60();
}

// @ 0x00df9a70
void __fastcall FUN_00df9a70(GGUI* p)
{
    kGUI_PanelIDs->Fn53d0(0);
    LaunchData d;
    d.Fn4b10();
    d.m04 = p;
    d.m38 = p ? (void*)&p->mBase8 : 0;
    d.m00 = 0x8f6443b2;
    d.m30 = &LAB_00ad0e52;
    FUN_0064a990(&d);
    d.Fn4b60();
}

// ===========================================================================
// 00df9be0   commit the current slot / start the frame timer
// ===========================================================================
// @ 0x00df9be0
void GGUI::FUN_00df9be0()
{
    ((B3*)FUN_00b3d360())->Fn7dec0();
    if (mTimer20.mUnits == 10)
        kGUI_PanelIDs->mMap3C.Fn9dc0(&m8c);
    if (mTimer20.mUnits == 9)
        kGUI_PanelIDs->mMap3C.Fn9dc0(&mB0[0]);
    m78 = 0;
    unsigned __int64 fr;
    if (mTimer70.mUnits == 1) {
        fr = __rdtsc();
    } else {
        QueryPerformanceCounter((LI*)&fr);
    }
    m64 = (int)(fr >> 32);
    m60 = (unsigned)fr;
    m68 = 0;
    m6c = 0;
    ((AGSwarm*)FUN_00dd9190())->FnBad0(&m8c);
}

// ===========================================================================
// 00df9c80   highlight a sub-window by id
// ===========================================================================
// @ 0x00df9c80
void GGUI::FUN_00df9c80(unsigned id)
{
    IWindow* w = mLayout.FindWindowByID(id, 1);
    if (w)
        w->Slot7C(1, 1);
    if (id == 0x7bfb2a2) {
        IWindow* a = mLayout.FindWindowByID(0x5400fa5, 1);
        if (a) {
            IWindow* b = (IWindow*)a->Slot0C(0xcf428691);
            if (b)
                b->Slot60(m168, 0);
        }
        IWindow* c = mLayout.FindWindowByID(0x7cce848, 1);
        if (c)
            c->Slot80(m168);
    }
}

// ===========================================================================
// 00df9d20   set the currently-edited slot / key from a value triple
// ===========================================================================
// @ 0x00df9d20
void GGUI::FUN_00df9d20(void* v)
{
    int* p = (int*)v;
    if (mTimer20.mUnits == 4) {
        Slot& s = mSlots[mCur];
        s.x = p[0];
        s.y = p[1];
        s.z = p[2];
        FUN_00df9850(mCur);
    }
    if (mTimer20.mUnits == 2) {
        mA4 = p[0];
        mA8 = p[1];
        mAC = p[2];
        if (m168 != m16c) {
            *(short*)m168 = 0;
            m16c = m168;
        }
        m7f = (FUN_00eed920(&mA4, &m168) == 0);
        FUN_00df98f0();
    }
}

// ===========================================================================
// 00df9dc0   fill the per-slot verb tray
// ===========================================================================
// @ 0x00df9dc0
void GGUI::FUN_00df9dc0(unsigned index, int v)
{
    IWindow* w = mLayout.FindWindowByID((unsigned)kIDs[2][index], 1);
    if (w) {
        IWindow* s = (IWindow*)w->Slot0C(0x8ed27e7a);
        if (s) {
            s->Slot28(4, v);
            IWindow* c = (IWindow*)s->Slot10();
            c->Slot7C(0x10, 1);
        }
    }
    IWindow* w2 = mLayout.FindWindowByID((unsigned)kIDs[3][index], 1);
    if (w2) {
        bool ok = ((char)v == 0);
        w2->Slot7C(2, ok);
    }
}

// ===========================================================================
// 00df9e60   step the slot selection back
// ===========================================================================
// @ 0x00df9e60
void GGUI::FUN_00df9e60()
{
    if (mIndex == 0) {
        FUN_00df9ad0();
        return;
    }
    --mIndex;
    mTimer20.mUnits = mItemBegin[mIndex].state;
    FUN_00df97e0();
    FUN_00df9c80(mItemBegin[mIndex].id);
    if (mTimer20.mUnits == 2 && m7c == 0)
        FUN_00df9e60();
    if (mTimer20.mUnits == 1) {
        char v = ((IWindow*)SP_AppSystem())->Slot54();
        if (v == 0 && kGUI_PanelIDs->m1F8 == 0)
            FUN_00df9e60();
    }
    m7e = 1;
}

// ===========================================================================
// 00df9ef0   step the slot selection forward
// ===========================================================================
// @ 0x00df9ef0
void GGUI::FUN_00df9ef0()
{
    if (mIndex < (unsigned)(mItemEnd - mItemBegin) - 1) {
        for (;;) {
            ++mIndex;
            mTimer20.mUnits = mItemBegin[mIndex].state;
            FUN_00df97e0();
            FUN_00df9c80(mItemBegin[mIndex].id);
            if (mTimer20.mUnits == 3) {
                IWindow* w = mLayout.FindWindowByID(0x5951103, 1);
                if (w)
                    w->Slot7C(1, (m7d == 0));
            }
            if ((mTimer20.mUnits != 2 || m7c != 0) &&
                (mTimer20.mUnits != 4 || m7d != 0))
                break;
            if ((unsigned)(mItemEnd - mItemBegin) - 1 <= mIndex)
                return;
        }
        m7e = 1;
    }
}

// ===========================================================================
// 00df9650   enter / re-enter the galaxy game entry screen
// ===========================================================================
// @ 0x00df9650
void GGUI::FUN_00df9650()
{
    bool eq = (kGUI_PanelIDs->m1D8 == kGUI_PanelIDs->m1DC);
    IWindow* ms = (IWindow*)SP_MovieSystem();
    if (ms)
        ms->Slot40(1);
    kGUI_PanelIDs->Fn5300();
    kGUI_PanelIDs->mGlobalUI->SetVisibility(1);
    FUN_00df95d0();
    ((IWindow*)this)->Slot68();
    FUN_00df8330();
    m68 = -1;
    mTimer70.SetUnits(4);
    if (eq) {
        mTimer20.SetUnits(4);
        FUN_00df6980();
    }
    kGUI_PanelIDs->Fn5260();
    IWindow* w = kGUI_PanelIDs->mLayout.FindWindowByID(0x615a5ff, 1);
    if (w)
        w->Slot7C(1, 1);
    FUN_00df6c40();
    kGUI_PanelIDs->mGlobalUI->SetVisibility(1);
    ((AGSwarm*)FUN_00dd9190())->FnB760();
    kGUI_PanelIDs->Fn9ec0();
    int flag = 1;
    IWindow* srv = (IWindow*)SP_MessageServer();
    srv->Slot14(0x80d7451, &flag, 0);
}

// ===========================================================================
// 00df9fc0   refresh every descriptor window
// ===========================================================================
// @ 0x00df9fc0
void GGUI::FUN_00df9fc0()
{
    IWindow* w;
    w = mLayout.FindWindowByID(0x5951103, 1);
    if (w)
        w->Slot7C(1, (m7d == 0));
    w = mLayout.FindWindowByID(0x6451156, 1);
    if (w)
        w->Slot7C(1, (mA4 == 0));
    w = mLayout.FindWindowByID(0x7ca46c1, 1);
    if (w)
        w->Slot7C(1, (mA4 != 0));
    w = mLayout.FindWindowByID(0x7cd1558, 1);
    if (w)
        w->Slot7C(1, (m7f == 0));
    w = mLayout.FindWindowByID(0x7cd1559, 1);
    if (w)
        w->Slot7C(1, m7f);
    w = mLayout.FindWindowByID(0x5400fa5, 1);
    if (w)
        w->Slot7C(1, m7f);
    w = mLayout.FindWindowByID(0x7cce848, 1);
    if (w)
        w->Slot7C(1, (m7f == 0));
    w = mLayout.FindWindowByID(0x7cd0034, 1);
    if (w)
        w->Slot7C(1, m7f);
    w = mLayout.FindWindowByID(0x7ccc2a4, 1);
    if (w)
        w->Slot7C(1, m7f);
    w = mLayout.FindWindowByID(0x7ee01a0, 1);
    if (w) {
        if (FUN_00eed840(&mA4) == 0) {
            if (FUN_00eed970(&mA4, &m8c) != 0) {
                cString s;
                s.FUN_006b5770(0x3dade1bb, 0x7ec9f8c, 0);
                w->Slot80((void*)s.FUN_006b55c0());
                w->Slot7C(1, 1);
                s.FUN_006b5240();
            } else {
                w->Slot7C(1, 0);
            }
        } else {
            cString s;
            s.FUN_006b5770(0x3dade1bb, 0x7ec9f8c, 0);
            w->Slot80((void*)s.FUN_006b55c0());
            w->Slot7C(1, 1);
            s.FUN_006b5240();
        }
    }
    unsigned i = 0;
    do {
        w = mLayout.FindWindowByID((unsigned)kIDs[0][i], 1);
        if (w)
            w->Slot7C(1, (mSlots[i].x == 0));
        w = mLayout.FindWindowByID((unsigned)kIDs[1][i], 1);
        if (w)
            w->Slot7C(1, (mSlots[i].x != 0));
        w = mLayout.FindWindowByID((unsigned)kIDs[3][i], 1);
        if (w) {
            if (i < mCount) {
                w->Slot7C(1, 1);
                FUN_00df9850(i);
                FUN_00df9dc0(i, (unsigned char)mSlots[i].state);
            } else {
                w->Slot7C(1, 0);
            }
        }
        ++i;
    } while (i < 3);
    char flag = 0;
    int k = mCount;
    if (k != 0) {
        Slot* p = &mSlots[1];
        do {
            if (p->state == 0)
                flag = 1;
            ++p;
        } while (--k != 0);
    }
    w = mLayout.FindWindowByID(0x7ccc115, 1);
    if (w)
        w->Slot7C(2, flag);
    int st = mTimer20.mUnits;
    char flag2 = 1;
    if (st == 1)
        flag2 = (m8c.type != 0);
    else if (st == 2)
        flag2 = (mA4 != 0);
    else if (st == 3 && m7f != 0)
        flag2 = (m168 != m16c);
    if (DAT_016c7AA4->m1c->Fn4320() != 0)
        flag2 = 0;
    FUN_00df9b30(flag2);
}

// ===========================================================================
// 00dfa460   launch an asset with a summary object
// ===========================================================================
// @ 0x00dfa460
void GGUI::FUN_00dfa460(int* param_2, unsigned char param_3)
{
    kGUI_PanelIDs->Fn53d0(0);
    Obj4C* obj = 0;
    FUN_006447c0(0, &obj);
    obj->m24 = DAT_015da7c4;
    obj->m28 = DAT_015da7c8;
    obj->m2c = DAT_015da7cc;
    obj->m30 = DAT_015da7d0;
    obj->m34 = 0;
    obj->m36 = 0;
    LD2 d;
    d.Fn4b10();
    d.m04 = this;
    Summ13* a = (Summ13*)operator_new(0x14, "Sporepedia", 0, 0, 0, 0);
    if (a == 0) {
        a = 0;
    } else {
        a->v4 = (int)vtbl_ContentValidationSummarizer;
        a->v8 = 0;
        a->v0 = (int)vtbl_AddRef;
        a->v4 = (int)vtbl_FUN_0149bad8;
        a->vc = (int)kGUI_PanelIDs;
        a->v10 = 0;
    }
    d.m0c = a;
    d.m38 = this ? (void*)&mBase8 : 0;
    d.m18 = param_2[0];
    d.m1c = param_2[1];
    d.m20 = param_2[2];
    d.m00 = 0x32ece105;
    d.m30 = &LAB_00ad0e52;
    d.m11 = 1;
    d.m24 = param_3;
    FUN_0064a990(&d);
    FUN_00ef7d90();
    d.Fn4b60();
    if (obj != 0)
        obj->FnV8();
}