// Slice s0056fb90: SP::Traits cRigBlockTag BlockKey/vector_set hashtable helpers.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int size_t;
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                                          const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* EASTL_Allocate(void* allocator, size_t size, int align, int flags);

// ---------------------------------------------------------------- hashtable/vector helpers
struct UnkClass_0056fb90 { void Method(void* a, void* b); };          // @ 0x0056fb90
void UnkClass_0056fb90::Method(void*, void*) { /* partial */ }

struct UnkClass_0056fe60 { void Method(void* a); };                   // @ 0x0056fe60
void UnkClass_0056fe60::Method(void*) { /* partial */ }

struct UnkClass_0056fee0 { void Method(void* a); };                   // @ 0x0056fee0
void UnkClass_0056fee0::Method(void*) { /* partial */ }

struct Key { uint32_t a; uint32_t b; };
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void assign(wchar_t* p, wchar_t* q);   // @ 0x00423650
};
struct StreamMeta {
    float f;                               // +0
    WStr str;                              // +4
    StreamMeta(const StreamMeta& s) { f = s.f; if (&str != &s.str) str.assign(s.str.mpBegin, s.str.mpEnd); }
};
struct StreamElem {
    Key key;                               // +0
    StreamMeta meta;                       // +8   (size 0x1c)
    StreamElem(const StreamElem& src);     // @ 0x00570140
};

StreamElem::StreamElem(const StreamElem& src) : key(src.key), meta(src.meta)
{
}

struct Pair8 { uint32_t a; uint32_t b; };
inline bool LessU32(uint32_t a, uint32_t b) { return a < b; }
Pair8* LowerBoundPair(Pair8* first, Pair8* last, const Pair8* key);   // @ 0x005701b0
Pair8* LowerBoundPair(Pair8* first, Pair8* last, const Pair8* key)
{
    int n = (int)(last - first);
    ScratchSlots<1>();
    while (n > 0) {
        Pair8* it = first;
        int half = n >> 1;
        it = it + half;
        if (LessU32(it->a, key->a)) {
            it = it + 1;
            first = it;
            n = n - (half + 1);
        }
        else {
            n = half;
        }
    }
    return first;
}

struct Key1c { uint32_t a; uint32_t b; };
struct Elem1c {
    char pad[0x1c];
    bool operator<(const Key1c& k) const;   // @ 0x005715d0
};
Elem1c* LowerBound1c(Elem1c* first, Elem1c* last, Key1c* key);        // @ 0x0056fe60
Elem1c* LowerBound1c(Elem1c* first, Elem1c* last, Key1c* key)
{
    // Names chosen from od_names.py fit 5 to reproduce the original /Od slot order.
    int it = (int)((char*)last - (char*)first) / 0x1c;
    ScratchSlots<1>();
    while (it > 0) {
        Elem1c* n28 = first;
        int v13 = it >> 1;
        n28 = n28 + v13;
        Elem1c* v28 = n28;
        if ((*v28).operator<(*key)) {
            n28 = n28 + 1;
            first = n28;
            it = it - (v13 + 1);
        }
        else {
            it = v13;
        }
    }
    return first;
}

struct UnkClass_00570230 { void Method(void* a); };                   // @ 0x00570230
void UnkClass_00570230::Method(void*) { /* partial */ }

void* MoveDestroyRange(void* first, void* last, void* dst);           // @ 0x005702c0
void* MoveDestroyRange(void* first, void* last, void* dst)
{
    void* r = 0;
    for (char* p = (char*)first; p != last; p += 0x1c)
        dst = (char*)dst + 0x1c;
    return r;
}

struct UnkClass_00570330 { void Method(void* a); };                   // @ 0x00570330
void UnkClass_00570330::Method(void*) { /* partial */ }

struct UnkClass_00570400 { void Method(void* a, void* b, void* c); }; // @ 0x00570400
void UnkClass_00570400::Method(void*, void*, void*) { /* partial */ }

extern void* g_015e4a1c;
void UnkInsert_00570480(int key, bool flag);                          // @ 0x00570480
void UnkInsert_00570480(int key, bool flag)
{
    /* partial: dispatches to one of two global-singleton methods */
    (void)key; (void)flag;
}

struct UnkClass_005704c0 { void Method(void* a); };                   // @ 0x005704c0
void UnkClass_005704c0::Method(void*) { /* partial */ }

// ---------------------------------------------------------------- object with two sub-inits
struct Sub { void Init(); };                                          // @ 0x00571640
struct Big {
    Sub a;                                  // +0
    char padA[0x1c - 1];                    // +1
    Sub b;                                  // +0x1c
    char padB[0x38 - 0x1c - 1];             // +0x1d
    float vx, vy, vz;                       // +0x38
    char padC[0x50 - 0x44];                 // +0x44
    bool flag;                              // +0x50
    char padD[3];                           // +0x51
    int value;                              // +0x54
    Big* Init();                            // @ 0x00570870
};

Big* Big::Init()
{
    a.Init();
    b.Init();
    float* pVec = &vx;
    int tmp;
    ((int*)pVec)[0] = 0;
    ((int*)pVec)[1] = 0;
    ((int*)pVec)[2] = 0;
    flag = false;
    value = 0;
    return this;
}

struct UnkClass_005708d0 { void Method(void* a); };                   // @ 0x005708d0
void UnkClass_005708d0::Method(void*) { /* partial */ }
