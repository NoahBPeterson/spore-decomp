// EA::RefCountTemplate<Counter>: a vptr (one slot: the virtual destructor) plus a reference count (8 bytes, = dev:
// EA::RefCountTemplate<int> and <EA::Thread::AtomicInt<int> > are size 8, vfptr, mRefCount at +4 in
// work/devbuild/types.json).  AddRef/Release are not virtual (dev functions EA::RefCountTemplate<int>::AddRef,
// <AtomicInt<int>>::Release).  Hand-maintained.  Retail layout and inlining unverified (no byte-exact user yet).
#ifndef GAME_EA_REFCOUNTTEMPLATE_H
#define GAME_EA_REFCOUNTTEMPLATE_H
namespace EA {
template <typename Counter>
class RefCountTemplate {
 public:
  virtual ~RefCountTemplate() {}
  int AddRef();
  int Release();
  Counter mRefCount;
};
}  // namespace EA
#endif
