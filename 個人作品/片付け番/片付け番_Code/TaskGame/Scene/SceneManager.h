#pragma once

#include<deque>

//　プロトタイプ宣言
class SceneBase;
class InputState;

class SceneManager
{
private:
	std::deque<SceneBase*> m_scene;

public:
	//シーンの切り替えを行う処理
	void ChangeScene(SceneBase* scene);
	//シーンを上に詰む
	void PushScene(SceneBase* scene);
	//一番上のシーンを削除する
	void PopScene();
	//更新を行う
	void Update(const InputState& input);
	//シーンの描画
	void Draw();

};

