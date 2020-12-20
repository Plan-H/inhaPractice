#pragma once
#include "cObject.h"
#include "SkinnedMesh.h"
#include "SoundManager.h"

//
class cSoulEaterState;
class cOBB;

enum eDebuff_Dragon 
{
	enum_Stun_Dragon,
	enum_Trip_Dragon,
};


class cDragonSoulEater :
	public cObject
{
private:
	cSkinnedMesh*		m_pSkinnedUnit;
	D3DMATERIAL9		m_Mstl;

	
	cSoulEaterState*	m_pCurState;
	DWORD				m_dwDelayState;

	D3DXMATRIXA16		m_matWorld;
	LPDIRECT3DTEXTURE9	m_pTexture;

	vector<BoundingBox> m_vecBoundingBoxList;
	
	// >> new
	D3DXVECTOR3*			m_pvTarget;
	int						m_nPrevStateIndex;
	D3DXMATRIXA16			m_matRotation;

	
	float				m_fElementalDefence;
	float				m_fPhysicsDefence;
	float				m_fPhysicDamage;
	float				m_fElementalDamage;

	int					m_nPhase;
	int m_Debuff;
	
	float				m_fRagegauge;
	bool				m_IsRage;

	DWORD				m_dwSwampCreateCoolTime;
	DWORD				m_dwSwampElapsedTime;

	Synthesize(float, m_fStungauge, STUN);
	Synthesize(float, m_fMaxHeathPoint, MAXHP);
	Synthesize(float, m_fCurHeathpoint, CURHP);
	bool m_IsBreathe;
	bool m_IsFireball;
public:
	cDragonSoulEater();
	~cDragonSoulEater();
	void Update() override;
	void Render(D3DXMATRIXA16* pmat) override;
	void Setup(char* szFolder, char* szFileName);
	cSkinnedMesh& GetSkinnedMesh() { return *m_pSkinnedUnit; }

	void GetWorldMatrix(D3DXMATRIXA16* matWorld);

	void SetupBoundingBox();
	virtual void CollisionProcess(cObject* pObject) override;
	//std::vector<cOBB*>* GetBouningBox() { return &m_vecBoundingBoxList; }

	//new
	void Request();
	D3DXVECTOR3* GetTarget();
	D3DXMATRIXA16* GetRotation() { return &m_matRotation; }
	void SetRotation(D3DXMATRIXA16* mat) { m_matRotation = *mat; }
};


