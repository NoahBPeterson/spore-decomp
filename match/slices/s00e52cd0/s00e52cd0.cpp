// Slice s00e52cd0: SP cell-game tutorial hint predicate (cell-game mode stream gspCellGame).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "game/types.h"

// ---- the game objects the predicate reads (members resolved from this function's retail offsets) ----
class cObjectPool
{
 public:
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

// The cell game. Its object pool is the base sub-object at +0x1c, so the (this = game + 0x1c) pool
// lookup at the end receives the game itself.
struct cCellGame : cObjectPool
{
  char pad5190[0x5190 - sizeof(cObjectPool)];
  cCellHintManager* mpHints;            // +0x5190
  char pad51cc[0x51cc - 0x5194];
  float mfHintElapsed;                  // +0x51cc: time since the last hint
  float mfHintDelay;                    // +0x51d0
  int   mnHintId;                       // +0x51d4: pool handle of the pending hint
};

// The cell game's mode stream: a handler-vtable object whose slot 12 (+0x30) looks an object up.
class cCellStream
{
 public:
  virtual void  v0(); virtual void  v1(); virtual void  v2(); virtual void  v3();
  virtual void  v4(); virtual void  v5(); virtual void  v6(); virtual void  v7();
  virtual void  v8(); virtual void  v9(); virtual void v10(); virtual void v11();
  virtual void* GetObject(unsigned int handle);   // +0x30
};

cCellStream* GetCellStream();           // 0x0067dd30

// The cell game's simulation world (0x016b3c0c).
struct cCellWorld
{
  char pad938[0x938];
  bool mbHintBlocked;                   // +0x938
};

// 0x00e52c70: has the level-grown hint sequence run out?
bool IsHintSequenceSpent();
// 0x00e51430: level -> time (cube-root table row interpolation); EDX is the level.
int __fastcall GetLevelTime(int level);

extern cCellGame*  gspCellGame;         // 0x016b3c04: the live cell game
extern cCellWorld* gspCellWorld;        // 0x016b3c0c
float kMaxHintElapsed;                  // 0x01485378: seconds a hint may stay pending

// @ 0x00e52cd0
bool IsTutorialHintDue()
{
  cCellHintManager* hints = gspCellGame->mpHints;
  int level = hints->mnLevel;
  if (level == 1000)
    return false;
  if ((unsigned)GetCellStream()->GetObject(0x04ea96cb) <= 0)
    return false;
  if (gspCellGame->mfHintElapsed > kMaxHintElapsed)
    return false;
  if (!hints->mbActive)
    return false;
  if (GetLevelTime(level) - hints->mnLevelEnd < 15)
    return false;
  if (IsHintSequenceSpent())
    return false;
  if (gspCellWorld->mbHintBlocked)
    return false;
  return gspCellGame->Get(gspCellGame->mnHintId) == 0;
}
