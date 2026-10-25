// src/game/SPGonzago/SPAudioCityMusicSummarizer.cpp -- migrated from slice(s) s00ea34f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAudioCityMusicSummarizer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/FunctionalMatch/DeclareParam.h"
#include "EA/Stopwatch.h"
#include "cSPUILayout.h"
#include <string.h>

// ---- items of slice s00ea34f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
struct MatchParam {
  u32 mType_00;
  u32 mGroup_04;
  u32 mName_08;
};
struct ParamVec {
  MatchParam* mpBegin_00;
  MatchParam* mpEnd_04;
  MatchParam* mpCap_08;
  void DoInsertKey(MatchParam* pos, const MatchParam& value);  // 0x004e3e10
  void Insert(const MatchParam& value)
  {
    MatchParam* slot = mpEnd_04;
    if (slot < mpCap_08) {
      mpEnd_04 = slot + 1;
      if (slot)
        *slot = value;
    } else {
      DoInsertKey(slot, value);
    }
  }
};
struct DeclareParam {
  MatchParam mParam_00;
  DeclareParam(u32 group, u32 type);                           // 0x00558bc0
};
// ---- items of slice s00ea34f0 end

// @ 0x00ea42c0
bool __stdcall FUN_00ea42c0(const MatchParam* param, ParamVec* vec)
{
  bool matches = param->mGroup_04 == 0x4f684a4;
  if (matches)
    vec->Insert(DeclareParam(0x2dc9d1e, 0x4f684a4).mParam_00);
  return matches;
}
