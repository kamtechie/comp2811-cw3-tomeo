//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

using namespace std;

ThePlayer::ThePlayer() : QMediaPlayer(NULL) {
    setVolume(0); // be slightly less annoying

    connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );

    videoWidget = new QVideoWidget;
    this->setVideoOutput(videoWidget);

    //set up the playback buttons
    playButton = new QPushButton;
    playButton->setIconSize(QSize(90,90));
    playButton->setIcon(QIcon((":/playback_images/pause.png")));
    connect(playButton, SIGNAL (released()), this, SLOT (playClicked()));

    ffButton = new QPushButton;
    ffButton->setIconSize(QSize(90,90));
    ffButton->setIcon(QIcon((":/playback_images/ff.png")));
    connect(ffButton, SIGNAL (released()), this, SLOT (ffClicked()));

    rewindButton = new QPushButton;
    rewindButton->setIconSize(QSize(90,90));
    rewindButton->setIcon(QIcon((":/playback_images/rewind.png")));
    connect(rewindButton, SIGNAL (released()), this, SLOT (rewindClicked()));

    nextButton = new QPushButton;
    nextButton->setIconSize(QSize(90,90));
    nextButton->setIcon(QIcon((":/playback_images/next.png")));
    connect(nextButton, SIGNAL (released()), this, SLOT (nextClicked()));

    restartButton = new QPushButton;
    restartButton->setIconSize(QSize(90,90));
    restartButton->setIcon(QIcon((":/playback_images/restart.png")));
    connect(restartButton, SIGNAL (released()), this, SLOT (restartClicked()));


    //set up the layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(videoWidget);

    QHBoxLayout *controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(restartButton);
    controlsLayout->addWidget(rewindButton);
    controlsLayout->addWidget(playButton);
    controlsLayout->addWidget(ffButton);
    controlsLayout->addWidget(nextButton);
    mainLayout->addLayout(controlsLayout);

    display = new QWidget;
    display->setLayout(mainLayout);
}

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    setPlaybackRate(1);

    switch (ms) {
    case QMediaPlayer::State::StoppedState:
        //play(); // starting playing again...
        playButton->setIcon(QIcon((":/playback_images/play.png")));
        break;
    case QMediaPlayer::State::PausedState:
        playButton->setIcon(QIcon((":/playback_images/play.png")));
        break;
    case QMediaPlayer::State::PlayingState:
        playButton->setIcon(QIcon((":/playback_images/pause.png")));
        break;
    default:
        break;
    }
}

void ThePlayer::playClicked() {

    if (playbackRate() != 1) {
        setPlaybackRate(1);
        playButton->setIcon(QIcon((":/playback_images/pause.png")));
        return;
    }

    switch (this->state()) {
    case QMediaPlayer::State::StoppedState:
        play();
        playButton->setIcon(QIcon((":/playback_images/pause.png")));
        break;
    case QMediaPlayer::State::PausedState:
        play();
        playButton->setIcon(QIcon((":/playback_images/pause.png")));
        break;
    case QMediaPlayer::State::PlayingState:
        pause();
        playButton->setIcon(QIcon((":/playback_images/play.png")));
        break;
    }
}

void ThePlayer::ffClicked() {
    playButton->setIcon(QIcon((":/playback_images/play.png")));
    setPlaybackRate(2);
}

void ThePlayer::rewindClicked() {
    playButton->setIcon(QIcon((":/playback_images/play.png")));
    setPlaybackRate(-2);
}

void ThePlayer::nextClicked() {
    currentUrl = buttons->at(0)->info->url;
    setMedia(* currentUrl);
    setPlaybackRate(1);
    play();
}

void ThePlayer::restartClicked() {
    setMedia(*currentUrl);
    setPlaybackRate(1);
    play();
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    currentUrl = button->url;
    setMedia(* currentUrl);
    setPlaybackRate(1);
    play();
}
