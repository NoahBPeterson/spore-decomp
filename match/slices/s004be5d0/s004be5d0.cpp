// Slice s004be5d0: an XML-driven element-graph parser (attribute callbacks that read into a
// 0x1D8-byte element record), XML writer helpers, and a small byte-RLE stream codec.
// Built without optimization: /Od /Ob1 /arch:SSE /GS- (frame pointer, movss float copies, no cookies).
#include "types.h"

extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);
extern "C" wchar_t* __cdecl wcscpy(wchar_t* dst, const wchar_t* src);
#pragma intrinsic(wcscmp, wcscpy)
extern "C" __declspec(dllimport) wchar_t* __cdecl _ultow(unsigned long value, wchar_t* buf, int radix);
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);

struct Vector3 {
    float x, y, z;
    float LengthSquared() const { return x * x + y * y + z * z; }
};

template <class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
};

// One parsed element (0x1D8 bytes).
struct ParseElem {
    int mKind;              // 0x00
    int mType;              // 0x04
    int mParent;            // 0x08
    int mPartner;           // 0x0C (mirror element, -1 if none)
    float mScale;           // 0x10
    uint32_t pad14[9];      // 0x14
    Vector3 mAxes[3];       // 0x38
    uint32_t pad5c[13];     // 0x5C
    uint32_t mNumValues;    // 0x90
    float mValues[8];       // 0x94
    int mValueIds[8];       // 0xB4
    uint32_t mNumSlots;     // 0xD4
    uint32_t padD8[64];     // 0xD8

    const Vector3& GetAxis(int k) const { return mAxes[k]; }
};

struct ParseData {
    uint32_t pad0[38];          // 0x00
    vector<ParseElem> mElems;   // 0x98
};

class XmlParseContext {
public:
    bool Validate();
    bool ParseFloat(float* out);       // 0x004BE2E0
    bool ParseUInt(uint32_t* out);     // 0x004BE380
    void SelectElement(uint32_t index);// 0x004BE420

    uint32_t pad0[0x3AA0 / 4];
    ParseData* mpData;      // 0x3AA0
    int mCurrent;           // 0x3AA4
    int m3AA8;              // 0x3AA8
    int mCurrentId;         // 0x3AAC
    wchar_t mText[256];     // 0x3AB0
};

int MapKind(uint32_t value);   // 0x004BD850
int MapType(uint32_t value);   // 0x004BD9C0

// @ 0x004BE5D0
bool XmlParseContext::Validate()
{
    ParseElem* data = mpData->mElems.mpBegin;
    int count = mpData->mElems.size();
    bool foundRoot = false;
    for (int j = 0; j < count; j++) {
        if (data[j].mType == -1)
            return false;
        if (data[j].mParent == -1)
            foundRoot = true;
        if (data[j].mPartner == j)
            return false;
        if (data[j].mPartner != -1 && data[data[j].mPartner].mPartner != j)
            return false;
        if (data[j].mScale < 1.5258789e-05f)
            return false;
        if (data[j].GetAxis(0).LengthSquared() < 0.9f)
            return false;
        if (data[j].GetAxis(1).LengthSquared() < 0.9f)
            return false;
        if (data[j].GetAxis(2).LengthSquared() < 0.9f)
            return false;
    }
    if (!foundRoot)
        return false;
    return true;
}

// @ 0x004BE820
bool ParseBoolAttr(XmlParseContext* ctx, void* out, int size)
{
    int value = wcscmp(ctx->mText, L"true") == 0;
    if (size == 4)
        *(int*)out = value;
    else if (size == 1)
        *(uint8_t*)out = (uint8_t)value;
    else
        return false;
    return true;
}

// @ 0x004BE8D0
bool ParseUIntAttr(XmlParseContext* ctx, void* out, int size)
{
    return size == 4 && ctx->ParseUInt((uint32_t*)out);
}

// @ 0x004BE910
bool ParseFloatAttr(XmlParseContext* ctx, void* out, int size)
{
    return size == 4 && ctx->ParseFloat((float*)out);
}

// @ 0x004BE950
bool ParseVector3Attr(XmlParseContext* ctx, void* out, int size)
{
    float* v = (float*)out;
    return size == 12 && ctx->ParseFloat(v) && ctx->ParseFloat(v + 1) && ctx->ParseFloat(v + 2);
}

// @ 0x004BE9C0
bool ParseKindAndType(XmlParseContext* ctx)
{
    ParseElem* node = &ctx->mpData->mElems.mpBegin[ctx->mCurrent];
    uint32_t kind = (uint32_t)-1;
    uint32_t type = (uint32_t)-1;
    if (!ctx->ParseUInt(&kind) || !ctx->ParseUInt(&type))
        return false;
    node->mKind = MapKind(kind);
    node->mType = MapType(type);
    return true;
}

// @ 0x004BEA50
bool ParseChild(XmlParseContext* ctx)
{
    uint32_t index = (uint32_t)-1;
    if (!ctx->ParseUInt(&index) || index >= 0x100)
        return false;
    ctx->SelectElement(index);
    ParseElem* child = &ctx->mpData->mElems.mpBegin[index];
    if (child->mParent != -1)
        return false;
    child->mParent = ctx->mCurrent;
    return true;
}

// @ 0x004BEAD0
bool ParseValue(XmlParseContext* ctx)
{
    ParseElem* elem = &ctx->mpData->mElems.mpBegin[ctx->mCurrent];
    if (elem->mNumValues >= 8)
        return false;
    if (!ctx->ParseFloat(&elem->mValues[elem->mNumValues]))
        return false;
    elem->mValueIds[elem->mNumValues] = ctx->mCurrentId;
    elem->mNumValues++;
    return true;
}

// @ 0x004BEB70
bool ParseSlotUInt(XmlParseContext* ctx, char* out, int stride)
{
    ParseElem* elem = &ctx->mpData->mElems.mpBegin[ctx->mCurrent];
    if (elem->mNumSlots >= 8)
        return false;
    return ParseUIntAttr(ctx, out + stride * elem->mNumSlots, stride);
}

// @ 0x004BEBD0
bool ParseSlotVector3(XmlParseContext* ctx, char* out, int stride)
{
    ParseElem* elem = &ctx->mpData->mElems.mpBegin[ctx->mCurrent];
    if (elem->mNumSlots >= 8)
        return false;
    return ParseVector3Attr(ctx, out + stride * elem->mNumSlots, stride);
}

// @ 0x004BEC30
bool EndSlot(XmlParseContext* ctx)
{
    ParseElem* elem = &ctx->mpData->mElems.mpBegin[ctx->mCurrent];
    if (elem->mNumSlots >= 8)
        return false;
    elem->mNumSlots++;
    return true;
}

wchar_t* FtoaEnglish16(double value, wchar_t* buf, int bufSize, int precision, bool trim);

class IXmlWriter {
public:
    virtual void Unk0();
    virtual void Unk1();
    virtual bool BeginElement(const wchar_t* name);
    virtual bool EndElement(const wchar_t* name);
    virtual void Unk4();
    virtual void Unk5();
    virtual void Unk6();
    virtual void Unk7();
    virtual bool WriteText(const wchar_t* text);
};

inline bool IsNaN(float f) { return (*(uint32_t*)&f & 0x7FFFFFFF) > 0x7F800000; }
inline bool IsInf(float f) { return (*(uint32_t*)&f & 0x7FFFFFFF) == 0x7F800000; }

union FloatBits {
    float f;
    uint32_t u;
};

namespace {

// @ 0x004BECA0
wchar_t* FormatFloat(wchar_t* buf, float value)
{
    FloatBits bits;
    bits.f = value;
    if (IsNaN(value))
        wcscpy(buf, (bits.u & 0x80000000) ? L"-nan" : L"nan");
    else if (IsInf(value))
        wcscpy(buf, (bits.u & 0x80000000) ? L"-inf" : L"inf");
    else
        FtoaEnglish16(value, buf, 64, 6, true);
    return buf;
}

} // namespace

// @ 0x004BEDE0
bool XmlWriteElement(IXmlWriter* writer, const wchar_t* name, const wchar_t* text)
{
    return writer->BeginElement(name) && writer->WriteText(text) && writer->EndElement(name);
}

namespace {

// @ 0x004BEE50
bool XmlWriteBool(IXmlWriter* writer, const wchar_t* name, bool value)
{
    return XmlWriteElement(writer, name, value ? L"true" : L"false");
}

} // namespace

// @ 0x004BEE90
bool XmlWriteUInt(IXmlWriter* writer, const wchar_t* name, unsigned long value)
{
    wchar_t buf[20];
    return XmlWriteElement(writer, name, _ultow(value, buf, 10));
}

namespace {

// @ 0x004BEEC0
bool XmlWriteHex(IXmlWriter* writer, const wchar_t* name, uint32_t value)
{
    wchar_t buf[11];
    buf[0] = L'0';
    buf[1] = L'x';
    buf[10] = 0;
    for (int i = 9; i >= 2; i--, value >>= 4)
        buf[i] = (wchar_t)(((value & 0xF) < 10 ? L'0' : L'a' - 10) + (value & 0xF));
    return XmlWriteElement(writer, name, buf);
}

} // namespace

// @ 0x004BEF40
bool XmlWriteFloat(IXmlWriter* writer, const wchar_t* name, float value)
{
    wchar_t buf[64];
    return XmlWriteElement(writer, name, FormatFloat(buf, value));
}

// @ 0x004BEF80
bool XmlWriteVector3(IXmlWriter* writer, const wchar_t* name, const Vector3& v)
{
    wchar_t buf[64];
    return writer->BeginElement(name) &&
           writer->WriteText(FormatFloat(buf, v.x)) && writer->WriteText(L" ") &&
           writer->WriteText(FormatFloat(buf, v.y)) && writer->WriteText(L" ") &&
           writer->WriteText(FormatFloat(buf, v.z)) &&
           writer->EndElement(name);
}

class IStream {
public:
    virtual void Unk0();
    virtual void Unk1();
    virtual void Unk2();
    virtual void Unk3();
    virtual void Unk4();
    virtual void Unk5();
    virtual void Unk6();
    virtual void Unk7();
    virtual void Unk8();
    virtual void Unk9();
    virtual void Unk10();
    virtual void Unk11();
    virtual int Read(void* dst, uint32_t size);
    virtual void Unk13();
    virtual bool Write(const void* src, uint32_t size);
};

// Run-length encoding: 0xFE <n> = n copies of the previous byte; 0xFE 0x00 = a literal 0xFE.
// Data is written in blocks of up to 2048 bytes, each prefixed by its 16-bit length.

// @ 0x004BF0A0
bool WriteRLE(IStream* stream, const uint8_t* data, uint32_t size)
{
    uint8_t buffer[2048];
    uint8_t* dst = buffer;
    const uint8_t* p = data;
    const uint8_t* end = data + size;
    uint8_t lastByte = 0;
    while (p < end) {
        if (dst + 2 > buffer + sizeof(buffer)) {
            uint16_t len = (uint16_t)(dst - buffer);
            if (!stream->Write(&len, 2) || !stream->Write(buffer, dst - buffer))
                return false;
            dst = buffer;
        }
        uint32_t repeat = 0;
        uint32_t maxRun = end - p < 0xFF ? end - p : 0xFF;
        while (repeat < maxRun && p[repeat] == lastByte)
            repeat++;
        if (repeat > 2) {
            *dst = 0xFE;
            dst++;
            *dst = (uint8_t)repeat;
            dst++;
            p += repeat;
        } else {
            *dst = *p;
            lastByte = *dst;
            dst++;
            p++;
            if (lastByte == 0xFE) {
                *dst = 0;
                dst++;
            }
        }
    }
    if (dst > buffer) {
        uint16_t len = (uint16_t)(dst - buffer);
        if (!stream->Write(&len, 2) || !stream->Write(buffer, dst - buffer))
            return false;
    }
    return true;
}

// @ 0x004BF2A0
bool ReadRLE(IStream* stream, uint8_t* data, uint32_t size)
{
    uint8_t buf[2048];
    uint8_t* in = buf + sizeof(buf);
    uint8_t* dst = data;
    uint8_t* limit = data + size;
    uint8_t fill = 0;
    while (dst < limit) {
        if (in == buf + sizeof(buf)) {
            uint16_t len;
            if (stream->Read(&len, 2) != 2)
                return false;
            if (len < 1 || len > sizeof(buf))
                return false;
            in = buf + sizeof(buf) - len;
            if (stream->Read(in, len) != len)
                return false;
        }
        if (*in == 0xFE) {
            in++;
            if (in >= buf + sizeof(buf))
                return false;
            if (*in != 0) {
                uint8_t n = *in;
                if (n > limit - dst)
                    return false;
                memset(dst, fill, n);
                dst += n;
            } else {
                *dst = 0xFE;
                fill = 0xFE;
                dst++;
            }
        } else {
            *dst = *in;
            fill = *dst;
            dst++;
        }
        in++;
    }
    return true;
}
