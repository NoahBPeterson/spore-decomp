// slice s008d35d0 -- TSI type-supplier / glyph-run list + sort utilities.
// Compile: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

extern "C" int   FUN_008d3580(int a, int b, int c, int d);
extern "C" char  FUN_008d3530(int a, int b, int c);
extern "C" int   FUN_00c7ea30(int a, int b, int c);
extern "C" void  FUN_00edba80(void* a, void* b, void* c);
extern "C" void* PTR_FUN_01435990;
extern "C" void* PTR_FUN_01435980;

struct TSI;

// Non-member helpers (cdecl fastcall/plain) ---------------------------------
void FUN_008d3750(unsigned* param_1, unsigned* param_2);
void FUN_008d3820(unsigned* param_1, unsigned* param_2);
unsigned* FUN_008d38d0(unsigned* a, unsigned* b, unsigned* c);
void FUN_008d3a10(int param_1, int param_2, int param_3, unsigned param_4, unsigned param_5,
                  unsigned param_6, unsigned param_7, unsigned param_8);
void FUN_008d3b70(int param_1, int param_2, int param_3, int param_4, unsigned param_5,
                  unsigned param_6, unsigned param_7, unsigned param_8, int param_9);
void FUN_008d4040(int* a, int* b, int* c, int d);
void FUN_008d40b0(int a, int b, int c);
void FUN_008d4110(unsigned* a, int b, int c);
void FUN_008d4250(unsigned* a, unsigned* b, unsigned c, unsigned d, unsigned e);
void FUN_008d4320(unsigned* a, unsigned* b, unsigned* c, int d);

// __thiscall container functions as real C++ member functions (ecx = this).
struct TSI;
struct TSI {
    char data[0x390];
    void  FUN_008d35d0(int param_2);
    void  FUN_008d3690(int* param_2);
    char  FUN_008d36f0(int a, int b, int c);
    unsigned FUN_008d3d30(int a, int b);
    int   FUN_008d3ad0(int a);
    int   FUN_008d3ae0(int a);
    void  FUN_008d3b10(int* a);
    int*  FUN_008d3dc0(int a, int* b, int c, int d, int e);
    void  FUN_008d3e30(int* a, unsigned p3);
    void  FUN_008d41b0(int* a);
    void  FUN_008d4400(int* a, int* b);
};

#define M(off) (*(int*)(data + (off)))
#define MU(off) (*(unsigned*)(data + (off)))

// ---------------------------------------------------------------------------
// @ 0x008d35d0
void TSI::FUN_008d35d0(int param_2)
{
    int local[7];
    int i;
    int* q;
    for (i = 0; i < 7; i++)
        local[i] = *(int*)(param_2 + i * 4);
    --M(0x388);
    q = (int*)(data + 8 + M(0x388) * 0x1c);
    if ((unsigned)param_2 < (unsigned)q) {
        for (i = 0; i < 7; i++)
            *(int*)(param_2 + i * 4) = q[i];
    }
    if (local[0] != 0 && *(int*)(local[0] + 0x10) != 0 && ((unsigned)local[6] & 0x2000) == 0) {
        ((void(*)(int, int*, int))*(int*)(local[0] + 0x10))(
            param_2, local, *(int*)(local[0] + 0x14));
    }
    if (local[2] != 0 && ((unsigned)local[6] & 0x1000) == 0) {
        int r = FUN_008d3580(local[2], (int)(char)local[5],
                             (int)(char)((unsigned)local[5] >> 8), 0x1000);
        if (r != 0)
            ((TSI*)r)->FUN_008d35d0(param_2);
    }
}

// @ 0x008d3690
void TSI::FUN_008d3690(int* param_2)
{
    int* p;
    int n;
    unsigned c;
    n = M(0x388);
    c = 0;
    if (n != 0) {
        p = (int*)(data + 0x14);
        do {
            if (p[-2] == param_2[1] && p[-3] == *param_2 && *p == param_2[3])
                c = c + 1;
            p = p + 7;
            n = n - 1;
        } while (n != 0);
    }
    *(unsigned short*)(param_2 + 6) = (unsigned short)(1 < c);
    ((TSI*)param_2)->FUN_008d35d0(0x5ece0001);
}

// @ 0x008d36f0
char TSI::FUN_008d36f0(int param_2, int param_3, int param_4)
{
    char* eax;
    unsigned u;
    if (param_2 != 0) {
        u = 0;
        unsigned cnt = MU(0x388);
        if (u < cnt) {
            eax = data + 0x1d;
            do {
                if (*(int*)(eax - 0x11) == param_2 &&
                    (param_3 == -2 || param_3 == *eax) &&
                    (param_4 == 7 || param_4 == eax[-1]))
                    return 1;
                u = u + 1;
                eax = eax + 0x1c;
            } while (u < cnt);
        }
    }
    return 0;
}

// @ 0x008d3750
void FUN_008d3750(unsigned* param_1, unsigned* param_2)
{
    unsigned u1, u2, u3, u4;
    unsigned *p5, *p6, *p7, *p8;
    bool b;
    unsigned short us;
    p6 = param_1;
    if (param_1 != param_2) {
        while ((p6 = p6 + 4) != param_2) {
            u1 = p6[1]; u2 = p6[3]; u3 = p6[2]; u4 = *p6;
            p7 = p6;
            if (p6 != param_1) {
                us = (unsigned short)(u3 >> 0x10);
                p5 = p6;
                do {
                    p8 = p5 - 4;
                    b = u4 < *p8;
                    if (u4 == *p8) {
                        b = *(unsigned short*)((int)p5 - 6) <= us;
                        if (us == *(unsigned short*)((int)p5 - 6)) {
                            if ((unsigned short)u3 == (unsigned short)p5[-2])
                                b = u1 < p5[-3];
                            else
                                b = (unsigned short)p5[-2] < (unsigned short)u3;
                        }
                    }
                    if (!b) break;
                    *p7 = *p8; p7[1] = p5[-3]; p7[2] = p5[-2]; p7[3] = p5[-1];
                    p7 = p7 - 4;
                    p5 = p8;
                } while (p7 != param_1);
            }
            *p7 = u4; p7[1] = u1; p7[2] = u3; p7[3] = u2;
        }
    }
}

// @ 0x008d3820
void FUN_008d3820(unsigned* param_1, unsigned* param_2)
{
    unsigned u1, u2, u3, u4;
    unsigned *p5, *p6, *p7;
    bool b;
    unsigned short us;
    for (; param_1 != param_2; param_1 = param_1 + 4) {
        u1 = param_1[1]; u2 = param_1[2]; u3 = param_1[3]; u4 = *param_1;
        us = (unsigned short)(u2 >> 0x10);
        p7 = param_1;
        p5 = param_1;
        while (true) {
            p6 = p5 - 4;
            b = u4 < *p6;
            if (u4 == *p6) {
                b = *(unsigned short*)((int)p5 - 6) <= us;
                if (us == *(unsigned short*)((int)p5 - 6)) {
                    if ((unsigned short)u2 == (unsigned short)p5[-2])
                        b = u1 < p5[-3];
                    else
                        b = (unsigned short)p5[-2] < (unsigned short)u2;
                }
            }
            if (!b) break;
            *p7 = *p6; p7[1] = p5[-3]; p7[2] = p5[-2]; p7[3] = p5[-1];
            p7 = p7 - 4;
            p5 = p6;
        }
        *p7 = u4; p7[1] = u1; p7[2] = u2; p7[3] = u3;
    }
}

// @ 0x008d38d0
unsigned* FUN_008d38d0(unsigned* param_1, unsigned* param_2, unsigned* param_3)
{
    unsigned u1, u2, u3;
    bool b;
    u1 = *param_1;
    u2 = *param_2;
    b = u1 < u2;
    if (u1 == u2) {
        b = *(unsigned short*)((int)param_2 + 10) <= *(unsigned short*)((int)param_1 + 10);
        if (*(unsigned short*)((int)param_1 + 10) == *(unsigned short*)((int)param_2 + 10)) {
            b = (unsigned short)param_2[2] <= (unsigned short)param_1[2];
            if ((unsigned short)param_1[2] == (unsigned short)param_2[2])
                b = param_1[1] < param_2[1];
        }
    }
    u3 = *param_3;
    if (b) {
        b = u2 < u3;
        if (u2 == u3) {
            b = *(unsigned short*)((int)param_3 + 10) <= *(unsigned short*)((int)param_2 + 10);
            if (*(unsigned short*)((int)param_2 + 10) == *(unsigned short*)((int)param_3 + 10)) {
                b = (unsigned short)param_3[2] <= (unsigned short)param_2[2];
                if ((unsigned short)param_2[2] == (unsigned short)param_3[2])
                    b = param_2[1] < param_3[1];
            }
        }
        if (!b) {
            b = u1 < u3;
            if (u1 == u3) {
                b = *(unsigned short*)((int)param_3 + 10) <= *(unsigned short*)((int)param_1 + 10);
                if (*(unsigned short*)((int)param_1 + 10) == *(unsigned short*)((int)param_3 + 10)) {
                    b = (unsigned short)param_3[2] <= (unsigned short)param_1[2];
                    if ((unsigned short)param_1[2] == (unsigned short)param_3[2])
                        b = param_1[1] < param_3[1];
                }
            }
            if (!b) return param_1;
            return param_3;
        }
    } else {
        b = u1 < u3;
        if (u1 == u3) {
            b = *(unsigned short*)((int)param_3 + 10) <= *(unsigned short*)((int)param_1 + 10);
            if (*(unsigned short*)((int)param_1 + 10) == *(unsigned short*)((int)param_3 + 10)) {
                b = (unsigned short)param_3[2] <= (unsigned short)param_1[2];
                if ((unsigned short)param_1[2] == (unsigned short)param_3[2])
                    b = param_1[1] < param_3[1];
            }
        }
        if (b) return param_1;
        b = *param_2 < u3;
        if (*param_2 == u3) {
            b = *(unsigned short*)((int)param_3 + 10) <= *(unsigned short*)((int)param_2 + 10);
            if (*(unsigned short*)((int)param_2 + 10) == *(unsigned short*)((int)param_3 + 10)) {
                b = (unsigned short)param_3[2] <= (unsigned short)param_2[2];
                if ((unsigned short)param_2[2] == (unsigned short)param_3[2])
                    b = param_2[1] < param_3[1];
            }
        }
        if (b) return param_3;
    }
    return param_2;
}

// @ 0x008d3a10
void FUN_008d3a10(int param_1, int param_2, int param_3, unsigned param_4, unsigned param_5,
                  unsigned param_6, unsigned param_7, unsigned param_8)
{
    unsigned u;
    int i4, i6;
    unsigned* p;
    bool b;
    (void)param_8;
    while (param_2 < param_3) {
        i6 = (param_3 - 1) >> 1;
        i4 = i6 * 0x10;
        u = *(unsigned*)(i4 + param_1);
        p = (unsigned*)(i4 + param_1);
        b = u < param_4;
        if (u == param_4) {
            b = (unsigned short)(param_6 >> 0x10) <= *(unsigned short*)((int)p + 10);
            if (*(unsigned short*)((int)p + 10) == (unsigned short)(param_6 >> 0x10)) {
                b = (unsigned short)param_6 <= (unsigned short)p[2];
                if ((unsigned short)p[2] == (unsigned short)param_6)
                    b = p[1] < param_5;
            }
        }
        if (!b) break;
        *(unsigned*)(param_3 * 0x10 + param_1) = p[0];
        *(unsigned*)(param_3 * 0x10 + param_1 + 4) = p[1];
        *(unsigned*)(param_3 * 0x10 + param_1 + 8) = p[2];
        *(unsigned*)(param_3 * 0x10 + param_1 + 0xc) = p[3];
        param_3 = i6;
    }
    p = (unsigned*)(param_3 * 0x10 + param_1);
    p[0] = param_4; p[1] = param_5; p[2] = param_6; p[3] = param_7;
}

// @ 0x008d3ad0
int TSI::FUN_008d3ad0(int param_2)
{
    return param_2 * 0x10 + M(4);
}

// @ 0x008d3ae0
int TSI::FUN_008d3ae0(int param_2)
{
    int p = M(4);
    while (true) {
        if (p == M(8))
            return 0;
        if (*(int*)(p + 4) == param_2) break;
        p = p + 0x10;
    }
    return p;
}

// @ 0x008d3b10
void TSI::FUN_008d3b10(int* param_2)
{
    TSI* self = this;
    unsigned u;
    int* p;
    p = (int*)*(int*)self->data;
    u = 0;
    do {
        if (p == (int*)self) {
        L_done:
            if (0 < MU(0x388)) {
                p = (int*)(self->data + 8);
                do {
                    if ((int*)*p == param_2)
                        ((TSI*)p)->FUN_008d35d0(0x5ece0002);
                    else {
                        u = u + 1;
                        p = p + 7;
                    }
                } while (u < MU(0x388));
            }
            return;
        }
        if (p == param_2) {
            p = (int*)param_2[1];
            int i1 = *param_2;
            *p = i1;
            *(int**)(i1 + 4) = p;
            *param_2 = 0;
            param_2[1] = 0;
            goto L_done;
        }
        p = (int*)*p;
    } while (true);
}

// @ 0x008d3b70
void FUN_008d3b70(int param_1, int param_2, int param_3, int param_4, unsigned param_5,
                  unsigned param_6, unsigned param_7, unsigned param_8, int param_9)
{
    unsigned u;
    int i2, i3, i4, i6;
    unsigned* p;
    bool b;
    while (true) {
        i4 = param_4 * 2;
        i6 = i4 + 2;
        if (param_3 <= i6) break;
        i2 = i6 * 0x10;
        u = *(unsigned*)(i2 - 0x10 + param_1);
        i3 = i2 + param_1;
        b = *(unsigned*)(i2 + param_1) < u;
        if (*(unsigned*)(i2 + param_1) == u) {
            b = *(unsigned short*)(i3 - 6) <= *(unsigned short*)(i3 + 10);
            if (*(unsigned short*)(i3 + 10) == *(unsigned short*)(i3 - 6)) {
                b = *(unsigned short*)(i3 - 8) <= *(unsigned short*)(i3 + 8);
                if (*(unsigned short*)(i3 + 8) == *(unsigned short*)(i3 - 8))
                    b = *(unsigned*)(i3 + 4) < *(unsigned*)(i3 - 0xc);
            }
        }
        if (b) i6 = i4 + 1;
        i4 = i6 * 0x10 + param_1;
        p = (unsigned*)(param_4 * 0x10 + param_1);
        p[0] = *(unsigned*)(i6 * 0x10 + param_1);
        p[1] = *(unsigned*)(i4 + 4);
        p[2] = *(unsigned*)(i4 + 8);
        p[3] = *(unsigned*)(i4 + 0xc);
        param_4 = i6;
    }
    if (i6 == param_3) {
        p = (unsigned*)(i6 * 0x10 - 0x10 + param_1);
        *(unsigned*)(param_4 * 0x10 + param_1) = p[0];
        i6 = param_4 * 0x10 + param_1;
        *(unsigned*)(i6 + 4) = p[1];
        *(unsigned*)(i6 + 8) = p[2];
        *(unsigned*)(i6 + 0xc) = p[3];
        param_4 = i4 + 1;
    }
    FUN_008d3a10(param_1, param_2, param_4, param_5, param_6, param_7, param_8, (unsigned)param_9);
}

// @ 0x008d3c60
void FUN_008d3c60(int* param_1, int param_2)
{
    param_1[0] = (int)&PTR_FUN_01435990;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = param_2;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[9] = param_2;
    param_1[10] = 0;
    *(char*)(param_1 + 0xb) = 0;
}

// @ 0x008d3ca0
void FUN_008d3ca0(int* param_1)
{
    int i;
    param_1[0] = (int)&PTR_FUN_01435990;
    i = param_1[6];
    if (i != 0)
        ((void(*)(int, int))*(int*)(*(int*)param_1[9] + 0xc))(
            i, ((param_1[8] - i) / 0x14) * 0x14);
    i = param_1[1];
    if (i != 0)
        ((void(*)(int, int))*(int*)(*(int*)param_1[4] + 0xc))(
            i, (param_1[3] - i >> 4) << 4);
    param_1[0] = (int)&PTR_FUN_01435980;
}

// @ 0x008d3d30
unsigned TSI::FUN_008d3d30(int param_2, int param_3)
{
    int* p1;
    int* p2;
    unsigned u;
    int* p4;
    p1 = *(int**)(data + 0x18);
    while (true) {
        if (p1 == *(int**)(data + 0x1c))
            return 0;
        if (*p1 == param_2) break;
        p1 = p1 + 5;
    }
    u = 0;
    p4 = p1;
    do {
        p4 = p4 + 1;
        if (*p4 != 0) {
            p1 = 0;
            if (*(int**)(param_3 + 0x388) == 0)
            L_zero:
                return 0;
            p2 = (int*)(param_3 + 0xc);
            while (*p2 != *p4) {
                p1 = (int*)((int)p1 + 1);
                p2 = p2 + 7;
                if (*(int**)(param_3 + 0x388) <= p1) goto L_zero;
            }
        }
        u = u + 1;
        if (3 < u)
            return 1;
    } while (true);
}

// @ 0x008d3da0
void __fastcall FUN_008d3da0v(int self)
{
    int p = self;
    *(int*)(p + 4) = p;
    *(int*)(p + 0) = p;
    *(int*)(p + 0x388) = 0;
    *(char*)(p + 0x38c) = 1;
}

// @ 0x008d3dc0
int* TSI::FUN_008d3dc0(int param_2, int* param_3, int param_4, int param_5, int param_6)
{
    int* p;
    int* p1;
    int i1, i2;
    p1 = (int*)(void*)this;      // param_1
    p = (int*)*(int*)p1;             // piVar1 = *param_1
    while (true) {
        if (p1 == p) return 0;
        i1 = p1[1];
        if (*(int*)(i1 + 0xc) != 0) {
            i2 = ((int(*)(int, int, int))*(int*)(*(int*)(i1 + 0xc) + 4))(param_2, param_4, param_5);
            *param_3 = i2;
            if (i2 != 0) return (int*)i1;
        }
        if ((*(unsigned char*)(i1 + 0x18) & 1) != 0) break;
        p1 = (int*)p1[1];
    }
    (void)param_6;
    return 0;
}

// @ 0x008d3e30
void TSI::FUN_008d3e30(int* param_2, unsigned param_3)
{
    int* p1;
    char* p5;
    int i4;
    int i6;
    int* p7;
    int* p8;
    unsigned u9;
    int local_24;
    int local_20;
    int local_1c;
    char local_18;
    if ((char)param_3 == '\0') {
        i4 = FUN_008d3530(param_2[3], (int)(char)param_2[5], (int)*(char*)((int)param_2 + 0x15));
        if (i4 != 0) {
            ((TSI*)i4)->FUN_008d3690(param_2);
            return;
        }
    } else if (MU(0x388) < 0x20) {
        local_24 = param_2[2];
        i4 = *param_2;
        local_20 = param_2[1];
        param_3 = (unsigned)*(unsigned short*)((int)param_2 + 0x16);
        if (i4 == 0 || local_20 == 0) {
            i4 = (int)this->FUN_008d3dc0(local_20, &local_1c, local_24, 0, 0);
        }
        if (i4 != 0 && *(int*)(i4 + 0x10) != 0) {
            p1 = (int*)(data + M(0x388) * 0x1c + 8);
            p7 = param_2;
            p8 = p1;
            for (i6 = 7; i6 != 0; i6 = i6 + -1) {
                *p8 = *p7;
                p7 = p7 + 1;
                p8 = p8 + 1;
            }
            *(unsigned short*)(p1 + 6) = 0;
            u9 = 0;
            p5 = data;
            if (M(0x388) != 0) {
                do {
                    char* nx = p5 + 0x1c;
                    if (param_2[3] == *(int*)(p5 + 0x14) && (char)param_2[5] == *nx &&
                        *(char*)((int)param_2 + 0x15) == p5[0x1d])
                        return;
                    if (*(int*)(p5 + 0xc) == local_20 && *(int*)(p5 + 8) == i4 &&
                        *nx == (char)param_2[5] && p5[0x1d] == *(char*)((int)param_2 + 0x15))
                        *(unsigned short*)(p1 + 6) = 1;
                    u9 = u9 + 1;
                    p5 = nx;
                } while (u9 < MU(0x388));
            }
            *p1 = i4;
            p1[1] = local_20;
            p1[2] = local_24;
            *(unsigned short*)((int)p1 + 0x16) = (unsigned short)param_3;
            if ((param_3 & 0x800) != 0)
                p1[4] = p1[4] ^ 0x80000000;
            M(0x388) = M(0x388) + 1;
            if ((param_3 & 0x2000) == 0)
                ((void(*)(int, int*, int))*(int*)(i4 + 0x10))(0x5ece0000, p1, *(int*)(i4 + 0x14));
            if (local_24 != 0 && (param_3 & 0x1000) == 0) {
                char c = ((char(*)(int, void*))*(int*)(*(int*)(i4 + 0xc) + 0xc))(
                    local_24, (void*)this);
                if (c != '\0') {
                    local_24 = 0;
                    local_20 = 0;
                    local_1c = 0;
                    local_18 = 0;
                    this->FUN_008d3e30((int*)&local_24, 1);
                }
            }
        }
    }
    (void)local_18;
}

// @ 0x008d4040
void FUN_008d4040(int* param_1, int* param_2, int* param_3, int param_4)
{
    int* p;
    int i2, i3, i4;
    i2 = 0;
    for (p = param_2; p != param_3; p = (int*)*p)
        i2 = i2 + 1;
    if (0 < i2) {
        do {
            i3 = i2 >> 1;
            i4 = i3;
            p = param_2;
            if (i3 < 0) {
                i4 = -i3;
                do {
                    i4 = i4 - 1;
                    p = (int*)p[1];
                } while (i4 != 0);
            } else {
                for (; i4 != 0; i4 = i4 - 1)
                    p = (int*)*p;
            }
            if (p[2] <= *(int*)(param_4 + 8)) {
                param_2 = (int*)*p;
                i3 = i2 + (-1 - i3);
            }
            i2 = i3;
        } while (0 < i3);
    }
    *param_1 = (int)param_2;
}

// @ 0x008d40b0
void FUN_008d40b0(int param_1, int param_2, int param_3)
{
    int i1, i2, i3;
    i1 = param_2 - param_1 >> 4;
    if (2 <= i1) {
        i3 = (i1 - 2 >> 1) + 1;
        i2 = i3 * 0x10 + param_1;
        do {
            i3 = i3 - 1;
            FUN_008d3b70(param_1, i3, i1, i3,
                         *(unsigned*)(i2 - 0x10), *(unsigned*)(i2 - 0xc),
                         *(unsigned*)(i2 - 8), *(unsigned*)(i2 - 4), param_3);
            i2 = i2 - 0x10;
        } while (i3 != 0);
    }
}

// @ 0x008d4110
void FUN_008d4110(unsigned* param_1, int param_2, int param_3)
{
    unsigned u1, u2, u3, u4;
    int i5;
    unsigned* p6;
    i5 = param_2 - (int)param_1 >> 4;
    if (1 < i5) {
        p6 = (unsigned*)(param_2 - 0x10);
        do {
            u1 = p6[3]; u2 = p6[0]; u3 = p6[1]; u4 = p6[2];
            p6[0] = param_1[0]; p6[1] = param_1[1]; p6[2] = param_1[2]; p6[3] = param_1[3];
            FUN_008d3b70((int)param_1, 0, i5 - 1, 0, u2, u3, u4, u1, param_3);
            p6 = p6 - 4;
            i5 = (0x10 - (int)param_1) + (int)p6 >> 4;
        } while (1 < i5);
    }
}

// @ 0x008d41b0
void TSI::FUN_008d41b0(int* param_2)
{
    int* p1;
    int i2;
    unsigned u3;
    int* p4;
    int local_4;
    int local_8;
    p1 = param_2;
    FUN_008d4040((int*)&param_2, (int*)*(int*)data, (int*)this, (int)param_2);
    p4 = (int*)param_2[1];
    param_2[1] = (int)p1;
    *p4 = (int)p1;
    u3 = 0;
    p1[1] = (int)p4;
    *p1 = (int)param_2;
    if (M(0xe2 * 4) != 0) {
        p4 = (int*)(data + 8);
        do {
            i2 = (int)this->FUN_008d3dc0(0, (int*)&param_2, local_8, local_4, 0);
            if (*p4 == i2 && (int*)p4[1] == param_2) {
                u3 = u3 + 1;
                p4 = p4 + 7;
            } else {
                ((TSI*)p4)->FUN_008d35d0(0x5ece0002);
            }
        } while (u3 < MU(0x388));
    }
}

// @ 0x008d4250
void FUN_008d4250(unsigned* param_1, unsigned* param_2, unsigned param_3, unsigned param_4,
                 unsigned param_5)
{
    unsigned u1, u2, u3, u4;
    unsigned* p5;
    unsigned short u6;
    bool b;
    while (true) {
        while (true) {
            b = *param_1 < param_3;
            u6 = (unsigned short)param_5;
            if (*param_1 == param_3) {
                b = (unsigned short)(param_5 >> 0x10) <= *(unsigned short*)((int)param_1 + 10);
                if (*(unsigned short*)((int)param_1 + 10) == (unsigned short)(param_5 >> 0x10)) {
                    b = u6 <= (unsigned short)param_1[2];
                    if ((unsigned short)param_1[2] == u6)
                        b = param_1[1] < param_4;
                }
            }
            if (!b) break;
            param_1 = param_1 + 4;
        }
        do {
            p5 = param_2;
            param_2 = p5 - 4;
            b = param_3 < p5[-4];
            if (param_3 == p5[-4]) {
                b = *(unsigned short*)((int)p5 - 6) <= (unsigned short)(param_5 >> 0x10);
                if ((unsigned short)(param_5 >> 0x10) == *(unsigned short*)((int)p5 - 6)) {
                    if (u6 == (unsigned short)p5[-2])
                        b = param_4 < p5[-3];
                    else
                        b = (unsigned short)p5[-2] < u6;
                }
            }
        } while (b);
        if (param_2 <= param_1) break;
        u1 = *param_1; u2 = param_1[1]; u3 = param_1[2]; u4 = param_1[3];
        *param_1 = *param_2;
        param_1[1] = p5[-3]; param_1[2] = p5[-2]; param_1[3] = p5[-1];
        *param_2 = u1;
        p5[-3] = u2; p5[-2] = u3; p5[-1] = u4;
        param_1 = param_1 + 4;
    }
}

// @ 0x008d4320
void FUN_008d4320(unsigned* param_1, unsigned* param_2, unsigned* param_3, int param_4)
{
    unsigned u1, u2, u3, u4;
    unsigned* p5;
    bool b;
    FUN_008d40b0((int)param_1, (int)param_2, param_4);
    for (p5 = param_2; p5 < param_3; p5 = p5 + 4) {
        b = *p5 < *param_1;
        if (*p5 == *param_1) {
            b = *(unsigned short*)((int)param_1 + 10) <= *(unsigned short*)((int)p5 + 10);
            if (*(unsigned short*)((int)p5 + 10) == *(unsigned short*)((int)param_1 + 10)) {
                b = (unsigned short)param_1[2] <= (unsigned short)p5[2];
                if ((unsigned short)p5[2] == (unsigned short)param_1[2])
                    b = p5[1] < param_1[1];
            }
        }
        if (b) {
            u1 = *p5; u2 = p5[1]; u3 = p5[2]; u4 = p5[3];
            *p5 = *param_1;
            p5[1] = param_1[1]; p5[2] = param_1[2]; p5[3] = param_1[3];
            FUN_008d3b70((int)param_1, 0, ((int)param_2 - (int)param_1) >> 4, 0, u1, u2, u3, u4,
                         param_4);
        }
    }
    FUN_008d4110(param_1, (int)param_2, param_4);
}

// @ 0x008d4400
void TSI::FUN_008d4400(int* param_2, int* param_3)
{
    int* p4;
    int i1, i2, i3, i5;
    p4 = (int*)M(4);
    if (p4 != (int*)M(8)) {
        if (param_2 <= param_3 && param_3 < p4)
            param_3 = param_3 + 4;
        if (p4 != 0) {
            p4[0] = p4[-4]; p4[1] = p4[-3]; p4[2] = p4[-2]; p4[3] = p4[-1];
        }
        FUN_00edba80(param_2, (void*)(M(4) - 0x10), (void*)M(4));
        param_2[0] = param_3[0]; param_2[1] = param_3[1];
        param_2[2] = param_3[2]; param_2[3] = param_3[3];
        M(4) = M(4) + 0x10;
        return;
    }
    i2 = (int)p4 - M(0) >> 4;
    if (i2 == 0) {
        i2 = 1;
    } else {
        i2 = i2 * 2;
        if (i2 == 0) { i3 = 0; goto L_opt; }
    }
    i3 = ((int(*)(int, int, int))*(int*)(*(int*)M(0xc) + 8))(i2 << 4, 0, M(0x10));
L_opt:
    p4 = (int*)FUN_00c7ea30(M(0), (int)param_2, i3);
    if (p4 != 0) {
        p4[0] = param_3[0]; p4[1] = param_3[1]; p4[2] = param_3[2]; p4[3] = param_3[3];
    }
    i5 = FUN_00c7ea30((int)param_2, M(4), (int)(p4 + 4));
    i1 = M(0);
    if (i1 != 0)
        ((void(*)(int, int))*(int*)(*(int*)M(0xc) + 0xc))(i1, (M(8) - i1 >> 4) << 4);
    M(4) = i5;
    M(8) = i2 * 0x10 + i3;
    M(0) = i3;
}
