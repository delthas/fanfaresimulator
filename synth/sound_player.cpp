#include <stdio.h>
#ifdef __unix__
#include <unistd.h>
#elif defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif
#include "sound_player.h"
#include "note.hpp"


Sound_player::Sound_player() {
    printf("Created the Synth !\n");
    settings = new_fluid_settings();
    synth = new_fluid_synth(settings);

    /* Set the synthesizer settings, if necessary */
#ifdef __linux__
            fluid_settings_setstr(settings, "audio.driver", "pulseaudio"); // à changer
#endif
    fluid_synth_sfload(synth, "../resources/sf.sf2", 1);

    adriver = new_fluid_audio_driver(settings, synth);

    fluid_settings_setnum(settings, "synth.gain", 2);

}

Sound_player::~Sound_player() {
    delete_fluid_audio_driver(adriver);
    delete_fluid_settings(settings);
    delete_fluid_synth(synth);
}

void Sound_player::playNote(Note* note){
    if(note->getSignal()){
        fluid_synth_noteon(synth, note->getInstrument(), note->getKey (), note->getVelocity ());
    }
    else {
        fluid_synth_noteoff(synth,note->getInstrument(),note->getVelocity ());
    }
    printf("played !\n");
}

void Sound_player::testSynth() {

}
