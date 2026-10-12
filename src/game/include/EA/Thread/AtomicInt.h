// EA::Thread::AtomicInt<T>: one value (= dev).  Hand-maintained.
#ifndef GAME_EA_THREAD_ATOMICINT_H
#define GAME_EA_THREAD_ATOMICINT_H
namespace EA { namespace Thread {
template <typename T>
class AtomicInt {
 public:
  volatile T mValue;
};
}}  // namespace EA::Thread
#endif
