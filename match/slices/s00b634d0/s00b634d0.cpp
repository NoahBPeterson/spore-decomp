// Slice s00b634d0: cGonzagoTimer (ctor/dtor/Write/serialize), a UI window-checkbox helper set,
// the simulator boot bool, an options handler switch, and Havok shape builders.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int  uint;
typedef unsigned char uchar;

#define PV(n) virtual void pv##n();

void __cdecl opdel_check(void* p);   // 0x00f47380 operator delete (eastl)

// ------------------------------------------------------------------ simulator boot
extern void  __cdecl FUN_00b60d80();   // 0x00b60d80 SP::cSimulatorSystem::Initialize
extern void* __cdecl FUN_00b3d220();   // 0x00b3d220
extern void* __cdecl SP_App();         // 0x0067dd10
struct IApp2 {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual void* GetWindowMgr();   // +0x50
};
struct IWnd2 {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual int FindWindow(unsigned id);   // +0x40
};

// @ 0x00b634d0
bool __cdecl FUN_00b634d0()
{
    FUN_00b60d80();
    void* p = FUN_00b3d220();
    IApp2* app = (IApp2*)SP_App();
    IWnd2* w = (IWnd2*)app->GetWindowMgr();
    int r = w->FindWindow(0xebb801);
    *(int*)((char*)p + 8) = r;
    return r != 0;
}

// ------------------------------------------------------------------ havok memory helpers
struct HkMem {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
    virtual void* Alloc(int a, int b);   // +0x10
};
extern HkMem* g_hkMemory;    // 0x016e4178 hkMemory::s_instance
extern void* g_157b0;        // placeholder

// ------------------------------------------------------------------ cGonzagoTimer
extern void __cdecl FUN_00b63880();
extern void __cdecl FUN_00bc31c0(void (*cb)());
extern void __cdecl FUN_005725a0();
extern void __cdecl FUN_00b316c0();
extern void* __cdecl GameTimeManager();   // 0x00b3d380
extern void* gGonzagoTimerVtbl;           // 0x01464450
extern void __cdecl FUN_005725a0();
extern void __cdecl FUN_00b316c0();

struct CSBase {
    void Init(void (*cb)());
    char IsRunning();            // 0x00feba90
    long long GetElapsedTime();  // 0x00bc3190
};
struct GameTimeObj { void Reset(); };         // 0x00b316c0 (thiscall)
struct DelObj { void Delete(); };

struct cGonzagoTimer : CSBase {
    char  pad04[4];
    long long mElapsed;  // +0x08
    long long mBase;     // +0x10
    int   mPad18;        // +0x18
    void* mGetMs;        // +0x1c
    cGonzagoTimer();
    ~cGonzagoTimer();
    void Write(void* ser);          // 0x00b638d0
    uchar Read(void* ser);          // 0x00b63930
    void AddElapsed(int v);         // 0x00b638c0
};

// @ 0x00b63880
void __cdecl FUN_00b63880()
{
    ((GameTimeObj*)GameTimeManager())->Reset();
}

// @ 0x00b63890
cGonzagoTimer::cGonzagoTimer()
{
    Init(&FUN_00b63880);
    *(void**)this = &gGonzagoTimerVtbl;
}

// @ 0x00b638b0
cGonzagoTimer::~cGonzagoTimer()
{
    *(void**)this = &gGonzagoTimerVtbl;
    FUN_005725a0();
}

// @ 0x00b638c0
void __thiscall cGonzagoTimer::AddElapsed(int v)
{
    *(long long*)((char*)this + 8) += v;
}

// ------------------------------------------------------------------ cVarListSerializer
struct cVarListSerializer {
    char data[0xa14];
    cVarListSerializer(void* obj, void* info, unsigned sig);  // 0x00692f90
    void Serialize(void* ser);                                 // 0x00692900
    uchar SerializeB(void* ser);                               // 0x00693e10
};
extern void* __cdecl cSPTimer_IsRunning(void* p);      // 0x00feba90 (thiscall-ish helper)
extern long long __cdecl cSPTimer_GetElapsed(void* p); // 0x00bc3190
extern char gSig2;   // 0x0156ad88
// @ 0x00b638d0
void __thiscall cGonzagoTimer::Write(void* ser)
{
    if (IsRunning()) {
        long long t = GetElapsedTime();
        mElapsed = t;
        long long b = ((long long(__thiscall*)(void*))mGetMs)(this);
        mBase = b;
    }
    cVarListSerializer s((char*)this, &gSig2, 0x1a80d26);
    s.Serialize(ser);
}

// @ 0x00b63930
uchar __thiscall cGonzagoTimer::Read(void* ser)
{
    cVarListSerializer s((char*)this, &gSig2, 0x1a80d26);
    uchar r = s.SerializeB(ser);
    long long b = ((long long(__thiscall*)(void*))mGetMs)(this);
    mBase = b;
    return r;
}

// ------------------------------------------------------------------ user32 checkbox helpers
extern "C" __declspec(dllimport) unsigned __stdcall IsDlgButtonChecked(void* hwnd, int id);
extern "C" __declspec(dllimport) void     __stdcall CheckDlgButton(void* hwnd, int id, unsigned check);
extern "C" __declspec(dllimport) int      __stdcall MoveWindow(void* hwnd, int x, int y, int w, int h, int repaint);

struct WndObj { char pad[4]; void* hwnd; void FSet(int id, char check); void FGet(int id, uchar* out); };

// @ 0x00b639b0
void __thiscall WndObj::FSet(int id, char check)
{
    int want = check != 0;
    unsigned cur = IsDlgButtonChecked(hwnd, id);
    if ((unsigned)want != cur) {
        CheckDlgButton(hwnd, id, (unsigned)want);
    }
}

// @ 0x00b639f0
void __thiscall WndObj::FGet(int id, uchar* out)
{
    unsigned cur = IsDlgButtonChecked(hwnd, id);
    switch (cur) {
    case 0: *out = 0; break;
    case 1: *out = 1; break;
    }
}

// ------------------------------------------------------------------ options handler (huge switch)
struct Obj63510 {
    char pad[0x30];
    int  mCount;   // +0x30
    uchar m0c;     // +0x0c
    uchar m0d;     // +0x0d
    uchar Dispatch(unsigned id, void* arg);   // 0x00b63510
};
// @ 0x00b63510  (partial: large option-id dispatch)
uchar __thiscall Obj63510::Dispatch(unsigned id, void* arg)
{
    (void)id; (void)arg;
    return 0;
}

// ------------------------------------------------------------------ table search helpers
// @ 0x00b63f70
int __cdecl FUN_00b63f70(int base, int n)
{
    if (n >= 0) {
        int* p = (int*)(base + 0x9c + n * 4);
        for (; n >= 0; n--, p--) {
            if (*p != 0) return n;
        }
    }
    return -1;
}

// ------------------------------------------------------------------ map<unsigned,int> init/dtor
struct MapU32 {
    char pad0[4];
    uint* mBuckets;   // +0x04
    uint  mCount;     // +0x08
    uchar mFlag;      // +0x0c
    void DoAllocateBuckets(uint a, uint b);   // 0x00693230 (thiscall)
};

struct Obj63BD0 {
    void* vt;                 // +0x00
    char  pad04[0x1118];
    MapU32 mapA;              // +0x1118
    MapU32 mapB;              // +0x1138
    void Init();              // 0x00b63bd0
};
extern void* gVtbl63BD0;   // 0x0145e9a8
extern void* gMapEmpty;    // 0x0154df28

// @ 0x00b63bd0
void __thiscall Obj63BD0::Init()
{
    *(void**)this = &gVtbl63BD0;
    *(float*)((char*)this + 0x1128) = 1.0f;
    *(float*)((char*)this + 0x112c) = 2.0f;
    *(uint*)((char*)this + 0x1120) = 1;
    *(uint*)((char*)this + 0x1124) = 0;
    *(uint*)((char*)this + 0x1130) = 0;
    *(void**)((char*)this + 0x111c) = &gMapEmpty;
    *(float*)((char*)this + 0x1148) = 1.0f;
    *(float*)((char*)this + 0x114c) = 2.0f;
    *(uint*)((char*)this + 0x1140) = 1;
    *(void**)((char*)this + 0x113c) = &gMapEmpty;
    *(uint*)((char*)this + 0x1144) = 0;
    *(uint*)((char*)this + 0x1150) = 0;
}

// @ 0x00b63b60  (dtor body)
void __cdecl FUN_00b63b60(void* self)
{
    *(void**)self = &gVtbl63BD0;
    MapU32* a = (MapU32*)((char*)self + 0x1138);
    a->DoAllocateBuckets(*(uint*)((char*)self + 0x113c), *(uint*)((char*)self + 0x1140));
    *(uint*)((char*)self + 0x1144) = 0;
    if (*(uint*)((char*)self + 0x1140) > 1) opdel_check(*(void**)((char*)self + 0x113c));
    MapU32* b = (MapU32*)((char*)self + 0x1118);
    b->DoAllocateBuckets(*(uint*)((char*)self + 0x111c), *(uint*)((char*)self + 0x1120));
    *(uint*)((char*)self + 0x1124) = 0;
    if (*(uint*)((char*)self + 0x1120) > 1) opdel_check(*(void**)((char*)self + 0x111c));
}

// ------------------------------------------------------------------ remaining (partial)
struct Obj63A20 { uchar F(void* p); };                      // 0x00b63a20
struct Obj63C70 { void F(void* menu, int x, int y, int w, int h, void* text); };  // 0x00b63c70
struct Obj63D50 { void F(void* menu, int x, int y, int w, int h, void* text); };  // 0x00b63d50
// @ 0x00b63a20
uchar __thiscall Obj63A20::F(void* p) { (void)p; return 0; }
// @ 0x00b63c70
void __thiscall Obj63C70::F(void* menu, int x, int y, int w, int h, void* text)
{ (void)menu; (void)x; (void)y; (void)w; (void)h; (void)text; }
// @ 0x00b63d50
void __thiscall Obj63D50::F(void* menu, int x, int y, int w, int h, void* text)
{ (void)menu; (void)x; (void)y; (void)w; (void)h; (void)text; }
// @ 0x00b63e30
void* __cdecl FUN_00b63e30(void* a, float s) { (void)a; (void)s; return 0; }
// @ 0x00b63fb0
int __cdecl FUN_00b63fb0(void* a) { (void)a; return 0; }
// @ 0x00b64040
void __cdecl FUN_00b64040() {}
// @ 0x00b64390
void __cdecl FUN_00b64390(void* a, int* b, int* c) { (void)a; *b = 0; *c = 0; }
