// s00aa9050 -- beam/attachment point update (0x00aa97f0).
//
// The function pushes a point through two optional 3x3 transforms, asks the attach target
// whether the point is valid (two virtual calls, the second returning a range that is then
// compared against the configured min/max or a random roll), optionally offsets the point
// along z, and finally maps the point back into local space of both transforms before
// writing it back into the caller's structure.

struct Vec3 {
    float x;
    float y;
    float z;
};

// 0x38-byte transform: flags, translation, uniform scale, row-major 3x3.
struct Xform {
    unsigned mFlags;                                        // +0x00
    Vec3     mPosition;                                     // +0x04
    float    mScale;                                        // +0x10
    float    mMatrix[9];                                    // +0x14
    void InverseTransformPoint(Vec3* point);                // 0x007cda70 (thiscall, ret 4)
};

struct AttachConfig {                                       // pointed to by owner+0x24
    char     pad00[8];
    unsigned mFlags;                                        // +0x08
};

struct AttachTarget {                                       // pointed to by owner+0x1b4
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14();
    virtual bool  Accept(Vec3* point);                      // +0x18
    virtual void  t1cdummy();
    virtual float GetRange(Vec3* point);                    // +0x20
};

struct RandomGlobal {
    double RandomDouble();                                  // 0x009360d0
};
extern RandomGlobal _sRandomGlobal;                         // 0x016778dc

double cConfigManagerUnnamedB90(float* values);             // 0x007cdb90

// Caller structure: the point lives at +0x10.
struct AttachPoint {
    char pad00[0x10];
    Vec3 mPosition;                                         // +0x10
};

struct BeamAttachUpdater {
    char          pad00[0x24];
    AttachConfig* mpConfig;                                 // +0x24
    char          pad28[0xc8 - 0x28];
    Xform         mWorldXform;                              // +0xc8
    Xform         mLocalXform;                              // +0x100
    char          pad138[0x188 - 0x138];
    float         mMinRange;                                // +0x188
    float         mMaxRange;                                // +0x18c
    char          pad190[0x1b4 - 0x190];
    AttachTarget* mpTarget;                                 // +0x1b4
    char          pad1b8[0x1bd - 0x1b8];
    bool          mEnabled;                                 // +0x1bd
    char          pad1be[0x1c8 - 0x1be];
    float         mField1c8;                                // +0x1c8
    char          pad1cc[0x1d4 - 0x1cc];
    float         mField1d4;                                // +0x1d4
    bool UpdateAttachPoint(AttachPoint* io);                // 0x00aa97f0
};

// @ 0x00aa97f0
bool BeamAttachUpdater::UpdateAttachPoint(AttachPoint* io)
{
    Vec3 pos;
    pos.x = io->mPosition.x;
    pos.y = io->mPosition.y;
    pos.z = io->mPosition.z;
    if (mEnabled) {
        if (mWorldXform.mFlags & 2) {
            Vec3 transformed;
            transformed.x = (mWorldXform.mMatrix[3] * pos.y + mWorldXform.mMatrix[6] * pos.z)
                            + mWorldXform.mMatrix[0] * pos.x;
            transformed.y = (mWorldXform.mMatrix[4] * pos.y + mWorldXform.mMatrix[7] * pos.z)
                            + mWorldXform.mMatrix[1] * pos.x;
            transformed.z = (mWorldXform.mMatrix[5] * pos.y + mWorldXform.mMatrix[8] * pos.z)
                            + mWorldXform.mMatrix[2] * pos.x;
            pos = transformed;
        }
        pos.x = mWorldXform.mPosition.x + mWorldXform.mScale * pos.x;
        pos.y = mWorldXform.mPosition.y + mWorldXform.mScale * pos.y;
        pos.z = mWorldXform.mPosition.z + mWorldXform.mScale * pos.z;
        if (mLocalXform.mFlags & 2) {
            Vec3 transformed;
            transformed.x = (mLocalXform.mMatrix[3] * pos.y + mLocalXform.mMatrix[6] * pos.z)
                            + mLocalXform.mMatrix[0] * pos.x;
            transformed.y = (mLocalXform.mMatrix[4] * pos.y + mLocalXform.mMatrix[7] * pos.z)
                            + mLocalXform.mMatrix[1] * pos.x;
            transformed.z = (mLocalXform.mMatrix[5] * pos.y + mLocalXform.mMatrix[8] * pos.z)
                            + mLocalXform.mMatrix[2] * pos.x;
            pos = transformed;
        }
        pos.x = mLocalXform.mPosition.x + mLocalXform.mScale * pos.x;
        pos.y = mLocalXform.mPosition.y + mLocalXform.mScale * pos.y;
        pos.z = mLocalXform.mPosition.z + mLocalXform.mScale * pos.z;
    }
    AttachTarget* target = mpTarget;
    if (!target)
        return false;
    if (!target->Accept(&pos))
        return false;
    float range = mpTarget->GetRange(&pos);
    if ((mpConfig->mFlags >> 6) & 1) {
        if (range < mMinRange)
            return false;
        if (range > mMaxRange)
            return false;
    } else if ((mpConfig->mFlags >> 7) & 1) {
        if (_sRandomGlobal.RandomDouble() >= range)
            return false;
    }
    if ((mpConfig->mFlags >> 5) & 1) {
        pos.z = range;
        float offset[2];
        offset[0] = mField1c8;
        offset[1] = mField1d4;
        pos.z = pos.z + cConfigManagerUnnamedB90(offset);
    }
    if (mEnabled) {
        mLocalXform.InverseTransformPoint(&pos);
        mWorldXform.InverseTransformPoint(&pos);
    }
    io->mPosition = pos;
    return true;
}
