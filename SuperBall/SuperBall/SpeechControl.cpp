#include "SpeechControl.h"
#include "stdafx.h"
#include "resource.h"

LPCWSTR SpeechControl::GrammarFileName = L"SpeechBasics-D2D.grxml";

// This is the class ID we expect for the Microsoft Speech recognizer.
// Other values indicate that we're using a version of sapi.h that is
// incompatible with this sample.
DEFINE_GUID(CLSID_ExpectedRecognizer, 0x495648e7, 0xf7ab, 0x4267, 0x8e, 0x0f, 0xca, 0xfb, 0x7a, 0x33, 0xc1, 0x60);



SpeechControl::SpeechControl(void) : 
//	m_pD2DFactory(NULL),
//    m_pTurtleController(NULL),
    m_pNuiSensor(NULL),
    m_pKinectAudioStream(NULL),
    m_pSpeechStream(NULL),
    m_pSpeechRecognizer(NULL),
    m_pSpeechContext(NULL),
    m_pSpeechGrammar(NULL),
    m_hSpeechEvent(INVALID_HANDLE_VALUE)
{
}


SpeechControl::~SpeechControl(void)
{
	if (m_pNuiSensor)
    {
        m_pNuiSensor->NuiShutdown();
    }
}


void start(){


HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    if (SUCCEEDED(hr))
    {
        {
            SpeechControl application;
            application.Run();
        }

        CoUninitialize();
    }


}

void SpeechControl::Run(){
	MSG       msg = {0};

	    const int eventCount = 1;
		HANDLE hEvents[eventCount];

	    while (WM_QUIT != msg.message)
    {
        hEvents[0] = m_hSpeechEvent;

        // Check to see if we have either a message (by passing in QS_ALLINPUT)
        // Or a speech event (hEvents)
        DWORD dwEvent = MsgWaitForMultipleObjectsEx(eventCount, hEvents, INFINITE, QS_ALLINPUT, MWMO_INPUTAVAILABLE);

        // Check if this is an event we're waiting on and not a timeout or message
        if (WAIT_OBJECT_0 == dwEvent)
        {
            ProcessSpeech();
        }

        if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
           /* // If a dialog message will be taken care of by the dialog proc
            if ((hWndApp != NULL) && IsDialogMessageW(hWndApp, &msg))
            {
                continue;
            }
			*/

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

}

void SpeechControl::ProcessSpeech()
{
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
                                BallAction action = MapSpeechTagToAction(pSemanticTag->pszValue);
								SuperBall::speechAction(action);
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

BallAction SpeechControl::MapSpeechTagToAction(LPCWSTR pszSpeechTag)
{
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