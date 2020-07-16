#ifndef BINTREE_H
#define BINTREE_H
#include <cstdlib>  // Provides NULL and size_t

namespace main_savitch_10 {
	class binary_tree_node {
	public:
		// TYPEDEF
		typedef int value_type;
		// CONSTRUCTOR
		binary_tree_node(const value_type& init_data = value_type(), binary_tree_node* init_left = NULL, binary_tree_node* init_right = NULL);
		// MODIFICATION MEMBER FUNCTIONS
		value_type& data() {return data_field;}
		binary_tree_node*& left() {return left_field;}
		binary_tree_node*& right() {return right_field;}
		void set_data(const value_type& new_data) {data_field = new_data;}
		void set_left(binary_tree_node* new_left) {left_field = new_left;}
		void set_right(binary_tree_node* new_right) {right_field = new_right;}
		// CONST MEMBER FUNCTIONS
		const value_type& data() const {return data_field;}
		const binary_tree_node* left() const {return left_field;}
		const binary_tree_node* right() const {return right_field;}
		bool is_leaf() const {return (left_field == NULL) && (right_field == NULL);}
	private:
		value_type data_field;
		binary_tree_node *left_field, *right_field;
	};

	// NON-MEMBER FUNCTIONS
	void print(binary_tree_node* node_ptr, size_t depth);
	void tree_clear(binary_tree_node*& root_ptr);
	binary_tree_node* tree_copy(const binary_tree_node* root_ptr);
}

#endif