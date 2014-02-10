//============================================================================
// Name        : BiDirSearch.cpp
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

#include "BiDirSearch.h"

/* ****************************************************          
 *          Constructors and Destructors 
 * ****************************************************/

BiDirSearch::BiDirSearch(GraphUD &g, GraphUD::Node src, GraphUD::Node dst)
   : i_node{src},
      i_cost{MAX_PATH_COST},
      src{src},
      dst{dst},
      src_dst{g},
      dst_src{g}
{ 
   BiDirectionalSearch();
}


/* ****************************************************          
 *          Accessor Functions 
 * ****************************************************/
int BiDirSearch::closedSetPerf(Direction d)
{
   switch (d) {
      case BiDirSearch::FORWARD:  return s_closed.size();
      case BiDirSearch::REVERSE:  return t_closed.size();
      default: return 0;
   } 
}

/*
 * Explores minPathCost in INTERSECTION(s_closed, t_closed) 
 *                            || INTERSECTION(s_closed, t_open)
 */
GraphUD::Cost BiDirSearch::minPath()
{
   return i_cost; 
}

GraphUD::Node BiDirSearch::iNode()
{
   return i_node;
}


/* ****************************************************          
 *          I/O Functions 
 * ****************************************************/

string BiDirSearch::stateTOpenSet()
{
   stringstream ss;
        
   for (GraphUD::Node e : t_open) {
      ss << e << " " ;
   }
   return ss.str();
}

string BiDirSearch::stateTClosedSet()
{
   stringstream ss;
        
   for (GraphUD::Node e : t_closed) {
      ss << e << " " ;
   }
   return ss.str();
}

string BiDirSearch::stateSClosedSet()
{
   stringstream ss;
        
   for (GraphUD::Node e : s_closed) {
      ss << e << " " ;
   }
   return ss.str();
}

string BiDirSearch::statePathCandidate()
{
   stringstream ss;
        
   for (GraphUD::Node e : s_closed) {
      ss << e << " " ;
   }
   return ss.str();
}

/* ****************************************************          
 *          Helper Functions
 * ****************************************************/
void BiDirSearch::BiDirectionalSearch()
{
   bool terminate = false;

   while (!terminate)
   {
   // Step DijkstraSP in each search direction
      src_dst.stepSP(src);
      dst_src.stepSP(dst);
      if (checkTerminate()) break;
   }  

// acquire current state
   dst_src.openSet(t_open);

// determine intersection
   set_intersection(s_closed.begin(), s_closed.end(), 
                      t_open.begin(), t_open.end(), 
                       std::inserter(result, result.begin())
                   );
   determineSP();
}


/*
 * Desc: Terminating condition: intersection(s_closed, t_closed) is not EMPTY
 */
bool BiDirSearch::checkTerminate()
{
// re-initialize 
   s_closed.clear(); t_closed.clear();

// acquire current state
   src_dst.closedSet(s_closed);
   dst_src.closedSet(t_closed);

// determine intersection
   set_intersection(s_closed.begin(), s_closed.end(), 
                      t_closed.begin(), t_closed.end(), 
                       std::inserter(result, result.begin())
                   );

   return( (result.empty()) ? false : true );

}

// make public funciton
void BiDirSearch::determineSP()
{
   GraphUD::Cost min_t;

   for (GraphUD::Node n : result) {
      min_t = min(i_cost, src_dst.pathCost(n) + dst_src.pathCost(n));
      if (min_t < i_cost) { 
         i_node   = n; 
         i_cost   = min_t;
      }
   }
}




