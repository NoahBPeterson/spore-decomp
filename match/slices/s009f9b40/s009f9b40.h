// nSPCreatureAnim layout slice s009f9b40 (0x009F9B40..0x009FA99C).
//
// The ten functions operate on a creature-animation "layout" record: a hierarchy pointer at +0x00, a
// node/pool pointer at +0x08, a quaternion at +0x148..+0x154, two 3-float vectors at +0x158/+0x164, a
// 7-float derived matrix at +0x170 echoed from the source matrix at +0x190, a byte cache at +0x1b8
// mirrored to +0x1f8, an update counter at +0x1ac, and a 0x2BC-byte element pool at +0x2e4..+0x2e8.
#ifndef S009F9B40_H
#define S009F9B40_H

#include "types.h"

struct AnimLayout;

// the hierarchy the layout points at (+0x00): a rotation quaternion at +0x128, two ints at +0x204 /
// +0x20c, three 3-float vectors at +0x344 / +0x350 / +0x35c and two flags at +0x370 / +0x371.
struct AnimHierarchy
{
    char pad0[0x128];
    float m_quat[4];        // +0x128
    char pad138[0x204 - 0x138];
    int m_204;              // +0x204
    int m_208;              // +0x208
    int m_20c;              // +0x20C
    char pad210[0x344 - 0x210];
    float m_v344[3];        // +0x344
    float m_v350[3];        // +0x350
    float m_v35c[3];        // +0x35C
    char pad368[0x370 - 0x368];
    unsigned char m_flag370;    // +0x370
    unsigned char m_flag371;    // +0x371
};

// the second object a layout points at (+0x08), also reachable as owner->m_08: a 7-float matrix at
// +0x190 and a 4-float quaternion-ish block at +0x19C.
struct AnimNodeBlock
{
    char pad0[0x190];
    float m_src[7];         // +0x190..+0x1A8
};

// The +0x150 sub-object. Its two methods (0x009B30E0 / 0x009B3110) are __thiscall: the object goes
// in ecx and the callee pops its own stack arguments, so they are declared as members rather than as
// extern "C" functions (a cdecl declaration makes the original's call sites mismatch the callee).
struct AnimNameRef
{
    unsigned char m_bytes[8];       // +0x00 (raw name text)
    bool HasTag(int tag) const;     // 0x009B30E0
    int  GetValue() const;          // 0x009B3110
};

struct AnimLayout
{
    AnimHierarchy* m_hier;      // +0x00
    char pad04[4];
    AnimNodeBlock* m_nodes;     // +0x08
    char pad0C[4];
    unsigned char m_flag10;     // +0x10
    char pad11[0x38 - 0x11];
    unsigned char m_flag38;     // +0x38
    char pad39[0x70 - 0x39];
    float m_f70;                // +0x70
    char pad74[0x138 - 0x74];
    float m_f138;               // +0x138
    char pad13C[4];
    float m_f140;               // +0x140
    char pad144[4];
    float m_quat[4];            // +0x148..+0x154
    float m_v158[3];            // +0x158
    float m_v164[3];            // +0x164
    float m_mat[7];             // +0x170..+0x188
    char pad18C[4];
    float m_src[7];             // +0x190..+0x1A8
    int m_counter;              // +0x1AC
    float m_f1b0;               // +0x1B0
    float m_f1b4;               // +0x1B4
    union
    {
        float m_f1b8;           // +0x1B8
        unsigned char m_cache[0x40];// +0x1B8 (same slot, byte view)
    };
    unsigned char m_mirror[0x40];// +0x1F8
    char pad238[0x2e4 - 0x238];
    unsigned char* m_poolBegin; // +0x2E4
    unsigned char* m_poolEnd;   // +0x2E8
    char pad2EC[0x370 - 0x2EC];
    unsigned char m_flag370;    // +0x370
    unsigned char m_flag371;    // +0x371
};

// the +0x150 sub-object with the two name methods.
struct AnimNameHolder
{
    char pad0[0x150];
    AnimNameRef m_name;         // +0x150
    char pad158[0x208 - 0x158];
    int m_208;                  // +0x208
};

#endif
