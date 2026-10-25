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
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
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

// Retail saves the incoming ECX with its 4-byte local-frame push and restores it at every exit.
// Keep the same caller-visible register state for LTCG callers without changing the C++ body.
struct EcxPreserve {
    __forceinline EcxPreserve() { __asm push ecx }
    __forceinline ~EcxPreserve() { __asm pop ecx }
};

// ---------------------------------------------------------------- the function
extern "C" void sResolvePartCollision(int p1, int p2, int p3, float p4, int* p5, int p6, int p7,
                                      int p8, int* p9, int p10, unsigned int p11, int p12, int p13,
                                      int p14)
{
    EcxPreserve ecxPreserve;
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

// ---------------------------------------------------------------------------------------------
// The part-side data the collision sweep below works on.
//
// Every part keeps a uniform-scale transform (translation +0x4c, scale +0x58, a column-major
// 3x3 at +0x5c..+0x7c) and the grid cell it occupies (+0xfc).  The cell is turned into a list of
// candidate contact points: a count at +0x00 of the list object followed by 0x48-byte records
// holding a kind (+0x00, 1 = empty), the point in part space (+0x04..+0x0c) and a radius
// (+0x34).
// ---------------------------------------------------------------------------------------------
struct Int3 {
    int x, y, z;
};

struct PartCell {
    int   kind;                          // +0x00: 1 = no contact point here
    float x, y, z;                       // +0x04, +0x08, +0x0c (part space)
    char  pad0[0x34 - 0x10];
    float radius;                        // +0x34
    char  pad1[0x48 - 0x38];
};

struct PartCellList {
    int      count;                      // +0x00
    int      pad;                        // +0x04
    PartCell cells[1];                   // +0x08
};

struct PartXform {
    char          pad0[0x48];
    unsigned char flags;                 // +0x48: bit 1 = contact points are in part space
    char          pad1[0x4c - 0x49];
    float         tx, ty, tz;            // +0x4c, +0x50, +0x54
    float         scale;                 // +0x58
    float         m00, m10, m20;         // +0x5c, +0x60, +0x64 (column 0)
    float         m01, m11, m21;         // +0x68, +0x6c, +0x70 (column 1)
    float         m02, m12, m22;         // +0x74, +0x78, +0x7c (column 2)
    char          pad2[0xfc - 0x80];
    Int3          cell;                  // +0xfc: grid cell whose contact list to sweep
};

// The caller's two per-collision context objects: only the 0xb0/0xb4 mode words are read.
struct ResolveCtx {
    char pad0[0xb0];
    int  b0;                             // +0xb0
    int  b4;                             // +0xb4
};

extern "C" unsigned int  FUN_00e573e0(void* a, void* b);
extern "C" PartCellList* FUN_00e679e0(Int3 cell);

// sResolvePartCollision's declared parameter types (see above) describe the roles it played for
// its first caller; the sweep below feeds it (mid, normal, overlap, ...) instead, so go through a
// pointer of the shape actually pushed here.
typedef void (__cdecl* ResolveSweepFn)(unsigned int p1, float* mid, float* normal, float overlap,
                                       void* partA, int cfgA, int kindB, int outerIdx,
                                       void* partB, int cfgB, int b0, unsigned int cfg,
                                       int kindA, int innerIdx);

// ---------------------------------------------------------------------------------------------
// 0x00e6ad80 -- for every candidate contact point of part A against every candidate of part B:
// transform both into world space, and when the spheres overlap hand the pair to
// sResolvePartCollision with the outward normal and the midpoint of the overlap.
// ---------------------------------------------------------------------------------------------
// @ 0x00e6ad80
void __cdecl FUN_00e6ad80(unsigned int p1, PartXform* a, PartXform* b, ResolveCtx* ctxA,
                          ResolveCtx* ctxB)
{
    unsigned int  cfg   = FUN_00e573e0(a, b);
    PartCellList* listA = FUN_00e679e0(a->cell);
    PartCellList* listB = FUN_00e679e0(b->cell);

    if (listA->count <= 0)
        return;

    for (int outer = 0; outer < listA->count; ++outer) {
        PartCell* cellA = &listA->cells[outer];

        if (cellA->kind == 1)
            continue;

        float ax = cellA->x;
        float ay = cellA->y;
        float az = cellA->z;

        if (a->flags & 2) {
            float rx = (a->m01 * ay + a->m02 * az) + a->m00 * ax;
            float ry = (a->m11 * ay + a->m12 * az) + a->m10 * ax;
            float rz = (a->m21 * ay + a->m22 * az) + a->m20 * ax;
            ax = rx;
            ay = ry;
            az = rz;
        }

        float scaleA = a->scale;
        float wax = a->tx + scaleA * ax;
        float way = a->ty + scaleA * ay;
        float waz = a->tz + scaleA * az;
        float radA = cellA->radius * a->scale;

        for (int inner = 0; inner < listB->count; ++inner) {
            PartCell* cellB = &listB->cells[inner];

            if (cellB->kind == 1)
                continue;

            float bx = cellB->x;
            float by = cellB->y;
            float bz = cellB->z;

            if (b->flags & 2) {
                float rx = (b->m01 * by + b->m02 * bz) + b->m00 * bx;
                float ry = (b->m11 * by + b->m12 * bz) + b->m10 * bx;
                float rz = (b->m21 * by + b->m22 * bz) + b->m20 * bx;
                bx = rx;
                by = ry;
                bz = rz;
            }

            float scaleB = b->scale;
            float wbx = b->tx + scaleB * bx;
            float wby = b->ty + scaleB * by;
            float wbz = b->tz + scaleB * bz;
            float radB = cellB->radius * b->scale;

            float dx = wbx - wax;
            float dy = wby - way;
            float dz = wbz - waz;
            float d2 = (dy * dy + dx * dx) + dz * dz;

            float normal[3];
            float mid[3];
            float overlap = radB + radA;
            bool  collide = true;

            if (d2 >= 1.52587890625e-05f) {
                float dist = sqrtf(d2);
                overlap -= dist;
                collide = (overlap >= 0.0f);
                if (collide) {
                    float inv = 1.0f / dist;
                    float nx  = dx * inv;
                    float ny  = dy * inv;
                    float nz  = dz * inv;
                    float dr  = radB - radA;
                    normal[0] = nx;
                    normal[1] = ny;
                    normal[2] = nz;
                    mid[0] = ((wax + wbx) + nx * dr) * 0.5f;
                    mid[1] = ((way + wby) + ny * dr) * 0.5f;
                    mid[2] = ((waz + wbz) + nz * dr) * 0.5f;
                }
            }

            if (collide) {
                ((ResolveSweepFn)&sResolvePartCollision)(p1, mid, normal, overlap, a, ctxA->b4,
                                                         cellB->kind, outer, b, ctxB->b4,
                                                         ctxB->b0, cfg, cellA->kind, inner);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------
// The look-at target list: a count at +0x04 and an array of {kind, weight} records at +0x00.
// ---------------------------------------------------------------------------------------------
struct LookatRec {
    int   kind;                          // +0x00
    float weight;                        // +0x04
};

struct LookatList {
    LookatRec* recs;                     // +0x00
    int        count;                    // +0x04
};

// The 8-byte selector pair FUN_00e68990 fills from the object's resolved look-at ids.
struct LookatSrc {
    int unknown;                         // +0x00 (left as-is by FUN_00e686c0)
    int handle;                          // +0x04
};

struct LookatMask {                      // the four selector bytes handed to FUN_00e68990
    unsigned char a, b, c, d;
};

namespace EA { namespace Random {
struct RandomLinearCongruential {
    double RandomDoubleUniform();        // 0x009360d0, __thiscall (ECX = this)
};
}}

static EA::Random::RandomLinearCongruential* const kRandom =
    (EA::Random::RandomLinearCongruential*)0x01601760;   // the process-wide RNG

extern "C" int  FUN_00e50af0(unsigned int p2, unsigned int p3);
extern "C" void FUN_00e686c0(int obj, void* handle, int* out, LookatMask* mask);
extern "C" void FUN_00e68990(int obj, int* src, int* out28, int* out2c, int* out30);

// ---------------------------------------------------------------------------------------------
// 0x00e6b180 -- pick a weighted-random look-at target of the given class from the object's
// candidate list.  Kinds 6..8 need the object's three resolved selector ids, which are computed
// once (lazily) through FUN_00e686c0/FUN_00e68990; kinds 4/5 map straight to object fields.
// A record is taken when the running weight total, scaled by a random fraction, still falls
// inside that record's own weight.  Returns the chosen record's kind, or 0.
// ---------------------------------------------------------------------------------------------
// @ 0x00e6b180
int __cdecl FUN_00e6b180(int obj, unsigned int p2, unsigned int p3, int* out)
{
    int id = FUN_00e50af0(p2, p3);

    RefPtr ref;
    ref.Ctor_00743b50();
    LookatList* list = (LookatList*)FUN_00e4cc40(id, &ref);

    int   kind8Id = 0;
    int   kind7Id = 0;
    int   kind6Id = 0;
    bool  resolved = false;
    float total    = 0.0f;
    int   chosen   = -1;

    for (int i = 0; i < list->count; ++i) {
        LookatRec* rec = &list->recs[i];

        if (rec->weight == 0.0f)
            continue;

        if ((rec->kind == 6 || rec->kind == 7 || rec->kind == 8) && !resolved) {
            LookatSrc  src;
            LookatMask mask;
            RefPtr     tmp;

            tmp.Ctor_00743b50();
            void* handle = FUN_00e4cc40(*(int*)((char*)obj + 0x108), &tmp);
            FUN_00e686c0(obj, handle, &src.handle, &mask);
            mask.a = 0;
            mask.b = 1;
            mask.c = 1;
            mask.d = 1;
            FUN_00e68990(obj, &src.unknown, &kind8Id, &kind7Id, &kind6Id);
            resolved = true;
            tmp.Release_00e82130();
        }

        int  value = 1;
        bool take  = true;
        switch (rec->kind) {
        case 4:
            value = *(int*)((char*)obj + 0x22c);
            if (value == 0) {
                value = *(int*)((char*)obj + 0x170);
                take  = (value != 0);
            }
            break;
        case 5:
            value = *(int*)((char*)obj + 0x220);
            take  = (value != 0);
            break;
        case 6:
            value = kind6Id;
            take  = (value != 0);
            break;
        case 7:
            value = kind7Id;
            take  = (value != 0);
            break;
        case 8:
            value = kind8Id;
            take  = (value != 0);
            break;
        }

        if (take) {
            total += rec->weight;
            double roll = kRandom->RandomDoubleUniform() * (double)total;

            if (roll > (double)total)
                roll = (double)total;
            if (roll < 0.0)
                roll = 0.0;
            if (roll < (double)rec->weight) {
                *out   = value;
                chosen = i;
            }
        }
    }

    if (chosen != -1) {
        int result = list->recs[chosen].kind;
        ref.Release_00e82130();
        return result;
    }

    ref.Release_00e82130();
    return 0;
}
