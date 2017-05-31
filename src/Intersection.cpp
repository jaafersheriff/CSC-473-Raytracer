#include "Intersection.hpp"

const static float EPSILON = 0.0001f;

Intersection::Intersection(Scene &scene, Ray& ray, int spatial_flag) {
  this->ray = ray;
  this->hit = false;
  this->t = std::numeric_limits<float>::max();

  for (unsigned int i = 0; i < scene.objects.size(); i++) {
    createIntersection(scene.objects[i], ray);
  }
  if (spatial_flag) {
    boxTraversal(scene.rootBox, ray);
  }
}

void Intersection::createIntersection(GeoObject *object, Ray &ray) {
   // Transform ray into object's object space
   glm::vec3 p = glm::vec3(object->inv_M * glm::vec4(ray.position, 1.0f));
   glm::vec3 d = glm::vec3(object->inv_M * glm::vec4(ray.direction, 0.0f));
   Ray objectRay(p, d);

   float obj_t = object->intersect(objectRay);
   if (obj_t > EPSILON && obj_t < this->t) {
      this->hit = true;
      this->t = obj_t;
      this->object = object;
      this->objectRay = objectRay;
      this->point = this->ray.calculatePoint(this->t);

      // Coordinate transform normal
      glm::vec3 obj_normal = this->object->findNormal(this->objectRay.calculatePoint(this->t));
      glm::vec3 world_normal = glm::vec3(glm::transpose(this->object->inv_M) * glm::vec4(obj_normal, 0.0f));
      this->normal = glm::normalize(world_normal);
  }
}

void Intersection::boxTraversal(Scene::BoxNode* node, Ray& ray) {
   if (node->boundingBox.intersect(ray) > EPSILON) {
      // Base case
      if (node->objects.size() <= 1) {
         createIntersection(node->objects[0], ray);
         return;
      }
      // Travesal
      float left_t = std::numeric_limits<float>::max();
      float right_t = std::numeric_limits<float>::max();
      
      if (node->leftChild != nullptr) {
         left_t = node->leftChild->boundingBox.intersect(ray);
      }
      if (node->rightChild != nullptr) {
         right_t = node->rightChild->boundingBox.intersect(ray);
      }
      if (left_t > EPSILON && left_t < right_t) {
        boxTraversal(node->leftChild, ray);
      }
      else if (right_t > EPSILON) {
         boxTraversal(node->rightChild, ray);
      }
   }
}

void Intersection::print() {
   if (!hit) {
      std::cout << "No Hit" << std::endl;
      return;
   }

   std::cout << "T = " << t << std::endl;
   std::cout << "Object Type: " << object->type << std::endl;
}
