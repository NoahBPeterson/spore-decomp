// Slice s00951c60 -- EA::UTFWin::InitFontSystem: bind the default text style and layout to the
// UTFSpore font manager's selection, once, when the 2D system exists.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// A UTF-16 string copy helper inlined by the original: copy through the NUL terminator.
inline void ScopyStr16(wchar_t* pDst, const wchar_t* pSrc)
{
    wchar_t c;
    int i = 0;
    do
    {
        c = pSrc[i];
        pDst[i] = c;
        i += 1;
    }
    while (c != 0);
}

struct I2DSystemID;                       // opaque: only the non-null test is needed

extern I2DSystemID* g_pI2DSystem;         // 0x0166aab8
extern bool  g_fontSystemInited;          // 0x0166aabc
extern const wchar_t g_sFontFamily[];     // 0x0140af84 L"Arial"
extern const wchar_t g_sFontFamilyUnicode[]; // 0x01440424 L"Arial Unicode MS"
extern char  g_defaultTextStyle[];        // 0x0166ae78 (EA::Text::TextStyle)
extern float g_defaultFontSize;           // 0x0166b078
extern int   g_defaultLineSpacing;        // 0x0166b08c
extern bool  g_textStyleDirty;            // 0x0166ae69
extern const float g_kFontSize10;         // 0x01473c70 (10.0f)

const void* __cdecl GetDefaultLayout(bool bUnicode);   // 0x00885ad0

// The layout object at 0x0166aaf8 (EA::Text::Layout); only its call sites matter here.
struct TextLayout {
    void Assign(const void* pSrc);                                                    // 0x0089d300
    void UpdateFontSelection(const void* pTextStyle, void* pFontSelection,
                             void* pFontServer);                                      // 0x0088ffa0
};
extern TextLayout g_defaultTextLayout;     // 0x0166aaf8 (EA::Text::Layout)

// @ 0x00951c60
void __cdecl InitFontSystem()
{
    if (g_pI2DSystem != 0 && !g_fontSystemInited)
    {
        g_fontSystemInited = true;
        ScopyStr16((wchar_t*)(g_defaultTextStyle + 0x00), g_sFontFamily);
        ScopyStr16((wchar_t*)(g_defaultTextStyle + 0x40), g_sFontFamilyUnicode);
        g_defaultFontSize = g_kFontSize10;
        g_defaultLineSpacing = 0;
        g_defaultTextLayout.Assign(GetDefaultLayout(true));
        g_textStyleDirty = true;
        g_defaultTextLayout.UpdateFontSelection(g_defaultTextStyle, 0, 0);
    }
}
