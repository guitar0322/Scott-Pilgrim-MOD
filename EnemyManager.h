#pragma once
#include <vector>

using namespace std;

#define SECTOR_NUM 1

#define TYPE_NUM 1

#define LUKE 0
class EnemyManager : public singletonBase<EnemyManager>
{
private:
	typedef int TYPE;
private:
	int _curSector;
	int _spawnPointV[SECTOR_NUM];
	bool _isActiveSector[SECTOR_NUM];
	vector<GameObject*> _enemyV[TYPE_NUM];
	vector<GameObject*> _sectorEnemyV;
	vector<pair<TYPE, int>> _sectorEnemyIdxV[SECTOR_NUM];
	Transform* _playerTr;
public:
	HRESULT Init();
	void Update();
	void Render();
	void Release();

	vector<GameObject*>* GetEnemyVAddress(int type) { return &(_enemyV[type]); }
	vector<GameObject*> GetSectorEnemy();
	bool IsClearSector();

	int GetSectorNum() const { return _curSector; }
	void SetSectorNum(int sectorNum) { _curSector = sectorNum; }

	void SetPlayerTransform(Transform* playerTr);

	void Clear() { _curSector++; }
};

