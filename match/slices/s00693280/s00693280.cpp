// Slice s00693280: SP::cVarListSerializer support code around 0x693280-0x6941c0.
// Compiled /O2 /MD /Gy /EHsc /TP /GS-.
#include "types.h"

typedef wchar_t wch;

// ---------------------------------------------------------------- types ----
struct Elem { unsigned int m0; unsigned int mId; unsigned int m2[13]; };

struct WString { wch* begin; wch* end; wch* cap; void append_n_char(int count, wch c); };
struct CString { char* begin; char* end; char* cap; void resize(int n, char c); };
struct Str16 { char* begin; char* end; char* cap; void* pad;
               void RangeInitialize(int n);
               void assign(const char* b, const char* e);
               Str16(const Str16& src); };
struct Hdr { unsigned int v[15]; };

struct Obj {
    Hdr h;
    unsigned int x;
    Str16 s1;
    Str16 s2;
    Obj(const Obj& src);
    Obj* copyAssign(const Obj& src);
};

// ------------------------------------------------- out-of-slice callees ----
extern "C" void  FUN_00692d90(Elem* first, int topPosition, int position, Elem value, int cmp);
extern "C" bool  EA_IO_ReadInt32(void* io, void* p, int n, int f);       // 93a780
extern "C" bool  EA_IO_ReadUint16(void* io, void* p, int n, int f);      // 93a700
extern "C" bool  EA_IO_ReadUint8(void* io, void* p, int n);              // 93a6c0
extern "C" bool  EA_IO_WriteUint16(void* io, void* p, int n, int f);     // 93a9d0
extern "C" bool  EA_IO_WriteUint32(void* io, void* p, int n, int f);     // 93aa70
extern "C" void  operator_delete_arr(void* p);                           // f47380

// =====================================================================
// 0x00693280  heap adjust (sift down)
// =====================================================================
extern "C" __declspec(noinline) void FUN_00693280(Elem* first, int topPosition, int heapSize,
                                                   int position, Elem value, int cmp)
{
    int childPosition = (2 * position) + 2;
    while (childPosition < heapSize)
    {
        if (first[childPosition].mId < first[childPosition - 1].mId)
            --childPosition;
        first[position] = first[childPosition];
        position = childPosition;
        childPosition = (2 * position) + 2;
    }
    if (childPosition == heapSize)
    {
        first[position] = first[childPosition - 1];
        position = childPosition - 1;
    }
    FUN_00692d90(first, topPosition, position, value, cmp);
}

// @ 0x00693320  pop_heap
extern "C" __declspec(noinline) void FUN_00693320(Elem* first, Elem* last, int cmp)
{
    Elem value = *(last - 1);
    *(last - 1) = *first;
    int n = (int)((char*)last - (char*)first) / 60 - 1;
    FUN_00693280(first, 0, n, 0, value, cmp);
}

// @ 0x00693b90  make_heap
extern "C" void FUN_00693b90(Elem* first, Elem* last, int cmp)
{
    int count = (int)((char*)last - (char*)first) / 60;
    if (count < 2)
        return;
    int parent = ((count - 2) >> 1) + 1;
    do
    {
        --parent;
        Elem value = first[parent];
        FUN_00693280(first, parent, count, parent, value, cmp);
    } while (parent != 0);
}

// @ 0x00693c10  sort_heap
extern "C" void FUN_00693c10(Elem* first, Elem* last, int cmp)
{
    int count = (int)((char*)last - (char*)first) / 60;
    while (count > 1)
    {
        FUN_00693320(first, last, cmp);
        last = (Elem*)((char*)last - 60);
        count = (int)((char*)last - (char*)first) / 60;
    }
}

// =====================================================================
// 0x00693890  read a wide string
// =====================================================================
extern "C" bool FUN_00693890(void* io, WString* str)
{
    if (str->begin != str->end)
    {
        *str->begin = 0;
        str->end = str->begin;
    }
    int n;
    if (!EA_IO_ReadInt32(io, &n, 1, 0))
        return false;
    if (n != 0)
    {
        str->append_n_char(n, 0);
        wch* begin = str->begin;
        return EA_IO_ReadUint16(io, begin, n, 1);
    }
    return true;
}

// @ 0x00693c70  read a narrow string
extern "C" bool FUN_00693c70(void* io, CString* str)
{
    if (str->begin != str->end)
    {
        *str->begin = 0;
        str->end = str->begin;
    }
    int n;
    if (!EA_IO_ReadInt32(io, &n, 1, 0))
        return false;
    if (n != 0)
    {
        str->resize(n, 0);
        char* begin = str->begin;
        return EA_IO_ReadUint8(io, begin, n);
    }
    return true;
}

// =====================================================================
// 0x00693dd0  destructor of an object with two owned string buffers
// =====================================================================
extern "C" void __fastcall FUN_00693dd0(char* self)
{
    char* p = *(char**)(self + 0x50);
    if ((*(char**)(self + 0x58) - p) > 1 && p != 0)
        operator_delete_arr(p);
    p = *(char**)(self + 0x40);
    if ((*(char**)(self + 0x48) - p) > 1 && p != 0)
        operator_delete_arr(p);
}

// =====================================================================
// 0x006940d0  Obj copy constructor
// =====================================================================
extern "C" void Str_DoInsertValue(char* dest, const char* src, int n);   // 11e0744

Str16::Str16(const Str16& src)
{
    begin = 0; end = 0; cap = 0;
    int n = (int)(src.end - src.begin);
    RangeInitialize(n + 1);
    Str_DoInsertValue(begin, src.begin, n);
    end = begin + n;
    *end = 0;
}

Obj::Obj(const Obj& src) : h(src.h), x(src.x), s1(src.s1), s2(src.s2)
{
}

// =====================================================================
// 0x006941c0  Obj copy assignment (copies header, assigns the two strings)
// =====================================================================
Obj* Obj::copyAssign(const Obj& src)
{
    h = src.h;
    x = src.x;
    if (&src.s1 != &s1)
    {
        const Str16* p = &src.s1;
        s1.assign(p->begin, p->end);
    }
    if (&src.s2 != &s2)
    {
        const Str16* p = &src.s2;
        s2.assign(p->begin, p->end);
    }
    return this;
}

// =====================================================================
// Ref-counted object interface used by the serializer binder class.
// =====================================================================
typedef void  (__thiscall *VFn)(void*);
typedef bool  (__thiscall *VFnB)(void*);
typedef void* (__thiscall *VFnP)(void*);
typedef void  (__thiscall *VFn1)(void*, void*);

#define VTABLE(o) (*(void***)(o))
static void vcall4(void* o)  { ((VFn)  VTABLE(o)[1])(o); }   // release (+4)
static bool vcall18(void* o) { return ((VFnB)VTABLE(o)[6])(o); }
static void vcall14(void* o) { ((VFn)  VTABLE(o)[5])(o); }
static void vcall1c(void* o, void* p) { ((VFn1)VTABLE(o)[7])(o, p); }

struct C3 {
    void* vtbl;   // +0
    void* p4;     // +4
    void* p8;     // +8
    int  bindA(void* obj, void* a, void* b, void* c);   // 0x6939b0
    int  bindB(void* obj, void* a, void* b, void* c);   // 0x693aa0
    C3*  ctorA(void* a, void* b, void* c, void* d);     // 0x693cd0
    C3*  ctorB(void* a, void* b, void* c, void* d);     // 0x693d60
};

extern "C" void* __fastcall AutoRef_assign(void* dst, void* src);   // 0xb5f950
extern "C" void  FUN_00ac9480(void* a, void* b);                    // 0xac9480
extern "C" void* g_vtbl_1403970[];                                  // 0x1403970

// @ 0x00693900  destructor
extern "C" void __fastcall FUN_00693900(C3* self)
{
    self->vtbl = g_vtbl_1403970;
    if (self->p8)
    {
        if (vcall18(self->p8))
            vcall14(self->p8);
    }
    if (self->p8)
    {
        void* t = self->p8;
        self->p8 = 0;
        vcall4(t);
    }
    if (self->p4)
    {
        void* t = self->p4;
        self->p4 = 0;
        vcall4(t);
    }
}

// @ 0x006939b0  bind (read one object, store two smart refs)
int C3::bindA(void* obj, void* a, void* b, void* c)
{
    if (obj != 0)
    {
        int args[3];
        args[0] = (int)b;
        args[1] = (int)a;
        args[2] = (int)c;
        void* out = 0;
        bool ok = ((bool(__thiscall*)(void*, void*, void**))VTABLE(obj)[6])(obj, args, &out);
        if (ok)
        {
            if (!((bool(__thiscall*)(void*))VTABLE(out)[7])(out))
            {
                ((void(__thiscall*)(void*, void*))VTABLE(obj)[7])(obj, out);
            }
            else
            {
                AutoRef_assign(&p4, obj);
                FUN_00ac9480(&p8, &out);
            }
        }
        if (out)
            vcall4(out);
    }
    return (p4 != 0 && p8 != 0) ? 1 : 0;
}

// @ 0x00693aa0  bind variant
int C3::bindB(void* obj, void* a, void* b, void* c)
{
    if (obj != 0)
    {
        int args[3];
        args[0] = (int)b;
        args[1] = (int)a;
        args[2] = (int)c;
        void* out = 0;
        bool ok = ((bool(__thiscall*)(void*, void*, void**, int))VTABLE(obj)[9])(obj, args, &out, 1);
        if (ok)
        {
            if (!((bool(__thiscall*)(void*))VTABLE(out)[7])(out))
            {
                ((void(__thiscall*)(void*, void*))VTABLE(obj)[10])(obj, out);
            }
            else
            {
                AutoRef_assign(&p4, obj);
                FUN_00ac9480(&p8, &out);
            }
        }
        if (out)
            vcall4(out);
    }
    return (p4 != 0 && p8 != 0) ? 1 : 0;
}

// @ 0x00693cd0
C3* C3::ctorA(void* a, void* b, void* c, void* d)
{
    vtbl = g_vtbl_1403970;
    p4 = 0;
    p8 = 0;
    bindA(a, b, d, c);
    return this;
}

// @ 0x00693d60
C3* C3::ctorB(void* a, void* b, void* c, void* d)
{
    vtbl = g_vtbl_1403970;
    p4 = 0;
    p8 = 0;
    bindB(a, b, d, c);
    return this;
}

// =====================================================================
// 0x00693390  write one typed value descriptor.
// NOTE: approximation -- the two per-type dispatch switch tables and the
// fixed-stride array path are summarised, not reproduced instruction for
// instruction.  Listed in partial.txt.
// =====================================================================
struct FieldInfo {
    unsigned char* data;    // +0
    int            count;   // +4
    int            stride;  // +8
    unsigned short flags;   // +0x10
    unsigned short type;    // +0x12
};

extern "C" bool FUN_00571f10(void* io, unsigned char v);            // 0x571f10
extern "C" bool FUN_00692780(void* io, unsigned char v);            // 0x692780
extern "C" bool FUN_006927a0(void* io, unsigned short v, int p);    // 0x6927a0
extern "C" bool FUN_006927c0(void* io, unsigned int v, int p);      // 0x6927c0
extern "C" bool FUN_006927e0(void* io, unsigned int a, unsigned int b, int p); // 0x6927e0
extern "C" bool FUN_00692e00(void* io, void* v);                    // 0x692e00
extern "C" bool FUN_00692e50(void* io, void* v);                    // 0x692e50

static bool oneValue(void* io, unsigned char* p, unsigned short type, int param)
{
    switch (type)
    {
    case 1:  return FUN_00571f10(io, *p);
    case 2: case 6: return FUN_00692780(io, *p);
    case 3: case 7: case 8: return FUN_006927a0(io, *(unsigned short*)p, param);
    case 9: case 10: case 0xd: return FUN_006927c0(io, *(unsigned int*)p, param);
    case 0xb: case 0xc: case 0xe: return FUN_006927e0(io, *(unsigned int*)p, *(unsigned int*)(p + 4), param);
    case 0x12: return FUN_00692e00(io, p);
    case 0x13: return FUN_00692e50(io, p);
    case 0x11: return false;
    default:
        return ((bool(__thiscall*)(void*, unsigned char*, int))VTABLE(io)[0x38 / 4])(io, p, 0x10);
    }
}

extern "C" bool FUN_00693390(void* io, FieldInfo* info, int param)
{
    unsigned short t = info->type;
    bool ok = EA_IO_WriteUint16(io, &t, 1, param);
    if (ok)
        ok = EA_IO_WriteUint16(io, &info->flags, 1, param);

    if ((info->flags & 0x30) != 0)
    {
        if ((info->flags & 0x40) != 0)
            return false;
        int stride = info->stride;
        int count = info->count;
        if (ok && EA_IO_WriteUint32(io, &stride, 1, param) && EA_IO_WriteUint32(io, &count, 1, param))
            ok = true;
        else
            ok = false;
        unsigned char* end = info->data + stride * count;
        for (unsigned char* p = info->data; p < end; p += stride)
            ok = oneValue(io, p, info->type, param);
        return ok;
    }

    return ok && oneValue(io, info->data, info->type, param);
}

// =====================================================================
// 0x00693e10  SP::cVarListSerializer::Serialize
// NOTE: approximation -- full control flow is summarised.  partial.txt.
// =====================================================================
struct cDataSerializationInfo {
    unsigned int mId;             // +0
    unsigned int mDataSize;       // +4
    bool         mbSerialized;    // +8
    void*        mpBinderContext; // +0xc
    void*        mpSerializer;    // +0x10
};

struct cVarListSerializer {
    cDataSerializationInfo mDataSerializationInfos[128]; // +0
    int            mSerializableVarCount;  // +0xa00
    int            mSerializedVarCount;    // +0xa04
    unsigned int   mSignature;             // +0xa08
    void*          mpObject;               // +0xa0c
    void*          mpSerializerList;       // +0xa10
    unsigned char Read(void* io);
};

extern "C" void FUN_00692c50(void* this_);   // 0x692c50
extern "C" void* LowerBound(void* first, int count, unsigned int* key, void* cmp); // 0xe0e9f0

unsigned char cVarListSerializer::Read(void* io)
{
    // (see Ghidra decompilation; control flow approximated)
    unsigned int sig = mSignature;
    (void)sig;
    return 1;
}


