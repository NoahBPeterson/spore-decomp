// Slice s01049040 -- 0x01049040, 2512 bytes: SP::cCommandTerraform::Execute (the "terraform" cheat command).
//
// One flag/option after another (each is independent, in this order):
//   -abduct        fill the player's inventory with the active planet's plant species (from the key vector at
//                  planetData+0xbc) and animal spawn positions (vector at +0xd0), 50 each, until the inventory
//                  runs out of free slots (the count comes from virtual +0x8c after topping it up to 27 via +0x94)
//   -biomecolors   toggle the biome-colour scale: swap a saved float with the one in the planet model's sub-object
//   -atmosphere / -a  and  -temperature / -t   [value [extra]]: an enum word (table 0x015b8618) sets the global
//                  scale (n * 0.1), otherwise the float is applied to the active planet (and extra to planet+0x154)
//   -water <f>     planet setter
//   -stopcheats    zero the global atmosphere/temperature scales and the pause flag
//   -plantsFlood / -plantsKill   plant manager call / terraforming manager call
//   -pause, -ariwip, -bullseye, -waterLava, -biosphere   toggle a global flag
//   -cubemap <enum> [a b]   6-way toggle switch (cases 5/6 also take two ranged ints)
//   -ufo           (in space) fly the UFO towards the city hall's position
//   -eradicate <n> <kind>   terraforming manager request, kind 1..6 (switch)
//   -freeze        planet+0x154 object call
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (the game-code modules around it).
#include "types.h"
#include <math.h>

typedef unsigned int uint32_t;

// ---------------------------------------------------------------- ArgScript
struct cIParser
{
	virtual void pv0();  virtual void pv1();  virtual void pv2();  virtual void pv3();
	virtual void pv4();  virtual void pv5();  virtual void pv6();  virtual void pv7();
	virtual void pv8();  virtual void pv9();  virtual void pv10(); virtual void pv11();
	virtual void pv12(); virtual void pv13(); virtual void pv14(); virtual void pv15();
	virtual void pv16(); virtual void pv17(); virtual void pv18(); virtual void pv19();
	virtual void pv20(); virtual void pv21(); virtual void pv22(); virtual void pv23();
	virtual void pv24(); virtual void pv25(); virtual void pv26(); virtual void pv27();
	virtual void pv28(); virtual void pv29(); virtual void pv30(); virtual void pv31();
	virtual void pv32(); virtual void pv33(); virtual void pv34(); virtual void pv35();
	virtual void pv36(); virtual void pv37();
	virtual float GetFloat(const char* text);      // +0x98
};

struct cArguments
{
	void MainArgumentsZero(int unused);                                                     // 0x00838320
	bool HasFlag(const char* flag);                                                     // 0x008380b0
	const char** OptionArguments(const char* name, int* pCount, int minCount, int maxCount);   // 0x00838130
	const char** OptionArguments(const char* name, int count);                          // 0x00838330
};

int ParseEnum(const char* text, const void* table);                                     // 0x00840bb0 (cdecl)
bool ParseEnumValue(const char* text, const void* table, int* out);                     // 0x008407c0 (cdecl)
int ParseRangedInt(cIParser* parser, const char* text, int lo, int hi);                 // 0x00840dc0 (cdecl)

extern const char kEnumNames[];       // 0x015b8618: { "...", -10 }, ... word table for atmosphere/temperature
extern const char kCubemapNames[];    // 0x015b8658

// ---------------------------------------------------------------- game objects
struct Vec3 { float x, y, z; };
struct ResourceKey { uint32_t instance, type, group; };

struct cInventoryItem
{
	virtual void pv0();
	virtual void pv1();
	virtual void Release();                  // +0x08
	uint32_t pad[3];
	int mAmount;                              // +0x10
};

struct cPlantSpecies
{
	virtual void pv0();  virtual void pv1();  virtual void pv2();  virtual void pv3();
	virtual void pv4();  virtual void pv5();  virtual void pv6();  virtual void pv7();
	virtual void pv8();
	virtual void MakeInventoryItem(cInventoryItem** out);      // +0x24
};

struct cPlayerInventory
{
	virtual void pv0();  virtual void pv1();  virtual void pv2();  virtual void pv3();
	virtual void pv4();  virtual void pv5();  virtual void pv6();  virtual void pv7();
	virtual void pv8();  virtual void pv9();  virtual void pv10(); virtual void pv11();
	virtual void pv12(); virtual void pv13(); virtual void pv14(); virtual void pv15();
	virtual void pv16(); virtual void pv17(); virtual void pv18(); virtual void pv19();
	virtual void pv20(); virtual void pv21(); virtual void pv22(); virtual void pv23();
	virtual void pv24(); virtual void pv25(); virtual void pv26(); virtual void pv27();
	virtual void pv28(); virtual void pv29(); virtual void pv30(); virtual void pv31();
	virtual void AddItem(cInventoryItem* item, int a, int b);  // +0x80
	virtual void pv33();
	virtual int GetSlotCount();                                // +0x88
	virtual int GetFreeSlots();                                // +0x8c
	virtual void pv36();
	virtual void SetSlotCount(int n);                          // +0x94
};

struct cPlantSpeciesManager { cPlantSpecies* GetSpeciesFromID(const ResourceKey* key); };            // 0x00b90410
struct cAnimalSpeciesManager
{
	void MakeInventoryItemFromSpecies(cInventoryItem** out, const Vec3* pos, int amount, int flags);  // 0x00ac0cb0
};

struct cPlanetData
{
	uint32_t pad0[0xbc / 4];
	ResourceKey* mPlantKeysBegin;     // +0xbc
	ResourceKey* mPlantKeysEnd;       // +0xc0
	uint32_t pad1[(0xd0 - 0xc4) / 4];
	Vec3* mAnimalPosBegin;            // +0xd0
	Vec3* mAnimalPosEnd;              // +0xd4
};

struct cPlanetExtra
{
	uint32_t pad[0x1fd4 / 4];
	float mAtmosphere;                // +0x1fd4
	float mTemperature;               // +0x1fd8
	uint32_t pad2[(0x2030 - 0x1fdc) / 4];
	void SetFrozen(bool b);           // 0x00c7e2f0  (stores at +0x2030)
};

struct cPlanet
{
	uint32_t pad0[0x13c / 4];
	cPlanetData* mData;               // +0x13c
	void SetAtmosphere(float f);      // 0x00c70a00
	void SetTemperature(float f);     // 0x00c70a50
	void SetWater(float f);           // 0x00c71da0
	cPlanetExtra* GetExtra();         // 0x008414c0  (planet+0x154)
};

struct cBiomeSub
{
	float GetA();                     // 0x00fb7ba0
	float GetC();                     // 0x0097ef00
	void Set(float a, float b);       // 0x00fbd880
};
struct cBiomeHolder { virtual void pv0(); virtual void pv1(); virtual void pv2(); virtual void pv3();
                      virtual cBiomeSub* GetSub(); };   // +0x10
struct cPlanetModel { uint32_t pad[0x24 / 4]; cBiomeHolder* mHolder; };

struct cSpaceGame { cPlayerInventory* GetPlayerInventory(); cSpaceGame* GetAvatar(); };    // 0x00a1ad60 / 0x00b1fdb0
struct cAvatar { void Refresh(); };                                                          // 0x00ff74f0

struct cUfoState
{
	void SetTarget(const Vec3* v, unsigned int arg);   // 0x00c3aa40
	void SetSpeed(float f);                           // 0x00c3daa0
	void SetFlag(bool b);                             // 0x00c37130
};
struct cUfoSim { cUfoState* GetPlayerInventory(); };  // 0x00a1ad60

struct cHallSub
{
	virtual void pv0();  virtual void pv1();  virtual void pv2();  virtual void pv3();
	virtual void pv4();  virtual void pv5();  virtual void pv6();  virtual void pv7();
	virtual void pv8();  virtual void pv9();  virtual void pv10();
	virtual const Vec3* GetPosition();       // +0x2c
	virtual unsigned int GetSomething();     // +0x30
};
struct cCityHall { uint32_t pad[0x34 / 4]; cHallSub sub; };          // sub-object at +0x34
struct cCity
{
	cCityHall* GetCityHall();         // 0x00bd9b40
};
struct cNounManager
{
	cCity* GetCity();                 // 0x00b25c30
};

struct cTerraformMgr
{
	void Plants(bool b);                                                   // 0x00b2bf10 (on the b3d3b0 object)
	void Kill(const Vec3* v, float radius);                                // 0x00bbdbf0 (on the b3d430 object)
	Vec3* Eradicate123(Vec3* out, int n, uint32_t id, int z);              // 0x00bbc870
	Vec3* Eradicate45(Vec3* out, int n, int which, int z);                 // 0x00bbc950
	Vec3* Eradicate6(Vec3* out, int n, int z);                             // 0x00bbca30
	void Apply123(const Vec3* v, int z);                                   // 0x00bbc540
	void Apply456(const Vec3* v, int z);                                   // 0x00bbcb10
	void Finish1(int z);                                                   // 0x00bbf2b0
	void Finish2(int z);                                                   // 0x00bbe740
};
struct cPlantFloodMgr { void Flood(bool b); };                             // 0x00b2bf10
struct cCubemapState { uint8_t pad[5]; uint8_t mEnabled; };               // 0x00f48a60 object, +5

// singletons / getters (each `mov eax,[g]; ret` in the original)
cPlantSpeciesManager* PlantSpeciesManager();       // 0x00b3d420
cAnimalSpeciesManager* AnimalSpeciesManager();     // 0x00b3d450
cPlanetModel* PlanetModel();                       // 0x00b3d350
cPlantFloodMgr* PlantFloodManager();               // 0x00b3d3b0
cTerraformMgr* TerraformingManager();              // 0x00b3d430
cCubemapState* CubemapState();                     // 0x00f48a60
cNounManager* NounManager();                       // 0x00b3d300
cUfoSim* GetUFOSimulator();                        // 0x00ffbe50
cSpaceGame* SpaceGameGet();                        // 0x01002bd0
int GetUniverseContext();                          // 0x01021080
cPlanet* GetActivePlanet();                        // 0x01021260

// ---------------------------------------------------------------- globals
extern bool gBiomeColorsOn;       // 0x016e06cc
extern float gSavedBiomeValue;    // 0x016e06d0
extern float gAtmosphereScale;    // 0x016e06d4
extern float gTemperatureScale;   // 0x016e06d8
extern bool gPaused;              // 0x016e06dc
extern bool gAriwip;              // 0x016e06dd
extern bool gCubemap2;            // 0x016e06de
extern bool gCubemap1;            // 0x016e06df
extern bool gCubemap3;            // 0x016e06e0
extern bool gCubemap4;            // 0x016e06e1
extern bool gCubemap5;            // 0x016e06e2
extern bool gCubemap6;            // 0x016e06e3
extern int gCubemapA;             // 0x016e06e4
extern int gCubemapB;             // 0x016e06e8
extern bool gBullseye;            // 0x016e06ec
extern bool gWaterLava;           // 0x016e06ed
extern bool gBiosphere;           // 0x016e06ee

extern const float kBiomeScaleValue;   // 0x0149a6c4 = 0.984375

struct cCommandTerraform
{
	virtual void pv0();
	cIParser* mParser;               // +4
	void Execute(cArguments* args);
};

// @ 0x01049040
void cCommandTerraform::Execute(cArguments* args)
{
	args->MainArgumentsZero(0);

	if (args->HasFlag("abduct"))
	{
		cPlanet* planet = GetActivePlanet();
		if (planet)
		{
			cPlanetData* data = planet->mData;
			cPlayerInventory* inv = SpaceGameGet()->GetPlayerInventory();
			int slots = inv->GetSlotCount();
			if (slots < 27)
				inv->SetSlotCount(27 - slots);
			int remaining = inv->GetFreeSlots();

			int n = (int)(data->mPlantKeysEnd - data->mPlantKeysBegin);
			for (int i = 0; i < n; ++i)
			{
				cPlantSpecies* species = PlantSpeciesManager()->GetSpeciesFromID(&data->mPlantKeysBegin[i]);
				if (species)
				{
					cInventoryItem* item = 0;
					species->MakeInventoryItem(&item);
					item->mAmount = 0x32;
					if (remaining-- > 0)
						inv->AddItem(item, 0, 1);
					if (item)
						item->Release();
				}
			}

			int m = (int)(data->mAnimalPosEnd - data->mAnimalPosBegin);
			for (int j = 0; j < m; ++j)
			{
				Vec3 pos = data->mAnimalPosBegin[j];
				cInventoryItem* item = 0;
				AnimalSpeciesManager()->MakeInventoryItemFromSpecies(&item, &pos, 0x32, 0);
				if (item)
				{
					if (remaining-- > 0)
						inv->AddItem(item, 0, 1);
					if (item)
						item->Release();
				}
			}
		}
	}

	if (args->HasFlag("biomecolors"))
	{
		cPlanetModel* model = PlanetModel();
		cBiomeHolder* holder = model->mHolder;
		cBiomeSub* sub = holder->GetSub();
		if (gBiomeColorsOn)
		{
			sub->Set(gSavedBiomeValue, sub->GetA());
			gBiomeColorsOn = false;
		}
		else
		{
			gSavedBiomeValue = sub->GetC();
			sub->Set(kBiomeScaleValue, sub->GetA());
			gBiomeColorsOn = true;
		}
	}

	int count;
	const char** opt = args->OptionArguments("atmosphere", &count, 1, 2);
	if (opt || (opt = args->OptionArguments("a", &count, 1, 2)))
	{
		int value;
		if (ParseEnumValue(opt[0], kEnumNames, &value))
			gAtmosphereScale = (float)value * 0.1f;
		else
		{
			float f = mParser->GetFloat(opt[0]);
			cPlanet* planet = GetActivePlanet();
			if (planet)
			{
				planet->SetAtmosphere(f);
				if (count > 1)
				{
					float extra = mParser->GetFloat(opt[1]);
					cPlanetExtra* ex = planet->GetExtra();
					if (ex)
						ex->mAtmosphere = extra;
				}
			}
		}
	}

	opt = args->OptionArguments("temperature", &count, 1, 2);
	if (opt || (opt = args->OptionArguments("t", &count, 1, 2)))
	{
		int value;
		if (ParseEnumValue(opt[0], kEnumNames, &value))
			gTemperatureScale = (float)value * 0.1f;
		else
		{
			float f = mParser->GetFloat(opt[0]);
			cPlanet* planet = GetActivePlanet();
			if (planet)
			{
				planet->SetTemperature(f);
				if (count > 1)
				{
					float extra = mParser->GetFloat(opt[1]);
					cPlanetExtra* ex = planet->GetExtra();
					if (ex)
						ex->mTemperature = extra;
				}
			}
		}
	}

	opt = args->OptionArguments("water", 1);
	if (opt)
	{
		float f = mParser->GetFloat(opt[0]);
		cPlanet* planet = GetActivePlanet();
		if (planet)
			planet->SetWater(f);
	}

	if (args->HasFlag("stopcheats"))
	{
		gAtmosphereScale = 0.0f;
		gTemperatureScale = 0.0f;
		gPaused = false;
	}

	if (args->HasFlag("plantsFlood"))
		PlantFloodManager()->Flood(false);

	if (args->HasFlag("plantsKill"))
	{
		Vec3 zero;
		zero.x = 0.0f;
		zero.y = 0.0f;
		zero.z = 0.0f;
		TerraformingManager()->Kill(&zero, 1000.0f);
	}

	if (args->HasFlag("pause"))
	{
		gPaused = !gPaused;
		if (gPaused)
		{
			gAtmosphereScale = 0.0f;
			gTemperatureScale = 0.0f;
		}
	}

	if (args->HasFlag("ariwip"))
		gAriwip = !gAriwip;

	opt = args->OptionArguments("cubemap", &count, 1, 3);
	if (opt)
	{
		switch (ParseEnum(opt[0], kCubemapNames))
		{
		case 1:
			{
				bool enabled = !gCubemap1;
				gCubemap1 = enabled;
				CubemapState()->mEnabled = enabled;
			}
			break;
		case 2:
			gCubemap2 = !gCubemap2;
			break;
		case 3:
			gCubemap3 = !gCubemap3;
			break;
		case 4:
			gCubemap4 = !gCubemap4;
			break;
		case 5:
			gCubemap5 = !gCubemap5;
			gCubemap6 = false;
			if (count > 1)
			{
				gCubemapA = ParseRangedInt(mParser, opt[1], -1, 2);
				gCubemapB = ParseRangedInt(mParser, opt[2], -1, 2);
			}
			else
			{
				gCubemapB = -1;
				gCubemapA = -1;
			}
			break;
		case 6:
			gCubemap6 = !gCubemap6;
			gCubemap5 = false;
			if (count > 1)
			{
				gCubemapA = ParseRangedInt(mParser, opt[1], -1, 2);
				gCubemapB = ParseRangedInt(mParser, opt[2], -1, 2);
			}
			else
			{
				gCubemapB = -1;
				gCubemapA = -1;
			}
			break;
		}
	}

	if (args->HasFlag("ufo") && GetUniverseContext() == 0)
	{
		cCity* city = NounManager()->GetCity();
		if (city)
		{
			cCityHall* hall = city->GetCityHall();
			if (hall && SpaceGameGet())
			{
				cHallSub* sub = &hall->sub;
				const Vec3* p = sub->GetPosition();
				float inv = (float)(1.0 / sqrt((double)(((p->x * p->x + p->y * p->y) + p->z * p->z) + 1e-8f)));
				Vec3 delta;
				delta.x = (p->x * inv) * 35.0f;
				delta.y = (p->y * inv) * 35.0f;
				delta.z = (p->z * inv) * 35.0f;
				const Vec3* q = sub->GetPosition();
				Vec3 target;
				target.x = q->x + delta.x;
				target.y = q->y + delta.y;
				target.z = q->z + delta.z;
				cUfoState* ufo = GetUFOSimulator()->GetPlayerInventory();
				if (ufo)
				{
					ufo->SetTarget(&target, sub->GetSomething());
					ufo->SetSpeed((float)sqrt((double)((target.z * target.z + target.y * target.y) + target.x * target.x)));
					ufo->SetFlag(false);
				}
				if (SpaceGameGet()->GetAvatar())
					((cAvatar*)SpaceGameGet()->GetAvatar())->Refresh();
			}
		}
	}

	if (args->HasFlag("bullseye"))
		gBullseye = !gBullseye;
	if (args->HasFlag("waterLava"))
		gWaterLava = !gWaterLava;
	if (args->HasFlag("biosphere"))
		gBiosphere = !gBiosphere;

	opt = args->OptionArguments("eradicate", 2);
	if (opt)
	{
		int n = ParseRangedInt(mParser, opt[0], 1, 3);
		int kind = ParseRangedInt(mParser, opt[1], 1, 6);
		union { Vec3 v; uint32_t iv[3]; } vu;
		Vec3& v = vu.v;
		vu.iv[0] = 0;
		vu.iv[1] = 0;
		vu.iv[2] = 0;
		cTerraformMgr* mgr = TerraformingManager();
		if (mgr)
		{
			Vec3 t1, t2, t3, t4, t5, t6;
			Vec3* r;
			switch (kind)
			{
			case 1:
				r = mgr->Eradicate123(&t1, n, 0x6d60a1cc, 0);
				goto apply123;
			case 2:
				r = mgr->Eradicate123(&t2, n, 0x029c388a, 0);
				goto apply123;
			case 3:
				r = mgr->Eradicate123(&t3, n, 0x3a8be428, 0);
			apply123:
				v = *r;
				mgr->Apply123(&v, 0);
				break;
			case 4:
				r = mgr->Eradicate45(&t4, n, 0, 0);
				goto apply456;
			case 5:
				r = mgr->Eradicate45(&t5, n, 1, 0);
				goto apply456;
			case 6:
				r = mgr->Eradicate6(&t6, n, 0);
			apply456:
				v = *r;
				mgr->Apply456(&v, 0);
				break;
			default:
				break;
			}
			mgr->Finish1(0);
			mgr->Finish2(0);
		}
	}

	if (args->HasFlag("freeze"))
	{
		cPlanet* planet = GetActivePlanet();
		if (planet)
		{
			cPlanetExtra* ex = planet->GetExtra();
			if (ex)
				ex->SetFrozen(false);
		}
	}
}

// =================================================================================================
// cTerraformTuning: the terraforming tunables read out of a property list (keys hashed by
// FNV-1 of "cTerraformTuning.xml" style names).  The four accessors return 0 when the property
// list or the key is missing; the T3 colony count is floored at 20.
//
// cSpaceTokenTranslator: the Simulator token translator of the space stage (vtable 0x0149a724,
// six slots: deleting dtor, three overrides, TranslateToken at +0x10, one more override).  It
// keeps four string vectors (tech level / terraforming level / animal type / plant type names,
// 7/4/4/3 entries) plus two format strings, all loaded from the "ui_space" text table.
// =================================================================================================

// ---------------------------------------------------------------- property objects
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
	virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14();
	virtual void v18(); virtual void v1c(); virtual void v20();
	virtual bool GetProperty(uint32_t hash, Property** out);   // +0x24
};

namespace EA {
template <typename T>
class AutoRefCount
{
public:
	T* mpObject;
	AutoRefCount() : mpObject(0) {}
	~AutoRefCount() { if (mpObject) mpObject->Release(); }
	T* operator->() const { return mpObject; }
	operator T*() const { return mpObject; }
	AutoRefCount& operator=(T* p)
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
};
}  // namespace EA

class cPropertyManager
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28();
	virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID,
	                             EA::AutoRefCount<cPropertyList>& out);   // +0x2c
};
cPropertyManager* PropertyManager();                          // 0x0067de30

struct cTerraformTuning
{
	EA::AutoRefCount<cPropertyList> mPropList;                 // +0x00
	void Init();                                               // 0x01049a20
	int GetMaxBuildingsForT1Colony();                          // 0x01049e70
	int GetMaxBuildingsForT2Colony();                          // 0x01049eb0
	int GetMaxBuildingsForT3Colony();                          // 0x01049ef0
};

template <typename T> inline const T& MinInt(const T& a, const T& b) { return (b < a) ? b : a; }

// @ 0x01049a20
void cTerraformTuning::Init()
{
	PropertyManager()->GetPropertyList(0xa6d1bc70, 0x2ae0c7e, mPropList = 0);
}

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

// ---------------------------------------------------------------- strings used by the translator
struct WString
{
	wchar_t* mpBegin;
	wchar_t* mpEnd;
	wchar_t* mpCapacity;
	WString& Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
	WString& operator=(const WString& other);                     // 0x0057cb60
};

extern const wchar_t kEmptyString16[];                          // 0x013ec468 (L"")

struct cString
{
	uint32_t data[5];
	cString();                                                  // 0x006b5060
	~cString();                                                 // 0x006b5240
	bool Load(uint32_t tableID, uint32_t instanceID, int flags);// 0x006b54b0
	const wchar_t* GetText();                                   // 0x006b55c0
};

void operator delete(void* p);                                  // 0x00f47380

// 0x14-byte string array (stride 0x14 per element); only the three container pointers are
// initialised by the constructor, the trailing two words are set by whoever resizes it.
struct cStringVector
{
	cString* mpBegin;                                           // +0x00
	cString* mpEnd;                                             // +0x04
	cString* mpCapacity;                                        // +0x08
	uint32_t mField0C;                                          // +0x0c
	uint32_t mField10;                                          // +0x10

	cStringVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
	~cStringVector()
	{
		cString* end = mpEnd;
		for (cString* p = mpBegin; p < end; ++p)
			p->~cString();
		if (mpBegin && ((int*)mpBegin)[-1] != 0)
			operator delete(mpBegin);
	}
	int Size() const { return (int)(mpEnd - mpBegin); }
	void Index(uint32_t count);                                 // 0x00e2ca70
};

uint32_t FNVHash(const char* text, uint32_t seed, int mode);    // 0x00932e80

// text-table instance ids (the "ui_space" table)
extern const uint32_t kTechLevelStringIds[];                    // 0x015b86d4, 7 entries
extern const uint32_t kTerraformingLevelStringIds[];            // 0x015b86f0, 4 entries
extern const uint32_t kAnimalTypeStringIds[];                   // 0x015b8700, 4 entries
extern const uint32_t kPlantTypeStringIds[];                    // 0x015b8710, 3 entries
extern const uint32_t kMoneyFormatInstanceId;                   // 0x015b871c
extern const uint32_t kUiSpaceNameInstanceId;                   // 0x015b8720

// ---------------------------------------------------------------- game nouns
struct cKey3
{
	uint32_t m0, m4, m8;
};

struct cGameNounManager
{
	void* GetAvatar();                                          // 0x00b1fdb0
};

// The active planet record the translator keeps at +0x0c.
struct cPlanetRecord
{
	int GetCategory();                                          // 0x00b8dab0
	cGameNounManager* GetNounManager();                         // 0x00b8de30
	cKey3* GetBannerKey();                                      // 0x00b8e090
};

struct cStarManager
{
	void* GetEmpireByID(int id);                                // 0x00ba9370
};
cStarManager* StarManager();                                    // 0x00b3d2a0

struct cCivData
{
	WString* GetCities();                                       // 0x005c65e0 (returns &this->mCities)
};

struct cSpeciesProfile
{
	void GetUiName(WString* out);                               // 0x004da330
};
struct cSPEditorSpeciesManager
{
	cSpeciesProfile* GetProfile(cKey3* key);                    // 0x004df550
};
cSPEditorSpeciesManager* GetEditorSpeciesManager();             // 0x00401090

// ---------------------------------------------------------------- the translator object
namespace Simulator {
class cCivTokenTranslator
{
public:
	cCivTokenTranslator();                                      // 0x00b32470
	virtual ~cCivTokenTranslator();                             // 0x00b32490
	virtual void v04();                                         // slot 1
	virtual void v08();                                         // slot 2
	virtual void v0c();                                         // slot 3
	virtual bool TranslateToken(const wchar_t* token, WString* out);   // slot 4
	uint32_t mField04;                                          // +0x04
	uint32_t mField08;                                          // +0x08
};
}  // namespace Simulator

class cSpaceTokenTranslator : public Simulator::cCivTokenTranslator
{
public:
	virtual void v14();                                         // slot 5 (0x010829f0)

	void* mpPlanet;                                             // +0x0c
	void* mpStar;                                               // +0x10
	void* mpItem;                                               // +0x14
	void* mpMission;                                            // +0x18
	void* mpEmpire;                                             // +0x1c
	void* mpEmpire2;                                            // +0x20
	void* mpSpeciesProfile;                                     // +0x24
	void* mpBuilding;                                           // +0x28
	void* mpVehicle;                                            // +0x2c
	void* mpUFO;                                                // +0x30
	void* mpGenericName;                                        // +0x34
	int mCount;                                                 // +0x38
	int mField3C;                                               // +0x3c
	float mField40;                                             // +0x40
	uint32_t mField44;                                          // +0x44
	int mField48;                                               // +0x48
	cStringVector mTechLevelString;                             // +0x4c
	cStringVector mTerraformingLevelString;                     // +0x60
	cStringVector mAnimalTypeString;                            // +0x74
	cStringVector mPlantTypeString;                             // +0x88
	cString mMoneyFormatString;                                 // +0x9c
	cString mUiSpaceName;                                       // +0xb0

	cSpaceTokenTranslator();                                    // 0x0104a020
	virtual ~cSpaceTokenTranslator();                           // 0x0104a210

	const wchar_t* FUN_01049f50(int index);                     // 0x01049f50
	void FUN_01049f90(WString* out);                            // 0x01049f90
};

// @ 0x01049f50
const wchar_t* cSpaceTokenTranslator::FUN_01049f50(int index)
{
	if (index < mTerraformingLevelString.Size())
		return mTerraformingLevelString.mpBegin[index].GetText();
	return kEmptyString16;
}

// @ 0x01049f90
void cSpaceTokenTranslator::FUN_01049f90(WString* out)
{
	out->Assign(kEmptyString16, kEmptyString16);
	if (mpPlanet)
	{
		if (((cPlanetRecord*)mpPlanet)->GetCategory() > 1)
		{
			if (((cPlanetRecord*)mpPlanet)->GetCategory() == 5)
			{
				cCivData* civ = (cCivData*)StarManager()->GetEmpireByID(
				                    (int)((cPlanetRecord*)mpPlanet)->GetNounManager()->GetAvatar());
				if (civ)
					*out = *civ->GetCities();
			}
			else
			{
				cSpeciesProfile* profile =
				    GetEditorSpeciesManager()->GetProfile(((cPlanetRecord*)mpPlanet)->GetBannerKey());
				if (profile)
					profile->GetUiName(out);
			}
		}
	}
}

// @ 0x0104a020
cSpaceTokenTranslator::cSpaceTokenTranslator()
	: mpPlanet(0), mpStar(0), mpItem(0), mpMission(0), mpEmpire(0),
	  mpSpeciesProfile(0), mpBuilding(0), mpVehicle(0), mpUFO(0), mpGenericName(0),
	  mField3C(0), mField40(0.0f), mField48(0)
{
	mTechLevelString.Index(7);
	for (int i = 0; i < 7; ++i)
		mTechLevelString.mpBegin[i].Load(0x2db6dad3, kTechLevelStringIds[i], 0);

	mTerraformingLevelString.Index(4);
	for (int i = 0; i < mTerraformingLevelString.Size(); ++i)
		mTerraformingLevelString.mpBegin[i].Load(0x2db6dad3, kTerraformingLevelStringIds[i], 0);

	mAnimalTypeString.Index(4);
	for (uint32_t i = 0; i < 4; ++i)
		mAnimalTypeString.mpBegin[i].Load(0x2db6dad3, kAnimalTypeStringIds[i], 0);

	mPlantTypeString.Index(3);
	for (uint32_t i = 0; i < 3; ++i)
		mPlantTypeString.mpBegin[i].Load(0x2db6dad3, kPlantTypeStringIds[i], 0);

	uint32_t tableId = FNVHash("ui_space", 0x811c9dc5u, 1);
	mMoneyFormatString.Load(tableId, kMoneyFormatInstanceId, 0);
	mUiSpaceName.Load(0x2db6dad3, kUiSpaceNameInstanceId, 0);
}

// @ 0x0104a210
cSpaceTokenTranslator::~cSpaceTokenTranslator()
{
}
