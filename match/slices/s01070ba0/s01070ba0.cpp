// Slice s01070ba0: SP::cSPUISpace::cSPUISpace (0x01070ba0, 2475 bytes).
// Generated from the disassembly in work/match/scratch_s01070ba0_card.txt (store order preserved).
// Flags: /O2 /MD /Gy /EHsc /TP. Retail layout: cString is 0x14 bytes, so fields are accessed by offset.
#include "types.h"

// Six-argument operator new (0x00f473a0, cdecl): size, tag, four zero flags; caller pops 0x18.
void* operator new(unsigned int size, const char* tag, int a, int b, int c, int d);

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

class cSPUISpace {
 public:
  cSPUISpace();                                               // 0x01070ba0

 private:
  template <class T>
  T& At(uint32_t off) { return *reinterpret_cast<T*>(reinterpret_cast<char*>(this) + off); }
  cString* Str(uint32_t off) { return reinterpret_cast<cString*>(reinterpret_cast<char*>(this) + off); }
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

}  // namespace SP
