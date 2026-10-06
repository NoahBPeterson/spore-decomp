// Slice s00f47680 -- SP::cSporeApp teardown, shutdown, frame update and message handler.
//
// Region is /O2 /MD: no frame pointer, scalar floats via movss, cvttss2si.
// Members at +0x20..+0x3c are EA::AutoRefCount<T> handles and the raw pointers
// mMovieSystem (+0x30) / mFactoryRegistry (+0x24); virtual "Release" calls are
// written as thiscall function-pointer calls at the observed vtable offsets.
#include "types.h"

typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long*);

// ---- external helpers (names from the dev PDB / caller evidence) ----
void* MessageServer();
void  SteamAPI_Shutdown();
void* FUN_0067cc10(int);
void* FUN_0067cc00(int);
void* FUN_0067cc60(int);
void* FUN_0067cb90(int);
void* FUN_0067cb60();
void* FUN_0067e0c0(int);
void* FUN_00692f20();
void* FUN_009200a0(int);
void* FUN_00808780();
void  FUN_00812d30(void*, int);
void* FUN_0068f4d0();
int   Timer_Elapsed(void*);
void  ThreadSleep(void*);
void  D3D9WindowResize(int);
int   GetDescription(void*, unsigned int);
unsigned int FNV1_String16(void*, unsigned int, int);
void* WrapperAlloc(unsigned int);
void* cStringCtor(void*);
void* cStringDtor(void*);
void* cStringTokenTranslatorCtor(void*);
void* cStringDetokenizerCtor(void*);
int   cStringLoad(void*, unsigned int, unsigned int, int);
void* CommandLineFindSwitch(void*, unsigned int, int, int, int);
unsigned int WStr_Format(void*, unsigned int, unsigned int);
void* GetDataDir(int);
void* FUN_009309b0(void*, void*, void*);
void* RangeInitialize(void*);
void* FUN_006884f0(int, int, int, void*, void*);
void  operator_delete__(void*);
void* g_sAppProperties;
void* g_CommandLine;
void* g_15fd928;

struct WString { int assign(unsigned int b, unsigned int e); };

#define VC0(p, off)        (*(void (__thiscall**)(void*))((*(char**)(p)) + (off)))(p)
#define VC1(p, off, a)     (*(void (__thiscall**)(void*, int))((*(char**)(p)) + (off)))(p, (a))
#define VC2i(p, off, a, b) (*(void (__thiscall**)(void*, int, int))((*(char**)(p)) + (off)))(p, (a), (b))
#define RVC0(p, off)       (*(int (__thiscall**)(void*))((*(char**)(p)) + (off)))(p)
#define RVC2i(p, off, a, b) (*(int (__thiscall**)(void*, int, int))((*(char**)(p)) + (off)))(p, (a), (b))

// ---------------------------------------------------------------------------
// cSporeApp layout (dev-PDB): IHandler at +0, RefCountVTemplate<int> at +4.
// ---------------------------------------------------------------------------
struct IHandlerBase {
    virtual bool HandleMessage(unsigned int, unsigned int, int*);
    virtual void h1(); virtual void h2(); virtual void h3(); virtual void h4();
};
struct RefCountBase {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3();
};

struct cSporeApp : IHandlerBase, RefCountBase {
    char pad8[4];
    bool mAppRunning;                  // +0xc
    char padD[3];
    uint64_t mReferenceCycle;          // +0x10
    float mMSPerCycle;                 // +0x18
    float mCyclesPerMS;                // +0x1c
    void* mAppSystem;                  // +0x20
    void* mFactoryRegistry;            // +0x24
    void* mUIMainWin;                  // +0x28
    void* mAudioSystem;                // +0x2c
    void* mMovieSystem;                // +0x30
    void* mEditorSystem;               // +0x34
    void* mTerrainSystem;              // +0x38
    void* mGonzagoSystem;              // +0x3c
    int   mExitCode;                   // +0x40
    void* mProfiler;                   // +0x44

    virtual ~cSporeApp();
    bool Shutdown();
    char HandleMessage(unsigned int msg, int* data);
    char UpdateCheck(void* s, void* out);
    void f47930();
};

// @ 0x00F47680  cSporeApp::~cSporeApp
cSporeApp::~cSporeApp()
{
    if (mGonzagoSystem) VC0(mGonzagoSystem, 0xc);
    if (mTerrainSystem) VC0(mTerrainSystem, 0x4);
    if (mEditorSystem)  VC0(mEditorSystem, 0xc);
    if (mAudioSystem)   VC0(mAudioSystem, 0x14);
    if (mUIMainWin)     VC0(mUIMainWin, 0x4);
    if (mAppSystem)     VC0(mAppSystem, 0x4);
}

// @ 0x00F47700  cSporeApp::Shutdown
bool cSporeApp::Shutdown()
{
    mAppRunning = false;
    void* appSys = mAppSystem;
    void* x = (*(void* (__thiscall**)(void*))(*(char**)appSys + 0x88))(appSys);
    (*(void (__thiscall**)(void*, int, int, int, int, int))(*(char**)x + 0x20))(
        x, (int)"AppShutdown", 0, 0, 0, 0);

    void* ms = MessageServer();
    (*(void (__thiscall**)(void*, int, int, int))(*(char**)ms + 0x14))(ms, 0x238de9c, 0, 0);
    (*(void (__thiscall**)(void*, int, int, int))(*(char**)ms + 0x2c))(ms, (int)(void*)this, 0x153c326, -9999);
    (*(void (__thiscall**)(void*, int, int, int))(*(char**)ms + 0x2c))(ms, (int)(void*)this, 0x1ee100a, -9999);
    (*(void (__thiscall**)(void*, int, int, int))(*(char**)ms + 0x2c))(ms, (int)(void*)this, 0x1ee1003, -9999);
    (*(void (__thiscall**)(void*, int, int, int))(*(char**)ms + 0x2c))(ms, (int)(void*)this, 0x44edd9c, -9999);
    SteamAPI_Shutdown();
    (*(void (__thiscall**)(void*))(*(char**)ms + 0x38))(ms);

    VC0(mEditorSystem, 0x18);
    VC0(mTerrainSystem, 0x14);
    VC0(mAppSystem, 0x24);

    if (mGonzagoSystem) {
        VC0(mGonzagoSystem, 0x1c);
        if (mGonzagoSystem) {
            void* a = mGonzagoSystem;
            mGonzagoSystem = 0;
            VC0(a, 0xc);
        }
    }
    if (mEditorSystem) {
        VC0(mEditorSystem, 0x1c);
        if (mEditorSystem) {
            void* a = mEditorSystem;
            mEditorSystem = 0;
            VC0(a, 0xc);
        }
    }
    if (mTerrainSystem) {
        VC0(mTerrainSystem, 0x18);
        if (mTerrainSystem) {
            void* a = mTerrainSystem;
            mTerrainSystem = 0;
            VC0(a, 0x4);
        }
    }
    if (mMovieSystem) {
        FUN_0067cc10(0);
        VC0(mMovieSystem, 0x8);
        if (mMovieSystem) {
            (*(void (__thiscall**)(void*, int))(*(char**)mMovieSystem + 0x0))(mMovieSystem, 1);
        }
        mMovieSystem = 0;
    }
    if (mUIMainWin) {
        VC0(mUIMainWin, 0x1c);
        if (mUIMainWin) {
            void* a = mUIMainWin;
            mUIMainWin = 0;
            VC0(a, 0x4);
        }
    }
    if (mAudioSystem) {
        VC0(mAudioSystem, 0x8);
        if (mAudioSystem) {
            void* a = mAudioSystem;
            mAudioSystem = 0;
            VC0(a, 0x14);
        }
        FUN_0067cc00(0);
    }
    void* test = g_15fd928;
    if (test) {
        VC0(test, 0x8);
        FUN_0067e0c0(0);
        (*(void (__thiscall**)(void*, int))(*(char**)test + 0x0))(test, 1);
    }
    if (mAppSystem) {
        VC0(mAppSystem, 0x28);
        if (mAppSystem) {
            void* a = mAppSystem;
            mAppSystem = 0;
            VC0(a, 0x4);
        }
    }
    void* p = FUN_0067cb60();
    if (p) {
        FUN_0067cc60(0);
        (*(void (__thiscall**)(void*, int))(*(char**)p + 0x0))(p, 1);
    }
    if (mFactoryRegistry) {
        FUN_00692f20();
        FUN_009200a0(0);
        FUN_0067cb90(0);
        if (mFactoryRegistry) {
            void* a = mFactoryRegistry;
            (*(void (__thiscall**)(void*, int))(*(char**)a + 0x0))(a, 1);
        }
        mFactoryRegistry = 0;
    }
    FUN_00808780();
    return 1;
}

// @ 0x00F47930  cSporeApp frame update (Timer driven)
void cSporeApp::f47930()
{
    if (!mAppRunning) return;
    long long t;
    QueryPerformanceCounter(&t);
    long long d = t - *(long long*)&mReferenceCycle;
    int cycles = (int)((float)d * mMSPerCycle);
    int budget = *(int*)(*(int*)(*(int*)&g_sAppProperties + 0x3c) + 0xb0);

    bool ok = (*(bool (__thiscall**)(void*))(*(char**)mAppSystem + 0x44))(mAppSystem);
    if (ok && budget < 0x2d) {
        if (budget < 0) {
            int v = budget + 1;
            budget = v < 0 ? -v : v;
        } else {
            budget = 0x2d;
        }
    }
    if (budget > 0) {
        void* o = FUN_0068f4d0();
        if ((*(bool (__thiscall**)(void*, int))(*(char**)o + 0x34))(o, -1)) {
            if (budget - cycles < 3) budget = cycles + 3;
            if (cycles < budget - 1) {
                VC1(mAppSystem, 0x84, budget - cycles - 1);
                cycles = Timer_Elapsed(this);
            }
        }
        if (budget - cycles > 0) {
            int wait = budget - cycles;
            ThreadSleep(&wait);
            cycles = Timer_Elapsed(this);
        }
    }

    float f = (float)cycles * mCyclesPerMS;
    long long add = (long long)f;
    *(long long*)&mReferenceCycle += add;

    void* ms = MessageServer();
    (*(void (__thiscall**)(void*))(*(char**)ms + 0x38))(ms);

    if (mUIMainWin) FUN_00812d30(mUIMainWin, cycles);
    if (mEditorSystem) VC1(mEditorSystem, 0x20, cycles);
    if (mTerrainSystem) VC1(mTerrainSystem, 0x1c, cycles);
    if (mGonzagoSystem) VC1(mGonzagoSystem, 0x28, cycles);
    if (mMovieSystem) VC1(mMovieSystem, 0xc, cycles);
    VC1(mAppSystem, 0x78, cycles);

    if (mAudioSystem) {
        float secs = f * 0.001f;
        (*(void (__thiscall**)(void*, float))(*(char**)mAudioSystem + 0x18))(mAudioSystem, secs);
    }
    (*(void (__thiscall**)(void*))(*(char**)mAppSystem + 0x7c))(mAppSystem);
}

// @ 0x00F47B10  cSporeApp::HandleMessage
char cSporeApp::HandleMessage(unsigned int msg, int* data)
{
    if (msg <= 0x1ee100a) {
        if (msg == 0x1ee100a) {
            f47930();
            VC0(mAppSystem, 0x80);
            return 1;
        }
        if (msg == 0x153c326) {
            int v = 0;
            if (data) v = *(int*)((char*)data + 8);
            mExitCode = v;
            *(char*)((char*)this + 0xd) = 0;
            return 1;
        }
        if (msg != 0x1ee1003) return 0;
        int* p = *(int**)((char*)data + 8);
        if (*p == 0x22 && GetDescription(&g_sAppProperties, 0x153c178)) {
            int h = p[4] - p[2];
            int w = p[3] - p[1];
            void* obj = *(char**)((char*)data + 4);
            int arg = RVC2i(obj, 0x94, w, h);
            D3D9WindowResize(arg);
        }
        return 1;
    }
    if (msg != 0x44edd9c) return 0;
    {
        int cycles = Timer_Elapsed(this);
        float f = mMSPerCycle * (float)cycles;
        long long add = (long long)f;
        *(long long*)&mReferenceCycle += add;
    }
    return 1;
}

// @ 0x00F47C20  resource-key predicate + localized-title assignment
char cSporeApp::UpdateCheck(void* s, void* out)
{
    if (FNV1_String16(s, 0x811c9dc5, 1) != 0x81041658) return 0;
    if (*(char*)((char*)this + 8)) {
        const unsigned short* p = (const unsigned short*)0x148d824; // L" Demo"
        const unsigned short* q = p;
        while (*++q != 0) {}
        ((WString*)out)->assign((unsigned int)p, (unsigned int)q);
    } else {
        ((WString*)out)->assign(0x13ec468, 0x13ec468);
    }
    return 1;
}

// @ 0x00F47CA0  build a cStringTokenTranslator / cStringDetokenizer pair and load a string
void f47ca0(char flag, void* outString)
{
    ((WString*)outString)->assign(0x148d830, 0x148d830 + 9 * 2); // L"SPORE(TM)"
    char local[0x10];
    cStringCtor(local);
    void* t = WrapperAlloc(0xc);
    char* trans = 0;
    if (t) {
        cStringTokenTranslatorCtor(t);
        *(char**)t = (char*)0x148d7f4;
        ((char*)t)[8] = flag;
        trans = (char*)t;
    }
    void* d = WrapperAlloc(0x5c);
    char* detok = 0;
    if (d) detok = (char*)cStringDetokenizerCtor(d);
    VC0(detok, 0x20);
    VC1(detok, 0x1c, (int)trans);
    if (cStringLoad(local, 0x40e05d38, 0x319ad21d, 0)) {
        VC2i(detok, 0x28, (int)local, (int)outString);
    }
    (*(void (__thiscall**)(void*, int))(*(char**)detok + 0x0))(detok, 1);
    cStringDtor(local);
}

// @ 0x00F47D80  command-line driven data-directory setup
void f47d80()
{
    void* cl = g_CommandLine;
    int r = (int)CommandLineFindSwitch(cl, 0x13f8d84, 0, 0, 0);
    if (r == -1) {
        r = (int)CommandLineFindSwitch(cl, 0x148d850, 0, 0, 0);
        if (r != -1) {
            char buf[0x40];
            WStr_Format(buf, 0x13f3da0, 0x148d844);
            char path[0x200];
            FUN_009309b0(path, buf, GetDataDir(4));
            char s2[0x10];
            *(char**)(s2 + 0) = (char*)0x1667bac;
            *(char**)(s2 + 4) = (char*)0x1667bac;
            *(char**)(s2 + 8) = (char*)0x1667bae;
            RangeInitialize(s2);
            int out[4];
            out[0] = 0; out[1] = 0; out[2] = 0;
            FUN_006884f0(1, 1, 0x6f4b5d1, out, s2);
            operator_delete__((void*)out[0]);
            operator_delete__((void*)out[2]);
        }
    }
}
