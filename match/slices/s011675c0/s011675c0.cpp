// @ 0x011675c0 : flip the sign of two floats (+0x14, +0x1c) in each of the 9 cells of each of the 8 rows
#include "types.h"

struct Cell { float f[8]; };
struct Row { Cell c[9]; };

// Written out per cell: a nested 9-iteration loop does not reproduce the original's 4x outer unroll.
#define NEGATE_CELL(i) r->c[i].f[5] *= -1.0f; r->c[i].f[7] *= -1.0f;

void NegateRows(Row* rows)
{
    Row* end = (Row*)((char*)rows + 0x900);
    for (Row* r = rows; r < end; ++r)
    {
        NEGATE_CELL(0) NEGATE_CELL(1) NEGATE_CELL(2)
        NEGATE_CELL(3) NEGATE_CELL(4) NEGATE_CELL(5)
        NEGATE_CELL(6) NEGATE_CELL(7) NEGATE_CELL(8)
    }
}
