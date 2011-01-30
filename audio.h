#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "resources.h"

class Audio
{
public:
enum {
    SFX_SHOT,
    SFX_DEATH,
    SFX_COLLECT,
    SFX_FLAME,
    SFX_LASER,
};

enum {
    MUSIC_TITLE,
    MUSIC_BATTLE,
};

static const int MAX_SFX = 64;

static void init(); // call this only once, before all other methos
static void playMusic(int no, bool repeat=true);
static void stopMusic();
static void playSFX(int no);
static void quit(); // after quit() it is safe to call init() again

private:

static ALLEGRO_MIXER *mixer;
static ALLEGRO_VOICE *voice;
static ALLEGRO_AUDIO_STREAM *musicStream;
static ALLEGRO_SAMPLE *sfx[MAX_SFX];

static const char *musicFiles[];

Audio();
~Audio();

};

#endif
