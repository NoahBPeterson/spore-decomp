// Slice s00549e40: SP::Pollen / EASTL vector<basic_string> operation instantiations
// (uninitialized_copy+destruct, lower_bound, DoInsertValue, copy-ctor, assign).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

// ---------------------------------------------------------------- externals
void  WString_FreeBuffer(void* self);                              // 0x4237d0
void  WString_Assign(void* self, const void* b, const void* e);    // 0x423650
void  WString_AllocateSelf(void* self, const void* b, const void* e);// 0x423820
void  AString_Assign(void* self, const void* b, const void* e);    // 0x454cb0
void* EAAlloc(void* alloc, int size, int align, int flags);        // 0x42dee0
void  EADealloc(void* p);                                          // 0xf47380
void* UninitCopy10(void* first, void* last, void* result);         // 0x54b400
void* Sub_4fdcb0(void* first, void* last, void* result);           // 0x4fdcb0
void* Sub_54b2f0(void* self, int n, void* first, void* last);      // 0x54b2f0
void* Sub_54b250(void* first, void* last, void* result);           // 0x54b250
void* Sub_54b350(void* first, void* last, void* result);           // 0x54b350
void* Sub_54b480(void* self, int n, void* first, void* last);      // 0x54b480
void* Sub_54b510(void* out, void* first, void* last, void* result, int tag); // 0x54b510
void* Sub_54b5b0(void* first, void* last, void* result);           // 0x54b5b0
void* Sub_54b630(void* first, void* last, void* result);           // 0x54b630
void  Sub_5477e0(void* self);                                      // 0x5477e0

// 16-byte header shared by the vectors and the string elements (3 pointers + allocator).
struct WStr {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    int       mAlloc;
    void Alloc040(const void* b, const void* e);   // 0x47d390 basic_string<char>::RangeCtor
};
// 20-byte map element: key + 16-byte string.
struct Pair20 {
    uint32_t  key;
    WStr      str;
};

// Vector header with member helpers (all __thiscall in the original).
struct V {
    char*  mpBegin;
    char*  mpEnd;
    char*  mpCapacity;
    int    mAlloc;
    void* FUN_0054a070(WStr* position, const WStr* value);
    void* FUN_0054a470(const Pair20* src);
    void* FUN_0054a670(char* other);
    void* FUN_0054a920(Pair20* position, const Pair20* value);
    void* FUN_0054aba0(char* other);
    void* FUN_0054ac70(char* other);
};

// Inline string comparison, -1 / 0 / 1 (matches the inlined basic_string::compare).
static __forceinline int WCompare(const uint16_t* a, const uint16_t* b) {
    for (;;) {
        uint16_t ca = *a;
        uint16_t cb = *b;
        if (ca != cb) return ca < cb ? -1 : 1;
        if (ca == 0) return 0;
        ca = a[1];
        cb = b[1];
        if (ca != cb) return ca < cb ? -1 : 1;
        a += 2;
        b += 2;
        if (ca == 0) return 0;
    }
}

// @ 0x00549e40
void* FUN_00549e40(char* first, char* last, char* result)
{
    void* res = UninitCopy10(first, last, result);
    char* tmp = result;
    while (first != last) {
        WString_FreeBuffer(first);
        first += 0x10;
        tmp += 0x10;
    }
    return res;
}

// @ 0x00549f80
WStr* FUN_00549f80(WStr* first, int last, const WStr* value)
{
    int n = (last - (int)first) >> 4;
    while (n > 0) {
        int half = n >> 1;
        WStr* mid = first + half;
        if (WCompare(mid->mpBegin, value->mpBegin) < 0) {
            first = mid + 1;
            n = n - (half + 1);
        } else {
            n = half;
        }
    }
    return first;
}

// @ 0x0054a070
void* V::FUN_0054a070(WStr* position, const WStr* value)
{
    if (mpEnd == mpCapacity) {
        int n = (int)(mpEnd - mpBegin) >> 4;
        int cnt = (n == 0) ? 1 : (n << 1);
        WStr* buf = (cnt == 0) ? 0 : (WStr*)EAAlloc(&mAlloc, cnt << 4, 8, 0);
        WStr* pv = const_cast<WStr*>(value);
        if ((char*)position <= (char*)value && (char*)value < mpEnd) {
            pv = const_cast<WStr*>(value) + 1;
        }
        WStr* mid = (WStr*)Sub_4fdcb0(mpBegin, position, buf);
        if (mid != 0) {
            *mid = *pv;
            mid = mid + 1;
        }
        WStr* e2 = (WStr*)Sub_4fdcb0(position, mpEnd, mid);
        if (mpBegin != 0) EADealloc(mpBegin);
        mpBegin = (char*)buf;
        mpEnd = (char*)e2;
        mpCapacity = (char*)buf + (cnt << 4);
    } else {
        WStr* pv = const_cast<WStr*>(value);
        if ((char*)position <= (char*)value && (char*)value < mpEnd) {
            pv = const_cast<WStr*>(value) + 1;
        }
        WStr* e = (WStr*)mpEnd;
        if (e != 0) *e = e[-1];
        WStr* dst = e;
        WStr* src = e - 1;
        while (src != position) {
            dst[-1] = src[-1];
            dst = dst - 1;
            src = src - 1;
        }
        *position = *pv;
        mpEnd = (char*)(e + 1);
    }
    return this;
}

// @ 0x0054a2d0
uint16_t** FUN_0054a2d0(uint16_t** first, int last, const uint16_t** value)
{
    int n = (last - (int)first) >> 3;
    while (n > 0) {
        int half = n >> 1;
        uint16_t** mid = first + half * 2;
        if (WCompare(mid[0], value[0]) < 0) {
            first = mid + 2;
            n = n - (half + 1);
        } else {
            n = half;
        }
    }
    return first;
}

// @ 0x0054a470
void* V::FUN_0054a470(const Pair20* src)
{
    Pair20* self = (Pair20*)this;
    self->key = src->key;
    self->str.mpBegin = 0;
    self->str.mpEnd = 0;
    self->str.mpCapacity = 0;
    self->str.Alloc040(src->str.mpBegin, src->str.mpEnd);
    return this;
}

// @ 0x0054a670
void* V::FUN_0054a670(char* otherp)
{
    V* other = (V*)otherp;
    if (otherp != (char*)this) {
        int n = (int)(other->mpEnd - other->mpBegin) / 0x14;
        if ((unsigned)((int)(mpCapacity - mpBegin) / 0x14) < (unsigned)n) {
            void* buf = Sub_54b2f0((char*)this, n, other->mpBegin, other->mpEnd);
            char* p = mpBegin;
            char* e = mpEnd;
            while (p < e) { Sub_5477e0(p); p += 0x14; }
            if (mpBegin != 0) EADealloc(mpBegin);
            mpBegin = (char*)buf;
            mpCapacity = (char*)buf + n * 0x14;
        } else if ((unsigned)((int)(mpEnd - mpBegin) / 0x14) < (unsigned)n) {
            char* off = other->mpBegin + ((int)(mpEnd - mpBegin) / 0x14) * 0x14;
            Sub_54b5b0(other->mpBegin, off, mpBegin);
            Sub_54b250(off, other->mpEnd, mpEnd);
        } else {
            char* d = (char*)Sub_54b5b0(other->mpBegin, other->mpEnd, mpBegin);
            char* e = mpEnd;
            while (d < e) { Sub_5477e0(d); d += 0x14; }
        }
        mpEnd = mpBegin + n * 0x14;
    }
    return this;
}

// @ 0x0054a920
void* V::FUN_0054a920(Pair20* position, const Pair20* value)
{
    if (mpEnd != mpCapacity) {
        Pair20* pv = const_cast<Pair20*>(value);
        if ((char*)position <= (char*)value && (char*)value < mpEnd) {
            pv = const_cast<Pair20*>(value) + 1;
        }
        if (mpEnd != 0) FUN_0054a470((const Pair20*)(mpEnd - 0x14));
        Sub_54b630(position, mpEnd - 0x14, mpEnd);
        position->key = pv->key;
        if (&pv->str != &position->str) {
            AString_Assign(&position->str, pv->str.mpBegin, pv->str.mpEnd);
        }
        mpEnd += 0x14;
        return this;
    }
    int n = (int)(mpEnd - mpBegin) / 0x14;
    int cnt = (n == 0) ? 1 : (n << 1);
    void* buf = (cnt == 0) ? 0 : EAAlloc(&mAlloc, cnt * 0x14, 4, 0);
    void* mid = Sub_54b350(mpBegin, position, buf);
    if (mid != 0) FUN_0054a470((const Pair20*)value);
    void* e2 = Sub_54b350(position, mpEnd, (char*)mid + 0x14);
    if (mpBegin != 0) EADealloc(mpBegin);
    mpBegin = (char*)buf;
    mpEnd = (char*)e2;
    mpCapacity = (char*)buf + cnt * 0x14;
    return this;
}

// @ 0x0054aba0
void* V::FUN_0054aba0(char* otherp)
{
    V* other = (V*)otherp;
    int n = (int)(other->mpEnd - other->mpBegin) >> 4;
    WStr* buf = (n == 0) ? 0 : (WStr*)EAAlloc(&mAlloc, n << 4, 4, 0);
    mpBegin = (char*)buf;
    mpEnd = (char*)buf;
    mpCapacity = (char*)buf + n * 0x10;
    void* out;
    Sub_54b510(&out, other->mpBegin, other->mpEnd, buf, 0);
    mpEnd = (char*)out;
    return this;
}

// @ 0x0054ac70
void* V::FUN_0054ac70(char* otherp)
{
    V* other = (V*)otherp;
    if (otherp != (char*)this) {
        int n = (int)(other->mpEnd - other->mpBegin) >> 4;
        if ((unsigned)((int)(mpCapacity - mpBegin) >> 4) < (unsigned)n) {
            void* buf = Sub_54b480((char*)this, n, other->mpBegin, other->mpEnd);
            char* p = mpBegin;
            char* e = mpEnd;
            while (p < e) { WString_FreeBuffer(p); p += 0x10; }
            if (mpBegin != 0) EADealloc(mpBegin);
            mpBegin = (char*)buf;
            mpCapacity = (char*)buf + n * 0x10;
        } else if ((unsigned)((int)(mpEnd - mpBegin) >> 4) < (unsigned)n) {
            WStr* dst = (WStr*)mpBegin;
            WStr* mid = (WStr*)other->mpBegin + ((int)(mpEnd - mpBegin) >> 4);
            for (WStr* src = (WStr*)other->mpBegin; src != mid; src = src + 1) {
                if (src != dst) WString_Assign(dst->mpBegin, src->mpBegin, src->mpEnd);
                dst = dst + 1;
            }
            void* end;
            Sub_54b510(&end, mid, other->mpEnd, dst, 0);
        } else {
            WStr* dst = (WStr*)mpBegin;
            for (WStr* src = (WStr*)other->mpBegin; src != (WStr*)other->mpEnd; src = src + 1) {
                if (src != dst) WString_Assign(dst->mpBegin, src->mpBegin, src->mpEnd);
                dst = dst + 1;
            }
            char* p = (char*)dst;
            char* e = mpEnd;
            while (p < e) { WString_FreeBuffer(p); p += 0x10; }
        }
        mpEnd = mpBegin + n * 0x10;
    }
    return this;
}
