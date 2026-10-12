// EA::RefCounted<Base, Counter, N>: the base's vptr plus a reference count (8 bytes, = dev).
// Hand-maintained.
#ifndef GAME_EA_REFCOUNTED_H
#define GAME_EA_REFCOUNTED_H
namespace EA {
template <typename Base, typename Counter, int N>
class RefCounted : public Base {
 public:
  Counter mRefCount;
};
}  // namespace EA
#endif
