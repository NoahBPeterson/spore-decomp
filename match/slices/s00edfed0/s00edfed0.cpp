// slice s00edfed0 -- UI::cScenarioTutorialsChecklistUI-adjacent property helpers.
//
// Module flags: /O2 /MD /Gy /TP  (no /EHsc; SSE scalar float ops; global singleton at
// 0x016c7aa4 whose +0x74 is the "checklist manager" used for lock/unlock and enumeration).
//
// The `this`/element layouts below are stubs reconstructed from the disassembly:
//   container: +0x20 byte flag, +0x70/+0x74 begin/end of an array of 0x4e0-byte entries
//   entry:     +0x4a4..+0x4c0 integer properties (and a byte at offset 0 in one variant)
#include "types.h"

struct Elem {
    int  v0;                 // +0x000 (byte in f_ee01e0)
    char pad0[0x4a4 - 0x4];
    int  v4a4;               // +0x4a4
    int  v4a8;               // +0x4a8
    int  v4ac;               // +0x4ac
    int  v4b0;               // +0x4b0
    int  v4b4;               // +0x4b4
    int  v4b8;               // +0x4b8
    int  v4bc;               // +0x4bc
    int  v4c0;               // +0x4c0
    char pad1[0x4e0 - 0x4c4];
};

struct Container {
    char  pad0[0x20];
    char  f20;               // +0x20
    char  pad1[0x70 - 0x21];
    char* begin;             // +0x70
    char* end;               // +0x74
};

struct Sub {
    char  pad0[0x84];
    char* f84;               // +0x84 begin
    char* f88;               // +0x88 end
};

struct Manager {
    void  Lock();                     // FUN_00f45970
    void  Unlock();                   // FUN_00f45a80
    void  Refresh();                  // FUN_00f427c0
    int   Count();                    // FUN_00f3be30
    Sub*  Get(int i);                 // FUN_00f3be60
    void* Find(int x);                // FUN_00f3e8a0
};

struct X25 { bool IsSet(); };         // FUN_00f25ed0

struct GlobalObj {
    char      pad0[0x14];
    void*     f14;           // +0x14  (object with FUN_006c0200 getter)
    char      pad1[0x74 - 0x18];
    Manager*  f74;           // +0x74  (checklist manager)
    char      pad2[0xd4 - 0x78];
    void*     fD4;           // +0xd4  (cScenarioTutorialsChecklistUI*)
};
extern GlobalObj* g_16c7aa4;

// ---------------------------------------------------------------------------
// external helpers (defined elsewhere in the module / other TUs)
// ---------------------------------------------------------------------------
bool  __cdecl   FUN_00edfda0(int* dst, int* src);
void  __cdecl   FUN_00edfce0(void* dst, void* src);
bool  __cdecl   FUN_00f3b340(int x);
int   __stdcall FUN_00f416b0(int a, void* b, int c, int d, int e, int f, int g, int h);
void  __cdecl   FUN_00eef170(void* p, int i);
int   __cdecl   FUN_00efc520();
void* __cdecl   FUN_00f40c20(void* a, void* out);
void  __cdecl   operator_delete(void* p);

// ---------------------------------------------------------------------------
// tables (0x148a720, 0x148a754, 0x148a764, 0x148a774)
// ---------------------------------------------------------------------------
static const int kTbl4a8[5] = { 1, 2, 3, 4, 5 };
static const int kTbl4b0[3] = { 1, 2, 3 };
static const int kTbl4b4[3] = { 1, 2, 3 };
static const int kTbl4b8[5] = { 1, 3, 4, 5, 6 };

// ===========================================================================
// @ 0x00edfed0
// ===========================================================================
struct CLS {
    char  pad0[0xc];
    void* f0c;               // +0x0c
    char  pad1[0x18 - 0x10];
    float f18;               // +0x18
    float f1c;               // +0x1c
    void sub(float* a, float* b);   // FUN_00edd440
    int  f_edfed0();
};

int CLS::f_edfed0()
{
    float a = 0.0f;
    float b = 0.0f;
    sub(&a, &b);
    return (f18 == a) && (f1c == b);
}

// ===========================================================================
// @ 0x00edff50   __stdcall: key on stack (manager in ecx ignored)
// ===========================================================================
void __stdcall f_edff50(int key)
{
    Manager* mgr = g_16c7aa4->f74;
    int i = 0;
    if (mgr->Count() > 0) {
        do {
            Sub* o = mgr->Get(i);
            int count = (int)((o->f88 - o->f84) / 0x188);
            int j = 0;
            do {
                if (j < count) {
                    char* e = o->f84 + j * 0x188;
                    if (e != 0 && FUN_00f3b340(*(int*)e)
                        && *(int*)(e + 0xc) == 0
                        && *(int*)(e + 4) == key) {
                        void* r = mgr->Find(*(int*)(e + 4));
                        if (r != 0 && ((X25*)r)->IsSet()) {
                            int v = FUN_00f416b0(i, e, *(int*)(e + 4), 0, 0, 1, 0, 1);
                            if (*(int*)(e + 0xc) != v) {
                                mgr->Lock();
                                *(int*)(e + 0xc) = v;
                                mgr->Unlock();
                            }
                        }
                    }
                }
                ++j;
            } while (j * 0x188 < 0x498);
            ++i;
        } while (i < mgr->Count());
    }
}

// ===========================================================================
// @ 0x00ee0080   __stdcall(void* p, int mode)
// slot indices: 0x1c/4=7, 0x3c/4=15, 0x7c/4=31, 0xf0/4=60
// ===========================================================================
struct VObj {
    virtual void  _v0();  virtual void _v1();  virtual void _v2();  virtual void _v3();
    virtual void  _v4();  virtual void _v5();  virtual void _v6();
    virtual int   GetTypeId();                          // 7  (0x1c)
    virtual void  _v8();  virtual void _v9();  virtual void _v10(); virtual void _v11();
    virtual void  _v12(); virtual void _v13(); virtual void _v14();
    virtual void* GetPtr15();                           // 15 (0x3c)
    virtual void  _v16(); virtual void _v17(); virtual void _v18(); virtual void _v19();
    virtual void  _v20(); virtual void _v21(); virtual void _v22(); virtual void _v23();
    virtual void  _v24(); virtual void _v25(); virtual void _v26(); virtual void _v27();
    virtual void  _v28(); virtual void _v29(); virtual void _v30();
    virtual void  SetFlag(int a, int b);                // 31 (0x7c)
    virtual void  _v32(); virtual void _v33(); virtual void _v34(); virtual void _v35();
    virtual void  _v36(); virtual void _v37(); virtual void _v38(); virtual void _v39();
    virtual void  _v40(); virtual void _v41(); virtual void _v42(); virtual void _v43();
    virtual void  _v44(); virtual void _v45(); virtual void _v46(); virtual void _v47();
    virtual void  _v48(); virtual void _v49(); virtual void _v50(); virtual void _v51();
    virtual void  _v52(); virtual void _v53(); virtual void _v54(); virtual void _v55();
    virtual void  _v56(); virtual void _v57(); virtual void _v58(); virtual void _v59();
    virtual void* FindByHash(int hash, int flag);       // 60 (0xf0)
};

struct HintObj { void ToggleHint(int a, int b); };

void __stdcall f_ee0080(void* p_, int mode)
{
    VObj* p = (VObj*)p_;
    if (p != 0) {
        p->SetFlag(1, 0);
    }
    if (mode == 0)
        return;
    int type = p->GetTypeId();
    if (type == 0x71725b0) {
        VObj* v = (VObj*)p->FindByHash(0x7172970, 1);
        void* r = (v != 0) ? v->GetPtr15() : 0;
        FUN_00edfce0(*(char**)((char*)g_16c7aa4->f74 + 0x10) + 0x7c, &r);
        ((HintObj*)g_16c7aa4->fD4)->ToggleHint(0x81, 0x82);
        return;
    }
    if (type == 0x7172600) {
        VObj* v = (VObj*)p->FindByHash(0x7172950, 1);
        void* r = (v != 0) ? v->GetPtr15() : 0;
        FUN_00edfce0(*(char**)((char*)g_16c7aa4->f74 + 0x10) + 0xb8, &r);
        VObj* w = (VObj*)p->FindByHash(0x7172960, 1);
        void* s = (w != 0) ? w->GetPtr15() : 0;
        FUN_00edfce0(*(char**)((char*)g_16c7aa4->f74 + 0x10) + 0xf4, &s);
        ((HintObj*)g_16c7aa4->fD4)->ToggleHint(0x83, 0x84);
    }
}

// ===========================================================================
// @ 0x00ee01e0   bool(Container*, char* p, char value)  -- byte property at +0
// ===========================================================================
bool __cdecl f_ee01e0(Container* c, char* p, char value)
{
    bool changed = false;
    if (c->f20 == 0) {
        if (*p != value) {
            g_16c7aa4->f74->Lock();
            *p = value;
            g_16c7aa4->f74->Unlock();
            return true;
        }
        return false;
    }
    char cur = *p;
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        if ((char)c->begin[i * 0x4e0] != cur) {
            changed = true;
            goto save;
        }
    }
    changed = (cur != value);
    if (!changed)
        return changed;
save:
    g_16c7aa4->f74->Lock();
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
        (char)c->begin[i * 0x4e0] = value;
    g_16c7aa4->f74->Unlock();
    return changed;
}

// ===========================================================================
// @ 0x00ee0310   bool(Container*, Elem* e, unsigned idx)  -- property +0x4a8, table5
// ===========================================================================
bool __cdecl f_ee0310(Container* c, Elem* e, unsigned idx)
{
    bool changed = false;
    if ((int)idx < 0 || idx >= 5)
        return false;
    idx = (unsigned)kTbl4a8[idx];
    if (c->f20 == 0)
        return FUN_00edfda0(&e->v4a8, (int*)&idx);
    int cur = e->v4a8;
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        if (*(int*)(c->begin + i * 0x4e0 + 0x4a8) != cur) {
            changed = true;
            goto save;
        }
    }
    changed = (cur != (int)idx);
    if (!changed)
        return changed;
save:
    g_16c7aa4->f74->Lock();
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
        *(int*)(c->begin + i * 0x4e0 + 0x4a8) = (int)idx;
    g_16c7aa4->f74->Unlock();
    return changed;
}

// ===========================================================================
// @ 0x00ee0450   bool(Container*, Elem* e, unsigned idx)  -- property +0x4b0, table3
// ===========================================================================
bool __cdecl f_ee0450(Container* c, Elem* e, unsigned idx)
{
    bool changed = false;
    if ((int)idx < 0 || idx >= 3)
        return false;
    idx = (unsigned)kTbl4b0[idx];
    if (c->f20 == 0)
        return FUN_00edfda0(&e->v4b0, (int*)&idx);
    int cur = e->v4b0;
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        if (*(int*)(c->begin + i * 0x4e0 + 0x4b0) != cur) {
            changed = true;
            goto save;
        }
    }
    changed = (cur != (int)idx);
    if (!changed)
        return changed;
save:
    g_16c7aa4->f74->Lock();
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
        *(int*)(c->begin + i * 0x4e0 + 0x4b0) = (int)idx;
    g_16c7aa4->f74->Unlock();
    return changed;
}

// ===========================================================================
// @ 0x00ee0590   bool(Container*, Elem* e, unsigned idx)  -- property +0x4b4, table3
// ===========================================================================
bool __cdecl f_ee0590(Container* c, Elem* e, unsigned idx)
{
    bool changed = false;
    if ((int)idx < 0 || idx >= 3)
        return false;
    idx = (unsigned)kTbl4b4[idx];
    if (c->f20 == 0)
        return FUN_00edfda0(&e->v4b4, (int*)&idx);
    int cur = e->v4b4;
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        if (*(int*)(c->begin + i * 0x4e0 + 0x4b4) != cur) {
            changed = true;
            goto save;
        }
    }
    changed = (cur != (int)idx);
    if (!changed)
        return changed;
save:
    g_16c7aa4->f74->Lock();
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
        *(int*)(c->begin + i * 0x4e0 + 0x4b4) = (int)idx;
    g_16c7aa4->f74->Unlock();
    return changed;
}

// ===========================================================================
// @ 0x00ee06d0   bool(Container*, Elem* e, int idx, void* arg4) -- property +0x4b8
// ===========================================================================
struct IntVec { int* begin; int* end; int* cap; };

bool __cdecl f_ee06d0(Container* c, Elem* e, int idx, void* arg4)
{
    if (idx < 0 || idx >= 5)
        return false;
    int newval = kTbl4b8[idx];
    int cur = e->v4b8;
    bool changed;

    if (c->f20 == 0) {
        if (cur == newval)
            return false;
        g_16c7aa4->f74->Lock();
        e->v4b8 = newval;
        if (!((cur == 4 && newval == 6) || (cur == 6 && newval == 4))) {
            IntVec vec;
            FUN_00f40c20(arg4, &vec);
            int n = (int)((vec.end - vec.begin) >> 2);
            if (n > 0) {
                for (int i = 0; i < n; ++i)
                    FUN_00eef170((void*)vec.begin[i], FUN_00efc520());
            }
            if (vec.begin != 0 && *(int*)(vec.begin - 1) != 0)
                operator_delete(vec.begin);
        }
        g_16c7aa4->f74->Unlock();
        return true;
    }

    changed = false;
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        if (*(int*)(c->begin + i * 0x4e0 + 0x4b8) != cur) {
            changed = true;
            goto save;
        }
    }
    changed = (cur != newval);
    if (!changed)
        return changed;
save:
    g_16c7aa4->f74->Lock();
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        int* slot = (int*)(c->begin + i * 0x4e0 + 0x4b8);
        if (*slot != newval) {
            int old = *slot;
            *slot = newval;
            if (!((old == 4 && newval == 6) || (old == 6 && newval == 4))) {
                IntVec vec;
                FUN_00f40c20(arg4, &vec);
                int n = (int)((vec.end - vec.begin) >> 2);
                if (n > 0) {
                    for (int k = 0; k < n; ++k)
                        FUN_00eef170((void*)vec.begin[k], i);
                }
                if (vec.begin != 0 && *(int*)(vec.begin - 1) != 0)
                    operator_delete(vec.begin);
            }
        }
    }
    g_16c7aa4->f74->Unlock();
    return changed;
}

// ===========================================================================
// @ 0x00ee0960   bool(int key, int index, int value)  -- property +0x4a4 of entry index
// ===========================================================================
struct Obj14 { void SetFlag(int key); };   // f_edff50 as a method of this object

bool __cdecl f_ee0960(int key, int index, int value)
{
    Container* c = (Container*)g_16c7aa4->f74->Find(key);
    char* base = c->begin;
    Elem* e = (Elem*)(base + index * 0x4e0);
    bool changed;

    if (c->f20 == 0) {
        changed = (e->v4a4 != value);
        if (!changed)
            return changed;
        g_16c7aa4->f74->Lock();
        e->v4a4 = value;
        g_16c7aa4->f74->Unlock();
    }
    else {
        int cur = e->v4a4;
        changed = false;
        for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
            if (*(int*)(c->begin + i * 0x4e0 + 0x4a4) != cur) {
                changed = true;
                goto save;
            }
        }
        changed = (cur != value);
        if (!changed)
            return changed;
    save:
        g_16c7aa4->f74->Lock();
        for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
            *(int*)(c->begin + i * 0x4e0 + 0x4a4) = value;
        g_16c7aa4->f74->Unlock();
    }

    if (changed) {
        void* p = (void*)(*(void**)((char*)g_16c7aa4->f14 + 0x18));
        ((Obj14*)p)->SetFlag(key);
        g_16c7aa4->f74->Refresh();
    }
    return changed;
}

// ===========================================================================
// @ 0x00ee0af0   bool(Container*, Elem* e, int value)  -- property +0x4bc
// ===========================================================================
bool __cdecl f_ee0af0(Container* c, Elem* e, int value)
{
    bool changed = false;
    if (c->f20 != 0) {
        int cur = e->v4bc;
        for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
            if (*(int*)(c->begin + i * 0x4e0 + 0x4bc) != cur) {
                changed = true;
                goto save;
            }
        }
        changed = (cur != value);
        if (!changed)
            return changed;
    save:
        g_16c7aa4->f74->Lock();
        for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
            *(int*)(c->begin + i * 0x4e0 + 0x4bc) = value;
        g_16c7aa4->f74->Unlock();
        return changed;
    }
    if (e->v4bc == value)
        return false;
    g_16c7aa4->f74->Lock();
    e->v4bc = value;
    g_16c7aa4->f74->Unlock();
    return true;
}

// ===========================================================================
// @ 0x00ee0c30   bool(Container*, Elem* e, int value)  -- property +0x4c0
// ===========================================================================
bool __cdecl f_ee0c30(Container* c, Elem* e, int value)
{
    bool changed = false;
    if (c->f20 == 0) {
        if (e->v4c0 == value)
            return false;
        g_16c7aa4->f74->Lock();
        e->v4c0 = value;
        g_16c7aa4->f74->Unlock();
        return true;
    }
    int cur = e->v4c0;
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i) {
        if (*(int*)(c->begin + i * 0x4e0 + 0x4c0) != cur) {
            changed = true;
            goto save;
        }
    }
    changed = (cur != value);
    if (!changed)
        return changed;
save:
    g_16c7aa4->f74->Lock();
    for (int i = 0; i < (int)((c->end - c->begin) / 0x4e0); ++i)
        *(int*)(c->begin + i * 0x4e0 + 0x4c0) = value;
    g_16c7aa4->f74->Unlock();
    return changed;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct HintObj {
    void ToggleHint();   // 0x00efbbe0 (equiv t2)
};
}
