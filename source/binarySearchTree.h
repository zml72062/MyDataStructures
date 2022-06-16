#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include "binaryTree.h"
#include "myUtility.h"
#include <utility>
#include <initializer_list>

namespace MyDataStructures
{
	template <class T, class Node = binaryTreeNode<T>, class Pred = MyDataStructures::less<T>>
	class binarySearchTree :protected inOrderBinaryTree<T, Node>
	{
	public:
		using iterator = inOrderBinaryTreeIterator<T, Node>;
		using reverse_iterator = inOrderBinaryTreeReverseIterator<T, Node>;
		using inOrderBinaryTree<T, Node>::begin;
		using inOrderBinaryTree<T, Node>::end;
		using inOrderBinaryTree<T, Node>::rbegin;
		using inOrderBinaryTree<T, Node>::rend;

	private:
		using binaryTree<T, Node>::righthead;
		using binaryTree<T, Node>::lefthead;
		using binaryTree<T, Node>::root;
		using binaryTree<T, Node>::size;

	public:
		binarySearchTree() :inOrderBinaryTree<T, Node>() {}
		binarySearchTree(const std::initializer_list<T>& _list) :inOrderBinaryTree<T, Node>()
		{
			insert(_list);
		}
		template <class U>
		binarySearchTree(const U& _begin, const U& _end) : inOrderBinaryTree<T, Node>()
		{
			insert(_begin, _end);
		}

		size_t length() const noexcept { return size; }

		virtual iterator insert(const T& _value)
		{
			if (size == 0)
			{
				root->data = new T(_value);
				++size;
				return iterator(root, righthead);
			}
			else
			{
				Pred comp;
				auto current_point = root;
				bool left_or_right = true; // true = left, false = right
				while (current_point != nullptr)
				{
					if (comp(*(current_point->data), _value)) // inserted value is larger
					{
						if (current_point->right != nullptr)
						{
							current_point = current_point->right;
						}
						else
						{
							left_or_right = false;
							break;
						}
					}
					else if (comp(_value, *(current_point->data))) // inserted value is smaller
					{
						if (current_point->left != nullptr)
						{
							current_point = current_point->left;
						}
						else
						{
							break;
						}
					}
					else
					{
						if (current_point->left != nullptr)
						{
							current_point = current_point->left;
						}
						else
						{
							break;
						}
					}
				}
				Node* p = nullptr;
				if (left_or_right)
				{
					auto q = current_point;
					q->left = new Node(_value);
					p = q->left;
					p->parent = q;
				}
				else 
				{
					auto q = current_point;
					q->right = new Node(_value);
					p = q->right;
					p->parent = q;
				}
				++size;
				return iterator(p, righthead);
			}
		}
		virtual iterator insert(T&& _value)
		{
			if (size == 0)
			{
				root->data = new T(_value);
				++size;
				return iterator(root, righthead);
			}
			else
			{
				Pred comp;
				auto current_point = root;
				bool left_or_right = true; // true = left, false = right
				while (current_point != nullptr)
				{
					if (comp(*(current_point->data), _value)) // inserted value is larger
					{
						if (current_point->right != nullptr)
						{
							current_point = current_point->right;
						}
						else
						{
							left_or_right = false;
							break;
						}
					}
					else if (comp(_value, *(current_point->data))) // inserted value is smaller
					{
						if (current_point->left != nullptr)
						{
							current_point = current_point->left;
						}
						else
						{
							break;
						}
					}
					else
					{
						if (current_point->left != nullptr)
						{
							current_point = current_point->left;
						}
						else
						{
							break;
						}
					}
				}
				Node* p = nullptr;
				if (left_or_right)
				{
					auto q = current_point;
					q->left = new Node(_value);
					p = q->left;
					p->parent = q;
				}
				else
				{
					auto q = current_point;
					q->right = new Node(_value);
					p = q->right;
					p->parent = q;
				}
				++size;
				return iterator(p, righthead);
			}
		}
		virtual void insert(const std::initializer_list<T>& _list)
		{
			for (auto p = _list.begin(); p != _list.end(); ++p)
			{
				insert(*p);
			}
		}
		template <class U>
		void insert(const U& _begin, const U& _end)
		{
			for (auto p = _begin; p != _end; ++p)
			{
				insert(*p);
			}
		}
		virtual iterator erase(const iterator& _iter)
		{
			if (size == 1)
			{
				--size;
				return end();
			}
			auto _it = _iter;
			if (_it.getNode()->left == nullptr && _it.getNode()->right == nullptr)
			{
				auto p = _it.getNode();
				++_it;
				if (p == p->parent->left)
				{
					p->parent->left = nullptr;
					delete p;
				}
				else
				{
					p->parent->right = nullptr;
					delete p;
				}
				--size;
				return _it;
			}
			else if (_it.getNode()->left == nullptr)
			{
				auto p = _it.getNode();
				++_it;
				if (p == p->parent->left)
				{
					p->parent->left = p->right;
					if (p == root)
					{
						lefthead->right = p->right;
					}
					p->right->parent = p->parent;
				}
				else
				{
					p->parent->right = p->right;
					p->right->parent = p->parent;
				}
				delete p;
				--size;
				root = righthead->left;
				return _it;
			}
			else if (_it.getNode()->right == nullptr)
			{
				auto p = _it.getNode();
				++_it;
				if (p == p->parent->left)
				{
					p->parent->left = p->left;
					if (p == root)
					{
						lefthead->right = p->right;
					}
					p->left->parent = p->parent;
				}
				else
				{
					p->parent->right = p->left;
					p->left->parent = p->parent;
				}
				delete p;
				--size;
				root = righthead->left;
				return _it;
			}
			else
			{
				auto q = (--_it);
				++_it;
				auto p1 = _it.getNode(), p2 = q.getNode();
				*(p1->data) = *(p2->data);
				if (p2->left == nullptr && p2->right == nullptr)
				{
					auto p = p2;
					if (p == p->parent->left)
					{
						p->parent->left = nullptr;
						delete p;
					}
					else
					{
						p->parent->right = nullptr;
						delete p;
					}
					--size;
				}
				else if (p2->left == nullptr)
				{
					auto p = p2;
					if (p == p->parent->left)
					{
						p->parent->left = p->right;
						if (p == root)
						{
							lefthead->right = p->right;
						}
						p->right->parent = p->parent;
					}
					else
					{
						p->parent->right = p->right;
						p->right->parent = p->parent;
					}
					delete p;
					--size;
				}
				else if (p2->right == nullptr)
				{
					auto p = p2;
					if (p == p->parent->left)
					{
						p->parent->left = p->left;
						if (p == root)
						{
							lefthead->right = p->right;
						}
						p->left->parent = p->parent;
					}
					else
					{
						p->parent->right = p->left;
						p->left->parent = p->parent;
					}
					delete p;
					--size;
				}

				++_it;
				root = righthead->left;
				return _it;
			}
		}
		virtual iterator erase(const iterator& _begin, const iterator& _end)
		{
			auto p = _begin;
			for (; p != _end;) p = erase(p);
			return p;
		}
		virtual iterator erase(const T& _value)
		{
			auto p1 = lower_bound(_value), p2 = upper_bound(_value);
			return erase(p1, p2);
		}
		
		iterator lower_bound(const T& _value) const
		{
			if (size == 0)
			{
				return end();
			}
			else
			{
				Pred comp;
				auto current_point = root;
				bool left_or_right = true; // true = left, false = right
				while (current_point != nullptr)
				{
					if (comp(*(current_point->data), _value)) // if _value is greater
					{
						if (current_point->right != nullptr)
						{
							current_point = current_point->right;
						}
						else
						{
							left_or_right = false;
							break;
						}
					}
					else if (comp(_value, *(current_point->data))) // if _value is smaller
					{
						if (current_point->left != nullptr)
						{
							current_point = current_point->left;
						}
						else
						{
							break;
						}
					}
					else
					{
						if (current_point->left != nullptr)
						{
							current_point = current_point->left;
						}
						else
						{
							break;
						}
					}
				}
				auto ans = iterator(current_point, righthead);
				if (!left_or_right) ++ans;
				return ans;
			}
		}
		
		iterator upper_bound(const T& _value) const
		{
			if (size == 0)
			{
				return end();
			}
			else
			{
				Pred comp;
				auto current_point = root;
				bool left_or_right = true; // true = left, false = right
				while (current_point != nullptr)
				{
					if (comp(*(current_point->data), _value)) // if _value is greater
					{
						if (current_point->right != nullptr)
						{
							current_point = current_point->right;
						}
						else
						{
							left_or_right = false;
							break;
						}
					}
					else if (comp(_value, *(current_point->data))) // if _value is smaller
					{
						if (current_point->left != nullptr)
						{
							current_point = current_point->left;
						}
						else
						{
							break;
						}
					}
					else
					{
						if (current_point->right != nullptr)
						{
							current_point = current_point->right;
						}
						else
						{
							left_or_right = false;
							break;
						}
					}
				}
				auto ans = iterator(current_point, righthead);
				if (!left_or_right) ++ans;
				return ans;
			}
		}

		std::pair<iterator, iterator> equal_range(const T& _value) const
		{
			return make_pair(lower_bound(_value), upper_bound(_value));
		}

		size_t count(const T& _value) const
		{
			auto p1 = lower_bound(_value), p2 = upper_bound(_value);
			size_t diff = 0;
			for (; p1 != p2; ++p1, ++diff);
			return diff;
		}

		virtual iterator find(const T& _value) const
		{
			if (size == 0)
			{
				return end();
			}
			else
			{
				Pred comp;
				auto current_point = root;
				while (current_point != nullptr)
				{
					if (comp(*(current_point->data), _value)) // if _value is greater
					{
						current_point = current_point->right;
					}
					else if (comp(_value, *(current_point->data))) // if _value is smaller
					{
						current_point = current_point->left;
					}
					else
					{
						return iterator(current_point, righthead);
					}
				}
				return end();
			}
		}
	};

	template <class T>
	struct AVLTreeNode
	{
		T* data;
		AVLTreeNode<T>* parent;
		AVLTreeNode<T>* left;
		AVLTreeNode<T>* right;
		int unbalance = 0;
		AVLTreeNode() :data(nullptr), parent(nullptr), left(nullptr), right(nullptr) {}
		explicit AVLTreeNode(const T& _data) :data(new T(_data)), parent(nullptr), left(nullptr), right(nullptr) {}
		explicit AVLTreeNode(T&& _data) :data(new T(_data)), parent(nullptr), left(nullptr), right(nullptr) {}
		AVLTreeNode(AVLTreeNode* _parent, AVLTreeNode* _left, AVLTreeNode* _right) :data(nullptr), parent(_parent), left(_left), right(_right) {}
		~AVLTreeNode() { delete data; }

		AVLTreeNode<T>* rightSibling() const
		{
			if (this == parent->left)
			{
				return parent->right;
			}
			else
			{
				return nullptr;
			}
		}
		AVLTreeNode<T>* leftSibling() const
		{
			if (this == parent->right)
			{
				return parent->left;
			}
			else
			{
				return nullptr;
			}
		}
		bool isLeft() const { return this == parent->left; }
		bool isRight() const { return this == parent->right; }

		T& operator*() { return *data; }
		const T& operator*() const { return *data; }
	};

	template <class T>
	struct RBTreeNode
	{
		T* data;
		RBTreeNode<T>* parent;
		RBTreeNode<T>* left;
		RBTreeNode<T>* right;
		enum class NodeColor
		{
			red, black
		} color = NodeColor::red;
		RBTreeNode() :data(nullptr), parent(nullptr), left(nullptr), right(nullptr) {}
		explicit RBTreeNode(const T& _data) :data(new T(_data)), parent(nullptr), left(nullptr), right(nullptr) {}
		explicit RBTreeNode(T&& _data) :data(new T(_data)), parent(nullptr), left(nullptr), right(nullptr) {}
		RBTreeNode(RBTreeNode* _parent, RBTreeNode* _left, RBTreeNode* _right) :data(nullptr), parent(_parent), left(_left), right(_right) {}
		~RBTreeNode() { delete data; }

		RBTreeNode<T>* rightSibling() const
		{
			if (this == parent->left)
			{
				return parent->right;
			}
			else
			{
				return nullptr;
			}
		}
		RBTreeNode<T>* leftSibling() const
		{
			if (this == parent->right)
			{
				return parent->left;
			}
			else
			{
				return nullptr;
			}
		}
		bool isLeft() const { return this == parent->left; }
		bool isRight() const { return this == parent->right; }

		T& operator*() { return *data; }
		const T& operator*() const { return *data; }
	};
}

#endif
