// slice s010898f0 -- Havok 3.1.0 hkGenericConstraintData scheme command handlers.
//
// The constraint construction kit serialises a constraint as a stream of command words.
// At runtime hkGenericConstraintData walks that stream and, for every command, copies the
// relevant basis vectors out of hkGenericConstraintDataParameters (pivotAw / pivotBw /
// linearBasisW / angularBasisAw / angularBasisBw; layout identical to
// hkpGenericConstraintDataParameters) into a small "info" block, hands that block to the
// matching hk1d*BuildJacobian helper together with the query in/out pair, and bumps
// m_currentResult by the number of solver results the helper produced.
//
// Handlers in address order:
//   010898f0 constrainToAngularW      (2 jacobians)
//   01089a20 constrainAllAngularW     (3 jacobians, no operand)
//   01089ba0 setLinearLimitW          (1 jacobian)
//   01089c60 setAngularLimitW         (1 jacobian)
//   01089d70 setConeLimitW            (1 jacobian)
//   01089f10 setTwistLimitW           (1 jacobian)
//   01089fc0 setAngularMotorW         (motor begin/commit, 1 jacobian)
//   0108a180 setLinearMotorW          (motor begin/commit, 1 jacobian)
//   0108a2b0 setAngularFrictionW      (1 jacobian)
//   0108a330 setLinearFrictionW       (1 jacobian)
#include <stddef.h>
#include <math.h>
#include "types.h"

class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };

template <typename T> class hkArray {
public:
    T*  m_data;
    int m_size;
    int m_capacityAndFlags;
};

struct hkConstraintInfo {
    int m_maxSizeOfJacobians;
    int m_sizeOfJacobians;
    int m_sizeOfSchemas;
    int m_numSolverResults;
};

// hkpGenericConstraintDataScheme; +0x34 is m_motors.m_data (hkArray<hkpConstraintMotor*>).
class hkGenericConstraintDataScheme {
public:
    hkConstraintInfo    m_info;         // +0x00
    hkArray<hkVector4>  m_data;         // +0x10
    hkArray<int>        m_commands;     // +0x1c
    hkArray<void*>      m_modifiers;    // +0x28
    hkArray<void*>      m_motors;       // +0x34
};

// hkpGenericConstraintDataParameters (3.1 layout, verified against every offset used here).
class hkGenericConstraintDataParameters {
public:
    hkVector4   m_pivotAw;              // +0x00
    hkVector4   m_pivotBw;              // +0x10
    hkVector4   m_linearBasisW[3];      // +0x20
    hkVector4   m_angularBasisAw[3];    // +0x50
    hkVector4   m_angularBasisBw[3];    // +0x80
    const void* m_rbA;                  // +0xb0
    const void* m_rbB;                  // +0xb4
    int         m_currentResult;        // +0xb8
};

// hkConstraintQueryIn.  Only +0x44 is read by these handlers: the base of the array of
// 8-byte solver results (indexed by hkGenericConstraintDataParameters::m_currentResult).
class hkConstraintQueryIn {
public:
    char        m_pad[0x44];
    const char* m_solverResults;        // +0x44
};

// hkConstraintQueryOut; the first dword is the hkConstraintInternal being filled.
class hkConstraintQueryOut {
public:
    void* m_constraintInternal;         // +0x00
};

class hkConstraintMotor {
public:
    virtual void unused0();
    virtual void unused1();
    virtual void update( void* jacobian, void* runtime );   // vtable slot 2
};

// ---------------------------------------------------------------- info blocks handed to the helpers
struct hk1dAngularBilateralInfo {
    hkVector4 m_axisA;                  // +0x00
    hkVector4 m_axisB;                  // +0x10
    hkVector4 m_axisW;                  // +0x20
};

struct hk1dLinearLimitInfo {
    hkVector4 m_pivotA;                 // +0x00
    hkVector4 m_pivotB;                 // +0x10
    hkVector4 m_dofW;                   // +0x20
    float     m_min;                    // +0x30
    float     m_max;                    // +0x34
};

struct hk1dAngularLimitInfo {
    hkVector4 m_axis;                   // +0x00
    float     m_min;                    // +0x10
    float     m_max;                    // +0x14
    float     m_angle;                  // +0x18
    float     m_tau;                    // +0x1c  (always 0.5f)
};

struct hk1dAngularFrictionInfo {
    const hkVector4* m_axis;            // +0x00
    const char*      m_solver;          // +0x04
    float            m_maxImpulse;      // +0x08
    int              m_useVelocity;     // +0x0c  (always 1)
};

struct hk1dLinearFrictionInfo {
    hkVector4   m_deltaPivot;           // +0x00
    hkVector4   m_dofW;                 // +0x10
    float       m_maxImpulse;           // +0x20
    const char* m_solver;               // +0x24
};

struct hk1dAngularMotorInfo {
    void*       m_constraintInternal;   // +0x00
    const hkConstraintQueryIn* m_in;    // +0x04
    const char* m_solver;               // +0x08
    const char* m_solver2;              // +0x0c
    int         m_unknown;              // +0x10
    float       m_targetAngle;          // +0x14
    char        m_scratch[24];          // +0x18
};

struct hk1dLinearMotorInfo {
    hkVector4   m_dofW;                 // +0x00
    void*       m_constraintInternal;   // +0x10
    const hkConstraintQueryIn* m_in;    // +0x14
    const char* m_solver;               // +0x18
    const char* m_solver2;              // +0x1c
    int         m_unknown;              // +0x20
    float       m_targetVelocity;       // +0x24
    char        m_scratch[36];          // +0x28
};

// ---------------------------------------------------------------------------- external helpers
// Plain C symbols in the Havok runtime.
extern "C" void hk1dAngularBilateralConstraintBuildJacobian( const hk1dAngularBilateralInfo* info,
                                                            const hkConstraintQueryIn* in, hkConstraintQueryOut* out );
extern "C" void hk1dLinearLimitBuildJacobian( const hk1dLinearLimitInfo* info,
                                             const hkConstraintQueryIn* in, hkConstraintQueryOut* out );
extern "C" void hk1dAngularLimitBuildJacobian( const hk1dAngularLimitInfo* info,
                                              const hkConstraintQueryIn* in, hkConstraintQueryOut* out );
extern "C" void hk1dAngularFrictionBuildJacobian( const hk1dAngularFrictionInfo* info,
                                                 const hkConstraintQueryIn* in, hkConstraintQueryOut* out );
extern "C" void hk1dLinearFrictionBuildJacobian( const hk1dLinearFrictionInfo* info,
                                                const hkConstraintQueryIn* in, hkConstraintQueryOut* out );
extern "C" void hk1dAngularVelocityMotorBeginJacobian( const hkVector4* axisW, const hkConstraintQueryIn* in,
                                                      void* constraintInternal, void* infoOut );
extern "C" void hk1dAngularVelocityMotorCommitJacobian( const void* infoTail,
                                                       const hkConstraintQueryIn* in, float targetAngle );
extern "C" void hk1dLinearVelocityMotorBeginJacobian( const hkVector4* dofW, const hkVector4* pivotBw,
                                                     const hkConstraintQueryIn* in, void* constraintInternal,
                                                     void* infoOut );
extern "C" void hk1dLinearVelocityMotorCommitJacobian( const void* infoTail,
                                                      const hkConstraintQueryIn* in, hkConstraintQueryOut* out );

namespace hkInternalConstraintUtils {
    void calcRelativeAngle( const hkVector4& a, const hkVector4& b, const hkVector4& c,
                            const hkVector4& d, hkVector4& out, float& angle );
}
namespace hkMath { float atan2fApproximation( float y, float x ); }

// 0x015b9b80: axis + 1 / axis + 2 (mod 3) lookup used to enumerate the two rotational
// degrees of freedom that are not 'axis'.
static const int s_mod3[5] = { 0, 1, 2, 0, 1 };

// 0x01089870 -- register-convention helper: axis in ECX, hkVector4 rows in EDX.
float __fastcall hkGenericConstraint_calcAngle( int axis, const hkVector4* rows );

inline hkVector4 hkNeg4( const hkVector4& v )
{
    hkVector4 r;
    r.x = -v.x; r.y = -v.y; r.z = -v.z; r.w = -v.w;
    return r;
}

// ---------------------------------------------------------------------------------- the handlers
class hkGenericConstraintData {
protected:
    void constrainToAngularW ( int*& currentCommand, hkVector4*& currentData,
                               const hkGenericConstraintDataScheme& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void constrainAllAngularW( int*& currentCommand, hkVector4*& currentData,
                               const hkGenericConstraintDataScheme& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setLinearLimitW     ( int*& currentCommand, hkVector4*& currentData,
                               const hkGenericConstraintDataScheme& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setAngularLimitW    ( int*& currentCommand, hkVector4*& currentData,
                               const hkGenericConstraintDataScheme& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setConeLimitW       ( int*& currentCommand, hkVector4*& currentData,
                               const hkGenericConstraintDataScheme& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setTwistLimitW      ( int*& currentCommand, hkVector4*& currentData,
                               const hkGenericConstraintDataScheme& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setAngularMotorW    ( int*& currentCommand, hkVector4*& currentData,
                               hkGenericConstraintDataScheme& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setLinearMotorW     ( int*& currentCommand, hkVector4*& currentData,
                               hkGenericConstraintDataScheme& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setAngularFrictionW ( int*& currentCommand, hkVector4*& currentData,
                               const hkGenericConstraintDataScheme& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
    void setLinearFrictionW  ( int*& currentCommand, hkVector4*& currentData,
                               const hkGenericConstraintDataScheme& scheme,
                               hkGenericConstraintDataParameters& vars,
                               const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const;
};

// @ 0x010898f0
void hkGenericConstraintData::constrainToAngularW( int*& currentCommand, hkVector4*& currentData,
        const hkGenericConstraintDataScheme& scheme, hkGenericConstraintDataParameters& vars,
        const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const
{
    const int axis = *++currentCommand;

    hk1dAngularBilateralInfo info;
    info.m_axisB = vars.m_angularBasisAw[ s_mod3[axis + 1] ];
    info.m_axisA = vars.m_angularBasisAw[ s_mod3[axis + 2] ];
    info.m_axisW = vars.m_angularBasisBw[ axis ];
    hk1dAngularBilateralConstraintBuildJacobian( &info, &in, &out );

    hkVector4 negB;
    negB.x = -info.m_axisB.x;
    negB.y = -info.m_axisB.y;
    negB.z = -info.m_axisB.z;
    negB.w = -info.m_axisB.w;
    info.m_axisB = info.m_axisA;
    info.m_axisA = negB;
    hk1dAngularBilateralConstraintBuildJacobian( &info, &in, &out );

    vars.m_currentResult += 2;
}

// @ 0x01089a20
void hkGenericConstraintData::constrainAllAngularW( int*& currentCommand, hkVector4*& currentData,
        const hkGenericConstraintDataScheme& scheme, hkGenericConstraintDataParameters& vars,
        const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const
{
    hk1dAngularBilateralInfo info;

    info.m_axisA = vars.m_angularBasisAw[0];
    info.m_axisW = vars.m_angularBasisBw[1];
    info.m_axisB = vars.m_angularBasisAw[2];
    hk1dAngularBilateralConstraintBuildJacobian( &info, &in, &out );

    info.m_axisA = vars.m_angularBasisAw[1];
    info.m_axisW = vars.m_angularBasisBw[2];
    info.m_axisB = vars.m_angularBasisAw[0];
    hk1dAngularBilateralConstraintBuildJacobian( &info, &in, &out );

    info.m_axisA = vars.m_angularBasisAw[2];
    info.m_axisW = vars.m_angularBasisBw[0];
    info.m_axisB = vars.m_angularBasisAw[1];
    hk1dAngularBilateralConstraintBuildJacobian( &info, &in, &out );

    vars.m_currentResult += 3;
}

// @ 0x01089ba0
void hkGenericConstraintData::setLinearLimitW( int*& currentCommand, hkVector4*& currentData,
        const hkGenericConstraintDataScheme& scheme, hkGenericConstraintDataParameters& vars,
        const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const
{
    const int dof = *++currentCommand;

    hk1dLinearLimitInfo info;
    info.m_dofW   = vars.m_linearBasisW[ dof ];
    info.m_pivotA = vars.m_pivotAw;
    info.m_pivotB = vars.m_pivotBw;

    const hkVector4* limits = currentData++;
    info.m_min = limits->x;
    info.m_max = limits->y;

    hk1dLinearLimitBuildJacobian( &info, &in, &out );
    vars.m_currentResult += 1;
}

// @ 0x01089c60
void hkGenericConstraintData::setAngularLimitW( int*& currentCommand, hkVector4*& currentData,
        const hkGenericConstraintDataScheme& scheme, hkGenericConstraintDataParameters& vars,
        const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const
{
    const int axis = *++currentCommand;

    hk1dAngularLimitInfo info;
    info.m_tau   = 0.5f;
    info.m_axis  = vars.m_angularBasisAw[ axis ];

    info.m_angle = hkGenericConstraint_calcAngle( axis, (const hkVector4*)&vars );

    hkVector4* limits = currentData++;
    info.m_min = limits->x;
    info.m_max = limits->y;

    if ( info.m_angle < 0.0f && limits->z > 0.0f && 3.1415927f < limits->z - info.m_angle )
    {
        info.m_angle = info.m_angle + 6.2831855f;
    }
    if ( info.m_angle > 0.0f && limits->z < 0.0f && 3.1415927f < info.m_angle - limits->z )
    {
        info.m_angle = info.m_angle - 6.2831855f;
    }
    limits->z = info.m_angle;

    hk1dAngularLimitBuildJacobian( &info, &in, &out );
    vars.m_currentResult += 1;
}

// @ 0x01089d70
void hkGenericConstraintData::setConeLimitW( int*& currentCommand, hkVector4*& currentData,
        const hkGenericConstraintDataScheme& scheme, hkGenericConstraintDataParameters& vars,
        const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const
{
    const int axis = *++currentCommand;

    const float* aw = (const float*)&vars.m_angularBasisAw[ axis ];
    const float fVar2 = aw[0];
    const float fVar3 = aw[1];
    const float fVar4 = aw[2];
    const float* bw = (const float*)&vars.m_angularBasisBw[ axis ];
    const float fVar5 = bw[0];
    const float fVar6 = bw[1];
    const float fVar7 = bw[2];

    hk1dAngularLimitInfo info;
    info.m_tau = 0.5f;
    info.m_axis.x = fVar7 * fVar3 - fVar6 * fVar4;
    info.m_axis.y = fVar4 * fVar5 - fVar7 * fVar2;
    info.m_axis.z = fVar6 * fVar2 - fVar3 * fVar5;

    float fVar9 = info.m_axis.x * info.m_axis.x
                + ( info.m_axis.y * info.m_axis.y + info.m_axis.z * info.m_axis.z );
    if ( 1.1920929e-07f <= fVar9 )
    {
        float fVar1;
        if ( fVar9 == 0.0f ) fVar1 = 0.0f;
        else                 fVar1 = 1.0f / sqrtf( fVar9 );

        info.m_axis.x = fVar1 * info.m_axis.x;

        hkVector4* data = currentData++;
        info.m_axis.y = info.m_axis.y * fVar1;
        info.m_axis.z = info.m_axis.z * fVar1;
        info.m_axis.w = fVar1 * 0.0f;

        info.m_angle = fVar5 * fVar2 + ( fVar6 * fVar3 + fVar4 * fVar7 );
        info.m_min = data->x;
        info.m_max = data->y;

        hk1dAngularLimitBuildJacobian( &info, &in, &out );
        vars.m_currentResult += 1;
    }
}

// @ 0x01089f10
void hkGenericConstraintData::setTwistLimitW( int*& currentCommand, hkVector4*& currentData,
        const hkGenericConstraintDataScheme& scheme, hkGenericConstraintDataParameters& vars,
        const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const
{
    const int axisA = *++currentCommand;
    const int axisB = *++currentCommand;

    hk1dAngularLimitInfo info;
    info.m_tau = 0.5f;

    hkInternalConstraintUtils::calcRelativeAngle( vars.m_angularBasisAw[ axisA ],
                                                 vars.m_angularBasisBw[ axisA ],
                                                 vars.m_angularBasisAw[ axisB ],
                                                 vars.m_angularBasisBw[ axisB ],
                                                 info.m_axis, info.m_angle );

    hkVector4* limits = currentData++;
    info.m_min = limits->x;
    info.m_max = limits->y;

    hk1dAngularLimitBuildJacobian( &info, &in, &out );
    vars.m_currentResult += 1;
}

// @ 0x01089fc0
void hkGenericConstraintData::setAngularMotorW( int*& currentCommand, hkVector4*& currentData,
        hkGenericConstraintDataScheme& scheme, hkGenericConstraintDataParameters& vars,
        const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const
{
    const int axis = *++currentCommand;
    const char* solverResults = in.m_solverResults;

    hkVector4* data = currentData++;
    const int   turns       = *(const int*)&data->z;
    const float targetAngle = data->y;
    const int   motorIndex  = (int)data->z;

    hkConstraintMotor* motor = (hkConstraintMotor*)scheme.m_motors.m_data[ motorIndex ];

    const float* aw  = (const float*)&vars.m_angularBasisAw[ s_mod3[axis + 1] ];
    const float* bwY = (const float*)&vars.m_angularBasisBw[ s_mod3[axis + 2] ];
    const float* bwX = (const float*)&vars.m_angularBasisBw[ s_mod3[axis + 1] ];

    // Angle between the two constrained body axes, relative to the reference axis.
    float angle = hkMath::atan2fApproximation(
            -( bwY[0] * aw[0] + ( bwY[1] * aw[1] + bwY[2] * aw[2] ) ),
            -( bwX[0] * aw[0] + ( bwX[1] * aw[1] + bwX[2] * aw[2] ) ) );
    angle = angle + 3.1415927f;

    int newTurns = turns;
    if ( -3.1415927f <= angle - targetAngle )
    {
        if ( 3.1415927f < angle - targetAngle ) newTurns = (int)( (float)turns - 1.0f );
    }
    else
    {
        newTurns = (int)( (float)turns + 1.0f );
    }

    data->y = angle;
    *(int*)&data->z = newTurns;
    data->w = 0.0f;

    if ( motor != 0 )
    {
        hk1dAngularMotorInfo info;
        info.m_solver  = 0;
        info.m_solver2 = 0;

        hk1dAngularVelocityMotorBeginJacobian( &vars.m_angularBasisAw[ axis ], &in, out.m_constraintInternal,
                                               &info );
        info.m_in      = &in;
        info.m_solver  = solverResults + vars.m_currentResult * 8;
        info.m_solver2 = solverResults + 4 + vars.m_currentResult * 8;
        info.m_targetAngle = -( (float)newTurns * 6.2831855f + angle );
        info.m_unknown = 0;

        motor->update( &info, info.m_scratch );
        hk1dAngularVelocityMotorCommitJacobian( &info.m_unknown, &in, angle );
    }
    vars.m_currentResult += 1;
}

// @ 0x0108a180
void hkGenericConstraintData::setLinearMotorW( int*& currentCommand, hkVector4*& currentData,
        hkGenericConstraintDataScheme& scheme, hkGenericConstraintDataParameters& vars,
        const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const
{
    const int dof = *++currentCommand;
    const char* solverResults = in.m_solverResults;

    const hkVector4* data = currentData++;
    const int motorIndex = (int)data->y;

    hkConstraintMotor* motor = (hkConstraintMotor*)scheme.m_motors.m_data[ motorIndex ];

    hk1dLinearMotorInfo info;
    info.m_dofW = vars.m_linearBasisW[ dof ];

    const float fVar4 = info.m_dofW.x * ( vars.m_pivotAw.x - vars.m_pivotBw.x );
    const float fVar6 = info.m_dofW.y * ( vars.m_pivotAw.y - vars.m_pivotBw.y );
    const float fVar5 = info.m_dofW.z * ( vars.m_pivotAw.z - vars.m_pivotBw.z );

    if ( motor != 0 )
    {
        info.m_solver  = 0;
        info.m_solver2 = 0;

        hk1dLinearVelocityMotorBeginJacobian( &info.m_dofW, &vars.m_pivotBw, &in, out.m_constraintInternal,
                                              &info.m_constraintInternal );
        info.m_targetVelocity = -( fVar4 + ( fVar6 + fVar5 ) );
        info.m_solver  = solverResults + vars.m_currentResult * 8;
        info.m_solver2 = solverResults + 4 + vars.m_currentResult * 8;
        info.m_unknown = 0;
        info.m_in      = &in;

        motor->update( &info.m_constraintInternal, info.m_scratch );
        hk1dLinearVelocityMotorCommitJacobian( &info.m_unknown, &in, &out );
    }
    vars.m_currentResult += 1;
}

// @ 0x0108a2b0
void hkGenericConstraintData::setAngularFrictionW( int*& currentCommand, hkVector4*& currentData,
        const hkGenericConstraintDataScheme& scheme, hkGenericConstraintDataParameters& vars,
        const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const
{
    const int axis = *++currentCommand;

    hk1dAngularFrictionInfo info;
    info.m_solver     = in.m_solverResults;
    info.m_axis       = &vars.m_angularBasisAw[ axis ];
    info.m_maxImpulse = currentData++->x;
    info.m_solver     = info.m_solver + vars.m_currentResult * 8;
    info.m_useVelocity = 1;

    hk1dAngularFrictionBuildJacobian( &info, &in, &out );
    vars.m_currentResult += 1;
}

// @ 0x0108a330
void hkGenericConstraintData::setLinearFrictionW( int*& currentCommand, hkVector4*& currentData,
        const hkGenericConstraintDataScheme& scheme, hkGenericConstraintDataParameters& vars,
        const hkConstraintQueryIn& in, hkConstraintQueryOut& out ) const
{
    const int dof = *++currentCommand;

    hk1dLinearFrictionInfo info;
    info.m_solver     = in.m_solverResults;
    info.m_deltaPivot.x = vars.m_pivotAw.x - vars.m_pivotBw.x;
    info.m_dofW = vars.m_linearBasisW[ dof ];
    info.m_deltaPivot.y = vars.m_pivotAw.y - vars.m_pivotBw.y;
    info.m_deltaPivot.z = vars.m_pivotAw.z - vars.m_pivotBw.z;
    info.m_deltaPivot.w = vars.m_pivotAw.w - vars.m_pivotBw.w;
    info.m_maxImpulse = currentData++->x;
    info.m_solver     = info.m_solver + vars.m_currentResult * 8;
    hk1dLinearFrictionBuildJacobian( &info, &in, &out );
    vars.m_currentResult += 1;
}
