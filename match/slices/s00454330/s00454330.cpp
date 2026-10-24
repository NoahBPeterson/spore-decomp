// Slice s00454330: EASTL container helpers (intrusive-pointer vectors, rbtree/hash set inserts),
// a few Vector3 helpers and EA::VariantTypeTraits<Key>::GetTPTR.
// Built unoptimized: /Od /Ob1 /arch:SSE (frame pointer, all locals in memory).
// Callees are declared with the calling convention seen at the call site; the bodies live elsewhere.
#include <math.h>
typedef unsigned int  uint32_t_;
typedef unsigned short uint16_t_;

// Intrusive ref-counted object: slot 1 = AddRef (+4), slot 2 = Release (+8).
struct cRefCounted {
    virtual void Slot0();
    virtual void AddRef();
    virtual void Release();
};
struct Vector3 { float x, y, z; };

// ---- external callees (not in this slice) ----
void  __cdecl  RefPtr_CopyBackward(void* first, void* last, void* destEnd);          // 0x4571d0
void* __fastcall Slot_Init0(void* self);                                              // 0x41d050
void* __cdecl  Tree_LowerBound(void* b, void* e, const int* key, bool cmpflag);       // 0x456410
void* __fastcall Tree_AllocNode0(void* self);                                         // 0x440f60
void  __fastcall Tree_ConstructValue(void* self, void* alloc);                        // 0x440ff0
void* __fastcall Tree_DoInsert(void* self, void* pos, void* value);                   // 0x4552e0 (thiscall)
void* __cdecl  EASTL_Allocate(void* alloc, unsigned n, unsigned align, unsigned off); // 0x42dee0
void  __cdecl  EASTL_allocator_deallocate(void* p);                                   // 0xf47380
void  __cdecl  Hashtable_DoFreeNodes(void* b, void* e, void* dest);                   // 0x4554f0
void* __cdecl  Tree2_LowerBound(void* b, void* e, const unsigned* key, bool flag);    // 0x5701b0
void* __cdecl  Tree2_DoInsert(void* self, void* pos, void* value);                    // 0x455590
void  __cdecl  Vec3_PushBackRealloc(void* self, void* pos, const float* v);           // 0x455660
void  __cdecl  Key_FillConstruct(void* at, unsigned n, void* value);                  // 0x541030
void  __cdecl  Key_Copy(void* first, void* last);                                     // eastl::copy do_copy
void  __cdecl  Ptr_FillConstruct(void* at, unsigned n, void* value);                  // 0x4566e0
void  __cdecl  Ptr_Copy(void* first, void* last);                                     // 0x4769b0
void  __cdecl  Vec3_Normalized(Vector3* out, void* in);                               // 0x455c00
float __cdecl  Vec3_Dot(const Vector3* a, const Vector3* b);                          // 0x455c50
void* __cdecl  FUN_006bb640(void* variant);                                           // 0x6bb640
extern "C" void* __cdecl FUN_11e0744_memcpy(void*, const void*, unsigned int);        // 0x011e0744
int   __cdecl  WStr_FindFirst(void* b, void* e, const void* nb, const void* ne);      // 0x455f50
void  __cdecl  Elem32_Destruct(void* p);                                              // 0x4ae250
void* __cdecl  Ptr_Move(void* first, void* last, void* destEnd);                      // 0x4574c0
void  __cdecl  Operator_Delete(void* p);                                              // 0xf47380

// ---- container layouts ----
struct PtrVector { cRefCounted** mpBegin; cRefCounted** mpEnd; cRefCounted** mpCapacity; };

struct RbSet {                // 0x00: begin, 0x04: end(anchor), ... 0x118: compare flag (variant A)
    void* mpBegin; void* mpEnd; char pad[0x110]; bool mFlag118;
};
struct RbSetSmall {           // variant B: flag at 0x98
    void* mpBegin; void* mpEnd; char pad[0x90]; bool mFlag98;
};
struct HashVec8 {             // 8-byte-element vector with an embedded allocator at +0xC and fixed buffer at +0x10
    char* mpBegin; char* mpEnd; char* mpCapacity; int mAlloc; char* mpFixed;
};
struct FloatVec {             // vector<float> (Vector3Template<float>::x slot copies)
    float* mpBegin; float* mpEnd; float* mpCapacity;
};
struct KeyVec { char* mpBegin; char* mpEnd; };          // 12-byte elements (EA::ResourceMan::Key)
struct IntVec { int* mpBegin; int* mpEnd; };            // 4-byte elements
struct WVec   { char* mpBegin; char* mpEnd; char* mpCapacity;      // 2-byte elements (addressed as bytes)
    int find(const wchar_t* needle, unsigned pos, int count); };
struct BlockVec { char* mpBegin; char* mpEnd; char* mpCapacity; int mAlloc; char* mpFixed; }; // 32-byte elements

// @ 0x00454330  (erase one intrusive pointer from a ref-ptr vector; returns position)
struct PtrVecOps : PtrVector {
    cRefCounted** erase(cRefCounted** position)
    {
        if (position + 1 < mpEnd) {
            RefPtr_CopyBackward(position + 1, mpEnd, position);
        }
        --mpEnd;
        if (*mpEnd) {
            (*mpEnd)->Release();
        }
        return position;
    }
};
cRefCounted** __fastcall PtrVec_Erase(PtrVecOps* self, int, cRefCounted** position) { return self->erase(position); }

// @ 0x00454400
void* __fastcall SlotInit_Wrapper(void* self)
{
    Slot_Init0(self);
    return self;
}

// @ 0x00454420
struct RbIntMap : RbSet {
    int* find_or_insert(const int* key)
    {
        int* node = (int*)Tree_LowerBound(mpBegin, mpEnd, key, mFlag118);
        if (node == (int*)mpEnd || *key < *node) {
            void* alloc = Tree_AllocNode0(this);
            int value[9];
            value[0] = *key;
            Tree_ConstructValue(value + 1, alloc);
            node = (int*)Tree_DoInsert(this, node, value);
        }
        return node + 1;
    }
};
int* __fastcall RbIntMap_Index(RbIntMap* self, int, const int* key) { return self->find_or_insert(key); }

// ---- EASTL rbtree pieces used by 0x004544d0 (all but find_or_insert live elsewhere) ----
struct RbNode;
struct RbNodeBase {                    // rbtree node header
    RbNodeBase* mpLeft;                // +0x000
    RbNodeBase* mpRight;               // +0x004
    RbNodeBase* mpParent;              // +0x008
};
struct RbNode : RbNodeBase {           // node value: pair<const unsigned, unsigned> at +0x10
    char     mColor;                   // +0x00c
    char     pad00d[3];
    unsigned mKey;                     // +0x010
    unsigned mValue;                   // +0x014
};
struct MapValue { unsigned mKey; unsigned mValue; };
struct RbIter {                        // 1-word node iterator
    RbNode*   mpNode;
    RbIter*   assign(RbNode* node);    // 0x00566c50  *this = node; returns this
    unsigned* value();                 // 0x00564f50  &node->mKey (the stored pair)
};
// Fixed 8-slot vector EASTL builds on the stack around the insert call.
struct NodeVec {
    void* mpBegin;                     // +0x000
    void* mpEnd;                       // +0x004
    void* mpCapacity;                  // +0x008
    char  mAlloc[8];                   // +0x00c
    void* mpOverflow;                  // +0x014
    char  mFixed[0x40];                // +0x018  8 inline 8-byte slots
    NodeVec* Construct();                        // 0x004727a0  default construction
    NodeVec* ConstructFrom(const NodeVec& src);  // 0x00455cf0  construction from another's allocator state
    void     Destroy();                          // 0x0045daf0  destroys the elements and frees storage
};
struct RbTree {
    char       pad000[4];
    RbNodeBase mAnchor;                // +0x004  end() sentinel node; mAnchor.mpParent (+0x00c) is the root
    RbIter* find(RbIter* out, const unsigned* key);                 // 0x004b5e90  lower_bound
    RbIter* insert(RbIter* out, RbIter position, const MapValue* value);  // 0x00455460
};
struct RbUIntMap2 : RbTree {
    unsigned* find_or_insert(const unsigned* key);
};
// @ 0x004544d0
unsigned* RbUIntMap2::find_or_insert(const unsigned* key)
{
    RbIter found;
    find(&found, key);
    RbIter end;
    end.assign((RbNode*)&mAnchor);
    if (found.mpNode == end.mpNode || *key < *found.value()) {
        // not present: build the value and insert it at the lower bound
        NodeVec scratchA;
        scratchA.Construct();
        MapValue value;
        value.mKey = *key;
        value.mValue = 0;
        NodeVec scratchB;
        scratchB.ConstructFrom(scratchA);
        RbIter out;
        insert(&out, found, &value);
        found = out;
        // the element destructors of both scratch vectors run inline (trivial 8-byte slots) before the storage is freed
        for (char* p = (char*)scratchB.mpBegin; p < (char*)scratchB.mpEnd; p += 8) {}
        scratchB.Destroy();
        for (char* p = (char*)scratchA.mpBegin; p < (char*)scratchA.mpEnd; p += 8) {}
        scratchA.Destroy();
    }
    return found.value() + 1;
}

// @ 0x00454640  (vector reserve for 8-byte elements with fixed-buffer allocator)
void __fastcall HashVec8_reserve(HashVec8* self, int, unsigned n)
{
    if ((unsigned)((self->mpCapacity - self->mpBegin) >> 3) < n) {
        char* newData = n ? (char*)EASTL_Allocate(&self->mAlloc, n << 3, 4, 0) : 0;
        Hashtable_DoFreeNodes(self->mpBegin, self->mpEnd, newData);
        int cap = (int)(self->mpCapacity - self->mpBegin) >> 3;
        (void)cap;
        if (self->mpBegin && self->mpBegin != self->mpFixed) {
            EASTL_allocator_deallocate(self->mpBegin);
        }
        int size = (int)(self->mpEnd - self->mpBegin) >> 3;
        self->mpBegin = newData;
        self->mpEnd = newData + size * 8;
        self->mpCapacity = self->mpBegin + n * 8;
    }
}

// @ 0x00454730
void* __fastcall SlotInit_Wrapper2(void* self)
{
    Slot_Init0(self);  // calls 0x4fc4a0
    return self;
}

// @ 0x00454750
struct RbUIntSet : RbSetSmall {
    unsigned* find_or_insert(const unsigned* key)
    {
        unsigned* node = (unsigned*)Tree2_LowerBound(mpBegin, mpEnd, key, mFlag98);
        if (node == (unsigned*)mpEnd || *key < *node) {
            unsigned value[3];
            value[1] = 0;
            value[0] = *key;
            value[2] = value[1];
            node = (unsigned*)Tree2_DoInsert(this, node, value);
        }
        return node + 1;
    }
};
unsigned* __fastcall RbUIntSet_Index(RbUIntSet* self, int, const unsigned* key) { return self->find_or_insert(key); }

// @ 0x004547f0  (vector<Vector3Template<float>-element, 4 bytes>::push_back)
void __fastcall FloatVec_push_back(FloatVec* self, int, const float* value)
{
    if (self->mpEnd < self->mpCapacity) {
        float* p = self->mpEnd;
        self->mpEnd = self->mpEnd + 1;
        if (p) {
            *p = *value;
        }
    } else {
        Vec3_PushBackRealloc(self, self->mpEnd, value);
    }
}

// @ 0x004548d0  (vector<Key> resize)
void __fastcall KeyVec_resize(KeyVec* self, int, unsigned n)
{
    if ((unsigned)((self->mpEnd - self->mpBegin) / 12) < n) {
        unsigned zero[3] = {0, 0, 0};
        Key_FillConstruct(self->mpEnd, n - (self->mpEnd - self->mpBegin) / 12, zero);
    } else {
        Key_Copy(self->mpBegin + n * 12, self->mpEnd);
    }
}

// @ 0x004549b0  (remove(first,last,value) for intrusive ptr ranges)
cRefCounted** PtrRange_Remove(cRefCounted** first, cRefCounted** last, cRefCounted* const* value)
{
    cRefCounted** it = first;
    while (it != last && *it != *value) ++it;
    if (it != last) {
        cRefCounted** dest = it;
        while (++it != last) {
            if (*it != *value) {
                cRefCounted* src = *it;
                if (src != *dest) {
                    cRefCounted* old = *dest;
                    if (src) src->AddRef();
                    *dest = src;
                    if (old) old->Release();
                }
                ++dest;
            }
        }
    }
    return it;
}

// @ 0x00454aa0  (angle between two vectors)
float __cdecl Vec3_AngleBetween(void* a, void* b)
{
    Vector3 na, nb, t1, t2;
    Vec3_Normalized(&t1, a); na = t1;
    Vec3_Normalized(&t2, b); nb = t2;
    float d = Vec3_Dot(&na, &nb);
    return (float)acos(d);
}

// @ 0x00454b10  EA::VariantTypeTraits<EA::ResourceMan::Key>::GetTPTR
struct Variant {
    void* mData;            // 0x00 (heap pointer when the 0x30 flags are set)
    char pad[0x0C];
    unsigned short mFlags;  // 0x10
    unsigned short mType;   // 0x12
};
void* __fastcall VariantTypeTraits_Key_GetTPTR(Variant* v)
{
    void* result;
    if (v->mType == 0x20 || v->mType == 0x10) {
        if ((v->mFlags & 0x30) == 0) {
            result = v;
            if (v->mType == 0) result = 0;
        } else {
            result = v->mData;
        }
    } else {
        result = FUN_006bb640(v);
    }
    return result;
}

// @ 0x00454b80  (vector<ptr> resize)
void __fastcall PtrVecInt_resize(IntVec* self, int, unsigned n)
{
    if ((unsigned)((self->mpEnd - self->mpBegin)) >> 2 < n) {
        int zero = 0;
        Ptr_FillConstruct(self->mpEnd, n - (unsigned)(self->mpEnd - self->mpBegin) / 4, &zero);
    } else {
        Ptr_Copy((char*)self->mpBegin + n * 4, self->mpEnd);
    }
}

// @ 0x00454c00  (cross product)
Vector3* __cdecl Vec3_Cross(Vector3* out, const Vector3* a, const Vector3* b)
{
    float az = a->z, bx = b->x, ax = a->x, bz = b->z, by = b->y, ay = a->y;
    out->x = a->y * b->z - b->y * a->z;
    out->y = az * bx - ax * bz;
    out->z = ax * by - ay * bx;
    return out;
}

// eastl::basic_string<char>::assign(first, last)
struct BasicString { char* mpBegin; char* mpEnd; char* mpCapacity;
    BasicString* assign(const char* first, const char* last);
    BasicString* append(const char* first, const char* last);   // 0x00455d60
    char*        erase(char* first, char* last);                // 0x0045f080
};
// @ 0x00454cb0
BasicString* BasicString::assign(const char* first, const char* last)
{
    unsigned n = (unsigned)(last - first);
    if (n > (unsigned)(mpEnd - mpBegin)) {
        // too long for the current buffer: keep the bytes that fit and append the rest
        FUN_11e0744_memcpy(mpBegin, first, (unsigned)(mpEnd - mpBegin));
        append(first + (mpEnd - mpBegin), last);
    } else {
        FUN_11e0744_memcpy(mpBegin, first, n);
        erase(mpBegin + n, mpEnd);
    }
    return this;
}

// wide string find: returns the element index of the first match, or -1
// @ 0x00454d50
int WVec::find(const wchar_t* needle, unsigned pos, int count)
{
    if (pos < (unsigned)((mpEnd - mpBegin) >> 1)) {
        char* p = (char*)WStr_FindFirst(mpBegin + pos * 2, mpEnd, needle, needle + count);
        if (p != mpEnd) {
            return (int)(p - mpBegin) >> 1;
        }
    }
    return -1;
}

// @ 0x00454dc0  (erase range of 32-byte elements, returns first)
char* __fastcall Block32_erase(BlockVec* self, int, char* first, char* last)
{
    char* end = self->mpEnd;
    char* dst = first;
    for (char* src = last; src != end; src += 0x20) {
        for (int i = 0; i < 8; ++i) ((unsigned*)dst)[i] = ((unsigned*)src)[i];
        dst += 0x20;
    }
    end = self->mpEnd;
    for (char* p = dst; p < end; p += 0x20) {
        Elem32_Destruct(p);
    }
    self->mpEnd -= ((int)(last - first) >> 5) * 0x20;
    return first;
}

// @ 0x00454e90  (release every pointer in [first,last))
struct PtrRangeOwner { void ReleaseRange(cRefCounted** first, cRefCounted** last); };
void PtrRangeOwner::ReleaseRange(cRefCounted** first, cRefCounted** last)
{
    for (; first < last; ++first) {
        if (*first) (*first)->Release();
    }
}

// vector<intrusive_ptr>::DoInsertValue(position, value)
struct RefPtrVec { cRefCounted** mpBegin; cRefCounted** mpEnd; cRefCounted** mpCapacity; int mAlloc;
    void DoInsertValue(cRefCounted** position, cRefCounted** value);
};
// @ 0x00454ee0
void RefPtrVec::DoInsertValue(cRefCounted** position, cRefCounted** value)
{
    if (mpEnd == mpCapacity) {
        // grow: copy the slot before the insertion point, construct the new element, copy the tail
        int size = (int)(mpEnd - mpBegin);
        int newCap = size > 0 ? size << 1 : 1;
        cRefCounted** newData = newCap ? (cRefCounted**)EASTL_Allocate(&mAlloc, newCap << 2, 4, 0) : 0;
        int before = (int)(position - mpBegin);
        cRefCounted** slot = (cRefCounted**)FUN_11e0744_memcpy(newData, mpBegin, before * 4) + before;
        if (slot) {
            *slot = *value;
            if (*slot) (*slot)->AddRef();
        }
        ++slot;
        int after = (int)(mpEnd - position);
        slot = (cRefCounted**)FUN_11e0744_memcpy(slot, position, after * 4) + after;
        if (mpBegin && ((int*)mpBegin)[-1] != 0) {
            Operator_Delete(mpBegin);
        }
        mpBegin = newData;
        mpEnd = slot;
        mpCapacity = newData + newCap;
    } else {
        // shift the tail one slot up, then assign the new pointer at the position
        cRefCounted* const* v = value;
        if (position <= value && value < mpEnd) ++v;
        cRefCounted** e = mpEnd;
        if (e) {
            *e = e[-1];
            if (*e) (*e)->AddRef();
        }
        Ptr_Move(position, mpEnd - 1, mpEnd);
        cRefCounted* nv = *v;
        if (nv != *position) {
            cRefCounted* old = *position;
            if (nv) nv->AddRef();
            *position = nv;
            if (old) old->Release();
        }
        ++mpEnd;
    }
}

// @ 0x004551e0  (uninitialized copy of intrusive pointers)
cRefCounted** __cdecl RefPtr_UninitCopy(cRefCounted** first, cRefCounted** last, cRefCounted** dest)
{
    for (; first != last; ++first) {
        if (dest) {
            *dest = *first;
            if (*dest) (*dest)->AddRef();
        }
        ++dest;
    }
    return dest;
}

// @ 0x00455290  (free storage unless it is the fixed buffer)
void __fastcall BlockVec_FreeStorage(BlockVec* self)
{
    if (self->mpBegin && self->mpBegin != self->mpFixed) {
        EASTL_allocator_deallocate(self->mpBegin);
    }
}

// @ 0x004552e0  (rbtree insert with hint)
struct RbHint : RbSet {
    int* insert_hint(int* position, int* key)
    {
        int* node;
        if (position == (int*)mpEnd || *position <= *key) {
            node = (int*)Tree_LowerBound(position, mpEnd, key, mFlag118);
        } else {
            node = (int*)Tree_LowerBound(mpBegin, position, key, mFlag118);
        }
        if (node == (int*)mpEnd || *key < *node) {
            node = (int*)Tree2_DoInsert(this, node, key);   // 0x456360
        }
        return node;
    }
};
int* __fastcall RbHint_insert(RbHint* self, int, int* position, int* key) { return self->insert_hint(position, key); }
