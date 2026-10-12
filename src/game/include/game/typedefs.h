// Scoped typedefs the dev PDB has no record of (it stores typedefs resolved).  Hand-maintained;
// tools/migrate/headers.py lists the names it needs here when it meets one.
#ifndef GAME_TYPEDEFS_H
#define GAME_TYPEDEFS_H
#include "game/types.h"
namespace EA { namespace IO {
// PositionType is the seek-origin enum (generated EA/IO/PositionType.h), not an offset type.
typedef int OffsetType;       // 32-bit in this build: IStream::SetPosition(int, PositionType) in the byte-exact slices
typedef unsigned int SizeType;
}}
#endif
