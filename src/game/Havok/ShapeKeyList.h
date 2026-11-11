#ifndef HAVOK_SHAPE_KEY_LIST_H
#define HAVOK_SHAPE_KEY_LIST_H
#include "game/types.h"

class hkStatisticsCollector;
class hkVector4_s0110_2fc0;

class hkReferencedObject_s0110_2fc0 { public:
    hkReferencedObject_s0110_2fc0() : m_referenceCount(1) {}
    virtual void* hkReferencedObject_deletingDtor(unsigned int flags);
    virtual void calcStatistics(hkStatisticsCollector*) const; // 0x0052e650
    uint16_t m_memSizeAndFlags;
    int16_t  m_referenceCount;
};

struct hkShapeContainer {
    // vtable slots used here (hkShapeContainer in the 3.1 shape collection): 7 getNumChildShapes, 8 getFirstKey,
    // 9 getNextKey, 10 getChildShape
    virtual void c0();
    virtual void c1();
    virtual void c2();
    virtual void c3();
    virtual void c4();
    virtual void c5();
    virtual void c6();
    virtual int  getNumChildShapes() const;                                      // +0x1c
    virtual uint32_t getFirstKey() const;                                        // +0x20
    virtual uint32_t getNextKey(uint32_t oldKey) const;                          // +0x24
    virtual const struct hkProjShape* getChildShape(uint32_t key, void* buffer512) const;   // +0x28
};

// hkShapeKeyList supplies the eight slots at retail vtable 0x014a5dec.
// Declarations for the unimplemented slots preserve their native thiscall ABI.
struct hkShapeKeyList : hkReferencedObject_s0110_2fc0 {
    hkShapeKeyList(hkShapeContainer* container);
    virtual void* hkReferencedObject_deletingDtor(unsigned int flags); // 0x01103560
    virtual int getNumKeys() const; // 0x00fc7e50
    virtual void fillKeys(uint8_t* out) const; // 0x011032c0
    virtual void calcMinMaxProjectionsAndStore(const hkVector4_s0110_2fc0& dir, uint32_t* entries, int n, float* minOut, float* maxOut) const; // 0x01103370
    virtual void calcMinMaxProjections(const hkVector4_s0110_2fc0& dir, uint32_t* entries, int n, float* minOut, float* maxOut) const; // 0x01103470
    // This native slot returns the fourth copied source word in EAX.
    virtual uint32_t copyVector(const hkVector4_s0110_2fc0& value, const void*, const void*, const void*, hkVector4_s0110_2fc0* out) const; // 0x01103300
    virtual int getKey(const void* entry, uint32_t* out) const; // 0x011032a0
    hkShapeContainer* m_container; // +8
    int m_numKeys; // +0xc
};

#endif
