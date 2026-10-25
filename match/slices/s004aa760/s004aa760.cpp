// Slice s004aa760 — Spore editor container/iterator helpers (x87, /Od /Ob1).
#include "types.h"
#include <new>

// ---------- shared stub types ----------
struct V3 { float x, y, z; V3(const V3& src); };            // copy ctor 0x4098a0
struct Item { float a; V3 b; };

struct cSPMatrix3 {
    float m[9];
    void Assign(const cSPMatrix3& src);                     // 0x41cb40
};

// A 0x34-byte point: matrix33, position, w.
struct OrientedPoint {
    cSPMatrix3 m;   // +0x00
    V3 p;           // +0x24
    float w;        // +0x30
    OrientedPoint(const OrientedPoint& src);                // 0x4aa2f0
};

struct cSPTransformOps {
    void* Assign(const void* src);                          // 0x537dc0
};

// 0x38-byte transform keyed by a leading dword (0x3c-byte vector element).
struct cSPTransform : public cSPTransformOps {
    unsigned short mFlags;              // +0x00
    unsigned short mModificationCount;  // +0x02
    V3 mTranslation;                    // +0x04
    float mScale;                       // +0x10
    cSPMatrix3 mRotation;               // +0x14
    cSPTransform(const cSPTransform& src);                  // 0x40ce80
};

struct TransformKey {
    uint32_t id;            // +0x00
    cSPTransform xform;     // +0x04
    TransformKey& operator=(const TransformKey& o)
    {
        id = o.id;
        xform.Assign(&o.xform);
        return *this;
    }
};

struct DequeIt {
    uint8_t* cur;    // +0x0
    uint8_t* first;  // +0x4
    uint8_t* last;   // +0x8
    uint8_t** node;  // +0xc
    void SetSubarray(void** subarray);  // 0x569340
    DequeIt* Inc();  // 0x4ab210
};

struct DequeBase {
    void* map;        // +0x0
    uint32_t mapSize; // +0x4
    DequeIt begin_;   // +0x8
    DequeIt end_;     // +0x18
    uint32_t alloc[8];// +0x28 allocator storage
    void* AllocNode();                    // 0x4ab320
    void  DequeAlloc(unsigned int n);     // 0x4ab350
    void  ReallocNodeMap(unsigned int n, int flag);  // 0x503470
    void* DoAllocatePtrArray(int n);      // 0x56a240
    void* PushFront(void* value);         // 0x4ab130
};

struct Matrix3Like { char pad[0x24]; Matrix3Like(const Matrix3Like&); };

extern void* EASTL_Allocate(void* alloc, int size, int align, int flags); // 0x42dee0
extern void  FreeRawBlock(void* p);                       // 0xf47380
extern void  FUN_0040ce80(void* p);
extern OrientedPoint* CopyOrientedRange(OrientedPoint* first, OrientedPoint* last,
                                        OrientedPoint* out); // 0x4ab640

// @ 0x004ab210
DequeIt* DequeIt::Inc()
{
    cur += 4;
    if (cur == last) {
        node += 1;
        first = *node;
        last = first + 0x100;
        cur = first;
    }
    return this;
}

// @ 0x004ab320
void* DequeBase::AllocNode()
{
    return EASTL_Allocate((char*)this + 0x28, 0x100, 4, 0);
}

// @ 0x004ab450
uint32_t** FillU32(uint32_t** out, uint32_t* param_dst, int param_count, uint32_t* param_src)
{
    int count = param_count;
    uint32_t* dst = param_dst;
    uint32_t v = *param_src;
    while (count--) *dst++ = v;
    *out = dst;
    return out;
}

// @ 0x004ab4a0
extern void FUN_004ab5b0(Item* begin, Item* end, Item* out);
void CopyItemsWrapper(Item* a, Item* b, Item* c)
{
    bool local = false;
    FUN_004ab5b0(a, b, c);
}

// @ 0x004ab5b0
Item* CopyItems(Item* begin, Item* end, Item* out)
{
    for (; begin != end; ++begin, ++out) {
        if (out != 0) {
            out->a = begin->a;
            out->b = begin->b;
        }
    }
    return out;
}

// @ 0x004ab4d0
Matrix3Like* CopyMatrixRange(Matrix3Like* param_1, Matrix3Like* param_2, Matrix3Like* param_3)
{
    Matrix3Like* local_48 = param_3;
    for (Matrix3Like* local_44 = param_1; local_44 != param_2;
         local_44 = (Matrix3Like*)((char*)local_44 + 0x34)) {
        if (local_48 != 0) {
            new (local_48) Matrix3Like(*local_44);
        }
        local_48 = (Matrix3Like*)((char*)local_48 + 0x34);
    }
    return local_48;
}

// @ 0x004ab530
struct Big34 { uint32_t d[0xf]; };
Big34* CopyBig34Range(Big34* param_1, Big34* param_2, Big34* param_3)
{
    Big34* local_4c = param_3;
    for (Big34* local_48 = param_1; local_48 != param_2;
         local_48 = (Big34*)((char*)local_48 + 0x3c)) {
        if (local_4c != 0) {
            local_4c->d[0] = local_48->d[0];
            FUN_0040ce80((char*)local_48 + 4);
        }
        local_4c = (Big34*)((char*)local_4c + 0x3c);
    }
    return local_4c;
}

// @ 0x004ab280
struct M36 { char pad[0x24]; };
M36* CopyM36Range(M36* param_1, M36* param_2, M36* param_3)
{
    M36* local_44 = param_3;
    for (M36* local_40 = param_1; local_40 != param_2;
         local_40 = (M36*)((char*)local_40 + 0x24)) {
        if (local_44 != 0) {
            *(M36*)local_44 = *(M36*)local_40;
        }
        local_44 = (M36*)((char*)local_44 + 0x24);
    }
    for (M36* local_4c = param_1; local_4c != param_2;
         local_4c = (M36*)((char*)local_4c + 0x24)) {
    }
    return local_44;
}

// @ 0x004ab130
void* DequeBase::PushFront(void* param_2)
{
    void* v = *(void**)param_2;
    if (begin_.node == map) {
        ReallocNodeMap(1, 0);
    }
    begin_.node[-1] = (uint8_t*)AllocNode();
    begin_.SetSubarray((void**)(begin_.node - 1));
    begin_.cur = begin_.last - 4;
    void* r = begin_.cur;
    return r ? (*(void**)r = v, r) : 0;
}

static inline const unsigned int& max_alt(const unsigned int& a, const unsigned int& b)
{
    return a < b ? b : a;
}

// @ 0x004ab350
void DequeBase::DequeAlloc(unsigned int n)
{
    const unsigned int nNewPtrArraySize = (n >> 6) + 1;
    const unsigned int kMinPtrArraySize_ = 8;

    mapSize = max_alt(kMinPtrArraySize_, (nNewPtrArraySize + 2));
    map = DoAllocatePtrArray((int)mapSize);

    uint32_t** const pPtrArrayBegin = (uint32_t**)((char*)map + ((mapSize - nNewPtrArraySize) >> 1) * 4);
    uint32_t** const pPtrArrayEnd = pPtrArrayBegin + nNewPtrArraySize;
    uint32_t** pPtrArrayCurrent = pPtrArrayBegin;

    while (pPtrArrayCurrent < pPtrArrayEnd)
        *pPtrArrayCurrent++ = (uint32_t*)AllocNode();

    begin_.SetSubarray((void**)pPtrArrayBegin);
    begin_.cur = begin_.first;
    end_.SetSubarray((void**)(pPtrArrayEnd - 1));
    end_.cur = end_.first + (n % 0x40) * 4;
}

// =====================================================================
// vector<T>::insert (DoInsertValue) for three element types
// =====================================================================
struct VecOP {
    OrientedPoint* begin;
    OrientedPoint* end;
    OrientedPoint* cap;
    uint32_t alloc;
    void Insert(OrientedPoint* position, const OrientedPoint& value);
};

struct VecTK {
    TransformKey* begin;
    TransformKey* end;
    TransformKey* cap;
    uint32_t alloc;
    void Insert(TransformKey* position, const TransformKey& value);
};

struct VecM33 {
    cSPMatrix3* begin;
    cSPMatrix3* end;
    cSPMatrix3* cap;
    uint32_t alloc;
    void Insert(cSPMatrix3* position, const cSPMatrix3& value);
};

// @ 0x004aa760
void VecOP::Insert(OrientedPoint* position, const OrientedPoint& value)
{
    if (end != cap) {
        OrientedPoint* destPosition = position;
        const OrientedPoint* pValue = &value;
        if (pValue >= destPosition && pValue < end) {
            pValue = pValue + 1;
        }
        OrientedPoint* oldEnd = end;
        if (oldEnd != 0) {
            OrientedPoint* src = oldEnd - 1;
            oldEnd->m.Assign(src->m);
            new (&oldEnd->p) V3(src->p);
            oldEnd->w = src->w;
        }
        OrientedPoint* dstCur = end;
        OrientedPoint* srcCur = end - 1;
        while (srcCur != destPosition) {
            srcCur = srcCur - 1;
            dstCur = dstCur - 1;
            *dstCur = *srcCur;
        }
        *destPosition = *pValue;
        end = end + 1;
    } else {
        unsigned int nPrevSize = (unsigned int)(end - begin);
        unsigned int nNewSize = nPrevSize > 0 ? nPrevSize * 2 : 1;
        OrientedPoint* pNewData = nNewSize
            ? (OrientedPoint*)EASTL_Allocate(&alloc, nNewSize * 0x34, 4, 0) : 0;
        OrientedPoint* pNewEnd = (OrientedPoint*)CopyMatrixRange(
            (Matrix3Like*)begin, (Matrix3Like*)position, (Matrix3Like*)pNewData);
        if (pNewEnd != 0) {
            new (pNewEnd) OrientedPoint(value);
        }
        pNewEnd = pNewEnd + 1;
        pNewEnd = CopyOrientedRange(position, end, pNewEnd);
        if (begin != 0 && *(int*)((char*)begin - 4) != 0) {
            FreeRawBlock(begin);
        }
        begin = pNewData;
        end = pNewEnd;
        cap = pNewData + nNewSize;
    }
}

// @ 0x004aaac0
void VecTK::Insert(TransformKey* position, const TransformKey& value)
{
    if (end != cap) {
        TransformKey* destPosition = position;
        const TransformKey* pValue = &value;
        if (pValue >= destPosition && pValue < end) {
            pValue = pValue + 1;
        }
        TransformKey* oldEnd = end;
        if (oldEnd != 0) {
            TransformKey* src = oldEnd - 1;
            oldEnd->id = src->id;
            new (&oldEnd->xform) cSPTransform(src->xform);
        }
        TransformKey* dstCur = end;
        TransformKey* srcCur = end - 1;
        while (srcCur != destPosition) {
            srcCur = srcCur - 1;
            dstCur = dstCur - 1;
            *dstCur = *srcCur;
        }
        *destPosition = *pValue;
        end = end + 1;
    } else {
        unsigned int nPrevSize = (unsigned int)(end - begin);
        unsigned int nNewSize = nPrevSize > 0 ? nPrevSize * 2 : 1;
        TransformKey* pNewData = nNewSize
            ? (TransformKey*)EASTL_Allocate(&alloc, nNewSize * 0x3c, 4, 0) : 0;
        TransformKey* pNewEnd = (TransformKey*)CopyBig34Range(
            (Big34*)begin, (Big34*)position, (Big34*)pNewData);
        if (pNewEnd != 0) {
            pNewEnd->id = value.id;
            new (&pNewEnd->xform) cSPTransform(value.xform);
        }
        pNewEnd = pNewEnd + 1;
        pNewEnd = (TransformKey*)CopyBig34Range(
            (Big34*)position, (Big34*)end, (Big34*)pNewEnd);
        if (begin != 0 && *(int*)((char*)begin - 4) != 0) {
            FreeRawBlock(begin);
        }
        begin = pNewData;
        end = pNewEnd;
        cap = pNewData + nNewSize;
    }
}

// @ 0x004aae30
void VecM33::Insert(cSPMatrix3* position, const cSPMatrix3& value)
{
    if (end != cap) {
        cSPMatrix3* destPosition = position;
        const cSPMatrix3* pValue = &value;
        if (pValue >= destPosition && pValue < end) {
            pValue = pValue + 1;
        }
        if (end != 0) {
            end->Assign(*(end - 1));
        }
        cSPMatrix3* dstCur = end;
        cSPMatrix3* srcCur = end - 1;
        while (srcCur != destPosition) {
            srcCur = srcCur - 1;
            dstCur = dstCur - 1;
            *dstCur = *srcCur;
        }
        *destPosition = *pValue;
        end = end + 1;
    } else {
        unsigned int nPrevSize = (unsigned int)(end - begin);
        unsigned int nNewSize = nPrevSize > 0 ? nPrevSize * 2 : 1;
        cSPMatrix3* pNewData = nNewSize
            ? (cSPMatrix3*)EASTL_Allocate(&alloc, nNewSize * 0x24, 4, 0) : 0;
        cSPMatrix3* pNewEnd = (cSPMatrix3*)CopyM36Range(
            (M36*)begin, (M36*)position, (M36*)pNewData);
        if (pNewEnd != 0) {
            pNewEnd->Assign(value);
        }
        pNewEnd = pNewEnd + 1;
        pNewEnd = (cSPMatrix3*)CopyM36Range(
            (M36*)position, (M36*)end, (M36*)pNewEnd);
        if (begin != 0 && *(int*)((char*)begin - 4) != 0) {
            FreeRawBlock(begin);
        }
        begin = pNewData;
        end = pNewEnd;
        cap = pNewData + nNewSize;
    }
}
