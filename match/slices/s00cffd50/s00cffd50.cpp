// Slice s00cffd50 -- SP::cCivTokenTranslator::TranslateToken.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

namespace eastl {
class string16 {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  int mAllocator;
  string16& operator=(const wchar_t* p);                        // 0x005c3d90
  string16& assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
  string16& assign(const wchar_t* p) {
    const wchar_t* end = p;
    while (*end)
      ++end;
    return assign(p, p + (end - p));
  }
};

struct UIntNameNode {
  char pad[0x10];
  uint32_t mKey;          // +0x10
  const wchar_t* mValue;  // +0x14
};
struct UIntNameIterator {
  UIntNameNode* mpNode;
  UIntNameIterator() {}
  UIntNameIterator(const UIntNameIterator& x) : mpNode(x.mpNode) {}
  UIntNameNode& operator*() const { return *mpNode; }
};
struct UIntNameMap {
  UIntNameIterator find(const uint32_t& key);  // 0x00e5c780
};
}  // namespace eastl

namespace EA {
namespace Hash {
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int caseMode);  // 0x00932f30
}
namespace Locale {
int SetNumberString(double value, wchar_t* buffer, int bufferSize, int flags);  // 0x00881ea0
int SetNumberString(int64_t value, wchar_t* buffer, int bufferSize);            // 0x00881ae0
}
}  // namespace EA

namespace SP {

class cISPEditorNameProvider {
 public:
  virtual void pv0();
  virtual const wchar_t* GetName();  // +0x4
};

struct cPlanetLookup {
  int GetType();  // 0x00801920 ([ecx+0x48])
};
struct cPlanetRecordEntry {
  char pad[0x3c];
  int* mpBegin;  // +0x3c
  int* mpEnd;    // +0x40
};
struct cPlanetRecord {
  char pad[0x15c];
  int* mpEntriesBegin;  // +0x15c
  int* mpEntriesEnd;    // +0x160
  cPlanetLookup* GetLookup();               // 0x00b8de30
  cPlanetRecordEntry* GetEntry(int index);  // 0x00b8dec0
};
struct cEmpire {
  cPlanetRecord* GetHomePlanet();  // 0x00c31730
};
struct cPlanet {
  char pad[0x13c];
  cPlanetRecord* mpRecord;  // +0x13c
  cEmpire* GetEmpire();     // 0x00c71e30
};
struct cTuning {
  float GetValue(int index);  // 0x0102f8c0
};
cTuning* GetTuning();         // 0x0102f810
int MapPlanetType(int type);  // 0x00c6fe00

struct cCity {
  char pad[0x34];
  cISPEditorNameProvider mNameProviderObj;  // +0x34
  cISPEditorNameProvider* NameProvider() { return &mNameProviderObj; }
  int GetPopulation();                   // 0x00bd8b80 (planet-mode population)
};
struct cCivilization {
  char pad[0x34];
  cISPEditorNameProvider mNameProviderObj;  // +0x34
  cISPEditorNameProvider* NameProvider() { return &mNameProviderObj; }
  char pad38[0x44 - 0x38];
  eastl::UIntNameMap mNames;             // +0x44 (rbtree)
  char pad44[0x2ac - 0x44 - 0x14];
  cCity* mpCityFromPlayer;               // +0x2ac
  char pad2b0[0x2d0 - 0x2b0];
  cCity* mpCityFromNPC;                  // +0x2d0
  char pad2d4[0x2f8 - 0x2d4];
  cCity* mpCityByPlayer;                 // +0x2f8
  float GetTradeValue(int a);            // 0x00bf6fa0
};

struct cGameData {
  virtual void* pv0();
  virtual void* pv1();
  virtual void* pv2();
  virtual void* QueryInterface(uint32_t typeId);  // +0xc
};

class cStringTokenTranslator {
 public:
  virtual ~cStringTokenTranslator();
  virtual int AddRef();
  virtual int Release();
  virtual bool TranslateToken(const wchar_t* token, eastl::string16& result);
  int mRefCount;
};
class cGameTokenTranslator : public cStringTokenTranslator {
 public:
  virtual bool TranslateToken(const wchar_t* token, eastl::string16& result);  // 0x00b324f0
  void* mPropList;                                                              // +0x8
};

int GetCurrentGameMode();  // 0x00b5b800
struct cSPLivingUniverse {
  static cPlanet* GetActivePlanet();   // 0x01021260
  static cEmpire* GetPlayerEmpire();   // 0x01021300
};
void ResolveSource(cGameData* source, cCivilization** ppCiv, cCity** ppCity);  // 0x00cfe9c0
cCity* FindTargetCity(int mode, cCivilization* civ);  // 0x00cfee00
float GetPlanetValue(cCivilization* civ);  // 0x00c72030
float ComputeScore(float a, float b, float c, bool d, bool e, int f, float g, int h, bool i);  // 0x00c71f00

class cCivTokenTranslator : public cGameTokenTranslator {
 public:
  virtual bool TranslateToken(const wchar_t* token, eastl::string16& result);  // 0x00cffd50
  cGameData* mpSource;  // +0xc
  cCity* mpTargetCity;  // +0x10
  int mOffers[5];       // +0x14
  int mCurrencyNumber;  // +0x28
};

#define TARGET_CITY_CASE(hash, mode)                                    \
  case hash: {                                                          \
    cCivilization* civ = 0;                                             \
    cCity* city = 0;                                                    \
    ResolveSource(mpSource, &civ, &city);                               \
    cCity* target = FindTargetCity(mode, civ);                          \
    if (target)                                                         \
      result = target->NameProvider()->GetName();                       \
    return true;                                                        \
  }

// @ 0x00cffd50
bool cCivTokenTranslator::TranslateToken(const wchar_t* token, eastl::string16& result) {
  wchar_t buffer[64];
  float value;
  int number;
  const wchar_t* name;
  switch (EA::Hash::FNV1_String16(token, 0x811c9dc5, 1)) {
    case 0x41d1ce62:
      if (mpTargetCity) {
        name = mpTargetCity->NameProvider()->GetName();
      nameString:
        result = name;
      }
      return true;
    case 0x3dd91065: {
      cCivilization* civ = 0;
      cCity* city = 0;
      ResolveSource(mpSource, &civ, &city);
      name = civ->mpCityFromPlayer->NameProvider()->GetName();
      goto nameString;
    }
    case 0x29f73bf5: {
      cCivilization* civ = 0;
      cCity* city = 0;
      ResolveSource(mpSource, &civ, &city);
      uint32_t key = 1;
      name = (*civ->mNames.find(key)).mValue;
      goto nameString;
    }
    case 0x4b8bb638:
      number = mOffers[3];
    numberString:
      EA::Locale::SetNumberString((int64_t)number, buffer, 64);
      buffer[63] = 0;
      result.assign(buffer);
      return true;
    case 0x4b8bb63d:
      number = mOffers[0];
      goto numberString;
    case 0x4b8bb639:
      number = mOffers[4];
      goto numberString;
    case 0x4b8bb63e:
      number = mOffers[1];
      goto numberString;
    case 0x6d2ddc32: {
      cCivilization* civ = 0;
      cCity* city = 0;
      ResolveSource(mpSource, &civ, &city);
      if (!city)
        return true;
      if (GetCurrentGameMode() == 0x1654c05) {
        cPlanet* planet = cSPLivingUniverse::GetActivePlanet();
        float tuning = GetTuning()->GetValue(MapPlanetType(planet->mpRecord->GetLookup()->GetType()));
        cEmpire* empire = planet->GetEmpire();
        bool bIsPlayer = empire == cSPLivingUniverse::GetPlayerEmpire();
        bool bIsHome;
        if (bIsPlayer)
          bIsHome = planet->mpRecord == empire->GetHomePlanet();
        else
          bIsHome = false;
        cPlanetRecord* rec = planet->mpRecord;
        int count = 1;
        if (rec->mpEntriesBegin != rec->mpEntriesEnd) {
          cPlanetRecordEntry* entry = rec->GetEntry(0);
          count = entry->mpEnd - entry->mpBegin;
        }
        value = ComputeScore((float)city->GetPopulation(), 0.0f, 3600.0f, bIsHome, bIsPlayer, 0, tuning, count, true);
        result = L"";
        EA::Locale::SetNumberString((double)value, buffer, 64, 0);
        buffer[63] = 0;
        result = buffer;
        return true;
      }
      number = city->GetPopulation();
      goto numberString;
    }
    case 0x4b8bb63f:
      number = mOffers[2];
      goto numberString;
    case 0x807555b7: {
      cCivilization* civ = 0;
      cCity* city = 0;
      ResolveSource(mpSource, &civ, &city);
      name = civ->mpCityByPlayer->NameProvider()->GetName();
      goto nameString;
    }
    case 0xb0554dd4:
      number = mCurrencyNumber;
      goto numberString;
    case 0xa36d8feb: {
      cCivilization* civ = 0;
      cCity* city = 0;
      ResolveSource(mpSource, &civ, &city);
      name = civ->mpCityFromNPC->NameProvider()->GetName();
      goto nameString;
    }
    TARGET_CITY_CASE(0xb7c9a880, 2)
    TARGET_CITY_CASE(0xb7c9a881, 1)
    TARGET_CITY_CASE(0xb7c9a882, 0)
    TARGET_CITY_CASE(0xb7c9a887, 3)
    TARGET_CITY_CASE(0xb7c9a886, 4)
    TARGET_CITY_CASE(0xb7c9a885, 5)
    TARGET_CITY_CASE(0xb7c9a884, 6)
    TARGET_CITY_CASE(0xb7c9a88b, 7)
    TARGET_CITY_CASE(0xb7c9a88a, 8)
    TARGET_CITY_CASE(0xd4744496, 9)
    case 0xf314632d: {
      cCivilization* civ = 0;
      cCity* city = 0;
      ResolveSource(mpSource, &civ, &city);
      if (!civ)
        return true;
      if (GetCurrentGameMode() == 0x1654c05) {
        value = GetPlanetValue(civ);
        result = L"";
        EA::Locale::SetNumberString((double)value, buffer, 64, 0);
        buffer[63] = 0;
        result = buffer;
        return true;
      }
      value = civ->GetTradeValue(0);
      number = (int)value;
      goto numberString;
    }
    case 0xee3981ea: {
      cCivilization* civ = 0;
      cCity* city = 0;
      ResolveSource(mpSource, &civ, &city);
      name = city->NameProvider()->GetName();
      goto nameString;
    }
  }
  return cGameTokenTranslator::TranslateToken(token, result);
}
}  // namespace SP
