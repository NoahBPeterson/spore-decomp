// Slice s006ab3d0 — fixed-allocator / cache / primitive EA helpers (mixed).
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <intrin.h>

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

void  WString_Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650 (basic_string<wchar_t>::assign)
void  EASTL_allocator_deallocate(void* p);                          // 0x00f47380
void* EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line);

// ===========================================================================
// eastl::basic_string<wchar_t>
// ===========================================================================
struct WString {
    wchar_t* mpBegin;    // +0
    wchar_t* mpEnd;      // +4
    wchar_t* mpCapacity; // +8
    void*    mAllocator; // +0xc

    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
    void assign(const wchar_t* p, unsigned n);                 // @ 0x006ab7e0
};

// @ 0x006ab7e0
void WString::assign(const wchar_t* p, unsigned n)
{
    assign(p, p + n);
}

// @ 0x006ab800
void FUN_006ab800(WString* s, int idx, unsigned count)
{
    unsigned size = (unsigned)(s->mpEnd - s->mpBegin);
    unsigned n = size - idx;
    if (n > count)
        n = count;
    s->assign(s->mpBegin + idx, s->mpBegin + idx + n);
}

// ===========================================================================
// atomics / refcount
// ===========================================================================

// @ 0x006abdf0
int __fastcall FUN_006abdf0(void** self)
{
    return _InterlockedExchangeAdd((volatile long*)*self, -2);
}

// @ 0x006abe00
void __fastcall FUN_006abe00(void** self)
{
    int* p = (int*)*self;
    _InterlockedExchangeAdd((volatile long*)p, -1);
    _InterlockedExchangeAdd((volatile long*)(p + 2), 1);
}

// @ 0x006abee0
bool __fastcall FUN_006abee0(char* self)
{
    if (self[8] == 0)
        self[8] = 1;
    return true;
}

// ===========================================================================
// fixed allocator
// ===========================================================================
struct FixedAlloc {
    bool AddCore(int, int);   // 0x00926650
};

// @ 0x006abe50
void* FUN_006abe50(FixedAlloc* self, uint32_t size, int flags)
{
    if (size > 0x14)
        return EASTL_allocator_allocate(size, "App", flags, 0, ALLOC_FILE, 0xd1);
    for (;;) {
        void* c = *(void**)((char*)self + 0x10);
        if (c) {
            *(void**)((char*)self + 0x10) = *(void**)c;
            return c;
        }
        if (!self->AddCore(0, 0))
            return 0;
    }
}

// ===========================================================================
// small copy / free helpers
// ===========================================================================

// @ 0x006ac440
void FUN_006ac440(uint32_t* dst, uint32_t count, const uint32_t* src)
{
    while (count != 0) {
        if (dst) {
            dst[0] = src[0];
            dst[1] = src[1];
        }
        dst += 2;
        --count;
    }
}

// @ 0x006ac470
void __fastcall FUN_006ac470(int self)
{
    int p = *(int*)(self + 4);
    if (p != 0 && p != *(int*)(self + 0x14))
        EASTL_allocator_deallocate((void*)p);
}

// @ 0x006abeb0
extern void* g_cacheManager;   // 0x016c8b44
struct CacheManager {
    void Method(void* p, int a, int b, int c, int d, int e);   // 0x009289f0
};
void FUN_006abeb0(void* p)
{
    ((CacheManager*)g_cacheManager)->Method(p, 0, 0, 0, 0, 0);
}

// ===========================================================================
// caching type accessors
// ===========================================================================
extern char sNullCache;            // 0x0152f7bc
extern char sManualExplicitCache;  // 0x0152f7c0
extern char sLRUCaches;            // 0x016032a8

// @ 0x006ac040
bool SetCachingType(int type, void* obj)
{
    if (*(void**)((char*)obj + 0x14) != 0)
        return false;
    if (type == 2) { *(void**)((char*)obj + 0x14) = &sNullCache; return true; }
    if (type == 1) { *(void**)((char*)obj + 0x14) = &sManualExplicitCache; return true; }
    if ((unsigned)(type - 3) <= 0xa) {
        *(void**)((char*)obj + 0x14) = (char*)&sLRUCaches + (type - 3) * 0x150;
        return true;
    }
    if (type != 0)
        return false;
    return true;
}

struct CacheHolder { void** vtbl; };
inline int CacheHolder_Find(CacheHolder* o, int id)
{
    typedef int (__thiscall* Fn)(void*, int);
    return ((Fn)o->vtbl[0xc / 4])(o, id);
}

// @ 0x006ac0a0
uint32_t FUN_006ac0a0(uint32_t type, CacheHolder* obj)
{
    if (!obj)
        return 0;
    int v = CacheHolder_Find(obj, 0x355d6f5);
    if (!v)
        return 0;
    return SetCachingType(type, (void*)v);
}

// @ 0x006ac0d0
int FUN_006ac0d0(CacheHolder* obj)
{
    if (!obj)
        return 0;
    int v = CacheHolder_Find(obj, 0x355d6f5);
    if (!v)
        return 0;
    void** c = *(void***)(v + 0x14);
    if (!c)
        return 0;
    if (c == (void**)&sManualExplicitCache) return 1;
    if (c == (void**)&sNullCache) return 2;
    if ((uint32_t)c > 0x16032a7u && (uint32_t)c < 0x1604118u)
        return (int)((char*)c - 0x16032a8) / 0x150 + 3;
    return 0;
}

// ===========================================================================
// Remaining slice functions (partial)
// ===========================================================================

// @ 0x006ab3d0
void FUN_006ab3d0(void* self, void* a2)
{
    // TODO(partial): fixed-allocator size-class / core management helper.
    (void)self; (void)a2;
}

// @ 0x006ab6c0
void FUN_006ab6c0(void* a1, void* a2, void* a3)
{
    // TODO(partial): hash-of-wstring + allocator helper.
    (void)a1; (void)a2; (void)a3;
}

// @ 0x006ab760
// eastl::hashtable<basic_string<wchar_t>, pair<const basic_string<wchar_t>, basic_string<wchar_t>>,
//                  fixed_hashtable_allocator<6,36,4,4,0,1>>::DoFindNode<wchar_t*, equal_to_2<...>>
bool FUN_006ab760(void* self, const wchar_t* key)
{
    // TODO(partial): fixed-hashtable node search by wchar_t* key.
    (void)self; (void)key;
    return false;
}

// @ 0x006ab840
void FUN_006ab840(void* self, void* a2, void* a3)
{
    // TODO(partial): wstring hashtable node find/insert helper.
    (void)self; (void)a2; (void)a3;
}

// @ 0x006ab950
void FUN_006ab950(void* self)
{
    // TODO(partial): wstring hashtable rehash/allocate helper.
    (void)self;
}

// @ 0x006aba80
// rw::graphics::D3D9ShaderGeneric3DMorphingInitialize
void D3D9ShaderGeneric3DMorphingInitialize(void* self, void* a2)
{
    // TODO(partial): D3D9 shader initialisation sequence.
    (void)self; (void)a2;
}

// @ 0x006abc90
void FUN_006abc90(void* self, void* a2, void* a3)
{
    // TODO(partial): shader constant / stream setup.
    (void)self; (void)a2; (void)a3;
}

// @ 0x006abf20
void FUN_006abf20(void* self)
{
    // TODO(partial): spin-wait / atomic retire queue.
    (void)self;
}

// @ 0x006abfa0
void FUN_006abfa0(void* self)
{
    // TODO(partial): atomic refcount retire helper.
    (void)self;
}

// @ 0x006ac140
void FUN_006ac140(void* self)
{
    // TODO(partial): FixedAllocatorBase::Init + vtable setup.
    (void)self;
}

// @ 0x006ac260
void* FUN_006ac260(void* self, void* value)
{
    // TODO(partial): fixed-allocator node allocation + value copy.
    (void)self; (void)value;
    return 0;
}

// @ 0x006ac2f0
void FUN_006ac2f0(void* self, void* a2, void* a3)
{
    // TODO(partial): fixed-allocator node init loop.
    (void)self; (void)a2; (void)a3;
}

// @ 0x006ac3c0
void FUN_006ac3c0(void* self)
{
    // TODO(partial): fixed-allocator core teardown.
    (void)self;
}

// @ 0x006ac5d0
void FUN_006ac5d0(void* self, void* buckets, uint32_t count)
{
    // TODO(partial): free a bucket array of allocated nodes.
    (void)self; (void)buckets; (void)count;
}
