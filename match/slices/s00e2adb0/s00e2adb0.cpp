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
#include <intrin.h>

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
class cSPUILayout
{ public:
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
class cSPUIPropertyLayout : public IWinProc { public:
    uint32_t pad04[2];
    cSPUILayout mLayout;                     // +0x0c
    virtual bool DoMessage(IWindow* window, const Message& message);       // 0x00828080
};

// ---- the rollover ------------------------------------------------------------------------------------
class cSPUIRolloverCivCityHall : public cSPUIPropertyLayout { public:
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

// ---------------------------------------------------------------- eastl rbtree / UI cursor attachment helpers
extern "C" void EASTL_allocator_deallocate(void* p);

class cString
{
public:
    ~cString();
    char mData[0x10];
};

struct CStringNode
{
    CStringNode* mpLeft;        // +0x00
    CStringNode* mpRight;       // +0x04
    uint8_t      mPad08[0x0c];  // +0x08
    cString      mValue;        // +0x14
};

struct CStringTree
{
    void DoNukeSubtree(CStringNode* node);
};

// @ 0x00e2b680
void CStringTree::DoNukeSubtree(CStringNode* node)
{
    while (node != 0) {
        DoNukeSubtree(node->mpLeft);
        CStringNode* right = node->mpRight;
        node->mValue.~cString();
        EASTL_allocator_deallocate(node);
        node = right;
    }
}

struct WorldNode
{
    WorldNode* mpLeft;          // +0x00
    WorldNode* mpRight;         // +0x04
    uint32_t   mPad08;          // +0x08
    uint32_t   mPad0c;          // +0x0c
    uint32_t   mKey[5];         // +0x10
};

struct WorldTree
{
    uint32_t mField00;          // +0x00
    WorldNode* mpLeft;          // +0x04 (header/sentinel link)
    WorldNode* mpRight;         // +0x08
    WorldNode* mpRoot;          // +0x0c
    uint8_t  mColor;            // +0x10
    uint8_t  mPad11[3];
    uint32_t mSize;             // +0x14

    void NukeSubtree(void* node);
    void Clear();
    void InsertNode(WorldNode** out, WorldNode* parent, const uint32_t* key, bool left);
};

extern "C" void eastl_RBTreeInsert(WorldNode* node, WorldNode* parent, WorldNode* header, bool side);

// @ 0x00e2adb0
void __fastcall FUN_00e2adb0(void* self)
{
    WorldTree* tree = (WorldTree*)((uint8_t*)self + 0x78);
    void* root = tree->mpRoot;
    tree->NukeSubtree(root);
    WorldNode* sentinel = (WorldNode*)&tree->mpLeft;
    tree->mpRight = sentinel;
    sentinel->mpLeft = sentinel;
    tree->mpRoot = 0;
    tree->mColor = 0;
    tree->mSize = 0;
}

void WorldTree::Clear()
{
    NukeSubtree(mpRoot);
    mpRight = mpLeft;
    mpLeft->mpLeft = mpLeft;
    mpRoot = 0;
    mColor = 0;
    mSize = 0;
}

// @ 0x00e2b6c0
void WorldTree::InsertNode(WorldNode** out, WorldNode* parent, const uint32_t* key, bool left)
{
    int side;
    if (!left && parent != (WorldNode*)&mpLeft && key[0] >= parent->mKey[0])
        side = 1;
    else
        side = 0;

    WorldNode* node = (WorldNode*)operator new(0x24, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (&node->mKey[0]) {
        node->mKey[0] = key[0];
        node->mKey[1] = key[1];
        node->mKey[2] = key[2];
        node->mKey[3] = key[3];
        node->mKey[4] = key[4];
    }
    eastl_RBTreeInsert(node, parent, (WorldNode*)&mpLeft, side);
    mSize++;
    *out = node;
}

struct SmallNode
{
    SmallNode* mpLeft;          // +0x00
    SmallNode* mpRight;         // +0x04
    void*      mpValue;         // +0x08
    uint8_t    mByte0c;         // +0x0c
    uint8_t    mPad0d[3];
    uint32_t   mKey0;           // +0x10
    uint32_t   mKey1;           // +0x14
};

// @ 0x00e2b7f0
void __stdcall FUN_00e2b7f0(SmallNode* source, void* value)
{
    SmallNode* node = (SmallNode*)operator new(0x18, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    uint32_t* key = &node->mKey0;
    if (key != 0) {
        key[0] = source->mKey0;
        key[1] = source->mKey1;
    }
    node->mpLeft = 0;
    node->mpRight = 0;
    node->mpValue = value;
    node->mByte0c = source->mByte0c;
}

class CPL
{
public:
    CPL();
    ~CPL();
    void*       mpVtable0;      // +0x00
    void*       mpVtable1;      // +0x04
    uint32_t    mPad08;         // +0x08
    struct CursorLayout
    {
        char mData[0x6c];
        IWindow* FindWindowByID(uint32_t id, bool recursive);
    } mLayout;                  // +0x0c .. +0x77
};

struct CursorLayoutAt0c
{
    char mData[0x6c];
    IWindow* FindWindowByID(uint32_t id, bool recursive);
};

class CursorAttachment : public CPL
{
public:
    CursorAttachment();

    WorldTree mTree;            // +0x78
    uint32_t  mPad90;           // +0x90
    int32_t   mField94;         // +0x94
    uint32_t  mField98;         // +0x98
    uint32_t  mField9c;         // +0x9c
    uint32_t  mFielda0;         // +0xa0
    uint8_t   mFielda4;         // +0xa4
    uint8_t   mFielda5;         // +0xa5
    uint8_t   mFielda6;         // +0xa6
    uint8_t   mPada7;           // +0xa7
    uint32_t  mFielda8;         // +0xa8

    void read_properties();
    void SetKey(const wchar_t* key, uint32_t value);
    void SetRootWindowId(uint32_t id);
    void SetPurposeIcon(int purpose);
    bool HandleUIMessage(IWindow* window, const Message& message);
};

// @ 0x00e2b8e0
CursorAttachment::CursorAttachment()
{
    uint32_t zero = 0;
    mpVtable0 = (void*)0x1481700;
    mpVtable1 = (void*)0x14816f0;
    _ReadWriteBarrier();

    mTree.mpRight = (WorldNode*)zero;
    mTree.mpRoot = (WorldNode*)zero;
    mTree.mColor = (uint8_t)zero;

    WorldNode* sentinel = (WorldNode*)&mTree.mpLeft;
    sentinel->mpLeft = sentinel;
    mTree.mpRight = sentinel;
    mTree.mpRoot = (WorldNode*)zero;
    mTree.mColor = (uint8_t)zero;
    mTree.mSize = zero;

    mField98 = zero;
    mField9c = zero;
    mFielda4 = (uint8_t)zero;
    mFielda5 = (uint8_t)zero;
    mFielda8 = zero;
    mField94 = -1;
    mFielda0 = 1;
    mFielda6 = 1;

    read_properties();
    SetKey(L"RolloverCivCity", 0x40464100);
    SetRootWindowId(0x199a7de);
}

class Object : public CPL
{
public:
    WorldTree mTree;            // +0x78
    Object* _virtual_dtor(unsigned flags);
};

// @ 0x00e2b990
Object* Object::_virtual_dtor(unsigned flags)
{
    WorldTree* tree = &mTree;
    mpVtable0 = (void*)0x1481700;
    mpVtable1 = (void*)0x14816f0;
    void* root = tree->mpRoot;
    tree->NukeSubtree(root);
    this->CPL::~CPL();
    if (flags & 1)
        EASTL_allocator_deallocate(this);
    return this;
}

struct CursorNode
{
    PV2 PV2 PV2 PV                 // slots 0..6
    virtual int GetControlID();    // +0x1c (slot 7)
    PV4 PV PV                     // slots 8..13
    virtual float* GetVector();    // +0x38 (slot 14)
    PV16                          // slots 15..30
    virtual void SetSelected(int mode, bool selected); // +0x7c (slot 31)
    PV16 PV2 PV                   // slots 32..50
    virtual void GetBegin(void** out);   // +0xcc (slot 51)
    virtual void GetEnd(void** out);     // +0xd0 (slot 52)
};

extern int32_t g_cursorListOffset;      // 0x01440aec
extern "C" void Pollinator(void* node, float* value); // 0x00806d10

// @ 0x00e2b4f0
void CursorAttachment::SetPurposeIcon(int purpose)
{
    IWindow* found = mLayout.FindWindowByID(0x3058a88, true);
    if (found != 0) {
        CursorNode* window = (CursorNode*)found;
        void* begin;
        void* end;
        window->GetBegin(&begin);
        window->GetEnd(&end);
        while (begin != end) {
            void* next = *(void**)begin;
            CursorNode* node = (CursorNode*)((uint8_t*)begin + g_cursorListOffset);
            int control = node->GetControlID();
            node->SetSelected(1, control == purpose);
            begin = next;
        }
    }
}

// @ 0x00e2b580
bool CursorAttachment::HandleUIMessage(IWindow* window, const Message& message)
{
    if (message.eventType == 0x11) {
        if (window->GetControlID() == 0x199a7de) {
            IWindow* found = mLayout.FindWindowByID(0x3058a88, true);
            if (found != 0) {
                CursorNode* cursorWindow = (CursorNode*)found;
                float* vector = cursorWindow->GetVector();
                float value[4];
                value[0] = vector[0];
                value[1] = vector[1];
                value[2] = vector[2];
                value[3] = vector[3];

                void* begin;
                void* end;
                cursorWindow->GetBegin(&begin);
                cursorWindow->GetEnd(&end);
                while (begin != end) {
                    void* next = *(void**)begin;
                    CursorNode* node = (CursorNode*)((uint8_t*)begin + g_cursorListOffset);
                    int control = node->GetControlID();
                    node->SetSelected(1, control == 0x338babf);
                    Pollinator(node, value);
                    begin = next;
                }
            }
        }
    }
    return false;
}
