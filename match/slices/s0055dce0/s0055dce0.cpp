// Slice s0055dce0: Skinner::PaintSystem save/load of paint resource-id tables plus
// EASTL rbtree/vector helpers emitted in this module.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }
extern "C" void EASTL_allocator_deallocate(void* p);

struct V32 { uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity; };

namespace eastl { struct allocator { allocator() {} }; }

// Helpers used by this module (call targets are relocated).
void FUN_004769b0(void* p, unsigned n);
void FUN_0050f0d0(void* p, void* q);
void FUN_00425990();
void FUN_004e1780(void* p);
void* FUN_00569980(void* key);
void* FUN_00569b80(void* key);
void* FUN_00569b10(void* key);
void FUN_005699f0(void* src, void* dst);
void FUN_005699f0_2();
void FUN_0056a1a0();
void FUN_00565920(void* p);
void FUN_00564470(void* p);
void FUN_00553fb0(void* p);
void FUN_00548400(void* p);
void FUN_00511f70(void* first, void* last, void* dst);
void* FUN_0042dee0(void* a, int size, int align, int flags);
void FUN_0067dea0();
void* FUN_00572590();
void FUN_00540470(void* p);
void FUN_00554020(void* out, void* val);
void FUN_0055dce0(void* p);
void FUN_0055de60(int* p);
void FUN_005699f0_copy();
void RBTreeInsert(void* node, void* where, void* anchor, char flag);
bool EA_IO_WriteUint32(void* stream, void* val, int n, int f);   // 0x93aa70
bool EA_IO_ReadInt32(void* stream, void* val, int n, int f);     // 0x93a780
void* GetManager();                                              // 0x67dcd0
void* GetSaveArea(uint32_t id);                                  // 0x6b1f90
void* FUN_00567190(void* a, void* b, void* c);
void FUN_00568740(int* dst, int* first, int* last, uint32_t flag);
namespace SP { uint32_t EditorEntityToResourceType(uint32_t modelType, int a); }
static uint32_t SP_EditorEntityToResourceType(uint32_t a, int b) { return SP::EditorEntityToResourceType(a, b); }

// PaintSystem's save-area interface: Open is at +0x34, Close at +0x3c, GetStream at +0x18,
// Release at +0x08.
typedef bool (__thiscall *OpenFn)(void* self, void* key, void** out, int a, int b, int c, int d);
typedef void (__thiscall *CloseFn)(void* self, void* out);
typedef void* (__thiscall *GetStreamFn)(void* self);
typedef int  (__thiscall *ReleaseFn)(void* self);
typedef bool (__thiscall *GetRes58Fn)(void* self, void* key);

// @ 0x0055dce0
void FUN_0055dce0(void* pList) {
    uint32_t* v = (uint32_t*)pList;
    FUN_004769b0((void*)*v, v[1]);
    uint32_t key[3];
    key[0] = 0x727e3e7; key[1] = 0x727e3e7; key[2] = 0x11ac19c;
    void* mgr = GetManager();
    void* obj = (void*)((GetRes58Fn)(*(void***)mgr)[0x58 / 4])(mgr, key);
    if (obj) {
        void* stream = 0;
        if (((OpenFn)(*(void***)obj)[0x34 / 4])(obj, key, &stream, 1, 3, 1, 0)) {
            void* io = ((GetStreamFn)(*(void***)stream)[0x18 / 4])(stream);
            int a = 0;
            if (EA_IO_ReadInt32(io, &a, 1, 0) && a == 0) {
                uint32_t n = 0;
                if (EA_IO_ReadInt32(io, &n, 1, 0)) {
                    bool ok = true;
                    for (uint32_t i = 0; ok && i < n; ++i) {
                        uint32_t val = 0;
                        ok = EA_IO_ReadInt32(io, &val, 1, 0);
                        if (ok) {
                            uint32_t tmp[3];
                            FUN_00554020(tmp, &val);
                        }
                    }
                }
            }
            ((CloseFn)(*(void***)obj)[0x3c / 4])(obj, stream);
        }
        if (stream)
            ((ReleaseFn)(*(void***)stream)[8 / 4])(stream);
    }
}

// @ 0x0055de60
void FUN_0055de60(int* pList) {
    void* area = GetSaveArea(0x11ac19c);
    uint32_t key[3];
    key[0] = 0x727e3e7; key[1] = 0x727e3e7; key[2] = 0x11ac19c;
    void* stream = 0;
    if (((OpenFn)(*(void***)area)[0x34 / 4])(area, key, &stream, 2, 2, 1, 0)) {
        void* io = ((GetStreamFn)(*(void***)stream)[0x18 / 4])(stream);
        uint32_t zero = 0;
        if (EA_IO_WriteUint32(io, &zero, 1, 0)) {
            uint32_t count = (uint32_t)(pList[1] - *pList) >> 2;
            uint32_t out = count;
            if (EA_IO_WriteUint32(io, &out, 1, 0)) {
                bool ok = true;
                uint32_t* end = (uint32_t*)pList[1];
                for (uint32_t* it = (uint32_t*)*pList; ok && it != end; ++it) {
                    uint32_t v = *it;
                    ok = EA_IO_WriteUint32(io, &v, 1, 0);
                }
            }
        }
        uint32_t trailer = 4;
        EA_IO_WriteUint32(io, &trailer, 1, 0);
        ((CloseFn)(*(void***)area)[0x3c / 4])(area, stream);
    }
    if (stream)
        ((ReleaseFn)(*(void***)stream)[8 / 4])(stream);
}

// @ 0x0055dfe0
unsigned char FUN_0055dfe0(void* this_) {
    FUN_0067dea0();
    int* list = (int*)FUN_00572590();
    int count = (int)(list[1] - *list) >> 2;
    uint32_t tmpA[3];
    FUN_00540470(&tmpA);
    uint32_t* end = (uint32_t*)list[1];
    for (uint32_t* it = (uint32_t*)*list; it != end; ++it) {
        uint32_t v = *(uint32_t*)*it;
        FUN_00554020(&count, &v);
    }
    uint32_t tmpB[3];
    FUN_00540470(&tmpB);
    int a[3];
    FUN_0055dce0(a);
    bool equal = ((a[1] - a[0]) >> 2) == ((int)(tmpA[2] - tmpA[0]) >> 2);
    if (equal) {
        uint32_t* p = (uint32_t*)a[0];
        uint32_t* q = (uint32_t*)tmpA[0];
        for (; p != (uint32_t*)a[1]; ++p, ++q) {
            if (*p != *q) {
                equal = false;
                break;
            }
        }
    }
    if (equal) {
        FUN_00553fb0(&tmpB);
        FUN_00553fb0(&tmpA);
        return 0;
    }
    FUN_0055de60((int*)&tmpA);
    unsigned char r = 1;
    for (int* p = (int*)a[0]; p < (int*)a[1]; ++p) {
    }
    FUN_00548400(&a);
    for (uint32_t* p = (uint32_t*)tmpA[0]; p < (uint32_t*)tmpA[1]; ++p) {
    }
    FUN_00548400(&tmpA);
    return r;
}

// @ 0x0055e190  (large; serialisation driver)
unsigned char FUN_0055e190(void* this_, char flag) {
    // Full driver reserved; skeleton keeps the external call shape.
    (void)this_; (void)flag;
    return 0;
}

// @ 0x0055eae0
void* FUN_0055eae0(void* this_, int* first, int count) {
    *(void**)this_ = (void*)0x13eb394;
    *(void**)this_ = (void*)0x13f4af0;
    ((int*)this_)[1] = 0;
    ((int*)this_)[2] = 0;
    ((int*)this_)[3] = 0;
    uint32_t flag;
    FUN_00568740((int*)this_ + 1, first, first + count, flag);
    FUN_0050f0d0((void*)((int*)this_)[1], (void*)((int*)this_)[2]);
    return this_;
}

// @ 0x0055eb70
char FUN_0055eb70(void* this_, int* p) {
    int key = p[1];
    if (key == 0x1a99b06b)
        key = (int)SP_EditorEntityToResourceType((uint32_t)p[2] >> 16 & 0xff, 1);
    void* end = (void*)((int*)this_)[2];
    void* it = (void*)FUN_00567190((void*)((int*)this_)[1], end, &key);
    bool r = (it != end) && (key < *(int*)it);
    return (char)r;
}

// @ 0x0055ec10
void* FUN_0055ec10(void* this_, unsigned flags) {
    uint32_t* v = (uint32_t*)((char*)this_ + 4);
    for (uint32_t* p = (uint32_t*)v[0]; p < (uint32_t*)v[1]; ++p) {
    }
    FUN_00425990();
    *(void**)this_ = (void*)0x13eb394;
    if (flags & 1)
        EASTL_allocator_deallocate(this_);
    return this_;
}
