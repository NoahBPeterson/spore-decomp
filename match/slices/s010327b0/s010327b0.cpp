// Slice s010327b0: simulated-agent interaction teardown.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef void* Vp;

struct cVec3 {
    float x;
    float y;
    float z;
};

// ---------------------------------------------------------------------------------------------
// Globals referenced by this routine
// ---------------------------------------------------------------------------------------------

extern float g_016ded38;              // 0x016ded38  default event origin, x
extern float g_016ded3c;              // 0x016ded3c  default event origin, y
extern float g_016ded40;              // 0x016ded40  default event origin, z
extern const float g_01470f1c;        // 0x01470f1c  2.0f
extern const float g_013ec4b4;        // 0x013ec4b4  0.9f
extern const float g_01485720;        // 0x01485720  1.0f
extern const float g_014996fc;        // 0x014996fc  FLT_MAX
extern const float g_013eb1bc;        // 0x013eb1bc  -1.0f

// ---------------------------------------------------------------------------------------------
// External helpers
// ---------------------------------------------------------------------------------------------

extern "C" void FUN_00f47380(void* p);       // 0x00f47380  operator delete[] (array form)
extern "C" Vp   FUN_00b3d260();              // 0x00b3d260  BehaviorManager accessor
extern "C" Vp   FUN_00b3d350();              // 0x00b3d350  PlanetModel accessor

// Sub-object at +0x34 of an agent target.  Only its member calls are used, so the body is an
// opaque byte span sized by the embedding struct.
struct cBehaviorHost {
    void F421B0(int flag);                   // 0x00c421b0
    void F41D60(void* value);                // 0x00c41d60
};

struct cPlanetModel {
    cVec3* DirectionToSurfacePosition(cVec3* out, void* value);   // 0x00b815a0
    cVec3* F81630(cVec3* out, void* value);                       // 0x00b81630
    float  F7E430(void* value, char flag);                        // 0x00b7e430
};

// Target returned by the 0xaeb336b4 hash lookup.
struct cAgentTargetA {
    unsigned char mPad00[0x34];               // +0x00
    cBehaviorHost mHost;                      // +0x34
    unsigned char mHostTail1[0x224 - 0x35];   // +0x35
    int  mField224;                           // +0x224  raycast result code
    unsigned char mHostTail2[0x528 - 0x228];  // +0x228
    unsigned char mbField528;                 // +0x528  cleared when the pass completes
    unsigned char mHostTail3[0x5e8 - 0x529];  // +0x529
    unsigned char mField5E8;                  // +0x5e8  attention sub-object
};

// Target returned by the 0x283d961 hash lookup.
struct cAgentTargetB {
    unsigned char mPad00[0x34];               // +0x00
    cBehaviorHost mHost;                      // +0x34
    unsigned char mHostTail1[0x224 - 0x35];   // +0x35
    int  mField224;                           // +0x224  raycast result code
    unsigned char mHostTail2[0x5d0 - 0x228];  // +0x228
    unsigned char mField5D0;                  // +0x5d0  attention sub-object
};

// Target returned by the 0x2dd8c33 hash lookup.
struct cAgentExtra {
    unsigned char mPad00[0x660];              // +0x00
    float mf660;                              // +0x660
};

// 0x74-byte event block handed to vtable slot 0xdc of an agent host.  Members are spelled out
// individually (no byte arrays) so that the local does not trip the /GS stack-cookie heuristic,
// which the retail build does not use here.
struct cAgentEvent {
    void* mpObject;              // +0x00  released through the array-delete path
    void* mpField04;             // +0x04  cleared
    void* mpField08;             // +0x08  cleared
    void* mpField0C;             // +0x0c
    void* mpField10;             // +0x10
    cVec3 mOrigin;               // +0x14
    float mf20;                  // +0x20
    void* mpField24;             // +0x24  cleared
    unsigned mField28;           // +0x28
    unsigned mField2C;           // +0x2c
    unsigned mField30;           // +0x30
    unsigned mField34;           // +0x34
    unsigned mField38;           // +0x38
    unsigned mField3C;           // +0x3c
    unsigned mField40;           // +0x40
    unsigned mField44;           // +0x44
    unsigned mField48;           // +0x48
    unsigned char mb4C;          // +0x4c  cleared
    unsigned char mb4D;          // +0x4d
    unsigned char mb4E;          // +0x4e
    unsigned char mb4F;          // +0x4f
    float mf50;                  // +0x50  cleared
    float mf54;                  // +0x54  cleared
    float mf58;                  // +0x58  cleared
    void* mpField5C;             // +0x5c  cleared
    float mf60;                  // +0x60
    float mf64;                  // +0x64
    float mf68;                  // +0x68
    float mf6C;                  // +0x6c  cleared
    void* mpField70;             // +0x70  cleared
};

// Sub-object at +0x80 of the interaction object; hands out the direction slot for an agent.
struct cInteractionOwner {
    cVec3* F0FEE0(void** source);            // 0x00d0fee0
};

// 0x18-byte filter description passed by value (the noun plus the agent id and four payload
// dwords that are only forwarded).
struct cAgentFilterRange {
    void* mpNoun;            // +0x00  noun owning the bit-pool agent table
    unsigned mId;            // +0x04  agent id: block = id >> 7, entry = id & 0x7f
    unsigned mField08;       // +0x08  forwarded unchanged
    unsigned mField0C;       // +0x0c  forwarded unchanged
    unsigned mField10;       // +0x10  forwarded unchanged
    unsigned mField14;       // +0x14  forwarded unchanged
};

struct cInteraction {
    unsigned char mPad00[0x80];              // +0x00
    cInteractionOwner mOwner;                // +0x80

    void RemoveAgent(cAgentFilterRange range);     // 0x00abedb0
    void TeardownAgent(cAgentFilterRange range);
};

// ---------------------------------------------------------------------------------------------
// Vtable dispatch helpers (the agent objects are opaque; only the slot offsets are known)
// ---------------------------------------------------------------------------------------------

static inline Vp VC0(void* p, int offset)
{
    return ((Vp(__thiscall*)(void*))(*(Vp**)p)[offset / 4])(p);
}

static inline Vp VC1P(void* p, int offset, void* arg)
{
    return ((Vp(__thiscall*)(void*, void*))(*(Vp**)p)[offset / 4])(p, arg);
}

static inline Vp VC1U(void* p, int offset, unsigned arg)
{
    return ((Vp(__thiscall*)(void*, unsigned))(*(Vp**)p)[offset / 4])(p, arg);
}

// Fills the event block with the defaults used for an agent interaction pass.
static inline void InitAgentEvent(cAgentEvent& ev)
{
    ev.mOrigin.x = g_016ded38;
    ev.mOrigin.y = g_016ded3c;
    ev.mOrigin.z = g_016ded40;
    ev.mf20 = g_01485720;
    ev.mf60 = g_01470f1c;
    ev.mf64 = g_013ec4b4;
    ev.mf68 = g_014996fc;
    ev.mpObject = 0;
    ev.mpField04 = 0;
    ev.mpField08 = 0;
    ev.mpField24 = 0;
    ev.mb4C = 0;
    ev.mf50 = 0.0f;
    ev.mf54 = 0.0f;
    ev.mf58 = 0.0f;
    ev.mpField5C = 0;
    ev.mf6C = 0.0f;
    ev.mpField70 = 0;
}

// Releases the array-style payload the event block may still own.
static inline void ReleaseAgentEvent(cAgentEvent& ev)
{
    void* p = ev.mpObject;
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        FUN_00f47380(p);
}

// ---------------------------------------------------------------------------------------------
// Implementation
// ---------------------------------------------------------------------------------------------

// @ 0x010327b0
void cInteraction::TeardownAgent(cAgentFilterRange range)
{
    // The noun owns a table of bit-pool blocks; block[id >> 7] holds 0x80 eight-byte agent
    // entries and the handle lives in the second dword of entry[id & 0x7f].
    void** pools = *(void***)range.mpNoun;
    void** block = (void**)pools[range.mId >> 7];
    void* agent = block[(range.mId & 0x7f) * 2 + 1];

    RemoveAgent(range);

    if (agent == 0)
        return;

    cVec3 surfaceDir;

    // ---- first hash: 0xce9f6639 -------------------------------------------------------------
    Vp obj1 = VC1U(agent, 0x08, 0xce9f6639u);
    if (obj1 != 0) {
        VC0(obj1, 0x00);            // AddRef
        VC1U(obj1, 0x9c, 0);        // clear one flag
        VC0(obj1, 0x54);            // refresh
    }

    // ---- second hash: 0xaeb336b4 ------------------------------------------------------------
    Vp obj2 = VC1U(agent, 0x08, 0xaeb336b4u);
    if (obj2 != 0) {
        cAgentTargetA* target = (cAgentTargetA*)obj2;

        VC0(obj2, 0x00);            // AddRef

        Vp mgr = FUN_00b3d260();    // BehaviorManager
        VC1P(mgr, 0x3c, &target->mField5E8);

        target->mHost.F421B0(0);

        Vp value = VC0(&target->mHost, 0x2c);
        cPlanetModel* planet = (cPlanetModel*)FUN_00b3d350();
        cVec3* dir = planet->DirectionToSurfacePosition(&surfaceDir, value);
        VC1P(&target->mHost, 0x38, dir);

        target->mField224 = 0;

        cAgentEvent event;
        InitAgentEvent(event);
        VC1P(&target->mHost, 0xdc, &event);
        ReleaseAgentEvent(event);

        target->mHost.F41D60(&g_016ded38);

        Vp source = VC0(&target->mHost, 0x2c);
        cVec3* slot = mOwner.F0FEE0(&obj2);
        *slot = *(const cVec3*)source;

        target->mbField528 = 0;
    }

    // ---- third hash: 0x283d961 --------------------------------------------------------------
    Vp obj3 = VC1U(agent, 0x08, 0x283d961u);
    if (obj3 != 0) {
        cAgentTargetB* target = (cAgentTargetB*)obj3;

        VC0(obj3, 0x00);            // AddRef

        Vp mgr = FUN_00b3d260();    // BehaviorManager
        VC1P(mgr, 0x3c, &target->mField5D0);

        target->mHost.F421B0(0);

        Vp value = VC0(&target->mHost, 0x2c);
        cPlanetModel* planet = (cPlanetModel*)FUN_00b3d350();
        cVec3* dir = planet->F81630(&surfaceDir, value);
        VC1P(&target->mHost, 0x38, dir);

        Vp probe = VC0(&target->mHost, 0x2c);
        float distance = ((cPlanetModel*)FUN_00b3d350())->F7E430(probe, 1);
        target->mField224 = (distance > 0.0f) ? 6 : 0;

        cAgentEvent event;
        InitAgentEvent(event);
        VC1P(&target->mHost, 0xdc, &event);
        ReleaseAgentEvent(event);

        target->mHost.F41D60(&g_016ded38);

        Vp extra = VC1U(obj3, 0x0c, 0x2dd8c33u);
        if (extra != 0)
            ((cAgentExtra*)extra)->mf660 = g_013eb1bc;

        VC0(obj3, 0x04);            // Release
    }

    if (obj2 != 0)
        VC0(obj2, 0x04);            // Release
    if (obj1 != 0)
        VC0(obj1, 0x04);            // Release
}
