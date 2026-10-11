// Slice s00ae08b0: Simulator object-context / trigger-manager helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" void* __cdecl operator_new(unsigned int size, const char* name, int, int, int, int); // 0xF473A0
extern "C" void __cdecl operator_delete_(void* p);                                              // 0xF47380

// ---------------------------------------------------------------------------
// Generic reference-counted / queryable object (its vtable slots are the only
// thing used here).  Every used slot returns int so call sites that ignore the
// result still compile.
// ---------------------------------------------------------------------------
struct VObj {
    virtual int v000(); virtual int v004(); virtual int v008();
    virtual int v00c(int);
    virtual int v010(); virtual int v014(); virtual int v018(); virtual int v01c();
    virtual int v020();
    virtual int v024(int);
    virtual int v028(int);
    virtual int v02c();
    virtual int v030(); virtual int v034();
    virtual int v038(int);
    virtual int v03c(); virtual int v040(); virtual int v044(); virtual int v048(); virtual int v04c();
    virtual int v050(); virtual int v054(); virtual int v058(); virtual int v05c();
    virtual int v060(); virtual int v064(); virtual int v068(); virtual int v06c();
    virtual int v070(); virtual int v074(); virtual int v078(); virtual int v07c();
    virtual int v080(); virtual int v084(); virtual int v088(); virtual int v08c();
    virtual int v090(); virtual int v094(); virtual int v098(); virtual int v09c();
    virtual int v0a0(); virtual int v0a4(); virtual int v0a8(); virtual int v0ac();
    virtual int v0b0(); virtual int v0b4(); virtual int v0b8();
    virtual int v0bc();
    virtual int v0c0();
};

// sub-objects reached through a Query result
struct SubObj {
    int FUN_00ade060(void* p);
    int FUN_00ad9010(void* p);
};
struct QueryResult {
    char pad_000[0x10];
    SubObj sub;                 // +0x10
};

// ---------------------------------------------------------------------------
// cTriggerMgr (working name; layout from the disassembly)
// ---------------------------------------------------------------------------
struct cTriggerMgr {
    char pad_000[0x28];
    uint8_t f028, f029, f02a, f02b;
    int f02c;
    char pad_030[0x118 - 0x30];
    void* f118;
    char pad_11c[0x128 - 0x11c];
    void* f128;
    void* f12c;
    void* f130;
    void* f134;
    char pad_138[0x140 - 0x138];
    VObj* f140;
    void* f144;
    void* f148;
    char pad_14c[0x154 - 0x14c];
    int f154;
    char pad_158[0x15f - 0x158];
    uint8_t f15f;
    char pad_160[0x170 - 0x160];
    uint8_t f170, f171;
    char pad_172[0x174 - 0x172];
    int f174, f178;
    uint8_t f17c;
    char pad_17d[0x180 - 0x17d];
    void* f180;
    void* f184;
    char pad_188[0x1a8 - 0x188];
    uint32_t f1a8;
    void* f1ac;
    void* f1b0;

    int  FUN_00adfd60(int a, int b, int c, int d, int e);   // 0xadfd60
    VObj* FUN_00adb250(int key, int val);                   // 0xadb250
    void FUN_00adc890(int key, VObj* obj, int val);         // 0xadc890
    int  PostTrigger(int a1, int a2, int a3, uint32_t* a4, int a5, int a6); // 0xae0930
    void PostAction(int a1, int a2, int a3);                // 0xae09b0
    void FUN_00ae0a80(int a1, int a2);                      // 0xae0a80
};

// 0xae0640
extern "C" void* __fastcall cObjectContext_ctor(void* self);

// container that owns the pointer array at self+0x10
struct Bkt {
    void* f00;
    void* f04;
    uint32_t f08;
    int   f0c;
    void Free(int* bucketArray, int count);
};

// vector<AutoRefCount<cStarRecord>> destructor at self+0x30
extern "C" void __fastcall vector_dtor_ae6970(void* v);

// ===========================================================================
// @ 0x00ae08b0  Simulator::cObjectContext::~cObjectContext (best effort)
// ===========================================================================
void __fastcall FUN_00ae08b0(void* self_)
{
    char* self = (char*)self_;
    *(void**)self = (void*)0x145b918;
    *(void**)(self + 8) = (void*)0x145b908;

    vector_dtor_ae6970(self + 0x30);

    Bkt* c = (Bkt*)(self + 0x10);
    c->Free((int*)c->f04, c->f08);
    c->f0c = 0;
    if (c->f08 > 1) {
        operator_delete_(c->f04);
    }

    *(void**)(self + 8) = (void*)0x13ec458;
    *(void**)self = (void*)0x13eb938;
}

// ===========================================================================
// @ 0x00ae0930  cTriggerMgr::PostTrigger
// ===========================================================================
int cTriggerMgr::PostTrigger(int a1, int a2, int a3, uint32_t* a4, int a5, int a6)
{
    if (!f15f)
        return 0;
    if (a1 == 0)
        return 0;

    int r = f140->v038(a1);
    f1a8 = 0;
    if (a4 != 0) {
        uint8_t* p = (uint8_t*)a4;
        f1a8 = (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
    }

    return FUN_00adfd60(r, a2, a3, a5, a6);
}

// ===========================================================================
// @ 0x00ae09b0  cTriggerMgr::PostAction
// ===========================================================================
void cTriggerMgr::PostAction(int a1, int a2, int a3)
{
    if (a3 == 0) {
        if ((int)f118 != (int)f128) {
            int e = (int)f128;
            int d = (int)f12c;
            int c = (int)f134;
            if (e == d)
                e = *(int*)((char*)(size_t)c - 4) + 0x100;
            a3 = *(int*)((char*)(size_t)e - 8);
        } else {
            a3 = (int)f148;
        }
    }

    VObj* obj = FUN_00adb250(0x4474369, a3);
    if (obj == 0) {
        void* mem = operator_new(0x58, "Simulator/cObjectContext", 0, 0, 0, 0);
        if (mem == 0)
            obj = 0;
        else
            obj = (VObj*)cObjectContext_ctor(mem);
        FUN_00adc890(0x4474369, obj, a3);
        if (obj == 0)
            return;
    }

    QueryResult* r = (QueryResult*)obj->v00c(0x446e39c);
    if (r != 0) {
        int t = r->sub.FUN_00ade060(&a1);
        ((SubObj*)t)->FUN_00ad9010((void*)a2);
    }
}

// ===========================================================================
// @ 0x00ae0a80  cTriggerMgr::PushAction (working name)
// ===========================================================================
void cTriggerMgr::FUN_00ae0a80(int a1, int a2)
{
    if (a2 == 0) {
        if (f118 == f128) {
            a2 = (int)f148;
        } else {
            int e = (int)f128;
            if (e == (int)f12c)
                e = *(int*)((char*)f134 - 4) + 0x100;
            a2 = *(int*)((char*)(size_t)e - 8);
        }
    }

    VObj* obj = FUN_00adb250(0x4474369, a2);
    if (obj == 0) {
        obj = (VObj*)operator_new(0x58, "Simulator/cObjectContext", 0, 0, 0, 0);
        if (obj) {
            cObjectContext_ctor(obj);
        } else {
            obj = 0;
        }
        FUN_00adc890(0x4474369, obj, a2);
        if (obj == 0)
            return;
    }

    VObj* list = (VObj*)obj->v00c(0x446e39c);
    if (list == 0)
        return;

    VObj* p = (VObj*)a1;
    if (p != 0)
        p->v000();

    int* v = (int*)((char*)list + 0x30);
    int* end = (int*)*(int*)((char*)list + 0x34);
    if (end < *(int**)((char*)list + 0x38)) {
        *(int**)((char*)list + 0x34) = end + 1;
        if (end != 0) {
            *end = (int)p;
            if (p != 0)
                p->v000();
        }
    } else {
        extern void FUN_00aea5d0(int* vecEnd, int* value); // 0xaea5d0
        FUN_00aea5d0(end, (int*)&p);
        p = (VObj*)p;
    }

    if (p != 0)
        p->v004();
}

// ===========================================================================
// @ 0x00ae0b80  event-log action dispatch (working reconstruction)
// ===========================================================================
struct Str { void* p0; void* p1; int n; };

struct EventLogObj {
    char GetEventData(int id, int* a, int* b, int zero, void** sptr); // 0xdd69f0
    void RemoveEvent(int id, int zero);                               // 0xdd6d10
};
struct PropMgr {
    int v02c(void* a, void* b, void** out);                           // +0x2c
};
struct PObj {
    virtual int p00(); virtual int p01(); virtual int p02(); virtual int p03();
    virtual int p04(); virtual int p05(); virtual int p06(); virtual int p07();
    virtual int p08();
    virtual int p09(int id, void** out);                              // +0x24
};
struct ActionTarget {
    char pad_000[0x2c];
    VObj* mObj;                                                       // +0x2c
    ActionTarget();                                                   // 0xad7940
};

extern EventLogObj* __cdecl SP_EventLog_();                           // 0xb3d3e0
extern PropMgr*     __cdecl PropertyManager_();                       // 0x67de30
extern cTriggerMgr* __cdecl GetTriggerMgr_();                         // 0xb3d4d0
extern int  __cdecl GetPropertyAsUint32_(void* prop, int id, int* out); // 0x4af210
extern int  __cdecl GetPropertyAsString8_(void* prop, int id, void* out); // 0x6a13b0
extern char* __cdecl FUN_0041e920(void* p);                           // 0x41e920
extern "C" int __cdecl strcmp(const char*, const char*);

bool __cdecl FUN_00ae0b80(int param_1)
{
    int v10 = 0;
    int v0C = 0;
    VObj* sp8 = 0;
    if (!SP_EventLog_()->GetEventData(param_1, &v10, &v0C, 0, (void**)&sp8)) {
        if (sp8 != 0)
            sp8->v004();
        return false;
    }

    PObj* sp4 = 0;
    PropMgr* pm = PropertyManager_();
    if (sp4 != 0) {
        PObj* t = sp4;
        sp4 = 0;
        t->p01();
    }
    pm->v02c((void*)v10, (void*)v0C, (void**)&sp4);

    if (sp8 != 0) {
        ActionTarget at;
        VObj* q = (VObj*)sp8->v00c(0x1186577);
        if (q != at.mObj) {
            if (q != 0)
                q->v0bc();
            VObj* old = at.mObj;
            at.mObj = q;
            if (old != 0)
                old->v0c0();
        }
        if (at.mObj != 0) {
            int v14 = 0;
            if (GetPropertyAsUint32_(sp4, 0x4531c33, &v14) && v14 != 0) {
                ((cTriggerMgr*)GetTriggerMgr_())->PostAction(v14, (int)(size_t)&at, 0);
            }
            at.mObj->v0c0();
        }
    }

    Str str;
    str.p0 = (void*)0x1667bac;
    str.p1 = (void*)0x1667bac;
    str.n  = 0x1667bad;
    if (GetPropertyAsString8_(sp4, 0x4498e8a, (void*)&str)) {
        const char* ps = (const char*)str.p0;
        if (strcmp(ps, (const char*)0x13ec47c) != 0) {
            cTriggerMgr* tm = (cTriggerMgr*)GetTriggerMgr_();
            if (tm->f15f != 0 && ps != 0) {
                int r = tm->f140->v038((int)ps);
                tm->f1a8 = 0;
                tm->FUN_00adfd60(r, 1, 0, 0, 0);
            }
        }
    }

    bool remove = true;
    if (sp4 != 0) {
        void* out = 0;
        if (sp4->p09(0x48f914e, &out)) {
            if (*(short*)((char*)out + 0x12) == 1 && *FUN_0041e920(out) == 0)
                remove = false;
        }
    }
    if (remove) {
        SP_EventLog_()->RemoveEvent(param_1, 0);
    }

    if (str.n - (int)(size_t)str.p0 > 1 && str.p0 != 0) {
        operator_delete_(str.p0);
    }
    if (sp4 != 0)
        sp4->p01();
    if (sp8 != 0)
        sp8->v004();
    return true;
}

// ===========================================================================
// @ 0x00ae0e00  cGameNounManager wrapper
// ===========================================================================
struct cGameNounManager {
    char* GetGameDataVector(void* f1, void* f2, void* f3, void* f4, int param); // 0xb21340
};

struct NounMgrWrapper : cGameNounManager {
    int FUN_00ae0e00(int param);
};

int NounMgrWrapper::FUN_00ae0e00(int param)
{
    return (int)GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                                  (void*)0x00ae05c0, (void*)0x00b1e520, param) + 4;
}
