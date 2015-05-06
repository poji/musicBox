#include <Arduino.h>
#include <avr/pgmspace.h>
#include <LiquidCrystal.h>
#include "include/tones.h"
#include "include/SongPlayer.h"

int get_key();
int adc2key(unsigned int input);

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int KEYPAD_NONE = -1;
const int KEYPAD_RIGHT = 0;
const int KEYPAD_UP = 1;
const int KEYPAD_DOWN = 2;
const int KEYPAD_LEFT = 3;
const int KEYPAD_SELECT = 4;

const char blank[17] = "                ";
char msgs[5][16] = {"Right Key OK ",
                    "Up Key OK    ",
                    "Down Key OK  ",
                    "Left Key OK  ",
                    "Select Key OK"
                   };

const int adcKeyVal[5] = { 50, 200, 400, 600, 800};
const int NUMKEYS = 5;
const int ADC_PIN = 0;

int oldKey = -1;

const int speakerPin = 9;
int playItSam=0;

/* code ARDUINO g��n��r�� par NokiaRTTL2Arduino */

// les notes et les dur��es sont stock��e en FLASH RAM (utilisation de PROGMEM

// La Famille Addams
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

// la liste des morceaux est en SRAM mais les morceux en eux-m��mes sans dans la m��moire FLASH
// on ��conomise pas mal de m��moire du coup.
// en gros l�� ou la SRAM me permettait tout juste de stocker les 6 morceaux, l�� j'empi��te �� peine sur la FLASH (ben enfin, vraiment pas beaucoup)
// et j'��conomise ENORMEMENT de SRAM.

TSongPROGMEM songsPM[6] = {
    {"Addams", addamsLength, addamsNotes, addamsDurations},
    {"Arkanoid", arkanoidLength, arkanoidNotes, arkanoidDurations},
    {"StarWars", SWLength, SWNotes, SWDurations},
    {"Duke3D", DukeLength, DukeNotes, DukeDurations},
    {"Simpsons", SimpsonsLength, SimpsonsNotes, SimpsonsDurations},
    {"Toccata", ToccataLength, ToccataNotes, ToccataDurations}
};


int nbSongs = 6; // 6 titres, on pourrait imaginer en avoir facilement trois ou quatre fois plus

/*================== END SONG INFO ==================================*/

SongPlayer player(speakerPin); // on instancie la class SongPlayer, parce que nous le vallons bien


void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("KeyPad :");
    lcd.setCursor(0, 1);


}

void loop() {
  int keypad = get_key();
  if (keypad != KEYPAD_NONE)
  {
    Serial.write(msgs[keypad]);
    lcd.setCursor(0,1);
    lcd.print(blank);
    lcd.setCursor(0,1);
    lcd.print(msgs[keypad]);

    // testons le bouton....
    // si bouton press��, alors le pianiste doit jouer...
    if (playItSam==0 && keypad == KEYPAD_SELECT) {
        playItSam=1;
    }

    if(playItSam==1)
    {
        // jouer un "titre" au hasard
        player.PlayRandomSong(songsPM, nbSongs);
        playItSam=0;
	}

  }
}

int get_key()
{
    unsigned int adc_key_in = analogRead(ADC_PIN);

    int key = adc2key(adc_key_in);
    if (key != oldKey)
    {
      delay(50); // wait for debounce
      adc_key_in = analogRead(ADC_PIN);
      key = adc2key(adc_key_in);
      if (key != oldKey) {
        return key;
      }

    }

    return KEYPAD_NONE;
}

// Convert ADC value to key number
int adc2key(unsigned int input)
{
  int k;
  for (k = 0; k < NUMKEYS; k++)
  {
    if (input < adcKeyVal[k])
    {
      return k;
    }
  }

  if (k >= NUMKEYS)
    k = KEYPAD_NONE;  // No valid key pressed

  return k;
}
