// src/game/SPCreatureAnim/parts_caps.cpp -- migrated from slice(s) s009fb8e0, s009a7810 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/parts_caps.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t DAT_015506c8[];   // deform rbtree overload table

// ---- items of slice s009a7810 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t DAT_015506c8[];   // deform rbtree overload table
namespace nSPCreatureAnim {
    int* GetAvailableDeformsForContextTarget(uint32_t* p, uint32_t* out);
}
// ---- items of slice s009a7810 end

// ---- items of slice s009fb8e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void*  g_1551774;   // 0x01551774  "deform"
extern void*  g_14487f4;   // 0x014487f4  vftable
typedef unsigned int   uint32;
extern void*  operator_new(uint32 size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
typedef void  (__thiscall *vt_v_ii)(void*, int, int);
#define VT(obj, off)  (*(void***)(obj))[(off) / 4]
struct Elem14 {
    void* b;
    void* e;
    void* c;
    uint32 pad;
    uint32 val;
    void assign(void* begin, void* end);   // 0x00454cb0
    void RangeInitialize(int n);           // 0x00475ab0
};
// ---- items of slice s009fb8e0 end

// @ 0x009a84f0
int* rbtree_find(int* param_1, uint32_t param_2, int param_3, uint32_t* param_4)
{
    uint32_t uVar3 = 0;
    int* piVar1 = param_1;
    if (param_2 != 0) {
        do {
            if (*piVar1 == param_3) {
                if (param_4 == 0) return param_1 + uVar3 * 7 + 1;
                uint32_t uVar2 = 0;
                int* q = param_1 + uVar3 * 7 + 1;
                do {
                    if (*q == 0) break;
                    uVar2++;
                    q++;
                } while (uVar2 < 6);
                *param_4 = uVar2;
                return param_1 + uVar3 * 7 + 1;
            }
            uVar3++;
            piVar1 += 7;
        } while (uVar3 < param_2);
    }
    if (param_4 != 0) *param_4 = 0;
    return 0;
}

// @ 0x009a8560
int* nSPCreatureAnim::GetAvailableDeformsForContextTarget(uint32_t* param_1, uint32_t* param_2)
{
    if ((*param_1 & 0x101c03) == 0) {
        return rbtree_find((int*)&DAT_015506c8, 8, (int)param_1[1], param_2);
    }
    if ((*param_1 & 0x100003) == 1) {
        return rbtree_find((int*)&DAT_015506c8, 8, 0x746f6f72, param_2);
    }
    if (param_2 != 0) *param_2 = 0;
    return 0;
}

// @ 0x009fc3e0
void cCommandBase_InitDeform(void* self, int a, int b)
{
    *(int*)((char*)self + 0x30) = b;
    // FUN_0083c780(a, b)
    extern void FUN_0083c780(int, int);      // 0x0083c780
    FUN_0083c780(a, b);
    void* cmd = operator_new(0x10, "ArgScript/Deform", 0, 0, 0, 0);
    if (cmd)
        *(void**)cmd = &g_14487f4;
    ((vt_v_ii)VT(self, 0x18))(self, (int)(size_t)g_1551774, (int)(size_t)cmd);
}

// @ 0x009fc680
void ElemAssignFrom(Elem14* a, Elem14* b, Elem14* c)
{
    for (Elem14* p = a; p != b; p = (Elem14*)((char*)p + 0x14)) {
        if (c != p)
            p->assign(c->b, c->e);
        p->val = c->val;
    }
}

// @ 0x009fc970
Elem14* ElemMove(Elem14* a, Elem14* b, Elem14* c)
{
    for (; a != b; a = (Elem14*)((char*)a + 0x14), c = (Elem14*)((char*)c + 0x14)) {
        if (a != c)
            c->assign(a->b, a->e);
        c->val = a->val;
    }
    return c;
}
