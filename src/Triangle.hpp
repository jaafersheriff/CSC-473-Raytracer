// Triangle class extends GeoObject

#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "GeoObject.hpp"

class Triangle: public GeoObject {
public:
	Triangle();
	
	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 v3;

	float intersect(const Ray &);
	glm::vec3 findNormal(const glm::vec3);
	
	void print();
};

#endif
