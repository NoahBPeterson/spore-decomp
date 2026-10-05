// Slice s0045edf0: EA string-buffer (EASTL basic_string storage) helpers and a
// 4x4 matrix * vector transform.  /Od /Ob1 /MD /Gy /TP.
#include "types.h"

extern "C" __declspec(dllimport) void* memmove(void* d, const void* s, unsigned int n);
extern "C" void* memcpy(void* d, const void* s, unsigned int n);
extern "C" void* EaAlloc(unsigned int n, const char* tag, int a, int b, const char* file, int line);

struct StrBuf {
    char* begin;   // +0
    char* end;     // +4
    char* cap;     // +8

    char* erase(char* first, char* last);                       // 0x45f080
    void  reserve(unsigned int n);                              // 0x45f0e0
    void  reallocate(unsigned int n);                           // 0x45f140
    void  swap(StrBuf& o);                                      // 0x45f2a0
    StrBuf* assign(const char* first, const char* last);        // 0x45f390
    void  appendGrow(const char* first, const char* last);      // 0x45f430
    void  appendFill(unsigned int n, char c);                   // 0x45efa0
    void  split_swap_dummy();                                   // placeholder for FUN_0045f240/f2a0 pair
    void  release();                                            // 0x429300
};

// =====================================================================
// @ 0x45f080  erase [first,last) from the string buffer
// =====================================================================
char* StrBuf::erase(char* first, char* last)
{
    if (first != last) {
        memmove(first, last, (unsigned int)((end - last) + 1));
        char* newEnd = end - (last - first);
        end = newEnd;
    }
    return first;
}

// =====================================================================
// @ 0x45f0e0  make room for max(n, size)+1 bytes
// =====================================================================
void StrBuf::reserve(unsigned int n)
{
    unsigned int size = (unsigned int)(end - begin);
    unsigned int* chosen;
    if (n < size) {
        chosen = &size;
    } else {
        chosen = &n;
    }
    unsigned int want = *chosen + 1;
    if ((unsigned int)(cap - begin) < want) {
        reallocate(want);
    }
    return;
}

// =====================================================================
// @ 0x45f140  grow the buffer to at least n bytes
// =====================================================================
void StrBuf::reallocate(unsigned int n)
{
    if (n == 0xffffffff || n <= (unsigned int)(end - begin)) {
        if (n < (unsigned int)(end - begin)) {
            reserve(n);
        }
        split_swap_dummy();
    } else {
        char* dst = (char*)EaAlloc(n, "Editor", 0, 0,
                                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        int used = (int)(end - begin);
        memcpy(dst, begin, (unsigned int)used);
        dst[used] = 0;
        release();
        begin = dst;
        end = dst + used;
        cap = dst + n;
    }
    return;
}

// =====================================================================
// @ 0x45f2a0  swap two string buffers
// =====================================================================
void StrBuf::swap(StrBuf& o)
{
    char* t0 = begin; begin = o.begin; o.begin = t0;
    char* t1 = end;   end = o.end;     o.end = t1;
    char* t2 = cap;   cap = o.cap;     o.cap = t2;
    return;
}

// =====================================================================
// @ 0x45f390  assign from a byte range
// =====================================================================
StrBuf* StrBuf::assign(const char* first, const char* last)
{
    unsigned int n = (unsigned int)(last - first);
    if ((unsigned int)(end - begin) < n) {
        memcpy(begin, first, (unsigned int)(end - begin));
        appendGrow((const char*)((end - begin) + first), last);
    } else {
        memcpy(begin, first, n);
        erase(begin + n, end);
    }
    return this;
}

// =====================================================================
// @ 0x45f430  append a range, growing if needed
// =====================================================================
void StrBuf::appendGrow(const char* first, const char* last)
{
    if (first == last) {
        return;
    }
    int used = (int)(end - begin);
    int add = (int)(last - first);
    unsigned int room = (unsigned int)((cap - begin) - 1);
    if (room < (unsigned int)(used + add)) {
        unsigned int want = (unsigned int)(used + add);
        unsigned int newCap = room < 9 ? 8 : room * 2;
        if (newCap < want) {
            newCap = want;
        }
        unsigned int alloc = newCap + 1;
        char* dst = (char*)EaAlloc(alloc, "Editor", 0, 0,
                                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        memcpy(dst, begin, (unsigned int)used);
        char* p = dst + used;
        memcpy(p, first, (unsigned int)add);
        p = p + add;
        *p = 0;
        release();
        begin = dst;
        end = p;
        cap = dst + alloc;
    } else {
        char* p = end + 1;
        memcpy(p, first, (unsigned int)(last - p));
        *end = first[0];
        end = end + (last - first);
        *end = 0;
    }
    return;
}

// =====================================================================
// @ 0x45efa0  append n copies of a byte
// =====================================================================
void StrBuf::appendFill(unsigned int n, char c)
{
    int used = (int)(end - begin);
    unsigned int room = (unsigned int)((cap - begin) - 1);
    if (room < (unsigned int)(used + n)) {
        unsigned int want = (unsigned int)(used + n);
        unsigned int newCap = room < 9 ? 8 : room * 2;
        if (newCap < want) {
            newCap = want;
        }
        reserve(newCap);
    }
    if (n != 0) {
        memcpy(end + 1, &c, n - 1);
        *end = c;
        end = end + n;
        *end = 0;
    }
    return;
}

// =====================================================================
// @ 0x45edf0  out = matrix * vector (4x4 * vec4)
// =====================================================================
void TransformVec4(float* out, const float* v, const float* m)
{
    float v0 = v[0];
    float v1 = v[1];
    float v2 = v[2];
    float v3 = v[3];
    out[0] = m[0] * v0 + m[4] * v1 + m[8] * v2 + m[12] * v3;
    out[1] = m[1] * v0 + m[5] * v1 + m[9] * v2 + m[13] * v3;
    out[2] = m[2] * v0 + m[6] * v1 + m[10] * v2 + m[14] * v3;
    out[3] = m[3] * v0 + m[7] * v1 + m[11] * v2 + m[15] * v3;
    return;
}

void StrBuf::split_swap_dummy()
{
    return;
}

void StrBuf::release()
{
    return;
}
