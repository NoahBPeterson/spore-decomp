// Slice s00d6e2e0 -- SP::PLAY_FIGHT_Decide (decide callback of the play-fight behaviour).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// callees (call targets are masked by the checker).  Addresses are used through
// explicit calling-convention casts so cl emits the retail ABI.
// ---------------------------------------------------------------------------
#define TCS(ret, params, name) ((ret(__thiscall*)params) name)

void* FUN_004d47d0(void*, int);                 // 0x004d47d0 thiscall, one stack arg
void* FUN_00bc9b00(uint32_t, void*, void*);     // 0x00bc9b00 stdcall (callee pops 3 dwords)
void* FUN_00bca620(void*);                      // 0x00bca620 thiscall
char  FUN_00bc9b50(void*);                      // 0x00bc9b50 thiscall (AtBegin)
void* FUN_00c04590(void*);                      // 0x00c04590 thiscall (Get)
char  FUN_00c0b770(void*);                      // 0x00c0b770 thiscall
char  FUN_00d6dcf0();                           // 0x00d6dcf0 SP::PLAY_FIGHT_Activate

extern float g_1470f1c;                         // 0x01470f1c 2.0f

// ---------------------------------------------------------------------------
// object layouts (offsets taken from the retail instruction diff)
// ---------------------------------------------------------------------------
struct Species {
    char  _p000[0x58c];
    float mf58c;                                // +0x58c
};

struct BehaviorTree {
    char     _p000[0x1d0];
    uint32_t mTypeId;                           // +0x1d0
};

struct Creature {
    char  _p000[0xb20];
    void* mpSpecies;                            // +0xb20
};

struct Neighbor {
    char          _p000[0x135];
    uint8_t       mFlag135;                     // +0x135
    char          _p136[0xb4c - 0x136];
    BehaviorTree* mpTree;                       // +0xb4c
    char          _p0b50[0xb5e - 0xb50];
    uint8_t       mDead;                        // +0xb5e
};

struct NeighborList {
    char   _p000[0x40];
    void** mpBegin;                             // +0x40
    void** mpEnd;                               // +0x44
};

// ===========================================================================
// @ 0x00d6e2e0  SP::PLAY_FIGHT_Decide
// ===========================================================================
float __cdecl PLAY_FIGHT_Decide(Creature* self, int a1, int a2, int a3,
                                void* stimuli, char* out, int a6, void* p7)
{
    (void)a1; (void)a2; (void)a3; (void)stimuli; (void)out; (void)a6; (void)p7;

    if (TCS(void*, (void*, int), FUN_004d47d0)(self->mpSpecies, 0x1f)
        && !(g_1470f1c > ((Species*)self->mpSpecies)->mf58c)) {
        void* it = ((void*(__stdcall*)(uint32_t, void*, void*)) FUN_00bc9b00)(
                        (uint32_t)0x53031f1, (void*)FUN_00d6dcf0, (void*)self);
        void* node = TCS(void*, (void*), FUN_00bca620)(it);
        if (node == 0) {
            NeighborList* list = TCS(NeighborList*, (void*), FUN_00c04590)(self);
            void** p = list->mpBegin;
            void** end = list->mpEnd;
            for (; p != end; ++p) {
                Neighbor* c = (Neighbor*)*p;
                if (TCS(char, (void*), FUN_00c0b770)(c)
                    && c->mFlag135 != 0
                    && c->mDead == 0
                    && c->mpTree->mTypeId == 0x2d876b9u)
                    return 1.0f;
            }
        } else {
            if (!TCS(char, (void*), FUN_00bc9b50)(node))
                return 1.0f;
        }
        return 0.0f;
    }
    return 0.0f;
}
