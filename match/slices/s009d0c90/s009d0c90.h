// nSPCreatureAnim dynamics slice s009d0c90 (0x009D0C90..0x009D1B3C).
//
// The nine functions all operate on the creature-animation "dynamics" instance: a skeleton whose bone
// table is 0x108 bytes per bone (interesting scalar at +0xAC), a list of active bone indices at
// +0xBC..+0xC0, and an array of 0x38-byte dynamics layers at +0x4C..+0x50 (each layer owns an array of
// bone pointers at +0x04..+0x08).
#ifndef S009D0C90_H
#define S009D0C90_H

#include "types.h"

struct AnimBone
{
    char pad0[0x6C];
    float m_field6C;        // +0x6C
    float m_field70;        // +0x70
    float m_field74;        // +0x74
    float m_field78;        // +0x78
    float m_field7C;        // +0x7C
    float m_field80;        // +0x80
    float m_field84;        // +0x84
    float m_field88;        // +0x88
    char pad8C[0x98 - 0x8C];
    float m_field98;        // +0x98
    char pad9C[0xAC - 0x9C];
    float m_fieldAC;        // +0xAC  (the scalar the min/max reductions read)
    char padB0[0xD4 - 0xB0];
    float m_fieldD4;        // +0xD4
    float m_fieldD8;        // +0xD8
    char padDC[0x108 - 0xDC];
};

struct AnimSkeleton
{
    char pad0[0x24];
    AnimBone* m_bones;      // +0x24
};

// one 0x38-byte dynamics layer: a vector<AnimBone*> (begin/end) at +0x04..+0x08
struct AnimDynamicsLayer
{
    char pad0[4];
    AnimBone** m_begin;     // +0x04
    AnimBone** m_end;       // +0x08
    char pad0C[0x38 - 0x0C];

    void destroy();         // 0x009D0B80
};

// one 12-byte phase sample: an angle at +0 and two weights.
struct AnimPhase
{
    float m_angle;          // +0x00
    float m_field04;        // +0x04
    float m_field08;        // +0x08
};

// the phase block the accumulators read (a vector<AnimPhase> at +0x0C..+0x10 plus tuning scalars).
struct AnimPhaseData
{
    char pad0[4];
    float m_f04;            // +0x04
    int m_count;            // +0x08  (-1 = no phase data)
    AnimPhase* m_begin;     // +0x0C
    AnimPhase* m_end;       // +0x10
    char pad14[0x34 - 0x14];
    float m_f34;            // +0x34
    float m_f38;            // +0x38
    float m_f3c;            // +0x3C
    float m_f40;            // +0x40
    float m_f44;            // +0x44
    float m_f48;            // +0x48
    float m_f4c;            // +0x4C
    float m_f50;            // +0x50
    float m_f54;            // +0x54
    float m_f58;            // +0x58
    float m_f5c;            // +0x5C
    float m_f60;            // +0x60
    float m_f64;            // +0x64
    float m_f68;            // +0x68
    float m_f6c;            // +0x6C
    float m_f70;            // +0x70
    float m_f74;            // +0x74
    float m_f78;            // +0x78
    float m_f7c;            // +0x7C
    float m_f80;            // +0x80
    float m_f84;            // +0x84
    float m_f88;            // +0x88
    float m_f8c;            // +0x8C
    float m_f90;            // +0x90
    float m_f94;            // +0x94
    float m_f98;            // +0x98
};

struct Vec4
{
    float x, y, z, w;
};

class nSPCreatureAnimDynamics
{
public:
    char pad0[0x10];
    float m_field10[14];            // +0x10..+0x44
    AnimSkeleton* m_skeleton;       // +0x48
    AnimDynamicsLayer* m_layers;    // +0x4C
    AnimDynamicsLayer* m_layersEnd; // +0x50
    char pad54[0x60 - 0x54];
    float m_field60;                // +0x60
    float m_field64;                // +0x64
    float m_field68;                // +0x68
    float m_field6C;                // +0x6C
    float m_field70;                // +0x70
    float m_field74;                // +0x74
    float m_field78;                // +0x78
    float m_field7C;                // +0x7C
    float m_field80;                // +0x80
    float m_field84;                // +0x84
    float m_field88;                // +0x88
    char pad8C[0x98 - 0x8C];
    float m_field98;                // +0x98
    char pad9C[0xBC - 0x9C];
    int* m_activeBones;             // +0xBC
    int* m_activeBonesEnd;          // +0xC0
    char padC4[0xD4 - 0xC4];
    float m_fieldD4;                // +0xD4
    float m_fieldD8;                // +0xD8
    char padDC[0xE0 - 0xDC];
    float m_boundMin[3];            // +0xE0
    float m_boundMax[3];            // +0xEC
    float m_sum[3];                 // +0xF8

    float getMaxBoneValue() const;                                  // 0x009D0C90
    float getMinBoneValue() const;                                  // 0x009D0DB0
    int findSteepestBone() const;                                   // 0x009D0EE0
    void destroyLayers();                                           // 0x009D1050
    void computeBounds(AnimBone** bones);                           // 0x009D1090
    void getExtentAndCentre(Vec4& extent, Vec4& centre) const;      // 0x009D12C0
    void resetBoneFields(const AnimPhaseData* data);                // 0x009D13A0
    void accumulate(float dt, const AnimPhaseData* data);           // 0x009D15E0
    void computeAngles(const AnimPhaseData* data);                  // 0x009D19B0
};

#endif
