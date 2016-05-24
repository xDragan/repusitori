#include "Application.h"
#include "Enemy_Girl.h"
#include "Module_Points.h"
#include "Enemy.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"

Enemy_Girl::Enemy_Girl(float x, float y) : Enemy(x, y)
{
	walk.PushBack({ 72, 3123, 34, 45 });
	walk.PushBack({ 115, 3123, 34, 45 });
	walk.speed = 0.07f;

	run.PushBack({152,3123,34,45});
	run.PushBack({202,3123,34,45});
	run.PushBack({246,3123,34,45});
	run.speed = 0.10f;
	run.loop = true;
	

	dead.PushBack({291,3123,34,45});
	dead.PushBack({332,3123,34,45});
	dead.PushBack({371,3123,34,45});
	dead.PushBack({418,3123,34,45});
	dead.PushBack({467,3108,34,45});
	dead.PushBack({512,3108,34,45});
	dead.PushBack({512,3108,34,45});
	dead.loop = false;

	dead.speed = 0.07f;
	

	path.PushBack({ 0.3f, 0 },300, &walk);

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Girl::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);

	if (dead.Finished() == true)
	{
		finished = true;
	}

	if (position.x >= SCREEN_WIDTH - 34){

		collider->type = COLLIDER_NONE;
		path.Erase();
		path.PushBack({ 0, 0 }, 40, &dead);
		path.loop = false;



	}
}

void Enemy_Girl::Die()
{
	
	 path.Erase(); 
	path.PushBack({ 1.0f, 0 }, 100, &run);

	
	
	App->enemies->AddEnemy(ENEMY_TYPES::POINTS, position.x, position.y, 1);
	App->enemies->AddEnemy(ENEMY_TYPES::POINTS, position.x + 20, position.y, 2);
	
	hit = true;

	
	
	
	
	
}