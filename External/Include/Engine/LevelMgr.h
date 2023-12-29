#pragma once

class CLevel;

class CLevelMgr : public CSingleton<CLevelMgr>
{
    SINGLE(CLevelMgr);


public:
    void Init();
    void Tick();

public:
    CLevel* GetCurrentLevel() { return m_CurLevel; }

private:
    CLevel* m_CurLevel;
};

