#pragma once

inline void Report_Tree_Behaviour_Blocker()
{
    BOOST_FAIL("Tree behaviour is currently blocked at the implementation boundary: Tree.hpp is not directly compilable as an ADT base, and the available high-order tree implementations do not currently provide a compileable child-sibling behaviour path matching Tree.md.");
}
