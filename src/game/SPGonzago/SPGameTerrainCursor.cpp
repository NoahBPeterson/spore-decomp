// src/game/SPGonzago/SPGameTerrainCursor.cpp -- migrated from slice(s) s0131c960, s00b308f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameTerrainCursor.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cDirectPropertyList.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_167e898;        // 0x0167e898  cCursorMessageHandler singleton
extern void* g_167e7a4;        // 0x0167e7a4  cursor object singleton

// ---- items of slice s00b308f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 { float x, y, z; };
#define G0  virtual void z00();
#define G1  G0  virtual void z01();
#define G2  G1  virtual void z02();
#define G3  G2  virtual void z03();
#define G4  G3  virtual void z04();
#define G5  G4  virtual void z05();
#define G6  G5  virtual void z06();
#define G7  G6  virtual void z07();
#define G8  G7  virtual void z08();
#define G9  G8  virtual void z09();
#define G10 G9  virtual void z10();
#define G11 G10 virtual void z11();
#define G12 G11 virtual void z12();
#define G13 G12 virtual void z13();
#define G14 G13 virtual void z14();
#define G15 G14 virtual void z15();
#define G16 G15 virtual void z16();
#define G17 G16 virtual void z17();
#define G18 G17 virtual void z18();
#define G19 G18 virtual void z19();
#define G20 G19 virtual void z20();
#define G21 G20 virtual void z21();
#define G22 G21 virtual void z22();
#define G23 G22 virtual void z23();
#define G24 G23 virtual void z24();
#define G25 G24 virtual void z25();
#define G26 G25 virtual void z26();
#define G27 G26 virtual void z27();
#define G28 G27 virtual void z28();
#define G29 G28 virtual void z29();
#define G30 G29 virtual void z30();
#define G31 G30 virtual void z31();
#define G32 G31 virtual void z32();
#define G33 G32 virtual void z33();
#define G34 G33 virtual void z34();
#define G35 G34 virtual void z35();
#define G36 G35 virtual void z36();
#define G37 G36 virtual void z37();
#define G38 G37 virtual void z38();
#define G39 G38 virtual void z39();
#define G40 G39 virtual void z40();
#define G41 G40 virtual void z41();
#define G42 G41 virtual void z42();
#define G43 G42 virtual void z43();
#define G44 G43 virtual void z44();
#define G45 G44 virtual void z45();
#define G46 G45 virtual void z46();
#define G47 G46 virtual void z47();
#define G48 G47 virtual void z48();
#define G49 G48 virtual void z49();
#define G50 G49 virtual void z50();
struct VT08 { G1  virtual void  f08(); };
struct VT0C { G2  virtual void  f0C(); };
struct VT0Cp{ G2  virtual void* f0C(void*); };
struct VT00 { virtual void f00(); };
struct VT01 { G0  virtual void f01(); };
struct VT20A{ G7  virtual void f20A(unsigned, unsigned); };
struct VT54 { G20 virtual void f54(bool); };
struct VT64 { G24 virtual void f64(); };
struct VT78 { G29 virtual void f78(); };
struct VT7C { G30 virtual void f7C(bool, int); };
struct VTCC { G50 virtual void fCC(int); };
void* __cdecl SP_MessageServer();                     // 0x0067dcc0
void* __cdecl FUN_00b3d300(void* key);                // 0x00b3d300  SP::NounManager
void* __cdecl FUN_00f473a0(unsigned sz, const char* name, int a, int b, int c, int d); // operator new
extern void* g_167e898;        // 0x0167e898  cCursorMessageHandler singleton
extern void* g_167e7a4;        // 0x0167e7a4  cursor object singleton
struct PtrVec { void* mpBegin; void* mpEnd; void* mpCapacity; };
struct cGameTerrainCursor {
    void*    vftable;                 // +0x000
    char     pad_004[0x108 - 4];
    Vector3  mPosition;               // +0x108
    Vector3  mAnchorPosition;         // +0x114
    Vector3  mDiagonalPosition1;      // +0x120
    Vector3  mDiagonalPosition2;      // +0x12c
    float    mOrientation[4];         // +0x138
    float    mRadius;                 // +0x148
    float    mAlpha;                  // +0x14c
    bool     mRectangleSelect;        // +0x150
    char     pad_151[3];
    int      mSelectionMode;          // +0x154
    bool     mAutoDeselect;           // +0x158
    bool     mIsVisible;              // +0x159
    bool     mIsFactoryObject;        // +0x15a
    char     pad_15b[1];
    int      mSelectedObjectCount;    // +0x15c
    bool     mAnchorValid;            // +0x160
    char     pad_161[3];
    PtrVec*  mpSelectableObjectVector;// +0x164
    void*    mpAttachedObject;        // +0x168

    void  func9Ch_(bool b, void* obj);
    void  func60h_(int coll, void* obj);
    void  func5Ch_(int coll);
    int   func7Ch_(bool b, bool c);
    void  funcA0h_(bool b, void* obj);
    cGameTerrainCursor* Assign(cGameTerrainCursor* src);
    __int64 GetFlagsQ();
    void  SetFour(float a, float b, float c, float d);
    void  SetFourRaw(float a, float b, float c, float d);
};
// ---- items of slice s00b308f0 end

// ---- items of slice s0131c960 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0131_c960; 
}
typedef eastl::string8_s0131_c960 string8_s0131_c960;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0131_c960&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
struct Attribute
{
    Attribute() {}

    // Member attribute: offset is relative to the current object.
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
bool Readv3(ISerializerReadStream* pStream, void* pData);      // 0x00b6e3a0
}
namespace Simulator {
bool Writev3(ISerializerWriteStream* pStream, void* pData);    // 0x00ac88c0
}
namespace Simulator {
void ReadTextv3(const string8_s0131_c960& text, void* pData);             // 0x006930f0
}
namespace Simulator {
void WriteTextv3(char* pBuffer, void* pData);                  // 0x00695010
}
namespace Simulator {
bool Validv3();                                                // 0x00b1fbf0
}
namespace Simulator {
bool ToXmlv3(void* pData, const char* pName, int depth);       // 0x00acbba0
}
namespace Simulator {
bool Readv4(ISerializerReadStream* pStream, void* pData);      // 0x00ae33d0
}
namespace Simulator {
bool Writev4(ISerializerWriteStream* pStream, void* pData);    // 0x00ae3400
}
namespace Simulator {
void ReadTextv4(const string8_s0131_c960& text, void* pData);             // 0x00693120
}
namespace Simulator {
void WriteTextv4(char* pBuffer, void* pData);                  // 0x00695040
}
namespace Simulator {
bool Validv4();                                                // 0x00b1fbf0
}
namespace Simulator {
bool ToXmlv4(void* pData, const char* pName, int depth);       // 0x00ae5700
}
namespace Simulator {
bool Readf(ISerializerReadStream* pStream, void* pData);       // 0x00572810
}
namespace Simulator {
bool Writef(ISerializerWriteStream* pStream, void* pData);     // 0x00ac88f0
}
namespace Simulator {
void ReadTextf(const string8_s0131_c960& text, void* pData);              // 0x006930b0
}
namespace Simulator {
void WriteTextf(char* pBuffer, void* pData);                   // 0x00694fc0
}
namespace Simulator {
bool Validf();                                                 // 0x00b1fbf0
}
namespace Simulator {
bool ToXmlf(void* pData, const char* pName, int depth);        // 0x00acbb80
}
namespace Simulator {
bool Readb(ISerializerReadStream* pStream, void* pData);       // 0x00ac8750
}
namespace Simulator {
bool Writeb(ISerializerWriteStream* pStream, void* pData);     // 0x00ac8780
}
namespace Simulator {
void ReadTextb(const string8_s0131_c960& text, void* pData);              // 0x00693090
}
namespace Simulator {
void WriteTextb(char* pBuffer, void* pData);                   // 0x00694fa0
}
namespace Simulator {
bool Validb();                                                 // 0x00b1fbf0
}
namespace Simulator {
bool ToXmlb(void* pData, const char* pName, int depth);        // 0x0057ce00
}
namespace Simulator {
bool Readn(ISerializerReadStream* pStream, void* pData);       // 0x00572810
}
namespace Simulator {
bool Writen(ISerializerWriteStream* pStream, void* pData);     // 0x00572840
}
namespace Simulator {
void ReadTextn(const string8_s0131_c960& text, void* pData);              // 0x00692ff0
}
namespace Simulator {
void WriteTextn(char* pBuffer, void* pData);                   // 0x00694ee0
}
namespace Simulator {
bool Validn();                                                 // 0x00b1fbf0
}
namespace Simulator {
bool ToXmln(void* pData, const char* pName, int depth);        // 0x0057cde0
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
extern AttrSlot GameTerrainCursor_sAttributes[12];   // 0x01568e18
}
namespace Simulator {
#define V3_ATTR Readv3, Writev3, ReadTextv3, WriteTextv3, Validv3, ToXmlv3
}
namespace Simulator {
#define V4_ATTR Readv4, Writev4, ReadTextv4, WriteTextv4, Validv4, ToXmlv4
}
namespace Simulator {
#define F_ATTR  Readf, Writef, ReadTextf, WriteTextf, Validf, ToXmlf
}
namespace Simulator {
#define B_ATTR  Readb, Writeb, ReadTextb, WriteTextb, Validb, ToXmlb
}
namespace Simulator {
#define N_ATTR  Readn, Writen, ReadTextn, WriteTextn, Validn, ToXmln
}
// ---- items of slice s0131c960 end

// @ 0x00b30d70
void* __cdecl SP_GetGameTerrainCursor()
{
    if (g_167e898 == 0) {
        void* p = FUN_00f473a0(0xc, "Simulator/cCursorMessageHandler", 0, 0, 0, 0);
        if (p) {
            *(void**)((char*)p + 4) = (void*)0x013ef094;
            *(void**)((char*)p + 8) = 0;
            *(void**)p = (void*)0x01460104;
            *(void**)((char*)p + 4) = (void*)0x01460100;
        }
        void* old = g_167e898;
        if (p != g_167e898) {
            if (p) ((VT08*)p)->f08();
            g_167e898 = p;
            if (old) ((VT0C*)old)->f0C();
        }
        void* ms = SP_MessageServer();
        ((VT20A*)ms)->f20A((unsigned)g_167e898, 0x01a0219e);
    }
    if (g_167e7a4 == 0) {
        void* mgr = FUN_00b3d300((void*)0x018c40bc);
        void* res = 0;
        if (mgr)
            res = ((VT0Cp*)mgr)->f0C((void*)0x014a4edc);
        void* old = g_167e7a4;
        if (res != g_167e7a4) {
            if (res) ((VT00*)res)->f00();
            g_167e7a4 = res;
            if (old) ((VT01*)old)->f01();
        }
        if (g_167e7a4)
            ((VTCC*)g_167e7a4)->fCC(0);
    }
    return g_167e7a4;
}

// @ 0x00b30e80
void cGameTerrainCursor::func9Ch_(bool b, void* obj)
{
    if (!mRectangleSelect) {
        if (b) {
            void* c = SP_GetGameTerrainCursor();
            ((VT64*)c)->f64();
        }
        ((VT78*)this)->f78();

        PtrVec* v = mpSelectableObjectVector;
        if (v != 0) {
            if ((unsigned)((int)((char*)v->mpEnd - (char*)v->mpBegin) >> 2) != 0) {
                void** p = (void**)v->mpBegin;
                unsigned i = 0;
                do {
                    if (obj == *p) {
                        ((VT54*)obj)->f54(true);
                        return;
                    }
                    ++i;
                    ++p;
                } while (i < (unsigned)((int)((char*)v->mpEnd - (char*)v->mpBegin) >> 2));
            }
        }
    } else {
        ((VT7C*)this)->f7C(false, 1);
    }
}

// @ 0x0131c960
namespace Simulator {
void InitGameTerrainCursorAttributes()
{
    { Attribute a("mPosition", 0x25b303f, 0x108, Readv3, Writev3, ReadTextv3, WriteTextv3, Validv3, ToXmlv3); *(Attribute*)&GameTerrainCursor_sAttributes[0] = a; }
    { Attribute a("mAnchorPosition", 0x25b3040, 0x114, Readv3, Writev3, ReadTextv3, WriteTextv3, Validv3, ToXmlv3); *(Attribute*)&GameTerrainCursor_sAttributes[1] = a; }
    { Attribute a("mDiagonalPosition1", 0x25b3041, 0x120, Readv3, Writev3, ReadTextv3, WriteTextv3, Validv3, ToXmlv3); *(Attribute*)&GameTerrainCursor_sAttributes[2] = a; }
    { Attribute a("mDiagonalPosition2", 0x25b3042, 0x12c, Readv3, Writev3, ReadTextv3, WriteTextv3, Validv3, ToXmlv3); *(Attribute*)&GameTerrainCursor_sAttributes[3] = a; }
    { Attribute a("mOrientation", 0x25b3043, 0x138, Readv4, Writev4, ReadTextv4, WriteTextv4, Validv4, ToXmlv4); *(Attribute*)&GameTerrainCursor_sAttributes[4] = a; }
    { Attribute a("mRadius", 0x25b3044, 0x148, Readf, Writef, ReadTextf, WriteTextf, Validf, ToXmlf); *(Attribute*)&GameTerrainCursor_sAttributes[5] = a; }
    { Attribute a("mAlpha", 0x25b3045, 0x14c, Readf, Writef, ReadTextf, WriteTextf, Validf, ToXmlf); *(Attribute*)&GameTerrainCursor_sAttributes[6] = a; }
    { Attribute a("mIsVisible", 0x25b3046, 0x159, Readb, Writeb, ReadTextb, WriteTextb, Validb, ToXmlb); *(Attribute*)&GameTerrainCursor_sAttributes[7] = a; }
    { Attribute a("mSelectedObjectCount", 0x25b3047, 0x15c, Readn, Writen, ReadTextn, WriteTextn, Validn, ToXmln); *(Attribute*)&GameTerrainCursor_sAttributes[8] = a; }
    { Attribute a("mIsFactoryObject", 0x25b3048, 0x15a, Readb, Writeb, ReadTextb, WriteTextb, Validb, ToXmlb); *(Attribute*)&GameTerrainCursor_sAttributes[9] = a; }
    { Attribute a("mRectangleSelect", 0x25b3049, 0x150, Readb, Writeb, ReadTextb, WriteTextb, Validb, ToXmlb); *(Attribute*)&GameTerrainCursor_sAttributes[10] = a; }
    { Attribute a("mAnchorValid", 0x25b3050, 0x160, Readb, Writeb, ReadTextb, WriteTextb, Validb, ToXmlb); *(Attribute*)&GameTerrainCursor_sAttributes[11] = a; }
}
}  // namespace Simulator
