// Slice s00a2bfa0 - EA::Audio resource/hashtable find-or-create helpers and System update.
// Compiled with /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <stdlib.h>
#include <string.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

#define EASTL_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define VFN(p, off) ((*(void***)(p))[(off) / 4])

extern void* g_pSystem;                                       // 0x0166d9f4

void* __cdecl eaNew(size_t size, const char* name, int flags, unsigned dbgFlags,
                    const char* file, int line);              // 0x00f473a0  EAAllocate
void  __cdecl operator_delete(void* p);                       // 0x00f47380
void* __cdecl ObjectError();                                  // 0x008de1a0

// ---------------------------------------------------------------------------
// eastl::hashtable-ish containers (bucket array at +4, bucket count at +8).
// ---------------------------------------------------------------------------
struct Key { u32 a, b, c; };                                  // EA::ResourceMan::Key (12 bytes)

struct HTex {                                                 // this+0x1189fc
    u32     f0;            // +0
    void**  buckets;       // +4
    u32     count;         // +8
    void find(void* iterOut, const Key* key);                 // 0x00833840
    void insert(void* iterOut, const void* pair, int flag);   // 0x00a26b00
};

struct HAudio {                                               // this+0x119bb8
    u32     f0;            // +0
    void**  buckets;       // +4
    u32     count;         // +8
    void find(void* iterOut, const u32* key);                 // 0x00645ed0
    void* GetOrInsert(const u32* key);                        // 0x00a2a150
};

// Object ctor used by the create paths: 0x00a145c0 (thiscall, returns object).
void* __cdecl CtorAudioObj(void* mem, u32 key);               // 0x00a145c0 (this in ecx via member below)
struct CtorT { void* ctor(u32 key); };

// ---------------------------------------------------------------------------
// Manager (retail layout: texture table +0x1189fc, audio table +0x119bb8,
// sound list +0x157438).
// ---------------------------------------------------------------------------
struct Sys {
    u8      pad0[0x1189fc];
    HTex    texTable;      // +0x1189fc
    u8      pad1[0x119bb8 - (0x1189fc + 0xc)];
    HAudio  audioTable;    // +0x119bb8
    u8      pad2[0x157438 - (0x119bb8 + 0xc)];
    void*   soundList;     // +0x157438 (intrusive list head)

    bool GetTextureInstance(const Key* key, void** out);      // 0x00a2bfa0
    void Update();                                            // 0x00a2c140
    bool GetAudioA(u32 key, u32 param);                       // 0x00a2c450
    bool GetAudioB(u32 key);                                  // 0x00a2c590
    void NotifyTex(const Key* key);                           // 0x00a28a20 (thiscall)
};

// @ 0x00a2bfa0
bool Sys::GetTextureInstance(const Key* key, void** out)
{
    void* iter[2];
    texTable.find(iter, key);
    if (iter[0] != texTable.buckets[texTable.count]) {
        void* val = *(void**)((char*)iter[0] + 0xc);
        if (!val) return false;
        if (out) {
            NotifyTex(key);
            ((void(__thiscall*)(void*))VFN(val, 0))(val);
            *out = val;
        }
        return true;
    }

    void* tmp = 0;
    void* err = ObjectError();
    if (tmp) ((void(__thiscall*)(void*))VFN(tmp, 4))(tmp);
    bool ok = ((bool(__thiscall*)(void*, const Key*, void**, int, int, int, int))VFN(err, 0xc))
                  (err, key, &tmp, 0, 0, 0, 0);

    struct Pair { Key k; void* v; } pair;
    pair.k = *key;
    pair.v = tmp;
    if (tmp) ((void(__thiscall*)(void*))VFN(tmp, 0))(tmp);
    u32 ins[2];
    texTable.insert(ins, &pair, 0);
    if (tmp) ((void(__thiscall*)(void*))VFN(tmp, 4))(tmp);

    if (!ok) {
        if (tmp) ((void(__thiscall*)(void*))VFN(tmp, 4))(tmp);
        return false;
    }
    if (out) {
        NotifyTex(key);
        ((void(__thiscall*)(void*))VFN(tmp, 0))(tmp);
        *out = tmp;
    }
    if (tmp) ((void(__thiscall*)(void*))VFN(tmp, 4))(tmp);
    return true;
}

// ---------------------------------------------------------------------------
// Global scratch vector used by Update (0x0166da14 begin / 18 end / 1c cap).
// ---------------------------------------------------------------------------
void** g_vecBegin;                                            // 0x0166da14
void** g_vecEnd;                                              // 0x0166da18
void** g_vecCap;                                              // 0x0166da1c
u32    g_vecInit;                                             // 0x0166da28

void __cdecl vecBoolClear(void** begin, void** end, int v);   // 0x011e0744
struct PtrVec { void DoInsertValue(void** pos, void** value); }; // 0x00a80dd0

bool  __cdecl fnA1af60(void* obj);                            // 0x00a1af60 (thiscall below)
int   __cdecl fnA1b3f0(void* obj);                            // 0x00a1b3f0
struct ObjFn { bool check(void); int check2(void); };
struct AtExitT { void reg(); };                               // 0x013c17f0
void __cdecl _atexit(void (*)(void));                         // 0x011e07ef

// @ 0x00a2c140
void Sys::Update()
{
    char* self = (char*)this;
    char* obj  = *(void**)(self + 0x157438) ? (char*)(*(void**)(self + 0x157438)) - 0x10 : 0;
    char* stop = self + 0x157438 - 0x10;

    while (obj != stop) {
        if (((*(u8*)(obj + 0xce4) & 0x10) != 0) &&
            ((ObjFn*)obj)->check() &&
            ((ObjFn*)obj)->check2() == 0) {
            if (!g_vecInit) {
                g_vecInit = 1;
                g_vecBegin = 0; g_vecEnd = 0; g_vecCap = 0;
                _atexit(0);                                   // 0x013c17f0
            }
            void** first = *(void***)(obj + 0xc7c);
            void** last  = *(void***)(obj + 0xc80);
            for (void** it = first; it != last; ++it) {
                void* e = *it;
                if (e) ((void(__thiscall*)(void*))VFN(e, 0))(e);
                bool keep = !((bool(__thiscall*)(void*, void*))VFN(e, 0xc4))(e, obj);
                if (keep) {
                    if (g_vecEnd < g_vecCap) {
                        *g_vecEnd++ = e;
                    } else {
                        ((PtrVec*)&g_vecBegin)->DoInsertValue(g_vecEnd, &e);
                    }
                }
                if (e) ((void(__thiscall*)(void*))VFN(e, 4))(e);
            }
            for (void** it = g_vecBegin; it != g_vecEnd; ++it) {
                void* e = *it;
                if (e) ((void(__thiscall*)(void*))VFN(e, 0))(e);
                ((void(__thiscall*)(void*))VFN(e, 0xc0))(e);
                if (e) ((void(__thiscall*)(void*))VFN(e, 4))(e);
            }
            vecBoolClear(g_vecBegin, g_vecEnd, 0);
            g_vecEnd -= (g_vecEnd - g_vecBegin);

            void* tmp = 0;
            if (((bool(__thiscall*)(void*, void**))VFN(this, 0x150))(this, &tmp)) {
                if (((*(u8*)(obj + 0xce4) & 0x20) != 0) && *(void**)(obj + 0x44)) {
                    void* p = *(void**)(obj + 0x44);
                    ((void(__thiscall*)(void*))VFN(p, 0x18))(p);
                    ((void(__thiscall*)(void*, int))VFN(p, 0x38))(p, 0);
                    if (p) { *(void**)(obj + 0x44) = 0;
                             ((void(__thiscall*)(void*))VFN(p, 4))(p); }
                    *(u32*)(obj + 0xce4) &= ~0x20u;
                }
                if ((*(u8*)(obj + 0xce4) & 8) != 0) {
                    *(u32*)(obj + 0xce4) &= ~8u;
                    ((void(__thiscall*)(void*, void*))VFN(this, 0x74))(this, obj);
                }
                void** f2 = *(void***)(obj + 0xc7c);
                void** l2 = *(void***)(obj + 0xc80);
                for (void** it = f2; it != l2; ++it) {
                    void* e = *it;
                    if (e) ((void(__thiscall*)(void*))VFN(e, 0))(e);
                    ((void(__thiscall*)(void*, int))VFN(e, 0xd4))(e, 0);
                    ((void(__thiscall*)(void*, void*))VFN(this, 0xb8))(this, e);
                    ((void(__thiscall*)(void*))VFN(e, 4))(e);
                }
                vecBoolClear(*(void***)(obj + 0xc7c), *(void***)(obj + 0xc80), 0);
                *(u32*)(obj + 0xc80) -= (*(u32*)(obj + 0xc80) - *(u32*)(obj + 0xc7c));
                ((void(__thiscall*)(void*, void*))VFN(tmp, 0xb8))(tmp, obj);
            }
            if (tmp) ((void(__thiscall*)(void*))VFN(tmp, 4))(tmp);
        }
        obj = *(void**)(obj + 0x10) ? (char*)(*(void**)(obj + 0x10)) - 0x10 : 0;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00a2c450
// ---------------------------------------------------------------------------
bool Sys::GetAudioA(u32 key, u32 param)
{
    void* iter[2];
    audioTable.find(iter, &key);
    void* val = 0;
    if (iter[0] != audioTable.buckets[audioTable.count]) {
        val = *(void**)((char*)iter[0] + 4);
        if (val) ((void(__thiscall*)(void*))VFN(val, 0))(val);
    } else {
        void* mem = eaNew(0x1874, "Audio", 0, 0, 0, 0);
        void* nw = mem ? ((CtorT*)mem)->ctor(key) : 0;
        if (nw) {
            ((void(__thiscall*)(void*))VFN(nw, 0))(nw);
            val = nw;
        }
        ((void(__thiscall*)(void*))VFN(val, 0x20))(val);
        void** slot = (void**)audioTable.GetOrInsert(&key);
        void* old = *slot;
        if (val != old) {
            ((void(__thiscall*)(void*))VFN(val, 0))(val);
            *slot = val;
            if (old) ((void(__thiscall*)(void*))VFN(old, 4))(old);
        }
        ((void(__thiscall*)(void*, void*))VFN(this, 0x16c))(this, val);
    }
    u8 r = ((u8(__thiscall*)(void*, u32))VFN(val, 0x28))(val, param);
    ((void(__thiscall*)(void*))VFN(val, 4))(val);
    return r != 0;
}

// @ 0x00a2c590
bool Sys::GetAudioB(u32 key)
{
    void* iter[2];
    audioTable.find(iter, &key);
    if (iter[0] != audioTable.buckets[audioTable.count])
        return false;

    void* mem = eaNew(0x1874, "Audio", 0, 0, 0, 0);
    void* nw = mem ? ((CtorT*)mem)->ctor(key) : 0;
    if (nw) ((void(__thiscall*)(void*))VFN(nw, 0))(nw);
    ((void(__thiscall*)(void*))VFN(nw, 0x20))(nw);
    void** slot = (void**)audioTable.GetOrInsert(&key);
    void* old = *slot;
    if (nw != old) {
        ((void(__thiscall*)(void*))VFN(nw, 0))(nw);
        *slot = nw;
        if (old) ((void(__thiscall*)(void*))VFN(old, 4))(old);
    }
    ((void(__thiscall*)(void*, void*))VFN(this, 0x16c))(this, nw);
    ((void(__thiscall*)(void*))VFN(nw, 4))(nw);
    return true;
}
