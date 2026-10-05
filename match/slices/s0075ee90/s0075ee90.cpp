// Slice s0075ee90: EASTL container helpers for SP::cRenderer render-job lists and
// cLayerInfoExtra. /O2, SSE (/arch:SSE2). Large list/vector constructors are partial.
#include "types.h"

struct RNode {
    virtual void AddRef();    // vtable slot 0
    virtual void Release();   // vtable slot 1
};

struct Elem {          // 0x14 bytes
    RNode* p;          // +0x00
    int    b;          // +0x04
    int    c;          // +0x08
    int    d;          // +0x0c
    float  f;          // +0x10
};

// @ 0x0075ee90
Elem* CopyElem(Elem* dst, Elem* src)
{
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

extern "C" void* EASTL_allocator_allocate(unsigned n, const char* name, int a, int b,
                                           const char* file, int line);   // @ 0x00f473a0
extern "C" void EASTL_deallocate(void* p);   // @ 0x00f47380
extern void ConstructElemArray(void* a, void* b, void* c, void* d, unsigned n); // @ 0x0075ef80

// @ 0x0075f770
void* AllocElemArray(unsigned count, void* dst, void* src)
{
    void* mem;
    if (count == 0)
        mem = 0;
    else
        mem = EASTL_allocator_allocate(count * 0x14, "Graphics", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
    ConstructElemArray(&count, dst, src, mem, count);
    return mem;
}

struct RenderJob {
    RenderJob* next;   // +0x00
    RenderJob* prev;   // +0x04
    RNode*     obj;    // +0x08
    int        pad;    // +0x0c
    float      id;     // +0x10
};

// @ 0x0075f8a0  (SP::cRenderer::RemovePostRenderJob)
bool RemovePostRenderJob(void* self, float id)
{
    char* sentinel = (char*)self + 0x324;
    RenderJob* n = *(RenderJob**)((char*)self + 0x324);
    if (n == (RenderJob*)sentinel)
        return false;
    while (n->id != id) {
        n = n->next;
        if (n == (RenderJob*)sentinel)
            return false;
    }
    n->prev->next = n->next;
    n->next->prev = n->prev;
    if (n->obj != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)n->obj + 4))(n->obj);
    EASTL_deallocate(n);
    return true;
}

// @ 0x0075f900  (SP::cRenderer::RemovePreRenderJob)
bool RemovePreRenderJob(void* self, float id)
{
    char* sentinel = (char*)self + 0x330;
    RenderJob* n = *(RenderJob**)((char*)self + 0x330);
    if (n == (RenderJob*)sentinel)
        return false;
    while (n->id != id) {
        n = n->next;
        if (n == (RenderJob*)sentinel)
            return false;
    }
    n->prev->next = n->next;
    n->next->prev = n->prev;
    if (n->obj != 0)
        ((void (__thiscall*)(void*))*(void**)(*(int*)n->obj + 4))(n->obj);
    EASTL_deallocate(n);
    return true;
}

// ---------------------------------------------------------------- partial placeholders
// @ 0x0075eed0
void* CopyElemRange(void* dst, void* first, void* last)
{
    (void)first; (void)last; return dst;   // partial placeholder
}
// @ 0x0075ef80
void ConstructElemArrayImpl()
{
    // partial placeholder
}
// @ 0x0075f030
bool RegisterRenderProperties()
{
    return true;   // partial placeholder
}
// @ 0x0075f510
bool AddPostRenderJob(void* a, void* b, void* c)
{
    (void)b; (void)c; return a != 0;   // partial placeholder
}
// @ 0x0075f640
bool AddPreRenderJob(void* a, void* b, void* c)
{
    (void)b; (void)c; return a != 0;   // partial placeholder
}
// @ 0x0075f7e0
void* DestroyRenderJobList(void* self)
{
    return self;   // partial placeholder
}
// @ 0x0075f960
void* RenderJobListCtor(void* self)
{
    return self;   // partial placeholder
}
// @ 0x0075fc70
void* InsertElemN(void* self, void* pos, unsigned n, void* v)
{
    (void)pos; (void)n; (void)v; return self;   // partial placeholder
}
// @ 0x0075fe50
void* ResizeElemArray(void* self, unsigned a, unsigned b, void* c)
{
    (void)a; (void)b; (void)c; return self;   // partial placeholder
}
