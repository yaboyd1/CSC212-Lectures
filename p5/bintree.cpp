#include <cassert>   // Provides assert
#include <cstdlib>   // Provides NULL, std::size_t
#include <iomanip>   // Provides std::setw
#include <iostream>  // Provides std::cout
#include "bintree.h"

namespace main_savitch_10 {
    void print(binary_tree_node* node_ptr, size_t depth) {
        if (node_ptr != NULL) {
            print(node_ptr->right(), depth + 1);
            std::cout << std::setw(4 * depth) << ""; // Indent 4 * depth spaces.
            std::cout << node_ptr->data() << std::endl;
            print(node_ptr->left(),  depth + 1);
        }
    }

    binary_tree_node::binary_tree_node(const value_type& init_data, binary_tree_node* init_left, binary_tree_node* init_right) {
        data_field = init_data; 
        left_field = init_left; 
        right_field = init_right;
    }

    void tree_clear(binary_tree_node*& root_ptr) {
    	if (root_ptr != NULL) {
            tree_clear(root_ptr->left());
            tree_clear(root_ptr->right());
            delete root_ptr;
            root_ptr = NULL;
        }
    }

    binary_tree_node* tree_copy(const binary_tree_node* root_ptr) {
        binary_tree_node *l_ptr, *r_ptr;
        if (root_ptr == NULL) return NULL;
        else {
            l_ptr = tree_copy(root_ptr->left());
            r_ptr = tree_copy(root_ptr->right());
            return new binary_tree_node(root_ptr->data(), l_ptr, r_ptr);
        }
    }
}