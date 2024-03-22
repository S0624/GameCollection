#include "SceneManager.h"
#include"SceneBase.h"

void SceneManager::ChangeScene(SceneBase* scene)
{
	if (!m_scene.empty())
	{
		delete m_scene.front();		//topはてっぺんの要素を返す
		m_scene.pop_front();		//一個減らす
	}
	m_scene.push_front(scene);		//一個増える
}

void SceneManager::PushScene(SceneBase* scene)
{
	m_scene.push_front(scene);		//一個増える
}

void SceneManager::PopScene()
{
	if (m_scene.size() > 1)
	{
		//ポップの結果、シーンがゼロにならないようにする	
		delete m_scene.front();
		m_scene.pop_front();
	}
}

void SceneManager::Update(const InputState& input)
{
	m_scene.front()->Update(input);
}

void SceneManager::Draw()
{
	for (int i = static_cast<int>(m_scene.size()) - 1; i >= 0; --i)
	{
		m_scene[i]->Draw();
	}
}
