#pragma once
#include <string>
#include <memory>
#include <unordered_map>

template < class Key, class Value >
class cache {
public:

	struct Node {
		typedef std::shared_ptr<Node> NodePtr;
		
		Node(Key k, Value v) {
			key = k;
			value = v;
		}

		~Node() {
			first.reset();
			last.reset();
			left.reset();
			right.reset();
		}

		void dump() {
			std::cout << "key[" << key << "] ";
			std::cout << "value[" << value << "] ";
			if (first) {
				std::cout << "first[" << first->key << "|" << first->value << "] ";
			}
			if (last) {
				std::cout << "last[" << last->key << "|" << last->value << "] ";
			}
			if (left) {
				std::cout << "left[" << left->key << "|" << left->value << "] ";
			}
			if (right) {
				std::cout << "right[" << right->key << "|" << right->value << "] ";
			}
			std::cout << std::endl;
		}

		Key key;
		Value value;
		NodePtr first;
		NodePtr last;

		NodePtr left;
		NodePtr right;
	};

	typedef std::shared_ptr<Node> NodePtr;


	cache(unsigned int capacity) {
		_capacity = capacity;
	}

	virtual ~cache() {

	}

	Value get(Key ref) {
		auto ci = _umap.find(ref);
		if (ci != _umap.end()) {
			NodePtr n = ci->second;
			remove(n);
			set_first(n);
			return n->value;
		}
		return NULL;
	}

	void add(Key key, Value value) {
		auto ci = _umap.find(key);
		if (ci != _umap.end()) {
			NodePtr old = ci->second;
			old->value = value;
			remove(old);
			set_first(old);
		}
		else {
			NodePtr created = std::make_shared<Node>(key, value);
			if (_umap.size() >= _capacity) {
				_umap.erase(last->key);
				remove(last);
				set_first(created);

			}
			else {
				set_first(created);
			}

			_umap.insert({ key, created });
		}
	}

	void destroy() {
		for (auto ci = _umap.begin(); ci != _umap.end(); ci++) {
			delete ci->second;
		}

		_umap.clear();
	}l  

	void dump() {
		if (first) {
			std::cout << "first[" << first->key << "|" << first->value << "] ";
		}
		if (last) {
			std::cout << "last[" << last->key << "|" << last->value << "] ";
		}
		std::cout << std::endl;

		for (auto ci = _umap.begin(); ci != _umap.end(); ci++) {
			std::cout << "\t";
			ci->second->dump();
		}		
	}

private:
	void remove(NodePtr ref) {
		if (ref->left != nullptr) {
			ref->left->right = ref->right;
		}
		else {
			first = ref->right;
		}

		if (ref->right != nullptr) {
			ref->right->left = ref->left;
		}
		else {
			last = ref->left;
		}
	}

	void set_first(NodePtr ref) {
		ref->right = first;
		ref->left = nullptr;

		if (first != nullptr) {
			first->last = ref;
		}

		first = ref;

		if (last == nullptr) {
			last = first;
		}
	}

public:
	NodePtr first;
	NodePtr last;

private:
	unsigned int _capacity;
	std::unordered_map<Key, NodePtr> _umap;
	

};