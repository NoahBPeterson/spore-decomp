// Slice s009205e0: EA::Audio::Eapd symbol/group hash tables, wchar_t path helpers,
// eastl fixed_pool / RBTreeIncrement and a couple of float range mappers.
#include "types.h"

typedef unsigned int size_t;

typedef void* HANDLE;
typedef unsigned long DWORD;

extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char*);
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, size_t);

void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                               const char* file, int line);   // 0x00f473a0
void  EASTL_allocator_deallocate(void* p);                     // 0x00f47380

void FUN_009223a0(int a, void* b);      // 0x9223a0 lock
void FUN_00922480();                    // 0x922480 unlock
void FUN_00921440(void* out, unsigned a, unsigned b, int c);  // 0x921440
void FUN_00920340(unsigned a);          // 0x920340
void FUN_00920560(void* out, void* key);  // 0x920560
void FUN_00920490(void* out, void* a, void* b); // 0x920490
void FUN_008e3f10(wchar_t c);           // 0x8e3f10 append char
void FUN_006859b0(void* a, void* b, void* c); // 0x6859b0
void FUN_00b4f930(void* a, void* b, void* c); // 0xb4f930
void* FUN_00922500(int a, int b);       // 0x922500
void  sys_gui();                        // 0xc2e4e0

extern wchar_t* g_pNullStr;             // 0x1667b88

// ---------------------------------------------------------------- path helpers
struct Range { wchar_t* begin; wchar_t* end; };
void FUN_00920f30(Range* r, char flag);
wchar_t* FindExtension(wchar_t* first, wchar_t* last);

// @ 0x00920c20
bool HasAltSeparator(wchar_t* first, wchar_t* last) {
    for (; first < last; ++first) {
        wchar_t c = *first;
        if (c == L':')
            return true;
        if (c == L'\\' || c == L'/')
            break;
    }
    return false;
}

// @ 0x00920f00
void NormalizeSeparators(Range* r) {
    wchar_t* p = r->begin;
    if (p != r->end) {
        do {
            if (*p == L'/' || *p == L'\\')
                *p = L'\\';
            ++p;
        } while (p != r->end);
    }
}

// @ 0x00920ee0
wchar_t* FindExtension(wchar_t* first, wchar_t* last);
void NormalizeSeparators2(Range* r) {
    FindExtension(r->begin, r->end);
}

// @ 0x00920c60
wchar_t* SkipComponent(wchar_t* first, wchar_t* last) {
    if (last == g_pNullStr) {
        wchar_t c = *first;
        last = first;
        while (c != 0) {
            ++last;
            c = *last;
        }
    }
    if ((first + 2 <= last) && (first[0] == L'\\' || first[0] == L'/') &&
        (first[1] == L'\\' || first[1] == L'/'))
        first += 2;
    if (first < last) {
        while (true) {
            wchar_t c = *first;
            if (c == L'\\' || c == L'/')
                break;
            ++first;
            if (c == L':')
                break;
            if (last <= first)
                return first;
        }
        if (first < last && (*first == L'\\' || *first == L'/'))
            ++first;
    }
    return first;
}

// @ 0x00920d00
wchar_t* SkipComponentBack(wchar_t* first, wchar_t* last) {
    if (last == g_pNullStr) {
        wchar_t c = *first;
        last = first;
        while (c != 0) {
            ++last;
            c = *last;
        }
    }
    if (first < last) {
        if (last[-1] == L'\\' || last[-1] == L'/')
            --last;
        if (first < last) {
            if (last[-1] == L':')
                --last;
            while (first < last && last[-1] != L'\\' && last[-1] != L'/' && last[-1] != L':')
                --last;
        }
    }
    if (last == first + 2 && (first[0] == L'\\' || first[0] == L'/') &&
        (first[1] == L'\\' || first[1] == L'/'))
        last = first;
    return last;
}

// @ 0x00920da0
wchar_t* ComponentAt(wchar_t* first, wchar_t* last, int index) {
    if (index >= 0) {
        wchar_t* p = first;
        for (index = index + 1; p < last && index > 0; --index)
            p = SkipComponent(p, last);
        if (index == 0 && first < p && (p[-1] == L'\\' || p[-1] == L'/'))
            --p;
        return p;
    }
    if (first < last) {
        while (index = index + 1, index < 0) {
            last = SkipComponentBack(first, last);
            if (last <= first)
                return last;
        }
        if (first < last && (last[-1] == L'\\' || last[-1] == L'/'))
            --last;
    }
    return last;
}

// @ 0x00920e30
wchar_t* FindExtension(wchar_t* first, wchar_t* last) {
    if (last == g_pNullStr) {
        wchar_t c = *first;
        last = first;
        while (c != 0) {
            ++last;
            c = *last;
        }
    }
    if (first < last && (last[-1] == L'\\' || last[-1] == L'/'))
        return last;
    if ((first + 2 <= last) && (first[0] == L'\\' || first[0] == L'/') &&
        (first[1] == L'\\' || first[1] == L'/'))
        first = SkipComponent(first, last);
    wchar_t* p = last - 1;
    while (first <= p) {
        wchar_t c = *p;
        if (c == L'\\' || c == L'/' || c == L':')
            break;
        if (c == L'.')
            return p;
        if (--p < first)
            return last;
    }
    return last;
}

// @ 0x00921150
void FUN_00921150(void* out, wchar_t* first, wchar_t* last) {
    if (last == g_pNullStr) {
        wchar_t c = *first;
        last = first;
        while (c != 0) {
            ++last;
            c = *last;
        }
    }
    if (first == last)
        return;
    if (first < last && (HasAltSeparator(first, last) ||
        (first < last && (*first == L'\\' || *first == L'/')))) {
        if (*(void**)((char*)out) != *(void**)((char*)out + 4)) {
            **(wchar_t**)out = 0;
            *(wchar_t**)((char*)out + 4) = *(wchar_t**)out;
            return;
        }
    } else if (*(void**)out == *(void**)((char*)out + 4) ||
               (*(wchar_t**)((char*)out + 4))[-1] != L'\\' &&
               (*(wchar_t**)((char*)out + 4))[-1] != L'/') {
        FUN_008e3f10(L'\\');
    }
}

// @ 0x00921210
void FUN_00921210(void* out, Range* r) {
    FUN_00921150(out, r->begin, r->end);
    FUN_00920f30((Range*)out, 1);
}

// @ 0x00921250
void DebugPrint(const char* s) {
    OutputDebugStringA(s);
    sys_gui();
}

// @ 0x00921260
struct FixedPool {
    void* mpHead;
    void init(unsigned char* p, unsigned count, unsigned blockSize, unsigned align, unsigned extra);
};

// @ 0x00921260
void FixedPool::init(unsigned char* p, unsigned count, unsigned blockSize, unsigned align, unsigned extra) {
    if (align < 1)
        align = 1;
    if (blockSize < 4)
        blockSize = ~(align - 1) & (align + 3);
    unsigned char* head = (unsigned char*)(((unsigned)p + align - 1) & ~(align - 1));
    mpHead = head;
    unsigned char* end = (unsigned char*)((count / blockSize - 1) * blockSize + (unsigned)p);
    while (head < end) {
        *(unsigned char**)head = head + blockSize;
        head += blockSize;
    }
    *(unsigned char**)head = 0;
}

// @ 0x009212c0  first element strictly greater than key
unsigned* UpperBound(unsigned* first, unsigned* last, const unsigned* key) {
    int n = (int)(last - first);
    if (n > 0) {
        unsigned k = *key;
        do {
            int half = n >> 1;
            if (!(k < first[half])) {
                first = first + half + 1;
                half = n + (-1 - half);
            }
            n = half;
        } while (n > 0);
    }
    return first;
}

// @ 0x00921300  first element not less than key
unsigned* LowerBound(unsigned* first, unsigned* last, const unsigned* key) {
    int n = (int)(last - first);
    if (n > 0) {
        unsigned k = *key;
        do {
            int half = n >> 1;
            if (first[half] < k) {
                first = first + half + 1;
                half = n + (-1 - half);
            }
            n = half;
        } while (n > 0);
    }
    return first;
}

extern unsigned g_boundLo[];   // 0x143d850
extern unsigned g_boundHi[];   // 0x143dc50
extern float g_mathConst;      // 0x13f4fd0 (2^32)

// @ 0x00921340
int FUN_00921340(unsigned key) {
    unsigned* p = UpperBound(g_boundLo, g_boundHi, &key);
    return (int)p[-1];
}

// @ 0x00921360
int FUN_00921360(float* p, unsigned key) {
    unsigned* r = LowerBound(g_boundLo, g_boundHi, &key);
    int v = (int)*r;
    float f = (float)v;
    if (v < 0)
        f += g_mathConst;
    float x = f * p[0];
    int i = (int)x;
    if ((float)i < x)
        ++i;
    p[2] = (float)i;
    return v;
}

// @ 0x009213c0
int FUN_009213c0(float* p, int key) {
    float f = (float)key;
    if (key < 0)
        f += g_mathConst;
    unsigned q = (unsigned)(int)(f / p[0]);
    unsigned* r = LowerBound(g_boundLo, g_boundHi, &q);
    int v = (int)*r;
    float g = (float)v;
    if (v < 0)
        g += g_mathConst;
    float x = g * p[0];
    int i = (int)x;
    if ((float)i < x)
        ++i;
    p[2] = (float)i;
    return v;
}

// @ 0x00921380/0x14.. use shared rounding: reproduce 00921360/13c0 tails above.
// @ 0x00921440
void FUN_00921440(float* p, unsigned char* out, int a, float b, float c) {
    unsigned n = (unsigned)(int)((int)c + (int)b);
    if ((unsigned)(int)p[2] < n) {
        if (a == 1)
            a = 0;
        float f = (float)(int)n;
        if ((int)n < 0)
            f += g_mathConst;
        float q = f / p[0];
        float g = (float)a;
        if (a < 0)
            g += g_mathConst;
        if (g < q) {
            float t = p[1] * g;
            float* sel = &t;
            if (p[1] * g <= q)
                sel = &q;
            unsigned key = (unsigned)(int)*sel;
            unsigned* r = LowerBound(g_boundLo, g_boundHi, &key);
            int v = (int)*r;
            float h = (float)v;
            if (v < 0)
                h += g_mathConst;
            float x = h * p[0];
            int i = (int)x;
            if ((float)i < x)
                ++i;
            p[2] = (float)i;
            out[0] = 1;
            *(int*)(out + 4) = v;
            return;
        }
        float x = g * p[0];
        int i = (int)x;
        if ((float)i < x)
            ++i;
        p[2] = (float)i;
    }
    *(int*)(out + 4) = 0;
    out[0] = 0;
}

// @ 0x00921580
struct RBNode { RBNode* mpRight; RBNode* mpLeft; RBNode* mpParent; };

RBNode* RBTreeIncrement(RBNode* n) {
    if (n->mpRight != 0) {
        n = n->mpRight;
        while (n->mpLeft != 0)
            n = n->mpLeft;
        return n;
    }
    RBNode* p = n->mpParent;
    while (n == p->mpRight) {
        n = p;
        p = p->mpParent;
    }
    if (n->mpRight != p)
        n = p;
    return n;
}
// ---------------------------------------------------------------- Eapd hash tables
struct HashNode { unsigned mKey; unsigned mValue; void* pad08; HashNode* mpNext; };
struct HashTable {
    HashNode** mpBuckets;   // +0
    unsigned mnBucketCount; // +4
    unsigned mnSize;        // +8
    void* pad0c;
    void* insert(void* out, HashNode* src);   // @ 009205e0
    unsigned lookup(unsigned key);            // @ 009209c0
    unsigned find2(unsigned key, unsigned* out); // @ 00920a70
};

struct EapdSymbolTable {
    char pad00[0x10c];
    void* mpEapdSymbols;   // +0x10c
    unsigned mnBuckets1;   // +0x110
    char pad114[0x1c];
    void* mpGroups;        // +0x12c
    unsigned mnBuckets2;   // +0x130
    void ctor();                                  // @ 009206d0
    bool LoadSymbols(void* stream);               // @ 00920780
    bool LoadGroups(void* stream, void* owner);   // @ 00920b30
};

extern HashNode* FUN_006859b0_ret(void* a, void* b, void* c);
extern HashNode* FUN_00920560_get(void* ht, unsigned key);  // 0x920560
extern HashNode* FUN_00922500_get(void* p);                 // 0x922500
extern HashNode* FUN_00685f30_find(void* ht, unsigned key); // 0x685f30

// @ 0x009205e0
void* HashTable::insert(void* out, HashNode* src) {
    bool bDummy;
    FUN_00921440(&bDummy, mnBucketCount, mnSize, 1);
    if (bDummy)
        FUN_00920340(mnSize);
    const unsigned char* s = (const unsigned char*)(size_t)src->mKey;
    unsigned h = 0x811c9dc5;
    unsigned char c = *s;
    while (c != 0) {
        ++s;
        h = h * 0x1000193 ^ c;
        c = *s;
    }
    unsigned idx = h % mnSize;
    HashNode* n = (HashNode*)EASTL_allocator_allocate(0x14, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (n != 0) {
        *(unsigned*)((char*)n + 0) = *(unsigned*)((char*)src + 0);
        *(unsigned*)((char*)n + 4) = *(unsigned*)((char*)src + 4);
        *(unsigned*)((char*)n + 8) = *(unsigned*)((char*)src + 8);
        *(unsigned*)((char*)n + 0xc) = *(unsigned*)((char*)src + 0xc);
    }
    n->mpNext = 0;
    HashNode* head = mpBuckets[idx];
    if (head != 0) {
        for (HashNode* p = head; p != 0; p = p->mpNext) {
            if (p->mKey == src->mKey) {
                n->mpNext = p->mpNext;
                p->mpNext = n;
                goto done;
            }
        }
    }
    n->mpNext = head;
    mpBuckets[idx] = n;
done:
    ++mnSize;
    *(HashNode**)out = n;
    *(void**)((char*)out + 4) = &mpBuckets[idx];
    return out;
}

// @ 0x009206d0
void EapdSymbolTable::ctor() {
    FUN_00922500(0, 1);
    *(unsigned*)((char*)this + 0x118) = 0x3f800000;
    *(unsigned*)((char*)this + 0x11c) = 0x40000000;
    *(unsigned*)((char*)this + 0x114) = 0;
    *(unsigned*)((char*)this + 0x120) = 0;
    *(unsigned*)((char*)this + 0x110) = 1;
    *(void**)((char*)this + 0x10c) = (void*)0x154df28;
    *(unsigned*)((char*)this + 0x138) = 0x3f800000;
    *(unsigned*)((char*)this + 0x13c) = 0x40000000;
    *(unsigned*)((char*)this + 0x134) = 0;
    *(unsigned*)((char*)this + 0x140) = 0;
    *(void**)((char*)this + 0x12c) = (void*)0x154df28;
    *(unsigned*)((char*)this + 0x130) = 1;
}

// @ 0x00920780
bool EapdSymbolTable::LoadSymbols(void* stream) {
    FUN_009223a0(2, (void*)0x143d820);
    unsigned char buf[0x80];
    unsigned n = 0;
    (void)buf;
    for (unsigned i = 0; i < n; ++i) {
        HashNode* sym = FUN_00922500_get(&buf[i * 4]);
        if (sym != 0) {
            HashNode* node = FUN_00920560_get(&buf[i * 4], 0);
            (void)node;
        }
    }
    FUN_00922480();
    return true;
}

// @ 0x009209c0
unsigned HashTable::lookup(unsigned key) {
    FUN_009223a0(1, (void*)0x143d820);
    HashNode* found = 0;
    HashNode* p = FUN_00685f30_find(this, key);
    while (p != 0) {
        if (p->mKey != key)
            break;
        if (found == 0 || found->mValue < (unsigned)(size_t)p->pad08)
            found = p;
        p = p->mpNext;
    }
    unsigned r = 0;
    if (found != 0)
        r = found->mKey;
    FUN_00922480();
    return r;
}

// @ 0x00920a70
unsigned HashTable::find2(unsigned key, unsigned* out) {
    FUN_009223a0(1, (void*)0x143d820);
    HashNode* found = 0;
    HashNode* p = FUN_00920560_get(this, key);
    while (p != 0) {
        if (p->mKey != key)
            break;
        if (found == 0 || found->mValue < (unsigned)(size_t)p->pad08)
            found = p;
        p = p->mpNext;
    }
    unsigned r = 0;
    if (found != 0) {
        if (out)
            *out = (unsigned)(size_t)found->pad08;
        r = found->mKey;
    }
    FUN_00922480();
    return r;
}

// @ 0x00920b30
bool EapdSymbolTable::LoadGroups(void* stream, void* owner) {
    FUN_009223a0(2, (void*)0x143d820);
    (void)stream;
    (void)owner;
    FUN_00922480();
    return true;
}

// @ 0x00920f30  (normalize a path range: collapse separators, "." and "..")
void FUN_00920f30(Range* r, char flag) {
    wchar_t* src = r->begin;
    wchar_t* last = r->end;
    wchar_t* dst = src;
    bool bAbsolute = (src + 2 <= last && (src[0] == L'\\' || src[0] == L'/') &&
                      (src[1] == L'\\' || src[1] == L'/'))
                     || HasAltSeparator(src, last);
    while (src < last) {
        wchar_t c = *src;
        if (c == L'\\' || c == L'/') {
            *dst++ = flag ? L'\\' : c;
            ++src;
            continue;
        }
        if (src + 2 <= last && src[0] == L'.' && (src[1] == L'\\' || src[1] == L'/')) {
            src += 2;
            continue;
        }
        if (src + 3 <= last && src[0] == L'.' && src[1] == L'.' &&
            (src[2] == L'\\' || src[2] == L'/')) {
            if (dst > r->begin) {
                wchar_t* p = SkipComponentBack(r->begin, dst);
                if (p > r->begin || !bAbsolute)
                    dst = p;
            }
            src += 3;
            continue;
        }
        *dst++ = *src++;
    }
    if (dst != last) {
        memmove(dst, last, 2);
        r->end = (wchar_t*)((char*)r->end + ((char*)last - (char*)dst));
    }
}
