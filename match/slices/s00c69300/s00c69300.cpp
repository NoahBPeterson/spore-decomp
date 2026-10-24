// Slice s00c69300 - SporeApp 0x00c69300..0x00c6a4d0
// Simulator::cGameData serialization helpers, Object::Cast and cHerd helpers.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// NOTE: the remaining slice VAs were not reconstructed in this pass and are
// recorded as unreconstructed in partial.txt.
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------
struct cPlanetModel {
    void SnapB();                 // 0x00b82970
};

struct cCreatureModeStrategy {
    bool HasCreatureTutorialOccurred();   // 0x00d38980
};

struct cVec3 {
    float mX;                     // 0x00
    float mY;                     // 0x04
    float mZ;                     // 0x08
};

u32 __stdcall SP_PlanetModel(u32 a, u32 b, u32 c);            // 0x00b3d350
void* GetCurrentGameMode();                                   // 0x00b5b800
cCreatureModeStrategy* __stdcall GetCreatureModeStrategy(u32 key);  // 0x00d38840

// vtable slot 0x2c dispatch (no arguments, returns bool in al)
static inline bool VT_2C_0(void* p)
{
    return ((bool (__thiscall*)(void*))(*(void***)p)[11])(p);
}

// ---------------------------------------------------------------------------------------------
// Simulator::cGameData
// ---------------------------------------------------------------------------------------------
struct cGameData {
    char Slot40(int param);       // 0x00b183f0
    void Refresh();               // 0x00c69600

    char Activate(int param);     // 0x00c697e0
};

// @ 0x00c697e0
// Initializes the game data, refreshing it when the vtable callback reports
// that it changed.
char cGameData::Activate(int param)
{
    char ok = Slot40(param);
    if (ok)
        Refresh();
    return ok;
}

// ---------------------------------------------------------------------------------------------
// Object
// ---------------------------------------------------------------------------------------------
struct cObjectBase {
    void* CastBase(int type);     // 0x00b18460
};

struct cObject {
    void* Cast(int type);         // 0x00c69db0
};

// @ 0x00c69db0
// Type-checked cast: returns this for the two game-data type ids, otherwise
// defers to the base implementation.
void* cObject::Cast(int type)
{
    if (type == (int)0xee3f516e)
        return this;
    if (type == (int)0x52aa6117)
        return this;
    return ((cObjectBase*)this)->CastBase(type);
}

// ---------------------------------------------------------------------------------------------
// Free helpers
// ---------------------------------------------------------------------------------------------
// @ 0x00c69bc0
// Creates the planet model for a pair of ids, snaps it and returns the first id.
u32 __stdcall SP_CreatePlanetAndSnap(u32 a, u32 b)
{
    cPlanetModel* model = (cPlanetModel*)SP_PlanetModel(a, b, 0);
    model->SnapB();
    return a;
}

// @ 0x00c69e30
// True when the object's vtable slot 0x2c reports success.
int SP_ObjectCheck(void* p)
{
    if (p != 0) {
        if (VT_2C_0(p))
            return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// cHerd
// ---------------------------------------------------------------------------------------------
struct cHerd {
    u8     mPad0000[0x15c];
    int    mState15c;             // 0x15c
    u8     mPad0160[0x208 - 0x160];
    u8     mFlag208;              // 0x208
    u8     mPad0209[0x20c - 0x209];
    cVec3  mTarget20c;            // 0x20c

    void SetTarget(const cVec3* v);   // 0x00c69ff0
    bool ShouldActivate();            // 0x00c6a030
};

// @ 0x00c69ff0
void cHerd::SetTarget(const cVec3* v)
{
    mFlag208 = 1;
    mTarget20c = *v;
}

// @ 0x00c6a030
// Whether the herd should activate now: always except in the tutorial state,
// where it depends on the creature tutorial having been seen already.
bool cHerd::ShouldActivate()
{
    if (mState15c != 9)
        return true;
    if (GetCurrentGameMode() != (void*)0x01654c01)
        return false;
    cCreatureModeStrategy* strategy = GetCreatureModeStrategy(0x7aee5ee7);
    return strategy->HasCreatureTutorialOccurred() == false;
}
