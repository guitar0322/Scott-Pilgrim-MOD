#pragma once
#include <vector>
#include "CameraControler.h"
class Player;
using namespace std;

#define SECTOR_NUM 2

#define TYPE_NUM 4

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
	Player* _playerComponent;
	CameraControler* _cameraControler;
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

	void SetPlayerTransform(GameObject* player);
	void SetCameraControler(CameraControler* cameraControler) { _cameraControler = cameraControler; }

	void Clear();
	void MakeSectorEnemyV();

	void DeadEvent(GameObject* deadObject);

	void InitSectorEnemyIdx();
};

