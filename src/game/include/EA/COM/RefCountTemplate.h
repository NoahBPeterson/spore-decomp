// EA::COM::RefCountTemplate<Counter>: a vptr (one slot: the virtual destructor) plus a reference count (8 bytes, = dev:
// EA::COM::RefCountTemplate<int> and <EA::Thread::AtomicInt<int> > are size 8, vfptr, mRefCount at +4 in
// work/devbuild/types.json; EA::Internet::HTTPResponse's dev vtable for it has 1 slot).  Hand-maintained.
// Retail layout and inlining unverified (no byte-exact user yet).
#ifndef GAME_EA_COM_REFCOUNTTEMPLATE_H
#define GAME_EA_COM_REFCOUNTTEMPLATE_H
namespace EA { namespace COM {
template <typename Counter>
class RefCountTemplate {
 public:
  virtual ~RefCountTemplate() {}
  int AddRef();
  int Release();
  Counter mRefCount;
};
}}  // namespace EA::COM
#endif
