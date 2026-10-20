// slice s00a027a0 -- SP::cAnimatingCreature animation-predicate helpers and small accessors
// from the nSPCreatureAnim subsystem of SporeApp.exe (32-bit, MSVC 2008 SP1 /O2).
//
//   @ 0x00a027a0  IsOrientIdleAnim(uint32)      orient idle-anim handle test
//   @ 0x00a02800  IsRestIdleAnim(uint32)        rest idle-anim handle test (falls back to orient)
//   @ 0x00a02840  IsMoveIdleAnim(uint32)        move idle-anim handle test
//   @ 0x00a02a00  cAnimatingCreature::         forward a 3-argument request to the handle table
//   @ 0x00a02ab0  cAnimatingCreature::         attach a slot (by handle or the root slot)
//   @ 0x00a02b00  cAnimatingCreature::         remove a slot
//   @ 0x00a02b40  cAnimatingCreature::         query slot A, false when there is no table
//   @ 0x00a02b70  cAnimatingCreature::         query slot B, false when there is no table
//   @ 0x00a02bd0  cAnimatingCreature::         current selector (falls back to slot 0 when 4)
//   @ 0x00a02bf0  cAnimatingCreature::         store a mode flag and a 3-dword value
//   @ 0x00a02c40  SetRestIdleAnimHandle()      pick the rest idle anim for every live slot
//   @ 0x00a02cd0  cAnimatingCreature::         swap the byte at +0x48, return the old one
//   @ 0x00a02ce0  cAnimatingCreature::         store a byte and two dwords
//   @ 0x00a02d00  cAnimatingCreature::         set one entry of the selector table
//   @ 0x00a02d40  thunk                        forward five dwords plus a zero
//   @ 0x00a02d70  thunk                        forward one pointer to the root-slot lookup
//
// Build: /O2 /MD /Gy /TP /arch:SSE /fp:fast   (no /EHsc)
#include "types.h"

typedef unsigned char uint8;
typedef unsigned int  uint32;

// ------------------------------------------------------------------ external code

bool   __stdcall IsOrientStopAnim(uint32 id);                 // 0x00a02740
void*  __cdecl   FindSlot(void* table, uint32 v);             // 0x009ff6f0
void*  __cdecl   RootSlot(void* table);                       // 0x009ff750
bool   __cdecl   QuerySlotA(void* table, int v, int flags);   // 0x009ff7c0
int    __cdecl   QuerySlotB(void* table, int v);              // 0x009ff7a0
uint32 __cdecl   PackHandle(uint32 v, uint8 idx);             // 0x009fef70
void   __cdecl   Forward3(void* table, int a, int b, int c);  // 0x00a00180
void   __cdecl   BigForward(int, int, int, int, int, int);    // 0x009b2340

// ------------------------------------------------------------------ node / table layout

struct Node {                                                 // 0xf0 bytes, table+8
    char   pad0[0xb4];
    uint32 value;                                             // +0xb4
    char   pad1[0xd8 - 0xb8];
    uint32 id;                                                // +0xd8
    char   pad2[0xf0 - 0xdc];
};

struct HandleTable {
    char   pad0[8];
    Node   nodes[16];                                         // +0x008
    char   pad1[0xf0c - 0xf08];
    uint32 tbl[16];                                           // +0x00f0c
    char   pad2[0xf8c - 0xf4c];
    uint8  live[16];                                          // +0x00f8c

    void __thiscall Detach(void* p, int flags);               // 0x00a00f90
    void __thiscall Remove(int v);                            // 0x00a01050
};

struct cAnimatingCreature {
    char          pad00[0x38];
    uint8         f38;                                        // +0x038
    char          pad39[3];
    int           f3c;                                        // +0x03c
    int           f40;                                        // +0x040
    char          pad44[4];
    uint8         f48;                                        // +0x048
    char          pad49[7];
    int           sel50[2];                                   // +0x050 / +0x054
    char          pad58[0x154 - 0x58];
    int           f154;                                       // +0x154
    char          pad158[0x164 - 0x158];
    int           f164;                                       // +0x164
    int           f168;                                       // +0x168
    int           f16c;                                       // +0x16c
    char          pad170[0x184 - 0x170];
    HandleTable*  table;                                      // +0x184
    uint32        f188;                                       // +0x188

    void __thiscall Forward(int a, int b, int c);             // 0x00a02a00
    bool __thiscall Attach(int v);                            // 0x00a02ab0
    bool __thiscall Detach(int v);                            // 0x00a02b00
    bool __thiscall QueryA(int v);                            // 0x00a02b40
    bool __thiscall QueryB(int v);                            // 0x00a02b70
    int  __thiscall Selector();                               // 0x00a02bd0
    void __thiscall SetMode(const int* v, uint8 b);           // 0x00a02bf0
    void __thiscall SetRestIdleAnimHandle();                  // 0x00a02c40
    uint8 __thiscall Swap48(uint8 v);                         // 0x00a02cd0
    void __thiscall Set38(uint8 a, int b, int c);             // 0x00a02ce0
    void __thiscall SetSel(int i, int v);                     // 0x00a02d00
};

// ------------------------------------------------------------------ @ 0x00a027a0

// @ 0x00a027a0
bool __stdcall IsOrientIdleAnim(uint32 id)
{
    if (id != 0x4866d8e && id != 0x452b634 && id != 0x5cb2176) {
        if (!IsOrientStopAnim(id) &&
            id != 0x4866dab && id != 0x5cb2177 && id != 0x44828e9 &&
            id != 0x4482906 && id != 0x452b64a)
            return false;
    }
    return true;
}

// ------------------------------------------------------------------ @ 0x00a02800

// @ 0x00a02800
bool __stdcall IsRestIdleAnim(uint32 id)
{
    if (id != 0x2481de5 && id != 0x27844ad && id != 0x4330667 && id != 0x5b6ddae) {
        if (!IsOrientIdleAnim(id))
            return false;
    }
    return true;
}

// ------------------------------------------------------------------ @ 0x00a02840

// @ 0x00a02840
bool __stdcall IsMoveIdleAnim(uint32 id)
{
    if (id == 0x2481de6 || id == 0x354559b || id == 0x35455a4 ||
        id == 0x4485a08 || id == 0x4485a0f)
        return true;
    return false;
}

// ------------------------------------------------------------------ @ 0x00a02a00

// @ 0x00a02a00
void __thiscall cAnimatingCreature::Forward(int a, int b, int c)
{
    Forward3(table, a, b, c);
}

// ------------------------------------------------------------------ @ 0x00a02ab0

// @ 0x00a02ab0
bool __thiscall cAnimatingCreature::Attach(int v)
{
    void* p = v ? FindSlot(table, (uint32)v) : RootSlot(table);
    if (p)
        table->Detach(p, 0);
    return true;
}

// ------------------------------------------------------------------ @ 0x00a02b00

// @ 0x00a02b00
bool __thiscall cAnimatingCreature::Detach(int v)
{
    table->Remove(v);
    return true;
}

// ------------------------------------------------------------------ @ 0x00a02b40

// @ 0x00a02b40
bool __thiscall cAnimatingCreature::QueryA(int v)
{
    if (table)
        return QuerySlotA(table, v, 0);
    return false;
}

// ------------------------------------------------------------------ @ 0x00a02b70

// @ 0x00a02b70
bool __thiscall cAnimatingCreature::QueryB(int v)
{
    if (table) {
        bool found = QuerySlotB(table, v) != 0;
        return found;
    }
    return false;
}

// ------------------------------------------------------------------ @ 0x00a02bd0

// @ 0x00a02bd0
int __thiscall cAnimatingCreature::Selector()
{
    int v = sel50[1];
    if (v == 4)
        v = sel50[0];
    return v;
}

// ------------------------------------------------------------------ @ 0x00a02bf0

// @ 0x00a02bf0
void __thiscall cAnimatingCreature::SetMode(const int* v, uint8 b)
{
    f154 = (b != 0) + 1;
    f164 = v[0];
    f168 = v[1];
    f16c = v[2];
}

// ------------------------------------------------------------------ @ 0x00a02c40

// @ 0x00a02c40
void __thiscall cAnimatingCreature::SetRestIdleAnimHandle()
{
    for (uint32 i = 0; i < 16; i++) {
        if (table->live[i]) {
            uint32 idx = table->tbl[i];
            Node* n = &table->nodes[idx];
            if (n->id == 0x2481de5 || n->id == 0x27844ad || n->id == 0x4330667 || n->id == 0x5b6ddae ||
                IsOrientIdleAnim(n->id))
                f188 = PackHandle(n->value, (uint8)idx);
        }
    }
}

// ------------------------------------------------------------------ @ 0x00a02cd0

// @ 0x00a02cd0
uint8 __thiscall cAnimatingCreature::Swap48(uint8 v)
{
    uint8 old = f48;
    f48 = v;
    return old;
}

// ------------------------------------------------------------------ @ 0x00a02ce0

// @ 0x00a02ce0
void __thiscall cAnimatingCreature::Set38(uint8 a, int b, int c)
{
    f38 = a;
    f3c = b;
    f40 = c;
}

// ------------------------------------------------------------------ @ 0x00a02d00

// @ 0x00a02d00
void __thiscall cAnimatingCreature::SetSel(int i, int v)
{
    sel50[i] = v;
}

// ------------------------------------------------------------------ @ 0x00a02d40

// @ 0x00a02d40
void __stdcall Forward5(int a, int b, int c, int d, int e)
{
    BigForward(a, b, c, d, e, 0);
}

// ------------------------------------------------------------------ @ 0x00a02d70

struct RootThunk { void* __thiscall RootOnly(void* p); };

// @ 0x00a02d70
void* __thiscall RootThunk::RootOnly(void* p)
{
    return RootSlot(p);
}
