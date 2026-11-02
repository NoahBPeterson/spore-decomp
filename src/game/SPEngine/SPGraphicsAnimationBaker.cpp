// src/game/SPEngine/SPGraphicsAnimationBaker.cpp -- migrated from slice(s) s006c0db0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsAnimationBaker.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern void  sub_11e28e0(void*, int, void*);               // Arena::GetExportedObjectByIndex
extern void  sub_f47380(void*);                            // allocator deallocate
extern void* sub_f25ea0(void*, void*, void*);              // eastl uninitialized copy
extern void* EAGetManager();
extern void* IDGenerator();
#include <string.h>

// ---- items of slice s006c0db0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
extern void  sub_11e0b22(void*, u32, u32, void*);          // ??_M vector dtor iterator
extern void  sub_11e0b85(void*, u32, u32, void*, void*);   // ??_L vector ctor iterator
extern void* sub_11e0744(void*, void*, u32);               // memcpy-ish
extern u32   sub_11e23a0(void*);                           // Arena::GetNumExportedObjects
extern void  sub_11e28e0(void*, int, void*);               // Arena::GetExportedObjectByIndex
extern void  sub_f47380(void*);                            // allocator deallocate
extern void* sub_f473a0(u32, const char*, int, int, const char*, int); // allocator allocate
extern void* sub_f25ea0(void*, void*, void*);              // eastl uninitialized copy
extern void  sub_acfe0(u32, u32);                          // FUN_006acfe0
extern void  sub_b4b60(u32, u32);                          // FUN_006b4b60
extern u32   sub_b1f90(u32, int, int);                     // SP::GetSaveArea
extern void  sub_ac040(u32, int);                          // SP::SetCachingType
extern void* EAGetManager();
extern void* IDGenerator();
struct cAnimationBaker {
    char pad00[8];
    u32 f08, f0c, f10;
    void GetBakedAnimations();
};
// ---- items of slice s006c0db0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void  sub_11e0b22(void*, u32, u32, void*);          // ??_M vector dtor iterator
extern void  sub_11e0b85(void*, u32, u32, void*, void*);   // ??_L vector ctor iterator
extern void* sub_11e0744(void*, void*, u32);               // memcpy-ish
extern u32   sub_11e23a0(void*);                           // Arena::GetNumExportedObjects
extern void* sub_f473a0(u32, const char*, int, int, const char*, int); // allocator allocate
extern void  sub_acfe0(u32, u32);                          // FUN_006acfe0
extern void  sub_b4b60(u32, u32);                          // FUN_006b4b60
extern u32   sub_b1f90(u32, int, int);                     // SP::GetSaveArea
extern void  sub_ac040(u32, int);                          // SP::SetCachingType

// @ 0x006c12e0
u32 VecDtorRange(u32 first, u32 last, u32 out)
{
    if (first == last)
        return out;
    do {
        sub_11e0b22((void*)(first + 0x18), 8, 4, (void*)0xc2e4e0);
        first += 0x38;
        out += 0x38;
    } while (first != last);
    return out;
}

// @ 0x006c13f0
void VecInsert38(int* v, u32 pos, u32 val)
{
    u32* end = (u32*)v[1];
    if (end != (u32*)v[2]) {
        if (pos <= val && val < (u32)end)
            val += 0x38;
        if (end != 0) {
            u32* src = end - 0xe;
            for (int i = 0; i < 0xe; ++i)
                end[i] = src[i];
        }
        u32* dst = (u32*)v[1];
        u32* src = dst - 0xe;
        while (src != (u32*)pos) {
            src -= 0xe;
            dst -= 0xe;
            for (int i = 0; i < 0xe; ++i)
                dst[i] = src[i];
        }
        for (int i = 0; i < 0xe; ++i)
            ((u32*)pos)[i] = ((u32*)val)[i];
        v[1] += 0x38;
        return;
    }
    int count = ((int)end - v[0]) / 0x38;
    int cnt;
    if (count == 0) cnt = 1;
    else { cnt = count * 2; if (cnt == 0) { cnt = 0; goto alloc_done; } }
    {
        void* p = sub_f473a0(cnt * 0x38,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0x13eb8a4, 0, 0, 0xd1);
        cnt = (int)p;
    }
alloc_done:
    {
        u32 old = v[0];
        u32 p = (u32)sub_f25ea0((void*)old, (void*)pos, (void*)cnt);
        VecDtorRange(old, (u32)pos, p);
        if (p != 0) {
            u32* d = (u32*)p;
            for (int i = 0; i < 0xe; ++i)
                d[i] = ((u32*)val)[i];
        }
        u32 tail = (u32)sub_f25ea0((void*)pos, (void*)v[1], (void*)(p + 0x38));
        VecDtorRange(pos, v[1], p + 0x38);
        u32 oldp = v[0];
        if (oldp != 0 && oldp != v[4])
            sub_f47380((void*)oldp);
        v[1] = tail;
        v[0] = cnt;
        v[2] = cnt + count * 0;   // capacity base; end computed by caller layout
    }
}

// @ 0x006c1570
void VecInsert4(int* v, u32 pos, u32 val)
{
    u32* end = (u32*)v[1];
    if (end != (u32*)v[2]) {
        if (pos <= val && val < (u32)end)
            val += 4;
        if (end != 0)
            *(u32*)end = end[-1];
        u32 s = (v[1] - 4) - pos;
        memmove((void*)((v[1]) + ((int)s >> 2) * -4), (void*)pos, s);
        *(u32*)pos = *(u32*)val;
        v[1] += 4;
        return;
    }
    int n = ((int)end - v[0]) >> 2;
    int cap;
    if (n == 0) cap = 1;
    else { cap = n * 2; if (cap == 0) { cap = 0; goto alloc_done; } }
    cap = (int)sub_f473a0(cap * 4,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0x13eb8a4, 0, 0, 0xd1);
alloc_done:
    {
        u32 s = pos - v[0];
        u32 p = (u32)sub_11e0744((void*)cap, (void*)v[0], s);
        u32* slot = (u32*)(p + (s >> 2) * 4);
        if (slot != 0)
            *slot = *(u32*)val;
        u32 oldend = v[1];
        u32 q = (u32)sub_11e0744(slot + 1, (void*)pos, oldend - pos);
        u32 old = v[0];
        if (old != 0 && old != v[4])
            sub_f47380((void*)old);
        v[0] = cap;
        v[1] = q + ((oldend - pos) >> 2) * 4;
        v[2] = cap + cap * 0;  // placeholder (capacity set from local)
    }
}

// @ 0x006c1680
void CollectArenaObjects(int self, u32* out, u32 a3)
{
    void* arena = *(void**)(self + 0x18);
    for (int i = 0; i < (int)sub_11e23a0(arena); ++i) {
        char obj[0x38];
        sub_11e0b85(obj + 0x18, 8, 4, (void*)0x6c0fa0, (void*)0xc2e4e0);
        *(u32*)(obj + 0x18) = 0;
        *(u32*)(obj + 0x1c) = 1;
        sub_11e28e0(arena, i, obj);
        sub_11e0b22(obj + 0x18, 8, 4, (void*)0xc2e4e0);
    }
    sub_acfe0(a3, out[0]);
    sub_b4b60(out[0], sub_b1f90(0x49a3d83, 0, 0));
}

// @ 0x006c1ae0
void cAnimationBaker::GetBakedAnimations()
{
    u32 a = f08, b = f0c, c = f10;
    void* handle = 0;
    if (((c & 0xc0000000) == 0x40000000) && ((c & 0xff0000) == 0x600000) && ((c & 0x1f000000) == 0)) {
        c = (c & 0xe1ffffff) | 0x1000000;
        void* mgr = EAGetManager();
        if (handle != 0) {
            handle = 0;
            ((void(__thiscall*)(void*))(*(void***)handle)[4 / 4])(handle);
        }
        bool ok = ((bool(__thiscall*)(void*, u32*, void**))(*(void***)mgr)[0xc / 4])(mgr, &a, &handle);
        if (ok && b != 0) {
            void* p = ((void*(__thiscall*)(void*, u32))(*(void***)(void*)b)[0xc / 4])((void*)b, 0x2f4e681b);
            if (p != 0) {
                *(u32*)c = (u32)p;
                ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
                goto done;
            }
        }
    } else {
        void* g = IDGenerator();
        ((void(__thiscall*)(void*))(*(void***)g)[4 / 4])(g);
    }
    CollectArenaObjects((int)this, (u32*)c, (u32)&a);
done:
    if (*(u32*)c != 0)
        sub_ac040(*(u32*)c, 9);
    if (b != 0)
        ((void(__thiscall*)(void*))(*(void***)(void*)b)[4 / 4])((void*)b);
}
