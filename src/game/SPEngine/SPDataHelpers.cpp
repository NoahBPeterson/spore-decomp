// src/game/SPEngine/SPDataHelpers.cpp -- migrated from slice(s) s006870a0, s006860e0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPDataHelpers.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* MemsetT(void*, int, uint32_t);                   // 0x011e073e
extern "C" void* EASTL_alloc6(uint32_t, void*, uint32_t, uint32_t, const char*, uint32_t); // 0x0f473a0
extern "C" char  g_allocTag[];
extern "C" char  g_fileEASTL[];
extern "C" void __cdecl ReadInt32(void*, void*, int, int);        // 0x093a780
extern "C" void* __cdecl HashFind(void* out, const void* key);    // 0x0685f30
extern "C" void __cdecl HashInsert(void*, void*, const void*);    // 0x0685f90
extern "C" int*  __cdecl GetManager();                            // 0x067dcd0

// ---- items of slice s006860e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline void** VT(void* p) { return *(void***)p; }
extern "C" void* MemsetT(void*, int, uint32_t);                   // 0x011e073e
extern "C" void* EASTL_alloc6(uint32_t, void*, uint32_t, uint32_t, const char*, uint32_t); // 0x0f473a0
extern "C" char  g_allocTag[];
extern "C" char  g_fileEASTL[];
extern "C" void __cdecl ReadInt32(void*, void*, int, int);        // 0x093a780
extern "C" void* __cdecl HashFind(void* out, const void* key);    // 0x0685f30
extern "C" void __cdecl HashInsert(void*, void*, const void*);    // 0x0685f90
extern "C" int*  __cdecl GetManager();                            // 0x067dcd0
struct HashMap {
    uint32_t f0;
    int* buckets;               // +0x04
    int bucketCount;            // +0x08
    int* findOut(int* out, const int* key) { HashFind(out, key); return out; }
    int* operator[](const int* key);
};
struct WFixed {
    wchar_t* mpBegin;           // +0
    wchar_t* mpEnd;             // +4
    WFixed* Append(const wchar_t* s);
    void append(const wchar_t* first, const wchar_t* last);   // 0x042f9d0 (out-of-slice)
};
struct VecBuf { int* b; int* e; int* c; int* Init(uint32_t n, void* tag); };
// ---- items of slice s006860e0 end

// ---- items of slice s006870a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl RegisterPackages(void*, void*, int, int, int); // 0x06872f0
extern "C" int  g_count;                    // 0x0152b348
extern "C" char* g_array;                   // 0x015fea00
// ---- items of slice s006870a0 end

// @ 0x00686380
int* HashMap::operator[](const int* key)
{
    int local_18[6];
    HashFind(local_18, key);
    if (local_18[0] == *(int*)((char*)buckets + bucketCount * 4)) {
        local_18[0] = *key;
        local_18[1] = 0;
        local_18[2] = 0;
        HashInsert(local_18 + 3, local_18, 0);
        local_18[0] = local_18[3];
    }
    return (int*)(local_18[0] + 4);
}

// @ 0x006863e0
WFixed* WFixed::Append(const wchar_t* s)
{
    if (mpBegin != s) {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
        const wchar_t* p = s;
        while (*p) ++p;
        int n = (int)(p - s);
        append(s, s + n);
    }
    return this;
}

// @ 0x00686430
int* VecBuf::Init(uint32_t n, void* tag)
{
    (void)tag;
    void* p = n ? EASTL_alloc6(n, g_allocTag, 0, 0, g_fileEASTL, 0xd1) : 0;
    b = (int*)p;
    e = (int*)p;
    c = (int*)((char*)p + n);
    if (n > 0)
        MemsetT(p, 0, n);
    e = (int*)((char*)b + n);
    return (int*)this;
}

// @ 0x00686490
extern "C" int OpenRecordAsStream(int arg)
{
    int* mgr = GetManager();
    if (mgr == 0) return -1;
    int* rec = (int*)((void* (__thiscall*)(void*, int))VT(mgr)[0x58 / 4])(mgr, arg);
    if (rec == 0) return -1;
    char buf[8];
    char ok = ((char (__thiscall*)(void*, int, void*, int, int, int))VT(rec)[0x34 / 4])
                  (rec, arg, buf, 1, 6, 1);
    if (ok) {
        int* ctr = (int*)0x015fe7b8;
        *ctr = *ctr + 1;
        int* slot = ((HashMap*)0x0152b5f8)->operator[](ctr);
        slot[0] = (int)rec;
        slot[1] = 1;
        int v = ((int (__thiscall*)(void*))VT(rec)[0x18 / 4])(rec);
        *(int*)(buf + 4) = v;
        return *ctr;
    }
    return -1;
}

// @ 0x00686520
__declspec(noinline) bool DecodeRecord(void* rd, int arg, uint32_t size, uint8_t flag)
{
    // (full body not reconstructed; see partial.txt)
    int i0, i1;
    ReadInt32(rd, &i0, 1, 0);
    ReadInt32(rd, &i1, 1, 0);
    (void)size; (void)flag;
    return false;
}

// @ 0x006866f0
static inline void* RecStream(void* r)
{ return ((void* (__thiscall*)(void*))VT(r)[0x18 / 4])(r); }

// @ 0x006872f0
extern "C" void RegisterPackagesDef(void* a, void* b, int c, int d, int e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    // (full body not reconstructed; see partial.txt)
}

// @ 0x00687590
extern "C" void Thunk_687590(void* a, void* b, int c)
{
    RegisterPackages(a, b, 0, 0, c);
}

// @ 0x006875b0
extern "C" void IteratePackages(void* param)
{
    int i = 0;
    if (g_count >= 0) {
        do {
            char* e = g_array + i * 0x28;
            if (e[0] != 0 && *(int*)(e + 8) != *(int*)(e + 0xc)) {
                int flag;
                switch (i) {
                case 1: flag = 1; break;
                case 2: flag = 100; break;
                default: flag = 0; break;
                }
                RegisterPackages(param, *(void**)(e + 8), 0, 0, flag);
            }
            ++i;
        } while (i <= g_count);
    }
}

// @ 0x00687610
extern "C" void SetupResources()
{
    // (full body not reconstructed; see partial.txt)
}
