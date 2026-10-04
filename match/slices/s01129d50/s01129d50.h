// Havok 3.1.0 slice s01129d50: hkDisableEntityCollisionFilter, hkDashpotAction, hkConstrainedSystemFilter,
// hkAngularDashpotAction, hkBinaryPackfileReader. Struct stubs carry members at the offsets of the 32-bit
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

struct hkQuaternion
{
    float x, y, z, w;
    void setMul(const hkQuaternion& a, const hkQuaternion& b);   // 0x01082210: this = a * b
};

struct hkStepInfo { float m_startTime; float m_endTime; float m_deltaTime; float m_invDeltaTime; };   // deltaTime @+8

// ---- bodies ---------------------------------------------------------------------------------------------------
class hkMotion
{
public:
    virtual ~hkMotion() {}                                                           // 0
    virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();  // 1..4
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
    virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23();                      // ..23
    virtual void applyLinearImpulse(const hkVector4& imp);                            // 24
    virtual void applyPointImpulse(const hkVector4& imp, const hkVector4& point);     // 25 (+0x64)
    virtual void applyAngularImpulse(const hkVector4& imp);                           // 26 (+0x68)

    hkInt16 m_memSizeAndFlags;     // +0x04
    hkInt16 m_referenceCount;      // +0x06
    uint32_t m_solverData;         // +0x08
    uint32_t m_pad0c;              // +0x0c
    hkTransform m_transform;       // +0x10 (motion state transform)
    uint32_t m_pad50[12];          // +0x50..+0x7f (rest of the motion state's first half)
    hkQuaternion m_rotation;       // +0x80 (motion state rotation)
    uint32_t m_pad90[16];          // +0x90..+0xcf
    hkVector4 m_linearVelocity;    // +0xd0
    hkVector4 m_angularVelocity;   // +0xe0
};

// ---- allocator helper (HK_DECLARE_CLASS_ALLOCATOR): memSize is stored at +4 of the object (after the vptr)
#define HK_DECLARE_CLASS_ALLOCATOR_B(cls) \
    static void* operator new(size_t n) { void* p = hkMemory::s_instance->allocateChunk((int)n, cls); \
        ((hkReferencedObject*)p)->m_memSizeAndFlags = (hkInt16)n; return p; } \
    static void operator delete(void* p) { hkMemory::s_instance->deallocateChunk(p, ((hkReferencedObject*)p)->m_memSizeAndFlags, cls); } \
    static void* operator new(size_t, void* p) { return p; } \
    static void operator delete(void*, void*) {}
