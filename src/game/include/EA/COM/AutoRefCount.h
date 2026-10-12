// EA::COM::AutoRefCount<T>: one pointer (= dev).  Hand-maintained.
#ifndef GAME_EA_COM_AUTOREFCOUNT_H
#define GAME_EA_COM_AUTOREFCOUNT_H
namespace EA { namespace COM {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  T* get() const { return mpObject; }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
}}  // namespace EA::COM
#endif
