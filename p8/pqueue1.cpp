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
	many_nodes = 0;
	for (Node* i = source.head; i != NULL; i = i->link) 
		insert(i->data, i->priority);
}

// MODIFICATION MEMBER FUNCTION 
void PriorityQueue::insert(const Item& entry, unsigned int priority) {
	if (is_empty() || priority > head->priority) {
		insert_front(entry, priority);
	} else {
		Node* i;
		for (i = head; i->link != NULL; i = i->link)
			if (priority > i->link->priority)
				break;
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
	Node* insert = new Node();
	insert->link = head;
	insert->data = entry;
	insert->priority = priority;
	head = insert;
}

void PriorityQueue::insert_after(Node* prev, const Item& entry, unsigned int priority) {
	Node* insert = new Node();
	insert->link = prev->link;
	insert->data = entry;
	insert->priority = priority;
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