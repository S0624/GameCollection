#pragma once

//	プロトタイプ宣言
class SceneManager;
class InputState;

class SceneBase
{
protected:
	SceneManager& m_manager;		//シーンマネージャへの参照
private:

public:
	SceneBase(SceneManager& manager) : m_manager(manager) {}
	virtual ~SceneBase() {};
	//シーンを更新する
	virtual void Update(const InputState& input) = 0;
	//シーンを描画する
	virtual void Draw() = 0;

};

