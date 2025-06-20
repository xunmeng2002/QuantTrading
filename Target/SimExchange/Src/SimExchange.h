#pragma once
#include "Mdb.h"
#include "Packages.h"
#include "Config.h"
#include "ThreadBase.h"


class SimExchange : public ThreadBase
{
public:
	SimExchange(const Config& config);
	~SimExchange();

	void Init();

protected:
	virtual void Run() override;


protected:
	mdb::Mdb* m_Mdb;
};