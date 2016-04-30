#include "TaskManager.h"
#include <array>


TaskManager::TaskManager()
{
	m_listOfTasks = NULL;
	m_randTask = NULL;
	m_numTasks = 0;
	m_currentTask = -1;
}


TaskManager::~TaskManager()
{
	delete[] m_listOfTasks;
	delete[] m_randTask;
	m_randTask = NULL;
	m_listOfTasks = NULL;
}

int TaskManager::getNumTasks()
{
	return m_numTasks;
}

void TaskManager::setNumTasks(int _num)
{
	if(_num>0)
		m_numTasks = _num;
}

void TaskManager::setCurrentTaskToNull()
{
	m_currentTask = -1;
}

void TaskManager::init()
{
	int numTasks;

	FILE*pFile = fopen("..\\Resources\\task.txt", "r");
	fscanf(pFile, "Num: %d;", &numTasks);
	m_numTasks = numTasks;
	m_listOfTasks = new WordTask[numTasks];
	char task[20];
	char ans[20];
	char key[20];

	for (int i = 0; i < numTasks; i++)
	{

		fscanf(pFile, "%s", &task);
		fscanf(pFile, "%s", &ans);
		fscanf(pFile, "%s", &key);
		m_listOfTasks[i].init(task, ans, key[0]);
	}
	fclose(pFile);

	m_randTask = new int[m_numTasks];
	for (int i = 0; i < m_numTasks; i++)
	{
		m_randTask[i] = i;
	}
	setRandomTasks();

	srand(time(0));
}

void TaskManager::setRandomTasks()
{

	for (int i = 0; i < m_numTasks; i++)
	{
		int randCnt = rand() % m_numTasks;
		if (randCnt != i)
		{
			WordTask temp = m_listOfTasks[i];
			m_listOfTasks[i] = m_listOfTasks[randCnt];
			m_listOfTasks[randCnt] = temp;
		}
		else i--;
	}
}

WordTask TaskManager::getTask(int _count)
{
	if(_count>-1&&_count<m_numTasks)
		return m_listOfTasks[_count];
}

WordTask TaskManager::getRandTask()
{
	m_currentTask++;
	return getTask(m_currentTask);
}
