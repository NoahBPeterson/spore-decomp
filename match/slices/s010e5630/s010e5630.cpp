// Slice s010e5630: Havok multi sphere collision agent.  Every entry point walks
// the child list (instanced shape) or the shape's sphere list (static helpers),
// builds the transform of each sphere from the body transform and forwards the
// query to the sphere's collision agent.

typedef unsigned char uchar;
typedef unsigned int  uint;

// ---------------------------------------------------------------------------
// Havok monitor stream
// ---------------------------------------------------------------------------
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4

extern void* __stdcall TlsGetValue(unsigned long index);
extern int   __stdcall TlsSetValue(unsigned long index, void* value);
extern unsigned __int64 __rdtsc(void);

static const char s_timerMultiSphere[] = "TtMultiSphere";
static const char s_timerEnd[] = "";

// Push a timer marker on the monitor stream when there is room for it.
static inline void hkTimerBegin(const char* name)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurrentTls);
    if (cur < end)
    {
        unsigned* entry = (unsigned*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        entry[0] = (unsigned)name;
        entry[1] = (unsigned)__rdtsc();
        TlsSetValue(g_hkMonitorStreamCurrentTls, entry + 3);
    }
}

static inline void hkTimerEnd()
{
    hkTimerBegin(s_timerEnd);
}

// ---------------------------------------------------------------------------
// Havok types
// ---------------------------------------------------------------------------
struct hkVector4
{
    float x, y, z, w;
};

struct __declspec(align(16)) hkTransform
{
    hkVector4 m_row[3];
    hkVector4 m_translation;
};

struct __declspec(align(16)) hkCdBody
{
    const void* m_shape;              // 0x00
    int         m_shapeKey;           // 0x04
    const hkTransform* m_transform;   // 0x08
    void*       m_motion;             // 0x0c
};

struct __declspec(align(16)) hkMotionState
{
    int         m_pad[4];             // 0x00
    hkTransform m_transform;          // 0x10
    hkVector4   m_sweptTransform;     // 0x50
};

struct hkMultiSphereShape
{
    int       m_memSizeAndFlags;      // 0x00
    int       m_referenceCount;       // 0x04
    int       m_type;                 // 0x08
    int       m_numSpheres;           // 0x0c
    hkVector4 m_spheres[1];           // 0x10: xyz offset, w radius
};

struct hkMultiSphereChild
{
    int             m_sphereIndex;    // 0x00
    const hkCdBody* m_body;           // 0x04
};

struct hkMultiSphereAgent
{
    int                  m_pad00;
    int                  m_pad04;
    int                  m_pad08;
    hkMultiSphereChild*  m_children;  // 0x0c
    int                  m_numChildren; // 0x10

    void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                          const void* input, void* output);
    void getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                          const void* input, void* collector);
    void linearCast(const hkCdBody& bodyA, const hkCdBody& bodyB,
                    const void* input, void* collector, void* collector2);

    static void staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                       const void* input, void* collector);
    static void staticLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                 const void* input, void* collector, void* collector2);
    static void staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                      const void* input, void* collector);
    void getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                const void* input, void* collector);
};

// Position of a sphere in world space: the parent rotation applied to the
// sphere offset plus the parent translation.
static inline void hkSphereTransform(hkTransform& dst, const hkTransform& src, const hkVector4& offset)
{
    dst = src;
    dst.m_translation.x = src.m_row[0].x * offset.x + src.m_row[1].x * offset.y +
                          src.m_row[2].x * offset.z + src.m_translation.x;
    dst.m_translation.y = src.m_row[0].y * offset.x + src.m_row[1].y * offset.y +
                          src.m_row[2].y * offset.z + src.m_translation.y;
    dst.m_translation.z = src.m_row[0].z * offset.x + src.m_row[1].z * offset.y +
                          src.m_row[2].z * offset.z + src.m_translation.z;
    dst.m_translation.w = src.m_translation.w;
}

typedef void (__thiscall *hkChildDispatch)(void*, const hkCdBody*, const void*, const void*, const void*);

// ------------------------------------------------------------------ 010e5630
// @ 0x010e5630
void hkMultiSphereAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                          const void* input, void* output)
{
    hkTimerBegin(s_timerMultiSphere);

    hkMotionState motion = *(const hkMotionState*)bodyA.m_motion;
    hkCdBody child(bodyA);

    const hkMultiSphereShape* shape = (const hkMultiSphereShape*)bodyA.m_shape;
    const hkMultiSphereChild* children = m_children;

    for (int i = m_numChildren - 1; i >= 0; --i)
    {
        const hkVector4& offset = shape->m_spheres[children[i].m_sphereIndex];

        hkTransform childTransform;
        hkSphereTransform(childTransform, motion.m_transform, offset);
        child.m_transform = &childTransform;

        void* agent = *(void**)children[i].m_body;
        ((hkChildDispatch)(((void**)*(void**)agent)[5]))(agent, &child, &bodyB, input, output);
    }

    hkTimerEnd();
}

// ------------------------------------------------------------------ 010e5850
// @ 0x010e5850
void hkMultiSphereAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                          const void* input, void* collector)
{
    hkTimerBegin(s_timerMultiSphere);

    hkMotionState motion = *(const hkMotionState*)bodyA.m_motion;
    hkCdBody child(bodyA);

    const hkMultiSphereShape* shape = (const hkMultiSphereShape*)bodyA.m_shape;
    const hkMultiSphereChild* children = m_children;

    for (int i = m_numChildren - 1; i >= 0; --i)
    {
        const hkVector4& offset = shape->m_spheres[children[i].m_sphereIndex];

        hkTransform childTransform;
        hkSphereTransform(childTransform, motion.m_transform, offset);
        child.m_transform = &childTransform;

        void* agent = *(void**)children[i].m_body;
        ((hkChildDispatch)(((void**)*(void**)agent)[3]))(agent, &child, &bodyB, input, collector);
    }

    hkTimerEnd();
}

// ------------------------------------------------------------------ 010e5a00
// @ 0x010e5a00
void hkMultiSphereAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                const void* input, void* collector)
{
    hkTimerBegin(s_timerMultiSphere);

    hkMotionState motion = *(const hkMotionState*)bodyA.m_motion;
    hkCdBody child(bodyA);

    const hkMultiSphereShape* shape = (const hkMultiSphereShape*)bodyA.m_shape;
    int numSpheres = shape->m_numSpheres;

    // shape type of the other body selects the dispatch slot of the collector
    int shapeType = ((int (__thiscall*)(void*))(((void**)*(void**)(void*)bodyB.m_shape)[2]))((void*)bodyB.m_shape);

    for (int i = 0; i < numSpheres; ++i)
    {
        const hkVector4& offset = shape->m_spheres[i];

        hkTransform childTransform;
        hkSphereTransform(childTransform, motion.m_transform, offset);
        child.m_transform = &childTransform;

        uchar slot = ((const uchar*)input)[400 + (uint)shapeType];
        void* dispatcher = (void*)input;
        typedef void (__thiscall *DispatchFn)(void*, const hkCdBody*, const void*, const void*, const void*);
        ((DispatchFn)(*(void**)((char*)dispatcher + 0x998 + (uint)slot * 0x14)))(dispatcher, &child, &bodyB,
                                                                                input, collector);
    }

    hkTimerEnd();
}

// ------------------------------------------------------------------ 010e5bf0
// @ 0x010e5bf0
void hkMultiSphereAgent::linearCast(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                    const void* input, void* collector, void* collector2)
{
    hkTimerBegin(s_timerMultiSphere);

    hkMotionState motion = *(const hkMotionState*)bodyA.m_motion;
    hkCdBody child(bodyA);

    const hkMultiSphereShape* shape = (const hkMultiSphereShape*)bodyA.m_shape;
    const hkMultiSphereChild* children = m_children;

    for (int i = m_numChildren - 1; i >= 0; --i)
    {
        const hkVector4& offset = shape->m_spheres[children[i].m_sphereIndex];

        hkTransform childTransform;
        hkSphereTransform(childTransform, motion.m_transform, offset);
        child.m_transform = &childTransform;

        void* agent = *(void**)children[i].m_body;
        hkChildDispatch fn = (hkChildDispatch)(((void**)*(void**)agent)[4]);
        ((void (__thiscall*)(void*, const hkCdBody*, const void*, const void*, const void*, const void*))fn)
            (agent, &child, &bodyB, input, collector, collector2);
    }

    hkTimerEnd();
}

// ------------------------------------------------------------------ 010e5dd0
// @ 0x010e5dd0
void hkMultiSphereAgent::staticLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                          const void* input, void* collector, void* collector2)
{
    hkTimerBegin(s_timerMultiSphere);

    hkMotionState motion = *(const hkMotionState*)bodyA.m_motion;
    hkCdBody child(bodyA);

    const hkMultiSphereShape* shape = (const hkMultiSphereShape*)bodyA.m_shape;
    int numSpheres = shape->m_numSpheres;

    int shapeType = ((int (__thiscall*)(void*))(((void**)*(void**)(void*)bodyB.m_shape)[2]))((void*)bodyB.m_shape);

    for (int i = 0; i < numSpheres; ++i)
    {
        const hkVector4& offset = shape->m_spheres[i];

        hkTransform childTransform;
        hkSphereTransform(childTransform, motion.m_transform, offset);
        child.m_transform = &childTransform;

        uchar slot = ((const uchar*)input)[400 + (uint)shapeType];
        void* dispatcher = (void*)input;
        typedef void (__thiscall *DispatchFn)(void*, const hkCdBody*, const void*, const void*, const void*,
                                              const void*);
        ((DispatchFn)(*(void**)((char*)dispatcher + (uint)slot * 4)))(dispatcher, &child, &bodyB, input,
                                                                     collector, collector2);
    }

    hkTimerEnd();
}

// ------------------------------------------------------------------ 010e5fd0
// @ 0x010e5fd0
void hkMultiSphereAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                         const void* input, void* collector)
{
    hkTimerBegin(s_timerMultiSphere);

    hkMotionState motion = *(const hkMotionState*)bodyA.m_motion;
    hkCdBody child(bodyA);

    const hkMultiSphereShape* shape = (const hkMultiSphereShape*)bodyA.m_shape;
    const hkMultiSphereChild* children = m_children;

    for (int i = m_numChildren - 1; i >= 0; --i)
    {
        const hkVector4& offset = shape->m_spheres[children[i].m_sphereIndex];

        hkTransform childTransform;
        hkSphereTransform(childTransform, motion.m_transform, offset);
        child.m_transform = &childTransform;

        void* agent = *(void**)children[i].m_body;
        ((hkChildDispatch)(((void**)*(void**)agent)[3]))(agent, &child, &bodyB, input, collector);
    }

    hkTimerEnd();
}

// ------------------------------------------------------------------ 010e61a0
// @ 0x010e61a0
void hkMultiSphereAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                               const void* input, void* collector)
{
    hkTimerBegin(s_timerMultiSphere);

    hkMotionState motion = *(const hkMotionState*)bodyA.m_motion;
    hkCdBody child(bodyA);

    const hkMultiSphereShape* shape = (const hkMultiSphereShape*)bodyA.m_shape;
    int numSpheres = shape->m_numSpheres;

    int shapeType = ((int (__thiscall*)(void*))(((void**)*(void**)(void*)bodyB.m_shape)[2]))((void*)bodyB.m_shape);

    for (int i = 0; i < numSpheres; ++i)
    {
        const hkVector4& offset = shape->m_spheres[i];

        hkTransform childTransform;
        hkSphereTransform(childTransform, motion.m_transform, offset);
        child.m_transform = &childTransform;

        uchar slot = ((const uchar*)input)[400 + (uint)shapeType];
        void* dispatcher = (void*)input;
        typedef void (__thiscall *DispatchFn)(void*, const hkCdBody*, const void*, const void*, const void*);
        ((DispatchFn)(*(void**)((char*)dispatcher + 0x994 + (uint)slot * 0x14)))(dispatcher, &child, &bodyB,
                                                                                input, collector);
    }

    hkTimerEnd();
}
