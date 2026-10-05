// Slice s004bd850 (cEditorModelParser XML callbacks + cSPEditorUI type map).
// Module flags: /Od /Ob1 /MD /Gy /TP (unoptimized; no C++ EH, no SSE).
#include "types.h"

// ---------------------------------------------------------------------------
// 004bd850  SP::cSPEditorUI::ShowDialogWithValidityReason: hash -> dialog id.
// ---------------------------------------------------------------------------
extern uint32_t g_15d86fc;
extern uint32_t g_15d860c;
extern uint32_t g_15d86d8;
extern uint32_t g_15d884c;
extern uint32_t g_15d8a40;
extern uint32_t g_15d86e4;
extern uint32_t g_15d87bc;
extern uint32_t g_15d8608;

struct PackedKey {
    uint32_t b0 : 8;
    uint32_t b1 : 8;
    uint32_t b2 : 8;
    uint32_t b3 : 6;
    uint32_t b4 : 2;
};
union PackedKeyUnion {
    uint32_t raw;
    PackedKey f;
};

uint32_t FUN_004bd850(uint32_t key) {
    switch (key) {
    case 0x6fd7d545: {
        PackedKeyUnion u;
        u.raw = 0;
        u.f.b4 = 1;
        u.f.b2 = 0x60;
        u.f.b1 = 0x60;
        return u.raw;
    }
    case 0xe67cff28: return g_15d86fc;
    case 0xf1fac055: return g_15d860c;
    case 0x3d0706da: return g_15d86d8;
    case 0x9735dda7: return g_15d86d8;
    case 0x3673ceff: return g_15d884c;
    case 0x326ba4c4: return g_15d860c;
    case 0x8c6f7366: return g_15d8a40;
    case 0xffbbdaee: return g_15d86e4;
    case 0x3d644e05: return g_15d87bc;
    case 0x46f485f5: return g_15d8608;
    default: return key;
    }
}

// 004bd9c0
int FUN_004bd9c0(int param) {
    switch (param) {
    case 0x5e49ce2c: return 0xd05c53a3;
    default: return param;
    }
}

// ---------------------------------------------------------------------------
// cEditorModelParser: 0x3a9c-byte prefix then the expat parser handle.
// ---------------------------------------------------------------------------
struct cEditorModelParser;
__declspec(thread) int g_tls_dummy;
__declspec(thread) cEditorModelParser* g_pCurrentParser;

struct cEditorModelParser {
    char pad[0x3a9c];
    void* mpXMLParser;        // +0x3a9c
    int m3aa0;                // +0x3aa0
    int m3aa4;                // +0x3aa4
    int m3aa8;                // +0x3aa8
    int m3aac;                // +0x3aac
    uint16_t mBuffer[0x400];  // +0x3ab0
    int mLength;              // +0x42b0
    int mCursor;              // +0x42b4

    int FUN_004bdbd0();
    void FUN_004bdae0();                            // 004bdae0
    void FUN_004bd9f0(int param);                   // 004bd9f0
    int FUN_004bdc00(int param);                    // 004bdc00
    bool FUN_004bdc60(int a, int b, uint8_t c);     // 004bdc60
    bool ReadULong(unsigned long* out);   // 004be380
    bool ReadFloat(float* out);           // 004be2e0
};

extern void* FUN_0090aed0(int a, void* table, int b);            // 0x90aed0
extern void FUN_009032e0(void* parser, void* thiz);              // 0x9032e0
extern void FUN_00903300(void* parser, void* start, void* end);  // 0x903300
extern void FUN_00903320(void* parser, void* cb);                // 0x903320
extern char PTR_FUN_0150c50c[];
extern void StartElementCb();   // 0x4bdcd0
extern void EndElementCb();     // 0x4be100
extern void CharDataCb();       // 0x4be070

// 004bdae0 -- teardown: free the expat parser and re-create the inline buffer.
struct FBAStub {
    void* mpBufferInfo;
    FBAStub* Create(void* pBuffer, uint32_t size, uint8_t bShared);
    void destroy_shared();
};
extern void FUN_009055d0(void* parser);   // XML_ParserFree, 0x9055d0

FBAStub* FBAStub::Create(void* pBuffer, uint32_t size, uint8_t bShared) {
    (void)pBuffer; (void)size; (void)bShared;
    return this;
}
void FBAStub::destroy_shared() {
}

void cEditorModelParser::FUN_004bdae0() {
    if (mpXMLParser != 0) {
        g_pCurrentParser = this;
        FUN_009055d0(mpXMLParser);
        mpXMLParser = 0;
        g_pCurrentParser = 0;
        FBAStub* fba = (FBAStub*)this;
        if (fba->mpBufferInfo != 0 &&
            (*(int*)((char*)fba->mpBufferInfo + 0x10) & 0x40000000) != 0)
            fba->destroy_shared();
        fba->mpBufferInfo = 0;
        fba->Create((char*)this + 4, 0x3a98, 0);
    }
    m3aa0 = 0;
}

// ---------------------------------------------------------------------------
// Large expat callbacks: reproduced only as skeletons (see partial.txt).
// ---------------------------------------------------------------------------
extern uint32_t EA_Hash_FNV1_String16(const void* s, uint32_t seed, int);  // 0x932f30

// 004bdcd0 SP::cEditorModelParser::StartElement  (PARTIAL skeleton)
bool cEditorModelParser_StartElement(void* self, const void* name, const void* atts) {
    (void)self; (void)name; (void)atts;
    return false;
}

// 004be100  (PARTIAL skeleton)
bool FUN_004be100(void* self, const uint16_t* name) {
    uint32_t hash = EA_Hash_FNV1_String16(name, 0x811c9dc5, 0);
    (void)self; (void)hash;
    return false;
}

// 004be420  (PARTIAL skeleton)
void FUN_004be420(void* self, int index) {
    (void)self; (void)index;
}

// 004bd9f0
void cEditorModelParser::FUN_004bd9f0(int param) {
    g_pCurrentParser = this;
    mpXMLParser = FUN_0090aed0(0, PTR_FUN_0150c50c, 0);
    FUN_009032e0(mpXMLParser, this);
    FUN_00903300(mpXMLParser, (void*)StartElementCb, (void*)EndElementCb);
    FUN_00903320(mpXMLParser, (void*)CharDataCb);
    g_pCurrentParser = 0;
    m3aa0 = param;
    m3aa4 = -1;
    m3aa8 = 0;
    mLength = 0;
    mCursor = 0;
}

extern int FUN_00903400(void* parser, int param);                       // 0x903400
extern int FUN_00905740(void* parser, int a, int b, int c);             // 0x905740

// 004bdc00
int cEditorModelParser::FUN_004bdc00(int param) {
    g_pCurrentParser = this;
    int result = FUN_00903400(mpXMLParser, param);
    g_pCurrentParser = 0;
    return result;
}

// 004bdc60
bool cEditorModelParser::FUN_004bdc60(int a, int b, uint8_t c) {
    g_pCurrentParser = this;
    bool result = FUN_00905740(mpXMLParser, a, b, c) == 1;
    g_pCurrentParser = 0;
    return result;
}

__declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int);
extern float FUN_0092ddc0(const wchar_t*, wchar_t**);   // 0x92ddc0

// 004be2e0
bool cEditorModelParser::ReadFloat(float* out) {
    wchar_t* local_4 = (wchar_t*)((char*)mBuffer + mCursor * 2);
    *out = FUN_0092ddc0((wchar_t*)((char*)mBuffer + mCursor * 2), &local_4);
    if (local_4 == (wchar_t*)((char*)mBuffer + mCursor * 2))
        return false;
    if (*local_4 == L',')
        local_4++;
    mCursor = (int)((char*)local_4 - (char*)mBuffer) >> 1;
    return true;
}

// 004be380
bool cEditorModelParser::ReadULong(unsigned long* out) {
    wchar_t* local_8 = (wchar_t*)((char*)mBuffer + mCursor * 2);
    *out = wcstoul((wchar_t*)((char*)mBuffer + mCursor * 2), &local_8, 0);
    if (local_8 == (wchar_t*)((char*)mBuffer + mCursor * 2))
        return false;
    if (*local_8 == L',')
        local_8++;
    mCursor = (int)((char*)local_8 - (char*)mBuffer) >> 1;
    return true;
}

extern int FUN_00903b40(void* parser);   // 0x903b40

// 004bdbd0
int cEditorModelParser::FUN_004bdbd0() {
    if (mpXMLParser)
        return FUN_00903b40(mpXMLParser);
    return -1;
}

// 004be070 -- append n UTF-16 units into the parser's 0x400-unit scratch buffer.
extern "C" void* __cdecl memcpy_impl(void* dst, const void* src, uint32_t n);  // 0x11e0744

// 004be070 -- free function (cdecl): append n UTF-16 units into the parser buffer.
void FUN_004be070(void* self, const void* src, int n) {
    void* p = self;
    if ((uint32_t)(*(int*)((char*)p + 0x42b0) + n) > 0x3ff)
        n = 0x3ff - *(int*)((char*)p + 0x42b0);
    void* dst = (char*)p + *(int*)((char*)p + 0x42b0) * 2 + 0x3ab0;
    memcpy_impl(dst, src, n * 2);
    *(int*)((char*)p + 0x42b0) = *(int*)((char*)p + 0x42b0) + n;
    *(uint16_t*)((char*)p + *(int*)((char*)p + 0x42b0) * 2 + 0x3ab0) = 0;
}
