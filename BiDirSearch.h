//============================================================================
// Name        : BiDirSearch.h
// Author      : Gregory Jackson 
// Version     : 1.0
// Copyright   : NOTICE:  All information contained herein is, and remains
//             * the property of University of California, Santa Cruz (UCSC). 
//             * The intellectual and technical concepts contained herein are 
//             * proprietary to UCSC and and are protected by trade secret or 
//             * copyright law. Dissemination of this information or reproduction 
//             * of this material is strictly forbidden unless prior written 
//             * permission is obtained from UCSC.
// Description : Implementation of Bidirectional Seach Algorithm, C++11
//============================================================================

#ifndef DIJKSTRA_SP_H
#define DIJKSTRA_SP_H

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>

#include "GraphUD.h"
#include "MinPriorityQ.h"
#include "DijkstraSP.h"

using namespace std;

class BiDirSearch
{
   static const GraphUD::Cost MAX_PATH_COST  = 1 << 16;

public:
   enum Direction {FORWARD, REVERSE};


/*          Friend Functions 
*/
   friend ostream& operator<<(ostream &out, const BiDirSearch &bisrch);


/*          Constructors and Destructors 
*/
   BiDirSearch(GraphUD &g, GraphUD::Node src, GraphUD::Node dst);


/*          Accessor Functions 
*/
   int closedSetPerf(Direction d);
  
   GraphUD::Cost minPath();
   GraphUD::Node iNode();


/*          I/O Functions 
*/
   string stateTOpenSet();
   string stateTClosedSet();
   string stateSClosedSet();
   string statePathCandidate();

private:
/*          Fields 
*/
   set<GraphUD::Node>   s_closed;
   set<GraphUD::Node>   t_open;
   set<GraphUD::Node>   t_closed;
   set<GraphUD::Node>   result;

   GraphUD::Node           i_node;
   GraphUD::Cost           i_cost;

   GraphUD::Node           src;
   GraphUD::Node           dst;

   DijkstraSP              src_dst;
   DijkstraSP              dst_src;

/*          Helper Functions 
 *
*   Note: Vertex -> AdjVertex<GraphUD::Node,GraphUD::Cost>
*/
   void BiDirectionalSearch();
   bool checkTerminate();
   void determineSP();
};


#endif
