// Slice s00dcc830 -- vehicle group orders: the cultural-convert-city order's destructor plus the
// order ticks/activations driven by the vehicle behaviour tree.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

class cRefCounted {
public:
    virtual void r00();
    virtual void Release();                              // +0x04
};

class cAnimatingCreature {
public:
    void Release();                                      // 0x00a05270
};

// Vtable objects installed into the order objects; only their addresses matter here.
struct cOrderVTable0 { int mSlot0; };
struct cOrderVTable1 { int mSlot0; };

extern cOrderVTable0 gCulturalConvertCityOrderVtbl0;
extern cOrderVTable1 gCulturalConvertCityOrderVtbl1;

class cCulturalConvertCityOrder {
public:
    cOrderVTable0* volatile mpVtbl0;                     // +0x00
    cOrderVTable1* volatile mpVtbl1;                     // +0x04
    uint8_t            pad008[0x8c];                     // +0x08 .. +0x93
    cRefCounted*       mpField94;                        // +0x94
    uint8_t            pad098[4];                        // +0x98 .. +0x9b
    cAnimatingCreature* mpField9c;                       // +0x9c
    cRefCounted*       mpFieldA0;                        // +0xa0
    cRefCounted*       mpFieldA4;                        // +0xa4

    ~cCulturalConvertCityOrder();

    // Body of the vehicle-group-order base destructor (0x00b22180).
    void DestroyBase();
};

class cVehicleTree {
public:
    void TradeWithCityOrder_Tick();
    void OfferToBuyCityOrder_Activate();
    void MoveToPointOrder_Activate();
};

class cVehicleTicker {
public:
    void* GetGroupOrder();
};

} // namespace SP

using namespace SP;

namespace SP {

// @ 0xdcc830 SP::VehicleTree::TradeWithCityOrder_Tick
void __thiscall cVehicleTree::TradeWithCityOrder_Tick()
{
}

// @ 0xdcce90 SP::VehicleTree::OfferToBuyCityOrder_Activate
void __thiscall cVehicleTree::OfferToBuyCityOrder_Activate()
{
}

// @ 0xdccfd0 SP::VehicleTree::MoveToPointOrder_Activate
void __thiscall cVehicleTree::MoveToPointOrder_Activate()
{
}

// @ 0xdcd050 FUN_00dcd050
void __fastcall FUN_00dcd050(void* this_, int unused)
{
    (void)this_;
}

// @ 0xdcd180 FUN_00dcd180
void __fastcall FUN_00dcd180(void* this_, int unused)
{
    (void)this_;
}

// @ 0xdcd220 FUN_00dcd220
void __fastcall FUN_00dcd220(void* this_, int unused)
{
    (void)this_;
}

// @ 0xdcd430 SP::cVehicleTicker::GetGroupOrder
void* __thiscall cVehicleTicker::GetGroupOrder()
{
    return 0;
}

// @ 0xdcd530 SP::cCulturalConvertCityOrder::~cCulturalConvertCityOrder
cCulturalConvertCityOrder::~cCulturalConvertCityOrder()
{
    mpVtbl0 = &gCulturalConvertCityOrderVtbl0;
    mpVtbl1 = &gCulturalConvertCityOrderVtbl1;
    if (mpFieldA4)
        mpFieldA4->Release();
    if (mpFieldA0)
        mpFieldA0->Release();
    if (mpField9c)
        mpField9c->Release();
    if (mpField94)
        mpField94->Release();
    DestroyBase();
}

// @ 0xdcd590 FUN_00dcd590
void __fastcall FUN_00dcd590(void* this_, int unused)
{
    (void)this_;
}

} // namespace SP
