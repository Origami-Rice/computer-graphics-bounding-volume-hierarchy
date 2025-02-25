#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"
#include <limits>

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  bool found = false; 
  double t = 0.0;
  hit_t = std::numeric_limits<double>::infinity();  
  Eigen::RowVector3d a, b, c;
  
  for (int i = 0; i < F.rows(); ++i) {
      a = V.row(F(i, 0));
      b = V.row(F(i, 1));
      c = V.row(F(i, 2));
      if (ray_intersect_triangle(ray, a, b, c, min_t, max_t, t) && t < hit_t) {
          hit_t = t;
          hit_f = i;
          found = true;
      }
  }
  return found;
}
