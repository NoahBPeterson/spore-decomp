// Slice s00a9dc00: cMetaParticlesEffect::UpdateParticle (EA::Swarm meta-particle update).
//
// Flag-set path (description flags bit 26): snap the particle onto the emitter path with the
// description's transformed bounding box, then apply the spin correction when the description's
// spin angle is non-zero. Otherwise pick the cheap or full integrator based on the description's
// timestep flags and per-step distance.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef unsigned int uint32;

struct cMetaParticle;
struct cMetaParticlesEffect;

// EA::Swarm::SnapParticleToPath (6 arguments, bool result).
extern "C" bool FUN_00a79f60(void* a1, float dt, void* a3, const float* a4, const float* a5, void* a6); // 0x00a79f60
// EA::Swarm spin correction (5 arguments, void).
extern "C" void FUN_00a9b120(const void* a1, const float* a2, float* a3, float dt, void* a5);          // 0x00a9b120

extern uint32 g_1679034;   // 0x01679034  timestep flag mask A
extern uint32 g_1679038;   // 0x01679038  timestep flag mask B

// Only the offsets touched by the update are named; the object is much larger.
struct cMetaParticle {
    char pad[0x28];
};

// The description owns the emitter/path data at +0x2a8.. and the spin angles at +0x278.
struct cMetaParticlesDescription {
    char pad[0x2b0];
};

struct cMetaParticlesEffect {
    bool UpdateParticle(cMetaParticle* p, float dt);        // 0x00a9dc00
    bool UpdateParticleCheap(cMetaParticle* p, float dt);   // 0x00a9b780
    bool UpdateParticleFull(cMetaParticle* p, float dt);    // 0x00a9d640
};

// @ 0x00a9dc00
bool cMetaParticlesEffect::UpdateParticle(cMetaParticle* p, float dt)
{
    char* self = (char*)this;
    char* desc = *(char**)(self + 0xc);
    if ((*(uint32*)(desc + 8) >> 26) & 1) {
        // save the particle's current position (used by the spin correction)
        float pos[3];
        pos[0] = *(float*)((char*)p + 0x1c);
        pos[1] = *(float*)((char*)p + 0x20);
        pos[2] = *(float*)((char*)p + 0x24);

        // path target: the effect's current path when active, else the description's default
        char* target = desc + 0x2a8;
        if (*(void**)(self + 0x218) != *(void**)(self + 0x21c))
            target = self + 0x218;

        void* path = p ? (char*)p + 8 : 0;

        char* d = *(char**)(self + 0xc);
        float w = *(float*)(d + 0x44);
        float size[3];
        size[0] = w * ((*(float*)(d + 0x2c) + *(float*)(d + 0x38)) * 0.5f);
        size[1] = w * ((*(float*)(d + 0x3c) + *(float*)(d + 0x30)) * 0.5f);
        size[2] = w * ((*(float*)(d + 0x40) + *(float*)(d + 0x34)) * 0.5f);
        float box[3];
        box[0] = (*(float*)(d + 0x58) + *(float*)(d + 0x4c)) * 0.5f;
        box[1] = (*(float*)(d + 0x5c) + *(float*)(d + 0x50)) * 0.5f;
        box[2] = (*(float*)(d + 0x60) + *(float*)(d + 0x54)) * 0.5f;

        if (!FUN_00a79f60(path, dt, target, box, size, self + 0x30))
            return false;

        char* d2 = *(char**)(self + 0xc);
        if (*(float*)(d2 + 0x278) != 0.0f)
            FUN_00a9b120(d2, pos, (float*)((char*)p + 0x1c), dt, p);
        return true;
    }

    // Cheap integrator while the description has no active timestep flags and the step is short.
    if ((*(uint32*)(desc + 0xc) & g_1679038) == 0 &&
        (*(uint32*)(desc + 8) & g_1679034) == 0 &&
        !(*(float*)(desc + 0x168) * dt > 0.05f))
        return UpdateParticleCheap(p, dt);
    return UpdateParticleFull(p, dt);
}
