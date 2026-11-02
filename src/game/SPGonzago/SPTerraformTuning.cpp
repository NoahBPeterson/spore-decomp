// src/game/SPGonzago/SPTerraformTuning.cpp -- migrated from slice(s) s01049040 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTerraformTuning.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPlanetModel.h"
#include <math.h>

// ---- items of slice s01049040 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Property
{
	uint8_t pad[0x12];
	uint16_t mType;                                            // +0x12
	int* GetInt();                                             // 0x0041e990
};
struct cPropertyList
{
	virtual int AddRef();                                      // +0x00
	virtual int Release();                                     // +0x04
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
	virtual bool GetProperty(uint32_t hash, Property** out);   // +0x24
};
namespace EA {
template <typename T>
class AutoRefCount_s0104_9040
{
public:
	T* mpObject;
	AutoRefCount_s0104_9040() : mpObject(0) {}
	~AutoRefCount_s0104_9040() { if (mpObject) mpObject->Release(); }
	T* operator->() const { return mpObject; }
	operator T*() const { return mpObject; }
	AutoRefCount_s0104_9040& operator=(T* p)
	{
		if (p != mpObject)
		{
			T* const old = mpObject;
			if (p)
				p->AddRef();
			mpObject = p;
			if (old)
				old->Release();
		}
		return *this;
	}
};  // namespace EA
}
struct cTerraformTuning
{
	EA::AutoRefCount_s0104_9040<cPropertyList> mPropList;                 // +0x00
	void Init();                                               // 0x01049a20
	int GetMaxBuildingsForT1Colony();                          // 0x01049e70
	int GetMaxBuildingsForT2Colony();                          // 0x01049eb0
	int GetMaxBuildingsForT3Colony();                          // 0x01049ef0
};
template <typename T> inline const T& MinInt(const T& a, const T& b) { return (b < a) ? b : a; }
// ---- items of slice s01049040 end

// @ 0x01049e70
int cTerraformTuning::GetMaxBuildingsForT1Colony()
{
	int result = 0;
	cPropertyList* list = mPropList;
	if (list)
	{
		Property* prop;
		if (list->GetProperty(0x04a5d473, &prop) && prop->mType == 9)
			result = *prop->GetInt();
	}
	return result;
}

// @ 0x01049eb0
int cTerraformTuning::GetMaxBuildingsForT2Colony()
{
	int result = 0;
	cPropertyList* list = mPropList;
	if (list)
	{
		Property* prop;
		if (list->GetProperty(0x04a5d46d, &prop) && prop->mType == 9)
			result = *prop->GetInt();
	}
	return result;
}

// @ 0x01049ef0
int cTerraformTuning::GetMaxBuildingsForT3Colony()
{
	int value = 0;
	cPropertyList* list = mPropList;
	if (list)
	{
		Property* prop;
		if (list->GetProperty(0x052f046e, &prop) && prop->mType == 9)
			value = *prop->GetInt();
	}
	return MinInt(value, 20);
}
