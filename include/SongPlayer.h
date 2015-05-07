#ifndef SONGPLAYER_H
#define SONGPLAYER_H

#include "Arduino.h"

/* this structure is for SRAM storage, it's more simple to use, but honestly,
    the class manage all the (little) difficulties
*/

typedef struct SSong {
    word notes[64];             // length arbitrary set
    word durations[64];         // idem
    byte length;                // real length of the song (yes GARBAGE !!!! if the song is 16 notes long, we use (48*2)*2 extra bytes
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
