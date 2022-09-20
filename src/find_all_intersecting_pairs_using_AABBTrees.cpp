#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
    leaf_pairs.clear(); 
    if (!box_box_intersect(rootA->box, rootB->box)) {
        return;
    }
    std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object> >> queue; 
    queue.push_back(std::make_pair(rootA, rootB));

    while (!queue.empty()) {
        auto nodes = queue.front();
        queue.pop_front();
        std::shared_ptr<AABBTree> node_A = std::dynamic_pointer_cast<AABBTree>(nodes.first);
        std::shared_ptr<AABBTree> node_B = std::dynamic_pointer_cast<AABBTree>(nodes.second);
        if (!node_A && !node_B) {
            leaf_pairs.push_back(std::make_pair(nodes.first, nodes.second));
        }
        else if (!node_A) {
            if (node_B->left && box_box_intersect(nodes.first->box, node_B->left->box)) {
                queue.push_back(std::make_pair(nodes.first, node_B->left));
            }
            if (node_B->right && box_box_intersect(nodes.first->box, node_B->right->box)) {
                queue.push_back(std::make_pair(nodes.first, node_B->right));
            }             
        }
        else if (!node_B) {
            if (node_A->left && box_box_intersect(nodes.second->box, node_A->left->box)) {
                queue.push_back(std::make_pair(node_A->left, nodes.second));
            }    
            if (node_A->right && box_box_intersect(nodes.second->box, node_A->right->box)) {
                queue.push_back(std::make_pair(node_A->right, nodes.second));
            }          
        }
        else {
            if (node_A->left && node_B->left && box_box_intersect(node_A->left->box, node_B->left->box)) {
                queue.push_back(std::make_pair(node_A->left, node_B->left));
            }
            if (node_A->left && node_B->right && box_box_intersect(node_A->left->box, node_B->right->box)) {
                queue.push_back(std::make_pair(node_A->left, node_B->right));
            }
            if (node_A->right && node_B->left && box_box_intersect(node_A->right->box, node_B->left->box)) {
                queue.push_back(std::make_pair(node_A->right, node_B->left));
            }
            if (node_A->right && node_B->right && box_box_intersect(node_A->right->box, node_B->right->box)) {
                queue.push_back(std::make_pair(node_A->right, node_B->right));
            }
        }
    }
}
