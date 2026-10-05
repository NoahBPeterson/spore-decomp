#include "types.h"
#include <wchar.h>

#define VFN(o,off) (*(void***)(o))[(off)/4]

extern "C" void FUN_0067e070(int x);   // 0x67e070
extern "C" void FUN_00883780();        // 0x883780
extern "C" void* GetManager();         // 0x67dcd0

// @ 0x00695c30
extern "C" bool __fastcall FUN_00695c30(void* self)
{
    if (*(char*)((char*)self + 8) != 0)
    {
        void* p = *(void**)((char*)self + 0x4c);
        if (p != 0)
            ((void(__thiscall*)(void*, int))VFN(p, 0))(p, 1);
        *(void**)((char*)self + 0x4c) = 0;
        FUN_0067e070(0);
        FUN_00883780();
    }
    *(char*)((char*)self + 8) = 0;
    return true;
}

// @ 0x00695c70
extern "C" int FUN_00695c70(const wchar_t* a, const wchar_t* b)
{
    int i = 0;
    if (a[0] != 0)
    {
        do
        {
            if (b[i] == 0)
                break;
            if ((wint_t)towlower(a[i]) != (wint_t)towlower(b[i]))
                break;
            ++i;
        } while (a[i] != 0);
    }
    return i;
}

// @ 0x00695cd0
extern "C" int __fastcall FUN_00695cd0(void* self)
{
    if (*(void**)((char*)self + 0x4c) != 0)
        return ((int(__thiscall*)(void*))VFN(*(void**)((char*)self + 0x4c), 0x10))
                   (*(void**)((char*)self + 0x4c));
    return 0;
}

// @ 0x00695cf0
extern "C" int FUN_00695cf0(void** p)
{
    void* o = *p;
    if (o == 0)
        return 0;
    void* t = *(void**)((char*)o + 4);
    void* self = (char*)o + 4;
    return ((int(__thiscall*)(void*, int))*(void**)((char*)t + 0xc))(self, 0x226a25b);
}

struct Ctl {
    char pad0[4];
    void* head;      // +4
    bool check(void* arg);
    void addThing(void* a, void* b);
};

// @ 0x00695d10
void Ctl::addThing(void* a, void* b)
{
    void* m = GetManager();
    bool ok = ((bool(__thiscall*)(void*, void*, void*, int, int, int, int))VFN(m, 0xc))
                  (m, a, b, 0, 0, 0, 0);
    if (!ok)
    {
        char* end = (char*)this + 0x60;
        void* n = *(void**)((char*)this + 0x60);
        while (n != end && !ok)
        {
            m = GetManager();
            ok = ((bool(__thiscall*)(void*, void*, void*, int, void*, int, int))VFN(m, 0xc))
                     (m, a, b, 0, *(void**)((char*)n + 8), 0, 0);
            n = *(void**)n;
        }
    }
}

// @ 0x00695d70
bool Ctl::check(void* arg)
{
    void* h = head;
    void* n = *(void**)h;
    if (n != h)
    {
        do
        {
            void* obj = *(void**)((char*)n + 8);
            if (((bool(__thiscall*)(void*, void*, int, int, int, int, int))VFN(obj, 0x34))
                    (obj, arg, 0, 1, 6, 1, 0))
                return true;
            n = *(void**)n;
        } while (n != head);
    }
    return false;
}

// @ 0x00695dc0
extern "C" void __fastcall FUN_00695dc0(void* self)
{
    void* n = *(void**)self;
    while (n != self)
    {
        void* cur = n;
        void* obj = *(void**)((char*)cur + 8);
        n = *(void**)n;
        if (obj != 0)
        {
            void* t = *(void**)((char*)obj + 4);
            ((void(__thiscall*)(void*))*(void**)((char*)t + 4))((char*)obj + 4);
        }
        void* mgr = *(void**)((char*)self + 8);
        ((void(__thiscall*)(void*, void*, int))VFN(mgr, 0xc))(mgr, cur, 0xc);
    }
}

// =====================================================================
// @ 0x00695450  run a (partial) sort over a 0x3c-record array
// =====================================================================
struct Elem { unsigned int m0; unsigned int mId; unsigned int m2[13]; };
extern "C" void operator_delete_arr(void* p);                       // 0xf47380
extern "C" void FUN_006950b0(Elem* first, Elem* last, bool cmp);   // 0x6950b0

struct Sorter {
    void* run(char* first);
};

void* Sorter::run(char* first)
{
    char* p = first;
    char* old;
    do
    {
        old = p;
        p += 0x3c;
        if (*(int*)(old + 0x24) == 0) break;
    } while (*(int*)(old + 0x28) != 0);
    bool flag = false;
    FUN_006950b0((Elem*)first, (Elem*)p, flag);
    return this;
}

// =====================================================================
// @ 0x00695490  reserve (vector of 0x60-byte objects)
// =====================================================================
extern "C" void* EASTL_alloc6(unsigned sz, const char* name, int a, int b, const char* file, int line); // 0xf473a0
extern "C" void  FUN_00694320(char* first, char* last, char* dst);   // 0x694320
extern "C" char* FUN_00694e00(char* first, char* last, char* out);  // 0x694e00

struct Vec60 {
    char* begin; char* end; char* cap;
    void reserve(unsigned int n);
};

void Vec60::reserve(unsigned int n)
{
    if ((unsigned)((end - begin) / 0x60) < n)
    {
        char* p;
        if (n == 0)
            p = 0;
        else
            p = (char*)EASTL_alloc6(n * 0x60, "App", 0, 0,
                     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        char* oldbegin = begin;
        char* oldend = end;
        FUN_00694320(oldbegin, oldend, p);
        FUN_00694e00(oldbegin, oldend, p);
        if (oldbegin != 0 && *(int*)(oldbegin - 4) != 0)
            operator_delete_arr(oldbegin);
        begin = p;
        end = ((end - oldbegin) / 0x60) * 0x60 + p;
        cap = n * 0x60 + p;
    }
}

// =====================================================================
// @ 0x00695e00  allocate and construct a 0xc node (EH)
// =====================================================================
extern "C" int __fastcall FUN_00695e00(void* self)
{
    void* alloc = *(void**)((char*)self + 8);
    void* arg   = *(void**)((char*)self + 0xc);
    int node = ((int(__thiscall*)(void*, int, int, void*))VFN(alloc, 8))(alloc, 0xc, 0, arg);
    int* p = (int*)(node + 8);
    if (p != 0)
    {
        int v = *(int*)arg;
        *p = v;
        if (v != 0)
            ((void(__thiscall*)(void*))*(void**)(v + 4))(p);
    }
    return node;
}

// =====================================================================
// @ 0x00695e80  destroy a content-validation summarizer object
// =====================================================================
extern "C" void* g_vtbl_a[];
extern "C" void* g_vtbl_b[];

extern "C" void __fastcall FUN_00695e80(void* self)
{
    *(void**)self = g_vtbl_a;
    FUN_00695dc0((char*)self + 0x60);
    FUN_00695dc0((char*)self + 0x50);
    char* p = *(char**)((char*)self + 0x18);
    int d = (int)(*(char**)((char*)self + 0x20) - p) & 0xfffffffe;
    if (d > 2 && p != 0 && p != *(char**)((char*)self + 0x28))
        operator_delete_arr(p);
    *(void**)self = g_vtbl_b;
}

// =====================================================================
// @ 0x00695f00  destroy the object's intrusive list + reset
// =====================================================================
extern "C" void FUN_00695f00(void* self)
{
    char* head = (char*)self + 0x60;
    while (*(void**)head != head)
    {
        char* n = *(char**)head;
        char* obj = *(char**)(n + 8);
        if (obj != 0)
        {
            void* t = *(void**)(obj + 4);
            void* fn = *(void**)((char*)t + 0xc);
            void* r = (void*)((int(__thiscall*)(void*, int))fn)(obj + 4, 0x226a25b);
            if (r != 0)
            {
                if (((int(__thiscall*)(void*))VFN(r, 0x4c))(r) != 0)
                {
                    ((void(__thiscall*)(void*))VFN(r, 0x1c))(r);
                    ((void(__thiscall*)(void*))VFN(r, 8))(r);
                }
            }
        }
        char* nn = *(char**)head;
        *(void**)(*(void**)(nn + 4)) = *(void**)nn;
        *(void**)((char*)(*(void**)nn) + 4) = *(void**)(nn + 4);
        if (*(void**)(nn + 8) != 0)
            ((void(__thiscall*)(void*))*(void**)((char*)(*(void**)(nn + 8)) + 4))(*(void**)(nn + 8));
        void* mgr = *(void**)((char*)self + 0x68);
        ((void(__thiscall*)(void*, void*, int))VFN(mgr, 0xc))(mgr, nn, 0xc);
    }
    char* l = (char*)self + 0x50;
    FUN_00695dc0(l);
    *(void**)l = l;
    *(void**)((char*)self + 0x54) = l;
}

// =====================================================================
// @ 0x00695fa0  destroy all pooled sub-vectors
// =====================================================================
static void destroy30(char* p, char* end)
{
    while (p < end)
    {
        char* d = *(char**)(p + 4);
        if (((*(int*)(p + 0xc) - (int)d) & 0xfffffffe) > 2 && d != 0)
            operator_delete_arr(d);
        p += 0x30;
    }
}

extern "C" void __fastcall FUN_00695fa0(void* self)
{
    char* b = (char*)self;
    if (*(char**)(b + 0x14) == *(char**)(b + 0x24))
    {
        char* p = *(char**)(b + 8);
        char* e = *(char**)(b + 0x18);
        destroy30(p, e);
    }
    else
    {
        destroy30(*(char**)(b + 8), *(char**)(b + 0x10));
        destroy30(*(char**)(b + 0x1c), *(char**)(b + 0x18));
        void* p = *(void**)(b + 0x1c);
        if (p != 0)
        {
            void* mgr = *(void**)(b + 0x28);
            ((void(__thiscall*)(void*, void*, int))VFN(mgr, 0xc))(mgr, p, 0xc0);
        }
    }
    char** pp = (char**)(*(char**)(b + 0x14) + 4);
    char** pe = *(char***)(b + 0x24);
    while (pp < pe)
    {
        char* v = *pp;
        destroy30(v, v + 0xc0);
        if (*pp != 0)
        {
            void* mgr = *(void**)(b + 0x28);
            ((void(__thiscall*)(void*, void*, int))VFN(mgr, 0xc))(mgr, *pp, 0xc0);
        }
        ++pp;
    }
    *(void**)(b + 0x18) = *(void**)(b + 8);
    *(void**)(b + 0x1c) = *(void**)(b + 0xc);
    *(void**)(b + 0x20) = *(void**)(b + 0x10);
    *(void**)(b + 0x24) = *(void**)(b + 0x14);
}

// =====================================================================
// Remaining bodies are large serializer/EH routines; recorded as partial.
// =====================================================================
// @ 0x00695140
extern "C" void FUN_00695140() { /* cVarListSerializer field walk: summarised */ }

// @ 0x00695550
extern "C" void FUN_00695550() { /* vector emplace with reallocation: summarised */ }

// @ 0x00695770
extern "C" void FUN_00695770() { /* cAnimNameCommand::Execute: summarised */ }

// @ 0x00695960
extern "C" void FUN_00695960() { /* cVarListSerializer::GetFields: summarised */ }

// @ 0x00695b40
extern "C" void FUN_00695b40() { /* serializer helper: summarised */ }
