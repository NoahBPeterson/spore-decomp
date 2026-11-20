// @ 0x00c1a270
// Slice s00c1a270 (327 bytes, one pointer argument, bool result).
//
// Animation event pump. The event names a target and a source object through the interface
// pointers at +0x3c / +0x40; each interface resolves a component by type key - the creature
// (0xce9f6639) and the combatant (0x1186577). The creature answer is the creature's combat
// manager (CCM): its inner table at +0xb54 holds the animation event rows at +0x8c (12-byte
// entries { key, value, extra }, count at +0x14c). For each of the three event kinds of the
// table at 0x0146a30c that the event's applied-kind mask (+0x8) does not already have, the
// event rows are scanned and every matching row is dispatched through HandleAnimEvent
// (0x00c1a110). The mask is written back and true returned.
//
// False is returned when there is no target interface, no manager, neither a source object
// nor an event id, no creature, or when the manager rejects the creature (e2c0); when the
// manager's e070 probe is false the event scan is skipped and the event still counts as
// handled. The whole condition chain is one nested statement, so the single false exit sits
// behind the true exit at the end of the function - that is the retail block layout (every
// failing branch is a 6-byte near jcc to the shared tail).
//
// Two codegen notes, both matching what the retail compiler did:
//  - A single tail `return false` (instead of plain early `return false`) keeps cl from
//    shrink-wrapping the callee-saved saves into the branches; the whole prologue stays
//    `push ebx/ebp/esi ... push edi`.
//  - The interface slots are read through a volatile view: retail loads +0x3c twice (once
//    for the null test, once for the lookup) and keeps only the second one as the
//    receiver. With plain fields cl proves the second test redundant, deletes its null
//    arm and the whole instruction sequence rotates.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast /GS- (creature module).
#include "types.h"

// Interface whose vtable slot 3 (+0xc) resolves a component by type key.
struct IQueryObject {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void* Query(uint32_t key);              // +0x0c
};

// One row of the manager's event list (12 bytes, base +0x8c).
struct cAnimEventRow {
    uint32_t mKey;                                  // +0x0
    uint32_t mValue;                                // +0x4
    uint32_t mExtra;                                // +0x8
};

// The creature combat manager (CCM_s00c0_ddb0): only the two predicates used here and the
// inner-table pointer at +0xb54 are needed.
class CCM {
public:
    bool e2c0(void* obj);                           // 0x00c0e2c0
    bool e070(void* obj);                           // 0x00c0e070
    char pad0000[0xb54];
    char* mpInner;                                  // +0xb54
};

// The event handed to the pump. The two interface slots have a plain and a volatile view of
// the same pointer; the plain one is the store-side view, the volatile one is the reload.
struct cHitEvent {
    void* mpCreature;                               // +0x00
    uint32_t mId;                                   // +0x04
    uint32_t mAppliedMask;                          // +0x08
    char pad0c[0x30];
    union {
        IQueryObject* mpTarget;                     // +0x3c
        IQueryObject* volatile mpTargetReload;
    };
    union {
        IQueryObject* mpSource;                     // +0x40
        IQueryObject* volatile mpSourceReload;
    };
};

void FUN_00c1a110(uint32_t key, uint32_t value, void* ccm, void* source,
                  uint32_t id);                     // 0x00c1a110

extern const uint32_t kAnimEventKinds[3];           // 0x0146a30c

bool __cdecl FUN_00c1a270(cHitEvent* ev)
{
    if (ev->mpTarget != 0) {
        IQueryObject* target = ev->mpTargetReload;
        void* ccm = target ? target->Query(0xce9f6639) : 0;
        IQueryObject* src = ev->mpSourceReload;
        void* source = src ? src->Query(0x1186577) : 0;
        uint32_t id = ev->mId;

        if (ccm != 0 && (source != 0 || id != 0)) {
            void* creature = ev->mpCreature;
            if (creature != 0 && !((CCM*)ccm)->e2c0(creature)) {
                if (((CCM*)ccm)->e070(creature)) {
                    uint32_t mask = ev->mAppliedMask;
                    char* inner = ((CCM*)ccm)->mpInner;
                    uint32_t count = *(uint32_t*)(inner + 0x14c);
                    cAnimEventRow* rows = (cAnimEventRow*)(inner + 0x8c);
                    for (int i = 0; i < 3; ++i) {
                        if (mask & (1u << i))
                            continue;
                        uint32_t kind = kAnimEventKinds[i];
                        for (uint32_t j = 0; j < count; ++j) {
                            if (rows[j].mKey == kind) {
                                mask |= (1u << i);
                                FUN_00c1a110(kind, rows[j].mValue, ccm, source, id);
                            }
                        }
                    }
                    ev->mAppliedMask = mask;
                }
                return true;
            }
        }
    }
    return false;
}
