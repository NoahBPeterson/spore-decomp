// rw::core::thread::AtomicInt<T>: one value (dev: AtomicInt<int>/<unsigned int> 4 bytes, <__int64>/<unsigned __int64> 8,
// a single member mValue at +0).  Hand-maintained.  Round 7 (fix pass 5): RwConditionData::mnWaitersBlocked needs it
// (SPAudio/AudioSystem.obj closure).  The dev PDB gives no member functions for the rw flavour; none are declared here,
// so code that constructs one through a dev method needs evidence first.  Unverified in retail.
#ifndef GAME_RW_CORE_THREAD_ATOMICINT_H
#define GAME_RW_CORE_THREAD_ATOMICINT_H
namespace rw { namespace core { namespace thread {
template <typename T>
class AtomicInt {
 public:
  T mValue;
};
}}}  // namespace rw::core::thread
#endif
