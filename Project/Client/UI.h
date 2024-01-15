#pragma once

class UI
{
public:
	UI();
	~UI();

public:
	void SetName(const string& _name) { m_strName = _name; }
	const string& GetName() { return m_strName; }
private:
	string m_strName;
	string m_strID;

};

