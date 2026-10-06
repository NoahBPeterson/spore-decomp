// @ 0x459370  SP::CapabilityManager::GetPropIDForAbility
// /Od module (push ebp frame, every switch value spilled to its own slot).
// Maps an ability ResourceID (+ level 1..5 / 1..3) to a property-ID hash.  Case bodies are
// laid out in source order at /Od, so the case order below follows the original's body order.
#include "types.h"

namespace EA { namespace Hash {
    uint32_t FNV1_String8(const char* pString, uint32_t nInitialValue, int charCase);  // 0x00932e80
} }

static inline uint32_t PropHash(const char* name)
{
    return EA::Hash::FNV1_String8(name, 0x811c9dc5, 1);
}

namespace SP {
struct CapabilityManager {
    static uint32_t GetPropIDForAbility(uint32_t abilityID, int level);
};

uint32_t CapabilityManager::GetPropIDForAbility(uint32_t abilityID, int level)
{
    switch (abilityID) {
    case 0x31c3e5b2: return 0xdb2d51a3; break;
    case 0x022e7847:
        switch (level) {
        case 1: return 0xc7e19209;
        case 2: return 0xc7e1920a;
        case 3: return 0xc7e1920b;
        case 4: return 0xc7e1920c;
        case 5: return 0xc7e1920d;
        default: return 0xc7e1920d;
        }
        break;
    case 0x022e785c:
        switch (level) {
        case 1: return 0x019e577c;
        case 2: return 0x019e577f;
        case 3: return 0x019e577e;
        case 4: return 0x019e5779;
        case 5: return 0x019e5778;
        default: return 0x019e5778;
        }
        break;
    case 0x04d18972: return 0x5cd23f68;
    case 0x04d18c4c: return 0x7ce5a7d4;
    case 0xb00f0fe2: return 0xfd3d2eda;
    case 0xb3e30313: return 0x1adbbadc;
        break;
    case 0x51c3e5b4:
        switch (level) {
        case 1: return 0x7523cc3f;
        case 2: return 0x7523cc3c;
        case 3: return 0x7523cc3d;
        case 4: return 0x7523cc3a;
        case 5: return 0x7523cc3b;
        default: return 0x7523cc3b;
        }
        break;
    case 0x330c117a:
        switch (level) {
        case 1: return 0x3fe1779a;
        case 2: return 0x3fe17799;
        case 3: return 0x3fe17798;
        case 4: return 0x3fe1779f;
        case 5: return 0x3fe1779e;
        default: return 0x3fe1779e;
        }
        break;
    case 0x04f4e1b4:
        switch (level) {
        case 1: return 0x3476bd1d;
        case 2: return 0x3476bd1e;
        case 3: return 0x3476bd1f;
        case 4: return 0x3476bd18;
        case 5: return 0x3476bd19;
        default: return 0x3476bd19;
        }
        break;
    case 0xf354a879:
        switch (level) {
        case 1: return 0x28a9da21;
        case 2: return 0x28a9da22;
        case 3: return 0x28a9da23;
        case 4: return 0x28a9da24;
        case 5: return 0x28a9da25;
        default: return 0x28a9da25;
        }
        break;
    case 0xf354a87a:
        switch (level) {
        case 1: return 0x21745c9e;
        case 2: return 0x21745c9d;
        case 3: return 0x21745c9c;
        case 4: return 0x21745c9b;
        case 5: return 0x21745c9a;
        default: return 0x21745c9a;
        }
        break;
    case 0xb354a87c:
        switch (level) {
        case 1: return 0x020c974b;
        case 2: return 0x020c9748;
        case 3: return 0x020c9749;
        case 4: return 0x020c974e;
        case 5: return 0x020c974f;
        default: return 0x020c974f;
        }
        break;
    case 0xb1c3e5b7:
        switch (level) {
        case 1: return 0x3a0c593c;
        case 2: return 0x3a0c593f;
        case 3: return 0x3a0c593e;
        case 4: return 0x3a0c5939;
        case 5: return 0x3a0c5938;
        default: return 0x3a0c5938;
        }
        break;
    case 0xb1c3e5b8:
        switch (level) {
        case 1: return 0xbb85808e;
        case 2: return 0xbb85808d;
        case 3: return 0xbb85808c;
        case 4: return 0xbb85808b;
        case 5: return 0xbb85808a;
        default: return 0xbb85808a;
        }
        break;
    case 0xb1c3e5b9:
        switch (level) {
        case 1: return 0x172b0cf0;
        case 2: return 0x172b0cf3;
        case 3: return 0x172b0cf2;
        case 4: return 0x172b0cf5;
        case 5: return 0x172b0cf4;
        default: return 0x172b0cf4;
        }
        break;
    case 0xb1c3e5c0:
        switch (level) {
        case 1: return 0xba81f234;
        case 2: return 0xba81f237;
        case 3: return 0xba81f236;
        case 4: return 0xba81f231;
        case 5: return 0xba81f230;
        default: return 0xba81f230;
        }
        break;
    case 0xb1c3e5c1:
        switch (level) {
        case 1: return 0xe8c82efb;
        case 2: return 0xe8c82ef8;
        case 3: return 0xe8c82ef9;
        case 4: return 0xe8c82efe;
        case 5: return 0xe8c82eff;
        default: return 0xe8c82eff;
        }
        break;
    case 0xb1c3e5c2:
        switch (level) {
        case 1: return 0x33280b7b;
        case 2: return 0x33280b78;
        case 3: return 0x33280b79;
        case 4: return 0x33280b7e;
        case 5: return 0x33280b7f;
        default: return 0x33280b7f;
        }
        break;
    case 0xb1c3e5c3:
        switch (level) {
        case 1: return 0x096bbf4f;
        case 2: return 0x096bbf4c;
        case 3: return 0x096bbf4d;
        case 4: return 0x096bbf4a;
        case 5: return 0x096bbf4b;
        default: return 0x096bbf4b;
        }
        break;
    case 0xb1c3e5c4:
        switch (level) {
        case 1: return 0x261c3dfc;
        case 2: return 0x261c3dff;
        case 3: return 0x261c3dfe;
        case 4: return 0x261c3df9;
        case 5: return 0x261c3df8;
        default: return 0x261c3df8;
        }
        break;
    case 0x3386c531:
        switch (level) {
        case 1: return 0x66f663e2;
        case 2: return 0x66f663e1;
        case 3: return 0x66f663e0;
        case 4: return 0x66f663e7;
        case 5: return 0x66f663e6;
        default: return 0x66f663e6;
        }
        break;
    case 0x055d370e:
        switch (level) {
        case 1: return 0x8b165dc1;
        case 2: return 0x8b165dc2;
        case 3: return 0x8b165dc3;
        case 4: return 0x8b165dc4;
        case 5: return 0x8b165dc5;
        default: return 0x8b165dc5;
        }
        break;
    case 0x055d3747:
        switch (level) {
        case 1: return 0xab202126;
        case 2: return 0xab202125;
        case 3: return 0xab202124;
        case 4: return 0xab202123;
        case 5: return 0xab202122;
        default: return 0xab202122;
        }
        break;
    case 0x055d374c:
        switch (level) {
        case 1: return 0x91935c22;
        case 2: return 0x91935c21;
        case 3: return 0x91935c20;
        case 4: return 0x91935c27;
        case 5: return 0x91935c26;
        default: return 0x91935c26;
        }
        break;
    case 0x055d3750:
        switch (level) {
        case 1: return 0xd4a90632;
        case 2: return 0xd4a90631;
        case 3: return 0xd4a90630;
        case 4: return 0xd4a90637;
        case 5: return 0xd4a90636;
        default: return 0xd4a90636;
        }
        break;
    case 0x055d3754:
        switch (level) {
        case 1: return 0xdb579a5b;
        case 2: return 0xdb579a58;
        case 3: return 0xdb579a59;
        case 4: return 0xdb579a5e;
        case 5: return 0xdb579a5f;
        default: return 0xdb579a5f;
        }
        break;
    case 0x11b78a70: return 0x5979cecb; break;
    case 0x11b78a71: return 0x34d6bd1e; break;
    case 0x11b78a72: return 0x157aa4e5; break;
    case 0x06329468: return 0xfd503a02; break;
    case 0x06329469: return 0x10c8a72e; break;
    case 0x0632946a: return 0x0f615124; break;
    case 0x11b79302: return 0x91c3bf70; break;
    case 0x066783b4: return 0xab97cd36; break;
    case 0x04d18efd: return 0x9052db45; break;
    case 0x04d192a1:
    case 0x11b79a74: return 0xb8221536; break;
    case 0x04d192a2:
    case 0x11b79a70: return 0xb56f5ab9; break;
    case 0x11b79a71: return 0x8a30ddc4; break;
    case 0x11b79a72: return 0xefd1720c; break;
    case 0x032f92e6: return 0x2d94dcd7; break;
    case 0x11b79a75: return 0xb40fb63b; break;
    case 0x11b79a76: return 0x6701d2bb; break;
    case 0x11b79a77: return 0x2b2d090b; break;
    case 0x04d192a3:
    case 0x11b79a78: return 0x6596f453; break;
    case 0x4d192a14: return 0xefbe61be; break;
    case 0x177209ee: return PropHash("CL_Herbivore_Carnivore"); break;
    case 0x64e7222b: return PropHash("CL_Herbivore_Proboscis"); break;
    case 0xf613df04: return PropHash("CL_Carnivore_Proboscis"); break;
    case 0x50c34699: return PropHash("CL_Herbivore_Carnivore_Proboscis"); break;
    case 0x0732c356:
        switch (level) {
        case 1: return PropHash("Adventurer_Missile1");
        case 2: return PropHash("Adventurer_Missile2");
        case 3: return PropHash("Adventurer_Missile3");
        default: return PropHash("Adventurer_Missile1");
        }
        break;
    case 0x073930ea:
        switch (level) {
        case 1: return PropHash("Adventurer_EnergyBlade1");
        case 2: return PropHash("Adventurer_EnergyBlade2");
        case 3: return PropHash("Adventurer_EnergyBlade3");
        default: return PropHash("Adventurer_EnergyBlade1");
        }
        break;
    case 0x073ce5dd: return PropHash("Adventurer_EnergyRegen"); break;
    case 0x073e33c7: return PropHash("Adventurer_ShieldGenerator"); break;
    case 0x074260ec:
        switch (level) {
        case 1: return PropHash("Adventurer_HoloCharm1");
        case 2: return PropHash("Adventurer_HoloCharm2");
        case 3: return PropHash("Adventurer_HoloCharm3");
        default: return PropHash("Adventurer_HoloCharm1");
        }
        break;
    case 0x075f5ba0:
        switch (level) {
        case 1: return PropHash("Adventurer_LightningSword1");
        case 2: return PropHash("Adventurer_LightningSword2");
        case 3: return PropHash("Adventurer_LightningSword3");
        default: return PropHash("Adventurer_LightningSword1");
        }
        break;
    case 0x075f5ba6:
        switch (level) {
        case 1: return PropHash("Adventurer_PulseGun1");
        case 2: return PropHash("Adventurer_PulseGun2");
        case 3: return PropHash("Adventurer_PulseGun3");
        default: return PropHash("Adventurer_PulseGun1");
        }
        break;
    case 0x075f5bab: return PropHash("Adventurer_BattleArmor"); break;
    case 0x075f5baf: return PropHash("Adventurer_PoweredArmor"); break;
    case 0x075f5bb4: return PropHash("Adventurer_AbsorptionShield"); break;
    case 0x075f5bb7: return PropHash("Adventurer_HealthRegen"); break;
    case 0x075f5bbc: return PropHash("Adventurer_HealthBonus1"); break; break;
    case 0x075f5bbf: return PropHash("Adventurer_SummonSwarm1"); break;
    case 0x075f5bc3: return PropHash("Adventurer_MindMeld1"); break;
    case 0x075f5bc8: return PropHash("Adventurer_PoisonBlade1"); break;
    case 0x075f5bcb: return PropHash("Adventurer_Freeze1"); break;
    case 0x075f5bcf: return PropHash("Adventurer_GracefulWaltz1"); break;
    case 0x075f5bd2: return PropHash("Adventurer_HarmoniousSong1"); break;
    case 0x075f5bd6: return PropHash("Adventurer_RoyalCharm1"); break;
    case 0x075f5bda: return PropHash("Adventurer_RadiantPose1"); break;
    case 0x075f5bde: return PropHash("Adventurer_SprintBurst1"); break;
    case 0x075f5be3: return PropHash("Adventurer_Hover1"); break;
    case 0x075f5be6: return PropHash("Adventurer_StealthField1"); break;
    case 0x075f5bea: return PropHash("Adventurer_JumpJet1"); break;
    case 0x075f5bee:
        switch (level) {
        case 1: return PropHash("Adventurer_InspiringSong1");
        case 2: return PropHash("Adventurer_InspiringSong2");
        case 3: return PropHash("Adventurer_InspiringSong3");
        default: return PropHash("Adventurer_InspiringSong1");
        }
        break;
    case 0x075f5bf2:
        switch (level) {
        case 1: return PropHash("Adventurer_StunningDance1");
        case 2: return PropHash("Adventurer_StunningDance2");
        case 3: return PropHash("Adventurer_StunningDance3");
        default: return PropHash("Adventurer_StunningDance1");
        }
        break;
    case 0x075f5bf7:
        switch (level) {
        case 1: return PropHash("Adventurer_ConfettiPose1");
        case 2: return PropHash("Adventurer_ConfettiPose2");
        case 3: return PropHash("Adventurer_ConfettiPose3");
        default: return PropHash("Adventurer_ConfettiPose1");
        }
        break;
    case 0x075f5bfa: return PropHash("Adventurer_EnergyStorage1");
    }
    return 0;
}
}  // namespace SP
