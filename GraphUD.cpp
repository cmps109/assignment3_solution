//============================================================================
// Name        : GraphUD.cpp
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
#include "GraphUD.h"

/*****************************************************
 *                Class Fields - alternative init 
* ****************************************************/
// const int            GraphUD::GRAPH_SZ = 50; 
// const GraphUD::Cost  GraphUD::NO_COST  = 0; 


/*****************************************************
 *          Constructors and Destructors
* ****************************************************/

GraphUD::GraphUD(int vertices) : adj_lst(vertices)
{  }


/*****************************************************
*              Accessor Functions 
* ****************************************************/

/* 
 * DESC: V(G): returns the number of vertices in the graph
 */
int GraphUD::V() const
{  
   return adj_lst.size();
}

/* 
 * DESC: E(G): returns the number of edges in the graph
 */
int GraphUD::E() const
{
   int sum = 0;

   for (auto &neighbors : adj_lst) { sum += neighbors.size(); }
   return sum;
} 

/*	
 *	DESC: get_edge_value( G, x, y): returns the cost associated to the edge (x,y).
 */
GraphUD::Cost GraphUD::weight(Node u, Node v) const
{
   list<Vertex>::const_iterator f_itr; 

   list<Vertex>::const_iterator first = adj_lst[u].begin();
   list<Vertex>::const_iterator last  = adj_lst[u].end(); 

   if ( (f_itr = find(first, last, v)) != last) { 
      return f_itr->cost(); 
   }
   else {
      return NO_COST;
   }
}

/* 
 * DESC: adjacent (G, x, y): tests whether there is an edge from node x to node y.
 */
bool GraphUD::adjacent(Node x, Node y) const
{
   list<GraphUD::Vertex>::const_iterator first = adj_lst[x].begin();
   list<GraphUD::Vertex>::const_iterator last  = adj_lst[x].end(); 

   if (find(first, last, y) != last) { return true; }
   else {
      return false;
   }
}

/* 
 * DESC: neighbors (G, x): lists all nodes y such that there is an edge from x to y.
 */
const list<GraphUD::Vertex>& GraphUD::neighbors(Node u)
{
   return adj_lst[u];
}


/*****************************************************
*             Mutator Functions 
* ****************************************************/

/*	
 *	DESC: insert(G, x, y, c): adds to G the edge from x to y with cost c, if it is not there.
 */
void GraphUD::insert( Node u, Node v, Cost cost)
{
   assert((u < V() && "Vertex out-of-bound")); 
   assert((v < V() && "Vertex out-of-bound")); 

   if (adjacent(u, v)) return;

   GraphUD::Vertex  adj_u(v, u, cost);
   GraphUD::Vertex  adj_v(u, v, cost);

   adj_lst[u].push_front(adj_v);
   adj_lst[v].push_front(adj_u);
}

/*	
 *	DESC: insert(G, x, y, c): adds to G the edge from x to y with cost c, if it is not there.
 */
void GraphUD::insert(Vertex &v)
{
   insert(v.tail(), v.head(), v.cost());
}

/*	
 *	DESC: erase(a, x, y): removes the edge from x to y, if it is there.
 */
void GraphUD::erase( Node u, Node v)
{
   list<Vertex>::iterator f_itr; 
   list<Vertex>::iterator first; 
   list<Vertex>::iterator last;  

   first = adj_lst[u].begin();
   last  = adj_lst[u].end();
   if ( (f_itr = find(first, last, v)) != last) { 
      adj_lst[u].erase(f_itr); 
   }

   first = adj_lst[v].begin();
   last  = adj_lst[v].end();
   if ( (f_itr = find(first, last, u)) != last) { 
      adj_lst[v].erase(f_itr); 
   }
}

/*	
 *	DESC: set_edge_value (G, x, y, v): sets the cost associated to the edge (x,y) to v.
 */
void GraphUD::setWeight(Node u, Node v, Cost c)
{
   list<Vertex>::iterator f_itr; 
   list<Vertex>::iterator first; 
   list<Vertex>::iterator last;  

   first = adj_lst[u].begin();
   last  = adj_lst[u].end();
   if ( (f_itr = find(first, last, v)) != last) { 
      f_itr->chgCost(c);
   }

   first = adj_lst[v].begin();
   last  = adj_lst[v].end();
   if ( (f_itr = find(first, last, u)) != last) { 
      f_itr->chgCost(c);
   }
}


/*****************************************************
*             I/O Functions 
* ****************************************************/
ostream& operator<<(ostream &out, GraphUD &g)
{
   list<GraphUD::Vertex> vlst;

   for (GraphUD::Node tail = 0; tail < g.V(); tail++) {
      vlst = g.neighbors(tail);
      cout << tail << ": ";
      for (auto head : vlst) {
         cout << head.toString() << " | ";
      }
      cout << endl;
   }    
   return out;
}

/*****************************************************
*           Helper Functions 
* ****************************************************/

/* 
 * DESC: finds adjacent node in adjacent_list(first, last)
 * RTN:  returns constant iterator to discovered incident-on node
 */
list<GraphUD::Vertex>::const_iterator
GraphUD::find(list<GraphUD::Vertex>::const_iterator first,
               list<GraphUD::Vertex>::const_iterator last,
               Node v ) const
{

   while (first != last) {
      if (first->head() == v) { return first; }
      first++;
   }
   return last;
}

/* 
 * DESC: finds adjacent node in adjacent_list(first, last)
 * RTN:  returns iterator to discovered incident-on node
 */
list<AdjVertex<GraphUD::Node, GraphUD::Cost>>::iterator 
GraphUD::find(list<AdjVertex<Node, Cost>>::iterator first, 
      list<AdjVertex<Node, Cost>>::iterator last, 
      Node v ) 
{
   while (first != last) {
      if (first->head() == v) { return first; }
      first++;
   }
   return last;
}


