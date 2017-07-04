/*
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef ANDROID_LIBAUDIORIL_H
#define ANDROID_LIBAUDIORIL_H

#include <stdbool.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Type definitions
//---------------------------------------------------------------------------

/**
 * Two mic Solution control
 * Two MIC Solution Device
 */
typedef enum __TwoMicSolDevice {
    AUDIENCE,
    FORTEMEDIA
} TwoMicSolDevice;


struct RilClient {
    void *prv;
};
typedef struct RilClient * HRilClient;


struct AudioRil;
typedef struct AudioRil * HAudioRil;


typedef int (*RilOnMessage)(HRilClient handle, const void *data, size_t datalen);


//---------------------------------------------------------------------------
// Client APIs
//---------------------------------------------------------------------------

HAudioRil CreateAudioRil(void);

int DestroyAudioRil(HAudioRil client);

int AudioRilsetVoicePath(HAudioRil client, int mode, int path);
int AudioRilsetVoiceVolume(HAudioRil client, int path, float volume);
int AudioRilsetTxMute(HAudioRil client, bool value);
int AudioRilsetRxMute(HAudioRil client, bool value);

void AudioRilsetExtraVolume(HAudioRil client, bool value);
void AudioRilsetScoSolution(HAudioRil client, bool value, int port);
void AudioRilsetLoopback(HAudioRil client, int mode, int route, int flag);
void AudioRilsetRealCallStatus(HAudioRil client, bool value);


#ifdef __cplusplus
};
#endif

#endif // ANDROID_LIBAUDIORIL_H
