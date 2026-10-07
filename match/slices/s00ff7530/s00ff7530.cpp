// Slice s00ff7530: SP::cSPSimPlanetHighLOD::UpdateGenesisDevice (0x00FF7530, 2938 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE math, x87 for the uint64 -> float conversions and the
// double-precision distance, __asm Clamp/RoundToInt helpers like the neighbouring cSPSimPlanetHighLOD code).
//
// Name from symbols/pdb_candidates.json (dev 0x0089cf80, caller-single: the only caller is
// cSPSimPlanetHighLOD::OnTick at 0x00ffbccc, guarded by mGenesisDeviceOn). Members follow the dev PDB
// layout of SP::cSPSimPlanetHighLOD (mGenesisDeviceOn, mGenesisDevicePos, mGenesisTScore, mGenesisTimer,
// mGenesisTimeT1..T3, mGenesisCells) at their retail offsets (+4 / +8).
//
// What it does: moves the genesis-device spot (planet record +0xb0/+0xb4, in [0,1] map space) toward the
// map centre at a speed chosen so it reaches the next terraform radius in time, asks the terraforming
// manager for the planet's new terraform level, and on every level-up records the level's start time,
// fires a relationship event with a foreign planet owner and seeds the new level's plants/animals at the
// device position. While the device runs it then ramps the plant/animal density of the genesis cells
// (three bands for terraform levels 3/2/1 that grow with time) and switches the device off at the end.
// Callees that only have FUN_ names are named after their use here (descriptive, not PDB).
#include "types.h"
#include <math.h>

#pragma warning(disable : 4035)

// float->int with the current MXCSR rounding (asm helper in the original).
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

__forceinline float Clamp(float value, float minValue, float maxValue)
{
	__asm {
		movss xmm0, value
		maxss xmm0, minValue
		minss xmm0, maxValue
		movss value, xmm0
	}
	return value;
}

// eastl::max (reference form)
template <typename T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

struct Vector2 {
	float x, y;
	Vector2() {}
	Vector2(float ax, float ay) : x(ax), y(ay) {}
};

struct Vector3 {
	float x, y, z;
};

struct ResourceKey {
	uint32_t instanceID;
	uint32_t typeID;
	uint32_t groupID;
};
inline bool operator==(const ResourceKey& a, const ResourceKey& b)
{
	return a.instanceID == b.instanceID && a.typeID == b.typeID && a.groupID == b.groupID;
}
inline bool operator!=(const ResourceKey& a, const ResourceKey& b) { return !(a == b); }

extern const ResourceKey kNullKey;               // 0x016DB434 (ResourceKey with all three ids "none")

void operator delete[](void* p);                 // 0x00F47380

// EA allocator-backed vector storage: delete[] only when the block header before the data is nonzero.
template <typename T>
struct SpVector {
	T* mpBegin;
	T* mpEnd;
	T* mpCapacity;
	SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
	~SpVector()
	{
		if (mpBegin && ((int*)mpBegin)[-1])
			operator delete[](mpBegin);
	}
	int size() const { return (int)(mpEnd - mpBegin); }
	T& operator[](int i) { return mpBegin[i]; }
};

// fixed_vector<T, 5> on the stack (buffer of 0x14 bytes preceded by a zero block header).
struct FixedVector5 {
	uint32_t* mpBegin;
	uint32_t* mpEnd;
	uint32_t* mpCapacity;
	uint32_t mPad[2];
	int mHeader;
	uint32_t mBuffer[5];
	FixedVector5() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + 5), mHeader(0) {}
	~FixedVector5()
	{
		if (mpBegin && ((int*)mpBegin)[-1])
			operator delete[](mpBegin);
	}
};

namespace SP {

struct cCubeSimIt {                              // 16 bytes
	uint32_t mPad[3];
	int mCellIndex;                              // +0xc
};

// Planet record data behind cPlanet+0x13c.
struct cPlanetData {
	uint32_t mPad[0xb0 / 4];
	float mGenesisU;                             // +0xb0
	float mGenesisV;                             // +0xb4
};

struct cGenesisSeeder {                          // cSimPlanetLowLOD + 0x50
	void Seed(const Vector3* pos, SpVector<cCubeSimIt>* cells, int flag);                     // 0x00C805B0
};

struct cSimPlanetLowLOD {
	uint32_t mPad[0x50 / 4];
	cGenesisSeeder mSeeder;                      // +0x50
	void SetSimPlantAt(const ResourceKey* species, const Vector3* pos, int flag);              // 0x00C81AB0
	void SetSimAnimalAt(const ResourceKey* species, const Vector3* pos, int flag);             // 0x00C82400
	void SetPlantDensity(int cell, const ResourceKey* species, int density, int flag);        // 0x00C81890
	void SetAnimalDensity(int cell, const ResourceKey* species, int density, int flag);       // 0x00C821B0
};

struct cPlanet {
	uint32_t mPad[0x13c / 4];
	cPlanetData* mpData;                         // +0x13c
	cSimPlanetLowLOD* GetSimPlanetLowLOD();      // 0x008414C0
	bool HasPlantSpecies(const ResourceKey& species);    // 0x00C70D40
	bool HasAnimalSpecies(const ResourceKey& species);   // 0x00C70D10
};

struct cPlanetRecord {
	int GetKind();                               // 0x00B8DAB0 (compared with 5)
};

struct cEmpireLookup {                           // returned by 0x01021240
	int GetOwnerEmpireID();                      // 0x00B1FDB0
};

struct cSPLivingUniverse {
	static cPlanet* GetActivePlanet();           // 0x01021260
	static cPlanetRecord* GetActivePlanetRecord();   // 0x010212A0
	static int GetPlayerEmpireID();              // 0x01021090
};
cEmpireLookup* GetEmpireLookup();                // 0x01021240

struct cRelationshipManager {
	float RecordEvent(int empireA, int empireB, uint32_t eventID, float scale);              // 0x00D06240
};
cRelationshipManager* RelationshipManager();     // 0x00B3D2C0

struct cTerraformingManager {
	void SetGenesisPosition(cPlanet* planet, Vector2 pos, int flag);                          // 0x00BBCF00
	int GetTerraformLevel(cPlanetData* data);                                                 // 0x00BBC670
	ResourceKey GetPlantSpecies(int level, uint32_t plantType, cPlanetData* data);           // 0x00BBC870
	ResourceKey GetAnimalSpecies(int level, int index, cPlanetData* data);                   // 0x00BBC950
	ResourceKey GetTopAnimalSpecies(int level, cPlanetData* data);                           // 0x00BBCA30
};
cTerraformingManager* TerraformingManager();     // 0x00B3D430

struct cTerrainSphere {
	void Refresh();                              // 0x00C75570
};
struct cNounManager {
	cTerrainSphere* GetCurrentTerrainSphere();   // 0x00F67D90
};
cNounManager* NounManager();                     // 0x00B3D300

struct cCreatureLookup {
	char* FindByID(uint32_t id);                 // 0x00AC10A0 (species key at +0x504)
};
cCreatureLookup* CreatureLookup();               // 0x00B3D450

struct cPlanetUpdater {
	void Update();                               // 0x00B2BBE0
	void Invalidate(int flags);                  // 0x00B2A750
};
cPlanetUpdater* PlanetUpdater();                 // 0x00B3D3B0

void GetPlantSpeciesList(uint32_t plantType, SpVector<ResourceKey>* out, int count);        // 0x00B90560 (cdecl)
float GetTerraformRadius(int level);             // 0x00FC1FA0

extern const float kGenesisStageDuration;        // 0x015B621C (8.5)
extern const float kGenesisStartTime;            // 0x015B6218 (14.0)
extern const float kGenesisMinEndTime;           // 0x015B6214 (39.0)

struct cSPTimer {
	uint32_t mData[8];
	uint64_t GetElapsedTime();                   // 0x00BC3190
};

class cSPSimPlanetHighLOD {
public:
	uint32_t mPad000[0x158 / 4];
	bool mGenesisDeviceOn;                       // +0x158
	Vector3 mGenesisDevicePos;                   // +0x15c
	int mGenesisTScore;                          // +0x168
	uint32_t mPad16c;
	cSPTimer mGenesisTimer;                      // +0x170
	float mGenesisTimeT1;                        // +0x190
	float mGenesisTimeT2;                        // +0x194
	float mGenesisTimeT3;                        // +0x198
	SpVector<cCubeSimIt> mGenesisCells;          // +0x19c

	void UpdateGenesisDevice(uint64_t deltaTime);
};

// @ 0x00FF7530
void cSPSimPlanetHighLOD::UpdateGenesisDevice(uint64_t deltaTime)
{
	cPlanet* planet = cSPLivingUniverse::GetActivePlanet();
	cPlanetData* data = planet->mpData;
	cSimPlanetLowLOD* lowLOD = planet->GetSimPlanetLowLOD();
	const float time = (float)mGenesisTimer.GetElapsedTime() * 0.001f;

	// move the device toward the map centre
	const float u = data->mGenesisU;
	const float v = data->mGenesisV;
	Vector2 dir(0.5f - u, 0.5f - v);
	float speed = 0.015f;
	const double dx = dir.x;
	const double dy = dir.y;
	const float dist = (float)sqrt(dx * dx + dy * dy);
	if (mGenesisTScore < 3)
	{
		const float remaining = dist - GetTerraformRadius(mGenesisTScore + 1);
		const float timeLeft = (float)mGenesisTScore * kGenesisStageDuration + kGenesisStartTime - time;
		if (remaining > 0.0f && timeLeft > 0.0f)
			speed = remaining / timeLeft;
	}
	const float step = (float)deltaTime * speed * 0.001f;
	if (dist > step)
	{
		const float s = step / dist;
		dir.x = dir.x * s;
		dir.y = dir.y * s;
	}

	cTerraformingManager* tm = TerraformingManager();
	tm->SetGenesisPosition(planet, Vector2(dir.x + u, dir.y + v), 0);
	const int level = tm->GetTerraformLevel(data);

	uint32_t plantTypes[3];
	plantTypes[0] = 0x6d60a1cc;
	plantTypes[1] = 0x029c388a;
	plantTypes[2] = 0x3a8be428;

	bool seed;
	if (level > mGenesisTScore)
	{
		while (mGenesisTScore < level)
		{
			++mGenesisTScore;
			switch (mGenesisTScore)
			{
			case 1: mGenesisTimeT1 = time; break;
			case 2: mGenesisTimeT2 = time; break;
			case 3: mGenesisTimeT3 = time; break;
			}
			if (cSPLivingUniverse::GetActivePlanetRecord()->GetKind() == 5)
			{
				const int owner = GetEmpireLookup()->GetOwnerEmpireID();
				if (owner != cSPLivingUniverse::GetPlayerEmpireID())
					RelationshipManager()->RecordEvent(owner, cSPLivingUniverse::GetPlayerEmpireID(), 0x526e535, 1.0f);
			}
		}
		lowLOD->mSeeder.Seed(&mGenesisDevicePos, &mGenesisCells, 1);
		seed = true;
	}
	else
	{
		seed = (level == 3 && time > kGenesisStartTime - 1.0f);
	}

	if (seed)
	{
		for (int stage = 1; stage <= level; ++stage)
		{
			// one plant of each type, for the types this level has none of yet
			for (int k = 0; k < 3; ++k)
			{
				const uint32_t plantType = plantTypes[k];
				ResourceKey current = tm->GetPlantSpecies(stage, plantType, data);
				if (current == kNullKey)
				{
					SpVector<ResourceKey> candidates;
					GetPlantSpeciesList(plantType, &candidates, 3);
					ResourceKey pick = kNullKey;
					for (int i = 0; i < 3; ++i)
					{
						ResourceKey species = candidates[i];
						if (!planet->HasPlantSpecies(species))
						{
							pick = species;
							break;
						}
					}
					lowLOD->SetSimPlantAt(&pick, &mGenesisDevicePos, 0);
				}
			}

			// the level's animals (two herbivore slots and the top one)
			for (int k = 0; k < 3; ++k)
			{
				const bool top = (k == 2);
				ResourceKey topKey, key;
				const ResourceKey* current;
				if (top)
				{
					topKey = tm->GetTopAnimalSpecies(stage, data);
					current = &topKey;
				}
				else
				{
					key = tm->GetAnimalSpecies(stage, k, data);
					current = &key;
				}
				if (*current == kNullKey)
				{
					ResourceKey pick = kNullKey;
					if (NounManager()->GetCurrentTerrainSphere())
						NounManager()->GetCurrentTerrainSphere()->Refresh();
					FixedVector5 scratch;
					char* creature = CreatureLookup()->FindByID(top ? 0x5029da65 : 0xef2601ca);
					if (creature)
					{
						const ResourceKey& species = *(const ResourceKey*)(creature + 0x504);
						if (species != kNullKey && !planet->HasAnimalSpecies(species))
							pick = species;
					}
					if (pick != kNullKey)
						lowLOD->SetSimAnimalAt(&pick, &mGenesisDevicePos, 0);
				}
			}
		}
	}

	// density ramp over the genesis cells
	bool finished = false;
	if (level > 0 && time > kGenesisStartTime)
	{
		const int numCells = mGenesisCells.size();
		int numLevel1;   // cells with at least level-1 life
		int numLevel2;   // ... level 2
		int numLevel3;   // ... level 3
		switch (level)
		{
		case 1:
		{
			const float end = kGenesisStageDuration * 3.0f + mGenesisTimeT1;
			const float e = Max(kGenesisMinEndTime, end);
			const float f1 = Clamp((time - mGenesisTimeT1) / (e - mGenesisTimeT1), 0.0f, 1.0f);
			numLevel1 = RoundToInt((float)numCells * f1);
			numLevel3 = 0;
			numLevel2 = 0;
			break;
		}
		case 2:
		{
			const float end = kGenesisStageDuration * 2.0f + mGenesisTimeT2;
			const float e = Max(kGenesisMinEndTime, end);
			const float f1 = Clamp((time - mGenesisTimeT1) / (e - mGenesisTimeT1), 0.0f, 1.0f);
			numLevel1 = RoundToInt(f1 * (float)numCells);
			const float f2 = Clamp(((time - mGenesisTimeT2) * 0.5f) / (e - mGenesisTimeT2), 0.0f, 0.5f);
			numLevel2 = RoundToInt(f2 * (float)numCells);
			numLevel3 = 0;
			break;
		}
		case 3:
		{
			const float end = mGenesisTimeT3 + kGenesisStageDuration;
			const float e = Max(kGenesisMinEndTime, end);
			const float cells = (float)numCells;
			const float f1 = Clamp((time - mGenesisTimeT1) / (e - mGenesisTimeT1), 0.0f, 1.0f);
			numLevel1 = RoundToInt(f1 * cells);
			const float f2 = Clamp(((time - mGenesisTimeT2) * 0.67f) / (e - mGenesisTimeT2), 0.0f, 0.67f);
			numLevel2 = RoundToInt(f2 * cells);
			const float f3 = Clamp(((time - mGenesisTimeT3) * 0.33f) / (e - mGenesisTimeT3), 0.0f, 0.33f);
			numLevel3 = RoundToInt(f3 * cells);
			if (time >= e)
				finished = true;
			else
				finished = false;
			break;
		}
		}
		if (numLevel2 >= numLevel1)
			numLevel2 = numLevel1 - 1;
		if (numLevel3 >= numLevel2)
			numLevel3 = numLevel2 - 1;

		bool plantsChanged = false;
		for (int i = 0; i < numLevel1; ++i)
		{
			cCubeSimIt& cell = mGenesisCells[i];
			const int stage = (i < numLevel3) ? 3 : (i < numLevel2) + 1;
			for (int k = 0; k < 3; ++k)
			{
				ResourceKey species = tm->GetPlantSpecies(stage, plantTypes[k], data);
				if (species != kNullKey)
				{
					lowLOD->SetPlantDensity(cell.mCellIndex, &species, 1, 0);
					plantsChanged = true;
				}
			}
			for (int j = 0; j < 3; ++j)
			{
				if (j < 2 && j == i % 2)
					continue;
				ResourceKey species;
				if (j == 2)
					species = tm->GetTopAnimalSpecies(stage, data);
				else
					species = tm->GetAnimalSpecies(stage, j, data);
				if (species != kNullKey)
					lowLOD->SetAnimalDensity(cell.mCellIndex, &species, 1, 0);
			}
		}
		if (plantsChanged)
		{
			PlanetUpdater()->Update();
			PlanetUpdater()->Invalidate(0x1f);
		}
	}
	if (finished)
		mGenesisDeviceOn = false;
}

}  // namespace SP
