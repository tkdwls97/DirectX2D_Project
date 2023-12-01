#pragma once

template<typename T>
class CSingleton
{
public:
	CSingleton()
	{
		typedef void(*FUNC_TYPE)(void);
		atexit((FUNC_TYPE)(&CSingleton::Destroy)); // main함수 종료시 호출할 함수 등록(Destroy()를 등록해서 메모리 자동해제)
	}
	~CSingleton()
	{

	}


public:
	static T* GetInst()
	{
		// T type객체가 없다면 새롭게 동적할당해서 return
		if (nullptr == m_This)
		{
			m_This = new T;
		}

		return m_This;
	}

	// T type 객체가 있다면 메모리 해제 후 nullptr
	static void Destroy()
	{
		if (nullptr != m_This)
		{
			delete m_This;
			m_This = nullptr;
		}
	}


private:
	static T* m_This;	// 생성한 static 객체의 주소를 저장할 static멤버 변수
};

// static 멤버 변수 초기화 해줘야함
template<typename T>
T* CSingleton<T>::m_This = nullptr;
