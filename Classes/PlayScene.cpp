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
 * PlayScene.cpp
 *
 *  Created on: 2015/09/14
 *      Author: tamura shingo
 */


#include "PlayScene.h"
#include "GameOverScene.h"

USING_NS_CC;

PlayScene::PlayScene() :
        postkun(new PostKun()), characterLayer(nullptr),
        scoreLabel(nullptr), counter(0),
        score(0), jumped(false),
        listener(nullptr)
{
    postkun->init();
}

PlayScene::~PlayScene()
{
    delete postkun;
}

cocos2d::Scene* PlayScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PlayScene::create();
    scene->addChild(layer);

    return scene;
}

bool PlayScene::init()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto bg = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
    this->addChild(bg);

    characterLayer = CharLayer::create();
    characterLayer->setPosition(0, 0);
    characterLayer->setPostKun(postkun);
    this->addChild(characterLayer, 0);

    characterLayer->enterFrame(0);

    scoreLabel = Label::createWithTTF("", "fonts/arial.ttf", 12);
    scoreLabel->setColor(Color3B::BLACK);
    scoreLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
    scoreLabel->setPosition(2, visibleSize.height);
    this->addChild(scoreLabel);

    this->scheduleOnce(schedule_selector(PlayScene::readyThree), 0.8f);
    this->scheduleOnce(schedule_selector(PlayScene::readyTwo),   1.6f);
    this->scheduleOnce(schedule_selector(PlayScene::readyOne),   2.4f);
    this->scheduleOnce(schedule_selector(PlayScene::readyStart), 3.2f);
    this->scheduleOnce(schedule_selector(PlayScene::start),      4.0f);

    listener = EventListenerTouchOneByOne::create();
    listener->setEnabled(false);
    listener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    characterLayer->setVisible(true);

    return true;
}

bool PlayScene::onTouchBegan(Touch* touch, Event* event)
{
    postkun->jump();
    return true;
}

void PlayScene::readyThree(float frame)
{
    scoreLabel->setString("3...");
}

void PlayScene::readyTwo(float frame)
{
    scoreLabel->setString("2...");
}

void PlayScene::readyOne(float frame)
{
    scoreLabel->setString("1...");
}

void PlayScene::readyStart(float frame)
{
    scoreLabel->setString("start!");
}

void PlayScene::start(float frame)
{
    scoreLabel->setString("score:0");
    jumped = false;
    this->scheduleUpdate();
    listener->setEnabled(true);
}

void PlayScene::update(float delta)
{
    counter += 1;
    if (counter == 14) {
        counter = 0;
        jumped = false;
    }
    if (counter % 2 == 1) {
        characterLayer->enterFrame(counter / 2);
    }
    if ((!jumped && counter == 12 && postkun->isJump)
            || (!jumped && counter == 13 && postkun->isJump)) {
        jumped = true;
        score++;
        auto str = StringUtils::format("score:%d", score);
        scoreLabel->setString(str);
    }

    if (!jumped && counter == 13) {
        // over
        auto scene = GameOverScene::createScene();
        auto over = (GameOverScene*)scene->getChildByName("GameOverLayer");
        over->setScore(score);
        Director::getInstance()->replaceScene(scene);
    }
}
