// Slice s00ff2060 -- SP::ReadSTLSequenceT<eastl::vector<cBuildingData>> (0x00ff2060).
//
// The 0x38-byte building-list reader: clear the vector, read the element count from the
// stream, reserve, then read each record through a cVarListSerializer (var list 0x015b5018)
// and append it (0x00ff11c0 assign, 0x00ff1650 slow insert). Same shape as the ornament
// sequence reader at 0x00ff21d0; offsets are read from the disassembly.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_15b5018[];

#include "types.h"

typedef unsigned int  u32;
typedef unsigned char u8;

struct Float3 { float x, y, z; };
struct Float4 { float x, y, z, w; };

// ---------------------------------------------------------------------------------------------
// retail callees / globals
// ---------------------------------------------------------------------------------------------
extern "C" {
void  __cdecl FUN_0093a780(void* stream, void* dst, int count, int mode);   // EA::IO::ReadInt32
}

extern float g_16dad08;   // 0x016dad08
extern float g_16dad0c;   // 0x016dad0c
extern float g_16dad10;   // 0x016dad10
extern float g_15b4e38;   // 0x015b4e38
extern float g_15b4e3c;   // 0x015b4e3c
extern float g_15b4e40;   // 0x015b4e40
extern float g_15b4e44;   // 0x015b4e44

extern void* gBuildingVarList[2];   // 0x015b5018 (building property descriptor table)

// ---------------------------------------------------------------------------------------------
// the 0x38-byte building record
// ---------------------------------------------------------------------------------------------
struct cBuildingData
{
    Float3 mPos;                        // 0x00
    Float4 mOri;                        // 0x0c
    float  f1c;                         // 0x1c
    u32    u20;                         // 0x20
    u8     b24;                         // 0x24
    u8     b25;                         // 0x25
    u8     pad26[2];                    // 0x26
    u32    u28;                         // 0x28
    u32    u2c;                         // 0x2c
    u32    u30;                         // 0x30
    u32    u34;                         // 0x34
    void Assign(const cBuildingData* src);          // 0x00ff11c0
};

// eastl::vector<cBuildingData> (begin/end/cap)
struct VectorEC
{
    void* mBegin;                                   // +0x00
    void* mEnd;                                     // +0x04
    void* mCap;                                     // +0x08
    void EraseBld(void* first, void* last);         // 0x00f28dd0
    void Resize(u32 n);                             // 0x00ff1530
    void InsertBld(void* pos, const void* val);     // 0x00ff1650
};

// cVarListSerializer (0xa14 bytes): ctor 0x00692f90, Serialize 0x00693e10.
struct cVarListSerializer
{
    u32  mStorage[0xa14 / 4];                       // property table + object/var-list pointers
    void Ctor(void* pObject, void* pVarList, u32 nSignature);   // 0x00692f90
    char Serialize(void* pStream);                              // 0x00693e10
};

// The stream object reached through the host (+0x18 = channel) and the host itself
// (+0x1c = close, +0x20 = stream).
struct SerObj
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void* Channel();                        // +0x18
};

struct SerHost
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void  Close();                          // +0x1c
    virtual SerObj* Stream();                       // +0x20
};

// ---------------------------------------------------------------------------------------------
// 0x00ff2060 -- read a building sequence
// ---------------------------------------------------------------------------------------------
// @ 0x00ff2060
void __cdecl FUN_00ff2060(SerHost* host, VectorEC* vec)
{
    vec->EraseBld(vec->mBegin, vec->mEnd);

    u32 count = 0;
    SerObj* s = host->Stream();
    void* stream = s->Channel();
    FUN_0093a780(stream, &count, 1, 0);
    vec->Resize(count);

    u32 i = 0;
    while (i < count) {
        cBuildingData buf;
        buf.mPos.x = g_16dad08;
        buf.mPos.y = g_16dad0c;
        buf.mPos.z = g_16dad10;
        buf.mOri.x = g_15b4e38;
        buf.mOri.y = g_15b4e3c;
        buf.mOri.z = g_15b4e40;
        buf.mOri.w = g_15b4e44;
        buf.f1c = 0.0f;
        buf.u20 = 0;
        buf.b24 = 0;
        buf.b25 = 0;
        buf.u28 = 0;
        buf.u2c = 0;
        buf.u30 = 0;
        buf.u34 = 0;

        cVarListSerializer ser;
        // Ctor(pObject, pVarList, nSignature): the building property descriptor table
        // lives at 0x015b5018 (gBuildingVarList); the address is spelled out so the
        // compiler emits the retail `push imm32` and the retail argument push order.
        ser.Ctor(&buf, (void*)g_15b5018, 0x1a80d26);
        ser.Serialize(host);

        cBuildingData* pos = (cBuildingData*)vec->mEnd;
        if ((char*)pos < (char*)vec->mCap) {
            vec->mEnd = (char*)pos + 0x38;
            if (pos != 0) {
                pos->Assign(&buf);
            }
        } else {
            vec->InsertBld(pos, &buf);
        }
        ++i;
    }

    host->Close();
}
