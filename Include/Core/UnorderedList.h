////////////////////////////////////////////////////////////////////////////////
// GAURDS
////////////////////////////////////////////////////////////////////////////////

#ifndef __UNORDEREDLIST_H__
#define __UNORDEREDLIST_H__

//+-----------------------------------------------------------------------------
//
//  Abstract Class:
//      UNORDEREDLIST
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
	class UnorderedList
	{

	private:

		int m_heapptr_index = 0;
		int m_heapptr_length = 0;
		int m_heapptr_ammort_length = 0;
		void ** m_heapptr = NULL;

		int m_heap_index = 0;
		int m_heap_default_size = 0;
		int m_heap_ammort_length = 0;
		T * m_heap = NULL;

		int m_fragments_available_index = 0;
		int m_fragments_cache_total = 0;
		int m_fragments_length = 0;
		int m_fragments_ammort_length = 0;
		void ** m_fragments = NULL;

		bool m_released = false;

		// Ammortizes the src array based on the parameters.
		// In most cases dstLength = srcLength * 2
		// Users of this method must watch out for double-freeing
		void ammortize(void *** x_src, int x_src_length, int x_dst_length)
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

	public:

		// Internal use for safely removing nodes and adding 
		// to fragment cache
		void remove_index(int index)
		{
			T * empty = &static_cast<T*>(m_heapptr[index / m_heap_default_size])[index % m_heap_default_size];

			memset(empty, 0, sizeof(T));

			void * fragment = NULL;
			bool found = false;

			// Add from heap fragments to m_fragments.
			// This is a basic queue
			if (m_fragments_available_index > 0)
			{
				// If the fragments are available in the front of m_fragment
				found = true;
				m_fragments[--m_fragments_available_index] = empty;  // decrement

				// Decrement size before return
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
			m_fragments[m_fragments_cache_total++] = empty;

			// Decrement size after remove
			m_size--;
		}

		// Allocate large chunks in heap
		void allocate_chunk()
		{
			// Check if the heap ptr index will greater than length
			if (m_heapptr_index + 1 >= m_heapptr_length)
			{
				// Ammortize the heap ptrs
				ammortize(&m_heapptr, m_heapptr_length, m_heapptr_length * 2);
				m_heapptr_length *= 2;
			}

			m_heap_index = 0;
			m_heap_size += m_heap_default_size;

			// Allocate new area in the heap
			m_heap = new T[m_heap_default_size];
			m_heapptr[m_heapptr_index++] = static_cast<void*>(m_heap);

			memset(m_heap, 0, m_heap_default_size);
		}

	public:

		// Create UnorderedList of type T
		UnorderedList<T>()
		{
			// Calculate ammmortization values based on 
			// the size of T. This will soon have some performance
			// changes.
			m_heap_ammort_length = max__hplist(sizeof(T), 80) / sizeof(T);

			//  Higher size T indicates more
			// ammortizations during UnorderedList lifetime.
			m_heapptr_ammort_length = max__hplist(m_heap_ammort_length / 20, 5);
			m_fragments_ammort_length = 5;

			// Malloc and prepare the UnorderedList
			renew();
		}

		// Releases resources on destruction
		~UnorderedList<T>()
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

			// Mark as released
			m_released = true;
		}

		// Cache the contents for heap allocation
		void renew()
		{
			if (!m_released)
			{
				release();
			}

			m_size = 0;

			m_heap_index = 0;
			m_heapptr_index = 0;
			m_fragments_available_index = 0;
			m_fragments_cache_total = 0;

			m_heap_size = m_heap_default_size = m_heap_ammort_length; // Because we are starting off with a full allocation on heap
			m_heapptr_length = m_heapptr_ammort_length;
			m_fragments_length = m_fragments_ammort_length;

			// initialize
			m_heap = new T[m_heap_default_size];
			m_heapptr = new void*[m_heapptr_length];
			m_fragments = new void*[m_fragments_length];

			m_heapptr[m_heapptr_index++] = m_heap;

			// Set heap to zero
			memset(m_heap, 0, m_heap_default_size);
		}

		// Add to the back
		void push(T t)
		{
			T * empty_slot = NULL;

			/*************************** CACHE - REQUEST ***************************/
			// Look for fragments in the heap
			if (m_fragments_available_index < m_fragments_cache_total)
			{
				empty_slot = static_cast<T*>(m_fragments[m_fragments_available_index]);
				m_fragments[m_fragments_available_index++] = NULL;
			}
			//// Allocate heap space if there are no fragments
			//// and use these.
			else if (m_heap_index >= m_heap_default_size)
			{
				allocate_chunk();
			}

			// L1 cache the m_end
			empty_slot = empty_slot ? empty_slot : &m_heap[m_heap_index++];

			/*************************** CACHE - REQUEST ***************************/

			// Copy the data into the empty slot
			memcpy(empty_slot, &t, sizeof(T));

			// Increase size
			m_size++;
		}

		// Remove first instance.
		void remove(T t, bool b) // true == remove_all; false == remove_first
		{
			if (m_size == 0) return;

			int imax_size = m_size;
			T * arr = m_heap;

            for (int i = 0; i < imax_size; i++)
			{
				if (arr[i] == t)
				{
					remove_index(i);

					if (b)
					{
						return;
					}
				}
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

		// Splice portions of list
		void splice(int start, int items)
		{
			int end_index = -1;

			// Precaution
			start = abs(start);
			items = abs(items);

			if (m_heap_size == 0 || (end_index = start + items) > m_heap_size) return;

			//int start_heapptr = start / m_heap_default_size;
			//int end_heapptr = end_index / m_heap_default_size;

			//int start_heap_index = start % m_heap_default_size;
			//int end_heap_index = end_index % m_heap_default_size;

			//if (start_heapptr == end_heapptr)
			//{
			//	memset(&static_cast<T*>(m_heapptr[start_heapptr])[start_heap_index], 0, sizeof(T)*(m_heap_default_size - end_heap_index));
			//}
			//else
			//{
			//	memset(&static_cast<T*>(m_heapptr[start_heapptr])[start_heap_index], 0, sizeof(T)*(m_heap_default_size - start_heap_index));

			//	for (++start_heapptr; start_heapptr < end_heapptr; start_heapptr++)
			//	{
			//		memset(&static_cast<T*>(m_heapptr[start_heapptr])[0], 0, sizeof(T)*(m_heap_default_size));
			//	}

			//	memset(&static_cast<T*>(m_heapptr[end_heapptr])[0], 0, sizeof(T)*(end_heap_index));
			//}
			for (int i = start; i < end_index; i++)
			{
			remove_index(i);
			}
		}

		int heap_size()
		{
			return m_heap_size;
		}

		T get(int index)
		{
			if (index >= m_heap_size || index < 0)
			{
				return 0;
			}

			return static_cast<T*>(m_heapptr[index / m_heap_default_size])[index % m_heap_default_size];
		}

	private:

		int								m_size = 0;
		int								m_heap_size = 0;
	};
}

#endif
