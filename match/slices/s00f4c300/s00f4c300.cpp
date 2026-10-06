// FUN_00f4c300  @ 0x00f4c300
//
// PARTIAL reconstruction. ~5816-byte unoptimized (/Od /Ob1) __fastcall object
// updater.  A species/type switch (1..0x14) selects one of the 0x44-byte preset
// records at 0x0148e2f8 (stride 0x48) -- those selects are reproduced; the long
// post-switch animation/particle stepping body (curve sampling, quaternion
// blending, RandomLinearCongruential roll, transform handoff) is outlined.
//
//   void __fastcall FUN_00f4c300(int* self)

#pragma once
typedef unsigned char byte;
typedef unsigned int  uint32;

extern "C" unsigned char DAT_0148e2f8[];  // preset record table (stride 0x48)
extern "C" unsigned char DAT_0148e268[];  // alt preset (cases 0xf/0x10)
extern "C" unsigned char DAT_0148e2b0[];  // alt preset (case 0x14)

// Preset record: 0x44 bytes = 0x11 dwords.
struct TuningPreset { uint32 v[0x11]; };

// callees (masked relocations)
extern "C" void FUN_00572590(void);
extern "C" int  FUN_00572c90(void);
extern "C" int  FUN_00684be0(float);
extern "C" float FUN_007d45d0(float, uint32);
extern "C" void* FUN_00f4b180(void);
extern "C" void FUN_00f4bcb0(float, TuningPreset&);
extern "C" void FUN_00f4b870(void*, void*, float, float, TuningPreset&);

// @ 0x00f4c300
void __fastcall FUN_00f4c300(int* self)
{
    // --- preset selection (switch on *(self[3] + 0x82)) ---
    TuningPreset preset;              // local_9c
    int presetMode = 6;               // uStack_74 default (set again below)
    int flags = 0;                    // uStack_8c

    if (*(char*)(self[3] + 0x80) != 0)
    {
        switch (*(unsigned char*)(self[3] + 0x82))
        {
        case 1:  case 2:  case 3:  case 4:  case 5:
        case 6:  case 7:
            preset = *(TuningPreset*)(DAT_0148e2f8 + (*(unsigned char*)(self[3] + 0x82) - 1) * 0x48);
            break;
        case 8:  case 9:  case 10:
            preset = *(TuningPreset*)(DAT_0148e2f8 + (*(unsigned char*)(self[3] + 0x82) - 1) * 0x48);
            presetMode = 6;
            break;
        case 0xb:
            preset = *(TuningPreset*)(DAT_0148e2f8 + 0xa * 0x48);
            break;
        case 0xc: case 0xd: case 0xe:
            preset = *(TuningPreset*)(DAT_0148e2f8 + (*(unsigned char*)(self[3] + 0x82) - 1) * 0x48);
            presetMode = 1;
            break;
        case 0xf: case 0x10:
            preset = *(TuningPreset*)DAT_0148e268;
            flags = *(uint32*)(self[3] + 0x84);
            if (*(unsigned char*)(self[3] + 0x82) == 0x10)
                flags ^= 0x80000000u;
            break;
        case 0x11: case 0x12: case 0x13:
            break;                     // keep the caller-initialised preset
        case 0x14:
            preset = *(TuningPreset*)DAT_0148e2b0;
            flags = *(uint32*)(self[3] + 0x84);
            break;
        default:
            return;
        }

        // mBlendMode overrides the preset mode.
        char b = *(char*)(self[3] + 0x83);
        if (b == 1)      presetMode = 0;
        else if (b == 2) presetMode = 1;
        else if (b == 3) presetMode = 6;
    }

    // --- partially reconstructed post-switch stepping body (omitted) ---
    // The original then, for up to `local_24 = FUN_005e4d30(...)` steps, samples
    // animation curves (FUN_00572c90/FUN_00684be0 piecewise lookup), builds
    // quaternions (SP::QuaternionFromDirections / FUN_005b26f0 slerp), advances
    // the phase (param_1[0x27..0x2f]), and either calls FUN_00f4b870(...) or the
    // editor path around FUN_00f4b160/FUN_00f4b180/FUN_00f4c150; finally it emits
    // the preset via FUN_00f4bcb0(local_100, preset) and invokes vtable slot +0xc.
    (void)presetMode;
    (void)flags;
    (void)preset;
    FUN_00572590();
}
