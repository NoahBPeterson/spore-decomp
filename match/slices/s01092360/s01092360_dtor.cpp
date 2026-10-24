// Slice s01092360: hkPoweredHingeConstraintData::~hkPoweredHingeConstraintData (Havok 3.1.0,
// 0x01092D80, 51 bytes).  Releases the motor reference at +0x98 through an inlined
// hkReferencedObject::removeReference and lets the empty base destructor restore the
// hkReferencedObject vtable.  Flags: /vc71 /O2 /MD /Gy /TP.
#include "types.h"

class hkReferencedObject
{
public:
	virtual ~hkReferencedObject() {}        // +0x00 (the deleting destructor is called on last ref)

	uint16_t mLockCount;                    // +0x04
	uint16_t mReferenceCount;               // +0x06
};

// hkReferencedObject::removeReference inlined: nothing while the object is locked, then drop the
// reference count and delete it when it reaches zero.
__forceinline void hkRemoveReference(hkReferencedObject* obj)
{
	if (obj == 0 || obj->mLockCount == 0)
		return;
	obj->mReferenceCount--;
	if (obj->mReferenceCount == 0)
		delete obj;
}

class hkPoweredHingeConstraintData : public hkReferencedObject
{
public:
	virtual void buildJacobian(const void* in, void* out);   // gives the class its own vtable

	uint32_t mPad008[(0x098 - 0x008) / 4];                  // +0x08 (hinge configuration / limits)

	hkReferencedObject* m_motor;                            // +0x98

	~hkPoweredHingeConstraintData();
};

// @ 0x01092D80
hkPoweredHingeConstraintData::~hkPoweredHingeConstraintData()
{
	hkRemoveReference(m_motor);
}
