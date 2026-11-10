// Slice s0089d300: copy-assignment of a large attribute record -- five inline
// words, a table-like member at +0x14 (copied through the jump thunk 0x0089bb70), a
// byte at +0xf4, a 0x278-byte buffer at +0xf8 (copy thunk 0x00894280), then two
// bytes, a float, a byte and two more bytes.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct MapCopy_0089d300 {
    char pad[0xe0];                             // +0x00 .. +0xdf
    void AssignFrom(const MapCopy_0089d300* src);   // 0x0089bb70
};

struct BufCopy_0089d300 {
    char pad[0x278];                            // +0x00 .. +0x277
    void CopyFrom(const BufCopy_0089d300* src);     // 0x00894280
};

struct Obj_0089d300 {
    int   m00;                                  // +0x000
    int   m04;                                  // +0x004
    int   m08;                                  // +0x008
    int   m0c;                                  // +0x00c
    int   m10;                                  // +0x010
    MapCopy_0089d300 mMap;                      // +0x014 (0xe0 bytes: +0x14 .. +0xf3)
    unsigned char mF4;                          // +0x0f4
    char  pad_f5[0xf8 - 0xf5];                  // +0x0f5 .. +0x0f7
    BufCopy_0089d300 mBuf;                      // +0x0f8 (0x278 bytes: +0xf8 .. +0x36f)
    unsigned char m370;                         // +0x370
    unsigned char m371;                         // +0x371
    char  pad_372[2];                           // +0x372
    float m374;                                 // +0x374
    unsigned char m378;                         // +0x378
    unsigned char m379;                         // +0x379
    unsigned char m37a;                         // +0x37a

    Obj_0089d300* AssignFrom(const Obj_0089d300* src);
};

// @ 0x0089d300
Obj_0089d300* Obj_0089d300::AssignFrom(const Obj_0089d300* src)
{
    m00 = src->m00;
    m04 = src->m04;
    m08 = src->m08;
    m10 = src->m10;
    m0c = src->m0c;
    mMap.AssignFrom(&src->mMap);
    mF4 = src->mF4;
    mBuf.CopyFrom(&src->mBuf);
    m370 = src->m370;
    m371 = src->m371;
    m374 = src->m374;
    m378 = src->m378;
    m379 = src->m379;
    m37a = src->m37a;
    return this;
}