// slice s008997f0 - four eastl vector mutation helpers of the text-layout code.
//
//   0x00899ae0  vector of 8-byte elements: DoInsertValue(position, count, value)
//   0x00899e10  vector of 16-byte elements: DoInsertValue(position, count, value)
//   0x00899fb0  vector of 12-byte elements: insert(position, first, last)
//   0x0089a1b0  vector of 8-byte pointers: insert(position, first, last)
//
// Every one is the eastl "insert" algorithm: grow-and-copy when the spare
// capacity is short, otherwise shift the tail in place.  The vector header is
// the usual eastl {begin, end, capacity} trio followed by the allocator, and the
// raw storage is reached through the allocator's virtual allocate/deallocate
// slots.  The helpers are pure raw-storage copies, so they take void*.
//
// Compile with /O2 /MD /Gy /EHSC /TP /arch:SSE /fp:fast.
#include "types.h"

typedef uint32_t u32;

// ---------------------------------------------------------------------------
// eastl raw-storage calls the four helpers make.
// ---------------------------------------------------------------------------
void* UninitCopy8(void* first, void* last, void* out);          // 0x0099efa0
void  GrowFill8(void* end, void* n, const void* value);         // 0x006ac440
void  CopyBackward8(void* first, void* last, void* outEnd);     // 0x0073fe50
void  SeqCopy8(void* result, void* first, void* last, void* x, void* y);   // 0x00a52da0 (5 args)
void  Copy8(void* result, void* first, void* last, void* outEnd, const void* value);   // 0x0076ffd0 (5 args)
void* MoveElements8(void* first, void* last, void* out);        // 0x0099efa0 (same shape)

void* E16UninitCopy(void* result, void* first, void* last, void* src, void* a);   // 0x007f1890
void  E16FillN(void* out, void* n, const void* value, void* a);                   // 0x0088f820
void  E16CopyBackward(void* first, void* last, void* outEnd);                     // 0x00edba80
void  E16Fill(void* first, void* last, const void* value);                        // 0x00898580
void* E16MoveElements(void* first, void* last, void* out);                        // 0x00c7ea30
void* E16Allocate(void* n);                                                       // 0x00f473a0
void  E16Deallocate(void* p);                                                     // 0x00f47380

void  AIUninitCopy(void* result, void* first, void* last, void* src, void* a);    // 0x00898b80
void  AICopyBackward(void* first, void* last, void* outEnd);                      // 0x00abced0
void  AIMoveElements(void* result, void* first, void* last);                      // 0x00a11310
void  AICopy(void* out, void* first, void* last);                                 // 0x00b84c80

// ---------------------------------------------------------------------------
// The eastl vector header shared by all four (only the element size differs).
// ---------------------------------------------------------------------------
struct EastlVecBase {
    char*    mpBegin;                // +0x00
    char*    mpEnd;                  // +0x04
    char*    mpCap;                  // +0x08
    void*    mpAlloc[4];             // +0x0c  (allocator: vtable, self, arena, ...)
};

// The allocator's two slots the grow path uses: +0x08 allocate, +0x0c deallocate.
struct EastlAllocVt {
    virtual void  Slot0();
    virtual void  Slot4();
    virtual void* Allocate(void* n, void* zero, void* arena);   // +0x08
    virtual void  Deallocate(void* p, void* n);                  // +0x0c
};

static inline void* VecAllocate(EastlVecBase* v, unsigned bytes)
{
    void* alloc = v->mpAlloc[0];
    EastlAllocVt* vt = *(EastlAllocVt**)alloc;
    return vt->Allocate((void*)bytes, 0, v->mpAlloc[3]);
}

static inline void VecDeallocate(EastlVecBase* v, void* p, unsigned bytes)
{
    void* alloc = v->mpAlloc[0];
    EastlAllocVt* vt = *(EastlAllocVt**)alloc;
    vt->Deallocate(p, (void*)bytes);
}

// ---------------------------------------------------------------------------
// Element records.  Only the sizes matter to the generic algorithm.
// ---------------------------------------------------------------------------
struct T8  { u32 a, b; };                 // 8 bytes  (text run)
struct E16 { u32 a, b, c, d; };           // 16 bytes (expanded run)
struct AnalysisInfo { u32 a, b, c; };     // 12 bytes

// ---------------------------------------------------------------------------
// 0x00899ae0: vector<T8>::DoInsertValue(position, count, value)
// `this` = the vector header, (position, count, value) on the stack.
// ---------------------------------------------------------------------------
struct Vec8 : EastlVecBase {
    void DoInsertValueN(T8* position, unsigned count, const T8* value);
};

// @ 0x00899ae0
void Vec8::DoInsertValueN(T8* position, unsigned count, const T8* value)
{
    unsigned have = (unsigned)(mpEnd - mpBegin) >> 3;
    if (have < count) {
        // --- grow path ----------------------------------------------------
        unsigned oldCount = (unsigned)(mpEnd - mpBegin) >> 3;
        unsigned cap2 = oldCount * 2;
        if (oldCount == 0)
            cap2 = 1;
        unsigned want = oldCount + count;
        if (cap2 > want)
            want = cap2;
        void* mem = 0;
        if (want != 0)
            mem = VecAllocate(this, want * 8);
        void* q = UninitCopy8(mpBegin, position, mem);
        for (unsigned i = count; i != 0; --i) {
            if (q != 0) {
                ((u32*)q)[0] = *(const u32*)value;
                ((u32*)q)[1] = ((const u32*)value)[1];
            }
            q = (char*)q + 8;
        }
        void* out = UninitCopy8(position, mpEnd, (char*)mem + count * 8);
        if (mpBegin != 0)
            VecDeallocate(this, mpBegin, (unsigned)((mpEnd - mpBegin) >> 3) * 8);
        mpBegin = (char*)mem;
        mpEnd = (char*)out;
        mpCap = (char*)mem + want * 8;
        return;
    }
    if (count == 0)
        return;

    // --- in-place path ----------------------------------------------------
    T8 local = *value;
    unsigned tail = (unsigned)((char*)mpEnd - (char*)position) >> 3;
    if (tail <= count) {
        unsigned add = count - tail;
        GrowFill8(mpEnd, (void*)add, &local);
        mpEnd += add * 8;
        Copy8((void*)0, position, (char*)mpEnd - add * 8, mpEnd, (void*)0);
        mpEnd += tail * 8;
        CopyBackward8((char*)position, (char*)position + add * 8, mpEnd);
        SeqCopy8((char*)position, (char*)position + add * 8, (char*)position + tail * 8, &local, (void*)0);
        return;
    }
    unsigned shift = count * 8;
    char* cut = mpEnd - shift;
    Copy8((void*)0, cut, mpEnd, mpEnd, (void*)0);
    mpEnd += shift;
    CopyBackward8((char*)position, cut, mpEnd);
    SeqCopy8(position, (char*)position + shift, mpEnd, &local, (void*)0);
}

// ---------------------------------------------------------------------------
// 0x00899e10: vector<E16>::DoInsertValue(position, count, value)
// ---------------------------------------------------------------------------
struct Vec16 : EastlVecBase {
    void DoInsertValueN(E16* position, unsigned count, const E16* value);
};

// @ 0x00899e10
void Vec16::DoInsertValueN(E16* position, unsigned count, const E16* value)
{
    unsigned have = (unsigned)(mpEnd - mpBegin) >> 4;
    if (have < count) {
        unsigned oldCount = (unsigned)(mpEnd - mpBegin) >> 4;
        unsigned cap2 = oldCount * 2;
        if (oldCount == 0)
            cap2 = 1;
        unsigned want = oldCount + count;
        if (cap2 > want)
            want = cap2;
        void* mem = 0;
        if (want != 0)
            mem = E16Allocate((void*)(want << 4));
        void* out = E16MoveElements(mpBegin, position, mem);
        E16FillN(out, (void*)count, value, position);
        void* out2 = E16MoveElements(position, mpEnd, (char*)out + count * 16);
        if (mpBegin != 0) {
            if (mpBegin != mpAlloc[3])
                E16Deallocate(mpBegin);
        }
        mpBegin = (char*)mem;
        mpEnd = (char*)out2;
        mpCap = (char*)mem + want * 16;
        return;
    }
    if (count == 0)
        return;

    E16 local = *value;
    unsigned tail = (unsigned)((char*)mpEnd - (char*)position) >> 4;
    if (tail <= count) {
        unsigned add = count - tail;
        E16FillN(mpEnd, (void*)add, &local, position);
        mpEnd += add * 16;
        E16UninitCopy((void*)0, position, (char*)mpEnd - add * 16, mpEnd, (void*)0);
        mpEnd += tail * 16;
        E16CopyBackward((char*)position, (char*)position + add * 16, mpEnd);
        E16Fill((char*)position, (char*)position + add * 16, &local);
        return;
    }
    unsigned shift = count * 16;
    char* cut = mpEnd - shift;
    E16UninitCopy((void*)0, cut, mpEnd, mpEnd, (void*)0);
    mpEnd += shift;
    E16CopyBackward((char*)position, cut, mpEnd);
    E16Fill(position, cut, &local);
}

// ---------------------------------------------------------------------------
// 0x00899fb0: vector<AnalysisInfo>::insert(position, first, last)
// ---------------------------------------------------------------------------
struct Vec12 : EastlVecBase {
    void InsertRange(AnalysisInfo* position, const AnalysisInfo* first, const AnalysisInfo* last);
};

// @ 0x00899fb0
void Vec12::InsertRange(AnalysisInfo* position, const AnalysisInfo* first, const AnalysisInfo* last)
{
    if (first == last)
        return;
    unsigned count = (unsigned)((char*)last - (char*)first) / 12;

    unsigned capHave = (unsigned)(mpCap - mpEnd) / 12;
    if (count > capHave) {
        // --- grow path ----------------------------------------------------
        unsigned oldCount = (unsigned)(mpEnd - mpBegin) / 12;
        unsigned cap2 = oldCount * 2;
        if (oldCount == 0)
            cap2 = 1;
        unsigned want = oldCount + count;
        if (cap2 > want)
            want = cap2;
        void* mem = 0;
        if (want != 0)
            mem = VecAllocate(this, want * 12);
        char* cursor = (char*)mem;
        AIMoveElements((void*)0, mpBegin, position);          // copy the head before position
        AIMoveElements(cursor, mpBegin, position);
        cursor += (char*)position - mpBegin;
        AIUninitCopy(cursor, (void*)first, (void*)last, cursor, (void*)0);
        AIMoveElements(cursor + count * 12, position, mpEnd);
        if (mpBegin != 0)
            VecDeallocate(this, mpBegin, (unsigned)((mpEnd - mpBegin) / 12) * 12);
        mpEnd = (char*)mem + ((mpEnd - mpBegin) / 12 + count) * 12;
        mpBegin = (char*)mem;
        mpCap = (char*)mem + want * 12;
        return;
    }

    unsigned tail = (unsigned)((char*)mpEnd - (char*)position) / 12;
    if (tail < count) {
        unsigned add = count - tail;
        char* cut = (char*)first + add * 12;
        AIMoveElements((void*)0, (void*)first, (void*)cut);
        mpEnd += add * 12;
        AIMoveElements((void*)0, (void*)first, (void*)last);
        mpEnd += tail * 12;
        AICopyBackward((void*)first, cut, (char*)position + add * 12);
        return;
    }
    char* cut = mpEnd - count * 12;
    AIMoveElements((void*)0, cut, mpEnd);
    mpEnd += count * 12;
    AICopyBackward(cut, mpEnd, (char*)position);
    AICopy((void*)0, (void*)first, (void*)last);
}

// ---------------------------------------------------------------------------
// 0x0089a1b0: vector<GlyphInfo*>::insert(position, first, last)
// ---------------------------------------------------------------------------
struct Vec8Range : EastlVecBase {
    void InsertRange(void** position, void** first, void** last);
};

// @ 0x0089a1b0
void Vec8Range::InsertRange(void** position, void** first, void** last)
{
    if (first == last)
        return;
    unsigned count = (unsigned)((char*)last - (char*)first) >> 3;
    unsigned capHave = (unsigned)(mpCap - mpEnd) >> 3;
    if (count > capHave) {
        unsigned oldCount = (unsigned)(mpEnd - mpBegin) >> 3;
        unsigned cap2 = oldCount * 2;
        if (oldCount == 0)
            cap2 = 1;
        unsigned want = oldCount + count;
        if (cap2 > want)
            want = cap2;
        void* mem = 0;
        if (want != 0)
            mem = VecAllocate(this, want * 8);
        void* out = UninitCopy8(mpBegin, position, mem);
        Copy8((void*)0, (void*)first, (void*)last, out, (void*)0);
        void* out2 = UninitCopy8(position, mpEnd, (char*)out + count * 8);
        if (mpBegin != 0)
            VecDeallocate(this, mpBegin, (unsigned)((mpEnd - mpBegin) >> 3) * 8);
        mpBegin = (char*)mem;
        mpEnd = (char*)out2;
        mpCap = (char*)mem + want * 8;
        return;
    }
    unsigned tail = (unsigned)((char*)mpEnd - (char*)position) >> 3;
    if (tail < count) {
        unsigned add = count - tail;
        Copy8((void*)0, (char*)first + add * 8, (void*)last, mpEnd, (void*)0);
        mpEnd += add * 8;
        CopyBackward8((char*)first, (char*)first + add * 8, (char*)position + add * 8);
        mpEnd += tail * 8;
        Copy8((void*)0, (void*)first, (char*)position, position, (void*)0);
        return;
    }
    char* cut = mpEnd - count * 8;
    CopyBackward8(cut, mpEnd, mpEnd);
    mpEnd += count * 8;
    CopyBackward8((char*)position, cut, mpEnd);
    Copy8((void*)0, (void*)first, (void*)last, position, (void*)0);
}
