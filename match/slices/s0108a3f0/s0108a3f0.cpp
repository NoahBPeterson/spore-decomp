// slice s0108a3f0 -- Havok 3.1.0 hkGenericConstraintData / hkConstraintChainInstance /
// hkLimitedHingeConstraintData.
//
// In address order:
//   0108a3f0  hkGenericConstraintData::buildJacobianInternal  (scheme command walker)
//   0108a980  hkGenericConstraintDataScheme::~                (4 hkArray frees)
//   0108aa40  hkGenericConstraintData::hkGenericConstraintData
//   0108aaa0  hkGenericConstraintData::~                      (motor refcounts + scheme dtor)
//   0108aaf0  hkGenericConstraintData::buildJacobian
//   0108aba0  hkConstraintChainInstance::entityRemovedCallback
//   0108ac30  hkConstraintChainInstance::addEntity
//   0108acb0  hkConstraintChainInstance::hkConstraintChainInstance
//   0108ad30  hkConstraintChainInstance::~
//   0108ae30  hkLimitedHingeConstraintData::hkLimitedHingeConstraintData
//   0108aec0  hkLimitedHingeConstraintData::setInBodySpace
//   0108b150  hkLimitedHingeConstraintData::isValid
#include <stddef.h>
#include <math.h>
#include <new>
#include "types.h"

typedef float hkReal;

// ----------------------------------------------------------------------------- core Havok types
class hkTransform;

class __declspec(align(16)) hkVector4 {
public:
    float x, y, z, w;
    void setZero() { x = y = z = w = 0.0f; }
    // Sets *this = t->m_rotation * v + t->m_translation.
    void setTransformedPos( const hkTransform* t, const hkVector4* v );   // 0x1081360
};

class hkMatrix3 {
public:
    hkVector4 m_col0;   // +0x00
    hkVector4 m_col1;   // +0x10
    hkVector4 m_col2;   // +0x20
    void setMul( const hkMatrix3& a, const hkMatrix3& b );
};

class hkRotation : public hkMatrix3 {};

class hkTransform {
public:
    hkRotation m_rotation;   // +0x00
    hkVector4  m_translation;// +0x30
};

class hkBool {
public:
    char m_bool;
    hkBool() {}
    hkBool( char b ) : m_bool( b ) {}
};

class hkBaseObject {
public:
    virtual ~hkBaseObject() {}
};

class hkReferencedObject : public hkBaseObject {
public:
    unsigned short m_memSizeAndFlags;   // +0x04
    short          m_referenceCount;    // +0x06
    hkReferencedObject() { m_referenceCount = 1; }
    void addReference() const;
    void removeReference() const;
};

// 3.1 hkThreadMemory: deallocateChunk is 0x107db10, reached through TlsGetValue(g_hkThreadMemoryTls).
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue( unsigned long index );
extern unsigned int g_hkThreadMemoryTls;   // 0x16e4174

class hkThreadMemory {
public:
    void deallocateChunk( void* p, int nbytes, int align );
    static hkThreadMemory* getCurrent();
};

hkThreadMemory* hkThreadMemory::getCurrent()
{
    return (hkThreadMemory*)TlsGetValue( g_hkThreadMemoryTls );
}

template <typename T> class hkArray {
public:
    T*  m_data;
    int m_size;
    int m_capacityAndFlags;
    hkArray() { m_data = 0; m_size = 0; m_capacityAndFlags = 0x80000000; }
    ~hkArray()
    {
        if ( ( m_capacityAndFlags & 0x80000000 ) == 0 )
            hkThreadMemory::getCurrent()->deallocateChunk(
                m_data, ( m_capacityAndFlags & 0x3fffffff ) * (int)sizeof(T), 0x14 );
    }
};

struct hkConstraintInfo {
    int m_maxSizeOfJacobians;
    int m_sizeOfJacobians;
    int m_sizeOfSchemas;
    int m_numSolverResults;
};

class hkGenericConstraintDataScheme {
public:
    hkConstraintInfo      m_info;        // +0x00
    hkArray<hkVector4>    m_data;        // +0x10
    hkArray<int>          m_commands;    // +0x1c
    hkArray<void*>        m_modifiers;   // +0x28
    hkArray<void*>        m_motors;      // +0x34

    hkGenericConstraintDataScheme();
};

hkGenericConstraintDataScheme::hkGenericConstraintDataScheme()
{
    m_info.m_maxSizeOfJacobians = 0;
    m_info.m_sizeOfJacobians = 0;
    m_info.m_sizeOfSchemas = 0;
    m_info.m_numSolverResults = 0;
}

class hkGenericConstraintDataParameters {
public:
    hkVector4   m_pivotAw;               // +0x00
    hkVector4   m_pivotBw;               // +0x10
    hkVector4   m_linearBasisW[3];       // +0x20
    hkVector4   m_angularBasisAw[3];     // +0x50
    hkVector4   m_angularBasisBw[3];     // +0x80
    const void* m_rbA;                   // +0xb0
    const void* m_rbB;                   // +0xb4
    int         m_currentResult;         // +0xb8
};

class hkConstraintQueryIn {
public:
    char        m_pad00[0x18];
    hkReal      m_rhsFactor;             // +0x18
    char        m_pad1c[0x30 - 0x1c];
    const hkTransform* m_transformA;     // +0x30
    const hkTransform* m_transformB;     // +0x34
    char        m_pad38[0x44 - 0x38];
    const char* m_solverResults;         // +0x44
};

class hkConstraintQueryOut {
public:
    void* m_constraintInternal;          // +0x00
};

class hkConstraintData : public hkReferencedObject {
public:
    unsigned int m_userData;             // +0x08
    hkConstraintData() { m_userData = 0; }
    virtual void buildJacobian( const hkConstraintQueryIn& in, hkConstraintQueryOut& out );
};

// --------------------------------------------------------- hkGenericConstraintData
class hkGenericConstraintData : public hkConstraintData {
public:
    hkGenericConstraintDataScheme m_scheme;   // +0x0c

    hkGenericConstraintData();
    virtual ~hkGenericConstraintData();
    virtual void buildJacobian( const hkConstraintQueryIn& in, hkConstraintQueryOut& out );

private:
    void buildJacobianInternal( const hkGenericConstraintDataScheme& scheme,
                                const hkConstraintQueryIn& in, hkConstraintQueryOut& out );

    // scheme command handlers (defined in slice s010898f0).
    void constrainToAngularW ( int*& cc, hkVector4*& cd, const hkGenericConstraintDataScheme& s,   // 0x10898f0
                               hkGenericConstraintDataParameters& v,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void constrainAllAngularW( int*& cc, hkVector4*& cd, const hkGenericConstraintDataScheme& s,   // 0x1089a20
                               hkGenericConstraintDataParameters& v,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setLinearLimitW     ( int*& cc, hkVector4*& cd, const hkGenericConstraintDataScheme& s,   // 0x1089ba0
                               hkGenericConstraintDataParameters& v,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setAngularLimitW    ( int*& cc, hkVector4*& cd, const hkGenericConstraintDataScheme& s,   // 0x1089c60
                               hkGenericConstraintDataParameters& v,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setConeLimitW       ( int*& cc, hkVector4*& cd, const hkGenericConstraintDataScheme& s,   // 0x1089d70
                               hkGenericConstraintDataParameters& v,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setTwistLimitW      ( int*& cc, hkVector4*& cd, const hkGenericConstraintDataScheme& s,   // 0x1089f10
                               hkGenericConstraintDataParameters& v,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setAngularMotorW    ( int*& cc, hkVector4*& cd, hkGenericConstraintDataScheme& s,         // 0x1089fc0
                               hkGenericConstraintDataParameters& v,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setLinearMotorW     ( int*& cc, hkVector4*& cd, hkGenericConstraintDataScheme& s,         // 0x108a180
                               hkGenericConstraintDataParameters& v,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setAngularFrictionW ( int*& cc, hkVector4*& cd, const hkGenericConstraintDataScheme& s,   // 0x108a2b0
                               hkGenericConstraintDataParameters& v,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setLinearFrictionW  ( int*& cc, hkVector4*& cd, const hkGenericConstraintDataScheme& s,   // 0x108a330
                               hkGenericConstraintDataParameters& v,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;

    // Linear-DOF builder helpers (defined in slice s01088960).
    void buildLinearDof( int*& cc, hkVector4*& cd, const hkGenericConstraintDataScheme& s,   // 0x10897d0
                         hkGenericConstraintDataParameters& v,
                         const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void buildLinearBasisWorld( int*& cc, hkVector4*& cd, const hkGenericConstraintDataScheme& s,   // 0x1089700
                         hkGenericConstraintDataParameters& v,
                         const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
};

// external helpers (Havok runtime / other slices)
extern "C" void hkBeginConstraints( const hkConstraintQueryIn* in, hkConstraintQueryOut* out,
        int numResults, int extra );                                               // 0x10aa080
extern "C" void hkReplacePreviousRhs( float value, const hkConstraintQueryIn* in,
        hkConstraintQueryOut* out, int count );                               // 0x10aa050
extern "C" void hkMatrix3_setIdentity( hkMatrix3* m );                             // 0x48daf0
extern "C" hkBool hkMath_equal( float a, float b, float eps );                     // 0x1080e40

// --------------------------------------------------------------------------------- walker
// Constraint-modifier entry points (scheme.m_modifiers): slot 1 = doConstraintModifier,
// slot 2 = doRhsModifier, both taking the parameters block and one integer operand.
typedef void  (*ModifierFn)( hkGenericConstraintDataParameters*, int );
typedef float (*ModifierFloatFn)( hkGenericConstraintDataParameters*, int );

// @ 0x0108a3f0
void hkGenericConstraintData::buildJacobianInternal( const hkGenericConstraintDataScheme& scheme,
        const hkConstraintQueryIn& in, hkConstraintQueryOut& out )
{
    hkConstraintQueryIn inCopy = in;
    hkGenericConstraintDataParameters vars;

    int*       currentCommand = scheme.m_commands.m_data;
    hkVector4* currentData    = scheme.m_data.m_data;
    void**     currentModifier = (void**)scheme.m_modifiers.m_data;
    float      strength = 0.0f;

    for ( ;; ) {
        switch ( *currentCommand ) {
        case 0:
            return;
        case 1:
            vars.m_pivotAw.setTransformedPos( inCopy.m_transformA, currentData );
            ++currentData;
            ++currentCommand;
            break;
        case 2:
            vars.m_pivotBw.setTransformedPos( inCopy.m_transformB, currentData );
            ++currentData;
            ++currentCommand;
            break;
        case 3:
        case 4: {
            const hkMatrix3* base = ( *currentCommand == 3 ) ? (const hkMatrix3*)inCopy.m_transformA
                                                             : (const hkMatrix3*)inCopy.m_transformB;
            const int idx = currentCommand[ 1 ];
            const hkVector4 v = *currentData;
            hkVector4& t = vars.m_linearBasisW[ idx ];
            t.x = v.x * base->m_col0.x + v.y * base->m_col1.x + v.z * base->m_col2.x;
            t.y = v.x * base->m_col0.y + v.y * base->m_col1.y + v.z * base->m_col2.y;
            t.z = v.x * base->m_col0.z + v.y * base->m_col1.z + v.z * base->m_col2.z;
            t.w = 0.0f;
            ++currentData;
            currentCommand += 2;
            break;
        }
        case 5: {
            const int idx = currentCommand[ 1 ];
            vars.m_linearBasisW[ idx ] = *currentData;
            ++currentData;
            currentCommand += 2;
            break;
        }
        case 6:
            buildLinearDof( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 7:
            buildLinearBasisWorld( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 8:
            ((hkMatrix3*)&vars.m_linearBasisW[0])->setMul( *(const hkMatrix3*)inCopy.m_transformA,
                                                           *(const hkMatrix3*)currentData );
            currentData += 3;
            ++currentCommand;
            break;
        case 9:
            ((hkMatrix3*)&vars.m_linearBasisW[0])->setMul( *(const hkMatrix3*)inCopy.m_transformB,
                                                           *(const hkMatrix3*)currentData );
            currentData += 3;
            ++currentCommand;
            break;
        case 10:
            hkMatrix3_setIdentity( (hkMatrix3*)&vars.m_angularBasisAw[0] );
            ++currentCommand;
            break;
        case 11:
            hkMatrix3_setIdentity( (hkMatrix3*)&vars.m_angularBasisBw[0] );
            ++currentCommand;
            break;
        case 12:
            constrainToAngularW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 13:
            constrainAllAngularW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 14:
            setAngularMotorW( currentCommand, currentData,
                              const_cast<hkGenericConstraintDataScheme&>(scheme), vars, inCopy, out );
            ++currentCommand;
            break;
        case 15:
            setLinearMotorW( currentCommand, currentData,
                             const_cast<hkGenericConstraintDataScheme&>(scheme), vars, inCopy, out );
            ++currentCommand;
            break;
        case 16:
            setLinearLimitW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 17:
            setAngularLimitW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 18:
            setConeLimitW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 19:
            setTwistLimitW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 20:
            setAngularFrictionW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 21:
            setLinearFrictionW( currentCommand, currentData, scheme, vars, inCopy, out );
            ++currentCommand;
            break;
        case 22:
            strength = strength * currentData->x;
            ++currentData;
            ++currentCommand;
            break;
        case 23:
            strength = inCopy.m_rhsFactor;
            ++currentCommand;
            break;
        case 24:
            ( *(ModifierFn)*currentModifier )( &vars, currentCommand[ 1 ] );
            currentCommand += 2;
            ++currentModifier;
            break;
        case 25: {
            const float f = ( *(ModifierFloatFn)*currentModifier )( &vars, currentCommand[ 1 ] );
            hkReplacePreviousRhs( f, &inCopy, &out, 1 );
            currentCommand += 2;
            ++currentModifier;
            break;
        }
        default:
            ++currentCommand;
            break;
        }
    }
}

// @ 0x0108a980 -- hkGenericConstraintDataScheme::~ is generated from the four hkArray members.

// @ 0x0108aa40
hkGenericConstraintData::hkGenericConstraintData()
{
    m_scheme.m_info.m_sizeOfSchemas = 24;
}

// @ 0x0108aaa0
hkGenericConstraintData::~hkGenericConstraintData()
{
    for ( int i = 0; i < m_scheme.m_motors.m_size; ++i ) {
        hkReferencedObject* motor = (hkReferencedObject*)m_scheme.m_motors.m_data[ i ];
        if ( motor->m_memSizeAndFlags != 0 ) {
            if ( --motor->m_referenceCount == 0 )
                delete motor;
        }
    }
}

// @ 0x0108aaf0
void hkGenericConstraintData::buildJacobian( const hkConstraintQueryIn& in, hkConstraintQueryOut& out )
{
    hkBeginConstraints( &in, &out, (int)(size_t)in.m_solverResults, 8 );
    buildJacobianInternal( m_scheme, in, out );
}

// ------------------------------------------------------- hkConstraintChainInstance
class hkEntity : public hkReferencedObject {
public:
    void* m_world;          // +0x08
};

class hkAction : public hkReferencedObject {};
class hkWorldObject : public hkReferencedObject {
public:
    void removeReference();                                  // 0x109ae60
};
class hkWorld;

class hkConstraintInstance : public hkReferencedObject {
public:
    hkConstraintInstance( int wantRuntime );
    virtual ~hkConstraintInstance();

    void*   m_owner;        // +0x08
    void*   m_data;         // +0x0c
    void*   m_entities[2];  // +0x10
    char    m_priority;     // +0x18
    char    m_wantRuntime;  // +0x19
    char*   m_name;         // +0x1c
    int     m_userData;     // +0x20
    char    m_pad24[4];
};

class hkWorld {
public:
    void removeActionImmediately( hkAction* action );         // 0x1086030
    void executePendingOperations();                         // 0x1082bf0
    char m_pad00[0x88];
    int  m_pending;                                          // +0x88
    int  m_refCount;                                         // +0x8c
    char m_pad90[4];
    char m_flag94;                                           // +0x94
};

class hkConstraintChainInstance;

// hkMemory: the runtime allocator singleton at 0x16e4178; slot +0x10 is allocate().
class hkMemory {
public:
    virtual void memoryUnused0();
    virtual void memoryUnused1();
    virtual void memoryUnused2();
    virtual void memoryUnused3();
    virtual void* allocate( int numBytes, int align );       // +0x10
    static hkMemory* s_instance;                             // 0x16e4178
};

// The action the chain instance registers with its world; holds a back-pointer at +0x18.
class hkConstraintChainInstanceAction : public hkAction {
public:
    hkConstraintChainInstanceAction( hkConstraintChainInstance* instance );

    unsigned int m_pad08[4];                                 // +0x08 .. +0x17
    hkConstraintChainInstance* m_chainInstance;              // +0x18
};

class hkConstraintChainInstance : public hkConstraintInstance {
public:
    hkArray<void*> m_chainedEntities;    // +0x28
    hkAction*      m_action;             // +0x34

    hkConstraintChainInstance( void* data );
    virtual ~hkConstraintChainInstance();
    virtual void entityRemovedCallback( hkEntity* entity );
    void addEntity( void* entity );
};

hkConstraintChainInstanceAction::hkConstraintChainInstanceAction( hkConstraintChainInstance* instance )
{
    m_memSizeAndFlags = 0x1c;
    m_pad08[ 0 ] = 0;
    m_pad08[ 1 ] = 0;
    m_pad08[ 2 ] = 0;
    m_pad08[ 3 ] = 0;
    m_chainInstance = instance;
}

extern "C" void hkWorldOperationUtil_removeConstraintImmediately( hkWorld* world,
        hkConstraintChainInstance* instance, int force );           // 0x109fa10
extern "C" void hkWorldObject_removeReference( hkWorldObject* obj );   // 0x109ae60
extern "C" void hkArrayUtil_reserveMore( void* array, int elems );     // 0x107f530
extern "C" void hkReferencedObject_addReference( hkReferencedObject* obj );  // 0x1082590

// @ 0x0108aba0
void hkConstraintChainInstance::entityRemovedCallback( hkEntity* entity )
{
    hkWorld* world = (hkWorld*)entity->m_world;
    world->m_refCount++;
    world->removeActionImmediately( m_action );
    hkWorldOperationUtil_removeConstraintImmediately( world, this, 1 );
    if ( --world->m_refCount == 0 && world->m_pending != 0 && world->m_flag94 == 0 )
        world->executePendingOperations();
}

// @ 0x0108ac30
void hkConstraintChainInstance::addEntity( void* entity )
{
    hkReferencedObject* ref = (hkReferencedObject*)entity;
    const int size = m_chainedEntities.m_size;
    if ( size < 2 && m_entities[ size ] == 0 ) {
        m_entities[ size ] = entity;
        ref->addReference();
    }
    hkArray<void*>& chain = m_chainedEntities;
    if ( chain.m_size == ( chain.m_capacityAndFlags & 0x3fffffff ) )
        hkArrayUtil_reserveMore( &chain, 4 );
    chain.m_data[ chain.m_size ] = entity;
    ++chain.m_size;
    ref->addReference();
}

// @ 0x0108acb0
hkConstraintChainInstance::hkConstraintChainInstance( void* data )
    : hkConstraintInstance( 1 )
{
    m_data = data;
    if ( *(unsigned short*)( (char*)data + 4 ) != 0 )
        ++*(short*)( (char*)data + 6 );
    m_entities[ 0 ] = 0;
    m_entities[ 1 ] = 0;

    void* mem = hkMemory::s_instance->allocate( 0x1c, 0x26 );
    hkConstraintChainInstanceAction* action =
        new (mem) hkConstraintChainInstanceAction( this );
    m_action = action;
}

// @ 0x0108ad30
hkConstraintChainInstance::~hkConstraintChainInstance()
{
    for ( int i = 0; i < m_chainedEntities.m_size; ++i )
        ( (hkWorldObject*)m_chainedEntities.m_data[ i ] )->removeReference();

    hkAction* action = m_action;
    if ( action->m_memSizeAndFlags != 0 ) {
        if ( --action->m_referenceCount == 0 )
            delete action;
    }
}

// ------------------------------------------------ hkLimitedHingeConstraintData
class hkLimitedHingeConstraintData : public hkConstraintData {
public:
    hkReal  m_minAngle;              // +0x0c
    hkReal  m_maxAngle;              // +0x10
    hkReal  m_maxFrictionTorque;     // +0x14
    hkReal  m_angularLimitsTauFactor;// +0x18
    char    m_pad1c[4];

    struct ConstraintBasisA {
        hkVector4 m_pivot;           // object +0x20
        hkVector4 m_axle;            // object +0x30
        hkVector4 m_perpToAxle1;     // object +0x40
        hkVector4 m_perpToAxle2;     // object +0x50
    } m_basisA;                      // +0x20

    struct ConstraintBasisB {
        hkVector4 m_pivot;           // object +0x60
        hkVector4 m_axle;            // object +0x70
        hkVector4 m_perp2FreeAxis;   // object +0x80
    } m_basisB;                      // +0x60

    hkLimitedHingeConstraintData();
    virtual ~hkLimitedHingeConstraintData();
    void setInBodySpace( const hkVector4& pivotA, const hkVector4& pivotB,
                         const hkVector4& axleA, const hkVector4& axleB,
                         const hkVector4& referenceA, const hkVector4& referenceB );
    virtual hkBool isValid() const;
};

// Scales all four components of v by 1/|v.xyz|; a zero-length vector is left at zero.
static __forceinline void hkVector4_normalize3( hkVector4& v )
{
    float len2 = v.x * v.x + v.y * v.y + v.z * v.z;
    float inv;
    if ( len2 == 0.0f )
        inv = 0.0f;
    else
        inv = 1.0f / sqrtf( len2 );
    v.x *= inv;
    v.y *= inv;
    v.z *= inv;
    v.w *= inv;
}

// @ 0x0108ae30
hkLimitedHingeConstraintData::hkLimitedHingeConstraintData()
{
    m_minAngle               = -3.1415927f;
    m_maxAngle               =  3.1415927f;
    m_maxFrictionTorque      =  0.0f;
    m_angularLimitsTauFactor =  1.0f;
    m_basisA.m_pivot.setZero();
    m_basisA.m_axle.setZero();
    m_basisA.m_perpToAxle1.setZero();
    m_basisA.m_perpToAxle2.setZero();
    m_basisB.m_pivot.setZero();
    m_basisB.m_axle.setZero();
    m_basisB.m_perp2FreeAxis.setZero();
}

// @ 0x0108aec0
void hkLimitedHingeConstraintData::setInBodySpace( const hkVector4& pivotA, const hkVector4& pivotB,
        const hkVector4& axleA, const hkVector4& axleB,
        const hkVector4& referenceA, const hkVector4& referenceB )
{
    m_basisA.m_pivot = pivotA;
    m_basisB.m_pivot = pivotB;
    m_basisA.m_axle  = axleA;
    m_basisB.m_axle  = axleB;

    hkVector4_normalize3( m_basisA.m_axle );
    hkVector4_normalize3( m_basisB.m_axle );

    m_basisA.m_perpToAxle2 = referenceA;
    hkVector4_normalize3( m_basisA.m_perpToAxle2 );
    m_basisA.m_perpToAxle1.w = 0.0f;
    m_basisA.m_perpToAxle1.x = m_basisA.m_axle.z * m_basisA.m_perpToAxle2.y
                             - m_basisA.m_perpToAxle2.z * m_basisA.m_axle.y;
    m_basisA.m_perpToAxle1.y = m_basisA.m_perpToAxle2.z * m_basisA.m_axle.x
                             - m_basisA.m_axle.z * m_basisA.m_perpToAxle2.x;
    m_basisA.m_perpToAxle1.z = m_basisA.m_axle.y * m_basisA.m_perpToAxle2.x
                             - m_basisA.m_axle.x * m_basisA.m_perpToAxle2.y;

    m_basisB.m_perp2FreeAxis = referenceB;
    hkVector4_normalize3( m_basisB.m_perp2FreeAxis );
}

// @ 0x0108b150
hkBool hkLimitedHingeConstraintData::isValid() const
{
    const float eps  = 1.0e-5f;
    const float fmax = 6.2831855f;

    float dotA = m_basisA.m_perpToAxle2.x * m_basisA.m_perpToAxle1.x
               + m_basisA.m_perpToAxle2.y * m_basisA.m_perpToAxle1.y
               + m_basisA.m_perpToAxle2.z * m_basisA.m_perpToAxle1.z;
    if ( fabsf( dotA ) >= eps )
        goto fail;

    float dotB = m_basisB.m_perp2FreeAxis.x * m_basisB.m_axle.x
               + m_basisB.m_perp2FreeAxis.y * m_basisB.m_axle.y
               + m_basisB.m_perp2FreeAxis.z * m_basisB.m_axle.z;
    if ( fabsf( dotB ) >= eps )
        goto fail;

    if ( fabsf( m_basisA.m_perpToAxle1.x * m_basisA.m_perpToAxle1.x
              + m_basisA.m_perpToAxle1.y * m_basisA.m_perpToAxle1.y
              + m_basisA.m_perpToAxle1.z * m_basisA.m_perpToAxle1.z - 1.0f ) >= eps )
        goto fail;

    if ( fabsf( m_basisA.m_perpToAxle2.x * m_basisA.m_perpToAxle2.x
              + m_basisA.m_perpToAxle2.y * m_basisA.m_perpToAxle2.y
              + m_basisA.m_perpToAxle2.z * m_basisA.m_perpToAxle2.z - 1.0f ) >= eps )
        goto fail;

    if ( fabsf( m_basisB.m_axle.x * m_basisB.m_axle.x
              + m_basisB.m_axle.y * m_basisB.m_axle.y
              + m_basisB.m_axle.z * m_basisB.m_axle.z - 1.0f ) >= eps )
        goto fail;

    {
        float len2 = m_basisA.m_axle.x * m_basisA.m_axle.x
                   + m_basisA.m_axle.y * m_basisA.m_axle.y
                   + m_basisA.m_axle.z * m_basisA.m_axle.z;
        if ( hkMath_equal( len2, 1.0f, 1.0e-5f ).m_bool == 0 )
            goto fail;
    }

    {
        float span;
        if ( ( m_minAngle < 0.0f ) == ( m_minAngle == 0.0f )
          || ( m_maxAngle < 0.0f ) == ( m_maxAngle == 0.0f ) )
            span = m_maxAngle - m_minAngle;
        else
            span = fabsf( m_minAngle ) + m_maxAngle;
        if ( span <= fmax )
            return hkBool( (char)1 );
    }

fail:
    return hkBool( (char)0 );
}