//============================================================================
// Name        : MinPriorityQ.cpp
// Author      : Gregory Jackson 
// Version     : 1.0
// Copyright   : NOTICE:  All information contained herein is, and remains
//             * the property of University of California, Santa Cruz (UCSC). 
//             * The intellectual and technical concepts contained herein are 
//             * proprietary to UCSC and and are protected by trade secret or 
//             * copyright law. Dissemination of this information or reproduction 
//             * of this material is strictly forbidden unless prior written 
//             * permission is obtained from UCSC.
// Description : Implementation of Min Priority Queue using HEAP sort, C++11
//============================================================================

#include "MinPriorityQ.h"

/* ##########################################################
 *
 *                   Interface Functions
 *
* ##########################################################*/

/* *******************************************************
 *         Constructors and Destructors
 * *******************************************************/

MinPriorityQ::MinPriorityQ()
{  }


/* *******************************************************
 *        Access Functions
 * *******************************************************/

int  MinPriorityQ::size() const
{
   return heap.size();
}

bool MinPriorityQ::empty() const    
{
   return !(heap.size() > 0);
}

const MinPriorityQ::Key& MinPriorityQ::min() const
{
   assert(!empty());
   return heap[ROOT];
}

void MinPriorityQ::nodes(set<Key> &nset) const
{
   for (auto &n : heap) {
      nset.insert(n);
   }
}


/* *******************************************************
 *        Mutate Functions
 * *******************************************************/

void MinPriorityQ::push(const Key& key)
{
   heap.push_back(key);
   swim(heap.size()-1);
}

void MinPriorityQ::pop() 
{
   exch(ROOT, heap.size()-1); 
   heap.pop_back();
   sink(ROOT);
}

// if AdjVertex in PQ & key.head.cost < pq.head.cost, relax cost
bool MinPriorityQ::relax(const Key& key)
{
 /*
*/
   for (HeapNode idx=0; idx < static_cast<int>(heap.size()); idx++) {
      if (key.head() == heap[idx].head()) {
         if (key.cost() < heap[idx].cost()) {  
            heap[idx] = key;
            swim(idx);
            return true;
         }
         else { return true; }    // key.cost > heap.cost, ignore
      }
   }
   return false;              // not in PQ
}

/* ##########################################################
 *
 *                   Private Functions
 *
* ##########################################################*/

/*  ++++++++++++++++++++++++++++++++++++++++++++++++++
 *        Heapify Functions
 *  +++++++++++++++++++++++++++++++++++++++++++++++++*/

void MinPriorityQ::swim(HeapNode node)
{
   HeapNode parent = (node-1) / 2;

   if (parent < ROOT) return;

   if (less(node, parent) ) {
      exch(node, parent); 
      swim(parent);
   }
   return;
}

void MinPriorityQ::sink(HeapNode node)
{
   HeapNode swapable = (node * 2) + 1;

   if ( !(swapable < static_cast<int>(heap.size())) ) return;

   if (swapable < static_cast<int>(heap.size())-1 && less(swapable+1, swapable)) {
      swapable++;
   }

   if ( less(swapable, node) ) {
      exch(node, swapable);
      sink(swapable);
   }
}

/*  ++++++++++++++++++++++++++++++++++++++++++++++++++
 *        operator Functions
 *  +++++++++++++++++++++++++++++++++++++++++++++++++*/
 
bool MinPriorityQ::less(const HeapNode i, const HeapNode j)
{
   return heap[i] < heap[j];
}

// Desc: swaps key at [i] with [j]
void MinPriorityQ::exch(HeapNode i, HeapNode j)
{
   Key key_t = heap[i];

   heap[i] = heap[j];
   heap[j] = key_t;
}


/*  ++++++++++++++++++++++++++++++++++++++++++++++++++
 *        Friend Functions
 *  +++++++++++++++++++++++++++++++++++++++++++++++++*/
 
ostream& operator<< (ostream &out, const MinPriorityQ &pq)
{
   vector<MinPriorityQ::Key>::const_iterator itr;

   for (itr=pq.heap.begin(); itr != pq.heap.end(); itr++) {
      out << itr->tail() << "->" << itr->head() << ":" << itr->cost() << " ";
   }
/*
   for (auto &itr : pq.heap) { out << itr << " "; }
*/
   out << endl;
   return out;
};


