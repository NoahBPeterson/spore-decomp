// Same shape as s009515e0's AnimationCurve::GetProperty (0x00951650): fills a
// PropertyRef with the curve descriptor, this, count 1 and the slot-5 vtable call.

// @ 0x0000990010
struct TypeDesc_00990010 { int x; };
extern const TypeDesc_00990010 kCurveDesc_00990010;   // 0x1445b2c

struct PropertyRef_00990010 {
    const TypeDesc_00990010* type;
    void* obj;
    int count;
    int value;
};

struct AnimCurve_00990010 {
    virtual void pv0();
    virtual void pv1();
    virtual void pv2();
    virtual int  pv3();
    virtual void pv4();
    virtual int  f5();                                // slot 5, offset 0x14
    void GetProperty(PropertyRef_00990010* out);
};

void AnimCurve_00990010::GetProperty(PropertyRef_00990010* out)
{
    out->type = &kCurveDesc_00990010;
    out->obj = this;
    out->count = 1;
    out->value = f5();
}
