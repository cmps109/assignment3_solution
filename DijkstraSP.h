//============================================================================
// Name        : DijkstraSP.h
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

#ifndef DIJKSTRA_SF_H
#define DIJKSTRA_SF_H

#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <sstream>

#include "GraphUD.h"
#include "MinPriorityQ.h"


using namespace std;

class DijkstraSP
{
   static const GraphUD::Node NOT_INIT    = -1;
   static const GraphUD::Node ALL_NODES   = -2;

public:
/*          Constructors and Destructors 
*/
   DijkstraSP(GraphUD &G);


/*          Accessor Functions 
*/
   void           closedSet (set<GraphUD::Node> &cset);
   void           openSet   (set<GraphUD::Node> &oset);
   GraphUD::Cost  pathCost (GraphUD::Node n);

/*          Mutators Functions 
*/
// finds SP to dst (default ALL_NODES) 
   void allSP(GraphUD::Node src, GraphUD::Node dst=ALL_NODES);


// incrementally discovers SP (default ALL_NODES)
   bool stepSP(GraphUD::Node src=0, GraphUD::Node dst=ALL_NODES);


/*          I/O Functions 
*/
   string graphMatrix();
   string costMatrix();
   string state();


private:
/*          Helper Functions 
 *
*   Note: Vertex -> AdjVertex<GraphUD::Node,GraphUD::Cost>
*/

   bool inClosedSet     (GraphUD::Vertex e);
   void pushClosedSet   (GraphUD::Vertex e); 

/*          Fields 
*/
   GraphUD::Node           source;

   GraphUD                 &graph;
   MinPriorityQ            pq;
   vector<GraphUD::Vertex> s_closed;      // maintains parent & path cost
   set<GraphUD::Vertex>    s_open;        // current open set
};


#endif
