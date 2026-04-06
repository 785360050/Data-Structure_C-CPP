#pragma once

template <typename GraphType>
void Check_Graph_Vertex_Add_Delete_Behaviour()
{
    GraphType graph;

    BOOST_CHECK_EQUAL(graph.Vertex_Count(), 0);
    BOOST_CHECK_EQUAL(graph.Edge_Count(), 0);

    graph.Vertex_Add("a", 1);
    graph.Vertex_Add("b", 2);
    graph.Vertex_Add("c", 3);
    BOOST_CHECK_EQUAL(graph.Vertex_Count(), 3);

    graph.Vertex_Delete("b");
    BOOST_CHECK_EQUAL(graph.Vertex_Count(), 2);
}

template <typename GraphType>
void Check_Graph_Edge_Add_Delete_Behaviour()
{
    GraphType graph;

    graph.Vertex_Add("a", 1);
    graph.Vertex_Add("b", 2);
    graph.Vertex_Add("c", 3);

    graph.Edge_Add("a", "b", 5);
    BOOST_CHECK_EQUAL(graph.Edge_Count(), 1);

    graph.Edge_Add("a", "c", 7);
    BOOST_CHECK_EQUAL(graph.Edge_Count(), 2);

    graph.Edge_Delete("a", "b");
    BOOST_CHECK_EQUAL(graph.Edge_Count(), 1);
}

template <typename GraphType>
void Check_Graph_Vertex_Delete_Removes_Incident_Edges_Behaviour()
{
    GraphType graph;

    graph.Vertex_Add("a", 1);
    graph.Vertex_Add("b", 2);
    graph.Vertex_Add("c", 3);
    graph.Edge_Add("a", "b", 1);
    graph.Edge_Add("b", "c", 2);

    BOOST_CHECK_EQUAL(graph.Edge_Count(), 2);
    graph.Vertex_Delete("b");
    BOOST_CHECK_EQUAL(graph.Edge_Count(), 0);
}

template <typename GraphType>
void Run_Graph_Behaviour_Suite()
{
    Check_Graph_Vertex_Add_Delete_Behaviour<GraphType>();
    Check_Graph_Edge_Add_Delete_Behaviour<GraphType>();
    Check_Graph_Vertex_Delete_Removes_Incident_Edges_Behaviour<GraphType>();
}
