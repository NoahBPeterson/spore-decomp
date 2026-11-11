#ifndef MATCH_S00E8D0E0_CURSOR_H
#define MATCH_S00E8D0E0_CURSOR_H

#include "game/types.h"
#include "SP/cGameDataView.h"
#include "SP/cGameData.h"
#include "SP/cMWModel.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/ResourceMan/Key.h"

// The global layout adapters in this slice remain for its older bodies. This
// declaration recovers the native hierarchy and ownership for the constructor.
namespace SP {
class cSpatialObject;
namespace cursor_detail {
// Pointer-sized owning reference: its default constructor clears the pointer;
// destruction releases through the referent's actual reference-count contract.
template<class T> class AutoRefCount {
    T* mpObject;
public:
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& other) : mpObject(other.mpObject) {
        if (mpObject) mpObject->AddRef();
    }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* object) {
        if (object != mpObject) {
            T* old = mpObject;
            if (object) object->AddRef();
            mpObject = object;
            if (old) old->Release();
        }
        return *this;
    }
    AutoRefCount& operator=(const AutoRefCount& other) {
        return operator=(other.mpObject);
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
}

class cSpatialObjectView : public cGameDataView {
public:
    cSpatialObjectView();                                  // 0x00e92af0
    virtual ~cSpatialObjectView();                         // 0x00e92660
    virtual void HandleSimulationUpdate(uint32_t,uint32_t);// 0x00e92ca0
    virtual cGameDataView* MakeView(cGameData*);            // 0x00e92b50
    virtual cGameData* GetData();                          // 0x00e929f0
    virtual void SetIsVisible(bool);                       // 0x00e889f0
    virtual bool GetIsVisible() const;                     // 0x00e92c80
    virtual void SetIsInWorld(bool);                       // 0x00e92620
    virtual bool GetIsInWorld() const;                     // 0x00e92c60
    virtual const cGameData* GetData() const;               // 0x00e929f0
    // New overloaded virtuals are declared in reverse slot order.
    virtual void Init(cGameData*,cIModelWorld*,const EA::ResourceMan::Key&,const cSPColorRGB&); // 0x00e92740
    virtual void Init(cGameData*);                         // 0x00e92910
    virtual cMWModel* GetModel();                          // 0x00e929b0
    virtual void SetModel(cMWModel*,cIModelWorld*);         // 0x00e929d0

    cSpatialObject* mpObject;                              // 0x0c
    void* mpObjectCombatant;                               // 0x10
    bool mbSelected;                                      // 0x14
    cSPColorRGB mColor;                                          // 0x18
    EA::ResourceMan::Key mKey;                                        // 0x24
    bool mbIsInWorld;                                     // 0x30
    bool mbIsVisible;                                     // 0x31
    bool mbField32;                                       // 0x32
};

class cGameTerrainCursorView : public cSpatialObjectView {
public:
    cGameTerrainCursorView();
    virtual ~cGameTerrainCursorView();                     // 0x00e8d790
    virtual void HandleSimulationUpdate(uint32_t,uint32_t);// 0x00e8d880
    virtual cGameDataView* MakeView(cGameData*);            // 0x00e8de10
    virtual cGameData* GetData();                          // 0x008e7f80
    virtual void SetIsVisible(bool);                       // 0x00e8d740
    virtual bool GetIsVisible() const;                     // 0x00e8d760
    virtual void SetIsInWorld(bool);                       // 0x010829f0
    virtual bool GetIsInWorld() const;                     // 0x00b1fbf0
    virtual const cGameData* GetData() const;               // 0x008e7f80

    cursor_detail::AutoRefCount<cGameData> mpCursor;        // 0x34
    cursor_detail::AutoRefCount<cMWModel> mpModel;          // 0x38
    cursor_detail::AutoRefCount<EA::UTFWin::IWindow> mpWindow;// 0x3c
};
typedef char SpatialViewSize[(sizeof(cSpatialObjectView)==0x34)?1:-1];
typedef char CursorViewSize[(sizeof(cGameTerrainCursorView)==0x40)?1:-1];
}

#endif
