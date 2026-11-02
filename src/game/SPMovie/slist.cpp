// src/game/SPMovie/slist.cpp -- migrated from slice(s) s00fcd210, s00fcc260, s00fcb210 by tools/migrate/rewrite.py
// Object file: SPMovie/slist.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#pragma intrinsic(__rdtsc)

// ---- items of slice s00fcb210 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
class IListNode
{ public:
    virtual void   v00();   // +0x00
    virtual void   v04();   // +0x04
    virtual void   v08();   // +0x08
    virtual void*  Next();  // +0x0c  (returns the following node)
};
}
namespace rw {
class SList
{ public:
    uint32_t pad_00;   // +0x00
    void*    mHead;    // +0x04
    void*    mTail;    // +0x08
    uint32_t mLength;  // +0x0c

    void* GetNode(uint32_t index) const;   // 0x00fcc220
};
}
using rw::SList;
// ---- items of slice s00fcb210 end

// ---- items of slice s00fcc260 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void MemFill8(void* dst, unsigned val, unsigned count);   // core::stdc::MemFill8
extern "C" void operator_delete(void* p);                            // ??3@YAXPAX@Z
namespace rw {
class IListNode_s00fc_c260 { public:
    virtual void*        GetData();                                     // +0x00
    virtual int          SetData(void* src, unsigned size, void* ctx);  // +0x04
    virtual void*        v08();                                         // +0x08
    virtual IListNode_s00fc_c260*   Next();                                        // +0x0c
    virtual void         SetNext(IListNode_s00fc_c260* n);                         // +0x10
    int pad4;                                                           // +4
};
}
namespace rw {
class SNode : public IListNode_s00fc_c260 { public:
    char data[1];                                                       // +8
};
}
namespace rw {
struct AllocVtbl {
    void* (*v00)(void* self);
    void* (*Alloc)(void* self, unsigned size, const char* tag, int a, int b, int c); // +0x04
    void* (*v08)(void* self);
    void  (*Free)(void* self, void* p, int flag);   // +0x0c
};
}
namespace rw {
struct IRWAllocator { AllocVtbl* vftable; };
}
namespace rw {
class IListIterator { public:
    virtual void*          GetValue();      // +0x00
    virtual void*          v04();           // +0x04
    virtual void*          v08();           // +0x08
    virtual IListIterator* Next();          // +0x0c
};
}
namespace rw {
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
}
namespace rw {
class ICompare { public:
    virtual int Compare(void* a, void* b);  // +0x00
};
}
namespace rw {
class ICallback { public:
    virtual void Invoke(void* data);        // +0x00
};
}
namespace rw {
class ISorter { public:
    virtual int Sort(void* array, unsigned count, unsigned stride, void* adapter);  // +0x00
};
}
namespace rw {
struct SListSortAdapter {
    void* vftable;                          // +0x00
    void* cmp;                              // +0x04
};
}
namespace rw {
class IInvokeValue { public:
    virtual void* Get();                    // +0x00
};
}
namespace rw {
class IInvokeMap { public:
    virtual void* Get(void* x);             // +0x00
};
}
namespace rw {
class IInvokeStore { public:
    virtual void  Set(void* x);             // +0x00
};
}
namespace rw {
class SList_s00fc_c260 { public:
    void*           vftable;                // +0x00
    SNode*          mHead;                  // +0x04
    SNode*          mTail;                  // +0x08
    unsigned        mLength;                // +0x0c
    IRWAllocator*   mAllocator;             // +0x10
    unsigned        mElementSize;           // +0x14
    unsigned        mUserAlignment;         // +0x18

    SList_s00fc_c260();                                                           // va 0x00fcce10
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
}
// ---- items of slice s00fcc260 end

// ---- items of slice s00fcd210 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
struct SNode_s00fc_d210 {
    void** m_vtbl;   // +0x00
    // the object payload (comparison key) is embedded at +0x10
};
struct SList_s00fc_d210 {
    char   m_pad00[0x04];
    SNode_s00fc_d210* m_head;       // +0x04
    SNode_s00fc_d210* m_tail;       // +0x08
    int    m_count;      // +0x0c
    int    LoadNewNode_helper();
};
extern "C" void        util_Copy16(u8*, u8*, int);          // 0x11ea910
extern "C" SNode_s00fc_d210* SList_LoadNewNode(SList_s00fc_d210* self, void* key, int a3);  // 0xfccf40
struct Vp6Tramp {
    int  Method320(int p2, int p3, int* p4);
    int  Method370(int p2, int p3, int* p4);
    void* Get();
};
// ---- items of slice s00fcd210 end

// @ 0x00fcc220
void* rw::SList::GetNode(uint32_t index) const
{
    uint32_t i = index;
    if (i >= mLength)
        return 0;
    if (i == mLength - 1)
        return mTail;

    void* node = mHead;
    while (i > 0u && node != 0)
    {
        --i;
        node = ((IListNode*)node)->Next();
    }
    return node;
}

// @ 0x00fcc260
namespace rw {
SNode* SList_s00fc_c260::FindNode(const void* key, ICompare* cmp)
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
}  // namespace rw

// @ 0x00fcc2e0
namespace rw {
SNode* SList_s00fc_c260::GetPrev(SNode* node)
{
    SNode* p = mHead;
    if (node == p || mLength == 0)
        return 0;
    while (p != 0 && (SNode*)p->Next() != node)
        p = (SNode*)p->Next();
    return p;
}
}  // namespace rw

// @ 0x00fcc330
namespace rw {
char SList_s00fc_c260::IsMember(SNode* node)
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
}  // namespace rw

// @ 0x00fcc370
namespace rw {
int SList_s00fc_c260::Append(IListSource* src, void* ctx)
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
}  // namespace rw

// @ 0x00fcc470
namespace rw {
int SList_s00fc_c260::Prepend(IListSource* src, void* ctx)
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
}  // namespace rw

// @ 0x00fcc5c0
namespace rw {
int SList_s00fc_c260::InsertBefore(IListSource* src, SNode* at, void* ctx)
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
}  // namespace rw

// @ 0x00fcc700
namespace rw {
int SList_s00fc_c260::InsertAfter(IListSource* src, SNode* at, void* ctx)
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
}  // namespace rw

// @ 0x00fcc810
namespace rw {
int SList_s00fc_c260::InsertAt(IListSource* src, unsigned idx, void* ctx)
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
}  // namespace rw

// @ 0x00fcc960
namespace rw {
int SList_s00fc_c260::Merge(IListSource* src, ICompare* cmp, void* ctx)
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
}  // namespace rw

// @ 0x00fccae0
namespace rw {
int SList_s00fc_c260::Remove(SNode* node, void** cb)
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
}  // namespace rw

// @ 0x00fccb80
namespace rw {
int SList_s00fc_c260::RemoveIf(void* key, ICompare* cmp, ICallback* cb)
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
}  // namespace rw

// @ 0x00fccc40
namespace rw {
void SList_s00fc_c260::Clear(void** cb)
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
}  // namespace rw

// @ 0x00fccca0
namespace rw {
int SList_s00fc_c260::Reverse()
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
}  // namespace rw

// @ 0x00fccd00
namespace rw {
int SList_s00fc_c260::Permute(int* idx)
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
        node->SetNext((IListNode_s00fc_c260*)temp[i]);
        node = (SNode*)temp[i];
        ++i;
    }
    mTail = (SNode*)temp[mLength - 1];
    mTail->SetNext(0);
    mAllocator->vftable->Free(mAllocator, temp, 0);
    return rc;
}
}  // namespace rw

// @ 0x00fccde0
namespace rw {
void* SList_s00fc_c260::Dtor(unsigned flags)
{
    mHead = 0;
    vftable = (void*)0x1491e4c;
    if (flags & 1)
        operator_delete(this);
    return this;
}
}  // namespace rw

// @ 0x00fcce10
namespace rw {
SList_s00fc_c260::SList_s00fc_c260()
{
    vftable = (void*)0x1491ef8;
    mHead = 0;
    mTail = 0;
    mLength = 0;
    mAllocator = 0;
    mElementSize = 0;
    mUserAlignment = 0;
}
}  // namespace rw

// @ 0x00fcce30
namespace rw {
void SList_s00fc_c260::InvokeKey(void** a, void** b)
{
    void* r0 = ((IInvokeValue*)*b)->Get();
    void* r1 = ((IInvokeMap*)*a)->Get(r0);
    ((IInvokeStore*)mHead)->Set(r1);
}
}  // namespace rw

// @ 0x00fcce70
namespace rw {
int SList_s00fc_c260::Sort(void* sorter, void* cmp)
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
            node->SetNext((IListNode_s00fc_c260*)temp[i]);
            node = (SNode*)temp[i];
            ++i;
        }
        mTail = (SNode*)temp[mLength - 1];
        mTail->SetNext(0);
    }
    mAllocator->vftable->Free(mAllocator, temp, 0);
    return rc;
}
}  // namespace rw

// @ 0x00fccf40
namespace rw {
SNode* SList_s00fc_c260::LoadNewNode(int a, int b)
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
}  // namespace rw

// @ 0x00fccfb0
namespace rw {
void* SList_s00fc_c260::ScalarDeletingDtor(unsigned flags)
{
    vftable = (void*)0x1491ef8;
    Clear(0);
    vftable = (void*)0x1491e68;
    if (flags & 1)
        operator_delete(this);
    return this;
}
}  // namespace rw

// @ 0x00fccfe0
namespace rw {
int SList_s00fc_c260::AppendOne(int a, int b)
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
}  // namespace rw

// @ 0x00fcd030
namespace rw {
int SList_s00fc_c260::PrependOne(int a, int b)
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
}  // namespace rw

// @ 0x00fcd080
namespace rw {
int SList_s00fc_c260::InsertBeforeOne(int a, SNode* at, void* ctx)
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
}  // namespace rw

// @ 0x00fcd120
namespace rw {
int SList_s00fc_c260::InsertAfterOne(int a, SNode* at, void* ctx)
{
    SNode* node = LoadNewNode(a, (int)ctx);
    node->SetNext(at->Next());
    at->SetNext(node);
    ++mLength;
    return 0;
}
}  // namespace rw

// @ 0x00fcd170
namespace rw {
int SList_s00fc_c260::InsertAtOne(int a, unsigned idx, int b)
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

// @ 0x00fcd210
extern "C" int SList_InsertSorted(SList_s00fc_d210* self, void* key, SNode_s00fc_d210* node, int a4)
{
    SNode_s00fc_d210* pNew = SList_LoadNewNode(self, key, a4);
    if (self->m_count == 0) {
        self->m_tail = pNew;
        self->m_head = pNew;
        self->m_count = 1;
        return 0;
    }
    SNode_s00fc_d210* cur = self->m_head;
    SNode_s00fc_d210* prev = 0;
    bool done = false;
    while (cur != 0 && !done) {
        void** vt1 = (void**)cur->m_vtbl;
        void** vt2 = (void**)node->m_vtbl;
        int lhs = ((int (*)(void*))vt1[0])((char*)cur + 0x10);
        int rhs = ((int (*)(void*, int))vt2[0])(key, lhs);
        if (rhs == -1) {
            done = true;
        } else {
            prev = cur;
            cur = (SNode_s00fc_d210*)((void* (*)(void*))((void**)cur->m_vtbl)[3])(cur);
        }
    }
    (void)a4;
    if (prev == 0) {
        ((void (*)(void*, SNode_s00fc_d210*))((void**)pNew->m_vtbl)[4])(pNew, self->m_head);
        self->m_count++;
        self->m_head = pNew;
        return 0;
    }
    if (cur == 0) {
        ((void (*)(void*, SNode_s00fc_d210*))((void**)prev->m_vtbl)[4])(prev, pNew);
        self->m_count++;
        self->m_tail = pNew;
        return 0;
    }
    ((void (*)(void*, SNode_s00fc_d210*))((void**)prev->m_vtbl)[3])(prev, pNew);
    ((void (*)(void*, SNode_s00fc_d210*))((void**)pNew->m_vtbl)[4])(pNew, cur);
    self->m_count++;
    return 0;
}

// @ 0x00fcd320
int Vp6Tramp::Method320(int p2, int p3, int* p4)
{
    int uVar1 = (int)Get();
    if (p2 == 0 || p3 == 0)
        return -1;
    if (p4 == 0) {
        util_Copy16((u8*)uVar1, (u8*)p2, p3);
    } else {
        int iVar2 = ((int (*)(int, int, int))((void**)*p4)[0])(uVar1, p2, p3);
        if (iVar2 == -1)
            return -1;
    }
    return 0;
}

// @ 0x00fcd370
int Vp6Tramp::Method370(int p2, int p3, int* p4)
{
    int uVar1 = (int)Get();
    if (p2 == 0 || p3 == 0)
        return -1;
    if (p4 == 0) {
        util_Copy16((u8*)p2, (u8*)uVar1, p3);
    } else {
        int iVar2 = ((int (*)(int, int, int))((void**)*p4)[0])(p2, uVar1, p3);
        if (iVar2 == -1)
            return -1;
    }
    return 0;
}
