// EA::SingletonBase<T, N>: an empty base (dev size 1) whose private static `spInstance` holds the one instance.  Hand-maintained.
// Dev evidence (work/devbuild/symbols.json): `?spInstance@?$SingletonBase@VcUIHints@@$0A@@EA@@0PAV12@A` (private static T*),
// `?Instance@?$SingletonBase@..@@SAPAV..@XZ` (public static, 6 bytes: load and return spInstance), and for
// SP::cStaticBufferDraw an 8-byte constructor and an 11-byte destructor (SPGraphicsStaticBufferDraw.obj): the constructor
// stores this, the destructor clears it.  Round 7 (fix pass 5): SP/cStaticBufferDraw.h derives from it.  Unverified in retail.
#ifndef GAME_EA_SINGLETONBASE_H
#define GAME_EA_SINGLETONBASE_H
namespace EA {
template <typename T, int N>
class SingletonBase {
 public:
  static T* Instance() { return spInstance; }
  SingletonBase() { spInstance = (T*)this; }
  ~SingletonBase() { spInstance = 0; }
 private:
  static T* spInstance;
};
template <typename T, int N> T* SingletonBase<T, N>::spInstance = 0;
}  // namespace EA
#endif
