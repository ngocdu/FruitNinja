#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "DrawLines.h"
#include "Fruit.h"
typedef struct segment {
    cocos2d::CCPoint a, b ;
} _segment;
using namespace cocos2d;
class HelloWorld : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
    
    void update(float dt) ;
    void updateTime(float dt);
    void createFruit(float dt) ;
    
    cocos2d::CCArray *spriteArray ;
    void slowAction(float dt);
	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);
protected:
    cocos2d::DrawLines* m_pLineLayer ;
private:
    void removeBreakFruit(cocos2d::CCNode* node) ;
    float cross(cocos2d::CCPoint a, cocos2d::CCPoint b, cocos2d::CCPoint c) ;
    float dot(cocos2d::CCPoint a, cocos2d::CCPoint b, cocos2d::CCPoint c);
    bool segcrossSimple(_segment sega, _segment segb);
    bool inRectangle(cocos2d::CCPoint p, float x1, float x2, float y1, float y2);
    void swap(float* a, float* b);
    bool segmentRectCollision(cocos2d::CCPoint leftTop, cocos2d::CCPoint rightBottom, _segment sega);
    void createDestorySprite(cocos2d::CCPoint pt,Fruit *fr, float angle) ;
    //-------------point----------------------
    CCSize size;
    int time;
    int timeDelay;
};

#endif // __HELLOWORLD_SCENE_H__
