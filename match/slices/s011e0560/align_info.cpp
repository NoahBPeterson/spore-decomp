#include "align_info.h"

// @ 0x011e20a0
unsigned int AlignInfo::AlignUpTo(const AlignInfo* other)
{
    unsigned int cur = this->current;
    unsigned int a = other->alignment;
    if (a > 1) { --a; cur += a; cur &= ~a; }
    unsigned int oldAlignment = this->alignment;
    this->current = cur;
    this->alignment = oldAlignment > other->alignment ? this->alignment : other->alignment;
    return oldAlignment;
}
