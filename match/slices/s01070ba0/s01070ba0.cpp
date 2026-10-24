// Slice s01070ba0: SP::cSPUISpace::cSPUISpace (0x01070ba0, 2475 bytes).
// Generated from the disassembly in work/match/scratch_s01070ba0_card.txt (store order preserved).
// Flags: /O2 /MD /Gy /EHsc /TP. Retail layout: cString is 0x14 bytes, so fields are accessed by offset.
#include "types.h"

// Six-argument operator new (0x00f473a0, cdecl): size, tag, four zero flags; caller pops 0x18.
void* operator new(unsigned int size, const char* tag, int a, int b, int c, int d);

namespace EA {
namespace Messaging {
void RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);  // 0x00571db0
}
}  // namespace EA

namespace SP {

inline float ConstOne() { return *reinterpret_cast<const float*>(0x01485720); }  // 1.0f
inline float ConstTwo() { return *reinterpret_cast<const float*>(0x01470f1c); }  // 2.0f

class cString {  // retail size 0x14
 public:
  cString();                                                  // 0x006b5060 (thiscall, no args)
  void Load(uint32_t tableId, uint32_t stringId, int flag);   // 0x006b54b0 (thiscall, ret 0xc)
  uint32_t mData[5];
};

class cSpaceTokenTranslator {  // size 0xc4
 public:
  cSpaceTokenTranslator();                                    // 0x0104a020 (thiscall, returns this)
  uint32_t mData[0x31];
};

namespace UI {
class MissionCardAnimator {  // size 0x20
 public:
  MissionCardAnimator();                                      // 0x007f83e0 (thiscall, returns this)
  uint32_t mData[8];
};
}  // namespace UI

class Callee5ec {
 public:
  void Init(int nFlag);                                       // 0x004ab350 (thiscall, ret 4)
};

class Callee620 {
 public:
  void Init();                                                // 0x00e0a390 (thiscall, plain ret)
};

// Singleton interface: slot 7 at +0x1c, slot 8 at +0x20.
class IVSlots {
 public:
  virtual void S0();
  virtual void S1();
  virtual void S2();
  virtual void S3();
  virtual void S4();
  virtual void S5();
  virtual void S6();
  virtual void S7(cSpaceTokenTranslator* translator);         // +0x1c
  virtual IVSlots* S8();                                      // +0x20
};
IVSlots* GetVSlotsSingleton();                                // 0x0067de40 (cdecl, no args)

// --- Interfaces touched by cSPUISpace::Shutdown (0x01071570) -------------------------------
// A window/global-UI object; only the vtable slots this path calls are interesting.
class IWindow {
 public:
  virtual void V000();          // +0x000
  virtual void V004();          // +0x004  Release()
  virtual void V008();          // +0x008
  virtual void V00c();          // +0x00c
  virtual void V010();  virtual void V014();  virtual void V018();  virtual void V01c();
  virtual void V020();  virtual void V024();  virtual int V028();
  virtual void V02c();  virtual void V030();  virtual void V034();  virtual void V038();
  virtual void V03c();  virtual void V040();  virtual void V044();  virtual void V048();
  virtual void V04c();  virtual void V050();  virtual void V054();  virtual void V058();
  virtual void V05c();  virtual void V060();  virtual void V064();  virtual void V068();
  virtual void V06c();  virtual void V070();  virtual void V074();  virtual void V078();
  virtual void V07c();  virtual void V080();  virtual void V084();  virtual void V088();
  virtual void V08c();  virtual void V090();  virtual void V094();  virtual void V098();
  virtual void V09c();  virtual void V0a0();  virtual void V0a4();  virtual void V0a8();
  virtual void V0ac();  virtual void V0b0();  virtual void V0b4();  virtual void V0b8();
  virtual void V0bc();  virtual void V0c0();  virtual void V0c4();  virtual void V0c8();
  virtual void V0cc();  virtual void V0d0();  virtual void V0d4();  virtual void V0d8();
  virtual void V0dc(void* p);
  virtual void V0e0();  virtual void V0e4();  virtual void V0e8();  virtual void V0ec();
  virtual void V0f0();  virtual void V0f4();  virtual void V0f8();  virtual void V0fc();
  virtual void V100();  virtual void V104();
  virtual void V108(void* p);   // +0x108
  void F_fe7e10();              // 0x00fe7e10
};

class ILayout : public IWindow {
 public:
  IWindow* FindWindowByID(uint32_t id, int flag);  // 0x008105b0
  void Shutdown(uint32_t flag);                    // 0x00811ad0
};

class IGlobalUI : public IWindow {
 public:
  IWindow* FindWindowByID(uint32_t id);            // 0x00e012b0
};

// Only the vtable slot at +0x8 takes an argument here.
class IObj8Arg {
 public:
  virtual void V000();
  virtual void V004();
  virtual void V008(int flag);
};

// Only the vtable slot at +0xc takes an argument here.
class IObjCArg {
 public:
  virtual void V000();
  virtual void V004();
  virtual void V008();
  virtual void V00c(int flag);
};

// Cheat manager: slot +0x1c takes one argument.
class ICheatMgr {
 public:
  virtual void V000();  virtual void V004();  virtual void V008();  virtual void V00c();
  virtual void V010();  virtual void V014();  virtual void V018();
  virtual void V01c(uint32_t arg);
};

class IObj31c : public IWindow {
 public:
  void* mpField4;   // +0x4
};

// Refcounted helper: Release() is inlined as --mRef with a virtual slot-0 callback.
class IRefObj {
 public:
  virtual void OnRelease(int flag);  // +0x0
  volatile int32_t mRef;             // +0x4
  void F_e28a80();                   // 0x00e28a80
  int Release() {
    const int32_t ref = --mRef;
    if (ref == 0) {
      mRef = 1;
      OnRelease(1);
    }
    return ref;
  }
};

class CTooltip {
 public:
  virtual void OnRelease(int flag);  // +0x0
  volatile int32_t mRef;             // +0x4
  void Shutdown();                   // 0x00e36500
  int Release() {
    const int32_t ref = --mRef;
    if (ref == 0) {
      mRef = 1;
      OnRelease(1);
    }
    return ref;
  }
};

class Deque5ec {                     // eastl::deque<SP::cStarRecord*>
 public:
  void clear();                      // 0x00996460
 private:
  char mBytes[0x2c];
};

class Blk28Vec {                     // 0x28-byte element vector at +0x530
 public:
  uint32_t* mpBegin;                 // +0x0
  uint32_t* mpEnd;                   // +0x4
  uint32_t* mpCapacity;              // +0x8
  void erase(uint32_t* first, uint32_t* last);  // 0x0106eb40
};

// Inline sub-object at +0x2a0.
struct Space2a0 {
  void* mp0;                         // +0x2a0
  void* mp4;                         // +0x2a4
  uint32_t m8;                       // +0x2a8
  uint32_t mc;                       // +0x2ac
  float mf10;                        // +0x2b0
  float mf14;                        // +0x2b4
  char mRest[0x40];                  // +0x2b8 .. +0x2f7
  void F(void* a, uint32_t b);       // 0x01068400
};

class IGlobal0810 {
 public:
  void SetParent(void* p);           // 0x00dd2800
};

IGlobal0810* GetGlobal0810();        // 0x00dd1ca0

class CurMgr {
 public:
  bool FindLocal(uint32_t id);       // 0x00801bb0
};
CurMgr* GetCurMgr();                 // 0x0067cab0

bool IsWorldLayoutFlagSet(int flag); // 0x00685520
IWindow* FUN_00b3d230();             // 0x00b3d230
ICheatMgr* CheatManager();           // 0x0067de20

extern uint32_t g15b7330;            // 0x015b7330
extern IWindow* g16e2234;            // 0x016e2234

class cSPUISpace {
 public:
  cSPUISpace();                                               // 0x01070ba0
  void Shutdown();                                            // 0x01071570
  void FUN_0106f540();                                        // 0x0106f540
  void FUN_0106ef30();                                        // 0x0106ef30
  void FUN_01068230();                                        // 0x01068230
  void FUN_010673f0(int flag);                                // 0x010673f0
  void FUN_01067510(int flag);                                // 0x01067510

 private:
  template <class T>
  T& At(uint32_t off) { return *reinterpret_cast<T*>(reinterpret_cast<char*>(this) + off); }
  cString* Str(uint32_t off) { return reinterpret_cast<cString*>(reinterpret_cast<char*>(this) + off); }

 public:
  char mPad000[0x10];               // +0x000 (three vtable pointers + id)
  IObj8Arg* mp10;                   // +0x010
  char mPad014[0x210];              // +0x014 .. +0x223
  IGlobalUI* mpGlobalUI;            // +0x224
  IRefObj* mpRef228;                // +0x228
  ILayout* mpLayout22c;             // +0x22c
  ILayout* mpLayout230;             // +0x230
  ILayout* mpLayout234;             // +0x234
  char mPad238[0x20];               // +0x238 .. +0x257
  ILayout* mpLayout258;             // +0x258
  char mPad25c[0x44];               // +0x25c .. +0x29f
  Space2a0 m2a0;                    // +0x2a0
  int32_t m2f8;                     // +0x2f8
  IObjCArg* mp2fc;                  // +0x2fc
  IObjCArg* mp300;                  // +0x300
  IObjCArg* mp304;                  // +0x304
  char mPad308[0x14];               // +0x308 .. +0x31b
  IObj31c* mp31c;                   // +0x31c
  char mPad320[0x210];              // +0x320 .. +0x52f
  Blk28Vec mVec530;                 // +0x530
  char mPad53c[0x30];               // +0x53c .. +0x56b
  uint32_t m56c;                    // +0x56c
  uint32_t m570;                    // +0x570
  uint32_t m574;                    // +0x574
  uint32_t m578;                    // +0x578
  uint32_t m57c;                    // +0x57c
  IWindow* mp580;                   // +0x580
  IWindow* mp584;                   // +0x584
  IWindow* mp588;                   // +0x588
  char mPad58c[0xc];                // +0x58c .. +0x597
  IWindow* mp598;                   // +0x598
  IWindow* mp59c;                   // +0x59c
  IWindow* mp5a0;                   // +0x5a0
  IWindow* mp5a4;                   // +0x5a4
  CTooltip* mp5a8;                  // +0x5a8
  char mPad5ac[0x18];               // +0x5ac .. +0x5c3
  IWindow* mp5c4;                   // +0x5c4
  char mPad5c8[0x24];               // +0x5c8 .. +0x5eb
  Deque5ec mDeque5ec;               // +0x5ec
  char mPad618[0x8];                // +0x618, +0x61c
  char mPad620[0x74];               // +0x620 .. +0x693
  IWindow* mp694;                   // +0x694
};

// @ 0x01070ba0
cSPUISpace::cSPUISpace()
{
  At<uint32_t>(0x4) = 0x13ec458;
  At<uint32_t>(0x8) = 0;
  At<uint32_t>(0xc) = 0x13eb384;
  At<uint32_t>(0x0) = 0x149c3ec;
  At<uint32_t>(0x4) = 0x149c3dc;
  At<uint32_t>(0xc) = 0x149c3cc;
  At<uint32_t>(0x10) = 0;
  At<uint32_t>(0x18) = 0;
  Str(0x1c)->cString::cString();
  Str(0x30)->cString::cString();
  Str(0x44)->cString::cString();
  Str(0x58)->cString::cString();
  Str(0x6c)->cString::cString();
  Str(0x80)->cString::cString();
  Str(0x94)->cString::cString();
  Str(0xa8)->cString::cString();
  Str(0xbc)->cString::cString();
  Str(0xd0)->cString::cString();
  Str(0xe4)->cString::cString();
  Str(0xf8)->cString::cString();
  Str(0x10c)->cString::cString();
  Str(0x120)->cString::cString();
  Str(0x134)->cString::cString();
  Str(0x148)->cString::cString();
  Str(0x15c)->cString::cString();
  Str(0x170)->cString::cString();
  Str(0x184)->cString::cString();
  Str(0x198)->cString::cString();
  Str(0x1ac)->cString::cString();
  Str(0x1c0)->cString::cString();
  Str(0x1d4)->cString::cString();
  Str(0x1e8)->cString::cString();
  Str(0x1fc)->cString::cString();
  Str(0x210)->cString::cString();
  At<uint32_t>(0x224) = 0;
  At<uint32_t>(0x228) = 0;
  At<uint32_t>(0x22c) = 0;
  At<uint32_t>(0x230) = 0;
  At<uint32_t>(0x234) = 0;
  At<uint32_t>(0x238) = 0;
  At<uint32_t>(0x23c) = 0;
  At<uint32_t>(0x240) = 0;
  At<uint32_t>(0x244) = 0;
  At<uint32_t>(0x248) = 0;
  At<uint32_t>(0x254) = 0;
  At<uint32_t>(0x258) = 0;
  At<float>(0x26c) = ConstOne();
  At<float>(0x270) = ConstTwo();
  At<uint32_t>(0x268) = 0;
  At<uint32_t>(0x274) = 0;
  At<uint32_t>(0x264) = 0x1;
  At<uint32_t>(0x260) = 0x154df28;
  At<uint32_t>(0x27c) = 0;
  At<uint32_t>(0x280) = 0;
  At<uint32_t>(0x284) = 0;
  At<uint32_t>(0x294) = 0;
  At<uint32_t>(0x298) = 0;
  At<uint32_t>(0x29c) = 0;
  At<float>(0x2b0) = ConstOne();
  At<float>(0x2b4) = ConstTwo();
  At<uint32_t>(0x2a4) = 0x154df28;
  At<uint32_t>(0x2a8) = 0x1;
  At<uint32_t>(0x2ac) = 0;
  At<uint32_t>(0x2b8) = 0;
  At<uint32_t>(0x2c0) = 0;
  At<uint32_t>(0x2c4) = 0;
  At<uint32_t>(0x2c8) = 0;
  At<float>(0x2e4) = ConstOne();
  At<float>(0x2e8) = ConstTwo();
  At<uint32_t>(0x2d8) = 0x154df28;
  At<uint32_t>(0x2dc) = 0x1;
  At<uint32_t>(0x2e0) = 0;
  At<uint32_t>(0x2ec) = 0;
  At<uint32_t>(0x2f4) = 0x68e0210;
  At<uint32_t>(0x2f8) = 0xffffffff;
  At<uint32_t>(0x2fc) = 0;
  At<uint32_t>(0x300) = 0;
  At<uint32_t>(0x304) = 0;
  At<uint32_t>(0x308) = 0;
  At<uint32_t>(0x30c) = 0;
  At<uint32_t>(0x310) = 0;
  At<uint32_t>(0x31c) = 0;
  Str(0x324)->cString::cString();
  Str(0x338)->cString::cString();
  Str(0x34c)->cString::cString();
  Str(0x360)->cString::cString();
  Str(0x374)->cString::cString();
  Str(0x388)->cString::cString();
  Str(0x39c)->cString::cString();
  Str(0x3b0)->cString::cString();
  Str(0x3c4)->cString::cString();
  Str(0x3d8)->cString::cString();
  Str(0x3ec)->cString::cString();
  Str(0x400)->cString::cString();
  Str(0x414)->cString::cString();
  Str(0x428)->cString::cString();
  Str(0x43c)->cString::cString();
  Str(0x450)->cString::cString();
  Str(0x464)->cString::cString();
  Str(0x478)->cString::cString();
  Str(0x48c)->cString::cString();
  Str(0x4a0)->cString::cString();
  Str(0x4b4)->cString::cString();
  Str(0x4c8)->cString::cString();
  Str(0x4dc)->cString::cString();
  Str(0x4f0)->cString::cString();
  At<uint32_t>(0x504) = 0;
  At<uint32_t>(0x508) = 0;
  At<uint32_t>(0x50c) = 0;
  At<uint32_t>(0x518) = 0;
  At<uint32_t>(0x51c) = 0;
  At<uint32_t>(0x520) = 0;
  At<float>(0x52c) = ConstOne();
  At<uint32_t>(0x530) = 0;
  At<uint32_t>(0x534) = 0;
  At<uint32_t>(0x538) = 0;
  At<uint32_t>(0x56c) = 0;
  At<uint32_t>(0x570) = 0;
  At<uint32_t>(0x574) = 0;
  At<uint32_t>(0x578) = 0;
  At<uint32_t>(0x57c) = 0;
  At<uint32_t>(0x580) = 0;
  At<uint32_t>(0x584) = 0;
  At<uint32_t>(0x588) = 0;
  At<uint32_t>(0x58c) = 0;
  At<uint32_t>(0x590) = 0;
  At<uint32_t>(0x594) = 0;
  At<uint32_t>(0x598) = 0;
  At<uint32_t>(0x59c) = 0;
  At<uint32_t>(0x5a0) = 0;
  At<uint32_t>(0x5a4) = 0;
  At<uint32_t>(0x5a8) = 0;
  At<uint32_t>(0x5ac) = 0;
  At<uint32_t>(0x5b0) = 0;
  At<uint32_t>(0x5b4) = 0;
  At<uint32_t>(0x5b8) = 0;
  At<uint32_t>(0x5bc) = 0;
  At<uint32_t>(0x5c0) = 0;
  At<uint32_t>(0x5c4) = 0;
  At<uint32_t>(0x5c8) = 0;
  At<uint32_t>(0x5cc) = 2;
  At<uint8_t>(0x5d0) = 0;
  At<uint8_t>(0x5d1) = 0;
  At<uint8_t>(0x5d2) = 0;
  At<uint8_t>(0x5d3) = 0;
  At<uint8_t>(0x5d4) = 0;
  At<uint8_t>(0x5d5) = 1;
  At<uint32_t>(0x5d8) = 0;
  At<uint32_t>(0x5dc) = 0;
  At<uint32_t>(0x5e0) = 0;
  At<uint32_t>(0x5ec) = 0;
  At<uint32_t>(0x5f0) = 0;
  At<uint32_t>(0x5f4) = 0;
  At<uint32_t>(0x5f8) = 0;
  At<uint32_t>(0x5fc) = 0;
  At<uint32_t>(0x600) = 0;
  At<uint32_t>(0x604) = 0;
  At<uint32_t>(0x608) = 0;
  At<uint32_t>(0x60c) = 0;
  At<uint32_t>(0x610) = 0;

  reinterpret_cast<Callee5ec*>(reinterpret_cast<char*>(this) + 0x5ec)->Init(0);
  At<uint32_t>(0x618) = 0;
  At<uint32_t>(0x61c) = 0;
  reinterpret_cast<Callee620*>(reinterpret_cast<char*>(this) + 0x620)->Init();
  At<uint32_t>(0x694) = 0;
  At<uint32_t>(0x698) = 0;
  At<uint32_t>(0x69c) = 0;
  At<uint32_t>(0x6a0) = 0;
  UI::MissionCardAnimator* animator =
      new (reinterpret_cast<const char*>(0x013f6b3c), 0, 0, 0, 0) UI::MissionCardAnimator();
  At<UI::MissionCardAnimator*>(0x568) = animator;
  *reinterpret_cast<cSpaceTokenTranslator**>(0x016e0d08) =
      new ("Simulator", 0, 0, 0, 0) cSpaceTokenTranslator();
  GetVSlotsSingleton()->S8()->S7(*reinterpret_cast<cSpaceTokenTranslator**>(0x016e0d08));
  Str(0x324)->Load(0x2db6dad3, 0x539aa94, 0);
  Str(0x338)->Load(0x2db6dad3, 0x539aa95, 0);
  Str(0x34c)->Load(0x2db6dad3, 0x539aa96, 0);
  Str(0x360)->Load(0x2db6dad3, 0x539aa97, 0);
  Str(0x374)->Load(0x2db6dad3, 0x539aa98, 0);
  Str(0x388)->Load(0x2db6dad3, 0x539aae8, 0);
  Str(0x39c)->Load(0x2db6dad3, 0x61dfe83, 0);
  Str(0x3b0)->Load(0x2db6dad3, 0x3e81c64, 0);
  Str(0x3c4)->Load(0x2db6dad3, 0x3e98b08, 0);
  Str(0x3d8)->Load(0x2db6dad3, 0x63c3d96, 0);
  Str(0x3ec)->Load(0x2db6dad3, 0x6748f94, 0);
  Str(0x400)->Load(0x2db6dad3, 0x3e98b09, 0);
  Str(0x414)->Load(0x2db6dad3, 0x3e98b0a, 0);
  Str(0x43c)->Load(0x2db6dad3, 0x3eadfd0, 0);
  Str(0x450)->Load(0x2db6dad3, 0x3eafdd3, 0);
  Str(0x464)->Load(0x2db6dad3, 0x3ebf7a8, 0);
  Str(0x478)->Load(0x2db6dad3, 0x3edfdd4, 0);
  Str(0x4a0)->Load(0x2db6dad3, 0x4729a65, 0);
  Str(0x48c)->Load(0x2db6dad3, 0x3edfdd5, 0);
  Str(0x4c8)->Load(0x2db6dad3, 0x37c32cc, 0);
  Str(0x1c)->Load(0x63bfe3fe, 0x3ffe77b, 0);
  Str(0x30)->Load(0x63bfe3fe, 0x3ffe7fb, 0);
  Str(0x44)->Load(0x63bfe3fe, 0x3ffe7ff, 0);
  Str(0x58)->Load(0x63bfe3fe, 0x3ffe803, 0);
  Str(0x6c)->Load(0x63bfe3fe, 0x4374114, 0);
  Str(0x80)->Load(0x63bfe3fe, 0x4374125, 0);
  Str(0x94)->Load(0x63bfe3fe, 0x4377191, 0);
  Str(0xa8)->Load(0x63bfe3fe, 0x4377196, 0);
  Str(0xbc)->Load(0x63bfe3fe, 0x43ad9e0, 0);
  Str(0xd0)->Load(0x63bfe3fe, 0x43ad9f2, 0);
  Str(0xe4)->Load(0x2db6dad3, 0x654cb13, 0);
  Str(0xf8)->Load(0x2db6dad3, 0x654cb16, 0);
  Str(0x10c)->Load(0x2db6dad3, 0x654cb0a, 0);
  Str(0x120)->Load(0x2db6dad3, 0x654cb0f, 0);
  Str(0x134)->Load(0x2db6dad3, 0x43db6b2, 0);
  Str(0x148)->Load(0x2db6dad3, 0x43db6b1, 0);
  Str(0x15c)->Load(0x2db6dad3, 0x43db6b3, 0);
  Str(0x170)->Load(0x2db6dad3, 0x43db6b4, 0);
  Str(0x184)->Load(0x2db6dad3, 0x43db6b5, 0);
  Str(0x198)->Load(0x2db6dad3, 0x43db6b7, 0);
  Str(0x1ac)->Load(0x2db6dad3, 0x43db6b8, 0);
  Str(0x1e8)->Load(0x2db6dad3, 0x43db6b9, 0);
  Str(0x1c0)->Load(0x2db6dad3, 0x4c82968, 0);
  Str(0x1d4)->Load(0x2db6dad3, 0x510b24f, 0);
  Str(0x4b4)->Load(0x2db6dad3, 0x473d0cf, 0);
  Str(0x1fc)->Load(0xc0152a6d, 0x615ffa7, 0);
  Str(0x210)->Load(0xc0152a6d, 0x615ffa8, 0);
  Str(0x4dc)->Load(0x2db6dad3, 0x678eecf, 0);
  Str(0x4f0)->Load(0x2db6dad3, 0x678eed0, 0);
}

// @ 0x01071570
void cSPUISpace::Shutdown() {
  GetCurMgr()->FindLocal(0x1002);

  m2a0.F(m2a0.mp4, m2a0.m8);
  m2a0.mc = 0;

  if (IsWorldLayoutFlagSet(2)) {
    if (mp694) {
      if (mpLayout258) {
        IWindow* pWnd = mpLayout258->FindWindowByID(0x755f180, 1);
        if (pWnd->V028() & 1) mp694->F_fe7e10();
      }
      if (mp694) {
        IWindow* p = mp694;
        if (p) {
          mp694 = 0;
          p->V004();
        }
      }
    }
    ILayout* pLayout = mpLayout258;
    if (pLayout) {
      pLayout->Shutdown(1);
      ILayout* p = mpLayout258;
      if (p) {
        mpLayout258 = 0;
        p->V008();
      }
    }
  }

  FUN_0106f540();
  mDeque5ec.clear();
  IGlobal0810* pGlobal = GetGlobal0810();
  if (pGlobal) pGlobal->SetParent(0);
  mVec530.erase(mVec530.mpBegin, mVec530.mpEnd);
  FUN_0106ef30();
  FUN_01068230();

  {
    CTooltip* p = mp5a8;
    if (p) {
      p->Shutdown();
      CTooltip* q = mp5a8;
      if (q) {
        mp5a8 = 0;
        q->Release();
      }
    }
  }
  {
    IWindow* p = mp59c;
    if (p) {
      mp59c = 0;
      p->V004();
    }
  }
  {
    IWindow* p = mp598;
    if (p) {
      mp598 = 0;
      p->V004();
    }
  }
  {
    IWindow* p = mp5a0;
    if (p) {
      mp5a0 = 0;
      p->V004();
    }
  }

  mpRef228->F_e28a80();
  {
    IRefObj* p = mpRef228;
    if (p) {
      mpRef228 = 0;
      p->Release();
    }
  }

  {
    IWindow* p = mp580;
    if (p) {
      mp580 = 0;
      p->V004();
    }
  }

  mp5a4->V024();
  {
    IWindow* p = mp5a4;
    if (p) {
      mp5a4 = 0;
      p->V004();
    }
  }

  m2f8 = -1;
  if (mp10) {
    mp10->V008(1);
    mp10 = 0;
  }

  IWindow* pWindow = mpGlobalUI->FindWindowByID(0xffffffff);
  if (pWindow) {
    pWindow->V000();
    pWindow->V108(this);
  }

  FUN_00b3d230()->V044();

  if (g16e2234) {
    g16e2234->V008();
    g16e2234 = 0;
  }

  {
    ILayout* p = mpLayout22c;
    if (p) {
      p->Shutdown(1);
      ILayout* q = mpLayout22c;
      if (q) {
        mpLayout22c = 0;
        q->V008();
      }
    }
  }
  {
    ILayout* p = mpLayout230;
    if (p) {
      p->Shutdown(1);
      ILayout* q = mpLayout230;
      if (q) {
        mpLayout230 = 0;
        q->V008();
      }
    }
  }
  {
    ILayout* p = mpLayout234;
    if (p) {
      p->Shutdown(1);
      ILayout* q = mpLayout234;
      if (q) {
        mpLayout234 = 0;
        q->V008();
      }
    }
  }

  if (mp31c) {
    IWindow* pWnd = mpGlobalUI->FindWindowByID(0x190722e);
    if (pWnd) pWnd->V0dc(mp31c ? &mp31c->mpField4 : 0);
    mp31c->V01c();
    IObj31c* p = mp31c;
    if (p) {
      mp31c = 0;
      p->V004();
    }
  }

  {
    IObjCArg* p = mp2fc;
    if (p) {
      p->V00c(1);
      IObjCArg* q = mp2fc;
      if (q) {
        mp2fc = 0;
        q->V004();
      }
    }
  }
  {
    IObjCArg* p = mp300;
    if (p) {
      p->V00c(1);
      IObjCArg* q = mp300;
      if (q) {
        mp300 = 0;
        q->V004();
      }
    }
  }
  {
    IObjCArg* p = mp304;
    if (p) {
      p->V00c(1);
      IObjCArg* q = mp304;
      if (q) {
        mp304 = 0;
        q->V004();
      }
    }
  }

  if (mpGlobalUI) {
    mpGlobalUI->V00c();
    mpGlobalUI = 0;
  }

  if (m56c) {
    EA::Messaging::RemoveHandler(m56c, m570, m574, m578, m57c);
    m56c = 0;
  }

  CheatManager()->V01c(g15b7330);

  {
    IWindow* p = mp5c4;
    if (p) {
      p->V088();
      IWindow* q = mp5c4;
      if (q) {
        mp5c4 = 0;
        q->V004();
      }
    }
  }

  FUN_010673f0(0);
  FUN_01067510(0);

  {
    IWindow* p = mp588;
    if (p) {
      mp588 = 0;
      p->V004();
    }
  }
  {
    IWindow* p = mp584;
    if (p) {
      mp584 = 0;
      p->V0c0();
    }
  }

  if (pWindow) pWindow->V004();
}

}  // namespace SP
