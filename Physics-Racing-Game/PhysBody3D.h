#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "Primitive.h"

class btRigidBody;
class Module;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	vec3 GetPos();
	void SetRotation(float x, float y, float z);
	vec3 GetRotation();
	vec3 GetVelocity();

public:
	btRigidBody* body = nullptr;
	p2List<Module*> collision_listeners;
	bool is_sensor = false;
};

#endif // __PhysBody3D_H__