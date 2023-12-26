#pragma once


struct FTask
{
	TASK_TYPE Type;
	UINT_PTR  Param_1;
	UINT_PTR  Param_2;
};

class CTaskMgr : public CSingleton<CTaskMgr>
{
	SINGLE(CTaskMgr);

public:
	void Tick();

	void AddTask(const FTask& _Task) { m_vecTask.push_back(_Task); }

private:

	vector<FTask>	m_vecTask;


};

