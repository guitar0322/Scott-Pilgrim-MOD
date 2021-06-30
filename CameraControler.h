#pragma once
#define SECTOR_NUM 1
class CameraControler
{
private:
    Transform* _playerTr;
    int _camLockPoint[SECTOR_NUM];
    bool _isLockPoint[SECTOR_NUM];
    bool _lock;
    float _lockTime;
    float _camSpeed;
    float _playerX;
    float _camX;
public:
    void Init();
    void Update();

    void SetPlayerTransform(Transform* playerTr) { _playerTr = playerTr; }
};

