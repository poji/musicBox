#ifndef SONGS_H
#define SONGS_H

/* code ARDUINO généré par NokiaRTTL2Arduino */

// notes and durations are stored in FLASH RAM with PROGMEM

// Addams Familly
prog_uint16_t addamsNotes[52] PROGMEM = {NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,0,NOTE_D5,NOTE_E5,NOTE_FS5,NOTE_G5,0,NOTE_D5,NOTE_E5,NOTE_FS5,NOTE_G5,0,NOTE_D5,NOTE_E5,NOTE_FS5,NOTE_G5,0,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,0,NOTE_C5,NOTE_F5,NOTE_A5,NOTE_F5,NOTE_C5,NOTE_B4,NOTE_G5,NOTE_F5,NOTE_E5,NOTE_G5,NOTE_E5,NOTE_C5,NOTE_A4,NOTE_F5,NOTE_C5,NOTE_F5,NOTE_A5,NOTE_F5,NOTE_C5,NOTE_B4,NOTE_G5,NOTE_F5,NOTE_E5,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5};
prog_uint8_t addamsDurations[52] PROGMEM = {8,8,8,8,1,8,8,8,8,1,8,8,8,8,4,8,8,8,8,4,8,8,8,8,1,8,4,8,4,8,4,2,8,4,8,4,8,4,2,8,4,8,4,8,4,2,8,4,8,4,8,2};
byte addamsLength = 52;

// Arkanoid
prog_uint16_t arkanoidNotes[10] PROGMEM = {NOTE_G6,0,NOTE_G6,NOTE_AS6,0,NOTE_A6,NOTE_G6,NOTE_F6,NOTE_A6,NOTE_G6};
prog_uint8_t arkanoidDurations[10] PROGMEM = {8,16,16,2,32,8,8,8,8,2};
byte arkanoidLength = 10;

// starwars
prog_uint16_t SWNotes[39] PROGMEM = {NOTE_F5,NOTE_F5,NOTE_F5,NOTE_AS5,NOTE_F6,NOTE_DS6,NOTE_D6,NOTE_C6,NOTE_AS6,NOTE_F6,NOTE_DS6,NOTE_D6,NOTE_C6,NOTE_AS6,NOTE_F6,NOTE_DS6,NOTE_D6,NOTE_DS6,NOTE_C6,0,NOTE_F5,NOTE_F5,NOTE_F5,NOTE_AS5,NOTE_F6,NOTE_DS6,NOTE_D6,NOTE_C6,NOTE_AS6,NOTE_F6,NOTE_DS6,NOTE_D6,NOTE_C6,NOTE_AS6,NOTE_F6,NOTE_DS6,NOTE_D6,NOTE_DS6,NOTE_C6};
prog_uint8_t SWDurations[39] PROGMEM = {8,8,8,1,2,8,8,8,2,4,8,8,8,2,4,8,8,8,2,4,8,8,8,1,2,8,8,8,2,4,8,8,8,2,4,8,8,8,2};
byte SWLength = 39;

// duke3d
prog_uint16_t DukeNotes[61] PROGMEM = {NOTE_FS4,NOTE_A4,0,NOTE_B4,0,NOTE_FS4,NOTE_B4,0,NOTE_CS5,0,NOTE_FS4,NOTE_CS5,0,NOTE_D5,0,NOTE_FS4,0,NOTE_CS5,NOTE_B4,NOTE_A4,NOTE_FS4,NOTE_E4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_B4,NOTE_A4,NOTE_G4,NOTE_FS4,NOTE_A4,0,NOTE_FS4,NOTE_A4,0,NOTE_B4,0,NOTE_FS4,NOTE_B4,0,NOTE_CS5,0,NOTE_FS4,NOTE_CS5,0,NOTE_D5,0,NOTE_FS4,0,NOTE_CS5,NOTE_B4,NOTE_A4,NOTE_FS4,NOTE_E4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_B4,NOTE_A4,NOTE_G4,NOTE_FS4,NOTE_A4};
prog_uint8_t DukeDurations[61] PROGMEM = {16,16,16,16,8,16,16,16,16,8,16,16,16,16,16,16,16,8,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,8,16,16,16,16,8,16,16,16,16,16,16,16,8,16,16,16,16,16,16,16,16,16,16,16,16};
byte DukeLength = 61;

// simpsons
prog_uint16_t SimpsonsNotes[23] PROGMEM = {NOTE_C6,NOTE_E6,NOTE_FS6,NOTE_A6,NOTE_G6,NOTE_E6,NOTE_C6,NOTE_A5,NOTE_FS5,NOTE_FS5,NOTE_FS5,NOTE_G5,0,0,NOTE_FS5,NOTE_FS5,NOTE_FS5,NOTE_G5,NOTE_AS5,NOTE_C6,NOTE_C6,NOTE_C6,NOTE_C5};
prog_uint8_t SimpsonsDurations[23] PROGMEM = {4,4,4,8,4,4,4,8,8,8,8,2,8,8,8,8,8,8,2,8,8,8,4};
byte SimpsonsLength = 23;

// TocattaFugue
prog_uint16_t ToccataNotes[25] PROGMEM = {NOTE_AS5,NOTE_GS5,NOTE_AS5,NOTE_GS5,NOTE_FS5,NOTE_F5,NOTE_DS5,NOTE_D5,NOTE_DS5,NOTE_AS5,NOTE_GS5,NOTE_AS5,NOTE_F5,NOTE_FS5,NOTE_D5,NOTE_DS5,NOTE_D5,NOTE_F5,NOTE_GS5,NOTE_B5,NOTE_D6,NOTE_F6,NOTE_GS5,NOTE_F5,NOTE_G5};
prog_uint8_t ToccataDurations[25] PROGMEM = {16,16,2,32,32,32,16,2,2,16,16,2,8,8,8,2,8,8,8,8,8,4,2,2,1};
byte ToccataLength = 25;

// song list is SRAM but the songs data are in FLASH RAM
// using only SRAM, i could'nt have more than 6 songs in the list (SRAM used nearly at 80%)

// this reside in SRAM, buts those are only pointers
TSongPROGMEM songsPM[6] = {
    {"Addams", addamsLength, addamsNotes, addamsDurations},
    {"Arkanoid", arkanoidLength, arkanoidNotes, arkanoidDurations},
    {"StarWars", SWLength, SWNotes, SWDurations},
    {"Duke3D", DukeLength, DukeNotes, DukeDurations},
    {"Simpsons", SimpsonsLength, SimpsonsNotes, SimpsonsDurations},
    {"Toccata", ToccataLength, ToccataNotes, ToccataDurations}
};

// for the moment i set only 6 songs, we could potentially have for or five more
int nbSongs = 6;

/*================== END SONG INFO ==================================*/

#endif // SONGS_H
