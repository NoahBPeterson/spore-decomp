// slice s00d30990 -- loads the creature-input tunables out of the game's property list.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (no /EHsc).
//
// The reader asks its owner (vtable slot 0x18) for the live property list, then copies
// every tunable it knows about into the writable .data globals of the creature-input
// module (g_StopMaxDistance, sPickBoxMaxScale, ...).  Each entry is independent: the
// property is looked up by its 32-bit id (vtable slot 0x24 of the list), the variant's
// type tag is checked against the expected type and only then is the value stored, so a
// missing or mistyped property leaves the previous value alone.  The list is released at
// the end.  A null list is tolerated (the guards past the first lookup), which is what
// the retail code's repeated null tests followed by the shared epilogue are.
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2

namespace SP {

// EA::Variant as it is named in the debug database ("Property"): the type tag lives at
// +0x12, the typed accessors are out-of-line members.
struct Variant {
  enum {
    kTypeBool = 1,
    kTypeUint32 = 10,
    kTypeFloat = 13,
  };

  unsigned char mStorage[0x10];
  unsigned short mFlags;    // 0x010
  unsigned short mTypeId;   // 0x012

  float* GetFloat();            // 0x0041ea70
  bool* GetBool();              // 0x0041e920
  unsigned int* GetUInt();      // 0x0041ea00
};

class cPropertyList {
 public:
  virtual int AddRef();                                            // 0x00
  virtual int Release();                                           // 0x04
  PV4 PV2 PV                                                       // 0x08-0x20
  virtual bool GetProperty(unsigned int, Variant** out);           // 0x24
};

// The tunables of this module (writable .data).  Known names where the rest of the tree
// already uses one; the rest are named after their address until the dev database gives
// them a name.
extern float sTunable1582ba0;              // 0x01582ba0
extern float sTunable1582ba4;              // 0x01582ba4
extern bool g_bAcceptKeyboardInput;        // 0x0169e170
extern float g_StopMaxDistance;            // 0x01582ba8
extern float sTunable1582bb4;              // 0x01582bb4
extern float sTunable1582bb8;              // 0x01582bb8
extern float sTunable1582bc0;              // 0x01582bc0
extern float sTunable1582bc4;              // 0x01582bc4
extern float g_MoveGoalMinDist;            // 0x01582bac
extern float g_MoveGoalMaxDist;            // 0x01582bb0
extern float sTunable1582bbc;              // 0x01582bbc
extern unsigned int g_ClickMoveTimeMs;     // 0x01582bc8
extern unsigned int sTunable1582bcc;       // 0x01582bcc
extern float g_StopRadiusCap;              // 0x01582bd0
extern float sTunable1582bd4;              // 0x01582bd4
extern float sPickBoxMaxScale;             // 0x01582bd8
extern float sPickBoxMinCameraDist;        // 0x01582bdc
extern float sPickBoxMaxCameraDist;        // 0x01582be0
extern float sPickBoxMinSpeed;             // 0x01582be4
extern float sPickBoxMaxSpeed;             // 0x01582be8
extern float sPickBoxMaxSize;              // 0x01582bf0
extern float sPickBoxConeCos;              // 0x01582bec

// One tunable read: guard the list, look the id up, check the tag, store the value.
// The variant temporary belongs to the read, not to the function (the compiler merges
// the 22 block-scoped temporaries into the one stack slot the retail code uses).
#define READ_FLOAT(id, dst)                                                    \
  if (!props) return;                                                          \
  {                                                                            \
    Variant* pv;                                                               \
    if (props->GetProperty(id, &pv) && pv->mTypeId == Variant::kTypeFloat)     \
      dst = *pv->GetFloat();                                                   \
  }

#define READ_UINT(id, dst)                                                     \
  if (!props) return;                                                          \
  {                                                                            \
    Variant* pv;                                                               \
    if (props->GetProperty(id, &pv) && pv->mTypeId == Variant::kTypeUint32)    \
      dst = *pv->GetUInt();                                                    \
  }

#define READ_BOOL(id, dst)                                                     \
  if (!props) return;                                                          \
  {                                                                            \
    Variant* pv;                                                               \
    if (props->GetProperty(id, &pv) && pv->mTypeId == Variant::kTypeBool)      \
      dst = *pv->GetBool();                                                    \
  }

class cCreatureInputConfig {
 public:
  PV4 PV2
  virtual bool GetPropertyList(cPropertyList** out);   // 0x18

  void LoadInputTunables();                            // 0x00d30990
};

// @ 0x00d30990
void cCreatureInputConfig::LoadInputTunables()
{
  cPropertyList* props = 0;
  if (GetPropertyList(&props)) {
    READ_FLOAT(0x175ae53u, sTunable1582ba0);
    READ_FLOAT(0x175ae5du, sTunable1582ba4);
    READ_BOOL(0x1a28c84u, g_bAcceptKeyboardInput);
    READ_FLOAT(0x24ca4c9u, g_StopMaxDistance);
    READ_FLOAT(0x2648458u, sTunable1582bb4);
    READ_FLOAT(0x3d03d69u, sTunable1582bb8);
    READ_FLOAT(0x48657b6u, sTunable1582bc0);
    READ_FLOAT(0x368ba8f2u, sTunable1582bc4);
    READ_FLOAT(0x275b79au, g_MoveGoalMinDist);
    READ_FLOAT(0x275b79fu, g_MoveGoalMaxDist);
    READ_FLOAT(0x35ebc26u, sTunable1582bbc);
    READ_UINT(0xb895359eu, g_ClickMoveTimeMs);
    READ_UINT(0x8a6f491u, sTunable1582bcc);
    READ_FLOAT(0xca16addau, g_StopRadiusCap);
    READ_FLOAT(0x38623218u, sTunable1582bd4);
    READ_FLOAT(0x7a7e1c91u, sPickBoxMaxScale);
    READ_FLOAT(0xc661855eu, sPickBoxMinCameraDist);
    READ_FLOAT(0x5c40bbb4u, sPickBoxMaxCameraDist);
    READ_FLOAT(0xa117ef5bu, sPickBoxMinSpeed);
    READ_FLOAT(0xce9f3f71u, sPickBoxMaxSpeed);
    READ_FLOAT(0x90bd714cu, sPickBoxMaxSize);
    READ_FLOAT(0xcd1e526du, sPickBoxConeCos);
  }
  if (!props) return;
  props->Release();
}

}  // namespace SP
