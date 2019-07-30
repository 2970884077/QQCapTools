#pragma once
#include<list>
#include"SessionElement.h"
#include"CachePackets.h"
class CSessions
{
public:

	CSessions()
	{
		NoFlag = 0;
	}

	virtual ~CSessions()
	{
	}
private:
	ClientEnum	mClientType;			//�ͻ�������
public:
	unsigned int NoFlag;//��ʶ����
	std::list<CSessionElement> mSessions;//ֻ��ʹ��AddSession������ӣ�������ʹ����push_back�Ⱥ���
	CCachePackets mCachePackets;
public:
	void SetClientType(ClientEnum m)
	{
		mClientType = m;
	}
	ClientEnum GetClientType()
	{
		return mClientType;
	}
	void AddSession(CSessionElement m)
	{
		mSessions.push_back(m);
	}
	const CSessionElement *FindSession(unsigned int _uuid)
	{
		std::list<CSessionElement>::iterator itor1=
			std::find_if(mSessions.begin(), mSessions.end(), [_uuid](CSessionElement const& obj){
			return obj.Getuuid() == _uuid;
		});
		if (itor1 != mSessions.end())
		{
			return &(*itor1);
		}
		return 0;
	}

};

