// Slice s0131c960 -- dynamic initializer of the Simulator::Attribute serializer
// table of SP::cGameTerrainCursor (12 records at 0x01568e18).
//
//   0x0131c960  table registered as L"cGameTerrainCursor" by the noun factory
//               (0x00695b40 / 0x00b30xxx) and consumed by the cVarListSerializer
//               ctor (0x00b30000).  Fields: mPosition, mAnchorPosition,
//               mDiagonalPosition1, mDiagonalPosition2, mOrientation, mRadius,
//               mAlpha, mIsVisible, mSelectedObjectCount, mIsFactoryObject,
//               mRectangleSelect, mAnchorValid.
//
// Records are 0x3c bytes (15 dwords) laid out exactly like s01318c70 /
// s0132cde0: name, id, offset, three untouched dwords, pCurrentObject,
// setDefaultFunction, offsetFunction, read/write/readText/writeText/validate/toXml.
// Each record is built in one reused 0x3c-byte stack temp at [esp+0x10] and copied
// into the table with `rep movsd` (ecx=0xf).  The three untouched dwords are
// deliberately left uninitialised in the constructor so cl emits the original write
// pattern.  Ids, offsets and callbacks were read off the initializer.
//
// Register shape reproduced from the original:
//   edx = DefaultOffset  (single non-template symbol, live across every record)
//   ebp = validate       (one symbol per attribute family; reloaded when it changes)
//   ebx = toXml          (one symbol per attribute family; reloaded when it changes)
// read/write/readText/writeText are materialised as immediates on every record (even
// where the same symbol recurs), so they are never cached in a callee-saved register.
// Flags: /O2 /MD /Gy /EHsc /TP.

#include "types.h"

namespace eastl { struct string8; }
typedef eastl::string8 string8;

namespace Simulator {

class ISerializerReadStream;
class ISerializerWriteStream;
struct Attribute;

typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
typedef void  (*ReadTextFunction_t)(const string8&, void*);
typedef void  (*WriteTextFunction_t)(char*, void*);
typedef bool  (*ValidateFunction_t)();
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
typedef void* (*OffsetFunction_t)(Attribute*);
typedef void  (*SetDefaultFunction_t)(Attribute*);

void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset

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

// One callback set per attribute family (Vector3 / Vector4 / float / bool / int).
// Distinct symbols per family reproduce the original's per-family validate/toXml
// register caching; read/write/readText/writeText stay immediates.
bool Readv3(ISerializerReadStream* pStream, void* pData);      // 0x00b6e3a0
bool Writev3(ISerializerWriteStream* pStream, void* pData);    // 0x00ac88c0
void ReadTextv3(const string8& text, void* pData);             // 0x006930f0
void WriteTextv3(char* pBuffer, void* pData);                  // 0x00695010
bool Validv3();                                                // 0x00b1fbf0
bool ToXmlv3(void* pData, const char* pName, int depth);       // 0x00acbba0

bool Readv4(ISerializerReadStream* pStream, void* pData);      // 0x00ae33d0
bool Writev4(ISerializerWriteStream* pStream, void* pData);    // 0x00ae3400
void ReadTextv4(const string8& text, void* pData);             // 0x00693120
void WriteTextv4(char* pBuffer, void* pData);                  // 0x00695040
bool Validv4();                                                // 0x00b1fbf0
bool ToXmlv4(void* pData, const char* pName, int depth);       // 0x00ae5700

bool Readf(ISerializerReadStream* pStream, void* pData);       // 0x00572810
bool Writef(ISerializerWriteStream* pStream, void* pData);     // 0x00ac88f0
void ReadTextf(const string8& text, void* pData);              // 0x006930b0
void WriteTextf(char* pBuffer, void* pData);                   // 0x00694fc0
bool Validf();                                                 // 0x00b1fbf0
bool ToXmlf(void* pData, const char* pName, int depth);        // 0x00acbb80

bool Readb(ISerializerReadStream* pStream, void* pData);       // 0x00ac8750
bool Writeb(ISerializerWriteStream* pStream, void* pData);     // 0x00ac8780
void ReadTextb(const string8& text, void* pData);              // 0x00693090
void WriteTextb(char* pBuffer, void* pData);                   // 0x00694fa0
bool Validb();                                                 // 0x00b1fbf0
bool ToXmlb(void* pData, const char* pName, int depth);        // 0x0057ce00

bool Readn(ISerializerReadStream* pStream, void* pData);       // 0x00572810
bool Writen(ISerializerWriteStream* pStream, void* pData);     // 0x00572840
void ReadTextn(const string8& text, void* pData);              // 0x00692ff0
void WriteTextn(char* pBuffer, void* pData);                   // 0x00694ee0
bool Validn();                                                 // 0x00b1fbf0
bool ToXmln(void* pData, const char* pName, int depth);        // 0x0057cde0

struct AttrSlot { uint32_t d[15]; };

extern AttrSlot GameTerrainCursor_sAttributes[12];   // 0x01568e18

#define V3_ATTR Readv3, Writev3, ReadTextv3, WriteTextv3, Validv3, ToXmlv3
#define V4_ATTR Readv4, Writev4, ReadTextv4, WriteTextv4, Validv4, ToXmlv4
#define F_ATTR  Readf, Writef, ReadTextf, WriteTextf, Validf, ToXmlf
#define B_ATTR  Readb, Writeb, ReadTextb, WriteTextb, Validb, ToXmlb
#define N_ATTR  Readn, Writen, ReadTextn, WriteTextn, Validn, ToXmln

#define ADD_CURSOR(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&GameTerrainCursor_sAttributes[IDX] = a; }

// @ 0x0131c960
void InitGameTerrainCursorAttributes()
{
    ADD_CURSOR(0, "mPosition", 0x25b303f, 0x108, V3_ATTR)
    ADD_CURSOR(1, "mAnchorPosition", 0x25b3040, 0x114, V3_ATTR)
    ADD_CURSOR(2, "mDiagonalPosition1", 0x25b3041, 0x120, V3_ATTR)
    ADD_CURSOR(3, "mDiagonalPosition2", 0x25b3042, 0x12c, V3_ATTR)
    ADD_CURSOR(4, "mOrientation", 0x25b3043, 0x138, V4_ATTR)
    ADD_CURSOR(5, "mRadius", 0x25b3044, 0x148, F_ATTR)
    ADD_CURSOR(6, "mAlpha", 0x25b3045, 0x14c, F_ATTR)
    ADD_CURSOR(7, "mIsVisible", 0x25b3046, 0x159, B_ATTR)
    ADD_CURSOR(8, "mSelectedObjectCount", 0x25b3047, 0x15c, N_ATTR)
    ADD_CURSOR(9, "mIsFactoryObject", 0x25b3048, 0x15a, B_ATTR)
    ADD_CURSOR(10, "mRectangleSelect", 0x25b3049, 0x150, B_ATTR)
    ADD_CURSOR(11, "mAnchorValid", 0x25b3050, 0x160, B_ATTR)
}

}  // namespace Simulator