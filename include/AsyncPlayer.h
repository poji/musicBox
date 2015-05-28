#ifndef ASYNCPLAYER_H
#define ASYNCPLAYER_H
#include <Arduino.h>
#include <avr/pgmspace.h>
#include "include/SongPlayer.h"

class AsyncPlayer
{
    public:
        AsyncPlayer();
        virtual ~AsyncPlayer();

        void begin(const int pinSpeaker);

		int isPlaying() const;
		void continuePlay();
		void start(TSongPROGMEM song);
		void pause();
		void stop();

    protected:
    private:
		TSongPROGMEM song;
		int mPinSpeaker;
		int mCurrentNote;
		int mCurrentNoteDuration;
		int mNoteStartedAt;
		int mIsPlaying;
		int mIsPaused;

		int mNoteIndex;

		int getNextNote();
		int getNextDuration();
};

#endif // ASYNCPLAYER_H
