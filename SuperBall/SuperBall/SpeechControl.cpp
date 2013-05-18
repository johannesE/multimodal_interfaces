/* 
#include "SpeechControl.h"
#include "stdafx.h"
#include "resource.h"
#include <iostream>
#include <stdlib.h>

#define INITGUID
#include <guiddef.h>

LPCWSTR SpeechControl::GrammarFileName = L"SpeechBasics-D2D.grxml";

// This is the class ID we expect for the Microsoft Speech recognizer.
// Other values indicate that we're using a version of sapi.h that is
// incompatible with this sample.
DEFINE_GUID(CLSID_ExpectedRecognizer, 0x495648e7, 0xf7ab, 0x4267, 0x8e, 0x0f, 0xca, 0xfb, 0x7a, 0x33, 0xc1, 0x60);



SpeechControl::SpeechControl() : 
//	m_pD2DFactory(NULL),
//  m_pTurtleController(NULL),
    m_pNuiSensor(NULL),
    m_pKinectAudioStream(NULL),
    m_pSpeechStream(NULL),
    m_pSpeechRecognizer(NULL),
    m_pSpeechContext(NULL),
    m_pSpeechGrammar(NULL),
    m_hSpeechEvent(INVALID_HANDLE_VALUE)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if(! SUCCEEDED(hr))
	{
		std::cout << "error. Could not initialize coinitializeEx. \n";
	}
}


SpeechControl::~SpeechControl(void)
{
	if (m_pNuiSensor)
    {
        m_pNuiSensor->NuiShutdown();
    }
}

void Run(){
	printf("Run() is called \n");
		SpeechControl* spct = new SpeechControl();

		MSG       msg = {0};

	    const int eventCount = 1;
		HANDLE hEvents[eventCount];


		spct->DlgProc(WM_INITDIALOG);


	    while (WM_QUIT != msg.message)
		{

        hEvents[0] = spct->m_hSpeechEvent;

        // Check to see if we have either a message (by passing in QS_ALLINPUT)
        // Or a speech event (hEvents)
        DWORD dwEvent = MsgWaitForMultipleObjectsEx(eventCount, hEvents, INFINITE, QS_ALLINPUT, MWMO_INPUTAVAILABLE);

        // Check if this is an event we're waiting on and not a timeout or message
        if (WAIT_OBJECT_0 == dwEvent)
        {
			printf("there has been a speech event \n");
            spct->ProcessSpeech();
        }

        if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {

			printf("something unknown is happening \n");
           // If a dialog message will be taken care of by the dialog proc
            if ((hWndApp != NULL) && IsDialogMessageW(hWndApp, &msg))
            {
                continue;
            }
			

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

}




void start(){


HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    if (SUCCEEDED(hr))
    {
        {
            printf("creating the thread for speechControl \n");
            std::thread t(Run);
			printf("cthread created ... now joining ... \n");
			t.detach();
			printf("speechControl joined \n");
        }

        CoUninitialize();
    }


}


void SpeechControl::ProcessSpeech()
{
	printf("processing speech \n");
    const float ConfidenceThreshold = 0.3f;

    SPEVENT curEvent;
    ULONG fetched = 0;
    HRESULT hr = S_OK;

    m_pSpeechContext->GetEvents(1, &curEvent, &fetched);

    while (fetched > 0)
    {
        switch (curEvent.eEventId)
        {
            case SPEI_RECOGNITION:
                if (SPET_LPARAM_IS_OBJECT == curEvent.elParamType)
                {
                    // this is an ISpRecoResult
                    ISpRecoResult* result = reinterpret_cast<ISpRecoResult*>(curEvent.lParam);
                    SPPHRASE* pPhrase = NULL;
                    
                    hr = result->GetPhrase(&pPhrase);
                    if (SUCCEEDED(hr))
                    {
                        if ((pPhrase->pProperties != NULL) && (pPhrase->pProperties->pFirstChild != NULL))
                        {
                            const SPPHRASEPROPERTY* pSemanticTag = pPhrase->pProperties->pFirstChild;
                            if (pSemanticTag->SREngineConfidence > ConfidenceThreshold)
                            {
								printf("Calling the Speech Action with ");
                                BallAction action = MapSpeechTagToAction(pSemanticTag->pszValue);
								std::cout << action << "\n";
								SuperBall::speechAction(action);
								printf("The speech Action was called \n");
                           
							}
                        }
                        ::CoTaskMemFree(pPhrase);
                    }
                }
                break;
        }

        m_pSpeechContext->GetEvents(1, &curEvent, &fetched);
    }

    return;
}

/// <summary>
/// Handles window messages, passes most to the class instance to handle
/// </summary>
/// <param name="hWnd">window message is for</param>
/// <param name="uMsg">message</param>
/// <param name="wParam">message data</param>
/// <param name="lParam">additional message data</param>
/// <returns>result of message processing</returns>

//LRESULT CALLBACK SpeechControl::MessageRouter(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
LRESULT CALLBACK SpeechControl::MessageRouter(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    SpeechControl* pThis = NULL;
    
    if (WM_INITDIALOG == uMsg)
    {
        pThis = reinterpret_cast<SpeechControl*>(lParam);
        //SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else
    {
        pThis = reinterpret_cast<SpeechControl*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (NULL != pThis)
    {
        return pThis->DlgProc(uMsg);
    }

    return 0;
}


BallAction SpeechControl::MapSpeechTagToAction(LPCWSTR pszSpeechTag)
{
	printf("mapping the tag to an action \n");
    struct SpeechTagToAction
    {
        LPCWSTR pszSpeechTag;
        BallAction action;
    };
    const SpeechTagToAction Map[] =
    { //right side is superball.h
        {L"FORWARD", UP},
        {L"BACKWARD", DOWN},
        {L"LEFT", LEFT},
        {L"RIGHT", RIGHT},
		{L"STOP", STOP}
    };

    BallAction action = NONE;

    for (int i = 0; i < _countof(Map); ++i)
    {
        if (0 == wcscmp(Map[i].pszSpeechTag, pszSpeechTag))
        {
            action = Map[i].action;
            break;
        }
    }

    return action;
}
HRESULT SpeechControl::CreateFirstConnected()
{
	printf("creating the kinect connection \n");
    INuiSensor * pNuiSensor;
    HRESULT hr;

    int iSensorCount = 0;
    hr = NuiGetSensorCount(&iSensorCount);
    if (FAILED(hr))
    {
        return hr;
    }

    // Look at each Kinect sensor
    for (int i = 0; i < iSensorCount; ++i)
    {
        // Create the sensor so we can check status, if we can't create it, move on to the next
        hr = NuiCreateSensorByIndex(i, &pNuiSensor);
        if (FAILED(hr))
        {
            continue;
        }

        // Get the status of the sensor, and if connected, then we can initialize it
        hr = pNuiSensor->NuiStatus();
        if (S_OK == hr)
        {
            m_pNuiSensor = pNuiSensor;
            break;
        }

        // This sensor wasn't OK, so release it since we're not using it
        pNuiSensor->Release();
    }

    if (NULL != m_pNuiSensor)
    {
        // Initialize the Kinect and specify that we'll be using audio signal
        hr = m_pNuiSensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_AUDIO); 
		printf("initializing the kinect \n");
        if (FAILED(hr))
        {

            // Some other application is streaming from the same Kinect sensor
            SafeRelease(m_pNuiSensor);
        }
    }

    if (NULL == m_pNuiSensor || FAILED(hr))
    {
        SetStatusMessage(L"No ready Kinect found!");
		printf("no ready kinect found \n");
        return E_FAIL;
    }

    hr = InitializeAudioStream();
    if (FAILED(hr))
    {
        SetStatusMessage(L"Could not initialize audio stream.");
		printf("could not initialize audio stream \n");
        return hr;
    }

    hr = CreateSpeechRecognizer();
    if (FAILED(hr))
    {
        SetStatusMessage(L"Could not create speech recognizer. Please ensure that Microsoft Speech SDK and other sample requirements are installed.");
        printf("recognizer not created \n");
		return hr;
    }

    hr = LoadSpeechGrammar();
    if (FAILED(hr))
    {
        SetStatusMessage(L"Could not load speech grammar. Please ensure that grammar configuration file was properly deployed.");
        printf("grammar not found \n");
		return hr;
    }

    hr = StartSpeechRecognition();
    if (FAILED(hr))
    {
        SetStatusMessage(L"Could not start recognizing speech.");
		printf("could not start recognizing speech \n");
        return hr;
    }

    return hr;
}

/// <summary>
/// Handle windows messages for the class instance
/// </summary>
/// <param name="hWnd">window message is for</param>
/// <param name="uMsg">message</param>
/// <param name="wParam">message data</param>
/// <param name="lParam">additional message data</param>
/// <returns>result of message processing</returns>

HRESULT SpeechControl::InitializeAudioStream()
{
    INuiAudioBeam*      pNuiAudioSource = NULL;
    IMediaObject*       pDMO = NULL;
    IPropertyStore*     pPropertyStore = NULL;
    IStream*            pStream = NULL;

    // Get the audio source
    HRESULT hr = m_pNuiSensor->NuiGetAudioSource(&pNuiAudioSource);
    if (SUCCEEDED(hr))
    {
        hr = pNuiAudioSource->QueryInterface(IID_IMediaObject, (void**)&pDMO);

        if (SUCCEEDED(hr))
        {
            hr = pNuiAudioSource->QueryInterface(IID_IPropertyStore, (void**)&pPropertyStore);
    
            // Set AEC-MicArray DMO system mode. This must be set for the DMO to work properly.
            // Possible values are:
            //   SINGLE_CHANNEL_AEC = 0
            //   OPTIBEAM_ARRAY_ONLY = 2
            //   OPTIBEAM_ARRAY_AND_AEC = 4
            //   SINGLE_CHANNEL_NSAGC = 5
            PROPVARIANT pvSysMode;
            PropVariantInit(&pvSysMode);
            pvSysMode.vt = VT_I4;
            pvSysMode.lVal = (LONG)(2); // Use OPTIBEAM_ARRAY_ONLY setting. Set OPTIBEAM_ARRAY_AND_AEC instead if you expect to have sound playing from speakers.
            pPropertyStore->SetValue(MFPKEY_WMAAECMA_SYSTEM_MODE, pvSysMode);
            PropVariantClear(&pvSysMode);

            // Set DMO output format
            WAVEFORMATEX wfxOut = {AudioFormat, AudioChannels, AudioSamplesPerSecond, AudioAverageBytesPerSecond, AudioBlockAlign, AudioBitsPerSample, 0};
            DMO_MEDIA_TYPE mt = {0};
            MoInitMediaType(&mt, sizeof(WAVEFORMATEX));
    
            mt.majortype = MEDIATYPE_Audio;
            mt.subtype = MEDIASUBTYPE_PCM;
            mt.lSampleSize = 0;
            mt.bFixedSizeSamples = TRUE;
            mt.bTemporalCompression = FALSE;
            mt.formattype = FORMAT_WaveFormatEx;	
            memcpy(mt.pbFormat, &wfxOut, sizeof(WAVEFORMATEX));
    
            hr = pDMO->SetOutputType(0, &mt, 0);

            if (SUCCEEDED(hr))
            {
                m_pKinectAudioStream = new KinectAudioStream(pDMO);

                hr = m_pKinectAudioStream->QueryInterface(IID_IStream, (void**)&pStream);

                if (SUCCEEDED(hr))
                {
                    hr = CoCreateInstance(CLSID_SpStream, NULL, CLSCTX_INPROC_SERVER, __uuidof(ISpStream), (void**)&m_pSpeechStream);

                    if (SUCCEEDED(hr))
                    {
                        hr = m_pSpeechStream->SetBaseStream(pStream, SPDFID_WaveFormatEx, &wfxOut);
                    }
                }
            }

            MoFreeMediaType(&mt);
        }
    }

    SafeRelease(pStream);
    SafeRelease(pPropertyStore);
    SafeRelease(pDMO);
    SafeRelease(pNuiAudioSource);

    return hr;
}

/// <summary>
/// Create speech recognizer that will read Kinect audio stream data.
/// </summary>
/// <returns>
/// <para>S_OK on success, otherwise failure code.</para>
/// </returns>
HRESULT SpeechControl::CreateSpeechRecognizer()
{
    ISpObjectToken *pEngineToken = NULL;
    std::cout << "CreateSpeechRecognizer";
    HRESULT hr = CoCreateInstance(CLSID_SpInprocRecognizer, NULL, CLSCTX_INPROC_SERVER, __uuidof(ISpRecognizer), (void**)&m_pSpeechRecognizer);
	 std::cout << "CreateSpeechRecognizer 2";
    if (SUCCEEDED(hr))
    {
		 std::cout << "CreateSpeechRecognizer SUCCEEDED(hr)";
        m_pSpeechRecognizer->SetInput(m_pSpeechStream, FALSE);
		std::cout << "CreateSpeechRecognizer SetInput";
        hr = SpFindBestToken(SPCAT_RECOGNIZERS,L"Language=409;Kinect=True",NULL,&pEngineToken);

        if (SUCCEEDED(hr))
        {
			std::cout << "CreateSpeechRecognizer SUCCEEDED(hr) twice";
            m_pSpeechRecognizer->SetRecognizer(pEngineToken);
			std::cout << "CreateSpeechRecognizer SetRecognizer";
            hr = m_pSpeechRecognizer->CreateRecoContext(&m_pSpeechContext);
			std::cout << "CreateSpeechRecognizer CreateRecoContext";
            // For long recognition sessions (a few hours or more), it may be beneficial to turn off adaptation of the acoustic model. 
            // This will prevent recognition accuracy from degrading over time.
            //if (SUCCEEDED(hr))
            //{
            //    hr = m_pSpeechRecognizer->SetPropertyNum(L"AdaptationOn", 0);                
            //}
        }
    }

    SafeRelease(pEngineToken);

    return hr;
}

/// <summary>
/// Load speech recognition grammar into recognizer.
/// </summary>
/// <returns>
/// <para>S_OK on success, otherwise failure code.</para>
/// </returns>
HRESULT SpeechControl::LoadSpeechGrammar()
{
    HRESULT hr = m_pSpeechContext->CreateGrammar(1, &m_pSpeechGrammar);

    if (SUCCEEDED(hr))
    {
        // Populate recognition grammar from file
        hr = m_pSpeechGrammar->LoadCmdFromFile(GrammarFileName, SPLO_STATIC);
    }

    return hr;
}

/// <summary>
/// Start recognizing speech asynchronously.
/// </summary>
/// <returns>
/// <para>S_OK on success, otherwise failure code.</para>
/// </returns>
HRESULT SpeechControl::StartSpeechRecognition()
{
	printf("speech recognition started");
    HRESULT hr = m_pKinectAudioStream->StartCapture();

    if (SUCCEEDED(hr))
    {
        // Specify that all top level rules in grammar are now active
        m_pSpeechGrammar->SetRuleState(NULL, NULL, SPRS_ACTIVE);

        // Specify that engine should always be reading audio
        m_pSpeechRecognizer->SetRecoState(SPRST_ACTIVE_ALWAYS);

        // Specify that we're only interested in receiving recognition events
        m_pSpeechContext->SetInterest(SPFEI(SPEI_RECOGNITION), SPFEI(SPEI_RECOGNITION));

        // Ensure that engine is recognizing speech and not in paused state
        hr = m_pSpeechContext->Resume(0);
        if (SUCCEEDED(hr))
        {
            m_hSpeechEvent = m_pSpeechContext->GetNotifyEventHandle();
        }
    }
        
    return hr;
}

void SpeechControl::SetStatusMessage(const WCHAR* szMessage)
{
	printf("STATUS MESSAGE: ");
	std::cout << szMessage << "\n";
    //SendDlgItemMessageW IDC_STATUS, WM_SETTEXT, 0, (LPARAM)szMessage);
} 


LRESULT CALLBACK SpeechControl::DlgProc( UINT message)
{
    LRESULT result = FALSE;

    switch (message)
    {
        case WM_INITDIALOG:
        {
		

            // Look for a connected Kinect, and create it if found
            HRESULT hr = CreateFirstConnected();
            if (FAILED(hr))
            {
				printf("Could not connect any kinect");
                break;
            }

            SetStatusMessage(L"Say: \"Forward\", \"Back\", \"Turn Left\" or \"Turn Right\"");


            result = FALSE;
            break;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
//            BeginPaint(hWnd, &ps);

			//here it would draw something
            //m_pTurtleController->Draw();
			printf("it would draw the turtle now \n");

//            EndPaint(hWnd, &ps);
            result = TRUE;
            break;
        }

        // If the titlebar X is clicked, destroy app
        case WM_CLOSE:
			printf("closing the audio stream and the speech recognizer \n");
            if (NULL != m_pKinectAudioStream)
            {
                m_pKinectAudioStream->StopCapture();
            }

            if (NULL != m_pSpeechRecognizer)
            {
                m_pSpeechRecognizer->SetRecoState(SPRST_INACTIVE);
            }

//            DestroyWindow(hWnd);
            result = TRUE;
            break;

        case WM_DESTROY:
            // Quit the main message pump
            PostQuitMessage(0);
            result = TRUE;
            break;
    }

    return result;
}



*/