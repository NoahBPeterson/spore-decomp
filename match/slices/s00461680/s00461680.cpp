// Slice s00461680: SortSkeletonNodes (0x00461680), creature skeleton node ordering.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE (unoptimized EASTL-heavy creature code).
#include "types.h"
inline void* operator new(unsigned, void* p) { return p; }

namespace eastl {

template <typename T, T v> struct integral_constant {
    static const T value = v;
    typedef T value_type;
    typedef integral_constant<T, v> type;
};
typedef integral_constant<bool, false> false_type;
template <typename T> struct remove_cv { typedef T type; };
template <typename T> struct is_integral_helper : public false_type {};
template <typename T> struct is_integral : public is_integral_helper<typename remove_cv<T>::type> {};

struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename T> struct iterator_traits;
template <typename T> struct iterator_traits<T*> {
    typedef random_access_iterator_tag iterator_category;
    typedef T value_type;
};

template <typename ForwardIterator>
inline void destruct(ForwardIterator first, ForwardIterator last)
{
    typedef typename iterator_traits<ForwardIterator>::value_type value_type;
    for (; first < last; ++first)
        (*first).~value_type();
}

struct allocator {
    void deallocate(void* p, unsigned) { delete[] (char*)p; }
};

// eastl::fixed_vector_allocator: overflow allocator plus the inline pool pointer.
struct fixed_vector_allocator {
    allocator mOverflowAllocator;
    void* mpPoolBegin;

    fixed_vector_allocator(void* pNodeBuffer) : mpPoolBegin(pNodeBuffer) {}
    fixed_vector_allocator(const fixed_vector_allocator& x)
    {
        mpPoolBegin = x.mpPoolBegin;
        mOverflowAllocator = x.mOverflowAllocator;
    }

    void deallocate(void* p, unsigned n)
    {
        if (p != mpPoolBegin)
            mOverflowAllocator.deallocate(p, n);
    }
};

template <typename T, typename Allocator>
struct VectorBase {
    typedef unsigned size_type;

    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    VectorBase(const Allocator& a) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}

    ~VectorBase() // 0x004c0b80 (fixed allocator)
    {
        if (mpBegin)
            DoFree(mpBegin, (size_type)(mpCapacity - mpBegin));
    }
    void DoFree(T* p, size_type n) { mAllocator.deallocate(p, n * sizeof(T)); }
};

// eastl::vector<T, Allocator>
template <typename T, typename Allocator = allocator>
class vector : public VectorBase<T, Allocator> {
public:
    typedef VectorBase<T, Allocator> base_type;
    typedef T* iterator;
    typedef T& reference;
    typedef unsigned size_type;
    using base_type::mpBegin;
    using base_type::mpEnd;
    using base_type::mpCapacity;

    vector() {}
    vector(const Allocator& a) : base_type(a) {}
    ~vector() { eastl::destruct(mpBegin, mpEnd); }

    iterator begin() { return mpBegin; }
    iterator end() { return mpEnd; }
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    reference operator[](size_type n) { return *(mpBegin + n); }

    void push_back(const T& value) // 0x00422380
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    iterator erase(iterator first, iterator last); // 0x004769b0
    void clear() { erase(mpBegin, mpEnd); }

    template <typename InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last)
    {
        DoInsert(position, first, last, is_integral<InputIterator>());
    }

protected:
    void DoInsertValue(iterator position, const T& value); // 0x004281d0

    template <typename InputIterator>
    void DoInsert(iterator position, InputIterator first, InputIterator last, false_type) // 0x004778c0
    {
        typedef typename iterator_traits<InputIterator>::iterator_category IC;
        DoInsertFromIterator(position, first, last, IC());
    }

    template <typename ForwardIterator>
    void DoInsertFromIterator(iterator position, ForwardIterator first, ForwardIterator last,
                              forward_iterator_tag); // 0x0042b9e0
};

// eastl::fixed_vector<T, nodeCount>: 0x18-byte vector header followed by the inline buffer.
template <typename T, int nodeCount>
class fixed_vector : public vector<T, fixed_vector_allocator> {
public:
    using vector<T, fixed_vector_allocator>::mpBegin;
    using vector<T, fixed_vector_allocator>::mpEnd;
    using vector<T, fixed_vector_allocator>::mpCapacity;
    uint32_t mBufferPad; // +0x14: the buffer starts at +0x18 in retail
    T mBuffer[nodeCount];

    fixed_vector() // 0x0041d050
        : vector<T, fixed_vector_allocator>(fixed_vector_allocator(mBuffer))
    {
        mpBegin = mpEnd = &mBuffer[0];
        mpCapacity = mpBegin + nodeCount;
    }
};

} // namespace eastl

// One skeleton node: parent index (-1 = root) and node class (1..5).
struct SkelNode {
    short parent;
    short type;
};

// 0x00460a80: depth-first reorder of the ids whose parent is `target`, returns count placed.
int ReorderChildren(const SkelNode* nodes, int target, int* ids, int count);

// @ 0x00461680
// Orders the skeleton's node indices into pOrder by class (5,4,3,2,1 from the highest root
// class downwards), each class's nodes depth-first under the previously placed ones.
// Outputs the running group boundaries.
// Local names are /Od slot-order picks (tools/matching/od_names.py fit 8); roles:
//   n19 = scratch fixed_vector<int,64>, t8 = root node index, t1 = root node class,
//   v20/t31/p32/t16 = sizes of the four placed groups, v26 = running count of the last pass.
void SortSkeletonNodes(const SkelNode* nodes, int count, eastl::vector<int>* pOrder,
                       int* pEnd1, int* pEnd2, int* pEnd3, int* pEnd4)
{
    pOrder->clear();
    if (pEnd1)
        *pEnd1 = 0;
    if (pEnd2)
        *pEnd2 = 0;
    if (pEnd3)
        *pEnd3 = 0;

    int t1;
    int v20 = 0;
    int t31 = 0;
    int p32 = 0;
    int t16 = 0;
    int v26 = 0;
    eastl::fixed_vector<int, 64> n19;
    int t8 = -1;
    t1 = 0;

    for (int i = 0; i < count; i++) {
        if (nodes[i].parent == -1 && nodes[i].type > t1) {
            t8 = i;
            t1 = nodes[i].type;
        }
    }

    if (t8 == -1 || t1 == 0)
        return;

    if (t1 == 5) {
        int n5;
        n19.push_back(t8);
        for (int i = 0; i < count; i++) {
            if (nodes[i].type == 5 && i != t8)
                n19.push_back(i);
        }
        v20 = ReorderChildren(nodes, t8, n19.begin() + 1, n19.size() - 1) + 1;
        for (int i = 1; i < v20; i++) {
            if (nodes[n19[i]].parent != n19[i - 1])
                v20 = i;
        }
        pOrder->insert(pOrder->end(), n19.begin(), n19.begin() + v20);
        n19.clear();

        for (int i = 0; i < count; i++) {
            if (nodes[i].type == 3)
                n19.push_back(i);
        }
        t31 = 0;
        for (int i = 0; i < v20; i++)
            t31 += ReorderChildren(nodes, (*pOrder)[i], n19.begin() + t31, n19.size() - t31);
        pOrder->insert(pOrder->end(), n19.begin(), n19.begin() + t31);
        n19.clear();

        for (int i = 0; i < count; i++) {
            if (nodes[i].type == 2)
                n19.push_back(i);
        }
        n5 = 0;
        for (int i = 0; i < v20; i++)
            n5 += ReorderChildren(nodes, (*pOrder)[i], n19.begin() + n5, n19.size() - n5);
        p32 = n5;
        for (int i = v20; i < v20 + t31; i++)
            n5 += ReorderChildren(nodes, (*pOrder)[i], n19.begin() + n5, n19.size() - n5);
        t16 = n5 - p32;
        pOrder->insert(pOrder->end(), n19.begin(), n19.begin() + n5);
        n19.clear();

        for (int i = 0; i < count; i++) {
            if (nodes[i].type == 1)
                n19.push_back(i);
        }
        for (int i = 0; i < v20 + t31 + n5; i++)
            v26 += ReorderChildren(nodes, (*pOrder)[i], n19.begin() + v26, n19.size() - v26);
        pOrder->insert(pOrder->end(), n19.begin(), n19.begin() + v26);
        n19.clear();
    } else if (t1 == 4) {
        int n4;
        for (int i = 0; i < count; i++) {
            if (nodes[i].type == 3)
                n19.push_back(i);
        }
        t31 = ReorderChildren(nodes, t8, n19.begin(), n19.size());
        pOrder->insert(pOrder->end(), n19.begin(), n19.begin() + t31);
        n19.clear();

        n19.push_back(t8);
        for (int i = 0; i < count; i++) {
            if (nodes[i].type == 2)
                n19.push_back(i);
        }
        n4 = ReorderChildren(nodes, t8, n19.begin() + 1, n19.size() - 1) + 1;
        p32 = n4;
        for (int i = 0; i < t31; i++)
            n4 += ReorderChildren(nodes, (*pOrder)[i], n19.begin() + n4, n19.size() - n4);
        t16 = n4 - p32;
        pOrder->insert(pOrder->end(), n19.begin(), n19.begin() + n4);
        n19.clear();

        for (int i = 0; i < count; i++) {
            if (nodes[i].type == 1)
                n19.push_back(i);
        }
        for (int i = 0; i < v20 + t31 + n4; i++)
            v26 += ReorderChildren(nodes, (*pOrder)[i], n19.begin() + v26, n19.size() - v26);
        pOrder->insert(pOrder->end(), n19.begin(), n19.begin() + v26);
        n19.clear();
    } else if (t1 == 3) {
        int n3;
        n19.push_back(t8);
        for (int i = 0; i < count; i++) {
            if (nodes[i].type == 3 && i != t8)
                n19.push_back(i);
        }
        t31 = ReorderChildren(nodes, t8, n19.begin() + 1, n19.size() - 1) + 1;
        pOrder->insert(pOrder->end(), n19.begin(), n19.begin() + t31);
        n19.clear();

        for (int i = 0; i < count; i++) {
            if (nodes[i].type == 2)
                n19.push_back(i);
        }
        n3 = 0;
        for (int i = 0; i < t31; i++)
            n3 += ReorderChildren(nodes, (*pOrder)[i], n19.begin() + n3, n19.size() - n3);
        t16 = n3;
        pOrder->insert(pOrder->end(), n19.begin(), n19.begin() + n3);
        n19.clear();

        for (int i = 0; i < count; i++) {
            if (nodes[i].type == 1)
                n19.push_back(i);
        }
        for (int i = 0; i < t31 + n3; i++)
            v26 += ReorderChildren(nodes, (*pOrder)[i], n19.begin() + v26, n19.size() - v26);
        pOrder->insert(pOrder->end(), n19.begin(), n19.begin() + v26);
        n19.clear();
    } else {
        n19.push_back(t8);
        for (int i = 0; i < count; i++) {
            if (nodes[i].type == 2 && i != t8)
                n19.push_back(i);
        }
        p32 = ReorderChildren(nodes, t8, n19.begin() + 1, n19.size() - 1) + 1;
        pOrder->insert(pOrder->end(), n19.begin(), n19.begin() + p32);
        n19.clear();

        for (int i = 0; i < count; i++) {
            if (nodes[i].type == 1 && i != t8)
                n19.push_back(i);
        }
        for (int i = 0; i < p32; i++)
            v26 += ReorderChildren(nodes, (*pOrder)[i], n19.begin() + v26, n19.size() - v26);
        pOrder->insert(pOrder->end(), n19.begin(), n19.begin() + v26);
        n19.clear();
    }

    if (pEnd1)
        *pEnd1 = v20;
    if (pEnd2)
        *pEnd2 = v20 + t31;
    if (pEnd3)
        *pEnd3 = v20 + t31 + p32;
    if (pEnd4)
        *pEnd4 = v20 + t31 + p32 + t16;
}
