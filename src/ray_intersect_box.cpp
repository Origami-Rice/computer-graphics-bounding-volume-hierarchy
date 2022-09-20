#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
    double min, max;
    double start = -std::numeric_limits<double>::infinity();
    double end = std::numeric_limits<double>::infinity();
    for (int i = 0; i < 3; ++i) {
        if (ray.direction[i] == 0) {
            min = -std::numeric_limits<double>::infinity();
            max = std::numeric_limits<double>::infinity();
            if (ray.origin[i] < box.min_corner[i] || ray.origin[i] > box.max_corner[i]) {
                return false;
            }
        }
        else if (ray.direction[i] > 0) {
            min = (box.min_corner[i] - ray.origin[i]) / ray.direction[i];
            max = (box.max_corner[i] - ray.origin[i]) / ray.direction[i];
        }
        else {
            min = (box.max_corner[i] - ray.origin[i]) / ray.direction[i];
            max = (box.min_corner[i] - ray.origin[i]) / ray.direction[i];
        }
        if (min > start) {
            start = min;
        }
        if (max < end) {
            end = max;
        } 
    }
    return end > min_t && start < max_t && end > start;
}
