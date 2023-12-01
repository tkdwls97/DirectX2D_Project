#pragma once

template<typename T>
class CSingleton
{
public:
	CSingleton()
	{
		typedef void(*FUNC_TYPE)(void);
		atexit((FUNC_TYPE)(&CSingleton::Destroy)); // main�Լ� ����� ȣ���� �Լ� ���(Destroy()�� ����ؼ� �޸� �ڵ�����)
	}
	~CSingleton()
	{

	}


public:
	static T* GetInst()
	{
		// T type��ü�� ���ٸ� ���Ӱ� �����Ҵ��ؼ� return
		if (nullptr == m_This)
		{
			m_This = new T;
		}

		return m_This;
	}

	// T type ��ü�� �ִٸ� �޸� ���� �� nullptr
	static void Destroy()
	{
		if (nullptr != m_This)
		{
			delete m_This;
			m_This = nullptr;
		}
	}


private:
	static T* m_This;	// ������ static ��ü�� �ּҸ� ������ static��� ����
};

// static ��� ���� �ʱ�ȭ �������
template<typename T>
T* CSingleton<T>::m_This = nullptr;
