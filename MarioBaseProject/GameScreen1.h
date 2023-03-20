#pragma once
#ifndef _GAMESCREEN1_H
#define _GAMESCREEN1_H

#include "GameScreen.h"
#include "Commons.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "Character.h"
#include "LevelMap.h"
#include "PowBlock.h"

class Texture2D;
class Character;
class PowBlock; 

class GameScreen1 : GameScreen
{
	
public: 
	
	
	GameScreen1(SDL_Renderer* renderer);
	~GameScreen1();

	void Render() override; 
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePowBlock(); 

private:
	bool SetUpLevel();
	void SetLevelMap();

	Texture2D* m_background_texture;
	CharacterMario* mario;
	CharacterLuigi* luigi; 
	LevelMap* m_level_map; 
	PowBlock* m_pow_block;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	void DoScreenShake();

	
protected:
	

};

#endif
