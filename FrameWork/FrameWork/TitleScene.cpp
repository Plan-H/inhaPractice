#include "stdafx.h"
#include "TitleScene.h"
#include "PopUp.h"
#include "Button.h"
#include "ObjectPool.h"
#include "OptionUIEvent.h"
#include "TitleSceneUIEvent.h"

cTitleScene::cTitleScene(SceneType T)
	:cScene(T)
{
}


cTitleScene::~cTitleScene()
{
	
}

void cTitleScene::Setup()
{

	//클라이언트 값을 받아와서
	//비율화
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	cout << "Left : " << rc.left << endl; // 0
	cout << "Right : " << rc.right << endl; // 1584
	cout << "Bottom : " << rc.bottom << endl; //860
	cout << "Top : " << rc.top << endl; // 0

	float nRight = 0.34;
	float nBottom = 0.45;

	cPopup *pBackgroundPopup = new cPopup;
	pBackgroundPopup->Setup("data/UI/TitleScene", "NW_Background.png",
		D3DXVECTOR3(0, 0, 0), 1, true, true);

	Setup_OptionWindow(pBackgroundPopup);
	
	cPopup *pTitleImagePopup = new cPopup;
	pTitleImagePopup->Setup("data/UI/TitleScene", "NW_Titleletter.png",
		D3DXVECTOR3(370, 140, 0), 1, true, true);
	pBackgroundPopup->cButtonPushBack(pTitleImagePopup);

	cPopup *pBackGoundBtnPopup = new cPopup;
	pBackGoundBtnPopup->Setup("data/UI/TitleScene", "NW_Start_UI_Back.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 1, true, true);
	pTitleImagePopup->cButtonPushBack(pBackGoundBtnPopup);

	//게임시작
	cButton *pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/START", "NW_StartButton_Idle.png", 
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 105, 30, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = StartGameBtnEvent;

	//이어하기
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/CONTINUE", "NW_ContinueButton_Idle.png", 
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 105, 110, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = ContinueGameBtnEvent;

	//설정
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/SETTING", "NW_SettingButton_Idle.png", 
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 105, 190, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = SetupGameBtnEvent;

	//게임종료
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/END", "NW_EndButton_Idle.png", 
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 105, 270, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = ExitGameBtnEvent;
	
	EventManager->Attach(pBackgroundPopup);
	ObjectManager->AddUIChild(pBackgroundPopup);



	//InGameUI
	nRight = 0.01;
	nBottom = 0.01;


<<<<<<< HEAD
	cPopup* inGmaePopup = new cPopup;
	inGmaePopup->Setup("","",
=======
	cPopUp* inGamePopup = new cPopUp;
	inGamePopup->Setup("","",
>>>>>>> d04387e72d124d93d2b8f61c81209152c961f87f
		D3DXVECTOR3(0, 0, 0), 1, true, true);


	//Hp
	cButton* hpBarBackground = new cButton;
	hpBarBackground->Setup("data/UI/InGame", "NW_HP_Bar_Background.png",
		D3DXVECTOR3(rc.right* nRight, rc.bottom * nBottom, 0), 20, 670, 0, 1, false, true);
	inGamePopup->cButtonPushBack(hpBarBackground);

	cButton* hpBar = new cButton;
	hpBar->Setup("data/UI/InGame", "NW_HP_Bar_Sword.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 50, 676, 0, 1, false, true);
	hpBarBackground->cButtonPushBack(hpBar);

	cButton* hpBarMark = new cButton;
	hpBarMark->Setup("data/UI/InGame", "NW_HP_Bar_Mark.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 50, 676, 0, 1, false, true);
	hpBarBackground->cButtonPushBack(hpBarMark);

	//Staminer
	cButton* staminerBarBackgound = new cButton;
	staminerBarBackgound->Setup("data/UI/InGame", "NW_ST_Bar_Background.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 20, 715, 0, 1, false, true);
	inGamePopup->cButtonPushBack(staminerBarBackgound);

	cButton* staminerBar = new cButton;
	staminerBar->Setup("data/UI/InGame", "NW_ST_Sword.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 50, 721, 0, 1, false, true);
	staminerBarBackgound->cButtonPushBack(staminerBar);

	cButton* staminerBarMark = new cButton;
	staminerBarMark->Setup("data/UI/InGame", "NW_ST_Bar_Mark.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 50, 721, 0, 1, false, true);
	staminerBarBackgound->cButtonPushBack(staminerBarMark);


	//MiniMap
	cPopup* miniMap = new cPopup;
	miniMap->Setup("data/UI/InGame", "NW_Minimap_Background.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 1230, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(miniMap);


	//보스 분노
	cPopUp* bossAnger = new cPopUp;
	bossAnger->Setup("data/UI/InGame", "NW_MonAnger_0.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 1230, 180, 0, 1, false, true);
	inGamePopup->cButtonPushBack(bossAnger);
	
	/*
	cButton* anger = new cButton;
	anger->Setup("data/UI/InGame", "NW_MonAnger_0.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 1230, 180, 0, 1, false, true);
	bossAnger->cButtonPushBack(anger);
	*/
	/* //분노 이미지 테스트
	anger = new cButton;
	anger->Setup("data/UI/InGame", "NW_MonAnger_50.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 1230, 180, 0, 1, false, true);
	bossAnger->cButtonPushBack(anger);

	anger = new cButton;
	anger->Setup("data/UI/InGame", "NW_MonAnger_100.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 1230, 180, 0, 1, true, true);
	bossAnger->cButtonPushBack(anger);
	*/

	//보스 상태이상 이미지



	//전리품
	cPopUp* spoilsBackgound = new cPopUp;
	spoilsBackgound->Setup("data/UI/InGame", "NW_Spoils_Back.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 1340, 600, 0, 1, false, true);
	inGamePopup->cButtonPushBack(spoilsBackgound);



	//전리품 게이지
	/*
	cButton* attriBackground = new cButton;
	attriBackground->Setup("data/UI/InGame","NW_AttriGauge_Background.png",
		D3DXVECTOR3(rc.right * nRight, rc.bottom * nBottom, 0), 1200, 700, 0, 1, true, true);
	spoilsBackgound->cButtonPushBack(attriBackground);

	cButton* attri = new cButton;
	*/

	EventManager->Attach(inGamePopup);
	ObjectManager->AddUIChild(inGamePopup);
}

//
void cTitleScene::Reset()
{
	
}

