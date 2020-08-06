
#ifndef _ZG_SINGLELIST_H
#define _ZG_SINGLELIST_H

#include <iostream>
#include <iterator>

namespace zg 
{
	//__________________________________________________ Class
	template<typename T>
	class singlelist
	{
		struct Node 
		{
			T value;
			Node* next;
			Node()
				:value{}
				, next(nullptr)
			{}

			Node(const T& value_)
				:value{ value_ }
				, next(nullptr)
			{}
		};

		Node* newNode(const T&  value_)
		{
#if _USEALLOCATOR_
			Node* pNode = AllocateMalloc<Node>(1);
			new (pNode) Node { value_ };
			++sz;            //count the size of list
			return pNode;
#else
			Node *pNode = new Node{ value_ };
			++sz;            //count the size of list
			return pNode;
#endif
			
		}

	public:
		singlelist () noexcept
			:root(nullptr), sz(0)
		{}
		
		// ______________________________________________________________________ Copy Constructor
		singlelist(const singlelist& rhs_) noexcept
			:root(nullptr), sz(0)
		{
			Node* tmp = rhs_.root;
			while (tmp)
			{
				push_back(tmp->value);
				tmp = tmp->next;
			}
		}

		// ______________________________________________________________________ Move Constructor
		singlelist(singlelist&& rhs_) noexcept
			:root(rhs_.root), sz(0)
		{
			rhs_.root = nullptr;
			rhs_.sz = 0;
		}

		// ______________________________________________________________________ Destructor
		~singlelist()
		{
			clear();
		}

		// ______________________________________________________________________ Copy operator
		singlelist& operator=	(const singlelist& rhs_) 
		{
			singlelist tmp{ rhs_ };
			root		= tmp.root;
			sz			= tmp.root;
			tmp.root	= nullptr;
			tmp.sz		= 0;
			return *this;
		}

		// ______________________________________________________________________ Move operator
		singlelist& operator=	(singlelist&& rhs_)
		{
			root		= rhs_.root;
			sz			= rhs_.sz;
			rhs_.root	= nullptr;
			rhs_.sz		= 0;
			return *this;
		}

		// ______________________________________________________________________ print list
		void print() const
		{
			Node* tmp = root;

			while (tmp)
			{
				std::cout << tmp->value << " ";
				tmp = tmp->next;
			}
			std::cout << std::endl;
		}
		bool empty() const;
		unsigned size() const;

		//__________________________________________________ clear
		void clear()
		{
			while (root) 
			{
				Node* toRemove = root;
				root = root->next;
#if _USEALLOCATOR_
				DeallocateMalloc(toRemove);
#else
				delete toRemove;            //free current Node
#endif
			}
			sz = 0;
			root = nullptr;
		}

		//__________________________________________________ push_front
		void push_front(const T&  value_)
		{
			Node* pNode = newNode(value_);	//allocate space for a Node
			pNode->next = root;				//point to the front of the list
			root = pNode;					//set the default to the front of the list/new list
		}

		//__________________________________________________ pop_front
		void pop_front()
		{
			Node* toRemove = root;
			root = root ? root->next : nullptr;
#if _USEALLOCATOR_
			DeallocateMalloc(toRemove);
#else
			delete toRemove;            //free current Node
#endif
			--sz;						//minus size
		}

		//__________________________________________________ push_back
		void push_back(const T&  value_)
		{
			Node* pNode = newNode(value_); //allocate space for a Node
			if (root)					    //if a Node exist
			{
				Node *tmp = root;			//a pointer to the front of the list
		
				while (tmp->next)           //while the tail is not NULL
					tmp = tmp->next;        //jump to the next list/last of the list
		
				tmp->next = pNode;            //anchor the last list to the new list
			}
			else
				root = pNode;           //reset the default to the front of the List
		}

		//__________________________________________________ pop_back
		void pop_back()
		{
			Node* toRemove = root;
			Node* prev = toRemove;
			while (toRemove->next)				//travel to last Node  
			{
				prev = toRemove;
				toRemove = toRemove->next;
			}

			if (toRemove == root)
				root = nullptr;					//set to NULL
			else
				prev->next = nullptr;

#if _USEALLOCATOR_
			DeallocateMalloc(toRemove);
#else
			delete toRemove;         //free current Node
#endif
			--sz;                    //decrease size
		}

		//__________________________________________________ insert
		void insert(unsigned pos, const T& value_)
		{
			//if out of bound
			if (pos >= sz || !root ) 
			{
				push_back(value_);
				return;
			}
			if(pos == 0)
			{
				push_front(value_);
				return;
			}

			Node* pNewNode  = newNode(value_);		//new node to insert
			Node* pNextNode = root;					//a tmp Node to find the position

			while (pNextNode && pos--)
				pNextNode = pNextNode->next;		//point to next list

			if (pNextNode->next != nullptr)			//if the next pointer is not null
			{
				Node* tmp = pNextNode->next;
				pNextNode->next = pNewNode;
				pNewNode->next = tmp;
			}
			else //if (pNextNode->next == nullptr)
			{
				pNextNode->next = pNewNode;     //anchor prev list to new node
			}
		}

		//__________________________________________________ Reverse
		void reverse()
		{
			Node* move = root;
			Node* back = nullptr;

			while(move)
			{
				Node* tmp = move;
				move = move->next;

				tmp->next = back;
				back = tmp;
			}
			root = back;
		}


		//__________________________________________________ Element access
		const T& front() const 
		{
			return root->value;
		}
		T& front() 
		{
			return root->value;
		}
		
	private:
		Node* root;
		unsigned sz;
	};

} // namespace zg

#endif //_ZG_SINGLELIST_H
