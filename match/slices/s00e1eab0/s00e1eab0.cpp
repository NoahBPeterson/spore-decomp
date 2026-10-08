// Slice s00e1eab0: 00e1f5c0, an EASTL-style partial_sort over 12-byte refcounted records (cdecl, 4 args).
// Element layout {unsigned key; bool flag; ref* ptr} is 12 bytes. Refcount vtable slots: AddRef = +4, Release = +8.
// The comparison is an unsigned compare on key; the 4-byte comparator value is only passed through.

struct IRefCounted {
    virtual void Slot0();
    virtual void AddRef();
    virtual void Release();
};

struct Elem {
    unsigned key;
    bool flag;
    IRefCounted* ptr;
};

struct Compare {
    unsigned mDummy;
};

void __cdecl MakeHeap(Elem* first, Elem* last, Compare comp);                 // 0x00e1f2c0
void __cdecl AdjustHeap(Elem* first, unsigned topIndex, unsigned holeIndex, unsigned len, Elem value, Compare comp);  // 0x00e1e8c0
void __cdecl SortHeap(Elem* first, Elem* last, Compare comp);               // 0x00e1f330

void __cdecl PartialSort(Elem* first, Elem* middle, Elem* last, Compare comp)
{
    MakeHeap(first, middle, comp);
    for (Elem* it = middle; it < last; ++it) {
        if (it->key < first->key) {
            Elem temp;
            temp.key = it->key;
            temp.flag = it->flag;
            temp.ptr = it->ptr;
            if (temp.ptr)
                temp.ptr->AddRef();
            it->key = first->key;
            it->flag = first->flag;
            IRefCounted* old = it->ptr;
            if (first->ptr != old) {
                if (first->ptr)
                    first->ptr->AddRef();
                it->ptr = first->ptr;
                if (old)
                    old->Release();
            }
            Elem value = temp;
            if (value.ptr)
                value.ptr->AddRef();
            AdjustHeap(first, 0, (unsigned)(middle - first) / 12, 0, value, comp);
            if (temp.ptr)
                temp.ptr->Release();
        }
    }
    SortHeap(first, middle, comp);
}
