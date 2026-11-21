// Slice s010c4d40: Havok 3.1.0 hkTriSampledHeightFieldCollection destructor (scalar deleting form): releases
// its heightfield shape and frees the instance through hkMemory (memory class 0x24). Same code as
// hkConvexTranslateShape's destructor 0x010c0110 (slice s010bfbe0).
// Flags: /vc71 /O2 /MD /Gy /TP
#include "../s0107e670/hk31_base.h"

class hkShape : public hkReferencedObject
{
public:
    virtual int getType() const;  // 2
    int m_userData;               // +0x08
};

class hkShapeCollection : public hkShape
{
public:
    hkBool m_disableWelding;      // +0x0c
};

class hkSampledHeightFieldShape : public hkShape
{
};

class hkTriSampledHeightFieldCollection : public hkShapeCollection
{
public:
    virtual ~hkTriSampledHeightFieldCollection();
    static void operator delete(void* p)
    {
        hkMemory::s_instance->deallocateChunk(p, static_cast<hkReferencedObject*>(p)->m_memSizeAndFlags, 0x24);
    }

    const hkSampledHeightFieldShape* m_heightfield;  // +0x10
    float m_radius;                                  // +0x14
};

// 0x010c4d40 is the scalar deleting form of this destructor (manifest row names ??_G).
hkTriSampledHeightFieldCollection::~hkTriSampledHeightFieldCollection()
{
    const_cast<hkSampledHeightFieldShape*>(m_heightfield)->removeReference();
}

// ---- hkBreakableConstraintData (0x010980d0): the same destructor shape with the released child at
// +0x0c; memory class 0x29 (constraint).
class hkConstraintData : public hkReferencedObject
{
public:
    virtual int getType() const;
    unsigned int m_userData;  // +0x08
};

class hkBreakableConstraintData : public hkConstraintData
{
public:
    virtual ~hkBreakableConstraintData();
    static void operator delete(void* p)
    {
        hkMemory::s_instance->deallocateChunk(p, static_cast<hkReferencedObject*>(p)->m_memSizeAndFlags, 0x29);
    }

    hkConstraintData* m_constraintData;  // +0x0c
};

// 0x010980d0 is the scalar deleting form of this destructor (manifest row names ??_G).
hkBreakableConstraintData::~hkBreakableConstraintData()
{
    m_constraintData->removeReference();
}
