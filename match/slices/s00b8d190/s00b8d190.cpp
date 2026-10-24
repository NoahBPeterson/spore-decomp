// Slice s00b8d190 -- the planet-model editor object (cPlanetModel): its message handler and cursor
// flags, the bio-protector banner lookup, the three 0x2c/0x1c element containers (append, erase,
// destroy, index) and the small key/name accessors shared with the creature editor.
//
// Object layout used by this slice (cPlanetModel):
//   +0x20  handler host (virtual slot 0xac), +0x24 cursor host (virtual slot 0x8c),
//   +0x28  mode word, +0x2c cursor/visibility flags (0x40, 0x100, 0x200, 0x400, 0x800),
//   +0x78 / +0xea  dirty bytes, +0xec  current index (-1 when idle),
//   +0xd4/+0xd8/+0xdc  0x1c-byte element container, +0x134/+0x138  0x2c-byte element container,
//   +0x15c/+0x160 and +0x170/+0x174  pointer containers, +0x184  star handle, +0x194  count,
//   +0x1a4..+0x1ac  the three-word property key.
//
// Flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define PV(n) virtual void pv##n();

// --------------------------------------------------------------------------- opaque services
namespace SP {
    void* __stdcall StarManager(uint32_t id);             // 0x00b3d2a0
    void* __stdcall GetMissionManager(uint32_t id);        // 0x00feb9f0
    void  GetPropertyAsKey(uint32_t property, uint32_t key, void* out); // 0x006a1250
}

void* __cdecl FUN_00f48a80();                             // 0x00f48a80
void  __cdecl FUN_00f47380(void* block);                  // 0x00f47380 (operator delete[])
uint32_t __cdecl FUN_0067dd50();                          // 0x0067dd50

// --------------------------------------------------------------------------- interfaces
struct cKeyService {                                      // returned by 0x00f48a80
    PV(0)
    virtual int32_t v1(uint32_t* key);                    // +0x04
};

struct cHandlerHost {
    PV(0)  PV(1)  PV(2)  PV(3)  PV(4)  PV(5)  PV(6)  PV(7)  PV(8)  PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42)
    virtual void v43();                                   // +0xac
};

struct cCursorHost {
    PV(0)  PV(1)  PV(2)  PV(3)  PV(4)  PV(5)  PV(6)  PV(7)  PV(8)  PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34)
    virtual void v35(uint32_t value);                     // +0x8c
};

struct cStarObject {
    int32_t  FUN_00bb99e0();                              // 0x00bb99e0
    uint32_t FUN_00ba6440();                              // 0x00ba6440
    void     FUN_00ba6660();                              // 0x00ba6660
    uint32_t FUN_00ba6d80();                              // 0x00ba6d80
    void*    FUN_00bb9b80();                              // 0x00bb9b80
};

struct cMission {
    int32_t FUN_00c4b220();                               // 0x00c4b220
};

struct cMissionManager {
    cMission* FUN_00fee220();                             // 0x00fee220
};

struct cOwnedElem {
    void FUN_00ff2e30();                                  // 0x00ff2e30
};

struct cOwnedElem2 {
    void FUN_00c2e4e0();                                  // 0x00c2e4e0
};

struct cKey3 {                                            // three-word property key
    uint32_t m0;                                          // +0x00
    uint32_t m4;                                          // +0x04
    uint32_t m8;                                          // +0x08
    cKey3() : m0(0), m4(0), m8(0) {}
};

struct cBioElem {                                         // 0x2c-byte bio-protector record
    int32_t  m00;                                         // +0x00
    float    m04;                                         // +0x04
    float    m08;                                         // +0x08
    float    m0C;                                         // +0x0c
    uint16_t m10;                                         // +0x10
    uint8_t  m12;                                         // +0x12
    uint8_t  mPad13;                                      // +0x13
    float    m14;                                         // +0x14
    int32_t  m18;                                         // +0x18
    int32_t  m1C;                                         // +0x1c
    int32_t  m20;                                         // +0x20
    int32_t  m24;                                         // +0x24
    uint8_t  m28;                                         // +0x28
    uint8_t  mPad29[3];                                   // +0x29
};

struct cBioElemSort {                                     // sort predicate object
    uint8_t  mPad00[0x184];                               // +0x000
    uint32_t mField184;                                   // +0x184
    uint32_t SortBanners();                               // 0x00b8de30
};

// --------------------------------------------------------------------------- planet model
struct cPlanetModel {
    uint8_t  mPad00[0x20];                                // +0x000
    cHandlerHost* mField20;                               // +0x020
    cCursorHost*  mField24;                               // +0x024
    int32_t  mField28;                                    // +0x028
    uint32_t mField2C;                                    // +0x02c
    uint8_t  mPad30[0x48];                                // +0x030
    uint8_t  mField78;                                    // +0x078
    uint8_t  mPad79[0x5b];                                // +0x079
    char*    mFieldD4;                                    // +0x0d4
    char*    mFieldD8;                                    // +0x0d8
    char*    mFieldDC;                                    // +0x0dc
    uint8_t  mPadE0[0x0a];                                // +0x0e0
    uint8_t  mFieldEA;                                    // +0x0ea
    uint8_t  mPadEB;                                      // +0x0eb
    int32_t  mFieldEC;                                    // +0x0ec
    uint8_t  mPadF0[0x44];                                // +0x0f0
    char*    mField134;                                   // +0x134
    char*    mField138;                                   // +0x138
    uint8_t  mPad13C[0x20];                               // +0x13c
    char*    mField15C;                                   // +0x15c
    char*    mField160;                                   // +0x160
    uint8_t  mPad164[0x0c];                               // +0x164
    char*    mField170;                                   // +0x170
    char*    mField174;                                   // +0x174
    uint8_t  mPad178[0x0c];                               // +0x178
    uint32_t mField184;                                   // +0x184
    uint8_t  mPad188[0x0c];                               // +0x188
    int32_t  mField194;                                   // +0x194
    uint8_t  mPad198[0x0c];                               // +0x198
    uint32_t mField1A4;                                   // +0x1a4
    uint32_t mField1A8;                                   // +0x1a8
    uint32_t mField1AC;                                   // +0x1ac

    void  UpdateMinimap(int32_t a, int32_t b, int32_t c);  // 0x00b8c330
    void  FUN_00b8c0f0();                                  // 0x00b8c0f0
    bool  HandleMessage(uint32_t id, void* msg);           // 0x00b8d2a0
    void  FUN_00b8d2f0();                                  // 0x00b8d2f0
    bool  FUN_00b8d750(uint32_t a, uint32_t b);            // 0x00b8d750
    bool  FUN_00b8d8a0(uint32_t a, bool refresh, uint32_t c); // 0x00b8d8a0
    uint32_t FUN_00b8d8f0();                               // 0x00b8d8f0
    void  FUN_00b8d910();                                  // 0x00b8d910
    void  FUN_00b8d920(bool flag);                         // 0x00b8d920
    void  FUN_00b8d950(bool flag);                         // 0x00b8d950
    void  FUN_00b8d980(bool flag);                         // 0x00b8d980
    int32_t FUN_00b8d9b0();                                // 0x00b8d9b0
    bool  FUN_00b8d9f0();                                  // 0x00b8d9f0
    int32_t FUN_00b8da70();                                // 0x00b8da70
    cKey3* FUN_00b8dd60(cKey3* out);                       // 0x00b8dd60
    void  FUN_00b8dde0(cKey3* key, int32_t unused);        // 0x00b8dde0
    void  FUN_00b8de60();                                  // 0x00b8de60
    int32_t FUN_00b8dec0(int32_t index);                   // 0x00b8dec0
    int32_t FUN_00b8def0(int32_t index);                   // 0x00b8def0
    void  FUN_00b8df20();                                  // 0x00b8df20
    void  FUN_00b8df80(int32_t index);                     // 0x00b8df80
    void  FUN_00b8dfe0(int32_t index);                     // 0x00b8dfe0
    bool  FUN_00b8e040(uint32_t id);                       // 0x00b8e040
    cKey3* FUN_00b8e090();                                 // 0x00b8e090
};

// --------------------------------------------------------------------------- 0x00b8d2a0
// Message handler: the minimap-init message arms the minimap with the payload's id, the two dirty
// messages only mark the model (and the key state) for a rebuild.
// @ 0x00b8d2a0
bool cPlanetModel::HandleMessage(uint32_t id, void* msg)
{
    if (id == 0x1b537e5) {
        int32_t value = 0;
        if (msg != 0) {
            value = ((int32_t*)msg)[2];
        }
        UpdateMinimap(0, 1, value);
        return true;
    }
    if (id == 0x44448ed) {
        mFieldEA = 1;
        mField78 = 1;
    } else if (id == 0x45fe992) {
        mField78 = 1;
    }
    return false;
}

// --------------------------------------------------------------------------- 0x00b8d2f0
// Drop the handler host and the index state: let the host release its cursor, then reset the
// current index to -1.
// @ 0x00b8d2f0
void cPlanetModel::FUN_00b8d2f0()
{
    if (mField20 != 0) {
        mField20->v43();
        FUN_00b8c0f0();
    }
    mFieldEC = -1;
}

// --------------------------------------------------------------------------- 0x00b8d8a0
// Insert a bio-protector record and, when asked, push the new entry into the cursor host.
// @ 0x00b8d8a0
bool cPlanetModel::FUN_00b8d8a0(uint32_t a, bool refresh, uint32_t c)
{
    bool inserted = FUN_00b8d750(a, c);
    if (refresh) {
        mField24->v35(FUN_0067dd50());
    }
    return inserted;
}

// --------------------------------------------------------------------------- 0x00b8d8f0
// Refresh the star object's banner list.
// @ 0x00b8d8f0
uint32_t cPlanetModel::FUN_00b8d8f0()
{
    return ((cStarObject*)SP::StarManager(mField184))->FUN_00ba6440();
}

// --------------------------------------------------------------------------- 0x00b8d910
// Mark the model as needing a full rebuild.
// @ 0x00b8d910
void cPlanetModel::FUN_00b8d910()
{
    mField2C |= 0x400;
}

// --------------------------------------------------------------------------- 0x00b8d920
// Toggle the 0x40 visibility flag.
// @ 0x00b8d920
void cPlanetModel::FUN_00b8d920(bool flag)
{
    mField2C = (mField2C & 0xffffffbfu) | (flag ? 0x40u : 0u);
}

// --------------------------------------------------------------------------- 0x00b8d950
// Toggle the 0x100 visibility flag.
// @ 0x00b8d950
void cPlanetModel::FUN_00b8d950(bool flag)
{
    mField2C = (mField2C & 0xfffffeffu) | (flag ? 0x100u : 0u);
}

// --------------------------------------------------------------------------- 0x00b8d980
// Toggle the 0x200 visibility flag.
// @ 0x00b8d980
void cPlanetModel::FUN_00b8d980(bool flag)
{
    mField2C = (mField2C & 0xfffffdffu) | (flag ? 0x200u : 0u);
}

// --------------------------------------------------------------------------- 0x00b8d9b0
// Resolve the mission that owns the model's star: the star object's own mission first, then the
// mission manager's.
// @ 0x00b8d9b0
int32_t cPlanetModel::FUN_00b8d9b0()
{
    int32_t result = ((cStarObject*)SP::StarManager((uint32_t)(void*)this))->FUN_00bb99e0();
    if (result == 0) {
        cMission* mission =
            ((cMissionManager*)SP::GetMissionManager((uint32_t)(void*)this))->FUN_00fee220();
        if (mission != 0) {
            return mission->FUN_00c4b220();
        }
    }
    return result;
}

// --------------------------------------------------------------------------- 0x00b8d9f0
// True when the model is in an editable state: a live mode word, the 0x100 flag clear, a mission
// behind the model and the 0x800 flag clear.
// @ 0x00b8d9f0
bool cPlanetModel::FUN_00b8d9f0()
{
    if (mField28 == 0) {
        return false;
    }
    if (mField28 == 1) {
        return false;
    }
    uint32_t state = (mField2C >> 8) & 1;
    if (state != 0) {
        return false;
    }
    if (FUN_00b8d9b0() != 0) {
        return false;
    }
    if (mField2C & 0x800) {
        return false;
    }
    return true;
}

// --------------------------------------------------------------------------- 0x00b8da70
// The model's star handle biased to the planet range.
// @ 0x00b8da70
int32_t cPlanetModel::FUN_00b8da70()
{
    return (int32_t)mField184 - 0x1000000;
}

// --------------------------------------------------------------------------- 0x00b8dd60
// Resolve the model's property key: detach and drop the cached key when the key service no longer
// recognises it, then export the surviving key into the caller's three words.
// @ 0x00b8dd60
cKey3* cPlanetModel::FUN_00b8dd60(cKey3* out)
{
    out->m0 = 0;
    out->m4 = 0;
    out->m8 = 0;
    if (mField1A4 != 0) {
        int32_t found = ((cKeyService*)FUN_00f48a80())->v1(&mField1A4);
        if (found == 0) {
            mField1A4 = 0;
            mField1A8 = 0;
            mField1AC = 0;
            ((cStarObject*)SP::StarManager((uint32_t)(void*)this))->FUN_00ba6660();
            found = ((cKeyService*)FUN_00f48a80())->v1(&mField1A4);
            if (found == 0) {
                return out;
            }
        }
        SP::GetPropertyAsKey((uint32_t)found, 0x3d03f84, out);
    }
    return out;
}

// --------------------------------------------------------------------------- 0x00b8dde0
// Re-key the model: copy the three key words when they differ from the cached key.
// @ 0x00b8dde0
void cPlanetModel::FUN_00b8dde0(cKey3* key, int32_t unused)
{
    if (key->m0 != mField1A4 || key->m4 != mField1A8 || key->m8 != mField1AC) {
        mField1A4 = key->m0;
        mField1A8 = key->m4;
        mField1AC = key->m8;
    }
}

// --------------------------------------------------------------------------- 0x00b8de30
// Sort the bio-protector banner list of the model's star.
// @ 0x00b8de30
uint32_t cBioElemSort::SortBanners()
{
    uint32_t banner = ((cStarObject*)SP::StarManager(mField184))->FUN_00ba6440();
    return ((cStarObject*)SP::StarManager(banner))->FUN_00ba6d80();
}

// --------------------------------------------------------------------------- 0x00b8de60
// Destroy the first pointer container element by element.
// @ 0x00b8de60
void cPlanetModel::FUN_00b8de60()
{
    while (mField15C != mField160) {
        cOwnedElem* element = *(cOwnedElem**)(mField160 - 4);
        mField160 -= 4;
        if (element != 0) {
            element->FUN_00ff2e30();
            FUN_00f47380(element);
        }
    }
}

// --------------------------------------------------------------------------- 0x00b8dec0
// Indexed access into the first pointer container.
// @ 0x00b8dec0
int32_t cPlanetModel::FUN_00b8dec0(int32_t index)
{
    if (index < (int32_t)(mField160 - mField15C) >> 2) {
        return *(int32_t*)(mField15C + index * 4);
    }
    return 0;
}

// --------------------------------------------------------------------------- 0x00b8def0
// Indexed access into the second pointer container.
// @ 0x00b8def0
int32_t cPlanetModel::FUN_00b8def0(int32_t index)
{
    if (index < (int32_t)(mField174 - mField170) >> 2) {
        return *(int32_t*)(mField170 + index * 4);
    }
    return 0;
}

// --------------------------------------------------------------------------- 0x00b8df20
// Destroy the second pointer container element by element.
// @ 0x00b8df20
void cPlanetModel::FUN_00b8df20()
{
    while (mField170 != mField174) {
        void* element = *(void**)(mField174 - 4);
        mField174 -= 4;
        if (element != 0) {
            ((cOwnedElem2*)element)->FUN_00c2e4e0();
            FUN_00f47380(element);
        }
    }
}

// --------------------------------------------------------------------------- 0x00b8df80
// Erase one element of the first pointer container (swap with the last element).
// @ 0x00b8df80
void cPlanetModel::FUN_00b8df80(int32_t index)
{
    int32_t count = (int32_t)((char*)mField160 - (char*)mField15C) >> 2;
    if (index >= count) {
        return;
    }
    int32_t* element = (int32_t*)FUN_00b8dec0(index);
    if (element != 0) {
        ((cOwnedElem*)element)->FUN_00ff2e30();
        FUN_00f47380(element);
    }
    int32_t* end = (int32_t*)mField160;
    int32_t* begin = (int32_t*)mField15C;
    int32_t value = *--end;
    begin[index] = value;
    mField160 = (char*)end;
}

// --------------------------------------------------------------------------- 0x00b8dfe0
// Erase one element of the second pointer container (swap with the last element).
// @ 0x00b8dfe0
void cPlanetModel::FUN_00b8dfe0(int32_t index)
{
    int32_t count = (int32_t)((char*)mField174 - (char*)mField170) >> 2;
    if (index >= count) {
        return;
    }
    int32_t* element = (int32_t*)FUN_00b8def0(index);
    if (element != 0) {
        ((cOwnedElem2*)element)->FUN_00c2e4e0();
        FUN_00f47380(element);
    }
    int32_t* end = (int32_t*)mField174;
    int32_t* begin = (int32_t*)mField170;
    int32_t value = *--end;
    begin[index] = value;
    mField174 = (char*)end;
}

// --------------------------------------------------------------------------- 0x00b8e040
// True when the 0x2c-byte container holds a record with the given id.
// @ 0x00b8e040
bool cPlanetModel::FUN_00b8e040(uint32_t id)
{
    int32_t count = (int32_t)((mField138 - mField134) / 0x2c);
    for (int32_t i = 0; i < count; ++i) {
        if (((cBioElem*)mField134)[i].m00 == (int32_t)id) {
            return true;
        }
    }
    return false;
}

// --------------------------------------------------------------------------- 0x00b8e090
// The model's banner key: the star's banner list key when the model has more than one entry, the
// shared empty three-word key otherwise.
// @ 0x00b8e090
cKey3* cPlanetModel::FUN_00b8e090()
{
    static cKey3 sEmptyKey;
    if (mField194 > 1) {
        uint32_t banner = ((cStarObject*)SP::StarManager(mField184))->FUN_00ba6440();
        uint32_t list = ((cStarObject*)SP::StarManager(banner))->FUN_00ba6d80();
        return (cKey3*)((cStarObject*)list)->FUN_00bb9b80();
    }
    return &sEmptyKey;
}

// --------------------------------------------------------------------------- 0x00b8e0f0
// Copy a run of 0x2c-byte bio-protector records, reporting the final destination.
// @ 0x00b8e0f0
void* __cdecl FUN_00b8e0f0(void** out, const cBioElem* first, const cBioElem* last,
                           cBioElem* dest)
{
    *out = dest;
    while (first != last) {
        if (dest != 0) {
            *dest = *first;
        }
        ++first;
        ++dest;
    }
    *out = dest;
    return out;
}
