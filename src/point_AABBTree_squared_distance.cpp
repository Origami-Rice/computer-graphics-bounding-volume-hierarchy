#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <utility>
typedef std::pair<std::shared_ptr<Object>, double> queue_obj;

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
    struct comparator {
        bool operator() (const queue_obj& a, const queue_obj& b) const
        {
            return a.second > b.second;
        }
    };
    std::priority_queue<queue_obj, std::vector<queue_obj>, comparator> queue;  
    queue.push(std::make_pair(root, point_box_squared_distance(query, root->box))); 

    while (!queue.empty()) {
        queue_obj top = queue.top();
        queue.pop();
        double s = top.second;
        if (s < max_sqrd) {
            std::shared_ptr<AABBTree> node = std::dynamic_pointer_cast<AABBTree>(top.first);
            if (!node) {
                if (s >= min_sqrd) {
                    sqrd = s;
                    descendant = top.first;
                    return true;
                }
                else {
                    continue; 
                }
            }
            if (node->left) {
                s = point_box_squared_distance(query, node->left->box);
                if (s < max_sqrd) {
                    queue.push(std::make_pair(node->left, s));
                }
            }
            if (node->right) {
                s = point_box_squared_distance(query, node->right->box);
                if (s < max_sqrd) {
                    queue.push(std::make_pair(node->right, s));
                }     
            }
        }
        else {
            return false;
        }
    }
    return false;
}
