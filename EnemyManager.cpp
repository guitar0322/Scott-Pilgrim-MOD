#include "stdafx.h"
#include "EnemyManager.h"
#include "Player.h"
HRESULT EnemyManager::Init()
{
	for (int i = 0; i < SECTOR_NUM; i++)
	{
		_isActiveSector[i] = false;
	}
	_spawnPointV[0] = 600;
	_spawnPointV[1] = 1500;
	_sectorEnemyIdxV[0].push_back({ 0, 0 });
	_sectorEnemyIdxV[1].push_back({ 0, 1 });
	_curSector = 0;
	return S_OK;
}

void EnemyManager::Update()
{
	for (int i = 0; i < SECTOR_NUM; i++)
	{
		if (_isActiveSector[i] == false && _playerTr->GetX() >= _spawnPointV[i])
		{
			MakeSectorEnemyV();
			for (int j = 0; j < _sectorEnemyV.size(); j++)
			{
				_sectorEnemyV[j]->SetActive(true);
			}
			_isActiveSector[i] = true;
		}
	}

	for (int i = 0; i < TYPE_NUM; i++)
	{
		for (int j = 0; j < _enemyV[i].size(); j++)
		{
			_enemyV[i][j]->Update();
		}
	}
}

void EnemyManager::Render()
{
}

void EnemyManager::Release()
{
}

vector<GameObject*> EnemyManager::GetSectorEnemy()
{
	return _sectorEnemyV;
}

bool EnemyManager::IsClearSector()
{
	for (int i = 0; i < _sectorEnemyIdxV[_curSector].size(); i++) {
		TYPE enemyType = _sectorEnemyIdxV[_curSector][i].first;
		int enemyIdx = _sectorEnemyIdxV[_curSector][i].second;
		if (_enemyV[enemyType][enemyIdx]->isActive == true)
			return false;
	}

	_cameraControler->UnLock();
	return true;
}

void EnemyManager::SetPlayerTransform(Transform* playerTr)
{
	_playerTr = playerTr;
	_playerComponent = _playerTr->gameObject->GetComponent<Player>();
	for (int i = 0; i < TYPE_NUM; i++)
	{
		for (int j = 0; j < _enemyV[i].size(); j++)
		{
			_enemyV[i][j]->GetComponent<EnemyAI>()->SetPlayer(_playerTr->gameObject);
		}
	}
}

void EnemyManager::Clear()
{
	_curSector++;
	_cameraControler->UnLock();
}

void EnemyManager::MakeSectorEnemyV()
{
	_sectorEnemyV.clear();
	for (int i = 0; i < _sectorEnemyIdxV[_curSector].size(); i++) {
		TYPE enemyType = _sectorEnemyIdxV[_curSector][i].first;
		int enemyIdx = _sectorEnemyIdxV[_curSector][i].second;
		_sectorEnemyV.push_back(_enemyV[enemyType][enemyIdx]);
	}
}

void EnemyManager::DeadEvent(GameObject* deadObject)
{
	for (int i = 0; i < _sectorEnemyIdxV[_curSector].size(); i++) {
		TYPE enemyType = _sectorEnemyIdxV[_curSector][i].first;
		int enemyIdx = _sectorEnemyIdxV[_curSector][i].second;
		if (_enemyV[enemyType][enemyIdx]->isActive == true)
			return;
	}
	Clear();
	return;
}
