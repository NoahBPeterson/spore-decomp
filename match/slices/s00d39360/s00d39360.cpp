// SP::cCreatureModeStrategy::OnCreatureEvent(uint32_t eventID, cKillInfo* info)
//
// Fan-out of one creature event to the strategy's registered listeners, then the
// strategy's own reactions, which are gated on the player's avatar being the
// victim of the event.  The four "report" arms carry a magic message id and two
// zero positions; they hand the avatar's and the animal attacker's species names
// to the event reporter (0x00e39710, cdecl, five arguments).
#include "types.h"

struct cSpeciesData;
// Three zero words handed to the event reporter by address.  The .exe only shows
// three integral words being cleared, so the record is modelled as a 12-byte POD.
struct cCreatureEventPos {
    unsigned int mWord0;    // +0x00
    unsigned int mWord1;    // +0x04
    unsigned int mWord2;    // +0x08
    void Clear() { mWord0 = 0; mWord1 = 0; mWord2 = 0; }
};

// ---------------------------------------------------------------------------
// helpers (addresses in the comments)
// ---------------------------------------------------------------------------
struct cCreatureBase;
class cCreatureAnimal;
class cCreatureModeStrategy;

class cGameNounManager {
public:
    cCreatureBase* GetAvatar();                      // 0x00b1fdb0
};

cGameNounManager* NounManager();                     // 0x00b3d300
extern cCreatureModeStrategy* g_pCreatureModeStrategy;   // 0x0169e294

// Reports one creature event to the UI event log with the two species names and
// the two (empty) positions.  cdecl: the caller pops five arguments.
void ReportCreatureEvent(unsigned int msgID, const char* pAvatarSpecies,
                         const char* pAnimalSpecies,
                         const cCreatureEventPos& animalPos,
                         const cCreatureEventPos& avatarPos);   // 0x00e39710

// ---------------------------------------------------------------------------
// the payload: whom the event happened to, who caused it, and a flag
// ---------------------------------------------------------------------------
struct cKillInfo {
    cCreatureBase* mpVictim;    // +0x00
    cCreatureBase* mpAttacker;  // +0x04
    int            mField08;    // +0x08
};

// virtual interface embedded in a creature at +0xc0
struct cEventTarget {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual bool IsEventTargetActive();     // +0x58
};

struct cCreatureBase {
    virtual void v00();                     // +0x00
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual unsigned int GetNounID();       // +0x20
    unsigned char mPad24[0xc0 - 0x24];
    cEventTarget  mEventTarget;             // +0xc0
    unsigned char mPadC4[0xb20 - 0xc4];
    cSpeciesData* mpSpecies;                // +0xb20
    unsigned char mPadB24[0xb28 - 0xb24];
    char          mInlineSpeciesName[0x14]; // +0xb28  used when mpSpecies is null

    const char* GetSpeciesName();           // 0x00c0bc00
};

// "creature animal" noun id, the type the attacker is filtered to
enum { kCreatureAnimalNoun = 0x18eb45e };

class cCreatureAnimal : public cCreatureBase {
};

// The noun id is checked in the helper below, which the compiler answers with a
// mask (`sub/neg/sbb/not/and`); the caller only has to guard the null pointer.
static __forceinline cCreatureAnimal* TypeCheckedAnimal(cCreatureBase* p) {
    if (p->GetNounID() != kCreatureAnimalNoun)
        return 0;
    return static_cast<cCreatureAnimal*>(p);
}

static __forceinline cCreatureAnimal* AsCreatureAnimal(cCreatureBase* p) {
    cCreatureAnimal* result;
    if (p != 0)
        result = TypeCheckedAnimal(p);
    else
        result = 0;
    return result;
}

// The event interface sits at creature + 0xc0; it is reached through its own
// vtable pointer, i.e. it is an embedded subobject rather than a member pointer.
static __forceinline cEventTarget* EventTargetOf(cCreatureBase* p) {
    return reinterpret_cast<cEventTarget*>(reinterpret_cast<char*>(p) + 0xc0);
}

// interface every event listener implements (callback at vtable +0x18)
struct IListener {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void OnCreatureEvent(unsigned int eventID, cKillInfo* info);  // +0x18
};

class cCreatureModeStrategy {
public:
    void OnCreatureEvent(unsigned int eventID, cKillInfo* info);   // 0x00d39360

    unsigned char mPad00[0x24];
    int           mField24;      // +0x24  counter toggled by the link event
    unsigned char mPad28[0x48 - 0x28];
    unsigned char mField48;      // +0x48  set when the avatar is the victim
    unsigned char mPad49[0xbc - 0x49];
    IListener**   mpListenersBegin;   // +0xbc
    IListener**   mpListenersEnd;     // +0xc0
};

// ---------------------------------------------------------------------------
// @ 0x00d39360
void cCreatureModeStrategy::OnCreatureEvent(unsigned int eventID, cKillInfo* info) {
    // One pair of position records per reporting arm; all four pairs are live for
    // the whole function, which is what the retail frame (0x64 = 4 + 8 * 12) says.
    cCreatureEventPos avatarPos1, animalPos1;
    cCreatureEventPos avatarPos2, animalPos2;
    cCreatureEventPos avatarPos3, animalPos3;
    cCreatureEventPos avatarPos4, animalPos4;

    IListener** const pListenersEnd = mpListenersEnd;
    IListener** pp = mpListenersBegin;
    while (pp != pListenersEnd) {
        (*pp)->OnCreatureEvent(eventID, info);
        ++pp;
    }

    switch (eventID) {
    case 0x045ab96e:                                   // avatar died
        if (info->mpVictim != NounManager()->GetAvatar())
            return;
        mField48 = 1;
        return;

    case 0x060b4124: {                                 // animal attack on the avatar
        cCreatureBase* avatar = NounManager()->GetAvatar();
        cCreatureAnimal* animal = AsCreatureAnimal(info->mpAttacker);
        if (info->mpVictim != avatar || animal == 0)
            return;
        avatarPos1.Clear();
        animalPos1.Clear();
        ReportCreatureEvent(0x3b29c983, avatar->GetSpeciesName(),
                            animal->GetSpeciesName(), animalPos1, avatarPos1);
        return;
    }

    case 0x060b4123: {                                 // second animal attack flavour
        cCreatureBase* avatar = NounManager()->GetAvatar();
        cCreatureAnimal* animal = AsCreatureAnimal(info->mpAttacker);
        if (info->mpVictim != avatar || animal == 0)
            return;
        avatarPos2.Clear();
        animalPos2.Clear();
        ReportCreatureEvent(0xfc6ce3b4, avatar->GetSpeciesName(),
                            animal->GetSpeciesName(), animalPos2, avatarPos2);
        return;
    }

    case 0x533535da: {                                 // animal socialising with the avatar
        cCreatureBase* avatar = NounManager()->GetAvatar();
        cCreatureAnimal* animal = AsCreatureAnimal(info->mpAttacker);
        if (info->mpVictim != avatar || animal == 0)
            return;
        avatarPos3.Clear();
        animalPos3.Clear();
        ReportCreatureEvent(0x81ad32e9, avatar->GetSpeciesName(),
                            animal->GetSpeciesName(), animalPos3, avatarPos3);
        return;
    }

    case 0xd335362c: {                                 // attack that must be seen
        cCreatureBase* avatar = NounManager()->GetAvatar();
        cCreatureAnimal* animal = AsCreatureAnimal(info->mpAttacker);
        cCreatureBase* victim = info->mpVictim;
        if (victim == 0)
            return;
        if (!EventTargetOf(victim)->IsEventTargetActive())
            return;
        if (animal == 0 || avatar == 0)
            return;
        avatarPos4.Clear();
        animalPos4.Clear();
        ReportCreatureEvent(0x64487065, avatar->GetSpeciesName(),
                            animal->GetSpeciesName(), animalPos4, avatarPos4);
        return;
    }

    case 0xd3353637:                                   // link / unlink
        if (info->mField08 == 0)
            --g_pCreatureModeStrategy->mField24;
        else
            ++g_pCreatureModeStrategy->mField24;
        return;
    }
}
