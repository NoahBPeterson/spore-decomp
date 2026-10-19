// Slice s006870a0: SP package/resource registration helpers (0x006870a0..0x00687bc0).
// Module compiled /O2 /MD /Gy /EHsc /TP (no SSE).
#include "types.h"

static inline void** VT(void* p) { return *(void***)p; }

extern "C" void* MemcpyT(void*, const void*, uint32_t);           // 0x011e0744
extern "C" void  EASTL_dealloc(void*);                            // 0x0f47380
extern "C" void* EASTL_alloc6(uint32_t, void*, uint32_t, uint32_t, const char*, uint32_t); // 0x0f473a0
extern "C" char  g_allocTag[];   // 0x013ebc58 "App"
extern "C" char  g_fileEASTL[];  // 0x013ebb38
extern "C" void __cdecl RegisterPackages(void*, void*, int, int, int); // 0x06872f0
extern "C" void __cdecl AppendWide(void*, const wchar_t*, const wchar_t*); // 0x042f9d0

// globals used by these helpers
extern "C" int  g_count;                    // 0x0152b348
extern "C" char* g_array;                   // 0x015fea00
extern "C" char* g_arrayEnd;                // 0x015fea04

// =====================================================================
// 0x006870a0  vector<Elem28>::DoInsertValues(position, n, value)
// Elem28 = {u8 flag, u32, two 16-byte wide strings}, 0x28 bytes.
// =====================================================================
struct Elem28 {
    uint8_t flag;
    uint8_t pad[3];
    uint32_t f4;
    uint32_t a[4];
    uint32_t b[4];
    Elem28(const Elem28& x);   // 0x00685a60 (thiscall, ret 4)
    ~Elem28();                 // 0x00d167e0
};
struct Elem28Out {
    Elem28* p;
    Elem28Out(Elem28* x) : p(x) {}
};
Elem28Out __cdecl UninitCopy28(Elem28* first, Elem28* last, Elem28* dest);       // 0x00685b40
void      __cdecl UninitFillN28(Elem28* first, uint32_t n, const Elem28& v);     // 0x00685bc0
Elem28*   __cdecl UninitReloc28(Elem28* first, Elem28* last, Elem28* dest);      // 0x00685c40
Elem28*   __cdecl DestroyRange28(Elem28* first, Elem28* last, Elem28* out);      // 0x00685cd0
Elem28*   __cdecl CopyBack28(Elem28* first, Elem28* last, Elem28* dstLast);      // 0x00686150
void      __cdecl Fill28(Elem28* first, Elem28* last, const Elem28& v);          // 0x00686290

struct Vec28 {
    Elem28* b; Elem28* e; Elem28* c;
    void ResizeLoop(Elem28* position, uint32_t n, const Elem28& value);   // 0x06870a0
    void DestroyRangeChunk(char* first, char* last);   // 0x0687050
    void Reserve(uint32_t n);                          // 0x0687ab0 (below)
};

// @ 0x006870a0
void Vec28::ResizeLoop(Elem28* position, uint32_t n, const Elem28& value) {
    {
        if ((uint32_t)(c - e) >= n) {
          if (n != 0) {
            const Elem28 temp(value);
            const uint32_t nElementsAfter = (uint32_t)(e - position);
            Elem28* pOldEnd = e;
            if (nElementsAfter > n) {
                UninitCopy28(e - n, e, e);
                e += n;
                CopyBack28(position, pOldEnd - n, pOldEnd);
                Fill28(position, position + n, temp);
            } else {
                UninitFillN28(e, n - nElementsAfter, temp);
                e += n - nElementsAfter;
                UninitCopy28(position, pOldEnd, e);
                e += nElementsAfter;
                Fill28(position, pOldEnd, temp);
            }
          }
        } else {
            const uint32_t nPrevSize = (uint32_t)(e - b);
            const uint32_t nGrowSize = nPrevSize ? nPrevSize * 2 : 1;
            const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
            Elem28* pNewData = nNewSize ? (Elem28*)EASTL_alloc6(nNewSize * sizeof(Elem28), g_allocTag, 0, 0, g_fileEASTL, 0xd1) : 0;
            Elem28* pNewEnd = UninitReloc28(b, position, pNewData);
            DestroyRange28(b, position, pNewData);
            UninitFillN28(pNewEnd, n, value);
            pNewEnd += n;
            pNewEnd = UninitReloc28(position, e, pNewEnd);
            DestroyRange28(position, e, pNewEnd);
            if (b && ((int*)b)[-1] != 0)
                EASTL_dealloc(b);
            b = pNewData;
            e = pNewEnd;
            c = pNewData + nNewSize;
        }
    }
}

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
    int size = (int)((char*)e - (char*)b) / 0x28;
    if ((uint32_t)size < n) {
        Elem19 tmp;
        tmp.flag = 0;
        tmp.f4 = 0;
        tmp.a0 = (void*)0x01667bac; tmp.a1 = (void*)0x01667bac; tmp.a2 = (void*)0x01667bae;
        tmp.b0 = (void*)0x01667bac; tmp.b1 = (void*)0x01667bac; tmp.b2 = (void*)0x01667bae;
        ResizeLoop(e, n - size, *(Elem28*)&tmp);
    } else {
        DestroyRangeChunk((char*)b + n * 0x28, (char*)e);
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
