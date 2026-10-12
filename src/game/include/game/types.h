// Fixed-width types for the original-faithful game sources (VC9 has no <stdint.h>).
#ifndef GAME_TYPES_H
#define GAME_TYPES_H
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif
