// Havok 3.1.0 slice s01102fc0: MOPP long-ray machine, MOPP compiler settings, hkAgent1nMachine track walkers.
// Struct stubs carry members at the offsets seen in the 32-bit binary (pointer members make 64-bit sizes differ).
#pragma once
#include "types.h"
#include <stddef.h>

typedef float hkReal;
typedef float hkTime;
typedef uint8_t hkBool;

struct hkVector4 { float x, y, z, w; };
struct hkTransform {
    hkVector4 m_rot[3];
    hkVector4 m_trans;
    void setMulInverseMul(const hkTransform& a, const hkTransform& b);   // this = inverse(a) * b
    void setInverse(const hkTransform& t);
};
struct hkSweptTransform { uint32_t m_data[20]; };                            // 0x50 bytes at hkMotionState+0x40
struct hkMotionState {                                                       // hkCdBody::m_motion points at one
    hkTransform m_transform;                                                 // +0
    hkSweptTransform m_sweptTransform;                                       // +0x40
};
struct hkSweptTransformUtil { static void lerp2(const hkSweptTransform& swept, float t, hkTransform& out); };

struct hkReferencedObject {
    virtual void* hkReferencedObject_deletingDtor(unsigned int flags);
    uint16_t m_memSizeAndFlags;
    int16_t  m_referenceCount;
};

// hkMemory::s_instance @0x016e4178 (vtable slots as used in this slice)
struct hkMemory {
    virtual void* allocate(int nbytes, int memClass);                        // slot 0
    virtual void  deallocate(void* p);                                       // slot 1
    virtual void  v2(); virtual void v3();
    virtual void* allocateChunk(int nbytes, int memClass);                   // slot 4
    virtual void  deallocateChunk(void* p, int nbytes, int memClass);        // slot 5
    virtual void* allocateChunkFromSizeClass(int sizeIndex, int memClass);   // slot 6
    static hkMemory* s_instance;
};

struct hkCdBody {
    const void* m_shape; uint32_t m_shapeKey; const hkMotionState* m_motion; const hkCdBody* m_parent;
};

struct hkContactMgr;
struct hkCollisionDispatcher;
struct hkCollisionInput;
struct hkCollisionFilter {
    // vtable slot 0 (returns hkBool through a hidden pointer in the binary)
    virtual hkBool isCollisionEnabled(const hkCollisionInput& input, const hkCdBody& a, const hkCdBody& b, const void* bContainer, uint32_t bKey) const;
};
struct hkCollisionInput {
    hkCollisionDispatcher* m_dispatcher;      // +0
    hkCollisionFilter* m_filter;              // +4
    uint32_t m_pad[2];
    float m_stepTime;                         // +0x10  (time handed to hkSweptTransformUtil::lerp2)
};

// ---- MOPP ------------------------------------------------------------------------------------------------
struct hkMoppCode : hkReferencedObject {
    uint32_t m_pad0;                          // +8
    uint32_t m_pad1;                          // +0xc
    hkVector4 m_offset;                       // +0x10: xyz = offset, w = scale (CodeInfo::getScale)
    uint8_t* m_data;                          // +0x20 (hkArray<hkUint8>::m_data)
    int m_dataSize;
    int m_dataCapacityAndFlags;
};
struct hkShapeRayCastInput {                  // 40 bytes
    hkVector4 m_from;                         // +0
    hkVector4 m_to;                           // +0x10
    uint32_t m_filterInfo;                    // +0x20
    uint32_t m_userData;                      // +0x24
};
struct hkShapeRayCastOutput;
struct hkRayHitCollector { virtual void v0(); float m_earlyOutHitFraction; };      // fraction at +4
struct hkShapeCollection;

struct hkMoppLongRayVirtualMachine {
    uint8_t m_pad0[0x10];                     // +0
    const hkMoppCode* m_code;                 // +0x10
    float m_invScale;                         // +0x14
    uint8_t m_pad1[8];                        // +0x18
    hkShapeRayCastInput m_rayInput;           // +0x20 .. 0x48
    uint8_t m_pad2[8];                        // +0x48
    hkBool m_hit;                             // +0x50
    uint8_t m_pad3[3];
    float m_hitFraction;                      // +0x54  (early out hit fraction)
    hkShapeRayCastOutput* m_output;           // +0x58
    hkRayHitCollector* m_collector;           // +0x5c
    const hkCdBody* m_cdBody;                 // +0x60
    const hkShapeCollection* m_shapeCollection; // +0x64
    hkBool queryLongRay(const hkShapeCollection* collection, const hkMoppCode* code, const hkShapeRayCastInput& input, hkShapeRayCastOutput& output);
    void   queryLongRay(const hkShapeCollection* collection, const hkMoppCode* code, const hkShapeRayCastInput& input, const hkCdBody& body, hkRayHitCollector& collector);
    void   queryRay(const hkVector4* zeroVec, const uint8_t* moppData, const float* fromTo);   // FUN_01102010 (thiscall)
};
