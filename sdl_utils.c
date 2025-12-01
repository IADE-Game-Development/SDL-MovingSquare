#include "sdl_utils.h"
#include <stdio.h>

static SDL_AudioDeviceID audio_device = 0;

int sdl_initialize_audio() {
    audio_device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
    if (audio_device == 0)
    {
        SDL_Log("Couldn't open audio device: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    return audio_device;
}

bool init_sound(const char *fname, Sound *sound)
{
    bool retval = false;
    SDL_AudioSpec spec;
    char *wav_path = NULL;

    /* Load the .wav files from wherever the app is being run from. */
    SDL_asprintf(&wav_path, "%s%s", SDL_GetBasePath(), fname); /* allocate a string of the full file path */
    if (!SDL_LoadWAV(wav_path, &spec, &sound->wav_data, &sound->wav_data_len))
    {
        SDL_Log("Couldn't load .wav file: %s", SDL_GetError());
        return false;
    }

    /* Create an audio stream. Set the source format to the wav's format (what
       we'll input), leave the dest format NULL here (it'll change to what the
       device wants once we bind it). */
    sound->stream = SDL_CreateAudioStream(&spec, NULL);
    if (!sound->stream)
    {
        SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
    }
    else if (!SDL_BindAudioStream(audio_device, sound->stream))
    { /* once bound, it'll start playing when there is data available! */
        SDL_Log("Failed to bind '%s' stream to device: %s", fname, SDL_GetError());
    }
    else
    {
        retval = true; /* success! */
    }

    SDL_free(wav_path); /* done with this string. */
    return retval;
}

void playSound(Sound *sound)
{
    SDL_ClearAudioStream(sound->stream);
    if (SDL_GetAudioStreamQueued(sound->stream) < ((int)sound->wav_data_len))
        SDL_PutAudioStreamData(sound->stream, sound->wav_data, (int)sound->wav_data_len);
}

SDL_Texture *sdl_load_texture(SDL_Renderer *renderer, const char *file_path)
{
    if (!renderer) {
        SDL_Log("sdl_load_texture: renderer is NULL");
        return NULL;
    }

    char *full_path = NULL;
    if (SDL_asprintf(&full_path, "%s%s", SDL_GetBasePath(), file_path) < 0) {
        SDL_Log("sdl_load_texture: SDL_asprintf failed");
        return NULL;
    }

    SDL_Texture *tex = IMG_LoadTexture(renderer, full_path);
    SDL_free(full_path);

    if (!tex) {
        SDL_Log("IMG_LoadTexture('%s') error: %s", file_path, SDL_GetError());
        return NULL;
    }

    return tex;
}