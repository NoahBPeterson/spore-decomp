// Slice s004c0410 (editor model containers + XML string helpers).
// Module flags: /Od /Ob1 /MD /Gy /TP (unoptimized; no C++ EH, no SSE).
#include "types.h"

// 004c0410  resize a pointer-range container (element stride is implicit in the args).
extern void FUN_004c10e0(void* dst, int n, void* def);   // 0x4c10e0
extern void FUN_00514750(void* first, void* last);       // 0x514750

void FUN_004c0410(int* self, uint32_t n) {
    if ((uint32_t)(self[1] - self[0]) < n) {
        char local_5 = 0;
        FUN_004c10e0((void*)self[1], n - (self[1] - self[0]), &local_5);
    } else {
        FUN_00514750((void*)(self[0] + n), (void*)self[1]);
    }
}

// 004c0600  lower_bound over 0x18-byte records (cdecl).
// 004c0680 / 004c0730  close a gap in a fixed-stride vector (POD element move).
struct Elem8c { uint32_t d[0x23]; };   // 0x8c bytes
struct Elem38 { uint32_t d[0xe]; };    // 0x38 bytes
struct Container {
    int* mBegin;     // +0
    int* mEnd;       // +4
    int* mCapacity;  // +8
    Elem8c* FUN_004c0680(Elem8c* first, Elem8c* last);
    Elem38* FUN_004c0730(Elem38* first, Elem38* last);
};

Elem8c* Container::FUN_004c0680(Elem8c* first, Elem8c* last) {
    bool bOutputIsPointer;
    bool bInputIsPointer;
    bool bHasTrivialCopy;
    Elem8c* end = (Elem8c*)mEnd;
    Elem8c* dst = first;
    for (Elem8c* src = last; src != end; src = (Elem8c*)((char*)src + 0x8c)) {
        *dst = *src;
        dst = (Elem8c*)((char*)dst + 0x8c);
    }
    for (Elem8c* p = dst; p < (Elem8c*)mEnd; p = (Elem8c*)((char*)p + 0x8c)) {
    }
    mEnd = (int*)((char*)mEnd - ((char*)last - (char*)first));
    (void)bOutputIsPointer; (void)bInputIsPointer; (void)bHasTrivialCopy;
    return first;
}

Elem38* Container::FUN_004c0730(Elem38* first, Elem38* last) {
    bool bOutputIsPointer;
    bool bInputIsPointer;
    bool bHasTrivialCopy;
    Elem38* end = (Elem38*)mEnd;
    Elem38* dst = first;
    for (Elem38* src = last; src != end; src = (Elem38*)((char*)src + 0x38)) {
        *dst = *src;
        dst = (Elem38*)((char*)dst + 0x38);
    }
    for (Elem38* p = dst; p < (Elem38*)mEnd; p = (Elem38*)((char*)p + 0x38)) {
    }
    mEnd = (int*)((char*)mEnd - ((char*)last - (char*)first));
    (void)bOutputIsPointer; (void)bInputIsPointer; (void)bHasTrivialCopy;
    return first;
}

// 004c0570  initialize an XML text writer with a 0x400-byte inline buffer.
extern void FUN_0042bfa0(uint32_t a, uint32_t* b);   // 0x42bfa0
extern void EASTL_allocator_deallocate(void* p);     // 0xf47380

struct StrWriter {
    int* mBegin;     // +0
    int* mEnd;       // +4
    int* mCapacity;  // +8
    int pad0c;       // +0xc
    int* mInline;    // +0x10
    int* Init(uint32_t a, uint32_t b);   // 004c0570
    void Free();                         // 004c0b80
};

int* StrWriter::Init(uint32_t a, uint32_t b) {
    int* local_8 = (int*)this + 6;
    mBegin = 0;
    mEnd = 0;
    mCapacity = 0;
    int* local_14 = (int*)this + 3;
    mInline = local_8;
    mEnd = (int*)this + 6;
    mBegin = mEnd;
    mCapacity = (int*)((char*)mBegin + 0x400);
    uint32_t local_18 = b;
    FUN_0042bfa0(a, &local_18);
    (void)local_14;
    return (int*)this;
}

// 004c0b80  free a vector's heap storage unless it uses the inline buffer.
void StrWriter::Free() {
    if (mBegin != 0) {
        int n40 = (int)((char*)mCapacity - (char*)mBegin) >> 2 << 2;
        int* len = mBegin;
        if (len != mInline) {
            int* v33 = len;
            EASTL_allocator_deallocate(v33);
        }
        (void)n40;
    }
}

// 004c07e0 / 004c09e0 / 004c0bd0  sorting / insertion helpers (PARTIAL skeletons).
extern void FUN_004c1920(void* first, void* last, int depth, uint8_t flag);  // 0x4c1920
extern void FUN_004c1b80(void* first, void* last, uint8_t flag);              // 0x4c1b80
void FUN_004c07e0(void* first, void* last, uint8_t flag) {
    if (first != last) {
        int n = (int)((char*)last - (char*)first) / 0x18;
        int depth = 0;
        for (int t = n; t != 0; t = t >> 1)
            depth++;
        FUN_004c1920(first, last, depth * 2 - 2, flag);
        FUN_004c1b80(first, last, flag);
    }
}

// 004c09e0  (PARTIAL skeleton)
void FUN_004c09e0(void* first, void* last, uint8_t flag) {
    (void)first; (void)last; (void)flag;
}

// 004c0bd0  (PARTIAL skeleton)
void FUN_004c0bd0(void* dst, int n, void* out) {
    (void)dst; (void)n; (void)out;
}

uint32_t* FUN_004c0600(uint32_t* begin, uint32_t* end, uint32_t* key) {
    int n = (int)((char*)end - (char*)begin) / 0x18;
    while (n > 0) {
        int nHalf = n >> 1;
        uint32_t* pMid = (uint32_t*)((char*)begin + nHalf * 0x18);
        bool bValueLessThanNode = pMid[0] < key[0];
        if (bValueLessThanNode) {
            begin = (uint32_t*)((char*)pMid + 0x18);
            n = n - (nHalf + 1);
        } else {
            n = nHalf;
        }
    }
    return begin;
}
