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
};
extern Game* g_pGame;             // 0x016c7aa4

struct TokenData {
  uint32_t pad[4 / 4];
  uint32_t f04;
  uint32_t f08;
  uint32_t f0c;
};

// Callees taking the sub-object at this+0x14 (cdecl)
bool __cdecl FUN_00f39470(void* sub, eastl::string16* out);                 // 0x00f39470
bool __cdecl FUN_00eed920(void* sub, eastl::string16* out);                 // 0x00eed920 (SetIntProperty)
bool __cdecl FUN_00eeea50(void* sub, eastl::string16* out);                 // 0x00eeea50
bool __cdecl FUN_00f392b0(void* sub, eastl::string16* out, uint32_t x);     // 0x00f392b0
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
    return FUN_00f39470(&mSub, out);
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
    return FUN_00f392b0(&mSub, out, mField20);
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
