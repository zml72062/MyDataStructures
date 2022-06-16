#ifndef BINARY_TREE_H
#define BINARY_TREE_H

namespace MyDataStructures
{
	template <class T>
	struct binaryTreeNode
	{
		T* data;
		binaryTreeNode<T>* parent;
		binaryTreeNode<T>* left;
		binaryTreeNode<T>* right;
		binaryTreeNode() :data(nullptr), parent(nullptr), left(nullptr), right(nullptr) {}
		explicit binaryTreeNode(const T& _data) :data(new T(_data)), parent(nullptr), left(nullptr), right(nullptr) {}
		explicit binaryTreeNode(T&& _data) :data(new T(_data)), parent(nullptr), left(nullptr), right(nullptr) {}
		binaryTreeNode(binaryTreeNode* _parent, binaryTreeNode* _left, binaryTreeNode* _right) :data(nullptr), parent(_parent), left(_left), right(_right) {}
		~binaryTreeNode() { delete data; }

		binaryTreeNode<T>* rightSibling() const
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
		binaryTreeNode<T>* leftSibling() const
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

	template <class T, class Node = binaryTreeNode<T>>
	class binaryTreeIterator
	{
	public:
		virtual T& operator*() { return *(node->data); }
		virtual const T& operator*() const { return *(node->data); }
		virtual bool operator==(const binaryTreeIterator<T, Node>& _right) const { return node == _right.node; }
		virtual bool operator!=(const binaryTreeIterator<T, Node>& _right) const { return node != _right.node; }
		Node* getNode() const { return node; }
		Node*& setNode() { return node; }
	protected:
		binaryTreeIterator(Node* _node) :node(_node) {}
		Node* node;
	};

	template <class T, class Node = binaryTreeNode<T>>
	class preOrderBinaryTreeIterator :public binaryTreeIterator<T, Node>
	{
	protected:
		using binaryTreeIterator<T, Node>::node;
		Node* head;
	public:
		// _head->left should be root
		preOrderBinaryTreeIterator(Node* _node, Node* _head) :binaryTreeIterator<T, Node>(_node), head(_head) {}

		preOrderBinaryTreeIterator<T, Node>& operator++()
		{
			if (node->left != nullptr)
			{
				node = node->left;
			}
			else if (node->right != nullptr)
			{
				node = node->right;
			}
			else
			{
				// head->left = root
				while (node->rightSibling() == nullptr && node != head->left)
				{
					node = node->parent;
				}
				node = node->rightSibling();
			}
			return *this;
		}
		preOrderBinaryTreeIterator<T, Node> operator++(int)
		{
			preOrderBinaryTreeIterator<T, Node> temp = *this;
			if (node->left != nullptr)
			{
				node = node->left;
			}
			else if (node->right != nullptr)
			{
				node = node->right;
			}
			else
			{
				// head->left = root
				while (node->rightSibling() == nullptr && node != head->left)
				{
					node = node->parent;
				}
				node = node->rightSibling();
			}
			return temp;
		}
		preOrderBinaryTreeIterator<T, Node>& operator--()
		{
			if (node->leftSibling() != nullptr)
			{
				node = node->leftSibling();
				while (node->left != nullptr || node->right != nullptr)
				{
					if (node->right != nullptr)
					{
						node = node->right;
					}
					else
					{
						node = node->left;
					}
				}
			}
			else
			{
				node = node->parent;
			}
			return *this;
		}
		preOrderBinaryTreeIterator<T, Node> operator--(int)
		{
			preOrderBinaryTreeIterator<T, Node> temp = *this;
			if (node->leftSibling() != nullptr)
			{
				node = node->leftSibling();
				while (node->left != nullptr || node->right != nullptr)
				{
					if (node->right != nullptr)
					{
						node = node->right;
					}
					else
					{
						node = node->left;
					}
				}
			}
			else
			{
				node = node->parent;
			}
			return temp;
		}
	};

	template <class T, class Node = binaryTreeNode<T>>
	class preOrderBinaryTreeReverseIterator :public binaryTreeIterator<T, Node>
	{
	protected:
		using binaryTreeIterator<T, Node>::node;
		Node* head;
	public:
		// _head->left should be root
		preOrderBinaryTreeReverseIterator(Node* _node, Node* _head) :binaryTreeIterator<T, Node>(_node), head(_head) {}

		preOrderBinaryTreeReverseIterator<T, Node>& operator++()
		{
			if (node->leftSibling() != nullptr)
			{
				node = node->leftSibling();
				while (node->left != nullptr || node->right != nullptr)
				{
					if (node->right != nullptr)
					{
						node = node->right;
					}
					else
					{
						node = node->left;
					}
				}
			}
			else
			{
				node = node->parent;
			}
			return *this;
		}
		preOrderBinaryTreeReverseIterator<T, Node> operator++(int)
		{
			preOrderBinaryTreeReverseIterator<T, Node> temp = *this;
			if (node->leftSibling() != nullptr)
			{
				node = node->leftSibling();
				while (node->left != nullptr || node->right != nullptr)
				{
					if (node->right != nullptr)
					{
						node = node->right;
					}
					else
					{
						node = node->left;
					}
				}
			}
			else
			{
				node = node->parent;
			}
			return temp;
		}
		preOrderBinaryTreeReverseIterator<T, Node>& operator--()
		{
			if (node->left != nullptr)
			{
				node = node->left;
			}
			else if (node->right != nullptr)
			{
				node = node->right;
			}
			else
			{
				// head->left = root
				while (node->rightSibling() == nullptr && node != head->left)
				{
					node = node->parent;
				}
				node = node->rightSibling();
			}
			return *this;
		}
		preOrderBinaryTreeReverseIterator<T, Node> operator--(int)
		{
			preOrderBinaryTreeReverseIterator<T, Node> temp = *this;
			if (node->left != nullptr)
			{
				node = node->left;
			}
			else if (node->right != nullptr)
			{
				node = node->right;
			}
			else
			{
				// head->left = root
				while (node->rightSibling() == nullptr && node != head->left)
				{
					node = node->parent;
				}
				node = node->rightSibling();
			}
			return temp;
		}
	};

	template <class T, class Node = binaryTreeNode<T>>
	class postOrderBinaryTreeIterator :public binaryTreeIterator<T, Node>
	{
	protected:
		using binaryTreeIterator<T, Node>::node;
		Node* head;
	public:
		// _head->right should be root
		postOrderBinaryTreeIterator(Node* _node, Node* _head) :binaryTreeIterator<T, Node>(_node), head(_head) {}

		postOrderBinaryTreeIterator<T, Node>& operator++()
		{
			if (node->rightSibling() != nullptr)
			{
				node = node->rightSibling();
				while (node->right != nullptr || node->left != nullptr)
				{
					if (node->left != nullptr)
					{
						node = node->left;
					}
					else
					{
						node = node->right;
					}
				}
			}
			else
			{
				node = node->parent;
			}
			return *this;
		}
		postOrderBinaryTreeIterator<T, Node> operator++(int)
		{
			postOrderBinaryTreeIterator<T, Node> temp = *this;
			if (node->rightSibling() != nullptr)
			{
				node = node->rightSibling();
				while (node->right != nullptr || node->left != nullptr)
				{
					if (node->left != nullptr)
					{
						node = node->left;
					}
					else
					{
						node = node->right;
					}
				}
			}
			else
			{
				node = node->parent;
			}
			return temp;
		}
		postOrderBinaryTreeIterator<T, Node>& operator--()
		{
			if (node->right != nullptr)
			{
				node = node->right;
			}
			else if (node->left != nullptr)
			{
				node = node->left;
			}
			else
			{
				// head->right = root
				while (node->leftSibling() == nullptr && node != head->right)
				{
					node = node->parent;
				}
				node = node->leftSibling();
			}
			return *this;
		}
		postOrderBinaryTreeIterator<T, Node> operator--(int)
		{
			postOrderBinaryTreeIterator<T, Node> temp = *this;
			if (node->right != nullptr)
			{
				node = node->right;
			}
			else if (node->left != nullptr)
			{
				node = node->left;
			}
			else
			{
				// head->right = root
				while (node->leftSibling() == nullptr && node != head->right)
				{
					node = node->parent;
				}
				node = node->leftSibling();
			}
			return temp;
		}
		
	};

	template <class T, class Node = binaryTreeNode<T>>
	class postOrderBinaryTreeReverseIterator :public binaryTreeIterator<T, Node>
	{
	protected:
		using binaryTreeIterator<T, Node>::node;
		Node* head;
	public:
		// _head->right should be root
		postOrderBinaryTreeReverseIterator(Node* _node, Node* _head) :binaryTreeIterator<T, Node>(_node), head(_head) {}

		postOrderBinaryTreeReverseIterator<T, Node>& operator--()
		{
			if (node->rightSibling() != nullptr)
			{
				node = node->rightSibling();
				while (node->right != nullptr || node->left != nullptr)
				{
					if (node->left != nullptr)
					{
						node = node->left;
					}
					else
					{
						node = node->right;
					}
				}
			}
			else
			{
				node = node->parent;
			}
			return *this;
		}
		postOrderBinaryTreeReverseIterator<T, Node> operator--(int)
		{
			postOrderBinaryTreeReverseIterator<T, Node> temp = *this;
			if (node->rightSibling() != nullptr)
			{
				node = node->rightSibling();
				while (node->right != nullptr || node->left != nullptr)
				{
					if (node->left != nullptr)
					{
						node = node->left;
					}
					else
					{
						node = node->right;
					}
				}
			}
			else
			{
				node = node->parent;
			}
			return temp;
		}
		postOrderBinaryTreeReverseIterator<T, Node>& operator++()
		{
			if (node->right != nullptr)
			{
				node = node->right;
			}
			else if (node->left != nullptr)
			{
				node = node->left;
			}
			else
			{
				// head->right = root
				while (node->leftSibling() == nullptr && node != head->right)
				{
					node = node->parent;
				}
				node = node->leftSibling();
			}
			return *this;
		}
		postOrderBinaryTreeReverseIterator<T, Node> operator++(int)
		{
			postOrderBinaryTreeReverseIterator<T, Node> temp = *this;
			if (node->right != nullptr)
			{
				node = node->right;
			}
			else if (node->left != nullptr)
			{
				node = node->left;
			}
			else
			{
				// head->right = root
				while (node->leftSibling() == nullptr && node != head->right)
				{
					node = node->parent;
				}
				node = node->leftSibling();
			}
			return temp;
		}
	};

	template <class T, class Node = binaryTreeNode<T>>
	class inOrderBinaryTreeIterator :public binaryTreeIterator<T, Node>
	{
	protected:
		using binaryTreeIterator<T, Node>::node;
		Node* head;
	public:
		// _head->left should be root
		inOrderBinaryTreeIterator(Node* _node, Node* _head) :binaryTreeIterator<T, Node>(_node), head(_head) {}

		inOrderBinaryTreeIterator<T, Node>& operator++()
		{
			if (node->right != nullptr)
			{
				node = node->right;
				while (node->left != nullptr)
				{
					node = node->left;
				}
			}
			else
			{
				if (node == head->right)
				{
					node = head;
					while (node->left != nullptr)
					{
						node = node->left;
					}
				}
				else
				{
					while (node->isRight())
					{
						node = node->parent;
					}
					node = node->parent;
				}
			}
			return *this;
		}
		inOrderBinaryTreeIterator<T, Node> operator++(int)
		{
			inOrderBinaryTreeIterator<T, Node> temp = *this;
			if (node->right != nullptr)
			{
				node = node->right;
				while (node->left != nullptr)
				{
					node = node->left;
				}
			}
			else
			{
				if (node == head->right)
				{
					node = head;
					while (node->left != nullptr)
					{
						node = node->left;
					}
				}
				else
				{
					while (node->isRight())
					{
						node = node->parent;
					}
					node = node->parent;
				}
			}
			return temp;
		}
		inOrderBinaryTreeIterator<T, Node>& operator--()
		{
			if (node->left != nullptr)
			{
				node = node->left;
				while (node->right != nullptr)
				{
					node = node->right;
				}
			}
			else
			{
				while (node != head && node->isLeft())
				{
					node = node->parent;
				}
				if (node != head)
				{
					node = node->parent;
				}
				else
				{
					node = node->right;
				}
			}
			return *this;
		}
		inOrderBinaryTreeIterator<T, Node> operator--(int)
		{
			inOrderBinaryTreeIterator<T, Node> temp = *this;
			if (node->left != nullptr)
			{
				node = node->left;
				while (node->right != nullptr)
				{
					node = node->right;
				}
			}
			else
			{
				while (node != head && node->isLeft())
				{
					node = node->parent;
				}
				if (node != head)
				{
					node = node->parent;
				}
				else
				{
					node = node->right;
				}
			}
			return temp;
		}
	};

	template <class T, class Node = binaryTreeNode<T>>
	class inOrderBinaryTreeReverseIterator :public binaryTreeIterator<T, Node>
	{
	protected:
		using binaryTreeIterator<T, Node>::node;
		Node* head;
	public:
		// _head->left should be root
		inOrderBinaryTreeReverseIterator(Node* _node, Node* _head) :binaryTreeIterator<T, Node>(_node), head(_head) {}

		inOrderBinaryTreeReverseIterator<T, Node>& operator--()
		{
			if (node->right != nullptr)
			{
				node = node->right;
				while (node->left != nullptr)
				{
					node = node->left;
				}
			}
			else
			{
				if (node == head->right)
				{
					node = head;
					while (node->left != nullptr)
					{
						node = node->left;
					}
				}
				else
				{
					while (node->isRight())
					{
						node = node->parent;
					}
					node = node->parent;
				}
			}
			return *this;
		}
		inOrderBinaryTreeReverseIterator<T, Node> operator--(int)
		{
			inOrderBinaryTreeReverseIterator<T, Node> temp = *this;
			if (node->right != nullptr)
			{
				node = node->right;
				while (node->left != nullptr)
				{
					node = node->left;
				}
			}
			else
			{
				if (node == head->right)
				{
					node = head;
					while (node->left != nullptr)
					{
						node = node->left;
					}
				}
				else
				{
					while (node->isRight())
					{
						node = node->parent;
					}
					node = node->parent;
				}
			}
			return temp;
		}
		inOrderBinaryTreeReverseIterator<T, Node>& operator++()
		{
			if (node->left != nullptr)
			{
				node = node->left;
				while (node->right != nullptr)
				{
					node = node->right;
				}
			}
			else
			{
				while (node != head && node->isLeft())
				{
					node = node->parent;
				}
				if (node != head)
				{
					node = node->parent;
				}
				else
				{
					node = node->right;
				}
			}
			return *this;
		}
		inOrderBinaryTreeReverseIterator<T, Node> operator++(int)
		{
			inOrderBinaryTreeReverseIterator<T, Node> temp = *this;
			if (node->left != nullptr)
			{
				node = node->left;
				while (node->right != nullptr)
				{
					node = node->right;
				}
			}
			else
			{
				while (node != head && node->isLeft())
				{
					node = node->parent;
				}
				if (node != head)
				{
					node = node->parent;
				}
				else
				{
					node = node->right;
				}
			}
			return temp;
		}

	};

	template <class T, class Node = binaryTreeNode<T>>
	class binaryTree
	{
	public:
		binaryTree() :lefthead(new Node()), root(new Node()), righthead(new Node())
		{
			lefthead->right = root;
			lefthead->left = new Node();
			lefthead->left->parent = lefthead;
			righthead->left = root;
			righthead->right = new Node();
			righthead->right->parent = righthead;
			size = 0;
		}
		template <size_t _size>
		binaryTree(T* (&_array)[_size]) :lefthead(new Node()), righthead(new Node())
		{
			size = 0;
			Node** _new_array = new Node*[_size];
			for (size_t i = 0; i < _size; ++i)
			{
				if (_array[i] == nullptr)
				{
					_new_array[i] = nullptr;
				}
				else
				{
					_new_array[i] = new Node(*(_array[i]));
					++size;
				}
			}
			root = _new_array[0];
			lefthead->right = root;
			lefthead->left = new Node();
			lefthead->left->parent = lefthead;
			righthead->left = root;
			righthead->right = new Node();
			righthead->right->parent = righthead;
			if (root != nullptr)
			{
				for (size_t i = 0; i < _size; ++i)
				{
					if (_new_array[i] != nullptr)
					{
						if ((i << 1) + 1 < _size)
						{
							_new_array[i]->left = _new_array[(i << 1) + 1];
							if (_new_array[i]->left != nullptr)
							{
								_new_array[(i << 1) + 1]->parent = _new_array[i];
							}
						}
						else
						{
							_new_array[i]->left = nullptr;
						}
						if ((i << 1) + 2 < _size)
						{
							_new_array[i]->right = _new_array[(i << 1) + 2];
							if (_new_array[i]->right != nullptr)
							{
								_new_array[(i << 1) + 2]->parent = _new_array[i];
							}
						}
						else
						{
							_new_array[i]->right = nullptr;
						}
					}
				}
			}
			delete[] _new_array;
		}
		binaryTree(T** _array, size_t _size) :lefthead(new Node()), righthead(new Node())
		{
			size = 0;
			Node** _new_array = new Node*[_size];
			for (size_t i = 0; i < _size; ++i)
			{
				if (_array[i] == nullptr)
				{
					_new_array[i] = nullptr;
				}
				else
				{
					_new_array[i] = new Node(*(_array[i]));
					++size;
				}
			}
			root = _new_array[0];
			lefthead->right = root;
			lefthead->left = new Node();
			lefthead->left->parent = lefthead;
			righthead->left = root;
			righthead->right = new Node();
			righthead->right->parent = righthead;
			if (root != nullptr)
			{
				for (size_t i = 0; i < _size; ++i)
				{
					if (_new_array[i] != nullptr)
					{
						if ((i << 1) + 1 < _size)
						{
							_new_array[i]->left = _new_array[(i << 1) + 1];
							if (_new_array[i]->left != nullptr)
							{
								_new_array[(i << 1) + 1]->parent = _new_array[i];
							}
						}
						else
						{
							_new_array[i]->left = nullptr;
						}
						if ((i << 1) + 2 < _size)
						{
							_new_array[i]->right = _new_array[(i << 1) + 2];
							if (_new_array[i]->right != nullptr)
							{
								_new_array[(i << 1) + 2]->parent = _new_array[i];
							}
						}
						else
						{
							_new_array[i]->right = nullptr;
						}
					}
				}
			}
			delete[] _new_array;
		}

		binaryTree(const binaryTree<T, Node>& _right) = delete;
		binaryTree(binaryTree<T, Node>&& _right) = delete;

		binaryTree<T, Node>& operator=(const binaryTree<T, Node>& _right) = delete;
		binaryTree<T, Node>& operator=(binaryTree<T, Node>&& _right) = delete;
		virtual ~binaryTree()
		{
			if (root != nullptr)
			{
				root->parent = lefthead;
				auto p = begin(), q = end();
				while (p != q)
				{
					auto s = p;
					++s;
					delete p.getNode();
					p.setNode() = nullptr;
					p = s;
				}
			}
			delete lefthead->left;
			delete righthead->right;
			delete lefthead;
			delete righthead;
		}

		Node* getRoot() const { return root; }
		size_t length() const { return size; }
	protected:
		Node* lefthead;  // lefthead->right = root
		Node* righthead; // righthead->left = root
		Node* root;
		size_t size;
	private:
		postOrderBinaryTreeIterator<T, Node> begin() const
		{
			postOrderBinaryTreeIterator<T, Node> temp(lefthead->left, lefthead);
			++temp;
			return temp;
		}
		postOrderBinaryTreeIterator<T, Node> end() const { return postOrderBinaryTreeIterator<T, Node>(lefthead, lefthead); }

	};

	template <class T, class Node = binaryTreeNode<T>>
	class preOrderBinaryTree :public binaryTree<T, Node>
	{
	private:
		using binaryTree<T, Node>::lefthead;
		using binaryTree<T, Node>::righthead;
		using binaryTree<T, Node>::root;
		using binaryTree<T, Node>::size;
	public:
		preOrderBinaryTree() : binaryTree<T, Node>()
		{
			root->parent = righthead;
		}
		template <size_t _size>
		preOrderBinaryTree(T* (&_array)[_size]) : binaryTree<T, Node>(_array)
		{
			if (size > 0) root->parent = righthead;
		}
		preOrderBinaryTree(T** _array, size_t _size) : binaryTree<T, Node>(_array, _size)
		{
			if (size > 0) root->parent = righthead;
		}
		preOrderBinaryTree(const preOrderBinaryTree<T, Node>& _right) = delete;
		preOrderBinaryTree(preOrderBinaryTree<T, Node>&& _right) = delete;

		preOrderBinaryTree<T, Node>& operator=(const preOrderBinaryTree<T, Node>& _right) = delete;
		preOrderBinaryTree<T, Node>& operator=(preOrderBinaryTree<T, Node>&& _right) = delete;
		preOrderBinaryTreeIterator<T, Node> begin() const 
		{
			if (size == 0) return end();
			return preOrderBinaryTreeIterator<T, Node>(root, righthead); 
		}
		preOrderBinaryTreeIterator<T, Node> end() const { return preOrderBinaryTreeIterator<T, Node>(righthead->right, righthead); }
		preOrderBinaryTreeReverseIterator<T, Node> rbegin() const
		{
			if (size == 0) return rend();
			preOrderBinaryTreeReverseIterator<T, Node> temp(righthead->right, righthead);
			++temp;
			return temp;
		}
		preOrderBinaryTreeReverseIterator<T, Node> rend() const { return preOrderBinaryTreeReverseIterator<T, Node>(righthead, righthead); }
	};

	template <class T, class Node = binaryTreeNode<T>>
	class inOrderBinaryTree :public binaryTree<T, Node>
	{
	private:
		using binaryTree<T, Node>::lefthead;
		using binaryTree<T, Node>::righthead;
		using binaryTree<T, Node>::root;
		using binaryTree<T, Node>::size;
	public:
		inOrderBinaryTree() : binaryTree<T, Node>()
		{
			root->parent = righthead;
		}
		template <size_t _size>
		inOrderBinaryTree(T* (&_array)[_size]) : binaryTree<T, Node>(_array)
		{
			if (size > 0) root->parent = righthead;
		}
		inOrderBinaryTree(T** _array, size_t _size) : binaryTree<T, Node>(_array, _size)
		{
			if (size > 0) root->parent = righthead;
		}
		inOrderBinaryTree(const inOrderBinaryTree<T, Node>& _right) = delete;
		inOrderBinaryTree(inOrderBinaryTree<T, Node>&& _right) = delete;

		inOrderBinaryTree<T, Node>& operator=(const inOrderBinaryTree<T, Node>& _right) = delete;
		inOrderBinaryTree<T, Node>& operator=(inOrderBinaryTree<T, Node>&& _right) = delete;
		inOrderBinaryTreeIterator<T, Node> end() const { return inOrderBinaryTreeIterator<T, Node>(righthead, righthead); }
		inOrderBinaryTreeIterator<T, Node> begin() const
		{
			if (size == 0) return end();
			inOrderBinaryTreeIterator<T, Node> temp(righthead->right, righthead);
			++temp;
			return temp;
		}
		inOrderBinaryTreeReverseIterator<T, Node> rbegin() const 
		{
			if (size == 0) return rend();
			inOrderBinaryTreeReverseIterator<T, Node> temp(righthead, righthead); 
			++temp;
			return temp;
		}
		inOrderBinaryTreeReverseIterator<T, Node> rend() const { return inOrderBinaryTreeReverseIterator<T, Node>(righthead->right, righthead); }
	};

	template <class T, class Node = binaryTreeNode<T>>
	class postOrderBinaryTree :public binaryTree<T, Node>
	{
	private:
		using binaryTree<T, Node>::lefthead;
		using binaryTree<T, Node>::righthead;
		using binaryTree<T, Node>::root;
		using binaryTree<T, Node>::size;
	public:
		postOrderBinaryTree() :binaryTree<T, Node>()
		{
			root->parent = lefthead;
		}
		template <size_t _size>
		postOrderBinaryTree(T* (&_array)[_size]) : binaryTree<T, Node>(_array)
		{
			if (size > 0) root->parent = lefthead;
		}
		postOrderBinaryTree(T** _array, size_t _size) : binaryTree<T, Node>(_array, _size)
		{
			if (size > 0) root->parent = lefthead;
		}
		postOrderBinaryTree(const postOrderBinaryTree<T, Node>& _right) = delete;
		postOrderBinaryTree(postOrderBinaryTree<T, Node>&& _right) = delete;
		postOrderBinaryTree<T, Node>& operator=(const postOrderBinaryTree<T, Node>& _right) = delete;
		postOrderBinaryTree<T, Node>& operator=(postOrderBinaryTree<T, Node>&& _right) = delete;
		postOrderBinaryTreeIterator<T, Node> begin() const
		{
			if (size == 0) return end();
			postOrderBinaryTreeIterator<T, Node> temp(lefthead->left, lefthead);
			++temp;
			return temp;
		}
		postOrderBinaryTreeIterator<T, Node> end() const { return postOrderBinaryTreeIterator<T, Node>(lefthead, lefthead); }
		postOrderBinaryTreeReverseIterator<T, Node> rbegin() const 
		{
			if (size == 0) return rend();
			return postOrderBinaryTreeReverseIterator<T, Node>(root, lefthead); 
		}
		postOrderBinaryTreeReverseIterator<T, Node> rend() const { return postOrderBinaryTreeReverseIterator<T, Node>(lefthead->left, lefthead); }
	};
}

#endif
