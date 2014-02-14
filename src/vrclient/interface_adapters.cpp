//========= Copyright Valve Corporation ============//
#include "hmdlatest.h"
#include "steamvr.h"

using namespace vr;

class InterfaceRegistrationBase
{
public:
	InterfaceRegistrationBase( const char *pchInterfaceName )
	{
		m_sName = pchInterfaceName;
		m_pNext = s_pFirst;
		s_pFirst = this;
	}
	virtual ~InterfaceRegistrationBase() {}

	static InterfaceRegistrationBase *Find( const char *pchInterfaceName )
	{
		for( InterfaceRegistrationBase *pCurr = s_pFirst; pCurr != NULL; pCurr = pCurr->m_pNext )
		{
			if( pCurr->m_sName == pchInterfaceName )
			{
				return pCurr;
			}
		}
		return NULL;
	}

	virtual void *GetInterface( IHmd *pHmdLatest ) = 0;

private:
	static InterfaceRegistrationBase *s_pFirst;
	InterfaceRegistrationBase *m_pNext;
	std::string m_sName;
};

InterfaceRegistrationBase *InterfaceRegistrationBase::s_pFirst = NULL;

void *FindInterface( const char *pchInterfaceName, vr::IHmd *pHmdLatest )
{
	InterfaceRegistrationBase *pReg = InterfaceRegistrationBase::Find( pchInterfaceName );
	if( !pReg )
		return NULL;

	return pReg->GetInterface( pHmdLatest );
}

bool HasInterfaceAdapter( const char *pchInterfaceName )
{
	return InterfaceRegistrationBase::Find( pchInterfaceName ) != NULL;
}


template< typename t >
class HmdInterfaceRegistration : public InterfaceRegistrationBase
{
public:
	HmdInterfaceRegistration( const char *pchInterfaceName ) 
		: InterfaceRegistrationBase( pchInterfaceName )
	{

	}

	virtual void *GetInterface( IHmd *pHmdLatest ) OVERRIDE
	{
		m_Interface.m_pHmdLatest = pHmdLatest;
		return &m_Interface;
	}

private:
	t m_Interface;
};

class CHmd_001
{
public:
	virtual bool GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) { m_pHmdLatest->GetWindowBounds( pnX, pnY, pnWidth, pnHeight ); return true; }
	virtual void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight ) { m_pHmdLatest->GetRecommendedRenderTargetSize( pnWidth, pnHeight ); }
	virtual void GetEyeOutputViewport( Hmd_Eye eEye, GraphicsAPIConvention eAPIType, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) { m_pHmdLatest->GetEyeOutputViewport( eEye, pnX, pnY, pnWidth, pnHeight ); }
	virtual HmdMatrix44_t GetProjectionMatrix( Hmd_Eye eEye, float fNearZ, float fFarZ, GraphicsAPIConvention eProjType ) { return m_pHmdLatest->GetProjectionMatrix( eEye, fNearZ, fFarZ, eProjType ); }
	virtual void GetProjectionRaw( Hmd_Eye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom ) { m_pHmdLatest->GetProjectionRaw( eEye, pfLeft, pfRight, pfTop, pfBottom ); }
	virtual DistortionCoordinates_t ComputeDistortion( Hmd_Eye eEye, float fU, float fV ) { return m_pHmdLatest->ComputeDistortion( eEye, fU, fV ); }
	virtual HmdMatrix44_t GetEyeMatrix( Hmd_Eye eEye ) { return m_pHmdLatest->GetEyeMatrix( eEye ); }
	virtual bool GetViewMatrix( float fSecondsFromNow, HmdMatrix44_t *pMatLeftView, HmdMatrix44_t *pMatRightView, HmdTrackingResult *peResult ) { return m_pHmdLatest->GetViewMatrix( fSecondsFromNow, pMatLeftView, pMatRightView, peResult ); }
	virtual int32_t GetD3D9AdapterIndex() { return m_pHmdLatest->GetD3D9AdapterIndex(); }
	virtual bool GetWorldFromHeadPose( float fPredictedSecondsFromNow, HmdMatrix34_t *pmPose, HmdTrackingResult *peResult ) { return m_pHmdLatest->GetWorldFromHeadPose( fPredictedSecondsFromNow, pmPose, peResult ); }
	virtual bool WillDriftInYaw() { return m_pHmdLatest->WillDriftInYaw(); }
	virtual uint32_t GetDriverId( char *pchBuffer, uint32_t unBufferLen ) { return m_pHmdLatest->GetDriverId( pchBuffer, unBufferLen ); }
	virtual uint32_t GetDisplayId( char *pchBuffer, uint32_t unBufferLen ) { return m_pHmdLatest->GetDisplayId( pchBuffer, unBufferLen ); }

	IHmd *m_pHmdLatest;
};

static HmdInterfaceRegistration<CHmd_001> hmd001( "IHmd_001" );

class CHmd_002
{
public:
	virtual bool GetWindowBounds( int32_t *pnX, int32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) { m_pHmdLatest->GetWindowBounds( pnX, pnY, pnWidth, pnHeight ); return true; }
	virtual void GetRecommendedRenderTargetSize( uint32_t *pnWidth, uint32_t *pnHeight ) { m_pHmdLatest->GetRecommendedRenderTargetSize( pnWidth, pnHeight ); }
	virtual void GetEyeOutputViewport( Hmd_Eye eEye, GraphicsAPIConvention eAPIType, uint32_t *pnX, uint32_t *pnY, uint32_t *pnWidth, uint32_t *pnHeight ) { m_pHmdLatest->GetEyeOutputViewport( eEye, pnX, pnY, pnWidth, pnHeight ); }
	virtual HmdMatrix44_t GetProjectionMatrix( Hmd_Eye eEye, float fNearZ, float fFarZ, GraphicsAPIConvention eProjType ) { return m_pHmdLatest->GetProjectionMatrix( eEye, fNearZ, fFarZ, eProjType ); }
	virtual void GetProjectionRaw( Hmd_Eye eEye, float *pfLeft, float *pfRight, float *pfTop, float *pfBottom ) { m_pHmdLatest->GetProjectionRaw( eEye, pfLeft, pfRight, pfTop, pfBottom ); }
	virtual DistortionCoordinates_t ComputeDistortion( Hmd_Eye eEye, float fU, float fV ) { return m_pHmdLatest->ComputeDistortion( eEye, fU, fV ); }
	virtual HmdMatrix44_t GetEyeMatrix( Hmd_Eye eEye ) { return m_pHmdLatest->GetEyeMatrix( eEye ); }
	virtual bool GetViewMatrix( float fSecondsFromNow, HmdMatrix44_t *pMatLeftView, HmdMatrix44_t *pMatRightView, HmdTrackingResult *peResult ) { return m_pHmdLatest->GetViewMatrix( fSecondsFromNow, pMatLeftView, pMatRightView, peResult ); }
	virtual int32_t GetD3D9AdapterIndex()  { return m_pHmdLatest->GetD3D9AdapterIndex(); }
	virtual bool GetWorldFromHeadPose( float fPredictedSecondsFromNow, HmdMatrix34_t *pmPose, HmdTrackingResult *peResult ) { return m_pHmdLatest->GetWorldFromHeadPose( fPredictedSecondsFromNow, pmPose, peResult ); }
	virtual bool GetLastWorldFromHeadPose( HmdMatrix34_t *pmPose ) { return m_pHmdLatest->GetLastWorldFromHeadPose( pmPose ); }
	virtual bool WillDriftInYaw() { return m_pHmdLatest->WillDriftInYaw(); }
	virtual void ZeroTracker() { m_pHmdLatest->ZeroTracker(); }
	virtual uint32_t GetDriverId( char *pchBuffer, uint32_t unBufferLen ) { return m_pHmdLatest->GetDriverId( pchBuffer, unBufferLen ); }
	virtual uint32_t GetDisplayId( char *pchBuffer, uint32_t unBufferLen )  { return m_pHmdLatest->GetDisplayId( pchBuffer, unBufferLen ); }

	IHmd *m_pHmdLatest;
};

static HmdInterfaceRegistration<CHmd_002> hmd002( "IHmd_002" );
