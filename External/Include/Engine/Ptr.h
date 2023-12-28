#pragma once

template<typename T>
class Ptr
{
public:
	Ptr()
		: Asset(nullptr)
	{
	}

	Ptr(const Ptr<T>& _Other)
		:Asset(_Other.Asset)
	{
		if (nullptr != Asset)
			Asset->AddRef();
	}

	Ptr(T* _Asset)
		: Asset(_Asset)
	{
		if (nullptr != Asset)
			Asset->AddRef();
	}



	~Ptr()
	{
		if (Asset)
		{
			Asset->Release();
		}
	}


public:
	T* Get() const { return Asset; }
	T** GetAdressOf() const { return &Asset; }



public:
	void operator = (const Ptr& _ptr)
	{
		if (nullptr != Asset)
			Asset->Release();

		Asset = _ptr.Asset;

		if (nullptr != Asset)
			Asset->AddRef();
	}

	void operator = (T* _Asset)
	{
		if (nullptr != Asset)
			Asset->Release();

		Asset = _Asset;

		if (nullptr != Asset)
			Asset->AddRef();
	}

	bool operator ==(const Ptr<T>& _Other)
	{
		if (Asset == _Other.Asset)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator != (const Ptr<T>& _Other)
	{
		return !(*this == _Other);
	}

	bool operator ==(const T* _Asset)
	{
		if (Asset == _Asset)
			return true;
		else
			return false;
	}

	bool operator != (const T* _Asset)
	{
		return !(*this == _Asset);
	}

	T* operator->() const { return Asset; }

private:
	T* Asset;
};

template<typename T>
bool operator == (const void* _Asset, const Ptr<T>& _Ptr)
{
	if (_Asset == _Ptr.Get())
		return true;
	else
		return false;
}

template<typename T>
bool operator != (const void* _Asset, const Ptr<T>& _Ptr)
{
	return !(_Asset == _Ptr);
}