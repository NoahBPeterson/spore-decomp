// Slice s0075ee90: EASTL container helpers for SP::cRenderer render-job lists and
// cLayerInfoExtra (SP::cLayerInfoExtra = the 0x14-byte Elem below).
// /O2, SSE (/arch:SSE2).
#include "types.h"

struct RNode {
    virtual void AddRef();    // vtable slot 0
    virtual void Release();   // vtable slot 1
};

struct Elem {          // 0x14 bytes (SP::cLayerInfoExtra)
    RNode* p;          // +0x00
    int    b;          // +0x04
    int    c;          // +0x08
    int    d;          // +0x0c
    float  f;          // +0x10
    Elem* Copy(Elem* src);
};

// EA::Thread::Mutex (only the 4-byte handle is ever touched here)
struct EA_Mutex {
    int mData;                 // +0x00
};

// eastl::list<SP::cRenderer::cRenderJob> sentinel (intrusive, next/prev at +0/+4)
struct JobList {
    void* mpNext;              // +0x00
    void* mpPrev;              // +0x04
    int   mField08;            // +0x08
};

// SP::cRenderer render-job linked-list node
struct RenderJob {
    RenderJob* mpNext;         // +0x00
    RenderJob* mpPrev;         // +0x04
    RNode*     mpObject;       // +0x08
    int        mField0c;       // +0x0c
    float      mJobId;         // +0x10
};

// SP::cRenderer.  Only the fields this slice touches are named; everything else is padN.
struct cRenderer {
    void*    mVtbl0;           // +0x00
    void*    mVtbl1;           // +0x04
    char     pad08[0x28 - 0x08];
    EA_Mutex mMutex;           // +0x28
    char     pad2c[0x8c - 0x2c];
    void*    mpNodesA;         // +0x8c  (render-node array)
    char     pad90[0x324 - 0x90];
    JobList  mPostJobs;        // +0x324
    JobList  mPreJobs;         // +0x330
    char     pad33c[0x34c - 0x33c];
    void*    mpNodesB;         // +0x34c (render-node array)
    char     pad350[0x63c - 0x350];
    void*    mpShaderDebug;    // +0x63c
    bool RemovePostRenderJob(float id);
    bool RemovePreRenderJob(float id);
};

// eastl::vector<SP::cLayerInfoExtra> (fixed_vector_allocator carries an inline buffer)
struct ElemVec {
    Elem* mpBegin;             // +0x00
    Elem* mpEnd;               // +0x04
    Elem* mpCapacity;          // +0x08
    int   mField0c;            // +0x0c
    Elem* mpInlineBuffer;      // +0x10
};

// ---------------------------------------------------------------- external helpers / data
extern "C" void* EASTL_allocator_allocate(unsigned n, const char* name, int a, int b,
                                          const char* file, int line);       // @ 0x00f473a0
extern "C" void  EASTL_deallocate(void* p);                                  // @ 0x00f47380
extern void  DestroyElemRange(void* first, void* last);                      // @ 0x0075e6a0
extern void  RelocateElemRange(void* first, void* last, void* mem);          // @ 0x0075e7f0
extern void  CopyRenderNode(void* dst, void* src);                           // @ 0x0075ed50
extern void  FreeRenderNodeArray(void* p);                                   // @ 0x0075eda0
extern void* MakeRenderSubObject(void* list, void* job);                     // @ 0x0075e750
extern void  RenderJobListErase(void* list);                                 // @ 0x0075f3f0
extern void  EAMutexLock(void* m, unsigned int pTimeoutMS);                  // @ 0x009221b0
extern void  EAMutexUnlock(void* m);                                         // @ 0x00922270
extern void  EAMutexDtor(void* m);                                           // @ 0x00922130
extern int   sRenderJobId;                                                   // @ 0x0162fc64
extern const unsigned int g_mutexInfiniteWait;                               // @ 0x0140dca0
extern char  g_vtbl_cRenderer;                                               // @ 0x0140dce8
extern char  g_vtbl_cRenderer1;                                              // @ 0x0140dce4
extern char  g_vtbl_dtorBase0;                                               // @ 0x013eb938
extern char  g_vtbl_dtorBase1;                                               // @ 0x013ef094

// The EASTL allocator source path baked into the originals.
static const char kAllocatorH[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// @ 0x0075ee90
Elem* Elem::Copy(Elem* src)
{
    Elem* dst = this;
    RNode* p = src->p;
    dst->p = p;
    if (p != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)p))(p);
    dst->b = src->b;
    dst->c = src->c;
    dst->d = src->d;
    dst->f = src->f;
    return dst;
}

// @ 0x0075eed0  (SP::CopyElemRange: uninitialized copy of a 0x14-byte element range)
void* CopyElemRange(void* first, void* last, void* dst)
{
    Elem* f = (Elem*)first;
    Elem* l = (Elem*)last;
    Elem* d = (Elem*)dst;
    while (f != l) {
        if (d != 0) {
            RNode* p = f->p;
            d->p = p;
            if (p != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)p))(p);
            d->b = f->b;
            d->c = f->c;
            d->d = f->d;
            d->f = f->f;
        }
        f++;
        d++;
    }
    return d;
}

// @ 0x0075ef80  (construct a range into an array whose write cursor is *pDst)
void* ConstructElemArrayImpl(void* pDst, void* first, void* last, void* mem)
{
    Elem** pd = (Elem**)pDst;
    Elem* f = (Elem*)first;
    Elem* l = (Elem*)last;
    *pd = (Elem*)mem;
    while (f != l) {
        Elem* d = *pd;
        if (d != 0) {
            RNode* p = f->p;
            d->p = p;
            if (p != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)p))(p);
            d->b = f->b;
            d->c = f->c;
            d->d = f->d;
            d->f = f->f;
        }
        *pd = (Elem*)((char*)*pd + 0x14);
        f++;
    }
    return pd;
}

// @ 0x0075f430  (copy_backward, EASTL uninitialized/relocate flavour)
Elem* CopyBackward(Elem* first, Elem* last, Elem* dest)
{
    if (last == first)
        return dest;
    do {
        last--;
        dest--;
        RNode* np = last->p;
        RNode* dp = dest->p;
        if (np != dp) {
            if (np != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)np))(np);
            dest->p = np;
            if (dp != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)dp + 4))(dp);
        }
        dest->b = last->b;
        dest->c = last->c;
        dest->d = last->d;
        dest->f = last->f;
    } while (last != first);
    return dest;
}

// @ 0x0075f4a0  (copy forward)
Elem* CopyForward(Elem* first, Elem* last, Elem* dest)
{
    if (first == last)
        return dest;
    do {
        RNode* np = first->p;
        RNode* dp = dest->p;
        if (np != dp) {
            if (np != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)np))(np);
            dest->p = np;
            if (dp != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)dp + 4))(dp);
        }
        dest->b = first->b;
        dest->c = first->c;
        dest->d = first->d;
        dest->f = first->f;
        first++;
        dest++;
    } while (first != last);
    return dest;
}

// @ 0x0075f510  (SP::cRenderer::AddPostRenderJob: build a render job, link it under the lock)
unsigned int AddPostRenderJob(void* self_, void* layer_, int a3, void* info_)
{
    cRenderer* self = (cRenderer*)self_;

    char job[0x38];
    int* jd = (int*)job;
    for (int i = 0; i < 0x38 / 4; ++i)
        jd[i] = 0;

    if (layer_ != 0) {
        ((void (__thiscall*)(void*))*(void**)(*(int*)layer_))(layer_);   // AddRef
        jd[0] = (int)layer_;
    }
    jd[1] = a3;
    jd[2] = sRenderJobId++;
    for (int i = 0; i < 0xb; ++i)
        jd[3 + i] = ((int*)info_)[i];

    EAMutexLock(&self->mMutex, (unsigned int)&g_mutexInfiniteWait);
    RenderJob* node = (RenderJob*)MakeRenderSubObject(&self->mPostJobs, job);
    node->mpNext = (RenderJob*)&self->mPostJobs;
    node->mpPrev = (RenderJob*)self->mPostJobs.mpPrev;
    ((RenderJob*)self->mPostJobs.mpPrev)->mpNext = node;
    self->mPostJobs.mpPrev = node;
    EAMutexUnlock(&self->mMutex);

    if (jd[0] != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)jd[0] + 4))((void*)jd[0]);   // Release
    return (unsigned int)jd[2];
}

// @ 0x0075f640  (SP::cRenderer::AddPreRenderJob: same, queued on the pre-render list)
unsigned int AddPreRenderJob(void* self_, void* layer_, int a3, void* info_)
{
    cRenderer* self = (cRenderer*)self_;

    char job[0x38];
    int* jd = (int*)job;
    for (int i = 0; i < 0x38 / 4; ++i)
        jd[i] = 0;

    if (layer_ != 0) {
        ((void (__thiscall*)(void*))*(void**)(*(int*)layer_))(layer_);   // AddRef
        jd[0] = (int)layer_;
    }
    jd[1] = a3;
    jd[2] = sRenderJobId++;
    for (int i = 0; i < 0xb; ++i)
        jd[3 + i] = ((int*)info_)[i];

    EAMutexLock(&self->mMutex, (unsigned int)&g_mutexInfiniteWait);
    RenderJob* node = (RenderJob*)MakeRenderSubObject(&self->mPreJobs, job);
    node->mpNext = (RenderJob*)&self->mPreJobs;
    node->mpPrev = (RenderJob*)self->mPreJobs.mpPrev;
    ((RenderJob*)self->mPreJobs.mpPrev)->mpNext = node;
    self->mPreJobs.mpPrev = node;
    EAMutexUnlock(&self->mMutex);

    if (jd[0] != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)jd[0] + 4))((void*)jd[0]);   // Release
    return (unsigned int)jd[2];
}

// @ 0x0075f770
void* AllocElemArray(unsigned count, void* dst, void* src)
{
    void* mem;
    if (count == 0)
        mem = 0;
    else
        mem = EASTL_allocator_allocate(count * 0x14, "Graphics", 0, 0, kAllocatorH, 0xd1);
    ConstructElemArrayImpl(&count, dst, src, mem);
    return mem;
}

// @ 0x0075f7e0  (SP::cRenderer::~cRenderer: tear the render-job lists and owned nodes down)
void* DestroyRenderJobList(void* self_)
{
    cRenderer* self = (cRenderer*)self_;
    self->mVtbl0 = &g_vtbl_cRenderer;
    self->mVtbl1 = &g_vtbl_cRenderer1;
    if (self->mpShaderDebug != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)self->mpShaderDebug + 4))(self->mpShaderDebug);
    FreeRenderNodeArray(self->mpNodesB);
    RenderJobListErase(&self->mPreJobs);
    RenderJobListErase(&self->mPostJobs);
    FreeRenderNodeArray(self->mpNodesA);
    EAMutexDtor(&self->mMutex);
    self->mVtbl1 = &g_vtbl_dtorBase1;
    self->mVtbl0 = &g_vtbl_dtorBase0;
    return self;
}

// @ 0x0075f8a0  (SP::cRenderer::RemovePostRenderJob)
bool cRenderer::RemovePostRenderJob(float id)
{
    void* self = this;
    char* sentinel = (char*)self + 0x324;
    RenderJob* n = *(RenderJob**)((char*)self + 0x324);
    if (n == (RenderJob*)sentinel)
        return false;
    while (n->mJobId != id) {
        n = n->mpNext;
        if (n == (RenderJob*)sentinel)
            return false;
    }
    n->mpPrev->mpNext = n->mpNext;
    n->mpNext->mpPrev = n->mpPrev;
    if (n->mpObject != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)n->mpObject + 4))(n->mpObject);
    EASTL_deallocate(n);
    return true;
}

// @ 0x0075f900  (SP::cRenderer::RemovePreRenderJob)
bool cRenderer::RemovePreRenderJob(float id)
{
    void* self = this;
    char* sentinel = (char*)self + 0x330;
    RenderJob* n = *(RenderJob**)((char*)self + 0x330);
    if (n == (RenderJob*)sentinel)
        return false;
    while (n->mJobId != id) {
        n = n->mpNext;
        if (n == (RenderJob*)sentinel)
            return false;
    }
    n->mpPrev->mpNext = n->mpNext;
    n->mpNext->mpPrev = n->mpPrev;
    if (n->mpObject != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)n->mpObject + 4))(n->mpObject);
    EASTL_deallocate(n);
    return true;
}

// @ 0x0075fc70  (eastl::vector<cLayerInfoExtra>::insert(pos, value))
void* InsertElemN(void* self_, void* pos_, void* value_)
{
    ElemVec* v = (ElemVec*)self_;
    Elem* pos = (Elem*)pos_;
    Elem* value = (Elem*)value_;
    Elem* end = v->mpEnd;

    if (end != v->mpCapacity) {
        if (pos <= value && value < end)
            value++;
        if (end != 0) {
            RNode* p = end[-1].p;
            end->p = p;
            if (p != 0)
                ((void (__thiscall*)(void*))*(void**)(*(int*)p))(p);
            end->b = end[-1].b;
            end->c = end[-1].c;
            end->d = end[-1].d;
            end->f = end[-1].f;
        }
        CopyBackward(pos, end - 1, end);
        CopyRenderNode(pos, value);
        v->mpEnd = end + 1;
        return self_;
    }

    unsigned off = (unsigned)(((char*)end - (char*)v->mpBegin) / 0x14);
    unsigned newCap = off ? off * 2 : 1;
    Elem* newData = 0;
    if (newCap != 0)
        newData = (Elem*)EASTL_allocator_allocate(newCap * 0x14, "Graphics", 0, 0, kAllocatorH, 0xd1);

    Elem* p = (Elem*)CopyElemRange(v->mpBegin, pos, newData);
    RelocateElemRange(v->mpBegin, pos, newData);
    if (p != 0) {
        RNode* q = value->p;
        p->p = q;
        if (q != 0)
            ((void (__thiscall*)(void*))*(void**)(*(int*)q))(q);
        p->b = value->b;
        p->c = value->c;
        p->d = value->d;
        p->f = value->f;
    }

    Elem* last = v->mpEnd;
    Elem* newEnd = (Elem*)CopyElemRange(pos, last, p + 1);
    RelocateElemRange(pos, last, p + 1);

    if (v->mpBegin != 0 && v->mpBegin != v->mpInlineBuffer)
        EASTL_deallocate(v->mpBegin);

    v->mpEnd = newEnd;
    v->mpBegin = newData;
    v->mpCapacity = (Elem*)((char*)newData + newCap * 0x14);
    return self_;
}

// @ 0x0075fe50  (eastl::vector<cLayerInfoExtra>::DoAssignFromIterator(first, last))
void* ResizeElemArray(void* self_, void* first_, void* last_)
{
    ElemVec* v = (ElemVec*)self_;
    Elem* first = (Elem*)first_;
    Elem* last = (Elem*)last_;
    Elem* begin = v->mpBegin;
    unsigned n = (unsigned)(((char*)last - (char*)first) / 0x14);

    if ((unsigned)(((char*)v->mpCapacity - (char*)begin) / 0x14) < n) {
        Elem* newData = (Elem*)AllocElemArray(n, first, last);
        DestroyElemRange(v->mpBegin, v->mpEnd);
        if (v->mpBegin != 0 && v->mpBegin != v->mpInlineBuffer)
            EASTL_deallocate(v->mpBegin);
        Elem* newEnd = (Elem*)((char*)newData + n * 0x14);
        v->mpBegin = newData;
        v->mpEnd = newEnd;
        v->mpCapacity = newEnd;
        return self_;
    }

    unsigned have = (unsigned)(((char*)v->mpEnd - (char*)begin) / 0x14);
    if (n <= have) {
        Elem* r = CopyForward(first, last, begin);
        DestroyElemRange(r, v->mpEnd);
        v->mpEnd = r;
        return self_;
    }

    Elem* mid = (Elem*)((char*)first + have * 0x14);
    CopyForward(first, mid, begin);
    ConstructElemArrayImpl(&last, mid, last, v->mpEnd);
    v->mpEnd = last;
    return self_;
}

// ---------------------------------------------------------------- not yet reconstructed
// @ 0x0075f030
bool RegisterRenderProperties()
{
    return true;   // partial placeholder
}
// @ 0x0075f960
void* RenderJobListCtor(void* self)
{
    return self;   // partial placeholder
}