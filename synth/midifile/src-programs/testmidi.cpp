#include "/home/romain/Documents/INF552/FANFARE/midifile/include/MidiFile.h"
#include "/home/romain/Documents/INF552/FANFARE/midifile/include/Options.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char** argv) {
   MidiFile midifile;
   midifile.read("Movie_Themes_-_1492_Conquest_of_Paradise.midi");

  int tracks = midifile.getTrackCount();
  cout << "TPQ: " << midifile.getTicksPerQuarterNote() << endl;
  if (tracks > 1) {
      cout << "TRACKS: " << tracks << endl;
  }
  for (int track=0; track < 3; track++) {
      if (tracks > 1) {
          cout << "\nTrack " << track << " has " << midifile.getEventCount(track) << " events" << endl;
       }
       for (int event=0; event < midifile.getEventCount(track); event++) {
          if(event < 100){
            cout << midifile.getEvent(track, event).tick << " ";
            cout << midifile.getEvent(track, event).getCommandByte() << " ";
            cout << midifile.getEvent(track, event).getCommandNibble() << " ";
                if(midifile.getEvent(track, event).isAftertouch()){
                  cout << "Aftertouch ";
                }
                if(midifile.getEvent(track, event).isController()){
                  cout << "Controller ";
                }
                if(midifile.getEvent(track, event).isMeta()){
                  cout << "Meta ";
                }
                if(midifile.getEvent(track, event).isNoteOn()){
                  cout << "Note On ";
                }
                if(midifile.getEvent(track, event).isNoteOff()){
                  cout << "Note Off ";
                }
                if(midifile.getEvent(track, event).isPitchbend()){
                  cout << "Pitchbend ";
                }
                if(midifile.getEvent(track, event).isPressure()){
                  cout << "Pressure ";
                }
                if(midifile.getEvent(track, event).isTempo()){
                  cout << "Tempo ";
                }
                if(midifile.getEvent(track, event).isTimbre()){
                  cout << "Timbre ";
                }
                for (int i=0; i<midifile.getEvent(track, event).size(); i++) {
                            cout << (int)midifile.getEvent(track, event)[i] << ' ';
                  }


  //       cout << dec << midifile[track][event].tick;
  //
  //        cout << '\t' << hex;
  //        for (int i=0; i<midifile[track][event].size(); i++) {
  //           cout << (int)midifile[track][event][i] << ' ';
              //}
          cout << endl;}
       }
   }

   return 0;
}