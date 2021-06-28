#pragma once
#include <Siv3D.hpp>

// 共通Header
// アプリケーション全体的に共通して使いたい定義や関数
// 等を入れて行きます～

// 画面遷移中のトランジションを表示する時間の長さ
const float TRANSITION_TIME = 0.5f;

// 関数ポインターの宣言
// 戻り値なしタイプ
typedef void (*FunctionPointer)();

// 戻り値に判定結果を返す(true/falseを返す)タイプ
typedef bool (*BoolFunctionPointer)();

// ゲームの各画面に共通して存在する処理の定義
typedef struct GameScreen {
	FunctionPointer Init;		// 初期化
	FunctionPointer Update;		// 更新
	FunctionPointer Draw;		// 描画
	FunctionPointer Terminate;	// 終了（リセット、解放)
	BoolFunctionPointer IsScreenChangeOK; // 画面遷移可能か判定
};

// ゲーム内に存在する画面の定義をしていきます
enum Screen {
	STitle,		//	0 (起動時にまず表示される画面)
	SScreen1,	//	1
	SScreen2,	//	2
	// 画面が増えて行く場合は
	// SScreen3,
	// SScreen4,
	// ...,
	// のようにここで定義を追加して行きます
};

enum GameResult {
	WIN,
	LOSE
};

enum GameDifficulty {
	EASY,
	HARD
};

struct GlobalData {
	GameResult result;
	GameDifficulty difficulty;
};

struct EnemyData {
	int MovePossibility;
	int YMoveByXMin;
	int YMoveByXMax;
};