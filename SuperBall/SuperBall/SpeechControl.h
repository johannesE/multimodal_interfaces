#pragma once

#include "SuperBall.h"
#include "KinectAudioStream.h"
#include "resource.h"
#include "SuperBall.h" //for the turtle action enum

// For configuring DMO properties
#include <wmcodecdsp.h>

// For FORMAT_WaveFormatEx and such
#include <uuids.h>

// For Kinect SDK APIs
#include <NuiApi.h>

// For speech APIs
// NOTE: To ensure that application compiles and links against correct SAPI versions (from Microsoft Speech
//       SDK), VC++ include and library paths should be configured to list appropriate paths within Microsoft
//       Speech SDK installation directory before listing the default system include and library directories,
//       which might contain a version of SAPI that is not appropriate for use together with Kinect sensor.
#include <sapi.h>
#include <sphelper.h>

class SpeechControl
{
public:
	SpeechControl(void);
	~SpeechControl(void);
	void SpeechControl::Run();

private:
	static LPCWSTR          GrammarFileName;

	// Current Kinect sensor
    INuiSensor*             m_pNuiSensor;

    // Audio stream captured from Kinect.
    KinectAudioStream*      m_pKinectAudioStream;

    // Stream given to speech recognition engine
    ISpStream*              m_pSpeechStream;

    // Speech recognizer
    ISpRecognizer*          m_pSpeechRecognizer;

    // Speech recognizer context
    ISpRecoContext*         m_pSpeechContext;

    // Speech grammar
    ISpRecoGrammar*         m_pSpeechGrammar;

    // Event triggered when we detect speech recognition
    HANDLE                  m_hSpeechEvent;

	/// <summary>
    /// Create the first connected Kinect found.
    /// </summary>
    /// <returns>S_OK on success, otherwise failure code.</returns>
    HRESULT                 CreateFirstConnected();

    /// <summary>
    /// Initialize Kinect audio stream object.
    /// </summary>
    /// <returns>S_OK on success, otherwise failure code.</returns>
    HRESULT                 InitializeAudioStream();

    /// <summary>
    /// Create speech recognizer that will read Kinect audio stream data.
    /// </summary>
    /// <returns>
    /// <para>S_OK on success, otherwise failure code.</para>
    /// </returns>
    HRESULT                 CreateSpeechRecognizer();

    /// <summary>
    /// Load speech recognition grammar into recognizer.
    /// </summary>
    /// <returns>
    /// <para>S_OK on success, otherwise failure code.</para>
    /// </returns>
    HRESULT                 LoadSpeechGrammar();

    /// <summary>
    /// Start recognizing speech asynchronously.
    /// </summary>
    /// <returns>
    /// <para>S_OK on success, otherwise failure code.</para>
    /// </returns>
    HRESULT                 StartSpeechRecognition();

    /// <summary>
    /// Process recently triggered speech recognition events.
    /// </summary>
    void                    ProcessSpeech();

    /// <summary>
    /// Maps a specified speech semantic tag to the corresponding action to be performed on turtle.
    /// </summary>
    /// <returns>
    /// Action that matches <paramref name="pszSpeechTag"/>, or TurtleActionNone if no matches were found.
    /// </returns>
    BallAction            MapSpeechTagToAction(LPCWSTR pszSpeechTag);

    /// <summary>
    /// Set the status bar message.
    /// </summary>
    /// <param name="szMessage">message to display.</param>
    void                    SetStatusMessage(const WCHAR* szMessage);
};

