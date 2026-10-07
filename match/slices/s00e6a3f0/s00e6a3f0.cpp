// slice s00e6a3f0 - SP::sResolvePartCollision (0x00e6a3f0), 2435 bytes.
//
// Event selector for a part-part collision: picks one of the event codes (0..0x19) from the two
// parts' kinds, their flags at +0x112, the relative speed/distance, and the caller's mode values,
// then emits the event through FUN_00e59cc0 and finishes with FUN_00e6a250.
//
// Callee conventions (checked from the ret forms and the call sites in the original):
//   FUN_00e59cc0  cdecl, 9 args (add esp,0x24 at each call site), void, leaves st0 alone
//   FUN_00e67330  cdecl, 5 args (cleaned by the add esp,0x1c after the following FUN_00e59e50 call)
//   FUN_00e59e50  cdecl(obj, slot) -> bool: obj->kind == FUN_00e4cce0(slot)
//   FUN_00e4cce0  cdecl(slot) -> int (table lookup)
//   FUN_00e5f590  cdecl(obj, p2) -> bool, ret with add esp,0xc
//   FUN_00e57340  cdecl(obj) -> int
//   FUN_00e57560  cdecl(obj) -> bool
//   FUN_00e50540  cdecl(obj) -> bool
//   FUN_00e6a060  cdecl(obj, p14) -> bool
//   FUN_00e6a250  cdecl, 8 args, void
//   FUN_00e4cc40  thunk to FUN_00e823a0: cdecl(id, RefPtr* out) -> int*, stores out->p = id, AddRef(id)
//   FUN_00743b50  thiscall, ECX = RefPtr*, zeroes it (ctor)
//   FUN_00e82130  thiscall, ECX = RefPtr*, Release (dec [p+0xc] if p != 0)
//   FUN_00e52960  usercall: no stack args, reads its object from ESI (= p9 at every call site); bool result in AL
//
// Flags: /O2 /MD /Gy /TP
#include "types.h"
#include <math.h>

// The two parts. Only the fields this function touches are named; the rest is padding.
struct CollPart {
    int id;                          // +0x00: *p5 / *p9 (compared with the cell game's owner id)
    char pad0[0x90 - 4];
    float px, py, pz;                // +0x90, +0x94, +0x98 (position, read as floats)
    char pad1[0x108 - 0x9c];
    int kind;                        // +0x108 (the param[0x42] slot)
    char pad2[0x112 - 0x10c];
    unsigned char flag;              // +0x112: nonzero blocks the event
};

// ---------------------------------------------------------------- RefPtr (intrusive)
struct RefPtr {
    int* p;
    void Ctor_00743b50();            // thiscall, zero p
    void Release_00e82130();         // thiscall, release p
};

// ---------------------------------------------------------------- external globals / callees
extern char* g_016b3c04;             // cell game object pointer (+0x411c owner id, +0x5190 table)

extern "C" void FUN_00e59cc0(int a1, int a2, int a3, float f, int idA, int idB, int a7, int a8, int code);
extern "C" void FUN_00e67330(int idA, int idB, int p2, float dist, int cfg);
extern "C" char FUN_00e59e50(int obj, int slot);
extern "C" int  FUN_00e4cce0(int slot);
extern "C" char FUN_00e5f590(int obj, int p2);
extern "C" int  FUN_00e57340(int obj);
extern "C" char FUN_00e57560(int obj);
extern "C" char FUN_00e50540(int obj);
extern "C" char FUN_00e6a060(int obj, int p14);
extern "C" void FUN_00e6a250(int a1, int a2, int a3, float f, int* a5, int* a9, int a10, int a12);
extern "C" int* FUN_00e4cc40(int id, RefPtr* out);     // thunk_FUN_00e823a0

extern "C" char FUN_00e52960();
// usercall shim for FUN_00e52960 (reads ESI). Behaviour: ESI = obj, call, AL is the result.
static char Usercall_e52960(int obj) {
    char r;
    __asm {
        push esi
        mov  esi, obj
        call FUN_00e52960
        pop  esi
        mov  r, al
    }
    return r;
}

static inline int CellOwnerId() { return *(int*)(g_016b3c04 + 0x411c); }

// ---------------------------------------------------------------- the function
extern "C" void sResolvePartCollision(int p1, int p2, int p3, float p4, int* p5, int p6, int p7,
                                      int p8, int* p9, int p10, unsigned int p11, int p12, int p13,
                                      int p14)
{
    CollPart* A = (CollPart*)p5;
    CollPart* B = (CollPart*)p9;
    int uVar5;
    int iVar2;
    char cVar1;

    if (p7 == 9) return;
    if (p13 == 9) return;
    if (p10 == 7) {
        iVar2 = *p5;
        if (iVar2 == CellOwnerId()) {
            FUN_00e59cc0(p1, p2, p3, p4, iVar2, *p9, p8, p14, 0x13);
            return;
        }
        FUN_00e59cc0(p1, p2, p3, p4, iVar2, *p9, p8, p14, 0);
        return;
    }
    if (p6 == 7) return;
    if (p10 == 6) {
        if (*p5 == CellOwnerId()) uVar5 = 0x12;
        else uVar5 = 1;
        FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, uVar5);
    }
    {
        float dx = A->px - B->px;
        float dy = A->py - B->py;
        float dz = A->pz - B->pz;
        float dist = (float)sqrt(dz * dz + dy * dy + dx * dx);
        FUN_00e67330(*p5, *p9, p2, dist,
                     *(int*)(*(int*)(g_016b3c04 + 0x5190) + 0x74));
    }
    cVar1 = FUN_00e59e50((int)p9, 0x15);
    if (cVar1 != 0 && p7 == 2 && p12 == 1 && p10 == 1) {
        FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 0x15);
        return;
    }
    iVar2 = FUN_00e4cce0(0x13);
    if (B->kind == iVar2 && p7 == 7 && p13 == 0xc && FUN_00e5f590((int)p9, p2) == 1 &&
        Usercall_e52960((int)p9) != 0 && FUN_00e57340((int)p9) > 2) {
        uVar5 = 8;
    LAB_00e6a61c:
        FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, uVar5);
        return;
    }
    iVar2 = FUN_00e4cce0(0x14);
    if (B->kind == iVar2 && p12 > 2 && (p7 == 7 || p7 == 4) && p13 == 0xb &&
        FUN_00e6a060((int)p9, p14) == 1) {
        uVar5 = 0x14;
        goto LAB_00e6a61c;
    }
    iVar2 = FUN_00e4cce0(0x19);
    if (B->kind == iVar2 && p12 > 2 && (p13 == 0xc || p13 == 10 || p13 == 0xb) && p7 == 4) {
        uVar5 = 0xd;
    LAB_00e6a762:
        FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, uVar5);
        return;
    }
    if (p10 == 4) {
        RefPtr r;
        int* obj;
        r.Ctor_00743b50();
        obj = FUN_00e4cc40(A->kind, &r);
        if (*(int*)((char*)obj + 0xb4) == 4) {
            iVar2 = *p9;
            int iVar4 = *p5;
            uVar5 = 2;
            FUN_00e59cc0(p1, p2, p3, p4, iVar4, iVar2, -1, -1, uVar5);
        } else {
            if ((p12 == 0 || p12 == 1 || p12 == 2) &&
                (p11 != 2 || *p5 == CellOwnerId())) {
                uVar5 = 3;
            } else {
                uVar5 = 1;
            }
            iVar2 = *p9;
            int iVar4 = *p5;
            FUN_00e59cc0(p1, p2, p3, p4, iVar4, iVar2, -1, -1, uVar5);
        }
        r.Release_00e82130();
    }
    if (p7 == 3) {
        if (p10 != 3) return;
        if (p12 != 1) return;
        if (A->flag != 0) return;
        uVar5 = 9;
        goto LAB_00e6a762;
    }
    if (p13 == 3) return;
    if (p7 == 2) {
        if (p10 == 2) {
            if (p12 != 2) {
                if (p12 == 0) {
                    if (B->flag != 0 || A->flag != 0) goto LAB_00e6ad4a;
                    uVar5 = 10;
                    goto LAB_00e6a8a6;
                }
                if (p12 == 1) {
                    if (*p9 != CellOwnerId() || B->flag != 0 || A->flag != 0) goto LAB_00e6a99f;
                    FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 7);
                    goto LAB_00e6a9a3;
                }
                goto LAB_00e6ac96;
            }
            if (A->flag == 0 && B->flag == 0 && p13 == 2) {
                FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 0xf);
            }
            if (A->flag != 0 || p13 == 2) goto LAB_00e6ad4e;
            iVar2 = FUN_00e57340((int)p9);
            if (iVar2 < 2) {
                cVar1 = Usercall_e52960((int)p9);
                if (cVar1 == 0) {
                    FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 1);
                    goto LAB_00e6ad4e;
                }
            }
        } else {
            if (((p11 & 1) == 0) || (p12 != 1)) {
                /* fVar3 stays p4 */
            } else {
            LAB_00e6a99f:
            LAB_00e6a9a3:
                if (*p9 != CellOwnerId() && A->flag == 0) {
                    FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 10);
                }
            }
            if (p10 != 2) goto LAB_00e6ad4e;
        LAB_00e6ac96:
            if (p12 != 3 || A->flag != 0) goto LAB_00e6ad4e;
            cVar1 = FUN_00e50540((int)p5);
            if (cVar1 == 0) {
                uVar5 = 4;
                goto LAB_00e6a8a6;
            }
        }
        uVar5 = 7;
    } else {
        if (p7 == 7) {
            if (((p11 & 1) == 0) || (1 < p12)) {
                /* fVar3 stays p4 */
            } else {
                FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 8);
            }
            if (p10 == 2) {
                if (p12 == 2) {
                    if (A->flag != 0) goto LAB_00e6ad4e;
                    if (p13 != 7) {
                        FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 8);
                        goto LAB_00e6ad4e;
                    }
                    uVar5 = 0xe;
                } else {
                    if (p12 == 1) {
                        if (A->flag == 0 && B->flag == 0 && FUN_00e57340((int)p9) > 1) {
                            FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 8);
                        }
                        goto LAB_00e6ad4e;
                    }
                    if (p12 != 3) goto LAB_00e6ad4e;
                    if (p13 == 2) {
                        if (A->flag != 0) goto LAB_00e6ad4e;
                        FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 5);
                    }
                    if (A->flag != 0) goto LAB_00e6ad4e;
                    if (B->flag == 0) {
                        FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 8);
                    }
                    if (A->flag != 0 || B->flag != 1) goto LAB_00e6ad4e;
                    uVar5 = 5;
                }
            } else {
                if (p10 != 3) {
                    if (p10 == 4) {
                        FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 3);
                    }
                    goto LAB_00e6ad4e;
                }
                if (p12 != 2) {
                    if (p12 == 4 && A->flag == 0) {
                        FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 5);
                    }
                    goto LAB_00e6ad4e;
                }
                if (A->flag != 0 || FUN_00e57340((int)p9) < 2) goto LAB_00e6ad4e;
                uVar5 = 6;
            }
        LAB_00e6a8a6:
            FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, uVar5);
            goto LAB_00e6ad4e;
        }
        if (p7 != 4) {
        LAB_00e6ad4a:
            goto LAB_00e6ad4e;
        }
        if (p10 != 3) {
            if (p10 == 2) {
                if ((p12 == 1 || p12 == 2) && FUN_00e57560((int)p9) != 0 &&
                    B->flag == 0 && A->flag == 0) {
                    if (p13 == 4) {
                        FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 0x10);
                    } else {
                        FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 0xc);
                    }
                }
                if (p12 == 3 && A->flag == 0) {
                    FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, 4);
                }
                goto LAB_00e6ad4e;
            }
            goto LAB_00e6ad4a;
        }
        if (p12 == 1) {
            if (A->flag == 0) {
                uVar5 = 0xb;
                goto LAB_00e6a8a6;
            }
            goto LAB_00e6ad4a;
        }
        if (p12 != 3 || A->flag != 0) goto LAB_00e6ad4a;
        uVar5 = 4;
    }
    FUN_00e59cc0(p1, p2, p3, p4, *p5, *p9, p8, p14, uVar5);
LAB_00e6ad4e:
    FUN_00e6a250(p1, p2, p3, p4, p5, p9, p10, p12);
}
