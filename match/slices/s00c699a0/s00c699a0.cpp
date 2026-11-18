// Slice s00c699a0: a predicate over a game object and a target: true when the object is
// registered, active, not blocked by its +0xc0 component, shares the target's owner id and is
// not the manager's current object.

struct Component_s00c6_99a0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool IsBlocked();  // slot 0x58
};

struct Object_s00c6_99a0 {
    char pad000[0xc0];
    Component_s00c6_99a0 mComponent;  // +0xc0
    char pad0c4[0xb20 - 0xc4];
    int mOwnerId;                     // +0xb20

    bool IsActive();  // 0x00c0b770
};

struct Target_s00c6_99a0 {
    char pad00[0xa4];
    int mOwnerId;  // +0xa4
};

struct Manager_s00c6_99a0 {
    Object_s00c6_99a0* GetCurrent();  // 0x00a1ad10
};

int IsRegistered_s00c6_99a0(Object_s00c6_99a0* obj);  // 0x00d99500
Manager_s00c6_99a0* GetManager_s00c6_99a0();          // 0x00d51660

// @ 0x00c699a0
int CanTarget_s00c6_99a0(Object_s00c6_99a0* obj, Target_s00c6_99a0* target)
{
    if (IsRegistered_s00c6_99a0(obj) && obj->IsActive() && !obj->mComponent.IsBlocked() &&
        obj->mOwnerId == target->mOwnerId && GetManager_s00c6_99a0()->GetCurrent() != obj)
        return 1;
    return 0;
}
