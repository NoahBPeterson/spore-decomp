// Havok 3.1.0 slice s010df100: hkListAgent (symmetric), hkPhantomAgent, hkTransformAgent (+ symmetric wrapper).
// Struct stubs carry members at the offsets seen in the 32-bit binary (pointer members make 64-bit sizes differ).
#pragma once
#include "types.h"
#include <stddef.h>
#include <intrin.h>

typedef float hkReal;
typedef float hkTime;
typedef uint8_t hkBool;

#define HK_REAL_MAX 3.40282e+38f     // 0x7f7fffee in this build

struct hkVector4 { float x, y, z, w; };
struct hkQuaternion {
    hkVector4 m_vec;
    void setMul(const hkQuaternion& a, const hkQuaternion& b);               // this = a * b
};
struct hkTransform {
    hkVector4 m_rot[3];                                                      // rows
    hkVector4 m_trans;
    void setMul(const hkTransform& a, const hkTransform& b);                 // this = a * b
};
struct hkContactPoint {
    hkVector4 m_position;
    hkVector4 m_separatingNormal;                                            // w = distance
    void setFlipped(const hkContactPoint& other);
};
struct hkProcessCdPoint { hkContactPoint m_contact; uint32_t m_extra[4]; };  // 0x30 bytes

// hkMotionState (0xb0 bytes): hkCdBody::m_motion points at one; its first member is the hkTransform.
struct hkMotionState {
    hkTransform m_transform;                                                 // +0
    hkVector4 m_centerOfMass0;                                               // +0x40
    hkVector4 m_centerOfMass1;                                               // +0x50
    hkQuaternion m_rotation0;                                                // +0x60
    hkQuaternion m_rotation1;                                                // +0x70
    hkVector4 m_centerOfMassLocal;                                           // +0x80
    uint32_t m_misc[7];                                                      // +0x90 .. 0xab (deltaAngle, objectRadius, ...)
    uint16_t m_h0;                                                           // +0xac
    uint16_t m_h1;                                                           // +0xae
    hkMotionState& operator=(const hkMotionState& other);                    // 0x010df5d0 (member-wise copy)
};

struct hkReferencedObject {
    virtual void* hkReferencedObject_deletingDtor(unsigned int flags);       // slot 0
    uint16_t m_memSizeAndFlags;
    int16_t  m_referenceCount;
};

// hkMemory::s_instance @0x016e4178
struct hkMemory {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void* allocateChunk(int nbytes, int memClass);                   // slot 4
    virtual void deallocateChunk(void* p, int nbytes, int memClass);         // slot 5
    static hkMemory* s_instance;
};
enum { HK_MEMORY_CLASS_COLLIDE = 0x1c };
#define HK_DECLARE_AGENT_ALLOCATOR(SIZE) \
    void* operator new(size_t n) { \
        void* p = hkMemory::s_instance->allocateChunk((int)n, HK_MEMORY_CLASS_COLLIDE); \
        ((hkReferencedObject*)p)->m_memSizeAndFlags = (uint16_t)n; return p; } \
    void operator delete(void*) {}

// ---- shapes ---------------------------------------------------------------------------------------
enum { HK_SHAPE_PHANTOM_CALLBACK = 0x1a };
struct hkCdBody;
struct hkCollisionInput;
struct hkShape : hkReferencedObject {
    uint32_t m_userData;                                                     // +8
    virtual void sh1();
    virtual int getType() const;                                             // slot 2 (+8)
};
struct hkPhantomCallbackShape : hkShape {
    virtual void sh3(); virtual void sh4(); virtual void sh5(); virtual void sh6();
    virtual void phantomEnterEvent(const hkCdBody* a, const hkCdBody* b, const hkCollisionInput* input);   // slot 7 (+0x1c)
    virtual void phantomLeaveEvent(const hkCdBody* a, const hkCdBody* b);                                  // slot 8 (+0x20)
};
struct hkTransformShape : hkShape {
    hkShape* m_childShape;                                                   // +0xc
    hkQuaternion m_rotation;                                                 // +0x10
    hkTransform m_transform;                                                 // +0x20
};

// ---- bodies / inputs / collectors -----------------------------------------------------------------------
struct hkCdBody {
    const hkShape* m_shape;                    // +0
    uint32_t m_shapeKey;                       // +4
    const hkMotionState* m_motion;             // +8
    const hkCdBody* m_parent;                  // +0xc
};
struct hkContactMgr;
struct hkCollisionDispatcher;
struct hkCollisionInput {
    hkCollisionDispatcher* m_dispatcher;       // +0
    uint32_t m_pad[2];
    hkBool m_createPredictiveAgents;           // +0xc (selects the predictive agent type table)
    uint8_t m_pad2[3];
};
struct hkProcessCollisionInput : hkCollisionInput {};
struct hkLinearCastCollisionInput : hkCollisionInput {
    hkVector4 m_path;                          // +0x10
    uint32_t m_pad3[4];                        // total 0x30 bytes
};
struct hkCdPoint { hkContactPoint m_contact; const hkCdBody* m_cdBodyA; const hkCdBody* m_cdBodyB; };
struct hkCdPointCollector {
    virtual void v0();
    virtual void addCdPoint(const hkCdPoint& point);
    float m_earlyOutDistance;                  // +4
};
struct hkCdBodyPairCollector {
    virtual void v0();
    virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b);       // slot 1 (+4)
    hkBool m_earlyOut;                         // +4
};
struct hkProcessCollisionOutput {
    hkProcessCdPoint* m_firstFreeContactPoint; // +0
    uint32_t m_pad0[3];
    hkContactPoint m_toiContact;               // +0x10
    hkProcessCdPoint m_contactPoints[256];     // +0x30
    uint32_t m_toiProperties;                  // +0x3030
    hkTime   m_toiTime;                        // +0x3034
};

// ---- collision agents (vtable slots as used by the transform agent) ------------------------------------
struct hkCollisionAgent : hkReferencedObject {
    hkContactMgr* m_contactMgr;                // +8
    virtual void ag1();
    virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);   // +8
    virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);     // +0xc
    virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);  // +0x10
    virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);  // +0x14
    virtual void cleanup();                                                                                            // +0x18
    virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&, const hkCollisionInput&);               // +0x1c
};

typedef hkCollisionAgent* (__cdecl *hkAgentCreateFunc)(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkContactMgr*);
typedef void (__cdecl *hkAgentGetPenetrationsFunc)(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
typedef void (__cdecl *hkAgentGetClosestPointsFunc)(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
typedef void (__cdecl *hkAgentLinearCastFunc)(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
struct hkAgentFuncs {                          // hkCollisionDispatcher::AgentFuncs (0x14 bytes in the 32-bit binary)
    hkAgentCreateFunc m_createFunc;            // +0
    hkAgentGetPenetrationsFunc m_getPenetrationsFunc;   // +4
    hkAgentGetClosestPointsFunc m_getClosestPointFunc;  // +8
    hkAgentLinearCastFunc m_linearCastFunc;    // +0xc
    hkBool m_isFlipped;                        // +0x10
    hkBool m_isPredictive;                     // +0x11
};
struct hkCollisionDispatcher {
    uint8_t m_pad0[0x190];                     // (32-bit layout)
    uint8_t m_agent2Types[32][32];             // +0x190: [typeA][typeB] -> agent index (non predictive)
    uint8_t m_agent2TypesPredictive[32][32];   // +0x590
    hkAgentFuncs m_agent2Func[1];              // +0x990, stride 0x14 in the binary
    void registerCollisionAgent(hkAgentFuncs& funcs, int typeA, int typeB);   // 0x010cd3e0
};

// ---- Havok monitor stream (timers).  TLS slot @0x016e42a4 = current write pointer, @0x016e42a8 = end.
#ifdef _WIN32
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
#endif
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorTimerEndTag[];           // string at 0x0149cc34 (end of a plain timer)
struct hkMonitorCommand { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_pad; };   // 12 bytes (32-bit)
#define HK_TIMER_COMMAND(name) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_commandAndMonitor = name; \
        c_->m_time0 = (uint32_t)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_BEGIN(name) HK_TIMER_COMMAND(name)
#define HK_TIMER_END()       HK_TIMER_COMMAND(hkMonitorTimerEndTag)
