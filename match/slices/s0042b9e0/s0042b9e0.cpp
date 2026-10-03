// Slice 0x0042B9E0..0x0042C1C0..0x0042C29D: EASTL-style container helpers from an unoptimized
// (/Od /Ob1 /MD /Gy /TP) module: a range insert for a vector of 4-byte elements, a stable-sort
// style merge driver over 12-byte elements, a vector fill-assign, and a red-black tree
// node insert keyed on a 3-word key.
//
// /Od frame-layout notes found here:
//  - The order of locals within a scope follows the local NAMES (alphabetical ascending ->
//    higher stack address), not declaration order (see Tree::InsertNode).
//  - A trailing empty-struct tag argument is passed by value as a (uninitialised) byte read from
//    the stack; extra dead empty-struct locals shift its slot (see MergeSortBuffered).
//  - `Elem3()` as a named local initialised with `= {}` gives `xor reg,reg` + three stores.

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

extern "C" void* memmove(void*, const void*, unsigned int);
extern "C" void* memcpy(void*, const void*, unsigned int);

struct Alloc { int x; };
struct Empty {};

// ---------------------------------------------------------------------------
// 0x0042B9E0: vector<uint32_t>::insert(pos, first, last) (range insert)
// ---------------------------------------------------------------------------
void UninitCopy4(Empty* tag, uint32_t* first, uint32_t* last, uint32_t* dest);  // 0x004D1240 (cdecl)
uint32_t* AllocateBytes(Alloc* a, uint32_t bytes, uint32_t align, uint32_t offset); // 0x0042DEE0 (cdecl)
uint32_t* CopyRange4(const uint32_t* first, const uint32_t* last, uint32_t* dest);   // 0x00511F70 (cdecl)
void FreeBlock(void* p);                                                           // 0xF47380 (EASTL allocator deallocate)

struct VecU32 {
    uint32_t* mBegin;
    uint32_t* mEnd;
    uint32_t* mCap;
    Alloc mAlloc;

    void InsertRange(uint32_t* pos, const uint32_t* first, const uint32_t* last);
    void Assign(uint32_t n, const uint32_t* value);
    void Adopt(struct VecHolder* h);                      // 0x004C2100
    void EraseRange(uint32_t* a, uint32_t* b);            // 0x004769B0
};

// @ 0x0042B9E0
void VecU32::InsertRange(uint32_t* pos, const uint32_t* first, const uint32_t* last) {
    if (first == last)
        return;
    uint32_t n = last - first;
    if (n <= (uint32_t)(mCap - mEnd)) {
        uint32_t elemsAfter = mEnd - pos;
        uint32_t* oldEnd = mEnd;
        if (n < elemsAfter) {
            Empty tag;
            UninitCopy4(&tag, mEnd - n, mEnd, mEnd);
            mEnd += n;
            memmove(oldEnd - (elemsAfter - n), pos, (elemsAfter - n) * 4);
            memcpy((void*)pos, first, (last - first) * 4);
        } else {
            const uint32_t* mid = first + elemsAfter;
            Empty tag;
            UninitCopy4(&tag, (uint32_t*)mid, (uint32_t*)last, mEnd);
            mEnd += n - elemsAfter;
            Empty tag2;
            UninitCopy4(&tag2, pos, oldEnd, mEnd);
            mEnd += elemsAfter;
            memmove(pos, first, (mid - first) * 4);
        }
    } else {
        uint32_t oldSize = mEnd - mBegin;
        uint32_t grow = oldSize ? oldSize * 2 : 1;
        uint32_t newSize = grow > oldSize + n ? grow : oldSize + n;
        uint32_t* newBuf = newSize ? AllocateBytes(&mAlloc, newSize * 4, 4, 0) : 0;
        uint32_t* cur = newBuf;
        memcpy(cur, mBegin, (pos - mBegin) * 4);
        cur += pos - mBegin;
        cur = CopyRange4(first, last, cur);
        memcpy(cur, pos, (mEnd - pos) * 4);
        cur += mEnd - pos;
        if (mBegin && mBegin[-1])
            FreeBlock(mBegin);
        mBegin = newBuf;
        mEnd = cur;
        mCap = newBuf + newSize;
    }
}

// ---------------------------------------------------------------------------
// 0x0042BEE0: merge-sort driver with a temporary buffer of 12-byte elements
// ---------------------------------------------------------------------------
struct Elem3 { uint32_t a, b, c; };
Elem3* AllocElems(Alloc* a, uint32_t bytes, uint32_t align, uint32_t off);          // 0x0042DEE0
void UninitFill(Elem3* f, Elem3* l, const Elem3& v, Empty t);                       // 0x0042F100
void MergeSortBuf(Elem3* f, Elem3* l, Elem3* buf, bool b);                          // 0x0042E090

// @ 0x0042BEE0
void MergeSortBuffered(Elem3* first, Elem3* last, Alloc* alloc, bool flag) {
    int n = last - first;
    Elem3* buf;
    if (n > 1) {
        buf = AllocElems(alloc, n * sizeof(Elem3), 4, 0);
        Elem3 tmp = {};
        {
            Empty e1;
            Empty tag;
            Empty e3;
            Empty e4;
            UninitFill(buf, buf + n, tmp, tag);
        }
        MergeSortBuf(first, last, buf, flag);
        {
            Elem3* p;
            for (p = buf; p != buf + n; p = p + 1) {
            }
        }
        {
            Elem3* q = buf;
            FreeBlock(q);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x0042BFA0: vector<uint32_t>::assign(n, value) (fill)
// ---------------------------------------------------------------------------
struct VecHolder {
    uint32_t* ptr;
    VecHolder(uint32_t n, Alloc* a);   // 0x0042F2E0
    ~VecHolder();                      // 0x004C0B80
};
void UninitFillN(Empty* t, uint32_t* first, uint32_t n, const uint32_t* v);   // 0x004AB450 (cdecl)
void FillN(uint32_t* first, uint32_t n, const uint32_t* v);                   // 0x0042E240 (cdecl)

inline void UninitFillNImpl(uint32_t* first, uint32_t n, const uint32_t* v) {
    Empty t;
    UninitFillN(&t, first, n, v);
}
inline void UninitFillNMid(uint32_t* first, uint32_t n, const uint32_t* v) {
    uint32_t* f = first;
    UninitFillNImpl(f, n, v);
}
inline void UninitFillNWrap(uint32_t* first, uint32_t n, const uint32_t* v) {
    uint32_t* f = first;
    UninitFillNMid(f, n, v);
}

// @ 0x0042BFA0
void VecU32::Assign(uint32_t n, const uint32_t* value) {
    if (n > (uint32_t)(mCap - mBegin)) {
        VecHolder holder(n, &mAlloc);
        UninitFillNWrap(holder.ptr, n, value);
        uint32_t* endp = holder.ptr + n;
        Adopt(&holder);
        for (uint32_t* q = holder.ptr; q < endp; ++q) {
        }
    } else if (n > (uint32_t)(mEnd - mBegin)) {
        uint32_t* last = mEnd;
        uint32_t* first = mBegin;
        uint32_t* it = first;
        uint32_t val = *value;
        for (; it != last; ++it)
            *it = val;
        uint32_t extra = n - (mEnd - mBegin);
        uint32_t* e = mEnd;
        UninitFillNWrap(e, extra, value);
        mEnd = mEnd + (n - (mEnd - mBegin));
    } else {
        FillN(mBegin, n, value);
        EraseRange(mBegin + n, mEnd);
    }
}

// ---------------------------------------------------------------------------
// 0x0042C1C0: red-black tree node insert (key = three 32-bit words)
// ---------------------------------------------------------------------------
struct Key { uint32_t a, b, c; };
struct TreeNode { uint32_t links[4]; Key key; };
struct TreeIter { void Set(TreeNode* n); };         // 0x00566C50

inline bool KeyLess(const Key* x, const Key* y) {
    bool r;
    if (x->a != y->a)
        r = x->a < y->a;
    else if (x->c != y->c)
        r = x->c < y->c;
    else
        r = x->b < y->b;
    return r;
}

void RbLink(TreeNode* node, TreeNode* pos, void* anchor, uint32_t left);  // 0x009216A0 (cdecl)

struct Tree {
    uint32_t pad0;
    uint32_t anchor[4];
    uint32_t count;
    TreeNode* AllocNode(const Key* k);                // 0x0042E290
    TreeIter* InsertNode(TreeIter* out, TreeNode* pos, const Key* key, bool forceLeft);
};

// @ 0x0042C1C0
TreeIter* Tree::InsertNode(TreeIter* out, TreeNode* pos, const Key* key, bool forceLeft) {
    // The single-letter names are load-bearing: /Od hands out frame slots by name, and
    // a = new node, c = insert-left flag, b = a dead slot in the original.
    TreeNode* a;
    uint32_t c;
    uint32_t b;
    if (forceLeft || pos == (TreeNode*)&anchor[0] || KeyLess(key, &pos->key))
        c = 0;
    else
        c = 1;
    a = AllocNode(key);
    RbLink(a, pos, &anchor[0], c);
    ++count;
    out->Set(a);
    return out;
}
