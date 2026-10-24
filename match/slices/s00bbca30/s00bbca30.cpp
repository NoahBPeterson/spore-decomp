// s00bbca30.cpp -- gold6 batch, worker 25
// Reconstructed from the annotated disassembly + Ghidra decompiles in
// work/match/scratch_s00bbca30_cards.txt.  Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;

#define VF(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

extern "C" void* __cdecl FUN_01021260();                       // SP::cSPLivingUniverse::GetActivePlanet
extern "C" void* __cdecl FUN_010212a0();                       // SP::cSPLivingUniverse::GetActivePlanetRecord
extern "C" void* __cdecl FUN_00401090();                       // SP::cSPEditorSpeciesManager singleton
extern "C" void* __cdecl FUN_004df550(void*);                  // GetProfile(const Key&)
extern "C" void  __cdecl FUN_01043c60(void*, void*);           // cZooMarkerMgr helper
extern "C" void  __cdecl FUN_00f47380(void*);                  // operator_delete_array
extern "C" bool  __cdecl EA_ResKeyNeq(void*, void*);           // EA::ResourceMan::operator!=

extern uint32_t DAT_0168a488, DAT_0168a48c, DAT_0168a490;

class TObj {
public:
    // ---- reused __thiscall callees (addresses in comments) -------------------
    void* F_4df550(void*);              // 0x4df550  GetProfile(const Key&)
    void* F_c745d0(int, void*);         // 0xc745d0
    void* F_8414c0();                   // 0x8414c0
    void  F_c80680(int, void*);         // 0xc80680
    void  F_f921d0(int, int);           // 0xf921d0
    void  F_b2a750();                   // 0xb2a750
    void  F_bbc870(void* out, int a, void* b, int c);   // 0xbbc870
    void  F_bbc540(void* out, void* p);                 // 0xbbc540  UpdateCargoSlots
    void  F_bbc950(void* out, int a, int b, int c);     // 0xbbc950
    void  F_c70a00(float);                              // 0xc70a00
    void  F_c70a50(float);                              // 0xc70a50
    float F_c71d30();                                   // 0xc71d30
    void  F_c71da0(float);                              // 0xc71da0
    char  F_c70a70();                                   // 0xc70a70
    void  F_c70aa0(float);                              // 0xc70aa0
    void* F_c71e30();                                   // 0xc71e30
    void  F_c70de0(int);                                // 0xc70de0
    float F_fbda80();                                   // 0xfbda80
    void  F_fbddb0(float, float, void*);                // 0xfbddb0
    int   F_bbc670(int);                                // 0xbbc670
    char  F_c308b0();                                   // 0xc308b0
    void  F_ffaa90();                                   // 0xffaa90
    void  F_dd8640(int, int, int, int, int, int);       // 0xdd8640
    void* F_b1fdb0();                                   // 0xb1fdb0
    void  F_01034880();                                 // 0x1034880

    // ---- slice targets -------------------------------------------------------
    int*  FUN_00bbca30(int* out, int index, int planet);   // 0xbbca30
    void  FUN_00bbcb10(void* key, void* planet);           // 0xbbcb10
    char  FUN_00bbcb90(int param_1, int param_2);          // 0xbbcb90
    void  FUN_00bbcf00(void* planet, float f2, float f3, int param_4);  // 0xbbcf00
    void  FUN_00bbd0a0(int delta);                         // 0xbbd0a0
    int*  FUN_00bbd0e0(int* node, int param_3, int** param_4);  // 0xbbd0e0
};

// ---- cdecl / stdcall free targets ----------------------------------------
bool __cdecl FUN_00bbcd40(int param_1, int param_2);       // 0xbbcd40
bool __stdcall FUN_00bbcda0(int param_1, int param_2);     // 0xbbcda0
bool __stdcall FUN_00bbce00(int param_1, int param_2);     // 0xbbce00

typedef bool (__cdecl *CmpFn)(int, int);

void __cdecl FUN_00bbd180(int* first, int param_2, int param_3, int hole, int param_5, CmpFn cmp);   // 0xbbd180
void __cdecl FUN_00bbd1f0(int* arr, int param_2, int param_3, void* param_4, CmpFn cmp);             // 0xbbd1f0

extern "C" void __cdecl FUN_00d52cb0(void*, int, int, int, void*);   // 0xd52cb0  push_heap-ish
extern "C" void* __cdecl FUN_00b3d3b0();                       // 0xb3d3b0  PlanetModel (0 args)
extern "C" void* __cdecl FUN_00b3d3b0b(int);                    // 0xb3d3b0  PlanetModel (1 arg)
extern "C" void  __cdecl FUN_00bbd2a0(void*, float, void*);     // 0xbbd2a0
extern "C" int   __cdecl FUN_00fc2080(float, float);            // 0xfc2080  TerraDistClass
extern "C" void* __cdecl FUN_01021080();                        // GetUniverseContext
extern "C" int   __cdecl FUN_01021090();                        // GetPlayerEmpireID
extern "C" void* __cdecl FUN_01002bd0(int);                     // SpaceGameGet
extern "C" void* __cdecl FUN_0067dcc0();                        // MessageServer
extern "C" void* __cdecl FUN_00b3d3e0(int,int,int,int,int,int); // EventLog
extern "C" void* __cdecl FUN_00b3d470();                        // GetTerraformingManager-ish

template<class T> const T& MinT(const T& a, const T& b) { return a <= b ? a : b; }

struct IVec3 { int x, y, z; };

// number of face slots held by a planet record (used by 0xbbcd40)
static inline int CountFaces(int p) {
    return (*(int*)(p + 0x358) - *(int*)(p + 0x354) >> 2) +
           (*(int*)(p + 0x344) - *(int*)(p + 0x340) >> 2);
}

extern "C" void* __cdecl FUN_00b3d350();                       // SP::PlanetModel

// ===========================================================================
// 0x00bbca30 - pick the index-th species key owning a planet face
// ===========================================================================
// @ 0x00bbca30
int* TObj::FUN_00bbca30(int* out, int index, int planet) {
    if (planet == 0) {
        planet = *(int*)((char*)FUN_01021260() + 0x13c);        // ActivePlanet(); ->+0x13c
    }
    int count = 0;
    TObj* mgr = (TObj*)FUN_00401090();
    int n = (*(int*)(planet + 0xd4) - *(int*)(planet + 0xd0)) / 0xc;
    for (int i = 0; i < n; i++) {
        void* e = (void*)(*(int*)(planet + 0xd0) + i * 0xc);
        TObj* p = (TObj*)mgr->F_4df550(e);
        if (p != 0) {
            if (*(uint32_t*)((char*)p + 0x608) > 0) {
                count++;
            }
            if (count == index) {
                out[0] = *(int*)e;
                out[1] = *((int*)e + 1);
                out[2] = *((int*)e + 2);
                return out;
            }
        }
    }
    out[0] = (int)DAT_0168a488;
    out[1] = (int)DAT_0168a48c;
    out[2] = (int)DAT_0168a490;
    return out;
}

// ===========================================================================
// 0x00bbcb10 - report a handled species key via the zoo marker manager
// ===========================================================================
// @ 0x00bbcb10
void TObj::FUN_00bbcb10(void* key, void* planet) {
    uint32_t* k = (uint32_t*)key;
    if (k[0] != DAT_0168a488 || k[1] != DAT_0168a48c || k[2] != DAT_0168a490) {
        if (planet == 0) {
            planet = FUN_01021260();
        }
        ((TObj*)planet)->F_c745d0(0, key);
        TObj* x = (TObj*)((TObj*)planet)->F_8414c0();
        if (x != 0) {
            x->F_c80680(0, key);
        }
        void* p = *(void**)((char*)planet + 0x13c);
        if (*(uint32_t*)((char*)p + 0x2c) & 0x800) {
            FUN_01043c60(p, key);
        }
    }
}

// ===========================================================================
// 0x00bbcd40 - total face count of two planet records, less-than
// ===========================================================================
// @ 0x00bbcd40
bool __cdecl FUN_00bbcd40(int param_1, int param_2) {
    return CountFaces(param_1) < CountFaces(param_2);
}

// ===========================================================================
// 0x00bbcda0 - does the record hold at least param_1*3 faces
// ===========================================================================
// @ 0x00bbcda0
bool __stdcall FUN_00bbcda0(int param_1, int param_2) {
    if (param_2 == 0) {
        param_2 = (int)FUN_010212a0();
    }
    int v;
    if ((*(uint32_t*)(param_2 + 0x2c) & 0x800) != 0) {
        v = *(int*)(param_2 + 0xc0) - *(int*)(param_2 + 0xbc);
    } else {
        v = *(int*)(param_2 + 0xd4) - *(int*)(param_2 + 0xd0);
    }
    return v / 0xc >= param_1 * 3;
}

// ===========================================================================
// 0x00bbce00 - does the record hold at least param_1*3 faces (coarse path)
// ===========================================================================
// @ 0x00bbce00
bool __stdcall FUN_00bbce00(int param_1, int param_2) {
    if (param_2 == 0) {
        param_2 = (int)FUN_010212a0();
    }
    int v = *(int*)(param_2 + 0xc0) - *(int*)(param_2 + 0xbc);
    return v / 0xc >= param_1 * 3;
}

// ===========================================================================
// 0x00bbd0a0 - accumulate time, clamped at 2000
// ===========================================================================
// @ 0x00bbd0a0
void TObj::FUN_00bbd0a0(int delta) {
    FUN_00b3d350();
    int cap = 2000;
    int& m = *(int*)((char*)this + 0x64);
    m = m + delta;
    m = MinT(m, cap);
}

// ===========================================================================
// 0x00bbd0e0 - unlink a node from an intrusive hash-bucket chain
// ===========================================================================
// @ 0x00bbd0e0
int* TObj::FUN_00bbd0e0(int* node, int param_3, int** param_4) {
    int iVar1 = *(int*)(param_3 + 0x14);
    node[1] = (int)param_4;
    *node = iVar1;
    while (iVar1 == 0) {
        node[1] += 4;
        iVar1 = *(int*)node[1];
        *node = iVar1;
    }
    int c = (int)*param_4;
    if (c == param_3) {
        *param_4 = (int*)*(int*)(c + 0x14);
        FUN_00f47380((void*)param_3);
        *(int*)((char*)this + 0xc) -= 1;
        return node;
    }
    int t = *(int*)(c + 0x14);
    while (t != param_3) {
        c = t;
        t = *(int*)(t + 0x14);
    }
    *(int*)(c + 0x14) = *(int*)(t + 0x14);
    FUN_00f47380((void*)param_3);
    *(int*)((char*)this + 0xc) -= 1;
    return node;
}

// ===========================================================================
// 0x00bbd180 - eastl adjust_heap sift-down over an int array
// ===========================================================================
// @ 0x00bbd180
void __cdecl FUN_00bbd180(int* first, int param_2, int param_3, int hole, int param_5, CmpFn cmp) {
    int iVar3;
    int iVar1;
    while (1) {
        iVar1 = hole * 2;
        iVar3 = iVar1 + 2;
        if (param_3 <= iVar3) {
            break;
        }
        if (cmp(first[iVar3], first[iVar3 - 1])) {
            iVar3 = iVar1 + 1;
        }
        first[hole] = first[iVar3];
        hole = iVar3;
    }
    if (iVar3 == param_3) {
        first[hole] = first[iVar3 - 1];
        hole = iVar1 + 1;
    }
    FUN_00d52cb0(first, param_2, hole, param_5, (void*)cmp);
}

// ===========================================================================
// 0x00bbd1f0 - eastl push_heap sift-up over an AutoRefCount array
// ===========================================================================
// @ 0x00bbd1f0
void __cdecl FUN_00bbd1f0(int* arr, int param_2, int param_3, void* param_4, CmpFn cmp) {
    int iVar3;
    while ((iVar3 = param_3, param_2 < iVar3)) {
        param_3 = (iVar3 - 1) >> 1;
        if (!((bool(__cdecl*)(int, void*))cmp)(arr[param_3], param_4)) {
            break;
        }
        int* piVar1 = (int*)arr[iVar3];
        int* piVar2 = (int*)arr[param_3];
        if (piVar2 != piVar1) {
            if (piVar2 != 0) {
                ((void(__thiscall*)(void*))VF(piVar2, 0))(piVar2);
            }
            arr[iVar3] = (int)piVar2;
            if (piVar1 != 0) {
                ((void(__thiscall*)(void*))VF(piVar1, 4))(piVar1);
            }
        }
    }
    int* piVar1b = (int*)arr[iVar3];
    void* p4 = param_4;
    if (p4 != piVar1b) {
        if (p4 != 0) {
            ((void(__thiscall*)(void*))VF(p4, 0))(p4);
        }
        arr[iVar3] = (int)p4;
        if (piVar1b != 0) {
            ((void(__thiscall*)(void*))VF(piVar1b, 4))(piVar1b);
        }
    }
    if (p4 != 0) {
        ((void(__thiscall*)(void*))VF(p4, 4))(p4);
    }
}

// ===========================================================================
// 0x00bbce40 - walk the face level down until the record holds 3*count slots
// ===========================================================================
// @ 0x00bbce40
int __stdcall FUN_00bbce40(int param_1) {
    if (param_1 == 0) {
        param_1 = (int)FUN_010212a0();
    }
    int iVar2 = param_1;
    if (param_1 == 0) {
        iVar2 = (int)FUN_010212a0();
    }
    iVar2 = FUN_00fc2080(*(float*)(iVar2 + 0xb0), *(float*)(iVar2 + 0xb4));
    if (iVar2 > 0) {
        int iVar4 = iVar2 * 3;
        do {
            int iVar3 = param_1;
            if (param_1 == 0) {
                iVar3 = (int)FUN_010212a0();
            }
            int iVar1;
            if ((*(uint32_t*)(iVar3 + 0x2c) & 0x800) != 0) {
                iVar1 = (*(int*)(iVar3 + 0xc0) - *(int*)(iVar3 + 0xbc)) / 0xc;
            } else {
                iVar1 = (*(int*)(iVar3 + 0xd4) - *(int*)(iVar3 + 0xd0)) / 0xc;
            }
            if (iVar1 >= iVar4) {
                return iVar2;
            }
            iVar2--;
            iVar4 -= 3;
        } while (iVar2 > 0);
    }
    return 0;
}

// ===========================================================================
// 0x00bbd6c0 - flush every entry of a 0x10-stride table through 00bbd2a0
// ===========================================================================
// @ 0x00bbd6c0
void __stdcall FUN_00bbd6c0(int* param_1) {
    TObj* o = (TObj*)FUN_00b3d3b0();
    TObj* hud = (TObj*)*(void**)((char*)o + 0x38);
    hud->F_f921d0(0x80, 0);
    int n = (param_1[1] - param_1[0]) >> 4;
    if (n != 0) {
        int off = 0;
        do {
            int base = param_1[0];
            FUN_00bbd2a0((void*)(base + off), *(float*)(base + off + 0xc), hud);
            off += 0x10;
            n--;
        } while (n != 0);
    }
    TObj* q = (TObj*)FUN_00b3d3b0b(0xf);
    q->F_b2a750();
}

// ===========================================================================
// 0x00bbcb90 - does this planet still own the three handled species keys?
// ===========================================================================
// @ 0x00bbcb90
char TObj::FUN_00bbcb90(int param_1, int param_2) {
    int iVar3 = param_2;
    if (param_2 == 0) {
        iVar3 = (int)FUN_01021260();
    }
    int iVar1 = *(int*)(iVar3 + 0x13c);
    int k1[3], k2[3], k3[3];
    F_bbc870(k1, param_1, (void*)0x6d60a1cc, iVar1);
    F_bbc540(k1, (void*)iVar3);
    F_bbc870(k2, param_1, (void*)0x29c388a, iVar1);
    F_bbc540(k2, (void*)iVar3);
    F_bbc870(k3, param_1, (void*)0x3a8be428, iVar1);
    F_bbc540(k3, (void*)iVar3);
    char flag = 1;
    if (k1[0] == (int)DAT_0168a488 && k1[1] == (int)DAT_0168a48c && k1[2] == (int)DAT_0168a490 &&
        k2[0] == (int)DAT_0168a488 && k2[1] == (int)DAT_0168a48c && k2[2] == (int)DAT_0168a490 &&
        k3[0] == (int)DAT_0168a488 && k3[1] == (int)DAT_0168a48c && k3[2] == (int)DAT_0168a490) {
        flag = 0;
    }
    if ((*(uint32_t*)(iVar1 + 0x2c) & 0x800) == 0) {
        int kc[3], k18[3], k24[3];
        FUN_00bbca30(kc, param_1, iVar1);
        FUN_00bbcb10(kc, (void*)iVar3);
        F_bbc950(k18, param_1, 1, iVar1);
        FUN_00bbcb10(k18, (void*)iVar3);
        F_bbc950(k24, param_1, 0, iVar1);
        FUN_00bbcb10(k24, (void*)iVar3);
        if (flag == 0) {
            if (k24[0] == (int)DAT_0168a488 && k24[1] == (int)DAT_0168a48c && k24[2] == (int)DAT_0168a490 &&
                k18[0] == (int)DAT_0168a488 && k18[1] == (int)DAT_0168a48c && k18[2] == (int)DAT_0168a490 &&
                !EA_ResKeyNeq(kc, &DAT_0168a488)) {
                return 0;
            }
            return 1;
        }
    }
    return flag;
}

// ===========================================================================
// 0x00bbcf00 - planet terraform / species-feedback tick
// ===========================================================================
// @ 0x00bbcf00
void TObj::FUN_00bbcf00(void* planet, float f2, float f3, int param_4) {
    TObj* pl = (TObj*)planet;
    int uVar7 = *(int*)((char*)planet + 0x13c);
    pl->F_c70a00(f2);
    pl->F_c70a50(f3);
    float t0 = pl->F_c71d30();
    pl->F_c71da0(t0);
    if (planet == FUN_01021260()) {
        if (FUN_01021080() == 0) {
            TObj* pm = (TObj*)FUN_00b3d350();
            TObj* sub = (TObj*)*(void**)((char*)pm + 0x24);
            if (sub != 0) {
                TObj* terr = (TObj*)((void*(__thiscall*)(void*))VF(sub, 0x10))(sub);
                if (terr != 0) {
                    float fa = terr->F_fbda80();
                    float lim = f3 - 0.8f;
                    float* pu = &f2;
                    if (f2 <= lim) {
                        pu = &lim;
                    }
                    terr->F_fbddb0(*pu, f3, (void*)param_4);
                    if (terr->F_c70a70() == 0) {
                        pl->F_c70aa0(*(float*)((char*)terr + 0x600));
                    }
                    if (fa != terr->F_fbda80()) {
                        TObj* ms = (TObj*)FUN_0067dcc0();
                        ((void(__thiscall*)(void*, int, int, int))VF(ms, 0x14))(ms, 0x45fe992, 0, 0);
                    }
                }
                TObj* ent = (TObj*)pl->F_c71e30();
                if (ent != 0) {
                    if (ent->F_c308b0() != 0) {
                        if (this->F_bbc670(uVar7) > 0) {
                            int id = FUN_01021090();
                            TObj* av = (TObj*)((TObj*)FUN_01002bd0(id))->F_b1fdb0();
                            av->F_ffaa90();
                            TObj* log = (TObj*)FUN_00b3d3e0(0xc4875746, 0x131a9f54, 0, 0, 1, 0);
                            log->F_dd8640(0xc4875746, 0x131a9f54, 0, 0, 1, 0);
                            pl->F_c70de0(1);
                        }
                    }
                }
            }
            TObj* t = (TObj*)FUN_00b3d470();
            if (t != 0) {
                ((TObj*)FUN_00b3d470())->F_01034880();
            }
        }
    }
}