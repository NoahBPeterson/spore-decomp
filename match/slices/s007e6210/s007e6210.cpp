// Slice s007e6210.
#include "../s007e5220/s007e5220.h"
#include <intrin.h>

extern "C" void operator_delete__(void* p);

// ---- generic property-list wrapper (watcher target) ----
struct PropListBase {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20();
  virtual char vf24(void* a, void* b);   // +0x24
};
int GetModCount(void* propertyList);
struct CPropList { int GetModificationCount(); };
struct PropWatcher {
  uint32_t f0;   // +0
  void*    f4;   // +4  (wraps the PropListBase)
  void*    f8;   // +8  (owner passed to vf24)
  int      fc;   // +0xc cached modification count
  void* f10;     // +0x10 (property list at wrapper+0x30)
  bool Check();
  void Read(void* p2);
};
extern int32_t gDefaultWatcherValue;

uint32_t* FUN_004e41c0();
struct R4E41c0 { uint32_t* getval(); };

struct JobManagerVtbl_ {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18();
  virtual void vf7(void* thread, void* sw, int b);   // +0x1c
  virtual void vf8(); virtual void vf9();
  virtual void vf10(void* a);                          // +0x28
  virtual void vf11();                                 // +0x2c
};
void* FUN_00921d70();

// @ 0x007E6690
struct PtrDel { void* p; void del(); };
void PtrDel::del() {
    operator_delete__(p);
}

// @ 0x007E6630
bool cAppSystem::FUN_007e6630() {
    long old = _InterlockedExchangeAdd((volatile long*)&mJobRefCount, 0);
    return old > 0;
}

// @ 0x007E65D0
void cAppSystem::FUN_007e65d0(bool add) {
    if (add) {
        if (_InterlockedIncrement((volatile long*)&mJobRefCount) == 1)
            ((JobManagerVtbl_*)mJobManager)->vf10(FUN_00921d70());
    } else {
        if (_InterlockedDecrement((volatile long*)&mJobRefCount) == 0)
            ((JobManagerVtbl_*)mJobManager)->vf11();
    }
}

// @ 0x007E6650
struct Stopwatch {
  char pad[0x20];
  void ctor(int a, int b);
  void SetTimeLimit(int limit, int b);
};
void cAppSystem::RunJobs(int timeLimit) {
    Stopwatch sw;
    sw.ctor(4, 0);
    sw.SetTimeLimit(timeLimit, 1);
    JobManagerVtbl_* jm = (JobManagerVtbl_*)mJobManager;
    jm->vf7(mBaseThread, &sw, 1);
}

// @ 0x007E66A0
bool PropWatcher::Check() {
    int* w = (int*)f4;
    if (w) {
        int mc = (int)w[0xc] ? ((CPropList*)w[0xc])->GetModificationCount() : 0;
        if ((int)fc != (int)w[0xd] + mc) {
            int mc2 = (int)w[0xc] ? ((CPropList*)w[0xc])->GetModificationCount() : 0;
            fc = (int)w[0xd] + mc2;
            PropListBase* pb = (PropListBase*)w;
            PropWatcher* local = this;
            if (pb->vf24(f8, &local)) {
                uint32_t v = *FUN_004e41c0();
                if (f0 != v) {
                    f0 = v;
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x007E6720
void PropWatcher::Read(void* p2) {
    PropListBase* pb = (PropListBase*)p2;
    if (pb->vf24(f8, &p2)) {
        int* q = (int*)p2;
        short t = *(short*)((char*)q + 0x12);
        int* src;
        if (t == 9 || t == 0x10) {
            if ((*(uint8_t*)((char*)q + 0x10) & 0x30) == 0)
                src = (int*)(-(uint32_t)(t != 0) & (uint32_t)q);
            else
                src = (int*)*q;
        } else {
            src = &gDefaultWatcherValue;
        }
        f0 = (uint32_t)*src;
    }
    int* w = (int*)f4;
    if (w[0xc]) {
        fc = (int)w[0xd] + ((CPropList*)w[0xc])->GetModificationCount();
        return;
    }
    fc = (int)w[0xd];
}

// @ 0x007E6210
void LoadGameInfoProperties(void* data) {
    // Reads "game info" AppProperties; incomplete (see partial.txt).
    (void)data;
}

// ---- PreShutdown helpers ----
extern void* gPTR_DAT_0153f85c;
extern void* gPTR_DAT_0153f860;
void FUN_008d5d10(int); void FUN_0067e090(int); void FUN_006ae940();
void FUN_00762f00(int); void FUN_0068c460();
void FUN_0067df00(int); void FUN_0067df30(int);
void FUN_007c79e0(); void FUN_00c2e4e0();
void* SP_CheatManager2();

typedef void (__thiscall *VF0)(void*);
typedef void (__thiscall *VF1)(void*, int);
typedef void (__thiscall *VF3)(void*, void*, int, int);
__forceinline void VC0(void* o, int off) { ((VF0)*(void**)((char*)*(void**)o + off))(o); }
__forceinline void VC1(void* o, int off, int a) { ((VF1)*(void**)((char*)*(void**)o + off))(o, a); }
__forceinline void VC3(void* o, int off, void* a, int b, int c) { ((VF3)*(void**)((char*)*(void**)o + off))(o, a, b, c); }

// @ 0x007E6470  (cAppSystem::PreShutdown)
int cAppSystem::PreShutdown() {
    VC0(*(void**)((char*)this + 0xc8), 0x1c);
    if (mJobManager) { VC0(mJobManager, 8); mBaseThread = 0; }
    if (mAsyncResourceManager) {
        FUN_008d5d10(0); FUN_0067e090(0); FUN_006ae940();
        VC0(mAsyncResourceManager, 4); mAsyncResourceManager = 0;
    }
    if (mGarbageMan) { FUN_00762f00(0); FUN_0068c460(); }
    VC1(SP_CheatManager2(), 0x1c, (int)gPTR_DAT_0153f85c);
    VC1(SP_CheatManager2(), 0x1c, (int)gPTR_DAT_0153f860);
    FUN_007c79e0();
    FUN_00c2e4e0();
    VC3(mMessageServer, 0x2c, (char*)this + 4, 0xf62add, 0xffffd8f1);
    VC3(mMessageServer, 0x2c, (char*)this + 4, (int)0xae1cfe73, 0xffffd8f1);
    VC3(mMessageServer, 0x2c, (char*)this + 4, 0x255abf5, 0xffffd8f1);
    VC3(mMessageServer, 0x2c, (char*)this + 4, 0x212d3e7, 0xffffd8f1);
    void* pc = *(void**)((char*)this + 0xc8);
    if (pc) {
        VC0(pc, 0x10);
        FUN_0067df00(0);
        void* q = *(void**)((char*)this + 0xc8);
        if (q) { *(void**)((char*)this + 0xc8) = 0; VC0(q, 4); }
    }
    void* am = mAppStateManager;
    if (am) {
        VC0(am, 0x14);
        FUN_0067df30(0);
        void* q = *(void**)((char*)this + 0x34);
        if (q) { mAppStateManager = 0; VC0(q, 4); }
    }
    void* gs = mGraphicsSystem;
    if (gs) VC0(gs, 0x10);
    return 1;
}

// @ 0x007E67A0  (cAppSystem::Init)
int cAppSystem::Init() {
    // Full startup sequence (2306 bytes) not reconstructed; see partial.txt.
    return 0;
}

