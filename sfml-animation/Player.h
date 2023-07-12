#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Player : public SpriteGo
{
public:

protected:
	AnimationController animation;
	sf::Vector2f velocity;
	sf::RectangleShape floor;
	float accel = 500.f;
	float speed = 500.f;
	float JumpForce = -250.f;
	float gravity = 500.f;

	bool isWPressed = false;
	bool isAPressed = false;
	bool isSPressed = false;
	bool isDPressed = false;
	bool filpX = false;
	bool filpY = false;
	bool isGround = true;

	bool adasd = false;

public:
	Player(const std::string& textureId = "", const std::string& n = "")
		: SpriteGo(textureId, n) {}
	virtual ~Player() override { Release(); }

	virtual void Init() override;
	virtual void Reset() override;
	virtual void Update(float dt) override;

	bool GetFlipX() const;
	bool GetFlipY() const;
	void SetFlipX(bool filp);
	void SetFlipY(bool filp);

	virtual void Draw(sf::RenderWindow& window) override;

};
