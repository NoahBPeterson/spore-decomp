// Slice s00f392b0: Simulator::cCivTokenTranslator::TranslateToken (0x00f39580).
// Hash-switch on the FNV-1 of the token; each case produces the replacement text.
// 32-bit MSVC 2008 SP1 (no /EHsc: no EH frames in the original).
// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"

namespace eastl {
class string16 {
 public:
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  int mAllocator;
  string16& operator=(const string16& x);   // 0x0057cb60
  string16& operator=(const wchar_t* p);    // 0x005c3d90
  string16& operator+=(const wchar_t* p);   // 0x00599bb0
  string16& assign(const wchar_t* first, const wchar_t* last);  // 0x00423650
  void clear();                             // 0x005726c0
};
}  // namespace eastl

namespace EA {
namespace Hash {
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int caseMode);   // 0x00932f30
}
namespace Locale {
int SetNumberString(uint64_t value, wchar_t* buffer, int bufferSize);              // 0x00881ae0
int SetNumberString(double value, wchar_t* buffer, int bufferSize, int flags);     // 0x00881ea0
}
}  // namespace EA

// 0x00881730: time formatter (hours, minutes, seconds into buffer using a format string)
void FormatTime(int a, int minutes, int seconds, wchar_t* buffer, int size, const wchar_t* fmt);
extern const wchar_t g_TimeFormat[];     // 0x0146d3c4
extern const wchar_t g_PercentSign[];    // 0x014278e0

// SP::cString (size 0x14): localized string handle
struct cString {
  uint32_t pad[5];
  cString();                                                         // 0x006b5060
  cString(uint32_t tableId, uint32_t instanceId, int flag);          // 0x006b5770
  void Load(uint32_t tableId, uint32_t instanceId, int flag);        // 0x006b54b0
  const wchar_t* GetText();                                          // 0x006b55c0
  ~cString();                                                        // 0x006b5240
};

// Localized string slot embedded in game data (wrapper around cString::GetText)
struct LocText {
  uint32_t pad;
  const wchar_t* Text();                                             // 0x00f26360
};

struct ResKey { uint32_t instanceId; uint32_t typeId; uint32_t groupId; };

struct RefObj {
  virtual void AddRef();      // +0
  virtual void Release();     // +4
  const wchar_t* GetName();   // 0x00414e10
};
struct RefLocal {             // AutoRefCount<RefObj> (constructed in place by 0x00572660)
  RefObj* mp;
  RefLocal* Init(RefObj* p);  // 0x00572660 (AddRef)
};
struct RefHolder {
  RefObj* mp;
  RefObj** AsPPTypeParam();   // 0x00a16f40
};
RefObj* __cdecl HolderGet(RefHolder* h);   // 0x00421f60

struct ResManager {
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual bool GetResource(ResKey* key, RefObj** out, int a, int b, int c, int d);   // slot 3 (+0xc)
};
ResManager* GetManager();       // 0x0067dcd0 (returns the global at 0x015fd894)

// Sub-interface at +4 of the A object
struct SubIface {
  virtual const wchar_t* s0();
  virtual const wchar_t* s1();    // +4
  virtual const wchar_t* s2();
  virtual const wchar_t* s3();    // +0xc
};
struct DataRecord {
  uint32_t pad0[8 / 4];
  uint32_t key[3];                // +0x08: resource key triple
  uint32_t pad14[(0x7c - 0x14) / 4];
  LocText mText7c;                // +0x7c
  uint32_t pad80[(0xb8 - 0x80) / 4];
  LocText mTextB8;                // +0xb8
  uint32_t padbc[(0xf4 - 0xbc) / 4];
  LocText mTextF4;                // +0xf4
};
struct GameA {                    // *(g + 0x74)
  uint32_t pad0;
  SubIface sub;                   // +4 (own vtable)
  uint32_t pad8;
  uint32_t padc;
  DataRecord* mpRecord;           // +0x10
  uint32_t GetThing();            // 0x00f3c0e0
  uint32_t GetCount();            // 0x00f3be30
};
struct GameB {                    // *(g + 0x78)
  uint32_t pad[0xd4 / 4];
  uint32_t mField0d4;             // +0xd4
  unsigned f19c20(uint32_t i);    // 0x00f19c20
  unsigned f19c40(uint32_t i);    // 0x00f19c40
  unsigned f19c60(uint32_t i);    // 0x00f19c60
  int f19190();                   // 0x00f19190
  float f19d10();                 // 0x00f19d10
  void f1b9b0(eastl::string16* out);              // 0x00f1b9b0
  void f1ba00(eastl::string16* out);              // 0x00f1ba00
  void f1ba50(uint32_t i, eastl::string16* out);  // 0x00f1ba50
  void f1bc00(uint32_t i, eastl::string16* out);  // 0x00f1bc00
  void f1bcb0(uint32_t i, eastl::string16* out);  // 0x00f1bcb0
  void f1bcd0(uint32_t i, eastl::string16* out);  // 0x00f1bcd0
  void f1bcf0(uint32_t i, eastl::string16* out);  // 0x00f1bcf0
};
struct GameRec {                  // *(A + 0x10): string slots
  uint32_t pad[0x7c / 4];
};
struct Game {
  uint32_t pad0[0x74 / 4];
  GameA* mpA;                     // +0x74
  GameB* mpB;                     // +0x78
  uint32_t pad1[(0xcc - 0x7c) / 4];
  int mMode;                      // +0xcc
  void FUN_00ef1930(void* p, float time);   // 0x00ef1930
};
extern Game* g_pGame;             // 0x016c7aa4

struct TokenData {
  uint32_t pad[4 / 4];
  uint32_t f04;
  uint32_t f08;
  uint32_t f0c;
};

// Callees taking the sub-object at this+0x14 (cdecl)
bool __cdecl FUN_00f39470(const ResKey* key, eastl::string16* out);         // 0x00f39470
bool __cdecl FUN_00eed920(void* sub, eastl::string16* out);                 // 0x00eed920 (SetIntProperty)
bool __cdecl FUN_00eeea50(void* sub, eastl::string16* out);                 // 0x00eeea50
bool __cdecl FUN_00f392b0(const ResKey& key, eastl::string16* out, uint32_t x); // 0x00f392b0
bool __cdecl FUN_00f39130(void* sub);                                       // 0x00f39130

struct cCivTokenTranslator {
  uint32_t pad0[0xc / 4];
  uint32_t mIndex;                // +0x0c
  TokenData* mpData;              // +0x10
  uint32_t mSub[3];               // +0x14
  uint32_t mField20;              // +0x20
  eastl::string16 mStr24;         // +0x24
  eastl::string16 mStr34;         // +0x34
  eastl::string16 mStr44;         // +0x44
  eastl::string16 mStr54;         // +0x54

  bool BaseTranslate(const wchar_t* token, eastl::string16* out);   // 0x00b324f0
  bool TranslateToken(const wchar_t* token, eastl::string16* out);  // 0x00f39580
};

static __forceinline void AssignLocalized(eastl::string16* out, uint32_t table, uint32_t inst)
{
  cString s(table, inst, 0);
  *out = s.GetText();
}

// @ 0x00f39580
bool cCivTokenTranslator::TranslateToken(const wchar_t* token, eastl::string16* out)
{
  wchar_t buf[64];
  const wchar_t* text;
  ResKey key;
  RefHolder res;
  RefLocal ref;
  uint32_t hash = EA::Hash::FNV1_String16(token, 0x811c9dc5, 1);
  switch (hash) {
  case 0x1204c9cd:
    text = g_pGame->mpA->sub.s3();
    break;
  case 0x04e6465a:
    { uint64_t n = (uint64_t)g_pGame->mpB->f19c60(mIndex);
    EA::Locale::SetNumberString(n, buf, 64); }
    text = buf;
    break;
  case 0x130b98d0:
    g_pGame->mpB->f1ba50(mIndex, out);
    return true;
  case 0x18e94bc0: {
    uint32_t v = mpData->f0c;
    if (v == 0) {
      AssignLocalized(out, 0x21851ebe, 0x7b53a1f);
      return true;
    }
    { uint64_t n = (uint64_t)v;
    EA::Locale::SetNumberString(n, buf, 64); }
    text = buf;
    break;
  }
  case 0x138ab6cc:
    return FUN_00eed920(&mSub, out);
  case 0x28b0ccfd:
    { uint64_t n = (uint64_t)g_pGame->mpB->f19c20(mIndex);
    EA::Locale::SetNumberString(n, buf, 64); }
    text = buf;
    break;
  case 0x30a6b541:
    text = g_pGame->mpA->mpRecord->mTextB8.Text();
    break;
  case 0x29ba9b78:
    { uint64_t n = (uint64_t)g_pGame->mpA->GetThing() + 1;
    EA::Locale::SetNumberString(n, buf, 64); }
    text = buf;
    break;
  case 0x343fa5e1:
    if (g_pGame->mMode == 2)
      g_pGame->mpB->f1bcd0(mIndex, out);
    else
      g_pGame->mpB->f1bc00(mpData->f08, out);
    return true;
  case 0x485be3a2: {
    AssignLocalized(out, 0x623d2fc0, 0x7ceb16b);
    return true;
  }
  case 0x37f56d0a: {
    DataRecord* rec = g_pGame->mpA->mpRecord;
    const ResKey& src = rec ? *(ResKey*)&rec->key : ResKey();
    key = src;
    key.typeId = 0x30bdee3;
    res.mp = 0;
    bool ok = false;
    if (key.instanceId) {
      ResManager* mgr = GetManager();
      if (mgr->GetResource(&key, res.AsPPTypeParam(), 0, 0, 0, 0)) {
        ref.Init(HolderGet(&res));
        if (ref.mp) {
          *out = ref.mp->GetName();
          ref.mp->Release();
          ok = true;
        }
      }
    }
    if (!ok) out->clear();
    if (res.mp) res.mp->Release();
    return true;
  }
  case 0x6c012eb6:
    return FUN_00f39470((const ResKey*)&mSub, out);
  case 0x9b683fc0:
    { uint64_t n = (uint64_t)g_pGame->mpB->f19c40(mIndex);
    EA::Locale::SetNumberString(n, buf, 64); }
    text = buf;
    break;
  case 0x761e22e9: {
    int ms = g_pGame->mpB->f19190();
    FormatTime(0, (ms / 1000) / 60, (ms / 1000) % 60, buf, 64, g_TimeFormat);
    text = buf;
    break;
  }
  case 0x9f5ea311:
    if (g_pGame->mMode == 2)
      g_pGame->mpB->f1bcb0(mIndex, out);
    else
      g_pGame->mpB->f1bc00(mpData->f04, out);
    return true;
  case 0xa88362d5: {
    *out = g_pGame->mpA->mpRecord->mText7c.Text();
    if (out->mpBegin == out->mpEnd) {
      AssignLocalized(out, 0x21851ebe, 0x71877c1);
    }
    return true;
  }
  case 0xa1348ef8:
    g_pGame->mpB->f1bcf0(g_pGame->mpB->mField0d4, out);
    return true;
  case 0xaf0bd59a:
    *out = mStr54;
    return true;
  case 0xb6c323fd: {
    AssignLocalized(out, 0x3dade1bb, 0x7ec9f8a);
    return true;
  }
  case 0xafffb8e5:
    g_pGame->mpB->f1ba00(out);
    return true;
  case 0xb88af570:
    EA::Locale::SetNumberString((double)(g_pGame->mpB->f19d10() * 100.0f), buf, 64, 0);
    *out = buf;
    *out += g_PercentSign;
    return true;
  case 0xc145b09a:
    text = g_pGame->mpA->mpRecord->mTextF4.Text();
    break;
  case 0xbbf42260:
    g_pGame->mpB->f1b9b0(out);
    return true;
  case 0xc5dc967b: {
    unsigned a = g_pGame->mpB->f19c60(mIndex);
    unsigned b = g_pGame->mpB->f19c40(mIndex);
    { uint64_t n = (uint64_t)(b - a);
    EA::Locale::SetNumberString(n, buf, 64); }
    text = buf;
    break;
  }
  case 0xcaba45ad:
    return FUN_00eeea50(&mSub, out);
  case 0xca3921ce: {
    AssignLocalized(out, 0x623d2fc0, 0x7ceb16a);
    return true;
  }
  case 0xcc67937a:
    return FUN_00f392b0(*(const ResKey*)&mSub, out, mField20);
  case 0xdc8470cc: {
    cString s;
    if (FUN_00f39130(&mSub))
      s.Load(0x623d2fc0, 0x7ceb169, 0);
    else
      s.Load(0x623d2fc0, 0x7ceb16a, 0);
    *out = s.GetText();
    return true;
  }
  case 0xda3ea6ed:
    text = g_pGame->mpA->sub.s1();
    break;
  case 0xde2f1218:
    text = g_pGame->mpA->sub.s1();
    break;
  case 0xe3410f82:
    text = mStr34.mpBegin;
    break;
  case 0xe3410f81:
    text = mStr24.mpBegin;
    break;
  case 0xe4e48c5c:
    *out = mStr44;
    return true;
  case 0xf89ca4c4:
    { uint64_t n = (uint64_t)g_pGame->mpA->GetCount();
    EA::Locale::SetNumberString(n, buf, 64); }
    text = buf;
    break;
  default:
    return BaseTranslate(token, out);
  }
  *out = text;
  return true;
}

// ---------------------------------------------------------------------------
// Property helpers used by the mission progress/collectable text builders.
// ---------------------------------------------------------------------------
struct cProperty;
struct cPropertyList : RefObj
{
  virtual void v08();                                       // +0x08
  virtual void v0c();                                       // +0x0c
  virtual void v10();                                       // +0x10
  virtual void v14();                                       // +0x14
  virtual void v18();                                       // +0x18
  virtual void v1c();                                       // +0x1c
  virtual void v20();                                       // +0x20
  virtual bool GetPropertyByKey(uint32_t name, cProperty** out);  // +0x24
};

struct cProperty
{
  uint32_t mValue;                                          // +0x00
  uint32_t mPad04[3];                                       // +0x04
  uint8_t  mFlags;                                          // +0x10
  uint8_t  mPad11;                                          // +0x11
  uint16_t mType;                                           // +0x12
  int* GetInt();                                            // 0x0041e990
};

struct cCollectableItems : RefObj
{
  void Load(const ResKey* key);                             // 0x00595a90
  bool GetValue(uint64_t* value);                           // 0x00595230
};

bool __cdecl GetEditorPropertyList(const ResKey& key, cPropertyList** out);  // 0x005bf0e0
bool __cdecl LoadCollectableItems(cPropertyList* list, cCollectableItems** out); // 0x005bf1e0
void* __cdecl FUN_00556140(const ResKey* key, uint32_t name);                   // 0x00556140
void* __cdecl FUN_00556140(const ResKey* key, uint32_t name, void* parent);     // 0x00556140
void* __cdecl FUN_00556440(void* node);                                         // 0x00556440
void __cdecl SplitItemId(uint64_t id, uint32_t* hi, uint32_t* lo);              // 0x00593960

extern const wchar_t g_emptyString[];   // 0x013ec468

// ===========================================================================
// 0x00f392b0 -- cSPCreatureNestMission::GetProgressText
// Reads the nest progress from the editor property list (when the supplied
// progress is negative), maps the mission template id to a localized string
// table and writes "table[base + progress - 1]".
// ===========================================================================
// @ 0x00f392b0
bool __cdecl FUN_00f392b0(const ResKey& key, eastl::string16* out, uint32_t x)
{
  cPropertyList* list = 0;
  int progress = 0;
  bool ok = GetEditorPropertyList(key, &list);

  if (ok)
  {
    if ((int)x < 0)
    {
      if (list != 0)
      {
        cProperty* prop = 0;
        if (list->GetPropertyByKey(0x5888ef41, &prop) && prop->mType == 9)
          progress = *prop->GetInt();
      }
    }
    else
    {
      progress = (int)x;
    }

    uint32_t base = 0x7cea000;
    if (progress > 0)
    {
      void* node = FUN_00556140(&key, 0x2db6dad3);
      if (node == 0)
      {
        void* a = FUN_00556140(&key, 0xbeb528cb);
        void* b = FUN_00556140(&key, 0xf71fa311, a);
        void* c = FUN_00556140(&key, 0xad56080c, b);
        void* d = FUN_00556140(&key, 0xa426730b, c);
        node = FUN_00556440(d);
      }

      switch ((int)node)
      {
      case (int)0x9ce4639c: base = 0x7cea500; break;
      case (int)0xa5656e84: base = 0x7cea900; break;
      case (int)0xb436c0bc: base = 0x7cea400; break;
      case (int)0xb7cb9f7a: base = 0x7cea600; break;
      case (int)0xcf6c2ab4: base = 0x7cea700; break;
      case (int)0xb40d2187: base = 0x7cea200; break;
      case (int)0xd9c806e4: base = 0x7cea800; break;
      case (int)0xf966d429: base = 0x7ceaa00; break;
      case (int)0x2b35f523: base = 0x7cea300; break;
      case (int)0x50fee6bf: base = 0x7cea100; break;
      }
      base = base - 1 + progress;
    }

    {
      cString str(0x623d2fc0, base, 0);
      const wchar_t* text = str.GetText();
      const wchar_t* end = text;
      while (*end != 0)
        ++end;
      out->assign(text, end);
    }
  }

  if (list != 0)
    list->Release();
  return ok;
}

// ===========================================================================
// 0x00f39470 -- collectable-item text builder
// ===========================================================================
// @ 0x00f39470
bool __cdecl FUN_00f39470(const ResKey* key, eastl::string16* out)
{
  cPropertyList* list = 0;
  bool ok = GetEditorPropertyList(*key, &list);
  bool result = false;

  if (ok)
  {
    cCollectableItems* items = 0;
    if (LoadCollectableItems(list, &items))
    {
      items->Load(key);
      uint64_t value = 0;
      if (items->GetValue(&value))
      {
        uint32_t hi = 0;
        uint32_t lo = 0;
        SplitItemId(value, &hi, &lo);
        AssignLocalized(out, 0x623d2fc0, lo);
      }
      else
      {
        *out = g_emptyString;
      }
      result = true;
    }
    if (items != 0)
      items->Release();
  }

  if (list != 0)
    list->Release();
  return result;
}

// ---------------------------------------------------------------------------
// Serialization thunk for the vehicle/GameData state.
// ---------------------------------------------------------------------------
class cStreamPos
{
public:
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual int Tell(int); virtual void Seek(int, int);
};

class cStreamWriter
{
public:
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5();
  virtual cStreamPos* GetStream();                          // +0x18
};

class cOutStream
{
public:
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6();
  virtual bool IsOk();                                      // +0x1c
  virtual cStreamWriter* GetWriter();                       // +0x20
};

struct cDataSerializerGeneric;

struct cVarListSerializer
{
  uint8_t mStorage[0xa14];
  cVarListSerializer(void* obj, cDataSerializerGeneric* list, uint32_t sig); // 0x00692f90
  bool Serialize(cOutStream* stream);                                      // 0x00692900
};

namespace EA { namespace IO {
bool __cdecl WriteUint32(void* stream, const void* value, int count, int flags); // 0x0093aa70
} }

static inline void WriteU32(cOutStream* s, uint32_t v)
{
  uint32_t t = v;
  cStreamPos* st = s->GetWriter()->GetStream();
  EA::IO::WriteUint32(st, &t, 1, 0);
}

struct SerializerThunk
{
  void Serialize(cOutStream* stream);
};

// ===========================================================================
// 0x00f39e80 -- write the 0x06fd9895 marker and serialize the object's vars.
// ===========================================================================
// @ 0x00f39e80
void SerializerThunk::Serialize(cOutStream* stream)
{
  WriteU32(stream, 0x06fd9895);

  cVarListSerializer serializer(this, (cDataSerializerGeneric*)0x015b029c, 0x01a80d26);
  serializer.Serialize(stream);
}

// ---------------------------------------------------------------------------
// Vehicle tick models.
// ---------------------------------------------------------------------------
struct cGameNounManager;
struct cGameTimeManager;
cGameNounManager* NounManager();          // 0x00b3d300
cGameTimeManager* GameTimeManager();      // 0x00b3d380
void RemoveVehicles();                    // 0x00dc6a20

struct Sub5d0
{
  virtual void* v00();
  virtual void* v04();
  virtual void* v08();
  virtual void* v0c();
  virtual void* v10();
  virtual void* v14();
  virtual void* v18();
  virtual void* v1c();
  virtual void* v20();                                      // +0x20
};

struct Stimuli
{
  uint32_t mPad00;
  uint32_t mPad04;
  void* UpdateStimuli(float time);                          // 0x00bc9980
};

struct StimuliHolder
{
  void*     m00;                                            // +0x000
  uint32_t  m04;                                            // +0x004
  Stimuli   m08;                                            // +0x008
  uint8_t   m10[0x1d0 - 0x10];                              // +0x010
  uint8_t   m1d0[0x5e8 - 0x1d0];                            // +0x1d0
  uint32_t  m5e8;                                           // +0x5e8
  uint32_t  m5ec;                                           // +0x5ec
  uint32_t  m5f0;                                           // +0x5f0
  uint32_t  m5f4;                                           // +0x5f4
  uint32_t  m5f8;                                           // +0x5f8
  uint32_t  m5fc;                                           // +0x5fc
};

struct cGameData
{
  void FUN_00cac710();                                      // 0x00cac710
  void FUN_00c9f2d0(int ms);                                // 0x00c9f2d0
  void FUN_00ca96b0();                                      // 0x00ca96b0
  void FUN_00ca31f0();                                      // 0x00ca31f0

  uint8_t mPad000[0x508];                                   // +0x000
  uint8_t mField508[0x5d0 - 0x508];                         // +0x508
  Sub5d0  mAt5d0;                                           // +0x5d0
  uint8_t mPad5d4[0xaf0 - 0x5d4];                           // +0x5d4
  StimuliHolder* mpAtAf0;                                   // +0xaf0
};

struct GameDataVector
{
  uint32_t     m00;                                         // +0x00
  cGameData**  mpBegin;                                     // +0x04
  cGameData**  mpEnd;                                       // +0x08
};

struct cGameNounManager
{
  GameDataVector* GetGameDataVector(void* a, void* b, void* c, void* d, void** e); // 0x00b21340
};

struct cGameTimeManager
{
  uint64_t FUN_00b316c0();                                  // 0x00b316c0
};

void __cdecl WalkTree(float time, double scaled, void* p0, void* data,
                      void* p1d0, void* p5e8, void* p5fc, void* upd); // 0x00bc8ff0

void* g_18c6de8 = 0;                                        // 0x018c6de8
static float g_timeScale = 0.001f;

// ===========================================================================
// 0x00f39f50 -- cVehicleTicker::OnTick
// ===========================================================================
// @ 0x00f39f50
void __cdecl FUN_00f39f50(uint32_t unused, int deltaMs)
{
  (void)unused;
  cGameNounManager* noun = NounManager();
  GameDataVector* vec = noun->GetGameDataVector(
      (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00ae72d0,
      (void*)0x00b1e500, &g_18c6de8);

  int count = (int)(vec->mpEnd - vec->mpBegin);
  cGameData*** begin = &vec->mpBegin;

  if (g_pGame->mMode != 2)
  {
    for (int i = 0; i < count; ++i)
      (*begin)[i]->FUN_00ca31f0();
    return;
  }

  float time = (float)(uint32_t)deltaMs * g_timeScale;

  for (int i = 0; i < count; ++i)
  {
    cGameData* data = (*begin)[i];
    data->FUN_00cac710();
    data->FUN_00c9f2d0(deltaMs);
    data->FUN_00ca96b0();

    if (data->mAt5d0.v20() == 0)
    {
      StimuliHolder* holder = data->mpAtAf0;
      if (holder->m00 != 0)
      {
        void* upd = holder->m08.UpdateStimuli(time);
        uint64_t now = GameTimeManager()->FUN_00b316c0();
        double scaled = (double)now * g_timeScale;
        WalkTree(time, scaled, holder->m00, data, &holder->m1d0,
                 (void*)holder->m5e8, (void*)holder->m5fc, upd);
      }
    }

    data->FUN_00ca31f0();
    g_pGame->FUN_00ef1930(data->mField508, time);
  }

  RemoveVehicles();
}

// ===========================================================================
// 0x00f3a120 -- scrub-rate lookup
// ===========================================================================
// @ 0x00f3a120
float __cdecl FUN_00f3a120(uint32_t index)
{
  switch (index)
  {
  case 0: return 0.0f;
  case 1: return 0.25f;
  case 2: return 0.5f;
  case 3: return 0.75f;
  case 4: return 1.0f;
  default: return 0.0f;
  }
}

// ===========================================================================
// 0x00f3a160 -- progress fraction -> discrete stage index
// ===========================================================================
// @ 0x00f3a160
int __cdecl FUN_00f3a160(float value)
{
  if (value < 0.1)
    return 0;
  if (value < 0.3)
    return 1;
  if (value < 0.65)
    return 2;
  if (value < 0.95)
    return 3;
  return 4;
}
