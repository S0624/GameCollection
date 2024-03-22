#pragma once

class FieldInformation; 

class Stage2
{
private:
	FieldInformation* m_Information;
public:
	Stage2();
	~Stage2() {};

	void FieldInit();
};

