/*-
 * PostKun - Cocos2d-x version
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2002, 2013, 2015 tamura shingo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "DemoScene.h"
#include "CharLayer.h"
#include "PlayScene.h"

USING_NS_CC;

DemoScene::DemoScene() :
        postkun(new PostKun()), characterLayer(nullptr), counter(0)
{
    postkun->init();
}

DemoScene::~DemoScene()
{
    delete postkun;
}

cocos2d::Scene* DemoScene::createScene()
{
    auto scene = Scene::create();
    auto layer = DemoScene::create();
    scene->addChild(layer);

    return scene;
}

bool DemoScene::init()
{
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
    this->addChild(bg);
  
    characterLayer = CharLayer::create();
    characterLayer->setPosition(0, 0);
    characterLayer->setPostKun(postkun);
    this->addChild(characterLayer, 0);

    characterLayer->enterFrame(0);
    characterLayer->setVisible(true);

    auto label = Label::createWithTTF("PostKun", "fonts/arial.ttf", 16);
    label->setColor(Color3B::BLACK);
    label->setAnchorPoint(Vec2(0.5f, 1.0f));
    label->setPosition(Point(visibleSize.width / 2, visibleSize.height - 8));
    this->addChild(label, 1);

    auto exitLabel = Label::createWithTTF("exit", "fonts/arial.ttf", 16);
    exitLabel->setColor(Color3B::BLACK);
    exitLabel->setAnchorPoint(Vec2::ZERO);
    exitLabel->setPosition(Point(2, 18));
    this->addChild(exitLabel);

    auto exitListener = EventListenerTouchOneByOne::create();
    exitListener->setSwallowTouches(true);
    exitListener->onTouchBegan = [](Touch* touch, Event* event) {
        auto target = event->getCurrentTarget();
        auto targetBox = target->getBoundingBox();
        auto touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);

        if (targetBox.containsPoint(touchPoint)) {
            return true;
        }

        return false;
    };
    exitListener->onTouchEnded = [](Touch* touch, Event* event) {
        Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(exitListener, exitLabel);

    auto startListener = EventListenerTouchOneByOne::create();
    startListener->setSwallowTouches(true);
    startListener->onTouchBegan = [](Touch* touch, Event* evnet) {
        return true;
    };
    startListener->onTouchEnded = [](Touch* touch, Event* event) {
        auto scene = PlayScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK));
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(startListener, characterLayer);

    this->scheduleUpdate();

    return true;
}

void DemoScene::update(float delta)
{
    counter += 1;
    if (counter == 6) {
        counter = 0;
    }
    else if (counter == 5) {
        postkun->jump();
    }
    characterLayer->enterFrame(counter);
}

