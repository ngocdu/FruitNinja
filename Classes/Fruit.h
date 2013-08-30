//
//  Fruit.h
//  Effect_Game_01
//
//  Created by MinhNT on 13/08/28.
//  Copyright (c) 2013年 chukong-inc. All rights reserved.
//

#ifndef Effect_Game_01_Fruit_h
#define Effect_Game_01_Fruit_h
#include "cocos2d.h"
#include <string.h>
#include "SimpleAudioEngine.h"
using namespace std;
class Fruit : public cocos2d::CCSprite
{
private:
	CC_SYNTHESIZE(int, _point, Point);
    CC_SYNTHESIZE(string, _name, Name);
    CC_SYNTHESIZE(int, _id, Id);
    CC_SYNTHESIZE(float, _timeAction, TimeAction);
    /* 
     0 - normal
     1 - fruit point
     2 - fruit time
     */
    CC_SYNTHESIZE(int, _catagoryFruit, CatagoryFruit);
public:
	Fruit();
	Fruit(int _id, int point, string name);// ham tao co doi so
};



#endif
