// src/game/SPGonzago/SPCommManager.cpp -- migrated from slice(s) s01315a50 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCommManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>

// ---- items of slice s01315a50 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0131_5a50; 
}
typedef eastl::string8_s0131_5a50 string8_s0131_5a50;
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
typedef void  (*ReadTextFunction_t)(const string8_s0131_5a50&, void*);
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
void* StaticOffset(Attribute* pAttr);    // 0x011874d0: (void*)pAttr->offset (class statics)
}
namespace Simulator {
struct Attribute
{
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

    // Static attribute: the offset field holds the static's address; no ToXml callback.
    Attribute(const char* pName, uint32_t nID, void* pStatic,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = 0;
        offsetFunction = StaticOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = 0;
        offset = (uint32_t)pStatic;
    }

    // Record with a default value: the store of the default (static or GetDefaultValue<T>()) is part
    // of the record's construction and sits just before the offset store.
    template<typename Store>
    __forceinline Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault, const Store& storeDefault)
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
        storeDefault();
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
class cCity;
}
namespace Simulator {
class cCivilization;
}
namespace Simulator {
class cMission;
}
namespace Simulator {
struct Int_mEventType;
}
namespace Simulator {
struct Int_mFileID;
}
namespace Simulator {
struct Int_mDialogID;
}
namespace Simulator {
struct Int_mPriority;
}
namespace Simulator {
struct UInt_mSource;
}
namespace Simulator {
struct UInt_mTarget;
}
namespace Simulator {
struct UInt_mPlanetKey;
}
namespace Simulator {
struct UInt_mDuration;
}
namespace Simulator {
struct UInt_mElapsedTime;
}
namespace Simulator {
template<typename T> bool Read4(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
template<typename T> bool Write4(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
template<typename T> void ReadTextInt(const string8_s0131_5a50& text, void* pData);
}
namespace Simulator {
template<typename T> bool AlwaysValid();
}
namespace Simulator {
template<typename T> void WriteTextInt(char* pBuffer, void* pData);
}
namespace Simulator {
template<typename T> void WriteTextUInt(char* pBuffer, void* pData);
}
namespace Simulator {
template<typename T> bool ToXmlInt(void* pData, const char* pName, int depth);
}
namespace Simulator {
template<typename T> bool ToXmlUInt(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ae97b0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ae9e00(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ae9e30(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00aeba50(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ae9e60(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0131_5a50& text, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0131_5a50& text, void* pData);
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);
}
namespace Simulator {
bool Validate_00ae9ed0();
}
namespace Simulator {
bool Validate_00b6f550();
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00aeacc0(void* pData, const char* pName, int depth);   // SerializeList
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
extern AttrSlot cCommEvent_sAttributes[16];   // 0x01566db0
}
namespace Simulator {
#define UINT_ATTR(T) Read4<T>, Write4<T>, ReadTextInt<T>, WriteTextUInt<T>, AlwaysValid<T>, ToXmlUInt<T>
}
namespace Simulator {
#define UINT2_ATTR(T) Read4<T>, Write4<uint32_t>, ReadTextInt<uint32_t>, WriteTextUInt<T>, AlwaysValid<T>, ToXmlUInt<T>
}
namespace Simulator {
#define INT_ATTR(T) Read4<T>, Write4<int>, ReadText_00692ff0, WriteTextInt<T>, AlwaysValid<T>, ToXmlInt<T>
}
namespace Simulator {
#define BOOL_ATTR  Read_00ac8750, Write_00ac8780, ReadTextInt<bool>, WriteText_00694fa0, AlwaysValid<bool>, ToXml_0057ce00
}
namespace Simulator {
#define PTR_ATTR(T, R, W, V)  /* T: pointee, for reading only */ R, W, ReadText_00c2e4e0, WriteText_00692fb0, V, ToXml_00ac8050
}
namespace Simulator {
#define LIST_ATTR  Read_00aeba50, Write_00ae9e60, ReadText_00c2e4e0, WriteText_00692fb0, Validate_00ae9ed0, ToXml_00aeacc0
}
namespace Simulator {
#define ADD(IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&cCommEvent_sAttributes[IDX] = a; }
}
namespace Simulator {
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_006930b0(const string8_s0131_5a50& text, void* pData);
}
namespace Simulator {
void WriteText_00694fc0(char* pBuffer, void* pData);
}
namespace Simulator {
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
}
namespace Simulator {
#define FLOAT_ATTR Read4<float>, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0, AlwaysValid<float>, ToXml_00acbb80
}
// ---- items of slice s01315a50 end

// @ 0x01315a50
namespace Simulator {
void InitCommEventAttributes()
{
    ADD(0,  "mEventType", 0x0444b325, 0xc, INT_ATTR(Int_mEventType))
    ADD(1,  "mSource", 0x04407904, 0x18, UINT_ATTR(UInt_mSource))
    ADD(2,  "mTarget", 0x04407905, 0x1c, UINT_ATTR(UInt_mTarget))
    ADD(3,  "mPlanetKey", 0x037add3d, 0x34, UINT_ATTR(UInt_mPlanetKey))
    ADD(4,  "mFileID", 0x037add3e, 0x38, INT_ATTR(Int_mFileID))
    ADD(5,  "mDialogID", 0x037add3f, 0x3c, INT_ATTR(Int_mDialogID))
    ADD(6,  "mpMission", 0x037add40, 0x40, PTR_ATTR(cMission, Read_00ae97b0, Write_00bca960, Validate_00b6f550))
    ADD(7,  "mPriority", 0x037add41, 0x44, INT_ATTR(Int_mPriority))
    ADD(8,  "mpTargetCity", 0x037add43, 0x24, PTR_ATTR(cCity, Read_00ae9e00, Write_00bca960, Validate_00b6f550))
    ADD(9,  "mpSourceCity", 0x037add44, 0x20, PTR_ATTR(cCity, Read_00ae9e00, Write_00bca960, Validate_00b6f550))
    ADD(10, "mpTargetCivilization", 0x037add45, 0x2c, PTR_ATTR(cCivilization, Read_00ae9e30, Write_00bca960, Validate_00b6f550))
    ADD(11, "mpSourceCivilization", 0x037add46, 0x28, PTR_ATTR(cCivilization, Read_00ae9e30, Write_00bca960, Validate_00b6f550))
    ADD(12, "mbVisibleInGalaxy", 0x037add47, 0x30, BOOL_ATTR)
    ADD(13, "mDynamicResponses", 0x037add42, 0x50, LIST_ATTR)
    ADD(14, "mDuration", 0x037add48, 0x48, UINT2_ATTR(UInt_mDuration))
    ADD(15, "mElapsedTime", 0x037add49, 0x4c, UINT2_ATTR(UInt_mElapsedTime))
}
}  // namespace Simulator
