// @ 0x0138c850  dynamic initializer of the Simulator::cScenarioResource serializer attribute table
// (34 Simulator::Attribute records, 0x3c bytes each, at 0x015af500..0x015afcf7).
//
// Same record layout and spelling as the cTribe / cHerd / cPlayer tables (s013551e0, s0134d380,
// s01350ca0): name, id, member offset, three uninitialized fields, pCurrentObject (+0x18),
// set-default callback (+0x1c), the offset function (DefaultOffset, 0x00692ca0 = pCurrentObject
// + offset for every row) and the read/write/text/validate/xml callbacks. Every record is built
// in one reused 0x3c-byte stack temp and copied (rep movsd) into the table.
// Member names and offsets agree with ModAPI cScenarioResource.h (mAvatarPosition +0x150,
// mActs +0x23c, mClasses +0x2bf4, mMarkers +0x2c10, mAvatarServerIDDEPRECATED +0x2ca0, ...).
// Row data read off the retail initializer; callbacks live outside this slice and are declared
// by address (the shared ones carry the names used in s013551e0).
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

// Read functions
// 4-byte raw read: Read4<uint32_t>, Read4<int> and Read4<float> fold to 0x00572810
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);   // bool
bool Read_00ae33d0(ISerializerReadStream* pStream, void* pData);   // Quaternion
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);   // ResourceKey
bool Read_00aff840(ISerializerReadStream* pStream, void* pData);   // uint64_t
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);   // Vector3
bool Read_00c95780(ISerializerReadStream* pStream, void* pData);   // vector<ResourceKey>
bool Read_00f26be0(ISerializerReadStream* pStream, void* pData);   // cScenarioAsset
bool Read_00f27170(ISerializerReadStream* pStream, void* pData);   // uint32_t[4]
bool Read_00f293f0(ISerializerReadStream* pStream, void* pData);   // cScenarioString
bool Read_00f2ae60(ISerializerReadStream* pStream, void* pData);   // posse members
bool Read_00f2b8d0(ISerializerReadStream* pStream, void* pData);   // vector<uint32_t>
bool Read_00f2f1b0(ISerializerReadStream* pStream, void* pData);   // markers
bool Read_00f2f4f0(ISerializerReadStream* pStream, void* pData);   // acts
bool Read_00f2f5e0(ISerializerReadStream* pStream, void* pData);   // vector<cScenarioClass>
bool Read_00f2f6c0(ISerializerReadStream* pStream, void* pData);   // classes

// Write functions
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3400(ISerializerWriteStream* pStream, void* pData);
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
bool Write_00aff870(ISerializerWriteStream* pStream, void* pData);
bool Write_00c6adc0(ISerializerWriteStream* pStream, void* pData);
bool Write_00f25d80(ISerializerWriteStream* pStream, void* pData);
bool Write_00f268b0(ISerializerWriteStream* pStream, void* pData);
bool Write_00f26c20(ISerializerWriteStream* pStream, void* pData);
bool Write_00f26ef0(ISerializerWriteStream* pStream, void* pData);
bool Write_00f27010(ISerializerWriteStream* pStream, void* pData);
bool Write_00f27200(ISerializerWriteStream* pStream, void* pData);
bool Write_00f27290(ISerializerWriteStream* pStream, void* pData);
bool Write_00f27ee0(ISerializerWriteStream* pStream, void* pData);
bool Write_00f28ce0(ISerializerWriteStream* pStream, void* pData);

// ReadText functions
void ReadText_00692fd0(const string8& text, void* pData);
void ReadText_00692ff0(const string8& text, void* pData);
// ReadTextInt<bool> folds to 0x00693090
template<typename T> void ReadTextInt(const string8& text, void* pData);
void ReadText_006930b0(const string8& text, void* pData);
void ReadText_006930f0(const string8& text, void* pData);
void ReadText_00693120(const string8& text, void* pData);
void ReadText_00693150(const string8& text, void* pData);
void ReadText_00c2e4e0(const string8& text, void* pData);

// WriteText functions
void WriteText_00692fb0(char* pBuffer, void* pData);
void WriteText_00694ec0(char* pBuffer, void* pData);
void WriteText_00694ee0(char* pBuffer, void* pData);
void WriteText_00694fa0(char* pBuffer, void* pData);
void WriteText_00694fc0(char* pBuffer, void* pData);
void WriteText_00695010(char* pBuffer, void* pData);
void WriteText_00695040(char* pBuffer, void* pData);
void WriteText_00695080(char* pBuffer, void* pData);

// Validate functions
// AlwaysValid<T>: every instantiation folds to 0x00b1fbf0 (return true)
template<typename T> bool AlwaysValid();
bool Validate_00f25b60();
bool Validate_00f25b80();
bool Validate_00f26f90();
bool Validate_00f26fd0();
bool Validate_00f270b0();
bool Validate_00f270f0();
bool Validate_00f27330();

// ToXml functions
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
bool ToXml_00595a70(void* pData, const char* pName, int depth);
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
bool ToXml_00acbba0(void* pData, const char* pName, int depth);
bool ToXml_00ae5700(void* pData, const char* pName, int depth);
bool ToXml_00ae5720(void* pData, const char* pName, int depth);
bool ToXml_00b1fbf0(void* pData, const char* pName, int depth);   // same body as AlwaysValid (return true)
bool ToXml_00c6c4e0(void* pData, const char* pName, int depth);
bool ToXml_00f28880(void* pData, const char* pName, int depth);
bool ToXml_00f29b90(void* pData, const char* pName, int depth);
bool ToXml_00f29ce0(void* pData, const char* pName, int depth);
bool ToXml_00f29e30(void* pData, const char* pName, int depth);
bool ToXml_00f29f80(void* pData, const char* pName, int depth);
bool ToXml_00f2a100(void* pData, const char* pName, int depth);
bool ToXml_00f2a250(void* pData, const char* pName, int depth);
bool ToXml_00f2a510(void* pData, const char* pName, int depth);

struct Vector3;
struct Quaternion;
struct ResourceKey;
struct ResourceKeyVector;

extern Attribute cScenarioResource_sAttributes[34];   // 0x015af500

// Fills the reused record temp; the store order is the original's.
#define ATTR(NAME, ID, OFFSET, RD, WR, RT, WT, VAL, XML, IDX) \
    a.name = NAME; a.id = ID; a.pCurrentObject = 0; a.setDefaultFunction = 0; \
    a.offsetFunction = DefaultOffset; a.readFunction = RD; a.writeFunction = WR; \
    a.readTextFunction = RT; a.writeTextFunction = WT; a.validateFunction = VAL; \
    a.toXmlFunction = XML; a.offset = (uint32_t)(OFFSET); \
    cScenarioResource_sAttributes[IDX] = a;

// @ 0x0138c850
void InitScenarioResourceAttributes()
{
    Attribute a;
    ATTR("avatarPosition", 0x07102e68, 0x150,
         Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, AlwaysValid<Vector3>, ToXml_00acbba0, 0)
    ATTR("avatarHealthMultiplier", 0x07c8cbfe, 0x170,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 1)
    ATTR("avatarIsInvulnerable", 0x07c8d9a6, 0x174,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 2)
    ATTR("avatarOrientation", 0x07102e69, 0x15c,
         Read_00ae33d0, Write_00ae3400, ReadText_00693120, WriteText_00695040, AlwaysValid<Quaternion>, ToXml_00ae5700, 3)
    ATTR("avatarScale", 0x07579cb4, 0x16c,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 4)
    ATTR("bAvatarLocked", 0x07734a68, 0x175,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 5)
    ATTR("initialPosseMembers", 0x07749ad3, 0x178,
         Read_00f2ae60, Write_00f26ef0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f26f90, ToXml_00f29b90, 6)
    ATTR("numAllowedPosseMembers", 0x07749afe, 0x238,
         Read4<int>, Write_00572840, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0, 7)
    ATTR("classes", 0x072a9b58, 0x2bf4,
         Read_00f2f6c0, Write_00f27ee0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f26fd0, ToXml_00f29ce0, 8)
    ATTR("acts", 0x07102e6a, 0x23c,
         Read_00f2f4f0, Write_00f27010, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f270b0, ToXml_00f29e30, 9)
    ATTR("markers", 0x07102e6c, 0x2c10,
         Read_00f2f1b0, Write_00f28ce0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f270f0, ToXml_00f29f80, 10)
    ATTR("winText", 0x07102e70, 0xb8,
         Read_00f293f0, Write_00f268b0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f25b60, ToXml_00f28880, 11)
    ATTR("loseText", 0x07102e71, 0xf4,
         Read_00f293f0, Write_00f268b0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f25b60, ToXml_00f28880, 12)
    ATTR("introText", 0x07102e72, 0x7c,
         Read_00f293f0, Write_00f268b0, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f25b60, ToXml_00f28880, 13)
    ATTR("type", 0x07102e76, 0x78,
         Read4<int>, Write_00572840, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0, 14)
    ATTR("bIsMission", 0x07102e77, 0x2c2c,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 15)
    ATTR("classIDCounter", 0x07906d3c, 0x2c0c,
         Read4<int>, Write_00572840, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0, 16)
    ATTR("mScreenshotTypes", 0x07cf8e1b, 0x68,
         Read_00f27170, Write_00f25d80, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<uint32_t[4]>, ToXml_00b1fbf0, 17)
    ATTR("mAvatarAsset", 0x07102e78, 0x130,
         Read_00f26be0, Write_00f26c20, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f25b80, ToXml_00f2a510, 18)
    ATTR("markerPositioningVersion", 0x07f33740, 0x2c50,
         Read4<int>, Write_00572840, ReadText_00692ff0, WriteText_00694ee0, AlwaysValid<int>, ToXml_0057cde0, 19)
    ATTR("usedAppPackIds", 0x07f33741, 0x2c54,
         Read_00f2b8d0, Write_00f27200, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<uint32_t*>, ToXml_00f2a100, 20)
    ATTR("cameraTarget", 0x07ea0c00, 0x2c30,
         Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010, AlwaysValid<Vector3>, ToXml_00acbba0, 21)
    ATTR("cameraOrientation", 0x07ea0c10, 0x2c3c,
         Read_00ae33d0, Write_00ae3400, ReadText_00693120, WriteText_00695040, AlwaysValid<Quaternion>, ToXml_00ae5700, 22)
    ATTR("cameraDistance", 0x07ea0c20, 0x2c4c,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 23)
    ATTR("avatarAssetKeyDEPRECATED", 0x07102e67, 0x2c94,
         Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080, AlwaysValid<ResourceKey>, ToXml_00ae5720, 24)
    ATTR("avatarServerIDDEPRECATED", 0x07102e6f, 0x2ca0,
         Read_00aff840, Write_00aff870, ReadText_00692fd0, WriteText_00694ec0, AlwaysValid<uint64_t>, ToXml_00595a70, 25)
    ATTR("atmosphereScoreDEPRECATED", 0x07102e6d, 0x54,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 26)
    ATTR("temperatureScoreDEPRECATED", 0x07102e6e, 0x58,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 27)
    ATTR("classesOld", 0x07102e6b, 0x2c6c,
         Read_00f2f5e0, Write_00f27290, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00f27330, ToXml_00f2a250, 28)
    ATTR("initialPosseMemberKeysDEPRECATED", 0x07749ad2, 0x2c80,
         Read_00c95780, Write_00c6adc0, ReadText_00c2e4e0, WriteText_00692fb0, AlwaysValid<ResourceKeyVector>, ToXml_00c6c4e0, 29)
    ATTR("waterScoreDEPRECATED", 0x07102e73, 0x50,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 30)
    ATTR("mbIsTimeLockedDEPRECATED", 0x07102e74, 0x5c,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 31)
    ATTR("mTimeElapsedDEPRECATED", 0x07102e75, 0x60,
         Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80, 32)
    ATTR("mbCustomScreenshotThumbnailDEPRECATED", 0x074b9f5a, 0x64,
         Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00, 33)
}

}  // namespace Simulator
