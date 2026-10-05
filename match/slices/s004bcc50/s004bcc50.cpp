// Slice s004bcc50: SP::cSPEditorResourceFactory::WriteResourceToStream (3069 bytes).
// Module flags: /Od /Ob1 /MD /Gy /TP (unoptimized; no C++ EH, no SSE).
//
// PARTIAL: this is a very large /Od XML serializer (0xa90-byte frame, dozens of
// inlined XmlTextWriter helpers). The file reproduces the top-level flow and the
// per-block/per-paint/per-handle element emission, but the exact helper set, the
// block-index fix-up arrays and the 0xa90-byte frame are not reproduced, so it is
// not claimed byte-exact (see partial.txt).
#include "types.h"

struct XmlTextWriter {
    XmlTextWriter();
    void Init(int a, int b);
    void WriteXmlHeader();
    void BeginElement(const wchar_t* name);
    bool EndElement(const wchar_t* name);
    void AppendAttributeF(const wchar_t* name, const wchar_t* fmt, int value);
    void WriteCharData(const char* text);
};

int WriteBinaryEditorModel(int data);                                    // 0x4b0010
bool FUN_004bfb20(void* factory, int data);                              // 0x4bfb20
void FUN_004c01b0();                                                     // 0x4c01b0
void FUN_00901a10(int a, int b);                                         // 0x901a10
void FUN_00901d30(void* factory, int a);                                 // 0x901d30
void FUN_004bee90(XmlTextWriter* w, const wchar_t* n, int v);            // 0x4bee90
void FUN_004bef40(XmlTextWriter* w, const wchar_t* n, float v);          // 0x4bef40
void FUN_004bef80(XmlTextWriter* w, const wchar_t* n, const void* v);    // 0x4bef80
void FUN_004bede0(XmlTextWriter* w, const wchar_t* n, uint32_t v);       // 0x4bede0
void XmlWriteHex(XmlTextWriter* w, const wchar_t* n, uint32_t v);
void XmlWriteBool(XmlTextWriter* w, const wchar_t* n, bool v);
void FUN_004c0570(uint32_t count, int v);                                // 0x4c0570
void FUN_004c0530(char* out, const char* fmt, uint32_t a, uint32_t b);   // 0x4c0530
void FUN_004c0b80();                                                     // 0x4c0b80
void FUN_00901a50();                                                     // 0x901a50
void FUN_004292a0();                                                     // 0x4292a0
void FormatFloat(char* out, float v);
bool operatorNE(const void* a, const void* b);
extern uint32_t g_attrCount;      // 0x013f01bc
extern char g_zeroUserOrient[];   // 0x015d88c0

// 004bcc50
bool FUN_004bcc50(void* factory, int data, int modelTypeHash) {
    int local_c = WriteBinaryEditorModel(data);
    if (local_c == 0)
        return false;
    if (modelTypeHash == 0x1a99b06b)
        return FUN_004bfb20(factory, data);

    XmlTextWriter writer;
    FUN_004c01b0();
    writer.Init(1, 0);
    FUN_00901d30(factory, 1);
    writer.WriteXmlHeader();
    writer.BeginElement(L"sporemodel");
    FUN_004bee90(&writer, L"formatversion", 0x12);
    writer.BeginElement(L"properties");

    int* props = (int*)(local_c + 0x18);
    XmlWriteHex(&writer, L"modeltype", (uint32_t)props[0]);
    if (props[2] != (int)0xcdcdcdcd &&
        (props[2] != 0 || props[3] != 0 || props[4] != 0)) {
        XmlWriteHex(&writer, L"skineffect1", (uint32_t)props[2]);
        XmlWriteHex(&writer, L"skineffect2", (uint32_t)props[3]);
        XmlWriteHex(&writer, L"skineffect3", (uint32_t)props[4]);
        FUN_004bee90(&writer, L"skineffectseed1", props[5]);
        FUN_004bee90(&writer, L"skineffectseed2", props[6]);
        FUN_004bee90(&writer, L"skineffectseed3", props[7]);
        FUN_004bef80(&writer, L"skincolor1", props + 8);
        FUN_004bef80(&writer, L"skincolor2", props + 0xb);
        FUN_004bef80(&writer, L"skincolor3", props + 0xe);
    }
    FUN_004bee90(&writer, L"zcorpscore", props[1]);
    writer.EndElement(L"properties");

    uint32_t count = (uint32_t)((*(int*)(local_c + 0x9c) - *(int*)(local_c + 0x98)) / 0x1d8);
    writer.BeginElement(L"blocks");
    writer.AppendAttributeF(L"count", (const wchar_t*)&g_attrCount, (int)count);
    FUN_004c0570(count, 0xffffffff);
    FUN_004c0570(count, 0xffffffff);

    for (uint32_t i = 0; i < count; ++i) {
        int* b = (int*)((int)i * 0x1d8 + *(int*)(local_c + 0x98));
        writer.BeginElement(L"blockref");
        char idbuf[64];
        FUN_004c0530(idbuf, "0x%08x, 0x%08x", (uint32_t)b[0], (uint32_t)b[1]);
        FUN_004bede0(&writer, L"blockid", (uint32_t)idbuf[0]);
        writer.BeginElement(L"transform");
        if (b[0x21] != 3) {
            FUN_004bee90(&writer, L"limbtype", b[0x21]);
            FUN_004bef40(&writer, L"musclescale", *(float*)&b[0x22]);
        }
        if (*(float*)&b[0x23] != 0.0f)
            FUN_004bef40(&writer, L"basemusclescale", *(float*)&b[0x23]);
        FUN_004bef40(&writer, L"scale", *(float*)&b[4]);
        FUN_004bef80(&writer, L"position", b + 5);
        FUN_004bef80(&writer, L"triangledirection", b + 8);
        FUN_004bef80(&writer, L"trianglepickorigin", b + 0xb);
        writer.BeginElement(L"orientation");
        FUN_004bef80(&writer, L"row0", b + 0xe);
        FUN_004bef80(&writer, L"row1", b + 0x11);
        FUN_004bef80(&writer, L"row2", b + 0x14);
        writer.EndElement(L"orientation");
        if (operatorNE(b + 0x17, g_zeroUserOrient)) {
            writer.BeginElement(L"userorientation");
            FUN_004bef80(&writer, L"userorientation_row0", b + 0x17);
            FUN_004bef80(&writer, L"userorientation_row1", b + 0x1a);
            FUN_004bef80(&writer, L"userorientation_row2", b + 0x1d);
            writer.EndElement(L"userorientation");
        }
        writer.EndElement(L"transform");
        XmlWriteBool(&writer, L"snapped", *(char*)(b + 0x20) != 0);
        if (b[0x35] != 0) {
            writer.BeginElement(L"paintlist");
            writer.AppendAttributeF(L"count", (const wchar_t*)&g_attrCount, b[0x35]);
            for (int p = 0; p < b[0x35]; ++p) {
                writer.BeginElement(L"paint");
                XmlWriteHex(&writer, L"paintregion", (uint32_t)b[p + 0x36]);
                XmlWriteHex(&writer, L"paintid", (uint32_t)b[p + 0x3e]);
                FUN_004bef80(&writer, L"color1", b + p * 3 + 0x46);
                FUN_004bef80(&writer, L"color2", b + p * 3 + 0x5e);
                writer.EndElement(L"paint");
            }
            writer.EndElement(L"paintlist");
        }
        if (b[0x24] != 0) {
            writer.BeginElement(L"handles");
            writer.AppendAttributeF(L"count", (const wchar_t*)&g_attrCount, b[0x24]);
            for (int h = 0; h < b[0x24]; ++h) {
                char fbuf[128];
                FormatFloat(fbuf, *(float*)&b[h + 0x25]);
                int channel = b[h + 0x2d];
                writer.BeginElement(L"weight");
                if (channel != 0)
                    writer.AppendAttributeF(L"channel", L"0x%08x", channel);
                writer.WriteCharData(fbuf);
                writer.EndElement(L"weight");
            }
            writer.EndElement(L"handles");
        }
        XmlWriteBool(&writer, L"isasymmetric", *(char*)((char*)b + 0x81) != 0);
        writer.EndElement(L"blockref");
    }
    writer.EndElement(L"blocks");
    bool result = writer.EndElement(L"sporemodel");
    FUN_004c0b80();
    FUN_004c0b80();
    FUN_00901a50();
    FUN_004292a0();
    return result;
}
