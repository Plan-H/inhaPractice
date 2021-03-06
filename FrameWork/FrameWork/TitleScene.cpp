#include "stdafx.h"
#include "TitleScene.h"
#include "PopUp.h"
#include "Button.h"
#include "ObjectPool.h"
#include "SettingUIEvent.h"
#include "TitleSceneUIEvent.h"
#include "GameSceneUIEvent.h"
#include "InGamePauseMenuUIEvent.h"
#include "SoundManager.h"
#include "jsonManager.h"

cTitleScene::cTitleScene(SceneType T)
	:cScene(T)
{
}


cTitleScene::~cTitleScene()
{
	
}

void cTitleScene::Setup()
{
	//예외 추가
	if(ObjectManager->GetUISize() > 0)
	{
		return;
	}
	//

	//클라이언트 값을 받아와서
	//비율화
	cout << "cTitleScene Setup" << endl;
	//RECT rc;
	//GetClientRect(g_hWnd, &rc);
	//cout << "Left : " << rc.left << endl; // 0
	//cout << "Right : " << rc.right << endl; // 1584
	//cout << "Bottom : " << rc.bottom << endl; //860
	//cout << "Top : " << rc.top << endl; // 0

#pragma region UI TAG::Title
	//TitleUI
	cPopup *pTitleBackgroundPopup = new cPopup;
	pTitleBackgroundPopup->Setup("data/UI/TitleScene", "NW_Background.png",
		D3DXVECTOR3(0, 0, 0), 1, true, true, TAG_UI::TagUI_Title);

	Setup_Setting_popup(pTitleBackgroundPopup);
	
	cPopup *pTitleImagePopup = new cPopup;
	pTitleImagePopup->Setup("data/UI/TitleScene", "NW_Titleletter.png",
		D3DXVECTOR3(50, 140, 0), 1, true, true);
	pTitleBackgroundPopup->cButtonPushBack(pTitleImagePopup);

	cPopup *pBackGoundBtnPopup = new cPopup;
	pBackGoundBtnPopup->Setup("data/UI/TitleScene", "NW_Start_UI_Back.png",
		D3DXVECTOR3(550, 380, 0), 1, true, true);
	pTitleImagePopup->cButtonPushBack(pBackGoundBtnPopup);

	//게임시작
	cButton *pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/START", "NW_StartButton_Idle.png", 
		D3DXVECTOR3(650, 420, 0), 0, 0, 0, 1, true, true);
		//D3DXVECTOR3(650, 420, 0), 0, 0, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = StartGameBtnEvent;

	// 이어하기
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/CONTINUE", "NW_ContinueButton_Disable.png", 
		D3DXVECTOR3(650, 495, 0), 0, 0, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	//pButton->EventProcess = ContinueGameBtnEvent;

	//설정
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/SETTING", "NW_SettingButton_Idle.png", 
		D3DXVECTOR3(650, 570, 0), 0, 0, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = SetupGameBtnEvent;

	//게임종료
	pButton = new cButton;
	pButton->Setup("data/UI/TitleScene/END", "NW_EndButton_Idle.png", 
		D3DXVECTOR3(650, 645, 0), 0, 0, 0, 1, true, true);
	pBackGoundBtnPopup->cButtonPushBack(pButton);
	pButton->EventProcess = ExitGameBtnEvent;
	
	EventManager->Attach(pTitleBackgroundPopup);
	ObjectManager->AddUIChild(pTitleBackgroundPopup);

	/*
	//이미지 크기 요청해서 수정 필요
	//게임시작 버튼 누를시 확인창
	cPopup* pNewGameCheckPopup = new cPopup;
	pNewGameCheckPopup->Setup("data/UI/Check", "NW_StartCheck_Background.png",
		D3DXVECTOR3(0, 0, 0), 0, 0, 0, 1, true, true, TAG_UI::TagUI_NewGameCheck);

	cButton* pNewGameCheckPopupYesBtn = new cButton;
	pNewGameCheckPopupYesBtn->Setup("data/UI/Check/YES", "NW_Check_Yesbutton_Idle.png",
		D3DXVECTOR3(0, 0, 0), 0, 0, 0, 1, true, true);
	pNewGameCheckPopup->cButtonPushBack(pNewGameCheckPopupYesBtn);
	//pNewGameCheckPopupYesBtn->EventProcess = ;

	cButton* pNewGameCheckPopupNoBtn = new cButton;
	pNewGameCheckPopupNoBtn->Setup("data/UI/check/NO", "NW_Check_Nobutton_Idle.png",
		D3DXVECTOR3(0, 0, 0), 0, 0, 0, 1, true, true);
	pNewGameCheckPopup->cButtonPushBack(pNewGameCheckPopupNoBtn);
	//pNewGameCheckPopupNoBtn->EventProcess = ;

	EventManager->Attach(pNewGameCheckPopup);
	ObjectManager->AddUIChild(pNewGameCheckPopup);
	

	//게임종료 버튼 누를시 확인창
	cPopup* pExitCheckPopup = new cPopup;
	pExitCheckPopup->Setup("data/UI/Check", "NW_EndCheck_Background.png",
		D3DXVECTOR3(500, 300, 0), 0, 0, 0, 0.5, true, true, TagUI_ExitCheck);
	
	cButton* pExitCheckPopupYesBtn = new cButton;
	pExitCheckPopupYesBtn->Setup("data/UI/Check/YES", "NW_Check_Yesbutton_Idle.png",
		D3DXVECTOR3(620, 450, 0), 0, 0, 0, 0.5, true, true);
	pExitCheckPopup->cButtonPushBack(pExitCheckPopupYesBtn);

	cButton* pExitCheckPopupNoBtn = new cButton;
	pExitCheckPopupNoBtn->Setup("data/UI/Check/NO", "NW_Check_Nobutton_Idle.png",
		D3DXVECTOR3(820, 450, 0), 0, 0, 0, 0.5, true, true);
	pExitCheckPopup->cButtonPushBack(pExitCheckPopupNoBtn);

	EventManager->Attach(pExitCheckPopup);
	ObjectManager->AddUIChild(pExitCheckPopup);
	*/

#pragma endregion << UI TAG::Title


#pragma region UI TAG::InGame
	//InGame UI
	cPopup* inGamePopup = new cPopup;
	inGamePopup->Setup("","",
		D3DXVECTOR3(0, 0, 0), 1, false, true, TAG_UI::TagUI_InGame);

	//Hp
	cPopup* hpBar = new cPopup;
	hpBar->Setup("data/UI/InGame", "NW_HP_Gauge.png",
		D3DXVECTOR3(61, 736, 0), 0, 0, 0, 1, false, true, TAG_UI::TagUI_Hp);
	hpBar->EventProcess = HpGaugeEvent;

	cPopup* hpBarBackground = new cPopup;
	hpBarBackground->Setup("data/UI/InGame", "NW_HPST_BarBackground.png",
		D3DXVECTOR3(30, 730, 0), 0, 0, 0, 1, false, true);
	hpBar->cButtonPushBack(hpBarBackground);

	EventManager->Attach(hpBar);
	ObjectManager->AddUIChild(hpBar);

	/* 이전버전소스 keep
	cButton* hpBarBackground = new cButton;
	hpBarBackground->Setup("data/UI/InGame", "NW_HP_BarBackground.png",
		D3DXVECTOR3(30, 730, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(hpBarBackground);

	
	cButton* hpBar = new cButton;
	hpBar->Setup("data/UI/InGame", "NW_HP_Bar_Sword.png",
		D3DXVECTOR3(60, 736, 0), 0, 0, 0, 1, false, true);
	hpBarBackground->cButtonPushBack(hpBar);

	cButton* hpBarMark = new cButton;
	hpBarMark->Setup("data/UI/InGame", "NW_HP_Bar_Mark.png",
		D3DXVECTOR3(60, 736, 0), 0, 0, 0, 1, false, true);
	hpBarBackground->cButtonPushBack(hpBarMark);
	*/


	//Stamina
	cPopup* staminaBar = new cPopup;
	staminaBar->Setup("data/UI/InGame", "NW_ST_Gauge.png",
		D3DXVECTOR3(61, 786, 0), 0, 0, 0, 1, false, true, TAG_UI::TagUI_Stamina); // 
	staminaBar->EventProcess = StaminaGaugeEvent;

	cPopup* staminaBarBackgound = new cPopup;
	staminaBarBackgound->Setup("data/UI/InGame", "NW_HPST_BarBackground.png",
		D3DXVECTOR3(30, 780, 0), 0, 0, 0, 1, false, true);
	staminaBar->cButtonPushBack(staminaBarBackgound);

	EventManager->Attach(staminaBar);
	ObjectManager->AddUIChild(staminaBar);


	//캐릭터 디버프
	cPopup* playerDebuff1 = new cPopup;
	playerDebuff1->Setup("data/UI/InGame/Player_Condition", "Condition_None.png",
		D3DXVECTOR3(60, 680, 0), 0, 0, 0, 1, false, true, TAG_UI::TagUI_player_Debuff1);
	EventManager->Attach(playerDebuff1);
	ObjectManager->AddUIChild(playerDebuff1);

	cPopup* playerDebuff2 = new cPopup;
	playerDebuff2->Setup("data/UI/InGame/Player_Condition", "Condition_None.png",
		D3DXVECTOR3(120, 680, 0), 0, 0, 0, 1, false, true, TAG_UI::TagUI_player_Debuff2);
	EventManager->Attach(playerDebuff2);
	ObjectManager->AddUIChild(playerDebuff2);


	//미니맵 삭제에 따른 주석
	/*
	//MiniMap
	cPopup* miniMap = new cPopup;
	miniMap->Setup("data/UI/InGame", "NW_Minimap_Background.png",
		D3DXVECTOR3(1305, 0, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(miniMap);
	*/

	//분노와 상태이상 표현 삭제에 따른 주석처리 변경 있을 수 있기떄문에 삭제x
	/*
	//보스 분노
	cPopup* bossAnger = new cPopup;
	bossAnger->Setup("data/UI/InGame", "NW_MonAnger_0.png",
		D3DXVECTOR3(1270, 180, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(bossAnger);
	

	//보스 상태이상 이미지 좌표 따기위해 적어둠
	cPopup* bossDiverf = new cPopup;
	bossDiverf->Setup("data/UI/InGame/Monster_Condition", "NW_Stun.png",
		D3DXVECTOR3(1330, 180, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(bossDiverf);
	*/
	/*
	bossDiverf = new cPopup;
	bossDiverf->Setup("data/UI/InGame", "NW_Condition_Stun.png",
		D3DXVECTOR3(1380, 180, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(bossDiverf);

	bossDiverf = new cPopup;
	bossDiverf->Setup("data/UI/InGame", "NW_Condition_Stun.png",
		D3DXVECTOR3(1430, 180, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(bossDiverf);

	bossDiverf = new cPopup;
	bossDiverf->Setup("data/UI/InGame", "NW_Condition_Stun.png",
		D3DXVECTOR3(1480, 180, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(bossDiverf);

	bossDiverf = new cPopup;
	bossDiverf->Setup("data/UI/InGame", "NW_Condition_Stun.png",
		D3DXVECTOR3(1530, 180, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(bossDiverf);
	*/
	
	//전리품 배경
	cPopup* pInGameTrophiesBackgound = new cPopup;
	pInGameTrophiesBackgound->Setup("data/UI/InGame", "NW_trophies_Back.png",
		D3DXVECTOR3(1270, 620, 0), 0, 0, 0, 1, false, true);
	inGamePopup->cButtonPushBack(pInGameTrophiesBackgound);
	
	//전리품 게이지
	cPopup* pInGameTropiesGauge = new cPopup;
	pInGameTropiesGauge->Setup("data/UI/InGame", "NW_Attri_Gauge.png",
		D3DXVECTOR3(1163, 785, 0), 0, 0, 0, 1, false, true, TAG_UI::TagUI_TrophiesGauge);
	pInGameTropiesGauge->EventProcess = TrophiseGaugeEvent;

	//전리품 게이지 배경
	cButton* pInGameTrophiesBarBackground = new cButton;
	pInGameTrophiesBarBackground->Setup("data/UI/InGame","NW_Attri_BarBackground.png",
		D3DXVECTOR3(1130, 780, 0), 0, 0, 0, 1, false, true);
	pInGameTropiesGauge->cButtonPushBack(pInGameTrophiesBarBackground);
	EventManager->Attach(pInGameTropiesGauge);
	ObjectManager->AddUIChild(pInGameTropiesGauge);

	/*
	cButton* attriBar = new cButton;
	attriBar->Setup("data/UI/InGame", "NW_Attri_Gauge.png",
		D3DXVECTOR3(1162, 765, 0), 0, 0, 0, 1, false, true);
	attriBarBackground->cButtonPushBack(attriBar);
	
	cButton* attriMark = new cButton;
	attriMark->Setup("data/UI/InGame", "NW_AttriGauge_Mark.png",
		D3DXVECTOR3(1162, 768, 0), 0, 0, 0, 1, false, true);
	attriBarBackground->cButtonPushBack(attriMark);
	*/

	EventManager->Attach(inGamePopup);
	ObjectManager->AddUIChild(inGamePopup);
#pragma endregion << UI TAG::InGame


#pragma region UI TAG::GameObject
	//오브젝트 게이지
	cPopup* obectBar = new cPopup;
	obectBar->Setup("", "", D3DXVECTOR3(0, 0, 0), 0, 0, 0, 1, false, true, TagUI_InGameObject);

	cButton* interactionBarBackground = new cButton;
	interactionBarBackground->Setup("data/UI/InGame", "NW_InteractionGauge_Background.png",
		D3DXVECTOR3(970, 300, 0), 0, 0, 0, 1, false, true);
	obectBar->cButtonPushBack(interactionBarBackground);

	/*
	cButton* interactionBarGauge = new cButton;
	interactionBarGauge->Setup("data/UI/InGame", "NW_Interaction_Gauge.png",
		D3DXVECTOR3(972.5, 445, 0), 0, 0, 0, 1, false, true);
	interactionBarBackground->cButtonPushBack(interactionBarGauge);
	*/
	
	EventManager->Attach(obectBar);
	ObjectManager->AddUIChild(obectBar);
#pragma endregion << UI TAG::GameObject



#pragma region UI TAG::ESC_Menu
	// TODO json 파일 쓸 때 대비해서 주석남겨둠
	// pPopup = new cPopup;
	// pPopup->Setup(파일위치, D3DXVECTOR3(x축 중앙 - 이미지 x크기 - 위치조정, y축 중앙 - 이미지 y 크기 - 위치조정, 0), 배율);
	// pPopup->Setup("data/UI/TitleScene", "게임 타이틀 사이즈 조정.png", D3DXVECTOR3(800 - 450, 450 - 150 - 200, 0), 2, false, false);

	//EventManager->Attach(pPopup);
	//ObjectManager->AddUIChild(pPopup);

	cPopup * pMediator = new cPopup;
	pMediator->Setup(
		"",
		"",
		D3DXVECTOR3(-1, -1, 0),
		0, 0, 0,
		1,
		true, true, TAG_UI::TagUI_ESC_Menu);
	pMediator->EventProcess = InGamePause_Event;
	
	cPopup *pSystemPopUp = Setup_InGamePauseMenu(pMediator);
	cPopup *pOptionPopUp = Setup_Setting_popup(pMediator);

	EventManager->Attach(pMediator);
	ObjectManager->AddUIChild(pMediator);
#pragma endregion << UI TAG::ESC_Menu
	static JSON_Object* p_json_object_setting = g_p_jsonManager->get_json_object_Setting();
	JSON_Object* Sound_object(json_object_get_object(p_json_object_setting, "Sound"));

	g_pSoundManager->AddBGM("data/Sound/BGM/NW_Lobby_BGM.mp3");
	g_pSoundManager->SetSFXSOUND((float)json_object_get_number(Sound_object, "SFX") * 0.01f);
	g_pSoundManager->SetBGMSOUND((float)json_object_get_number(Sound_object, "BGM") * 0.01f);
	//g_pSoundManager->SetBGMSOUND(0.3f);
	//g_pSoundManager->SetSFXSOUND(0.3f);
	g_pSoundManager->PlayBGM();

}

//
void cTitleScene::Reset(int sceneType)
{
	cPopup* popup = NULL;

	switch (sceneType)
	{
	//게임 씬으로 이동 할 때
	/*
	case SceneType::SCENE_BOSS_1:
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_InGame);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}

		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_Hp);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}

		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_Stamina);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}
		
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_TrophiesGauge);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}

		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_ESC_Menu);
		if (popup != NULL)
		{
			popup->PowerOnOff_OnlySelf(true);
		}
		break;
		*/
	//스테이지 축소로 인해 주석
	/*
	case SceneType::SCENE_BOSS_2:
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_InGame);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}

		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_ESC_Menu);
		if (popup != NULL)
		{
			popup->PowerOnOff_OnlySelf(true);
		}
		break;
	*/

	//게임 오버 씬으로 이동할 때
	/*
	case SceneType::SCENE_GAMEOVER:
		popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_GameOver);
		if (popup != NULL)
		{
			popup->PowerOnOff();
		}
		break;
		*/

	default:
		break;
	}

	popup = (cPopup*)ObjectManager->SearchChildUI(TAG_UI::TagUI_Title);
	if (popup != NULL)
	{
		popup->PowerOnOff();
	}

}