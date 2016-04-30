#ifndef _WORDTASK_H_
#define _WORDTASK_H_

#pragma once
#include "cocos2d.h"
#pragma once
using namespace cocos2d;

#define KEYCODE_OFFSET 27

class WordTask
{
private:
	std::string m_task;
	std::string m_answer;
	char m_key;

public:
	WordTask();
	~WordTask();

	int init(char*, char*, char);
	bool isKeyCorrect(EventKeyboard::KeyCode keyCode);

	char getKey() { return m_key; };
	const char* getTask() { return m_task.c_str(); };
	const char*getAnswer() { return m_answer.c_str(); };

	int setKey(char);
	int setTask(char*);
	int setAnswer(char*);
};

#endif // !_WORDTASK_H_

