#include "game/types.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"

// The tuning values are read out of the property list through the variant's typed
// int accessor (0x0041e990), which the generated EA::Variant header does not declare.
struct Variant : EA::Variant
{
	int* GetInt();                                             // 0x0041e990
};
template <typename T> inline const T& MinInt(const T& a, const T& b) { return (b < a) ? b : a; }

class cTerraformTuning
{
public:
	EA::AutoRefCount<SP::cPropertyList> mPropList;             // +0x00
	int GetMaxBuildingsForT1Colony();                          // 0x01049e70
	int GetMaxBuildingsForT2Colony();                          // 0x01049eb0
	int GetMaxBuildingsForT3Colony();                          // 0x01049ef0
};

// @ 0x01049e70
int cTerraformTuning::GetMaxBuildingsForT1Colony()
{
	int result = 0;
	SP::cPropertyList* list = mPropList;
	if (list)
	{
		const EA::Variant* prop;
		if (list->GetProperty(0x04a5d473, &prop) && prop->mTypeId == 9)
			result = *((Variant*)prop)->GetInt();
	}
	return result;
}

// @ 0x01049eb0
int cTerraformTuning::GetMaxBuildingsForT2Colony()
{
	int result = 0;
	SP::cPropertyList* list = mPropList;
	if (list)
	{
		const EA::Variant* prop;
		if (list->GetProperty(0x04a5d46d, &prop) && prop->mTypeId == 9)
			result = *((Variant*)prop)->GetInt();
	}
	return result;
}

// @ 0x01049ef0
int cTerraformTuning::GetMaxBuildingsForT3Colony()
{
	int value = 0;
	SP::cPropertyList* list = mPropList;
	if (list)
	{
		const EA::Variant* prop;
		if (list->GetProperty(0x052f046e, &prop) && prop->mTypeId == 9)
			value = *((Variant*)prop)->GetInt();
	}
	return MinInt(value, 20);
}
