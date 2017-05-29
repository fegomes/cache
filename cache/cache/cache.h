#pragma once
#include <string>
#include <memory>
#include <unordered_map>

// If you need another cache, I can create template specialization, it is simple like this
/*

enum cache_type {
lru = 0,
fifo = 1,
lifo = 2
};

template < cache_type type, class key, class value >
class cache {
public:
cache() {}
};

template <class key, class value >
class cache <cache_type::lru, key, value> {
public:
cache() {}
key _key;
value _value;
// TODO: your code here
std::string type() { return "lru"; }
};

template <class key, class value >
class cache <cache_type::fifo, key, value> {
public:
cache() {}
key _key;
value _value;
// TODO: your code here
std::string type() { return "fifo"; }
};

// example
int main() {

cache<lru, int, int> cache_;

std::cout << cache_.type() << std::endl;

return 0;

}

*/


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
		destroy();
	}

	Value get(Key ref) {
		auto ci = _umap.find(ref);
		if (ci != _umap.end()) {
			NodePtr n = ci->second;
			remove(n);
			set_first(n);
			return n->value;
		}
		// TODO: It needs to be revised to return throw (std::out_of_range) or boost::optional for best performance
		return Value();
	}

	void add(Key key, Value value) {
		auto ci = _umap.find(key);
		if (ci != _umap.end()) {
			NodePtr ref = ci->second;
			ref->value = value;
			remove(ref);
			set_first(ref);
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
			ci->second.reset();
		}

		first.reset();
		last.reset();

		_umap.clear();
	}  

	void dump() {
		auto ci = _umap.begin();

		if (ci == _umap.end()) {
			std::cout << "[empty]" << std::endl;
			return;
		}

		if (first) {
			std::cout << "first[" << first->key << "|" << first->value << "] ";
		}
		if (last) {
			std::cout << "last[" << last->key << "|" << last->value << "] ";
		}
		std::cout << std::endl;

		for (; ci != _umap.end(); ci++) {
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
			first->left = ref;
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