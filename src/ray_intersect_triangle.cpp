#include "ray_intersect_triangle.h"
#include <Eigen/Dense>

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  Eigen::Vector3d t0 = A.transpose(); 
  Eigen::Vector3d t1 = B.transpose() - t0;
  Eigen::Vector3d t2 = C.transpose() - t0;
  Eigen::Matrix3d M;
  M << t1, t2, -1 * ray.direction;
  if (M.determinant() == 0) {
      return false;
  }
  Eigen::Vector3d x = M.inverse() * (ray.origin - t0);   
  if (x[0] < 0 || x[1] < 0 || x[0] + x[1] > 1 || x[2] < min_t || x[2] > max_t){
      return false;
  }
  else {
      t = x[2];
      return true;
  }
      
  
}

