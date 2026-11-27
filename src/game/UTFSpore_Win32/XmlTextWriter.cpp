// addresses retail relocates here, named so the build relocates them too
extern "C" char g_143a1c0[];
extern "C" char g_143a2ac[];

#include "EA/XML/XmlTextWriter.h"
#include "EA/IO/IStream.h"
#include <stdarg.h>

// Retail helpers this translation unit calls but does not define (address in the comment).
extern "C" size_t wcslen(const wchar_t*);
extern "C" bool  __cdecl IO_WriteEncoded(EA::IO::IStream* pStream, const void* p, unsigned int n,
                                         unsigned int enc);                    // 0x93b820
extern "C" int   __cdecl Vsnprintf16(wchar_t* buf, unsigned int count,
                                     const wchar_t* fmt, va_list ap);          // 0x939950

// @ 0x009014c0
bool EA::XML::XmlTextWriter::WriteEscapedString(wchar_t const * str)
{    const wchar_t* start = str;
    wchar_t c = *str;
    if (c != 0) {
        do {
            switch (c) {
            case L'"':
            case L'&':
            case L'\'':
            case L'<':
            case L'>':
                if (start < str && !WriteText(start, (str - start)))
                    return false;
                switch (c) {
                case L'&':  if (!WriteText(L"&amp;", 5))  return false;
                case L'<':  if (!WriteText(L"&lt;", 4))   return false;
                case L'>':  if (!WriteText(L"&gt;", 4))   return false;
                case L'"':  if (!WriteText(L"&quot;", 6)) return false;
                case L'\'': if (!WriteText(L"&apos;", 6)) return false;
                }
                start = str + 1;
                break;
            default:
                break;
            }
            c = str[1];
            ++str;
        } while (c != 0);
        if (start < str && !WriteText(start, (str - start)))
            return false;
    }
    return true;
}

// @ 0x00901630
bool EA::XML::XmlTextWriter::CloseCurrentElement()
{
    switch (mnState) {
    case kStateElement:
        if (!WriteText(L">", 1)) return false;
        break;
    case kStatePI:
        if (!WriteText(L"?>", 2)) return false;
        break;
    case kStateCDATA:
        if (!WriteText(L"]]>", 3)) return false;
        break;
    default:
        break;
    }
    mnState = kStateChars;
    return true;
}

// @ 0x00901690
bool EA::XML::XmlTextWriter::BeginProcessingInstruction(wchar_t const * s)
{
    if (CloseCurrentElement()) {
        if (WriteText(L"<?", 2)) {
            int n = (int)wcslen(s);
            if (WriteText(s, n)) {
                mbSimpleElement = 0;
                mnState = kStatePI;
                return true;
            }
        }
    }
    return false;
}

// @ 0x00901700
bool EA::XML::XmlTextWriter::EndProcessingInstruction()
{
    EState s = mnState;
    mbSimpleElement = 0;
    switch (s) {
    case kStatePI:
        mnState = kStateChars;
        return WriteText(L"?>", 2);
    case kStateChars:
    case kStateElement:
        mnState = kStateChars;
        return false;
    case kStateCDATA:
        return false;
    default:
        return false;
    }
}

// @ 0x00901740
bool EA::XML::XmlTextWriter::AppendAttribute(wchar_t const * name, wchar_t const * value)
{
    if (mnState != kStateElement && mnState != kStatePI)
        return false;
    return (WriteText(L" ", 1)
         && WriteName(name)
         && WriteText(L"=\"", 2)
         && WriteEscapedString(value)
         && WriteText(L"\"", 1)) ? 1 : 0;
}

// @ 0x009017d0
bool __cdecl EA::XML::XmlTextWriter::AppendAttributeF(wchar_t const * name, wchar_t const * fmt, ...)
{
    if (this->mnState != kStateElement && this->mnState != kStatePI)
        return false;
    wchar_t buf[256];
    va_list ap;
    va_start(ap, fmt);
    int n = Vsnprintf16(buf, 256, fmt, ap);
    va_end(ap);
    if (n >= 256)
        return false;
    return (this->WriteText(L" ", 1)
         && this->WriteName(name)
         && this->WriteText(L"=\"", 2)
         && this->WriteEscapedString(buf)
         && this->WriteText(L"\"", 1)) ? 1 : 0;
}

// @ 0x009018a0
int EA::XML::XmlTextWriter::WriteCharData(wchar_t const * s)
{
    if (CloseCurrentElement()) {
        if (WriteEscapedString(s))
            return 1;
    }
    return 0;
}

// @ 0x009018d0
bool EA::XML::XmlTextWriter::WriteCDATA(wchar_t const * s)
{
    if (mnState != kStateCDATA) {
        if (!CloseCurrentElement())
            return false;
        if (!WriteText(L"<![CDATA[", 9))
            return false;
        mnState = kStateCDATA;
    }
    int n = (int)wcslen(s);
    return WriteText(s, n);
}

// @ 0x00901930
bool EA::XML::XmlTextWriter::WriteName(wchar_t const * s)
{
    int n = (int)wcslen(s);
    return WriteText(s, n);
}

// @ 0x00901960
bool EA::XML::XmlTextWriter::WriteXmlHeader()
{
    bool ok = BeginProcessingInstruction(L"<?xml") && AppendAttribute(L"version", L"1.0");
    switch (mOutputEncoding) {
    default:
        if (ok && !AppendAttribute(L"encoding", L"UTF-8")) return false;
        break;
    case 3:
        if (ok && !AppendAttribute(L"encoding", L"US-ASCII")) return false;
        break;
    case 2:
        if (ok && !AppendAttribute(L"encoding", L"ISO-8859-1")) return false;
        break;
    case 1:
        if (ok && !AppendAttribute(L"encoding", L"UTF-16")) return false;
        break;
    }
    if (!EndProcessingInstruction()) return false;
    return true;
}

// @ 0x00901a10
EA::XML::XmlTextWriter::XmlTextWriter(bool bPretty, EA::XML::XmlTextWriter::OutputEncoding nEncoding)
{
    mOutputEncoding = nEncoding;
    *(void**)this = (void*)g_143a1c0;  // XmlTextWriter vtable
    mbFormatPretty = bPretty;
    mbSimpleElement = 0;
    mnState = kStateChars;
    mnIndentLevel = 0;
    mnIndentSpaces = 2;
    mLineEnd = kLineEndWindows;
    mpOutputStream.mpObject = 0;
}

// @ 0x00901a50
EA::XML::XmlTextWriter::~XmlTextWriter()
{
    *(void**)this = (void*)g_143a1c0;  // XmlTextWriter vtable
    if (mpOutputStream.get() != 0) {
        EA::IO::IStream* p = mpOutputStream.get();
        p->Release();
    }
}

// @ 0x00901a70
bool EA::XML::XmlTextWriter::WriteIndent()
{
    if (!mbFormatPretty)
        return true;
    int n = 2 - (mLineEnd != 1);
    int max = 0x43 - n;
    int count = mnIndentSpaces * mnIndentLevel;
    const wchar_t* sEnd = L"\r\n                                                                ";
    if (count > 0) {
        int chunk = (max <= count) ? max : count;
        if (!WriteText(sEnd, chunk + n))
            return false;
        count -= chunk;
        if (count > 0) {
            do {
                chunk = (max <= count) ? max : count;
                if (!WriteText(sEnd + n, chunk))
                    return false;
                count -= chunk;
            } while (count > 0);
        }
    }
    return true;
}

// @ 0x00901b30
bool EA::XML::XmlTextWriter::BeginElement(wchar_t const * name)
{
    if (CloseCurrentElement()) {
        if (WriteIndent()) {
            if (WriteText(L"<", 1)) {
                if (WriteName(name)) {
                    ++mnIndentLevel;
                    mnState = kStateElement;
                    mbSimpleElement = 1;
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x00901b90
bool EA::XML::XmlTextWriter::EndElement(wchar_t const * name)
{
    EState s = mnState;
    --mnIndentLevel;
    switch (s) {
    case kStateElement:
        mnState = kStateChars;
        mbSimpleElement = 0;
        return WriteText(L"/>", 2);
    case kStateCDATA:
        CloseCurrentElement();
        // fall through
    case kStateChars:
        if (mbSimpleElement == 0) {
            if (!WriteIndent())
                return false;
        }
        break;
    case kStatePI:
        return false;
    default:
        return false;
    }
    mbSimpleElement = 0;
    return (WriteText(L"</", 2)
         && WriteText(name, wcslen(name))
         && WriteText(L">", 1)) ? 1 : 0;
}

// @ 0x00901c60
bool EA::XML::XmlTextWriter::WriteComment(wchar_t const * s, bool bIndent)
{
    const wchar_t* p = s;
    const wchar_t* start = s;
    if (!CloseCurrentElement())
        return false;
    if (bIndent != 0) {
        if (!WriteIndent())
            return false;
    }
    if (!WriteText(L"<!-- ", 5))
        return false;
    wchar_t c = *p;
    if (c != 0) {
        do {
            ++p;
            if (c == L'-') {
                if (start < p && !WriteText(start, (p - start) + 1))
                    return false;
                while (*p == L'-')
                    ++p;
            }
            c = *p;
        } while (c != 0);
        if (start < p && !WriteText(start, (p - start)))
            return false;
    }
    return WriteText(L" -->", 4) != 0;
}

// @ 0x00901d30
void EA::XML::XmlTextWriter::SetOutputStream(EA::IO::IStream * pStream, bool bPretty)
{
    EA::IO::IStream* old = mpOutputStream.get();
    if (pStream != old) {
        if (pStream != 0)
            pStream->AddRef();
        mpOutputStream.mpObject = pStream;
        if (old != 0)
            old->Release();
    }
    mbFormatPretty = bPretty;
}

// @ 0x00901d90
bool EA::XML::XmlTextWriter::WriteText(wchar_t const * p, unsigned int n)
{
    EA::IO::IStream* stream = mpOutputStream.get();
    if (stream != 0) {
        // 0x143a2ac maps OutputEncoding to the EA text-encoding id IO_WriteEncoded expects.
        return IO_WriteEncoded(stream, p, n,
                               ((unsigned int*)g_143a2ac)[mOutputEncoding]);
    }
    return false;
}
