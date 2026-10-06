// Shadows EAThread's std::atomic-based AtomicInt (C++11, not in VS2008) so eathread_atomic.h uses its
// own Interlocked-based fallback implementation, the pre-C++11 style.
#pragma once
