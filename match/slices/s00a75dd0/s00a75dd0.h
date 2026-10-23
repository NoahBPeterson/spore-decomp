// Slice s00a75dd0 — EA::Swarm::cMapInfo (MapInfo component), second batch.
// Self-contained: the class layout is repeated from the neighbouring slice
// s00a75000 (retail vftable 0x014575d4, class string "Swarm/MapInfo").
#pragma once
#include "types.h"

namespace EA { namespace Swarm {

// Grid-owner interface reached through +0x38.  Slot 0x14 (index 5) is the
// grid-request call used by the Init helpers here.
struct IcOwner {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual bool v14(int id, int a, int b, void* out);              // +0x14
    virtual bool RequestGrid(void* src, int* a, int* b, int* out);  // +0x18
};

struct cMapInfo {
    void*       mpvtable;    // +0x00
    uint32_t    m04;         // +0x04
    uint32_t    m08;         // +0x08
    float       mMinX;       // +0x0c
    float       mMinY;       // +0x10
    float       mMaxX;       // +0x14
    float       mMaxY;       // +0x18
    uint8_t     mbWrap1c;    // +0x1c
    uint32_t    m20;         // +0x20
    uint32_t    m24;         // +0x24
    float       mScaleX;     // +0x28
    float       mScaleY;     // +0x2c
    void*       mpGrid;      // +0x30
    uint8_t     mbValid34;   // +0x34
    IcOwner*    mpOwner38;   // +0x38
    uint8_t     mbWrap3c;    // +0x3c
    uint32_t*   mpPixels40;  // +0x40
    int32_t     m44;         // +0x44
    int32_t     m48;         // +0x48
    int32_t     m4c;         // +0x4c

    // shared with slice s00a75000
    void  MapToCell(float rx, float ry, int* px, int* py, float* fx, float* fy); // 0x00a75020
    void  UnpackColor(float* out, int packed, uint32_t a);                       // 0x00a754f0

    void   SampleColorClamp(float* out, const float* p);        // 0x00a75dd0
    void   Init11(const float* rect, int a2, int a3, uint8_t a4, IcOwner* owner, uint8_t a6); // 0x00a76070
    float  SampleAlpha(const float* p);                         // 0x00a76110
    void   SampleDir(float* out, uint32_t a);                   // 0x00a761d0
    void   SampleColor(float* out, const float* p);             // 0x00a76240
    void   Init9(const float* rect, int a2, int a3, uint8_t a4, IcOwner* owner, uint8_t a6);  // 0x00a76420
    float  SampleBit(const float* p);                           // 0x00a764c0
    void   SampleNormal(float* out, const float* p);            // 0x00a765f0
    float* SampleTangent(float* out, uint32_t a);               // 0x00a76970
    void   SampleScalar4(float* out, uint32_t a);               // 0x00a76990
    void   Init12(const float* rect, int a2, int a3, uint8_t a4, IcOwner* owner); // 0x00a769b0
    float  SampleBitOriented(const float* p);                   // 0x00a76a50
    void   NormalizeVec3(float* out, const float* v);           // 0x00a76b30
    void   Init13(const float* rect, int a2, int a3, uint8_t a4, IcOwner* owner); // 0x00a76b80
    float  SampleByteOriented(const float* p);                  // 0x00a76c20
    float* SampleVec3(float* out, uint32_t a);                  // 0x00a76cd0
};

// Free helper (0x00a75560 in the neighbouring slice; __cdecl, 4 args).
int __cdecl ClassifyOrientation(const float* n, int* cls, float* u, float* v);

}}
