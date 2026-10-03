// Single function: builds a local vector of 24-byte elements via a helper, then the inlined
// vector destructor walks it (trivially destructible element loop) and calls the out-of-line
// base destructor (FUN_004fd940). Returns the helper's bool.
// Built unoptimized: /Od /Ob1 /MD /Gy /TP /arch:SSE
//
// The local is a 96-byte object: a 12-byte vector header followed by 84 bytes of extra
// storage (modelled as a derived-class array; it is never touched by this function).
struct Elem24 { unsigned int pad[6]; };

struct Elem24VectorBase {
    Elem24* mpBegin;
    Elem24* mpEnd;
    Elem24* mpCapacity;
    bool Collect(unsigned int a, unsigned int b);   // FUN_0041aaa0
    ~Elem24VectorBase();                            // FUN_004fd940
};

struct Elem24Vector : Elem24VectorBase {
    Elem24Vector() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~Elem24Vector() {
        for (Elem24* p = mpBegin; p < mpEnd; ++p) {
        }
        {
            unsigned int dead1[3];   // dead debug local of the original inline dtor
        }
    }
};

struct Elem24VectorWithStorage : Elem24Vector {
    unsigned int storage[21];
};

// @ 0x0041aa40
bool CollectAndDestroy(unsigned int a, unsigned int b)
{
    Elem24VectorWithStorage v;
    return v.Collect(a, b);
}
