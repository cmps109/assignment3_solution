//============================================================================
// Name        : DijkstraSP.cpp
// Author      : Gregory Jackson 
// Version     : 1.0
// Copyright   : NOTICE:  All information contained herein is, and remains
//             * the property of University of California, Santa Cruz (UCSC). 
//             * The intellectual and technical concepts contained herein are 
//             * proprietary to UCSC and and are protected by trade secret or 
//             * copyright law. Dissemination of this information or reproduction 
//             * of this material is strictly forbidden unless prior written 
//             * permission is obtained from UCSC.
// Description : Implementation of Dijkstra's Shortest Path Algorithm, C++11
//============================================================================
#include "DijkstraSP.h"

/*****************************************************
*          Constructors and Destructors
* ****************************************************/

DijkstraSP::DijkstraSP (GraphUD &G) 
        : source(NOT_INIT),
            graph(G), 
            s_closed(graph.V())    // default ctor Vertex
{   }


/*****************************************************
*              Accessor Functions 
* ****************************************************/
void DijkstraSP::closedSet (set<GraphUD::Node> &cset)
{
   for (auto &v : s_closed) {
      if (!v.isNull()) cset.insert(v.head());
   }
}

void DijkstraSP::openSet (set<GraphUD::Node> &oset)
{
   s_open.clear();
   pq.nodes(s_open);   
   for (GraphUD::Vertex v : s_open) {
      oset.insert(v.head());
   }
}

GraphUD::Cost DijkstraSP::pathCost (GraphUD::Node n)
{
   s_open.clear();
   pq.nodes(s_open);   

   if (!s_closed[n].isNull())
      return s_closed[n].cost(); 
   else
      for (GraphUD::Vertex v : s_open) {
         if (v.head() == n) return v.cost();
      }
  cout << "Node not in SET" << n << endl;
  return 0;
}

/*****************************************************
*             Mutator Functions 
* ****************************************************/
void DijkstraSP::allSP(GraphUD::Node src, GraphUD::Node dst)
{

// shortest path: source to ->
   if (dst == ALL_NODES) {
      while (stepSP(src)) ;
   } else {
      while (stepSP(src, dst)) ;
   }
}

bool DijkstraSP::stepSP(GraphUD::Node src, GraphUD::Node dst)
{
   GraphUD::Vertex  c_node;   
   list<GraphUD::Vertex> adj_lst;
   
// initial conditions: 
//
   if (source == NOT_INIT) { 
      source = src;
      c_node = GraphUD::Vertex(source,source,0);   
      pq.push(c_node);
   }

// shortest path: source to ->
   if (!pq.empty())
   {
      c_node = pq.min();
      pq.pop();

      pushClosedSet(c_node);
      if ((dst != ALL_NODES) && (c_node.head() == dst) ) return false;

      adj_lst = graph.neighbors(c_node.head());   // copy u.adjList 
      for (auto &e : adj_lst) {
    	  string s = e.toString();
         if (inClosedSet(e)) { 
                 continue; 
         }       // discovered nodes

         e.chgCost(c_node.cost() + e.cost());    // dist[w] = dist[u] + w.cost 
         if (!pq.relax(e)) { pq.push(e); }       // in pq->relax, otherwise insert
      }
      return true;
   }
   return false;
}

/*****************************************************
*             I/O Functions 
* ****************************************************/
string DijkstraSP::graphMatrix()
{
   stringstream ss;
   int idx = 0;
   
   for (auto &p : s_closed) {
      if (!p.isNull()) { 
         ss << "|" << idx++ << "-" << p.tail() << "|";
      } else {
         
         ss << "|" << idx++ << "-N" << "|";
      }
   }
   return ss.str();
}

string DijkstraSP::costMatrix()
{
   stringstream ss;
   int idx = 0;
   
   for (auto &p : s_closed) {
      if (!p.isNull()) { 
         ss << "|" << idx++ << "-" << p.cost() << "|";
      } else {
         
         ss << "|" << idx++ << "-N" << "|";
      }
   }
   return ss.str();
}


string DijkstraSP::state()
{
   stringstream ss;
   int idx = 0;
   
   for (auto &p : s_closed) {
      ss << "|" << idx++ << "-" << p.toString() << "|";
   }
   return ss.str();
}


/*****************************************************
*             Helper Functions 
* ****************************************************/

bool DijkstraSP::inClosedSet(GraphUD::Vertex e)
{
   return (!s_closed[e.head()].isNull() );
}


void DijkstraSP::pushClosedSet(GraphUD::Vertex e)
{
   s_closed[e.head()] = e;
}

