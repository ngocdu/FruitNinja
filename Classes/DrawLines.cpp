//
//  DrawLines.cpp
//  Effect_Game_01
//
//  Created by Eddy on 12-3-28.
//  Copyright home 2012年. All rights reserved.
//
#include "GameManager.h"
#include "DrawLines.h"
#include "SimpleAudioEngine.h"
//#include <OpenGLES/ES1/gl.h>
using namespace cocos2d ;

DrawLines::DrawLines()
{
    CCLayerColor::initWithColor(ccc4(0, 0, 0, 255));
}
DrawLines::~DrawLines()
{
    
}
bool DrawLines::init()
{
    bool bRet = false;
    do {
        m_pParticle = CCParticleSystemQuad::create("Particle.plist") ;
        this->addChild(m_pParticle, 10) ;
        m_pParticle->setVisible(false) ;
        memset(m_pointPath, 0, sizeof(m_pointPath)) ;
        m_timer = 0 ;
        m_touchBeganPoint = m_touchEndPoint = ccp(0, 0) ;
        bRet = true ;
    } while (0);
    return true ;
}
void DrawLines::line()
{
    if (m_Index<3 || m_Index > 1024) {
		return;
	}
	CCPoint *p = m_pointPath ;
	//CCPoint vertexMiddle[1024]={ccp(0.0, 0.0)};
    CCPoint *vertexMiddle = new CCPoint[m_Index] ;
	//memset(vertexMiddle, 0, sizeof(vertexMiddle)) ;
	memcpy(vertexMiddle, p, sizeof(CCPoint)*m_Index);
	
	CCPoint pt = ccpSub(p[m_Index-1], p[m_Index-2]);
	GLfloat angle = ccpToAngle(pt);
	vertexMiddle[m_Index-1].x += cosf(angle)*10*CC_CONTENT_SCALE_FACTOR();
	vertexMiddle[m_Index-1].y += sinf(angle)*10*CC_CONTENT_SCALE_FACTOR();
    
	CCPoint vertexTop[1024]={ccp(0.0, 0.0)};
	
	vertexTop[0].x = p[m_Index-1].x + cosf(angle)*10*CC_CONTENT_SCALE_FACTOR();
	vertexTop[0].y = p[m_Index-1].y + sinf(angle)*10*CC_CONTENT_SCALE_FACTOR();
	
	GLint count1 = 1;
	
	for (int i = (m_Index-2); i>0; --i) {
		float w = i*0.5f ;
		if (w < 3)w = 3 ;
		else if(w > 8)w = 8 ;
		triangle(&(vertexTop[count1]),p[i],p[i-1], w);
		count1++;
	}
	vertexTop[count1++] = p[0];
    
	CCPoint vertexBottom[1024]={ccp(0.0, 0.0)};
	
	vertexBottom[0].x = p[m_Index-1].x + cosf(angle)*10*CC_CONTENT_SCALE_FACTOR();
	vertexBottom[0].y = p[m_Index-1].y + sinf(angle)*10*CC_CONTENT_SCALE_FACTOR();
	
	GLint count2 = 1;
	
	for (int i = (m_Index-2); i>0; --i) {
		float w = i*0.5f ;
		if (w < 3)w = 3 ;
		else if(w > 8)w =8 ;
		triangle(&(vertexBottom[count2]),p[i],p[i-1], -w);
		count2++;
	}
	vertexBottom[count2++] = p[0];
	
	CCPoint vertexTriangle[512] ={ccp(0.0, 0.0)} ;
	CCPoint*vertexCpy = vertexTriangle;
	GLubyte lineColors[1024] = {0,133,234,0};
	GLubyte *lineCpy = lineColors ;
	//1
	*vertexCpy = vertexMiddle[m_Index-1] ;
	*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
	vertexCpy++ ;
	
	*vertexCpy = vertexMiddle[m_Index-2] ;
	*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
	vertexCpy++ ;
	
	*vertexCpy = vertexTop[1] ;
	*lineCpy = TOP_POINT_R; lineCpy++ ;
	*lineCpy = TOP_POINT_G; lineCpy++ ;
	*lineCpy = TOP_POINT_B; lineCpy++ ;
	*lineCpy = TOP_POINT_A; lineCpy++ ;
	vertexCpy++ ;
	
	*vertexCpy = vertexMiddle[m_Index-1] ;
	*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
	vertexCpy++ ;
	*vertexCpy = vertexBottom[1] ;
	*lineCpy = BOTTOM_POINT_R; lineCpy++ ;
	*lineCpy = BOTTOM_POINT_G; lineCpy++ ;
	*lineCpy = BOTTOM_POINT_B; lineCpy++ ;
	*lineCpy = BOTTOM_POINT_A; lineCpy++ ;
	vertexCpy++ ;
	*vertexCpy = vertexMiddle[m_Index-2] ;
	*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
	*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
	vertexCpy++ ;
	
	for (int i = 0; i < m_Index-2; i++) {
		//上半个四边形 - Trên một nửa vuông
		*vertexCpy = vertexMiddle[m_Index-(i+2)] ;
		*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexMiddle[m_Index-(i+3)] ;
		*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexTop[i+1] ;
		*lineCpy = TOP_POINT_R; lineCpy++ ;
		*lineCpy = TOP_POINT_G; lineCpy++ ;
		*lineCpy = TOP_POINT_B; lineCpy++ ;
		*lineCpy = TOP_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		
		*vertexCpy = vertexTop[i+1] ;
		*lineCpy = TOP_POINT_R; lineCpy++ ;
		*lineCpy = TOP_POINT_G; lineCpy++ ;
		*lineCpy = TOP_POINT_B; lineCpy++ ;
		*lineCpy = TOP_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexMiddle[m_Index-(i+3)] ;
		*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexTop[i+2] ;
		*lineCpy = TOP_POINT_R; lineCpy++ ;
		*lineCpy = TOP_POINT_G; lineCpy++ ;
		*lineCpy = TOP_POINT_B; lineCpy++ ;
		*lineCpy = TOP_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		
		//下半个四边形 - Một nửa vuông
		*vertexCpy = vertexBottom[i+1] ;
		*lineCpy = BOTTOM_POINT_R; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_G; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_B; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexBottom[i+2] ;
		*lineCpy = BOTTOM_POINT_R; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_G; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_B; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexMiddle[m_Index-(i+2)] ;
		*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		
		*vertexCpy = vertexMiddle[m_Index-(i+2)] ;
		*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexBottom[i+2] ;
		*lineCpy = BOTTOM_POINT_R; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_G; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_B; lineCpy++ ;
		*lineCpy = BOTTOM_POINT_A; lineCpy++ ;
		vertexCpy++ ;
		*vertexCpy = vertexMiddle[m_Index-(i+3)] ;
		*lineCpy = MIDDLE_POINT_R; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_G; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_B; lineCpy++ ;
		*lineCpy = MIDDLE_POINT_A; lineCpy++ ;
		vertexCpy++ ;
	}
    CC_NODE_DRAW_SETUP();
//    ccGLEnableVertexAttribs( kCCVertexAttrib_Position );
//    ccGLEnableVertexAttribs( kCCVertexAttrib_Color );
	kmGLPushMatrix();
    ccGLBlendFunc( CC_BLEND_SRC, CC_BLEND_DST );
    ccGLBindTexture2D(GL_TEXTURE_2D);
//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_SRC_COLOR);
	
//	glVertexPointer(2, GL_FLOAT, 0, vertexTriangle);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, sizeof(vertexTriangle[0]), vertexTriangle);
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glColorPointer(kCCVertexAttrib_Color, GL_UNSIGNED_BYTE, 0, lineColors);
    glVertexAttribPointer(kCCVertexAttrib_Color, GL_UNSIGNED_BYTE, 0, GL_FALSE, sizeof(lineColors[0]), lineColors);
//	glEnableClientState(GL_COLOR_ARRAY);
    glEnable(GL_SRC_COLOR);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLint)((vertexCpy-vertexTriangle-1)));
    
//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_ONE_MINUS_SRC_COLOR);
    kmGLPopMatrix();
    
    delete [] vertexMiddle ;
}
void DrawLines::erasureNail()
{
    if ( m_Index < 3 || m_Index > 1024)
        return ;
    
    CCPoint*p = m_pointPath ;
    m_Index-- ;
    memmove(p, &(p[1]), sizeof(CCPoint)*(m_Index)) ;
}
void DrawLines::draw()
{
    this->getParent()->draw();
    long dt = time(NULL) ;
    
    if ( m_timer > 100 )
    {
        m_timer = 0 ;
        erasureNail() ;
    }
    else {
        m_timer += dt ;
    }
    
    line() ;
}
void DrawLines::triangle(CCPoint* vertex, CCPoint p1, CCPoint p2, GLfloat w)
{
    CCPoint pt = ccpSub(p1, p2);
	GLfloat angle = ccpToAngle(pt);
	
	GLfloat x = sinf(angle) * w;
	GLfloat y = cosf(angle) * w;
	vertex->x = p1.x+x;
	vertex->y = p1.y-y;
}
void DrawLines::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    CCTouch*touch = (CCTouch*)touches->anyObject() ;
    CCPoint touchPoint = touch->getLocationInView() ;
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint) ;
    m_touchEndPoint = m_touchBeganPoint = touchPoint ;
	
	m_bTouched = true ;
	m_Index = 0 ;
	m_pointPath[m_Index++] = ccpMult(touchPoint, CC_CONTENT_SCALE_FACTOR())  ;
	m_pParticle->resetSystem() ;
	m_pParticle->setPosition(touchPoint) ;
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("smallcut.mp3");
}
void DrawLines::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    CCTouch*touch = (CCTouch*)touches->anyObject() ;
    m_touchBeganPoint = touch->getLocationInView() ;
    m_touchBeganPoint = CCDirector::sharedDirector()->convertToGL(m_touchBeganPoint) ;
    
    m_touchEndPoint = touch->getPreviousLocationInView() ;
    m_touchEndPoint = CCDirector::sharedDirector()->convertToGL(m_touchEndPoint) ;
    
    m_bTouched = true ;
    m_pParticle->setVisible(true) ;
    m_pParticle->setPosition(m_touchBeganPoint) ;
    
    CCPoint pointTmp = ccpMult(m_touchBeganPoint, CC_CONTENT_SCALE_FACTOR());
	float distance = ccpDistance(pointTmp, m_pointPath[m_Index]) ;
	if ( distance < 5  )return ;
	if ( m_Index < POINT_NUM )
	{
		m_pointPath[m_Index++] = pointTmp ;
	}
	else {
		memmove(m_pointPath, &m_pointPath[1], sizeof(CCPoint)*(POINT_NUM-1)) ;
		m_pointPath[m_Index-1] = pointTmp ;
        int pnow = GameManager::sharedGameManager()->getPointNow();
        int ptotal = GameManager::sharedGameManager()->getPointTotal();
        GameManager::sharedGameManager()->setPointTotal(ptotal + pnow);
        GameManager::sharedGameManager()->setPointNow(0);
        if (pnow >= 3) {
            GameManager::sharedGameManager()->setHit(pnow);
        }
	}
}
void DrawLines::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCTouch*touch = (CCTouch*)touches->anyObject() ;
    CCPoint touchPoint = touch->getLocationInView() ;
    touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint) ;
	m_bTouched = false ;
	m_touchEndPoint = touchPoint ;
	m_pParticle->stopSystem() ;
    
    int pnow = GameManager::sharedGameManager()->getPointNow();
    int ptotal = GameManager::sharedGameManager()->getPointTotal();
    GameManager::sharedGameManager()->setPointTotal(ptotal + pnow);
    GameManager::sharedGameManager()->setPointNow(0);
    if (pnow >= 3) {
        GameManager::sharedGameManager()->setHit(pnow);
    }  
}
