#pragma once
#define PI 3.14159f
#define PI2 PI * 2
#include "GameObject.h"
#include "ParticleSystem.h"
#include "Renderer.h"
#include "AnimationClip.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "PlayerControler.h"
#include "TriggerTest.h"
#include "ObjectInfo.h"
#include "UIRenderer.h"
#include "Cam.h"
#include "Camera.h"
#include "UIBase.h"
#include "Text.h"
#include "Box.h"
#include "Zone.h"
#include "Item.h"
#include "ImageObject.h"
#include "Character.h"
#include "Ground.h"
#include "Controler.h"
#include "ZOrder.h"
#include "ItemObject.h"
#include "Enemy.h"
#include "Luke.h"
#include "EnemyAI.h"
#include "DebugText.h"
#include <typeinfo>

typedef RECT ELLIPSE;
typedef struct tagPOINTF {
	float x;
	float y;
}POINTF;

namespace HDY_UTIL
{
	float GetDistance(float x1, float y1, float x2, float y2);
	template <typename T>
	T GetDistance(T x1, T x2);

	float GetAngle(float x1, float y1, float x2, float y2);

	int GetCenterX(RECT rc);
	int GetCenterY(RECT rc);
	POINT GetCenter(RECT rc);
	POINTF GetCenterF(RECT rc);
	int GetWidth(RECT rc);
	int GetHeight(RECT rc);
	int GetRadius(ELLIPSE rc);
	template <typename T>
	T GetCenter(T a, T b);
	POINTF GetCollisionPoint(RECT rc1, RECT rc2);
	POINTF MoveTowardTo(float x1, float y1, float x2, float y2, float speed, int limit = 0);
	POINTF MoveTowardTo(RECT& rc1, RECT& rc2, float speed, int limit = 0);
}