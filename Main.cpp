#include "Game.h"

void Main()
{
	Window::SetTitle(U"ゲームアプリテンプレート");

	Window::SetFullscreen(true);

	// ゲーム全体で共通して使えるFontの設定を行う

	// 画面のタイトル用
	FontAsset::Register(U"Title", 120, U"example/font/AnnyantRoman/AnnyantRoman.ttf");
	
	// ボタン用
	FontAsset::Register(U"Button", 24);
	
	// ラベル用
	FontAsset::Register(U"Label1", 18);

	// スコアー用
	FontAsset::Register(U"Score", 50, U"example/font/AnnyantRoman/AnnyantRoman.ttf");

	// ゲーム結果用
	FontAsset::Register(U"GameResult", 200, U"example/font/AnnyantRoman/AnnyantRoman.ttf");

	// BGM登録
	AudioAsset::Register(U"GameBGM", U"assets/bgm.wav");
	AudioAsset(U"GameBGM").setLoop(true);
	AudioAsset(U"GameBGM").setVolume(0.25);

	// SE登録
	AudioAsset::Register(U"HitSE", U"assets/hit.wav");
	AudioAsset::Register(U"GoalSE", U"assets/goal.wav");

	// サイズの定義を増やしたい時は以下に
	// FontAsset::Register(U"定義名", xx, yy);として設定する
	// xxの所はフォントサイズ
	// yyの所はフォントファイルのパス

	// アプリケーションの初期化
	Game::Init();

	while (System::Update())
	{
		// アプリケーションの更新
		Game::Update();

		// アプリケーションの描画
		Game::Draw();
	}
}
