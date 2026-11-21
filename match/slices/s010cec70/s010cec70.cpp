// Slice s010cec70 -- Havok 3.1.0 symmetric-agent wrappers: each runs its agent's processCollision with
// the two bodies swapped, flips the contact points it added and negates the separating normal when the
// cached distance changed.  Same code as hkAgentWrapper::FUN_010cfd30 (slice s010cfcf0), one per agent.
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP

class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };
class hkCdBody;
struct hkCollisionInput { int pad[2]; float m_tolerance; };
struct hkProcessCollisionInput : hkCollisionInput { };
class hkContactPoint {
public:
    hkVector4 m_position;
    hkVector4 m_separatingNormal;
    void setFlipped(const hkContactPoint& other);  // 0x010cecf0
};
typedef unsigned short hkContactPointId;
struct hkProcessCdPoint { hkContactPoint m_contact; hkContactPointId m_id; char m_pad[14]; };  // 0x30 bytes
struct hkProcessCollisionOutput
{
    hkProcessCdPoint* m_firstFreeContactPoint;  // +0x00
    char              m_padding4[0x1c];         // +0x04
    float             m_separatingNormal[3];    // +0x20
    char              m_padding2c[0x3008];      // +0x2c
    float             m_cachedDistance;         // +0x3034
};

#define HK_AGENT_PROCESS(Agent)                                                                  \
    class Agent {                                                                                \
    public:                                                                                      \
        virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,              \
                                      const hkProcessCollisionInput& input,                      \
                                      hkProcessCollisionOutput& output);                         \
    };

#define HK_SYMMETRIC_PROCESS(Wrapper, Agent)                                                     \
    void Wrapper::processCollision(void* a1, void* a2, void* a3, void* a4)                      \
    {                                                                                            \
        hkProcessCollisionOutput& output = *(hkProcessCollisionOutput*)a4;                       \
        const float oldDistance = output.m_cachedDistance;                                       \
        hkProcessCdPoint* point = output.m_firstFreeContactPoint;                                \
                                                                                                 \
        ((Agent*)this)->Agent::processCollision(                                                 \
            *(const hkCdBody*)a2, *(const hkCdBody*)a1,                                          \
            *(const hkProcessCollisionInput*)a3, output);                                        \
                                                                                                 \
        while (point < output.m_firstFreeContactPoint) {                                         \
            hkContactPoint* contact = &point->m_contact;                                         \
            contact->setFlipped(*contact);                                                       \
            point = (hkProcessCdPoint*)((char*)point + 0x30);                                    \
        }                                                                                        \
                                                                                                 \
        if (oldDistance != output.m_cachedDistance) {                                            \
            output.m_separatingNormal[0] = -output.m_separatingNormal[0];                        \
            output.m_separatingNormal[1] = -output.m_separatingNormal[1];                        \
            output.m_separatingNormal[2] = -output.m_separatingNormal[2];                        \
        }                                                                                        \
    }

// agent processCollision at 0x010cdd30
HK_AGENT_PROCESS(hkAgent_010cec70)
struct hkSymmetricAgent_010cec70 { void processCollision(void* a1, void* a2, void* a3, void* a4); };
// 0x010cec70 (bound by the manifest row)
HK_SYMMETRIC_PROCESS(hkSymmetricAgent_010cec70, hkAgent_010cec70)

// agent processCollision at 0x010d28c0
HK_AGENT_PROCESS(hkAgent_010d4170)
struct hkSymmetricAgent_010d4170 { void processCollision(void* a1, void* a2, void* a3, void* a4); };
// 0x010d4170 (bound by the manifest row)
HK_SYMMETRIC_PROCESS(hkSymmetricAgent_010d4170, hkAgent_010d4170)

// agent processCollision at 0x010d7710
HK_AGENT_PROCESS(hkAgent_010d88c0)
struct hkSymmetricAgent_010d88c0 { void processCollision(void* a1, void* a2, void* a3, void* a4); };
// 0x010d88c0 (bound by the manifest row)
HK_SYMMETRIC_PROCESS(hkSymmetricAgent_010d88c0, hkAgent_010d88c0)

// agent processCollision at 0x010de110
HK_AGENT_PROCESS(hkAgent_010de760)
struct hkSymmetricAgent_010de760 { void processCollision(void* a1, void* a2, void* a3, void* a4); };
// 0x010de760 (bound by the manifest row)
HK_SYMMETRIC_PROCESS(hkSymmetricAgent_010de760, hkAgent_010de760)

// agent processCollision at 0x010de9e0
HK_AGENT_PROCESS(hkAgent_010df040)
struct hkSymmetricAgent_010df040 { void processCollision(void* a1, void* a2, void* a3, void* a4); };
// 0x010df040 (bound by the manifest row)
HK_SYMMETRIC_PROCESS(hkSymmetricAgent_010df040, hkAgent_010df040)

// agent processCollision at 0x010e3430
HK_AGENT_PROCESS(hkAgent_010e53d0)
struct hkSymmetricAgent_010e53d0 { void processCollision(void* a1, void* a2, void* a3, void* a4); };
// 0x010e53d0 (bound by the manifest row)
HK_SYMMETRIC_PROCESS(hkSymmetricAgent_010e53d0, hkAgent_010e53d0)

// agent processCollision at 0x010e5630
HK_AGENT_PROCESS(hkAgent_010e6850)
struct hkSymmetricAgent_010e6850 { void processCollision(void* a1, void* a2, void* a3, void* a4); };
// 0x010e6850 (bound by the manifest row)
HK_SYMMETRIC_PROCESS(hkSymmetricAgent_010e6850, hkAgent_010e6850)

