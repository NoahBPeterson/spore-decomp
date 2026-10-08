// Declarations for SP::nSpaceCheats::cCommandMission::Execute (slice s01023fc0).
// Callees are external (relocated) in the original; names from the PDB where known.
#pragma once
#include "types.h"

typedef unsigned int size_t;

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00F473A0
void  operator delete[](void* p);                                                                                  // 0x00F47380

extern "C" size_t __cdecl strlen(const char* p);
extern "C" void* __cdecl memcpy(void* d, const void* s, size_t n);
#pragma intrinsic(strlen, memcpy)

#define EASTL_SIM_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace eastl {

extern wchar_t gEmptyString16[2];   // 0x01667BAC

struct allocator { allocator() {} };

// basic_string<char, allocator> (out-of-line ctor/dtor)
class string {
public:
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator mAllocator;
    string(const char* p, const allocator& a = allocator());    // 0x0057ED80
    ~string();                                                  // 0x00530670
    const char* c_str() const { return mpBegin; }
};

class string16 {
public:
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    allocator mAllocator;
    string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf();                                      // 0x00933960
    const wchar_t* c_str() const { return mpBegin; }
};

// The "Simulator" string: allocator inlined (operator new[] named "Simulator").
struct sim_allocator {
    sim_allocator() {}
    void* allocate(size_t n) { return operator new[](n, "Simulator", 0, 0, EASTL_SIM_FILE, 0xd1); }
    void  deallocate(void* p) { operator delete[](p); }
};

class sim_string {
public:
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    sim_allocator mAllocator;

    __forceinline sim_string(const char* p) { RangeInit(p, p + strlen(p)); }
    __forceinline void RangeInit(const char* pBegin, const char* pEnd)
    {
        const size_t n = (size_t)(pEnd - pBegin);
        AllocateSelf(n);
        memcpy(mpBegin, pBegin, n);
        mpEnd = mpBegin + (pEnd - pBegin);
        *mpEnd = 0;
    }
    ~sim_string() { DeallocateSelf(); }
    __forceinline void AllocateSelf(size_t nLen)
    {
        if (nLen + 1 > 1) {
            mpBegin = (char*)mAllocator.allocate(nLen + 1);
            mpCapacity = mpBegin + nLen + 1;
        } else {
            mpBegin = (char*)gEmptyString16;
            mpCapacity = (char*)gEmptyString16 + 1;
        }
    }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            mAllocator.deallocate(mpBegin);
    }
};
bool operator==(const sim_string& a, const char* b);            // 0x00555020

} // namespace eastl

namespace EA { namespace ArgScript {

class FormatParser {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
    virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
    virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C();
    virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4C();
    virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5C();
    virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6C();
    virtual void vf70(); virtual void vf74(); virtual void vf78(); virtual void vf7C();
    virtual void vf80(); virtual void vf84(); virtual void vf88(); virtual void vf8C();
    virtual void vf90();
    virtual bool ParseBool(const char* s) const;                // 0x94
    virtual float ParseFloat(const char* s) const;              // 0x98
    virtual int ParseInt(const char* s) const;                  // 0x9C
};

class cArguments {
public:
    int NumArguments();                                         // 0x00837F30
    const char* operator[](int i);                              // 0x00837F20
};

void Output(FormatParser* parser, const char* fmt, ...);        // 0x00841000

}} // namespace EA::ArgScript

namespace SP {

class cSPMission {
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08(); virtual void vf0C();
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1C();
    virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2C();
    virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3C();
    virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4C();
    virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5C();
    virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6C();
    virtual void vf70(); virtual void vf74(); virtual void vf78(); virtual void vf7C();
    virtual void vf80(); virtual void vf84(); virtual void vf88(); virtual void vf8C();
    virtual void vf90(); virtual void vf94(); virtual void vf98(); virtual void vf9C();
    virtual eastl::string16* GetName(eastl::string16* out);     // 0xA0
    virtual void vfA4(); virtual void vfA8(); virtual void vfAC();
    virtual void vfB0(); virtual void vfB4(); virtual void vfB8(); virtual void vfBC();
    virtual void vfC0(); virtual void vfC4(); virtual void vfC8(); virtual void vfCC();
    virtual void vfD0(); virtual void vfD4(); virtual void vfD8(); virtual void vfDC();
    virtual void vfE0(); virtual void vfE4(); virtual void vfE8(); virtual void vfEC();
    virtual void vfF0(); virtual void vfF4(); virtual void vfF8(); virtual void vfFC();
    virtual void vf100(); virtual void vf104(); virtual void vf108(); virtual void vf10C();
    virtual void vf110(); virtual void vf114(); virtual void vf118(); virtual void vf11C();
    virtual void vf120(); virtual void vf124(); virtual void vf128(); virtual void vf12C();
    virtual void vf130(); virtual void vf134(); virtual void vf138(); virtual void vf13C();
    virtual void vf140(); virtual void vf144(); virtual void vf148(); virtual void vf14C();
    virtual void vf150(); virtual void vf154(); virtual void vf158();
    virtual void Fulfill();                                     // 0x15C
    uint32_t pad[0x17c / 4 - 1];
    cSPMission* mpParentMission;                                // +0x17C
    void Accept();                                              // 0x00C485B0
    void Abort();                                               // 0x00C485D0
    void Complete();                                            // 0x00C485E0
    void Fail();                                                // 0x00C485F0
};

class cPlanet {
public:
    uint32_t pad[0x13c / 4];
    void* mpPlanetRecord;                                       // +0x13C
    void* GetOrbitTarget();                                     // 0x00C71E30
};

// vector<AutoRefCount<cSPMission>> copy (opaque): copy ctor and dtor are out of line.
class MissionList {
public:
    cSPMission** mpBegin;
    cSPMission** mpEnd;
    cSPMission** mpCapacity;
    uint32_t mExtra[2];
    MissionList(const MissionList& x);                          // 0x00BA95A0
    ~MissionList();                                             // 0x00AE6970
    size_t size() const { return (size_t)(mpEnd - mpBegin); }
};

class cSPMissionManager {
public:
    uint32_t pad[0x14 / 4];
    bool mbDebugDraw;                                           // +0x14
    uint32_t pad2;
    uint32_t mNextMissionID;                                    // +0x1C
    cSPMission* CreateMissionFromID(uint32_t id, void* planetRecord, void* target, int flag); // 0x00FEC590
    MissionList* GetMissionList();                              // 0x00FEDD50
    int GetNumNonEventMissions(bool b);                         // 0x00FEDD80
    int GetNumEventMissions();                                  // 0x00FEDDF0
    bool ToggleDebugDraw();                                     // 0x00FEBA50
    void SetNextMissionID(uint32_t id);                         // 0x007CD950
};
cSPMissionManager* GetMissionManager();                         // 0x00FEB9F0
uint32_t SPIDFromName(const char* name);                        // 0x00571CF0 (cdecl)

class cSPSimulatorSpaceGame;
cSPSimulatorSpaceGame* SpaceGameGet();                          // 0x01002BD0
class cGameNounManager;
cGameNounManager* NounManager();                                // 0x00B3D300

class cUIManager {
public:
    void ShowMissionUI(void* arg);                              // 0x00E190C0
};
cUIManager* GetUIManager();                                     // 0x00B3D3F0

struct cSPLivingUniverse {
    static cPlanet* GetActivePlanet();                          // 0x01021260
};

namespace nSpaceCheats {

class cCommandMission {
public:
    virtual void ParseLine(EA::ArgScript::cArguments* args);
    EA::ArgScript::FormatParser* mpFormatParser;                // +0x04
    void Execute(EA::ArgScript::cArguments* args);              // 0x01023FC0
    cSPMission* VerifyMission(uint32_t id);                     // 0x01022FD0
};

} // namespace nSpaceCheats
} // namespace SP
