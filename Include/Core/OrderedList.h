////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __ORDEREDLIST_H__
#define __ORDEREDLIST_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      ORDEREDLIST
//
//  Synopsis:
//      Differentiates which of the two possible arcs could match the given arc
//      parameters.
//
//------------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
// INCLUDE
////////////////////////////////////////////////////////////////////////////////
/*
*
* List.cpp
* @author Mathew Kurian
* @version 1.0
*
* From Aurora-SDK
* https://github.com/Muzzler/Aurora-SDK
*
* Please report any issues
* https://github.com/Muzzler/Aurora-SDK
*
* Date: 12/31/2013 12:28:16 AM
**
* ----------------BENCHMARK------------------
*
* -------------------------------------
* A2D::List push_back - Integer[10000000 iterations]
* Time taken : 0.736000000s
* -------------------------------------
* A2D::List remove - Integer[1 iterations]
* Time taken : 0.426000000s
* -------------------------------------
* A2D::List push_back - Integer[10000000 iterations]
* Time taken : 0.372000000s
* -------------------------------------
* A2D::List max_remove_all - Integer[1 iterations][Competing against std::vector!!!!]
* Time taken : 0.000000000s
* -------------------------------------
* std::vector push_back - Integer[10000000 iterations]
* Time taken : 4.229000000s
* -------------------------------------
* std::vector remove_all - Integer[1 iterations]
* Time taken : 0.006000000s
* -------------------------------------
* std::vector push_back - Integer[10000000 iterations]
* Time taken : 4.218000000s
* -------------------------------------
* std::list push_back - Integer[10000000 iterations]
* Time taken : 25.740000000s
* -------------------------------------
* std::list remove_all - Integer[1 iterations]
* Time taken : 560.740000000s
* -------------------------------------
* std::list push_back - Integer[10000000 iterations]
* Time taken : 42.640000000s
*
*/

// Testing
// - Cached m_t_array is changed
// - Check for m_arrayed - requires testing

#define abs__hplist(a)     (((a) < 0) ? -(a) : (a))
#define max__hplist(a, b)  (((a) > (b)) ? (a) : (b))
#define min__hplist(a, b)  (((a) < (b)) ? (a) : (b))

namespace A2D{

	template <class T>
	class OrderedList
	{

	public:


		// Internal node system
		template <class T>
		struct Node
		{
			T value;
			Node<T> * left;
			Node<T> * right;
		};

		template<class T>
		struct Iterator
		{

		private:

			Node<T> * m_node;
			bool m_first = true;
			int m_size = 0;

		public:

			void update(Node<T> * node, int size)
			{
				m_node = node;
				m_size = size;
			}

			inline T  next()
			{
				T  t = m_node->value;

				m_node = m_node->right;
				m_size--;

				return t;
			}

			inline bool has_next()
			{
				return m_node != NULL && m_size;
			}

			inline T  previous()
			{
				T  t = m_node->value;

				m_node = m_node->left;
				m_size--;

				return t;
			}

			inline bool has_previous()
			{
				return  m_node != NULL && m_size;
			}
		};

	private:

		int m_heapptr_index = 0;
		int m_heapptr_length = 0;
		int m_heapptr_ammort_length = 0;
		void ** m_heapptr;

		int m_heap_free = 0;
		int m_heap_length = 0;
		int m_heap_ammort_length = 0;
		Node<T> * m_heap;

		int m_fragments_available_index = 0;
		int m_fragments_cache_total = 0;
		int m_fragments_length = 0;
		int m_fragments_ammort_length = 0;
		void ** m_fragments;

		bool m_released = true;
		bool m_arrayed = false;

		// Ammortizes the src array based on the parameters.
		// In most cases dstLength = srcLength * 2
		// Users of this method must watch out for double-freeing
		inline void ammortize(void *** x_src, int x_src_length, int x_dst_length)
		{
			// Create pointer in L1 cache for src array
			void ** src_alloc = *x_src;

			// Mallow new area in heap for array
			void** dst_alloc = new void *[x_dst_length];

			// Loop through and copy data from src->dst
			for (int i = 0; i < x_src_length; i++)
			{
				dst_alloc[i] = src_alloc[i];
			}

			// Delete the src pointer of pointer to array
			delete[] src_alloc;

			// Reasize the pointer to new pointer of array
			*x_src = dst_alloc;
		}

		// Internal use for safely removing nodes and adding 
		// to fragment cache
		inline void remove_node(Node<T> * node)
		{
			// Remove the value
			node->value = 0;

			// If node is m_head
			if (node == m_head)
			{
				m_head = node->right;
				m_head->left = NULL; // Enforce
			}
			// If node is anything else
			else
			{
				node->left->right = node->right;
				node->right->left = node->left;
			}

			// Disable the current node
			node->left = NULL;
			node->right = NULL;

			// Add from heap fragments to m_fragments.
			// This is a basic queue
			if (m_fragments_available_index > 0)
			{
				// If the fragments are available in the front of m_fragment
				m_fragments[--m_fragments_available_index] = node;  // decrement
				// Decrement size after remove
				m_size--;
				return;
			}
			else if (m_fragments_cache_total + 1 >= m_fragments_length)
			{
				// If there is no more space inside the m_fragment
				ammortize(&m_fragments, m_fragments_length, m_fragments_length * 2);
				m_fragments_length *= 2;
			}

			// Assign the new fragment to empty location
			m_fragments[m_fragments_cache_total++] = node;

			// Decrement size after remove
			m_size--;
		}

		inline Node<T> * find_node(int index)
		{
			// This testing is not required because fine_node is an internal method
			//if (index >= m_size || index < 0)
			//{
			//	return 0;
			//}

			bool start_on_right = index > m_size / 2 ? true : false;
			Node<T> * node = start_on_right ? m_end : m_head;
			int i = start_on_right ? m_size - index : index;

			if (start_on_right)
			{
				while (--i > -1)
				{
					node = node->left;
				}
			}
			else
			{
				while (--i > -1)
				{
					node = node->right;

				}
			}

			return node;
		}

		// Allocate large chunks in heap
		inline void allocate_chunk()
		{
			// Check if the heap ptr index will greater than length
			if (m_heapptr_index + 1 >= m_heapptr_length)
			{
				// Ammortize the heap ptrs
				ammortize(&m_heapptr, m_heapptr_length, m_heapptr_length * 2);
				m_heapptr_length *= 2;
			}

			// Allocate new area in the heap
			m_heap = new Node<T>[m_heap_free = (m_heap_length *= 2)];
			m_heapptr[m_heapptr_index++] = static_cast<void*>(m_heap);
		}

	public:

		// Create OrderedList of type T
		OrderedList<T>()
		{
			// Calculate ammmortization values based on 
			// the size of T. This will soon have some performance
			// changes.
			m_heap_ammort_length = max__hplist(sizeof(T), 80) / sizeof(T);

			//  Higher size T indicates more
			// ammortizations during OrderedList lifetime.
			m_heapptr_ammort_length = max__hplist(m_heap_ammort_length / 20, 5);
			m_fragments_ammort_length = 5;

			// Malloc and prepare the OrderedList
			renew();
		}

		// Releases resources on destruction
		~OrderedList<T>()
		{
			release();
		}

		// Release the resources
		void release()
		{
			if (m_released) return;

			// Go through each heap ptr
			for (int i = 0; i <= m_heapptr_index - 1; i++)
			{
				// Delete the heaps 
				delete[] m_heapptr[i];
				m_heapptr[i] = 0;
			}

			// Free the fragment cache
			if (m_fragments)
			{
				delete[] m_fragments;
			}

			// Free heap pointers
			if (m_heapptr)
			{
				delete[] m_heapptr;
			}

			// Release the requested array
			if (m_t_array)
			{
				delete[] m_t_array;
			}

			// Mark as released
			m_released = true;
			m_arrayed = false;
		}

		// Cache the contents for heap allocation
		void renew()
		{
			if (!m_released)
			{
				release();
			}

			m_size = 0;

			m_heapptr_index = 0;
			m_fragments_available_index = 0;
			m_fragments_cache_total = 0;

			m_heap_free = m_heap_length = m_heap_ammort_length; // Because we are starting off with a full allocation on heap
			m_heapptr_length = m_heapptr_ammort_length;
			m_fragments_length = m_fragments_ammort_length;

			// initialize
			m_heap = new Node<T>[m_heap_free];
			m_heapptr = new void*[m_heapptr_length];
			m_fragments = new void*[m_fragments_length];

			// Attach heap to heap ptr to keep track of it
			m_heapptr[m_heapptr_index++] = static_cast<void*>(m_heap);
			// Set the decrement the heap since the head takes one
			m_head = &m_heap[--m_heap_free];
			// Head should point to m_end
			m_end = m_head;

			// Enfore the the left of the head to be null -DOUBLECHEK IF NEEDED
			// m_head->left = NULL;
		}

		/*************************************************************
		* Code repeated for performance
		* - push_back(T t)
		* - push_front(T t)
		* - insert(T t, int index)
		**************************************************************/

		void insert(T t, int index, void ** ptr)
		{
			m_arrayed = false;

			index = min__hplist(abs__hplist(index), m_size);

			if (index == 0)
			{
				return push_front(t, ptr);
			}
			else if (index >= m_size)
			{
				return push_back(t, ptr);
			}
			else
			{
				// The next node from the current is null
				Node<T> * next_node = NULL;

				// L1 cache the m_end
				Node<T> * node = m_head; // Select front or back based on index

				/*************************** CACHE - REQUEST ***************************/
				// Look for fragments in the heap
				if (m_fragments_available_index < m_fragments_cache_total)
				{
					next_node = static_cast<Node<T>*>(m_fragments[m_fragments_available_index]);
					m_fragments[m_fragments_available_index++] = NULL;
				}
				// Allocate heap space if there are no fragments
				// and use these.
				else if (m_heap_free - 1 <= -1)
				{
					allocate_chunk();
				}

				next_node = next_node ? next_node : &m_heap[--m_heap_free];
				/*************************** CACHE - REQUEST ***************************/

				int i = index;

				while (--i > -1) // Before index so its 0
				{
					node = node->right;
				}

				// Set found node and append to the m_end
				next_node->value = t;
				next_node->right = node;
				next_node->left = node->left;
				if (node->left)	node->left->right = next_node;
				node->left = next_node;

				// Increase size
				m_size++;

				if (ptr)
				{
					*ptr = next_node;
				}
			}
		}

		// Add to the back
		void push_back(T t, void ** ptr)
		{
			m_arrayed = false;

			// The next node from the current is null
			Node<T> * next_node = NULL;

			// L1 cache the m_end
			Node<T> * node = m_end;

			/*************************** CACHE - REQUEST ***************************/
			// Look for fragments in the heap
			if (m_fragments_available_index < m_fragments_cache_total)
			{
				next_node = static_cast<Node<T>*>(m_fragments[m_fragments_available_index]);
				m_fragments[m_fragments_available_index++] = NULL;
			}
			// Allocate heap space if there are no fragments
			// and use these.
			else if (m_heap_free - 1 <= -1)
			{
				allocate_chunk();
			}

			// L1 cache the m_end
			next_node = m_end = next_node ? next_node : &m_heap[--m_heap_free];

			/*************************** CACHE - REQUEST ***************************/

			// Set found node and append to the m_end
			node->value = t;
			next_node->left = node;
			node->right = next_node;

			// Increase size
			m_size++;

			if (ptr)
			{
				*ptr = node;
			}
		}

		void push_front(T t, void ** ptr)
		{
			m_arrayed = false;

			// The next next_node
			Node<T> * next_node = NULL;

			// L1 cache the m_hea
			Node<T> * node = m_head;

			/*************************** CACHE - REQUEST ***************************/
			// Look for fragments in the heap
			if (m_fragments_available_index < m_fragments_cache_total)
			{
				next_node = static_cast<Node<T>*>(m_fragments[m_fragments_available_index]);
				m_fragments[m_fragments_available_index++] = NULL;
			}
			// Allocate heap space if there are no fragments
			// and use these.
			else if (m_heap_free - 1 <= -1)
			{
				allocate_chunk();
			}

			next_node = m_head = next_node ? next_node : &m_heap[--m_heap_free];

			/*************************** CACHE - REQUEST ***************************/

			// Set found next_node and append to the m_end
			next_node->value = t;
			next_node->right = node;
			node->left = next_node;

			// Increase size
			m_size++;

			if (ptr)
			{
				*ptr = next_node;
			}
		}

		// Convert to string
		T* to_array()
		{
			// Delete the last converted array
			if (m_t_array && !m_arrayed)
			{
				delete[] m_t_array;
			}

			// Allocate new space on heap for the
			// array version
			m_t_array = new T[m_size];

			int i = 0;

			// Pointer to head
			Node<T> * node = m_head;

			// Loop through and add the current
			// data to array
			while (node && i < m_size)
			{
				m_t_array[i++] = node->value;
				node = node->right;
			}

			m_arrayed = true;

			return m_t_array;
		}

		// Remove first instance.
		void remove(T t)
		{
			if (m_size == 0) return;

			m_arrayed = false;

			Node<T> * node = m_head;
			int i = m_size;

			while (--i > -1 && node->value != t)
			{
				node = node->right;
			}

			if (i == -1) return;

			// same code as remove_node
			// placed here for performance!

			remove_node(node);

		}

		// Remove all values of t
		void remove_all(T t)
		{
			if (m_size == 0) return;

			m_arrayed = false;

			Node<T> * node_right;
			Node<T> * node = m_head;
			int i = m_size;

			while (--i > -1 && node)
			{
				node_right = node->right;

				if (node->value == t && node_right)
				{
					remove_node(node);
				}

				node = node_right;
			}
		}

		// Remove all the values
		void remove_all()
		{
			splice(0, m_size);
		}

		// High speed remove all
		void max_remove_all()
		{
			release();
			renew();
		}

		// Get size of list
		int size()
		{
			return m_size;
		}

		// Check if lis tis empty
		bool is_empty()
		{
			return m_size <= 0;
		}

		// Remove selected index
		void remove_index(int i)
		{
			splice(i, 1);
		}

		void remove_request(void ** x)
		{
			if (*x = NULL)
			{
				return;
			}

			remove_node(static_cast<Node<T>*>(*x));
			*x = NULL;
		}

		// Splice portions of list
		void splice(int start, int items)
		{
			m_arrayed = false;

			// Precaution
			start = abs(start);
			items = abs(items);

			if (m_size == 0 || (start + items) > m_size) return;

			Node<T> * node = find_node(start);
			Node<T> * node_right;

			int i = items;

			while (--i > -1 && node)
			{
				// store 
				node_right = node->right;

				// remove_node using fragment caching
				remove_node(node);

				// store the right node
				node = node_right;
			}

			// point the head to m_end
			if (m_size == 0)
			{
				m_end = m_head;
			}
		}

		Iterator<T>& iterator()
		{
			m_iterator.update(m_head, m_size);
			return m_iterator;
		}

		Iterator<T>& reverse_iterator()
		{
			m_iterator.update(m_end->left, m_size);
			return m_iterator;
		}

		///////////// TO DO /////////////

		T max_get(int index)
		{
			// Account for -1 (because we start of with 1 extra)
			if (index >= m_size || index < 0)
			{
				return 0;
			}

			if (m_arrayed)
			{
				return m_t_array[index];
			}
			else
			{
				to_array();
				return max_get(index);
			}
		}

		T get(int index)
		{
			if (index >= m_size || index < 0)
			{
				return 0;
			}

			bool start_on_right = index > m_size / 2 ? true : false;
			Node<T> * node = start_on_right ? m_end : m_head;
			int i = start_on_right ? m_size - index : index;

			if (start_on_right)
			{
				while (--i > -1)
				{
					node = node->left;

				}
			}
			else
			{
				while (--i > -1)
				{
					node = node->right;

				}
			}

			return node->value;
		}

		T peek()
		{
			return m_head->value;
		}

		Node<T> * _head()
		{
			return m_head;
		}

		Node<T> * _end()
		{
			return m_end->left;
		}

		void pop();
		void sort(); // This will be a pain. In time tho!

	private:

		Iterator<T>						m_iterator;
		int								m_size = 0;
		Node<T>					*		m_head;
		Node<T>					*		m_end;
		T					    *		m_t_array;
	};
}


#endif