#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
    for (int i = 0; i < 3; ++i) {
        B.min_corner[i] = std::min(A.min_corner[i], B.min_corner[i]);
        B.max_corner[i] = std::max(A.max_corner[i], B.max_corner[i]);
    }
}

