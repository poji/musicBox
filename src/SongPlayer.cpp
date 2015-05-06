#include <Arduino.h>
#include <avr/pgmspace.h>
#include "include/SongPlayer.h"

SongPlayer::SongPlayer(int speakerPin)
{
    _speakerPin = speakerPin;
}

// y a surement moyen d'améliorer mais je vais faire simple
// 1) parce que je suis rouillé en C++, 2) parce que je suis pas sûr
// que le compilo AVR supporte toute les possibilités de C++
// (et en plus j'ai la flemme, mais ça je peux pas le dire...)
void SongPlayer::PlayRandomSong(TSong songs[], int nbSongs)
{
        // On choisit une chanson au hasard
        randomSeed(analogRead(0));
        int songNumber = random(nbSongs);

        this->PlaySong(songs[songNumber]);
}

void SongPlayer::PlayRandomSong(TSongPROGMEM songs[], int nbSongs){

        // On choisit une chanson au hasard
        randomSeed(analogRead(0));
        int songNumber = random(nbSongs);

        this->PlaySong(songs[songNumber]);
}

void SongPlayer::PlaySong(TSong song)
{
        // longeur du morceau
        int songLength = song.length;

        for (int thisNote = 0; thisNote < songLength; thisNote++)
        {

            // la table durations contient la durée en quantième de secondes
            // donc la ch'tite formule là, permet d'obtenir une durée en milliseconde.
            // (j'avoue cette partie là n'est pas de moi... :p )
            int noteDuration = 1000/song.durations[thisNote];
            tone(_speakerPin, song.notes[thisNote],noteDuration);

            // une p'tite pause entre les notes pour bien les entendres
            // (et non, ça non plus ce n'est pas de moi).
            int pauseBetweenNotes = noteDuration * 1.30;
            delay(pauseBetweenNotes);

            // mais tu vas la fermer ta g... heu... peux tu faire silence quelques instants afin que l'audience distingue nettement les notes
            noTone(8);
        }
}

void SongPlayer::PlaySong(TSongPROGMEM song)
{
        // longeur du morceau
        int songLength = song.Length;

        for (int thisNote = 0; thisNote < songLength; thisNote++)
        {

            // on ne peut pas accéder directement aux données en PROGMEM,
            // faut passer par un pointeur et une fonction dédiée
            word note = pgm_read_word_near(song.notesAddr + thisNote);
            byte duration = pgm_read_byte_near(song.durationsAddr + thisNote);

            // la table durations contient la durée en quantième de secondes
            // donc la ch'tite formule là, permet d'obtenir une durée en milliseconde.
            // (j'avoue cette partie là n'est pas de moi... :p )
            int noteDuration = 1000/duration;
            tone(_speakerPin, note,noteDuration);

            // une p'tite pause entre les notes pour bien les entendres
            // (et non, ça non plus ce n'est pas de moi).
            int pauseBetweenNotes = noteDuration * 1.30;
            delay(pauseBetweenNotes);

            // mais tu vas la fermer ta g... heu... peux tu faire silence quelques instants afin que l'audience distingue nettement les notes
            noTone(8);

            // oui, ce sont les mêmes commentaires, en mm temps ce sont QUASI les mêmes fontions hein !

        }



}
