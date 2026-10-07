// Slice s00b38e50 -- Simulator::cGameViewManager::GetHoveredObject (0x00B38E50), vtable slot 0x30 of the
// vtable at 0x014609F4 (ModAPI: "/* 30h */ virtual cGameData* GetHoveredObject();").
// Casts the mouse pick ray into the Gonzago model world (and, in universe contexts 1 and 2, into the
// second model world at +0xE4), ranks every hit model's owner by the pick-priority table (+0xAC), the pick filter
// callback (+0x100) and distance, then makes the winner the hovered object (+0x88, ref-counted), notifying the
// rollover callback (+0xFC).
// Built /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the ref-counted locals have no EH frame); /fp:fast is what
// inlines sqrtf as fsqrt (without it cl calls _CIsqrt).
// Names: member names follow the 2008 PDB's SP::cGameViewManager (retail offsets are +4/+8) and ModAPI;
// everything marked "(name guessed)" is Claude-coined.
#include "types.h"
#include <math.h>
#include <float.h>

typedef uint8_t u8;
typedef uint32_t u32;

// Placeholder virtuals used to put a real method at its vtable slot.
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(_p, __COUNTER__)();
#define VP4 VP VP VP VP
#define VP16 VP4 VP4 VP4 VP4

enum
{
	kGameCreature = 0x1654C01,
	kGameTribe = 0x1654C02,
	kScenarioMode = 0x1654C10,
};
enum
{
	kTypeGameData = 0x17F243B,      // Simulator::cGameData::TYPE
	kTypeSpatialObject = 0x1186577, // Simulator::cSpatialObject::TYPE
	kType189e11f = 0x189E11F,       // unidentified interface: its presence alone makes an object pickable
	kTypeHitSphere = 0x2E71A5A,     // Simulator::cHitSphere::TYPE
	kPickGroupId = 0x7AA969B,       // model group whose bit makes a model "always pickable" (name guessed)
};

struct Vec3
{
	float x, y, z;
	Vec3() {}
	Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

// COM-style object: AddRef/Release at slots 0/1, Cast(TYPE) at slot 3.
struct Object
{
	virtual int AddRef();
	virtual int Release();
	VP
	virtual void* Cast(u32 type);   // 0xc
};

struct cGameData : Object
{
	VP4 VP VP VP
	virtual bool IsDestroyed();      // 0x2c (name guessed)
	VP VP
	virtual int GetPickGroup();      // 0x38 (name guessed): equal values = same owner/group
};

struct cSpatialObject : Object
{
	VP4 VP
	virtual bool IsRolloverSuppressed();                 // 0x24 (name guessed)
	VP
	virtual void* GetRolloverLight(float scale, int b);  // 0x2c (name guessed)
	char pad[0x6f - 4];
	bool mbPickable;                                     // 0x6f (name guessed)
};

struct Model;
struct cHitSphere
{
	char pad[0x24c];
	Object* mpOwner;   // 0x24c (name guessed): the object the hit sphere stands for
};

struct Model
{
	char pad[0x44];
	u32 mGroupBits[2];   // 0x44: eastl::bitset<64> of model groups
	char pad4c[0x18];
	Object* mpOwner;     // 0x64
};

// eastl::bitset<64>::test without exceptions: out-of-range bits read as clear.
static __forceinline bool TestBit(const u32* words, u32 n)
{
	if (n < 64)
		return (words[n >> 5] & (1 << (n & 31))) != 0;
	return false;
}

// One ray hit: model plus its parametric distance along the ray.
struct PickHit
{
	Model* model;
	float t;
};

// Argument of the pick filter callback (+0x100).
struct PickInfo
{
	Model* model;
	float t;
	Vec3 start;
	Vec3 end;
	bool flag;
};

// Physics/model query filter passed to the world's ray casts.
struct Filter
{
	u32 w0, w1, w2, w3;
	u32 e;
	u8 type;
	u8 z;
};

void __cdecl operator_delete_array(void* p);   // 0x00F47380 (operator delete[])

struct InsertTag {};
// eastl::fixed_vector<PickHit, 16> (mpBegin, mpEnd, mpCapacity, allocator with mpPoolBegin at +0x10, buffer at +0x18).
struct PickHitVector
{
	PickHit* mpBegin;
	PickHit* mpEnd;
	PickHit* mpCapacity;
	u32 mOverflowAllocator;
	PickHit* mpPoolBegin;
	u32 mPad14;
	PickHit mBuffer[16];

	PickHitVector()
	{
		mpPoolBegin = mBuffer;
		mpBegin = mBuffer;
		mpEnd = mBuffer;
		mpCapacity = mBuffer + 16;
	}
	~PickHitVector()
	{
		if (mpBegin && mpBegin != mpPoolBegin)
			operator_delete_array(mpBegin);
	}
	u32 size() const { return (u32)(mpEnd - mpBegin); }
	PickHit* begin() { return mpBegin; }
	PickHit* end() { return mpEnd; }
	void push_back(const PickHit& v);                                              // 0x00B38260
	void DoInsertFromIterator(PickHit* pos, PickHit* first, PickHit* last, InsertTag);   // 0x00B37720
	void insert(PickHit* pos, PickHit* first, PickHit* last) { DoInsertFromIterator(pos, first, last, InsertTag()); }
};

struct cIModelWorld
{
	virtual int AddRef();
	virtual int Release();
	VP4 VP4 VP VP
	virtual void Raycast(const Vec3& start, const Vec3& end, PickHitVector& hits, Filter& filter, float radius);   // 0x30
};

template <class T>
struct AutoRefCount
{
	T* mpObject;
	AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
	~AutoRefCount() { if (mpObject) mpObject->Release(); }
	AutoRefCount& operator=(T* p)
	{
		if (p != mpObject)
		{
			T* const pTemp = mpObject;
			if (p)
				p->AddRef();
			mpObject = p;
			if (pTemp)
				pTemp->Release();
		}
		return *this;
	}
	T* get() const { return mpObject; }
	T* operator->() const { return mpObject; }
	operator T*() const { return mpObject; }
};

struct cCamera
{
	void GetPickRay(Vec3* start, Vec3* end);   // 0x007C46F0 (name guessed)
};
struct cCameraOwner
{
	VP4 VP VP VP
	virtual cCamera* GetCamera();              // 0x1c (name guessed)
};
struct cApp
{
	VP16 VP4
	virtual cCameraOwner* GetCameraManager();  // 0x50 (name guessed)
};
struct cModelManager
{
	VP4 VP4 VP VP
	virtual u32 GetGroupIndex(u32 id, int b);   // 0x28 (name guessed)
};
struct cLightingManager
{
	VP16 VP16 VP16 VP VP
	virtual void SetRolloverLight(void* light);  // 0xc8 (name guessed)
};
struct cEditorThing
{
	VP16 VP16 VP4 VP4 VP VP VP
	virtual Model* GetModel();                   // 0xac (name guessed)
};
struct cScenarioPlayTarget
{
	Object* GetEditTarget();                     // 0x00F3D880 (name guessed)
};
struct cScenarioModeData
{
	char pad[0x74];
	cScenarioPlayTarget* mp74;                   // 0x74
	char pad78[0xcc - 0x78];
	int mMode;                                   // 0xcc: 1 = playing (name guessed)
};
extern cScenarioModeData* g_pScenarioMode;       // 0x016C7AA4

struct cSomeGameState
{
	bool IsBusy();                               // 0x00AC80F0 (name guessed)
};

cApp* App();                                     // 0x0067DD10 SP::App
unsigned GetCurrentGameMode();                   // 0x00B5B800 SP::GetCurrentGameMode
int GetUniverseContext();                        // 0x01021080 SP::cSPLivingUniverse::GetUniverseContext
cIModelWorld* GonzagoModelWorld();               // 0x00B3D520 SP::GonzagoModelWorld
cModelManager* ModelManager();                   // 0x0067DD80 SP::ModelManager
cLightingManager* LightingManager();             // 0x0067DE00
int __cdecl IsPickBlocker(Object* o);            // 0x00B18E20 (name guessed)
cGameData* GetTutorialObject();                  // 0x00EFE5A0 (name guessed)
bool __cdecl ScenarioTutorials_HasObjectByKey(cGameData* o);   // 0x00EFE610
bool IsUIModal();                                // 0x00DD1230 (name guessed)
bool IsUIBusy();                                 // 0x00E09540 (name guessed)
cSomeGameState* GetSomeGameState();              // 0x00B3D4D0 (name guessed)

extern const Vec3 kInvalidPosition;              // 0x0167E9A4 (name guessed)

struct PickPriority
{
	u32 mType;     // interface TYPE the owner must support
	int mKind;     // 1: skip for hit-sphere owners, 2: skip for others (name guessed)
	int mPriority; // lower wins
};

typedef void (__cdecl* RolloverCallback)(cSpatialObject* object, bool rolledOver);
typedef bool (__cdecl* PickFilterCallback)(PickInfo* info);

class cGameViewManager
{
public:
	VP4 VP4 VP4
	virtual Object* GetHoveredObject();                 // 0x30
	VP
	virtual Vec3 GetWorldPosition(int a, Vec3 fallback);   // 0x38 (ModAPI func38h_)

	char pad4[0x88 - 4];
	AutoRefCount<Object> mHoveredObject;                // 0x88 (PDB mCachedObjectUnderMouse)
	char pad8c[0xac - 0x8c];
	PickPriority* mPickPrioritiesBegin;                 // 0xac (PDB mPickPriorities)
	PickPriority* mPickPrioritiesEnd;                   // 0xb0
	char padb4[0xe4 - 0xb4];
	cIModelWorld* mpSecondaryWorld;                     // 0xe4 (name guessed)
	char pade8[0xfc - 0xe8];
	RolloverCallback mpObjectRolledOverCallback;        // 0xfc
	PickFilterCallback mpFilterPickedObjectCallback;    // 0x100
};

// @ 0x00b38e50
Object* cGameViewManager::GetHoveredObject()
{
	if (!App())
	{
		mHoveredObject = 0;
		return 0;
	}

	unsigned mode = GetCurrentGameMode();
	bool isScenarioPlay;
	bool isCreatureOrTribe;
	if (mode == kScenarioMode && g_pScenarioMode->mMode == 1)
	{
		isScenarioPlay = true;
		isCreatureOrTribe = false;
	}
	else
	{
		isScenarioPlay = false;
		if (mode == kGameCreature || mode == kGameTribe)
			isCreatureOrTribe = true;
		else
			isCreatureOrTribe = false;
	}

	bool isContext1 = false;
	float maxRayLength = FLT_MAX;
	int context = GetUniverseContext();
	switch (context)
	{
	case 0:
		if (isScenarioPlay)
			maxRayLength = 5000.0f;
		else
			maxRayLength = 1000.0f;
		break;
	case 1:
		maxRayLength = 3000.0f;
		isContext1 = true;
		break;
	case 2:
		maxRayLength = 50.0f;
		break;
	}

	Object* best = 0;
	cGameData* bestGameData = 0;
	cHitSphere* bestHitSphere = 0;

	Vec3 start, end;
	cCamera* camera = App()->GetCameraManager()->GetCamera();
	camera->GetPickRay(&start, &end);
	Vec3 dir;
	dir.x = end.x - start.x;
	dir.y = end.y - start.y;
	dir.z = end.z - start.z;
	float rayLength = sqrtf(dir.z * dir.z + dir.y * dir.y + dir.x * dir.x);
	if (rayLength > maxRayLength)
	{
		const float s = maxRayLength / rayLength;
		end.x = dir.x * s + start.x;
		end.y = dir.y * s + start.y;
		end.z = dir.z * s + start.z;
		rayLength = maxRayLength;
	}

	float maxPickDistance = FLT_MAX;
	if (context == 0)
	{
		Vec3 p = GetWorldPosition(0, kInvalidPosition);
		if (p.x != kInvalidPosition.x || p.y != kInvalidPosition.y || p.z != kInvalidPosition.z)
		{
			const float dx = p.x - start.x;
			const float dy = p.y - start.y;
			const float dz = p.z - start.z;
			maxPickDistance = sqrtf(dz * dz + dy * dy + dx * dx) + 1.0f;
		}
	}

	PickHitVector hits;
	float bestDistance = maxPickDistance;
	int bestPriority = 10000;
	AutoRefCount<cIModelWorld> world(GonzagoModelWorld());
	const u32 groupBit = ModelManager()->GetGroupIndex(kPickGroupId, 0);

	if (isScenarioPlay)
	{
		if (!world)
			goto done;
		Object* target = g_pScenarioMode->mp74->GetEditTarget();
		if (target)
		{
			PickHit hit;
			hit.t = 1e-4f;
			hit.model = ((cEditorThing*)target->Cast(kTypeSpatialObject))->GetModel();
			hits.push_back(hit);
		}
		else
		{
			Filter filter;
			filter.w0 = 0;
			filter.w1 = 0;
			filter.w2 = 0;
			filter.w3 = 0;
			filter.e = 0;
			filter.type = 3;
			filter.z = 1;
			world->Raycast(start, end, hits, filter, 0.0f);
		}

		PickInfo info;
		info.start = start;
		info.end = end;
		info.flag = false;
		const u32 count = hits.size();
		for (u32 i = 0; i < count; i++)
		{
			Model* model = hits.mpBegin[i].model;
			const float t = hits.mpBegin[i].t;
			if (!model || !model->mpOwner)
				continue;
			Object* owner = model->mpOwner;
			if (!owner)
				continue;
			cGameData* gameData = (cGameData*)owner->Cast(kTypeGameData);
			if (!gameData)
				continue;
			cSpatialObject* spatial = (cSpatialObject*)gameData->Cast(kTypeSpatialObject);
			if (gameData->IsDestroyed() || !spatial->mbPickable)
				continue;
			info.model = model;
			info.t = t;
			if (!mpFilterPickedObjectCallback || !mpFilterPickedObjectCallback(&info))
				continue;

			const bool inGroup = TestBit(model->mGroupBits, groupBit);
			int priority = inGroup ? 100 : 1000;
			if (gameData == GetTutorialObject() || ScenarioTutorials_HasObjectByKey(gameData))
				priority = 100;
			const float distance = t * rayLength;
			if ((inGroup || distance < maxPickDistance) &&
				(priority < bestPriority || (priority == bestPriority && distance < bestDistance)))
			{
				bestDistance = distance;
				bestPriority = priority;
				best = model->mpOwner;
			}
		}
	}
	else
	{
		if (world)
		{
			Filter filter;
			filter.w0 = 0;
			filter.w1 = 0;
			filter.w2 = 0;
			filter.w3 = 0;
			filter.e = 0;
			filter.type = 3;
			filter.z = 1;
			world->Raycast(start, end, hits, filter, 0.0f);
		}
		if (context == 1 || context == 2)
		{
			PickHitVector secondaryHits;
			Filter filter;
			filter.w0 = 0;
			filter.w1 = 0;
			filter.w2 = 0;
			filter.w3 = 0;
			filter.e = 0;
			filter.type = 0;
			filter.z = 1;
			mpSecondaryWorld->Raycast(start, end, secondaryHits, filter, 0.0f);
			hits.insert(hits.end(), secondaryHits.begin(), secondaryHits.end());
		}

		const u32 count = hits.size();
		if (count == 0)
			goto done;
		PickInfo info;
		info.start = start;
		info.end = end;
		info.flag = false;
		for (u32 i = 0; i < count; i++)
		{
			Model* model = hits.mpBegin[i].model;
			const float t = hits.mpBegin[i].t;
			if (!model)
				continue;
			Object* owner = model->mpOwner;
			if (!owner)
				continue;

			bool fromHitSphere = false;
			cGameData* gameData = (cGameData*)owner->Cast(kTypeGameData);
			cSpatialObject* spatial = (cSpatialObject*)owner->Cast(kTypeSpatialObject);
			void* other = owner->Cast(kType189e11f);
			cHitSphere* hitSphere = (cHitSphere*)owner->Cast(kTypeHitSphere);
			if (hitSphere && hitSphere->mpOwner)
			{
				owner = hitSphere->mpOwner;
				fromHitSphere = true;
			}
			if (spatial && !spatial->mbPickable && !other)
				continue;
			if (gameData && gameData->IsDestroyed())
				continue;
			if (IsPickBlocker(owner))
			{
				best = owner;
				break;
			}

			int priority = 10000;
			for (PickPriority* p = mPickPrioritiesBegin; p != mPickPrioritiesEnd; ++p)
			{
				if (p->mKind == 1 && fromHitSphere)
					continue;
				if (p->mKind == 2 && !fromHitSphere)
					continue;
				if (owner->Cast(p->mType))
				{
					priority = p->mPriority;
					break;
				}
			}
			if (isCreatureOrTribe && priority == 10000)
				continue;
			if (priority > bestPriority)
				continue;
			if (mpFilterPickedObjectCallback)
			{
				info.model = model;
				info.t = t;
				if (!mpFilterPickedObjectCallback(&info))
					continue;
			}

			const float distance = t * rayLength;
			bool better;
			if (isContext1 && best && gameData && bestGameData &&
				gameData->GetPickGroup() == bestGameData->GetPickGroup())
			{
				if (hitSphere)
				{
					if (!bestHitSphere)
						continue;
					better = priority < bestPriority || !best;
				}
				else if (bestHitSphere)
					better = true;
				else
					better = priority < bestPriority || !best;
			}
			else
				better = priority < bestPriority || !best;
			const bool closer = distance < bestDistance;
			if (!TestBit(model->mGroupBits, groupBit) && !(distance < maxPickDistance))
				continue;
			if (isCreatureOrTribe)
			{
				if (!better)
					continue;
			}
			else if (!better && !(priority == bestPriority && closer))
				continue;

			bestDistance = distance;
			bestPriority = priority;
			best = owner;
			bestGameData = gameData;
			bestHitSphere = hitSphere;
		}
	}

	if (best)
	{
		cSpatialObject* spatial = (cSpatialObject*)best->Cast(kTypeSpatialObject);
		if (spatial && best != mHoveredObject.get())
		{
			if (context == 1)
			{
				cLightingManager* lighting = LightingManager();
				lighting->SetRolloverLight(spatial->GetRolloverLight(0.75f, 1));
			}
			if ((unsigned)(GetCurrentGameMode() - kGameCreature) > 1)   // not creature/tribe
			{
				if (IsUIModal() || IsUIBusy() || GetSomeGameState()->IsBusy())
					goto done;
			}
			if (mpObjectRolledOverCallback)
			{
				mpObjectRolledOverCallback(spatial, true);
				if (isScenarioPlay && !spatial->IsRolloverSuppressed())
					best = mHoveredObject.get();
			}
		}
	}

done:
	if (mHoveredObject.get())
	{
		cSpatialObject* old = (cSpatialObject*)mHoveredObject.get()->Cast(kTypeSpatialObject);
		if (old && best != mHoveredObject.get() && mpObjectRolledOverCallback)
			mpObjectRolledOverCallback(old, false);
	}
	mHoveredObject = best;
	return best;
}
