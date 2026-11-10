// Slice s00c44bd0: one method of the game-object class around 0x00C44A20 (see slice s00c44a20).
// Register a second block of resource ids through the same vtable slot 0x150 (index 84).
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

#define PV(n) virtual void pv##n();
class GameObj {
public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
  PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
  PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
  PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
  PV(60) PV(61) PV(62) PV(63) PV(64) PV(65) PV(66) PV(67) PV(68) PV(69)
  PV(70) PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77) PV(78) PV(79)
  PV(80) PV(81) PV(82) PV(83)
  virtual void v84(uint32_t id);

  void RegisterIds_c44bd0();
};

// @ 0x00C44BD0
void GameObj::RegisterIds_c44bd0() {
  v84(0x35ec3de);
  v84(0x248975f);
  v84(0x2489760);
  v84(0x4249453);
}
