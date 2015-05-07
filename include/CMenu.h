#ifndef CMENU_H
#define CMENU_H
#include <Arduino.h>
#include <LiquidCrystal.h>

// double linked structure for the menu
// I have prepared the possibility to have child menu, not implemented yet.
typedef struct TMenuItem
{
    int cmd;                    // an "command" identifier, for extra purpose
    const char *text;           // text to show on lcd
    void (* callback)();        // callback to call is selected
    TMenuItem *previous;        // obvious, no ?
    TMenuItem *next;            // this one too i think
    TMenuItem *parent;          // for a child menu, point to the parent menuitem
    TMenuItem *children;        // for a parent menu, point to the first child menuitem
} TMenuItem;

// An (simple) LCD menu system.
class CMenu
{
    public:
        CMenu(LiquidCrystal &lcd);              // reference to lcd variable instancied in the main sketche
        virtual ~CMenu();                       // destructor, do nothing (for the moment)

        void begin(int row);                    // init the menu with the row to use on the display

        int getCmd(void) const;                 // return the last commande activated

        TMenuItem *getDisplayedMenu() const;    // get the current displayed menu item
        void setRootMenu(TMenuItem *root);      // set the system menu tree

        virtual int onKey(int key);             // process the key, return the cmd, if any
        virtual void draw(void) const;          // draw the current menu.



    protected:
    private:
        int mrow;                               // lcd row to use
        int mlastCmd;                           // last cmd selected
        LiquidCrystal &mlcd;                    // reference to the lcd instance
        TMenuItem *mrootMenu;                   // tree menu
        TMenuItem *mdisplayedItem;              // current menu item

        TMenuItem *getNext();                   // get the next menu item
        TMenuItem *getPrevious();               // get the previous menu item
        TMenuItem *head();                      // get the first item in the menu tree
        TMenuItem *tail();                      // get the last item of the current menu branch

};

/*
                    utility belt functions
*/

// create a menu item. nested call create the menu tree
TMenuItem *addMenuItem(int cmd, const char *text, void (*callback)(), TMenuItem *next);

#endif // CMENU_H
