//
//  GameFishAppDelegate.cpp
//  GameFish
//
//  Created by MinhNT on 13/07/29.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "GameManager.h"
using namespace cocos2d;
USING_NS_CC;
using namespace CocosDenshion;
typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;
static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "iPhone" };
static Resource mediumResource =  { cocos2d::CCSizeMake(960, 640),  "iPhone_hd"   };
static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "ipadhd" };
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);
AppDelegate::AppDelegate()
{
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    SimpleAudioEngine::sharedEngine()->preloadEffect("smallcut.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("squash.mp3");
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("nature_bgm.mp3");
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    CCSize designSize = CCSizeMake(480, 320);
    CCSize resourceSize = CCSizeMake(480, 320);
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
    std::vector<std::string> resDirOrders;
    
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    if (platform == kTargetIphone || platform == kTargetIpad)
    {
        std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
        //        searchPaths.insert(searchPaths.begin(), "Published-iOS");
        //        searchPaths.insert(searchPaths.begin(), "Resources");
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
        
        if (screenSize.height > 768)
        {
            resourceSize = CCSizeMake(2048, 1536);
//            resDirOrders.push_back("resources-ipadhd");
            resDirOrders.push_back("iPhone_hd");
            searchPaths.push_back("iPhone_hd");
        }
        else if (screenSize.height > 640)
        {
            resourceSize = CCSizeMake(1536, 768);
//            resDirOrders.push_back("resources-ipad");
            resDirOrders.push_back("iPhone_hd");
            searchPaths.push_back("iPhone_hd");
        }else if (screenSize.height > 320)
        {
            resourceSize = CCSizeMake(960, 640);
            //            resDirOrders.push_back("resources-iphonehd");
            //            searchPaths.push_back("resources-iphonehd");
//            resDirOrders.push_back("iPhone_hd");
//            searchPaths.push_back("iPhone_hd");
            resDirOrders.push_back("iPhone");
            searchPaths.push_back("iPhone");
        }
        else
        {
            //            resDirOrders.push_back("resources-iphone");
            //            searchPaths.push_back("resources-iphone");
            resDirOrders.push_back("iPhone");
            searchPaths.push_back("iPhone");
        }
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
    }
    else if (platform == kTargetAndroid || platform == kTargetWindows)
    {
        
        if (screenSize.width > 720)
        {
            resourceSize = CCSizeMake(960, 640);
            resDirOrders.push_back("resources-large");
        }
        else if (screenSize.width > 568)
        {
            resourceSize = CCSizeMake(720, 480);
            resDirOrders.push_back("resources-medium");
        }
        else
        {
            resourceSize = CCSizeMake(568, 320);
            resDirOrders.push_back("resources-small");
        }
    }
    
    CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
    float scale = (float)resourceSize.width * 1.0f/designSize.width;
//    pDirector->setContentScaleFactor(scale);
    //     pDirector->setContentScaleFactor(2.0f);
    //    pDirector->setContentScaleFactor(designSize.width / resourceSize.width);
    GameManager::sharedGameManager()->setScaleSize(scale);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);
    
    // turn on display FPS
    pDirector->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
   
    CCScene *pScene = HelloWorld::scene();
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
