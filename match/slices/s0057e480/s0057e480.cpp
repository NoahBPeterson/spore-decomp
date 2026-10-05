// slice s0057e480 — editor helpers (mix of implemented small helpers and oversized stubs).
#include "types.h"

typedef unsigned int size_t;

// ---------------------------------------------------------------------------------------------
// 0x0057ed80 — init a 12-byte object from a source
struct cUnkEd80 {
    void* m0;
    void* m4;
    void* m8;
    void FUN_0057cc10(void* p);
    void* Init(void* p, void* unused);
};

// @ 0x0057ed80
void* cUnkEd80::Init(void* p, void* unused)
{
    m0 = 0;
    m4 = 0;
    m8 = 0;
    FUN_0057cc10(p);
    return this;
}

// ---------------------------------------------------------------------------------------------
// 0x0057edf0 — erase the element after `pos`
void DoInsertValue(void* dst, void* src, int n);   // 0x011e0744 (cdecl)

struct cVec16 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* EraseAfter(void* pos);
};

// @ 0x0057edf0
void* cVec16::EraseAfter(void* pos)
{
    char* src = (char*)pos + 4;
    if (src < (char*)mpEnd)
        DoInsertValue(pos, src, (int)((char*)mpEnd - src));
    mpEnd = (char*)mpEnd - 4;
    return pos;
}

// ---------------------------------------------------------------------------------------------
// 0x0057eda0 — eastl::basic_string<wchar_t>::trim
namespace eastl {
struct allocator {};

template <typename T, typename Alloc = allocator>
class basic_string {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Alloc mAlloc;

    size_t find_first_not_of(const T* s, size_t pos);   // 0x00579af0
    basic_string& erase(size_t pos, size_t n);          // 0x004228e0
    void rtrim();                                       // 0x005541e0

    // @ 0x0057eda0
    void trim()
    {
        {
            T ws[3] = { (T)0x20, (T)9, (T)0 };
            erase(0, find_first_not_of(ws, 0));
        }
        return rtrim();
    }
};

template class basic_string<wchar_t, allocator>;
} // namespace eastl

// ---------------------------------------------------------------------------------------------
// Oversized / not-yet-reconstructed functions (skeleton stubs; see partial.txt).
struct cUnkE480 { void Run(); };
void cUnkE480::Run() {}

void FUN_0057e480() {}   // 0x0057e480  780 B
void FUN_0057e790() {}   // 0x0057e790  265 B
void FUN_0057e8a0() {}   // 0x0057e8a0  390 B
void FUN_0057ea30() {}   // 0x0057ea30  446 B
void FUN_0057ebf0() {}   // 0x0057ebf0  264 B
void FUN_0057ed00() {}   // 0x0057ed00  126 B
void FUN_0057ee20() {}   // 0x0057ee20  294 B
void FUN_0057efa0() {}   // 0x0057efa0  329 B
void FUN_0057f0f0() {}   // 0x0057f0f0  299 B
void FUN_0057f220() {}   // 0x0057f220  440 B
