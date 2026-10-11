// Slice s00a7f2e0 -- EA::Swarm collision/effect template helpers.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------------------
// external helpers
extern "C" void  operator_delete__(void* p);
extern "C" void* operator_new(int size, const char* tag, int a, int b, const char* file, int line);

extern "C" void* FUN_00a7d5e0(void* a, void* b, void* c);
extern "C" void  FUN_00a7d640(void* a, void* b, void* c);
extern "C" void  FUN_00a7eb60(void* a, void* b, void* c);

extern "C" void  FUN_0093a780(void* s, void* buf, int n, int pad);
extern "C" void  FUN_0093a800(void* s, void* buf, int n, int pad);
extern "C" void  FUN_007ed920(void* s, void* dst);
extern "C" void* FUN_00539440(void* a, void* b);   // EA::Swarm::normalized

// data globals referenced by literal address
extern float DAT_0167764c;
extern float DAT_01677650;
extern float DAT_01677654;
extern const float DAT_016776f8[];    // 9-float matrix source
extern unsigned int DAT_01564c98;
extern const float DAT_01485720;      // 1.0f
extern unsigned char DAT_016778dc[];  // RandomLinearCongruential instance

// ---------------------------------------------------------------------------
// element copy/destroy helpers (thiscall in the original).  Modeled as methods
// so the compiler places the destination in ecx.
struct ElemOps {
    void FUN_00a7d540(void* src);   // copy-construct (dst = this)
    void FUN_00a7d580(void* src);   // construct from value
};

// factory used by FUN_00a7f470 (thiscall: this in ecx)
struct IFactory {
    void* FUN_00a71410(int a, int b, int c);
};

// 4-byte element vector used by FUN_00a7f470
struct PVec {
    void** begin;
    void** end;
    void** cap;
    void FUN_00a0a360(void** e, void* v);   // thiscall append
};

// 0x18-byte element record / vector
struct Elem6 {
    void* obj;    // +0
    char* par;    // +4
    int   a;      // +8
    int   b;      // +0xc
    int   c;      // +0x10
    int   d;      // +0x14
};
struct ElemVec {
    Elem6* begin;
    Elem6* end;
};
struct Vec24 {
    char* begin;
    char* end;
    char* cap;
    void FUN_00a7f2e0(char* pos, char* val);   // thiscall insert
};

// object interfaces (virtual slot comments give the byte offset)
struct IObjA {
    virtual void v00();          // 0x00 (AddRef)
    virtual void v04();          // 0x04 (Release)
    virtual void v08(int);       // 0x08
    virtual void v0c();          // 0x0c
    virtual void v10();          // 0x10
    virtual void v14(void*);     // 0x14
    virtual void v18(void*);     // 0x18
    virtual void v1c();          // 0x1c
    virtual void v20();          // 0x20
    virtual void v24();          // 0x24
    virtual void v28();          // 0x28
    virtual void v2c();          // 0x2c
    virtual void v30(void*);     // 0x30
};

struct IObjB {
    virtual void  b00();         // 0x00
    virtual void  b04();         // 0x04
    virtual char  v08(float, void*, void*, float*, int, int);   // 0x08
    virtual float v0c(void*, int, int);                          // 0x0c
    virtual char  v10(void*, void*, float*, int, int, int);      // 0x10
    virtual void  v14(void*, void*, float*, int, int, int);      // 0x14
};

struct IObjC {
    virtual void   c00();        // 0x00 (Release at +0)
    virtual void   c04();        // 0x04 (AddRef)
    virtual void   c08();        // 0x08
    virtual void   c0c();        // 0x0c
    virtual void   c10();        // 0x10
    virtual void   c14();        // 0x14
    virtual void   c18();        // 0x18
    virtual int    v1c();        // 0x1c
    virtual void   c20();        // 0x20
    virtual void   c24();        // 0x24
    virtual int    v28();        // 0x28
    virtual void   c2c();        // 0x2c
    virtual void   c30();        // 0x30
    virtual void   c34();        // 0x34
    virtual void   c38();        // 0x38
    virtual void   c3c();        // 0x3c
    virtual void   c40();        // 0x40
    virtual void   c44();        // 0x44
    virtual void   c48();        // 0x48
    virtual void   c4c();        // 0x4c
    virtual void   c50();        // 0x50
    virtual void   c54();        // 0x54
    virtual void   c58();        // 0x58
    virtual void   c5c();        // 0x5c
    virtual void   c60();        // 0x60
    virtual void   c64();        // 0x64
    virtual void   c68();        // 0x68
    virtual void   c6c();        // 0x6c
    virtual void   c70();        // 0x70
    virtual void   c74();        // 0x74
    virtual void   c78();        // 0x78
    virtual IObjC* v7c(int, int); // 0x7c
};

struct RandomLCG {
    float FUN_009360d0();        // RandomDoubleUniform (thiscall)
};

// Matrix33::Assign (thiscall) at 0x0041cb40
struct Matrix33 {
    float m[9];
    void  FUN_0041cb40(const void* rhs);
};

// configuration block passed to IObjA::v18 by FUN_00a7f470
struct Cfg {
    unsigned short flags;      // +0x00
    unsigned short count;      // +0x02
    float f4;                  // +0x04
    float f8;                  // +0x08
    float fc;                  // +0x0c
    float f10;                 // +0x10
    float f14;                 // +0x14
    float mat[9];              // +0x18
};

// ===========================================================================
// @ 0x00a7f2e0
void Vec24::FUN_00a7f2e0(char* pos, char* val)
{
    char* end = this->end;
    if (end != this->cap) {
        if (!(val < pos) && val < end)
            val = val + 0x18;
        if (end != 0)
            ((ElemOps*)end)->FUN_00a7d540(end - 0x18);
        FUN_00a7d640(pos, this->end - 0x18, this->end);
        ((ElemOps*)pos)->FUN_00a7d580(val);
        this->end = this->end + 0x18;
        return;
    }

    int n = (int)((end - this->begin) / 0x18);
    char* buf;
    if (n == 0) {
        n = 1;
    } else {
        n *= 2;
    }
    if (n == 0) {
        buf = 0;
    } else {
        buf = (char*)operator_new(n * 0x18, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }

    char* begin = this->begin;
    char* iVar3 = (char*)FUN_00a7d5e0(begin, pos, buf);
    FUN_00a7eb60(begin, pos, buf);
    if (iVar3 != 0)
        ((ElemOps*)iVar3)->FUN_00a7d540(val);
    char* e2 = this->end;
    char* iVar4 = (char*)FUN_00a7d5e0(pos, e2, iVar3 + 0x18);
    FUN_00a7eb60(pos, e2, iVar3 + 0x18);
    char* old = this->begin;
    if (old != 0 && *(int*)(old - 4) != 0)
        operator_delete__(old);
    this->end = iVar4;
    this->begin = buf;
    this->cap = buf + n * 0x18;
}

// ===========================================================================
// @ 0x00a7f470
void __cdecl FUN_00a7f470(int A1, int A2, IFactory* A3, void* A4p, int A5,
                           PVec* A6, int A7, int A8)
{
    float* A4 = (float*)A4p;
    IObjA* obj = (IObjA*)A3->FUN_00a71410(A2, A1, A8);
    if (obj != 0) {
        obj->v00();

        Cfg cfg;
        cfg.f4    = DAT_0167764c;
        cfg.f8    = DAT_01677650;
        cfg.count = 0;
        cfg.fc    = DAT_01677654;
        cfg.flags = 0;
        cfg.f14   = DAT_01485720;
        ((Matrix33*)cfg.mat)->FUN_0041cb40(DAT_016776f8);

        cfg.flags = (unsigned short)(cfg.flags | 4);
        cfg.count = (unsigned short)(cfg.count + 1);
        cfg.f4 = A4[0];
        cfg.f8 = A4[1];
        cfg.fc = A4[2];

        obj->v18(&cfg);
        if (A7 != 0)
            obj->v14((void*)A7);
        obj->v30((void*)A5);
        obj->v08(0);

        if (A6 != 0) {
            void** e = A6->end;
            if (e < A6->cap) {
                A6->end = e + 1;
                if (e != 0) {
                    *e = obj;
                    obj->v00();
                }
            } else {
                A6->FUN_00a0a360(e, &obj);
            }
        }

        if (obj != 0)
            obj->v04();
    }
}

// ===========================================================================
// @ 0x00a7f5a0
char __cdecl FUN_00a7f5a0(int param_1, int param_2, ElemVec* pvec, int param_4,
                         float param_5, char* param_6, char* param_7, float* param_8,
                         int param_9, int param_10, int param_11)
{
    Elem6* p = pvec->begin;
    if (p != pvec->end) {
        do {
            int iVar4 = (p->a == 0) ? 0 : p->b + param_4;
            unsigned int uVar1 = *(unsigned int*)p->par;
            float vec[3];
            char auStack_c[12];

            if ((uVar1 >> 1 & 1) == 0) {
                if ((uVar1 >> 2 & 1) == 0) {
                    if ((uVar1 & 1) == 0) {
                        if ((uVar1 >> 4 & 1) != 0) {
                            float fv = ((IObjB*)p->obj)->v0c(param_7, 0, 0);
                            if (fv < *(float*)(p->par + 0x18))
                                ((IObjB*)p->obj)->v10(param_7, auStack_c, vec, 0, iVar4, 0);
                        }
                    } else {
                        char cVar2 = ((IObjB*)p->obj)->v08(
                            (float)(*(unsigned int*)(p->par + 0x18)) * param_5,
                            param_6, param_7, vec, iVar4, 0);
                        if (cVar2 != 0) {
                            float fVar7 = *(float*)(p->par + 0x1c);
                            if (fVar7 != 0.0f &&
                                (fVar7 == 1.0f ||
                                 ((RandomLCG*)DAT_016778dc)->FUN_009360d0() <= fVar7)) {
                                if (-1 < *(int*)(p->par + 0x3c))
                                    FUN_00a7f470(param_1, *(int*)(p->par + 0x3c), (IFactory*)param_2,
                                                 param_7, param_9, (PVec*)0, param_10, param_11);
                                return 0;
                            }
                            if (-1 < *(int*)(p->par + 0x38))
                                FUN_00a7f470(param_1, *(int*)(p->par + 0x38), (IFactory*)param_2,
                                             param_7, param_9, (PVec*)0, param_10, param_11);

                            float fSlide = param_8[2] * vec[2] + param_8[1] * vec[1] + *param_8 * vec[0];
                            float fStack_10 = vec[2] * fSlide;
                            float fVar9 = *(float*)(p->par + 0x10) + 1.0f;
                            float fVar8 = 1.0f - *(float*)(p->par + 0x14);
                            param_8[0] = param_8[0] - ((vec[0] * fSlide) * fVar9 + (*param_8 - vec[0] * fSlide) * fVar8);
                            param_8[1] = param_8[1] - ((vec[1] * fSlide) * fVar9 + (param_8[1] - vec[1] * fSlide) * fVar8);
                            param_8[2] = param_8[2] - (fStack_10 * fVar9 + (param_8[2] - fStack_10) * fVar8);
                        }
                    }
                } else {
                    ((IObjB*)p->obj)->v14(param_6, param_7, param_8, 0, iVar4, 0);
                }
            } else {
                char cVar2 = ((IObjB*)p->obj)->v10(param_7, param_7, vec, 0, iVar4, 0);
                if (cVar2 != 0) {
                    float fVar7 = -((param_8[2] * vec[2] + param_8[1] * vec[1]) + *param_8 * vec[0]);
                    if (0.0f < fVar7) {
                        param_8[0] = param_8[0] + vec[0] * fVar7;
                        param_8[1] = param_8[1] + vec[1] * fVar7;
                        param_8[2] = param_8[2] + vec[2] * fVar7;
                    }
                }
            }
            p = p + 1;
        } while (p != pvec->end);
    }
    return 1;
}

// ===========================================================================
// @ 0x00a7f8d0
char __cdecl FUN_00a7f8d0(int param_1, int param_2, ElemVec* pvec, int param_4,
                         int param_5, float param_6, char* param_7, char* param_8,
                         float* param_9, int param_10, int param_11, int param_12,
                         int param_13, int param_14)
{
    Elem6* p = pvec->begin;
    if (p != pvec->end) {
        do {
            int iVar5 = (p->a == 0) ? 0 : p->b + param_4;
            int iVar3 = (p->c == 0) ? 0 : p->d + param_5;
            unsigned int uVar1 = *(unsigned int*)p->par;
            float vec[3];
            char auStack_c[12];

            if ((uVar1 >> 1 & 1) == 0) {
                if ((uVar1 >> 2 & 1) == 0) {
                    if ((uVar1 & 1) == 0) {
                        if ((uVar1 >> 4 & 1) == 0 && (uVar1 >> 5 & 1) != 0)
                            ((IObjB*)p->obj)->v10(param_8, auStack_c, vec, param_10, iVar5, iVar3);
                    } else {
                        char cVar2 = ((IObjB*)p->obj)->v08(
                            (float)(*(unsigned int*)(p->par + 0x18)) * param_6,
                            param_7, param_8, vec, iVar5, iVar3);
                        if (cVar2 != 0) {
                            float fVar8 = *(float*)(p->par + 0x1c);
                            if (fVar8 != 0.0f &&
                                (fVar8 == 1.0f ||
                                 ((RandomLCG*)DAT_016778dc)->FUN_009360d0() <= fVar8)) {
                                if (-1 < *(int*)(p->par + 0x3c))
                                    FUN_00a7f470(param_1, *(int*)(p->par + 0x3c), (IFactory*)param_2,
                                                 param_8, param_11, (PVec*)param_12, param_13, param_14);
                                return 0;
                            }
                            if (-1 < *(int*)(p->par + 0x38))
                                FUN_00a7f470(param_1, *(int*)(p->par + 0x38), (IFactory*)param_2,
                                             param_8, param_11, (PVec*)param_12, param_13, param_14);

                            float fSlide = param_9[2] * vec[2] + param_9[1] * vec[1] + *param_9 * vec[0];
                            float fStack_10 = vec[2] * fSlide;
                            float fVar10 = *(float*)(p->par + 0x10) + 1.0f;
                            float fVar9 = 1.0f - *(float*)(p->par + 0x14);
                            param_9[0] = param_9[0] - ((vec[0] * fSlide) * fVar10 + (*param_9 - vec[0] * fSlide) * fVar9);
                            param_9[1] = param_9[1] - ((vec[1] * fSlide) * fVar10 + (param_9[1] - vec[1] * fSlide) * fVar9);
                            param_9[2] = param_9[2] - (fStack_10 * fVar10 + (param_9[2] - fStack_10) * fVar9);
                        }
                    }
                } else {
                    ((IObjB*)p->obj)->v14(param_7, param_8, param_9, param_10, iVar5, iVar3);
                }
            } else {
                char cVar2 = ((IObjB*)p->obj)->v10(param_8, param_8, vec, param_10, iVar5, iVar3);
                if (cVar2 != 0) {
                    float fVar8 = -((param_9[2] * vec[2] + param_9[1] * vec[1]) + *param_9 * vec[0]);
                    if (0.0f < fVar8) {
                        param_9[0] = param_9[0] + vec[0] * fVar8;
                        param_9[1] = param_9[1] + vec[1] * fVar8;
                        param_9[2] = param_9[2] + vec[2] * fVar8;
                    }
                }
            }
            p = p + 1;
        } while (p != pvec->end);
    }
    return 1;
}

// ===========================================================================
// @ 0x00a7fc10
// source vector elements are 0x58 bytes; fields at +8/+0xc are the two ints
// passed to v7c.  Output vector holds 0x18-byte Elem6 records.
struct Src58 {
    char pad[8];
    int  k8;     // +8
    int  kc;     // +0xc
};

void __cdecl FUN_00a7fc10(IObjC* param_1, Src58** param_2, Vec24* param_3,
                          int* param_4, int* param_5, char* param_6)
{
    IObjC* cur = 0;
    IObjC* local18 = 0;
    if (param_6 != 0)
        *param_6 = 0;

    Src58* p = *param_2;
    if (p != (Src58*)param_2[1]) {
        do {
            IObjC* nw = param_1->v7c(p->k8, p->kc);
            if (nw != cur) {
                if (nw != 0)
                    nw->c04();
                local18 = nw;
                if (cur != 0)
                    cur->c00();
                cur = nw;
            }
            if (cur != 0) {
                if (param_6 != 0 && (DAT_01564c98 & *(unsigned int*)p) != 0)
                    *param_6 = 1;

                int iVar3 = cur->v1c();
                int iStack_c = *param_4;
                int iVar4 = cur->v28();
                int iStack_4 = *param_5;
                *param_4 = *param_4 + iVar3;
                *param_5 = *param_5 + iVar4;

                char* e = param_3->end;
                if (e < param_3->cap) {
                    param_3->end = e + 0x18;
                    if (e != 0) {
                        *(IObjC**)e = cur;
                        cur->c04();
                        *(void**)(e + 4) = p;
                        *(int*)(e + 8) = iVar3;
                        *(int*)(e + 0xc) = iStack_c;
                        *(int*)(e + 0x10) = iVar4;
                        *(int*)(e + 0x14) = iStack_4;
                    }
                } else {
                    Elem6 rec;
                    rec.obj = cur;
                    rec.par = (char*)p;
                    rec.a = iVar3;
                    rec.b = iStack_c;
                    rec.c = iVar4;
                    rec.d = iStack_4;
                    param_3->FUN_00a7f2e0(e, (char*)&rec);
                    cur = local18;
                }
            }
            p = (Src58*)((char*)p + 0x58);
        } while (p != (Src58*)param_2[1]);

        if (cur != 0)
            cur->c00();
    }
}

// ===========================================================================
// @ 0x00a7fd60
void __cdecl FUN_00a7fd60(void* stream, unsigned int* out)
{
    unsigned int local;
    FUN_0093a780(stream, &local, 1, 0);
    out[0] = local & 0x3fff;
    FUN_0093a800(stream, out + 2, 1, 0);
    FUN_0093a780(stream, out + 4, 1, 0);
    FUN_0093a780(stream, out + 5, 1, 0);
    FUN_0093a780(stream, out + 6, 1, 0);
    FUN_0093a780(stream, out + 7, 1, 0);
    FUN_0093a780(stream, out + 8, 1, 0);
    FUN_0093a780(stream, out + 0xe, 1, 0);
    FUN_0093a780(stream, out + 0xf, 1, 0);
    FUN_007ed920(stream, out + 0x10);
}

// ===========================================================================
// @ 0x00a7fe20
// thiscall: this in ecx (fields +0x10 interface, +0x70 float), one stack arg.
struct ObjFE20 {
    virtual char v10(void*, void*, float*, int, int, int);   // slot 0x10
};

struct Owner {
    char  pad0[0x10];
    ObjFE20* p10;     // +0x10
    char  pad1[0x5c];
    float f70;        // +0x70
    void  FUN_00a7fe20(void* arg);
};

void Owner::FUN_00a7fe20(void* arg)
{
    char* p = (arg != 0) ? ((char*)arg - 8) : 0;

    unsigned short w = *(unsigned short*)(p + 0xa);
    if (*(unsigned short*)(p + 0xa0) == w)
        return;

    *(unsigned short*)(p + 0xa0) = w;
    *(unsigned int*)(p + 0x80) = *(unsigned int*)(p + 0x1c);
    *(unsigned int*)(p + 0x84) = *(unsigned int*)(p + 0x20);
    *(unsigned int*)(p + 0x88) = *(unsigned int*)(p + 0x24);
    *(unsigned int*)(p + 0x8c) = *(unsigned int*)(p + 0x28);
    *(unsigned int*)(p + 0x90) = *(unsigned int*)(p + 0x2c);
    *(unsigned int*)(p + 0x94) = *(unsigned int*)(p + 0x30);

    float* pf = (float*)(p + 0x74);
    if (p10 == 0) {
        *pf = *(float*)(p + 0xc);
        *(unsigned int*)(p + 0x78) = *(unsigned int*)(p + 0x10);
        *(unsigned int*)(p + 0x7c) = *(unsigned int*)(p + 0x14);
        *(unsigned int*)(p + 0x7c) = 0;
    } else {
        float fVar3 = this->f70;
        float buf[3];
        buf[0] = 0.0f; buf[1] = 0.0f; buf[2] = 0.0f;
        int f70bits = *(int*)&fVar3;
        char cVar5 = p10->v10(p + 0xc, pf, buf, 0, f70bits, 0);
        if (cVar5 != 0) {
            float out[3];
            float a0 = buf[0];
            float a1 = fVar3;
            float a2 = 0.0f;
            float left  = a0 * *(float*)(p + 0x8c) + (*(float*)(p + 0x94) * a1 + *(float*)(p + 0x90) * a2);
            float right = (*(float*)(p + 0x88) * a1 + *(float*)(p + 0x84) * a2) + *(float*)(p + 0x80) * a0;
            float fabsL = left < 0.0f ? -left : left;
            float fabsR = right < 0.0f ? -right : right;
            float* puVar6;
            if (fabsL <= fabsR) {
                out[0] = *(float*)(p + 0x90) * a1 - *(float*)(p + 0x94) * a2;
                puVar6 = (float*)FUN_00539440(buf, out);
                *(float*)(p + 0x80) = puVar6[0];
                *(float*)(p + 0x84) = puVar6[1];
                *(float*)(p + 0x88) = puVar6[2];
                *(float*)(p + 0x8c) = *(float*)(p + 0x88) * a2 - *(float*)(p + 0x84) * a1;
                *(float*)(p + 0x90) = *(float*)(p + 0x80) * a1 - *(float*)(p + 0x88) * a0;
                *(float*)(p + 0x94) = *(float*)(p + 0x84) * a0 - *(float*)(p + 0x80) * a2;
            } else {
                out[0] = *(float*)(p + 0x88) * a2 - *(float*)(p + 0x84) * a1;
                puVar6 = (float*)FUN_00539440(buf, out);
                *(float*)(p + 0x8c) = puVar6[0];
                *(float*)(p + 0x90) = puVar6[1];
                *(float*)(p + 0x94) = puVar6[2];
                *(float*)(p + 0x80) = *(float*)(p + 0x90) * a1 - *(float*)(p + 0x94) * a2;
                *(float*)(p + 0x84) = *(float*)(p + 0x94) * a0 - *(float*)(p + 0x8c) * a1;
                *(float*)(p + 0x88) = *(float*)(p + 0x8c) * a2 - *(float*)(p + 0x90) * a0;
            }
            float fVar2 = *(float*)(p + 0x70);
            *pf = fVar2 * a0 + *pf;
            *(float*)(p + 0x78) = fVar2 * a2 + *(float*)(p + 0x78);
            *(float*)(p + 0x7c) = fVar2 * a1 + *(float*)(p + 0x7c);
        }
    }

    int iv = *(int*)(p + 0x98);
    if (iv != 0) {
        if (*pf < *(float*)(iv + 0x28))
            *(float*)(iv + 0x28) = *pf;
        if (*(float*)(iv + 0x34) < *pf)
            *(float*)(iv + 0x34) = *pf;
        if (*(float*)(p + 0x78) < *(float*)(iv + 0x2c))
            *(float*)(iv + 0x2c) = *(float*)(p + 0x78);
        if (*(float*)(iv + 0x38) < *(float*)(p + 0x78))
            *(float*)(iv + 0x38) = *(float*)(p + 0x78);
        if (*(float*)(p + 0x7c) < *(float*)(iv + 0x30))
            *(float*)(iv + 0x30) = *(float*)(p + 0x7c);
        if (*(float*)(iv + 0x3c) < *(float*)(p + 0x7c))
            *(float*)(iv + 0x3c) = *(float*)(p + 0x7c);
    }
}
