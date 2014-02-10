//============================================================================
// Name        : GraphUD.h
// Author      : Gregory Jackson 
// Version     : 1.0
// Copyright   : NOTICE:  All information contained herein is, and remains
//             * the property of University of California, Santa Cruz (UCSC). 
//             * The intellectual and technical concepts contained herein are 
//             * proprietary to UCSC and and are protected by trade secret or 
//             * copyright law. Dissemination of this information or reproduction 
//             * of this material is strictly forbidden unless prior written 
//             * permission is obtained from UCSC.
// Description : Implementation of Undirect Graph w/ Adjacency ListShortest, C++11
//============================================================================

#ifndef GRAPH_UNDIRECTED
#define GRAPH_UNDIRECTED

#include <iostream>
#include <vector>
#include <list>
//#include <cassert>
#include <assert.h>

#include "AdjVertex.h"

class GraphUD
{

public:
   typedef int Node;
   typedef int Cost;
   typedef AdjVertex<Node, Cost> Vertex;

/*          Class Fields 
*/
   static const int  GRAPH_SZ = 50;
   static const Cost NO_COST  = 0;

/*       Friend I/O Functions
 */
   friend ostream& operator<<(ostream &out, GraphUD &g);

/*          Constructors and Destructors
*/
   GraphUD(int vertices=GRAPH_SZ);


/*          Accessor Functions 
*/
   int   V() const; 
   int   E() const; 
   Cost  weight(Node u, Node v) const;

   bool adjacent(Node x, Node y) const;
   const list<Vertex>& neighbors(Node u);


/*          Mutator Functions 
*/
   void insert( Node u, Node v, Cost cost);
   void insert(Vertex &v);
   void erase( Node u, Node v);

   void  setWeight(Node u, Node v, Cost c);

private: 
/*       Fields
*/
   vector<list<Vertex>> adj_lst;


/*          Helper Functions  
*/

   list<Vertex>::const_iterator
   find(list<Vertex>::const_iterator first,
               list<Vertex>::const_iterator last,
               Node v ) const;


   list<AdjVertex<Node, Cost>>::iterator                    // could use Vertex
   find(list<AdjVertex<Node, Cost>>::iterator first,
               list<AdjVertex<Node, Cost>>::iterator last,
               Node v );
};


#endif
