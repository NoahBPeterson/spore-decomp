// Declarations for slice s01022fd0 (SP::nSpaceCheats cheat-console commands and the
// eastl pointer-container helpers around cSPUILayoutManager). Names from the PDB where
// known; callees are external (relocated) in the original.
#pragma once
#include "types.h"

typedef unsigned int size_t;

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00F473A0
void  operator delete[](void* p);                                                                                  // 0x00F47380
void  operator delete(void* p);                                                                                    // 0x00F47380

extern "C" size_t __cdecl strlen(const char* p);
extern "C" void*  __cdecl memcpy(void* d, const void* s, size_t n);
#pragma intrinsic(strlen, memcpy)

#define EASTL_SIM_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
class allocator { public: allocator() {} };
} // namespace eastl

namespace EA { namespace ArgScript {
class cArguments {
public:
    int NumArguments();                                         // 0x00837F30
    const char* operator[](int i);                              // 0x00837F20
    bool HasFlag(const char* name);                             // 0x008380B0
};
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
    virtual bool  ParseBool(const char* s) const;               // 0x94
    virtual float ParseFloat(const char* s) const;              // 0x98
    virtual int   ParseInt(const char* s) const;                // 0x9C
};
void Output(FormatParser* parser, const char* fmt, ...);        // 0x00841000
}} // namespace EA::ArgScript

namespace SP {

class cGameNounManager;
cGameNounManager* NounManager();                                // 0x00B3D300

// A node in the cGameNounManager intrusive list: 0x0c-byte header then the noun pointer.
struct cGameNounNode {
    void*    pad00[3];                                          // 0x000..0x00c
    cGameNounNode* mpNext;                                      // 0x00c
};

class cGameNounManager {
public:
    cGameNounNode* GetAllNouns();                               // 0x00B1F9B0
};

using EA::ArgScript::cArguments;
using EA::ArgScript::FormatParser;

namespace nSpaceCheats {

// cCommandMission: the "mission" cheat command object (see slice s01023fc0).
class cCommandMission {
public:
    virtual void ParseLine(EA::ArgScript::cArguments* args);
    virtual void vf04(); virtual void vf08();
    virtual void Execute(EA::ArgScript::cArguments* args);      // 0x01023FC0 (vtable +0x0c)
    EA::ArgScript::FormatParser* mpFormatParser;                // +0x04
    void* VerifyMission(uint32_t id);                           // 0x01022FD0
};

void FUN_00b2af00(void* a, void* b);                            // 0x00B2AF00

// The tool-cheat command object (its Execute is the target 0x010234A0).
class cCommandToolCheat {
public:
    virtual void ParseLine();
    virtual void vf04(); virtual void vf08();
    virtual void Execute(EA::ArgScript::cArguments* args);      // 0x010234A0
    FormatParser* mpFormatParser;                               // +0x04
};

void UseToolSet(void* inventory, uint32_t toolID);              // 0x00FF4B90
void FUN_00ff4840(void* inventory, int a);                      // 0x00FF4840
int  FUN_00ff3ba0(void* inventory);                             // 0x00FF3BA0

// --- the "ari" cheat command (Execute @ 0x01023BE0) ---------------------------------
class cArguments;                                               // EA::ArgScript::cArguments
class cCommandAri {
public:
    virtual void ParseLine();
    virtual void vf04(); virtual void vf08();
    virtual void Execute(EA::ArgScript::cArguments* args);      // 0x01023BE0
    FormatParser* mpFormatParser;                               // +0x04
};

// Callees used by cCommandAri::Execute (names/addresses from the retail disassembly).
void* FUN_01021230();                                           // 0x01021230
void* FUN_00b3d470(void* p);                                    // 0x00B3D470
void  FUN_01034b90(void* p);                                    // 0x01034B90
void* MessageServer();                                          // 0x0067DCC0
void  FUN_006bb6c0(void* out, const void* begin, int count);    // 0x006BB6C0
void* FUN_01021300();                                           // 0x01021300 (GetPlayerEmpire)
void  FUN_00c31a60(void* this_, int id);                        // 0x00C31A60
void  FUN_00feba50();                                           // 0x00FEBA50
void* StarManager();                                            // 0x00B3D2A0
void* RelationshipManager();                                    // 0x00B3D2C0
void* cGameNounManager_GetAvatar(void* this_, int id);          // 0x00B1FDB0
void* SpaceGameGet();                                           // 0x01002BD0

struct cArgumentsFlags {
    bool HasFlag(const char* name);                             // 0x008380B0
};

} // namespace nSpaceCheats
} // namespace SP
