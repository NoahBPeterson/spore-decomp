// Slice s00e1a1d0: eight instances of EASTL's insertion_sort / insertion_sort_simple (sort.h)
// over arrays of ref-counted pointers, one pair per comparator. The comparators' operator()
// are out of line (0x00e19dd0, 0x00e19d30, 0x00e19f60, 0x00e1a040).

struct RefCounted_s00e1_a1d0 {
    virtual int AddRef();
    virtual int Release();
};

// intrusive_ptr with the EASTL assignment shape (and a conversion to the raw pointer, which
// the comparators take)
struct RefPtr_s00e1_a1d0 {
    RefCounted_s00e1_a1d0* mpObject;

    RefPtr_s00e1_a1d0(const RefPtr_s00e1_a1d0& ip) : mpObject(ip.mpObject)
    {
        if (mpObject)
            mpObject->AddRef();
    }
    ~RefPtr_s00e1_a1d0()
    {
        if (mpObject)
            mpObject->Release();
    }
    RefPtr_s00e1_a1d0& operator=(const RefPtr_s00e1_a1d0& ip) { return operator=(ip.mpObject); }
    RefPtr_s00e1_a1d0& operator=(RefCounted_s00e1_a1d0* pObject)
    {
        if (pObject != mpObject) {
            RefCounted_s00e1_a1d0* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    operator RefCounted_s00e1_a1d0*() const { return mpObject; }
};

struct CompareA_s00e1_a1d0 { bool operator()(RefCounted_s00e1_a1d0* a, RefCounted_s00e1_a1d0* b); };  // 0x00e19dd0
struct CompareB_s00e1_a1d0 { bool operator()(RefCounted_s00e1_a1d0* a, RefCounted_s00e1_a1d0* b); };  // 0x00e19d30
struct CompareC_s00e1_a1d0 { bool operator()(RefCounted_s00e1_a1d0* a, RefCounted_s00e1_a1d0* b); };  // 0x00e19f60
struct CompareD_s00e1_a1d0 { bool operator()(RefCounted_s00e1_a1d0* a, RefCounted_s00e1_a1d0* b); };  // 0x00e1a040
struct CompareE_s00e1_a1d0 { bool operator()(RefCounted_s00e1_a1d0* a, RefCounted_s00e1_a1d0* b); };  // 0x00e13160 (mission cards)
struct CompareF_s00e1_a1d0 { bool operator()(RefCounted_s00e1_a1d0* a, RefCounted_s00e1_a1d0* b); };  // 0x0100dc20 (game nouns)

template <typename BidirectionalIterator, typename StrictWeakOrdering>
void insertion_sort(BidirectionalIterator first, BidirectionalIterator last, StrictWeakOrdering compare)
{
    if (first != last) {
        BidirectionalIterator iCurrent, iNext, iSorted = first;

        for (++iSorted; iSorted != last; ++iSorted) {
            const RefPtr_s00e1_a1d0 temp(*iSorted);

            iNext = iCurrent = iSorted;

            for (--iCurrent; (iNext != first) && compare(temp, *iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;

            *iNext = temp;
        }
    }
}

template <typename RandomAccessIterator, typename StrictWeakOrdering>
void insertion_sort_simple(RandomAccessIterator first, RandomAccessIterator last, StrictWeakOrdering compare)
{
    for (RandomAccessIterator current = first; current != last; ++current) {
        RandomAccessIterator end(current), prev(current);
        const RefPtr_s00e1_a1d0 value(*current);

        for (--prev; compare(value, *prev); --end, --prev)
            *end = *prev;

        *end = value;
    }
}

// 0x00e1a1d0, 0x00e1a370, 0x00e1a510, 0x00e1a6b0, 0x00e14d90, 0x0100ed20: insertion_sort;
// 0x00e1a2a0, 0x00e1a440, 0x00e1a5e0, 0x00e1a780, 0x00e14e60, 0x0100edf0: insertion_sort_simple
// (manifest rows name each instance)
template void insertion_sort(RefPtr_s00e1_a1d0*, RefPtr_s00e1_a1d0*, CompareA_s00e1_a1d0);
template void insertion_sort(RefPtr_s00e1_a1d0*, RefPtr_s00e1_a1d0*, CompareB_s00e1_a1d0);
template void insertion_sort(RefPtr_s00e1_a1d0*, RefPtr_s00e1_a1d0*, CompareC_s00e1_a1d0);
template void insertion_sort(RefPtr_s00e1_a1d0*, RefPtr_s00e1_a1d0*, CompareD_s00e1_a1d0);
template void insertion_sort(RefPtr_s00e1_a1d0*, RefPtr_s00e1_a1d0*, CompareE_s00e1_a1d0);
template void insertion_sort(RefPtr_s00e1_a1d0*, RefPtr_s00e1_a1d0*, CompareF_s00e1_a1d0);
template void insertion_sort_simple(RefPtr_s00e1_a1d0*, RefPtr_s00e1_a1d0*, CompareA_s00e1_a1d0);
template void insertion_sort_simple(RefPtr_s00e1_a1d0*, RefPtr_s00e1_a1d0*, CompareB_s00e1_a1d0);
template void insertion_sort_simple(RefPtr_s00e1_a1d0*, RefPtr_s00e1_a1d0*, CompareC_s00e1_a1d0);
template void insertion_sort_simple(RefPtr_s00e1_a1d0*, RefPtr_s00e1_a1d0*, CompareD_s00e1_a1d0);
template void insertion_sort_simple(RefPtr_s00e1_a1d0*, RefPtr_s00e1_a1d0*, CompareE_s00e1_a1d0);
template void insertion_sort_simple(RefPtr_s00e1_a1d0*, RefPtr_s00e1_a1d0*, CompareF_s00e1_a1d0);
