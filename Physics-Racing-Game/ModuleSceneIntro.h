#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class SceneObjectGenerator
{
	Application* App;
public:
	SceneObjectGenerator(Application* App);
	PhysBody3D* CreateRectangle(vec3 position = { 0,0,0 }, vec3 rotation = { 0,0,0 }, vec3 scale = { 1,1,1 }, float mass = 0, bool isSensor = false);
	void CreateSphere(vec3 position = { 0,0,0 }, vec3 rotation = { 0,0,0 }, float radius = 1.0f, float mass = 0, bool isSensor = false);
	void CreateCylinder(vec3 position = { 0,0,0 }, vec3 rotation = { 0,0,0 }, float radius = 1.0f, float height = 2.0f, float mass = 0, bool isSensor = false);
	void CreateCurve(vec3 position = { 0,0,0 }, vec3 rotation = { 0,0,0 }, float radius = 20, float targetAngle = 90);
	void RenderObjects();
private:
	p2List<Primitive*> ground;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:
	/*
	PhysBody3D* pb_snake[MAX_SNAKE];
	Sphere s_snake[MAX_SNAKE];

	PhysBody3D* pb_snake2[MAX_SNAKE];
	Sphere s_snake2[MAX_SNAKE];
	*/

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

	SceneObjectGenerator sog = SceneObjectGenerator(App);

	PhysBody3D* zLimiter;
	PhysBody3D* finishLine;
	p2List<PhysBody3D*> checkpoints;
};