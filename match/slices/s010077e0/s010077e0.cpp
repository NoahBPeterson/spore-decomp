// s010077e0 -- SP::cSPSimulatorSpaceGame galaxy/solar/planet chase transitions.
//
// Reconstructed from the retail disassembly alone
// (work/match/scratch_s010077e0_cards.txt, work/match/scratch_s010077e0_helpers.txt).
// The dev-PDB headers under src/game/include/SP do NOT describe this build, so every
// member offset below comes from the observed code, not from a header.
//
//   0x010077e0  ChaseFromGalaxyToSolar    thiscall
//   0x01007bf0  ChaseFromSolarToPlanet    thiscall
//   0x01007ed0  ChaseFromPlanetToSolar    thiscall
//   0x01008100  ChaseFromSolarToGalaxy    thiscall
//   0x01008270  UpdateChasingUFOs         thiscall, one stack argument (ret 4)
//   0x01008820  TCopyForward              cdecl, eastl::copy_impl body
//   0x01008850  UFOArray::erase          thiscall (first,last), ret 8
//   0x010088e0  TCopyBackward             cdecl, eastl::copy_backward_impl body

#include <math.h>

// ---------------------------------------------------------------------------
// vector / quaternion types and the .rdata basis + chase constants
// ---------------------------------------------------------------------------

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };

extern const Vector3 kYAxis;           // 0x015b64c4  (0,1,0)
extern const Vector3 kZAxis;           // 0x015b64d0  (0,0,1)
extern const float   kDist100;         // 0x015b6888  100.0f
extern const float   kDist1000;        // 0x015b688c  1000.0f
extern const float   kDist500;         // 0x015b6890  500.0f
extern const float   kDist5;           // 0x015b6894  5.0f
extern const float   kNearTargetDist;  // 0x015b6898  state-6 approach threshold
extern const float   kNearPosDist;     // 0x01477fc0  300.0f
extern const float   kOrbitSpeed;      // 0x016dc720  per-UFO orbit angle seed scale
extern const Vector3 kChaseOffset;     // 0x016dc100  solar->galaxy destination offset
// other immediates read inline: 0.41176471f (7/17) @0x0149535c, 0.5f @0x01471064,
// 20.0f @0x015b64b4, 2.0f @0x01470f1c, 1.0f @0x01485720, sign mask @0x013eb8b0.

struct cSPGameDataUFO;
struct cCreatureData;

// ---------------------------------------------------------------------------
// cSpatialObject -- the spatial sub-object embedded at UFO+0x34
// ---------------------------------------------------------------------------

class cSpatialObject {
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual void v20();  virtual void v24();  virtual void v28();
    virtual const Vector3* GetPosition();              // +0x2c
    virtual void v30();  virtual void v34();
    virtual void SetPosition(const Vector3* pPos);     // +0x38
    virtual void v3c();
    virtual void Notify();                             // +0x40
    virtual void v44();  virtual void v48();  virtual void v4c();  virtual void v50();
    virtual void v54();  virtual void v58();
    virtual void GetPositionOut(Vector3* pOut);        // +0x5c
    virtual void v60();  virtual void v64();  virtual void v68();  virtual void v6c();
    virtual void v70();  virtual void v74();  virtual void v78();  virtual void v7c();
    virtual void v80();  virtual void v84();  virtual void v88();  virtual void v8c();
    virtual void v90();  virtual void v94();  virtual void v98();  virtual void v9c();
    virtual void vA0();  virtual void vA4();  virtual void vA8();
    virtual void* GetTarget();                         // +0xac
};

// ---------------------------------------------------------------------------
// cSPGameDataUFO -- the chased craft
// ---------------------------------------------------------------------------

class cSPGameDataUFO {
public:
    virtual int  AddRef();                // +0x00
    virtual int  Release();               // +0x04
    virtual void v08();  virtual void v0c();  virtual void v10();  virtual void v14();
    virtual void v18();  virtual void v1c();  virtual void v20();  virtual void v24();
    virtual void v28();
    virtual bool IsDestroyed();           // +0x2c

    // non-virtual interface (direct calls in the retail image)
    void SetDestination(const Vector3* pDest);       // 0x00c3bfe0
    void SetDestinationOffset(const Vector3* pOff);  // 0x00c381e0
    void PopToDestination();                         // 0x00c37e60
    void FlyTowards(const Vector3* pDest);           // 0x00c3dae0
    void OnContextChange(int context);               // 0x00c3a2b0
    bool FUN_00c370e0();                             // 0x00c370e0  post-flag retask test

    // data: the only virtual storage is the single vptr
    char            mPad04[0x34 - 0x04];
    cSpatialObject  mSpatial;          // +0x34
    char            mPad38[0x68c - 0x38];
    cSPGameDataUFO* mpCached68c;       // +0x68c  interceptor's cached player
    Vector3         mDir694;           // +0x694  heading / approach direction
    int             mAngleSeed6b0;     // +0x6b0  orbit phase seed
    Vector3         mVec6bc;           // +0x6bc  fallback destination
    char            mPad6c8[0x714 - 0x6c8];
    unsigned int    mState;            // +0x714  chase state (3..9)
    Vector3         mPos718;           // +0x718  current position
    char            mPad724[0x730 - 0x724];
    Quaternion      mOrientation;      // +0x730
    Vector3         mOffset740;        // +0x740
    char            mPad74c[0x750 - 0x74c];
    Vector3         mTargetPos750;     // +0x750
    void*           mp75c;             // +0x75c  host object, null <=> "no host"
    char            mPad760[0x77e - 0x760];
    bool            mb77e;             // +0x77e
    char            mPad77f[0x7b0 - 0x77f];
    void*           mp7b0;             // +0x7b0  record whose dword at +0x70 is a handle
};

// ---------------------------------------------------------------------------
// surrounding subsystems
// ---------------------------------------------------------------------------

class cStar {
public:
    bool   FUN_00c8b800();          // 0x00c8b800  refcount-based "background busy" test
    cStar* GetSolarSystem();        // 0x00c8b770
    float  FUN_00c84d40(int arg);   // 0x00c84d40  returns a float in st(0), ret 4
};

class cStarMap {
public:
    void RemoveVisual(unsigned int handle, unsigned int visualId, int a, int b); // 0x01045ae0
};

class cActivePlanet {
public:
    virtual void v00();  virtual void v04();  virtual void v08();  virtual void v0c();
    virtual void v10();  virtual void v14();  virtual void v18();  virtual void v1c();
    virtual void v20();  virtual void v24();  virtual void v28();
    virtual const Vector3* GetPosition();     // +0x2c
};

class cCivData {
public:
    Vector3* GetCities();            // 0x005c65e0  lea eax,[ecx+0x3c]; ret
};

class cSPUIMinimapWin {
public:
    void RemoveIcon(cSPGameDataUFO* pUfo, int a, int b);   // 0x00e0f9c0  ret 0xc
};

class cSpaceUI {
public:
    cSPUIMinimapWin* GetMinimap();   // 0x01067e60  returns this->mpMinimap (+0x31c)
};

// free services
cStar*         GetBackgroundSim();       // 0x01021230
cStarMap*      GetStarMap();             // 0x01046fc0
cCivData*      GetCurrentStar();         // 0x01021240
cActivePlanet* GetActivePlanet();        // 0x01021260
void  DestroyCreature(cCreatureData* cr, unsigned int flags);            // 0x0102c340
void  CreateMinimapIcon(cSPGameDataUFO* pUfo, cSPUIMinimapWin* pWin);    // 0x01042080
void  QuaternionFromFacingAndUp(Quaternion* pOut, const Vector3* pFacing, const Vector3* pUp);
                                                                         // 0x0069b600
Vector3* QuatRotateAxis(Vector3* pOut, const Vector3* pAxis, const float* pQuat); // 0x0059aed0
Vector3* RandomDirection3(Vector3* pOut);                                // 0x00b7e560

// ---------------------------------------------------------------------------
// cSPSimulatorSpaceGame -- owner of the UFO list and the chase entry points
// ---------------------------------------------------------------------------

class cSPSimulatorSpaceGame {
public:
    cSPGameDataUFO* GetPlayerInventory();        // 0x00a1ad60
    void BeginChase(int mode);                   // 0x00ffe3a0
    void UpdatePosseUFO(cSPGameDataUFO* pUfo, unsigned int id,
                        float a, float b, float c);                 // 0x01006a40
    bool UpdateInterceptorUFO(cSPGameDataUFO* pUfo, bool flag);     // 0x01003df0

    void ChaseFromGalaxyToSolar();               // 0x010077e0  (this file)
    void ChaseFromSolarToPlanet();               // 0x01007bf0
    void ChaseFromPlanetToSolar();               // 0x01007ed0
    void ChaseFromSolarToGalaxy();               // 0x01008100
    void UpdateChasingUFOs(unsigned int param);  // 0x01008270

    char              mPad00[0x14];
    cSpaceUI*         mpSpaceUI;      // +0x14
    char              mPad18[0x78 - 0x18];
    cSPGameDataUFO**  mUFOsBegin;     // +0x78
    cSPGameDataUFO**  mUFOsEnd;       // +0x7c
};

cSPSimulatorSpaceGame* GetUFOSimulator();        // 0x00ffbe50

// ---------------------------------------------------------------------------
// 0x010077e0  SP::cSPSimulatorSpaceGame::ChaseFromGalaxyToSolar
// ---------------------------------------------------------------------------
// @ 0x010077e0
void cSPSimulatorSpaceGame::ChaseFromGalaxyToSolar()
{
    cSPSimulatorSpaceGame* self = this;
    cSPSimulatorSpaceGame* sim = GetUFOSimulator();
    sim->BeginChase(1);
    cSPGameDataUFO* player = sim->GetPlayerInventory();
    const Vector3* playerPos = player->mSpatial.GetPosition();

    cSPGameDataUFO** cur = self->mUFOsBegin;
    for (;;) {
        if (cur == self->mUFOsEnd)
            break;
        cSPGameDataUFO** nxt = cur + 1;
        cSPGameDataUFO* ufo = *cur;
        bool bErase = false;
        if (ufo->IsDestroyed()) {
            bErase = true;
        } else {
            if (ufo->mState == 8) {
                unsigned int handle = *(unsigned int*)((char*)ufo->mp7b0 + 0x70);
                GetStarMap()->RemoveVisual(handle, 0xb7735c3, 0, 1);

                double a = (double)ufo->mAngleSeed6b0 * kOrbitSpeed * 0.41176471f * 0.5f;
                float s = (float)sin(a);
                float c = (float)cos(a);
                float ax = s * kZAxis.x;
                float ay = s * kZAxis.y;
                float az = s * kZAxis.z;
                ufo->mDir694.x = ((c * ay + az * ax) * kYAxis.z + (ax * ay - c * az) * kYAxis.y) * 2.0f
                                 + (1.0f - (az * az + ay * ay) * 2.0f) * kYAxis.x;
                ufo->mDir694.y = ((az * ay - c * ax) * kYAxis.z + (c * az + ax * ay) * kYAxis.x) * 2.0f
                                 + (1.0f - (az * az + ax * ax) * 2.0f) * kYAxis.y;
                ufo->mDir694.z = (c * ax + az * ay) * kYAxis.y * 2.0f + (az * ax - c * ay) * kYAxis.x
                                 + (1.0f - (ax * ax + ay * ay) * 2.0f) * kYAxis.z;

                if (!GetBackgroundSim()->FUN_00c8b800())
                    bErase = true;
            }
            {
                float inv = (float)(1.0 / sqrt((double)ufo->mDir694.x * (double)ufo->mDir694.x
                                             + (double)ufo->mDir694.y * (double)ufo->mDir694.y
                                             + (double)ufo->mDir694.z * (double)ufo->mDir694.z));
                Vector3 n;
                n.x = ufo->mDir694.x * inv;
                n.y = ufo->mDir694.y * inv;
                n.z = ufo->mDir694.z * inv;

                Vector3 dest;
                dest.x = playerPos->x + n.x * kDist100;
                dest.y = playerPos->y + n.y * kDist100;
                dest.z = playerPos->z + n.z * kDist100;
                ufo->SetDestination(&dest);
                ufo->PopToDestination();

                Vector3 facing;
                facing.x = -n.x;
                facing.y = -n.y;
                facing.z = -n.z;
                Quaternion q;
                QuaternionFromFacingAndUp(&q, &facing, &kZAxis);
                ufo->mOrientation = q;
                ufo->OnContextChange(1);
            }
        }

        if (!bErase) {
            ++cur;
            continue;
        }

        /* shared erase/release tail (LAB_01007b79) */
        if (!ufo->IsDestroyed())
            DestroyCreature((cCreatureData*)ufo, 0);
        for (cSPGameDataUFO** d = cur, ** s = nxt; s != self->mUFOsEnd; ++s)
            *d++ = *s;
        self->mUFOsEnd -= 1;
        cSPGameDataUFO* tail = *self->mUFOsEnd;
        if (tail)
            tail->Release();
    }
}

// ---------------------------------------------------------------------------
// 0x01007bf0  SP::cSPSimulatorSpaceGame::ChaseFromSolarToPlanet
// ---------------------------------------------------------------------------
// @ 0x01007bf0
void cSPSimulatorSpaceGame::ChaseFromSolarToPlanet()
{
    cSPSimulatorSpaceGame* self = this;
    cSPSimulatorSpaceGame* sim = GetUFOSimulator();
    sim->BeginChase(0);
    cSPGameDataUFO* player = sim->GetPlayerInventory();
    const Vector3* playerPos = player->mSpatial.GetPosition();

    float upInv = (float)(1.0 / sqrt((double)playerPos->x * (double)playerPos->x
                                    + (double)playerPos->y * (double)playerPos->y
                                    + (double)playerPos->z * (double)playerPos->z));
    Vector3 up;
    up.x = playerPos->x * upInv;
    up.y = playerPos->y * upInv;
    up.z = playerPos->z * upInv;

    cSPUIMinimapWin* win = self->mpSpaceUI->GetMinimap();

    cSPGameDataUFO** cur = self->mUFOsBegin;
    for (;;) {
        if (cur == self->mUFOsEnd)
            break;
        cSPGameDataUFO** nxt = cur + 1;
        cSPGameDataUFO* ufo = *cur;
        if (ufo->IsDestroyed()) {
            for (cSPGameDataUFO** d = cur, ** s = nxt; s != self->mUFOsEnd; ++s)
                *d++ = *s;
            self->mUFOsEnd -= 1;
            cSPGameDataUFO* tail = *self->mUFOsEnd;
            if (tail)
                tail->Release();
            continue;
        }
        ++cur;

        if (ufo->mState == 8) {
            Vector3 tmp;
            Vector3* rd = RandomDirection3(&tmp);
            ufo->mDir694 = *rd;
        }
        float inv = (float)(1.0 / sqrt((double)ufo->mDir694.x * (double)ufo->mDir694.x
                                     + (double)ufo->mDir694.y * (double)ufo->mDir694.y
                                     + (double)ufo->mDir694.z * (double)ufo->mDir694.z));
        Vector3 n;
        n.x = ufo->mDir694.x * inv;
        n.y = ufo->mDir694.y * inv;
        n.z = ufo->mDir694.z * inv;

        Vector3 temp;
        temp.x = playerPos->x + n.x * kDist500;
        temp.y = playerPos->y + n.y * kDist500;
        temp.z = playerPos->z + n.z * kDist500;
        float tempInv = (float)(1.0 / sqrt((double)temp.x * (double)temp.x
                                          + (double)temp.y * (double)temp.y
                                          + (double)temp.z * (double)temp.z));
        Vector3 dest;
        dest.x = temp.x * tempInv * kDist1000;
        dest.y = temp.y * tempInv * kDist1000;
        dest.z = temp.z * tempInv * kDist1000;
        ufo->FlyTowards(&dest);

        Vector3 facing;
        facing.x = -n.x;
        facing.y = -n.y;
        facing.z = -n.z;
        Quaternion q;
        QuaternionFromFacingAndUp(&q, &facing, &up);
        ufo->mOrientation = q;
        ufo->OnContextChange(0);
        CreateMinimapIcon(ufo, win);
    }
}

// ---------------------------------------------------------------------------
// 0x01007ed0  SP::cSPSimulatorSpaceGame::ChaseFromPlanetToSolar
// ---------------------------------------------------------------------------
// @ 0x01007ed0
void cSPSimulatorSpaceGame::ChaseFromPlanetToSolar()
{
    cSPSimulatorSpaceGame* self = this;
    const Vector3* planetPos = GetActivePlanet()->GetPosition();

    cSPSimulatorSpaceGame* sim = GetUFOSimulator();
    sim->BeginChase(1);
    cSPGameDataUFO* player = sim->GetPlayerInventory();

    Vector3 playerPos;
    player->mSpatial.GetPositionOut(&playerPos);

    cSPUIMinimapWin* win = self->mpSpaceUI->GetMinimap();

    cSPGameDataUFO** cur = self->mUFOsBegin;
    for (;;) {
        if (cur == self->mUFOsEnd)
            break;
        cSPGameDataUFO** nxt = cur + 1;
        cSPGameDataUFO* ufo = *cur;
        if (ufo->IsDestroyed()) {
            for (cSPGameDataUFO** d = cur, ** s = nxt; s != self->mUFOsEnd; ++s)
                *d++ = *s;
            self->mUFOsEnd -= 1;
            cSPGameDataUFO* tail = *self->mUFOsEnd;
            if (tail)
                tail->Release();
            continue;
        }
        ++cur;

        unsigned int st = ufo->mState;
        if (st == 3) {
            cSPGameDataUFO* old = ufo->mpCached68c;
            if (player != old) {
                player->AddRef();
                ufo->mpCached68c = player;
                if (old)
                    old->Release();
            }
        } else if (st == 8) {
            double a = (double)ufo->mAngleSeed6b0 * kOrbitSpeed * 0.41176471f * 0.5f;
            float s = (float)sin(a);
            float c = (float)cos(a);
            float rot[4];
            rot[0] = s * kZAxis.x;
            rot[1] = s * kZAxis.y;
            rot[2] = s * kZAxis.z;
            rot[3] = c;
            Vector3 tmp;
            ufo->mDir694 = *QuatRotateAxis(&tmp, &kYAxis, rot);
        }

        ufo->SetDestination(planetPos);
        ufo->PopToDestination();

        Quaternion q;
        QuaternionFromFacingAndUp(&q, &playerPos, &kZAxis);
        ufo->mOrientation = q;
        ufo->mSpatial.Notify();
        ufo->OnContextChange(1);
        win->RemoveIcon(ufo, 1, 0);
    }
}

// ---------------------------------------------------------------------------
// 0x01008100  SP::cSPSimulatorSpaceGame::ChaseFromSolarToGalaxy
// ---------------------------------------------------------------------------
// @ 0x01008100
void cSPSimulatorSpaceGame::ChaseFromSolarToGalaxy()
{
    cSPSimulatorSpaceGame* self = this;
    Vector3* cityPos = GetCurrentStar()->GetCities();

    cSPSimulatorSpaceGame* sim = GetUFOSimulator();
    sim->BeginChase(2);
    cSPGameDataUFO* player = sim->GetPlayerInventory();

    Vector3 playerPos;
    player->mSpatial.GetPositionOut(&playerPos);

    cSPGameDataUFO** cur = self->mUFOsBegin;
    for (;;) {
        if (cur == self->mUFOsEnd)
            break;
        cSPGameDataUFO** nxt = cur + 1;
        cSPGameDataUFO* ufo = *cur;
        if (ufo->IsDestroyed()) {
            for (cSPGameDataUFO** d = cur, ** s = nxt; s != self->mUFOsEnd; ++s)
                *d++ = *s;
            self->mUFOsEnd -= 1;
            cSPGameDataUFO* tail = *self->mUFOsEnd;
            if (tail)
                tail->Release();
            continue;
        }
        ++cur;

        ufo->SetDestination(cityPos);
        ufo->PopToDestination();
        ufo->SetDestinationOffset(&kChaseOffset);

        Vector3 d2;
        d2.x = cityPos->x + kZAxis.x;
        d2.y = cityPos->y + kZAxis.y;
        d2.z = cityPos->z + kZAxis.z;
        ufo->SetDestination(&d2);

        Quaternion q;
        QuaternionFromFacingAndUp(&q, &playerPos, &kZAxis);
        ufo->mOrientation = q;
        ufo->mSpatial.Notify();
        ufo->OnContextChange(2);
    }
}

// ---------------------------------------------------------------------------
// 0x01008270  SP::cSPSimulatorSpaceGame::UpdateChasingUFOs
// ---------------------------------------------------------------------------
// @ 0x01008270
void cSPSimulatorSpaceGame::UpdateChasingUFOs(unsigned int param)
{
    cSPSimulatorSpaceGame* self = this;
    unsigned int posseSeed = 0;        // state-3 orbit seed counter
    unsigned int interceptorSeed = 0;  // state-8 orbit seed counter

    cSPGameDataUFO** cur = self->mUFOsBegin;
    for (;;) {
        if (cur == self->mUFOsEnd)
            break;
        cSPGameDataUFO** nxt = cur + 1;
        cSPGameDataUFO* ufo = *cur;
        bool erase = false;

        unsigned int idx = ufo->mState - 3;
        if (idx <= 6) {
            switch (ufo->mState) {
            case 3:
                ufo->mAngleSeed6b0 = (int)posseSeed;
                ++posseSeed;
                UpdatePosseUFO(ufo, param, 10.0f, 0.7f, 10.0f);
                break;

            case 6: {
                double dx = (double)ufo->mPos718.x - (double)ufo->mTargetPos750.x;
                double dy = (double)ufo->mPos718.y - (double)ufo->mTargetPos750.y;
                double dz = (double)ufo->mPos718.z - (double)ufo->mTargetPos750.z;
                float dist = (float)sqrt(dx * dx + dy * dy + dz * dz);
                if (dist >= kNearTargetDist)
                    break;                       // too far, leave as is
                if (ufo->mp75c == 0) {
                    float pdist = (float)sqrt((double)ufo->mPos718.x * (double)ufo->mPos718.x
                                             + (double)ufo->mPos718.y * (double)ufo->mPos718.y
                                             + (double)ufo->mPos718.z * (double)ufo->mPos718.z);
                    if (pdist >= kNearPosDist) {
                        erase = true;            // LAB_01008318
                        break;
                    }
                    ufo->SetDestination(&ufo->mVec6bc);
                } else {
                    float invPos = (float)(1.0 / sqrt((double)ufo->mPos718.x * (double)ufo->mPos718.x
                                                     + (double)ufo->mPos718.y * (double)ufo->mPos718.y
                                                     + (double)ufo->mPos718.z * (double)ufo->mPos718.z));
                    float invDest = (float)(1.0 / sqrt((double)ufo->mVec6bc.x * (double)ufo->mVec6bc.x
                                                              + (double)ufo->mVec6bc.y * (double)ufo->mVec6bc.y
                                                              + (double)ufo->mVec6bc.z * (double)ufo->mVec6bc.z));
                    Vector3 sum;
                    sum.x = ufo->mVec6bc.x * invDest + ufo->mPos718.x * invPos;
                    sum.y = ufo->mVec6bc.y * invDest + ufo->mPos718.y * invPos;
                    sum.z = ufo->mVec6bc.z * invDest + ufo->mPos718.z * invPos;
                    float invSum = (float)(1.0 / sqrt((double)sum.x * (double)sum.x
                                                     + (double)sum.y * (double)sum.y
                                                     + (double)sum.z * (double)sum.z));
                    float scale = GetBackgroundSim()->GetSolarSystem()->FUN_00c84d40(0) + 20.0f;
                    Vector3 dest;
                    // retail reads the destination back out of the sum/normalise scratch:
                    // the x component uses the un-normalised sum.z, y/z use -n.x/-n.y.
                    dest.x = sum.z * scale;
                    dest.y = -sum.x * invSum * scale;
                    dest.z = -sum.y * invSum * scale;
                    ufo->SetDestination(&dest);
                }
                break;
            }

            case 8:
                ufo->mAngleSeed6b0 = (int)interceptorSeed;
                ++interceptorSeed;
                if (!UpdateInterceptorUFO(ufo, false))
                    break;
                erase = true;                    // fall into LAB_01008318
                break;

            case 9: {
                double dx = (double)ufo->mPos718.x - (double)ufo->mTargetPos750.x;
                double dy = (double)ufo->mPos718.y - (double)ufo->mTargetPos750.y;
                double dz = (double)ufo->mPos718.z - (double)ufo->mTargetPos750.z;
                float dist = (float)sqrt(dx * dx + dy * dy + dz * dz);
                if (dist < kDist5)
                    erase = true;                // close enough -> retask
                break;
            }

            default:                             // states 4, 5, 7
                break;
            }
        }

        if (!erase) {
            ++cur;
            continue;
        }

        /* LAB_01008318: flag the craft and retask it if the host says so */
        ufo->mb77e = true;
        if (!ufo->FUN_00c370e0()) {
            ++cur;
            continue;
        }
        DestroyCreature((cCreatureData*)ufo, 0);
        for (cSPGameDataUFO** d = cur, ** s = nxt; s != self->mUFOsEnd; ++s)
            *d++ = *s;
        self->mUFOsEnd -= 1;
        cSPGameDataUFO* tail = *self->mUFOsEnd;
        if (tail)
            tail->Release();
    }
}

// ---------------------------------------------------------------------------
// eastl vector<pointer> element shift helpers -- the element type is 0x14 bytes
// and only the fields at +0xc / +0x10 are copied by the shift routines.
// ---------------------------------------------------------------------------

struct UFOElem {
    virtual void v00();                // +0x00
    virtual void v04();                // +0x04
    virtual void Destroy(int flags);   // +0x08
    char         mPad0c[0x0c - 0x04];
    void*        mpLink0c;             // +0x0c
    void*        mpLink10;             // +0x10
};
struct UFOArray {
    UFOElem* mpBegin;             // +0x00
    UFOElem* mpEnd;               // +0x04
    UFOElem* mpCap;               // +0x08
    UFOElem* erase(UFOElem* first, UFOElem* last);  // 0x01008850
};

// ---------------------------------------------------------------------------
// 0x01008820  TCopyForward(first, last, dst)  -- eastl copy_impl body
// ---------------------------------------------------------------------------
// @ 0x01008820
void TCopyForward(UFOElem* first, UFOElem* last, UFOElem* dst)
{
    if (first != last) {
        do {
            dst->mpLink0c = first->mpLink0c;
            dst->mpLink10 = first->mpLink10;
            ++first;
            ++dst;
        } while (first != last);
    }
}

// ---------------------------------------------------------------------------
// 0x01008850  UFOArray::erase(first, last)  -- thiscall, ret 8
// ---------------------------------------------------------------------------
// @ 0x01008850
UFOElem* UFOArray::erase(UFOElem* first, UFOElem* last)
{
    UFOElem* dst = first;
    if (last != this->mpEnd) {
        UFOElem* src = last;
        do {
            dst->mpLink0c = src->mpLink0c;
            dst->mpLink10 = src->mpLink10;
            ++src;
            ++dst;
        } while (src != this->mpEnd);
    }
    for (UFOElem* p = dst; p < this->mpEnd; ++p)
        p->Destroy(0);
    this->mpEnd += last - first;
    return first;
}

// ---------------------------------------------------------------------------
// 0x010088e0  TCopyBackward(first, last, dst)  -- eastl copy_backward_impl body
// ---------------------------------------------------------------------------
// @ 0x010088e0
void TCopyBackward(UFOElem* first, UFOElem* last, UFOElem* dst)
{
    while (last != first) {
        --last;
        --dst;
        dst->mpLink0c = last->mpLink0c;
        dst->mpLink10 = last->mpLink10;
    }
}