// Same shape as s009515e0's AnimationCurve::GetProperty (0x00951650): fills a
// PropertyRef with the curve descriptor, this, count 1 and the slot-5 vtable call.

// @ 0x0000988aa0
struct TypeDesc_00988aa0 { int x; };
extern const TypeDesc_00988aa0 kCurveDesc_00988aa0;   // 0x1445398

struct PropertyRef_00988aa0 {
    const TypeDesc_00988aa0* type;
    void* obj;
    int count;
    int value;
};

struct AnimCurve_00988aa0 {
    virtual void pv0();
    virtual void pv1();
    virtual void pv2();
    virtual int  pv3();
    virtual void pv4();
    virtual int  f5();                                // slot 5, offset 0x14
    void GetProperty(PropertyRef_00988aa0* out);
};

void AnimCurve_00988aa0::GetProperty(PropertyRef_00988aa0* out)
{
    out->type = &kCurveDesc_00988aa0;
    out->obj = this;
    out->count = 1;
    out->value = f5();
}
