#include "Screen1.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "Ball.h"
#include "Logic.h"

namespace Screen1
{
	//RoundRect screen2Button;
	//Transition buttonTransition;
	Player::Player user;
	Player::Player cpu;

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
		AudioAsset(U"GameBGM").play();

		Scene::SetBackground(Palette::Black);
		//screen2Button = RoundRect(Scene::Center().x - 150, Scene::Height() - 100, 300, 50, 15);
		//buttonTransition = Transition(0.4s, 0.2s);

		user = Player::CreatePlayer(Player::Type::User);
		cpu = Player::CreatePlayer(Player::Type::CPU);

		Player::Init(user);
		Player::Init(cpu);

		Stage::Init();
		Ball::Init(Scene::Center());
	}

	void Update()
	{
		/*if (screen2Button.leftClicked()) 
		{
			Game::ChangeScreen(SScreen2);
		}

		buttonTransition.update(screen2Button.mouseOver());*/
		
		Stage::Update(user, cpu);
		Ball::Update();
		Player::Update(user);
		Player::Update(cpu);
		
		// ゲーム終了判定
		if (Logic::ValidateGameFinish(user,cpu))
		{
			// 結果画面へ遷移
			Game::ChangeScreen(Screen::SScreen2);
		}
	}

	void Draw()
	{
		/*Vec2 center(Scene::Center().x, 100);
		FontAsset(U"Title")(U"ゲームスクリーン").drawAt(center.moveBy(5, 20), ColorF(0.0, 0.5));
		FontAsset(U"Title")(U"ゲームスクリーン").drawAt(center);

		screen2Button.draw(ColorF(1.0, 1 - buttonTransition.value() * 0.5f)).drawFrame(5, ColorF(0.0f, 0.5f));
		FontAsset(U"Button")(U"クレジット").drawAt(screen2Button.center(), Palette::Black);*/

		Stage::Draw();
		Ball::Draw();
		Player::Draw(user);
		Player::Draw(cpu);

		FontAsset(U"Score")(U"---").drawAt(Scene::Center().moveBy(0, 0));
	}

	void Terminate()
	{
		AudioAsset(U"GameBGM").stop();
		Stage::Terminate();
		Ball::Terminate();
		Player::Terminate(user);
		Player::Terminate(cpu);
	}

	bool IsScreenChangeOK()
	{
		return false;
	}
}
