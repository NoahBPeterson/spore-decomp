// Slice s00b84270: SP::cPlanetModel surface-position search.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

struct Vector3 {
    float x, y, z;
};

struct cTerrainMapSet {
    char  pad00[0x34];
    float mRadius;          // +0x34
    float mMaxHeight;       // +0x38
    float mWaterHeight;     // +0x3c
    float GetHeightAt(const Vector3& p);                    // 0x00f927c0
};

struct ISphere {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual cTerrainMapSet* GetMap();                       // slot +0x0c
};

struct cPlanetModel {
    char      pad00[0x20];
    void*     mpSphere;     // +0x20
    ISphere*  mpISphere;    // +0x24
    float GetRadiusAt(const Vector3& p);                    // 0x00b7ef70
    void  FindSurfacePosition(Vector3* out);                // 0x00b84730
};

void RandomDirection3(Vector3* out);                       // 0x00b7e560

extern Vector3 gNoSurfacePosition;                          // 0x016881f0

// @ 0x00b84730
void cPlanetModel::FindSurfacePosition(Vector3* out)
{
    Vector3 pos;
    Vector3 dir;
    RandomDirection3(&dir);
    volatile float radius = GetRadiusAt(dir);
    pos.x = dir.x * radius;
    pos.y = dir.y * radius;
    pos.z = dir.z * radius;

    int i = 0;
    do {
        int prev = i;
        i = prev + 1;
        if (mpISphere == 0)
            break;
        float height = mpISphere->GetMap()->GetHeightAt(pos);
        cTerrainMapSet* terrain = mpISphere->GetMap();
        float water = terrain->mWaterHeight * terrain->mMaxHeight + terrain->mRadius;
        if (water <= height)
            break;

        Vector3 ndir;
        RandomDirection3(&ndir);
        float r;
        if (mpSphere != 0) {
            r = mpISphere->GetMap()->GetHeightAt(ndir);
        } else if (mpISphere != 0 && mpISphere->GetMap() != 0) {
            r = mpISphere->GetMap()->mRadius;
        } else {
            r = 500.0f;
        }
        dir.x = ndir.x * r;
        dir.y = ndir.y * r;
        dir.z = ndir.z * r;
        pos = dir;
    } while (i < 10000);

    if (i < 10000) {
        out->x = pos.x;
        out->y = pos.y;
        out->z = pos.z;
    } else {
        out->x = gNoSurfacePosition.x;
        out->y = gNoSurfacePosition.y;
        out->z = gNoSurfacePosition.z;
    }
}
