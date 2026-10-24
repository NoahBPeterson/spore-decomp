// Slice s004bd850 (cEditorModelParser XML callbacks + cSPEditorUI type map).
// Module flags: /Od /Ob1 /MD /Gy /TP (unoptimized; no C++ EH, no SSE).
#include <wchar.h>
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

// @ 0x004bd850
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

// @ 0x004bdae0
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

__declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int);

// The original expands wcscmp inline (compiler intrinsic: two characters per pass, sbb result).
#pragma intrinsic(wcscmp)

extern void FUN_00903550(void* parser, int arg);   // 0x903550 (XML_StopParser-style, cdecl)
struct ParserBlockOps {
    void AddBlock(int index);                      // 0x004be420 (thiscall, ret 4)
};
struct ParserModelBlocks {
    void Reserve(uint32_t count);                  // 0x004c0250 (thiscall, ret 4)
};

// 004bdcd0 SP::cEditorModelParser::StartElement (expat start-element callback)
// @ 0x004bdcd0
void cEditorModelParser_StartElement(void* userData, const wchar_t* name, const wchar_t** atts) {
    cEditorModelParser* nCount = (cEditorModelParser*)userData;
    unsigned long p15;
    const wchar_t** hi;
    const wchar_t* t22;
    const wchar_t* t26;
    const wchar_t** item;

    nCount->mBuffer[0] = 0;
    nCount->mLength = 0;
    nCount->mCursor = 0;
    if (wcscmp(name, L"blockref") == 0) {
        if (nCount->m3aa8 < 0x100) {
            nCount->m3aa4 = nCount->m3aa8;
            nCount->m3aa8 = nCount->m3aa8 + 1;
            ((ParserBlockOps*)nCount)->AddBlock(nCount->m3aa4);
        } else {
            FUN_00903550(nCount->mpXMLParser, 0);
        }
    } else if (wcscmp(name, L"blocks") == 0) {
        t22 = L"0";
        do {
            for (hi = atts; hi[0] && hi[1]; hi += 2) {
                if (wcscmp(hi[0], L"p15") == 0) {
                    t22 = hi[1];
                    break;
                }
            }
        } while (0);
        p15 = wcstoul(t22, 0, 0);
        if (p15 <= 0x100)
            ((ParserModelBlocks*)((char*)nCount->m3aa0 + 0x98))->Reserve(p15);
        else
            FUN_00903550(nCount->mpXMLParser, 0);
    } else if (wcscmp(name, L"weight") == 0) {
        t26 = L"0";
        do {
            for (item = atts; item[0] && item[1]; item += 2) {
                if (wcscmp(item[0], L"channel") == 0) {
                    t26 = item[1];
                    break;
                }
            }
        } while (0);
        nCount->m3aac = wcstoul(t26, 0, 0);
    }
}

// ---------------------------------------------------------------------------
// 004be100  expat end-element callback: FNV1 hash -> handler lookup in the
// 36-entry static table at 0x150c518 (element stride 0x18).
// ---------------------------------------------------------------------------
struct EditorModelElem {
    uint32_t        mHash;      // +0x00  FNV1 hash of the element name
    const wchar_t*  mpName;     // +0x04
    int             mKind;      // +0x08  0 = index-based target
    bool (__cdecl*  mpFn)(void* self, void* target, void* arg);   // +0x0c
    int             mOffset;    // +0x10  added to the resolved target
    void*           mpArg;      // +0x14
};

extern EditorModelElem g_editorModelElems[];    // 0x150c518, 36 entries
extern EditorModelElem* FUN_004c0600(EditorModelElem* first, EditorModelElem* last,
                                     const uint32_t* value, uint8_t ordered);  // 0x4c0600

// @ 0x004be100
// Semantics are complete and verified by the equivalence gate; the /Od slot layout is
// not byte-exact. The original frame is:
//   self -4, end -8, data -0xc, hash -0x10, item -0x14,
//   target -0x18, ok -0x19, ordered -0x1a,
// with `ordered` materialised as `xor eax,eax; mov [slot],al` (a 5-byte form this
// toolchain did not produce for any `bool` spelling tried), while the original's three
// tail slots are target -0x18, ok -0x19, ordered -0x1a. cl 15's /Od local order is
// driven by a hash of the local identifiers (docs/codegen.md §6.4); the identifiers
// that reproduce this frame were not found within budget, so the names here are the
// readable ones.
void FUN_004be100(void* userData, const wchar_t* name) {
    cEditorModelParser* self = (cEditorModelParser*)userData;
    uint32_t hash = EA_Hash_FNV1_String16(name, 0x811c9dc5, 0);

    EditorModelElem* data = g_editorModelElems;
    EditorModelElem* end  = data + 36;
    bool ordered = false;
    bool ok;
    int  target;
    EditorModelElem* item = FUN_004c0600(data, end, &hash, ordered);

    for (; item != end && item->mHash == hash; ++item) {
        if (wcscmp(item->mpName, name) == 0) {
            target = 0;
            if (item->mKind == 0) {
                if (self->m3aa4 == -1)
                    target = self->m3aa0 + 0x18;
            } else {
                if (self->m3aa4 != -1)
                    target = self->m3aa4 * 0x1d8 + *(int*)(self->m3aa0 + 0x98);
            }
            ok = (target != 0) && (item->mpFn(self, (char*)target + item->mOffset, item->mpArg) != 0);
            if (!ok) {
                FUN_00903550(self->mpXMLParser, 0);
                return;
            }
            break;
        }
    }
    self->mBuffer[0] = 0;
    self->mLength = 0;
    self->mCursor = 0;
}

// ---------------------------------------------------------------------------
// 004be420  cEditorModelParser::AddBlock(index): grow the model block vector
// at (m3aa0 + 0x98) to index+1 elements, then initialise the new tail blocks.
// ---------------------------------------------------------------------------
struct ModelBlock {                  // 0x1d8 bytes
    int   mField00;                  // +0x00
    int   mField04;                  // +0x04
    int   mField08;                  // +0x08
    int   mField0C;                  // +0x0c
    uint8_t mPad10[0x5c - 0x10];
    float mMatrix[3][3];             // +0x5c  (diagonal set to 1.0f)
    uint8_t mPad80[0x84 - 0x80];
    int   mField84;                  // +0x84
    uint8_t mPad88[0x1d8 - 0x88];
};

struct ModelBlockVec {
    int mpBegin;                     // +0x00  (first block address)
    int mpEnd;                       // +0x04
    int mpCapacity;                  // +0x08
    uint8_t mPad0C[0x14 - 0x0c];
    void Reserve(uint32_t count);    // 0x004afd00 (thiscall, ret 4)
};

extern "C" void* __cdecl memset_impl(void* dst, int value, uint32_t n);   // 0x11e073e

extern float HK_REAL_ONE;   // 0x1485720  (_HK_REAL_ONE, Havok's 1.0f)

// @ 0x004be420
void ParserBlockOps::AddBlock(int index) {
    ModelBlockVec* pVec = (ModelBlockVec*)(((cEditorModelParser*)this)->m3aa0 + 0x98);
    int count = (pVec->mpEnd - pVec->mpBegin) / 0x1d8;
    if (count <= index) {
        int newCount = index + 1;
        pVec->Reserve(newCount);
        ModelBlock* base = (ModelBlock*)pVec->mpBegin;
        memset_impl((char*)base + count * 0x1d8, 0, (newCount - count) * 0x1d8);
        for (int i = count; i < newCount; ++i) {
            ModelBlock* e = &base[i];
            e->mField00 = -1;
            e->mField04 = -1;
            e->mField08 = -1;
            e->mField0C = -1;
            e->mMatrix[0][0] = HK_REAL_ONE;
            e->mMatrix[1][1] = HK_REAL_ONE;
            e->mMatrix[2][2] = HK_REAL_ONE;
            e->mField84 = 3;
        }
    }
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
