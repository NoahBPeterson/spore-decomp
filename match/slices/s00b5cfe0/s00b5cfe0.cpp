// Slice s00b5cfe0 (batch bfs1) — 18 functions.
// Module "Spore"; SP::cGonzagoMode and Gonzago UI helpers.  Each block starts with
// its original address.

#include "s00b5cfe0.h"

extern "C" void* operator_new_ea(unsigned, const char*, int, int, int, int);
extern "C" int   atexit(void (*)(void));
extern "C" void  FUN_013c29f0(void);
extern "C" void  FUN_0060c4a0(void*);       // eastl list DoClear
extern "C" void  DoClear_571db0(void*, void*, void*, void*, void*);
extern "C" void  operator_delete_00f47380(void*);
extern "C" void  RemoveHandler_571db0(void*, void*, void*, void*, void*);
extern "C" void  FUN_00ae6970(void*);

extern unsigned g_168710c;
extern int g_16870fc, g_1687100, g_1687104;
extern char g_1667bac;
extern char g_vt0dummy, g_vt1dummy, g_vt2dummy, g_vt3dummy;

static inline void* g_vt(void* p) { return *(void**)p; }
static inline void* g_vfn(void* p, int off) { return *(void**)((char*)g_vt(p) + off); }

// @ 0x00b5d3f0
void FUN_00b5d3f0(int* param)
{
    void* p = operator_new_ea(4, "App", 0, 0, 0, 0);
    if (p) *(void**)p = &g_vt2dummy;
    else p = 0;
    ((void(__thiscall*)(void*, void*, void*, const char*))g_vfn(param, 0x20))
        (param, p, (void*)0x1654c08, "LoadGame");
}

// @ 0x00b5d760
void __stdcall FUN_00b5d760(int)
{
    if ((g_168710c & 1) == 0)
    {
        g_168710c |= 1;
        g_16870fc = (int)&g_1667bac;
        g_1687100 = (int)&g_1667bac;
        g_1687104 = 0x1667bad;
        atexit(FUN_013c29f0);
    }
}

// @ 0x00b5d7a0
void __stdcall FUN_00b5d7a0(int* p)
{
    p[0] = 0x412402d0;
    p[1] = 0x2f7d0004;
    p[2] = 0xca14de92;
}

// ---------------------------------------------------------------------------
// SP::cGonzagoMode
// ---------------------------------------------------------------------------

// @ 0x00b5d510
bool cGonzagoMode::FUN_00b5d510(int param)
{
    char* head = (char*)this + 0x20;
    char* n = *(char**)head;
    while (n != head)
    {
        if (*(int*)(n + 8) == param) return true;
        n = *(char**)n;
    }
    return false;
}

// @ 0x00b5d7c0 (destructor)
cGonzagoMode::~cGonzagoMode()
{
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
    // eastl::vector<AutoRefCount<cStarRecord>> dtor at +0x5c
    // (approximated: the vector release is not reconstructed here)
    FUN_00ae6970((char*)this + 0x5c);
    if (*(int*)((char*)this + 0x48))
    {
        *(int*)((char*)this + 0x48) = 0;
        RemoveHandler_571db0((char*)this + 0x48, (char*)this + 0x4c,
                             (char*)this + 0x50, (char*)this + 0x54, (char*)this + 0x58);
    }
    if (*(int*)((char*)this + 0x34))
    {
        *(int*)((char*)this + 0x34) = 0;
        RemoveHandler_571db0((char*)this + 0x34, (char*)this + 0x38,
                             (char*)this + 0x3c, (char*)this + 0x40, (char*)this + 0x44);
    }
    FUN_0060c4a0((char*)this + 0x20);
    if (*(void**)((char*)this + 0x1c))
        ((void(__thiscall*)(void*))g_vfn(*(void**)((char*)this + 0x1c), 0xc))(*(void**)((char*)this + 0x1c));
    if (*(void**)((char*)this + 0x18))
        ((void(__thiscall*)(void*))g_vfn(*(void**)((char*)this + 0x18), 8))(*(void**)((char*)this + 0x18));
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
}

// @ 0x00b5db40
bool cGonzagoMode::FUN_00b5db40(int param)
{
    char* head = (char*)this + 0x20;
    char* n = *(char**)head;
    while (n != head)
    {
        if (*(int*)(n + 8) == param)
        {
            char* prev = *(char**)(n + 0);
            char* next = *(char**)(n + 4);
            *(char**)next = prev;
            *(char**)(prev + 4) = next;
            void* data = *(void**)(n + 8);
            if (data)
                ((void(__thiscall*)(void*))g_vfn(data, 8))(data);
            operator_delete_00f47380(n);
            return true;
        }
        n = *(char**)n;
    }
    return false;
}

// @ 0x00b5db90
void cGonzagoMode::FUN_00b5db90()
{
    char* l = (char*)this + 0x20;
    ((void(__thiscall*)(void*))FUN_0060c4a0)(l);
    *(void**)l = l;
    *(void**)(l + 4) = l;
}

// @ 0x00b5df90 (constructor)
cGonzagoMode::cGonzagoMode()
{
    vt4 = (void**)&g_vt1dummy;
    m08 = 0;
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
    b0c = b0d = b0e = 0;
    f10 = 0.0f;
    f14 = 0.0f;
    m18 = 0;
    m1c = 0;
    void** l = &listHead;
    listHead = l;
    listTail = l;
    b2c = 0;
    m30 = m34 = m38 = m3c = m40 = m44 = m48 = m4c = 0;
    m50 = m54 = m58 = m5c = m60 = m64 = 0;
}

// ---------------------------------------------------------------------------
// Remaining (approximations)
// ---------------------------------------------------------------------------

// @ 0x00b5cfe0
void FUN_00b5cfe0(void*, void*) { /* large mode enter/exit; incomplete */ }

// @ 0x00b5d130
void FUN_00b5d130(void*, int) { /* minimap init + layer loop; incomplete */ }

// @ 0x00b5d220
void FUN_00b5d220(void*, int) { /* hash bucket rehash; incomplete */ }

// @ 0x00b5d2c0
void FUN_00b5d2c0(void*, void*) { /* arg parse + background color; incomplete */ }

// @ 0x00b5d430
void FUN_00b5d430(void*, int) { /* ban-mode scene setup; incomplete */ }

// @ 0x00b5d540
void FUN_00b5d540(void*) { /* mode-strategy availability check; incomplete */ }

// @ 0x00b5d870
void FUN_00b5d870(void*, void*) { /* command-line switch handling; incomplete */ }

// @ 0x00b5da50
void FUN_00b5da50(void*, void*) { /* mode setup; incomplete */ }

// @ 0x00b5dbb0
void FUN_00b5dbb0(void*) { /* effects manager update; incomplete */ }

// @ 0x00b5e050
int FUN_00b5e050(void*, int*) { /* style hashtable find; incomplete */ return 0; }