#pragma once
#include"nlohmannJson.h"

class Player
{
public:
	Player() = default;
	Player(const Player& playerData);
	~Player();

	const int getHP()const { return hp_; }

	friend inline void from_json(const nlohmann::json& json, Player& player);

private:

	int		hp_;
	float	velocity_;
};

//任意の型変換(第一引数→nlohmannjson、第二引数→jsonのデータ) get<MY_TYPE>() get_to(MY_TYPE& arg) が呼ばれた時に、自動的にfrom_jsonが呼ばれる。
inline void from_json(const nlohmann::json& json, Player& player)
{
	//at("")でデータの要素を指定してget_toで指定した要素の中身（数値など)をget_toの引数の変数に代入する
	json.at("hp_max").get_to(player.hp_);
	json.at("velocity").get_to(player.velocity_);
}