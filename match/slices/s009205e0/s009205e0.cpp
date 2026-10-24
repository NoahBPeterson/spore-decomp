// Slice s009205e0: EA::Audio::Eapd symbol/group hash tables, wchar_t path helpers,
// eastl fixed_pool / RBTreeIncrement and a couple of float range mappers.
#include "types.h"

typedef unsigned int size_t;

typedef void* HANDLE;
typedef unsigned long DWORD;

#pragma warning(disable:4035)
// EA math helper: hand-written SSE asm (cvtss2si is round-to-nearest, then bump).
__forceinline int CeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}
__forceinline int TruncToInt(float f) { __asm cvttss2si eax, f }

extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char*);
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, size_t);

void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                               const char* file, int line);   // 0x00f473a0
void  EASTL_allocator_deallocate(void* p);                     // 0x00f47380

void FUN_009223a0(int a, void* b);      // 0x9223a0 lock
void FUN_00922480();                    // 0x922480 unlock
struct EapdLock {
    int  Lock(int reason, void* name);   // 0x9223a0
    void Unlock();                       // 0x922480
};
struct RangeMapper {   // receiver arrives in ECX
    float scale;        // +0
    float growth;       // +4
    int   limit;        // +8
    int   Round1(unsigned key);                                    // 0x921360
    int   Round2(int key);                                         // 0x9213c0
    void  Map(unsigned char* out, int a, int b, int c);            // 0x921440
};
void FUN_00920340(unsigned a);          // 0x920340
void FUN_00920490(void* out, void* a, void* b); // 0x920490
void FUN_006859b0(void* a, void* b, void* c); // 0x6859b0
void FUN_00b4f930(void* a, void* b, void* c); // 0xb4f930
void* FUN_00922500(int a, int b);       // 0x922500
void  sys_gui();                        // 0xc2e4e0

extern wchar_t* g_pNullStr;             // 0x1667b88

// ---------------------------------------------------------------- path helpers
struct Range {
    wchar_t* begin;
    wchar_t* end;
    void append(const wchar_t* first, const wchar_t* last);   // 0x672750
    void appendChar(wchar_t c);                               // 0x8e3f10
};
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
Range* NormalizeSeparators(Range* r) {
    wchar_t* p = r->begin;
    if (p != r->end) {
        do {
            if (*p == L'/' || *p == L'\\')
                *p = L'\\';
            ++p;
        } while (p != r->end);
    }
    return r;
}

wchar_t* FindExtension(wchar_t* first, wchar_t* last);
// @ 0x00920ee0
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
Range* FUN_00921150(Range* out, wchar_t* first, wchar_t* last) {
    if (last == g_pNullStr) {
        wchar_t* e = first;
        while (*e != 0)
            ++e;
        last = e;
    }
    if (first == last)
        return out;
    bool alt = first < last && HasAltSeparator(first, last);
    if (!alt)
        alt = first < last && (*first == L'\\' || *first == L'/');
    if (alt) {
        if (out->begin != out->end) {
            *out->begin = 0;
            out->end = out->begin;
            out->append(first, last);
            return out;
        }
    } else if (out->begin == out->end ||
               (out->end[-1] != L'\\' && out->end[-1] != L'/')) {
        out->appendChar(L'\\');
    }
    out->append(first, last);
    return out;
}

// @ 0x00921210
void FUN_00921210(void* out, Range* r) {
    FUN_00921150((Range*)out, r->begin, r->end);
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

__declspec(noinline) unsigned* UpperBound(unsigned* first, unsigned* last, const unsigned* key);
__declspec(noinline) unsigned* LowerBound(unsigned* first, unsigned* last, const unsigned* key);

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
int RangeMapper::Round1(unsigned key) {
    unsigned* r = LowerBound(g_boundLo, g_boundHi, &key);
    unsigned v = *r;
    float f = (float)v;
    float x = f * scale;
    limit = CeilToInt(x);
    return (int)v;
}

// @ 0x009213c0
int RangeMapper::Round2(int key) {
    float f = (float)(unsigned)key;
    float t = f / scale;
    int q = TruncToInt(t);
    unsigned* r = LowerBound(g_boundLo, g_boundHi, (unsigned*)&q);
    unsigned v = *r;
    float g = (float)v;
    float x = g * scale;
    limit = CeilToInt(x);
    return (int)v;
}

// @ 0x00921380/0x14.. use shared rounding: reproduce 00921360/13c0 tails above.
// @ 0x00921440
void RangeMapper::Map(unsigned char* out, int a, int b, int c) {
    unsigned n = (unsigned)(c + b);
    if ((unsigned)limit < n) {
        if (a == 1)
            a = 0;
        float f = (float)n;
        float q = f / scale;
        float g = (float)(unsigned)a;
        if (q <= g) {
            limit = CeilToInt(g * scale);
        } else {
            float t = growth * g;
            float sel = t;
            if (sel < q)
                sel = q;
            unsigned key = (unsigned)TruncToInt(sel);
            unsigned* r = LowerBound(g_boundLo, g_boundHi, &key);
            unsigned v = *r;
            float h = (float)v;
            limit = CeilToInt(h * scale);
            out[0] = 1;
            *(int*)(out + 4) = (int)v;
            return;
        }
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
void FUN_00920560(void* out, void* key);                    // 0x920560
extern HashNode* FUN_00920560_get(void* ht, unsigned key);  // 0x920560
extern HashNode* FUN_00922500_get(void* p);                 // 0x922500
extern HashNode* FUN_00685f30_find(void* ht, unsigned key); // 0x685f30

// ---- the two Eapd hash tables whose find wrappers live at 009209c0 / 00920a70 ----
struct EapdNode {
    unsigned mKey;      // +0
    unsigned mValue;    // +4
    unsigned mExtra;    // +8
    EapdNode* mpNext;   // +0xc
};
struct EapdFind {
    EapdNode*  node;
    EapdNode** slot;
};
struct EapdEastlTable {
    unsigned    pad0;         // +0
    EapdNode**  mpBuckets;    // +4
    unsigned    mnBucketCount;// +8
    unsigned    mnSize;       // +0xc
    void find(EapdFind* out, const unsigned* key);   // 0x685f30
};

struct EapdGroupNode {
    unsigned mKey;      // +0
    unsigned mValue;    // +4
    unsigned mExtra;    // +8
    unsigned mData;     // +0xc
    EapdGroupNode* mpNext;  // +0x10
};
struct EapdGroupFind {
    EapdGroupNode*  node;
    EapdGroupNode** slot;
};
struct EapdGroupTable {
    unsigned        pad0;          // +0
    EapdGroupNode** mpBuckets;     // +4
    unsigned        mnBucketCount; // +8
    unsigned        mnSize;        // +0xc
    void Find(EapdGroupFind* out, const unsigned* key);   // 0x920560
};

// @ 0x009205e0
void* HashTable::insert(void* out, HashNode* src) {
    bool bDummy;
    ((RangeMapper*)((char*)this + 0x10))->Map((unsigned char*)&bDummy, mnBucketCount, mnSize, 1);
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
    EapdLock* lk = (EapdLock*)((char*)this + 8);
    lk->Lock(1, (void*)0x143d820);
    EapdEastlTable* t = (EapdEastlTable*)((char*)this + 0x108);
    EapdFind it;
    t->find(&it, &key);
    EapdNode* end = t->mpBuckets[t->mnBucketCount];
    EapdNode* p = it.node;
    unsigned* found = 0;
    if (p != end) {
        while (true) {
            if (p->mKey != key)
                break;
            if (found == 0 || found[1] < p->mExtra)
                found = &p->mValue;
            p = p->mpNext;
            if (p == 0) {
                EapdNode** slot = it.slot + 1;
                do {
                    p = *slot;
                    ++slot;
                } while (p == 0);
            }
            if (p == end)
                break;
        }
    }
    unsigned r = 0;
    if (found != 0)
        r = *found;
    lk->Unlock();
    return r;
}

// @ 0x00920a70
unsigned HashTable::find2(unsigned key, unsigned* out) {
    EapdLock* lk = (EapdLock*)((char*)this + 8);
    lk->Lock(1, (void*)0x143d820);
    EapdGroupTable* t = (EapdGroupTable*)((char*)this + 0x128);
    EapdGroupFind it;
    t->Find(&it, &key);
    EapdGroupNode* end = t->mpBuckets[t->mnBucketCount];
    EapdGroupNode* p = it.node;
    unsigned* found = 0;
    if (p != end) {
        while (true) {
            if (p->mKey != key)
                break;
            if (found == 0 || found[1] < p->mExtra)
                found = &p->mValue;
            p = p->mpNext;
            if (p == 0) {
                EapdGroupNode** slot = it.slot + 1;
                do {
                    p = *slot;
                    ++slot;
                } while (p == 0);
            }
            if (p == end)
                break;
        }
    }
    unsigned r = 0;
    if (found != 0) {
        if (out != 0)
            *out = found[2];
        r = *found;
    }
    lk->Unlock();
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
