#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
    if (ray_intersect_box(ray, this->box, min_t, max_t)) {
        double left_t, right_t;
        std::shared_ptr<Object> left_des = this->left;
        std::shared_ptr<Object> right_des = this->right;
        bool left_hit = this->left && this->left->ray_intersect(ray, min_t, max_t, left_t, left_des);
        bool right_hit = this->right && this->right->ray_intersect(ray, min_t, max_t, right_t, right_des);
        if (left_hit && right_hit) {
            if (left_t < right_t) {
                t = left_t;
                descendant = left_des;
            }
            else {
                t = right_t;
                descendant = right_des;
            }
        }
        else if (left_hit) {
            t = left_t;
            descendant = left_des;
        }
        else if (right_hit) {
            t = right_t;
            descendant = right_des;
        }
        else {
            return false;
        }
        return true; 
    }
    else {
        return false;
    }
}

