#include "stdafx.h"
#include "TimerManager.h"
#include "ObjectPool.h"
#include "EventManager.h"

#include "cOBB.h"
#include "cTerrain.h"
#include "Arthur.h"
#include "DragonSoulEater.h"
#include "ObjObject.h"


ObjectPool::ObjectPool()
{
}


ObjectPool::~ObjectPool()
{
	//

}

void ObjectPool::Update()
{
	static cTerrain* terrain;
	if (terrain == NULL)
		terrain = (cTerrain*)SearchChild(Tag::Tag_Map);

	//static cArthur* arthur;
	//if (arthur == NULL)
	//	arthur = (cArthur*)SearchChild(Tag::Tag_Player);

	//static DragonSoulEater* souleater;
	//if (souleater == NULL)
	//	souleater = (DragonSoulEater*)SearchChild(Tag::Tag_Boss);

	RECT rc;
	if (terrain)
	{
		rc = terrain->GetCullingRect();
	}
	else
		rc = { 0,0,3000,30000 };
	
	for(int i = 0; i< vecObjectList.size(); i++)
	{
		
		if (terrain != NULL)
		{
			vecObjectList.at(i)->PosInMap(rc);
		if(vecObjectList.size() - m_nRefcnt < i)
		{
				D3DXVECTOR3 pos = vecObjectList[i]->GetPos();
				float h = terrain->getHeight(pos);
				pos.y = h;
				vecObjectList[i]->SetPos(pos);
		}
		}

		vecObjectList.at(i)->Update();
	}

	//if (arthur && souleater)
	//{
	//	if (souleater->GetOBB() == NULL || arthur->GetOBB() == NULL)
	//	{

	//	}
	//	else
	//	{
	//		bool isCrash = cOBB::IsCollision(arthur->GetOBB(), souleater->GetOBB());

	//		if (isCrash)
	//		{
	//			//arthur->GetColor(D3DCOLOR_XRGB(128, 128, 128));
	//			g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s", "TRUE");
	//		}
	//		else
	//		{
	//			//arthur->GetColor(D3DCOLOR_XRGB(0, 255, 250));
	//			g_pLogger->ValueLog(__FUNCTION__, __LINE__, "s", "FALSE");
	//		}

	//	}
	//}
}

void ObjectPool::Render(D3DXMATRIXA16* pmat)
{
	g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	if(pmat)
	{
		matWorld *= *pmat;
	}

	for(int i = 0 ; i < vecObjectList.size(); i++)
	{
		//if (!vecObjectList.at(i)->GetIsRender() && vecObjectList.size() - m_nRefcnt <= i)
		//	continue;
		vecObjectList.at(i)->Render(NULL);
	}

	g_pTimeManager->DrawFPS();

	for(int i = 0; i < vecUserInterface.size(); i++)
	{
		vecUserInterface.at(i)->Render(NULL);
	}

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void ObjectPool::AddChild(cObject* obj)
{
	vecObjectList.push_back(obj);
	++m_nRefcnt;
}

void ObjectPool::AddStaticChild(cObject* obj)
{
	if(m_nRefcnt > 0)
	{
		int SwapIndex = vecObjectList.size() - m_nRefcnt;
		
		vecObjectList.resize(vecObjectList.size() + 1);

		vecObjectList[vecObjectList.size() - 1] = vecObjectList[SwapIndex];
		vecObjectList[SwapIndex] = NULL;
		vecObjectList[SwapIndex] = obj;
	}
	else
	{
		vecObjectList.push_back(obj);
	}

}

void ObjectPool::Revert()
{
	int nRevertSize = vecObjectList.size() - m_nRefcnt;

	std::vector<cObject*> vecNewList;
	vecNewList.resize(nRevertSize);

	for(int i =0; i < nRevertSize; ++i)
	{
		vecNewList.at(i) = vecObjectList.at(i);
	}

	vecObjectList.swap(vecNewList);
	m_nRefcnt = 0;

	//Detech를 해줘야한다
	for(int i = 0; i < vecUserInterface.size(); i++)
	{
		cPopUp* popup = (cPopUp*)vecUserInterface[i];
		popup->Destroy();
	}
	
	std::vector<cObject*> vecNewUIList;
	vecUserInterface.swap(vecNewUIList);


	
	return;
}

const cObject* ObjectPool::GetChlid(int nIndex)
{
	if (nIndex < vecObjectList.size())
		return vecObjectList[nIndex];
	else
		return NULL;
}

void ObjectPool::AddUIChild(cObject* obj)
{
	vecUserInterface.push_back(obj);
}

void ObjectPool::RemoveUIChild(cObject& obj)
{
	vecUserInterface.erase(remove(vecUserInterface.begin(),
		vecUserInterface.end(), &obj));
}

const cObject* ObjectPool::SearchChild(int nTag)
{
	int i = 0;
	if (vecObjectList.empty()) return NULL;
	
	while(vecObjectList.at(i)->GetTag() != nTag)
	{
		++i;

		if(vecObjectList.size() <= i)
		{
			return NULL;
		}
	}

	return vecObjectList.at(i);

}

void ObjectPool::CollisionProcess()
{

	for (int i = 0; i < vecObjectList.size(); ++i)
	{
		if (!vecObjectList.at(i)->GetIsRender() ||
			vecObjectList.at(i)->GetOBB() == NULL)
			continue;

		for (int j = i + 1; j < vecObjectList.size(); ++j)
		{
			if (!vecObjectList.at(j)->GetIsRender() ||
				vecObjectList.at(j)->GetOBB() == NULL)
				continue;


			if (cOBB::IsCollision(vecObjectList.at(i)->GetOBB(),
				vecObjectList.at(j)->GetOBB()))
			{
				// 수치 계산
				
			}

		}

	}

}

void ObjectPool::RemoveChild(cObject& obj)
{
	int nOrginalSize = vecObjectList.size();

	vecObjectList.erase(remove(vecObjectList.begin(),
		vecObjectList.end(), &obj));

	m_nRefcnt -= (nOrginalSize - vecObjectList.size());

}
