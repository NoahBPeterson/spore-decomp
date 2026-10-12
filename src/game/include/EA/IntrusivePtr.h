// EA::IntrusivePtr<T>: one pointer.  Hand-maintained.
#ifndef GAME_EA_INTRUSIVEPTR_H
#define GAME_EA_INTRUSIVEPTR_H
namespace EA {
template <typename T>
class IntrusivePtr {
 public:
  T* mpObject;
  T* operator->() const { return mpObject; }
};
}  // namespace EA
#endif
