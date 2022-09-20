#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
    if (num_leaves <= 2) {
        this->left = objects[0];
        insert_box_into_box(objects[0]->box, this->box);
        if (num_leaves == 2) {
            this->right = objects[1];
            insert_box_into_box(objects[1]->box, this->box);
        }
        else {
            this->right = nullptr;
        }
    }
    else {
        std::vector<double> min_axis(3, std::numeric_limits<double>::infinity());
        std::vector<double> max_axis(3, -std::numeric_limits<double>::infinity());
        for (auto obj : objects) {
            for (int i = 0; i < 3; ++i) {
                double min = obj->box.min_corner[i];
                double max = obj->box.max_corner[i];
                if (min < min_axis[i]) {
                    min_axis[i] = min;
                }
                if (max > max_axis[i]) {
                    max_axis[i] = max;
                }       
            }
        }
        int axis = 0;
        for (int i = 1; i < 3; ++i) {
            if (max_axis[i] - min_axis[i] > max_axis[axis] - min_axis[axis]) {
                axis = i;
            }         
        }
        auto comp = [&axis](const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b) {
            return a->box.center()[axis] < b->box.center()[axis];
        };
        std::vector<std::shared_ptr<Object>> obj(objects);
        std::sort(obj.begin(), obj.end(), comp);
        auto start = obj.begin();
        auto middle = obj.begin() + num_leaves / 2;
        auto end = obj.end();

        this->left = std::make_shared<AABBTree>(std::vector<std::shared_ptr<Object>>(start, middle), this->depth + 1);
        this->right = std::make_shared<AABBTree>(std::vector<std::shared_ptr<Object>>(middle, end), this->depth + 1);
        insert_box_into_box(this->left->box, this->box);
        insert_box_into_box(this->right->box, this->box);
    }
}
