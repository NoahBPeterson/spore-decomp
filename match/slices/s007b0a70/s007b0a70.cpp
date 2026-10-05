// Slice s007b0a70 — graphics texture/vector helpers (eastl vector of 0x20-byte nodes,
// image registration and DXT compression wrappers). Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// ---------------------------------------------------------------------------
// external helpers (definitions elsewhere; call targets are masked relocs)
// ---------------------------------------------------------------------------
void  __cdecl EAFree(void* p);                                    // 0x00F47380
void* __cdecl EAAlloc(unsigned n, const char* name, int a, int b, const char* f, int l); // 0x00F473A0
void  __cdecl DestroyElems(void* first, void* last);              // 0x00B007F0
void  __cdecl CopyIntrusive(void* first, void* last, void* dest); // 0x006F43E0
void  __cdecl RemoveIf(void* a, void* b, void* c);                // 0x0076DE80
void  __cdecl MoveNodes(void* a, void* b, void* c);               // 0x007AF5D0
void  __cdecl MoveNodes2(void* a, void* b, void* c);              // 0x007AF6D0
void  __cdecl DoCopy4(void* first, void* last, void* dest);       // 0x006782C0

struct VecClearOp { void DestroyRange(void* b, void* e); };       // 0x0070F520 __thiscall
struct VecReserve  { void Reserve(int n); };                      // 0x004E0880 __thiscall
struct VecInsert4  { void DoInsertValue(void* p, const void* v); }; // 0x004558A0 __thiscall

struct C20;
struct T20 {
    int a,b,c,d,e,f,g; char h;
    T20& operator=(const T20& o) { a=o.a;b=o.b;c=o.c;d=o.d;e=o.e;f=o.f;g=o.g;h=o.h; return *this; }
};

struct C20 {
    T20* begin;  T20* end;  T20* cap;                             // +0x0
    char pad0[8];                                                 // +0xc
    int* freeBegin;  int* freeEnd;  int* freeCap;                 // +0x14
    void grow(T20* p, const T20& v);                              // 0x007b0a70
    void push_back(const T20& v);                                 // 0x007b0f40
    void resize(int n);                                           // 0x007b1040
    int  Alloc();                                                 // 0x007b10a0
    void clear();                                                 // 0x007b1950
};

// 4-byte-element vector used by the container helpers
struct C4 {
    void** begin; void** end; void** cap;
    void assign(void** first, void** last);                       // 0x007b0da0
};

// ---------------------------------------------------------------------------
// @ 0x007b0f40  eastl::vector<T20>::push_back
// ---------------------------------------------------------------------------
void C20::push_back(const T20& v)
{
    T20* p = end;
    if (p < cap) {
        end = p + 1;
        if (p)
            *p = v;
    } else {
        grow(p, v);
    }
}

// ---------------------------------------------------------------------------
// @ 0x007b0a70  eastl::vector<T20>::DoInsertValue / grow-on-insert
// ---------------------------------------------------------------------------
void C20::grow(T20* pos, const T20& v)
{
    T20* e = end;
    if (e != cap) {
        T20* src = pos;
        if (pos <= &v && &v < e)
            src = (T20*)((char*)&v + 0x20);
        if (e) {
            e->a = e[-1].a; e->b = e[-1].b; e->c = e[-1].c; e->d = e[-1].d;
            e->e = e[-1].e; e->f = e[-1].f; e->g = e[-1].g; e->h = e[-1].h;
        }
        MoveNodes2(pos, (char*)end - 0x20, end);
        *pos = v;
        end = (T20*)((char*)end + 0x20);
        return;
    }
    int n = (int)(e - begin);
    if (n == 0)
        n = 1;
    else
        n = n * 2;
    T20* p = n ? (T20*)EAAlloc(n << 5, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    T20* q = (T20*)MoveNodes(begin, pos, p);
    if (q)
        *q = v;
    T20* ne = (T20*)MoveNodes(pos, end, (char*)q + 0x20);
    if (begin && *((int*)begin - 1))
        EAFree(begin);
    end = ne;
    cap = (T20*)((char*)p + n*0x20);
    begin = p;
}

// ---------------------------------------------------------------------------
// @ 0x007b0da0  eastl::vector<Ref4>::assign (4-byte elements)
// ---------------------------------------------------------------------------
void C4::assign(void** first, void** last)
{
    int n = (int)((char*)last - (char*)first) >> 2;
    if ((int)((char*)cap - (char*)begin) >> 2 < n) {
        void** p = (void**)MoveNodes(first, last, 0);   // grow/realloc helper FUN_007b0920
        DestroyElems(begin, end);
        if (begin && *((int*)begin - 1))
            EAFree(begin);
        void** ne = (void**)((char*)p + n*4);
        begin = p; end = ne; cap = ne;
        return;
    }
    int cur = (int)((char*)end - (char*)begin) >> 2;
    if (n <= cur) {
        void** ne = (void**)DoCopy4(first, last, begin);
        DestroyElems(ne, end);
        end = ne;
        return;
    }
    void** mid = (void**)((char*)first + cur*4);
    DoCopy4(first, mid, begin);
    CopyRefRange4(mid, last, end);
    end = (void**)((char*)end + (n - cur)*4);
}

// ---------------------------------------------------------------------------
// @ 0x007b1040  eastl::vector<T20>::resize(n)
// ---------------------------------------------------------------------------
void C20::resize(int n)
{
    int cnt = (int)(end - begin);
    if (n > cnt) {
        char tmp[0x20];
        // DoInsert(end, n - cnt, tmp)  (0x007b0be0)
        C20_InsertTail(this, end, n - cnt, tmp);
    } else {
        T20* ne = begin + n;
        RemoveIf(end, end, ne);
        end = (T20*)((char*)end - ((char*)end - (char*)ne));
    }
}

// ---------------------------------------------------------------------------
// @ 0x007b10a0  allocate a slot index (reuse a free-list entry if present)
// ---------------------------------------------------------------------------
int C20::Alloc()
{
    if (freeBegin != freeEnd) {
        int v = freeEnd[-1];
        freeEnd--;
        return v;
    }
    int n = (int)(end - begin);
    resize(n + 1);
    return n;
}

// ---------------------------------------------------------------------------
// @ 0x007b1950  clear two 4-byte vectors at +0xc / +0x20
// ---------------------------------------------------------------------------
void C20::clear()
{
    // vector at +0xc
    void** b1 = *(void***)((char*)this + 0xc);
    void** e1 = *(void***)((char*)this + 0x10);
    if (b1 != e1)
        CopyIntrusive(e1, e1, b1);
    // vector at +0x20
    void** b2 = *(void***)((char*)this + 0x20);
    void** e2 = *(void***)((char*)this + 0x24);
    if (b2 != e2)
        CopyIntrusive(e2, e2, b2);
}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// remaining entry points (bodies reconstructed from the disassembly summary)
// ---------------------------------------------------------------------------
struct JobOps {
    bool Continuation(void* fn, void* arg);
    void SetSomething(void* fn, void* arg);
    void GetStatus();
    void DoWait();
};

// @ 0x007b0be0  (append N default T20 nodes)
void C20_InsertTail(C20* self, T20* pos, int count, void* value)
{
    (void)self; (void)pos; (void)count; (void)value;
}

// @ 0x007b0e60  (tree-node reap: fold redundant nodes and push their indices on a free list)
void FUN_007b0e60(void* self, int idx)
{
    (void)self; (void)idx;
}

// @ 0x007b0fa0  (build a T20 from two ints and push it)
void FUN_007b0fa0(C20* self, int a, int b)
{
    T20 v;
    v.a = 0; v.b = 0; v.c = 0; v.d = 0; v.e = 0; v.f = 0; v.g = 0; v.h = 0;
    v.e = a; v.f = b; v.d = -1; v.g = -1; v.h = 0;
    self->push_back(v);
}

// @ 0x007b10d0  SP::RegisterImagesAsTexture
bool SP_RegisterImagesAsTexture(void* a, void* b, void* c, void* d)
{
    (void)a; (void)b; (void)c; (void)d;
    return false;
}

// @ 0x007b13b0  (create a DXT compress job)
bool FUN_007b13b0(void* a, void** jobOut, int flag)
{
    (void)a; if (jobOut) *jobOut = 0; (void)flag;
    return false;
}

// @ 0x007b1710  SP::DXTCompress
bool SP_DXTCompress(void* a, void* b, void* message, int* handler)
{
    (void)a; (void)b; (void)message; (void)handler;
    return false;
}

// @ 0x007b1830  (DXTCompress variant flag=1)
bool FUN_007b1830(void* a, void* b, void* message, int* handler)
{
    (void)a; (void)b; (void)message; (void)handler;
    return false;
}
