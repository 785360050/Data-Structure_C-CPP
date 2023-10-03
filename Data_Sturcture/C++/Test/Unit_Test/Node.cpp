#include "../../Node.hpp"
#include "Test_Element.hpp"

#define BOOST_TEST_MODULE Stack
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Node_Base)
{
    {
        Node<int> node, node5{5}, node_copy{node};
        BOOST_CHECK(node.element == int{});
        BOOST_CHECK(node5.element == 5);
        BOOST_CHECK(node_copy.element == node.element);
        Node<int> node_move(std::move(node5));
        BOOST_CHECK(node5.element == 0);
        BOOST_CHECK(node_move.element == 5);
    }

    {
        using Element = Element<int>;
        Node<Element> node, node5{{5, 5}}, node_copy{node};
        BOOST_CHECK(node.element == Element{});
        BOOST_CHECK(node5.element == Element(5, 5));
        BOOST_CHECK(node_copy.element == node.element);
        Node<Element> node_move(std::move(node5));
        BOOST_CHECK(node5.element == Element{});
        BOOST_CHECK(node_move.element == Element(5, 5));
    }
    
}