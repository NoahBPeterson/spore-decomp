#include "game/types.h"

// Unnamed retail callees (address in the comment).
extern "C" void *SP_NounManager();                        // 0x00b3d300
extern "C" void *FUN_00b1fdb0(void *o);                   // 0x00b1fdb0 cGameNounManager::GetAvatar
extern "C" void *FUN_00c04590(void *o);                   // 0x00c04590 GetCurrent
extern "C" void *FUN_00d99500(void *o);                   // 0x00d99500 creature cast
extern "C" uint8_t FUN_00c0b770(void *o);                 // 0x00c0b770
extern "C" void FUN_00b5f950(void *pField, void *pValue); // 0x00b5f950 AutoRefCount assignment

struct RefObj { void **m_vtbl; };
typedef void (__thiscall *ReleaseThunk)(void *self);

static __forceinline void AutoRefRelease(void **ppField)
{
    void *pOld = *ppField;
    if (pOld != 0) {
        *ppField = 0;
        ((ReleaseThunk)((RefObj *)pOld)->m_vtbl[1])((RefObj *)pOld);
    }
}

struct cCreatureAnimal {
    void    **m_vtbl;      // +0x000
    uint8_t   m_pad004[0xb5a];
    uint8_t   m_b5e;       // +0xb5e
};

// One reference-counted creature handle: a single pointer, read through Get().
struct AutoRefCount {
    void *m_ptr;           // +0x00

    void *Get() const { return m_ptr; }
};

// eastl::vector-style range at +0x40 of the object 0x00c04590 returns
struct CreatureRange {
    AutoRefCount *m_begin;     // +0x00
    AutoRefCount *m_end;       // +0x04
    AutoRefCount *m_capacity;  // +0x08
};
struct CreatureList {
    uint8_t       m_pad00[0x40];
    CreatureRange m_creatures;  // +0x40
};

struct cSPDramaManager {
    void    **m_vtbl;           // +0x00
    uint8_t   m_pad04[0x10];
    AutoRefCount m_babyTeacher14;  // +0x14  AutoRefCount<creature>
    uint8_t   m_pad18[0x20];
    AutoRefCount m_mate38;         // +0x38  AutoRefCount<creature>

    void AssignBabyTeacher();   // 0x00d4b220
};

// @ 0x00d4b220
void cSPDramaManager::AssignBabyTeacher()
{
    if (FUN_00d99500(m_babyTeacher14.Get()) != 0 && m_babyTeacher14.Get() != m_mate38.Get())
        return;

    AutoRefRelease((void **)&m_babyTeacher14);

    void *nounMgr = SP_NounManager();
    void *avatar  = ((void *(__thiscall *)(void *))FUN_00b1fdb0)(nounMgr);

    CreatureRange &creatures =
        ((CreatureList *)((void *(__thiscall *)(void *))FUN_00c04590)(avatar))->m_creatures;
    AutoRefCount *it = creatures.m_begin;

    CreatureRange &creatures2 =
        ((CreatureList *)((void *(__thiscall *)(void *))FUN_00c04590)(avatar))->m_creatures;
    AutoRefCount *end = creatures2.m_end;

    for (; it != end; ++it) {
        void *creature = FUN_00d99500(it->Get());
        if (creature != 0
            && ((uint8_t (__thiscall *)(void *))FUN_00c0b770)(creature)
            && !((uint8_t (__thiscall *)(void *))(*(void ***)((uint8_t *)creature + 0xc0))[0x58 / 4])((uint8_t *)creature + 0xc0)
            && ((cCreatureAnimal *)creature)->m_b5e == 0
            && creature != m_mate38.Get()) {
            ((void (__thiscall *)(void *, void *))FUN_00b5f950)(&m_babyTeacher14, creature);
            return;
        }
    }
}
