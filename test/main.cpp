#include "DxLib.h"
#include"player.h"
#include "nlohmannJson.h"

//hp描画関数
void DrawHP(int hp, int hpMax, VECTOR initPosition)
{
	int color = GetColor(255, 255, 255);
	DrawBoxAA(initPosition.x, initPosition.y,
		initPosition.x + 200, initPosition.y + 20, color, FALSE);	//枠を描画
	DrawBoxAA(initPosition.x, initPosition.y,
		initPosition.x + 200 * hp / hpMax, initPosition.y + 20, color, TRUE);	//HPゲージを描画
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定;

	int currentHp = 0;

	//jsonデータ用の構造体変数にデータを読み込み。templateの<>で型をjsonデータ用の構造体にする
	JsonData jsonData = LoadData<JsonData>("data.json");
	Player playerData = LoadData<Player>("playerData.json");

	//保存したデータを使ってプレイヤーを生成
	std::shared_ptr<Player> player = std::make_shared<Player>(playerData);

	//保存したデータをjson型に変換して使えるようにする
	nlohmann::json data = playerData;

	//読み込みデータを直で使ってプレイヤーを生成
	//std::shared_ptr<Player> player = std::make_shared<Player>(LoadData<Player>("playerData.json"));


	VECTOR position = VGet(jsonData. initUIPositionX, jsonData. initUIPositionY, 0.0);

	//メインループ
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE)) 
	{
		DrawHP(currentHp, jsonData.hpMax, position);
		currentHp++;
		if (currentHp >= jsonData.hpMax)
		{
			currentHp = 0;
		}

		DrawFormatString(0, 0, GetColor(255, 255, 255), "HP(playerのデータを使用):%d", player->getHP());

		int hp = data["hp_max"];//直で値を使おうとすると未定義になるので一回代入する
		DrawFormatString(0, 100, GetColor(255, 255, 255), "HP(jsonのデータを使用):%d", hp);	
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}