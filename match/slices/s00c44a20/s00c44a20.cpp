// Slice s00c44a20: methods of an unidentified game-object class around 0x00C44A20,
// plus one free __stdcall float helper. Names are provisional unless noted.
// 0x00C44D00 needs /arch:SSE2 (movss + fld float return); see manifest.txt.
#include "types.h"

struct ResourceKey {
  uint32_t instance, type, group;
  ResourceKey() : instance(0), type(0), group(0) {}
};

struct Resource {
  char pad[0x504];
  ResourceKey key;
  void FUN_004da330(void* p);
};

struct ResourceManager {
  Resource* FUN_004df550(const ResourceKey* key);
};
ResourceManager* FUN_00401090();

// 0xA14-byte stack serializer built over the owner (ctor 0x00692F90). Declared with a
// non-char array so /GS does not add a cookie.
struct LocalSerializer {
  uint32_t buf[0xa14 / 4];
  LocalSerializer(void* owner, const void* table, uint32_t id);
  bool FUN_00692900(void* stream);
  bool FUN_00693e10(void* stream);
  void FUN_00695960(void* stream);
};
extern char DAT_015745f0[];

#define PV(n) virtual void pv##n();
class GameObj {
public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41)
  virtual uint32_t v42();
  PV(43) PV(44) PV(45) PV(46) PV(47)
  virtual int v48(int a);
  PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58)
  PV(59) PV(60) PV(61)
  virtual bool v62();
  virtual bool v63();
  virtual bool v64();
  PV(65) PV(66) PV(67) PV(68) PV(69) PV(70) PV(71) PV(72) PV(73) PV(74)
  PV(75) PV(76) PV(77) PV(78) PV(79) PV(80) PV(81) PV(82)
  virtual void v83(uint32_t id);

  bool FUN_00b18590(void* stream);
  bool FUN_00b18600(void* stream);

  int Read_c44a20(void* stream);
  bool Write_c44ad0(void* stream);
  void Serialize_c44b40(void* stream);
  void RegisterIds_c44b80();
  void ForwardToResource_c44c40(void* p);
  int CallV48_c44c60(int a);
  bool CallV42_c44c90();
  uint32_t GetTypeId_c44cb0();

  char pad[0x16c - 4];
  Resource* mpResource;  // 0x16C
  ResourceKey mKey;      // 0x170
};

// @ 0x00C44A20
int GameObj::Read_c44a20(void* stream) {
  if (mpResource)
    mKey = mpResource->key;
  else
    mKey = ResourceKey();
  bool ok = FUN_00b18590(stream);
  LocalSerializer s(this, DAT_015745f0, 0x1a80d26);
  if (s.FUN_00692900(stream) && ok)
    return 1;
  return 0;
}

// @ 0x00C44AD0
bool GameObj::Write_c44ad0(void* stream) {
  bool ok = FUN_00b18600(stream);
  LocalSerializer s(this, DAT_015745f0, 0x1a80d26);
  ok &= s.FUN_00693e10(stream);
  if (mKey.instance != 0)
    mpResource = FUN_00401090()->FUN_004df550(&mKey);
  return ok;
}

// @ 0x00C44B40
void GameObj::Serialize_c44b40(void* stream) {
  LocalSerializer s(this, DAT_015745f0, 0x1a80d26);
  s.FUN_00695960(stream);
}

// @ 0x00C44B80
void GameObj::RegisterIds_c44b80() {
  v83(0x35ec3de);
  v83(0x248975f);
  v83(0x2489760);
  v83(0x4249453);
}

// @ 0x00C44C40
void GameObj::ForwardToResource_c44c40(void* p) {
  if (mpResource)
    mpResource->FUN_004da330(p);
}

// @ 0x00C44C60
int GameObj::CallV48_c44c60(int a) {
  return v48(a);
}

// @ 0x00C44C90
bool GameObj::CallV42_c44c90() {
  return 0 < v42();
}

// @ 0x00C44CB0
uint32_t GameObj::GetTypeId_c44cb0() {
  if (v62())
    return 0x11965a4d;
  if (v63())
    return v64() ? 0x11fd3bf3 : 0xe22e5c17;
  return 0x1a2b6f64;
}

struct Thing {
  char pad[0x2c];
  uint32_t flags;  // 0x2C
  bool FUN_00b8d970();
  int FUN_00b8d9b0();
  void* FUN_00b8de30();
};
struct ThingMgr { bool FUN_00fee110(Thing* t); };
ThingMgr* FUN_00feb9f0();
struct IndexTable { int FUN_00b1fdb0(); };
struct Relations { bool FUN_00c31bf0(int i); bool FUN_00c31b10(int i); };
Relations* FUN_01021300();

// @ 0x00C44D00
float __stdcall GetFactor_c44d00(Thing* t, const bool* mode) {
  if (t->FUN_00b8d970() || t->FUN_00b8d9b0() != 0 || (t->flags & 0x800))
    return -1.0f;
  bool m = FUN_00feb9f0()->FUN_00fee110(t);
  if (mode[0] || mode[1]) {
    Relations* r = FUN_01021300();
    int i = ((IndexTable*)t->FUN_00b8de30())->FUN_00b1fdb0();
    bool a, b;
    if (i != -1) {
      a = r->FUN_00c31bf0(i);
      b = r->FUN_00c31b10(i);
    } else {
      a = false;
      b = false;
    }
    if (mode[0]) {
      if (a) return m ? 0.07f : 1.5f;
      if (b) return 0.0f;
      return m ? 0.05f : 0.5f;
    }
    if (mode[1]) {
      if (a) return 0.0f;
      if (b) return m ? 0.07f : 1.5f;
      return m ? 0.05f : 0.5f;
    }
  }
  return m ? 0.1f : 1.0f;
}
