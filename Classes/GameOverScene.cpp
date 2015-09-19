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

/*
 * GameOverScene.cpp
 *
 *  Created on: 2015/09/14
 *      Author: tamura shingo
 */

#include "GameOverScene.h"
#include "PlayScene.h"
#include "PostKunConstants.h"

USING_NS_CC;

GameOverScene::GameOverScene() :
        score(0)
{
}

GameOverScene::~GameOverScene()
{
}

cocos2d::Scene* GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer, 0, "GameOverLayer");

    return scene;
}

bool GameOverScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto bg = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
    this->addChild(bg);

    auto sprite = Sprite::create("post.png");
    sprite->setPosition(PostKunConstants::CENTER_X, PostKunConstants::CENTER_Y);
    sprite->setRotation(-20);
    this->addChild(sprite);

    this->scheduleOnce(schedule_selector(GameOverScene::doQuit), 1.5f);

    return true;
}

void GameOverScene::setScore(int score)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto str = StringUtils::format("score:%d", score);
    auto scoreLabel = Label::createWithTTF(str, "fonts/arial.ttf", 12);
    scoreLabel->setColor(Color3B::BLACK);
    scoreLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
    scoreLabel->setPosition(2, visibleSize.height);
    this->addChild(scoreLabel);
}

void GameOverScene::doQuit(float frame)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto replayLabel = Label::createWithTTF("replay?", "fonts/arial.ttf", 12);
    replayLabel->setColor(Color3B::BLACK);
    replayLabel->setAnchorPoint(Vec2(1.0f, 0.0f));
    replayLabel->setPosition(Point(visibleSize.width - 2, 8));
    this->addChild(replayLabel);

    auto replayListener = EventListenerTouchOneByOne::create();
    replayListener->setSwallowTouches(true);
    replayListener->onTouchBegan = [](Touch* touch, Event* event) {
        auto target = event->getCurrentTarget();
        auto targetBox = target->getBoundingBox();
        auto touchPoint = Vec2(touch->getLocation().x, touch->getLocation().y);

        if (targetBox.containsPoint(touchPoint)) {
            return true;
        }

        return false;
    };
    replayListener->onTouchEnded = [](Touch* touch, Event* event) {
        auto scene = PlayScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK));
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(replayListener, replayLabel);

    auto exitLabel = Label::createWithTTF("exit", "fonts/arial.ttf", 12);
    exitLabel->setColor(Color3B::BLACK);
    exitLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    exitLabel->setPosition(Point(2, 8));
    this->addChild(exitLabel);

    auto exitListener = EventListenerTouchOneByOne::create();
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
}

