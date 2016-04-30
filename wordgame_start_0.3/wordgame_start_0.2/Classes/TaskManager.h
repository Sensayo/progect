#ifndef _TASKMANAGER_H_
#define _TASKMANAGER_H_

#pragma once
#include "WordTask.h"

class TaskManager
{
	WordTask*m_listOfTasks;
	int m_numTasks;
	int m_currentTask;
	int*m_randTask;


public:
	TaskManager();
	~TaskManager();

	int getNumTasks();
	void setNumTasks(int);
	void setCurrentTaskToNull();
	void init();
	void setRandomTasks();
	WordTask getTask(int);
	WordTask getRandTask();
};
#endif

