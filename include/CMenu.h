#ifndef CMENU_H
#define CMENU_H
#include <Arduino.h>
#include <LiquidCrystal.h>

typedef struct TMenuItem
{
    int cmd;
    const char *text;
    void (* callback)();
    TMenuItem *previous;
    TMenuItem *next;
    TMenuItem *parent;
    TMenuItem *children;
} TMenuItem;

class CMenu
{
    public:
        CMenu(LiquidCrystal &lcd);
        virtual ~CMenu();

        void begin(int row);

        int getCmd(void);

        TMenuItem *getDisplayedMenu() const;
        void setRootMenu(TMenuItem *root);

        virtual void onKey(int key);
        virtual void draw(void) const;



    protected:
    private:
        int mrow;
        LiquidCrystal &mlcd;
        TMenuItem *mrootMenu;
        TMenuItem *mdisplayedItem;

        TMenuItem *getNext();
        TMenuItem *getPrevious();
        TMenuItem *head();
        TMenuItem *tail();

};

// utility functions
TMenuItem *addMenuItem(int cmd, const char *text, void (*callback)(), TMenuItem *next);

#endif // CMENU_H
