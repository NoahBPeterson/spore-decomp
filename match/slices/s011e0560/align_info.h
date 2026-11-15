#pragma once

// RenderWare arena alignment state shared by the two original object profiles.
struct AlignInfo {
    unsigned int current;
    unsigned int alignment;
    unsigned int AlignUpTo(const AlignInfo* other);
    void Advance(const AlignInfo* other);
};
