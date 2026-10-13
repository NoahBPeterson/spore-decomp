// EA::RefCountVTemplate<Counter>: a vptr plus a reference count (8 bytes, = dev: EA::RefCountVTemplate<EA::Thread::AtomicInt<int> >
// is size 8, vfptr, mRefCount at +4 in work/devbuild/types.json).  Virtual slots as in its derived classes' vtables
// (EA::SharedLibrary vtable 0x143ea00: slot 0 destructor, 1 AddRef 0x8dd1b0, 2 Release 0x8dd1c0, 3 GetRefCount 0x59d930).
// Hand-maintained.  Retail layout unverified (no byte-exact user yet).
#ifndef GAME_EA_REFCOUNTVTEMPLATE_H
#define GAME_EA_REFCOUNTVTEMPLATE_H
namespace EA {
template <typename Counter>
class RefCountVTemplate {
 public:
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  virtual int GetRefCount() const;
  Counter mRefCount;
};
}  // namespace EA
#endif
