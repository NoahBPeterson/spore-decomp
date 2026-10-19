// slice s006b47a0, second translation unit: EASTL map/string helpers that are
// only partially reconstructed (see partial.txt). Kept separate so the main
// TU still sees them as opaque out-of-line calls.
// Flags: /O2 /MD /Gy /EHsc /GS- /TP
#include "types.h"

typedef unsigned short wchar16;

void __cdecl operator_delete__(void* p);   // 0x00f47380

// eastl::basic_string<wchar_t> core (used at 0x006b5110/0x006b51a0/0x006b53a0)
struct StrW {
    uint32_t mpBegin;      // +0
    uint32_t mpEnd;        // +4
    uint32_t mpCapacity;   // +8
    uint32_t mAllocator;   // +0xc (empty eastl allocator, 4 bytes padded)
    void RangeInitialize(const wchar16* src);     // 0x00579a90
    void assign(uint32_t begin, uint32_t end);    // 0x00423650
    void AllocateSelf(uint32_t n);                // 0x00429760
    void push_back(wchar16 ch);                   // 0x004f6510
    void Append(uint32_t begin, uint32_t end);    // 0x00429580
    ~StrW()
    {
        if (((int)((mpCapacity - mpBegin) & 0xfffffffeu) > 2) && mpBegin != 0)
            operator_delete__((void*)mpBegin);
    }
};

struct HtNode {
    uint32_t mKey;         // +0
    StrW     mStr;         // +4
    HtNode*  mpNext;       // +0x14
};

// The map object lives at 0x015308a8; both entry points below are its methods.
struct EaHt {
    void   find(void** pOut, const uint32_t* pKey);   // 0x00a3b2c0
    void*  op_index(uint32_t* pKey);                  // 0x0068d340
};

extern EaHt      g_ht;          // 0x015308a8
extern uint32_t* g_htBuckets;   // 0x015308ac
extern uint32_t  g_htCount;     // 0x015308b0
extern uint32_t  g_counter;     // 0x01605350

namespace SP {
struct HashMap {
    void*    mpUnk0;         // +0
    HtNode** mpBucketArray;  // +4
    uint32_t mnBucketCount;  // +8
    uint32_t mnSize;         // +0xc
    uint32_t erase_key(uint32_t* key);
};
}

// @ 0x006b50d0
uint32_t* __cdecl FUN_006b50d0(uint32_t key)
{
    uint32_t* it[2];
    uint32_t* node = 0;
    g_ht.find((void**)it, &key);
    uint32_t n = g_htCount;
    if (it[0] != (uint32_t*)g_htBuckets[n])
        node = it[0] + 1;
    return node;
}

// @ 0x006b5110
uint32_t SP::HashMap::erase_key(uint32_t* key)
{
    uint32_t oldSize = mnSize;
    HtNode** pp = &mpBucketArray[*key % mnBucketCount];
    if (*pp != 0) {
        HtNode* node;
        do {
            node = *pp;
            if (*key == node->mKey)
                break;
            pp = &node->mpNext;
        } while (node->mpNext != 0);
        if (*pp != 0) {
            while (*pp != 0 && *key == (*pp)->mKey) {
                node = *pp;
                *pp = node->mpNext;
                uint32_t begin = node->mStr.mpBegin;
                if (((int)((node->mStr.mpCapacity - begin) & 0xfffffffeu) > 2) && begin != 0)
                    operator_delete__((void*)begin);
                operator_delete__(node);
                mnSize--;
            }
        }
    }
    return oldSize - mnSize;
}

// @ 0x006b51a0
uint32_t __cdecl FUN_006b51a0(const wchar16* src)
{
    ++g_counter;
    StrW s;
    s.mpBegin = 0;
    s.mpEnd = 0;
    s.mpCapacity = 0;
    s.RangeInitialize(src);
    StrW* p = (StrW*)g_ht.op_index(&g_counter);
    if (&s != p)
        p->assign(s.mpBegin, s.mpEnd);
    return g_counter;
}

// @ 0x006b53a0
StrW __cdecl FUN_006b53a0(wchar16 ch, const StrW* other)
{
    StrW r;
    r.mpBegin = 0;
    r.mpEnd = 0;
    r.mpCapacity = 0;
    r.AllocateSelf(((int)(other->mpEnd - other->mpBegin) >> 1) + 2);
    *(wchar16*)r.mpEnd = 0;
    r.push_back(ch);
    r.Append(other->mpBegin, other->mpEnd);
    return r;
}
