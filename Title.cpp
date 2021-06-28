#include "Title.h"
#include "Game.h"

namespace Title
{
	RoundRect startButton;
	Transition startTransition;

	RoundRect exitButton;
	Transition exitTransition;

	RoundRect easyButton;
	RoundRect hardButton;

	bool isSelectDifficulty = false;

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
		isSelectDifficulty = false;
		Scene::SetBackground(Palette::Tomato);
		startButton = RoundRect(Scene::Center().x - 150, Scene::Height() - 300, 300, 50, 15);
		exitButton = RoundRect(Scene::Center().x - 150, Scene::Height() - 200, 300, 50, 15);
		startTransition = Transition(0.4s, 0.2s);
		exitTransition = Transition(0.4s, 0.2s);

		easyButton = RoundRect(Scene::Center().x - 200, Scene::Center().y - 50, 150, 25, 15);
		hardButton = RoundRect(Scene::Center().x + 50, Scene::Center().y - 50, 150, 25, 15);
	}

	void Update() 
	{
		if (startButton.leftClicked()) 
		{
			isSelectDifficulty = true;
		}

		if (exitButton.leftClicked())
		{
			System::Exit();
		}

		if (isSelectDifficulty)
		{
			if (easyButton.leftClicked()) 
			{
				Game::GetGlobalData()->difficulty = EASY;
				Game::ChangeScreen(SScreen1);
			}

			if (hardButton.leftClicked())
			{
				Game::GetGlobalData()->difficulty = HARD;
				Game::ChangeScreen(SScreen1);
			}
		}

		startTransition.update(startButton.mouseOver());
		exitTransition.update(exitButton.mouseOver());
	}

	void Draw()
	{

		Vec2 center(Scene::Center().x, 100);
		FontAsset(U"Title")(U"AIR HOCKEY").drawAt(center.moveBy(5, 20), ColorF(0.0, 0.5));
		FontAsset(U"Title")(U"AIR HOCKEY").drawAt(center, HSV( 90 + Periodic::Sine0_1(10) * 90));

		startButton.draw(ColorF(1.0, 1- startTransition.value() * 0.5f)).drawFrame(5, ColorF(0.0f,0.5f));
		FontAsset(U"Button")(U"START").drawAt(startButton.center(), Palette::Black);

		exitButton.draw(ColorF(1.0, 1- exitTransition.value() * 0.5f)).drawFrame(5, ColorF(0.0f, 0.5f));
		FontAsset(U"Button")(U"EXIT").drawAt(exitButton.center(), Palette::Black);
	
		
		if (isSelectDifficulty)
		{
			Rect(0, 0, Scene::Size()).draw(ColorF(0.0, 0.8));
			easyButton.draw().drawFrame(5, ColorF(0.0f, 0.5f));
			FontAsset(U"Button")(U"EASY").drawAt(easyButton.center(), Palette::Black);

			hardButton.draw().drawFrame(5, ColorF(0.0f, 0.5f));
			FontAsset(U"Button")(U"HARD").drawAt(hardButton.center(), Palette::Black);
		}
	}

	void Terminate() 
	{
		isSelectDifficulty = false;
	}

	bool IsScreenChangeOK() 
	{
		return true;
	}
}
