#include "String.hpp">



void main()
{
	String x("aabaabaaf");///3
	//String x("ABCDABCABCABABCABCDA");///12
	//String x("bacbababaabcbab");///-1
	//String x("ABADABABC");///6
	//String x("ABC");///2

	String y("aabaaf");
	//String y("ABCABCD");
	//String y("abababca");
	//String y("ABC");
	//String y("C");
	//std::cout<<x.String_Fetch_KMP(y);
	std::cout<<x.String_Fetch_Brute_Force(y);
}



