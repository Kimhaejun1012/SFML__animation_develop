#pragma once

enum class AnimationLoopTypes
{
	Single,
	Loop,
};

struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord;
	//�Ű������� ���̵� ��ȯ���� ���̵��� �Լ� ���� ����
	std::function<void()> action;
};

struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames;
	AnimationLoopTypes loopType;
	int fps;

	bool LoadFromFile(const std::string path);
};