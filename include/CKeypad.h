#ifndef CKEYPAD_H
#define CKEYPAD_H

#define NUMKEYS 5
extern int adcKeyVal[];

class CKeypad
{
    public:
        CKeypad();
        virtual ~CKeypad();
        void begin(int adc_pin);

        int get_key();
        int get_adcvalue() const;

        static const int KEYPAD_NONE = -1;
        static const int KEYPAD_RIGHT = 0;
        static const int KEYPAD_UP = 1;
        static const int KEYPAD_DOWN = 2;
        static const int KEYPAD_LEFT = 3;
        static const int KEYPAD_SELECT = 4;

    protected:
    private:
        int mlastkey;
        int madcValue;
        int madcPin;

        int adc2key(unsigned int input);



};

#endif // CKEYPAD_H
