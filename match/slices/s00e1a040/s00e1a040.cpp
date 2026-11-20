// Sort predicate: orders mission game objects by the distance of their source
// planet to a reference body. Objects whose mission has no source planet sort
// after every object that has one.
// Reconstructed from the retail disassembly; the concrete callee classes are
// not yet confirmed, so the minimal layouts they touch are declared here.
#include "types.h"

struct Vec3 {
    float x, y, z;
};

struct cSPMission;
struct cPlanet;
struct cPlanetRecord;
struct cCelestialBody;

// Interface-resolving object: vtable slot at +0x0c returns the object that
// implements the requested interface id.
struct cIObject {
    virtual void vf00();
    virtual void vf04();
    virtual void vf08();
    virtual cSPMission* AsInterface(uint32_t iid);   // vtable +0x0c
};

struct cSPMission {
    cPlanet* GetSourcePlanet();                      // 0x00c45ce0
};

struct cPlanet {
    char pad00[0x13c];
    cPlanetRecord* mpRecord;                         // +0x13c
};

struct cCelestialBody {
    Vec3* GetPosition();                             // 0x005c65e0
};

struct cPlanetRecord {
    cCelestialBody* GetCelestialBody();              // 0x00b8de30
};

struct cGameState {
    char pad00[0x48];
    cCelestialBody* mpReferenceBody;                 // +0x48
};

cGameState* GetGameState();                          // 0x01021230

// Vector from a body's position to the singleton's reference body.
inline Vec3 DeltaToReference(cCelestialBody* body, cGameState* game) {
    Vec3* ref = game->mpReferenceBody->GetPosition();
    Vec3* pos = body->GetPosition();
    Vec3 d;
    d.x = pos->x - ref->x;
    d.y = pos->y - ref->y;
    d.z = pos->z - ref->z;
    return d;
}

// The retail code accumulates the two squared lengths in different component
// orders (y,z,x for the first body, z,y,x for the second); the sums are equal,
// only the last-bit rounding differs, so the order is kept per body.
inline float LengthSqA(const Vec3& v) {
    float r = v.y * v.y;
    r = r + v.z * v.z;
    r = r + v.x * v.x;
    return r;
}

inline float LengthSqB(const Vec3& v) {
    float r = v.z * v.z;
    r = r + v.y * v.y;
    r = r + v.x * v.x;
    return r;
}

// 0x2aa5ada is the interface id handed to AsInterface.
enum { kMissionInterfaceId = 0x2aa5ada };

// @ 0x00e1a040
// Free __stdcall predicate: the retail function never reads `this` (ecx), and it
// pops both arguments itself (ret 8), so a stateless comparator is equivalent.
bool __stdcall CompareMissionsByDistanceToReference(cIObject* a, cIObject* b) {
    cSPMission* missionA = a ? a->AsInterface(kMissionInterfaceId) : 0;
    cSPMission* missionB = b ? b->AsInterface(kMissionInterfaceId) : 0;

    cPlanet* planetA = missionA->GetSourcePlanet();
    cPlanet* planetB = missionB->GetSourcePlanet();
    if (!planetA)
        return false;
    if (!planetB)
        return true;

    cCelestialBody* bodyA = planetA->mpRecord->GetCelestialBody();
    cCelestialBody* bodyB = planetB->mpRecord->GetCelestialBody();
    cGameState* game = GetGameState();

    return LengthSqA(DeltaToReference(bodyA, game)) < LengthSqB(DeltaToReference(bodyB, game));
}
