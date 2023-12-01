#pragma once


template<typename T>
class CSingleton
{
	friend class T;
private:
	CSingleton()
	{

	}
	~CSingleton()
	{

	}

public:
	static T* GetInst()
	{
		if (nullptr == m_This)
		{
			m_This = new T;
		}

		return m_This;
	}

	static void Destroy()
	{
		if (nullptr != m_This)
		{
			delete m_This;
			m_This = nullptr;
		}
	}


private:
	static T* m_This;
};
