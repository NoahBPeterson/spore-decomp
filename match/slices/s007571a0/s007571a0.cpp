// Slice s007571a0 (batch w2g3, slice 15).
// Graphics / game-model region.  The 0x10c-byte object built by FUN_00755070 is an
// intrusive-refcounted job/model holder (two polymorphic bases at +0/+4, a RefVector at
// +0x84, refcounted pointers at +0x98/+0x9c, bools at +0xb0/+0xc4/+0xc5, a resource-key
// block at +0xf0 and pointers at +0x104/+0x108).
// Built with /O2 /arch:SSE and /EHsc (SEH prologs).
#include "../../include/types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// intrusive reference-count protocol (refcount is the int at object+4)
// ---------------------------------------------------------------------------
struct RCObj;
struct RCObj { void* vptr; long refcount; };

static inline void RCAddRef(RCObj* p) {
    if (p) _InterlockedIncrement(&p->refcount);
}
static inline void RCRelease(RCObj* p) {
    if (p && _InterlockedExchangeAdd(&p->refcount, -1) == 1) {
        *((long*)&p->refcount) = 1;
        ((void (__thiscall*)(RCObj*, int))p->vptr)(p, 1);
    }
}

// vector of intrusive pointers {begin,end,cap}
struct RCArray {
    RCObj** mBegin;
    RCObj** mEnd;
    RCObj** mCap;
};

// The big job/model object.
struct C0755 {
    void* vptr;      // +0x00
    void* vptr2;     // +0x04
    void* mp08;      // +0x08
    void* mp0c;      // +0x0c
    RCObj* mp10;     // +0x10
    char pad14[0x84 - 0x14];
    RCArray mVec;    // +0x84
    char pad90[0x98 - 0x90];
    RCObj* mp98;     // +0x98
    RCObj* mp9c;     // +0x9c
    char padA0[0xb0 - 0xa0];
    bool mbB0;       // +0xb0
    char padB1[0xc4 - 0xb1];
    bool mbC4;       // +0xc4
    bool mbC5;       // +0xc5
    char padC6[0x104 - 0xc6];
    RCObj* mp104;    // +0x104
    RCObj* mp108;    // +0x108
    bool EnsureFront(void* arg);
};

// small 0x58 value produced by the two paths of FUN_007571a0.
struct C0058 {
    void* vptr;      // +0
    long refcount;   // +4
    char pad[0x58 - 8];
};

extern "C" void  __cdecl FUN_007391f0(void* vec, void* p);        // push into vector
extern "C" void  __cdecl FUN_0041ee90(int n);                      // vector resize
extern "C" void  __cdecl FUN_006df280(void* p);                     // release holder
extern "C" void  __cdecl FUN_007361e0(void* p);                     // front hook A
extern "C" void  __cdecl FUN_00734970(void* p);                     // front hook B
extern "C" void  __cdecl FUN_00756fc0(void* a, void* b);            // vector reset
extern "C" void* __cdecl FUN_0040d160(void);                        // 0x58 factory
extern "C" void  __cdecl FUN_0041ebe0(void* p);                     // refarray assign
extern "C" void  __cdecl FUN_0041f320(void* p);                     // refarray assign 2
extern "C" void  __cdecl FUN_007552e0(void* p);                     // refarray assign 3
extern "C" void  __cdecl FUN_00753e00(void* p, void* dst, int n);   // copy 6 words
extern "C" void* __cdecl FUN_0068f4d0(void);                        // job manager singleton
extern "C" void  __cdecl FUN_0068f9b0(void* p);
extern "C" void  __cdecl FUN_006909b0(void);
extern "C" void  __cdecl FUN_00691380(void* p);
extern "C" void  __cdecl FUN_0068f950(void* p);
extern "C" void  __cdecl FUN_006a1710(void* p);
extern "C" void* __cdecl FUN_00755070(void* p);
extern "C" void* __cdecl operator_new_graph(unsigned size);         // 0xf473a0 allocator
extern "C" void* __cdecl SP_PropertyManager();
extern "C" void* __cdecl SP_MaterialManager();
extern "C" int   __cdecl FUN_0071ddc0(void* self, int a, int b, int c, int d);
extern "C" void  __cdecl FUN_00424430(void*, void*);
extern "C" void  __cdecl eh_vec_ctor_006c0fa0(void* p, unsigned sz, unsigned n, void* ctor);
extern "C" void  __cdecl eh_vec_dtor(void* p, unsigned sz, unsigned n, void* dtor);

// ---------------------------------------------------------------------------
// @ 0x00757d10
// ---------------------------------------------------------------------------
extern int g_vtbl_13ef094[];
void __fastcall FUN_00757d10(int* self) {
    self[1] = (int)g_vtbl_13ef094;
}

// ---------------------------------------------------------------------------
// @ 0x00757e20   ctor of a small value type (two Matrix3, a refcounted ptr, an int)
// ---------------------------------------------------------------------------
struct M3 { float m[9]; };
extern M3 g_m3_162f16c;
extern float g_f162f028, g_f162f02c, g_f162f030, g_f1485720;
extern "C" void __cdecl M3Assign(M3* dst, const M3* src);

struct Val7e20 {
    uint16_t w00;      // +0
    uint16_t w02;      // +2
    float f04, f08, f0c, f10;   // +4,+8,+c,+10
    M3 m14;            // +0x14
    uint16_t w38, w3a; // +0x38
    float f3c, f40, f44, f48;   // +0x3c..+0x48
    M3 m4c;            // +0x4c
    int   i70;         // +0x70
    RCObj* p74;        // +0x74
    RCObj* p78;        // +0x78
    Val7e20* Ctor(Val7e20* src, RCObj* a2, RCObj* a3);
};
Val7e20* Val7e20::Ctor(Val7e20* src, RCObj* a2, RCObj* a3) {
    this->w02 = 0;
    this->w00 = 0;
    this->f04 = g_f162f028;
    this->f08 = g_f162f02c;
    this->f0c = g_f162f030;
    this->f10 = g_f1485720;
    M3Assign(&this->m14, &g_m3_162f16c);
    this->w38 = src->w00;
    this->w3a = src->w02;
    this->f3c = src->f04;
    this->f40 = src->f08;
    this->f44 = src->f0c;
    this->f48 = src->f10;
    M3Assign(&this->m4c, &src->m14);
    this->i70 = -1;
    this->p74 = a2;
    if (a2) ((void (__thiscall*)(RCObj*))a2->vptr)(a2);
    this->p78 = a3;
    if (a3) ++a3->refcount;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00757ff0   ctor of a 0x24-byte value type
// ---------------------------------------------------------------------------
struct Val7ff0Base {
    virtual void slot0();
};
struct Val7ff0 : Val7ff0Base {
    char pad04[4];
    RCObj* p0c;    // +0x0c
    RCObj* p10;    // +0x10
    int    f14, f18, f1c, f20, f24;   // +0x14..+0x24
    Val7ff0* Ctor(RCObj* a2, int* a3);
};
Val7ff0* Val7ff0::Ctor(RCObj* a2, int* a3) {
    this->p0c = 0;
    this->p10 = 0;
    this->p0c = a2;
    if (a2) ((void (__thiscall*)(RCObj*))a2->vptr)(a2);
    RCObj* r = (RCObj*)a3[0];
    this->p10 = r;
    if (r) _InterlockedIncrement(&r->refcount);
    this->f14 = a3[1];
    this->f18 = a3[2];
    this->f1c = a3[3];
    this->f20 = a3[4];
    this->f24 = a3[5];
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x007580a0
// ---------------------------------------------------------------------------
struct C0755b { void* vptr; char pad[0x10]; };
C0755b* __cdecl FUN_007580a0(C0755b* self) {
    void* mm = SP_MaterialManager();
    int idx = FUN_0071ddc0(self, 0x15, 0, 6, 0xe);
    if (idx < 0) return 0;
    char* base = *(char**)((char*)self + 8);
    char* e = base + idx * 0x20;
    RCObj* p1 = *(RCObj**)(e + 0x1c);
    void** p2 = *(void***)(e + 0x14);
    int v = *(int*)(e + 0x10);
    if (p1) ((void (__thiscall*)(RCObj*))p1->vptr)(p1);
    if (v) {
        int r = (*(int (__thiscall**)(void*, void*))(*(int*)mm + 0x28))(mm, *p2);
        if (r) {
            int out = *(int*)(r + 4);
            RCRelease(p1);
            return (C0755b*)out;
        }
    }
    RCRelease(p1);
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x007581a0   destructor
// ---------------------------------------------------------------------------
void __fastcall FUN_007581a0(C0755* self) {
    RCRelease(self->mp10);
    if (self->mp0c) ((void (__thiscall*)(void*))(*(void***)self->mp0c)[1])(self->mp0c);
    self->vptr2 = g_vtbl_13ef094;
}

// ---------------------------------------------------------------------------
// @ 0x00757d20   SP::GetRwModelAsGameMeshesNoCache
// ---------------------------------------------------------------------------
struct Arena {
    int  GetNumExportedObjects();
    void GetExportedObjectByIndex(int i, void* out);
};
struct ArenaHolder { char pad[0x18]; Arena* pArena; };
int __cdecl FUN_00757d20(ArenaHolder* h) {
    Arena* a = *(Arena**)((char*)h + 0x18);
    int n = a->GetNumExportedObjects();
    if (n <= 0) return 0;
    for (int i = 0; i < n; ++i) {
        char buf[0x38];
        *(int*)(buf + 0) = 0;
        *(int*)(buf + 4) = 0;
        *(int*)(buf + 0xc) = 0;
        *(int*)(buf + 0x10) = 0;
        *(int*)(buf + 0x14) = 0;
        *(int*)(buf + 8) = 0;
        eh_vec_ctor_006c0fa0(buf + 0x18, 8, 4, (void*)0);
        *(int*)(buf + 0x18) = 0;
        *(int*)(buf + 0x1c) = 1;
        a->GetExportedObjectByIndex(i, buf);
        bool hit = (*(int*)buf == 0x200af);
        eh_vec_dtor(buf + 0x18, 8, 4, (void*)0);
        if (hit) return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x007571a0
// ---------------------------------------------------------------------------
C0058* __cdecl MakeC0058(int kind, void* src);
bool C0755::EnsureFront(void* arg) {
    C0755* self = this;
    RCArray* v = &self->mVec;
    FUN_00756fc0(v, v);
    unsigned count = (unsigned)(v->mEnd - v->mBegin);
    bool empty = (v->mBegin == v->mEnd);
    if (count > 1) {
        C0058* p = MakeC0058(1, self);
        FUN_007391f0(v, p);
        FUN_0041ee90(1);
        FUN_006df280(&p);
    } else if (!empty) {
        C0058* p = MakeC0058(2, arg);
        if (v->mEnd < v->mCap) {
            *v->mEnd = (RCObj*)p;
            v->mEnd = v->mEnd + 1;
            if (p) _InterlockedIncrement(&p->refcount);
        } else {
            FUN_00424430(v->mEnd, &p);
        }
        RCRelease((RCObj*)p);
    }
    FUN_007361e0(*(void**)v->mBegin);
    if (!self->mbC5) FUN_00734970(*(void**)v->mBegin);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x007573a0   SP::GetModelAsGameMeshes
// ---------------------------------------------------------------------------
// Large asynchronous job-setup routine.  Reproduces the allocation, the property
// manager lookup, and the 4-slot callback loop.
struct PropList { void* vptr; };
PropList* __cdecl FUN_007573a0(void* param_1, void* a2, void* a3, void* a4,
                               void* a5, void* a6, void* a7, int a8, void* a9,
                               void* a10, void* a11) {
    C0755* obj = (C0755*)operator_new_graph(0x10c);
    if (obj) FUN_00755070(obj);
    void* pm = SP_PropertyManager();
    (*(void (__thiscall**)(void*, void*, void*, void**))(*(int*)pm + 0x34))(pm, a4, a5, &obj->mp08);
    void* jm = FUN_0068f4d0();
    (*(void (__thiscall**)(void*))(*(int*)jm + 0x20))(jm);
    for (int i = 0; i < 4; ++i) {
        void* cb = 0;
        (*(void (__thiscall**)(void*, void**))(*(int*)jm + 0x10))(jm, &cb);
        FUN_0068f9b0(obj);
        FUN_00691380(cb);
        (*(void (__thiscall**)(void*))(*(int*)jm + 0x24))(jm);
    }
    (void)param_1; (void)a2; (void)a3; (void)a6; (void)a7; (void)a8; (void)a9;
    (void)a10; (void)a11;
    return (PropList*)obj;
}
