//============================================================================
// Name        : MinPriorityQ.h
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

#ifndef HEAP_SORT_H
#define HEAP_SORT_H


#include <iostream>
#include <vector>
#include <set>
#include <assert.h>

#include "AdjVertex.h"
#include "GraphUD.h"

using namespace std;

class  MinPriorityQ
{
public:
   typedef int HeapNode;
   typedef int Cost;

   typedef AdjVertex<HeapNode, Cost> Key;

/*           Friends 
*/
   friend ostream& operator<< (ostream &out, const MinPriorityQ &pq);

/*
 *         Constructors and Destructors
 */
   MinPriorityQ();

/*
 *        Access Functions
 */
   int         size() const;
   bool        empty() const;    
   const Key&  min() const;
   void        nodes(set<Key> &nset) const;


/*
 *        Mutate Functions
 */
    void push(const Key& key);
    void pop(); 
    bool relax(const Key& key);

private:

/*         Class  Fields
*/
   static const HeapNode ROOT = 0;

/*         Instance  Fields
*/
   vector<Key> heap;

/*
 *        Heapify Functions
 */
   void swim(HeapNode node);
   void sink(HeapNode node);

/*
 *        operator Functions
 */
   bool less(const HeapNode i, const HeapNode j);
   void exch(HeapNode i, HeapNode j);
};


#endif
