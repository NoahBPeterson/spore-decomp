// @ 0x00c69a70
// SP::cEgg::GetFieldValues -- the fields cGameData contributes, then those of the egg's spatial object
// (+0x34) and of the egg itself, the last two through a cVarListSerializer each.  Returns the number of
// fields written by all three.
//
// The generated SP/cEgg.h lays its bases out at the dev offsets (SP::cSpatialObject at +0x2c because it
// gives SP::cGameData the dev size 0x2c); retail has cSpatialObject at +0x34 (cGameData's declared retail
// size, and slice s00c69a00 has cEgg::AsInterface reaching it), so the extents below are the retail ones.
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "game/types.h"
#include "SP/cVarListSerializer.h"

// Serializer tables of the two objects (each a data blob in retail, not a readable pointer).
extern char kSpatialObjectSerializerList[];  // 0x0157a1f8
extern char kEggSerializerList[];            // 0x01578f0

namespace SP {

typedef eastl::vector<SP::cField, eastl::sp_vector_allocator> tFieldVector;

// SP::cGameData as cEgg stores it in retail: 0x34 bytes, with GetFieldValues the base implementation the
// egg overrides.
class cGameData {
 public:
  int GetFieldValues(tFieldVector &fields);  // 0x00b18420

 private:
  unsigned char mGameData[0x34];
};

// SP::cSpatialObject, of which cEgg::GetFieldValues needs only the extent: retail places it at +0x34.
class cSpatialObject {
 private:
  unsigned char mSpatialObject[0xd4];
};

// SP::cEgg at its retail extents.
class cEgg : public cGameData {
 public:
  int GetFieldValues(tFieldVector &fields);

 private:
  cSpatialObject mSpatialObject;  // +0x34
};

int cEgg::GetFieldValues(tFieldVector &fields)
{
  int count = cGameData::GetFieldValues(fields);

  cVarListSerializer spatialSerializer(&mSpatialObject,
                                      reinterpret_cast<cDataSerializerGeneric *>(kSpatialObjectSerializerList),
                                      cVarListSerializer::kSignature);
  count += spatialSerializer.GetFields(fields);

  cVarListSerializer eggSerializer(this,
                                   reinterpret_cast<cDataSerializerGeneric *>(kEggSerializerList),
                                   cVarListSerializer::kSignature);
  return eggSerializer.GetFields(fields) + count;
}

}  // namespace SP
