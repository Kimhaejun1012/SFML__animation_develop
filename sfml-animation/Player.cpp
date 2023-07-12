#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"

void Player::Init()
{
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/Idle.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/Move.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/Up.csv");
	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "tables/Down.csv");



	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/Move.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/Up.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("tables/Down.csv"));

	animation.SetTarget(&sprite);

	SetOrigin(Origins::BC);


	floor.setFillColor(sf::Color::Green);
	floor.setPosition({ 0,0 });
	floor.setOutlineColor(sf::Color::Magenta);
	floor.setOutlineThickness(100);
	Utils::SetOrigin(floor, Origins::BC);
	floor.setSize(sf::Vector2f{ 500, 500 });
}

void Player::Reset()
{
	animation.Play("Idle");
	SetOrigin(origin);
	SetPosition({ 0, 0 });
	SetFlipX(false);
}

void Player::Update(float dt)
{
	isWPressed = INPUT_MGR.GetKey(sf::Keyboard::W);
	isAPressed = INPUT_MGR.GetKey(sf::Keyboard::A);
	isSPressed = INPUT_MGR.GetKey(sf::Keyboard::S);
	isDPressed = INPUT_MGR.GetKey(sf::Keyboard::D);

	animation.Update(dt);
	float h = INPUT_MGR.GetAxis(Axis::Horizontal);
	float w = INPUT_MGR.GetAxis(Axis::Vertical);
	// �ø�
	if (h != 0.f)
	{
		bool flip = h > 0.f;
		if (GetFlipX() != flip)
		{
			SetFlipX(flip);
		}
	}

	// ����

	// �̵�
	velocity.x = h * speed;
	velocity.y = w * speed;
	position += velocity * dt;

	// �ٴ� �浹 ó��
	//if (position.y > 0.f)
	//{
	//	isGround = true;
	//	position.y = 0.f;
	//	velocity.y = 0.f;
	//}


	//�밢 �̻��� 

	SetPosition(position);

	// ���ϸ��̼�
	if (animation.GetCurrentClipId() == "Idle" || animation.GetCurrentClipId() == "Up" || animation.GetCurrentClipId() == "Down" )
	{
		if (h != 0.f)
		{
			animation.Play("Move");
		}
	}
	else if (animation.GetCurrentClipId() == "Move")
	{
		if (h == 0.f)
		{
			animation.Play("Idle");
		}
	}

	if ((animation.GetCurrentClipId() == "Idle" || animation.GetCurrentClipId() == "Down" || animation.GetCurrentClipId() == "Move") && h==0)
	{
		//animation.GetCurrentClipId() = "Up";
		if (w < 0.f)
		{
			animation.Play("Up");
		}
	}
	else if (animation.GetCurrentClipId() == "Up")
	{
		if (w == 0.f)
		{
			animation.Play("Idle");
		}
	}
	if ((animation.GetCurrentClipId() == "Idle" || animation.GetCurrentClipId() == "Up" || animation.GetCurrentClipId() == "Move")&& h == 0)
	{
		if (w > 0.f)
		{
			animation.Play("Down");
		}
	}
	else if (animation.GetCurrentClipId() == "Down")
	{
		if (w == 0.f)
		{
			animation.Play("Idle");
		}
	}


}

bool Player::GetFlipX() const
{
	return filpX;
}

bool Player::GetFlipY() const
{
	return filpY;
}

void Player::SetFlipX(bool filp)
{
	filpX = filp;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !filpX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}

void Player::SetFlipY(bool filp)
{
	filpY = filp;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !filpY ? abs(scale.y) : -abs(scale.y);
	sprite.setScale(scale);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(floor);
	SpriteGo::Draw(window);
}
