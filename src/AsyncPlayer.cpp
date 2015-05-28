#include "AsyncPlayer.h"

AsyncPlayer::AsyncPlayer()
{
    //ctor
}

AsyncPlayer::~AsyncPlayer()
{
    //dtor
}


void AsyncPlayer::begin(const int pinSpeaker){
    mPinSpeaker = pinSpeaker;
}

int AsyncPlayer::isPlaying() const
{
    return mIsPlaying;

}

void AsyncPlayer::continuePlay(){}
void AsyncPlayer::start(TSongPROGMEM song){}
void AsyncPlayer::pause(){}
void AsyncPlayer::stop(){}


int AsyncPlayer::getNextNote();
int AsyncPlayer::getNextDuration();
