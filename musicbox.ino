#include <Arduino.h>
#include <avr/pgmspace.h>
#include <LiquidCrystal.h>

#include "include/tones.h"
#include "include/SongPlayer.h"
#include "include/CMenu.h"
#include "include/songs.h"
#include "include/CKeypad.h"

// some usefull const var
const int adc_pin = 0;                          // used by the keypad of the linksprite lcd keypad
const int speakerPin = 11;                      // pin used by the speaker, obviously

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);            // the linkpsprite pin are fixed, we can't change them
CMenu menu(lcd);                                // our menu
CKeypad keypad;                                 // keypad management facility


// the song currently selected
int currentSong = 0;
char blank[17];      // for cleaning a line of the lcd
char buffer[50];     // for debug message
void fillBuffer(char *buffer, char fillingChar, size_t length); // buffer to send message accros serial


// some callback, used by the menu
void nextSong(void);
void prevSong(void);
void playSong(void);
void displaySongname(int songnum);

// sonplayer class take care of the retrieval and the playing of song data
SongPlayer player(speakerPin);

void initCString(char *buffer, char value, int size){
    memset(buffer, value, size-1);
    buffer[size-1]='\0'; // null terminated string

}


void setup()
{
    Serial.begin(9600);             // for debug purpose for the moment
    lcd.begin(16, 2);               // yes, the lcd is a 16X2 characters screen
    keypad.begin(adc_pin);          // we can use always A0, it's not manageable with the linksprite
    menu.begin(0);                  // menu would be shown on the row 0 of the lcd

    // we create the menu "tree", nota the use of callbacks
    // create a "blank" line, useful for lcd row cleanup
    initCString(blank, 32, 17);      // 16 space char and a zero terminal string

    menu.setRootMenu
        (
            addMenuItem(1, "Next Song", nextSong,
            addMenuItem(2, "Prev Song", prevSong,
            addMenuItem(3, "Play", playSong, NULL)))
        );

    // display the menu, it would be usefull...
    menu.draw();


}

void loop() {

    // get the key pressed, if any
  int key = keypad.get_key();
  if (key != CKeypad::KEYPAD_NONE)
  {

    fillBuffer(buffer, 0, 50);
    sprintf(buffer, "Event > adc/key = %d/%d\n", keypad.get_adcvalue(), key);
    Serial.println(buffer);

    // give the key to the menu, and let it do things with it
    int cmd = menu.onKey(key);
    if(cmd!=0){
        Serial.print("Command activated : ");
        Serial.println(cmd);
    }
  }
}

void fillBuffer(char *buffer, char fillingChar, size_t length){
    memset(buffer, fillingChar, length);
}

// those are callbacks for the menu, names are suffisently obvious, i think
void nextSong(void)
{
    currentSong++;
    if(currentSong>=nbSongs)
        currentSong = 0;
    displaySongname(currentSong);
}
void prevSong(void){
    currentSong--;
    if(currentSong<0)
        currentSong = nbSongs-1;
    displaySongname(currentSong);
}

// play a song, for the moment, the playing is synchrone, i've planned to do an "asynchrone" playing function...
void playSong(void){
    lcd.setCursor(0,1);
    lcd.print(blank);
    lcd.setCursor(0,1);
    lcd.print("Playing ");
    lcd.print(songsPM[currentSong].Name);
    player.PlaySong(songsPM[currentSong]);
    lcd.setCursor(0,1);
    lcd.print(blank);
    lcd.setCursor(0,1);
    lcd.print("Played ");
    lcd.print(songsPM[currentSong].Name);

}

// just display the name of the current selected/played song
void displaySongname(int songnum){
    lcd.setCursor(0,1);
    lcd.print(blank);
    lcd.setCursor(0,1);
    lcd.print(songsPM[songnum].Name);
}
