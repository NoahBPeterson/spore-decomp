// Slice s006afa10: LRU cache / resource-request adapters and helpers.
// Mostly /O2; several small vtable-dispatch leaves match directly.
#include "../../include/types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// 006afae0  void FUN_006afae0(void* self)
// ---------------------------------------------------------------------------
void __fastcall FUN_006afae0(void* self)
{
    void* p = *(void**)((char*)self + 0x14);
    if (p)
        ((void(__thiscall*)(void*, int, void*, int))(*(void***)self)[17])(self, 0, p, 0);
    void* q = *(void**)((char*)self + 0xc);
    ((void(__thiscall*)(void*))(*(void***)q)[2])(q);
}

// ---------------------------------------------------------------------------
// 006afb20  bool Cfb20::f(void*, void*, void*)
// ---------------------------------------------------------------------------
struct Cfb20 {
    char pad[0xc];
    void* m0c;   // +0xc
    void* m10;   // +0x10
    bool f(void* a1, void* a2, void* a3);
};

bool Cfb20::f(void* a1, void* a2, void* a3)
{
    bool r = ((bool(__thiscall*)(void*, void*, void*, void*))(*(void***)m0c)[6])(m0c, a1, a2, a3);
    if (r) {
        ((void(__thiscall*)(void*))(*(void***)m10)[4])(m10);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 006afb60  void FUN_006afb60(void* self)
// ---------------------------------------------------------------------------
void __fastcall FUN_006afb60(void* self)
{
    void* p = *(void**)((char*)self + 0x10);
    ((void(__thiscall*)(void*))(*(void***)p)[5])(p);
    void* q = *(void**)((char*)self + 0xc);
    ((void(__thiscall*)(void*))(*(void***)q)[7])(q);
}

// ---------------------------------------------------------------------------
// 006afbe0  char Cfb860::f(int* p)
// ---------------------------------------------------------------------------
struct Cfb860 {
    char pad[0xc];
    void* m0c;   // +0xc
    void* m10;   // +0x10
    char f(int* p);
};

char Cfb860::f(int* p)
{
    if (p[0] == 0x2e5a9763 && p[2] == 0 && p[1] == 0x2e5a9763)
        return 0;
    char r = ((char(__thiscall*)(void*, int*))(*(void***)m0c)[16])(m0c, p);
    if (r)
        ((void(__thiscall*)(void*, int*))(*(void***)m10)[8])(m10, p);
    return r;
}

// ---------------------------------------------------------------------------
// 006afa90  void* CAfa90::Query(int iid)
// ---------------------------------------------------------------------------
struct CAfa90 {
    void* Query(int iid);
};

void* CAfa90::Query(int iid)
{
    if (iid == 0x498d9c1)
        return (char*)this - 4;
    if (iid == 0xee3f516e) {
        if (this != (CAfa90*)4 && this != 0)
            return this;
    }
    int* x = *(int**)((char*)this + 8);
    void** p = (void**)((char*)x + 4);
    return ((void*(__thiscall*)(void*, int))(*(void***)p)[3])(p, iid);
}

// ---------------------------------------------------------------------------
// 006b05d0  bool __stdcall FUN_006b05d0(void*)
// ---------------------------------------------------------------------------
void FUN_006afe80();
bool __stdcall FUN_006b05d0(void* self)
{
    FUN_006afe80();
    return true;
}

// ===========================================================================
// more functions
// ===========================================================================
extern "C" void* ea_alloc_raw(unsigned size, void* zone, int, int, int, int); // 0xf473a0
struct SubC1b0 { void init(int, int); };   // FUN_0068c1b0

// ---------------------------------------------------------------------------
// 006afe40  void __fastcall FUN_006afe40(void* self, LN* node)
// ---------------------------------------------------------------------------
struct LN { LN* flink; LN* blink; };
struct CAfe40 {
    void f(LN* node);
};

void CAfe40::f(LN* node)
{
    LN* first = node->flink;
    LN* head = (LN*)((char*)this + 0x34);
    if (head != node && head != first) {
        first->blink->flink = head;
        node->blink->flink = first;
        head->blink->flink = node;
        LN* t = head->blink;
        head->blink = first->blink;
        first->blink = node->blink;
        node->blink = t;
    }
    *(char*)((char*)this + 0x15) = 1;
}

// ---------------------------------------------------------------------------
// 006b0530  void* __stdcall FUN_006b0530(void* src)
// ---------------------------------------------------------------------------
void* __stdcall FUN_006b0530(void* src)
{
    char* p = (char*)ea_alloc_raw(0x20, (void*)"App", 0, 0, 0, 0);
    if (!src) {
        if (!p)
            return 0;
        *(void**)p = 0;
        *(void**)(p + 0x10) = 0;
        *(void**)(p + 4) = 0;
        *(void**)(p + 8) = 0;
        *(void**)(p + 0xc) = 0;
        ((SubC1b0*)(p + 0x18))->init(0, 0);
        return p;
    }
    if (!p)
        return 0;
    *(void**)p = *(void**)src;
    *(void**)(p + 4) = *(void**)((char*)src + 4);
    *(void**)(p + 8) = *(void**)((char*)src + 8);
    *(void**)(p + 0xc) = *(void**)((char*)src + 0xc);
    *(void**)(p + 0x10) = *(void**)((char*)src + 0x10);
    ((SubC1b0*)(p + 0x18))->init(0, 0);
    return p;
}

// ---------------------------------------------------------------------------
// 006b08a0  void* __stdcall FUN_006b08a0(void* a, void* b)
// ---------------------------------------------------------------------------
void* __stdcall FUN_006b08a0(void* a, void* b)
{
    char* p = (char*)ea_alloc_raw(0x128, (void*)"App/Resource/LRUCache", 0, 0, 0, 0);
    if (!p)
        return 0;
    *(void**)p = a;
    *(void**)(p + 4) = b;
    *(void**)(p + 8) = 0;
    *(void**)(p + 0xc) = 0;
    char* q = p + 0x28;
    *(void**)(p + 0x10) = q;
    *(void**)(p + 0x14) = q;
    q += 0x100;
    *(void**)(p + 0x24) = 0;
    *(void**)(p + 0x18) = q;
    return p;
}

// ---------------------------------------------------------------------------
// complex functions left as partial skeletons (see partial.txt)
// ---------------------------------------------------------------------------
void __fastcall FUN_006afa10(void*) {}
void __fastcall FUN_006afc40(void*, void*) {}
void __fastcall FUN_006afcb0(void*) {}
void __fastcall FUN_006afd10(void*, void*) {}
void __fastcall FUN_006afdd0(void*) {}
void __fastcall FUN_006aff70(void*, void*, void*) {}
void __fastcall FUN_006b0020(void*) {}
void __fastcall FUN_006b00a0(void*, void*, void*) {}
void __fastcall FUN_006b0130(void*, void*, void*, void*, void*, void*, void*) {}
void __fastcall FUN_006b02b0(void*) {}
void __fastcall FUN_006b0300(void*, void*) {}
void __fastcall FUN_006b04a0(void*, void*, void*, void*, char) {}
void __fastcall FUN_006b0670(void*, void*, void*) {}
void __fastcall FUN_006b0720(void*, void*, void*) {}
void __fastcall FUN_006b0900(void*) {}
#pragma code_seg(".text$zz")
extern "C" void dummy_extern();
void FUN_006afe80() { dummy_extern(); }
#pragma code_seg()
