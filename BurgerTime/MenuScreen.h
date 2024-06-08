#pragma once
namespace dae
{
	class TextComponent;
}


class MenuScreen
{
public:
	MenuScreen();
private:
	void Initialize();

	dae::TextComponent* m_SinglePlayer = nullptr;
	dae::TextComponent* m_Coop = nullptr;
	dae::TextComponent* m_Versus = nullptr;


};

