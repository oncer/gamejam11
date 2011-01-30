#include "audio.h"

ALLEGRO_MIXER* Audio::mixer;
ALLEGRO_VOICE* Audio::voice;
ALLEGRO_AUDIO_STREAM* Audio::musicStream;
ALLEGRO_SAMPLE* Audio::sfx[MAX_SFX];

const char* Audio::musicFiles[] = {
	"audio/super extinction.ogg", // MUSIC_TITLE
	"audio/battle.ogg", // MUSIC_BATTLE
};;

void Audio::init()
{
    al_init_acodec_addon();
    al_install_audio();
    voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
    mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
    al_attach_mixer_to_voice(mixer, voice);
	al_reserve_samples(32);
    musicStream = NULL;

    for (int i=0; i<MAX_SFX; i++) {
        sfx[i] = NULL;
    }
#define LOAD(no,f)\
	sfx[no] = al_load_sample(f)
	LOAD(SFX_SHOT,		"audio/shot.wav"	);
	LOAD(SFX_DEATH,		"audio/death.wav"	);
	LOAD(SFX_COLLECT,	"audio/collect.wav" );
#undef LOAD
}

void Audio::playMusic(int no, bool repeat)
{
    musicStream = al_load_audio_stream(musicFiles[no], 6, 1536);
    if (repeat) {
        al_set_audio_stream_playmode(musicStream, ALLEGRO_PLAYMODE_LOOP);
    } else {
        al_set_audio_stream_playmode(musicStream, ALLEGRO_PLAYMODE_ONCE);
    }
	al_attach_audio_stream_to_mixer(musicStream, mixer);
}

void Audio::stopMusic()
{
    if (musicStream != NULL) {
        al_destroy_audio_stream(musicStream);
        musicStream = NULL;
    }
}

void Audio::playSFX(int no)
{
	if (sfx[no] == NULL) return;
	al_play_sample(sfx[no], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void Audio::quit()
{
    stopMusic();
	for (int i=0; i<MAX_SFX; i++) {
		if (sfx[i] != NULL) {
			al_destroy_sample(sfx[i]);
		}
	}
    al_destroy_mixer(mixer);
    al_destroy_voice(voice);
    al_uninstall_audio();
}

