// Slice s010554c0: 0x01055890, a function whose whole body is 28 function-local static registrations
// (Simulator::cSimRegistration<N>, the same macro shape as cSimulatorSystem::Initialize in s00b60d80).
// Each `static cSimRegistration<N> s;` is guarded by a bit in the shared init mask at 0x016e1b10 and registers its
// destructor with atexit; then `if (!s.IsRegistered()) s.Register();` runs every time (the last one is a tail call).
// Flags: /O2 /MD /Gy /TP.
#include "types.h"

namespace Simulator {

// Function-local static registrations (base 0x14 bytes, linked into a global list by the base ctor).
struct cSimRegistrationBase {
    cSimRegistrationBase(int);                // 0x00692f60
    virtual ~cSimRegistrationBase();
    bool IsRegistered();                      // 0x00ab30c0
    void Register();                          // 0x00692850
    uint32_t mData[4];
};
template <int N>
struct cSimRegistration : cSimRegistrationBase {
    cSimRegistration() : cSimRegistrationBase(0) {}
    virtual ~cSimRegistration();
};

#define STATIC_REGISTRATION(N) \
    static cSimRegistration<N> sRegistration##N; \
    if (!sRegistration##N.IsRegistered()) sRegistration##N.Register();

// @ 0x01055890
void RegisterStaticRegistrations()
{
    STATIC_REGISTRATION(0)
    STATIC_REGISTRATION(1)
    STATIC_REGISTRATION(2)
    STATIC_REGISTRATION(3)
    STATIC_REGISTRATION(4)
    STATIC_REGISTRATION(5)
    STATIC_REGISTRATION(6)
    STATIC_REGISTRATION(7)
    STATIC_REGISTRATION(8)
    STATIC_REGISTRATION(9)
    STATIC_REGISTRATION(10)
    STATIC_REGISTRATION(11)
    STATIC_REGISTRATION(12)
    STATIC_REGISTRATION(13)
    STATIC_REGISTRATION(14)
    STATIC_REGISTRATION(15)
    STATIC_REGISTRATION(16)
    STATIC_REGISTRATION(17)
    STATIC_REGISTRATION(18)
    STATIC_REGISTRATION(19)
    STATIC_REGISTRATION(20)
    STATIC_REGISTRATION(21)
    STATIC_REGISTRATION(22)
    STATIC_REGISTRATION(23)
    STATIC_REGISTRATION(24)
    STATIC_REGISTRATION(25)
    STATIC_REGISTRATION(26)
    STATIC_REGISTRATION(27)
}

}  // namespace Simulator
