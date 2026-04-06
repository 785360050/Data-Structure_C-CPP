#define BOOST_TEST_MODULE Graph_AdjacencyList_Behaviour
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Behaviour.hpp"
#include "Graph_Structure/Graph_AdjacencyList/Graph_AdjacencyList.hpp"

template <bool Directed>
class Graph_AdjacencyList_TestHarness : public Storage::Graph_AdjacencyList<int, Directed>
{
public:
    int Vertex_Count() const { return this->num_vertex; }
    int Edge_Count() const { return this->num_edge; }
};

BOOST_AUTO_TEST_SUITE(Graph)
BOOST_AUTO_TEST_SUITE(Behaviour)

BOOST_AUTO_TEST_CASE(AdjacencyList_Undirected_Behaviour)
{
    Run_Graph_Behaviour_Suite<Graph_AdjacencyList_TestHarness<false>>();
}

BOOST_AUTO_TEST_CASE(AdjacencyList_Directed_Behaviour)
{
    Run_Graph_Behaviour_Suite<Graph_AdjacencyList_TestHarness<true>>();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
