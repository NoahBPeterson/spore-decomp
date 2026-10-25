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
extern "C" int __cdecl strcmp(const char*, const char*);

void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                               const char* file, int line);   // 0x00f473a0
void  EASTL_allocator_deallocate(void* p);                     // 0x00f47380

void FUN_009223a0(int a, void* b);      // 0x9223a0 lock
void FUN_00922480();                    // 0x922480 unlock
struct EapdLock {
    int  mLockWord;                      // +0
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
Range* FUN_00920f30(Range* r, char flag);
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
struct HashNode;
struct SymbolNode;

// 8-byte hash iterator; non-POD so the compiler returns it through a hidden pointer,
// exactly like the original (member call with `this` + 3 stack words, `ret 0xc`).
struct HashIter {
    HashNode*  mpNode;      // +0
    HashNode** mpSlot;      // +4
    HashIter() {}
    HashIter(const HashIter& o) : mpNode(o.mpNode), mpSlot(o.mpSlot) {}
};
struct SymbolIter {
    SymbolNode*  mpNode;    // +0
    SymbolNode** mpSlot;    // +4
    SymbolIter() {}
    SymbolIter(const SymbolIter& o) : mpNode(o.mpNode), mpSlot(o.mpSlot) {}
};

// Group entries are keyed by an interned name pointer and hashed on its contents.
struct HashValue {
    const char* mpName;     // +0
    void*       mpStream;   // +4
    void*       mpOwner;    // +8
    unsigned    mKey;       // +0xc
};
struct HashNode {
    const char* mpName;     // +0
    void*       mpStream;   // +4
    void*       mpOwner;     // +8
    unsigned    mKey;       // +0xc
    HashNode*   mpNext;     // +0x10
};

// Symbol entries are keyed by a plain integer id.
struct SymbolValue {
    unsigned    mKey;       // +0
    void*       mpStream;   // +4
    void*       mpOwner;    // +8
};
struct SymbolNode {
    unsigned    mKey;       // +0
    void*       mpStream;   // +4
    void*       mpOwner;    // +8
    SymbolNode* mpNext;     // +0xc
};

struct HashTable {
    void*        mpUnknown0;    // +0
    HashNode**   mpBuckets;     // +4
    unsigned     mnBucketCount; // +8
    unsigned     mnSize;        // +0xc
    RangeMapper  mRangeMap;     // +0x10
    HashIter     insert(const HashValue& value, bool bFlag);  // @ 009205e0
    void         rehash(unsigned newSize);                    // 0x920340
    void         find(HashIter* out, const char* const* key); // 0x920560
    HashIter     erase(HashIter pos);                         // 0xb4f930
    unsigned     lookup(unsigned key);                        // @ 009209c0
    unsigned     find2(unsigned key, unsigned* out);          // @ 00920a70
};

struct SymbolHashTable {
    char         pad0[4];       // +0
    SymbolNode** mpBuckets;     // +4
    unsigned     mnBucketCount; // +8
    unsigned     mnSize;        // +0xc
    RangeMapper  mRangeMap;     // +0x10
    SymbolIter   insert(const SymbolValue& value, bool bFlag); // 0x920490
    SymbolIter   erase(SymbolIter pos);                        // 0x6859b0
};

struct EapdStream {
    virtual void        Unused0();                          // +0
    virtual unsigned    Read(void* buffer, unsigned size);  // +4
    virtual void        Unused1();                          // +8
    virtual const char* GetName(unsigned key);              // +0xc
};

struct EapdSymbolTable {
    char            pad00[8];    // +0
    EapdLock        mLock;       // +8
    char            pad0c[0xfc]; // +0xc
    SymbolHashTable symbols;     // +0x108
    char            pad124[4];   // +0x124
    HashTable       groups;      // +0x128
    void ctor();                                       // @ 009206d0
    bool LoadSymbols(EapdStream* stream);              // @ 00920780
    bool LoadGroups(EapdStream* stream, void* owner);  // @ 00920b30
};

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

// Result of RangeMapper::Map: a validity byte followed by the mapped value.
struct MapOut {
    bool mValid;   // +0
    int  mKey;     // +4
};

// @ 0x009205e0
HashIter HashTable::insert(const HashValue& value, bool bFlag) {
    MapOut mo;
    mRangeMap.Map((unsigned char*)&mo, mnBucketCount, mnSize, 1);
    if (mo.mValid)
        rehash(mo.mKey);
    const unsigned char* s = (const unsigned char*)value.mpName;
    unsigned h = 0x811c9dc5;
    unsigned c = *s;
    while (c != 0) {
        ++s;
        h = h * 0x1000193 ^ c;
        c = *s;
    }
    unsigned idx = h % mnBucketCount;
    HashNode* n = (HashNode*)EASTL_allocator_allocate(0x14, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (n != 0) {
        n->mpName = value.mpName;
        n->mpStream = value.mpStream;
        n->mpOwner = value.mpOwner;
        n->mKey = value.mKey;
    }
    n->mpNext = 0;
    HashNode* head = mpBuckets[idx];
    HashNode* p = head;
    while (p != 0 && p->mpName != value.mpName)
        p = p->mpNext;
    if (p == 0) {
        n->mpNext = head;
        mpBuckets[idx] = n;
    } else {
        n->mpNext = p->mpNext;
        p->mpNext = n;
    }
    ++mnSize;
    HashIter result;
    result.mpNode = n;
    result.mpSlot = &mpBuckets[idx];
    return result;
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
bool EapdSymbolTable::LoadSymbols(EapdStream* stream) {
    bool ok = true;
    mLock.Lock(2, (void*)0x143d820);
    unsigned keys[0x80];
    unsigned count = stream->Read(keys, 0x80);
    for (unsigned i = 0; i < count; ++i) {
        unsigned key = keys[i];
        unsigned idx = key % symbols.mnBucketCount;
        SymbolNode* node = symbols.mpBuckets[idx];
        SymbolNode** slot = &symbols.mpBuckets[idx];
        if (node != 0) {
            while (node->mKey != key) {
                node = node->mpNext;
                if (node == 0)
                    break;
            }
        }
        SymbolIter it;
        if (node == 0) {
            it.mpNode = symbols.mpBuckets[symbols.mnBucketCount];
            it.mpSlot = &symbols.mpBuckets[symbols.mnBucketCount];
        } else {
            it.mpNode = node;
            it.mpSlot = slot;
        }
        SymbolNode* end = symbols.mpBuckets[symbols.mnBucketCount];
        while (it.mpNode != end) {
            if (it.mpNode->mKey != key) {
                ok = false;
                break;
            }
            if (it.mpNode->mpStream == stream) {
                symbols.erase(it);
                break;
            }
            if (it.mpNode->mpNext != 0) {
                it.mpNode = it.mpNode->mpNext;
            } else {
                do {
                    ++it.mpSlot;
                    it.mpNode = *it.mpSlot;
                } while (it.mpNode == 0);
            }
            if (it.mpNode == end)
                break;
        }
        const char* name = stream->GetName(key);
        if (name != 0) {
            HashIter git;
            groups.find(&git, &name);
            HashNode* gend = groups.mpBuckets[groups.mnBucketCount];
            while (git.mpNode != gend) {
                if (strcmp(git.mpNode->mpName, name) != 0) {
                    ok = false;
                    break;
                }
                if (git.mpNode->mpStream == stream) {
                    groups.erase(git);
                    break;
                }
                if (git.mpNode->mpNext != 0) {
                    git.mpNode = git.mpNode->mpNext;
                } else {
                    do {
                        ++git.mpSlot;
                        git.mpNode = *git.mpSlot;
                    } while (git.mpNode == 0);
                }
                if (git.mpNode == gend)
                    break;
            }
        }
    }
    mLock.Unlock();
    return ok;
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
bool EapdSymbolTable::LoadGroups(EapdStream* stream, void* owner) {
    mLock.Lock(2, (void*)0x143d820);
    unsigned keys[0x80];
    unsigned count = stream->Read(keys, 0x80);
    for (unsigned i = 0; i < count; ++i) {
        unsigned key = keys[i];
        SymbolValue sv;
        sv.mKey = key;
        sv.mpStream = stream;
        sv.mpOwner = owner;
        bool bSymFlag = false;
        symbols.insert(sv, bSymFlag);
        const char* name = stream->GetName(key);
        if (name != 0) {
            HashValue gv;
            gv.mpName = name;
            gv.mpStream = stream;
            gv.mpOwner = owner;
            gv.mKey = key;
            bool bGroupFlag = false;
            groups.insert(gv, bGroupFlag);
        }
    }
    mLock.Unlock();
    return true;
}

// @ 0x00920f30  (canonicalize a path range: separators, "." and "..")
Range* FUN_00920f30(Range* r, char flag) {
    wchar_t* src = r->begin;
    wchar_t* last = r->end;
    wchar_t* dst = src;
    bool bAbsolute = false;
    if (src + 2 <= last && (src[0] == L'\\' || src[0] == L'/') &&
        (src[1] == L'\\' || src[1] == L'/'))
        bAbsolute = true;
    if (HasAltSeparator(src, last))
        bAbsolute = true;
    // leading run of separators is copied verbatim (UNC prefix)
    while (src < last) {
        wchar_t c = *src;
        if (c != L'\\' && c != L'/')
            break;
        if (flag)
            c = L'\\';
        *dst++ = c;
        ++src;
    }
    while (src < last) {
        if (src + 1 < last && src[0] == L'.' && (src[1] == L'\\' || src[1] == L'/')) {
            src += 2;
            while (src < last && (*src == L'\\' || *src == L'/'))
                ++src;
            continue;
        }
        if (src + 2 < last && src[0] == L'.' && src[1] == L'.' &&
            (src[2] == L'\\' || src[2] == L'/')) {
            wchar_t* begin = r->begin;
            if (dst > begin) {
                wchar_t* p = SkipComponentBack(begin, dst);
                if (p > begin || !bAbsolute) {
                    src += 3;
                    dst = p;
                    while (src < last && (*src == L'\\' || *src == L'/'))
                        ++src;
                    continue;
                }
            }
        }
        while (src < last) {
            wchar_t c = *src++;
            if (c == L'\\' || c == L'/') {
                if (flag)
                    c = L'\\';
                *dst++ = c;
                while (src < last && (*src == L'\\' || *src == L'/'))
                    ++src;
                break;
            }
            if (c == L':') {
                *dst++ = c;
                if (src >= last)
                    goto done;
                if (*dst == L'\\' || *dst == L'/')
                    continue;
                break;
            }
            *dst++ = c;
        }
    }
done:
    if (dst != last) {
        wchar_t* e = r->end;
        memmove(dst, last, (size_t)(e - last + 1) * sizeof(wchar_t));
        r->end = dst + (e - last);
    }
    return r;
}
