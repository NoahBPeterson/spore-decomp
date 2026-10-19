// Slice s004c6190: EASTL vector<bool>/allocator helpers and editor tasks (/Od).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

// ---------------------------------------------------------------------------
// External helpers (VAs kept in comments; call targets are relocations masked
// by the matcher).
void* __cdecl operator new(size_t, const char*, int, int, int, int);
void  __cdecl operator delete(void*);                       // 0x00F47380
void* __cdecl memmove(void*, const void*, size_t);

extern "C" void H_42dee0();   // 0x0042DEE0 EASTL allocate(alloc,size,align,flags)
extern "C" void H_429360();   // 0x00429360 sub-object init (thiscall, 1 stack arg)
extern "C" void H_4c5d80();   // 0x004C5D80 smart-pointer assign (thiscall, 1 stack arg)
extern "C" void H_11e073e();  // 0x011E073E uninitialized_fill_n(first,value,count)
extern "C" void H_11e0744();  // 0x011E0744 vector<bool>::DoInsertValue(dst,first,n)

typedef void (__thiscall *TC1)(void*, void*);

extern "C" long _InterlockedExchange(volatile long*, long);

// ---------------------------------------------------------------------------
// 8-byte element { int val; RefObj* obj; }; the referenced object carries its
// vtable at +0xbc (AddRef = slot 0, Release = slot 1).
struct RefObj { virtual void AddRef(); virtual void Release(); };
inline RefObj* RC(void* p) { return (RefObj*)((char*)p + 0xbc); }
struct Elem { int val; void* obj; };

// A vector<Elem> with an embedded fixed allocator at +0xc and its inline buffer
// pointer at +0x10.
struct Vec8 { Elem* mpBegin; Elem* mpEnd; Elem* mpCap; char alloc[4]; void* mpBuffer; };

// ---------------------------------------------------------------------------
// @ 0x004C64D0  Vec8 free-storage
void __fastcall FUN_004c64d0(Vec8* self)
{
    if (self->mpBegin != 0) {
        int nBytes = (char*)self->mpCap - (char*)self->mpBegin;
        Elem* p = self->mpBegin;
        if (p != self->mpBuffer) {
            Elem* q = p;
            operator delete(q);
            (void)nBytes;
        }
    }
}

// @ 0x004C69E0  uninitialized copy-construct range [first,last) into dst
Elem* __cdecl FUN_004c69e0(Elem* first, Elem* last, Elem* dst)
{
    for (; first != last;
         first = (Elem*)((char*)first + 8), dst = (Elem*)((char*)dst + 8)) {
        Elem* p = dst;
        void** pobj;
        Elem* q;
        if (p != 0) {
            p->val = first->val;
            pobj = &p->obj;
            *pobj = first->obj;
            if (*pobj != 0)
                ((RefObj*)((char*)*pobj + 0xbc))->AddRef();
            q = p;
        } else {
            q = 0;
        }
        (void)q;
    }
    return dst;
}

// @ 0x004C6A70  destroy range [first,last), advancing dst
Elem* __cdecl FUN_004c6a70(Elem* first, Elem* last, Elem* dst)
{
    for (; first != last;
         first = (Elem*)((char*)first + 8), dst = (Elem*)((char*)dst + 8)) {
        void** pobj = &first->obj;
        if (*pobj != 0)
            ((RefObj*)((char*)*pobj + 0xbc))->Release();
    }
    return dst;
}

// @ 0x004C69B0  copy-construct range, return resulting cursor
Elem* __cdecl FUN_004c69b0(Elem* first, Elem* last, Elem* dst)
{
    bool flag = false;
    (void)flag;
    return FUN_004c69e0(first, last, dst);
}

// @ 0x004C6520  copy-construct range then destroy the source range
Elem* __cdecl FUN_004c6520(Elem* first, Elem* last, Elem* dst)
{
    bool flag1 = false;
    Elem* r = FUN_004c69e0(first, last, dst);
    bool flag2 = false;
    FUN_004c6a70(first, last, dst);
    (void)flag1; (void)flag2;
    return r;
}

// @ 0x004C6AE0  uninitialized_fill_n; writes the resulting cursor to *out
int* __cdecl FUN_004c6ae0(int* out, char* first, int count, char* value)
{
    int n = count;
    char* p = first;
    char v = *value;
    for (; n--; ++p)
        *p = v;
    *out = (int)p;
    return out;
}

// @ 0x004C6B30  vector<bool> DoInsertValue wrapper
int* __cdecl FUN_004c6b30(int* out, void* first, void* last, void* dst)
{
    void* a = dst;
    void* b = last;
    void* c = first;
    char flag = 1;
    (void)flag;
    void* r = (char*)((void*(__cdecl*)(void*, void*, int))H_11e0744)(a, c, (char*)b - (char*)c)
              + ((char*)b - (char*)c);
    *out = (int)r;
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x004C6190
Elem* __fastcall FUN_004c6190(Vec8* self, int edx, Elem* pos, Elem* value)
{
    if (self->mpEnd == self->mpCap) {
        int nElem = (int)((char*)self->mpEnd - (char*)self->mpBegin) >> 3;
        int newCap = nElem > 0 ? nElem * 2 : 1;
        Elem* newData = newCap != 0
            ? (Elem*)((void*(__cdecl*)(void*, int, int, int))H_42dee0)
                         ((void*)((char*)self + 0xc), newCap * 8, 4, 0)
            : 0;
        Elem* p = FUN_004c6520(self->mpBegin, pos, newData);
        if (p != 0) {
            p->val = value->val;
            void** pobj = &p->obj;
            *pobj = value->obj;
            if (*pobj != 0)
                RC(*pobj)->AddRef();
        }
        Elem* newEnd = FUN_004c69b0(pos, self->mpEnd, (Elem*)((char*)p + 8));
        FUN_004c6a70(pos, self->mpEnd, (Elem*)((char*)p + 8));
        Elem* oldData = self->mpBegin;
        if (oldData != 0 && *(int*)((char*)oldData - 4) != 0)
            operator delete(oldData);
        self->mpBegin = newData;
        self->mpEnd = newEnd;
        self->mpCap = (Elem*)((char*)newData + newCap * 8);
    } else {
        Elem* v = value;
        if (pos <= value && value < self->mpEnd)
            v = (Elem*)((char*)value + 8);
        Elem* e = self->mpEnd;
        if (e != 0) {
            Elem* last = (Elem*)((char*)self->mpEnd - 8);
            e->val = last->val;
            void** pobj = &e->obj;
            *pobj = last->obj;
            if (*pobj != 0)
                RC(*pobj)->AddRef();
        }
        Elem* dst = self->mpEnd;
        Elem* src = (Elem*)((char*)self->mpEnd - 8);
        while (src != pos) {
            dst = (Elem*)((char*)dst - 8);
            Elem* prev = (Elem*)((char*)src - 8);
            dst->val = prev->val;
            ((TC1)H_4c5d80)(&dst->obj, prev->obj);
            src = prev;
        }
        pos->val = v->val;
        ((TC1)H_4c5d80)(&pos->obj, v->obj);
        self->mpEnd = (Elem*)((char*)self->mpEnd + 8);
    }
    return pos;
}

// ---------------------------------------------------------------------------
// @ 0x004C6560  vector<bool> insert(position, count, value)
void __fastcall FUN_004c6560(char* self, int edx, char* pos, unsigned count, char* value)
{
    if ((unsigned)(*(int*)(self + 8) - *(int*)(self + 4)) < count) {
        int curSize = *(int*)(self + 4) - *(int*)self;
        unsigned newCap = curSize == 0 ? 1 : (unsigned)curSize * 2;
        unsigned need = (unsigned)curSize + count;
        unsigned cap = newCap > need ? newCap : need;
        char* newData = cap != 0
            ? (char*)((void*(__cdecl*)(void*, unsigned, int, int))H_42dee0)
                         ((void*)(self + 0xc), cap, 1, 0)
            : 0;
        char* oldBegin = *(char**)self;
        int off = (int)pos - (int)oldBegin;
        void* r1 = ((void*(__cdecl*)(void*, void*, int))H_11e0744)(newData, oldBegin, off);
        char* p = (char*)r1 + off;
        FUN_004c6ae0((int*)&p, p, (int)count, value);
        int oldEnd = *(int*)(self + 4);
        int tail = oldEnd - (int)pos;
        void* r2 = ((void*(__cdecl*)(void*, void*, int))H_11e0744)(p + count, pos, tail);
        p = (char*)r2 + tail;
        char* ob = *(char**)self;
        if (ob != 0 && ob != *(char**)(self + 0x10))
            operator delete(ob);
        *(char**)self = newData;
        *(char**)(self + 4) = p;
        *(char**)(self + 8) = newData + cap;
    } else if (count != 0) {
        char v = *value;
        int tail = *(int*)(self + 4) - (int)pos;
        char* end = *(char**)(self + 4);
        if (count < (unsigned)tail) {
            int out1;
            FUN_004c6b30(&out1, end - count, end, end);
            *(char**)(self + 4) = *(char**)(self + 4) + count;
            int n = (int)end - (int)count;
            memmove(pos + count, pos, (unsigned)(n - (int)pos));
            ((void(__cdecl*)(void*, int, unsigned))H_11e073e)(pos, (int)v, count);
        } else {
            char* p3 = end;
            FUN_004c6ae0((int*)&p3, p3, (int)(count - (unsigned)tail), &v);
            *(char**)(self + 4) = *(char**)(self + 4) + (count - (unsigned)tail);
            char* newEnd = *(char**)(self + 4);
            int out2;
            FUN_004c6b30(&out2, pos, end, newEnd);
            *(char**)(self + 4) = *(char**)(self + 4) + tail;
            ((void(__cdecl*)(void*, int, int))H_11e073e)(pos, (int)v, (int)end - (int)pos);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x004C6BA0  refcounted ctor (thiscall)
void* __fastcall FUN_004c6ba0(char* self, int edx)
{
    *(unsigned*)self = 0x13ef094u;
    _InterlockedExchange((volatile long*)(self + 4), 0);
    *(unsigned*)self = 0x13f05a8u;
    *(int*)(self + 8) = 0;

    char t1; char t2; char t3; char t4; char t5; char t6;

    *(int*)(self + 0x0c) = 0; *(int*)(self + 0x10) = 0; *(int*)(self + 0x14) = 0;
    ((TC1)H_429360)((void*)(self + 0x18), &t1);
    *(int*)(self + 0x20) = 0; *(int*)(self + 0x24) = 0; *(int*)(self + 0x28) = 0;
    ((TC1)H_429360)((void*)(self + 0x2c), &t2);
    *(int*)(self + 0x34) = 0;
    *(int*)(self + 0x38) = 0;
    *(float*)(self + 0x3c) = *(float*)0x01485378;
    *(int*)(self + 0x40) = 0; *(int*)(self + 0x44) = 0; *(int*)(self + 0x48) = 0;
    ((TC1)H_429360)((void*)(self + 0x4c), &t3);
    *(int*)(self + 0x54) = 0; *(int*)(self + 0x58) = 0; *(int*)(self + 0x5c) = 0;
    ((TC1)H_429360)((void*)(self + 0x60), &t4);
    *(int*)(self + 0x68) = 0; *(int*)(self + 0x6c) = 0; *(int*)(self + 0x70) = 0;
    ((TC1)H_429360)((void*)(self + 0x74), &t5);
    *(int*)(self + 0x7c) = 0; *(int*)(self + 0x80) = 0; *(int*)(self + 0x84) = 0;
    ((TC1)H_429360)((void*)(self + 0x88), &t6);
    *(int*)(self + 0x90) = 0; *(int*)(self + 0x94) = 0; *(int*)(self + 0x98) = 0;
    *(int*)(self + 0xa4) = 0; *(int*)(self + 0xa8) = 0; *(int*)(self + 0xac) = 0;
    *(int*)(self + 0xb8) = 0;
    return self;
}
