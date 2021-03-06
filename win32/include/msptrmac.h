#ifndef _MSPTRMAC_H_
#define _MSPTRMAC_H_

#define WAVEIN_NAME L"WaveIn Terminal"

#ifdef __cplusplus

class CAudioCaptureTerminal : public IDispatchImpl<ITBasicAudioTerminal,&IID_ITBasicAudioTerminal,&LIBID_TAPI3Lib>,public IDispatchImpl<ITStaticAudioTerminal,&IID_ITStaticAudioTerminal,&LIBID_TAPI3Lib>,public CSingleFilterStaticTerminal,public CMSPObjectSafetyImpl
{
  BEGIN_COM_MAP(CAudioCaptureTerminal)
    COM_INTERFACE_ENTRY(IObjectSafety)
    COM_INTERFACE_ENTRY(ITBasicAudioTerminal)
    COM_INTERFACE_ENTRY(ITStaticAudioTerminal)
    COM_INTERFACE_ENTRY_CHAIN(CSingleFilterStaticTerminal)
  END_COM_MAP()
  DECLARE_VQI()
  DECLARE_LOG_ADDREF_RELEASE(CAudioCaptureTerminal)
public:
  CAudioCaptureTerminal();
  virtual ~CAudioCaptureTerminal();
  static HRESULT CreateTerminal(CComPtr<IMoniker> pMoniker,MSP_HANDLE htAddress,ITTerminal **ppTerm);
  HRESULT FindTerminalPin();
public:
  STDMETHOD(get_Balance)(long *pVal);
  STDMETHOD(put_Balance)(long newVal);
  STDMETHOD(get_Volume) (long *pVal);
  STDMETHOD(put_Volume) (long newVal);
public:
  STDMETHOD(get_WaveId) (long *plWaveId);
  STDMETHODIMP CompleteConnectTerminal(void);
  STDMETHODIMP DisconnectTerminal(IGraphBuilder *pGraph,DWORD dwReserved);
  virtual HRESULT AddFiltersToGraph();
  virtual DWORD GetSupportedMediaTypes(void) { return (DWORD) TAPIMEDIATYPE_AUDIO; }
  HRESULT CreateFilters();
  inline HRESULT CreateFiltersIfRequired();
private:
  bool m_bResourceReserved;
  CComPtr<IAMAudioInputMixer> m_pIAMAudioInputMixer;
};

inline HRESULT CAudioCaptureTerminal::CreateFiltersIfRequired() {
  if(!m_pIFilter) return CreateFilters();
  return S_OK;
}

#endif /* __cplusplus */

#endif
