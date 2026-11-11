// Slice s0089b080 -- release the dynamic arrays of a render object.
//
//  0x0089b080  Obj0089b080::Clear(): for each of the four {begin, end} vectors the
//              object owns, run the trivial-type destroy (a zero-byte memcpy) and
//              rewind the end pointer to begin; the two middle vectors have real
//              destructors (0xd018d0 / 0x899420).  Then zero the seven handles at
//              +0x90..+0xa4.
#include "types.h"

// compile with /O2 /MD /Gy /TP /arch:SSE /fp:fast

extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned size);   // 0x011e0744
extern "C" void  __cdecl FUN_00d018d0(void* self, int* beg, int* end);        // 0x00d018d0
extern "C" void  __cdecl FUN_00899420(void* self, int* beg, int* end);        // 0x00899420

struct Obj0089b080 {
    char  pad0[0x2c];
    short* m2c;     // +0x2c
    short* m30;     // +0x30
    char  pad34[0x40 - 0x34];
    int*  m40;      // +0x40
    int*  m44;      // +0x44
    char  pad48[0x54 - 0x48];
    int*  m54;      // +0x54
    int*  m58;      // +0x58
    char  pad5c[0x68 - 0x5c];
    int*  m68;      // +0x68
    int*  m6c;      // +0x6c
    char  pad70[0x7c - 0x70];
    int*  m7c;      // +0x7c
    int*  m80;      // +0x80
    char  pad84[0x90 - 0x84];
    int   m90;      // +0x90
    int   m94;      // +0x94
    int   m98;      // +0x98
    int   m9c;      // +0x9c
    int   ma0;      // +0xa0
    int   ma4;      // +0xa4

    void Clear();
};

// @ 0x0089b080
void Obj0089b080::Clear()
{
    memcpy(m2c, m30, 0);
    m30 -= m30 - m2c;

    FUN_00d018d0(m40, m40, m44);
    FUN_00899420(m54, m54, m58);

    memcpy(m68, m6c, 0);
    m6c -= m6c - m68;

    memcpy(m7c, m80, 0);
    m80 -= m80 - m7c;

    m90 = 0;
    m94 = 0;
    m98 = 0;
    m9c = 0;
    ma0 = 0;
    ma4 = 0;
}
