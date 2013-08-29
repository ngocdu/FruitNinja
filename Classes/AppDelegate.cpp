//
//  AirHockeyAppDelegate.cpp
//  AirHockey
//
//  Created by Trung Kien Do on 13/07/09.
//  Copyright __FRAMGIA__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "HelloWorldScene.h"
using namespace cocos2d;
using namespace CocosDenshion;
AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // Preload music file
//    SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/hitPuck.wav");
//    SimpleAudioEngine::sharedEngine()->preloadEffect("Sounds/score.wav");
//    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sounds/StartBG.mp3");
//    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sounds/BG.mp3");
//    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sounds/HardBG.mp3");
//    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sounds/StartBG.mp3");
//    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sounds/PlayIntro.mp3");

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    //    this->displayRanking();
    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
