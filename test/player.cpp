#include"DxLib.h"
#include"player.h"


Player::Player(const Player& playerData):
	hp_(playerData.hp_),
	velocity_(playerData.velocity_)
{
}

Player::~Player()
{
}