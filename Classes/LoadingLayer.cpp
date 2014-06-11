#include "LoadingLayer.h"
USING_NS_CC;
bool LoadingLayer::init()
{
    bool isRet = false;
    do{
	CC_BREAK_IF(!BaseLayer::init());
	CC_BREAK_IF(!this->setUpdateView());
	CCTextureCache::sharedTextureCache()->addImageAsync("gmbg/loading.png", this, callfuncO_selector(LoadingLayer::loadCallBack));
	isRet = true;
    }while(0);
    return isRet;
}

CCScene* LoadingLayer::scene()
{
    CCScene* scene = CCScene::create();
    LoadingLayer* layer = LoadingLayer::create();
    scene->addChild(layer);
    return scene;
}

void LoadingLayer::loadCallBack(CCObject* ped)
{
    loadingNum++;
    CCProgressTimer* pt = (CCProgressTimer*)this->getChildByTag(1);
    //float now = pt->getPercentage();
    pt->setPercentage(loadingNum/totalNum);
    if(loadingNum < totalNum){
	CCLOG("loading...");
    }else{
	CCLOG("loading over");
    }
}

LoadingLayer::LoadingLayer()
{
    this->loadingNum = 0;
    this->totalNum = 100;
}

bool LoadingLayer::setUpdateView()
{
    bool isRet = false;
    do{
	CCSprite* loadingbackimg = CCSprite::create("gmbg/loadingbg.png");
	CC_BREAK_IF(!loadingbackimg);
	loadingbackimg->setPosition(ccp(getWinSize().width/2 + getWinOrigin().x, getWinSize().height/5 + getWinOrigin().y));
	this->addChild(loadingbackimg, 1);

	CCSprite* loadimg = CCSprite::create("gmbg/loading.png");
	CC_BREAK_IF(!loadimg);
	CCProgressTimer* pt = CCProgressTimer::create(loadimg);
	pt->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeBar));
	pt->setMidpoint(ccp(0,0.5));
	pt->setBarChangeRate(ccp(1,0));
	float tex = getWinSize().width/2 + getWinOrigin().x;
	float tey = getWinSize().height/5 + getWinOrigin().y-5;
	pt->setPosition(ccp(tex, tey));
	pt->setPercentage(0);
	this->addChild(pt, 2, 1);
	CCProgressTo* to = CCProgressTo::create(5, 100);
	pt->runAction(CCRepeatForever::create(to));
	isRet = true;
	
    }while(0);
    return isRet;
}
