// Slice s00f15890 -- eastl container helpers (Simulator module).
//  00f16260  tiny cleanup: release the object's parts, then destroy the member at +0x08
//  00f16280  fixed_vector<__int64,32>::assign over a linked-list iterator range
//  00f16330  vector<Element>::erase over 0x70-byte elements with virtual destructors
//  00f16390  vector<Element>::insert (grow path / in-place path)
// Flags: /O2 /MD /Gy /EHsc /TP /arch=SSE /fp:fast.  Callees are masked relocations.
typedef unsigned int uint;
typedef long long int64;

extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int size);

// ---------------------------------------------------------------------------------------------
// 00f16260: release parts, then destroy the member object at +0x08 (tail call)
// ---------------------------------------------------------------------------------------------
struct PartHolder {
    char pad00[8];
    struct Part { void Destroy(); } mPart;                  // +0x08, 0x00e0a5c0
    void ReleaseParts();                                    // 0x00f14980
    void Cleanup();                                         // 0x00f16260
};

// ---------------------------------------------------------------------------------------------
// fixed_vector<int64,32>: three pointers, list iterators are singly linked nodes with the value
// at +0x08 (next at +0x00)
// ---------------------------------------------------------------------------------------------
struct ListNode {
    ListNode* mpNext;                                       // +0x00
    int       mPad;                                         // +0x04
    int64     mValue;                                       // +0x08
};

// singly linked list iterator: the object stays in its stack slot (its member is updated in place
// by operator++), which is why the retail loop reloads and stores the parameter slot each step
struct ListIterator {
    ListNode* mpNode;
    ListIterator& operator++()      { mpNode = mpNode->mpNext; return *this; }
    int64&        operator*() const { return mpNode->mValue; }
    bool operator==(const ListIterator& other) const { return mpNode == other.mpNode; }
};

inline int64* CopyRange64(const int64* first, const int64* last, int64* dst)
{
    memcpy(dst, first, (uint)((const char*)last - (const char*)first));
    return dst + (last - first);
}

struct Int64ListVector {
    int64* mpBegin;                                         // +0x00
    int64* mpEnd;                                           // +0x04
    int64* mpCapacity;                                      // +0x08

    void InsertList(int64* pos, ListIterator first, ListIterator last, ListIterator first2); // 0x00f143c0
    void AssignFromList(ListIterator first, ListIterator last, int tag);   // 0x00f16280
};

// ---------------------------------------------------------------------------------------------
// vector of 0x70-byte elements with a virtual destructor
// ---------------------------------------------------------------------------------------------
const int kElementSize = 0x70;

struct Element {
    Element(const Element* other);                          // 0x00f14690
    virtual void Destroy(int flags);                        // +0x00
    void DestroySelf();                                     // 0x00e0a400
    int mData[0x1b];
};

// allocation header the SD node allocator keeps in front of the payload; a zero size means the
// block was not heap allocated and must not be released
struct BlockHeader {
    unsigned int mSize;
};

Element* MoveElements(Element* first, Element* last, Element* dst);          // 0x00f14900
Element* CopyConstructRange(Element* first, Element* last, Element* dst);    // 0x00f148c0
Element* DestroyRange(Element* first, Element* last, Element* dst);          // 0x00f120e0
Element* CopyConstructBackward(Element* first, Element* last, Element* dstEnd); // 0x00f14940
Element** CopyConstructSaved(Element** result, Element* first, Element* last,
                             Element* dst);                                  // 0x00f147a0
void     FillUninitialized(Element* dst, unsigned int n, const Element* value); // 0x00f16230
void     FillAssigned(Element* first, Element* last, const Element* value);  // 0x00f16300
void     FreeRawBlock(void* block);                                          // 0x00f47380

void* operator new(unsigned int size, const char* name, int flags, int align,
                   const char* file, int line);

inline void* AllocElementBlock(unsigned int size, int line)
{
    return ::operator new(size, "Simulator", 0, 0, "EASTL/allocator.h", line);
}

struct ElementVector {
    Element* mpBegin;                                       // +0x00
    Element* mpEnd;                                         // +0x04
    Element* mpCapacity;                                    // +0x08

    Element* EraseRange(Element* last, Element* pos);       // 0x00f16330
    void     InsertN(Element* position, unsigned int n, const Element* value); // 0x00f16390
};

// ---------------------------------------------------------------------------------------------
// @ 0x00f16260
void PartHolder::Cleanup()
{
    ReleaseParts();
    mPart.Destroy();
}

// @ 0x00f16280
void Int64ListVector::AssignFromList(ListIterator first, ListIterator last, int tag)
{
    int64* p = mpBegin;
    if (p != mpEnd) {
        do {
            if (first == last)
                break;
            *p = *first;
            ++first;
            ++p;
        } while (p != mpEnd);
    }
    if (first == last) {
        int64* lastPos = mpEnd;
        CopyRange64(lastPos, mpEnd, p);
        mpEnd -= lastPos - p;
    } else {
        InsertList(mpEnd, first, last, first);
    }
}

// @ 0x00f16330
Element* ElementVector::EraseRange(Element* last, Element* pos)
{
    Element* p = MoveElements(pos, mpEnd, last);
    Element* end = mpEnd;
    for (; p < end; ++p)
        p->Destroy(0);
    mpEnd -= pos - last;
    return last;
}

// @ 0x00f16390
void ElementVector::InsertN(Element* position, unsigned int n, const Element* value)
{
    unsigned int freeCount = (unsigned int)(mpCapacity - mpEnd);
    if (n <= freeCount) {
        if (n == 0)
            return;

        Element temp(value);

        Element* oldEnd = mpEnd;
        unsigned int tail = (unsigned int)(oldEnd - position);
        if (n < tail) {
            // the new elements fit before the end: move the last n elements into the unused space,
            // then shift the middle part right
            Element* src = oldEnd - n;
            Element* dst = oldEnd;
            CopyConstructSaved(&dst, src, oldEnd, oldEnd);
            mpEnd = mpEnd + n;
            CopyConstructBackward(position, src, mpEnd);
            FillAssigned(position, position + n, &temp);
        } else {
            // the tail is shorter than the insert: fill the unused space, then move the tail behind
            // the inserted block
            FillUninitialized(oldEnd, n - tail, &temp);
            mpEnd = mpEnd + (n - tail);
            Element* dst = oldEnd;
            CopyConstructSaved(&dst, position, oldEnd, mpEnd);
            mpEnd = mpEnd + tail;
            FillAssigned(position, oldEnd, &temp);
        }
        temp.DestroySelf();
        return;
    }

    int oldSize = (int)(mpEnd - mpBegin);
    int newCapacity = oldSize * 2;
    if (oldSize == 0)
        newCapacity = 1;
    int total = oldSize + (int)n;
    if (total < newCapacity)
        total = newCapacity;

    Element* newData = 0;
    if (total != 0)
        newData = (Element*)AllocElementBlock((unsigned int)(total * (int)sizeof(Element)), 0xd1);

    Element* p = CopyConstructRange(mpBegin, position, newData);
    DestroyRange(mpBegin, position, newData);
    FillUninitialized(p, n, value);
    p += n;
    Element* newEnd = CopyConstructRange(position, mpEnd, p);
    DestroyRange(position, mpEnd, p);

    if (mpBegin != 0 && ((BlockHeader*)mpBegin)[-1].mSize != 0)
        FreeRawBlock(mpBegin);

    mpBegin = newData;
    mpEnd = newEnd;
    mpCapacity = newData + total;
}
