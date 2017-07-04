/*
 * Copyright (C) 2008 The Android Open Source Project
 * Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_LIBAUDIO_RIL_H
#define ANDROID_LIBAUDIO_RIL_H

#include <stdlib.h>
#include <stdint.h>

#include <utils/String8.h>
#include "../libaudioril.h"


namespace android {

// ---------------------------------------------------------------------------

class SecRil
{
public:
    SecRil();
    ~SecRil();

    int init();
    int init_dualRIL();
    int close();

    int checkConnection();
    int checkMultiSim();
    int getDeviceType(int route, int flag);
    int isLoopbackStart();

    int registerCallback(HRilClient client, uint32_t id, RilOnMessage handler);
    int registerCallbackSlot2(HRilClient client, uint32_t id, RilOnMessage handler);

    void rilDump(int fd);

    int setAudioMode(int mode, int state);
    int setCallClockSync(const android::String8 *mode);

    void setCallFowardingMode(bool value);
    void setCoverState(bool value);
    void setCurrentModem(int value);

    int setDhaSolution(const android::String8 *parameters);
    int setDualMic(TwoMicSolDevice device);

    void setEmergencyMode(bool value);
    void setExtraVolume(bool value);
    void setHACMode(bool value);

    int setLoopback(int mode, int route, int flag);

    void setRealCallStatus(bool value);
    int setRxMute(bool value);
    void setScoSolution(bool value, int port);
    int setTxMute(bool value);
    int setVoicePath(int mode, int path);
    int setVoiceSolution();
    int setVoiceVolume(int path, float volume);

private:
    char unk[0x40];
};
// ---------------------------------------------------------------------------
}; // namespace android

#endif // ANDROID_LIBAUDIO_RIL_H
