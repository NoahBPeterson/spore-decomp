// s00b43290 -- SP game-code collision/phantom transforms and the shared world object.
//
// Reconstructed from the disassembly + Ghidra decompiles in
// work/match/scratch_s00b43290_cards.txt, using the type/global conventions of the
// sibling slice s00b4b590 (work object pointer cell 0x0167eb70 = World70*).
// MSVC 2008 SP1, /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-.
//
//   00b43290  cWorld::FUN_00b43290   compose two 3x3 bases and their translation
//                                     into this->0xa4 and this->0xf8 (thiscall)
//   00b43710  FUN_00b43710           erase one key from the +0x58 hashtable
//   00b43790  FUN_00b43790           closest-approach contact along a segment
//   00b43990  FUN_00b43990           swept contact between two moving objects
//   00b43bc0  FUN_00b43bc0           sphere-vs-box contact, twice (two proxies)
//
// Everything outside this slice is a relocation (referenced by address only), so a
// helper's exact name does not matter.

typedef unsigned int  u32;
typedef unsigned char uchar;

#include <math.h>

// ------------------------------------------------------------------ module globals
extern "C" char* g_167eb70;                 // 0x0167eb70  World70*
extern "C" float g_13ec4b8;                 // 0x013ec4b8 1e-8f added before the sqrt
extern "C" float g_1461150;                 // 0x01461150
extern "C" float g_13f51ac;                 // 0x013f51ac
extern "C" float g_167eb8c;                 // 0x0167eb8c contact normal.x
extern "C" float g_167eb90;                 // 0x0167eb90 contact normal.y
extern "C" float g_167eb94;                 // 0x0167eb94 contact normal.z
extern "C" float g_1485720;                 // 0x01485720 1.0f
extern "C" char  g_167ec08;                 // 0x0167ec08 Matrix3 source

// ------------------------------------------------------------------ callees
extern "C" void  FUN_00b3f3a0(void*, void*);                        // 0x00b3f3a0
extern "C" void  FUN_004fc990(void*, void*, void*);                // 0x004fc990
extern "C" float FUN_00b3dcd0();                                   // 0x00b3dcd0
extern "C" void* FUN_00477820(void*, void*, float);                // 0x00477820
extern "C" void  FUN_00b3d9c0(void*, void*);                       // 0x00b3d9c0
extern "C" void  FUN_00b42370(void*, void*, void*);                // 0x00b42370
extern "C" float FUN_00b3d630(void*);                              // 0x00b3d630
extern "C" float FUN_00698b30(void*, void*, void*);                // 0x00698b30
extern "C" void  FUN_00698e00(void*, void*, void*, void*);         // 0x00698e00
extern "C" float FUN_00b3dfa0(void*, void*, void*, void*, void*, void*); // 0x00b3dfa0
extern "C" void  FUN_00b3f420(void*);                              // 0x00b3f420
extern "C" void  FUN_0041cb40(void*, void*);                       // 0x0041cb40 Matrix3::Assign
extern "C" int   FUN_00b3f6c0(void*);                              // 0x00b3f6c0
extern "C" int   FUN_00b3fe40(void*, float, void*, void*, int, void*); // 0x00b3fe40 SphereVsBoxContact
extern "C" void  FUN_00b645ed0(void*, void*, void*);               // 0x00645ed0 hashtable::find
extern "C" void  FUN_00bbc330(int, int);                           // 0x00bbc330
extern "C" void  FUN_00b72260(int);                                // 0x00b72260
extern "C" void  FUN_01068380(void*, void*);                       // 0x01068380 deque erase/clear

// ------------------------------------------------------------------ 0x00b43290
struct X {
    void FUN_00b43290();                 // thiscall: compose two bases into this+0xa4 / +0xf8
};

// @ 0x00b43290
void X::FUN_00b43290()
{
    void* self = this;
    float la8, la4, la0, l9c, l98, l94, l90, l8c, l88;      // basis A (FUN_00b3f3a0)
    float l80, l7c, l78, l74, l70, l6c, l68, l64, l60, l5c, l58, l54, l50, l4c, l84;
    float l48, l44, l40, l3c, l38, l34, l30, l2c, l28;
    float l24[5];
    float l10, lc, l8, l4;
    float f1, f2, f3, f8, f9, f10, f11, f12, f13;

    FUN_00b3f3a0(self, &la8);
    FUN_004fc990(&l70, &la8, &l80);

    l4c = *(float*)((char*)self + 0x68);
    f1  = *(float*)((char*)self + 0x5c);
    l80 = *(float*)((char*)self + 0x74);
    l7c = *(float*)((char*)self + 0x6c);
    f9  = (f1 * la8 + l4c * la4) + l80 * la0;
    f2  = *(float*)((char*)self + 0x78);
    l84 = *(float*)((char*)self + 0x70);
    l78 = *(float*)((char*)self + 0x60);
    f11 = (l78 * la8 + l7c * la4) + f2 * la0;
    f3  = *(float*)((char*)self + 0x7c);
    l74 = *(float*)((char*)self + 0x64);
    f12 = (l74 * la8 + l84 * la4) + f3 * la0;
    f10 = (f1 * l9c + l4c * l98) + l80 * l94;
    f13 = (l78 * l9c + l7c * l98) + f2 * l94;
    l10 = (l74 * l9c + l84 * l98) + f3 * l94;
    lc  = (f1 * l90 + l4c * l8c) + l80 * l88;
    l8  = (l78 * l90 + l7c * l8c) + f2 * l88;
    l4  = (l74 * l90 + l84 * l8c) + f3 * l88;

    l48 = (f11 * l64 + f12 * l58) + f9  * l70;
    l44 = (f9  * l6c + f11 * l60) + f12 * l54;
    l40 = (f9  * l68 + f11 * l5c) + f12 * l50;
    l3c = (f13 * l64 + l10 * l58) + f10 * l70;
    l34 = (f10 * l68 + f13 * l5c) + l10 * l50;
    l38 = (f10 * l6c + f13 * l60) + l10 * l54;
    l30 = (l8  * l64 + l4  * l58) + lc  * l70;
    l2c = (lc  * l6c + l8  * l60) + l4  * l54;
    l28 = (lc  * l68 + l8  * l5c) + l4  * l50;

    float* dst = (float*)((char*)self + 0xa4);
    dst[0] = l48; dst[1] = l44; dst[2] = l40; dst[3] = l3c; dst[4] = l38;
    dst[5] = l34; dst[6] = l30; dst[7] = l2c; dst[8] = l28;

    f8 = FUN_00b3dcd0();
    const float* src = (const float*)FUN_00477820(l24, dst, f8);
    for (int i = 0; i < 9; ++i)
        dst[i] = src[i];

    float* q = (float*)((char*)self + 0xf8);
    q[0] = la8; q[1] = la4; q[2] = la0; q[3] = l9c; q[4] = l98;
    q[5] = l94; q[6] = l90; q[7] = l8c; q[8] = l88;
}

// ------------------------------------------------------------------ 0x00b43710
// @ 0x00b43710
void __cdecl FUN_00b43710(u32 key)
{
    char* w = g_167eb70;
    char* ht = w + 0x58;                                  // hashtable at +0x58
    void* arr   = *(void**)(ht + 4);
    int   count = *(int*)(ht + 8);

    void* it_node = 0;
    FUN_00b645ed0(ht, &it_node, &key);                    // find(&it, &key)

    if (it_node != *(void**)((char*)arr + (u32)count * 4)) {
        int* pair = *(int**)((char*)it_node + 4);
        FUN_00bbc330(*(int*)(w + 4), pair[2]);
        FUN_00b72260(pair[0]);
        FUN_01068380(w + 0x58, &it_node);
    }
}

// ------------------------------------------------------------------ 0x00b43790
// @ 0x00b43790
void __cdecl FUN_00b43790(void* a, void* b, float* out)
{
    float vA[4];                       // local_30
    float qa[3], qb[3];                // local_c, local_24
    float p[3];                        // local_18, local_14, local_10

    FUN_00b3d9c0(a, vA);
    FUN_00b42370(b, qa, qb);
    float f2  = FUN_00b3d630(a);
    float fv4 = *(float*)((char*)b + 0x134) * *(float*)((char*)b + 0x10) + f2;
    float f3  = FUN_00698b30(vA, qa, qb);

    if (f3 <= fv4) {
        FUN_00698e00(p, vA, qa, qb);
        p[0] -= vA[0];
        p[1] -= vA[1];
        p[2] -= vA[2];
        *(int*)(out + 0x60) = 1;                                   // out+0x180
        float f1 = 1.0f / sqrt((p[0] * p[0] + (p[1] * p[1] + p[2] * p[2])) + 1e-08f);
        float fv4b = fv4 - f3;
        float fv2  = f2 - fv4b;
        out[0] = (f1 * p[0]) * fv2 + vA[0];
        out[1] = (p[1] * f1) * fv2 + vA[1];
        out[2] = (p[2] * f1) * fv2 + vA[2];
        out[0x30] = out[0];
        out[0x31] = out[1];
        out[0x32] = out[2];
        out[0x61] = f1 * p[0];
        out[0x62] = p[1] * f1;
        out[99]   = p[2] * f1;
        out[0x65] = out[0x61] * fv4b;
        out[0x66] = out[0x62] * fv4b;
        out[0x67] = out[99]   * fv4b;
        out[100]  = 0.0f;
    }
}

// ------------------------------------------------------------------ 0x00b43990
// @ 0x00b43990
void __cdecl FUN_00b43990(void* param_1, void* param_2, float* param_3)
{
    float qa[3], qb[3];                // local_c, local_18
    float qc[3], qd[3];                // local_24, local_30
    float r1[3];                       // local_48, local_44, local_40
    float r2[3];                       // local_3c, local_38, local_34

    FUN_00b42370(param_1, qa, qb);
    FUN_00b42370(param_2, qc, qd);

    float f4 = *(float*)((char*)param_2 + 0x134) * *(float*)((char*)param_2 + 0x10);
    float f3 = *(float*)((char*)param_1 + 0x134) * *(float*)((char*)param_1 + 0x10);
    float f5 = f4 + f3;
    float f2 = FUN_00b3dfa0(qa, qb, qc, qd, r1, r2);

    if (f2 <= f5) {
        float f7 = r2[2] - r1[2];
        float f6 = r2[1] - r1[1];
        float f8 = r2[0] - r1[0];
        f5 = f5 - f2;
        f3 = f3 - f5;
        float f1 = 1.0f / sqrt((f8 * f8 + (f6 * f6 + f7 * f7)) + 1e-08f);
        f8 = f1 * f8;
        f6 = f6 * f1;
        f7 = f7 * f1;
        param_3[0] = f8 * f3 + r1[0];
        f4 = f4 - f5;
        param_3[1] = f6 * f3 + r1[1];
        param_3[2] = f7 * f3 + r1[2];
        param_3[0x31] = r2[1] - f6 * f4;
        param_3[0x32] = r2[2] - f7 * f4;
        param_3[0x30] = r2[0] - f8 * f4;
        param_3[0x61] = f8;
        param_3[0x62] = f6;
        *(int*)(param_3 + 0x60) = 1;                               // param_3+0x180
        param_3[99]   = f7;
        param_3[0x65] = f5 * param_3[0x61];
        param_3[0x66] = param_3[0x62] * f5;
        param_3[0x67] = param_3[99]   * f5;
        param_3[100]  = 0.0f;
    }
}

// ------------------------------------------------------------------ 0x00b43bc0
// @ 0x00b43bc0
void __cdecl FUN_00b43bc0(void* param_1, void* param_2, void* param_3)
{
    float g68[3], g5c[3];              // local_68, local_5c  (two query points)
    float box[6];                      // local_50..local_3c  (min/max working box)
    float sph[6];                      // local_38..local_28  (centre + radius)
    float mtx[12];                     // local_24  (Matrix33Template)

    FUN_00b42370(param_1, g68, g5c);
    float f2 = *(float*)((char*)param_1 + 0x134) * *(float*)((char*)param_1 + 0x10);

    unsigned fm = 0x7f7fffffu, fn = 0xff7fffffu;
    box[0] = box[1] = box[2] = *(float*)&fm;
    box[3] = box[4] = box[5] = *(float*)&fn;
    FUN_00b3f420(box);

    sph[0] = 0.0f; sph[1] = 0.0f;                  // local_38 / local_36
    sph[2] = g_167eb8c;
    sph[3] = g_167eb90;
    sph[4] = g_167eb94;
    sph[5] = 1.0f;

    FUN_0041cb40(mtx, &g_167ec08);
    int flags = FUN_00b3f6c0(sph);

    if (*(char*)((char*)param_1 + 0x34) == 0 || *(char*)((char*)param_2 + 0x34) == 0)
        flags = 1;
    else
        flags &= 0xffffff00;

    FUN_00b3fe40(g68, f2, box, sph, flags, param_3);

    if (*(int*)((char*)param_3 + 0x180) == 0) {
        if (*(char*)((char*)param_1 + 0x34) == 0 || *(char*)((char*)param_2 + 0x34) == 0)
            flags = 1;
        else
            flags &= 0xffffff00;
        FUN_00b3fe40(g5c, f2, box, sph, flags, param_3);
    }
}