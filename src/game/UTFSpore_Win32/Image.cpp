// src/game/UTFSpore_Win32/Image.cpp -- migrated from slice(s) s009579f0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Image.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Thread/Mutex.h"
#include "EA/UTFWin/WindowMgr.h"
#include <intrin.h>
#include <xmmintrin.h>
#pragma intrinsic(_InterlockedIncrement, _InterlockedExchange)

// ---- items of slice s009579f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  uchar;
#define B(p)     ((char*)(p))
int  __cdecl EA_atexit(void*);                       // 0x011E07EF atexit
struct Ext {
    void* ctor(int, int);                                    // 0x009222A0 Mutex::Mutex
    int   Lock(const void*);                                 // 0x009221B0 Mutex::Lock
    void  tp3(float* out, const float* in);                  // 0x0095EEB0 TransformPoint3
    void  tp4(float* out, const float* in);                  // 0x0095F1C0 TransformPoint4
    void  bb80(void*);                                       // 0x0095BB80
    void  bd60(void*, void*);                                // 0x0095BD60
    void  Splice1(void*);                                    // 0x0099A9D0 XmlReaderState::Splice
    void  ba90(void*);                                       // 0x0095BA90
    void* ba70(void*);                                       // 0x0095BA70
    void  ea0();                                             // 0x00961AE0
    void  r2db_dtor();                                       // 0x00952F80 Renderable2DBuilder::~Renderable2DBuilder
    void  iba0();                                            // 0x00951BA0
};
int __fastcall Mutex_Unlock(void*);                          // 0x00922270
struct VTab {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c(int);
    virtual void  v10(int, int);
    virtual void  v14();
    virtual void  v18(int, int, void*);
    virtual void  v1c();
    virtual char  v20(void*);
    virtual void  v24();
    virtual void  v28();
    virtual void  v2c();
    virtual void  v30();
    virtual void  v34();
    virtual void  v38();
    virtual void  v3c();
    virtual void  v40();
    virtual void  v44();
    virtual void  v48();
    virtual void  v4c();
    virtual void  v50();
    virtual void  v54();
    virtual void  v58(int, int);
    virtual void  v5c();
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual void  v6c();
    virtual void  v70();
    virtual char  v74(void*, int);
    virtual void  v78(void*, int);
    virtual void  v7c();
};
struct SimpleVec { void DoInsertValue(unsigned* pos, const unsigned& v); };  // 0x004558A0
struct ImageTable {
    char      _m[0x30];
    unsigned* begin;             // +0x30
    unsigned* end;               // +0x34
    unsigned* cap;               // +0x38
    void Add(void* obj, uchar k);    // 0x00957BB0
};
char  __fastcall Fn00957c40(void* self);     // 0x00957C40
void* __cdecl    GetGlobalImageTable();                  // 0x00957B00
void  __cdecl    ProcessPendingTextures();               // 0x00957D30
// ---- items of slice s009579f0 end

// @ 0x00957b00
void* __cdecl GetGlobalImageTable()
{
    void* r = *(void**)0x166b130;
    if (r == 0) {
        if ((*(unsigned*)0x166b188 & 1) == 0) {
            *(unsigned*)0x166b188 |= 1;
            ((Ext*)0x166b140)->ctor(0, 1);
            *(int*)0x166b170 = 0;
            *(int*)0x166b174 = 0;
            *(int*)0x166b178 = 0;
            EA_atexit((void*)0x13c1110);
        }
        r = (void*)0x166b140;
        *(void**)0x166b130 = r;
    }
    return r;
}

// @ 0x00957bb0
void ImageTable::Add(void* obj, uchar k)
{
    ((Ext*)this)->Lock((const void*)0x14405d0);
    unsigned v = (unsigned)obj + (unsigned)k;
    unsigned* end = this->end;
    if (end < this->cap) {
        this->end = end + 1;
        if (end) *end = v;
    } else {
        ((SimpleVec*)((char*)this + 0x30))->DoInsertValue(end, v);
    }
    ((VTab*)obj)->v00();
    Mutex_Unlock(this);
}

// @ 0x00957c20
void __cdecl Fn00957c20(int a, int b)
{
    ((ImageTable*)GetGlobalImageTable())->Add((void*)a, (uchar)b);
}

// @ 0x00957c40
char __fastcall Fn00957c40(void* self)
{
    ((Ext*)self)->Lock((const void*)0x14405d0);
    int* src = *(int**)(B(self) + 0x30);
    int* end = *(int**)(B(self) + 0x34);
    char result = 0;
    if (src != end) {
        result = 1;
        *(int**)(B(self) + 0x34) = src;
    }
    Mutex_Unlock(self);
    return result;
}

// @ 0x00957d30
void __cdecl ProcessPendingTextures()
{
    Fn00957c40(GetGlobalImageTable());
}
