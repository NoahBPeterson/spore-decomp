// s00f7b520 -- GroundCover "Swarm" behaviour-node pool.
//
// Reconstructed from the disassembly + Ghidra decompiles in
// work/match/scratch_s00f7b520_cards.txt.
// MSVC 2008 SP1, /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.
//
//   00f7b520  Swarm::FUN_00f7b520   large per-id property dispatcher (thiscall)
//   00f7ba80  Swarm::FUN_00f7ba80   one integration step over the node list (thiscall)
//   00f7bd70  Swarm::FUN_00f7bd70   release the whole +0x18 node list (thiscall)
//   00f7be20  FUN_00f7be20          allocate + construct a 0x230 Swarm node (cdecl)
//   00f7be60  FUN_00f7be60          install the 8-entry command table at 0x1676430
//   00f7bef0  Swarm::FUN_00f7bef0   shutdown / detach (thiscall)
//
// Everything outside this slice is a relocation (referenced by address only).

typedef unsigned int  u32;
typedef unsigned char uchar;

#include <string.h>

// ------------------------------------------------------------------ module globals
extern "C" int   g_1675edc;                  // 0x01675edc
extern "C" int   g_1675ee0;                  // 0x01675ee0
extern "C" int   g_1675ee8;                  // 0x01675ee8
extern "C" int   g_1675eec;                  // 0x01675eec
extern "C" int   g_1676430[8];               // 0x01676430  command table
extern "C" int*  g_16c9b68;                  // 0x016c9b68  free node list head
extern "C" char  g_16c9b58;                  // 0x016c9b58  FixedAllocatorBase
extern "C" int   g_15b0ebc[];               // 0x015b0ebc  per-type step callback table

// ------------------------------------------------------------------ callees
extern "C" void* FUN_00f473a0(u32, const char*, int, int, int, int);  // 0x00f473a0 EAAllocate
extern "C" char* FUN_00f75fc0(void);                                  // 0x00f75fc0
extern "C" char  FUN_00f79bf0(char*);                                 // 0x00f79bf0
extern "C" void  FUN_00f58620(char*);                                 // 0x00f58620
extern "C" void  FUN_00f7a6a0(char*);                                 // 0x00f7a6a0
extern "C" void  FUN_00f7a5d0(char*);                                 // 0x00f7a5d0
extern "C" void  FUN_007cda70(float*);                                // 0x007cda70
extern "C" void  FUN_00a7ab40(int, void*, int, void*);                // 0x00a7ab40
extern "C" void* FUN_007d5590(void*, void*, void*, void*);            // 0x007d5590
extern "C" void* FUN_00aa8ea0(void*, void*);                          // 0x00aa8ea0
extern "C" char  FUN_00f79bb0(void);                                  // 0x00f79bb0
extern "C" void  FUN_00f74480(void);                                  // 0x00f74480 GroundCoverAddCommands
struct AllocObj { void* FUN_00f7afd0(void*, void*); };                // 0x00f7afd0 (thiscall)
extern "C" char  EA_AddCore(void*, int, int);                         // 0x00bbc... FixedAllocatorBase::AddCore

int FUN_00f7be20(int, int);                                           // defined below

typedef int* (__thiscall *PFN_Get)(void*);
typedef int  (__thiscall *PFN_Slot)(void*, int, int, int, int, int);

// ------------------------------------------------------------------ Swarm object
struct Swarm {
    int  FUN_00f7b520(int id, float* p, int n);
    void FUN_00f7ba80(float dt);
    void FUN_00f7bd70();
    void FUN_00f7bef0(int param_2);
};

// @ 0x00f7b520
int Swarm::FUN_00f7b520(int param_2, float* param_3, int param_4)
{
    char* s = (char*)this;
    float f2, f3, f4, f5, f6, f16;
    int   i9, i15;
    char* p14;
    char* p7; char* p8;
    void* u13;
    char  c11;

    if (param_2 < 0x102) {
        if (param_2 == 0x101) {
            *(float*)(s + 0x128) = param_3[0];
            *(float*)(s + 0x130) = param_3[1];
            *(float*)(s + 0x138) = param_3[2];
            *(float*)(s + 300)   = param_3[3];
            *(float*)(s + 0x134) = param_3[4];
            *(float*)(s + 0x13c) = param_3[5];
            return 1;
        }
        switch (param_2) {
        case 0:
            *(float*)(s + 0x140) = param_3[0];
            return 1;
        case 1:
            *(float*)(s + 0x148) = param_3[0];
            return 1;
        case 3:
            *(float*)(s + 0x144) = param_3[0];
            return 1;
        case 4:
            *(float*)(s + 0x14c) = param_3[0];
            return 1;
        case 5:
            f2 = param_3[1];
            f3 = param_3[2];
            *(float*)(s + 0x154) = param_3[0];
            *(float*)(s + 0x158) = f2;
            *(float*)(s + 0x15c) = f3;
            return 1;
        case 6:
            i15 = param_4 / 3;
            i9 = *(int*)(s + 0x18);
            while (i9 < i15) {
                char* node = (char*)FUN_00f75fc0();
                if (FUN_00f79bf0(node) != 0) {
                    *(char**)(node + 4) = *(char**)(s + 0x14);
                    *(char**)node       = s + 0x10;
                    *(char**)(s + 0x14) = node;
                    *(char**)*(char**)(node + 4) = node;
                    *(int*)(s + 0x18) = *(int*)(s + 0x18) + 1;
                }
                i9 = *(int*)(s + 0x18);
            }
            i9 = *(int*)(s + 0x18);
            p14 = *(char**)(s + 0x10);
            while (i15 < i9) {
                p7 = *(char**)(p14 + 4);
                p8 = *(char**)p14;
                *(char**)p7 = p8;
                *(char**)(p8 + 4) = p7;
                *(char**)p14 = 0;
                *(char**)(p14 + 4) = 0;
                *(int*)(s + 0x18) = *(int*)(s + 0x18) - 1;
                FUN_00f7a6a0(p14);
                p14 = p8;
                i9 = *(int*)(s + 0x18);
            }
            p14 = *(char**)(s + 0x10);
            if (0 < i15) {
                do {
                    *(float*)(p14 + 0x38) = param_3[0];
                    *(float*)(p14 + 0x3c) = param_3[1];
                    f16 = param_3[2];
                    param_3 += 3;
                    --i15;
                    *(float*)(p14 + 0x40) = f16;
                    p14 = *(char**)p14;
                } while (i15 != 0);
            }
            return 1;
        case 9:
            *(float*)(s + 0x6c) = param_3[0];
            *(float*)(s + 0x70) = param_3[1];
            *(float*)(s + 0x74) = param_3[2];
            return 1;
        case 10:
            *(float*)(s + 0x78) = param_3[0];
            return 1;
        case 0xb:
            f2 = param_3[5];
            f3 = param_3[3];
            f4 = param_3[4];
            f16 = (((*(float*)(s + 0xa4) - param_3[2]) * f2 +
                    (*(float*)(s + 0xa0) - param_3[1]) * f4) +
                   (*(float*)(s + 0x9c) - param_3[0]) * f3) /
                  ((f4 * f4 + f3 * f3) + f2 * f2);
            f2 = param_3[5];
            f5 = param_3[1];
            f6 = param_3[2];
            *(float*)(s + 0x6c) = param_3[0] + f3 * f16;
            *(float*)(s + 0x70) = f4 * f16 + f5;
            *(float*)(s + 0x74) = f2 * f16 + f6;
            *(float*)(s + 0x78) = (float)(0.0f <= f16);
            FUN_007cda70((float*)(s + 0x6c));
            return 1;
        case 0xd:
            i9 = *(int*)(s + 0x1c);
            i15 = param_4 / 3;
            if (*(int*)(i9 + 8) < 0) {
                char auStack_38[56];
                u13 = FUN_007d5590(auStack_38, s + 0xa8, s + 0xe0, s + 0x1fc);
                FUN_00a7ab40(i15, param_3, *(int*)(i9 + 0x44), u13);
                return 1;
            }
            i9 = *(int*)(s + 0x18);
            while (i9 < i15) {
                char* node = (char*)FUN_00f75fc0();
                if (FUN_00f79bf0(node) != 0)
                    FUN_00f58620(node);
                i9 = *(int*)(s + 0x18);
            }
            i9  = *(int*)(s + 0x18);
            u13 = *(void**)(s + 0x10);
            while (i15 < i9) {
                void* nx = *(void**)FUN_00aa8ea0(&param_2, u13);
                *(int*)(s + 0x18) = *(int*)(s + 0x18) - 1;
                FUN_00f7a6a0((char*)u13);
                u13 = nx;
                i9 = *(int*)(s + 0x18);
            }
            p14 = *(char**)(s + 0x10);
            if (0 < i15) {
                do {
                    *(float*)(p14 + 0x10) = param_3[0];
                    *(float*)(p14 + 0x14) = param_3[1];
                    f16 = param_3[2];
                    param_3 += 3;
                    --i15;
                    *(float*)(p14 + 0x18) = f16;
                    p14 = *(char**)p14;
                } while (i15 != 0);
            }
            return 1;
        case 0xe:
            if (-1 < *(int*)(s + 0x21c)) {
                void* obj = *(void**)(s + 0x24);
                int* v = (int*)((PFN_Get)*(void**)(*(int*)obj + 0x20))(obj);
                return ((PFN_Slot)*(void**)(*v + 0x74))(v, 0, *(int*)(s + 0x21c), 0, param_4, (int)param_3);
            }
            if (-1 < *(int*)(s + 0x218)) {
                void* obj = *(void**)(s + 0x24);
                int* v = (int*)((PFN_Get)*(void**)(*(int*)obj + 0x20))(obj);
                return ((PFN_Slot)*(void**)(*v + 0x74))(v, 1, *(int*)(s + 0x218), 0, param_4, (int)param_3);
            }
            break;
        case 0x10:
            if (param_4 == 2 ||
                (int)(param_3[2] < 0.0f ? param_3[2] - 0.5f : param_3[2] + 0.5f) ==
                    (int)*(uchar*)(*(int*)(s + 0x1c) + 0x131)) {
                *(float*)(s + 0x164) = param_3[0];
                *(float*)(s + 0x168) = param_3[1];
                return 1;
            }
            break;
        case 0x12:
            *(float*)(s + 0x150) = param_3[0];
            return 1;
        }
    }
    return 0;
}

// @ 0x00f7ba80
void Swarm::FUN_00f7ba80(float param_2)
{
    char* s = (char*)this;
    float f9, f2, f3, f4, f10, f11, f12;
    int   i5, i8;
    char* p6;
    char  c7;

    f9 = param_2 * (float)*(double*)(s + 0x58) + (float)*(double*)(s + 0x48);
    *(double*)(s + 0x48) = (double)f9;

    if ((float)*(int*)(s + 0x50) <= f9) {
        f9 = **(float**)(*(int*)(s + 0x24) + 0x68) * *(float*)(s + 0x174);
        i8 = (int)(f9 < 0.0f ? f9 - 0.5f : f9 + 0.5f);
        if ((float)i8 < f9)
            i8 = i8 + 1;

        for (i8 = i8 - *(int*)(s + 0x20); 0 < i8; i8 = i8 - 1) {
            for (;;) {
                p6 = (char*)g_16c9b68;
                if (g_16c9b68 != 0) {
                    g_16c9b68 = *(int**)g_16c9b68;
                    *(void**)(p6 + 4) = 0;
                    *(void**)p6 = 0;
                    break;
                }
                c7 = EA_AddCore(&g_16c9b58, 0, 0);
                if (c7 != 0)
                    break;
            }
            c7 = FUN_00f79bf0(p6);
            if (c7 == 0) {
            LAB_ret:
                if (*(int*)(s + 0x218) == 0 ||
                    (*(float*)(p6 + 8) < *(float*)(p6 + 0xc) &&
                     ((*(u32*)(*(int*)(s + 0x24) + 8) >> 0x1b & 1) == 0))) {
                    *(int**)p6 = g_16c9b68;
                    g_16c9b68 = (int*)p6;
                } else {
                    FUN_00f7a5d0(p6);
                    if (*(int*)(s + 0x218) != 0 && *(int*)(s + 0x20) == 0 &&
                        *(char*)(s + 0x15) != 0)
                        ((void(__thiscall*)(void*, int))*(void**)(*(int*)(*(int*)(s + 0x218) + 8) + 0xc))
                            (*(void**)(s + 0x218), 0);
                }
            } else {
                i5 = *(int*)(s + 0x24);
                int fncell = g_15b0ebc[(u32)*(uchar*)(i5 + 0x130)];
                if (fncell == 0) {
                    f9 = *(float*)(p6 + 8);
                    *(float*)(p6 + 8) = f9 + param_2;
                    if (f9 + param_2 < *(float*)(p6 + 0xc)) {
                        f9  = *(float*)(s + 100);
                        f2  = *(float*)(p6 + 0x24);
                        f10 = *(float*)(s + 0x68);
                        f3  = *(float*)(p6 + 0x1c);
                        f4  = *(float*)(p6 + 0x20);
                        f11 = *(float*)(s + 0x6c) * param_2 + *(float*)(p6 + 0x24);
                        *(float*)(p6 + 0x24) = f11;
                        f9  = f3 + f9 * param_2;
                        *(float*)(p6 + 0x1c) = f9;
                        f10 = f4 + f10 * param_2;
                        *(float*)(p6 + 0x20) = f10;
                        f12 = 1.0f - *(float*)(i5 + 0x160) * param_2;
                        f9  = f9 * f12;
                        *(float*)(p6 + 0x1c) = f9;
                        f11 = f11 * f12;
                        f10 = f10 * f12;
                        *(float*)(p6 + 0x20) = f10;
                        *(float*)(p6 + 0x24) = f11;
                        f12 = param_2 * 0.5f;
                        *(float*)(p6 + 0x14) = *(float*)(p6 + 0x14) + (f10 + f4) * f12;
                        *(float*)(p6 + 0x10) = *(float*)(p6 + 0x10) + (f9 + f3) * f12;
                        *(float*)(p6 + 0x18) = *(float*)(p6 + 0x18) + (f11 + f2) * f12;
                        c7 = 1;
                    } else {
                        c7 = 0;
                    }
                } else {
                    c7 = ((char(__thiscall*)(void*, float, int, char*))fncell)(p6, param_2, i5, s);
                }
                if (c7 == 0)
                    goto LAB_ret;

                *(char**)(p6 + 4) = *(char**)(s + 0x1c);
                *(char**)p6       = s + 0x18;
                *(char**)(s + 0x1c) = p6;
                *(char**)*(char**)(p6 + 4) = p6;
                *(int*)(s + 0x20) = *(int*)(s + 0x20) + 1;

                if (*(float*)(p6 + 0x10) < *(float*)(s + 0x88))
                    *(float*)(s + 0x88) = *(float*)(p6 + 0x10);
                f9 = *(float*)(p6 + 0x10);
                if (*(float*)(s + 0x94) <= f9 && f9 != *(float*)(s + 0x94))
                    *(float*)(s + 0x94) = f9;
                if (*(float*)(p6 + 0x14) < *(float*)(s + 0x8c))
                    *(float*)(s + 0x8c) = *(float*)(p6 + 0x14);
                f9 = *(float*)(p6 + 0x14);
                if (*(float*)(s + 0x98) <= f9 && f9 != *(float*)(s + 0x98))
                    *(float*)(s + 0x98) = f9;
                if (*(float*)(p6 + 0x18) < *(float*)(s + 0x90))
                    *(float*)(s + 0x90) = *(float*)(p6 + 0x18);
                f9 = *(float*)(p6 + 0x18);
                if (*(float*)(s + 0x9c) <= f9 && f9 != *(float*)(s + 0x9c))
                    *(float*)(s + 0x9c) = f9;
            }
        }
    }
}

// @ 0x00f7bd70
void Swarm::FUN_00f7bd70()
{
    char* s    = (char*)this;
    char* head = s + 0x18;
    char* n    = *(char**)(s + 0x18);

    while (n != head) {
        char* nx = *(char**)n;
        char* pv = *(char**)(n + 4);
        *(char**)pv       = nx;
        *(char**)(nx + 4) = pv;
        *(char**)n        = 0;
        *(char**)(n + 4)  = 0;
        *(int*)(s + 0x20) = *(int*)(s + 0x20) - 1;

        if (*(int*)(s + 0x218) == 0 ||
            (*(float*)(n + 8) < *(float*)(n + 0xc) &&
             ((*(u32*)(*(int*)(s + 0x24) + 8) >> 0x1b & 1) == 0))) {
            *(int**)n = g_16c9b68;
            g_16c9b68 = (int*)n;
        } else {
            FUN_00f7a5d0(n);
            if (*(int*)(s + 0x218) != 0 && *(int*)(s + 0x20) == 0 &&
                *(char*)(s + 0x15) != 0)
                ((void(__thiscall*)(void*, int))*(void**)(*(int*)(*(int*)(s + 0x218) + 8) + 0xc))
                    (*(void**)(s + 0x218), 0);
        }
        n = nx;
    }

    char* m = *(char**)(s + 0x18);
    while (m != head) {
        char* mx = *(char**)m;
        *(char**)(m + 4) = 0;
        *(char**)m       = 0;
        m = mx;
    }
    *(char**)head       = head;
    *(char**)(head + 4) = head;
}

// @ 0x00f7be20
int FUN_00f7be20(int param_1, int param_2)
{
    char* p = (char*)FUN_00f473a0(0x230, "Swarm", 0, 0, 0, 0);
    if (p != 0) {
        char* r = (char*)((AllocObj*)p)->FUN_00f7afd0((void*)param_1, (void*)param_2);
        if (r != 0)
            return (int)(r + 8);
    }
    return 0;
}

// @ 0x00f7be60
void FUN_00f7be60(void)
{
    int local[8];
    local[0] = 0;
    local[1] = (int)&FUN_00f74480;
    local[2] = (int)&FUN_00f7be20;
    local[3] = g_1675edc;
    local[4] = g_1675ee0;
    local[5] = 0;
    local[6] = g_1675ee8;
    local[7] = g_1675eec;
    memcpy((void*)g_1676430, local, sizeof(local));
    g_1676430[0] = (int)&FUN_00f79bb0;
}

// @ 0x00f7bef0
void Swarm::FUN_00f7bef0(int param_2)
{
    char* s = (char*)this;
    if (*(char*)(s + 0xc) != 0) {
        if (*(int*)(s + 0x210) != 0 && *(int*)(s + 0x18) == 0) {
            void* obj = (char*)*(void**)(s + 0x210) + 8;
            ((void(__thiscall*)(void*, int))*(void**)(*(int*)obj + 0xc))(obj, param_2);
        }
        *(char*)(s + 0xd) = (param_2 == 0);

        if (*(char*)(s + 0xd) == 0) {
            *(char*)(s + 0xc) = *(char*)(s + 0xd);
            ((Swarm*)((char*)this - 8))->FUN_00f7bd70();   // lea ecx,[esi-8]: list owner is 8 bytes below

            if (*(int*)(s + 0x21c) >= 0) {
                void* obj = *(void**)(s + 0x24);
                int* v = (int*)((PFN_Get)*(void**)(*(int*)obj + 0x20))(obj);
                ((void(__thiscall*)(void*, int, int))*(void**)(*v + 0x24))(v, *(int*)(s + 0x21c), 0);
                return;
            }
            if (*(int*)(s + 0x218) >= 0) {
                void* obj = *(void**)(s + 0x24);
                int* v = (int*)((PFN_Get)*(void**)(*(int*)obj + 0x20))(obj);
                ((void(__thiscall*)(void*, int, int))*(void**)(*v + 0x38))(v, *(int*)(s + 0x218), 0);
            }
        }
    }
}
