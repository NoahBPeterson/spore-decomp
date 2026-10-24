// Slice s00fe4be0 -- badge manager property lookup.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

class Property;

// Object stored in the badge map: resolves a property id into an out slot.
class cBadgeObject {
public:
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020();
    virtual bool ResolveProperty(uint32_t key, Property** ppValue); // +0x24
};

// Property value accessor (external).
class Property {
public:
    uint32_t* GetUInt();                                 // 0x0041ea00

    uint8_t  pad000[0x12];                               // +0x00 .. +0x11
    uint16_t mType;                                      // +0x12
};

// Badge map: find returns the slot holding the stored object.
class cBadgePropertyMap {
public:
    cBadgeObject** FUN_00dd85c0(Property** ppValue);     // 0x00dd85c0
};

namespace SP {

class cSPBadgeManager {
public:
    uint32_t FUN_00fe54d0(Property* pProperty);
    void     GetBadgeImageKey();
    void     TestRequirement();

    uint8_t             pad000[0x10];                    // +0x00 .. +0x0f
    cBadgePropertyMap   mBadgeMap;                       // +0x10
};

} // namespace SP

using namespace SP;

// @ 0xfe4be0 FUN_00fe4be0
void __cdecl FUN_00fe4be0()
{
}

// @ 0xfe4d60 FUN_00fe4d60
void __cdecl FUN_00fe4d60()
{
}

// @ 0xfe4e80 FUN_00fe4e80
void __cdecl FUN_00fe4e80()
{
}

// @ 0xfe4fa0 SP::cSPBadgeManager::cSPBadgeManager
void __fastcall cSPBadgeManagerCtor(void* this_, int unused)
{
    (void)this_;
}

// @ 0xfe5430 FUN_00fe5430
void __cdecl FUN_00fe5430()
{
}

namespace SP {

// @ 0xfe54d0 SP::cSPBadgeManager::FUN_00fe54d0
uint32_t __thiscall cSPBadgeManager::FUN_00fe54d0(Property* pProperty)
{
    cBadgeObject** ppSlot = mBadgeMap.FUN_00dd85c0(&pProperty);
    cBadgeObject* pBadge = *ppSlot;
    if (pBadge && pBadge->ResolveProperty(0x60b5892u, &pProperty) && pProperty->mType == 0xa)
        return *pProperty->GetUInt();
    return 0;
}

// @ 0xfe5520 SP::cSPBadgeManager::GetBadgeImageKey
void __thiscall cSPBadgeManager::GetBadgeImageKey()
{
}

// @ 0xfe55b0 SP::cSPBadgeManager::TestRequirement
void __thiscall cSPBadgeManager::TestRequirement()
{
}

} // namespace SP
