#include "pqueue1.h"
#include <cassert>
using namespace std;

// CONSTRUCOR ans BIG THREE
PriorityQueue::PriorityQueue() {
	head = NULL;
	many_nodes = 0;
}

PriorityQueue::PriorityQueue(const PriorityQueue& source) {
	copy(source);
}

PriorityQueue::~PriorityQueue() {
	clear();
}

void PriorityQueue::operator =(const PriorityQueue& source) {
	if (this == &source) return;
	clear();
	copy(source);
}

void PriorityQueue::copy(const PriorityQueue& source) {
	head = NULL;
	if (source.is_empty()) return;
	insert_front(source.head->data, source.head->priority);
	Node* traversal = head->link;
	for (Node* i = source.head->link; i != NULL; i = i->link) {
		insert_after(traversal, source.head->data, source.head->priority);
		traversal = traversal->link;
	}
}

// MODIFICATION MEMBER FUNCTION 
void PriorityQueue::insert(const Item& entry, unsigned int priority) {
	/* Empty */
	if (is_empty()) {
		insert_front(entry, priority);
	}
	/* Insert at front */
	else if (priority > head->priority) {
		insert_front(entry, priority);
	}
	/* Insert at middle */
	else {
		/* Find link where priority is less */
		Node* i;

		for (i = head; i->link != NULL && priority > i->link->priority; i = i->link);

		insert_after(i, entry, priority);
	}
	++many_nodes;
}

PriorityQueue::Item PriorityQueue::get_front() {
	assert(!is_empty());
	Item value = head->data;
	remove_front();
	return value;
}

void PriorityQueue::insert_front(const Item& entry, unsigned int priority) {
	head = new Node();
	head->data = entry;
	head->priority = priority;
	head->link = NULL;
}

void PriorityQueue::insert_after(Node* prev, const Item& entry, unsigned int priority) {
	Node* insert = new Node();
	insert->data = entry;
	insert->priority = priority;
	insert->link = prev->link;
	prev->link = insert;
}

void PriorityQueue::remove_front() {
	Node* remove = head;
	head = head->link;
	delete remove;
	--many_nodes;
}

void PriorityQueue::clear() {
	while (!is_empty()) remove_front();
}