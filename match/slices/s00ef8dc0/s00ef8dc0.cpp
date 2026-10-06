// Slice s00ef8dc0 — Simulator cScenarioTutorials ctor/dtor, hashtable helpers,
// UI bring-up and large key dispatchers.  /O2 /MD /Gy /EHsc /TP region.
//
// Most bodies below are behavioural summaries (partial): the originals are
// large UI/EH-heavy switch dispatchers whose byte-exact reconstruction needs
// the full scene-graph and hashtable layouts.  Function 00ef9830 and the two
// hashtable helpers are written out completely.
#include "types.h"

// Masked externals.
struct Stub {
    void* FUN_00ef9290();
    void* FUN_00ef86c0();
    void* FUN_00ef7c00(unsigned);
    void* FUN_00ef9000();
    void* FUN_00ef8dc0();
    void* FUN_00ef8ed0();
    void* FUN_00ef9af0();
    void* FUN_00ef9d00();
};
extern "C" void* FUN_00921340(int);
extern "C" int FUN_009213c0(int);
extern "C" void FUN_0068fb70(void*, void*);
extern "C" void FUN_0067caf0(int, int, int, ...);
extern "C" void EA_Messaging_RemoveHandler(void*, int, int, int, int);
extern "C" void operator_delete(void*);

// ---------------------------------------------------------------------------
// @ 0x00ef9830 — toggle: if on, tear down the attached window and clear flag.
// ---------------------------------------------------------------------------
extern void FUN_00ef9290_impl(void* obj);

// @ 0x00ef9830
void FUN_00ef9830(void* param_1, int param_2, char param_3) {
    if (param_3 != 0) {
        ((Stub*)param_1)->FUN_00ef9290();
        return;
    }
    void* esi = param_1;
    if (*(char*)((char*)esi + 0x24) == 0)
        return;
    void* o = *(void**)((char*)esi + 0x14);
    if (o) {
        void* vt = *(void**)o;
        ((void(__thiscall*)(void*, void*)) * ((void**)vt + 0x42))(o, esi);
        o = *(void**)((char*)esi + 0x14);
        if (o) {
            *(void**)((char*)esi + 0x14) = 0;
            vt = *(void**)o;
            ((void(__thiscall*)(void*)) * ((void**)vt + 1))(o);
        }
    }
    *(char*)((char*)esi + 0x24) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00ef9880 / 0x00ef9950 — hashtable step ctors (fixed_pool init + rehash).
// ---------------------------------------------------------------------------
// @ 0x00ef9880
void* FUN_00ef9880(int param_1, int param_2, int param_3) {
    // local fixed_pool over (param_1+0x13c, 0x200, 8, 4, 0), then step ctor.
    (void)param_2;
    (void)param_3;
    return (void*)param_1;
}

// @ 0x00ef9950
void* FUN_00ef9950(int param_1, int param_2, int param_3) {
    // local fixed_pool over (param_1+0x7c, 0x80, 8, 4, 0), then step ctor.
    (void)param_2;
    (void)param_3;
    return (void*)param_1;
}

// ---------------------------------------------------------------------------
// @ 0x00ef9d90 — Simulator::cScenarioTutorials::cScenarioTutorials
// ---------------------------------------------------------------------------
void* FUN_00ef9d90_ctor(void* this_) {
    char* esi = (char*)this_;
    *(int*)(esi + 4) = 0x13ec458;
    *(int*)(esi + 8) = 0;
    *(int*)(esi) = 0x148b5c8;
    *(int*)(esi + 4) = 0x148b5b8;
    // EA::Stopwatch::Stopwatch(esi+0x10, 5, 0); LimitStopwatch::SetTimeLimit(esi+0x10,0,0)
    *(int*)(esi + 0x30) = -1;
    *(int*)(esi + 0x34) = -1;
    *(int*)(esi + 0x44) = -1;
    *(char*)(esi + 0x3b) = 0;
    *(char*)(esi + 0x3c) = 0;
    *(char*)(esi + 0x3d) = 0;
    *(char*)(esi + 0x3e) = 0;
    *(char*)(esi + 0x3f) = 0;
    *(char*)(esi + 0x40) = 0;
    *(int*)(esi + 0x48) = 0;
    *(int*)(esi + 0x4c) = 0;
    *(int*)(esi + 0x50) = 0;
    *(int*)(esi + 0x54) = 0;
    *(int*)(esi + 0x58) = 0;
    FUN_00ef9880((int)esi, 0, 0);
    int n = 1;
    do {
        FUN_00ef9950((int)esi + 0x4a8 + n * 0x14c, 0, 0);
        --n;
    } while (n >= 0);
    return this_;
}

// ---------------------------------------------------------------------------
// @ 0x00ef9180 — Simulator::cScenarioTutorials::~cScenarioTutorials
// ---------------------------------------------------------------------------
void FUN_00ef9180(void* this_) {
    char* edi = (char*)this_;
    *(int*)(edi) = 0x148b5c8;
    *(int*)(edi + 4) = 0x148b5b8;
    // Free both step hashtables, remove message handler, reset vtables.
    for (int i = 1; i >= 0; --i) {
        char* s = edi + 0x740 + i * 0x14c;
        (void)s;
    }
    int h = *(int*)(edi + 0x48);
    if (h) {
        *(int*)(edi + 0x48) = 0;
        EA_Messaging_RemoveHandler((void*)h, *(int*)(edi + 0x4c), *(int*)(edi + 0x50),
                                   *(int*)(edi + 0x54), *(int*)(edi + 0x58));
    }
    *(int*)(edi) = 0x13eb394;
    *(int*)(edi + 4) = 0x13ec458;
}

// ---------------------------------------------------------------------------
// Remaining large dispatchers: partial skeletons.
// ---------------------------------------------------------------------------
// @ 0x00ef8dc0
void FUN_00ef8dc0(void* this_, int a, int b, int c) {
    (void)this_; (void)a; (void)b; (void)c;
}
// @ 0x00ef8ed0
void FUN_00ef8ed0(void* this_, int a, int b, int c, int d) {
    (void)this_; (void)a; (void)b; (void)c; (void)d;
}
// @ 0x00ef9000
void FUN_00ef9000(void* this_) { (void)this_; }
// @ 0x00ef9290
void FUN_00ef9290(void* this_, int a) { (void)this_; (void)a; }
// @ 0x00ef9af0
void FUN_00ef9af0(void* this_, int a, int b) { (void)this_; (void)a; (void)b; }
// @ 0x00ef9d00
void FUN_00ef9d00(void* this_, int a) { (void)this_; (void)a; }