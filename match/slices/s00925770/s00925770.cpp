// EA::Trace helper/allocator tail end (0x00925770..0x00926350). Many small EAThread/EASTL helpers;
// the simple ones are byte-exact, the larger allocator internals are skeletons (see partial.txt).
#include <windows.h>
#include <stddef.h>
#include <string.h>

namespace EA { namespace Trace {

// @ 0x00925770  AutoOSGlobalPtr<EATracerPtr,...>::Create
extern "C" void* __cdecl eanew(int, int, int, const char*, int, int, int, int);
extern void* __fastcall ctor_00925540(void*);
void* CreateTracerPtr() {
    int* p = (int*)eanew(0x14, 4, 0, "OSGlobal", 0, 0, 0, 0);
    if (p) return ctor_00925540(p);
    return 0;
}
// @ 0x00925BC0
extern void* __fastcall ctor_00925b00(void*);
void* CreateHelperTablePtr() {
    int* p = (int*)eanew(0x14, 4, 0, "OSGlobal", 0, 0, 0, 0);
    if (p) return ctor_00925b00(p);
    return 0;
}

// @ 0x00925CB0  ICoreAllocator::GetDefaultAllocator
extern void* g_01668eac;
extern void* g_0154df84;
extern char  g_0154df88;
extern void* g_0154df8c;
extern void* g_0154df90;
extern void* g_016c8b44;
void* GetDefaultAllocatorX() {
    if (!g_01668eac) {
        if (!g_0154df84) {
            g_0154df84 = g_016c8b44;
            g_0154df88 = 0;
            g_0154df8c = 0;
            g_0154df90 = 0;
        }
        g_01668eac = (void*)0x0154df80;
    }
    return g_01668eac;
}

// @ 0x00926020  ZoneObject::operator_new
void* ZoneObject_new(int a1, int a2, int a3) {
    void* alloc = GetDefaultAllocatorX();
    int* r = (int*)((void* (__thiscall*)(void*, int, int, int, int, int))(*(void***)alloc)[1])
        (alloc, a1 + 8, a2, a3, 4, 0);
    if (r) { *r = (int)alloc; return r + 2; }
    return 0;
}
// @ 0x00926060  ZoneObject::operator_delete
void ZoneObject_delete(void* p) {
    if (p) {
        void* base = (char*)p - 8;
        ((void (__thiscall*)(void*, int))(*(void***)*(void**)base)[3])(base, 0);
    }
}

// @ 0x00925BF0
void FUN_00925bf0(unsigned a1, unsigned a2, int a3) {
    void* obj = *(void**)(a3 + 4);
    void** vt = *(void***)obj;
    int r = ((int (__thiscall*)(void*, unsigned, int, int))vt[2])(obj, a1, 0, 0);
    unsigned* out = (unsigned*)a2;
    if (out) *out = (r != 0) ? a1 : 0;
}
// @ 0x00925C20
void FUN_00925c20(unsigned a1, int a2) {
    void* obj = *(void**)(a2 + 4);
    void** vt = *(void***)obj;
    ((void (__thiscall*)(void*, unsigned, int))vt[3])(obj, a1, 0);
}
// @ 0x00925DA0
void FUN_00925da0(void* self, unsigned a2, unsigned a3, unsigned a4) {
    ((void (__thiscall*)(void*, unsigned, unsigned, unsigned, int, int))(*(void***)self)[1])(
        self, a2, a3, a4, 0, 0);
}

// @ 0x00925E40
void FUN_00925e40(int* self, int* p) {
    int old = self[2];
    self[2] = (int)p;
    *p = old;
    --self[4];
}
// @ 0x00925E60
extern void FUN_00925d60();
struct HashHolder { void FUN_00925e60() { *(void**)this = (void*)0x0143e104; FUN_00925d60(); } };
void FUN_00925e60_hash(HashHolder* h) { h->FUN_00925e60(); }

// @ 0x00925CF0
struct AllocDebug { char pad[8]; char flag; void* p1; void* p2; void* p3; };
void FUN_00925cf0(AllocDebug* self) { (void)self; }
// @ 0x00925D60
void FUN_00925d60(void* self) { (void)self; }

// @ 0x00926100
void* FUN_00926100(void* p) {
    if (p) { *(void**)((char*)p + 0x18) = 0; InitializeCriticalSectionAndSpinCount((CRITICAL_SECTION*)p, 10); return p; }
    return 0;
}
// @ 0x00926120
int FUN_00926120(void* p) {
    EnterCriticalSection((CRITICAL_SECTION*)p);
    ++*(int*)((char*)p + 0x18);
    return *(int*)((char*)p + 0x18);
}
// @ 0x00926140
int FUN_00926140(void* p) {
    --*(int*)((char*)p + 0x18);
    int n = *(int*)((char*)p + 0x18);
    LeaveCriticalSection((CRITICAL_SECTION*)p);
    return n;
}
// @ 0x00926340
void FUN_00926340(void* p) { DeleteCriticalSection((CRITICAL_SECTION*)p); }

// @ 0x00925F30
void FUN_00925f30(int* p, int a2, int a3, int a4) {
    p[1] = a2;
    p[5] = a4;
    p[2] = 0; p[3] = 0; p[4] = 0;
    p[6] = a3;
    *p = 0x0143e104;
    p[7] = 0;
}

}} // namespace EA::Trace

// ================================================================== skeletons (partial)
extern "C" {
void sk_009257a0() {}
void sk_009257e0() {}
void sk_009258f0() {}
void sk_00925960() {}
void sk_009259d0() {}
void sk_00925a30() {}
void* __fastcall ctor_00925b00(void* p) { return p; }
void sk_00925b50() {}
void sk_00925c40() {}
void sk_00925c70() {}
void sk_00925ca0() {}
void sk_00925dc0() {}
void sk_00925e70() {}
void sk_00925eb0() {}
void sk_00925f90() {}
void sk_00925fe0() {}
void sk_00926080() {}
void sk_009260c0() {}
void sk_00926160() {}
void sk_00926190() {}
void sk_009261f0() {}
void sk_00926300() {}
void sk_00926350() {}
}
