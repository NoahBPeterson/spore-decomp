// Slice s004b9960: Editor resource ctors/dtors (cEditorResource / cPropertyList) plus a vector
// DoInsertValue and an AsInterface thunk. Unoptimized editor module: /Od /Ob1 /arch:SSE, no /EHsc.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

extern void* g_vtblA;   // 0x013ebcc8
extern void* g_vtblB;   // 0x013ef8d4
extern void* g_vtblC;   // Editor::cPropertyList
extern void* g_vtblD;   // Editor::cEditorResource
extern void* g_vtblE;   // 0x013eeda4

extern "C" {
    void  FUN_004329e0();
    void  FUN_004b1700();
    void* __fastcall FUN_00429360(void* self, int dummy, void* arg);
    void  FUN_00427440();
    void  FUN_00425990(void* vec);
    void  FUN_0041e5d0();
    void  FUN_004250b0();
    void  Memset32(void* dst, int value, int count);
    void  FUN_0042xxx_push(void* v);
    void* SP_cResourceBase_AsInterface2(void* self, int type);
}

struct cResourceBase;
class cEditorResource;
struct cResourceBase { cResourceBase* AsInterface(int type); };

extern "C" void* memcpy(void*, const void*, uint32_t);   // @ 0x11e0744
inline void* operator new(unsigned int, void* p) { return p; }

// ---- EA::AutoRefCount<SP::cSPEditorModel> ------------------------------------------------
// Refcounted model object: the count lives in the RefCounted sub-object at +0x04, so the
// integer that AddRef bumps is at +0x08.
struct EditorRefCount {
    void*    mpVtbl;      // +0x00
    int32_t  mCount;      // +0x04
    void AddRef() { ++mCount; }
};
struct cSPEditorModel {
    void*          mpVtbl;        // +0x00
    EditorRefCount mRefCount;     // +0x04 (mCount at +0x08)
};

// 4-byte smart pointer, the element type of the model vector.
struct EditorModelRef {
    cSPEditorModel* mpObject;                                    // +0x00
    EditorModelRef() : mpObject(0) {}
    EditorModelRef(const EditorModelRef& r) : mpObject(r.mpObject) { if (mpObject) mpObject->mRefCount.AddRef(); }
    EditorModelRef& operator=(cSPEditorModel* p);                // @ 0x41d980
    EditorModelRef& operator=(const EditorModelRef& r) { return operator=(r.mpObject); }
};

// Block header EASTL stores in front of every allocation (owner id at -0x04).
struct EastlBlockHeader {
    int32_t mPad;         // -0x08
    int32_t mOwner;       // -0x04
};

struct EditorModelVector {
    EditorModelRef* mpBegin;      // +0x00
    EditorModelRef* mpEnd;        // +0x04
    EditorModelRef* mpCapacity;   // +0x08
    char            mAllocator[4];// +0x0c
    void DoInsertValue(EditorModelRef* position, const EditorModelRef* value);  // @ 0x4b9960
};

extern "C" {
    void* EASTL_Allocate(void* pAllocator, uint32_t size, uint32_t alignment, int flags); // @ 0x42dee0
    void  FreeRawBlock(void* p);                                                          // @ 0xf47380
}

// @ 0x4b9960
void EditorModelVector::DoInsertValue(EditorModelRef* position, const EditorModelRef* value)
{
    if (mpEnd == mpCapacity) {
        // grow: copy head and tail around the inserted element, then swap the buffer
        const int count = (int)(mpEnd - mpBegin);
        const int capacity = (count > 0) ? count * 2 : 1;
        EditorModelRef* pNew = capacity
            ? (EditorModelRef*)EASTL_Allocate(mAllocator, (uint32_t)(capacity * 4), 4, 0)
            : 0;
        const EditorModelRef* pOld = mpBegin;
        const int headCount = (int)(position - mpBegin);
        EditorModelRef* pMid = (EditorModelRef*)memcpy(pNew, pOld, (uint32_t)((const char*)position - (const char*)pOld)) + headCount;
        if (pMid)
            new (pMid) EditorModelRef(*value);
        const int tailCount = (int)(mpEnd - position);
        EditorModelRef* pNewEnd = (EditorModelRef*)memcpy(pMid + 1, position,
                            (uint32_t)((const char*)mpEnd - (const char*)position)) + tailCount;
        if (mpBegin) {
            EastlBlockHeader* pHeader = ((EastlBlockHeader*)mpBegin) - 1;
            if (pHeader->mOwner)
                FreeRawBlock(mpBegin);
        }
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpCapacity = pNew + capacity;
    } else {
        // in place: keep a pointer to the value if it aliases the vector itself
        const EditorModelRef* pValue = value;
        if (!(pValue < position) && pValue < mpEnd)
            pValue = value + 1;
        EditorModelRef* pLast = mpEnd;
        if (pLast)
            new (pLast) EditorModelRef(mpEnd[-1]);
        EditorModelRef* pDest = mpEnd;
        EditorModelRef* pSrc = mpEnd - 1;
        while (pSrc != position) {
            --pSrc;
            --pDest;
            pDest->operator=(pSrc->mpObject);
        }
        position->operator=(pValue->mpObject);
        ++mpEnd;
    }
}

// @ 0x4b9c70
int* __fastcall FUN_004b9c70(int* p)
{
    FUN_004329e0();
    *p = (int)&g_vtblA;
    p[5] = 0;
    *p = (int)&g_vtblB;
    for (int i = 3; i >= 0; i--) {
    }
    p[0x26] = 0;
    p[0x27] = 0;
    p[0x28] = 0;
    Memset32(p + 6, 0, 0x20);
    return p;
}

// @ 0x4b9d40
void __fastcall FUN_004b9d40(int* p)
{
    *p = (int)&g_vtblB;
    for (uint32_t i = p[0x26]; i < (uint32_t)p[0x27]; i += 0x1d8) {
    }
    FUN_004b1700();
    *p = (int)&g_vtblC;
    *p = (int)&g_vtblD;
}

// @ 0x4b9da0
int* __fastcall FUN_004b9da0(int* p)
{
    char tag;
    FUN_004329e0();
    *p = (int)&g_vtblA;
    p[5] = 0;
    *p = (int)&g_vtblE;
    for (int i = 3; i >= 0; i--) {
    }
    p[0x26] = 0;
    p[0x27] = 0;
    p[0x28] = 0;
    FUN_00429360((char*)p + 0xa4, 0, &tag);
    p[0x2b] = 0; p[0x2c] = 0; p[0x2d] = 0;
    FUN_00429360((char*)p + 0xb8, 0, &tag);
    p[0x30] = 0; p[0x31] = 0; p[0x32] = 0;
    FUN_00429360((char*)p + 0xcc, 0, &tag);
    p[0x35] = 0; p[0x36] = 0; p[0x37] = 0;
    FUN_00429360((char*)p + 0xe0, 0, &tag);
    p[0x3a] = 0; p[0x3b] = 0; p[0x3c] = 0;
    p[0x3f] = 0; p[0x40] = 0; p[0x41] = 0;
    p[0x45] = 0; p[0x46] = 0; p[0x47] = 0;
    Memset32(p + 6, 0, 0x20);
    return p;
}

// @ 0x4b9f70
void __fastcall FUN_004b9f70(int* p)
{
    *p = (int)&g_vtblE;
    for (uint32_t i = p[0x45]; i < (uint32_t)p[0x46]; i += 0x38) {
    }
    FUN_00427440();
    for (uint32_t i = p[0x3f]; i < (uint32_t)p[0x40]; i += 4) {
    }
    FUN_00425990(p + 0x3f);
    for (uint32_t i = p[0x3a]; i < (uint32_t)p[0x3b]; i += 4) {
    }
    FUN_00425990(p + 0x3a);
    for (uint32_t i = p[0x35]; i < (uint32_t)p[0x36]; i += 4) {
    }
    FUN_00425990(p + 0x35);
    FUN_0041e5d0();
    for (uint32_t i = p[0x2b]; i < (uint32_t)p[0x2c]; i += 4) {
    }
    FUN_00425990(p + 0x2b);
    for (uint32_t i = p[0x26]; i < (uint32_t)p[0x27]; i += 0x8c) {
    }
    FUN_004250b0();
    *p = (int)&g_vtblC;
    *p = (int)&g_vtblD;
}

// @ 0x4ba120
class cEditorResource2 {
public:
    cResourceBase* AsInterface(int type);
};
cResourceBase* cEditorResource2::AsInterface(int type)
{
    if (type == 0x3c609f8) return (cResourceBase*)this;
    return ((cResourceBase*)this)->AsInterface(type);
}
