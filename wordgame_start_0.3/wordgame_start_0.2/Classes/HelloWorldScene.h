#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"
#include "WordTask.h"
#include "TaskManager.h"

#define SCORE_CHANGE 10
#define HEALTH_POINTS 3

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:

	void updateTask(float);
	void initPoseMove();

public:
    
	Scene*m_Scene;

	int m_health = HEALTH_POINTS;
	int m_score;

	Label*m_taskLabel;
	Label*m_scoreLabel;

	WordTask m_task;
	TaskManager m_taskManager;
	PhysicsWorld *m_sceneWorld;

	Vec2 origin;
	Size visibleSize;

	Sprite *m_healthIndicator[HEALTH_POINTS];

	//////////////////////////////////////////	

	static cocos2d::Scene* createScene();
	virtual bool init();
	bool onCollisionContact(PhysicsContact&);

	Label *CreateTextLabel(char*text, char*ff, int fsize, Vec2 pos);
	Sprite *CreateHealthPicture(Vec2 pos, float scale);

	int healthPointMinus();

	void addScore(int);
	void createGameScene();
	void createEndScene();
	void createWinScene();
	void keyPressed(EventKeyboard::KeyCode keycode, Event*event);
	void menuSetCallback(Ref*);
	void menuReplayCallback(Ref*);
	void menuCloseCallback(cocos2d::Ref* pSender);

	void setPhysicsWorld(PhysicsWorld *);
	void setTaskLabel();
	void setHealth();
	void setScore(int);
	void showAnswer();
	void showEnd(float);
	void showWin(float);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
