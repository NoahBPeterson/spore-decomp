// slice s00fcc260 -- RenderWare rw::SList intrusive doubly-linked list.
// Compile: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

extern "C" void MemFill8(void* dst, unsigned val, unsigned count);   // core::stdc::MemFill8
extern "C" void operator_delete(void* p);                            // ??3@YAXPAX@Z

namespace rw {

// ---- node interface ----------------------------------------------------
// A list node heap block: [vptr @0][pad @4][element data @8 ..].
class IListNode { public:
    virtual void*        GetData();                                     // +0x00
    virtual int          SetData(void* src, unsigned size, void* ctx);  // +0x04
    virtual void*        v08();                                         // +0x08
    virtual IListNode*   Next();                                        // +0x0c
    virtual void         SetNext(IListNode* n);                         // +0x10
    int pad4;                                                           // +4
};
class SNode : public IListNode { public:
    char data[1];                                                       // +8
};

// mAllocator vtable: +0x04 Alloc(size,tag,a,b,c), +0x0c Free(ptr,flag).
struct AllocVtbl {
    void* (*v00)(void* self);
    void* (*Alloc)(void* self, unsigned size, const char* tag, int a, int b, int c); // +0x04
    void* (*v08)(void* self);
    void  (*Free)(void* self, void* p, int flag);   // +0x0c
};
struct IRWAllocator { AllocVtbl* vftable; };

// Iterator over a source collection: +0x00 GetValue(), +0x0c Next().
class IListIterator { public:
    virtual void*          GetValue();      // +0x00
    virtual void*          v04();           // +0x04
    virtual void*          v08();           // +0x08
    virtual IListIterator* Next();          // +0x0c
};

// Source object (Append/Prepend/Merge/...): +0x28 GetIterator(), +0x3c GetCount().
class IListSource { public:
    virtual void*          v00();           // +0x00
    virtual void*          v04();           // +0x04
    virtual void*          v08();           // +0x08
    virtual void*          v0c();           // +0x0c
    virtual void*          v10();           // +0x10
    virtual void*          v14();           // +0x14
    virtual void*          v18();           // +0x18
    virtual void*          v1c();           // +0x1c
    virtual void*          v20();           // +0x20
    virtual void*          v24();           // +0x24
    virtual IListIterator* GetIterator();   // +0x28
    virtual void*          v2c();           // +0x2c
    virtual void*          v30();           // +0x30
    virtual void*          v34();           // +0x34
    virtual void*          v38();           // +0x38
    virtual unsigned       GetCount();      // +0x3c
};

// Comparison functor (slot 0) and removal callback (slot 0).
class ICompare { public:
    virtual int Compare(void* a, void* b);  // +0x00
};
class ICallback { public:
    virtual void Invoke(void* data);        // +0x00
};

// Sort helper: slot 0 receives the node array, count, stride and an adapter.
class ISorter { public:
    virtual int Sort(void* array, unsigned count, unsigned stride, void* adapter);  // +0x00
};
struct SListSortAdapter {
    void* vftable;                          // +0x00
    void* cmp;                              // +0x04
};

// InvokeKey dispatches through three different objects.
class IInvokeValue { public:
    virtual void* Get();                    // +0x00
};
class IInvokeMap { public:
    virtual void* Get(void* x);             // +0x00
};
class IInvokeStore { public:
    virtual void  Set(void* x);             // +0x00
};

class SList { public:
    void*           vftable;                // +0x00
    SNode*          mHead;                  // +0x04
    SNode*          mTail;                  // +0x08
    unsigned        mLength;                // +0x0c
    IRWAllocator*   mAllocator;             // +0x10
    unsigned        mElementSize;           // +0x14
    unsigned        mUserAlignment;         // +0x18

    SList();                                                           // va 0x00fcce10
    SNode* FindNode(const void* key, ICompare* cmp);                   // va 0x00fcc260
    SNode* GetPrev(SNode* node);                                       // va 0x00fcc2e0
    char   IsMember(SNode* node);                                      // va 0x00fcc330
    int    Append(IListSource* src, void* ctx);                        // va 0x00fcc370
    int    Prepend(IListSource* src, void* ctx);                       // va 0x00fcc470
    int    InsertBefore(IListSource* src, SNode* at, void* ctx);       // va 0x00fcc5c0
    int    InsertAfter(IListSource* src, SNode* at, void* ctx);        // va 0x00fcc700
    int    InsertAt(IListSource* src, unsigned idx, void* ctx);        // va 0x00fcc810
    int    Merge(IListSource* src, ICompare* cmp, void* ctx);          // va 0x00fcc960
    int    Remove(SNode* node, void** cb);                             // va 0x00fccae0
    int    RemoveIf(void* key, ICompare* cmp, ICallback* cb);          // va 0x00fccb80
    void   Clear(void** cb);                                           // va 0x00fccc40
    int    Reverse();                                                  // va 0x00fccca0
    int    Permute(int* idx);                                          // va 0x00fccd00
    void*  Dtor(unsigned flags);                                       // va 0x00fccde0
    void   InvokeKey(void** a, void** b);                              // va 0x00fcce30
    int    Sort(void* sorter, void* cmp);                              // va 0x00fcce70
    SNode* LoadNewNode(int a, int b);                                  // va 0x00fccf40
    void*  ScalarDeletingDtor(unsigned flags);                         // va 0x00fccfb0
    int    AppendOne(int a, int b);                                    // va 0x00fccfe0
    int    PrependOne(int a, int b);                                   // va 0x00fcd030
    int    InsertBeforeOne(int a, SNode* at, void* ctx);               // va 0x00fcd080
    int    InsertAfterOne(int a, SNode* at, void* ctx);                // va 0x00fcd120
    int    InsertAtOne(int a, unsigned idx, int b);                    // va 0x00fcd170
};

// @ 0x00fcce10
SList::SList()
{
    vftable = (void*)0x1491ef8;
    mHead = 0;
    mTail = 0;
    mLength = 0;
    mAllocator = 0;
    mElementSize = 0;
    mUserAlignment = 0;
}

// @ 0x00fcc260
SNode* SList::FindNode(const void* key, ICompare* cmp)
{
    SNode* node = mHead;
    if (node == 0)
        return 0;
    for (;;) {
        void* data = node->GetData();
        if (cmp != 0) {
            if (cmp->Compare((void*)key, data) == 0)
                return node;
        } else {
            unsigned n = mElementSize;
            bool same = true;
            if (n == 0)
                return node;
            do {
                if (!same)
                    break;
                --n;
                same = *(const unsigned char*)data == *(const unsigned char*)key;
            } while (n != 0);
            if (same)
                return node;
        }
        node = (SNode*)node->Next();
        if (node == 0)
            return 0;
    }
}

// @ 0x00fcc2e0
SNode* SList::GetPrev(SNode* node)
{
    SNode* p = mHead;
    if (node == p || mLength == 0)
        return 0;
    while (p != 0 && (SNode*)p->Next() != node)
        p = (SNode*)p->Next();
    return p;
}

// @ 0x00fcc330
char SList::IsMember(SNode* node)
{
    char found;
    SNode* p;
    if (mLength == 0)
        return 0;
    p = mHead;
    found = 0;
    do {
        if (p == 0)
            return found;
        if (node == p)
            found = 1;
        p = (SNode*)p->Next();
    } while (found == 0);
    return found;
}

// @ 0x00fcc370
int SList::Append(IListSource* src, void* ctx)
{
    unsigned size;
    IListIterator* it;
    SNode* node;
    if (src == 0)
        return -1;
    size = mElementSize;
    if (src->GetCount() < 1)
        return 0;
    it = src->GetIterator();
    if (it == 0)
        return 0;
    for (;;) {
        node = (SNode*)mAllocator->vftable->Alloc(mAllocator, size + 8, "SNode", 0, 4, 0);
        if (node == 0)
            return -1;
        if (node->SetData(it->GetValue(), size, ctx) == -1) {
            mAllocator->vftable->Free(mAllocator, node, 0);
            return -1;
        }
        if (mLength == 0)
            mHead = node;
        else
            mTail->SetNext(node);
        ++mLength;
        mTail = node;
        it = it->Next();
        if (it == 0)
            return 0;
    }
}

// @ 0x00fcc470
int SList::Prepend(IListSource* src, void* ctx)
{
    unsigned size;
    IListIterator* it;
    SNode* node;
    SNode* prev;
    SNode* last;
    if (src == 0)
        return -1;
    size = mElementSize;
    if (src->GetCount() < 1)
        return 0;
    prev = mHead;
    it = src->GetIterator();
    node = 0;
    last = 0;
    for (;;) {
        if (it == 0) {
            if (mTail == 0)
                mTail = last;
            return 0;
        }
        node = (SNode*)mAllocator->vftable->Alloc(mAllocator, size + 8, "SNode", 0, 4, 0);
        if (node == 0)
            return -1;
        if (node->SetData(it->GetValue(), size, ctx) == -1) {
            mAllocator->vftable->Free(mAllocator, node, 0);
            return -1;
        }
        node->SetNext(prev);
        if (mHead == 0)
            mHead = node;
        else if (last == 0)
            mHead = node;
        else
            last->SetNext(node);
        ++mLength;
        last = node;
        it = it->Next();
    }
}

// @ 0x00fcc5c0
int SList::InsertBefore(IListSource* src, SNode* at, void* ctx)
{
    unsigned size;
    SNode* prev;
    IListIterator* it;
    SNode* first;
    SNode* last;
    SNode* node;
    if (src->GetCount() == 0)
        return 0;
    size = mElementSize;
    prev = GetPrev(at);
    if (prev == 0 && at != mHead)
        return -1;
    it = src->GetIterator();
    first = 0;
    last = 0;
    while (it != 0) {
        node = (SNode*)mAllocator->vftable->Alloc(mAllocator, size + 8, "SNode", 0, 4, 0);
        node->SetData(it->GetValue(), size, ctx);
        if (first == 0)
            first = node;
        else
            last->SetNext(node);
        last = node;
        it = it->Next();
    }
    if (prev == 0) {
        last->SetNext(mHead);
        mHead = first;
    } else {
        last->SetNext(prev->Next());
        prev->SetNext(first);
    }
    mLength += src->GetCount();
    return 0;
}

// @ 0x00fcc700
int SList::InsertAfter(IListSource* src, SNode* at, void* ctx)
{
    unsigned size;
    IListIterator* it;
    SNode* first;
    SNode* last;
    SNode* node;
    if (src->GetCount() == 0)
        return 0;
    size = mElementSize;
    it = src->GetIterator();
    first = 0;
    last = 0;
    while (it != 0) {
        node = (SNode*)mAllocator->vftable->Alloc(mAllocator, size + 8, "SNode", 0, 4, 0);
        node->SetData(it->GetValue(), size, ctx);
        if (first == 0)
            first = node;
        else
            last->SetNext(node);
        last = node;
        it = it->Next();
    }
    last->SetNext(at->Next());
    at->SetNext(first);
    if (mTail == at)
        mTail = last;
    mLength += src->GetCount();
    return 0;
}

// @ 0x00fcc810
int SList::InsertAt(IListSource* src, unsigned idx, void* ctx)
{
    unsigned size;
    IListIterator* it;
    SNode* first;
    SNode* last;
    SNode* node;
    if (idx > mLength)
        return -1;
    if (src->GetCount() < 1)
        return 0;
    size = mElementSize;
    it = src->GetIterator();
    first = 0;
    last = 0;
    while (it != 0) {
        node = (SNode*)mAllocator->vftable->Alloc(mAllocator, size + 8, "SNode", 0, 4, 0);
        node->SetData(it->GetValue(), size, ctx);
        if (first == 0)
            first = node;
        else
            last->SetNext(node);
        last = node;
        it = it->Next();
    }
    if (idx == 0) {
        last->SetNext(mHead);
        mHead = first;
    } else if (idx == mLength) {
        mTail->SetNext(first);
        mTail = last;
    } else {
        SNode* (*getAt)(void*, unsigned) = (SNode* (*)(void*, unsigned))((*(void***)this)[0x30 / 4]);
        SNode* at = getAt(this, idx - 1);
        last->SetNext(at->Next());
        at->SetNext(first);
    }
    mLength += src->GetCount();
    return 0;
}

// @ 0x00fcc960
int SList::Merge(IListSource* src, ICompare* cmp, void* ctx)
{
    unsigned size;
    IListIterator* it;
    SNode* first;
    SNode* last;
    SNode* node;
    SNode* a;
    SNode* prev;
    if (src->GetCount() == 0)
        return 0;
    size = mElementSize;
    it = src->GetIterator();
    first = 0;
    last = 0;
    while (it != 0) {
        node = (SNode*)mAllocator->vftable->Alloc(mAllocator, size + 8, "SNode", 0, 4, 0);
        node->SetData(it->GetValue(), size, ctx);
        if (first == 0)
            first = node;
        else
            last->SetNext(node);
        last = node;
        it = it->Next();
    }
    a = mHead;
    prev = 0;
    while (first != 0) {
        if (a == 0)
            break;
        if (cmp->Compare(first->GetData(), a->GetData()) == -1) {
            SNode* nx = (SNode*)first->Next();
            first->SetNext(a);
            if (prev == 0) {
                mHead = first;
                prev = first;
            } else {
                prev->SetNext(first);
                prev = first;
            }
            first = nx;
        } else {
            prev = a;
            a = (SNode*)a->Next();
        }
    }
    if (first != 0) {
        mTail = last;
        prev->SetNext(first);
    } else if (a != 0) {
        prev->SetNext(a);
    }
    mLength += src->GetCount();
    return 0;
}

// @ 0x00fccae0
int SList::Remove(SNode* node, void** cb)
{
    SNode* prev;
    if (node == 0)
        return -1;
    prev = GetPrev(node);
    if (prev == 0) {
        if (node != mHead)
            return -1;
        prev = (SNode*)node->Next();
        mHead = prev;
        if (prev == 0)
            mTail = 0;
    } else {
        if (node == mTail)
            mTail = prev;
        prev->SetNext(node->Next());
    }
    if (cb != 0) {
        void (*fn)(void*) = (void (*)(void*))(*cb);
        fn(node->GetData());
    }
    --mLength;
    mAllocator->vftable->Free(mAllocator, node, 0);
    return 0;
}

// @ 0x00fccb80
int SList::RemoveIf(void* key, ICompare* cmp, ICallback* cb)
{
    SNode* node = mHead;
    SNode* prev = 0;
    for (;;) {
        void* data;
        if (node == 0)
            return 0;
        data = node->GetData();
        if (cmp->Compare(key, data) != 0) {
            prev = node;
            node = (SNode*)node->Next();
            continue;
        }
        if (cb != 0)
            cb->Invoke(data);
        if (prev == 0) {
            SNode* nx = (SNode*)node->Next();
            mHead = nx;
            if (mTail == node)
                mTail = nx;
            mAllocator->vftable->Free(mAllocator, node, 0);
            node = mHead;
            --mLength;
        } else {
            prev->SetNext(node->Next());
            if (mTail == node)
                mTail = prev;
            mAllocator->vftable->Free(mAllocator, node, 0);
            node = (SNode*)prev->Next();
            --mLength;
        }
    }
}

// @ 0x00fccc40
void SList::Clear(void** cb)
{
    SNode* node = mHead;
    while (node != 0) {
        SNode* nx = (SNode*)node->Next();
        if (cb != 0) {
            void (*fn)(void*) = (void (*)(void*))*cb;
            fn(node->GetData());
        }
        mAllocator->vftable->Free(mAllocator, node, 0);
        node = nx;
    }
    mTail = 0;
    mHead = 0;
    mLength = 0;
}

// @ 0x00fccca0
int SList::Reverse()
{
    SNode* p;
    SNode* nx;
    if (mLength <= 1)
        return 0;
    p = mHead;
    nx = (SNode*)p->Next();
    p->SetNext(0);
    while (nx != 0) {
        SNode* nn = (SNode*)nx->Next();
        nx->SetNext(p);
        p = nx;
        nx = nn;
    }
    nx = mHead;
    mHead = mTail;
    mTail = nx;
    return 0;
}

// @ 0x00fccd00
int SList::Permute(int* idx)
{
    unsigned* temp;
    SNode* node;
    unsigned i;
    int rc = 0;
    if (mLength < 2)
        return -1;
    temp = (unsigned*)mAllocator->vftable->Alloc(mAllocator, mLength * 4, "SList::Permute temp", 0, 4, 0);
    MemFill8(temp, 0, mLength * 4);
    node = mHead;
    while (node != 0) {
        unsigned k = (unsigned)*idx;
        if (k >= mLength || temp[k] != 0) {
            rc = -1;
            break;
        }
        temp[k] = (unsigned)node;
        node = (SNode*)node->Next();
        ++idx;
    }
    node = (SNode*)temp[0];
    i = 1;
    mHead = node;
    while (i < mLength) {
        node->SetNext((IListNode*)temp[i]);
        node = (SNode*)temp[i];
        ++i;
    }
    mTail = (SNode*)temp[mLength - 1];
    mTail->SetNext(0);
    mAllocator->vftable->Free(mAllocator, temp, 0);
    return rc;
}

// @ 0x00fccde0
void* SList::Dtor(unsigned flags)
{
    mHead = 0;
    vftable = (void*)0x1491e4c;
    if (flags & 1)
        operator_delete(this);
    return this;
}

// @ 0x00fcce30
void SList::InvokeKey(void** a, void** b)
{
    void* r0 = ((IInvokeValue*)*b)->Get();
    void* r1 = ((IInvokeMap*)*a)->Get(r0);
    ((IInvokeStore*)mHead)->Set(r1);
}

// @ 0x00fcce70
int SList::Sort(void* sorter, void* cmp)
{
    unsigned* temp;
    SNode* node;
    unsigned i;
    int rc;
    if (mLength < 2)
        return 0;
    temp = (unsigned*)mAllocator->vftable->Alloc(mAllocator, mLength * 4, "SList::Sort temp", 0, 4, 0);
    node = mHead;
    if (node != 0) {
        unsigned* p = temp;
        do {
            *p = (unsigned)node;
            node = (SNode*)node->Next();
            ++p;
        } while (node != 0);
    }
    {
        SListSortAdapter adapter;
        adapter.vftable = (void*)0x1491fb8;
        adapter.cmp = cmp;
        rc = ((ISorter*)sorter)->Sort(temp, mLength, 4, &adapter);
    }
    if (rc == 0) {
        node = (SNode*)temp[0];
        i = 1;
        mHead = node;
        while (i < mLength) {
            node->SetNext((IListNode*)temp[i]);
            node = (SNode*)temp[i];
            ++i;
        }
        mTail = (SNode*)temp[mLength - 1];
        mTail->SetNext(0);
    }
    mAllocator->vftable->Free(mAllocator, temp, 0);
    return rc;
}

// @ 0x00fccf40
SNode* SList::LoadNewNode(int a, int b)
{
    SNode* node = (SNode*)mAllocator->vftable->Alloc(mAllocator, mElementSize + 8, "SNode", 0, 4, 0);
    if (node == 0)
        return 0;
    *(void**)node = (void*)0x1491fa0;
    node->pad4 = 0;
    if (node->SetData((void*)a, mElementSize, (void*)b) == -1) {
        mAllocator->vftable->Free(mAllocator, node, 0);
        return 0;
    }
    return node;
}

// @ 0x00fccfb0
void* SList::ScalarDeletingDtor(unsigned flags)
{
    vftable = (void*)0x1491ef8;
    Clear(0);
    vftable = (void*)0x1491e68;
    if (flags & 1)
        operator_delete(this);
    return this;
}

// @ 0x00fccfe0
int SList::AppendOne(int a, int b)
{
    SNode* node = LoadNewNode(a, b);
    if (node == 0)
        return -1;
    if (mTail == 0) {
        ++mLength;
        mHead = node;
        mTail = node;
        return 0;
    }
    mTail->SetNext(node);
    ++mLength;
    mTail = node;
    return 0;
}

// @ 0x00fcd030
int SList::PrependOne(int a, int b)
{
    SNode* node = LoadNewNode(a, b);
    if (node == 0)
        return -1;
    if (mHead == 0) {
        ++mLength;
        mTail = node;
        mHead = node;
        return 0;
    }
    node->SetNext(mHead);
    ++mLength;
    mHead = node;
    return 0;
}

// @ 0x00fcd080
int SList::InsertBeforeOne(int a, SNode* at, void* ctx)
{
    SNode* node = LoadNewNode(a, (int)ctx);
    if (at == mHead) {
        node->SetNext(mHead);
        ++mLength;
        mHead = node;
        return 0;
    }
    SNode* prev = GetPrev(at);
    if (prev == 0) {
        if (at != mHead)
            return -1;
        node->SetNext(mHead);
        ++mLength;
        mHead = node;
        return 0;
    }
    node->SetNext(prev->Next());
    prev->SetNext(node);
    ++mLength;
    return 0;
}

// @ 0x00fcd120
int SList::InsertAfterOne(int a, SNode* at, void* ctx)
{
    SNode* node = LoadNewNode(a, (int)ctx);
    node->SetNext(at->Next());
    at->SetNext(node);
    ++mLength;
    return 0;
}

// @ 0x00fcd170
int SList::InsertAtOne(int a, unsigned idx, int b)
{
    if (idx > mLength)
        return -1;
    SNode* node = LoadNewNode(a, b);
    if (idx == 0) {
        node->SetNext(mHead);
        ++mLength;
        mHead = node;
        return 0;
    }
    if (idx == mLength) {
        mTail->SetNext(node);
        ++mLength;
        mTail = node;
        return 0;
    }
    {
        SNode* (*getAt)(void*, unsigned) = (SNode* (*)(void*, unsigned))((*(void***)this)[0x30 / 4]);
        SNode* at = getAt(this, idx - 1);
        node->SetNext(at->Next());
        at->SetNext(node);
    }
    ++mLength;
    return 0;
}

}  // namespace rw
