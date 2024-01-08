#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// Create map
	// {position.x, position.y, position.z}, 
	// {rotation.x, rotation.y, rotation.z}, 
	// {scale.x, scale.y, scale.z}
	sog.CreateRectangle({ 0,0,0 }, { 0,0,0 }, { 10,10,10 });

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

SceneObjectGenerator::SceneObjectGenerator(Application* App)
{
	this->App = App;
}

PhysBody3D* SceneObjectGenerator::CreateRectangle(vec3 position, vec3 rotation, vec3 scale, float mass, bool isSensor)
{
	Cube* c = new Cube();
	c->size = scale;
	c->SetRotation(rotation.x, rotation.y, rotation.z);
	c->SetPos(position.x, position.y, position.z);
	if (!isSensor)ground.add((Primitive*)c);

	return App->physics->AddBody(*c, mass);
}

void SceneObjectGenerator::CreateSphere(vec3 position, vec3 rotation, float radius, float mass, bool isSensor)
{
	Sphere* s = new Sphere();
	s->SetRotation(rotation.x, { 1,0,0 });
	s->SetRotation(rotation.y, { 0,1,0 });
	s->SetRotation(rotation.z, { 0,0,1 });
	s->SetPos(position.x, position.y, position.z);
	s->radius = radius;
	if (!isSensor)ground.add((Primitive*)s);

	App->physics->AddBody(*s, mass);
}

void SceneObjectGenerator::CreateCylinder(vec3 position, vec3 rotation, float radius, float height, float mass, bool isSensor)
{
	Cylinder* c = new Cylinder();
	c->SetRotation(rotation.x, { 1,0,0 });
	c->SetRotation(rotation.y, { 0,1,0 });
	c->SetRotation(rotation.z, { 0,0,1 });
	c->SetPos(position.x, position.y, position.z);
	c->radius = radius;
	c->height = height;
	if (!isSensor)ground.add((Primitive*)c);

	App->physics->AddBody(*c, mass);
}

void SceneObjectGenerator::CreateCurve(vec3 position, vec3 rotation, float radius, float targetAngle)
{
	float segmentLength = 2.0;
	float angle = 0;
	int segmentCount = radius * 2;

	for (int i = 0; i <= segmentCount; i++)
	{
		{
			CreateRectangle({ position.x + i * segmentLength / segmentCount * (float)cos((rotation.x + angle) / 2 * 3.1415 / 180) * radius, position.y ,position.z - i * segmentLength / segmentCount * (float)sin((rotation.z + angle) / 2 * 3.1415 / 180) * radius }, { rotation.x,rotation.y + angle,rotation.z }, { segmentLength,1,10 });
			angle += targetAngle / segmentCount;
		}
	}
}

void SceneObjectGenerator::RenderObjects()
{
	p2List_item<Primitive*>* groundSegment = ground.getFirst();
	while (groundSegment != NULL)
	{
		groundSegment->data->Render();
		groundSegment = groundSegment->next;
	}
}
