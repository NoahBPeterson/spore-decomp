// Slice s006870a0: SP package/resource registration helpers (0x006870a0..0x00687bc0).
// Module compiled /O2 /MD /Gy /EHsc /TP (no SSE).
#include "types.h"

static inline void** VT(void* p) { return *(void***)p; }

extern "C" void* MemcpyT(void*, const void*, uint32_t);           // 0x011e0744
extern "C" void  EASTL_dealloc(void*);                            // 0x0f47380
extern "C" void* EASTL_alloc6(uint32_t, void*, uint32_t, uint32_t, const char*, uint32_t); // 0x0f473a0
extern "C" char  g_allocTag[];
extern "C" char  g_fileEASTL[];
extern "C" void __cdecl RegisterPackages(void*, void*, int, int, int); // 0x06872f0
extern "C" void __cdecl AppendWide(void*, const wchar_t*, const wchar_t*); // 0x042f9d0

// globals used by these helpers
extern "C" int  g_count;                    // 0x0152b348
extern "C" char* g_array;                   // 0x015fea00
extern "C" char* g_arrayEnd;                // 0x015fea04

// =====================================================================
// @ 0x006870a0  fill/insert loop into a 0x28-stride element vector (partial)
// =====================================================================
struct Vec28 {
    char* b; char* e; char* c;
    void ResizeLoop(int pos, uint32_t n, void* val);   // 0x06870a0 (partial)
    void DestroyRangeChunk(char* first, char* last);   // 0x0687050
    void Reserve(uint32_t n);                          // 0x0687ab0 (below)
};


// =====================================================================
// @ 0x006872f0  anonymous_namespace::RegisterPackages (partial)
// =====================================================================
extern "C" void RegisterPackagesDef(void* a, void* b, int c, int d, int e) {
    (void)a; (void)b; (void)c; (void)d; (void)e;
    // (full body not reconstructed; see partial.txt)
}

// =====================================================================
// @ 0x00687590  thin thunk: RegisterPackages(a,b,0,0,c)
// =====================================================================
extern "C" void Thunk_687590(void* a, void* b, int c) {
    RegisterPackages(a, b, 0, 0, c);
}

// =====================================================================
// @ 0x006875b0  iterate array, register each populated entry
// =====================================================================
extern "C" void IteratePackages(void* param) {
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

// =====================================================================
// @ 0x00687610  SP::SetupResources (partial)
// =====================================================================
extern "C" void SetupResources() {
    // (full body not reconstructed; see partial.txt)
}

// =====================================================================
// @ 0x00687a00  append range to global vector
// =====================================================================
struct VecU32G { uint32_t* b; uint32_t* e; uint32_t* c;
    void InsertRange(uint32_t* first, uint32_t* last, uint32_t* dst); // 0x06ad970
};
extern "C" void Thunk_687a00(int n, uint32_t* base) {
    ((VecU32G*)0x0152b5a0)->InsertRange(base, base + n, base);
}

// =====================================================================
// @ 0x00687a20  iterate array, push strings/ids into two vectors
// =====================================================================
struct VecWStr { void* b; void* e; void* c;
    void push_back(const void* p);          // 0x0553f10
};
struct VecU32 { uint32_t* b; uint32_t* e; uint32_t* c;
    void DoIns(uint32_t* pos, const uint32_t* val); // 0x04558a0
};
extern "C" void Iterate2(VecWStr* v0, VecU32* v1) {
    if (g_count >= 0) {
        for (int i = 0; i <= g_count; ++i) {
            char* e = g_array + i * 0x28;
            if (e[0] != 0 && *(int*)(e + 4) != 0 &&
                *(int*)(e + 0x18) != *(int*)(e + 0x1c)) {
                v0->push_back(e + 0x18);
                uint32_t val = *(uint32_t*)(e + 4);
                uint32_t* p = v1->e;
                if (p < v1->c) {
                    v1->e = p + 1;
                    if (p) *p = val;
                } else {
                    v1->DoIns(p, &val);
                }
            }
        }
    }
}

// =====================================================================
// @ 0x00687ab0  reserve n 0x28-stride elements
// =====================================================================
struct Elem19 {
    uint8_t flag;
    uint8_t pad[3];
    uint32_t f4;
    void* a0; void* a1; void* a2;
    void* b0; void* b1; void* b2;
};
void Vec28::Reserve(uint32_t n) {
    int size = (int)(e - b) / 0x28;
    if ((uint32_t)size < n) {
        Elem19 tmp;
        tmp.flag = 0;
        tmp.f4 = 0;
        tmp.a0 = (void*)0x01667bac; tmp.a1 = (void*)0x01667bac; tmp.a2 = (void*)0x01667bae;
        tmp.b0 = (void*)0x01667bac; tmp.b1 = (void*)0x01667bac; tmp.b2 = (void*)0x01667bae;
        ResizeLoop((int)e, n - size, &tmp);
    } else {
        DestroyRangeChunk(b + n * 0x28, e);
    }
}

// =====================================================================
// @ 0x00687bc0  set element count cap; returns index or -1
// =====================================================================
extern "C" int SetCount(int n) {
    if (n > g_count) {
        ((Vec28*)&g_array)->Reserve((uint32_t)(n + 1));
        g_count = n;
    }
    if (n == 2) return -1;
    int r = -1;
    int count = (int)(g_arrayEnd - g_array) / 0x28;
    if (n < count) r = n;
    return r;
}
