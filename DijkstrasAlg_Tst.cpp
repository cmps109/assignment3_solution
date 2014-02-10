//============================================================================
// Name        : GraphUD_Basic.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <cmath>

#include "AdjVertex.h"
#include "GraphUD.h"
#include "MinPriorityQ.h"
#include "DijkstraSP.h"
#include "BiDirSearch.h"

using namespace std;

/* ******************************************
 *          Testing Funcitons
 * ******************************************/
void stepDijkstraSP(GraphUD graph, GraphUD::Node src);
void stepDijkstraSP(GraphUD graph, GraphUD::Node src, GraphUD::Node dst);




int main()
{
   GraphUD     graph(7);

   graph.insert(0,1,30);
   graph.insert(1,2,7);
   graph.insert(1,3,9);
   graph.insert(1,6,14);
   graph.insert(2,3,10);
   graph.insert(2,4,15);
   graph.insert(3,6,2);
   graph.insert(3,4,11);
   graph.insert(4,5,6);
   graph.insert(5,6,9);

   cout << "V: " << graph.V() << endl;
   cout << "E: " << graph.E() << endl;
   cout << "Graph Adjacency List\n" << graph  << endl;  

   
   stepDijkstraSP(graph, 1, 5);

   BiDirSearch bsrch(graph,1,5);
   cout << "\nBiDirSearch 1 -> 5" << endl;  
   cout << "MinPath:"  << bsrch.minPath() << endl; 
   cout << "iNode:"    << bsrch.iNode()   << endl;
   cout << "Src-Dst Perf:" << bsrch.closedSetPerf(BiDirSearch::FORWARD) << endl;
   cout << "sClosed  "     << bsrch.stateSClosedSet() << endl;
   cout << "Dst-Src Perf:" << bsrch.closedSetPerf(BiDirSearch::REVERSE) << endl;
   cout << "tClosed  "     << bsrch.stateTClosedSet() << endl;

}

   void stepDijkstraSP(GraphUD graph, GraphUD::Node src)
   {
      DijkstraSP  sp1(graph);
      set<GraphUD::Node> oset;

      cout << "Open Set: path = " << src << " -> ALL" << endl;
      while (sp1.stepSP(src)) {
                     
         sp1.openSet(oset);
         for (auto n = oset.begin(); n != oset.end(); n++) {
            cout << *n << " " ;
         }
         cout << endl;
         oset.clear();
      }
      cout << sp1.graphMatrix() << endl;
      cout << sp1.costMatrix() << endl;
   }


   void stepDijkstraSP(GraphUD graph, GraphUD::Node src, GraphUD::Node dst)
   {
      DijkstraSP  sp1(graph);
      set<GraphUD::Node> oset;
      set<GraphUD::Node> cset;

      cout << "\nDijkstraSP: path = " << src << " -> " << dst << endl;
      while (sp1.stepSP(src, dst)) {
                     
         cout << "Open Set: ";
         sp1.openSet(oset);
         for (auto n = oset.begin(); n != oset.end(); n++) {
            cout << *n << " " ;
         }
         cout << endl;
         oset.clear();
      }
      sp1.closedSet(cset);
      cout << "Closed set: ";
      for (auto n = cset.begin(); n != cset.end(); n++) {
         cout << *n << " " ;
      }
      cout << endl;
      cout << "minPath: " << sp1.pathCost(dst) << endl;
   }
