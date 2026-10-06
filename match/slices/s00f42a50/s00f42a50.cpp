// Slice s00f42a50 -- unnamed action/vector helpers + FunctionalMatch (bfs1 slice 6).
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

void* __cdecl eastl_alloc(size_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  __cdecl eastl_free(void* p);                                                                   // 0x00f47380

// element whose stride is 0x34
struct T34 { char pad[0x34]; void Construct(const T34&) throw(); };
struct Vec34 {
    T34* mpBegin; T34* mpEnd; T34* mpCapacity; char alloc[4];
    T34* insert(T34* pos, const T34& value);       // 0x00f42dc0
    void DoInsert(T34* pos, const T34& value);     // 0x00f2cd50
    void DoAssign(uint32_t n, const void* value);      // 0x00f2cb50
    void eraseRange(T34* first, T34* last);        // 0x00f2cb00
};

// @ 0x00f42dc0
T34* Vec34::insert(T34* pos, const T34& value)
{
    int index = pos - mpBegin;
    if (pos == mpEnd && mpEnd != mpCapacity) {
        T34* p = mpEnd++;
        if (p != 0)
            p->Construct(value);
    } else {
        DoInsert(pos, value);
    }
    return mpBegin + index;
}

// element whose stride is 0x4e0
struct T4e0 { char pad[0x4e0]; void Construct(const T4e0&) throw(); };
struct Vec4e0 {
    T4e0* mpBegin; T4e0* mpEnd; T4e0* mpCapacity; char alloc[4];
    T4e0* insert(T4e0* pos, const T4e0& value);    // 0x00f43880
    void DoInsert(T4e0* pos, const T4e0& value);   // 0x00f2df80
    void eraseRange(T4e0* first, T4e0* last);      // 0x00f2dd70
    Vec4e0* fillCtor(uint32_t n, const T4e0& value, const void* alloc);   // 0x00f42f90
};

// @ 0x00f43880
T4e0* Vec4e0::insert(T4e0* pos, const T4e0& value)
{
    int index = pos - mpBegin;
    if (pos == mpEnd && mpEnd != mpCapacity) {
        T4e0* p = mpEnd++;
        if (p != 0)
            p->Construct(value);
    } else {
        DoInsert(pos, value);
    }
    return mpBegin + index;
}

// @ 0x00f42f90  vector(n, value, alloc)
Vec4e0* Vec4e0::fillCtor(uint32_t n, const T4e0& value, const void* alloc)
{
    (void)alloc;
    T4e0* p = n ? (T4e0*)eastl_alloc(n * 0x4e0, "Simulator", 0, 0,
                                     "eastl/allocator.h", 0xd1) : 0;
    uint32_t count = n;
    mpBegin = p;
    mpEnd = p;
    mpCapacity = (T4e0*)((char*)p + count * 0x4e0);
    T4e0* it = p;
    while (n > 0) {
        if (it)
            it->Construct(value);
        --n;
        it = (T4e0*)((char*)it + 0x4e0);
    }
    mpEnd = (T4e0*)((char*)mpBegin + count * 0x4e0);
    return this;
}

// element whose stride is 0x188; it owns a sub-vector at +0x18 (stride 0x44)
struct T188 {
    char   pad00[0x18];
    char*  mpSubBegin;   // +0x18
    char*  mpSubEnd;     // +0x1c
    char   pad20[0x188 - 0x20];
};
struct Vec188 {
    T188* mpBegin; T188* mpEnd; T188* mpCapacity; char alloc[4];
    T188* erase(T188* pos);   // 0x00f43740
};
void __cdecl eastl_copy188(T188* first, T188* last, T188* dest);  // 0x00dfd250
struct Sub { void destroy(); };                                   // 0x00f280f0

// @ 0x00f43740
T188* Vec188::erase(T188* pos)
{
    if ((char*)pos + 0x188 < (char*)mpEnd)
        eastl_copy188(pos + 1, mpEnd, pos);
    mpEnd = (T188*)((char*)mpEnd - 0x188);
    T188* last = mpEnd;
    char* end = last->mpSubEnd;
    for (char* it = last->mpSubBegin; it < end; it += 0x44)
        ((Sub*)(it + 4))->destroy();
    char* base = last->mpSubBegin;
    if (base != 0 && *(int*)(base - 4) != 0)
        eastl_free(base);
    return pos;
}

// @ 0x00f43830  erase element #idx from the 0x188 vector of the object returned by 0xf3be60
struct Obj188 {
    char   pad00[0x84];
    Vec188 vec;             // +0x84
};
void* __stdcall FUN_00f3be60(int a);   // 0x00f3be60
void __cdecl f_43830(int a, int idx)
{
    Obj188* o = (Obj188*)FUN_00f3be60(a);
    if (o != 0 && idx >= 0) {
        Vec188* v = &o->vec;
        int count = (int)(((char*)v->mpEnd - (char*)v->mpBegin) / 0x188);
        if (idx < count)
            v->erase((T188*)((char*)v->mpBegin + idx * 0x188));
    }
}

// ---------------------------------------------------------------- FunctionalMatch helpers (skeletons)
struct FMConstraint {
    int32_t mField0, mField4, mField8, mFieldC, mField10, mField14, mField18, mField1C, mField20;
};
extern "C" void* __cdecl FM_DataList_SetAssetData(int a, int b);

// @ 0x00f42a50
int f_42a50(int a, int b, int c)
{
    (void)a; (void)b; (void)c;
    return 0;
}

// @ 0x00f42e60
void* f_42e60(void* self, void* src)
{
    (void)self; (void)src;
    return self;
}

// @ 0x00f42ef0
void f_42ef0(void* self, int n)
{
    (void)self; (void)n;
}

// @ 0x00f43010
int f_43010(void)
{
    return 0;
}

// @ 0x00f43200
int f_43200(void* out, int a, int b)
{
    (void)out; (void)a; (void)b;
    return 0;
}

// @ 0x00f43420
int f_43420(void)
{
    return 0;
}

// @ 0x00f438f0
void f_438f0(void* self, int n, int value)
{
    (void)self; (void)n; (void)value;
}
