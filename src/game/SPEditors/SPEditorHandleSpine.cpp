// src/game/SPEditors/SPEditorHandleSpine.cpp -- migrated from slice(s) s005a7d00 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorHandleSpine.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPEditorHandleSpine.h"
#include "SP/cIModelWorld.h"
#include "SP/cMWModel.h"
#include "cSPBoundingBox.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorHandle.h"
#include "SP/cSPEditorLimbJoint.h"
#include "cSPMatrix3.h"
#include "cSPVector3.h"
#include <intrin.h>
#include <math.h>
#include "SP/cModelManager.h"

// ---- items of slice s005a7d00 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
namespace EA {
template <typename T>
class RefCountVTemplate_s005a_7d00 {
public:
    RefCountVTemplate_s005a_7d00() : mnRefCount(0) {}
    virtual ~RefCountVTemplate_s005a_7d00() {}
    virtual int AddRef() { return ++mnRefCount; }
    virtual int Release() { int n = (*(volatile int*)&mnRefCount += -1); if (n == 0) { mnRefCount = 1; delete this; return 0; } return mnRefCount; }
    T mnRefCount;
};
}
namespace EA {
namespace COM {
 class IUnknown32_s005a_7d00 {
     public: virtual int AddRef() = 0;
     virtual int Release() = 0;
 };
}
}
namespace SP {
struct cSPVector3 { float x, y, z; cSPVector3() {} cSPVector3(float a, float b, float c) : x(a), y(b), z(c) {} cSPVector3(const cSPVector3& c) : x(c.x), y(c.y), z(c.z) {} };
}
namespace SP {
struct cSPMatrix3 { float m[9]; cSPMatrix3() {} cSPMatrix3(const cSPMatrix3&); void Assign(const cSPMatrix3&); };  // 0x0041cb40
}
namespace SP {
class cMWModel_s005a_7d00 { public: char pad[0x44]; unsigned mGroups[2]; };
}
namespace SP {
class cModelManager_s005a_7d00 { public: PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    virtual unsigned GetGroupIndex(unsigned key, int flag); };  // +0x28
}
namespace SP {
cModelManager_s005a_7d00* ModelManager();  // 0x0067dd80
}
namespace SP {
class cSPEditorBlock_s005a_7d00 {
public:
    char pad0[0x10];
    unsigned mId;               // +0x10
    char pad1[4];
    class cBoundsProvider* mProvider;  // +0x18
    char pad2[0x48 - 0x1c];
    cSPVector3 mPos;            // +0x48
    char pad3[0x60 - 0x54];
    cSPMatrix3 mRot;            // +0x60
};
}
namespace SP {
class cBoundsProvider {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
    virtual float* GetBounds(unsigned id);  // +0x60
};
}
namespace SP {
class cSPEditorHandle_s005a_7d00 : public EA::COM::IUnknown32_s005a_7d00, public EA::RefCountVTemplate_s005a_7d00<int> {
public:
    cSPEditorHandle_s005a_7d00();
    virtual ~cSPEditorHandle_s005a_7d00();
    void Shutdown();  // 0x0047e2c0
    void Init(void* p, int a, int b, int c);  // 0x0047db30
    char pad[0x10 - 0xc];
    cSPEditorBlock_s005a_7d00* mBlock;     // +0x10
    cMWModel_s005a_7d00* mModel;           // +0x14
    cMWModel_s005a_7d00* mOverdrawModel;   // +0x18
    char pad2[0x50 - 0x1c];
};
}
namespace SP {
class cSPEditorHandleSpine_s005a_7d00 : public cSPEditorHandle_s005a_7d00 {
public:
    cSPVector3 mOffset;   // +0x50
    cSPMatrix3 mOrient;   // +0x5c
    cSPEditorHandleSpine_s005a_7d00();
    virtual ~cSPEditorHandleSpine_s005a_7d00() { Shutdown(); }
    void Init(void* param, const cSPVector3* offset, const cSPMatrix3* orient);  // 0x005a8970
    cSPVector3* GetAttachPoint(cSPVector3* out);  // 0x005a8b20
};
}
// ---- items of slice s005a7d00 end

// @ 0x005a8970
void SP::cSPEditorHandleSpine_s005a_7d00::Init(void* param, const cSPVector3* offset, const cSPMatrix3* orient)
{
    cSPEditorHandle_s005a_7d00::Init(param, 1, 0, 0);
    if (mBlock) {
        cMWModel_s005a_7d00* model = mModel;
        *(int*)&mOffset.x = *(const int*)&offset->x;
        *(int*)&mOffset.y = *(const int*)&offset->y;
        *(int*)&mOffset.z = *(const int*)&offset->z;
        mOrient = *orient;
        if (model) {
            cModelManager_s005a_7d00* mgr = ModelManager();
            cMWModel_s005a_7d00* m = mModel;
            unsigned i = mgr->GetGroupIndex(0x31390734, 0);
            if (i < 0x40) m->mGroups[i >> 5] |= 1u << (i & 0x1f);
        }
        if (mOverdrawModel) {
            cModelManager_s005a_7d00* mgr = ModelManager();
            cMWModel_s005a_7d00* m = mOverdrawModel;
            unsigned i = mgr->GetGroupIndex(0x31390735, 0);
            if (i < 0x40) m->mGroups[i >> 5] |= 1u << (i & 0x1f);
            mgr = ModelManager();
            m = mOverdrawModel;
            i = mgr->GetGroupIndex(0x22fff11, 0);
            if (i < 0x40) m->mGroups[i >> 5] |= 1u << (i & 0x1f);
        }
    }
}
