// Slice s00547e90: EASTL vector/vector_map helpers for SP::Feed.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <string.h>

typedef unsigned int size_t;

// ---------------------------------------------------------------- externals
void* operator new[](size_t, const char*, int, unsigned, const char*, int);
void  operator_delete__(void*);
void* FUN_0042dee0(void* alloc, int size, int align, int flags); // @ 0x42dee0
void  FUN_00423820(int a, int b);
void* FUN_00549e40(int a, int b, int c);           // @ 0x549e40 relocate
int   FUN_00549ec0(int a, int b, int c);           // @ 0x549ec0 copy
void* FUN_00549f80(int a, int b, int c, char d);   // @ 0x549f80 lower_bound
void  FUN_0054a070(int a, void* b);                // @ 0x54a070 insert
void* FUN_0054a2d0(int a, int b, int c, char d);   // @ 0x54a2d0 lower_bound
int   FUN_0054a3c0(int a, int b, int c);           // @ 0x54a3c0 relocate
int   FUN_00548ee0(int a);                         // @ 0x548ee0 ctor 0x118
void  FUN_00549250(int a);                         // @ 0x549250 copy 0x118
int   FUN_00549500(int a);                         // @ 0x549500 ctor 0x70
void  FUN_005496a0(int a);                         // @ 0x5496a0 move 0x70
void  FUN_00547840();                              // @ 0x547840 dtor 0x70
void* DoInsertBool(void* vec, void* pos, int n);   // @ 0x11e0744
void  WStringAssign(void* self, const wchar_t* s); // eastl basic_string<wchar_t>::assign
void  WStringAppend(void* self, const wchar_t* a, const wchar_t* b);

static int Cmp16(const unsigned short* a, const unsigned short* b)
{
    for (;;) {
        if (*b != *a) return *b < *a ? -1 : 1;
        if (*b == 0) return 0;
        a++; b++;
    }
}

// ---------------------------------------------------------------- object
struct Obj43 {
    char mPad[0x200];

    void  FUN_00547e90(int* pos, int* value);
    void  FUN_00548180();
    void  FUN_005481d0(int* pos, int* value);
    void  FUN_00548400();
    void  FUN_00548450(int pos, int value);
    void* FUN_00548690(int* param_2, int* param_3);
    void* FUN_00548740(int* param_2, int* param_3);
    int   FUN_00548860(int param_2, int* param_3);
    void* FUN_00548910(int* param_2, int* param_3);
    int   FUN_00548a30(int param_2, int param_3);
    void  FUN_00548b10(int param_2, int param_3);
};

// @ 0x00547e90  (vector of 0x10-byte wstrings: insert/grow)
void Obj43::FUN_00547e90(int* pos, int* value)
{
    int* v = (int*)this;
    if (v[1] == v[2]) {
        int old = v[1] - *v >> 4;
        int cap = old == 0 ? 1 : old << 1;
        int newBuf = cap == 0 ? 0 : (int)FUN_0042dee0((char*)v + 0xc, cap << 4, 4, 0);
        int* p = (int*)FUN_00549e40(*v, (int)pos, newBuf);
        int* mid;
        if (p == 0) mid = 0;
        else {
            p[0] = 0; p[1] = 0; p[2] = 0;
            FUN_00423820(value[0], value[1]);
            mid = p;
        }
        int end = (int)FUN_00549e40((int)pos, v[1], (int)(p + 4));
        (void)mid;
        if (*v != 0) operator_delete__((void*)*v);
        *v = newBuf;
        v[1] = end;
        v[2] = cap * 0x10 + newBuf;
    } else {
        int* src = value;
        if ((int*)pos <= value && value < (int*)v[1]) src = value + 4;
        int* end = (int*)v[1];
        if (end != 0) {
            end[0] = 0; end[1] = 0; end[2] = 0;
            FUN_00423820(*(int*)(v[1] - 0x10), *(int*)(v[1] - 0xc));
        }
        int* dst = (int*)v[1];
        int* cur = (int*)(v[1] - 0x10);
        while (cur != pos) {
            int* nxt = cur - 4;
            dst = dst - 4;
            if (nxt != dst)
                WStringAssign(nxt, (const wchar_t*)cur[-3]);
            cur = nxt;
        }
        if (src != pos)
            WStringAssign(src, (const wchar_t*)src[1]);
        v[1] = v[1] + 0x10;
    }
}

// @ 0x00548180
void Obj43::FUN_00548180()
{
    int* p = (int*)this;
    if (*p != 0)
        operator_delete__((void*)*p);
}

// @ 0x005481d0  (vector<int>: insert/grow)
void Obj43::FUN_005481d0(int* pos, int* value)
{
    int* v = (int*)this;
    if (v[1] == v[2]) {
        int old = v[1] - *v >> 2;
        int cap = old == 0 ? 1 : old << 1;
        int newBuf = cap == 0 ? 0 : (int)FUN_0042dee0((char*)v + 0xc, cap << 2, 4, 0);
        int* base = (int*)*v;
        void* pv = DoInsertBool((void*)newBuf, base, (int)pos - (int)base);
        int* mid = (int*)((int)pv + (((int)pos - (int)base) >> 2) * 4);
        if (mid != 0) *mid = *value;
        int end = v[1];
        void* pv2 = DoInsertBool((void*)(mid + 1), pos, end - (int)pos);
        if (*v != 0) operator_delete__((void*)*v);
        *v = newBuf;
        v[1] = (int)((int)pv2 + ((end - (int)pos) >> 2) * 4);
        v[2] = (int)((char*)newBuf + cap * 4);
    } else {
        int* src = value;
        if ((int*)pos <= value && value < (int*)v[1]) src = value + 1;
        if ((int*)v[1] != 0)
            *(int*)v[1] = *(int*)(v[1] - 4);
        memmove((void*)(v[1] + (((v[1] - 4) - (int)pos) >> 2) * -4), pos,
                (unsigned int)((v[1] - 4) - (int)pos));
        *pos = *src;
        v[1] = v[1] + 4;
    }
}

// @ 0x00548400
void Obj43::FUN_00548400()
{
    int* p = (int*)this;
    if (*p != 0)
        operator_delete__((void*)*p);
}

// @ 0x00548450  (vector of 0x118-byte entries: insert/grow)
void Obj43::FUN_00548450(int pos, int value)
{
    int* v = (int*)this;
    if (v[1] == v[2]) {
        int old = (v[1] - *v) / 0x118;
        int cap = old == 0 ? 1 : old << 1;
        int newBuf = cap == 0 ? 0 : (int)FUN_0042dee0((char*)v + 0xc, cap * 0x118, 8, 0);
        int iVar1 = FUN_00549ec0(*v, pos, newBuf);
        int uVar2;
        if (iVar1 == 0) uVar2 = 0;
        else uVar2 = (int)FUN_00548ee0(value);
        (void)uVar2;
        int iVar3 = FUN_00549ec0(pos, v[1], iVar1 + 0x118);
        iVar1 = *v;
        if (iVar1 != 0 && *(int*)(iVar1 - 4) != 0) operator_delete__((void*)iVar1);
        *v = newBuf;
        v[1] = iVar3;
        v[2] = cap * 0x118 + newBuf;
    } else {
        int src = value;
        if ((unsigned int)pos <= (unsigned int)value && (unsigned int)value < (unsigned int)v[1])
            src = value + 0x118;
        if (v[1] != 0) FUN_00548ee0(v[1] - 0x118);
        int cur = v[1] - 0x118;
        while (cur != pos) {
            cur = cur - 0x118;
            FUN_00549250(cur);
        }
        FUN_00549250(src);
        v[1] = v[1] + 0x118;
    }
}

// @ 0x00548690
void* Obj43::FUN_00548690(int* param_2, int* param_3)
{
    int base = (int)this;
    int* end = *(int**)(base + 4);
    int* dst = param_2;
    for (int* cur = param_3; cur != end; cur = cur + 4) {
        dst[0] = cur[0]; dst[1] = cur[1]; dst[2] = cur[2]; dst[3] = cur[3];
        dst = dst + 4;
    }
    *(int*)(base + 4) = *(int*)(base + 4) + (((int)param_3 - (int)param_2) >> 4) * -0x10;
    return param_2;
}

// @ 0x00548740
void* Obj43::FUN_00548740(int* param_2, int* param_3)
{
    int* p = (int*)this;
    int* it = (int*)FUN_00549f80(p[0], p[1], (int)param_3, *(char*)(p + 5));
    if (it != (int*)p[1]) {
        int cmp = Cmp16((const unsigned short*)*it, (const unsigned short*)*param_3);
        if (cmp >= 0) {
            param_2[0] = (int)it;
            param_2[1] = (int)(it + 4);
            return param_2;
        }
    }
    param_2[0] = (int)it;
    param_2[1] = (int)it;
    return param_2;
}

// @ 0x00548860
int Obj43::FUN_00548860(int param_2, int* param_3)
{
    int* p = (int*)this;
    int base = *p;
    if (param_2 == p[1] && p[1] != p[2]) {
        int* e = (int*)p[1];
        p[1] = p[1] + 0x10;
        if (e != 0) {
            e[0] = param_3[0]; e[1] = param_3[1]; e[2] = param_3[2]; e[3] = param_3[3];
        }
    } else {
        FUN_0054a070(param_2, param_3);
    }
    return (param_2 - base >> 4) * 0x10 + *p;
}

// @ 0x00548910
void* Obj43::FUN_00548910(int* param_2, int* param_3)
{
    int* p = (int*)this;
    int* it = (int*)FUN_0054a2d0(p[0], p[1], (int)param_3, *(char*)(p + 5));
    if (it != (int*)p[1]) {
        int cmp = Cmp16((const unsigned short*)*it, (const unsigned short*)*param_3);
        if (cmp >= 0) {
            param_2[0] = (int)it;
            param_2[1] = (int)(it + 2);
            return param_2;
        }
    }
    param_2[0] = (int)it;
    param_2[1] = (int)it;
    return param_2;
}

// @ 0x00548a30
int Obj43::FUN_00548a30(int param_2, int param_3)
{
    int base = (int)this;
    int end = *(int*)(base + 4);
    int dst = param_2;
    for (int cur = param_3; cur != end; cur = cur + 0x70) {
        FUN_005496a0(cur);
        dst = dst + 0x70;
    }
    int stop = *(int*)(base + 4);
    for (int cur = dst; cur < stop; cur = cur + 0x70)
        FUN_00547840();
    *(int*)(base + 4) = *(int*)(base + 4) + ((param_3 - param_2) / 0x70) * -0x70;
    return param_2;
}

// @ 0x00548b10  (vector of 0x70-byte entries: insert/grow)
void Obj43::FUN_00548b10(int param_2, int param_3)
{
    int* v = (int*)this;
    if (v[1] == v[2]) {
        int old = (v[1] - *v) / 0x70;
        int cap = old == 0 ? 1 : old << 1;
        int newBuf = cap == 0 ? 0 : (int)FUN_0042dee0((char*)v + 0xc, cap * 0x70, 8, 0);
        int iVar1 = FUN_0054a3c0(*v, param_2, newBuf);
        int uVar2;
        if (iVar1 == 0) uVar2 = 0;
        else uVar2 = (int)FUN_00549500(param_3);
        (void)uVar2;
        int iVar3 = FUN_0054a3c0(param_2, v[1], iVar1 + 0x70);
        iVar1 = *v;
        if (iVar1 != 0 && *(int*)(iVar1 - 4) != 0) operator_delete__((void*)iVar1);
        *v = newBuf;
        v[1] = iVar3;
        v[2] = cap * 0x70 + newBuf;
    } else {
        int src = param_3;
        if ((unsigned int)param_2 <= (unsigned int)param_3
            && (unsigned int)param_3 < (unsigned int)v[1])
            src = param_3 + 0x70;
        if (v[1] != 0) FUN_00549500(v[1] - 0x70);
        int cur = v[1] - 0x70;
        while (cur != param_2) {
            cur = cur - 0x70;
            FUN_005496a0(cur);
        }
        FUN_005496a0(src);
        v[1] = v[1] + 0x70;
    }
}
