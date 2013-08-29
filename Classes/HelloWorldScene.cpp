#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "stdio.h"
#include "Fruit.h"
using namespace cocos2d;
using namespace CocosDenshion;

#pragma mark - segcross
float HelloWorld::cross(CCPoint a, CCPoint b, CCPoint c) 
{
	float x1 = b.x - a.x;
	float y1 = b.y - a.y;
	float x2 = c.x - a.x;
	float y2 = c.y - a.y;
	return (x1 * y2 - x2 * y1);
}
float HelloWorld::dot(CCPoint a, CCPoint b, CCPoint c) { //点积，结果大于０则夹角小于９０度，小于０则大于９０度，等于０则垂直
	int x1 = b.x - a.x;
	int y1 = b.y - a.y;
	int x2 = c.x - a.x;
	int y2 = c.y - a.y;
	return (x1 * x2 + y1 * y2);
}

bool HelloWorld::segcrossSimple(_segment sega, _segment segb) { //判断两线段是否相交（规范相交，非规范相交）
	float d1 = cross(sega.a, sega.b, segb.a); //得用叉积原理判断另外一线段的两点是否在另一线段的两侧
	float d2 = cross(sega.a, sega.b, segb.b);
	float d3 = cross(segb.a, segb.b, sega.a);
	float d4 = cross(segb.a, segb.b, sega.b);
	//规范相交
	if(d1 * d2 < 0 && d3 * d4 < 0) //一线段的两端点在另一线段的两侧，相交
		return true;
	//非规范相交
	if(d1 == 0 && dot(segb.a, sega.a, sega.b) <= 0) //如果线段共线，判断是否在线段上
		return true;
	if(d2 == 0 && dot(segb.b, sega.a, sega.b) <= 0)
		return true;
	if(d3 == 0 && dot(sega.a, segb.a, segb.b) <= 0)
		return true;
	if(d4 == 0 && dot(sega.b, segb.a, segb.b) <= 0)
		return true;
	return false;
}
bool HelloWorld::inRectangle(CCPoint p, float x1, float x2, float y1, float y2) {
	return (p.x >= x1 && p.x <= x2 && p.y >= y1 && p.y <= y2);
}
void HelloWorld::swap(float* a, float* b)
{
	float tmp ;
	tmp = *a ;
	*a = *b ;
	*b = tmp ;
}
bool HelloWorld::segmentRectCollision(CCPoint leftTop, CCPoint rightBottom, _segment sega)
{
	int segCross;
	_segment segTmp ; 
	if(leftTop.x > rightBottom.x) swap(&leftTop.x, &rightBottom.x);
	if(leftTop.y < rightBottom.y) swap(&leftTop.y, &rightBottom.y);
	if(inRectangle(sega.a, leftTop.x, rightBottom.x, rightBottom.y, leftTop.y) ||
	   inRectangle(sega.b, leftTop.x, rightBottom.x, rightBottom.y, leftTop.y)) {
		return true ;
	}
	segTmp.a.x = leftTop.x;
	segTmp.a.y = leftTop.y;
	segTmp.b.x = rightBottom.x;
	segTmp.b.y = leftTop.y;
	segCross = segcrossSimple(sega, segTmp);
	if(segCross) {
		return true ;
	}
	segTmp.b.x = leftTop.x;
	segTmp.b.y = rightBottom.y;
	segCross = segcrossSimple(sega, segTmp);
	if(segCross) {
		return true ;
	}
	segTmp.a.x = rightBottom.x;
	segTmp.a.y = rightBottom.y;
	segCross = segcrossSimple(sega, segTmp);
	if(segCross) {
		return true ;
	}
	segTmp.b.x = rightBottom.x;
	segTmp.b.y = leftTop.y;
	segCross = segcrossSimple(sega, segTmp);
	if(segCross) {
		return true ;
	}
	
	return false ;
}

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
										"CloseNormal.png",
										"CloseSelected.png",
										this,
										menu_selector(HelloWorld::menuCloseCallback) );
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label
	CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// position the label on the center of the screen
	pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	pSprite->setPosition( ccp(size.width/2, size.height/2) );

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("edge.plist") ;
	
    m_pLineLayer = new DrawLines() ; 
    m_pLineLayer->init() ;
    m_pLineLayer->setTouchEnabled(true) ;
	this->addChild(m_pLineLayer, 10) ;
    
    spriteArray = CCArray::createWithCapacity(0);
    spriteArray->retain() ;
    CCLOG("%d", spriteArray->data->num) ;
    this->schedule(schedule_selector(HelloWorld::update)) ;
    
    this->schedule(schedule_selector(HelloWorld::createFruit), 0.5f) ;
	return true;
}
void HelloWorld::createFruit(float dt)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    int r = rand() % 7 + 1;
    char imageName[10] = {0}; //khong duoc xoa hai dong nay de lan sau con dung
    sprintf(imageName, "fruit%i.png", r);
    Fruit * fruitSp = new Fruit(r, 10, imageName);
    fruitSp->initWithFile(fruitSp->getName().c_str()) ;
    fruitSp->setPosition(ccp(rand()%(int)size.width, -80)) ;
    this->addChild(fruitSp, 10) ;
    CCJumpTo* jumpAction = CCJumpTo::create(3.0f, ccp(rand()%(int)size.width, -80), size.height , 1) ;
    CCRotateBy* rotateAction = CCRotateBy::create(3.0f, 360);
    
    CCHide*hideAction = CCHide::create() ;
    CCFiniteTimeAction* spawnAction = CCSpawn::create(jumpAction, rotateAction, NULL) ;
    CCFiniteTimeAction*SequenceAction = CCSequence::create(spawnAction, hideAction, NULL) ;
    
    fruitSp->runAction(SequenceAction) ;
    spriteArray->addObject(fruitSp) ;
    
    
}
CCRect getRect(CCSprite* sprite, float sc)
{
	CCRect rt = CCRectMake(sprite->getPosition().x - sprite->getContentSize().width/2,
						   sprite->getPosition().y - sprite->getContentSize().height/2,
						   sprite->getContentSize().width,
						   sprite->getContentSize().height) ;
	rt.size.width *= sc ;
	rt.size.height *= sc ;
	rt.origin.x = sprite->getPosition().x - sprite->getContentSize().width/2 ;
	rt.origin.y = sprite->getPosition().y - sprite->getContentSize().height/2 ;
	
	return rt ;
}
void HelloWorld::createDestorySprite(CCPoint pt, Fruit *sp, float angle)
{
    CCLOG("angle is %f", angle) ;
    CCLOG("angle is %f", angle/3.14*180) ;
    CCSprite *leftFruit = CCSprite::create(sp->getName().c_str()) ;
    CCSprite *rightFruit = CCSprite::create(sp->getName().c_str()) ;
    //--------left--------
    cocos2d::CCImage::EImageFormat type=cocos2d::CCImage::kFmtPng;
    CCImage *image=  new CCImage();
    
    image->initWithImageFile(sp->getName().c_str(), type);
    CCTexture2D *textture=new CCTexture2D();
    
    textture->initWithImage(image);
    
//    CCSprite *fullImage = sp;
    
    CCSprite *cutImage = CCSprite::create(sp->getName().c_str());
    
//    cutImage->setPosition(ccp(200,120));
//    cutImage->setTexture(textture);
//    cutImage->setTextureRect(CCRectMake(0,212,160,106));
    
    
    int widthFullImage = sp->getContentSize().width;
    int heightFullImage = sp->getContentSize().height;
    int withCutImage = widthFullImage/2;
    int heightCutImage = heightFullImage;
    
//    fullImage->setContentSize(CCSize(360,270));
    
    leftFruit->setTexture(textture);
    leftFruit->setTextureRect(CCRectMake(0, 0, withCutImage, heightCutImage));
    //---------right-------------
    CCImage *imageright =  new CCImage();
    
    imageright->initWithImageFile(sp->getName().c_str(), type);
    CCTexture2D *texttureright=new CCTexture2D();
    
    texttureright->initWithImage(imageright);

    rightFruit->setTexture(textture);
    rightFruit->setTextureRect(CCRectMake(withCutImage, 0, withCutImage, heightCutImage));
    //-------------------------------------
//    CCSprite *leftFruit = CCSprite::spriteWithFile("apple_left.png") ;
//    CCSprite *rightFruit = CCSprite::spriteWithFile("apple_right.png") ;
    
    leftFruit->setRotation(angle/3.14*180) ;
    rightFruit->setRotation(angle/3.14*180) ;
    leftFruit->setAnchorPoint(ccp(1.0f, 0.5f)) ;
    rightFruit->setAnchorPoint(ccp(0, 0.5f)) ;
    leftFruit->setPosition(pt) ;
    rightFruit->setPosition(pt) ;
    
    CCMoveBy*moveByLeftAction = CCMoveBy::create(0.1, ccp(-20, 10)) ;
    CCRotateBy*rotateLeftAction = CCRotateBy::create(0.5f, 300) ;
    CCMoveTo*moveToLeftAction = CCMoveTo::create(0.5f, ccp(pt.x-100, -80)) ;
    CCFiniteTimeAction* spawnLeftAction = CCSpawn::create(rotateLeftAction, moveToLeftAction, NULL) ;
    
    CCMoveBy*moveByRightAction = CCMoveBy::create(0.1, ccp(+20, 10)) ;
    CCRotateBy*rotateRightAction = CCRotateBy::create(0.5f, 360) ;
    CCMoveTo*moveToRightAction = CCMoveTo::create(0.5f, ccp(pt.x+100, -80)) ;
    CCFiniteTimeAction* spawnRightAction = CCSpawn::create(rotateRightAction, moveToRightAction, NULL) ;
    CCCallFuncN*removeAction = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::removeBreakFruit)) ;
    
    leftFruit->runAction(CCSequence::create(moveByLeftAction, spawnLeftAction, NULL)) ;
    rightFruit->runAction(CCSequence::create(moveByRightAction, spawnRightAction, removeAction, NULL)) ;
    
    this->addChild(leftFruit, 10, 99) ;
    this->addChild(rightFruit, 10, 98) ;
    
    CCParticleSystem*explodePar = CCParticleSystemQuad::create("explode.plist") ;
    explodePar->setPosition(pt) ;
    if (sp->getId() == 1) {
//        explodePar->setStartColor(ccc4FFromccc3B(ccc3(255, 250, 0)));
//        explodePar->setEndColor(ccc4FFromccc3B(ccc3(0, 250, 0)));
    }else if (sp->getId() == 2) {
        explodePar->setStartColor(ccc4FFromccc3B(ccc3(178, 34, 34)));
        explodePar->setEndColor(ccc4FFromccc3B(ccc3(178, 34, 34)));
    }else if (sp->getId() == 3) {
        explodePar->setStartColor(ccc4FFromccc3B(ccc3(210, 105, 30)));
        explodePar->setEndColor(ccc4FFromccc3B(ccc3(210, 105, 30)));
    }else if (sp->getId() == 4) {
        explodePar->setStartColor(ccc4FFromccc3B(ccc3(255, 165, 0)));
        explodePar->setEndColor(ccc4FFromccc3B(ccc3(255, 165, 0)));
    }else if (sp->getId() == 5) {
        explodePar->setStartColor(ccc4FFromccc3B(ccc3(173, 255, 147)));
        explodePar->setEndColor(ccc4FFromccc3B(ccc3(173, 255, 147)));
    }else if (sp->getId() == 6) {
        explodePar->setStartColor(ccc4FFromccc3B(ccc3(0, 205, 0)));
        explodePar->setEndColor(ccc4FFromccc3B(ccc3(0, 205, 0)));
    }else if (sp->getId() == 7) {
        explodePar->setStartColor(ccc4FFromccc3B(ccc3(255, 205, 0)));
        explodePar->setEndColor(ccc4FFromccc3B(ccc3(255, 205, 0)));
    }

    
    this->addChild(explodePar, 11, 100) ;
    
    
//    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache() ;
//	
//	CCArray *frames = new CCArray() ;
//	for (int i = 1; i <= 2; i++) {
//		//NSString *frameName = [NSString stringWithFormat:@"edge%02d.png", i] ;
//        char frameName[64] ;
//        sprintf(frameName, "edge%02d.png", i) ;
//		CCSpriteFrame *frame = cache->spriteFrameByName(frameName) ;
//		frames->addObject(frame) ;
//	}
//
//	CCSprite* spEffect = CCSprite::create("edge01.png") ;
//	CCAnimation *animation = CCAnimation::create(frames, 0.05f) ;
//	spEffect->runAction(CCSequence::create(CCAnimate::create(animation), CCHide::create(), NULL)) ;
//    spEffect->setPosition(pt) ;
//	this-> addChild(spEffect, 11, 101) ;
//	frames->removeAllObjects() ;
//	frames->release() ;
    
}   
void HelloWorld::removeBreakFruit(cocos2d::CCNode* node) 
{
    CCSprite *spL = (CCSprite*)(this->getChildByTag(99)) ;
    CCSprite *spE = (CCSprite*)(this->getChildByTag(101)) ;
    CCSprite *spR = (CCSprite*)node ;
    CCParticleSystem *par = (CCParticleSystem*)this->getChildByTag(100) ;
    
    this->removeChild(spL);
    this->removeChild(spE);
    this->removeChild(spR);
    this->removeChild(par);
    
//    spL->removeFromParentAndCleanup(true) ;
//    spE->removeFromParentAndCleanup(true) ;
//    spR->removeFromParentAndCleanup(true) ;
//    par->stopSystem() ;
//    par->removeFromParentAndCleanup(true) ;
}
void HelloWorld::update(float dt)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCObject*obj = NULL ;
    CCARRAY_FOREACH(spriteArray, obj) 
    {
        if ( !obj ) break ;
        
        Fruit *sp = (Fruit*)obj ;
        
        if ( !sp->isVisible() )
        {
            sp->removeFromParentAndCleanup(true) ;
            spriteArray->removeObject(sp) ;
            sp = NULL ;
            continue ;
        }
        CCPoint lt = getRect(sp, sp->getScale()).origin ;
        CCPoint rb = ccpAdd(getRect(sp, sp->getScale()).origin, ccp(sp->getContentSize().width*sp->getScale(), sp->getContentSize().height*sp->getScale())) ;
        _segment seg = { 
            ccp(m_pLineLayer->getTouchBeganPoint().x, m_pLineLayer->getTouchBeganPoint().y),
            ccp(m_pLineLayer->getTouchEndPoint().x, m_pLineLayer->getTouchEndPoint().y) 
        };
        if (  m_pLineLayer->getbTouched() ){
            if ( segmentRectCollision(lt, rb, seg ))
            {
                CCLOG("割到拉！！！－ －！") ;
                createDestorySprite(sp->getPosition(), sp, ccpAngle(m_pLineLayer->getTouchBeganPoint(), m_pLineLayer->getTouchEndPoint())) ;
                sp->removeFromParentAndCleanup(true) ;
                spriteArray->removeObject(sp) ;
                sp = NULL ;   
            }
        }
    }
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    this->removeAllChildrenWithCleanup(true) ;
    m_pLineLayer->release() ;
    
    spriteArray->removeAllObjects() ;
    spriteArray->release() ;
    
    
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
