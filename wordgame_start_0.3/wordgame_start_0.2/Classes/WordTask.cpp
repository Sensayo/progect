#include "WordTask.h"

WordTask::WordTask()
{
}


WordTask::~WordTask()
{
}

int WordTask::init(char* _task, char *_answer, char _key)
{
	if (_task != nullptr&&_answer != nullptr) {
		this->setTask(_task);
		this->setAnswer(_answer);
	}

	this->setKey(_key);
	return 0;
}

bool WordTask::isKeyCorrect(EventKeyboard::KeyCode keyCode)
{
	if ((EventKeyboard::KeyCode)(this->m_key + KEYCODE_OFFSET) == keyCode)
		return true;
	return false;
}

int WordTask::setKey(char _key)
{
	if (_key >= 97&&_key<=147)
		this->m_key = _key;
	return 0;
}

int WordTask::setTask(char *_task)
{
	if (_task != nullptr)
		this->m_task = _task;
	return 0;
}

int WordTask::setAnswer(char * _ans)
{
	if (_ans != nullptr)
		this->m_answer = _ans;
	return 0;
}
