// Slice s00cf9190 -- seeds a stage's id set with the fixed resource list and then
// with the two counts the sim singleton reports for mode 1.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

// 0x00f473a0: tagged allocation (size, tag, flags, debugFlags, file, line).
void* __cdecl operator_new6(unsigned int size, const char* tag, int flags,
                            int debugFlags, const char* file, int line);

// 0x00ae5c30, 0xc8 bytes: the single SimSingleton the simulator keeps at 0x0167a60c.
struct SimSingleton {
    SimSingleton();

    static void* operator new(unsigned int size,
                              const char* tag = "Simulator/SimSingleton",
                              int flags = 0, int debugFlags = 0,
                              const char* file = 0, int line = 0)
    {
        return operator_new6(size, tag, flags, debugFlags, file, line);
    }

    // 0x00ae3ed0: fills the two out values for the given mode and says whether
    // both were available (only mode 1 is ever asked for below).
    bool GetCounts(int mode, uint32_t* outA, uint32_t* outB);

    uint8_t mPad00[0xc8];                                    // +0x00 .. +0xc7
};

SimSingleton* gSimSingleton;                                 // 0x0167a60c

// 0x007d01d0: insert an id into the set (value is the entry's initial count).
struct cIDSet {
    void Add(uint32_t id, int count);
};

// Stage object holding the fixed preload set (+0x110) and the per-run set (+0x114).
struct cStageIDs {
    uint8_t mPad00[0x110];                                   // +0x00 .. +0x10f
    cIDSet* mpFixedIDs;                                      // +0x110
    cIDSet* mpRuntimeIDs;                                    // +0x114
    void SeedIDs();
};

// @ 0x00cf9190
void cStageIDs::SeedIDs()
{
    // The stage's fixed resource list.
    mpFixedIDs->Add(0xa19b0182, 0);
    mpFixedIDs->Add(0xce12fd0a, 0);
    mpFixedIDs->Add(0xce12fd09, 0);
    mpFixedIDs->Add(0xce12fd08, 0);
    mpFixedIDs->Add(0x243b0adb, 0);
    mpFixedIDs->Add(0xb25afc86, 0);
    mpFixedIDs->Add(0x00bba461, 0);
    mpFixedIDs->Add(0x08b23aea, 0);
    mpFixedIDs->Add(0x51538f55, 0);
    mpFixedIDs->Add(0x495700b5, 0);
    mpFixedIDs->Add(0x5da27201, 0);
    mpFixedIDs->Add(0xd9f9374b, 0);
    mpFixedIDs->Add(0xddf6a600, 0);
    mpFixedIDs->Add(0x8f732b53, 0);

    uint32_t counts[4] = { 0, 0, 0, 0 };
    if (!gSimSingleton)
        gSimSingleton = new SimSingleton();
    if (gSimSingleton->GetCounts(1, &counts[0], &counts[1]))
    {
        mpRuntimeIDs->Add(counts[0], 0);
        mpRuntimeIDs->Add(counts[1], 0);
    }
}

} // namespace SP
