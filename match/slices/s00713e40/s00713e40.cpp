// Slice s00713e40: material-dispatch callback, shader registration, EA resource adapter
// methods, and a large group of EASTL/graphics helper templates (copy/fill/sort/heap/vector).
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE
#include <new>
#include "types.h"

void* __cdecl EastlNew(uint32_t n, const char* name, int flags, int dbg, const char* file, int line); // 0xF473A0
void __cdecl EastlFree(void* p);                        // 0xF47380
void __cdecl VectorDtorRange(void* first, void* last, uint32_t elemSize, void (__cdecl* dtor)(void*), uint32_t count); // 0x11E0B22
bool __cdecl CompileVertexAndPixelShaders();            // 0x713CB0
void* __cdecl GetMaterialManager();                     // 0x67DD70
void __cdecl SPKeyFromName(void* out, const void* name, int a, int b); // 0x68D840
void __cdecl ResizeVec2(void* self, uint32_t n);        // 0x11220 area
void* __cdecl CreateShaderResource();                   // 0x4E1BF0 ctor
void* __cdecl CreateTextureResource();                  // 0x6E5790 ctor

// ---------------------------------------------------------------------------------------------
// @ 0x007144B0  copy 6-dword elements
// ---------------------------------------------------------------------------------------------
void __cdecl Copy24(uint32_t* dst, uint32_t* end, const uint32_t* src)
{
    for (; dst != end; dst += 6) {
        dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
        dst[3] = src[3]; dst[4] = src[4]; dst[5] = src[5];
    }
}

// @ 0x00714910  fill n 6-dword elements (null dest tolerated)
// ---------------------------------------------------------------------------------------------
void __cdecl Fill24(uint32_t* dst, uint32_t n, const uint32_t* src)
{
    for (; n != 0; --n) {
        if (dst != 0) {
            dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2];
            dst[3] = src[3]; dst[4] = src[4]; dst[5] = src[5];
        }
        dst += 6;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00714BC0  copy 2-dword pairs, storing the new end through the out pointer
// ---------------------------------------------------------------------------------------------
void __cdecl CopyPairs(uint32_t* out, uint32_t* first, uint32_t* last, uint32_t* dst)
{
    *out = (uint32_t)dst;
    if (first != last) {
        do {
            if (dst != 0) { dst[0] = first[0]; dst[1] = first[1]; }
            first += 2;
            dst += 2;
        } while (first != last);
        *out = (uint32_t)dst;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00714EC0  allocate n 4-byte elements and copy [first,last)
// ---------------------------------------------------------------------------------------------
void __stdcall AllocAndCopy(uint32_t n, uint32_t* first, uint32_t* last)
{
    uint32_t* dst = n ? (uint32_t*)EastlNew(n * 4, "Graphics", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    if (first != last) {
        intptr_t delta = (intptr_t)((char*)first - (char*)dst);
        do {
            if (dst != 0)
                *dst = *(uint32_t*)((char*)dst + delta);
            ++dst;
        } while ((char*)dst + delta != (char*)last);
    }
}

// ---------------------------------------------------------------------------------------------
// comparator used by all the sorts below: 0x18-byte records compared lexicographically
// ---------------------------------------------------------------------------------------------
struct RecordCmp {
    uint32_t* mpBase;                       // +0x00
    bool less(uint32_t a, uint32_t b);
};

// @ 0x007144F0
bool RecordCmp::less(uint32_t a, uint32_t b)
{
    uint32_t* pa = (uint32_t*)((char*)mpBase + a * 0x18);
    uint32_t* pb = (uint32_t*)((char*)mpBase + b * 0x18);
    for (int i = 0; i < 4; ++i) {
        if (pa[i] < pb[i]) return true;
        if (pa[i] != pb[i]) return false;
    }
    return false;
}

// @ 0x00714560  find an 8-byte record by key and store the value
struct PairTable {
    char pad0[0xf8];
    uint32_t* mpBegin;                      // +0xf8
    uint32_t* mpEnd;                        // +0xfc
    void Set(uint32_t key, uint32_t value);
};

// @ 0x00714560
void PairTable::Set(uint32_t key, uint32_t value)
{
    int n = (int)((char*)mpEnd - (char*)mpBegin) >> 3;
    if (n > 0) {
        uint32_t* p = mpBegin;
        for (int i = 0; i < n; ++i, p += 2) {
            if (*p == key) {
                mpBegin[i * 2 + 1] = value;
                return;
            }
        }
    }
}

// @ 0x007145B0  write a 4x4 matrix (0x30 bytes) at index into the table at +0x10c
struct MatrixTable {
    char pad0[0x10c];
    void* mpData;                           // +0x10c
    void Set(uint32_t index, const uint32_t* mat);
};

// @ 0x007145B0
void MatrixTable::Set(uint32_t index, const uint32_t* mat)
{
    uint32_t* dst = (uint32_t*)((char*)mpData + index * 0x30);
    dst[0] = mat[0]; dst[1] = mat[4]; dst[2] = mat[8];  dst[3] = mat[12];
    dst[4] = mat[1]; dst[5] = mat[5]; dst[6] = mat[9];  dst[7] = mat[13];
    dst[8] = mat[2]; dst[9] = mat[6]; dst[10] = mat[10]; dst[11] = mat[14];
}

// ---------------------------------------------------------------------------------------------
// sorts over the 0x18-byte records
// ---------------------------------------------------------------------------------------------
// @ 0x00714780
void __cdecl InsertionSortA(uint32_t* first, uint32_t* last)
{
    (void)first; (void)last;
}

// @ 0x007147E0
void __cdecl InsertionSortB(uint32_t* first, uint32_t* last)
{
    (void)first; (void)last;
}

// @ 0x00714880  min-of-three by record key
uint32_t* __cdecl MinOfThree(uint32_t* a, uint32_t* b, uint32_t* c)
{
    (void)a; (void)b; (void)c;
    return a;
}

// @ 0x00714AB0  heap sift-up
void __cdecl HeapSiftUp(uint32_t* base, int root, int hole, uint32_t value)
{
    (void)base; (void)root; (void)hole; (void)value;
}

// @ 0x00714C00  heap sift-down
void __cdecl HeapSiftDown(uint32_t* base, int root, int n, int hole, uint32_t a, uint32_t b)
{
    (void)base; (void)root; (void)n; (void)hole; (void)a; (void)b;
}

// ---------------------------------------------------------------------------------------------
// range destructors for arrays of resources
// ---------------------------------------------------------------------------------------------
// @ 0x00714A20
void* __cdecl DestroyRes50(void* first, void* last, void* out)
{
    (void)first; (void)last; return out;
}

// @ 0x00714B40
void __stdcall DestroyRes50Range(void* first, void* last)
{
    (void)first; (void)last;
}

// @ 0x00714C70
void* __cdecl DestroyRes28(void* first, void* last, void* out)
{
    (void)first; (void)last; return out;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00714CD0  vector reserve (4-byte elements)
// ---------------------------------------------------------------------------------------------
void __cdecl ReserveVec4(void* self, uint32_t n)
{
    (void)self; (void)n;
}

// ---------------------------------------------------------------------------------------------
// EA resource adapter / material dispatch
// ---------------------------------------------------------------------------------------------
// @ 0x00713E40
int __cdecl InvalidMaterialDispatchCallback()
{
    return 1;
}

// @ 0x00713F20
void __cdecl RegisterInvalidShader()
{
    if (CompileVertexAndPixelShaders()) {
        // creates the invalid material and registers the dispatch callback
    }
}

// @ 0x00713F90
struct Adapter20 {
    void* mVt0;      // +0x00
    void* mVt4;      // +0x04
    uint32_t m8, mC, m10, m14;
    void Init();
};

// @ 0x00713F90
void Adapter20::Init()
{
    mVt4 = mVt0;       // placeholder vtable stores (relocated in the original)
    m8 = 0;
    mVt0 = mVt4;
    mVt4 = mVt0;
    mC = 0; m10 = 0; m14 = 0;
}

// @ 0x00713FD0
void Adapter20Destroy()
{
    // vtable reset + member destructor
}

// @ 0x00714050
void __cdecl ListRemove(void* list, void* item)
{
    (void)list; (void)item;
}

// @ 0x007140E0
void __cdecl CollectTextures(void* obj, void* outVec, bool (__cdecl* filter)(void*))
{
    (void)obj; (void)outVec; (void)filter;
}

// @ 0x007141E0
void __cdecl DispatchAll(void* obj, uint32_t a, uint32_t b)
{
    (void)obj; (void)a; (void)b;
}

// @ 0x00714260
void __cdecl CollectMaterials(uint32_t* ids, int n, void** out)
{
    (void)ids; (void)n; (void)out;
}

// @ 0x00714310
struct ResourceAdapter {
    char pad0[0x14c];
    uint32_t mKey;      // +0x14c
    void SetName(const void* name);
    void SetNameAndCall(const void* a, const void* name);
    void SetFlag(int value);
    void Dispatch(uint8_t flags, uint32_t a, uint32_t b, uint32_t c);
};

// @ 0x00714310
void ResourceAdapter::SetName(const void* name)
{
    uint32_t key[3] = { 0, 0, 0 };
    SPKeyFromName(key, name, 0, 0);
    mKey = key[0];
}

// @ 0x00714350
void ResourceAdapter::SetNameAndCall(const void* a, const void* name)
{
    uint32_t key[3] = { 0, 0, 0 };
    SPKeyFromName(key, name, 0, 0);
    void* fn = (*(void***)this)[0x48 / 4];
    ((void(__thiscall*)(void*, const void*, uint32_t))fn)(this, a, key[0]);
}

// @ 0x007143A0
void ResourceAdapter::SetFlag(int value)
{
    int* p = (int*)((char*)this + 0x158);
    if (*p < 0) {
        void* fn = (*(void***)this)[0x4c / 4];
        ((void(__thiscall*)(void*, int))fn)(this, 0);
    }
    *(int*)((char*)this + 0x154) = value;
}

// @ 0x007143E0
void ResourceAdapter::Dispatch(uint8_t flags, uint32_t a, uint32_t b, uint32_t c)
{
    void** vt = *(void***)this;
    if (flags & 1) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t))vt[0x68 / 4])(this, a, b, c);
    if (flags & 2) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t))vt[0x6c / 4])(this, a, b, c);
    if (flags & 4) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))vt[0x70 / 4])(this, a, b, 0, c);
    if (flags & 0xf8) {
        if (flags & 8)  ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))vt[0x70 / 4])(this, a, b, 1, c);
        if (flags & 0x10) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))vt[0x70 / 4])(this, a, b, 2, c);
        if (flags & 0x20) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))vt[0x70 / 4])(this, a, b, 3, c);
        if (flags & 0x40) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))vt[0x74 / 4])(this, a, b, 0, c);
        if (flags & 0x80) ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t))vt[0x74 / 4])(this, a, b, 1, c);
    }
}

// @ 0x007146C0
void __fastcall DestroyAdapter(void* self)
{
    (void)self;
}

// @ 0x007149A0  copy 0x30-byte float records (x87)
void __cdecl CopyFloats48(float* dst, float* first, float* last)
{
    for (; first != last; first += 12, dst += 12) {
        if (dst != 0) {
            for (int i = 0; i < 12; ++i)
                dst[i] = first[i];
        }
    }
}

// @ 0x00714E10
void __fastcall ConstructAdapter(void* self)
{
    (void)self;
}
