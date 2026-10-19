// Slice s00713e40: material-dispatch callback, shader registration, EA resource
// adapter methods, and the material/texture collection helpers.
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include <new>
#include <math.h>
#include <intrin.h>
#include "types.h"

void* __cdecl EastlNew(uint32_t n, const char* name, int flags, int dbg, const char* file, int line); // 0xF473A0
void __cdecl EastlFree(void* p);                        // 0xF47380
void __cdecl VectorDtorRange(void* first, uint32_t elemSize, uint32_t count, void (__cdecl* dtor)(void*)); // 0x11E0B22
int  __cdecl CompileVertexAndPixelShaders();            // 0x713CB0
void* __cdecl GetMaterialManager();                     // 0x67DD70
void __cdecl SPKeyFromName(void* out, const void* name, int a, int b); // 0x68D840
void* __cdecl CreateShaderResource();                   // 0x4E1BF0 ctor
void __cdecl D3DXMatrixMultiplyTranspose(float* out, const float* a, const float* b); // 0x11E1FE6
__int64 __cdecl GameTime();                             // 0x93A3A0
void __cdecl FUN_11f7850();                             // 0x11F7850
void __cdecl FUN_11f6920();                             // 0x11F6920
void __cdecl PushBack(void* item);                      // 0x7A6AC0
void __fastcall FUN_711170(void* self);                 // 0x711170
typedef bool (__cdecl* TextureFilter)(void*);
extern void*    g_spRenderDevice;                       // 0x16F89D0
extern uint32_t g_spVSShader;                           // 0x162A218
extern uint32_t g_spVSShaderCur;                        // 0x16F6564
extern uint32_t g_spPSShader;                           // 0x162A21C
extern uint32_t g_spPSShaderCur;                        // 0x16F89CC
extern const float* g_spClipMatrix;                     // 0x16F85AC
extern float    g_spFrameTime;                          // 0x162A3B4
extern float    g_spTimeScale;                          // 0x15362C8
extern float    g_spClipMatrixB[16];                    // 0x16F8BE0

// Additional external callees/globals used by the resource-adapter / material dispatch group.
int  __cdecl FUN_11fa000(int a);                        // 0x11FA000
void __cdecl FUN_11f4440(void* self, int a, int b, int c, int d, int e, int f, int g, int h); // 0x11F4440
void __fastcall FUN_11f44f0(void* self);                // 0x11F44F0
void __fastcall FUN_435480(void* self);                 // 0x435480
void __fastcall FUN_a23920(void* self);                 // 0xA23920
extern char g_spIndexObj;                               // 0x162A2E8
extern char g_spAdapterObj;                             // 0x162A3A0
extern void* g_spDispatchCallback;                      // 0x162A2FC

struct MaterialManager;
struct MaterialManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09();
    virtual void* at28(uint32_t id);                                     // +0x28
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void at3c(void* element, uint32_t a, uint32_t b);            // +0x3c
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
};

// @ 0x00713E40  invalid-material dispatch callback
int __cdecl InvalidMaterialDispatchCallback()
{
    float mat[4][4];
    float* pmat;
    const float* clipA;
    uint32_t vs = g_spVSShader;
    if (g_spVSShaderCur != g_spVSShader) {
        void** vt = *(void***)g_spRenderDevice;
        ((void(__thiscall*)(void*, uint32_t))vt[0x170 / 4])(g_spRenderDevice, g_spVSShader);
        g_spVSShaderCur = vs;
    }
    pmat = mat[0];
    clipA = g_spClipMatrix;

    // 0.5 is a float constant here, unlike the 1.0 which is a double.
    extern const float g_halfConst;                     // 0x1471064
    D3DXMatrixMultiplyTranspose(pmat, clipA, g_spClipMatrixB);
    __int64 t = GameTime();
    float x = (float)t * g_spFrameTime;
    float zero = 0.0f;
    float y = x * g_spTimeScale;
    float sn = (float)sin((double)y + (double)y);
    float s = (float)(((double)sn + 1.0) * g_halfConst);
    void* dev = g_spRenderDevice;
    void** vt = *(void***)dev;
    struct { float m0, m1, m2, m3; } consts;
    consts.m0 = x;
    consts.m2 = zero;
    consts.m3 = zero;
    consts.m1 = s;
    ((void(__thiscall*)(void*, uint32_t, void*, uint32_t))vt[0x178 / 4])(dev, 0, &consts, 5);
    uint32_t ps = g_spPSShader;
    if (g_spPSShaderCur != g_spPSShader) {
        void** vt2 = *(void***)g_spRenderDevice;
        ((void(__thiscall*)(void*, uint32_t))vt2[0x1AC / 4])(g_spRenderDevice, g_spPSShader);
        g_spPSShaderCur = ps;
    }
    FUN_11f7850();
    FUN_11f6920();
    return 1;
}

// @ 0x00713F20  register the invalid/fallback shader
void __cdecl RegisterInvalidShader()
{
    if (FUN_11fa000(0x7ffffffe))
        return;
    if (!CompileVertexAndPixelShaders())
        return;
    FUN_11f4440(&g_spIndexObj, 0x7ffffffe, 0, 0, 0,
                (int)0xfffe0101, (int)0xfffe0200, (int)0xffff0100, (int)0xffff0200);
    FUN_11f44f0(&g_spIndexObj);
    g_spDispatchCallback = (void*)&InvalidMaterialDispatchCallback;
    FUN_435480(&g_spAdapterObj);
}

struct Adapter20 {
    void* mVt0;      // +0x00
    void* mVt4;      // +0x04
    uint32_t m8, mC, m10, m14;
    void* Init();
};

// @ 0x00713F90  resource-adapter init (vtable/field stores)
void* Adapter20::Init()
{
    // The original keeps BOTH stores at +0x04 (a base vtable, then the final one); a plain
    // pair of stores lets MSVC drop the first as dead. The volatile qualifier pins it.
    void* self = this;
    void* v = 0;
    *(void* volatile*)((char*)self + 4) = (void*)0x13ef094;
    *(void**)((char*)self + 8) = v;
    *(void**)self = (void*)0x140cca4;
    *(void**)((char*)self + 4) = (void*)0x140cca0;
    *(void**)((char*)self + 0xc) = v;
    *(void**)((char*)self + 0x10) = v;
    *(void**)((char*)self + 0x14) = v;
    return self;
}

// member sub-object destroyed by the destructor (call at 0xA23920)
struct AdapterSub {
    void* mVt; void* m4; void* m8; void* mC; void* m10; void* m14;
    __declspec(noinline) ~AdapterSub();
};
__declspec(noinline) AdapterSub::~AdapterSub() { FUN_a23920(this); }
struct AdapterBase {
    void* mVt0; void* mVt4;
    uint32_t m8;
    AdapterSub mSub;    // +0x0c
    void Destroy();
};

// @ 0x00713FD0  resource-adapter destructor (vtable reset + member dtor)
void AdapterBase::Destroy()
{
    mVt0 = (void*)0x140cca4;
    mVt4 = (void*)0x140cca0;
    mSub.~AdapterSub();
    mVt4 = (void*)0x13ef094;
    mVt0 = (void*)0x13eb938;
}

// intrusive refcounted handle: ctor AddRefs (vtable slot 0), dtor Releases (vtable slot 1)
struct SmartPtr {
    void* mp;
    SmartPtr(void* q) : mp(q) {
        if (mp)
            ((void(__thiscall*)(void*))(*(void***)mp)[0])(mp);
    }
    ~SmartPtr() {
        if (mp)
            ((void(__thiscall*)(void*))(*(void***)mp)[1])(mp);
    }
};

struct AdapterVec {
    void* mpBegin;                      // +0x00
    void* mpEnd;                        // +0x04
    void* mpCap;                        // +0x08
    void push_back(const void* item);   // 0x7A6AC0
};

struct AdapterList {
    void* mVt0; void* mVt1;             // +0x00
    uint32_t m8;                        // +0x08
    AdapterVec mVec;                    // +0x0c
    void Remove(void* item);
};

// @ 0x00714050  list remove-by-value
void AdapterList::Remove(void* item)
{
    int n = (int)((char*)mVec.mpEnd - (char*)mVec.mpBegin) >> 2;
    int i = 0;
    if (n > 0) {
        char* p = (char*)mVec.mpBegin;
        do {
            if (*(void**)p == item)
                return;
            ++i;
            p += 4;
        } while (i < n);
    }
    SmartPtr local(item);
    mVec.push_back(&local);
}

// @ 0x007140E0  collect textures matching a filter into an output vector
__declspec(noinline) void __cdecl CollectTextures(void* obj, void* outVec, TextureFilter filter)
{
    int n = (*(int*)((char*)obj + 0xc) - *(int*)((char*)obj + 8)) >> 2;
    int i = 0;
    if (n > 0) {
        do {
            int element = *(int*)(*(int*)((char*)obj + 8) + i * 4);
            if (*(short*)(element + 4) == 0x20d) {
                int j = 0;
                if (0 < *(int*)(element + 0xc)) {
                    int* p = (int*)(element + 0x14);
                    do {
                        int v = *p;
                        if (v != 0 && (filter == 0 || filter((void*)v))) {
                            FUN_711170(outVec);
                            int* slot = (int*)((char*)outVec + 4);
                            int* cur  = (int*)(*slot - 4);
                            int old   = *cur;
                            if (v != old) {
                                _InterlockedExchangeAdd((volatile long*)(v + 8), 1);
                                *cur = v;
                                if (old != 0) {
                                    int* rc = (int*)(old + 8);
                                    if (_InterlockedExchangeAdd((volatile long*)rc, -1) < 1)
                                        _InterlockedExchangeAdd((volatile long*)rc, 1);
                                    else
                                        _InterlockedExchangeAdd((volatile long*)rc, 0);
                                }
                            }
                        }
                        ++p;
                        ++j;
                    } while (j < *(int*)(element + 0xc));
                }
            }
            ++i;
        } while (i < n);
    }
}

struct DispatchTarget {
    char pad[0xb8];
    void** mB8;     // +0xb8
    void** mBC;     // +0xbc
    char pad2[0xf4 - 0xc0];
    void** mF4;     // +0xf4
    void** mF8;     // +0xf8
};

// @ 0x007141E0  dispatch over the two resource pointer arrays
void __cdecl DispatchAll(DispatchTarget* obj, void* a, void* filter)
{
    for (void** it = obj->mB8; it != obj->mBC; ++it) {
        void* element = *it;
        if (element)
            ((MaterialManager*)GetMaterialManager())->at3c(element, (uint32_t)a, (uint32_t)filter);
    }
    for (void** it2 = obj->mF4; it2 != obj->mF8; ++it2) {
        void* element = *it2;
        if (element)
            CollectTextures(element, a, (TextureFilter)filter);
    }
}

// @ 0x00714260  collect materials: allocate an adapter and add it to the list
void __cdecl CollectMaterials(uint32_t* ids, int n, void** out)
{
    int i = 0;
    if (n > 0) {
        do {
            uint32_t id = ids[i];
            void* item = *(void**)((char*)((MaterialManager*)GetMaterialManager())->at28(id) + 0x1c);
            if (item != 0 && *out == 0) {
                void* obj = EastlNew(0x20, (const char*)0x13eb8a4, 0, 0, 0, 0);
                if (obj) {
                    // two stores to +4: the base vtable then the final one; keep the first alive.
                    *(void* volatile*)((char*)obj + 4) = (void*)0x13ef094;
                    *(uint32_t*)((char*)obj + 8) = 0;
                    *(void**)obj = (void*)0x140cca4;
                    *(void**)((char*)obj + 4) = (void*)0x140cca0;
                    *(uint32_t*)((char*)obj + 0xc) = 0;
                    *(uint32_t*)((char*)obj + 0x10) = 0;
                    *(uint32_t*)((char*)obj + 0x14) = 0;
                } else {
                    obj = 0;
                }
                *out = obj;
                (*(void(__thiscall**)(void*))obj)(obj);
                ((AdapterList*)*out)->Remove(item);
            }
            ++i;
        } while (i < n);
    }
}

extern void* g_vecdtor4E1BF0;   // 0x4E1BF0 element destructor

// EASTL guarded deallocate: skips a null pointer or an empty allocation header.
static void EastlFreeGuarded(void* p)
{
    if (p && *(int*)((char*)p - 4) != 0)
        EastlFree(p);
}

struct AdapterTeardown {
    char pad0[8];
    void* m8;          // +0x08
    char pad0C[0x10];
    void* m1c;         // +0x1c
    char pad20[0x10];
    char m30[0x50];    // +0x30  vector: begin/end/cap + 4 * 0x14 elements
    char m80[0x28];    // +0x80  vector: begin/end/cap + 2 * 0x14 elements
    void* ma8;         // +0xa8
    char padAC[0x10];
    void* mbc;         // +0xbc
    void Destroy();
};

// @ 0x007146C0  resource-adapter teardown (frees + two vector destructors)
void AdapterTeardown::Destroy()
{
    EastlFreeGuarded(mbc);
    EastlFreeGuarded(ma8);
    VectorDtorRange(m80, 0x14, 2, (void (__cdecl*)(void*))&g_vecdtor4E1BF0);
    VectorDtorRange(m30, 0x14, 4, (void (__cdecl*)(void*))&g_vecdtor4E1BF0);
    EastlFreeGuarded(m1c);
    EastlFreeGuarded(m8);
}

// comparator used by the sort below (callee 0x7144F0): 0x18-byte records, 4 key dwords
struct RecordCmp {
    const char* mpBase;                     // +0x00
    bool less(uint32_t a, uint32_t b) const;
};

// @ 0x007144F0
__declspec(noinline) bool RecordCmp::less(uint32_t a, uint32_t b) const
{
    const uint32_t* pa = (const uint32_t*)(mpBase + a * 0x18);
    const uint32_t* pb = (const uint32_t*)(mpBase + b * 0x18);
    for (int i = 0; i < 4; ++i) {
        if (pa[i] < pb[i]) return true;
        if (pa[i] != pb[i]) return false;
    }
    return false;
}

// @ 0x00714780  insertion sort over 0x18-byte records
void __cdecl InsertionSortA(uint32_t* first, uint32_t* last, RecordCmp compare)
{
    if (first == last)
        return;
    uint32_t* cur = first + 1;
    if (cur == last)
        return;
    do {
        const uint32_t value = *cur;
        uint32_t* pos = cur;
        while (pos != first && compare.less(value, *(pos - 1))) {
            *pos = *(pos - 1);
            --pos;
        }
        *pos = value;
        ++cur;
    } while (cur != last);
}

// ===== functions restored from HEAD (dropped by the agent rewrite) =====

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
    uint32_t* Set(uint32_t index, const uint32_t* mat);
};

// @ 0x007145B0
uint32_t* MatrixTable::Set(uint32_t index, const uint32_t* mat)
{
    uint32_t* dst = (uint32_t*)((char*)mpData + index * 0x30);
    dst[0] = mat[0]; dst[1] = mat[4]; dst[2] = mat[8];  dst[3] = mat[12];
    dst[4] = mat[1]; dst[5] = mat[5]; dst[6] = mat[9];  dst[7] = mat[13];
    dst[8] = mat[2]; dst[9] = mat[6]; dst[10] = mat[10]; dst[11] = mat[14];
    return dst + 8;
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

