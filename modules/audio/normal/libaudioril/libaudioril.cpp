#define LOG_TAG "wrap_AudioRil"

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <utils/Log.h>
#include <utils/String8.h>

#include <libaudio-ril.h>

#include "libaudioril.h"

extern "C"
HAudioRil CreateAudioRil(void) {
    android::SecRil *client = NULL;

    client = new android::SecRil();
    if (client == NULL)
        ALOGE("load audio ril fail");

    return (HAudioRil)client;
}

extern "C"
int DestroyAudioRil(HAudioRil client) {
    int ret = 0;

    if (client == NULL)
        return ret;

    ret = ((android::SecRil *)client)->close();
    if (ret < 0)
        ALOGE("audio ril close failed.");

    delete client;
    return ret;
}

extern "C"
int AudioRilsetVoicePath(HAudioRil client, int mode, int path) {
    if (client == NULL)
        return 0;

    return ((android::SecRil *)client)->setVoicePath(mode, path);
}

extern "C"
int AudioRilsetVoiceVolume(HAudioRil client, int path, float volume) {
    if (client == NULL)
        return 0;

    return ((android::SecRil *)client)->setVoiceVolume(path, volume*5);
}

extern "C"
int AudioRilsetTxMute(HAudioRil client, bool value) {
    if (client == NULL)
        return 0;

    return ((android::SecRil *)client)->setTxMute(value);
}

extern "C"
int AudioRilsetRxMute(HAudioRil client, bool value) {
    if (client == NULL)
        return 0;

    return ((android::SecRil *)client)->setRxMute(value);
}

extern "C"
void AudioRilsetExtraVolume(HAudioRil client, bool value) {
    if (client == NULL)
        return;

    ((android::SecRil *)client)->setExtraVolume(value);
}

extern "C"
void AudioRilsetScoSolution(HAudioRil client, bool value, int port) {
    if (client == NULL)
        return;

    ((android::SecRil *)client)->setScoSolution(value, port);
}

extern "C"
void AudioRilsetLoopback(HAudioRil client, int mode, int route, int flag) {
    if (client == NULL)
        return;

    ((android::SecRil *)client)->setLoopback(mode, route, flag);
}

extern "C"
void AudioRilsetRealCallStatus(HAudioRil client, bool value) {
    if (client == NULL)
        return;

    ((android::SecRil *)client)->setRealCallStatus(value);
}

