// Slice s007819d0: EASTL vector<12-byte> and vector<36-byte> machinery for an
// editor/simulator object (0x7819d0..0x78285b), plus two small member helpers.
// /O2 /MD /Gy /EHsc /TP module.  Element sizes: 0xc and 0x24.
#include "types.h"

struct cPropertyList;

struct IRefObj {
    virtual void slot0();
    virtual void Release();
};

// 12-byte element (a refcounted pointer + two ints)
struct E12 {
    void* p;
    int   a;
    int   b;
};

// vector of E12
struct Vec12 {
    E12* begin;                     // +0x0
    E12* end;                       // +0x4
    E12* cap;                       // +0x8

    __declspec(noinline) Vec12* ConstructRange(const Vec12& src);    // 0x00781a60
    __declspec(noinline) void   Destroy();                           // 0x00781b10
    __declspec(noinline) Vec12* Assign(const Vec12& src);            // 0x00782270
};

struct ElemVecPair {
    int a, b, c;
};

// 36-byte element: refcounted ptr + Vec12 + int + bool + int
struct E36 {
    void* p0;                       // +0x00
    Vec12 v;                        // +0x04 (ends +0x10)
    char  pad_10[8];                // +0x10
    int   a;                        // +0x18
    bool  b;                        // +0x1c
    int   c;                        // +0x20
};

// externals
void* EastlAllocate(unsigned int size, const char* name, int a, int b, const char* file, int line);
void  EastlDeallocate(void* p, int a);
void  FUN_0077fa70(void* out, void* first, void* last, void* dst, void* extra);
void  FUN_00760ba0(void* first, void* last, void* dst);
int*  FUN_007809f0(unsigned int n, void* first, void* last);
void  FUN_007809c0(void* first, void* last);
void  FUN_00760ca0(void* pos, void* value);
void  FUN_00743b50(void* p);
void  FUN_00576620(void* p);
unsigned int FUN_00777ae0(int a, int b, int c);
void  FUN_0077f6a0(void* self);
void  FUN_0077f980(void* self);
void  FUN_00780810(void* self);
void  FUN_007806a0(void* self);
void  FUN_00780ab0(void* self);
void* FUN_0067dd50();
void* FUN_006ffdc0(void* out, void* in);
void  FUN_007c4d00(void* p);
void  FUN_007c4ba0(float x);
void  FUN_007c4bc0(float x);
void  FUN_007c53d0(float x);
void  FUN_007c5440(float a, float b);
void  FUN_007c40c0(float* a, float* b);
void  FUN_007c4b00(float a, float b);
void  FUN_007c4180(float* out, float* in);
void  FUN_007c4ad0(float a, float b);
float FUN_0077eef0(int a, int b, float t);
float FUN_005a6e00(float x);
void  FUN_006bac90(void* a, float* b);
struct Sub14 { void FreeRange(void* a, void* b); };
struct ShadowBase { void Notify(); };

extern int   g_16fa3a8;
extern int   g_16f966c, g_16f9670, g_16f9678, g_16f967c, g_16f9680;
extern int   g_16f954c, g_16f9550, g_16f9558, g_16f955c;
extern float g_140e8f8;
extern char  g_153a2ec;
extern float g_153a2f0;
extern float g_153a108;

// ---------------------------------------------------------------------------
// 0x00781A60 : Vec12 range/copy construction
// ---------------------------------------------------------------------------
Vec12* Vec12::ConstructRange(const Vec12& src)
{
    int count = (int)(src.end - src.begin) / 0xc;
    E12* buf;
    if (count == 0) {
        buf = 0;
    } else {
        buf = (E12*)EastlAllocate(count * 0xc, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }
    begin = buf;
    end = buf;
    cap = (E12*)((char*)buf + count * 0xc);
    void* tmp = 0;
    FUN_0077fa70(&tmp, src.begin, src.end, buf, (void*)end);
    end = (E12*)tmp;
    return this;
}

// ---------------------------------------------------------------------------
// 0x00781B10 : Vec12 destroy
// ---------------------------------------------------------------------------
void Vec12::Destroy()
{
    E12* p = begin;
    E12* e = end;
    for (; p < e; p = (E12*)((char*)p + 0xc)) {
        if (p->p)
            ((IRefObj*)p->p)->Release();
    }
    if (begin && *(int*)((char*)begin - 4) != 0)
        EastlDeallocate(begin, 0);
}

// ---------------------------------------------------------------------------
// 0x00782270 : Vec12 assignment
// ---------------------------------------------------------------------------
Vec12* Vec12::Assign(const Vec12& src)
{
    if (&src == this)
        return this;
    unsigned newCount = (unsigned)(src.end - src.begin) / 0xc;
    E12* oldBegin = begin;
    if ((unsigned)(cap - begin) / 0xc < newCount) {
        E12* fresh = (E12*)FUN_007809f0(newCount, src.begin, src.end);
        FUN_007809c0(begin, end);
        if (begin && *(int*)((char*)begin - 4) != 0)
            EastlDeallocate(begin, 0);
        cap = (E12*)((char*)fresh + newCount * 0xc);
        begin = fresh;
        end = (E12*)((char*)fresh + newCount * 0xc);
        return this;
    }
    unsigned oldCount = (unsigned)(end - oldBegin) / 0xc;
    if (oldCount < newCount) {
        FUN_00760ba0(src.begin, (E12*)((char*)src.begin + oldCount * 0xc), oldBegin);
        void* srcEnd = src.end;
        void* tmp = 0;
        FUN_0077fa70(&tmp, (E12*)((char*)src.begin + ((char*)end - (char*)begin)), srcEnd, end, srcEnd);
        end = (E12*)((char*)begin + newCount * 0xc);
        return this;
    }
    FUN_00760ba0(src.begin, src.end, oldBegin);
    FUN_007809c0((void*)0, end);
    end = (E12*)((char*)begin + newCount * 0xc);
    return this;
}

// ---------------------------------------------------------------------------
// 0x00781B80 : copy E36 range into uninitialised storage
// ---------------------------------------------------------------------------
E36* Func_00781B80(E36* first, E36* last, E36* dst)
{
    while (first != last) {
        if (dst) {
            dst->p0 = first->p0;
            dst->v.ConstructRange(first->v);
            dst->a = first->a;
            dst->b = first->b;
            dst->c = first->c;
        }
        first = (E36*)((char*)first + 0x24);
        dst = (E36*)((char*)dst + 0x24);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// 0x00781C30 : E36 constructor from a value
// ---------------------------------------------------------------------------
E36* E36_Construct(E36* self, void* p0, const E36* src)
{
    self->p0 = p0;
    self->v.ConstructRange(src->v);
    self->a = src->a;
    self->b = src->b;
    self->c = src->c;
    self->v.Destroy();
    return self;
}

// ---------------------------------------------------------------------------
// 0x00781CB0 : destroy E36 range
// ---------------------------------------------------------------------------
E36* Func_00781CB0(E36* first, E36* last, E36* dst)
{
    while (first != last) {
        first->v.Destroy();
        first = (E36*)((char*)first + 0x24);
        dst = (E36*)((char*)dst + 0x24);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// 0x00781CF0 : E36 vector destroy
// ---------------------------------------------------------------------------
void Func_00781CF0(char* v)
{
    char* begin = *(char**)v;
    char* end = *(char**)(v + 4);
    for (; begin < end; begin += 0x24)
        ((Vec12*)(begin + 4))->Destroy();
    begin = *(char**)v;
    if (begin && *(int*)(begin - 4) != 0)
        EastlDeallocate(begin, 0);
}

// ---------------------------------------------------------------------------
// 0x00781D60 : big object constructor
// ---------------------------------------------------------------------------
int* __fastcall Func_00781D60(int* param_1)
{
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[0] = 0;
    param_1[2] = 0;
    *((char*)param_1 + 0xc) = 0;
    *((char*)param_1 + 0xd) = 0;
    *((char*)param_1 + 0xe) = 0;
    param_1[4] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[0xc] = 0;
    param_1[0xd] = 0;
    param_1[0xe] = 0;
    // bulk member init / raster-release loops omitted (see partial.txt)
    return param_1;
}

// ---------------------------------------------------------------------------
// 0x007821B0 : object destructor
// ---------------------------------------------------------------------------
void __fastcall Func_007821B0(int* param_1)
{
    if (param_1[0x6f])
        ((IRefObj*)param_1[0x6f])->Release();
    for (int i = 0; i < 8; ++i)
        FUN_00576620((char*)param_1 + 0x10c + i * 4);
    for (int i = 0; i < 2; ++i)
        FUN_00576620((char*)param_1 + 0xf4 + i * 4);
    Func_00781CF0((char*)param_1 + 0x30);
    ((Vec12*)((char*)param_1 + 0x1c))->Destroy();
    if (param_1[6])
        ((IRefObj*)param_1[6])->Release();
    param_1[0] = 0;
    param_1[2] = 0;
}

// ---------------------------------------------------------------------------
// 0x00782420 : copy-assign E36 range into initialised storage
// ---------------------------------------------------------------------------
E36* Func_00782420(E36* first, E36* last, E36* dst)
{
    while (first != last) {
        dst->p0 = first->p0;
        dst->v.Assign(first->v);
        dst->a = first->a;
        dst->b = first->b;
        dst->c = first->c;
        first = (E36*)((char*)first + 0x24);
        dst = (E36*)((char*)dst + 0x24);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// 0x00782470 : move-assign E36 range backwards
// ---------------------------------------------------------------------------
E36* Func_00782470(E36* first, E36* last, E36* dst)
{
    while (last != first) {
        last = (E36*)((char*)last - 0x24);
        dst = (E36*)((char*)dst - 0x24);
        dst->p0 = last->p0;
        dst->v.Assign(last->v);
        dst->a = last->a;
        dst->b = last->b;
        dst->c = last->c;
    }
    return dst;
}

// ---------------------------------------------------------------------------
// 0x007824E0 : pop_back
// ---------------------------------------------------------------------------
void __fastcall Func_007824E0(int* param_1)
{
    char* end = (char*)param_1[0xb];
    (*(void(__thiscall**)(int*, void*))(*param_1 + 0x10))(param_1, *(void**)(end - 0x24));
    ((Vec12*)(end - 0x20))->Assign(*(Vec12*)(end - 0x20));
    param_1[0x87] = *(int*)(end - 0xc);
    (*(void(__thiscall**)(int*, void*))(*param_1 + 0x14))(param_1, *(void**)(end - 4));
    (*(void(__thiscall**)(int*, int))(*param_1 + 0x28))(param_1, *(unsigned char*)(end - 8));
    ((ShadowBase*)((char*)param_1 - 8))->Notify();
    param_1[0xb] = param_1[0xb] - 0x24;
    ((Vec12*)(param_1 + 4))->Destroy();
}

// ---------------------------------------------------------------------------
// 0x00782540 : push_back(E36)
// ---------------------------------------------------------------------------
void Func_00782540(char* self, const E36* value)
{
    char* end = *(char**)(self + 4);
    if (end < *(char**)(self + 8)) {
        *(char**)(self + 4) = end + 0xc;
        if (end) {
            *(void**)end = value->p0;
            if (*(void**)end)
                (*(IRefObj**)end)->slot0();
            *(int*)(end + 4) = value->v.begin ? 0 : 0;
            *(int*)(end + 4) = 0;
            *(int*)(end + 8) = 0;
        }
    } else {
        FUN_00760ca0(end, (void*)value);
    }
}

// ---------------------------------------------------------------------------
// 0x007825D0 : emplace at end with combined flag
// ---------------------------------------------------------------------------
void Func_007825D0(int* param_1, unsigned param_2)
{
    int* p = (int*)(*(void*(__thiscall**)(int*))(*param_1 + 0x13c))(param_1);
    if (p)
        ((IRefObj*)p)->slot0();
    unsigned f = param_2 | 0x11d00;
    E36 tmp;
    tmp.p0 = p;
    tmp.a = f;
    tmp.c = f;
    Func_00782540((char*)param_1 + 0x14, &tmp);
    if (tmp.p0)
        ((IRefObj*)tmp.p0)->Release();
}

// ---------------------------------------------------------------------------
// 0x00782660 : emplace a freshly allocated 16-byte object
// ---------------------------------------------------------------------------
void Func_00782660(int* param_1, unsigned param_2)
{
    int* p = (int*)EastlAllocate(0x10, "Graphics", 0, 0, 0, 0);
    if (p) {
        int v = (*(int(__thiscall**)(int*))(*param_1 + 0xa0))(param_1);
        p[1] = 0;
        p[2] = 0;
        p[0] = 0;
        p[3] = v;
        Func_00782540((char*)param_1 + 0x14, (E36*)p);
        if (p)
            ((IRefObj*)p)->Release();
    }
}

// ---------------------------------------------------------------------------
// 0x00782740 : emplace from an existing refcounted object
// ---------------------------------------------------------------------------
void Func_00782740(int* param_1, void* p)
{
    if (p)
        ((IRefObj*)p)->slot0();
    E36 tmp;
    tmp.p0 = p;
    tmp.a = (int)p;
    tmp.c = (int)p;
    Func_00782540((char*)param_1 + 0x14, &tmp);
    if (tmp.p0)
        ((IRefObj*)tmp.p0)->Release();
}

// ---------------------------------------------------------------------------
// 0x007827C0 : clear + notify
// ---------------------------------------------------------------------------
void __fastcall Func_007827C0(int param_1)
{
    int* p = *(int**)(param_1 + 0x10);
    if (p) {
        *(int*)(param_1 + 0x10) = 0;
        ((IRefObj*)p)->Release();
    }
    ((Sub14*)(param_1 + 0x14))->FreeRange(*(void**)(param_1 + 0x14), *(void**)(param_1 + 0x18));
    ((ShadowBase*)(param_1 - 8))->Notify();
}

// ---------------------------------------------------------------------------
// 0x00782800 : insert range
// ---------------------------------------------------------------------------
char* Func_00782800(char* self, char* first, char* last)
{
    char* dst = (char*)Func_00782420((E36*)last, *(E36**)(self + 4), (E36*)first);
    char* end = *(char**)(self + 4);
    for (; dst < end; dst += 0x24)
        ((Vec12*)(dst + 4))->Destroy();
    int n = (int)((last - first) * -0x38e38e39LL >> 32);
    *(int*)(self + 4) += ((n >> 3) - (n >> 0x1f)) * 0x24;
    return first;
}

// ---------------------------------------------------------------------------
// 0x007819D0 : conditional apply/notify (member of cShadowWorld subobject at +8)
// ---------------------------------------------------------------------------
struct ShadowSub {
    char pad0[4];                   // +0x00
    char mUnk4;                     // +0x04
    char mUnk5;                     // +0x05
    char mUnk6;                     // +0x06
    char pad7[1];
    int  mUnk8;                     // +0x08
    char pad_c[4];
    int  mUnk10;                    // +0x10
    char pad_14[0x1bc - 0x14];
    bool mUnk1bc;                   // +0x1bc
};

void Func_007819D0(ShadowSub* self, int other)
{
    if (self->mUnk8 != 0)
        return;
    if (self->mUnk10 != 0 && other == self->mUnk10 && self->mUnk5 && self->mUnk4 && self->mUnk6) {
        FUN_00777ae0(0x20a, 0, 0);
        FUN_00777ae0(0x20b, 0, 0);
        FUN_00777ae0(0x223, (int)self + 0x3c, 1);
        if (self->mUnk1bc) {
            FUN_00780810((char*)self - 8);
            return;
        }
        FUN_0077f980((char*)self - 8);
        return;
    }
    FUN_00777ae0(0x223, 0, 0);
}
