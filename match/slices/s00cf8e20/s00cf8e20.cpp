// Slice s00cf8e20 -- player-civilization city count over the SimSingleton scale.
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

    uint8_t mPad00[0xac];                                    // +0x00 .. +0xab
    int     mCityCountScale;                                 // +0xac
    uint8_t mPadB0[0xc8 - 0xb0];                             // +0xb0 .. +0xc7
};

SimSingleton* gSimSingleton;                                 // 0x0167a60c

// 0x00bef6c0 hands back the address of the civilization's city list (+0x9c).
struct CityVector {
    void* mpBegin;                                           // +0x00
    void* mpEnd;                                             // +0x04
};

struct ICivilization {
    uint8_t     mPad00[0x9c];                                // +0x00 .. +0x9b
    CityVector* GetCities();                                 // 0x00bef6c0
};

struct cNounManager {
    ICivilization* GetPlayerCivilization();                  // 0x00b25fb0
};

cNounManager* NounManager();                                 // 0x00b3d300

// The player civilization's city count over the simulator's current scale; zero
// while there is no civilization or the scale is unset (avoids dividing by it).
// @ 0x00cf8e20
double PlayerCityCountRatio()
{
    ICivilization* civ = NounManager()->GetPlayerCivilization();
    if (civ)
    {
        CityVector* cities = civ->GetCities();
        float count = (float)(unsigned int)
            (((int)((char*)cities->mpEnd - (char*)cities->mpBegin)) >> 2);
        if (!gSimSingleton)
            gSimSingleton = new SimSingleton();
        float scale = (float)gSimSingleton->mCityCountScale;
        if (scale != 0.0f)
            return (double)count / (double)scale;
    }
    return 0.0;
}

} // namespace SP
