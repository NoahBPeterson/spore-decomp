// EA::Thread::AtomicInt<T>: one value (= dev).  Hand-maintained.
// The constructor stores the initial value with an interlocked exchange (`xchg [this], reg`), as the inlined Resource
// constructor of cPropertyList (0x6a1b90, byte-exact in s006a11b0) and the slice's own AtomicInt do; a plain store gives
// `mov [this], 0`.  Layout unchanged (one value).
#ifndef GAME_EA_THREAD_ATOMICINT_H
#define GAME_EA_THREAD_ATOMICINT_H
extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)
namespace EA { namespace Thread {
template <typename T>
class AtomicInt {
 public:
  volatile T mValue;
  AtomicInt(T n = 0) { SetValue(n); }
  void SetValue(T n) { _InterlockedExchange((long*)&mValue, n); }
};
}}  // namespace EA::Thread
#endif
