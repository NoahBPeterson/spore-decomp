// @ 0x00b815a0
// SP::cPlanetModel::DirectionToSurfacePosition
//   retail: ?DirectionToSurfacePosition@cPlanetModel@@QBEPAUcSPVector3@@PAU3@PBU3@@Z
//   (the generated cPlanetModel.h still carries the dev-PDB by-value overload, so the
//    retail signature is declared here rather than by editing the shared header)
#include "game/types.h"
#include "cSPVector3.h"

#include <math.h>

extern const float kVectorEpsilon;

namespace SP {

struct Quat {
  float x, y, z, w;
};

// The terrain sphere carries the local surface frame; 0x0156b614 supplies the
// fixed reference orientation when no sphere is attached to the planet model.
struct cTerrainSphere {
  // retail returns cSPQuaternion by value; the hidden return pointer is spelled
  // out here so the call site keeps that shape.
  void BuildSurfaceOrientation(Quat * out, cSPVector3 const & dir,
                               Quat const & ref) const;  // 0x00f9c960
};

void RandomDirection3(float * out);                                             // 0x00b7e560
void QuaternionFromDirections(float * out, const float * from, const float * to);  // 0x00698180
void Matrix3FromQuaternion(float * out, const float * q);                       // 0x0059c190
extern const float kOne;                                                        // 0x01485720 (1.0f)
extern const float kRefDirection[3];                                            // 0x01688278
extern const Quat kDefaultOrientation;                                          // 0x0156b614

class cPlanetModel {
 public:
  char pad0[0x20];
  cTerrainSphere * mpSphere;  // +0x20
  int mpISphere;              // +0x24

  float GetRadiusAt(cSPVector3 const &) const;
  float GetRadiusAt(cSPVector3 const * dir) const;
  cSPVector3 * DirectionToSurfacePosition(cSPVector3 *, cSPVector3 const *) const;
  int IsPositionBelowSurface(cSPVector3 const * dir) const;
  void FUN_00b81a40(cSPVector3 * out, cSPVector3 const * dir, float a, float b);
};

// Normalise dir, then push it out to the surface radius.  The normalised direction
// is kept in a local three-float array (retail keeps the three products in
// xmm2/xmm0/xmm1 and the radius in xmm3 while the sum is built on the x87 stack).
cSPVector3 * cPlanetModel::DirectionToSurfacePosition(cSPVector3 * out,
                                                      cSPVector3 const * dir) const {
  float radius = GetRadiusAt(*dir);
  float inv = 1.0f / sqrtf(dir->x * dir->x + dir->y * dir->y + dir->z * dir->z +
                            kVectorEpsilon);
  float v[3];
  v[0] = dir->x * inv;
  v[1] = dir->y * inv;
  v[2] = dir->z * inv;
  out->x = v[0] * radius;
  out->y = v[1] * radius;
  out->z = v[2] * radius;
  return out;
}

} // namespace SP
