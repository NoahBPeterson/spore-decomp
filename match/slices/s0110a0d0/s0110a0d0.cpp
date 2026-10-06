// Slice s0110a0d0 -- Havok 3.1.0 hkBoxBoxCollisionDetection manifold/validation helpers.
//
// These six functions are the box-box contact-manifold builders (feature-index ->
// validation-data mapping, the 956-byte manifold setup and the 713-byte
// addAdditionalEdgeHelper). The float-heavy x87 bodies were not reconstructed in
// full; the smaller dispatcher is approximated. See partial.txt.
#include "types.h"

struct hkFeaturePointCache {};
struct hkBoxBoxManifold {};
struct hkFeatureContactPoint {};

struct hkBoxBoxCollisionDetection
{
    void faceAVertexBValidationDataFromFeatureIndex(hkFeaturePointCache& c, int featureIndex) const {}
    void faceBVertexAValidationDataFromFeatureIndex(hkFeaturePointCache& c, int featureIndex) const {}
    void edgeEdgeValidationDataFromFeatureIndex(hkFeaturePointCache& c) const {}
    void addAdditionalEdgeHelper(hkBoxBoxManifold& m, hkFeatureContactPoint& p, float f) const {}
};

void FUN_01108750(void* a, void* b);

// @ 0x0110a0d0  hkBoxBoxCollisionDetection::faceAVertexBValidationDataFromFeatureIndex
// partial: 480-byte x87 feature validation build-up not reproduced.

// @ 0x0110a2b0  hkBoxBoxCollisionDetection::faceBVertexAValidationDataFromFeatureIndex
// partial: 508-byte x87 feature validation build-up not reproduced.

// @ 0x0110a4b0  hkBoxBoxCollisionDetection::edgeEdgeValidationDataFromFeatureIndex
// partial: 326-byte x87 edge validation build-up not reproduced.

// @ 0x0110a600  box-box manifold setup (956 bytes)
// partial: not reproduced.
void FUN_0110a600() {}

// @ 0x0110a9c0  hkBoxBoxCollisionDetection::addAdditionalEdgeHelper
// partial: 713-byte additional-edge helper not reproduced.

// @ 0x0110ac90  additional-edge fan-out dispatcher (224 bytes)
void FUN_0110ac90(hkBoxBoxCollisionDetection* self, unsigned short bits, hkBoxBoxManifold& m,
                  void* a3, void* a4, int p5, int p6, void* a7, void* a8, float f)
{
    unsigned int local = bits;
    FUN_01108750(a3, a4);
    self->addAdditionalEdgeHelper(m, *(hkFeatureContactPoint*)&local, f);

    char c1 = (p5 == 0) ? 3 : (char)((p5 == 1) + 1);
    char c3 = (p6 == 0) ? 3 : (char)((p6 == 1) + 1);

    unsigned char b4 = (unsigned char)(1 << (c1 + 4));
    local = (local & 0xffffff00u) | (unsigned char)((unsigned char)local ^ b4);
    self->addAdditionalEdgeHelper(m, *(hkFeatureContactPoint*)&local, f);

    unsigned char b2 = (unsigned char)(((local >> 8) & 0xff) ^ (unsigned char)(1 << (c3 + 4)));
    local = (local & 0xffff0000u) | (unsigned int)(unsigned char)local | ((unsigned int)b2 << 8);
    self->addAdditionalEdgeHelper(m, *(hkFeatureContactPoint*)&local, f);

    local = (local & 0xffffff00u) | (unsigned char)((unsigned char)local ^ b4);
    self->addAdditionalEdgeHelper(m, *(hkFeatureContactPoint*)&local, f);
}
