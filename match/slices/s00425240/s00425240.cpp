// Deque / hashtable helpers (EASTL-style), built unoptimized: /Od /Ob1.
#include "types.h"

inline void* operator new(unsigned, void* p) { return p; }

// ---- 16-byte value with out-of-line copy constructor ----
struct Key16 { uint32_t a, b, c, d; };

struct __declspec(align(8)) HashNode {
    Key16 value;
    HashNode* next;
};

extern void* AllocateRaw(void* alloc, unsigned size, unsigned align, unsigned offset);
extern void EASTL_allocator_deallocate(void* p);

struct HashTable {
    uint32_t pad0;
    HashNode** buckets;      // +4
    uint32_t bucketCount;    // +8
    uint32_t pad1[4];
    uint32_t allocator;      // +0x1c

    HashNode* DoAllocateNode(const Key16& v);
    HashNode** DoAllocateBuckets(unsigned n);
    void DoRehash(unsigned n);
    inline unsigned BucketIndex(const HashNode* node, unsigned n) const { unsigned c = node->value.a; return c % n; }
    inline void DoFreeBuckets(HashNode** p, unsigned n) { if (n > 1) { HashNode** q = p; EASTL_allocator_deallocate(q); } }
};

// @ 0x00425240
HashNode* HashTable::DoAllocateNode(const Key16& v)
{
    HashNode* p = (HashNode*)AllocateRaw(&allocator, sizeof(HashNode), 8, 0);
    ::new (&p->value) Key16(v);
    p->next = 0;
    return p;
}

// @ 0x004252b0
void HashTable::DoRehash(unsigned n)
{
    HashNode** newBuckets = DoAllocateBuckets(n);
    HashNode* node;
    for (unsigned i = 0; i < bucketCount; ++i) {
        while ((node = buckets[i]) != 0) {
            unsigned idx = BucketIndex(node, n);
            buckets[i] = node->next;
            node->next = newBuckets[idx];
            newBuckets[idx] = node;
        }
    }
    DoFreeBuckets(buckets, bucketCount);
    bucketCount = n;
    buckets = newBuckets;
}

// ---- deque of 0x30-byte elements, 4 per subarray ----
struct Elem {
    uint32_t data[12];
    Elem(const Elem&);
    ~Elem();
};

struct Tag {};

struct DequeIter {
    Elem* cur;
    Elem* begin;
    Elem* end;
    Elem** node;

    DequeIter();
    DequeIter(const DequeIter& x);
    DequeIter(const DequeIter& x, Tag t);
    DequeIter& operator++();
    DequeIter operator++(int);
    DequeIter& MoveBackwardInto(const DequeIter& first, const DequeIter& last, Tag t);
    DequeIter operator+(int n) const;
    DequeIter Copy(const DequeIter& a, const DequeIter& b, Tag t);
};

// Iterator difference (elements between two deque iterators).
static inline int operator-(const DequeIter& x, const DequeIter& y)
{
    return 4 * ((x.node - y.node) - 1) + (x.cur - x.begin) + (y.end - y.cur);
}

struct Deque {
    Elem** ptrArray;     // +0
    uint32_t ptrArraySize; // +4
    DequeIter itBegin;   // +8
    DequeIter itEnd;     // +0x18

    Deque(unsigned n, const int& a);
    bool empty() const;
    unsigned size() const;
    void push_front(const Elem& v);
    void push_back(const Elem& v);
    void pop_front();
    void pop_back();
    void DoPushFront(const Elem& v);
    void DoPushBack(const Elem& v);
    void DoPopFront();
    void DoInit(unsigned n);
    void clear();
    DequeIter erase(DequeIter position);
    void DoFreeSubarray(Elem* p);
};

// @ 0x00425380
DequeIter DequeIter::operator++(int)
{
    DequeIter tmp(*this);
    ++*this;
    return tmp;
}

// @ 0x004253c0
DequeIter& DequeIter::operator++()
{
    ++cur;
    if (cur == end) {
        ++node;
        begin = *node;
        end = begin + 4;
        cur = begin;
    }
    return *this;
}

// @ 0x00425430
bool Deque::empty() const { return itBegin.cur == itEnd.cur; }

// @ 0x00425450
unsigned Deque::size() const { return itEnd - itBegin; }

// @ 0x004254c0
// Not byte-exact (3 bytes): original frame has 0x24 bytes of unused locals below the new-temp.
void Deque::push_front(const Elem& v)
{
    if (itBegin.cur != itBegin.begin)
        ::new (--itBegin.cur) Elem(v);
    else
        DoPushFront(v);
    uint32_t pad[9];
}

// @ 0x00425530
// Not byte-exact (5 bytes): original frame has 0x24 bytes of unused locals below the new-temp.
void Deque::push_back(const Elem& v)
{
    if (itEnd.cur + 1 != itEnd.end)
        ::new (itEnd.cur++) Elem(v);
    else
        DoPushBack(v);
    uint32_t pad[9];
}

// @ 0x004255a0
void Deque::pop_front()
{
    if (itBegin.cur + 1 != itBegin.end) {
        Elem* p = itBegin.cur++;
        p->~Elem();
    } else
        DoPopFront();
}

// @ 0x00425600
// Not byte-exact (2 bytes): the empty-tag temporaries land in different frame slots.
DequeIter Deque::erase(DequeIter pos)
{
    DequeIter itNext(pos, Tag());
    int index = pos - itBegin;
    if (index < (int)(size() >> 1)) {
        Tag g; Tag t1; Tag h;
        itNext.MoveBackwardInto(itBegin, pos, t1);
        pop_front();
    } else {
        Tag g; Tag t2; Tag h;
        pos.Copy(itNext, itEnd, t2);
        pop_back();
    }
    return itBegin + index;
}

// @ 0x004256e0
void Deque::clear()
{
    if (itBegin.node != itEnd.node) {
        for (Elem* p = itBegin.cur; p < itBegin.end; ++p)
            p->~Elem();
        for (Elem* p = itEnd.begin; p < itEnd.cur; ++p)
            p->~Elem();
        DoFreeSubarray(itEnd.begin);
    } else {
        for (Elem* p = itBegin.cur; p < itEnd.cur; ++p)
            p->~Elem();
    }
    for (Elem** n = itBegin.node + 1; n < itEnd.node; ++n) {
        for (Elem* p = *n, *last = *n + 4; p < last; ++p)
            p->~Elem();
        DoFreeSubarray(*n);
    }
    itEnd = itBegin;
}

// @ 0x00425860
Deque::Deque(unsigned n, const int& a) : ptrArray(0), ptrArraySize(0)
{
    DoInit(n);
}

// ---- segmented iterator over 0x2c-byte entries ----
struct Entry {
    uint32_t pad[11];
    bool IsEmpty();
    DequeIter BeginA();
    DequeIter BeginB();
};

struct SegIter {
    Entry* cur;          // +0
    DequeIter inner;     // +4
    void* aux;           // +0x14
    Entry* end;          // +0x18

    SegIter(Entry* c, void* a, Entry* e, const DequeIter& i);
    void Normalize();
};

// @ 0x004258b0
SegIter::SegIter(Entry* c, void* a, Entry* e, const DequeIter& i) : cur(c), inner(i), aux(a), end(e)
{
}

static inline bool NotEqual(const DequeIter& a, const DequeIter& b) { return a.cur != b.cur; }

// @ 0x004258f0
void SegIter::Normalize()
{
    if (NotEqual(inner, cur->BeginA()))
        return;
    do {
        ++cur;
    } while (cur < end && cur->IsEmpty());
    if (cur < end)
        inner = cur->BeginB();
}

// ---- vectors of ref-counted pointers ----
struct RefCounted { void Release(); };
struct RefPtr {
    RefCounted* p;
    ~RefPtr() { if (p) p->Release(); }
};

extern RefPtr* MoveRange(RefPtr* first, RefPtr* last, RefPtr* dest);

struct PtrVector {
    void** begin;   // +0
    RefPtr* end;    // +4
    void** cap;     // +8
    void Free();
    RefPtr* erase(RefPtr* first, RefPtr* last);
};

// @ 0x00425990
// Not byte-exact (6 bytes): p/q frame slots swapped.
void PtrVector::Free()
{
    void** q;
    void** p;
    unsigned bytes;
    if (begin) {
        bytes = (cap - begin) * 4;
        p = begin;
        if (((int*)p)[-1]) {
            q = p;
            EASTL_allocator_deallocate(q);
        }
    }
}

static inline RefPtr* MoveHelper(RefPtr* a, RefPtr* b, RefPtr* c)
{
    bool t0 = false;
    bool t1 = false;
    return MoveRange(a, b, c);
}
static inline void DestroyRange(RefPtr* f, RefPtr* l)
{
    for (RefPtr* p = f; p < l; ++p)
        p->~RefPtr();
}

// @ 0x004259e0
// Not byte-exact (2 bytes): the tag bytes land 0x10 lower in the frame than in the original.
RefPtr* PtrVector::erase(RefPtr* first, RefPtr* last)
{
    RefPtr* dest;
    uint32_t pad[4];
    dest = MoveHelper(last, end, first);
    DestroyRange(dest, end);
    end -= (last - first);
    return first;
}
