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
