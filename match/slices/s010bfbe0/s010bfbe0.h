// Havok 3.1.0 slice s010bfbe0: solver keycode check, hkConvexTranslateShape, hkAabbUtil::calcAabb, hkBoxShape. Struct stubs carry members at the offsets of the 32-bit
// binary (comments give the 32-bit offset); pointer members make 64-bit offsets differ.
#pragma once
#include "../s0107e670/hk31_base.h"
#include <new>
#if defined(_MSC_VER)
#include <intrin.h>
#define HK_RDTSC32() ((hkUint32)__rdtsc())
#else
#define HK_RDTSC32() ((hkUint32)__builtin_ia32_rdtsc())
#endif

// Value the binary keeps on the x87 stack without storing. X87-PRECISION: switch to float / long double to experiment.
typedef double hkX87Real;

// ---- monitor stream (HK_TIMER_BEGIN / HK_TIMER_END). TLS @0x016e42a4 = current pointer, @0x016e42a8 = end.
// TlsGetValue / TlsSetValue come from hk31_base.h (non-Windows builds supply their own thread-local shim).
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorTimerEndTag[];           // "Et" at 0x0149cc34
struct hkMonitorCommand { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_pad; };   // 12 bytes (32-bit)
#define HK_TIMER_COMMAND(name) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_commandAndMonitor = name; \
        c_->m_time0 = HK_RDTSC32(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_BEGIN(name) HK_TIMER_COMMAND(name)
#define HK_TIMER_END()       HK_TIMER_COMMAND(hkMonitorTimerEndTag)

// Raw (no destructor) array view used where the binary frees the buffer by hand.
template <typename T>
struct hkArrayPOD
{
    T* m_data; int m_size; int m_capacityAndFlags;
    int indexOf(const T& t) const { int i = 0; while (i < m_size) { if (m_data[i] == t) return i; ++i; } return -1; }
    void freeBuffer(int elemSize)
    {
        if (m_capacityAndFlags >= 0)
            hkThreadMemory::getInstance().deallocateChunk(m_data, (m_capacityAndFlags & 0x3fffffff) * elemSize, HK_MEMORY_CLASS_ARRAY);
    }
    void pushBack(const T& t)
    {
        if (m_size == (m_capacityAndFlags & 0x3fffffff)) hkArrayUtil::_reserveMore(this, (int)sizeof(T));
        m_data[m_size] = t;
        m_size = m_size + 1;
    }
};

// ---- allocator helper (HK_DECLARE_CLASS_ALLOCATOR): memSize is stored at +4 of the object (after the vptr)
#define HK_DECLARE_CLASS_ALLOCATOR_B(cls) \
    static void* operator new(size_t n) { void* p = hkMemory::s_instance->allocateChunk((int)n, cls); \
        ((hkReferencedObject*)p)->m_memSizeAndFlags = (hkInt16)n; return p; } \
    static void operator delete(void* p) { hkMemory::s_instance->deallocateChunk(p, ((hkReferencedObject*)p)->m_memSizeAndFlags, cls); } \
    static void* operator new(size_t, void* p) { return p; } \
    static void operator delete(void*, void*) {}
