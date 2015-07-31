#include "fundirectededge.h"

FUndirectedEdge::FUndirectedEdge()
{

}

FUndirectedEdge::FUndirectedEdge(int node1, int node2, double weight)
{
    this->node1 = node1;
    this->node2 = node2;
    this->weight = weight;
}
