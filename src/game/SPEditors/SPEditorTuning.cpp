// src/game/SPEditors/SPEditorTuning.cpp -- migrated from slice(s) s005dbd20 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorTuning.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cAppModeEditorBase.h"
#include "cSPColorRGB.h"
#include "cSPColorRGBA.h"
#include "SP/cSPEditorTuning.h"
#include "SP/cSPUIAssetBrowser.h"
#include "SP/cSPUIAssetBrowserCallback.h"
#include "cSPUILayout.h"
#include "cSPUITooltipWinProc.h"
#include "SP/cString.h"

// ---- items of slice s005dbd20 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPColorRGB_s005d_bd20 { float r, g, b; };
struct cSPColorRGBA_s005d_bd20 { float r, g, b, a; };
namespace EA {
namespace ResourceMan {
struct Key_s005d_bd20 { uint32_t mInstance, mType, mGroup; };
}
}
using EA::ResourceMan::Key_s005d_bd20;
namespace App {
class Property {
public:
    float* GetValueFloat();          // 0x0041EA70
    uint16_t pad[9];
    uint16_t mnType;                 // +0x12 (0xd = float)
};
}
namespace App {
class PropertyList {
public:
    virtual int AddRef();
    virtual int Release();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(uint32_t propertyID, Property*& result);   // +0x24
};
}
namespace SP {
bool GetPropertyAsColorRGB(App::PropertyList* pList, uint32_t propertyID, cSPColorRGB_s005d_bd20* pValue);     // 0x006A11B0
}
namespace SP {
bool GetPropertyAsColorRGBA(App::PropertyList* pList, uint32_t propertyID, cSPColorRGBA_s005d_bd20* pValue);   // 0x006A1200
}
namespace SP {
bool GetPropertyAsKey(App::PropertyList* pList, uint32_t propertyID, Key_s005d_bd20* pValue);                 // 0x006A1250
}
namespace SP {
inline bool GetPropertyAsFloat(App::PropertyList* pList, uint32_t propertyID, float& value)
{
    App::Property* pProp;
    if (pList && pList->GetProperty(propertyID, pProp) && pProp->mnType == 0xd) {
        value = *pProp->GetValueFloat();
        return true;
    }
    return false;
}
}
namespace SP {
class cSPEditorTuning_s005d_bd20 {
public:
    void LoadTuningValues(App::PropertyList* pList);  // 0x005dbd20 (SP::cSPEditorTuning::LoadTuningValues)

    void* vftable;                            // +0x0
    cSPColorRGB_s005d_bd20 mSpineHandleColor;            // +0x4
    float mSpineHandleSize;                   // +0x10
    float mSpineHandleAlpha;                  // +0x14
    float mSpineHandleOverdrawAlpha;          // +0x18
    float mSpineHandleDistance;               // +0x1c
    cSPColorRGBA_s005d_bd20 mVertebraTorsoRolloverColor; // +0x20
    cSPColorRGBA_s005d_bd20 mVertebraTorsoSelectedColor; // +0x30
    cSPColorRGBA_s005d_bd20 mVertebraHighlightColor;     // +0x40
    cSPColorRGBA_s005d_bd20 mVertebraUnselectedColor;    // +0x50
    Key_s005d_bd20 mRotationBallHandleTuningKey;         // +0x60
    Key_s005d_bd20 mDeformHandleTuningKey;               // +0x6c
    Key_s005d_bd20 mBallConnectorHandleTuningKey;        // +0x78
    Key_s005d_bd20 mUnknownKey84;                        // +0x84
    Key_s005d_bd20 mRotationRingHandleTuningKey;         // +0x90
    Key_s005d_bd20 mUnknownKey9C;                        // +0x9c
    Key_s005d_bd20 mUnknownKeyA8;                        // +0xa8
    float mVertebraFadeTime;                  // +0xb4
};
}
// ---- items of slice s005dbd20 end

// @ 0x005dbd20
void SP::cSPEditorTuning_s005d_bd20::LoadTuningValues(App::PropertyList* pList)
{
    SP::GetPropertyAsColorRGB(pList, 0x04DC44CB, &mSpineHandleColor);
    SP::GetPropertyAsFloat(pList, 0x04DC44CC, mSpineHandleSize);
    SP::GetPropertyAsFloat(pList, 0x04DC44CD, mSpineHandleAlpha);
    SP::GetPropertyAsFloat(pList, 0x04DC44CE, mSpineHandleOverdrawAlpha);
    SP::GetPropertyAsFloat(pList, 0x04DC44CF, mSpineHandleDistance);
    SP::GetPropertyAsColorRGBA(pList, 0x04FE1603, &mVertebraTorsoRolloverColor);
    SP::GetPropertyAsColorRGBA(pList, 0x04FE1604, &mVertebraTorsoSelectedColor);
    SP::GetPropertyAsColorRGBA(pList, 0x04FE1605, &mVertebraHighlightColor);
    SP::GetPropertyAsColorRGBA(pList, 0x04FE1606, &mVertebraUnselectedColor);
    SP::GetPropertyAsFloat(pList, 0x04FE1607, mVertebraFadeTime);
    SP::GetPropertyAsKey(pList, 0x050FC283, &mRotationBallHandleTuningKey);
    SP::GetPropertyAsKey(pList, 0x050FC284, &mRotationRingHandleTuningKey);
    SP::GetPropertyAsKey(pList, 0x050FC286, &mUnknownKeyA8);
    SP::GetPropertyAsKey(pList, 0x050FC285, &mUnknownKey9C);
    SP::GetPropertyAsKey(pList, 0x050FC287, &mDeformHandleTuningKey);
    SP::GetPropertyAsKey(pList, 0xB8E88BEC, &mBallConnectorHandleTuningKey);
    SP::GetPropertyAsKey(pList, 0x3042E156, &mUnknownKey84);
}
