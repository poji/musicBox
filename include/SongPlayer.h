#ifndef SONGPLAYER_H
#define SONGPLAYER_H

#include "Arduino.h"

typedef struct SSong {
    word notes[64];             // longueur de tableau totalement arbitraire, la version PROGMEM utilise des pointeurs, plus économe en espace mémoire du coup
    word durations[64];         // idem
    byte length;
    String name;
} TSong;

typedef struct SSongPROGMEM     // bon alors en fait, du coup dans ce projet-ci, je n'utilise que cette structure... l'autre pourrait sauter sans regret...
{
    String Name;
    byte Length;
    prog_uint16_t* notesAddr;
    prog_uint8_t* durationsAddr;
} TSongPROGMEM;

class SongPlayer
{
    public:
        SongPlayer(int speakerPin);
        void PlaySong(TSong song);
        void PlaySong(TSongPROGMEM songPM);
        void PlayRandomSong(TSong songs[], int nbSongs);
        void PlayRandomSong(TSongPROGMEM songs[], int nbSongs);
    protected:
    private:
        int _speakerPin;
};

#endif // SONGPLAYER_H
