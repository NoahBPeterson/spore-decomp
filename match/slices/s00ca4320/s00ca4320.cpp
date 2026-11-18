// Slice s00ca4320 -- inventory-item creation for the vehicle object.
// Mirrors cBuilding::FUN_00bcf490: process the inventory, construct a
// cObjectInstanceInventoryItem, attach the passed owner, add it to the
// inventory, and release the local reference.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct cObjectInstanceInventoryItem;

struct cInventory
{
    virtual void vpad0(); virtual void vpad1(); virtual void vpad2(); virtual void vpad3();
    virtual void vpad4(); virtual void vpad5(); virtual void vpad6(); virtual void vpad7();
    virtual void vpad8(); virtual void vpad9(); virtual void vpad10(); virtual void vpad11();
    virtual void vpad12(); virtual void vpad13(); virtual void vpad14(); virtual void vpad15();
    virtual void vpad16(); virtual void vpad17(); virtual void vpad18(); virtual void vpad19();
    virtual void vpad20(); virtual void vpad21(); virtual void vpad22(); virtual void vpad23();
    virtual void vpad24(); virtual void vpad25(); virtual void vpad26(); virtual void vpad27();
    virtual void vpad28(); virtual void vpad29(); virtual void vpad30(); virtual void vpad31();
    virtual void AddItem(cObjectInstanceInventoryItem* item, int a, int b);   // +0x80
};

struct cObjectInstanceInventoryItem
{
    virtual void vpad0();                              // +0x00
    virtual void AddRef();                             // +0x04
    virtual void Func8();                              // +0x08
    cObjectInstanceInventoryItem* Construct();         // 0x00c6f3d0
    void SetOwner(void* owner);                        // 0x00c6f5e0
};

struct Stimuli
{
    void ClearAll(int mask, int flags);                // 0x00bc98f0
};

struct GameGlobalAt78
{
    void Func(void* owner, void* param);               // 0x00f1aff0
};

struct GameGlobal
{
    uint8_t m_pad0[0x78];                              // +0x00
    GameGlobalAt78* m_at78;                            // +0x78
};
extern GameGlobal* gpGameGlobal;                       // 0x016c7aa4

void* __cdecl operator_new(uint32_t size, const char* name,
                           int a, int b, int c, int d);   // 0x00f473a0

int GetCurrentGameMode();                              // 0x00b5b800

struct cVehicle_s00ca4320
{
    uint8_t m_pad0[0xaf0];                             // +0x0000
    void* mpAF0;                                       // +0x0af0
    uint8_t m_padAf4[0xd94 - 0xaf4];                   // +0x0af4
    cInventory* mpInventoryD94;                        // +0x0d94

    void ProcessEA();                                  // 0x00ca04a0
    bool FUN_00ca4320(void* param);
};

// @ 0x00ca4320
bool cVehicle_s00ca4320::FUN_00ca4320(void* param)
{
    if (mpInventoryD94 != 0) {
        ProcessEA();

        cObjectInstanceInventoryItem* item = (cObjectInstanceInventoryItem*)
            operator_new(0x80, "Simulator/cObjectInstanceInventoryItem", 0, 0, 0, 0);
        if (item != 0) {
            item = item->Construct();
            if (item != 0) {
                item->AddRef();
                item->SetOwner(param);
                mpInventoryD94->AddItem(item, 0, 1);

                if (GetCurrentGameMode() == 0x1654c10)
                    gpGameGlobal->m_at78->Func(this, param);
                item->Func8();
                return true;
            }
        }
    }

    ((Stimuli*)((char*)mpAF0 + 8))->ClearAll(0x8000, 0);
    return false;
}
