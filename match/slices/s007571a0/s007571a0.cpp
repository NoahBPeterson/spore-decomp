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
// SP::GetModelAsGameMeshes (0x007573a0)
// ---------------------------------------------------------------------------
// Builds the 0x10c-byte mesh-job object from a property list (loading or creating the
// "Graphics" list when none is given), then queues the per-slot job chain on the job manager.
typedef unsigned int u32;

void* operator new(unsigned size, const char* name, int flags, unsigned dbg, const char* file, int line);   // 0x00f473a0
struct MeshJob;

struct cJob {
    void* mpCallback;       // +0x00
    void* mpCallbackData;   // +0x04
    char  pad08[0x10];
    u32   mThreadAffinity;  // +0x18
    int   mSlot;            // +0x1c
    u32   pad20[2];
    void AddRef();                  // 0x0068f950
    void Release();                 // 0x00690120
    void SetExtra(void* obj);       // 0x0068f9b0 (ret 4)
    void After(cJob* prev);         // 0x00691380 (ret 4)
    void Submit();                  // 0x006909b0
};

// EA::AutoRefCount-like handle to a job
struct JobRef {
    cJob* p;
    JobRef() : p(0) {}
    JobRef(cJob* q) : p(q) { if (p) p->AddRef(); }
    ~JobRef() { if (p) p->Release(); }
    JobRef& operator=(const JobRef& o)
    {
        if (o.p != p) {
            cJob* old = p;
            if (o.p) o.p->AddRef();
            p = o.p;
            if (old) old->Release();
        }
        return *this;
    }
    cJob** operator&() { if (p) { cJob* o = p; p = 0; o->Release(); } return &p; }
    cJob* operator->() const { return p; }
};

struct Property {
    void* data;             // +0x00 (inline value or pointer)
    u32   pad04[3];
    u32   flags;            // +0x10
    short type;             // +0x12 is the high half of flags
};
struct PropList {
    virtual void AddRef();
    virtual void Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20();
    virtual bool GetProperty(u32 id, Property** out);   // 0x24
    void SetParent(PropList* parent);                    // 0x006a1710 (ret 4)
};
struct cPropertyList : PropList {
    u32 pad04[13];                                       // sizeof == 0x38
    cPropertyList();                                     // 0x006a1c40
};
void operator delete(void* p, const char* name, int flags, unsigned dbg, const char* file, int line);
struct PropMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropList(u32 a, u32 b, PropList** out);       // 0x2c
    virtual void v30();
    virtual void RegisterPropList(PropList* l, u32 a, u32 b);     // 0x34
};
PropMgr* GetPropMgr();      // 0x0067de30
extern PropList* g_AppProperties;   // 0x015fd918

struct JobMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual bool CreateJob(cJob** out);     // 0x10
    virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void Begin();                   // 0x20
    virtual void End();                     // 0x24
};
JobMgr* GetJobMgr();        // 0x0068f4d0

template <class T> struct ARC {
    T* p;
    ARC(T* q) : p(q) { if (p) p->AddRef(); }
    ~ARC() { if (p) p->Release(); }
    T** operator&() { if (p) { T* o = p; p = 0; o->Release(); } return &p; }
    T* operator->() const { return p; }
    ARC& operator=(T* q)
    {
        T* old = p;
        if (q != old) {
            if (q) q->AddRef();
            p = q;
            if (old) old->Release();
        }
        return *this;
    }
};

struct VecA {
    void Assign(const VecA* src);   // 0x0041ebe0 (ret 4)
};
struct VecB {
    void Assign(const void* src);   // 0x0041f320 (ret 4)
};
struct VecC {
    void Assign(const void* src);   // 0x007552e0 (ret 4)
};
void CopyProps6(PropList* list, void* dst, int n);    // 0x00753e00 (cdecl)

struct Sub4 { void* vptr; };   // second base at +4 of the arg10 object

// intrusive pointer whose target keeps its refcounted interface at +4
struct SubRef {
    Sub4* p;
    SubRef& operator=(Sub4* q)
    {
        Sub4* old = p;
        if (q != old) {
            if (q) ((void(__thiscall*)(void*))(*(void***)((char*)q + 4))[0])((char*)q + 4);
            p = q;
            if (old) ((void(__thiscall*)(void*))(*(void***)((char*)old + 4))[1])((char*)old + 4);
        }
        return *this;
    }
};

static inline void RCRelease2(RCObj* p) {
    if (p && _InterlockedDecrement(&p->refcount) == 0) {
        _InterlockedExchange(&p->refcount, 1);
        ((void (__thiscall*)(RCObj*, int))(*(void***)p)[0])(p, 1);
    }
}

struct MeshJob {
    virtual void AddRef();
    virtual void Release();
    void* vptr2;            // +0x04
    char  pad08[4];
    u32   mId3;             // +0x0c
    u32   mId4;             // +0x10
    u32   mIds[4];          // +0x14
    float mSlotWeight[4];   // +0x24
    int   mSlotInt[4];      // +0x34
    char  pad44[0x10];
    u32   mProps[6];        // +0x54
    char  pad6c[0x84 - 0x6c];
    VecA  mVec84;           // +0x84
    char  pad85[0x14 - 1];
    RCObj* mp98;            // +0x98
    VecA  mVec9c;           // +0x9c
    char  pad9d[0x14 - 1];
    bool  mbB0;             // +0xb0
    char  padB1[0xc4 - 0xb1];
    bool  mbC4;             // +0xc4
    bool  mbC5;             // +0xc5
    char  padC6[2];
    VecB  mVecC8;           // +0xc8
    char  padC9[0x14 - 1];
    VecC  mVecDc;           // +0xdc
    char  padDd[0x14 - 1];
    bool  mbF0;             // +0xf0
    char  padF1[3];
    u32   mKey[3];          // +0xf4
    char  padOth[0x104 - 0x100];
    PropList* mpList;       // +0x104
    SubRef mSub108;         // +0x108
    MeshJob();              // 0x00755070 (thiscall, returns this)
};

#include <stddef.h>
#define OFFCHK(m, off) typedef char chk_##m[(offsetof(MeshJob, m) == (off)) ? 1 : -1]
OFFCHK(mId3, 0x0c); OFFCHK(mIds, 0x14); OFFCHK(mSlotWeight, 0x24); OFFCHK(mSlotInt, 0x34); OFFCHK(mProps, 0x54);
OFFCHK(mVec84, 0x84); OFFCHK(mp98, 0x98); OFFCHK(mVec9c, 0x9c); OFFCHK(mbB0, 0xb0); OFFCHK(mbC4, 0xc4); OFFCHK(mbC5, 0xc5);
OFFCHK(mVecC8, 0xc8); OFFCHK(mVecDc, 0xdc); OFFCHK(mbF0, 0xf0); OFFCHK(mKey, 0xf4); OFFCHK(mpList, 0x104); OFFCHK(mSub108, 0x108);
typedef char chk_size[(sizeof(MeshJob) == 0x10c) ? 1 : -1];

// job callbacks, stored as raw function addresses
extern char FUN_00757390, FUN_00754fe0, FUN_007564a0, FUN_00757170, FUN_00757180, FUN_00757190, FUN_00754c00, FUN_00756b40;

struct Key12 { u32 a, b, c; };

// @ 0x007573a0
bool __cdecl FUN_007573a0(cJob** pJob, VecA* vecSrc, u32 id3, u32 id4, RCObj* rc5, VecA* vec6,
                          PropList* listArg, VecB* arg8, VecC* arg9, Sub4* arg10, Key12* key,
                          cJob* chain)
{
    ARC<PropList> list(listArg);
    if (!list.p) {
        PropMgr* pm = GetPropMgr();
        pm->GetPropList(id3, id4, &list);
        if (!list.p) {
            list = new ("Graphics", 0, 0, 0, 0) cPropertyList;
            ARC<PropList> parent(0);
            PropMgr* pm2 = GetPropMgr();
            if (pm2->GetPropList(0xabf001c6, 0x44a7f6af, &parent))
                list.p->SetParent(parent.p);
            GetPropMgr()->RegisterPropList(list.p, id3, id4);
        }
    }

    ARC<MeshJob> obj(new ("Graphics", 0, 0, 0, 0) MeshJob);
    obj->mVec84.Assign(vecSrc);
    {
        RCObj* old = obj->mp98;
        if (rc5 != old) {
            RCAddRef(rc5);
            obj->mp98 = rc5;
            RCRelease2(old);
        }
    }
    obj->mbB0 = false;
    if (vec6) {
        obj->mVec9c.Assign(vec6);
        obj->mbB0 = true;
    }
    obj->mSub108 = arg10;
    obj->mbC4 = false;
    obj->mbC5 = false;
    if (key) {
        obj->mbF0 = true;
        obj->mKey[0] = key->a;
        obj->mKey[1] = key->b;
        obj->mKey[2] = key->c;
        obj->mKey[1] = 0x2f4e681b;
    } else {
        obj->mbF0 = false;
    }
    if (arg8) {
        obj->mVecC8.Assign(arg8);
        obj->mbC4 = true;
    }
    if (arg9) {
        obj->mVecDc.Assign(arg9);
        obj->mbC5 = true;
    }
    obj->mId3 = id3;
    obj->mId4 = id4;
    u32 base = id4 & 0xffffff00;
    obj->mIds[0] = base;
    base = (base & 0xffffff01) | 1;
    obj->mIds[1] = base;
    base = (base & 0xffffff02) | 2;
    obj->mIds[2] = base;
    base = (base & 0xffffff03) | 3;
    obj->mIds[3] = base;
    obj->mSlotWeight[0] = -1.0f;
    obj->mSlotWeight[1] = 0.0f;
    obj->mSlotWeight[2] = 0.0f;
    obj->mSlotWeight[3] = 0.0f;

    bool found = false;
    for (int i = 0; i < 4; ++i) {
        if (list.p) {
            Property* prop;
            if (list->GetProperty(0x2e765cf + i, &prop) && prop->type == 0xd) {
                float* v = (float*)prop;
                if (prop->flags & 0x30) v = *(float**)prop;
                found = true;
                obj->mSlotWeight[i] = *v;
            }
            if (list.p) {
                Property* prop2;
                if (list->GetProperty(0x452027c + i, &prop2) && prop2->type == 0xa) {
                    int* v2 = (int*)prop2;
                    if (prop2->flags & 0x30) v2 = *(int**)prop2;
                    obj->mSlotInt[i] = *v2;
                }
            }
        }
    }
    if (!found) {
        int i = 0;
        do {
            Property* prop3;
            if (g_AppProperties && g_AppProperties->GetProperty(0x2e765cf + i, &prop3) && prop3->type == 0xd) {
                float* v = (float*)prop3;
                if (prop3->flags & 0x30) v = *(float**)prop3;
                obj->mSlotWeight[i] = *v;
            }
            ++i;
        } while (i < 4);
    }
    CopyProps6(list.p, obj->mProps, 6);
    {
        PropList* old = obj->mpList;
        if (list.p != old) {
            if (list.p) list.p->AddRef();
            obj->mpList = list.p;
            if (old) old->Release();
        }
    }

    JobMgr* jm = GetJobMgr();
    jm->Begin();
    if (jm->CreateJob(pJob)) {
        (*pJob)->mpCallback = &FUN_00757390;
        (*pJob)->mpCallbackData = obj.p;
        (*pJob)->mThreadAffinity = 0x80000000;
        (*pJob)->SetExtra(obj.p);
        JobRef jobA;
        jm->CreateJob(&jobA.p);
        jobA->mpCallback = &FUN_00754fe0;
        jobA->mpCallbackData = obj.p;
        jobA->SetExtra(obj.p);
        jobA->mThreadAffinity = 1;
        JobRef jobB;
        if (arg9) {
            jm->CreateJob(&jobB.p);
            jobB->mpCallback = &FUN_007564a0;
            jobB->mpCallbackData = obj.p;
            jobB->mThreadAffinity = 1;
            jobB->SetExtra(obj.p);
        }
        JobRef jobC;
        JobRef jobD;
        for (int i = 0; i < 4; ++i) {
            JobRef prev(*pJob);
            JobRef jobE;
            if (0.0f < obj->mSlotWeight[i]) {
                jm->CreateJob(&jobE.p);
                jobE->mpCallback = &FUN_00757170;
                jobE->mpCallbackData = obj.p;
                jobE->mSlot = i;
                jobE->mThreadAffinity = 0x80000000;
                jobE->After(prev.p);
                jobE->SetExtra(obj.p);
                jobE->Submit();
                prev = jobE;
            }
            if (obj->mSlotWeight[i] != 0.0f) {
                if (i == 2 && obj->mbF0) {
                    jm->CreateJob(&jobC);
                    jobC->mpCallback = &FUN_00757180;
                    jobC->mpCallbackData = obj.p;
                    jobC->mSlot = 2;
                    jobC->mThreadAffinity = 0x80000000;
                    jobC->SetExtra(obj.p);
                    jobC->After(prev.p);
                    jobC->Submit();
                    prev = jobC;
                }
                JobRef jobF;
                jm->CreateJob(&jobF.p);
                jobF->mpCallback = &FUN_00757190;
                jobF->mpCallbackData = obj.p;
                jobF->mSlot = i;
                jobF->mThreadAffinity = 1;
                jobF->SetExtra(obj.p);
                jobF->After(prev.p);
                jobF->Submit();
                prev = jobF;
                if (i == 0 && obj->mbF0) {
                    jm->CreateJob(&jobD);
                    jobD->mpCallback = &FUN_00754c00;
                    jobD->mpCallbackData = obj.p;
                    jobD->mSlot = 0;
                    jobD->mThreadAffinity = 0x80000000;
                    jobD->SetExtra(obj.p);
                    jobD->After(prev.p);
                    prev = jobD;
                }
                if (jobB.p) {
                    JobRef jobG;
                    jm->CreateJob(&jobG.p);
                    jobG->mpCallback = &FUN_00756b40;
                    jobG->mpCallbackData = obj.p;
                    jobG->mSlot = i;
                    jobG->mThreadAffinity = 1;
                    jobG->SetExtra(obj.p);
                    jobG->After(prev.p);
                    jobG->Submit();
                    jobB->After(jobG.p);
                }
                jobA->After(prev.p);
            }
        }
        if (jobD.p) {
            jobD->After(jobC.p);
            jobD->Submit();
        }
        jobA->Submit();
        if (jobB.p) {
            jobB->After(jobA.p);
            jobB->Submit();
            if (chain) chain->After(jobB.p);
        } else if (chain) {
            chain->After(jobA.p);
        }
    }
    jm->End();
    return true;
}
