#include "types.h"

#define PV(n) virtual void pv##n();

namespace SP {

struct Vector3 {
    float x;
    float y;
    float z;
};

struct cSpatialObject {
    PV(0)  PV(1)  PV(2)  PV(3)
    PV(4)  PV(5)  PV(6)  PV(7)
    PV(8)  PV(9)  PV(10)

    virtual const Vector3* GetPosition(); // +0x2C

    PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23)
    PV(24) PV(25) PV(26) PV(27)
    PV(28) PV(29) PV(30) PV(31)
    PV(32) PV(33) PV(34) PV(35)
    PV(36) PV(37) PV(38) PV(39)
    PV(40) PV(41) PV(42) PV(43)
    PV(44) PV(45) PV(46)

    virtual void AddRef();  // +0xBC
    virtual void Release(); // +0xC0
};

struct CameraController {
    void SetTargetPosition(
        const Vector3* position,
        int a,
        int b
    ); // 0x00B146A0
};

struct CameraInterface {
    PV(0) PV(1) PV(2)

    virtual CameraController* Query(unsigned int id); // +0x0C
};

struct CameraProvider {
    PV(0)  PV(1)  PV(2)  PV(3)
    PV(4)  PV(5)  PV(6)  PV(7)
    PV(8)  PV(9)  PV(10) PV(11)
    PV(12) PV(13) PV(14) PV(15)

    virtual CameraInterface* GetInterface(unsigned int id); // +0x40
};

struct SporeApp {
    PV(0)  PV(1)  PV(2)  PV(3)
    PV(4)  PV(5)  PV(6)  PV(7)
    PV(8)  PV(9)  PV(10) PV(11)
    PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19)

    virtual CameraProvider* GetCameraProvider(); // +0x50
};

SporeApp* __cdecl GetSporeApp(); // 0x0067DD10

struct cSPUIGlobalUI {
    void ShowOptionWindows(char show); // 0x00e042d0
};

struct cCivUIRoot {
    uint32_t        mPad00[0x64 / 4];
    cSPUIGlobalUI*  mpGlobalUI;       // +0x64
};

struct cCivTrackRoot {
    uint32_t mPad00[0x80 / 4];
    void*    mpTracked;               // +0x80
};

struct cCivModeStrategy {
    uint32_t        mPad00[0xe8 / 4];
    cCivTrackRoot*  mpTrackRoot;          // +0xE8
    cCivUIRoot*     mpUIRoot;             // +0xEC
    uint32_t        mPadF0;              // +0xF0
    cSpatialObject* mpCameraTrackObject; // +0xF4

    void SetCameraTrackObject(cSpatialObject* object);
    void ShowOptionWindows();
    bool HasActiveTrack();
};

struct cRangeOut {
    void*    mpFunc;
    uint32_t mArg;
};

bool __cdecl FUN_00d09660(void* track);

void __cdecl ForEachNode(
    cRangeOut* out,
    uint32_t* first,
    uint32_t* last,
    void (__fastcall* fn)(void*),
    uint32_t extra
);

// @ 0x00cf8d70
void cCivModeStrategy::SetCameraTrackObject(
    cSpatialObject* object
)
{
    CameraInterface* cameraInterface =
        GetSporeApp()
            ->GetCameraProvider()
            ->GetInterface(0xE3057616);

    if (cameraInterface) {
        CameraController* camera =
            cameraInterface->Query(0x011966ED);

        if (camera && object) {
            camera->SetTargetPosition(
                object->GetPosition(),
                1,
                1
            );
        }
    }

    cSpatialObject* previous = mpCameraTrackObject;

    if (object != previous) {
        if (object) {
            object->AddRef();
        }

        mpCameraTrackObject = object;

        if (previous) {
            previous->Release();
        }
    }
}

// @ 0x00cf8e00
void cCivModeStrategy::ShowOptionWindows()
{
    mpUIRoot->mpGlobalUI->ShowOptionWindows(1);
}

// @ 0x00cf94b0
bool cCivModeStrategy::HasActiveTrack()
{
    if (mpTrackRoot && mpTrackRoot->mpTracked) {
        if (FUN_00d09660(mpTrackRoot->mpTracked))
            return true;
    }
    return false;
}

// @ 0x00cf94e0
void __cdecl ForEachNode(
    cRangeOut* out,
    uint32_t* first,
    uint32_t* last,
    void (__fastcall* fn)(void*),
    uint32_t extra
)
{
    for (; first != last; ++first)
        fn((void*)(*first + extra));

    out->mpFunc = (void*)fn;
    out->mArg = extra;
}

} // namespace SP
