// Slice s0075ff50 : SP::cRenderer (retail layout) + small render-list helpers.
// Region is /O2 /MD /Gy /EHsc /TP. Callees / globals are masked relocations, so only
// the call shapes and field offsets matter.
#include "types.h"
#include <intrin.h>
#include <new>

extern "C" {
void* __cdecl operator_new(unsigned int size, int align, const char* name);
void  __cdecl operator_delete_(void* p);
}

void __cdecl ResetGlobalState();
void* __cdecl SP_Canvas();
void* __cdecl SP_AppSystem();
void __cdecl ClearJobList(void* list);
void __cdecl CloseArena();
void __cdecl DevStop1();
void __cdecl DevStop2();
void __cdecl DevStop3();
void __cdecl timeEndPeriod_(int);
float __cdecl StopwatchElapsed(void* stopwatch);
unsigned int __cdecl ReadCounter(void* out);

namespace EA { namespace Thread {
struct Mutex {
    void Lock(const char* name);   // @ 0x9221b0
    void Unlock();                 // @ 0x922270
};
}}

namespace SP {

// ---------------------------------------------------------------- shared types
struct cILayer {                       // reference-counted interface
    virtual void AddRef();             // +0x0
    virtual void Release();            // +0x4
};

struct cLayerInfo {                    // size 0x14
    cILayer*     mLayer;               // +0x0
    unsigned int mLayerNumber;         // +0x4
    unsigned int mLayerFlags;          // +0x8
    unsigned int mInfoFlags;           // +0xc
    float        mTimeMS;              // +0x10
    void operator=(const cLayerInfo& o);   // @ 0x75ed50
    cLayerInfo(const cLayerInfo& o);       // @ 0x75ee90
    cLayerInfo() {}
};

struct LayerVector {                   // `this` points at mpBegin
    cLayerInfo* mpBegin;               // +0x0
    cLayerInfo* mpEnd;                 // +0x4
    cLayerInfo* mpCapacity;            // +0x8
    void erase(cLayerInfo* first, cLayerInfo* last);                  // @ 0x75fc00
    void DoInsertValue(cLayerInfo* position, const cLayerInfo& value);// @ 0x75fc70
    cLayerInfo* insert(cLayerInfo* position, const cLayerInfo& value);// @ 0x760030
};

void __cdecl copy_layers(cLayerInfo* first, cLayerInfo* last, cLayerInfo* dest); // @ 0x75f4a0

struct MutexLock {
    EA::Thread::Mutex* mMutex;
    MutexLock(EA::Thread::Mutex* m) : mMutex(m) { mMutex->Lock("Renderer"); }
    ~MutexLock() { mMutex->Unlock(); }
};

class cRenderer {
public:
    char mData[0x648];

    bool ClearLayer(unsigned int layerNumber);             // @ 0x75ff50
    bool Shutdown();                                       // @ 0x7600d0
    void SetLayer(cILayer* layer, unsigned int layerNumber, unsigned int flags); // @ 0x7602a0
    void ClearAllLayers();                                  // @ 0x7603e0
    void Render(unsigned int flags);                        // @ 0x760450
};

// @ 0x760030
cLayerInfo* LayerVector::insert(cLayerInfo* position, const cLayerInfo& value)
{
    int idx = (int)(position - mpBegin);
    if (position == mpEnd && mpEnd != mpCapacity) {
        mpEnd = mpEnd + 1;
        if (position)
            new (position) cLayerInfo(value);
    } else {
        DoInsertValue(position, value);
    }
    return mpBegin + idx;
}

// --------------------------------------------------------------------- 0x760ac0
struct AcInner {
    void AcMethod(int v);              // thiscall, @ 0x7c3c50
};

void __stdcall sub_760ac0(void* a, void* b, AcInner** c, void* d)
{
    (*c)->AcMethod(7);
}

// --------------------------------------------------------------- render list 0x760ad0
struct IJob {
    virtual void j0();
    virtual void j1();
    virtual void j2();
    virtual void Run(void* p2, void* p1, void* a2, void* a3);
};
struct JobEntry { IJob* p0; void* p1; void* p2; };
struct JobList {
    char pad[0xc];
    JobEntry* mpBegin;                 // +0xc
    JobEntry* mpEnd;                   // +0x10
    void Dispatch(void* a0, void* a1, void* a2, void* a3);   // @ 0x760ad0
};

void JobList::Dispatch(void* a0, void* a1, void* a2, void* a3)
{
    JobEntry* it = mpBegin;
    if (it != mpEnd) {
        do {
            it->p0->Run(it->p2, it->p1, a2, a3);
            it++;
        } while (it != mpEnd);
    }
}

// ------------------------------------------------------------- ref triple (0x760b50)
struct RefObj {
    virtual void AddRef();             // +0x0
    virtual void Release();            // +0x4
};
struct RefTriple {
    RefObj* p;                         // +0x0
    int     a;                         // +0x4
    int     b;                         // +0x8
    RefTriple* operator=(const RefTriple& o);   // @ 0x760b50
};

RefTriple* RefTriple::operator=(const RefTriple& o)
{
    RefObj* old = p;
    RefObj* src = o.p;
    if (src != old) {
        if (src) src->AddRef();
        p = src;
        if (old) old->Release();
    }
    a = o.a;
    b = o.b;
    return this;
}

// @ 0x760ba0
RefTriple* copy_triples(RefTriple* first, RefTriple* last, RefTriple* dest)
{
    for (; first != last; first++, dest++) {
        RefObj* s = first->p;
        RefObj* d = dest->p;
        if (s != d) {
            if (s) s->AddRef();
            dest->p = s;
            if (d) d->Release();
        }
        dest->a = first->a;
        dest->b = first->b;
    }
    return dest;
}

// --------------------------------------------------------------- 0x760c00 (ctor)
struct Base2 {
    virtual void b0();
    int x, y, z, w;
    Base2() : x(0), y(0), z(0), w(0) {}
};
struct Base1 {
    virtual void a0();
};
struct Poly2 : Base1, Base2 {
    Poly2();
};
Poly2::Poly2() {}

// ---------------------------------------------------------------- 0x760c40 (erase)
struct RefCountedAt8 {
    virtual void r0();
    int r1;
    int mRefCount;                     // +0x8
    void AddRef();
    void Release();
};
struct Elem3 {
    RefCountedAt8* p;                  // +0x0
    void* a;                           // +0x4
    void* b;                           // +0x8
};
void __cdecl move_elems(Elem3* dest, Elem3* last, Elem3* src);    // @ 0x6f43e0
Elem3* __cdecl move_elems2(Elem3* dest, Elem3* last, Elem3* src);  // @ 0x77fb10
void __cdecl destroy_range(Elem3* first, Elem3* last);            // @ 0x760b10
void __cdecl uninit_move(Elem3* first, Elem3* last, Elem3* dest); // @ 0x780a50
void __cdecl move_ptrs(RefCountedAt8** dest, RefCountedAt8** last, RefCountedAt8** src); // @ 0x6f43e0

struct PtrVec {
    RefCountedAt8** mpBegin;           // +0x0
    RefCountedAt8** mpEnd;             // +0x4
    RefCountedAt8** mpCapacity;        // +0x8
    RefCountedAt8** erase(RefCountedAt8** position);   // @ 0x760c40
};

struct Vec3 {
    Elem3* mpBegin;                    // +0x0
    Elem3* mpEnd;                      // +0x4
    Elem3* mpCapacity;                 // +0x8
    Elem3* insert(Elem3* position, const Elem3& value); // @ 0x760ca0
};

RefCountedAt8** PtrVec::erase(RefCountedAt8** position)
{
    if (position + 1 < mpEnd)
        move_ptrs(position + 1, mpEnd, position);
    mpEnd = mpEnd - 1;
    RefCountedAt8* p = *mpEnd;
    if (p) {
        volatile long* rc = (volatile long*)((char*)p + 8);
        _InterlockedExchangeAdd(rc, -1);
        if (_InterlockedExchangeAdd(rc, 0) < 1) {
            _InterlockedExchangeAdd(rc, 1);
            return position;
        }
    }
    return position;
}

Elem3* Vec3::insert(Elem3* position, const Elem3& value)
{
    if (mpEnd != mpCapacity) {
        Elem3* end = mpEnd;
        if (position < end) {
            Elem3* p = end;
            while (p != position) {
                Elem3* prev = p - 1;
                p->p = prev->p;
                if (p->p) p->p->AddRef();
                p->a = prev->a;
                p->b = prev->b;
                p = prev;
            }
        }
        *position = value;
        if (position->p) position->p->AddRef();
        mpEnd = end + 1;
        return position;
    }
    int count = (int)(mpEnd - mpBegin);
    int cap = (count == 0) ? 1 : count * 2;
    Elem3* newBuf = cap ? (Elem3*)operator_new(cap * 0xc, 0, "Graphics") : 0;
    Elem3* newPos = move_elems2(newBuf, position, 0);
    destroy_range(newBuf, position);
    if (newPos) { *newPos = value; if (newPos->p) newPos->p->AddRef(); }
    Elem3* newEnd = move_elems2(position, mpEnd, newPos + 1);
    destroy_range(position, mpEnd);
    if (mpBegin && *(int*)((char*)mpBegin - 4) != 0) operator_delete_(mpBegin);
    mpEnd = newEnd;
    mpBegin = newBuf;
    mpCapacity = newBuf + cap;
    return newPos;
}

// ============================================================== cRenderer methods
// @ 0x75ff50
bool cRenderer::ClearLayer(unsigned int layerNumber)
{
    char* self = (char*)this;
    EA::Thread::Mutex* m = (EA::Thread::Mutex*)(self + 0x28);
    MutexLock lock(m);
    LayerVector* v = (LayerVector*)(self + 0x8c);
    cLayerInfo* it = v->mpBegin;
    cLayerInfo* last = v->mpEnd;
    unsigned int n = layerNumber;
    while (it != last) {
        if (n <= it->mLayerNumber) break;
        it = (cLayerInfo*)((char*)it + 0x14);
    }
    if (it != last && n == it->mLayerNumber) {
        if ((char*)(it + 1) < (char*)v->mpEnd)
            copy_layers(it + 1, v->mpEnd, it);
        v->mpEnd = (cLayerInfo*)((char*)v->mpEnd - 0x14);
        cLayerInfo* e = v->mpEnd;
        if (e->mLayer) e->mLayer->Release();
        return true;
    }
    return false;
}

// @ 0x7600d0
bool cRenderer::Shutdown()
{
    char* self = (char*)this;
    if (!*(char*)(self + 0xc)) return false;
    EA::Thread::Mutex* m = (EA::Thread::Mutex*)(self + 0x28);
    *(char*)(self + 0xc) = 0;
    MutexLock lock(m);
    *(int*)(self + 0x7c) = 0;
    *(int*)(self + 0x80) = 0;
    *(int*)(self + 0x84) = 0;
    *(int*)(self + 0x88) = 0;
    LayerVector* v = (LayerVector*)(self + 0x8c);
    v->erase(v->mpBegin, v->mpEnd);
    *(int*)(self + 0x33c) = 0;
    *(int*)(self + 0x340) = 0;
    *(int*)(self + 0x344) = 0;
    *(int*)(self + 0x348) = 0;
    LayerVector* v2 = (LayerVector*)(self + 0x34c);
    v2->erase(v2->mpBegin, v2->mpEnd);
    ClearJobList(self + 0x330);
    ClearJobList(self + 0x324);
    if (*(char*)(self + 0xd)) {
        DevStop1();
        if (*(char*)(self + 0xd)) {
            DevStop2();
            *(char*)(self + 0xd) = 0;
            DevStop3();
        }
    }
    if (*(int*)(self + 0x20)) {
        CloseArena();
        *(int*)(self + 0x20) = 0;
    }
    *(int*)(self + 0x58) = 0;
    timeEndPeriod_(1);
    return true;
}

// @ 0x7602a0
void cRenderer::SetLayer(cILayer* layer, unsigned int layerNumber, unsigned int flags)
{
    char* self = (char*)this;
    EA::Thread::Mutex* m = (EA::Thread::Mutex*)(self + 0x28);
    MutexLock lock(m);
    LayerVector* v = (LayerVector*)(self + 0x8c);
    cLayerInfo* it = v->mpBegin;
    cLayerInfo* last = v->mpEnd;
    cLayerInfo* found = 0;
    while (it != last) {
        if (layerNumber <= it->mLayerNumber) break;
        it = (cLayerInfo*)((char*)it + 0x14);
    }
    if (it != last && layerNumber == it->mLayerNumber)
        found = it;
    cLayerInfo info;
    info.mLayer = layer;
    if (layer) layer->AddRef();
    info.mLayerNumber = layerNumber;
    info.mLayerFlags = flags;
    info.mInfoFlags = 1;
    info.mTimeMS = 0.0f;
    if (found)
        found->operator=(info);
    else
        v->insert(it, info);
    if (info.mLayer) info.mLayer->Release();
}

// @ 0x7603e0
void cRenderer::ClearAllLayers()
{
    char* self = (char*)this;
    EA::Thread::Mutex* m = (EA::Thread::Mutex*)(self + 0x28);
    MutexLock lock(m);
    LayerVector* v = (LayerVector*)(self + 0x8c);
    v->erase(v->mpBegin, v->mpEnd);
}

// @ 0x760450 : SP::cRenderer::Render
void cRenderer::Render(unsigned int flags)
{
    char* self = (char*)this;
    if (*(char*)(self + 0x6c) && SP_Canvas()) {
        void* c = SP_Canvas();
        char* vt = *(char**)c;
        if (!(*(bool(__thiscall**)(void*))(vt + 0x44))(c))
            return;
    }
    char listA[8]; *(void**)(listA + 0) = listA; *(void**)(listA + 4) = listA;
    char listB[8]; *(void**)(listB + 0) = listB; *(void**)(listB + 4) = listB;
    EA::Thread::Mutex* m = (EA::Thread::Mutex*)(self + 0x28);
    m->Lock("Renderer");
    if (!*(int*)(self + 0x7c)) {
        m->Unlock();
        ClearJobList(listB);
        ClearJobList(listA);
        return;
    }
    *(int*)(self + 0x33c) = *(int*)(self + 0x7c);
    *(int*)(self + 0x340) = *(int*)(self + 0x80);
    *(int*)(self + 0x344) = *(int*)(self + 0x84);
    *(int*)(self + 0x348) = *(int*)(self + 0x88);
    LayerVector* v = (LayerVector*)(self + 0x8c);
    LayerVector* fv = (LayerVector*)(self + 0x34c);
    if (fv != v) {
        fv->erase(fv->mpBegin, fv->mpEnd);
        for (cLayerInfo* p = v->mpBegin; p != v->mpEnd; p = (cLayerInfo*)((char*)p + 0x14))
            fv->insert(fv->mpEnd, *p);
    }
    int budget = *(int*)(self + 0x10);
    m->Unlock();
    if ((*(bool(__thiscall**)(void*))(*(char**)SP_AppSystem() + 0x44))(SP_AppSystem())) {
        if (budget < *(int*)(self + 0x14) * 3)
            budget = *(int*)(self + 0x14) * 3;
    }
    bool b = false;
    float f[5] = {0, 0, 0, 0, 0};
    if (*(char*)(self + 0x1b)) { DevStop1(); *(char*)(self + 0x1b) = 0; }
    DevStop2();
    if ((*(bool(__thiscall**)(void*))(*(char**)self + 0x88))(self)) {
        ResetGlobalState();
        operator_new(0x40, 0, "a"); operator_new(0x57, 0, "b"); operator_new(0x40, 0, "c");
        for (int done = 0; done < budget; ) {
            JobEntry* e = *(JobEntry**)listA;
            if (e == (JobEntry*)listA) break;
            (*(void(__thiscall**)(void*, float*))(*(char**)e->p1 + 0x10))(e->p1, f);
            done += (int)e->p2;
            break;
        }
        ResetGlobalState();
        operator_new(0x40, 0, "a"); operator_new(0x57, 0, "b"); operator_new(0x40, 0, "c");
        unsigned int mask = b ? 0x10001 : 0x10005;
        unsigned int want = b ? 1 : 5;
        cLayerInfo* last = v->mpEnd;
        cLayerInfo* sel = v->mpBegin;
        for (cLayerInfo* p = v->mpBegin; p != last; p = (cLayerInfo*)((char*)p + 0x14))
            if (p->mInfoFlags & 2) sel = p;
        if (sel != last) {
            cLayerInfo* p = sel;
            do {
                if ((p->mInfoFlags & mask) == want) {
                    unsigned int id = p->mLayerNumber;
                    *(unsigned int*)(self + 0x654) = id;
                    ResetGlobalState();
                    if (p->mLayer)
                        (*(void(__thiscall**)(void*, unsigned int, void*, void*))
                            (*(char**)p->mLayer + 0xc))(p->mLayer, p->mLayerFlags | flags,
                                                        (void*)(self + 0x33c), f);
                }
                p->mInfoFlags &= 0xfffeffff;
                p = (cLayerInfo*)((char*)p + 0x14);
            } while (p != last);
        }
        ResetGlobalState();
        operator_new(0x40, 0, "a"); operator_new(0x57, 0, "b"); operator_new(0x40, 0, "c");
        (*(void(__thiscall**)(void*))(*(char**)self + 0x8c))(self);
        *(char*)(self + 0x18) = 0;
    }
    float elapsed = StopwatchElapsed(self + 0x5e8);
    *(float*)(self + 0x600) = elapsed * *(float*)(self + 0x5e8);
    *(float*)(self + 0x604) = *(float*)(self + 0x604) * 0.9f +
                              (elapsed * *(float*)(self + 0x5e8)) * 0.1f;
    if (*(int*)(self + 0x5f0) == 1) {
        unsigned int t[2];
        ReadCounter(t);
        *(unsigned int*)(self + 0x5e8) = t[0];
        *(unsigned int*)(self + 0x5ec) = t[1];
    } else {
        unsigned int t[2];
        ReadCounter(t);
        *(unsigned int*)(self + 0x5e8) = t[0];
        *(unsigned int*)(self + 0x5ec) = t[1];
    }
    *(int*)(self + 0x5f0) = 0;
    *(int*)(self + 0x5f4) = 0;
    m->Lock("Renderer");
    m->Unlock();
}

} // namespace SP
