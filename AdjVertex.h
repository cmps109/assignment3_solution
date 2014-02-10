 
#ifndef ADJ_VERTEX
#define ADJ_VERTEX

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

using namespace std;

template <typename Name, typename Cost>
class AdjVertex
{
   enum {V_HEAD, V_COST};

public:  
/*           
 *          Constructors and Destructors
 */
   AdjVertex();
   AdjVertex(Name tail, Name head, Cost c);
   AdjVertex(const AdjVertex &rhs);

/*           
 *          Accessor Functions 
 */
   const Name& tail() const;        // from vertex
   const Name& head() const;        // to vertex
   const Cost& cost() const;

   inline bool isNull() { return is_null; }

   string      toString() const;

/*           
 *          Mutators Functions 
 */
   void chgCost(const Cost &c);

/*           
 *          operator Overloading 
 */

   bool        operator< (const AdjVertex &rhs) const;
   bool        operator> (const AdjVertex &rhs) const;

   AdjVertex&  operator=(const AdjVertex &rhs);


   /*           Memeber Fields 
   */
   Name              v_tail;
   pair<Name, Cost>  vertex;
   bool              is_null;
};


/*           
 *          Constructors and Destructors
 */

template <typename Name, typename Cost>
AdjVertex<Name,Cost>::AdjVertex() : is_null(true) 
{ 
//   cout << "AdjVertex.default_ctor" << endl;
}

template <typename Name, typename Cost>
AdjVertex<Name,Cost>::AdjVertex(Name tail, Name head, Cost c)
      : v_tail(tail), 
         vertex(make_pair(head,c)), 
         is_null(false)
{  
//   cout << "AdjVertex.ctor" << endl;

}


template <typename Name, typename Cost>
AdjVertex<Name,Cost>::AdjVertex(const AdjVertex &rhs)
      : v_tail(rhs.v_tail), 
         vertex(make_pair(rhs.vertex.first, rhs.vertex.second)),
         is_null(false)
{ 
//   cout << "AdjVertex.copy_ctor" << endl;
}

/*           
 *          Accessor Functions 
 */

// returns source node of directed edge
template <typename Name, typename Cost>
const Name& AdjVertex<Name,Cost>::tail() const
{
	return v_tail;
}


// returns destination of directed edge 
template <typename Name, typename Cost>
const Name& AdjVertex<Name,Cost>::head() const
{
	return vertex.first;
// return get<V_HEAD>(vertex);
}


template <typename Name, typename Cost>
const Cost& AdjVertex<Name,Cost>::cost() const
{
   return vertex.second;
//   return get<V_COST>(vertex);
}

/*           
 *          Mutators Functions  
 */
template <typename Name, typename Cost>
void AdjVertex<Name,Cost>::chgCost(const Cost &c)
{
   vertex.second  = c;
//   get<V_COST>(vertex) = c;
}

/*           
 *          operator Overloading 
 */
template <typename Name, typename Cost>
bool AdjVertex<Name,Cost>::operator< (const AdjVertex &rhs) const
{
   return this->vertex.second < rhs.vertex.second;
//   return get<V_COST>(vertex) < get<V_COST>(v.vertex);
}

template <typename Name, typename Cost>
bool AdjVertex<Name,Cost>::operator> (const AdjVertex &rhs) const
{
   return this->vertex.second > rhs.vertex.second;
//   return get<V_COST>(vertex) > get<V_COST>(v.vertex);
}

template <typename Name, typename Cost>
AdjVertex<Name,Cost>& AdjVertex<Name,Cost>::operator=(const AdjVertex &rhs)
{  
   this->v_tail         = rhs.v_tail;
   this->vertex.first   = rhs.vertex.first;
   this->vertex.second  = rhs.vertex.second;
   this->is_null        = rhs.is_null;

//   get<V_HEAD>(this.vertex) = get<V_HEAD>(rhs.vertex);
//   get<V_COST>(this.vertex) = get<V_COST>(rhs.vertex);

   return *this;
}

template <typename Name, typename Cost>
string AdjVertex<Name,Cost>::toString () const 
{
   stringstream ss;

   ss << "("  << v_tail << ","; 
   ss << this->vertex.first << ",";
   ss << this->vertex.second << ")";
   ss << "-" << this->is_null;
/*
   str_t.append(","); 
   str_t.append(
   str_t.append(")");
*/
//   string s = ss.str();

   return ss.str();
}

#endif
