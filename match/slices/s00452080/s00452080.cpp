// slice s00452080 -- SP::cSPEditorBlock::BuildNewPhysicsShape (4555 bytes).
// MARKED PARTIAL: the full Havok shape construction (hkRigidBodyCinfo, box
// shapes, child recursion) is only outlined here.
#include "types.h"

struct cSPEditorBlock;

struct cSPEditorBlock {
    // @ 0x00452080
    void* BuildNewPhysicsShape();
};

// @ 0x00452080
void* cSPEditorBlock::BuildNewPhysicsShape() {
    // Full body (~4.5 KB) not reconstructed: builds an hkRigidBodyCinfo,
    // computes the block bounding box, attaches box shapes for each collision
    // primitive and recurses over children.
    return 0;
}
