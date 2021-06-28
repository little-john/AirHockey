#include "Game.h"

// 実装して行く各画面へのinclude
#include "Title.h"
#include "Screen1.h"
#include "Screen2.h"

namespace Game
{
	// 表示（実行）中の画面
	Screen current;

	// 遷移先の画面
	Screen next;

	// 1つ前の画面
	Screen previous;

	// 全ての画面への参照
	Array<GameScreen> screens;

	// トランジション用
	bool isFadeIn = false;	// フェードアウト再生中
	bool isFadeOut = false;	// フェードイン再生中
	float timeElapsedFromTransition = 0.0f;	// トランジション開始してからの経過時間
	FunctionPointer onFadeInFinish;	// フェードインが終了した時に実行したい処理

	GlobalData globalData;

	EnemyData enemyData[2];

	void Init() {

		// Common.hのScreenで定義した画面の一番目から設定
		current = (Screen)0;

		// １つ前の画面はまだ内ので同じく一番目の画面から
		previous = (Screen)0;

		// 全画面への参照にScreenの定義の順番と合わせて
		// 各画面を生成して、追加する
		screens << Title::CreateScreen();
		screens << Screen1::CreateScreen();
		screens << Screen2::CreateScreen();
		// 画面を増やして行きたい場合は、
		// 以下のように
		// screens << ScreenXXX:CreateScreen();
		// (ScreenXXX)の所は実装する画面の名前を各

		// 実行する画面の初期化
		screens[current].Init();

		// 全画面でアクセスできるデータ生成
		globalData = GlobalData();

		// ゲームの難易度データロード
		JSONReader reader(U"EnemySettings.txt");
		if (!reader) {
			throw Error(U"Load Setting Fail");
		}
		
		// Easyモードの設定をロード
		EnemyData easy;
		easy.MovePossibility = reader[U"EASY.MOVE_POSSIBLITY"].get<int>();
		easy.YMoveByXMin = reader[U"EASY.Y_MOVE_BY_X_MIN"].get<int>();
		easy.YMoveByXMax = reader[U"EASY.Y_MOVE_BY_X_MAX"].get<int>();

		// Hardモードの設定をロード
		EnemyData hard;
		hard.MovePossibility = reader[U"HARD.MOVE_POSSIBLITY"].get<int>();
		hard.YMoveByXMin = reader[U"HARD.Y_MOVE_BY_X_MIN"].get<int>();
		hard.YMoveByXMax = reader[U"HARD.Y_MOVE_BY_X_MAX"].get<int>();

		enemyData[0] = easy;
		enemyData[1] = hard;

		// 設定ファイルを閉じる
		reader.close();
	}

	void Update() {

		if (isFadeIn)
		{
			timeElapsedFromTransition += Scene::DeltaTime();
			if (timeElapsedFromTransition >= TRANSITION_TIME)
			{
				timeElapsedFromTransition = 0.0f;
				isFadeOut = true;
				isFadeIn = false;
				onFadeInFinish();

				// 遷移先の画面の初期化
				screens[current].Init();
			}

			return;
		}
		else if (isFadeOut)
		{
			timeElapsedFromTransition += Scene::DeltaTime();
			if (timeElapsedFromTransition >= TRANSITION_TIME)
			{
				timeElapsedFromTransition = 0.0f;
				isFadeOut = false;
				isFadeIn = false;
			}

			return;
		}

		// バックスペースキーが押されて
		if (KeyBackspace.down())
		{
			// 表示中の画面が画面遷移可能の場合
			if (screens[current].IsScreenChangeOK())
			{
				// 1つ前の画面へ遷移してみる
				if (BackToPreviousScreen())
				{
					// 成功したら表示中のUpdat処理は中断するので
					// この場でreturnします
					return;
				}
			}
		}

		// 表示中の画面の更新
		screens[current].Update();
	}

	void Draw() {

		// 表示中の画面の描画
		if (isFadeIn)
		{
			float alpha = Math::Lerp(0, 1, timeElapsedFromTransition / TRANSITION_TIME);
			Rect(0, 0, Scene::Width(), Scene::Height()).draw(ColorF(1.0, alpha));
		}
		else if (isFadeOut)
		{
			float alpha = Math::Lerp(1, 0, timeElapsedFromTransition / TRANSITION_TIME);
			Rect(0, 0, Scene::Width(), Scene::Height()).draw(ColorF(1.0, alpha));
		}
		else
		{
			screens[current].Draw();
		}
	}

	void CallbackForNextScreen()
	{
		// 表示中の画面を終了
		screens[current].Terminate();

		// 1つ前の画面に表示中の画面を代入
		previous = current;

		// 遷移先の画面を現在の方に代入
		current = next;
	}

	void CallbackForBackScreen()
	{
		// 表示中の画面を終了
		screens[current].Terminate();

		// 表示中の画面に1つ前の画面を代入
		current = previous;

		// 1つ前の画面変数が最初の画面でなければ
		if (previous > 0) {
			// 1引いて代入
			previous = (Screen)(previous - 1);
		}
	}

	void ChangeScreen(Screen screenName)
	{
		// 遷移する画面と表示中の画面が同じでなければ
		if (screenName != current) {

			next = screenName;

			onFadeInFinish = (FunctionPointer)(CallbackForNextScreen);

			isFadeIn = true;
		}
	}

	bool BackToPreviousScreen()
	{
		// 表示中の画面が一番最初の画面でなければ
		if (current != (Screen)0)
		{
			onFadeInFinish = nullptr;
			onFadeInFinish = (FunctionPointer)(CallbackForBackScreen);

			isFadeIn = true;

			// 遷移成功のためtrueを返す
			return true;
		}

		// 遷移しなかったので、falseを返す
		return false;
	}

	GlobalData* GetGlobalData() {
		return &globalData;
	}

	EnemyData* GetEnemyData(GameDifficulty difficulty)
	{
		return &enemyData[(int)difficulty];
	}
}