// Slice s0089cbc0 -- string reset/append helper: empty the wide buffer, then
// rebuild the sub-vectors through their own vector assignments.
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;

struct Vec3_s0089cbc0 { u32 a, b, c; };

// A vector<Vec3_s0089cbc0> laid out at +0x18 of the string: begin/end.
struct Vec3List_s0089cbc0 {
    Vec3_s0089cbc0* mpBegin;    // +0x00
    Vec3_s0089cbc0* mpEnd;      // +0x04
    void Assign(Vec3_s0089cbc0* first, Vec3_s0089cbc0* last);   // 0x009e0480
};

struct Str89cbc0 {
    void* pad00;
    u16*  mpBegin;                          // 0x04
    u16*  mpEnd;                            // 0x08
    u32   pad0c[3];
    Vec3List_s0089cbc0 mNodes;              // 0x18
    u32   pad20[3];
    u32   pad2c[2];
    u32   pad34[0x1d];
    u32   pada8;                            // 0xa8
    u32   padac;                            // 0xac
    void  Append(u32 n);
    void  Reset();                          // 0x0089b080
};

// @ 0x0089cbc0
void Str89cbc0::Append(u32 n)
{
    padac = 0;
    pada8 = 0;
    if (mpBegin != mpEnd) {
        *mpBegin = 0;
        mpEnd = mpBegin;
    }
    mNodes.Assign(mNodes.mpBegin, mNodes.mpEnd);
    Reset();
}
