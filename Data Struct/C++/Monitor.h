#pragma once


#include <string>

class Monitor
{
public:
	virtual ~Monitor() = default;
	virtual void List_Show(const std::string& string="") = 0;
};





