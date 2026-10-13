// SP::cEltArrayRefT<T>: the typed view of SP::cEltArrayRef (0x10 {mNumElts, mData, mEltSize, mEltStride, mDataRC}); the dev
// PDB gives every instantiation 0x10 with cEltArrayRef as its only base and no members of its own.  Hand-maintained.
// Unverified in retail.
#ifndef GAME_SP_CELTARRAYREFT_H
#define GAME_SP_CELTARRAYREFT_H
#include "SP/cEltArrayRef.h"
namespace SP {
template <class T>
struct cEltArrayRefT : public SP::cEltArrayRef {
};
}  // namespace SP
#endif
