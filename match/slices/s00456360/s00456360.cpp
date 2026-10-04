// Slice s00456360: EASTL container helpers (vector/rbtree/uninitialized_copy etc.) and two vec3 helpers.
// Source is behaviorally equivalent; /Od EASTL inline layers are flattened.
#include "types.h"
#include <string.h>
#include <math.h>

// Allocator / helper externs (callees are masked relocations).
void* EASTL_Allocate(void* alloc, uint32_t size, uint32_t align, uint32_t flags); // FUN_0042dee0
void  EASTL_Free(void* p);                                                         // operator delete[]

// 28-byte payload that follows the 4-byte key in a 0x20 element.
struct SubObj {
    char d[28];
    void CopyFrom(const SubObj* src);      // FUN_00440ff0 (this = dst, arg = src)
};
struct SubObj2 {                           // payload in the rbtree node at +0x14
    char d[92];
    void CopyFrom(const SubObj2* src);     // FUN_00455cf0
};

struct Elem32 {
    int32_t key;
    SubObj  sub;
};

// vector<Elem32, fixed_vector_allocator>: begin/end/capacity/allocator/fixed buffer
struct ElemVector {
    Elem32* mpBegin;     // +0
    Elem32* mpEnd;       // +4
    Elem32* mpCapacity;  // +8
    uint32_t alloc[1];   // +0xC (allocator, address passed to Allocate)
    void*   mpFixedBuf;  // +0x10

    Elem32* DoInsertValue(Elem32* pos, const Elem32* val);   // FUN_00456d60 (shown via FUN_00456360 helper)
    Elem32* insert(Elem32* pos, const Elem32* val);          // 0x456360
};

static Elem32* uninitialized_copy_Elem32(Elem32* first, Elem32* last, Elem32* dst); // 0x457540

// @ 0x456360
Elem32* ElemVector::insert(Elem32* pos, const Elem32* val)
{
    int idx = pos - mpBegin;
    if (pos == mpEnd && mpEnd != mpCapacity) {
        Elem32* p = mpEnd;
        mpEnd = mpEnd + 1;
        if (p) {
            p->key = val->key;
            p->sub.CopyFrom(&val->sub);
        }
    } else {
        DoInsertValue(pos, val);
    }
    return mpBegin + idx;
}

// @ 0x456410  (eastl::lower_bound on Elem32 keys, int less-than)
Elem32* lower_bound_Elem32(Elem32* first, Elem32* last, const int32_t* key)
{
    int n = last - first;
    while (n > 0) {
        int half = n >> 1;
        Elem32* mid = first + half;
        if (mid->key < *key) {
            first = mid + 1;
            n = n - (half + 1);
        } else {
            n = half;
        }
    }
    return first;
}

// ---- rbtree (hint insert position lookup) -------------------------------------------
struct RBNode {
    RBNode* mpNodeRight;   // +0  (checked for null in the hint path)
    RBNode* mpNodeLeft;    // +4
    RBNode* mpNodeParent;  // +8
    int     mColor;        // +0xC
    uint32_t mKey;         // +0x10
};
struct RBIter { RBNode* mpNode; };
void RBIter_Next(RBIter* it);            // FUN_00422c50 (operator++ / decrement as applicable)
void RBIter_Assign(void* out, RBIter* in); // FUN_005673e0

struct RBTree {
    char    pad0[4];
    RBNode  anchorDummy;     // placeholder; real layout: +4 anchor node
    // fields below accessed by raw offset in the original
    void*   DoInsertValueImpl(void* out, RBNode* x, RBNode* y, const uint32_t* key, bool bLeft); // 0x457060
    void*   DoGetResult(void* out, const uint32_t* key, bool b);                                 // 0x457310
    void*   hintInsert(void* result, RBNode* hint, const uint32_t* key);                         // 0x456490
};

// @ 0x456490
// Original works on raw offsets: this+4 = anchor (end) node, this+0x14 = size.
void* RBTree_GetInsertPosition(char* self, void* result, RBNode* hint, const uint32_t* key)
{
    RBNode* anchor = *(RBNode**)(self + 4);
    RBTree* t = (RBTree*)self;
    char tmp[8];
    if (hint == anchor || hint == (RBNode*)(self + 4)) {
        if (*(int*)(self + 0x14) != 0 && anchor->mKey < *key) {
            t->DoInsertValueImpl(result, anchor, 0, key, false);
            return result;
        }
        t->DoGetResult(tmp, key, false);
        RBIter_Assign(result, (RBIter*)tmp);
        return result;
    }
    RBIter itNext; itNext.mpNode = hint;
    RBIter itPrev;
    RBIter_Assign(&itPrev, &itNext);   // copy hint into itPrev (0x5673e0 on [ebp-8])
    RBIter_Next(&itPrev);
    RBNode* prev = itPrev.mpNode;
    if (hint->mKey < *key && *key < prev->mKey) {
        if (hint->mpNodeRight == 0) {
            t->DoInsertValueImpl(result, hint, 0, key, false);
        } else {
            t->DoInsertValueImpl(result, prev, 0, key, true);
        }
        return result;
    }
    t->DoGetResult(tmp, key, false);
    RBIter_Assign(result, (RBIter*)tmp);
    return result;
}

// @ 0x4565f0  (reads param as vec3, returns 1/sqrt(dot))
struct Vec3 { float x, y, z; };
float Vec3_InvLength(const Vec3* v)
{
    float d = v->x * v->x + v->y * v->y + v->z * v->z;
    return 1.0f / sqrtf(d);
}

// @ 0x456650
Vec3* Vec3_Scale(Vec3* out, const Vec3* v, float s)
{
    float x = v->x * s;
    float y = v->y * s;
    float z = v->z * s;
    out->x = x; out->y = y; out->z = z;
    return out;
}

// @ 0x4566e0  (vector<uint32_t>::insert(pos, n, value))
struct U32Vector {
    uint32_t* mpBegin;      // +0
    uint32_t* mpEnd;        // +4
    uint32_t* mpCapacity;   // +8
    uint32_t  alloc[1];     // +0xC
    uint32_t* mpFixedBuf;   // +0x10
    void insert(uint32_t* pos, uint32_t n, const uint32_t* value);
};

void U32Vector::insert(uint32_t* pos, uint32_t n, const uint32_t* value)
{
    if ((uint32_t)(mpCapacity - mpEnd) < n) {
        uint32_t oldSize = mpEnd - mpBegin;
        uint32_t grow = oldSize ? oldSize * 2 : 1;
        uint32_t newCap = (oldSize + n < grow) ? grow : oldSize + n;
        uint32_t* newBuf = newCap ? (uint32_t*)EASTL_Allocate(alloc, newCap * 4, 4, 0) : 0;
        uint32_t* d = newBuf;
        size_t headBytes = (char*)pos - (char*)mpBegin;
        memmove(d, mpBegin, headBytes);
        d += headBytes >> 2;
        for (uint32_t i = 0; i < n; ++i) d[i] = *value;
        d += n;
        size_t tailBytes = (char*)mpEnd - (char*)pos;
        memmove(d, pos, tailBytes);
        d += tailBytes >> 2;
        if (mpBegin && mpBegin != mpFixedBuf)
            EASTL_Free(mpBegin);
        mpBegin = newBuf;
        mpEnd = d;
        mpCapacity = newBuf + newCap;
    } else if (n != 0) {
        uint32_t v = *value;
        uint32_t tail = mpEnd - pos;
        uint32_t* oldEnd = mpEnd;
        if (n < tail) {
            memmove(oldEnd, oldEnd - n, n * 4);
            mpEnd += n;
            memmove(oldEnd - ((oldEnd - n) - pos), pos, ((char*)(oldEnd - n)) - (char*)pos);
            for (uint32_t* p = pos; p != pos + n; ++p) *p = v;
        } else {
            for (uint32_t i = 0; i < n - tail; ++i) oldEnd[i] = v;
            mpEnd += n - tail;
            memmove(mpEnd, pos, tail * 4);
            mpEnd += tail;
            for (uint32_t* p = pos; p != oldEnd; ++p) *p = v;
        }
    }
}

// @ 0x456bb0  (scalar deleting destructor; member range at +0x14..+0x18 has trivial elements)
struct RangeOwner {
    char pad[0x14];
    char* mpBegin;   // +0x14
    char* mpEnd;     // +0x18
    void  Destroy(); // FUN_0045daf0 called on (this+0x14)
};
void* RangeOwner_DeletingDtor(RangeOwner* self, uint32_t flags);
extern void RangeOwner_DtorBody(void* sub);      // FUN_0045daf0, thiscall on this+0x14
void* RangeOwner_DeletingDtor(RangeOwner* self, uint32_t flags)
{
    for (char* p = self->mpBegin; p < self->mpEnd; p += 8) {}
    RangeOwner_DtorBody(&self->mpBegin);
    if (flags & 1)
        EASTL_Free(self);
    return self;
}

// @ 0x456d60  (vector<Elem32>::DoInsertValue: insert one element at pos)
Elem32* ElemVector::DoInsertValue(Elem32* pos, const Elem32* val)
{
    if (mpEnd == mpCapacity) {
        uint32_t oldSize = mpEnd - mpBegin;
        uint32_t newSize = oldSize ? oldSize * 2 : 1;
        Elem32* newBuf = newSize ? (Elem32*)EASTL_Allocate(alloc, newSize << 5, 4, 0) : 0;
        Elem32* newPos = uninitialized_copy_Elem32(mpBegin, pos, newBuf);
        if (newPos) {
            newPos->key = val->key;
            newPos->sub.CopyFrom(&val->sub);
        }
        Elem32* newEnd = uninitialized_copy_Elem32(pos, mpEnd, newPos + 1);
        if (mpBegin && mpBegin != (Elem32*)mpFixedBuf)
            EASTL_Free(mpBegin);
        mpBegin = newBuf;
        mpEnd = newEnd;
        mpCapacity = newBuf + newSize;
    } else {
        const Elem32* src = val;
        if (pos <= val && val < mpEnd)
            ++src;
        if (mpEnd) {
            Elem32* last = mpEnd - 1;
            mpEnd->key = last->key;
            mpEnd->sub.CopyFrom(&last->sub);
        }
        Elem32* d = mpEnd;
        Elem32* s = mpEnd - 1;
        while (s != pos) {
            --s; --d;
            *d = *s;
        }
        *pos = *src;
        ++mpEnd;
    }
    return pos;
}

// @ 0x457030  (Elem32 copy-construct helper, this = dest, arg = src)
struct Elem32Copy {
    int32_t key;
    SubObj  sub;
    Elem32Copy* construct(const Elem32* src);
};
Elem32Copy* Elem32Copy::construct(const Elem32* src)
{
    key = src->key;
    sub.CopyFrom(&src->sub);
    return this;
}

// ---- intrusive-pointer range copy helpers -------------------------------------------
struct RefObj {
    virtual void v0();
    virtual void AddRef();   // vtable +4
    virtual void Release();  // vtable +8
};

// @ 0x4571d0  (copy range of RefObj* forward, with AddRef/Release)
RefObj** copy_ref_forward(RefObj** first, RefObj** last, RefObj** dst)
{
    for (; first != last; ++first) {
        RefObj* p = *first;
        if (p != *dst) {
            RefObj* old = *dst;
            if (p) p->AddRef();
            *dst = p;
            if (old) old->Release();
        }
        ++dst;
    }
    return dst;
}

// @ 0x457250
Elem32* uninitialized_move_Elem32(Elem32* first, Elem32* last, Elem32* dst)
{
    Elem32* r = uninitialized_copy_Elem32(first, last, dst);
    for (Elem32* p = first; p != last; ++p) {}
    return r;
}

// @ 0x4572b0  (rbtree node allocate + construct value at +0x10)
struct NodeValue {
    uint32_t key;
    SubObj2  sub;
};
struct NodeAlloc {
    char pad[0x18];
    uint32_t alloc[1];
    char* DoCreateNode(const NodeValue* v);
};
char* NodeAlloc::DoCreateNode(const NodeValue* v)
{
    char* node = (char*)EASTL_Allocate(alloc, 0x6c, 4, 0);
    NodeValue* val = (NodeValue*)(node + 0x10);
    if (val) {
        val->key = v->key;
        val->sub.CopyFrom(&v->sub);
    }
    return node;
}

// @ 0x457450  (uninitialized_fill_n of 12-byte elements)
struct Triple { uint32_t a, b, c; };
void uninitialized_fill_n_Triple(Triple* dst, int n, const Triple* v)
{
    Triple* p = dst;
    for (; n != 0; --n) {
        if (p) { p->a = v->a; p->b = v->b; p->c = v->c; }
        ++p;
    }
}

// @ 0x4574c0  (copy_backward of RefObj* with AddRef/Release)
RefObj** copy_ref_backward(RefObj** first, RefObj** last, RefObj** dst)
{
    while (last != first) {
        --last; --dst;
        RefObj* p = *last;
        if (p != *dst) {
            RefObj* old = *dst;
            if (p) p->AddRef();
            *dst = p;
            if (old) old->Release();
        }
    }
    return dst;
}

// @ 0x457540
static Elem32* uninitialized_copy_Elem32(Elem32* first, Elem32* last, Elem32* dst)
{
    Elem32* d = dst;
    for (Elem32* s = first; s != last; ++s) {
        if (d) {
            d->key = s->key;
            d->sub.CopyFrom(&s->sub);
        }
        ++d;
    }
    return d;
}
