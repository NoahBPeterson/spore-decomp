// Shared declarations for slice s00a75000.
// EA::Swarm "MapInfo" component (retail vftable 0x014575d4, class string
// "Swarm/MapInfo").  A grid-orientation / normalization helper that owns an
// integer cell grid, a colour table and derived pixel spacing.  Layout and
// addresses come from the original disassembly and the retail vftable /
// class-string tables.
#pragma once
#include "types.h"

namespace EA { namespace Swarm {

struct Vec4 { float x, y, z, w; };

// Grid-owner interface reached through +0x38.  Only vtable slot 0x18 is used.
struct IcOwner {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual bool RequestGrid(void* src, int* a, int* b, int* out); // slot 0x18
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
    uint32_t    m50;         // +0x50
    uint32_t    m54;         // +0x54
    uint32_t    m58;         // +0x58
    uint32_t    m5c;         // +0x5c
    uint32_t    m60;         // +0x60
    uint32_t    m64;         // +0x64
    uint32_t    m68;         // +0x68
    uint32_t    m6c;         // +0x6c

    float  Get1c();                                          // 0x00a75010
    void   MapToCell(float rx, float ry, int* px, int* py,
                     float* fx, float* fy);                  // 0x00a75020
    void   Normalize();                                      // 0x00a75120
    void   NormalizeNoWrap();                                // 0x00a751a0
    void   NormalizeFloor();                                 // 0x00a75200
    void   NormalizeRound();                                 // 0x00a75270
    void   SetColor(int idx, const Vec4* c);                 // 0x00a752d0
    void   SetPoint(int idx, uint32_t a, uint32_t b);        // 0x00a75340

    void   UnpackColor(float* out, int packed, uint32_t a);  // 0x00a754f0
    int    ClassifyOrientation(const float* n, int* out);    // 0x00a75560

    void   SetVec3(float* out, uint32_t a);                  // 0x00a756a0 (stdcall)
    float* MulScale(float* out, float* s);                   // 0x00a756d0
    void   Fill(float* out, uint32_t a);                     // 0x00a75720
    void   GetBounds(float* out);                            // 0x00a75750
    bool   Contains(const float* p);                         // 0x00a757c0
    void   InitA(const float* rect, uint8_t a, void* b, int c, uint8_t d); // 0x00a75810
    void   InitB(const float* rect, uint8_t a, void* b, int c, uint8_t d, int e); // 0x00a758b0
    float  SampleBilinear(const float* p);                   // 0x00a75960
    void   SampleBicubic(float* out, const float* p);        // 0x00a75a30
    void   NormalizeVec(float* out, uint32_t a);             // 0x00a75d00
};

// Free helpers (not member functions in the original).
float __stdcall cMapInfo_One(void*);                                     // 0x00a75000
void  __cdecl   cMapInfo_ResetGrid(void* a, uint32_t* b);                      // 0x00a75390
void  __cdecl   cMapInfo_SortRect2(float* out, const float* a, const float* b);  // 0x00a753b0
void  __cdecl   cMapInfo_SortRect3(float* out, const float* b, const float* a);  // 0x00a75410
void  __cdecl   cMapInfo_SortRect3R(float* out, const float* b, const float* a); // 0x00a75480

}}
