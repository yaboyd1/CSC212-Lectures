#include <iostream>
#include "bintree.h"
using namespace std;
using namespace main_savitch_10;

int main() {
	/* Constructor works! */
	cout << "Using constructor to make a new binary tree with a whole bunch of nodes..." << endl;
	binary_tree_node *root = new binary_tree_node(10,
		new binary_tree_node(11,
			new binary_tree_node(13,
				new binary_tree_node(17),
				new binary_tree_node(18)
			),
			new binary_tree_node(14,
				new binary_tree_node(19),
				new binary_tree_node(20)
			)
		),
		new binary_tree_node(12,
			new binary_tree_node(15,
				new binary_tree_node(21),
				new binary_tree_node(22)
			),
			new binary_tree_node(16,
				new binary_tree_node(23),
				new binary_tree_node(24)
			)
		)
	);
	print(root, 2);

	/* Tree_copy works! */
	cout << "Using tree_copy to make a copy of the original binary tree..." << endl;
	binary_tree_node *copy = tree_copy(root);
	print(copy, 2);

	/* Tree_clear works! */
	cout << "Using tree_clear to clear the copy..." << endl;
	tree_clear(copy);
	print(copy, 2);

	cout << endl << "Tree_copy should have printed the same binary tree as the original" << endl;
	cout << "Tree_clear should not have printed anything" << endl;

	return 0;
}