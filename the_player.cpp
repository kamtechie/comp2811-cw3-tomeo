//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

using namespace std;

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

// change the image and video for one button every one second
void ThePlayer::shuffle() {
    int dup = 1; //duplicate indicator, 0 if not a duplicate, 1 if a duplicate
    TheButtonInfo* i;
//        setMedia(*i->url);

    while (dup == 1) {
        dup = 0;
        //get a new random video
        i = & infos -> at (rand() % infos->size() );

        //check if the video is already in the up next
        for (int j=0; j < 4; j++) {
            if (buttons->at(j)->info->url == i->url) {
                dup = 1;
             }
        }
    }
    //change the button
    buttons -> at( updateCount++ % buttons->size() ) -> init( i );
}

void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    switch (ms) {
        case QMediaPlayer::State::StoppedState:
            play(); // starting playing again...
            break;
    default:
        break;
    }
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    play();
}
