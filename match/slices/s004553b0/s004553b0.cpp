// slice s004553b0 -- EASTL container helpers and small string/vector utilities.
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast module.
#include "types.h"

struct Vec3 { float x, y, z; };

extern void  FUN_0050d750(void* p);
extern int   FUN_00456410(int a, int b, int* c, unsigned char d);
extern void  FUN_00456bb0(int a);
extern void  FUN_004570f0(void* a, void* b, void* c, void* d, unsigned char e);
extern void  FUN_00457170(void* a, int n, void* v, unsigned char e);
extern void  FUN_00456c10(void* a, void* b, void* c);
extern void* FUN_00456cb0(void* a, void* b, void* c);
extern void  FUN_0044d960(void* a);
extern void  FUN_004ae250(void* a);
extern void* FUN_0042dee0(void* a, int n, int sz, int z);
extern void* FUN_005701b0(void* a, void* b, void* c, unsigned char d);
extern void* EASTL_allocator_deallocate(void* p, int n); // 0x00f47380
extern float FUN_004565f0(int s);
extern void  FUN_00456650(void* out, int s, float f);
extern void* FUN_11e0744_alloc(unsigned int n);
extern void  FUN_11e0744_copy(void* dst, void* src, int n);

// eastl::vector<T, sp_vector_allocator> element moves: this module calls a statically linked
// memcpy directly (0x011e0744) but memmove through the import table (call [__imp__memmove]).
extern "C" void* __cdecl FUN_11e0744_memcpy(void*, const void*, unsigned int);   // 0x011e0744
__declspec(dllimport) void __cdecl memmove(void*, const void*, unsigned int);
void __cdecl FUN_00f47380_dealloc(void* block);                                  // 0x00f47380

// Placement new, as the retail eastl code uses it (`::new(p) T(v)`).
inline void* operator new(unsigned int, void* p) { return p; }

// @ 0x00455cc0
float Dot3(const Vec3* a, const Vec3* b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

// @ 0x00455c50
float ClampDot(const Vec3* a, const Vec3* b) {
    float d = Dot3(a, b);
    if (d < -1.0f) {
        d = -1.0f;
    } else {
        if (d > 1.0f) {
            d = 1.0f;
        } else {
            d = d;
        }
    }
    return d;
}

// @ 0x00455f50
short* FindFirst(short* begin, short* end, short* valsBegin, short* valsEnd) {
    short* it;
    for (;;) {
        if (begin == end)
            return end;
        for (it = valsBegin; it != valsEnd; ++it) {
            if (*begin == *it)
                return begin;
        }
        ++begin;
    }
}

struct FixedC {
    int* InitFixed(void* p);      // 0x00455cf0
    void FUN_0050d750(void* p);   // 0x0050d750, ecx = this
};

// @ 0x00455cf0
int* FixedC::InitFixed(void* p) {
    ((int*)this)[0] = 0;
    ((int*)this)[1] = 0;
    ((int*)this)[2] = 0;
    ((int*)this)[5] = 0;
    ((int*)this)[0] = (int)((int*)this + 6);
    ((int*)this)[1] = ((int*)this)[0];
    ((int*)this)[2] = ((int*)this)[0] + 0x40;
    FUN_0050d750(p);
    return (int*)this;
}

// ---------------------------------------------------------------------------
// EASTL helpers (approximations; not byte-exact)
// ---------------------------------------------------------------------------

struct Iter;
struct HT {
    int* mpBegin;              // +0
    int* mpEnd;                // +4
    char pad8[0x98 - 8];
    unsigned char mField98;    // +0x98  (used by insert)
    char pad99[0x118 - 0x99];
    unsigned char mField118;   // +0x118 (used by find)
    Iter* Find(Iter* out, int* key);
    int* Insert(int* pos, int* value);
    int* FUN_00533740(int* node, int* value);   // 0x00533740, thiscall
};

struct Iter { int* first; int* second; };

// @ 0x004553b0
Iter* HT::Find(Iter* out, int* key) {
    HT* self = this;
    int* node = (int*)FUN_00456410((int)self->mpBegin, (int)self->mpEnd, key, self->mField118);
    if (node == self->mpEnd || *key < *node) {
        out->first = node;
        out->second = node;
    } else {
        out->first = node;
        out->second = node + 8;
    }
    return out;
}

struct Node { Node* p0; Node* p1; };
struct NodeOwner {
    void FreeTree(Node* node);          // 0x004554a0
    void FUN_00456bb0(int a);           // 0x00456bb0, ecx = node
};

// @ 0x004554a0
void NodeOwner::FreeTree(Node* node) {
    while (node != 0) {
        FreeTree(node->p0);
        Node* next = node->p1;
        ((NodeOwner*)node)->FUN_00456bb0(0);
        FUN_00f47380_dealloc(node);
        node = next;
    }
}

// @ 0x004554f0
void* DoFreeNodes(void* first, void* last, void* dest) {
    char* d = (char*)dest;
    for (char* f = (char*)first; f != (char*)last; f += 8, d += 8) {
        if (dest != 0) {
            *(int*)(d + 0) = *(int*)(f + 0);
            *(int*)(d + 4) = *(int*)(f + 4);
        }
    }
    for (char* f = (char*)first; f != (char*)last; f += 8) {
    }
    return d;
}

// @ 0x00455590
int* HT::Insert(int* pos, int* value) {
    HT* self = this;
    int* node;
    if (pos == self->mpEnd || !((unsigned)*value < (unsigned)*pos))
        node = (int*)FUN_005701b0(pos, self->mpEnd, value, self->mField98);
    else
        node = (int*)FUN_005701b0(self->mpBegin, pos, value, self->mField98);
    if (node == self->mpEnd || (unsigned)*value < (unsigned)*node)
        node = FUN_00533740(node, value);
    return node;
}

// @ 0x00455ae0 -- move 0x14-stride elements down over [param2,param3)
struct Vec14 { int* self_[2]; void* Move14(void* param2, void* param3); };
void* Vec14::Move14(void* param2, void* param3) {
    int* self = (int*)this;
    char* dst = (char*)param2;
    char* end = (char*)self[1];
    for (char* src = (char*)param3; src != end; src += 0x14, dst += 0x14) {
        *(int*)(dst + 0x00) = *(int*)(src + 0x00);
        *(int*)(dst + 0x04) = *(int*)(src + 0x04);
        *(int*)(dst + 0x08) = *(int*)(src + 0x08);
        *(int*)(dst + 0x0c) = *(int*)(src + 0x0c);
        *(int*)(dst + 0x10) = *(int*)(src + 0x10);
    }
    for (char* it = dst; it < (char*)self[1]; it += 0x14) {
    }
    int n = ((char*)param3 - (char*)param2) / 0x14;
    self[1] = self[1] - n * 0x14;
    return param2;
}

// @ 0x00455c00
void* ParseVec3(void* out, const char* s) {
    float f = FUN_004565f0((int)s);
    float local[3];
    FUN_00456650(local, (int)s, f);
    ((float*)out)[0] = local[0];
    ((float*)out)[1] = local[1];
    ((float*)out)[2] = local[2];
    return out;
}
extern float FUN_004565f0(int s);
extern void  FUN_00456650(void* out, int s, float f);

// @ 0x00455d60 -- eastl::basic_string<char>::append(first,last)
int* StringAppend(int* self, const char* first, const char* last) {
    if (first != last) {
        int oldSize = self[1] - self[0];
        int n = (int)last - (int)first;
        unsigned int capacity = (unsigned int)((self[2] - self[0]) - 1);
        if (capacity < (unsigned int)(oldSize + n)) {
            unsigned int newCap = (unsigned int)(oldSize + n);
            unsigned int cap2 = capacity <= 8 ? 8 : capacity * 2;
            unsigned int alloc = (cap2 < newCap ? newCap : cap2) + 1;
            char* p = (char*)FUN_11e0744_alloc(alloc);
            FUN_11e0744_copy(p, (void*)self[0], oldSize);
            FUN_11e0744_copy(p + oldSize, (void*)first, n);
            p[oldSize + n] = 0;
            if (self[2] - self[0] > 1) {
                if (self[0] != 0)
                    EASTL_allocator_deallocate((void*)self[0], 0);
            }
            self[0] = (int)p;
            self[1] = (int)(p + oldSize + n);
            self[2] = (int)(p + alloc);
        } else {
            FUN_11e0744_copy((void*)(self[1] + 1), (void*)(first + 1), n - 1);
            *(char*)(self[1] + n) = 0;
            *(char*)self[1] = *first;
            self[1] += n;
        }
    }
    return self;
}
extern void* FUN_11e0744_alloc(unsigned int n);
extern void  FUN_11e0744_copy(void* dst, void* src, int n);

// @ 0x00455fa0 -- vector-of-0x20 insert/resize (partial approximation)
void* VecInsert32(int* self, void* position, unsigned int count, void* value) {
    if (count > (unsigned int)((self[2] - self[1]) >> 5)) {
        int oldSize = (self[1] - self[0]) >> 5;
        unsigned int newCap = oldSize == 0 ? 1 : (unsigned int)(oldSize << 1);
        unsigned int need = (unsigned int)oldSize + count;
        unsigned int total = newCap < need ? need : newCap;
        char* p = (char*)FUN_0042dee0(self + 3, (int)total << 5, 4, 0);
        char* end = (char*)FUN_00456cb0((void*)self[0], position, p);
        FUN_00457170(end, (int)count, value, 0);
        end = (char*)FUN_00456cb0(position, (void*)self[1], end + (count << 5));
        if (self[0] != 0 && *(int*)(self[0] - 4) != 0)
            EASTL_allocator_deallocate((void*)self[0], 0);
        self[0] = (int)p;
        self[1] = (int)end;
        self[2] = (int)(p + (total << 5));
    } else if (count != 0) {
        FUN_0044d960(value);
        unsigned int tail = (unsigned int)((self[1] - (int)position) >> 5);
        char* oldEnd = (char*)self[1];
        if (count < tail) {
            FUN_004570f0(0, (void*)(self[1] - (count << 5)), (void*)self[1], (void*)self[1], 0);
            self[1] += count << 5;
            for (char* it = oldEnd - (count << 5); it != position; )
                it -= 0x20;
        } else {
            FUN_00457170((void*)self[1], (int)(count - tail), 0, 0);
            self[1] += (count - tail) << 5;
            FUN_00456c10(position, oldEnd, (void*)self[1]);
            self[1] += tail << 5;
        }
        FUN_004ae250(0);
    }
    return position;
}

// ---------------------------------------------------------------------------------------------
// eastl::vector<T, sp_vector_allocator> plus the eastl helpers its DoInsertValue expands.
// The helper text below mirrors the retail eastl headers (eastl/vector.h, algorithm.h, memory.h);
// they are `inline`, so /Ob1 expands them into the two instantiations exactly as the retail did.
// { T* mpBegin; T* mpEnd; T* mpCapacity; Allocator mAllocator; } with a 4-byte element type.
// ---------------------------------------------------------------------------------------------

template <typename T>
inline T* eastl_copy(const T* first, const T* last, T* result) // copy_impl<true,RA>::do_copy (memcpy path)
{
    return (T*)FUN_11e0744_memcpy(result, first, (unsigned)last - (unsigned)first) + (last - first);
}

template <typename T>
inline T* eastl_uninitialized_copy_ptr(const T* first, const T* last, T* result)
{
    const bool bA = true;
    T* p = eastl_copy(first, last, result);
    const bool bB = true;
    return p;
}

template <typename T>
inline void eastl_copy_backward_impl(const T* first, const T* last, T* result) // copy_backward_impl<true,RA>
{
    memmove((T*)result - (last - first), first, (unsigned)last - (unsigned)first);
}

template <typename T>
inline void eastl_copy_backward_chooser(const T* first, const T* last, T* result)
{
    const bool bHasTrivialCopy = true;
    eastl_copy_backward_impl(first, last, result);
}

template <typename T>
inline void eastl_copy_backward(const T* first, const T* last, T* result)
{
    const bool bInputIsGenericIterator  = false;
    const bool bOutputIsGenericIterator = false;
    eastl_copy_backward_chooser(first, last, result);
}

inline unsigned eastl_GetNewCapacity(unsigned currentCapacity) // VectorBase::GetNewCapacity
{
    // This needs to return a value of at least currentCapacity and at least 1.
    return (currentCapacity > 0) ? (2 * currentCapacity) : 1;
}

template <typename T>
inline T* eastl_DoAllocate(void* allocator, unsigned n) // VectorBase::DoAllocate
{
    // If n is zero, then we allocate no memory and just return NULL.
    return n ? (T*)FUN_0042dee0(allocator, n * sizeof(T), 4, 0) : 0;
}

inline void eastl_sp_deallocate(void* p, unsigned n) // sp_vector_allocator::deallocate
{
    if (((int*)p)[-1]) { void* q = p; FUN_00f47380_dealloc(q); }
}

template <typename T>
inline void eastl_DoFree(T* p, unsigned n) // VectorBase::DoFree
{
    if (p) eastl_sp_deallocate(p, n * sizeof(T));
}

struct SPVecFloat_s004553b0 {
    float* mBegin;        // +0x00
    float* mEnd;          // +0x04
    float* mCapacity;     // +0x08
    void*  mAllocator;    // +0x0c
    void VectorPushBack3(float* position, const float& value);
};

struct SPVecU32_s004553b0 {
    unsigned* mBegin;     // +0x00
    unsigned* mEnd;       // +0x04
    unsigned* mCapacity;  // +0x08
    void*     mAllocator; // +0x0c
    void VectorInsertU32(unsigned* position, const unsigned& value);
};

// @ 0x00455660
void SPVecFloat_s004553b0::VectorPushBack3(float* position, const float& value)
{
    if (mEnd != mCapacity) // If size < capacity ...
    {
        // We need to take into account the possibility that value may come from within the vector itself.
        const float* pValue = &value;
        if ((pValue >= position) && (pValue < mEnd)) // If value comes from within the range to be moved...
            ++pValue;
        ::new(mEnd) float(*(mEnd - 1));
        eastl_copy_backward(position, mEnd - 1, mEnd); // We need copy_backward because of potential overlap issues.
        *position = *pValue;
        ++mEnd;
    }
    else // else (size == capacity)
    {
        const unsigned nPrevSize = (unsigned)(mEnd - mBegin);
        const unsigned nNewSize  = eastl_GetNewCapacity(nPrevSize);
        float* const   pNewData  = eastl_DoAllocate<float>(&mAllocator, nNewSize);

        float* pNewEnd = eastl_uninitialized_copy_ptr(mBegin, position, pNewData);
        ::new(pNewEnd) float(value);
        pNewEnd = eastl_uninitialized_copy_ptr(position, mEnd, ++pNewEnd);

        eastl_DoFree(mBegin, (unsigned)(mCapacity - mBegin));

        mBegin    = pNewData;
        mEnd      = pNewEnd;
        mCapacity = pNewData + nNewSize;
    }
}

// @ 0x004558a0
void SPVecU32_s004553b0::VectorInsertU32(unsigned* position, const unsigned& value)
{
    if (mEnd != mCapacity) // If size < capacity ...
    {
        // We need to take into account the possibility that value may come from within the vector itself.
        const unsigned* pValue = &value;
        if ((pValue >= position) && (pValue < mEnd)) // If value comes from within the range to be moved...
            ++pValue;
        ::new(mEnd) unsigned(*(mEnd - 1));
        eastl_copy_backward(position, mEnd - 1, mEnd); // We need copy_backward because of potential overlap issues.
        *position = *pValue;
        ++mEnd;
    }
    else // else (size == capacity)
    {
        const unsigned nPrevSize = (unsigned)(mEnd - mBegin);
        const unsigned nNewSize  = eastl_GetNewCapacity(nPrevSize);
        unsigned* const pNewData = eastl_DoAllocate<unsigned>(&mAllocator, nNewSize);

        unsigned* pNewEnd = eastl_uninitialized_copy_ptr(mBegin, position, pNewData);
        ::new(pNewEnd) unsigned(value);
        pNewEnd = eastl_uninitialized_copy_ptr(position, mEnd, ++pNewEnd);

        eastl_DoFree(mBegin, (unsigned)(mCapacity - mBegin));

        mBegin    = pNewData;
        mEnd      = pNewEnd;
        mCapacity = pNewData + nNewSize;
    }
}
// --- equivalence checker address annotations
    void EASTL_allocator_deallocate(...); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
