#include <Arduino.h>
#include "include/CKeypad.h"

int adcKeyVal[NUMKEYS] = { 50, 200, 400, 600, 800};

CKeypad::CKeypad()
{
    //ctor
}

CKeypad::~CKeypad()
{
    //dtor
}

void CKeypad::begin(int adc_pin)
{
    madcPin = adc_pin;
}

int CKeypad::get_adcvalue() const
 {
    return madcValue;
}

int CKeypad::get_key()
{
    unsigned int adc_key_in = analogRead(madcPin);
    madcValue = adc_key_in;

    int key = adc2key(adc_key_in);
    if (key != mlastkey)
    {
      delay(50); // wait for debounce
      adc_key_in = analogRead(madcPin);
      key = adc2key(adc_key_in);
      if (key != mlastkey)
      {
        mlastkey = key;
        return key;
      }

    }

    return KEYPAD_NONE;
}


// Convert ADC value to key number
int CKeypad::adc2key(unsigned int input)
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
    k = CKeypad::KEYPAD_NONE;  // No valid key pressed

  return k;
}
