// cSPUIRolloverCivCityHall::DoMessage @ 0x00E2ADE0  (1798 bytes, __thiscall ret 8; vtable slot of the
// IWinProc interface: UTFWin::IWinProc::HandleUIMessage(IWindow*, const Message&) -> bool).
//
// The civ-stage city hall rollover UI. Flags: /O2 /MD /Gy /TP /GS- /arch:SSE.
//   * message 0x11 (window id 0x199a7de): reset the specialty icon, clear the caption of the vehicle window
//     0x46adf86 and re-register this window proc on it
//   * message 0xe (text changed) from window 0x46adf86: parse the caption as a number and set the clamped
//     (0..100) value on the sub-interface 0x10edf11 of that window; text changes of 0x2cf2f74 are swallowed
//   * message 0x287259f6 (button): the data word selects an action on the city this rollover shows
//       0x62d6902 / 0x62d6908 / 0x62d690f  buy vehicle 0 / 1 / 2: affordable? -> create it, pay, tutorial
//                                          hint, "vehicle bought" event
//       0x62d5618                          select the city hall and post a message
//   * every path ends in the base cSPUIPropertyLayout::DoMessage
// Every callee/global is a masked relocation, so the stub classes below fix only calling conventions,
// argument lists, and vtable slots / field offsets used here.
#include "types.h"
#include <stdlib.h>

#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16

void* operator new(unsigned int size, const char* name, int flags, unsigned int debugFlags, const char* file, int line);   // 0x00F473A0

// SSE clamp helper (inline asm in the original headers: maxss/minss against the memory params)
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

enum
{
    kGameModeCiv   = 0x01654c04,
    kGameModeSpace = 0x01654c05,
};

struct ResourceKey { uint32_t instanceID, typeID, groupID; };
struct Vector3 { float x, y, z; };

// ---- UTFWin ------------------------------------------------------------------------------------------
struct IWinProc;
struct IWindow;

struct ISlider        // interface cast out of a window (typeID 0x10edf11)
{
    PV
    virtual void SetValue(float v);        // +0x4
};

struct IWindow
{
    PV2 PV                                   // +0x00 .. +0x08
    virtual ISlider* Cast(uint32_t typeID);  // +0x0c
    PV2 PV                                   // +0x10 .. +0x18
    virtual uint32_t GetControlID();         // +0x1c
    PV4 PV2 PV                               // slots 8..14 (+0x20 .. +0x38)
    virtual const wchar_t* GetCaption();     // +0x3c
    PV16                                     // slots 16..31
    virtual void SetCaption(const wchar_t*); // +0x80
    PV32                                     // slots 33..64
    virtual void AddWinProc(IWinProc* p);    // +0x104 (slot 65)
};

struct Message
{
    IWindow* source;      // +0x00
    int      field_04;
    int      eventType;   // +0x08
    int      param;       // +0x0c
};

// ---- game objects ------------------------------------------------------------------------------------
struct cSPUILayout
{
    char data[0x9c];
    IWindow* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0 (thiscall, ret 8)
};

struct IVehicleSub          // polymorphic member of the vehicle at +0x34
{
    PV32 PV4 PV2                             // slots 0..37
    virtual void* Slot98();                  // +0x98
};
struct cVehicle
{
    char pad000[0x34];
    IVehicleSub mSub34;                      // +0x34 (embedded, own vtable)
    char pad038[0xb20 - 0x38];
    int mType;                               // +0xb20
    void FUN_00ca80e0(int v);                // 0x00ca80e0 (ret 4)
};

struct cCivBase3c { uint32_t pad; uint32_t mValue; };
struct cCivilization
{
    char pad000[0x3c];
    cCivBase3c mBase3c;                      // +0x3c (member +4 is read)
    int FUN_00bf2100(int specialty);                         // 0x00bf2100 (ret 4): how many are available
    float FUN_00bf2170(int specialty, int index);            // 0x00bf2170 (ret 8): vehicle cost
    float FUN_00bef6d0();                                    // 0x00bef6d0: current money
    void SpendMoney(float amount);                           // 0x00bef710 (ret 4)
    const ResourceKey* GetModelTypeKey(int modelType);       // 0x00bf9770 (ret 4)
    char* FUN_00bef950();                                    // 0x00bef950
};

struct ICitySub { PV16 PV4 PV2 virtual bool Slot58(); };   // +0x58 (slot 22)
struct cCityHall;
struct cCity
{
    char pad000[0x120];
    ICitySub mSub120;                        // +0x120 (embedded, own vtable)
    int GetVehicleSpecialty();                               // 0x00bd81d0 (returns [this+0x540])
    cCityHall* GetCityHall();                                // 0x00bd9b40
    cVehicle* FUN_00bddda0(int specialty, int index, ResourceKey key, bool spaceStage);   // 0x00bddda0 (ret 0x18)
};

struct cTerrainSphere { void FUN_00c77bf0(uint32_t key); };  // 0x00c77bf0 (ret 4)
struct cGameNounManager
{
    cCivilization* GetPlayerCivilization();                  // 0x00b25fb0
    cTerrainSphere* GetCurrentTerrainSphere();               // 0x00f67d90 (returns [this+0x74])
};

struct cStrategyState { char pad[0x110]; cCityHall* mpSelectedCityHall; };   // +0x110
struct cCivModeStrategy
{
    char pad000[0xe8];
    cStrategyState* mpState;                 // +0xe8
    static cCivModeStrategy* Get();                          // 0x00cf74c0
    cStrategyState* FUN_00cf74f0();                          // 0x00cf74f0: returns [this+0xe8]
    void FUN_00cf84a0();                                     // 0x00cf84a0
    void FUN_00cf8ec0(cVehicle* v);                          // 0x00cf8ec0 (ret 4)
    void DoNextCivTutorial(uint32_t hint, int arg);          // 0x00cfa990 (ret 8)
};

// message server / message objects
struct cMessage
{
    virtual void v0();
    virtual int AddRef();                    // +0x04
    virtual int Release();                   // +0x08
    char pad004[0x8 - 0x4];
    int mSource;                             // +0x08
    char pad0c[0x30 - 0xc];
    uint32_t mMessageID;                     // +0x30
    char pad34[0x40 - 0x34];
};
struct MessageBasicRC5 : public cMessage { MessageBasicRC5(int arg); };   // 0x00421c80
struct cMessageServer
{
    PV4 PV2
    virtual void PostMSG(uint32_t id, cMessage* msg, int a, int b);   // +0x18
};
cMessageServer* MessageServer();                       // 0x0067dcc0
struct MsgPtr                                          // eastl::intrusive_ptr<cMessage>
{
    cMessage* mpObject;
    MsgPtr(cMessage* p);                               // 0x0061df40 (out of line, AddRefs)
    ~MsgPtr() { if (mpObject) mpObject->Release(); }
};

cGameNounManager* NounManager();                       // 0x00b3d300
int GetCurrentGameMode();                              // 0x00b5b800
int FUN_00c9e6d0(int specialty, int index);            // 0x00c9e6d0 (cdecl): model type of a vehicle
// 0x00e3c7c0 (cdecl): play a "vehicle bought" event
void FUN_00e3c7c0(uint32_t hash, char* where, void* src, Vector3* offset, uint32_t civValue, int a, int b);

struct IWinProc { virtual void v0(); };
struct cSPUIPropertyLayout : public IWinProc
{
    uint32_t pad04[2];
    cSPUILayout mLayout;                     // +0x0c
    virtual bool DoMessage(IWindow* window, const Message& message);       // 0x00828080
};

// ---- the rollover ------------------------------------------------------------------------------------
struct cSPUIRolloverCivCityHall : public cSPUIPropertyLayout
{
    cCity* mpCity;                           // +0xa8
    void SetSpecialtyIcon(int index);        // 0x00e2a7b0 (ret 4)
    virtual bool DoMessage(IWindow* window, const Message& message);
};

// One "buy vehicle" button: the three variants differ only in the vehicle index, the tutorial hint and the
// sound/event hashes selected by the vehicle's type.
template <int Index, uint32_t Hint, uint32_t Ev0, uint32_t Ev1, uint32_t Ev2, bool TerrainEdit>
static __forceinline void BuyVehicle(cSPUIRolloverCivCityHall* self, cCivilization* civ)
{
    if (civ->FUN_00bf2100(self->mpCity->GetVehicleSpecialty()) <= 0)
        return;
    const float cost = civ->FUN_00bf2170(self->mpCity->GetVehicleSpecialty(), Index);
    if (!(civ->FUN_00bef6d0() >= cost))
        return;
    const ResourceKey* key = civ->GetModelTypeKey(FUN_00c9e6d0(self->mpCity->GetVehicleSpecialty(), Index));
    cVehicle* vehicle = self->mpCity->FUN_00bddda0(self->mpCity->GetVehicleSpecialty(), Index, *key,
                                                   GetCurrentGameMode() == kGameModeSpace);
    if (vehicle)
        vehicle->FUN_00ca80e0(10);
    civ->SpendMoney(cost);
    if (!vehicle)
        return;
    if (Hint)
        cCivModeStrategy::Get()->DoNextCivTutorial(Hint, 0);
    else
        cCivModeStrategy::Get()->FUN_00cf84a0();
    cCivModeStrategy::Get()->FUN_00cf8ec0(vehicle);
    uint32_t ev = Ev0;
    if (vehicle->mType != 0)
    {
        if (vehicle->mType == 1)
            ev = Ev1;
        else if (vehicle->mType == 2)
            ev = Ev2;
    }
    Vector3 zero;
    zero.x = 0.0f; zero.y = 0.0f; zero.z = 0.0f;
    FUN_00e3c7c0(ev, NounManager()->GetPlayerCivilization()->FUN_00bef950() + 0x504,
                 vehicle->mSub34.Slot98(), &zero,
                 NounManager()->GetPlayerCivilization()->mBase3c.mValue, 0, 0);
    if (TerrainEdit && GetCurrentGameMode() == kGameModeCiv)
        NounManager()->GetCurrentTerrainSphere()->FUN_00c77bf0(0x5dd433e);
}

// @ 0x00E2ADE0
bool cSPUIRolloverCivCityHall::DoMessage(IWindow* window, const Message& message)
{
    if (message.eventType == 0x11 && window->GetControlID() == 0x199a7de)
    {
        SetSpecialtyIcon(0);
        uint32_t empty = 0;
        mLayout.FindWindowByID(0x46adf86, true)->SetCaption((const wchar_t*)&empty);
        mLayout.FindWindowByID(0x46adf86, true)->AddWinProc((IWinProc*)this);
        goto done;
    }

    if (message.eventType == 0xe)
    {
        if (message.param == 2 && window->GetControlID() == 0x46adf86)
        {
            const wchar_t* text = message.source->GetCaption();
            if (text)
            {
                const float value = (float)wcstod(text, 0);
                ISlider* slider = mLayout.FindWindowByID(0x46adf86, true)->Cast(0x10edf11);
                if (slider)
                    slider->SetValue(Clamp(value, 0.0f, 100.0f));
            }
            goto done;
        }
        if (message.eventType == 0xe && message.param == 2 && window->GetControlID() == 0x2cf2f74)
            goto done;
    }

    if (message.eventType == 0x287259f6 && mpCity != 0 && mpCity->mSub120.Slot58())
    {
        cCivilization* civ = NounManager()->GetPlayerCivilization();
        switch (message.param)
        {
        case 0x62d6908:
            if (civ)
                BuyVehicle<1, 0x6d3814ed, 0x300602f6, 0x10d02b2a, 0x8b3fcdf4, false>(this, civ);
            break;
        case 0x62d5618:
        {
            cCityHall* cityHall = mpCity->GetCityHall();
            cCivModeStrategy::Get()->FUN_00cf74f0()->mpSelectedCityHall = cityHall;
            NounManager()->GetCurrentTerrainSphere()->FUN_00c77bf0(0x52da1f5);
            MessageBasicRC5* raw = new ("App", 0, 0, 0, 0) MessageBasicRC5(0);
            MsgPtr msg(raw);
            msg.mpObject->mMessageID = 0xb2699148;
            msg.mpObject->mSource = -1;
            MessageServer()->PostMSG(msg.mpObject->mMessageID, msg.mpObject, 0, 0);
            break;
        }
        case 0x62d6902:
            if (civ)
                BuyVehicle<0, 0, 0x703af052, 0xad067a5e, 0xe7454134, false>(this, civ);
            break;
        case 0x62d690f:
            if (civ)
                BuyVehicle<2, 0xced8b9d4, 0xf5195d53, 0x1181713f, 0x01ca7441, true>(this, civ);
            break;
        }
    }
done:
    return cSPUIPropertyLayout::DoMessage(window, message);
}
