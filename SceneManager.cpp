#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "StartScene.h"
#include "SecondScene.h"
SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

HRESULT SceneManager::Init()
{
    startScene = new StartScene();
    secondScene = new SecondScene();
    AddScene("start", startScene);
    _curScene = startScene;
    _curScene->Init();
    return S_OK;
}

void SceneManager::Update()
{
    _curScene->Update();
}

void SceneManager::Render()
{
    _curScene->Render();
}

void SceneManager::Release()
{
}

void SceneManager::AddScene(string sceneName, Scene* scene)
{
    sceneMap.insert(pair<string, Scene*>(sceneName, scene));
}

void SceneManager::LoadScene(string sceneName)
{
    _curScene->Release();
    sceneIter = sceneMap.find(sceneName);
    if (sceneIter != sceneMap.end()) {
        _curScene = sceneIter->second;
    }
}

Scene* SceneManager::GetScene(string sceneName)
{
    sceneIter = sceneMap.find(sceneName);
    if (sceneIter != sceneMap.end()) {
        return sceneIter->second;
    }
    return nullptr;
}
