// Slice s00ef7d90 — Simulator editor/UI helpers (config, gadget HUD, audio,
// hashtable insertion, key handling).  /O2 /MD /Gy /EHsc /TP region.
#include "types.h"

// ---------------------------------------------------------------------------
// Masked externals.
// ---------------------------------------------------------------------------
extern int g_simMgr;    // 0x016c7aa4
extern int g_appPrefs;  // 0x015fd91c

struct Stub {  // generic thiscall target carrier (only conventions matter)
    void* GetPlayerInventory(int, int, int);
    void* FUN_005cae30();
    void* FUN_005c2e50();
    void* GetAllocator();
    int FUN_00f3e8a0(void*);
    void* FUN_00ed4b50(int);
    int FUN_006c0200();
    void* FUN_0067caf0(int, int, int, int, int, int, int, int, int, int);
    void* FUN_0067aaf0(int, int, int, int, int, int, int, int, int, int);
    void* FUN_0067cac0(unsigned, int);
    void* FUN_0067c8c0(unsigned, int);
    void* FindWindowByID(int, int);
    void* GetWindowByID(int);
    void* FUN_00a23d20(int*);
    void* FUN_00a23ef0(int*, int*);
    void* FUN_00ef7ec0(int);
    void* FUN_00ef7b40();
    void  SetBoolProperty();   // 0x0093a2e0 (cDirectPropertyList)
    void  SetTimeLimit(unsigned, int);   // 0x0093a480 (LimitStopwatch)
    void  ReleaseAll();        // 0x00ef7b40
    void* FUN_00ef7b90(void*);
    void* FUN_00ef7a00();
    void* FUN_00efa0b0(int, int);
    void* FUN_00ef75b0(int, int, int);
    void* FUN_00ef7640(int, int);
    void* FUN_00ef7600(int, int, int);
    void* FUN_00ef76a0(int, int);
};

struct VObj {  // polymorphic subobject (vtable slot access)
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void* s3(unsigned);
    virtual void* s4();
    virtual void* s5(unsigned);
    virtual void* s6(unsigned);
    virtual void* s7(unsigned);
    virtual void* s8();
    virtual void* s9(unsigned);
    virtual void* s10(unsigned);
    virtual void* s11(unsigned);
    virtual void* s12(unsigned);
    virtual void* s13(unsigned);
    virtual void* s14(unsigned);
    virtual void* s15(unsigned);
    virtual void* s16(unsigned, unsigned);
    virtual void* s17(unsigned);
    virtual void* s18(unsigned);
    virtual void* s19(unsigned);
    virtual void* s20(unsigned);
    virtual void* s21(unsigned);
    virtual void* s22(unsigned);
    virtual void* s23(unsigned);
    virtual void* s24(unsigned);
    virtual void* s25(unsigned);
    virtual void* s26(unsigned);
    virtual void* s27(unsigned);
    virtual void* s28(unsigned);
    virtual void* s29(unsigned);
    virtual void* s30(unsigned);
    virtual void* s31(int, int);
};

struct CEditor {  // receiver (ECX) carrier for the hashtable/step helpers
    bool FUN_00ef8820(int);
    void FUN_00ef8860();
    bool FUN_00ef84b0();          // this+0x44 = inventory index (default 5)
    int  FUN_00ef8940(int mode);  // hashtable gap count for table mode 0/1
};

extern "C" void* FUN_0041e920(void* p);  // Property::GetBool

// ---------------------------------------------------------------------------
// @ 0x00ef8440
// ---------------------------------------------------------------------------
// @ 0x00ef8440
bool FUN_00ef8440() {
    void* g = *(void**)((char*)(*(void**)(char*)&g_simMgr) + 0x14);
    g = *(void**)((char*)g + 0x14);
    void* x = 0;
    if (g) {
        void* p1 = ((Stub*)g)->GetPlayerInventory(0, 0, 0);
        void* p2 = ((Stub*)p1)->FUN_005cae30();
        void* p3 = ((Stub*)p2)->FUN_005c2e50();
        void* p4 = ((Stub*)p3)->FUN_005cae30();
        if (p4)
            x = ((VObj*)((char*)p4 + 0xc))->s3(0x722de63);
    }
    void* holder = *(void**)((char*)(*(void**)(char*)&g_simMgr) + 0x74);
    return ((Stub*)holder)->FUN_00f3e8a0(((Stub*)x)->GetAllocator()) == 0;
}

// ---------------------------------------------------------------------------
// @ 0x00ef84b0
// ---------------------------------------------------------------------------
bool CEditor::FUN_00ef84b0() {
    void* g = *(void**)((char*)(*(void**)(char*)&g_simMgr) + 0x14);
    g = *(void**)((char*)g + 0x14);
    void* x = 0;
    if (g) {
        int idx = *(int*)((char*)this + 0x44);
        if (idx == -1)
            idx = 5;
        void* p1 = ((Stub*)g)->GetPlayerInventory(0, 0, idx);
        void* p2 = ((Stub*)p1)->FUN_005cae30();
        void* p3 = ((Stub*)p2)->FUN_005c2e50();
        void* p4 = ((Stub*)p3)->FUN_005cae30();
        if (p4)
            x = ((VObj*)((char*)p4 + 0xc))->s3(0x722de63);
    }
    void* holder = *(void**)((char*)(*(void**)(char*)&g_simMgr) + 0x74);
    return ((Stub*)holder)->FUN_00f3e8a0(((Stub*)x)->GetAllocator()) == 0;
}

// ---------------------------------------------------------------------------
// @ 0x00ef8550
// ---------------------------------------------------------------------------
extern "C" void* __cdecl SP_ConfigManager();   // 0x67dd30

struct ConfigMgr {              // SP::ConfigManager() result; only slot 0x30 is used here
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual int  HasProperty(unsigned id);      // +0x30
};

struct CGadget {                // receiver (ecx) of the simulator gadget toggles
    char   pad0[0x10];
    void*  mpWindow;            // +0x10  window whose children are toggled
    VObj*  mpFlash;             // +0x14  flash/video player
    char   pad1[0x28 - 0x18];
    int    m28;                 // +0x28
    char   pad2[0x34 - 0x2c];
    int    m34;                 // +0x34
    void   releaseAll();        // 0x00ef7b40
    void   Toggle(int show);    // 0x00ef8550
    void   AudioToggle(int id); // 0x00ef8600
};

// @ 0x00ef8550
void CGadget::Toggle(int show)
{
    if ((char)show != 0) {
        if (((ConfigMgr*)SP_ConfigManager())->HasProperty(0x4ea96cb) == 0)
            return;
    } else {
        releaseAll();
    }
    VObj* o = mpFlash;
    if (o)
        o->s31(1, show);
}

// ---------------------------------------------------------------------------
// @ 0x00ef8590
// ---------------------------------------------------------------------------
struct Qpc {                       // LARGE_INTEGER
    __int64 q;                     // +0x00
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(Qpc* out);  // [0x13cc2b8]
extern int     g_16c7b60;
extern int     g_16c7b64;
extern __int64 g_deadline;         // 0x16c7b78 (LARGE_INTEGER)
extern int     g_15acef0;

struct SimManager {                // the global simulator manager (0x016c7aa4)
    char  pad0[0x14];
    Stub* mpAudio;                 // +0x14  audio/voice object
};

// @ 0x00ef8590
void FUN_00ef8590() {
    if ((g_16c7b60 | g_16c7b64) == 0)
        return;
    Qpc now;
    QueryPerformanceCounter(&now);
    if (g_deadline - now.q >= 0)
        return;
    ((Stub*)&g_16c7b60)->SetBoolProperty();
    Stub* audio = ((SimManager*)*(void**)&g_simMgr)->mpAudio;
    Stub* r = (Stub*)audio->FUN_00ed4b50(g_15acef0);
    return r->ReleaseAll();
}

// ---------------------------------------------------------------------------
// @ 0x00ef3770-family and larger bodies: behavioural reconstructions.
// ---------------------------------------------------------------------------
extern "C" void* __cdecl EA_Audio_GetSystemAT();   // 0xa206f0

// @ 0x00ef8600
void CGadget::AudioToggle(int id) {
    releaseAll();
    VObj* c = (VObj*)((VObj*)((Stub*)mpWindow)->FindWindowByID(id + 1000, 1))->s4();
    c->s31(2, 1);
    VObj* at = (VObj*)EA_Audio_GetSystemAT();
    void* u = at ? at->s8() : 0;
    VObj* at2 = (VObj*)EA_Audio_GetSystemAT();
    if (at2) {
        at2->s14(0x3475365);
        at2->s16(0x3475381, 0x738674d7);
        at2->s16(0x3475385, (unsigned)u);
        at2->s22(0);
    }
    ((Stub*)&g_16c7b60)->SetTimeLimit(4, 1);
    g_15acef0 = m28;
    m34 = id;
}

// @ 0x00ef8770
void* FUN_00ef8770(int param_1, unsigned param_2, int* param_3) {
    *(int*)(param_1 + 8) = 0;
    *(int*)(param_1 + 0xc) = 0;
    *(int*)(param_1 + 0x10) = 0x3f800000;
    *(int*)(param_1 + 0x14) = 0x40000000;
    *(int*)(param_1 + 0x18) = 0;
    int iVar1 = *param_3;
    *(int*)(param_1 + 0x1c) = 0;
    // eastl::fixed_pool_base::init(param_1+0x1c, iVar1, 0x80, 8, 4, 0)
    ((Stub*)((char*)&g_simMgr))->FUN_00ed4b50(iVar1);
    *(int*)(param_1 + 0x24) = iVar1;
    *(int*)(param_1 + 0x28) = iVar1 + 0x80;
    *(int*)(param_1 + 0x2c) = 8;
    *(int*)(param_1 + 0x30) = param_3[5];
    if (param_2 < 2) {
        *(int*)(param_1 + 0xc) = 0;
        *(int*)(param_1 + 0x18) = 0;
        *(int*)(param_1 + 8) = 1;
        *(int*)(param_1 + 4) = (int)0x154df28;
        return (void*)param_1;
    }
    unsigned v = (unsigned)((Stub*)0)->FUN_00ef7b90(0);
    *(int*)(param_1 + 8) = v;
    *(int*)(param_1 + 4) = (int)((Stub*)v)->FUN_00ef7b90((void*)(size_t)v);
    return (void*)param_1;
}

// @ 0x00ef8820
bool CEditor::FUN_00ef8820(int param_2) {
    int param_1 = (int)this;
    int local_8[2];
    ((Stub*)((char*)param_1 + 0x5c))->FUN_00a23ef0(local_8, &param_2);
    return local_8[0] != *(int*)(*(int*)(param_1 + 0x60) + *(int*)(param_1 + 0x64) * 4);
}

// @ 0x00ef8860
void CEditor::FUN_00ef8860() {
    int param_1 = (int)this;
    int iVar3 = *(int*)(param_1 + 0x30);
    if (iVar3 == -1)
        return;
    int iVar1 = *(int*)(param_1 + 0x34);
    if (iVar1 == -1)
        return;
    int* table = 0;
    if (iVar1 == 0)
        table = (int*)(0x148b450 + iVar3 * 0x10);
    else if (iVar1 == 1)
        table = (int*)(0x148b510 + iVar3 * 0x10);
    if (table) {
        int i = table[0];
        while (i <= table[1]) {
            ((Stub*)((char*)param_1 + 0x5c))->FUN_00a23d20(&i);
            ++i;
        }
        for (int k = 0; k != 0xad; ++k)
            ((Stub*)param_1)->FUN_00ef7ec0(k);
    }
    int o = (int)((Stub*)(*(void**)((char*)(*(void**)(char*)&g_simMgr) + 0x14)))->FUN_00ed4b50(*(int*)(param_1 + 0x34));
    if (o) {
        void* sub = *(void**)(o + 0x1c);
        ((VObj*)sub)->s31(1, 0);
    }
    *(int*)(param_1 + 0x30) = -1;
    *(int*)(param_1 + 0x34) = -1;
    *(char*)(param_1 + 0x3b) = 0;
    *(char*)(param_1 + 0x3d) = 0;
    *(char*)(param_1 + 0x3e) = 0;
    *(char*)(param_1 + 0x3f) = 0;
    *(char*)(param_1 + 0x40) = 0;
    *(int*)(param_1 + 0x44) = -1;
    *(short*)(param_1 + 0x38) = 0;
    *(char*)(param_1 + 0x3a) = 0;
}

// @ 0x00ef8940 — hashtable occupancy/gap count over a bucket array.
int CEditor::FUN_00ef8940(int mode) {
    int count = 0;
    if (mode == 0)
        count = 0xc;
    else if (mode == 1)
        count = 5;
    char* base = (char*)this + mode * 0x14c + 0x4a8;
    int stride = *(int*)(base + 8);
    int* buckets = (int*)*(int*)((char*)this + mode * 0x14c + 0x4ac);
    int* ref = (int*)buckets[stride];
    int diff = 0;
    for (int u = 0; u < count; ++u) {
        int* p = *(int**)((char*)buckets + (u % stride) * 4);
        int* found;
        while (p) {
            if (u == *p) {
                found = p;
                goto chk;
            }
            p = (int*)p[1];
        }
        found = *(int**)((char*)buckets + stride * 4);
    chk:
        if (found != ref)
            ++diff;
    }
    return diff;
}

// ---------------------------------------------------------------------------
// Large dispatchers below: behaviour summarised (partial).
// ---------------------------------------------------------------------------
// @ 0x00ef7d90
void FUN_00ef7d90() {
    void* prefs = *(void**)&g_appPrefs;
    void* cm = *(void**)((char*)&g_simMgr);  // ConfigManager(); placeholder
    (void)cm;
    int present = 0;
    char old = 0;
    if (prefs) {
        int* prop = 0;
        if (((VObj*)prefs)->s3(0x7d1fe81) != 0) {
            (void)prefs;
        }
        (void)prop;
    }
    if (present && old == 0)
        ;
}

// @ 0x00ef7ec0
void FUN_00ef7ec0(int param_1) {
    (void)param_1;  // large key dispatcher; see decompile (partial)
}

// @ 0x00ef8390
void FUN_00ef8390(int param_1, int a2, int a3, int a4, int a5, int a6, int a7) {
    (void)param_1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6; (void)a7;
}

// @ 0x00ef8a10
void FUN_00ef8a10(int param_1, unsigned param_2) {
    switch (param_2) {
        case 0x19: ((Stub*)param_1)->FUN_00ef75b0(0, 0x1a, 0x1b); ((Stub*)param_1)->FUN_00ef7640(0, 1); break;
        case 0x27: *(char*)(param_1 + 0x38) = 1; *(char*)(param_1 + 0x3a) = 1; break;
        case 0x2b: ((Stub*)param_1)->FUN_00ef75b0(2, 0x2c, 0x2d); ((Stub*)param_1)->FUN_00ef7640(2, 1); break;
        case 0x31: ((Stub*)param_1)->FUN_00ef75b0(5, 0x32, 0x33); ((Stub*)param_1)->FUN_00ef7640(5, 1); break;
        case 0x3f: ((Stub*)param_1)->FUN_00ef75b0(0, 0x40, 0x41); ((Stub*)param_1)->FUN_00ef7640(0, 1); break;
        case 0x55: ((Stub*)param_1)->FUN_00ef75b0(1, 0x56, 0x57); ((Stub*)param_1)->FUN_00ef7640(1, 1); break;
        case 0x88: ((Stub*)param_1)->FUN_00ef7600(0, 0x89, 0x8a); ((Stub*)param_1)->FUN_00ef76a0(0, 1); break;
        case 0x8e: ((Stub*)param_1)->FUN_00ef7600(1, 0x8f, 0x90); ((Stub*)param_1)->FUN_00ef76a0(1, 1); break;
        case 0x9a: ((Stub*)param_1)->FUN_00ef7600(2, 0x9b, 0x9c); ((Stub*)param_1)->FUN_00ef76a0(2, 0); break;
        case 0x9e: ((Stub*)param_1)->FUN_00ef7600(3, 0x9f, 0xa0); ((Stub*)param_1)->FUN_00ef76a0(3, 0); break;
        case 0xa4: ((Stub*)param_1)->FUN_00ef7600(4, 0xa5, 0xa6); ((Stub*)param_1)->FUN_00ef76a0(4, 1); break;
        default: break;
    }
}

// @ 0x00ef8cc0 — eastl::hashtable::DoInsertKey (partial: allocator/hash tail)
void FUN_00ef8cc0(int param_1, void* param_2, unsigned* param_3) {
    (void)param_1; (void)param_2; (void)param_3;
}