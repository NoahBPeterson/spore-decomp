// slice s00fcc260 -- RenderWare rw::SList intrusive doubly-linked list.
// Compile: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

extern "C" void MemFill8(void* dst, unsigned val, unsigned count);   // core::stdc::MemFill8
extern "C" void operator_delete(void* p);                            // ??3@YAXPAX@Z

namespace rw {

// ---- node interface ----------------------------------------------------
// A list node heap block: [vptr @0][pad @4][element data @8 ..].
struct IListNode {
    virtual void*        GetData();              // +0x00
    virtual int          SetData(void* p);       // +0x04
    virtual void*        v08();                  // +0x08
    virtual IListNode*   Next();                 // +0x0c
    virtual void         SetNext(IListNode* n);  // +0x10
    int pad4;                                    // +4
};
struct SNode : public IListNode {
    char data[1];                                // +8
};

// mAllocator vtable: +0x04 Alloc(size,tag,a,b,c), +0x0c Free(ptr,flag).
struct AllocVtbl {
    void* (*v00)(void* self);
    void* (*Alloc)(void* self, unsigned size, const char* tag, int a, int b, int c); // +0x04
    void* (*v08)(void* self);
    void  (*Free)(void* self, void* p, int flag);   // +0x0c
};
struct IRWAllocator { AllocVtbl* vftable; };

// Source object (Append/Prepend/Merge/...) vtable slots used:
//   +0x28  GetIterator(a,b) -> iterator
//   +0x3c  GetCount()       -> unsigned
// Iterator vtable: +0x00 GetValue(), +0x0c Next().
struct SrcVtbl {
    void* (*v00)(void*);
    void* (*v04)(void*);
    void* (*v08)(void*);
    void* (*v0c)(void*);
    void* (*v10)(void*);
    void* (*v14)(void*);
    void* (*v18)(void*);
    void* (*v1c)(void*);
    void* (*v20)(void*);
    void* (*v24)(void*);
    void* (*GetIterator)(void*, int a, int b);   // +0x28
    void* (*v2c)(void*);
    void* (*v30)(void*);
    void* (*v34)(void*);
    void* (*v38)(void*);
    unsigned (*GetCount)(void*);                 // +0x3c
};

struct SList {
    void*           vftable;                // +0x00
    SNode*          mHead;                  // +0x04
    SNode*          mTail;                  // +0x08
    unsigned        mLength;                // +0x0c
    IRWAllocator*   mAllocator;             // +0x10
    unsigned        mElementSize;           // +0x14
    unsigned        mUserAlignment;         // +0x18

    SList();                                                           // va 0x00fcce10
    SNode* FindNode(const char* key, void** cmp);                      // va 0x00fcc260
    SNode* GetPrev(SNode* node);                                       // va 0x00fcc2e0
    char   IsMember(SNode* node);                                      // va 0x00fcc330
    int    Append(SrcVtbl* src, int a);                                // va 0x00fcc370
    int    Prepend(SrcVtbl* src, int a);                               // va 0x00fcc470
    int    InsertBefore(SrcVtbl* src, SNode* at, int a);               // va 0x00fcc5c0
    int    InsertAfter(SrcVtbl* src, SNode* at, int a);                // va 0x00fcc700
    int    InsertAt(SrcVtbl* src, unsigned idx, int a);                // va 0x00fcc810
    int    Merge(SrcVtbl* src, void** cmp);                            // va 0x00fcc960
    int    Remove(SNode* node, void** cb);                             // va 0x00fccae0
    int    RemoveIf(void** key, void** cmp);                           // va 0x00fccb80
    void   Clear(void** cb);                                           // va 0x00fccc40
    int    Reverse();                                                  // va 0x00fccca0
    int    Permute(int* idx);                                          // va 0x00fccd00
    void*  Dtor(unsigned flags);                                       // va 0x00fccde0
    void   InvokeKey(void** a, void** b);                              // va 0x00fcce30
    int    Sort(void** cmp);                                           // va 0x00fcce70
    SNode* LoadNewNode(int a, int b);                                  // va 0x00fccf40
    void*  ScalarDeletingDtor(unsigned flags);                         // va 0x00fccfb0
    int    AppendOne(int a, int b);                                    // va 0x00fccfe0
    int    PrependOne(int a, int b);                                   // va 0x00fcd030
    int    InsertBeforeOne(int a, int b, SNode* at);                   // va 0x00fcd080
    int    InsertAfterOne(int a, int b, SNode* at);                    // va 0x00fcd120
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
SNode* SList::FindNode(const char* key, void** cmp)
{
    SNode* node = mHead;
    if (node == 0)
        return 0;
    for (;;) {
        int (*fn)(void*, const char*, void*) = (int (*)(void*, const char*, void*))(*cmp);
        if (fn(cmp, key, node->GetData()) == 0)
            return node;
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
int SList::Append(SrcVtbl* src, int a)
{
    unsigned size;
    void* it;
    SNode* node;
    if (src == 0)
        return -1;
    size = mElementSize;
    if (src->GetCount(src) < 1)
        return 0;
    it = src->GetIterator(src, 0, 0);
    if (it == 0)
        return 0;
    for (;;) {
        node = (SNode*)mAllocator->vftable->Alloc(mAllocator, size + 8, "SNode", 0, 4, 0);
        if (node == 0)
            return -1;
        if (node->SetData((*(void* (**)(void*))it)(it)) == -1) {
            mAllocator->vftable->Free(mAllocator, node, 0);
            return -1;
        }
        if (mLength == 0)
            mHead = node;
        else
            mTail->SetNext(node);
        ++mLength;
        mTail = node;
        it = (*(void* (**)(void*))(*(char**)it + 0xc))(it);
        if (it == 0)
            return 0;
    }
}

// @ 0x00fcc470
int SList::Prepend(SrcVtbl* src, int a)
{
    unsigned size;
    void* it;
    SNode* node;
    SNode* prev;
    if (src == 0)
        return -1;
    size = mElementSize;
    if (src->GetCount(src) < 1)
        return 0;
    prev = mHead;
    it = src->GetIterator(src, 0, 0);
    node = 0;
    for (;;) {
        if (it == 0) {
            if (mTail == 0)
                mTail = node;
            return 0;
        }
        node = (SNode*)mAllocator->vftable->Alloc(mAllocator, size + 8, "SNode", 0, 4, 0);
        if (node == 0)
            return -1;
        if (node->SetData((*(void* (**)(void*))it)(it)) == -1) {
            mAllocator->vftable->Free(mAllocator, node, 0);
            return -1;
        }
        node->SetNext(prev);
        if (mHead == 0)
            mHead = node;
        else if (prev == 0)
            mHead = node;
        else
            prev->SetNext(node);
        ++mLength;
        prev = node;
        it = (*(void* (**)(void*))(*(char**)it + 0xc))(it);
    }
}

// @ 0x00fcc5c0
int SList::InsertBefore(SrcVtbl* src, SNode* at, int a)
{
    unsigned size;
    SNode* prev;
    void* it;
    SNode* first;
    SNode* node;
    if (src->GetCount(src) == 0)
        return 0;
    size = mElementSize;
    prev = GetPrev(at);
    if (prev == 0 && at != mHead)
        return -1;
    it = src->GetIterator(src, 0, 0);
    first = 0;
    while (it != 0) {
        node = (SNode*)mAllocator->vftable->Alloc(mAllocator, size + 8, "SNode", 0, 4, 0);
        node->SetData((*(void* (**)(void*))it)(it));
        if (first == 0)
            first = node;
        else
            node->SetNext(first);
        it = (*(void* (**)(void*))(*(char**)it + 0xc))(it);
    }
    if (prev == 0) {
        node = first;
        first->SetNext(mHead);
        node->SetNext(mHead);
        mHead = first;
    } else {
        SNode* next = (SNode*)prev->Next();
        prev->SetNext(first);
        first->SetNext(next);
    }
    mLength += src->GetCount(src);
    return 0;
}

// @ 0x00fcc700
int SList::InsertAfter(SrcVtbl* src, SNode* at, int a)
{
    unsigned size;
    void* it;
    SNode* first;
    SNode* node;
    SNode* last;
    if (src->GetCount(src) == 0)
        return 0;
    size = mElementSize;
    it = src->GetIterator(src, 0, 0);
    first = 0;
    last = at;
    while (it != 0) {
        node = (SNode*)mAllocator->vftable->Alloc(mAllocator, size + 8, "SNode", 0, 4, 0);
        node->SetData((*(void* (**)(void*))it)(it));
        if (first == 0)
            first = node;
        else
            node->SetNext(first);
        it = (*(void* (**)(void*))(*(char**)it + 0xc))(it);
    }
    {
        SNode* next = (SNode*)last->Next();
        last->SetNext(first);
        first->SetNext(next);
    }
    if (mTail == at) {
        SNode* p = first;
        while (p->Next() != 0)
            p = (SNode*)p->Next();
        mTail = p;
    }
    mLength += src->GetCount(src);
    return 0;
}

// @ 0x00fcc810
int SList::InsertAt(SrcVtbl* src, unsigned idx, int a)
{
    unsigned size;
    void* it;
    SNode* first;
    SNode* node;
    if (idx > mLength)
        return -1;
    if (src->GetCount(src) < 1)
        return 0;
    size = mElementSize;
    it = src->GetIterator(src, 0, 0);
    first = 0;
    while (it != 0) {
        node = (SNode*)mAllocator->vftable->Alloc(mAllocator, size + 8, "SNode", 0, 4, 0);
        node->SetData((*(void* (**)(void*))it)(it));
        if (first == 0)
            first = node;
        else
            node->SetNext(first);
        it = (*(void* (**)(void*))(*(char**)it + 0xc))(it);
    }
    if (idx == 0) {
        first->SetNext(mHead);
        mHead = first;
    } else if (idx == mLength) {
        mTail->SetNext(0);
        mTail = first;
    } else {
        SNode* (*getAt)(void*, unsigned) = (SNode* (*)(void*, unsigned))((*(void***)this)[0x30 / 4]);
        SNode* at = getAt(this, idx - 1);
        SNode* next = (SNode*)at->Next();
        first->SetNext(next);
        at->SetNext(first);
    }
    mLength += src->GetCount(src);
    return 0;
}

// @ 0x00fcc960
int SList::Merge(SrcVtbl* src, void** cmp)
{
    unsigned size;
    void* it;
    SNode* first;
    SNode* node;
    SNode* a;
    SNode* prev;
    if (src->GetCount(src) == 0)
        return 0;
    size = mElementSize;
    it = src->GetIterator(src, 0, 0);
    first = 0;
    node = 0;
    while (it != 0) {
        SNode* nn = (SNode*)mAllocator->vftable->Alloc(mAllocator, size + 8, "SNode", 0, 4, 0);
        nn->SetData((*(void* (**)(void*))it)(it));
        if (first == 0)
            first = nn;
        else
            node->SetNext(nn);
        node = nn;
        it = (*(void* (**)(void*))(*(char**)it + 0xc))(it);
    }
    a = mHead;
    prev = 0;
    while (first != 0) {
        if (a == 0)
            break;
        {
            int (*fn)(void*, void*, void*) = (int (*)(void*, void*, void*))(*cmp);
            int r = fn(cmp, a->GetData(), first->GetData());
            if (r == -1) {
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
    }
    if (first != 0 || a != 0) {
        SNode* tailNode = (first != 0) ? first : a;
        if (prev != 0)
            prev->SetNext(tailNode);
    }
    mLength += src->GetCount(src);
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
int SList::RemoveIf(void** key, void** cmp)
{
    SNode* node = mHead;
    SNode* prev = 0;
    while (node != 0) {
        void* data = node->GetData();
        int (*fn)(void*, void*) = (int (*)(void*, void*))(*cmp);
        if (fn(key, data) == 0) {
            SNode* nx;
            if (key != 0) {
                void (*cb)(void*) = (void (*)(void*))*key;
                cb(data);
            }
            nx = (SNode*)node->Next();
            if (prev == 0) {
                mHead = nx;
                if (mTail == node)
                    mTail = nx;
                mAllocator->vftable->Free(mAllocator, node, 0);
                --mLength;
                node = mHead;
            } else {
                prev->SetNext(nx);
                if (mTail == node)
                    mTail = prev;
                mAllocator->vftable->Free(mAllocator, node, 0);
                node = (SNode*)prev->Next();
                --mLength;
            }
        } else {
            prev = node;
            node = (SNode*)node->Next();
        }
    }
    return 0;
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
    void* p = *a;
    void* q = *b;
    void** qv = *(void***)q;
    void* h = mHead;
    void** hv = *(void***)h;
    void* (*f0)(void*) = (void* (*)(void*))*qv;
    void* r0 = f0(qv);
    void* (*f1)(void*, void*) = (void* (*)(void*, void*))*(void**)p;
    void* r1 = f1(p, r0);
    void  (*f2)(void*, void*) = (void  (*)(void*, void*))*hv;
    f2(hv, r1);
}

// @ 0x00fcce70
int SList::Sort(void** cmp)
{
    unsigned* temp;
    SNode* node;
    unsigned i;
    int rc;
    if (mLength < 2)
        return 0;
    temp = (unsigned*)mAllocator->vftable->Alloc(mAllocator, mLength * 4, "SList::Sort temp", 0, 4, 0);
    node = mHead;
    {
        unsigned* p = temp;
        while (node != 0) {
            *p = (unsigned)node;
            node = (SNode*)node->Next();
            ++p;
        }
    }
    {
        unsigned dummy = 0;
        int (*fn)(void*, unsigned, int, unsigned*) = (int (*)(void*, unsigned, int, unsigned*))(*cmp);
        rc = fn(cmp, mLength, 4, &dummy);
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
    if (node->SetData((void*)a) == -1) {
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
int SList::InsertBeforeOne(int a, int b, SNode* at)
{
    SNode* node = LoadNewNode(a, b);
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
int SList::InsertAfterOne(int a, int b, SNode* at)
{
    SNode* node = LoadNewNode(a, b);
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
