// Slice s00e52cd0: SP cell-game tutorial hint predicate.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "game/types.h"

// ---- the game objects the predicate reads (members resolved from this function's retail offsets) ----
class cObjectPool
{
 public:
  char* mpData;
  int mFreeHead;
  uint32_t mNextHandle;
  int mUsed;
  int mHighWater;
  int mStride;
  int mCapacity;
  void* Get(unsigned int handle);       // 0x00b721d0
};

struct cCellHintManager
{
  char  pad1c[0x1c];
  int   mnLevel;                        // +0x1c: level the hint sequence has grown to
  char  pad30[0x30 - 0x20];
  int   mnLevelEnd;                     // +0x30
  char  pad69[0x69 - 0x34];
  bool  mbActive;                       // +0x69
};

// Prefix view of the cell game: the cell object pool starts at +0x1c.
struct cCellGame
{
  uint32_t pad0[7];
  cObjectPool mCells;
  uint32_t pad38[(0x5190 - 0x38) / 4];
  cCellHintManager* mpHints;            // +0x5190
  char pad51cc[0x51cc - 0x5194];
  float mfHintElapsed;                  // +0x51cc: time since the last hint
  float mfHintDelay;                    // +0x51d0
  int   mnHintId;                       // +0x51d4: pool handle of the pending hint
};

// Local interface view: the retail config-manager GetOption is slot 12 (+0x30).
class cIConfigManager
{
 public:
  virtual void  v0(); virtual void  v1(); virtual void  v2(); virtual void  v3();
  virtual void  v4(); virtual void  v5(); virtual void  v6(); virtual void  v7();
  virtual void  v8(); virtual void  v9(); virtual void v10(); virtual void v11();
  virtual unsigned int GetOption(unsigned int id);   // +0x30, 0x007c7c40
};

cIConfigManager* ConfigManager();           // 0x0067dd30

// The cell game's simulation world (0x016b3c0c).
struct cCellWorld
{
  char pad938[0x938];
  bool mbHintBlocked;                   // +0x938
};

// 0x00e52c70: has the level-grown hint sequence run out?
bool IsHintSequenceSpent();
// 0x00e51430: level -> time (cube-root table row interpolation); ECX is the level.
int __fastcall GetLevelTime(int level);

extern cCellGame*  gspCellGame;         // 0x016b3c04: the live cell game
extern cCellWorld* gspCellWorld;        // 0x016b3c0c
extern const float kMaxHintElapsed;                  // 0x01485378: seconds a hint may stay pending

// @ 0x00e52cd0
bool IsTutorialHintDue()
{
  if (gspCellGame->mpHints->mnLevel == 1000 ||
      ConfigManager()->GetOption(0x04ea96cb) <= 0 ||
      gspCellGame->mfHintElapsed > kMaxHintElapsed ||
      !gspCellGame->mpHints->mbActive ||
      GetLevelTime(gspCellGame->mpHints->mnLevel) - gspCellGame->mpHints->mnLevelEnd < 15 ||
      IsHintSequenceSpent() ||
      gspCellWorld->mbHintBlocked)
    goto notDue;

  {
    cObjectPool& cells = gspCellGame->mCells;
    if (cells.Get(gspCellGame->mnHintId) == 0)
      return true;
  }
notDue:
  return false;
}
