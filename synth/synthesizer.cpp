#include "synthesizer.hpp"

#include <stdio.h>
#include <unistd.h>

#include "fluidsynth.h"
#include "fluidsynth/settings.h"

void testSynth () {
	
	printf("Hello world from the synth !");
	
	
    fluid_settings_t* settings;
    fluid_synth_t* synth;
    fluid_audio_driver_t* adriver;
    settings = new_fluid_settings();
    /* Set the synthesizer settings, if necessary */
    synth = new_fluid_synth(settings);
    fluid_settings_setstr(settings, "audio.driver", "jack"); // à changer
    
    
    adriver = new_fluid_audio_driver(settings, synth);
    
    
    fluid_synth_sfload(synth, "sf.sf2", 1);
    
    int key;
	for (int i = 0; i < 12; i++) {
		/* Generate a random key */
		key = 60;
		/* Play a note */
		fluid_synth_noteon(synth, 0, key, 80);
		/* Sleep for 1 second */
		sleep(1);
		/* Stop the note */
		fluid_synth_noteoff(synth, 0, key);
	}
    
    /* Do useful things here */
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
	
	
	return;
	
}