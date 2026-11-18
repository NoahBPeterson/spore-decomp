// Slice s00e6ee10 -- SP cell TU: begin a turn for one cell (0x00e6ee10, 173 bytes).
//
// The cell arrives in ESI (a helper called from 0x00e6eec0).  When the cell is idle the
// body reads its facing quaternion, resolves the cell record through the cell-game pool,
// builds a 16-argument cell-command record of kind 0x22 whose duration comes from the
// per-cell parameter at +0x1b0, and then starts the turn with 0x00e5ed50, passing the
// untruncated duration twice (it is both the 4th and the 5th argument, which is what the
// `fst [esp+0x3c]` / `fstp [esp]` pair at the tail spells).  The float code is x87 (no
// /arch:SSE here): the 0x00e6d200 result and the two 0.0f arguments travel through ST(0),
// and 0x013eba80 is subtracted from the command duration.  The pool handle is read into a
// named local first; that is what makes cl load it into EAX before the pool singleton into
// ECX (the argument is evaluated before the implicit `this`).
#include "types.h"

struct Vec3 { float x, y, z; };

// 0x00b72210: handle -> live element pointer (thiscall, `ret 4`).
// The pool stores its base at +0x00 and the element stride at +0x14.
struct cObjectPool {
    char* mBase;              // +0x00
    char  mPad04[0x10];
    int   mStride;            // +0x14
    void* Get(unsigned handle);
};

// The cell record: only the fields this function touches.
struct Cell {
    int   mIndex;             // +0x00 pool handle of this cell
    char  mPad04[0x10];
    int   mQuat[4];           // +0x14 facing quaternion
    char  mPad24[0x168];
    int   mState;             // +0x18c turn/command state (0 = idle)
    char  mPad190[0x20];
    int   mParam1b0;          // +0x1b0 per-cell duration parameter
};

extern char* gspCellGame;     // 0x016b3c04, cCellGame* (mCells pool at +0x1c)
extern const float g_13eba80; // 0x013eba80, trimmed from the command duration

// 0x00e5eb20: normalized facing direction (writes three floats); 0x00e6d200: duration.
const Vec3* CellFacing(Vec3* out, Cell* self);
float FUN_00e6d200(void* obj, int a, int b, int c);

// 0x00e51ee0: enqueue a cell-command record (16 stack arguments: kind, time, ids,
// flags and two direction/quaternion pointers).
void FUN_00e51ee0(int kind, float t, int a, int b, int c, int d, int e, int f,
                  float g, float h, void* dir, int j, void* quat, int l, int m, int n);

// 0x00e5ed50: start the turn described by the record just queued; the duration is passed
// as the 4th and the 5th argument.
void FUN_00e5ed50(int handle, const Vec3* dir, const int* quat, float t, float t2);

// @ 0x00e6ee10
void CellStartTurn(Cell* self)
{
    if (self->mState != 0)
        return;

    Vec3 facing;
    CellFacing(&facing, self);

    int idx = self->mIndex;
    cObjectPool* cells = (cObjectPool*)((char*)gspCellGame + 0x1c);
    void* obj = cells->Get(idx);
    float t = FUN_00e6d200(obj, 0, 0x2f, *(int*)((char*)obj + 0x1b0));

    FUN_00e51ee0(0x22, t - g_13eba80, self->mIndex, 0, -1, -1, 0, 0,
                 0.0f, 0.0f, &facing, 0, self->mQuat, 0, 0, 0);
    FUN_00e5ed50(self->mIndex, &facing, self->mQuat, t, t);
}
