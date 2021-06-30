#include "stdafx.h"
#include "EnemyManager.h"

HRESULT EnemyManager::Init()
{
	for (int i = 0; i < SECTOR_NUM; i++)
	{
		_isActiveSector[i] = false;
	}
	_spawnPointV[0] = 600;
	_sectorEnemyIdxV[0].push_back({ 0, 0 });
	_curSector = 0;
	return S_OK;
}

void EnemyManager::Update()
{
	for (int i = 0; i < SECTOR_NUM; i++)
	{
		if (_isActiveSector[i] == false && _playerTr->GetX() >= _spawnPointV[i])
		{
			_sectorEnemyV.clear();
			vector<GameObject*> sectorEnemyV = GetSectorEnemy();
			for (int j = 0; j < sectorEnemyV.size(); j++)
			{
				sectorEnemyV[j]->SetActive(true);
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
	vector<GameObject*> sectorEnemyV;
	for (int i = 0; i < _sectorEnemyIdxV[_curSector].size(); i++) {
		TYPE enemyType = _sectorEnemyIdxV[_curSector][i].first;
		int enemyIdx = _sectorEnemyIdxV[_curSector][i].second;
		sectorEnemyV.push_back(_enemyV[enemyType][enemyIdx]);
	}
	return sectorEnemyV;
}

bool EnemyManager::IsClearSector()
{
	for (int i = 0; i < _sectorEnemyIdxV[_curSector].size(); i++) {
		TYPE enemyType = _sectorEnemyIdxV[_curSector][i].first;
		int enemyIdx = _sectorEnemyIdxV[_curSector][i].second;
		if (_enemyV[enemyType][enemyIdx]->isActive == true)
			return false;
	}
	return true;
}

void EnemyManager::SetPlayerTransform(Transform* playerTr)
{
	_playerTr = playerTr;
	for (int i = 0; i < TYPE_NUM; i++)
	{
		for (int j = 0; j < _enemyV[i].size(); j++)
		{
			_enemyV[i][j]->GetComponent<EnemyAI>()->SetPlayer(_playerTr->gameObject);
		}
	}
}
