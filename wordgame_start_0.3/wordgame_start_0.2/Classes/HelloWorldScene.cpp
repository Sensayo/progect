#include "HelloWorldScene.h"

USING_NS_CC;

#define LABEL_FONTNAME "fonts/Marker Felt.ttf"
#define LABEL_FONTSIZE 24
#define TASK_COLLISION_BITMASK 0x000001
#define BOARD_COLLISION_BITMASK 0x000002


Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_CONTACT);
    auto layer = HelloWorld::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	Label * lbEnd = Label::createWithTTF("Hello Player", LABEL_FONTNAME, 3 * LABEL_FONTSIZE);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 pos = Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + 60);

	auto backgroundSprite = Sprite::create("Background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	lbEnd->setPosition(pos);
	this->addChild(lbEnd);

	auto replayItem = MenuItemImage::create("BeginNormal.png",
		"BeginSelected.png",
		CC_CALLBACK_1(HelloWorld::menuSetCallback, this));
	replayItem->setPosition(Vec2(pos.x,
		pos.y - lbEnd->getContentSize().height - 10));

	auto menu = Menu::create(replayItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

    return true;
}

bool HelloWorld::onCollisionContact(PhysicsContact &_contact)
{
	PhysicsBody*a = _contact.getShapeA()->getBody();
	PhysicsBody*b = _contact.getShapeB()->getBody();

	if ((TASK_COLLISION_BITMASK==a->getCollisionBitmask()&& BOARD_COLLISION_BITMASK==b->getCollisionBitmask())
		|| (TASK_COLLISION_BITMASK == b->getCollisionBitmask() && BOARD_COLLISION_BITMASK == a->getCollisionBitmask()))
	{
		showAnswer();
		if (healthPointMinus() == 0)
		{
			b->removeFromWorld();
			scheduleOnce(schedule_selector(HelloWorld::showEnd), 1);
		}
		else
		{
			b->removeFromWorld();
			scheduleOnce(schedule_selector(HelloWorld::updateTask), 1);
		}
	}
	return true;
}

Label *HelloWorld::CreateTextLabel(char*text, char*fontname, int fontsize, Vec2 pos) 
{
	Label*label = Label::createWithTTF(text, fontname, fontsize);
	label->setPosition(pos);
	this->addChild(label, 1, "text_label");
	return label;
}

void HelloWorld::setPhysicsWorld(PhysicsWorld * _world)
{
	m_sceneWorld = _world;
}

void HelloWorld::setTaskLabel()
{
	auto taskBody = PhysicsBody::createBox( Size(m_taskLabel->getContentSize().width*4, m_taskLabel->getContentSize().height));
	taskBody->setCollisionBitmask(TASK_COLLISION_BITMASK);
	taskBody->setContactTestBitmask(true);
	m_taskLabel->setPhysicsBody(taskBody);
}

void HelloWorld::keyPressed(EventKeyboard::KeyCode keycode, Event*event) {
	if (m_task.isKeyCorrect(keycode)) 
	{
		showAnswer();
		m_taskLabel->removeFromPhysicsWorld();
		addScore(SCORE_CHANGE);
		scheduleOnce(schedule_selector(HelloWorld::updateTask), 1);

	}
	else
	{
		showAnswer();
		m_taskLabel->removeFromPhysicsWorld();
		if(healthPointMinus()==0)
			scheduleOnce(schedule_selector(HelloWorld::showEnd), 1);
		else
			scheduleOnce(schedule_selector(HelloWorld::updateTask), 1);
	}
	switch(keycode){
	case EventKeyboard::KeyCode::KEY_ESCAPE: exit(0); break;
	default: break;
	}
}

void HelloWorld::showAnswer() {
	m_taskLabel->setString(m_task.getAnswer());
	m_taskLabel->stopAllActions();
}

void HelloWorld::addScore(int s)
{
	setScore(m_score + s);
	if (m_score == 60)
	{
		scheduleOnce(schedule_selector(HelloWorld::showWin), 1);
	}
}

void HelloWorld::setScore(int s)
{
	m_score = s;
	m_scoreLabel->setString("Count:"+std::to_string (m_score));
}

void HelloWorld::setHealth()
{
	m_health = HEALTH_POINTS;
	for (int i = 0; i < m_health; i++)
	{
		m_healthIndicator[i]->setOpacity(255);
	}
}

void HelloWorld::createEndScene()
{
	m_Scene = Scene::create();

	Label * lbEnd = Label::createWithTTF("End", LABEL_FONTNAME, 3 * LABEL_FONTSIZE);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 pos = Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2+60 );

	auto backgroundSprite = Sprite::create("Background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	m_Scene->addChild(backgroundSprite);

	lbEnd->setPosition(pos);
	m_Scene->addChild(lbEnd);

	auto replayItem = MenuItemImage::create("ContinueNormal.png",
		"ContinueSelected.png",
		CC_CALLBACK_1(HelloWorld::menuReplayCallback, this));
	replayItem->setPosition(Vec2(pos.x,
		pos.y-lbEnd->getContentSize().height-10));

	auto menu = Menu::create(replayItem, NULL);
	menu->setPosition(Vec2::ZERO);
	m_Scene->addChild(menu,1);
}

void HelloWorld::createWinScene()
{
	m_Scene = Scene::create();

	Label * lbEnd = Label::createWithTTF("YOU WIN", LABEL_FONTNAME, 3 * LABEL_FONTSIZE);
	lbEnd->setColor(Color3B(140, 0, 140));
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 pos = Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + 60);

	auto backgroundSprite = Sprite::create("Background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	m_Scene->addChild(backgroundSprite);

	lbEnd->setPosition(pos);
	m_Scene->addChild(lbEnd);

	auto replayItem = MenuItemImage::create("ContinueNormal.png",
		"ContinueSelected.png",
		CC_CALLBACK_1(HelloWorld::menuReplayCallback, this));
	replayItem->setPosition(Vec2(pos.x,
		pos.y - lbEnd->getContentSize().height - 10));

	auto menu = Menu::create(replayItem, NULL);
	menu->setPosition(Vec2::ZERO);
	m_Scene->addChild(menu, 1);
}

void HelloWorld::createGameScene()
{
	this->removeAllChildren();

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	auto backgroundSprite = Sprite::create("Background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(BOARD_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);

	m_taskManager.init();
	Vec2 health_pos = Vec2(origin.x + visibleSize.width*0.8, origin.y + visibleSize.height*0.9);

	m_taskLabel = CreateTextLabel("hi", LABEL_FONTNAME, LABEL_FONTSIZE, Vec2(0, 0));

	updateTask(0);
	for (int i = 0; i < 3; i++)
	{
		m_healthIndicator[i] = CreateHealthPicture(Vec2(origin.x + visibleSize.width*0.8 + (i * 20), origin.y + visibleSize.height*0.9), 3.0);
	}

	m_scoreLabel = CreateTextLabel("Count: 0", LABEL_FONTNAME, LABEL_FONTSIZE,
		Vec2(origin.x + visibleSize.width*0.1, origin.y + visibleSize.height*0.9));
	setScore(0);

	/////////////////////////////////////////////////
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::keyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onCollisionContact, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

}

void HelloWorld::showEnd(float dt)
{
	createEndScene();
	Director::getInstance()->pushScene(m_Scene);
}

void HelloWorld::showWin(float)
{
	createWinScene();
	Director::getInstance()->pushScene(m_Scene);
}

void HelloWorld::menuSetCallback(Ref*pSender)
{
	createGameScene();
}

void HelloWorld::menuReplayCallback(Ref*pSender)
{
	Director::getInstance()->popScene();
	m_taskManager.setRandomTasks();
	m_taskManager.setCurrentTaskToNull();
	setHealth();
	setScore(0);
	updateTask(0);
}

int HelloWorld::healthPointMinus()
{
	m_health -= 1;
	if (m_health > 0)
	{
		m_healthIndicator[m_health]->setOpacity(30);
		return 1;
	}
	else if(m_health==0)
	{
		m_healthIndicator[m_health]->setOpacity(30);
		return 0;
	}
	else return 0;
}

void HelloWorld::updateTask(float _dt)
{
	m_task = m_taskManager.getRandTask();
	m_taskLabel->setString(m_task.getTask());
	//////////////////////////////////////////
	setTaskLabel();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 task_pos = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 20);

	m_taskLabel->setPosition(task_pos);
	m_taskLabel->setScale(1);
	//////////////////////////////////////////
}

Sprite *HelloWorld::CreateHealthPicture(Vec2 pos, float scale) 
{
	auto healthIndicator = Sprite::create("heart.png");
	healthIndicator->setPosition(pos);
	healthIndicator->setScale(scale);
	this->addChild(healthIndicator);
	return healthIndicator;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
