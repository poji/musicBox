#include <Arduino.h>
#include <avr/pgmspace.h>
#include <LiquidCrystal.h>

#include "include/tones.h"
#include "include/SongPlayer.h"
#include "include/CMenu.h"
#include "include/songs.h"
#include "include/CKeypad.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
CMenu menu(lcd);
CKeypad keypad;

const char blank[17] = "                ";

const int adc_pin = 0;
const int speakerPin = 9;

int currentSong = 0;

void nextSong(void);
void prevSong(void);
void playSong(void);
void displaySongname(int songnum);

SongPlayer player(speakerPin); // on instancie la class SongPlayer, parce que nous le vallons bien

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    keypad.begin(adc_pin);
    menu.begin(0);

    menu.setRootMenu
        (
            addMenuItem(1, "Next Song", nextSong,
            addMenuItem(2, "Prev Song", prevSong,
            addMenuItem(3, "Play", playSong, NULL)))
        );

    menu.draw();


}

void loop() {
  int key = keypad.get_key();
  if (key != CKeypad::KEYPAD_NONE)
  {
    Serial.write("key press : ");
    Serial.write(keypad.get_adcvalue());
    Serial.write("/");
    Serial.write(key);
    Serial.write("\n");

    menu.onKey(key);
  }
}

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

void displaySongname(int songnum){
    lcd.setCursor(0,1);
    lcd.print(blank);
    lcd.setCursor(0,1);
    lcd.print(songsPM[songnum].Name);
}
