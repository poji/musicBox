#include <Arduino.h>
#include "include/CMenu.h"
#include "include/CKeypad.h"

#define BLANKLINE "                "

CMenu::CMenu(LiquidCrystal &lcd):mlcd(lcd), mrootMenu(NULL), mdisplayedItem(NULL)
{}
CMenu::~CMenu(){}

void CMenu::setRootMenu(TMenuItem *root){
    mrootMenu = root;
    mdisplayedItem = root;
}

void CMenu::begin(int row){
    mrow = row;
}

TMenuItem *CMenu::getDisplayedMenu() const
{
    return mdisplayedItem;
}


void CMenu::onKey(int key)
{
    switch(key){
    case CKeypad::KEYPAD_SELECT:
        if(mdisplayedItem!=NULL && mdisplayedItem->callback!=NULL){
            mdisplayedItem->callback();
        }
        break;
    case CKeypad::KEYPAD_DOWN:
        mdisplayedItem = getNext();
        draw();
        break;
    case CKeypad::KEYPAD_UP:
        mdisplayedItem = getPrevious();
        draw();
        break;
    default:
        // do nothing
        break;
    }

}

void CMenu::draw(void) const
{
    mlcd.setCursor(0,mrow);
    mlcd.print(BLANKLINE);
    mlcd.setCursor(0,mrow);

    if(mdisplayedItem!=NULL)
    {
        if(mdisplayedItem->parent!=NULL){
            mlcd.print("<");
        }
        mlcd.print(mdisplayedItem->text);
        if(mdisplayedItem->children!=NULL){
            mlcd.print(">");
        }

    }
    else
        mlcd.print("<NO MENU>");
}


TMenuItem *CMenu::getNext(){
    if(mdisplayedItem==NULL)
        return head();

    if(mdisplayedItem->next==NULL)
        return head();

    return mdisplayedItem->next;
}
TMenuItem *CMenu::getPrevious()
{
    if(mdisplayedItem==NULL)
        return head();

    if(mdisplayedItem->previous==NULL)
        return tail();

    return mdisplayedItem->previous;
}

TMenuItem *CMenu::head()
{
    return mrootMenu;
}
TMenuItem *CMenu::tail(){
    if(mrootMenu==NULL)
        return NULL;

    TMenuItem *cursor = mrootMenu;
    while(cursor->next!=NULL)
        cursor = cursor->next;
    return cursor;
}




/*
                                    UTILITY BELT
*/


TMenuItem *addMenuItem(int cmd, const char *text, void (*callback)(), TMenuItem *next)
{
        TMenuItem *mnuItem = new TMenuItem();
        mnuItem->cmd = cmd;
        mnuItem->text = text;
        mnuItem->callback = callback;
        mnuItem->next = next;
        mnuItem->previous = NULL;
        if(next!=NULL){
            next->previous = mnuItem;
        }
        mnuItem->parent = NULL;
        mnuItem->children = NULL;

        return mnuItem;
}
