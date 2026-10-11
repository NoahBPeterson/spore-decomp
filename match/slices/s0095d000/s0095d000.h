// Slice s0095d000 -- EA::UTFWin::Drawing (9-slice blit, std button, bevel) and the
// EA::UTFWinTools SerPropertyInfo serialization helpers (Build/Commit/FindProp/walk).
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#pragma once
#include "types.h"

namespace EA { namespace UTFWin {

struct Image { char pad0[0x1c]; int width; int height; };   // +0x1c w, +0x20 h
struct Vec2 { float x, y; };

struct Canvas {
    virtual void v00();
    virtual void SetColor(uint32_t);                                  // +0x04
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(float, float, float, float);                     // +0x38
    virtual void FillQuad();                                          // +0x3c
    virtual void v16(); virtual void v17();
    virtual void DrawQuad(const void*, float, const void*, float,
                          const void*, float, const void*, float);    // +0x48
    virtual void v19(); virtual void v20(); virtual void v21();
    virtual void DrawImage(const float* rect, Image* img, const float* uv); // +0x58
};

namespace Color {
uint32_t __cdecl Lerp(uint32_t a, uint32_t b, float t);               // 0x7f5eb0
}

namespace Drawing {
void __cdecl BltEdgeStretch(Canvas*, const float* dest, const float* edge, Image* img,
                            const float* uv, float sx, float sy);                     // 0x95d000
void __cdecl GradientBox(Canvas*, const float* outer, const float* inner,
                         const float* colOuter, const float* colInner);               // 0x95d540
void __cdecl DrawStdButton(Canvas*, const float* rect, uint32_t color, uint32_t state,
                           float thickness);                                          // 0x95d780
void __cdecl DrawBevel(Canvas*, const float* rect, uint32_t color, float width);      // 0x95da40
}
}}

// ---------------------------------------------------------------- serialization model
extern void* kSerTypeTable[];                                                          // 0x154eea0
extern void* __cdecl VectorDoInsertValue(void* begin, void* pos, int count);           // 0x11e0744
extern void* __cdecl OperatorNewArray(void* dst, int zero, unsigned size);             // 0x11e073e
extern "C" void  WString_Clear(void* self);                                            // 0x5726c0
extern "C" void  WString_Append(void* self, const void* s);                            // 0x5c3d90

struct SerItem;
struct StAlloc {
    virtual void* Alloc(uint32_t size, uint32_t align);              // vtable[0]
};
struct PropInfo {
    char      pad0[4];
    int*      meta;                    // +0x04  { fn(void*) at +0, fn2 at +8 }
    uint32_t  id;                      // +0x08
    uint16_t  flags;                   // +0x0c  low 12 bits = type, bit 15 = variable
    uint16_t  pad_e;
    uint32_t  offset;                  // +0x10
    uint32_t  count;                   // +0x14
    bool Commit(SerItem* base, uint32_t* value, int* st);          // 0x95dda0
    bool Build(SerItem* out, SerItem* base, uint32_t count, int* st, int flag); // 0x95dbd0
};
struct SerDesc { char pad0[8]; uint32_t elemSize; PropInfo* elems; uint32_t nelems; };
struct SerItem {
    SerDesc*  desc;                    // +0
    uint32_t  a;                       // +4
    uint32_t  b;                       // +8
    PropInfo* FindProp(SerItem* out, uint32_t id, int* st);         // 0x95dd00
};

bool __cdecl SerWalk(SerItem* item, uint32_t* value);              // 0x95db50

// ---------------------------------------------------------------- drawing externs
void __cdecl BltEdgeStretch_impl();     // placeholder (unused)
