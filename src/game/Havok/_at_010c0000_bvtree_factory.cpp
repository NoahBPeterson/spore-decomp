// Havok 3.1.0 tree-stream agent factory. Kept separate from the mixed-compiler
// migrated translation unit so this factory can use its original VC7.1 profile.
#include "../../../match/slices/s010e1340/hk31_agents.h"

class hkBvTreeStreamAgent_s010c_eb50 : public hkCollisionAgent
{
public:
    static hkCollisionAgent* createShapeBvAgent(const hkCdBody& bodyA,
        const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr);

    virtual void getPenetrations(const hkCdBody&, const hkCdBody&,
        const hkCollisionInput&, hkCdBodyPairCollector&);
    virtual void getClosestPoints(const hkCdBody&, const hkCdBody&,
        const hkCollisionInput&, hkCdPointCollector&);
    virtual void linearCast(const hkCdBody&, const hkCdBody&,
        const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
    virtual void processCollision(const hkCdBody&, const hkCdBody&,
        const hkProcessCollisionInput&, hkProcessCollisionOutput&);
    virtual void cleanup();
    virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&,
        const hkCollisionInput&);

protected:
    // 0x010ceaf0: ECX receiver, four stack arguments, ret 16.
    // The address suffix keeps this view separate from the legacy partial class.
    hkBvTreeStreamAgent_s010c_eb50(const hkCdBody&, const hkCdBody&,
        const hkCollisionInput&, hkContactMgr*); // 0x010ceaf0
    unsigned int m_dispatcherData;       // +0x0c
    unsigned int m_agentState[8];        // +0x10..+0x2f
    hkArray<void*> m_agents;             // +0x30
    void* m_agentStorage[1];             // +0x3c
};
typedef char hkBvTreeStreamAgent_s010c_eb50_size_check[sizeof(hkBvTreeStreamAgent_s010c_eb50) == 0x40 ? 1 : -1];

// @ 0x010ceb50
hkCollisionAgent* hkBvTreeStreamAgent_s010c_eb50::createShapeBvAgent(const hkCdBody& bodyA,
    const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr)
{
    return new hkBvTreeStreamAgent_s010c_eb50(bodyA, bodyB, input, mgr);
}
