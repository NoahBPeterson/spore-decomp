// Slice s00cfe160 -- civilisation relation helpers and pointer-slot setters.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

// Civilisation object; the owner id is virtual slot 0x4c.
class cCivilization {
public:
    virtual void v000(); virtual void v004(); virtual void v008();
    virtual void* GetMember(uint32_t key);               // +0x0c
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048();
    virtual int32_t GetOwnerId();                        // +0x4c

    cCivilization* GetCivilization();                    // 0x00bd9bf0
};

// Growable pointer list of civilisations.
struct tCivilizationList {
    cCivilization** mpBegin;                             // +0x00
    cCivilization** mpEnd;                               // +0x04
    cCivilization** mpCapacity;                          // +0x08
};

class cGameNounManager {
public:
    tCivilizationList* GetCivilizationList();            // 0x00b25ca0
    cCivilization* GetPlayerCivilization();              // 0x00b25fb0
};

class cRelationshipManager {
public:
    int32_t GetAttitude(int32_t ownerA, int32_t ownerB, int32_t mode); // 0x00d00a70
};

extern cGameNounManager*      __cdecl NounManager();       // 0x00b3d300
extern cRelationshipManager*  __cdecl RelationshipManager(); // 0x00b3d2c0

} // namespace SP

using namespace SP;

// Pointer slot table with two scalar slots and a pointer array.
class cCivRefTable {
public:
    cCivilization* SetField0C(cCivilization* pValue);
    cCivilization* SetField10(cCivilization* pValue);
    cCivilization* SetEntry(int32_t index, cCivilization* pValue);

    uint8_t         pad000[0x0c];                        // +0x000 .. +0x00b
    cCivilization*  mpField0C;                           // +0x00c
    cCivilization*  mpField10;                           // +0x010
    cCivilization*  mpEntries[1];                        // +0x014
};

// @ 0xcfe160 FUN_00cfe160
void __cdecl FUN_00cfe160()
{
}

// @ 0xcfe5b0 FUN_00cfe5b0
void __cdecl FUN_00cfe5b0()
{
}

// @ 0xcfe780 cCivRefTable::SetField0C
cCivilization* __thiscall cCivRefTable::SetField0C(cCivilization* pValue)
{
    cCivilization* pOld = mpField0C;
    mpField0C = pValue;
    return pOld;
}

// @ 0xcfe790 cCivRefTable::SetField10
cCivilization* __thiscall cCivRefTable::SetField10(cCivilization* pValue)
{
    cCivilization* pOld = mpField10;
    mpField10 = pValue;
    return pOld;
}

// @ 0xcfe7a0 cCivRefTable::SetEntry
cCivilization* __thiscall cCivRefTable::SetEntry(int32_t index, cCivilization* pValue)
{
    cCivilization* pOld = mpEntries[index];
    mpEntries[index] = pValue;
    return pOld;
}

// @ 0xcfe820 SP::GetTributeAmount
void __cdecl GetTributeAmount()
{
}

// @ 0xcfe930 SP::IsAllied
bool __cdecl IsAllied(cCivilization* pCiv)
{
    tCivilizationList* pList = NounManager()->GetCivilizationList();
    int32_t count = (int32_t)(pList->mpEnd - pList->mpBegin);
    for (int32_t i = 0; i < count; ++i) {
        cCivilization* pOther = pList->mpBegin[i];
        if (pOther == NounManager()->GetPlayerCivilization())
            continue;
        if (pOther == pCiv)
            continue;
        int32_t playerOwner = NounManager()->GetPlayerCivilization()->GetOwnerId();
        if (RelationshipManager()->GetAttitude(pOther->GetOwnerId(), playerOwner, 1) >= 4)
            return true;
    }
    return false;
}

// @ 0xcfe9c0 FUN_00cfe9c0
void __cdecl FUN_00cfe9c0(cCivilization* pObject, cCivilization** ppCity, cCivilization** ppOwner)
{
    cCivilization* pCity = pObject ? (cCivilization*)pObject->GetMember(0x901f1362) : 0;
    *ppCity = pCity;
    cCivilization* pOwner = pObject ? (cCivilization*)pObject->GetMember(0xee9b2232) : 0;
    *ppOwner = pOwner;
    if (!*ppCity && pOwner)
        *ppCity = pOwner->GetCivilization();
}

// @ 0xcfea20 FUN_00cfea20
void __cdecl FUN_00cfea20()
{
}

// @ 0xcfeac0 FUN_00cfeac0
void __cdecl FUN_00cfeac0()
{
}

// @ 0xcfeb40 FUN_00cfeb40
void __cdecl FUN_00cfeb40()
{
}

// Summarizer base pair (multiple inheritance: second base at +4).
class cSummarizerBase {
public:
    virtual void v000();                                 // +0x00
};

class ContentValidationSummarizer {
public:
    virtual void v000();                                 // +0x00
};

extern float gField169d388;                              // 0x0169d388
extern float gField169d38c;                              // 0x0169d38c
extern float gField169d390;                              // 0x0169d390

class cSummarizer : public cSummarizerBase, public ContentValidationSummarizer {
public:
    cSummarizer();

    int32_t  mField08;                                   // +0x08
    int32_t  mField0C;                                   // +0x0c
    int32_t  mField10;                                   // +0x10
    int32_t  mField14;                                   // +0x14
    int32_t  mField18;                                   // +0x18
    float    mField1C;                                   // +0x1c
    float    mField20;                                   // +0x20
    float    mField24;                                   // +0x24
    int32_t  mField28;                                   // +0x28
};

// @ 0xcfec10 cSummarizer::cSummarizer
__thiscall cSummarizer::cSummarizer()
{
    mField08 = 0;
    mField0C = 0;
    mField10 = 0;
    mField14 = -1;
    mField18 = -1;
    mField1C = gField169d388;
    mField20 = gField169d38c;
    mField24 = gField169d390;
    mField28 = 0;
}

// Subsystem with a second base at +4; the derived fields follow it.
class cGonzagoSubsystem {
public:
    cGonzagoSubsystem();                                 // 0x00b5b960
    virtual void v000();                                 // +0x00
};

class cSecondBase {
public:
    virtual void v000();                                 // +0x00
    uint8_t mPayload[0x14];                              // +0x04 .. +0x17
};

class cGonzagoChild : public cGonzagoSubsystem, public cSecondBase {
public:
    cGonzagoChild();

    int32_t mField1C;                                    // +0x1c
    int32_t mField20;                                    // +0x20
    int32_t mField24;                                    // +0x24
};

// @ 0xcfecc0 cGonzagoChild::cGonzagoChild
__thiscall cGonzagoChild::cGonzagoChild()
{
    mField1C = 0;
    mField20 = 0;
    mField24 = 0;
}

// @ 0xcfee00 SP::FindTargetCity
void __cdecl FindTargetCity()
{
}
