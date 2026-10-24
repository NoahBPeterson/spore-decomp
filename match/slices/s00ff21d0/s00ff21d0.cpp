// Slice s00ff21d0 -- Simulator cCityData / cCitySummary serialization + update helpers.
//
// SP::ReadSTLSequenceT over eastl::vector<cOrnamentData>, the cCityData constructor and
// Update, the city-summary refcount/bitmap helpers (AddCityData / RemoveCityDataAt /
// ResetForward / dtor / ReadCivDataSummary), and the summary reader that rebuilds the
// cCityData / cVehicleData arrays.
//
// The shared src/game/include headers carry the 2008 dev-PDB layout; the retail offsets in this
// object are read from the disassembly and modelled with locally declared stub classes, following
// the sibling-slice style.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

typedef unsigned int  u32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char   s8;

// Small POD vector types used for position/orientation copies (assigned by value).
struct Float3 { float x, y, z; };
struct Float4 { float x, y, z, w; };

// ---------------------------------------------------------------------------------------------
// retail callees / globals
// ---------------------------------------------------------------------------------------------
extern "C" {
void  __cdecl FUN_00f47380(void* p);                     // ??3 operator delete
void* __cdecl FUN_00f473a0(u32 size, const char* file, int a, int b, int c, int d);  // EAAllocate
void  __cdecl FUN_00b96600(void* pos, const void* val);  // 0x00b96600 vector insert slow path
void  __cdecl FUN_00e25bd0(void* vec, void* first, void* last);   // vector::erase (general)
void  __cdecl FUN_0093a780(void* stream, void* dst, int count, int a);  // EA::IO::ReadInt32
void* __cdecl memcpy(void* d, const void* s, unsigned n);
}

// eastl::vector<SP::cOrnamentData...>::erase
void  __cdecl FUN_00ff1840(void* first, void* last);     // 0x00ff1840
void  __cdecl FUN_00ff1790(void* self, u32 n);           // 0x00ff1790
void  __cdecl FUN_00ff18a0(void* pos, const void* val);  // 0x00ff18a0
void  __cdecl FUN_00ff11c0(void* dst, const void* src);  // 0x00ff11c0
void  __cdecl FUN_00ff1650(void* pos, const void* val);  // 0x00ff1650
void  __cdecl FUN_00ff1450(u32 n);                       // 0x00ff1450
void  __cdecl FUN_00ff19c0(void* pos, const void* val);  // 0x00ff19c0
void  __cdecl FUN_00ff1cb0(void* o);                     // 0x00ff1cb0 cCityData ctor helper
void  __cdecl FUN_00ff04d0(void* o, void* stream);       // 0x00ff04d0 cCityData::Read-ish
void  __cdecl FUN_00ff08b0(void* self, float f, int arg);  // 0x00ff08b0
void  __cdecl FUN_00ff13c0(void* o);                     // 0x00ff13c0 cCityData dtor
void  __cdecl FUN_00f28dd0(void* first, void* last);     // 0x00f28dd0 vector<cBuildingData>::erase

// cCity query helpers (all __thiscall: ecx = the city); see the member decls in cCity below.
struct VecHolder;
struct CityVehicle;
struct TileEntity;

extern u32  g_16dad08;   // 0x016dad08  (float bits)
extern u32  g_16dad0c;   // 0x016dad0c
extern u32  g_16dad10;   // 0x016dad10
extern u32  g_15b4e38;   // 0x015b4e38
extern u32  g_15b4e3c;   // 0x015b4e3c
extern u32  g_15b4e40;   // 0x015b4e40
extern u32  g_15b4e44;   // 0x015b4e44

extern u16  g_emptyString16_begin[1];   // 0x01667bac
extern u16  g_emptyString16_end[1];     // 0x01667bae

// ---------------------------------------------------------------------------------------------
// cVarListSerializer (0xa14) -- ctor (0x692f90), Serialize (0x693e10).
// ---------------------------------------------------------------------------------------------
struct cVarListSerializer
{
    u32  mData[0x280];                                   // +0x000
    int  mSerializableVarCount;                          // +0xa00
    int  mSerializedVarCount;                            // +0xa04
    u32  mSignature;                                     // +0xa08
    void* mpObject;                                      // +0xa0c
    void* mpSerializerList;                              // +0xa10
    void Ctor(void* inst, void* dat, int tag);           // 0x692f90
    char Serialize(void* stream);                        // 0x693e10
};

// ---------------------------------------------------------------------------------------------
// An eastl local vector (begin/end/cap) whose element erase is FUN_00e25bd0.
// ---------------------------------------------------------------------------------------------
struct VectorEC
{
    void* mBegin;                       // +0x00
    void* mEnd;                         // +0x04
    void* mCap;                         // +0x08
    void Erase();                       // 0x00e25bd0 vector::erase(begin,end) (general)
    void EraseBld();                    // 0x00f28dd0 eastl::vector<cBuildingData>::erase
    void EraseOrn();                    // 0x00ff1840 eastl::vector<cOrnamentData>::erase
    void InsertSlow(void* pos, const void* val);            // 0x00b96600 (ret 8)
    void InsertBld(void* pos, const void* val);             // 0x00ff1650 (ret 8)
    void InsertOrn(void* pos, const void* val);             // 0x00ff18a0 (ret 8)
};

// ---------------------------------------------------------------------------------------------
// eastl heap node: the bookkeeping word that precedes an allocation payload.
// ---------------------------------------------------------------------------------------------
struct HeapNode
{
    int mSizeOrCookie;                  // +0x00 (payload starts at +0x04)
};

// ---------------------------------------------------------------------------------------------
// SP::cOrnamentData -- 13 floats (0x34 bytes), read/written by ReadSTLSequenceT.
// ---------------------------------------------------------------------------------------------
struct cOrnamentData
{
    float f00, f04, f08, f0c, f10, f14, f18, f1c;
    u32   u20, u24, u28, u2c, u30;
};

// eastl::vector<cOrnamentData> -- the caller-owned element vector.
struct VecOrn
{
    void* mBegin;                       // +0x00
    void* mEnd;                         // +0x04
    void* mCap;                         // +0x08
    void Erase(void* first, void* last);            // 0x00ff1840 (ret 8)
    void Resize(u32 n);                             // 0x00ff1790 (ret 4)
    void InsertSlow(void* pos, const void* val);    // 0x00ff18a0 (ret 8)
};

// eastl::vector<u32> -- the caller-owned id vector used by the summary reader.
struct VecU32
{
    void* mBegin;                       // +0x00
    void* mEnd;                         // +0x04
    void* mCap;                         // +0x08
    void Resize(u32 n);                             // 0x00ff1450 (ret 4)
    void InsertSlow(void* pos, const void* val);    // 0x00ff19c0 (ret 8)
};

// A 0x38-byte building record (matching FUN_00ff11c0 / FUN_00ff1650 element).
struct cBuildingData
{
    Float3 mPos;                               // 0x00..0x0c
    Float4 mOri;                               // 0x0c..0x1c
    float f1c;                                 // 0x1c
    u32   u20;                                 // 0x20
    u8    b24;                                 // 0x24
    u8    b25;                                 // 0x25
    u16   pad26;                               // 0x26
    u32   u28;                                 // 0x28
    u32   u2c;                                 // 0x2c
    u32   u30;                                 // 0x30
    u32   u34;                                 // 0x34
    void Assign(const cBuildingData* src);     // 0x00ff11c0 (thiscall, ret 4)
};

// A 0x34-byte ornament record (matching FUN_00ff18a0 element).
struct cOrnamentData2
{
    Float3 mPos;                               // 0x00..0x0c
    Float4 mOri;                               // 0x0c..0x1c
    float f1c;                                 // 0x1c
    u32   u20;                                 // 0x20
    u32   u24;                                 // 0x24
    u32   u28;                                 // 0x28
    u32   u2c;                                 // 0x2c
    u32   u30;                                 // 0x30
};

// ---------------------------------------------------------------------------------------------
// SP::cCityData -- the summary record (0xc4 bytes). Offsets are from the disassembly.
// ---------------------------------------------------------------------------------------------
struct cCityData
{
    void Destroy();                 // 0x00ff13c0 (thiscall dtor)
    void Init();                    // 0x00ff1cb0 (thiscall ctor helper)
    void ReadFrom(void* stream);    // 0x00ff04d0 (thiscall, ret 4)

    Float3 mPos;                    // 0x00
    Float4 mOri;                    // 0x0c
    float f1c;                      // 0x1c
    u32   u20;                      // 0x20
    u32   u24;                      // 0x24
    u8    mFlags;                   // 0x28
    u8    pad29[0x2c - 0x29];
    u32   u2c;                      // 0x2c
    float f30;                      // 0x30
    u32   u34;                      // 0x34
    u32   u38;                      // 0x38
    float f3c;                      // 0x3c
    u16*  mBeg;                     // 0x40
    u16*  mEnd;                     // 0x44
    u16*  mCap;                     // 0x48
    u32   pad4c;                    // 0x4c
    u16*  m2Beg;                    // 0x50
    u16*  m2End;                    // 0x54
    u16*  m2Cap;                    // 0x58
    u8    pad5c[0x60 - 0x5c];       // 0x5c..0x60
    u16   mSummary[0x0e];           // 0x60 (14 u16 groups for the 196-bitmap)
    VectorEC mBuildings;            // 0x7c (vector of cBuildingData, 0x38 elems)
    u8    pad88[0x90 - 0x88];       // 0x88..0x90
    VectorEC mOrnaments;            // 0x90 (vector of cOrnamentData, 0x34 elems)
    u8    pad9c[0xa4 - 0x9c];       // 0x9c..0xa4
    VectorEC m4;                    // 0xa4 (vector, 0xc-size elems)
    u8    padB0[0xb8 - 0xb0];       // 0xb0..0xb8
    u32   uB8;                      // 0xb8
    u32   uBC;                      // 0xbc
    u32   uC0;                      // 0xc0
};

// ---------------------------------------------------------------------------------------------
// SP::cVehicleData -- the 0x14-byte vehicle record built inline by ReadCivDataSummary.
// ---------------------------------------------------------------------------------------------
struct cVehicleData
{
    u32 m00;                        // +0x00
    u32 m04;                        // +0x04
    u32 m08;                        // +0x08
    u32 m0c;                        // +0x0c
    u32 m10;                        // +0x10
};

// ---------------------------------------------------------------------------------------------
// SP::cCitySummary -- the collection of cCityData records.
// ---------------------------------------------------------------------------------------------
struct cCitySummary
{
    VectorEC mPacked;               // 0x00  (vector of cCityData*)
    VectorEC mVehicles;             // 0x0c  (vector of cVehicleData*)
    u8       pad18[0x20 - 0x18];
    int      mPackCnt20;            // 0x20  running popcount tally
    int      mPackSum24;            // 0x24  running (u24 - popcount) tally
    VectorEC mCityData;             // 0x28  (vector of cCityData*, owned by l28)
    u8       pad34[0x3c - 0x34];
    VectorEC mBuildingList;         // 0x3c  (vector of cCityData*)
    u32      pad48[0x60 - 0x48];

    // 0x00ff2c70 -- account for one record's bit count into the summary tallies.
    void AddRecord(cCityData* rec);                     // ret 4
    // 0x00ff2d50 -- remove the record at index (frees and pops).
    void RemoveAt(int index);                           // ret 8
    // 0x00ff2d80 -- release all records and both vectors.
    void ResetForward();
    // 0x00ff2e30 -- release everything plus the three owning vectors.
    void Destroy();
};

// ---------------------------------------------------------------------------------------------
// SP::cCity -- only the members touched here.
// ---------------------------------------------------------------------------------------------
// A spatial object with +0x2c (GetPosition) and +0x30 (GetOrientation) vtable slots.
struct Spatial
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    Float3* GetPosition();                                  // +0x2c
    Float4* GetOrientation();                               // +0x30
};

struct cCity
{
    // vtable pointer at +0 (a single vptr; the individual virtual slots are not touched here).
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90();

    u8    pad04[0x120 - 0x04];
    // (0x120) mSpatial -- the city's spatial sub-object (vtable +0x2c GetPosition, +0x30 GetOrientation)
    Spatial mSpatial120;            // 0x120
    u8    pad124[0x2e8 - 0x124];
    u32   u2e8;                     // 0x2e8
    u32   u2ec;                     // 0x2ec
    u8    pad2f0[0x340 - 0x2f0];
    int   mVecBeg340;               // 0x340
    int   mVecEnd344;               // 0x344
    u8    pad348[0x354 - 0x348];
    int   mVecBeg354;               // 0x354
    int   mVecEnd358;               // 0x358
    u8    pad35c[0x3ec - 0x35c];
    // 0x3ec -- the action circle storage (cast to cActionCircle* by the callers)
    u8    pad3ec[0x748 - 0x3ec];
    float f748;                     // 0x748
    u32   u74c;                     // 0x74c

    // 0x00bd8110 / 0x00bd8b80 / 0x00bd7d00 / 0x00bd81d0 -- scalar queries (thiscall).
    u32   Query8110();
    u32   Query8b80();
    float Query7d00();
    u32   GetVehicleSpecialty();
    // 0x00bd8130 -- the ornament entity vector (thiscall).
    VecHolder* OrnamentVec();
    // 0x00bd9e20 -- the packed-tile entity (thiscall).
    TileEntity* TileEntity();
    // 0x00bd7f60 -- the city action circle (thiscall).
    void* ActionCircle();
};

// SP::cActionCircle -- the slot vector (begin/cap at +0x50/+0x54, 0x18-byte slots) plus the
// accessor used here (ecx = circle, slot on the stack).
struct cActionCircle
{
    u8   pad00[0x50];
    int  mBeg50;                                            // +0x50
    int  mCap54;                                            // +0x54
    void* SlotAt(u32 slot);                                 // 0x00af9ff0
};

// A slot handle in the action circle: its factory accessor is FUN_00fcc210 (ecx = the slot).
struct SlotObject
{
    CityVehicle* ToVehicle();                               // 0x00fcc210
};

// A serial stream / object with a vtable +0x18 slot that yields the raw IO channel.
struct SerObj
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    void* Channel();                                        // +0x18
};

// An object offering the +0x1c / +0x20 vtable slots used by the serializer helpers.
struct SerHost
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    void Close();                                           // +0x1c
    SerObj* Stream();                                       // +0x20
};

// A city entity (building/vehicle) reached from FUN_00fcc210: vtable +0x0c AsInterface,
// +0x20 GetId, and the vtable +0x2c/+0x30 spatial slots of the sub-object at +0x34.
struct CityEntity
{
    virtual void v00(); virtual void v04(); virtual void v08();
    void* AsInterface(u32 id);                              // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    u32  GetId();                                           // +0x20

    u8   pad24[0x22c - 0x24];
    u32  u22c;                      // 0x22c
    u8   pad230[0x274 - 0x230];
    u8   mFlags274[0xc4];           // 0x274 (0xc4 bytes)
    u8   pad338[0x34];              // 0x338.. (unused)
};

// The +0x34 sub-object of a city entity: vtable with +0x2c GetPosition / +0x30 GetOrientation.
struct EntitySpatial
{
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    Float3* GetPosition();          // +0x2c
    Float4* GetOrientation();       // +0x30
};

// The +0x120 file-slot sub-object of a building entity (ecx = the sub-object).
struct FileSlot
{
    u32 Count();                                            // 0x008e7f80 GetFileCount
};

// The packed-tile entity returned by cCity::TileEntity() (0x00bd9e20): identity vtable with
// GetPackedId at +0x64, and the packed tile flags array at +0x274.
struct TileEntity
{
    virtual void v00(); virtual void v04(); virtual void v08();
    void* AsInterface(u32 id);                              // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    u32  GetId();                                           // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60();
    u32  GetPackedId();                                     // +0x64
    u8   pad68[0x274 - 0x68];
    u8   mFlags274[0xc4];                                   // 0x274 (packed tile flags)
};

// A city entity reached via FUN_00fcc210. The identity vtable at +0x00 carries AsInterface
// (+0x0c), GetId (+0x20) and the packed-tile accessor (+0x64); the spatial sub-object used by
// the building path sits at +0x34, the file slot at +0x120, and the scalar fields follow.
struct CityVehicle
{
    virtual void v00(); virtual void v04(); virtual void v08();
    void* AsInterface(u32 id);                              // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    u32  GetId();                                           // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60();
    u32  GetPackedId();                                     // +0x64
    u8   SpecialByte();                                     // 0x00c3f540 (thiscall)

    EntitySpatial mSpatial34;       // 0x34 (building path)
    u8   pad64[0x70 - 0x64];
    EntitySpatial mSpatial70;       // 0x70 (ornament path, via a +0x70 cast)

    u8   padA4[0x120 - 0xa4];
    FileSlot mFiles;                // 0x120
    u8   pad124[0x158 - 0x124];
    float f158;                     // 0x158
    u8   pad15c[0x22c - 0x15c];
    u32  u22c;                      // 0x22c
    u8   pad230[0x289 - 0x230];
    u8   u289;                      // 0x289
    u8   pad28a[0x28c - 0x28a];
    int  i28c;                      // 0x28c
    int  i290;                      // 0x290
};

// A plain begin/end/cap holder (the FUN_00bd8130 result vector).
struct VecHolder
{
    void** mBegin;                  // +0x00
    void** mEnd;                    // +0x04
    void** mCap;                    // +0x08
};

// ---------------------------------------------------------------------------------------------
// 0x00ff21d0 -- SP::ReadSTLSequenceT<eastl::vector<cOrnamentData>>
// ---------------------------------------------------------------------------------------------
// @ 0x00ff21d0
void __cdecl FUN_00ff21d0(SerHost* host, VecOrn* vec)
{
    vec->Erase(vec->mBegin, vec->mEnd);

    u32 count = 0;
    SerObj* s = host->Stream();
    void* stream = s->Channel();
    FUN_0093a780(stream, &count, 1, 0);
    vec->Resize(count);

    u32 i = 0;
    while (i < count) {
        cOrnamentData buf;
        buf.f00 = *(float*)&g_16dad08;
        buf.f04 = *(float*)&g_16dad0c;
        buf.f08 = *(float*)&g_16dad10;
        buf.f0c = *(float*)&g_15b4e38;
        buf.f10 = *(float*)&g_15b4e3c;
        buf.f14 = *(float*)&g_15b4e40;
        buf.f18 = *(float*)&g_15b4e44;
        buf.f1c = 0.0f;
        buf.u20 = 0;
        buf.u24 = 0;
        buf.u28 = 0;
        buf.u2c = 0;
        buf.u30 = 0;

        cVarListSerializer ser;
        ser.Ctor((void*)0x015b52b0, &buf, 0x1a80d26);
        ser.Serialize(host);

        cOrnamentData* pos = (cOrnamentData*)vec->mEnd;
        if ((char*)pos < (char*)vec->mCap) {
            vec->mEnd = (char*)pos + 0x34;
            if (pos != 0) {
                pos->f00 = buf.f00;
                pos->f04 = buf.f04;
                pos->f08 = buf.f08;
                pos->f0c = buf.f0c;
                pos->f10 = buf.f10;
                pos->f14 = buf.f14;
                pos->f18 = buf.f18;
                pos->f1c = buf.f1c;
                pos->u20 = buf.u20;
                pos->u24 = buf.u24;
                pos->u28 = buf.u28;
                pos->u2c = buf.u2c;
                pos->u30 = buf.u30;
            }
        } else {
            vec->InsertSlow(pos, &buf);
        }
        ++i;
    }

    host->Close();
}

// ---------------------------------------------------------------------------------------------
// 0x00ff23b0 -- cCityData::cCityData(cCity*)  (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00ff23b0
cCityData* __fastcall FUN_00ff23b0(cCityData* ecx_this, void* edx, cCity* city)
{
    ecx_this->mFlags = 0;
    ecx_this->mBeg = g_emptyString16_begin;
    ecx_this->mEnd = g_emptyString16_begin;
    ecx_this->mCap = g_emptyString16_end;
    ecx_this->m2Beg = g_emptyString16_begin;
    ecx_this->m2End = g_emptyString16_begin;
    ecx_this->m2Cap = g_emptyString16_end;
    ecx_this->mBuildings.mBegin = 0;
    ecx_this->mBuildings.mEnd = 0;
    ecx_this->mBuildings.mCap = 0;
    ecx_this->mOrnaments.mBegin = 0;
    ecx_this->mOrnaments.mEnd = 0;
    ecx_this->mOrnaments.mCap = 0;
    ecx_this->m4.mBegin = 0;
    ecx_this->m4.mEnd = 0;
    ecx_this->m4.mCap = 0;

    if (city == 0) {
        return ecx_this;
    }

    Spatial* sp = &city->mSpatial120;
    ecx_this->mPos = *sp->GetPosition();
    ecx_this->mOri = *sp->GetOrientation();

    ecx_this->u20 = city->Query8110();
    ecx_this->u24 = ((city->mVecEnd344 - city->mVecBeg340) >> 2)
                  + ((city->mVecEnd358 - city->mVecBeg354) >> 2);
    ecx_this->u2c = city->Query8b80();
    ecx_this->f30 = city->Query7d00();
    ecx_this->u34 = city->GetVehicleSpecialty();
    ecx_this->u38 = city->u74c;
    ecx_this->f3c = city->f748;
    ecx_this->f1c = 0.0f;

    cActionCircle* circle = (cActionCircle*)((char*)city + 0x3ec);
    for (u32 slot = 0; slot < 0xe; ++slot) {
        void* s = circle->SlotAt(slot);
        if (s == 0) {
            continue;
        }
        CityVehicle* ent = ((SlotObject*)s)->ToVehicle();
        if (ent == 0) {
            continue;
        }
        ent = (CityVehicle*)ent->AsInterface(0xe9cb8ba);
        if (ent == 0) {
            continue;
        }
        cBuildingData rec;
        EntitySpatial* es = &ent->mSpatial34;
        rec.mPos = *es->GetPosition();
        rec.mOri = *es->GetOrientation();
        rec.f1c = ent->f158;
        rec.u20 = ent->mFiles.Count();
        rec.b24 = ent->u289;
        rec.b25 = ent->SpecialByte();
        rec.u28 = ent->i28c;
        rec.u2c = ent->i290;
        rec.u30 = slot;
        rec.u34 = ent->GetId();

        VectorEC* v = &ecx_this->mBuildings;
        cBuildingData* pos = (cBuildingData*)v->mEnd;
        if (pos < (cBuildingData*)v->mCap) {
            v->mEnd = (char*)pos + 0x38;
            if (pos != 0) {
                pos->Assign(&rec);
            }
        } else {
            v->InsertBld(pos, &rec);
        }
    }

    VecHolder* src = city->OrnamentVec();
    u32 n = (u32)(((int*)src->mEnd - (int*)src->mBegin) >> 2);
    for (u32 i = 0; i < n; ++i) {
        CityVehicle* ent = (CityVehicle*)src->mBegin[i];
        EntitySpatial* es = &ent->mSpatial70;
        cOrnamentData2 rec;
        rec.mPos = *es->GetPosition();
        rec.mOri = *es->GetOrientation();
        rec.f1c = 0.0f;
        rec.u20 = 0;
        rec.u24 = ent->u22c;
        rec.u28 = 0;
        rec.u2c = 0;
        rec.u30 = ent->GetId();

        VectorEC* v = &ecx_this->mOrnaments;
        cOrnamentData2* pos = (cOrnamentData2*)v->mEnd;
        if (pos < (cOrnamentData2*)v->mCap) {
            v->mEnd = (char*)pos + 0x34;
            if (pos != 0) {
                *pos = rec;
            }
        } else {
            v->InsertOrn(pos, &rec);
        }
    }

    TileEntity* tiles = city->TileEntity();
    ecx_this->uB8 = tiles->GetPackedId();

    u16* dst = ecx_this->mSummary;
    for (u32 i = 0; i < 0xc4; i += 0xe) {
        *dst = 0;
        u16 bit = 1;
        for (u32 j = 0; j < 0xe; ++j) {
            u8 b = *((u8*)tiles + i + j + 0x274);
            if (b != 0) {
                *dst |= bit;
            }
            bit = (u16)(bit << 1);
        }
        ++dst;
    }

    cActionCircle* flagsCircle = (cActionCircle*)city->ActionCircle();
    int cnt = (flagsCircle->mCap54 - flagsCircle->mBeg50) / 0x18;
    for (int i = 0; i < cnt; ++i) {
        u8* pc = (u8*)flagsCircle->SlotAt((u32)i);
        if (*pc != 0) {
            ecx_this->mFlags |= (u8)(1 << i);
        }
    }

    return ecx_this;
}

// ---------------------------------------------------------------------------------------------
// 0x00ff2810 -- cCityData::Update(cCity*, int)  (ret 8)
// ---------------------------------------------------------------------------------------------
// @ 0x00ff2810
void __fastcall FUN_00ff2810(cCityData* ecx_this, void* edx, cCity* city, int arg)
{
    if (city == 0) {
        return;
    }

    ecx_this->uBC = city->u2e8;
    ecx_this->uC0 = city->u2ec;

    Spatial* sp = &city->mSpatial120;
    ecx_this->mPos = *sp->GetPosition();
    ecx_this->mOri = *sp->GetOrientation();

    ecx_this->u20 = city->Query8110();
    ecx_this->u24 = ((city->mVecEnd344 - city->mVecBeg340) >> 2)
                  + ((city->mVecEnd358 - city->mVecBeg354) >> 2);
    ecx_this->u2c = city->Query8b80();
    FUN_00ff08b0(ecx_this, city->Query7d00(), arg);
    ecx_this->u38 = city->u74c;
    ecx_this->f3c = city->f748;

    ecx_this->mBuildings.EraseBld();

    cActionCircle* circle = (cActionCircle*)((char*)city + 0x3ec);
    for (u32 slot = 0; slot < 0xe; ++slot) {
        void* s = circle->SlotAt(slot);
        if (s == 0) {
            continue;
        }
        CityVehicle* ent = ((SlotObject*)s)->ToVehicle();
        if (ent == 0) {
            continue;
        }
        ent = (CityVehicle*)ent->AsInterface(0xe9cb8ba);
        if (ent == 0) {
            continue;
        }
        cBuildingData rec;
        EntitySpatial* es = &ent->mSpatial34;
        rec.mPos = *es->GetPosition();
        rec.mOri = *es->GetOrientation();
        rec.f1c = ent->f158;
        rec.u20 = ent->mFiles.Count();
        rec.b24 = ent->u289;
        rec.b25 = ent->SpecialByte();
        rec.u28 = ent->i28c;
        rec.u2c = ent->i290;
        rec.u30 = slot;
        rec.u34 = ent->GetId();

        VectorEC* v = &ecx_this->mBuildings;
        cBuildingData* pos = (cBuildingData*)v->mEnd;
        if (pos < (cBuildingData*)v->mCap) {
            v->mEnd = (char*)pos + 0x38;
            if (pos != 0) {
                pos->Assign(&rec);
            }
        } else {
            v->InsertBld(pos, &rec);
        }
    }

    ecx_this->mOrnaments.EraseOrn();

    VecHolder* src = city->OrnamentVec();
    u32 n = (u32)(((int*)src->mEnd - (int*)src->mBegin) >> 2);
    for (u32 k = 0; k < n; ++k) {
        CityVehicle* ent = (CityVehicle*)src->mBegin[k];
        cOrnamentData2 rec;
        EntitySpatial* es = &ent->mSpatial70;
        rec.mPos = *es->GetPosition();
        rec.mOri = *es->GetOrientation();
        rec.f1c = 0.0f;
        rec.u20 = 0;
        rec.u24 = ent->u22c;
        rec.u28 = 0;
        rec.u2c = 0;
        rec.u30 = ent->GetId();

        VectorEC* v = &ecx_this->mOrnaments;
        cOrnamentData2* pos = (cOrnamentData2*)v->mEnd;
        if (pos < (cOrnamentData2*)v->mCap) {
            v->mEnd = (char*)pos + 0x34;
            if (pos != 0) {
                *pos = rec;
            }
        } else {
            v->InsertOrn(pos, &rec);
        }
    }

    TileEntity* nb = city->TileEntity();
    ecx_this->uB8 = nb->GetPackedId();

    u16* dst = ecx_this->mSummary;
    for (u32 off = 0; off < 0xc4; off += 0xe) {
        *dst = 0;
        u32 bit = 1;
        for (u32 b = 0; b < 0xe; ++b) {
            u8 flag = nb->mFlags274[off + b];
            *dst |= (u16)((flag != 0) ? bit : 0);
            bit = (bit << 1) | (bit >> 31);
        }
        ++dst;
    }

    cActionCircle* flagsCircle = (cActionCircle*)city->ActionCircle();
    ecx_this->mFlags = 0;
    int cnt = (flagsCircle->mCap54 - flagsCircle->mBeg50) / 0x18;
    for (int i = 0; i < cnt; ++i) {
        u8* s = (u8*)flagsCircle->SlotAt((u32)i);
        if (*s != 0) {
            ecx_this->mFlags |= (u8)(1 << i);
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00ff2c70 -- cCitySummary::AddRecord(cCityData*)  (ret 4)
// ---------------------------------------------------------------------------------------------
// Popcount over the low 8 bits, written in the compiler's association order:
//   x = b - ((b >> 1) & 0x55555555);
//   x = ((x >> 2) & 0x33333333) + (x & 0x33333333);
//   x = (((x >> 4) + x) & 0x0f0f0f0f) * 0x01010101 >> 24;
static __inline u32 PopCount8(u32 b)
{
    u32 x = b - ((b >> 1) & 0x55555555u);
    x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);
    x = ((x >> 4) + x) & 0x0f0f0f0fu;
    return (x * 0x01010101u) >> 24;
}

// @ 0x00ff2c70
void cCitySummary::AddRecord(cCityData* rec)
{
    if (rec == 0) {
        return;
    }

    u32 pc1 = PopCount8((u32)rec->mFlags);
    mPackCnt20 += (int)pc1;

    u32 pc2 = PopCount8((u32)rec->mFlags);
    mPackSum24 += (int)(rec->u24 - pc2);

    VectorEC* v = &mBuildingList;
    cCityData** pos = (cCityData**)v->mEnd;
    if (pos < (cCityData**)v->mCap) {
        v->mEnd = (char*)pos + 4;
        if (pos != 0) {
            *pos = rec;
            return;
        }
    } else {
        v->InsertSlow(pos, &rec);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00ff2d50 -- cCitySummary::RemoveAt(int)  (ret 8)
// ---------------------------------------------------------------------------------------------
// @ 0x00ff2d50
void __fastcall FUN_00ff2d50(cCitySummary* ecx_this, void* edx, int index, cCitySummary* target)
{
    int idx = index;
    cCityData** vec = (cCityData**)ecx_this->mBuildingList.mBegin;
    target->AddRecord(vec[idx]);
    cCityData** v2 = (cCityData**)ecx_this->mBuildingList.mBegin;
    cCityData** end = (cCityData**)ecx_this->mBuildingList.mEnd;
    v2[idx] = end[-1];
    ecx_this->mBuildingList.mEnd = (char*)ecx_this->mBuildingList.mEnd - 4;
}

// ---------------------------------------------------------------------------------------------
// 0x00ff2d80 -- cCitySummary::ResetForward()
// ---------------------------------------------------------------------------------------------
// @ 0x00ff2d80
void cCitySummary::ResetForward()
{
    int n = (int)(((char*)mBuildingList.mEnd - (char*)mBuildingList.mBegin) >> 2);
    for (int i = 0; i < n; ++i) {
        cCityData* pc = ((cCityData**)mBuildingList.mBegin)[i];
        if (pc != 0) {
            pc->Destroy();
            FUN_00f47380(pc);
        }
    }
    int m = (int)(((char*)mCityData.mEnd - (char*)mCityData.mBegin) >> 2);
    for (int i = 0; i < m; ++i) {
        cCityData* pc = ((cCityData**)mCityData.mBegin)[i];
        if (pc != 0) {
            FUN_00f47380(pc);
        }
    }
    // vector::erase(begin(), end()) on mBuildingList
    cCityData** bEnd = (cCityData**)mBuildingList.mEnd;
    cCityData** bBeg = (cCityData**)mBuildingList.mBegin;
    cCityData** bLast = (cCityData**)mBuildingList.mEnd;
    memcpy(bBeg, bLast, (unsigned)((char*)bEnd - (char*)bLast));
    *(char* volatile*)&mBuildingList.mEnd = (char*)mBuildingList.mEnd - (((int)((char*)bEnd - (char*)bBeg) >> 2) * 4);
    // vector::erase(begin(), end()) on mCityData
    cCityData** cEnd = (cCityData**)mCityData.mEnd;
    cCityData** cLast = (cCityData**)mCityData.mEnd;
    cCityData** cBeg = *(cCityData** volatile*)&mCityData.mBegin;
    memcpy(cBeg, cLast, (unsigned)((char*)cEnd - (char*)cLast));
    mCityData.mEnd = (char*)mCityData.mEnd - (((int)((char*)cEnd - (char*)cBeg) >> 2) * 4);
}

// ---------------------------------------------------------------------------------------------
// 0x00ff2e30 -- cCitySummary::Destroy()
// ---------------------------------------------------------------------------------------------
// @ 0x00ff2e30
void __fastcall FUN_00ff2e30(cCitySummary* ecx_this, void* edx)
{
    ecx_this->ResetForward();

    void* v = ecx_this->mBuildingList.mBegin;
    if (v != 0 && ((HeapNode*)v - 1)->mSizeOrCookie != 0) {
        FUN_00f47380(v);
    }
    void* w = ecx_this->mCityData.mBegin;
    if (w != 0 && ((HeapNode*)w - 1)->mSizeOrCookie != 0) {
        FUN_00f47380(w);
    }
    void* u = ecx_this->mPacked.mBegin;
    if (u != 0 && ((HeapNode*)u - 1)->mSizeOrCookie != 0) {
        FUN_00f47380(u);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00ff2e80 -- cCitySummary::ReadCivDataSummary(stream)  (ret 4)
// ---------------------------------------------------------------------------------------------
// @ 0x00ff2e80
void __fastcall FUN_00ff2e80(cCitySummary* ecx_this, void* edx, void* stream)
{
    cVarListSerializer ser;
    ser.Ctor(ecx_this, (void*)0x015b59c0, 0x1a80d26);

    SerObj* s = ((SerHost*)stream)->Stream();
    void* str = s->Channel();
    u32 count = 0;
    FUN_0093a780(str, &count, 1, 0);

    for (u32 i = 0; i < count; ++i) {
        cCityData* rec = (cCityData*)FUN_00f473a0(0xc4, "Simulator/cCityData", 0, 0, 0, 0);
        if (rec != 0) {
            rec->Init();
        } else {
            rec = 0;
        }
        rec->ReadFrom(stream);
        VectorEC* v = &ecx_this->mBuildingList;
        cCityData** pos = (cCityData**)v->mEnd;
        if (pos < (cCityData**)v->mCap) {
            v->mEnd = (char*)pos + 4;
            if (pos != 0) {
                *pos = rec;
            }
        } else {
            v->InsertSlow(pos, &rec);
        }
    }

    SerObj* s2 = ((SerHost*)stream)->Stream();
    void* str2 = s2->Channel();
    u32 count2 = 0;
    FUN_0093a780(str2, &count2, 1, 0);

    for (u32 i = 0; i < count2; ++i) {
        cVehicleData* rec = (cVehicleData*)FUN_00f473a0(0x14, "Simulator/cVehicleData", 0, 0, 0, 0);
        void* pv = 0;
        if (rec != 0) {
            rec->m00 = g_16dad08;
            rec->m04 = g_16dad0c;
            rec->m08 = g_16dad10;
            rec->m0c = 0;
            rec->m10 = 0xffffffff;
            pv = rec;
        }
        cVarListSerializer ser2;
        ser2.Ctor(pv, (void*)0x015b4f28, 0x1a80d26);
        ser2.Serialize(stream);
        VectorEC* v = &ecx_this->mCityData;
        void** pos = (void**)v->mEnd;
        if (pos < (void**)v->mCap) {
            v->mEnd = (char*)pos + 4;
            if (pos != 0) {
                *pos = pv;
            }
        } else {
            v->InsertSlow(pos, &pv);
        }
    }

    int n = (int)(((long long)((int)ecx_this->mPacked.mEnd - (int)ecx_this->mPacked.mBegin) * -0x2aaaaaab) >> 32);
    ecx_this->mPacked.mEnd = (void*)((int)ecx_this->mPacked.mEnd + ((n >> 1) - (n >> 31)) * 0xc);

    ser.Serialize(stream);
}

// ---------------------------------------------------------------------------------------------
// 0x00ff3090 -- read a summary list of ids (ret 0)
// ---------------------------------------------------------------------------------------------
// @ 0x00ff3090
void __cdecl FUN_00ff3090(SerHost* host, VecU32* vec)
{
    u32* it = (u32*)vec->mBegin;
    u32* end = (u32*)vec->mEnd;
    u32* d = it;
    while (it != end) {
        *d++ = *it++;
    }
    vec->mEnd = (char*)vec->mEnd + -(((int)((char*)end - (char*)vec->mBegin) >> 2) * 4);

    SerObj* s = host->Stream();
    void* str = s->Channel();
    u32 count = 0;
    FUN_0093a780(str, &count, 1, 0);
    vec->Resize(count);

    for (u32 i = 0; i < count; ++i) {
        u32 val = 0;
        cVarListSerializer ser;
        ser.Ctor((void*)0x015b5458, &val, 0x1a80d26);
        ser.Serialize(host);
        u32* pos = (u32*)vec->mEnd;
        if ((char*)pos < (char*)vec->mCap) {
            vec->mEnd = (char*)pos + 4;
            if (pos != 0) {
                *pos = val;
            }
        } else {
            vec->InsertSlow(pos, &val);
        }
    }

    host->Close();
}
