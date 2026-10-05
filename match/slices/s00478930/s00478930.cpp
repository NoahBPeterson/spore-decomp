// Slice s00478930: eastl basic_string resize + vector integer/12-byte/0x29c insert helpers.
// Built /Od /Ob1 /MD /Gy /TP.
#include "types.h"

typedef unsigned int uint;
void* EASTL_Allocate(void* alloc, uint bytes, uint align, uint flags);   // @ 0x0042dee0
void  EASTL_allocator_deallocate(void* p);                               // @ 0x00f47380

struct Counted { char pad[0x40]; int mRefCount; void Release(); };
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct AutoRefCount {
    Counted* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};

// ---- eastl::basic_string<char> ----------------------------------------------------------
struct Str8 {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void Shrink(char* first, char* last);           // @ 0x0045f080
    void ResizeFill(uint n, char c);                // @ 0x00478930 (recursive)
    void resize(uint n);
};

// @ 0x00478930
void Str8::resize(uint n)
{
    const uint cur = (uint)(mpEnd - mpBegin);
    if (n < cur) {
        Shrink(mpBegin + n, mpEnd);
    } else if (n > cur) {
        ResizeFill(n - cur, 0);
    }
}

// ---- vector<int, ...> insert ------------------------------------------------------------
int* CopyIntRange(int* first, int* last, int* dest);           // @ 0x0047c700
void DestroyInts(int* first, int* last);                       // @ 0x0047c660
int* MoveIntsBack(int* first, int* last, int* dst);            // @ 0x0047c010
void FillInts(int* dst, uint n, const int& v);                 // @ 0x0047c0d0
int  VectorIntDoInsert(void* dst, const void* src, int n);     // @ 0x0047c700 (shared helper)

// @ 0x00478990
void IntVectorInsert(int* mpBegin, int*& mpEnd, int*& mpCapacity,
                     int* position, uint n, const int& value)
{
    if ((uint)(mpCapacity - mpEnd) < n) {
        uint oldSize = (uint)(mpEnd - mpBegin);
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        int* pNew = newSize ? (int*)EASTL_Allocate(mpCapacity, newSize * 4, 4, 0) : 0;
        int* p = CopyIntRange(mpBegin, position, pNew);
        FillInts(p, n, value);
        int* pNewEnd = CopyIntRange(position, mpEnd, p + n);
        if (mpBegin) EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        int v = value;
        uint tail = (uint)(mpEnd - position);
        if (n < tail) {
            int* newEnd = MoveIntsBack(position, mpEnd, mpEnd + n);
            DestroyInts(position, position + n);
            FillInts(position, n, v);
            (void)newEnd;
        } else {
            FillInts(mpEnd, n - tail, v);
            mpEnd += n - tail;
            CopyIntRange(position, mpEnd - n, mpEnd);
            mpEnd += tail;
            FillInts(position, tail, v);
        }
    }
}

// @ 0x00478db0
struct RefPtr {
    Counted* mpObject;
    RefPtr& operator=(Counted* p);
};
RefPtr& RefPtr::operator=(Counted* p)
{
    ScratchSlots<2>();
    if (p != mpObject) {
        Counted* old = mpObject;
        if (p) p->mRefCount += 1;
        mpObject = p;
        if (old) old->Release();
    }
    return *this;
}

// ---- vector<0x29c> insert ---------------------------------------------------------------
struct Elem29c {
    char pad[0x294];
    Counted* m298;
    Elem29c() : m298(0) {}
};
void MoveElem29(Elem29c* dst, Elem29c* src);                   // @ 0x0047cf00
Elem29c* Copy29Range(Elem29c* first, Elem29c* last, Elem29c* dest); // @ 0x0047c140
void Construct29Range(Elem29c* dst, uint n, const Elem29c& v);      // @ 0x0047c920
void Shift29(Elem29c* first, Elem29c* last);                        // @ 0x0047c8a0
void Fill29(Elem29c* dst, uint n, const Elem29c& v);                // @ 0x0047bbf0

// @ 0x00478e00
void Elem29Insert(Elem29c*& mpBegin, Elem29c*& mpEnd, Elem29c*& mpCapacity,
                  Elem29c* position, uint n, const Elem29c& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 0x29c < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 0x29c;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        Elem29c* pNew = newSize ? (Elem29c*)EASTL_Allocate(mpCapacity, newSize * 0x29c, 4, 0) : 0;
        Elem29c* p = Copy29Range(mpBegin, position, pNew);
        Construct29Range(p, n, value);
        Elem29c* pNewEnd = Copy29Range(position, mpEnd, p + n);
        if (mpBegin) EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        Elem29c v = value;
        uint tail = (uint)((char*)mpEnd - (char*)position) / 0x29c;
        if (n < tail) {
            Shift29(position, mpEnd);
            mpEnd += n;
            Elem29c* q = mpEnd - n;
            while (q != position) { --q; MoveElem29(q, q + n); }
            Fill29(position, n, v);
        } else {
            Construct29Range(mpEnd, n - tail, v);
            mpEnd += n - tail;
            Shift29(position, mpEnd - n + tail);
            Fill29(position, n, v);
        }
    }
}

// ---- vector<12-byte> insert -------------------------------------------------------------
struct E12 { float x, y, z; };
void* Copy12Range(const void* first, const void* last, void* dest);   // @ 0x004b66b0
void  Construct12Range(void* dst, uint n, const void* v);             // @ 0x0047ca00
void* Move12Range(const void* first, const void* last, void* dest);   // @ 0x004b6bf0
void  Shift12(void* first, void* last, void* out);                    // @ 0x004797a0

// @ 0x004797a0
void Shift12Out(E12** out, E12* first, E12* last, E12* dest)
{
    E12* d = dest;
    while (first != last) {
        if (d) { d->x = first->x; d->y = first->y; d->z = first->z; }
        ++first;
        ++d;
    }
    *out = d;
}

// @ 0x00479330
void Elem12Insert(E12*& mpBegin, E12*& mpEnd, E12*& mpCapacity,
                  E12* position, uint n, const E12& value)
{
    if ((uint)((char*)mpCapacity - (char*)mpEnd) / 0xc < n) {
        uint oldSize = (uint)((char*)mpEnd - (char*)mpBegin) / 0xc;
        uint grow = oldSize ? oldSize * 2 : 1;
        uint newSize = (oldSize + n < grow) ? grow : oldSize + n;
        E12* pNew = newSize ? (E12*)EASTL_Allocate(mpCapacity, newSize * 0xc, 4, 0) : 0;
        E12* p = (E12*)Copy12Range(mpBegin, position, pNew);
        Construct12Range(p, n, &value);
        E12* pNewEnd = (E12*)Move12Range(position, mpEnd, p + n);
        if (mpBegin) EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + newSize;
    } else if (n != 0) {
        E12 v = value;
        uint tail = (uint)((char*)mpEnd - (char*)position) / 0xc;
        if (n < tail) {
            E12* tmp;
            Shift12Out(&tmp, mpEnd - n, mpEnd, mpEnd);
            mpEnd += n;
            E12* q = mpEnd - n;
            while (q != position) { --q; q[n] = *q; }
            for (E12* w = position; w != position + n; ++w) *w = v;
        } else {
            Construct12Range(mpEnd, n - tail, &v);
            mpEnd += n - tail;
            Move12Range(position, mpEnd - n + tail, position + n);
            mpEnd += tail;
            for (E12* w = position; w != position + n; ++w) *w = v;
        }
    }
}
