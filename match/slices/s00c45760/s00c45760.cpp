// Slice s00c45760 -- SP::cSPMission::PickRewardTool (retail 0x00c45760, 252 bytes).
//
// Picks the reward tool a mission offers. The owner empire's trait selects a
// trait-specific tool property; the tool property is looked up in the mission's
// property list and one entry of its Key (or Key array) value is drawn with the
// global RNG. No property list / no such property yields the invalid key.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

namespace EA {

// EA::Variant, 0x14 bytes: 16-byte value union, flags at +0x10, type id at
// +0x12. When bits 0x30 of the flags are set the value is an array pointed to
// by mPointer, otherwise a single inline element lives in the union itself.
struct Variant {
    struct Pointer {
        void *mpData;                                        // 0x000
        u32 mElementSize;                                    // 0x004
        u32 mElementCount;                                   // 0x008
    };
    union {
        Pointer mPointer;
        u8 mData[16];
    };
    u16 mFlags;                                              // 0x010
    u16 mTypeId;                                             // 0x012
};

namespace ResourceMan {

// EA::ResourceMan::Key, 0xc bytes -- same members and constructor as the
// generated EA/ResourceMan/Key.h (Key(unsigned int, unsigned __int64, unsigned
// int)). The middle argument is the long instance id; its high half is the type.
// The retail symbols mangle it as a struct (?AUKey...), so keep `struct`.
struct Key {
    Key(u32 instance, unsigned __int64 longInstanceId, u32 group)
        : mInstance(instance), mType((u32)(longInstanceId >> 32)), mGroup(group) {}

    u32 mInstance;                                           // 0x000
    u32 mType;                                               // 0x004
    u32 mGroup;                                              // 0x008
};

}  // namespace ResourceMan
}  // namespace EA

namespace SP {

// SP::cPropertyList -- only the virtuals PickRewardTool dispatches through are
// named; the slots before them are kept so +0x1c / +0x28 stay correct.
class cPropertyList {
 public:
    virtual void vf00();                                     // slot 0
    virtual void vf04();                                     // slot 1
    virtual void vf08();                                     // slot 2
    virtual void vf0c();                                     // slot 3
    virtual void vf10();                                     // slot 4
    virtual void vf14();                                     // slot 5
    virtual void vf18();                                     // slot 6
    virtual bool HasProperty(u32 id) const;                  // slot 7, vt+0x1c
    virtual void vf20();                                     // slot 8
    virtual void vf24();                                     // slot 9
    virtual EA::Variant const &GetProperty(u32 id) const;    // slot 10, vt+0x28
};

class cSPMission {
 public:
    void *GetOwnerEmpire() const;                            // 0x00c451e0
    EA::ResourceMan::Key PickRewardTool() const;             // 0x00c45760

 private:
    // The mission's property list, at this+0x180 (the generated header's
    // mMissionPropList offset does not match this function's retail build).
    SP::cPropertyList *GetPropertyList() const
    {
        return *(SP::cPropertyList *const *)((const u8 *)this + 0x180);
    }
};

}  // namespace SP

// EA's global RNG, called as a member with ecx = the generator object.
struct RandomLCG {
    u32 __thiscall RandomUint32Uniform(u32 n);               // 0x00a68fb0
};
extern RandomLCG g_sMathRandom;                              // 0x01601760

// The invalid tool key every failure path returns (0x0168e844).
extern const EA::ResourceMan::Key kInvalidToolKey;           // 0x0168e844

// @ 0x00c45760
EA::ResourceMan::Key SP::cSPMission::PickRewardTool() const
{
    // The owner empire's trait decides which trait-specific tool to prefer.
    u32 trait = 0;
    void *empire = GetOwnerEmpire();
    if (empire != 0) trait = *(const u32 *)((const u8 *)empire + 0x54);

    u32 toolID = 0xe1261ed6;                                 // default tool property
    u32 traitToolID = 0;                                     // trait specific tool property
    switch (trait) {
    case 1: traitToolID = 0x27eb756a; break;
    case 2: traitToolID = 0x1ff96460; break;
    case 3: traitToolID = 0x209f3e3; break;
    }

    // The member is re-read (not cached) at each use, as the retail build does.
    // Every failure falls through to the one invalid-key return at the end.
    int count = 0;
    if (GetPropertyList() != 0) {
        if (traitToolID != 0 && GetPropertyList()->HasProperty(traitToolID))
            toolID = traitToolID;

        if (GetPropertyList()->HasProperty(toolID)) {
            const EA::Variant &value = GetPropertyList()->GetProperty(toolID);

            // A Key array value has its element count in the pointer form; a
            // single inline key counts as one. A typed-but-empty value (no
            // type id) has nothing to draw from.
            if ((value.mFlags & 0x30) != 0)
                count = (int)value.mPointer.mElementCount;
            else if (value.mTypeId != 0)
                count = 1;

            if (count > 0) {
                const u32 *elements =
                    ((value.mFlags & 0x30) != 0)
                        ? (const u32 *)value.mPointer.mpData
                        : (value.mTypeId != 0 ? (const u32 *)&value : (const u32 *)0);

                // The drawn element carries the instance only: the tool key has
                // no type or group.
                return EA::ResourceMan::Key(
                    ((const EA::ResourceMan::Key *)elements)
                        [g_sMathRandom.RandomUint32Uniform((u32)count)]
                            .mInstance,
                    0, 0);
            }
        }
    }
    return kInvalidToolKey;
}
