// match/slices/s00a93cf0/s00a93cf0.h
#pragma once
#include "types.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed   int   i32;
typedef unsigned long long u64;

// Simulator::cCreatureAbility -- a creature-ability game component that also
// carries a refcount interface (three vtable words, see the ctor at 0x00a94470).
struct CAbil;

// EA::IO helper objects passed as the first argument to the (de)serialisers.
struct IoObj;
