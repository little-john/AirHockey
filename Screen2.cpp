#include "Screen2.h"
#include "Game.h"

namespace Screen2
{
	RoundRect titleButton;
	Transition buttonTransition;

	RoundRect retryButton;
	Transition retryButtonTransition;

	GameScreen CreateScreen()
	{
		GameScreen screen;
		screen.Init = (FunctionPointer)(Init);
		screen.Update = (FunctionPointer)(Update);
		screen.Draw = (FunctionPointer)(Draw);
		screen.Terminate = (FunctionPointer)(Terminate);
		screen.IsScreenChangeOK = (BoolFunctionPointer)(IsScreenChangeOK);
		return screen;
	}

	void Init()
	{
		Scene::SetBackground(Palette::Lightpink);
		titleButton = RoundRect(Scene::Center().x - 150, Scene::Height() - 100, 300, 50, 15);
		buttonTransition = Transition(0.4s, 0.2s);

		retryButton = RoundRect(Scene::Center().x - 150, Scene::Height() - 200, 300, 50, 15);
		retryButtonTransition = Transition(0.4s, 0.2s);
	}

	void Update()
	{
		if (titleButton.leftClicked())
		{
			Game::ChangeScreen(STitle);
		}

		buttonTransition.update(titleButton.mouseOver());

		if (retryButton.leftClicked())
		{
			Game::ChangeScreen(SScreen1);
		}

		retryButtonTransition.update(titleButton.mouseOver());

	}

	void Draw()
	{
		Vec2 center(Scene::Center());
		
		if (Game::GetGlobalData()->result == WIN) {
			FontAsset(U"GameResult")(U"YOU WIN").drawAt(center,Palette::Orange);
		}
		else {
			FontAsset(U"GameResult")(U"YOU LOSE").drawAt(center,Palette::Red);
		}
		

		FontAsset(U"Label1")(U"プログラマー:JOHN BALAX").drawAt(center.moveBy(0, 300), Palette::Black);

		titleButton.draw(ColorF(1.0, 1 - buttonTransition.value() * 0.5f)).drawFrame(5, ColorF(0.0f, 0.5f));
		FontAsset(U"Button")(U"TITLE").drawAt(titleButton.center(), Palette::Black);

		retryButton.draw(ColorF(1.0, 1 - retryButtonTransition.value() * 0.5f)).drawFrame(5, ColorF(0.0f, 0.5f));
		FontAsset(U"Button")(U"RETRY").drawAt(retryButton.center(), Palette::Black);
	}

	void Terminate()
	{

	}

	bool IsScreenChangeOK()
	{
		return false;
	}
}
