#include "Sphere.h"

using namespace glm;
using namespace std;

Sphere::Sphere() {
	this->translate = vec3(0, 0, 0);

	this->center = vec3(0, 0, 0);
	this->radius = 0;
	this->pigment = vec3(0, 0, 0);
	this->ambient = 0;
	this->diffuse = 0;
}

float Sphere::intersect(Ray &ray) {
	float A = dot(ray.direction, ray.direction);
	vec3 pc = ray.position-center;
	float B = dot(ray.direction + ray.direction, pc);
	float C = dot(pc, pc) - radius*radius;

	float det = sqrt(B*B-4*A*C);
	float t1 = -B+det/(2*A);
	float t2 = -B-det/(2*A);
	
	return t1 > t2 ? t1 : t2;
}

void Sphere::print() {
	cout << "- Type: Sphere" << endl;
	cout << "- Center: {";
		cout << center.x << " " << center.y << " " << center.z;
		cout << "}" << endl;
	cout << "- Radius: ";
		cout << radius << endl;
	cout << "- Color: {";
		cout << pigment.x << " " << pigment.y << " " << pigment.z;
		cout << "}" << endl;
	cout << "- Material:" << endl;
		cout << "\t- Ambient: ";
			cout << ambient << endl;
		cout << "\t- Diffuse: ";
			cout << diffuse << endl;
	cout << "- Transform:" << endl;
		cout << "\t- Translate: {"; 
			cout << translate.x << " " << translate.y << " " << translate.z;
			cout << "}" << endl;
}
