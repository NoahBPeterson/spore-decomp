// addresses retail relocates here, named so the build relocates them too
extern "C" char g_145f924[];

#include "types.h"

typedef unsigned int size_t;

void* operator new(
    size_t size,
    const char* name,
    int flags,
    unsigned int debugFlags,
    const char* file,
    int line
);

namespace SP {

struct CivNotification {
    void Clear();                      // 0x007CFC60
    void Update(int value, int flags); // 0x007D01D0
};

struct SimSingleton {
    unsigned char pad[0xC8];
    SimSingleton();                    // 0x00AE5C30

    bool Query(
        int mode,
        uint32_t* first,
        uint32_t* second
    );                                 // 0x00AE3ED0
};

extern SimSingleton* g_167a60c;        // 0x0167A60C

struct cCivModeStrategy {
    unsigned char mPad00[0x114];
    CivNotification* mpNotification;   // +0x114

    void FUN_00cf9310();
};

// @ 0x00cf9310
void cCivModeStrategy::FUN_00cf9310()
{
    mpNotification->Clear();

    SimSingleton* singleton = g_167a60c;

    uint32_t values[4] = {
        0, 0, 0, 0
    };

    if (singleton == 0) {
        singleton = new (
            (const char*)g_145f924,
            0, 0, 0, 0
        ) SimSingleton();

        g_167a60c = singleton;
    }

    if (singleton->Query(
        0,
        &values[0],
        &values[1]
    )) {
        mpNotification->Update(values[0], 0);
        mpNotification->Update(values[1], 0);
    }
}

} // namespace SP
