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
  // Assignment as retail inlines it (DatabasePackedFile::CloseInternal 0x8d94a0 / Attach: `mpStream = 0` is
  // `mov ecx,[this]; test ecx,ecx; je; mov [this],0; call [vtbl+8]` = Release of the old object after the store;
  // the new object is AddRef'd first when it is not null).  Evidence: byte-exact slice s008d81d0/s008d91e0 AutoRef.
  AutoRefCount& operator=(T* q) {
    T* old = mpObject;
    if (q != old) {
      if (q) q->AddRef();
      mpObject = q;
      if (old) old->Release();
    }
    return *this;
  }
};
}}  // namespace EA::COM
#endif
