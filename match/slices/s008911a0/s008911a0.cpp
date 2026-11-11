// Slice s008911a0: EA::Text::OutlineFont vtable leaf accessors.
// Built /O2 /MD /Gy /TP /arch:SSE /GS- /fp:fast (UTFSpore manager2.obj family, no /EHsc).
#include "types.h"

namespace EA { namespace Text {

// OutlineFont: EA::Text::Font (0x48 bytes) followed by the OTF/member block.
// Only the fields read by these accessors are named (retail +0xa0/+0xa4).
class OutlineFont {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual int v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();

    uint32_t pad004[0x27];       // +0x004 .. +0x09f
    int32_t  mnBitmapFormat;     // +0xa0   (1 = outlined)
    int32_t  mnEffect;           // +0xa4   (non-zero: effects rasterise into a 32-bit surface)
};

// @ 0x008911a0
int OutlineFont::v09()
{
    if (mnEffect == 0) {
        int n = mnBitmapFormat - 1;
        return n != 0 ? 1 : 8;
    }
    return 0x20;
}

}}  // namespace EA::Text
