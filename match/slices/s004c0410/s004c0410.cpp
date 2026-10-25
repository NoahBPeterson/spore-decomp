// Slice s004c0410 (editor model containers + XML string helpers).
// Module flags: /Od /Ob1 /MD /Gy /TP (unoptimized; no C++ EH, no SSE).
#include "types.h"

// 004c0410  resize a pointer-range container (element stride is implicit in the args).
// The callees are thiscall members of the same vector object (the original sets ecx = this
// before each call), so declare them as members so cl emits the thiscall sequence.
struct VecOps {
    void FUN_004c10e0(void* end, int n, void* value);   // 0x4c10e0
    void FUN_00514750(void* first, void* last);         // 0x514750
};

struct VecPtr { int m[4]; void FUN_004c0410(uint32_t n); };
// @ 0x004c0410
void VecPtr::FUN_004c0410(uint32_t n) {
    int* self = (int*)this;
    if ((uint32_t)(self[1] - self[0]) < n) {
        char local_5 = 0;
        ((VecOps*)this)->FUN_004c10e0((void*)self[1], (int)(n - (self[1] - self[0])), &local_5);
    } else {
        ((VecOps*)this)->FUN_00514750((void*)(self[0] + n), (void*)self[1]);
    }
}

// 004c0600  lower_bound over 0x18-byte records (cdecl).
// 004c0680 / 004c0730  close a gap in a fixed-stride vector (POD element move).
struct Elem8c { uint32_t d[0x23]; };   // 0x8c bytes; out-of-line copy ctor is 0x47b950
struct Elem38 { uint32_t d[0xe]; };    // 0x38 bytes
struct Container {
    int* mBegin;         // +0
    int* mEnd;           // +4
    int* mCapacity;      // +8
    char mAllocator[4];  // +0xc
    Elem8c* FUN_004c0680(Elem8c* first, Elem8c* last);
    Elem38* FUN_004c0730(Elem38* first, Elem38* last);
    void FUN_004c0bd0(Elem8c* position, uint32_t n, const Elem8c& value);
};

// Block header EASTL keeps in front of every allocation (owner id at -0x04).
struct EastlBlockHeader {
    int32_t mPad;    // -0x08
    int32_t mOwner;  // -0x04
};

void*   EASTL_Allocate(void* pAllocator, uint32_t size, uint32_t alignment, int flags);  // @ 0x42dee0
void    FreeRawBlock(void* p);                                                           // @ 0xf47380
// eastl internals used by vector::insert: uninitialized copy / fill / copy-to-end.
Elem8c* FUN_004c1ce0(Elem8c* first, Elem8c* last, Elem8c* dst);                          // @ 0x4c1ce0
void    FUN_004c2320(Elem8c* dst, int n, const Elem8c* value, bool tag);                 // @ 0x4c2320
void    FUN_004c22a0(Elem8c** pOut, Elem8c* first, Elem8c* last, Elem8c* dst, bool tag); // @ 0x4c22a0
// Elem8c copy ctor: thiscall (ecx = destination, one stack argument).
void __fastcall FUN_0047b950(Elem8c* self, int dummy, const Elem8c* src);                // @ 0x47b950

// @ 0x004c0bd0  eastl::vector<Elem8c>::insert(position, n, value)
void Container::FUN_004c0bd0(Elem8c* position, uint32_t n, const Elem8c& value) {
    const uint32_t nFree = (uint32_t)(((char*)mCapacity - (char*)mEnd) / 0x8c);
    if (nFree < n) {
        // grow: move the head, fill the new elements, move the tail, free the old block
        const uint32_t nOldSize = (uint32_t)(((char*)mEnd - (char*)mBegin) / 0x8c);
        const uint32_t nDoubled = (nOldSize > 0) ? nOldSize * 2 : 1;
        const uint32_t nNewCapacity = (nDoubled > nOldSize + n) ? nDoubled : nOldSize + n;
        Elem8c* pNew = nNewCapacity
            ? (Elem8c*)EASTL_Allocate(mAllocator, nNewCapacity * 0x8c, 4, 0) : 0;
        Elem8c* pResult = FUN_004c1ce0((Elem8c*)mBegin, position, pNew);
        FUN_004c2320(pResult, (int)n, &value, false);
        pResult = FUN_004c1ce0(position, (Elem8c*)mEnd, (Elem8c*)((char*)pResult + n * 0x8c));
        const uint32_t nOldCapacity = (uint32_t)(((char*)mCapacity - (char*)mBegin) / 0x8c);
        Elem8c* pOld = (Elem8c*)mBegin;
        if (pOld && ((EastlBlockHeader*)pOld)[-1].mOwner)
            FreeRawBlock(pOld);
        mBegin = (int*)pNew;
        mEnd = (int*)pResult;
        mCapacity = (int*)((char*)pNew + nNewCapacity * 0x8c);
        (void)nOldCapacity;
    } else if (n != 0) {
        Elem8c valueSaved;
        FUN_0047b950(&valueSaved, 0, &value);
        const uint32_t nTail = (uint32_t)(((char*)mEnd - (char*)position) / 0x8c);
        Elem8c* pOldEnd = (Elem8c*)mEnd;
        if (n < nTail) {
            // open a gap inside the tail, then shift the middle right and fill
            Elem8c* pPast;
            FUN_004c22a0(&pPast, (Elem8c*)((char*)pOldEnd - n * 0x8c), pOldEnd, pOldEnd, false);
            mEnd = (int*)((char*)mEnd + n * 0x8c);
            Elem8c* pDest = pOldEnd;
            Elem8c* pSrc = (Elem8c*)((char*)pOldEnd - n * 0x8c);
            while (pSrc != position) {
                --pSrc;
                --pDest;
                *pDest = *pSrc;
            }
            for (Elem8c* p = position; p != (Elem8c*)((char*)position + n * 0x8c); ++p)
                *p = valueSaved;
        } else {
            // append the elements that do not fit, move the tail to the end, fill the gap
            const uint32_t nAppend = n - nTail;
            FUN_004c2320(pOldEnd, (int)nAppend, &valueSaved, false);
            mEnd = (int*)((char*)mEnd + nAppend * 0x8c);
            Elem8c* pPast;
            FUN_004c22a0(&pPast, position, pOldEnd, (Elem8c*)mEnd, false);
            mEnd = (int*)((char*)mEnd + nTail * 0x8c);
            for (Elem8c* p = position; p != pOldEnd; ++p)
                *p = valueSaved;
        }
    }
}

// @ 0x004c0680
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

// @ 0x004c0730
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
    // Retail rounds the byte delta down to whole 0x38-byte elements (idiv then imul).
    int nMove = (int)((char*)last - (char*)first) / (int)sizeof(Elem38);
    mEnd = (int*)((char*)mEnd - nMove * 0x38);
    (void)bOutputIsPointer; (void)bInputIsPointer; (void)bHasTrivialCopy;
    return first;
}

// 004c0570  initialize an XML text writer with a 0x400-byte inline buffer.
struct WriterOps {
    void FUN_0042bfa0(uint32_t a, uint32_t* b);   // 0x42bfa0
};
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

// @ 0x004c0570
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
    ((WriterOps*)this)->FUN_0042bfa0(a, &local_18);
    (void)local_14;
    return (int*)this;
}

// 004c0b80  free a vector's heap storage unless it uses the inline buffer.
// @ 0x004c0b80
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

// 004c07e0  eastl::sort over 0x18-byte records: introsort, then a final insertion pass over
// the elements past the first 28 (which were insertion-sorted on their own).
struct Elem18 { uint32_t a, b, c, d, e, f; };   // 0x18 bytes, ordered by the first dword
void FUN_004c1920(Elem18* first, Elem18* last, int depth, bool flag);   // @ 0x4c1920
void FUN_004c1b80(Elem18* first, Elem18* last, bool flag);              // @ 0x4c1b80

// @ 0x004c07e0
void FUN_004c07e0(Elem18* first, Elem18* last, bool flag) {
    if (first != last) {
        int depth = 0;
        int n = (int)((char*)last - (char*)first) / 0x18;
        while (n != 0) {
            n = n >> 1;
            depth++;
        }
        FUN_004c1920(first, last, depth * 2 - 2, flag);
        if ((int)((char*)last - (char*)first) / 0x18 < 0x1d) {
            FUN_004c1b80(first, last, flag);
        } else {
            FUN_004c1b80(first, first + 0x1c, flag);
            for (Elem18* i = first + 0x1c; i != last; ++i) {
                Elem18 value = *i;
                Elem18* pInsert = i;
                Elem18* pPrev = i - 1;
                while (value.a < pPrev->a) {
                    *pInsert = *pPrev;
                    --pInsert;
                    --pPrev;
                }
                *pInsert = value;
            }
        }
    }
}

// 004c09e0  eastl::basic_string<wchar16>::sprintf_va_list: format into the spare capacity,
// growing (and resizing) until Vsnprintf16 reports a result that fits.
extern wchar_t gEmptyString16;                                      // 0x01667bac
int Vsnprintf16(int16_t* pDest, uint32_t n, const wchar_t* fmt, char* args);  // @ 0x939950

struct BasicString16 {
    uint16_t* mpBegin;     // +0
    uint16_t* mpEnd;       // +4
    uint16_t* mpCapacity;  // +8
    void resize(uint32_t n);                                          // @ 0x4c1c80
    BasicString16* sprintf_va_list(const wchar_t* fmt, char* args);  // @ 0x4c09e0
};

// @ 0x004c09e0
BasicString16* BasicString16::sprintf_va_list(const wchar_t* fmt, char* args) {
    const int nOldSize = (int)(((char*)mpEnd - (char*)mpBegin) >> 1);
    int n = (mpBegin == (uint16_t*)&gEmptyString16)
        ? Vsnprintf16((int16_t*)mpEnd, 0, fmt, args)
        : Vsnprintf16((int16_t*)mpEnd, (uint32_t)(((char*)mpCapacity - (char*)mpEnd) >> 1), fmt, args);
    if (n < (int)(((char*)mpCapacity - (char*)mpEnd) >> 1)) {
        if (n < 0) {
            // not even the current size fits: double the capacity until it does (or give up)
            const int nMin = 7;
            int nTry0 = nOldSize * 2;
            int nTry = (nMin < nTry0) ? nTry0 : nMin;
            while (n < 0 && (uint32_t)nTry < 1000000u) {
                resize((uint32_t)nTry);
                n = Vsnprintf16((int16_t*)mpBegin + nOldSize, (uint32_t)((nTry + 1) - nOldSize), fmt, args);
                nTry = nTry * 2;
            }
        }
    } else {
        resize((uint32_t)(nOldSize + n));
        n = Vsnprintf16((int16_t*)mpBegin + nOldSize, (uint32_t)(n + 1), fmt, args);
    }
    if (n >= 0)
        mpEnd = mpBegin + nOldSize + n;
    return this;
}

// @ 0x004c0600
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
