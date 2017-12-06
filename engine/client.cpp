
#include <../include/client.hpp>

Client::Client(NetworkClient &network, std::string username) {
    this->net = &network;
    this->username = username;
}

vector<string> Client::pupitreMapToNameVec(std::map<Pupitre, bool> pmap) {
    vector<string> pupitreVec = vector<string>();
    for(pair<Pupitre, bool> p : pmap){
        if(!p.second) continue;
        string instrumentName = p.first.getInstrument().getname();
        int track = p.first.getTrack();
        string pupitreName = instrumentName + "_" + to_string(track);
        pupitreVec.push_back(pupitreName);
    }
    return pupitreVec;
}

void Client::sendAddClient(std::string username) {
    if (username.empty()){
        throw std::invalid_argument("Username null");
    }
    net->sendHello();
}

void Client::choosePupitre(Pupitre p) {

}

void Client::sendNote(Note note) {
    net->sendNote(note);
}

void Client::sendReady() {
    net->sendReady();
}

// SLOTS

void Client::loadPartition(Partition partition) {
    this->partition = partition;
    // generate global partition HERE !
	partitionGlobale = PartitionGlobale(partition);

    // create State
    vector<NoteGlobale>::iterator it = partitionGlobale.getNotes().begin();
    state = new State(it);

    // load game screen here !
    // need to check with ui team if this block the main thread

    sendReady(); // maybe in ui
}

void Client::forwardPupitreMap(std::map<Pupitre, bool>) {
    // send pupitre map to UI in order to display it HERE !
    // get choice and ack server about the pupitre choosen sendPupitreChoice
}

void Client::start() {
    // start UI game screen here : load global partition etc ...
}

// State Function



void Client::mainStateFunction() {
    if(state->getCurrentTime() < state->getBlockTime()) return;
    if(!state->stateChanged){

    }


}

// CAUTION : send notes just from global note with singal == false

void Client::sendNotesAfterError() {
    vector<NoteGlobale>::iterator start = state->itPartitionGlobal;
    vector<NoteGlobale>::iterator end =
            partitionGlobale.getNextValidIterator(start, state->getCurrentTime());
    for (vector<NoteGlobale>::iterator it = start; it!=end; it++){
        if(it->getSignal()) continue;
        // get a pointer in order to store
        // just unsended note in note global
        vector<Note>* vNote = it->getListOfNotes();
        vector<Note>::iterator start = vNote->begin();
        vector<Note>::iterator end = vNote->end();
        for (vector<Note>::iterator it = start; it!=end; it++){
            Note n = *it;
            sendNote(n);
        }
        vNote->clear();
    }
}