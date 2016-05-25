#include "Application.h"
#include "Enemy_CowBoy_Green_Medium_Left.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleSceneFirst.h"

Enemy_CowBoy_Green_Medium_Left::Enemy_CowBoy_Green_Medium_Left(float x, float y) : Enemy(x, y)
{
	forward.PushBack({ 1959, 2860, 25, 40 });
	forward.PushBack({ 2004, 2860, 25, 40 });
	forward.PushBack({ 2036, 2860, 25, 40 });
	forward.PushBack({ 2072, 2860, 25, 40 });
	forward.PushBack({ 2116, 2860, 25, 40 });
	forward.PushBack({ 2164, 2860, 25, 40 });
	forward.speed = 0.20f;

	stop_shoot.PushBack({ 374, 2848, 25, 40 });
	stop_shoot.PushBack({ 374, 2848, 25, 40 });
	stop_shoot.speed = 0.04f;
	stop_shoot.loop = true;

	dieshot.PushBack({ 1911, 2860, 25, 40 });
	dieshot.PushBack({ 1864, 2860, 25, 40 });
	dieshot.PushBack({ 1815, 2860, 25, 40 });
	dieshot.PushBack({ 1767, 2860, 25, 40 });
	dieshot.speed = 0.15f;
	dieshot.loop = false;

	dieexplotion.PushBack({ 1722, 2860, 25, 40 });
	dieexplotion.PushBack({ 1671, 2860, 25, 40 });
	dieexplotion.PushBack({ 1629, 2971, 25, 40 });
	dieexplotion.PushBack({ 156, 2971, 25, 40 });
	dieexplotion.speed = 0.3f;



	collider = App->collision->AddCollider({ 0, -20, 24, 55 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	path.PushBack({ 1.0f, 0 }, 95, &forward);
	path.PushBack({ 0, 0 }, 67, &stop_shoot);
	path.PushBack({ 1.0f, 0 }, 95, &forward);
	path.PushBack({ 0, 0 }, 67, &stop_shoot);
	path.PushBack({ 1.0f, 0 }, 95, &forward);
	path.loop = true;

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_CowBoy_Green_Medium_Left::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);

	if (dieshot.Finished() == true)
	{
		finished = true;
	}
}

void Enemy_CowBoy_Green_Medium_Left::Die()
{
	App->player->win_condition++;
	path.Erase();
	path.PushBack({ 0.0f, 0.0f }, 40, &dieshot);
	path.loop = false;
}