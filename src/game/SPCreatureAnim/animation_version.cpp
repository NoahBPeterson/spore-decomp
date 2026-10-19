// src/game/SPCreatureAnim/animation_version.cpp -- migrated from slice(s) s009a7810 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/animation_version.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "nSPCreatureAnim/latest_version/animation_static_data.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  operator_new__(void* p, int a, int b);   // 0x011e073e (lib_crt placement init)
extern "C" uint32_t FUN_009a4660(uint32_t a, uint32_t b); // 0x009a4660 BitMatch (defined in s009a4c70)
extern char DAT_015507a8[];       // property-name table (0x1c stride, 20 entries)

// ---- items of slice s009a7810 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  operator_new__(void* p, int a, int b);   // 0x011e073e (lib_crt placement init)
extern "C" uint32_t FUN_009a4660(uint32_t a, uint32_t b); // 0x009a4660 BitMatch (defined in s009a4c70)
extern char DAT_015507a8[];       // property-name table (0x1c stride, 20 entries)
namespace nSPCreatureAnim {
namespace converters {
        void ConvertEvent_v11_v12(uint32_t* src, uint32_t* dst);
}
}
namespace nSPCreatureAnim {
namespace converters {
        void ConvertEvent_v9_v10(uint32_t* src, uint32_t* dst);
}
}
// ---- items of slice s009a7810 end

// @ 0x009a8170
uint32_t FUN_009a8170(uint32_t param_1, uint32_t param_2)
{
    uint32_t uVar2 = 0;
    uint32_t uVar1 = 1;
    while ((param_2 != 0) && (param_1 != 0)) {
        uint32_t uVar3 = param_1 - 1 & param_1;
        uVar2 = uVar2 | (uint32_t)(-(int32_t)((uVar1 & param_2) != 0) & (uVar3 ^ param_1));
        param_2 = param_2 & ~uVar1;
        uVar1 = uVar1 * 2;
        param_1 = uVar3;
    }
    return uVar2;
}

// @ 0x009a81b0
void nSPCreatureAnim::converters::ConvertEvent_v11_v12(uint32_t* param_1, uint32_t* param_2)
{
    *param_2 = *param_1;
    uint32_t uVar1 = param_1[2] & 0xfffeefff;
    param_2[10] = uVar1;
    if ((param_1[2] & 0x1000) != 0) param_2[10] = uVar1 | 0x1000;
    param_2[0xb] = param_1[5];
    param_2[0xc] = param_1[6];
    param_2[0xd] = param_1[7];
    param_2[0xe] = param_1[8];
    param_2[0xf] = param_1[9];
    param_2[0x10] = param_1[10];
    param_1[10] = 0;
    param_2[0x11] = param_1[0xb];
    param_2[0x13] = 0; param_2[0x14] = 0; param_2[0x15] = 0; param_2[0x16] = 0; param_2[0x17] = 0;
    *param_2 = *param_2 & 0xffffa7ff;
    if ((*param_1 & 0x800) != 0) *param_2 = *param_2 | 0x4800;
    if ((*param_1 & 0x1800) != 0) *param_2 = *param_2 | 0x1000;
    uVar1 = param_1[1] & 0xfffeefff;
    if ((param_1[1] & 0x1000) != 0) uVar1 = uVar1 | 0x1000;
    param_2[7] = uVar1; param_2[4] = uVar1; param_2[1] = uVar1;
    param_2[8] = param_1[3]; param_2[9] = param_1[4];
    param_2[5] = param_1[3]; param_2[6] = param_1[4];
    param_2[2] = param_1[3]; param_2[3] = param_1[4];
}

// @ 0x009a8290
void nSPCreatureAnim::converters::ConvertEvent_v9_v10(uint32_t* param_1, uint32_t* param_2)
{
    uint32_t* puVar1 = param_1;
    uint32_t* puVar2 = param_2;
    operator_new__(param_2, 0, 0x60);
    param_2[7] = param_1[1];
    param_2[9] = param_1[2];
    param_2[10] = param_1[3];
    uint32_t uVar7 = *param_1;
    param_1[3] = 0;
    uint32_t acc = 0;
    uint32_t bit = 1;
    uint32_t uVar3 = 0x420;
    while ((uVar7 != 0) && (uVar3 != 0)) {
        uint32_t uVar5 = (uVar3 - 1) & uVar3;
        uVar3 = uVar5 ^ uVar3;
        uint32_t uVar6 = (uint32_t)(-(uint32_t)((uVar3 & uVar7) != 0) & bit);
        bit = bit << 1;
        acc = acc | uVar6;
        uVar7 = uVar7 & ~uVar3;
        uVar3 = uVar5;
    }
    uint32_t res = 0;
    uint32_t bit2 = 1;
    uVar3 = 0xc0;
    while ((acc != 0) && (uVar3 != 0)) {
        uint32_t uVar5 = (uVar3 - 1) & uVar3;
        res = res | (uint32_t)(-(uint32_t)((bit2 & acc) != 0) & (uVar5 ^ uVar3));
        acc = acc & ~bit2;
        bit2 = bit2 * 2;
        uVar3 = uVar5;
    }
    *puVar2 = *puVar2 | res;
    uVar7 = *puVar2;
    if ((*puVar1 & 0x201) == 0x201) {
        if ((*puVar1 & 0x800) != 0) {
            puVar2[0xb] = puVar1[4];
            *puVar2 = uVar7 | 0x200;
        }
    } else {
        puVar2[0xb] = puVar1[5];
        uint32_t uVar4 = FUN_009a4660(0x6000, *puVar1);
        uVar3 = FUN_009a8170(0x300, uVar4);
        *puVar2 = uVar3 | uVar7;
    }
    if ((*puVar1 & 0xc0) == 0) {
        *puVar2 = *puVar2 | 0x20;
    } else if ((*puVar1 & 0xc0) == 0x80) {
        *puVar2 = *puVar2 | 0x10;
    }
    if ((*puVar1 & 0x100) != 0) *puVar2 = *puVar2 | 8;
    if ((*puVar1 & 0x10000) != 0) *puVar2 = *puVar2 | 0x400;
    uVar7 = *puVar1 & 0x201;
    if (0x200 < uVar7) {
        if (uVar7 != 0x201) return;
        *puVar2 = *puVar2 | 3;
        puVar2[1] = puVar2[1] | 0x12;
        puVar2[2] = puVar2[2] | 0x4015;
        return;
    }
    if (uVar7 == 0x200) {
        *puVar2 = *puVar2 | 2;
LAB_009a84a4:
        puVar2[1] = puVar2[1] | 2;
        return;
    }
    if (uVar7 == 0) goto LAB_009a84a4;
    if (uVar7 != 1) return;
    *puVar2 = *puVar2 | 1;
    switch (*puVar1 & 6) {
    case 0:
        puVar2[1] = puVar2[1] | 9;
        if ((*puVar1 & 0x1000) == 0) return;
        puVar2[1] = puVar2[1] | 0x180;
        return;
    case 2:
        goto code_r0x009a8432;
    case 4:
        puVar2[1] = puVar2[1] | 0x15;
        uVar7 = puVar2[1];
        if ((*puVar1 & 0x8008) == 8) goto LAB_009a8478;
        if ((*puVar1 & 0x8008) == 0x8000) { uVar7 = uVar7 | 0x400; goto LAB_009a847d; }
        goto LAB_009a8480;
    case 6:
        break;
    default:
        goto LAB_009a84c2;
    }
    puVar2[1] = puVar2[1] | 0x2000;
code_r0x009a8432:
    puVar2[1] = puVar2[1] | 2;
    uVar7 = puVar2[1];
    if ((*puVar1 & 0x8008) == 8) {
LAB_009a8478:
        uVar7 = uVar7 | 0x200;
LAB_009a847d:
        puVar2[1] = uVar7;
    } else if ((*puVar1 & 0x8008) == 0x8000) {
        uVar7 = uVar7 | 0x400;
        goto LAB_009a847d;
    }
LAB_009a8480:
    if ((*puVar1 & 0x1000) != 0) puVar2[1] = puVar2[1] | 0x180;
    if ((*puVar1 & 0x10) != 0) { *puVar2 = *puVar2 | 0x800; return; }
LAB_009a84c2:
    return;
}

// @ 0x009a85c0
int FUN_009a85c0(uint32_t* param_1, uint32_t* param_2)
{
    uint32_t key = *param_1 & 0x100003;
    switch (key) {
    case 0:
        key = param_1[1];
        break;
    case 1:
        key = 0x746f6f72;
        break;
    default:
        goto LAB_009a8613;
    }
    {
        uint32_t m = *param_1 & 0x801c00;
        if ((m == 0x1800) || (m == 0x1c00)) key = param_1[2];
    }
    {
        uint32_t off = 0;
        int i = 0;
        do {
            if (*(uint32_t*)((DAT_015507a8) + off) == key) {
                if (param_2 == 0) goto LAB_009a8650;
                uint32_t c = 0;
                int* q = (int*)(i * 0x1c + 0x15507ac);
                do {
                    if (*q == 0) break;
                    c++;
                    q++;
                } while (c < 6);
                *param_2 = c;
LAB_009a8650:
                return i * 0x1c + 0x15507ac;
            }
            off += 0x1c;
            i++;
        } while (off < 0x230);
    }
LAB_009a8613:
    if (param_2 != 0) *param_2 = 0;
    return 0;
}

// @ 0x009a8670
namespace nSPCreatureAnim {
unsigned long ComputeAnimationStaticDataSizeBytesForVersion(latest_version::animation_static_data * param_1)
{
    int param_1_v = (int)param_1;
    uint32_t uVar2 = *(uint32_t*)(param_1_v + 4);
    uint32_t uVar1 = *(uint32_t*)(param_1_v + 8);
    if (uVar1 >= 0xe) return uVar2;
    if (uVar1 <= 9) {
        uVar2 = (*(int*)(param_1_v + 0x13c) * 0x60 + 3 + uVar2) & 0xfffffffc;
    }
    if (uVar1 <= 0xd) {
        uVar2 = (uVar2 + 0x203) & 0xfffffffc;
    }
    return uVar2;
}
}  // namespace nSPCreatureAnim
