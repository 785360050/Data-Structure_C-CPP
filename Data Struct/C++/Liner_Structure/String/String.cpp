#include "String.h">





int String_Fetch_Brute_Force(const String& string, const String& Sub_String)
{
	int i_fetch = 1;
	for (; i_fetch <= string.length; ++i_fetch)
	{
		int i_sub = 1;
		for (; i_sub <= Sub_String.length; ++i_sub)
			if (
				string.string_[i_fetch + i_sub] 
				!= 
				Sub_String.string_[i_sub]
			   )
				break;
		if (i_sub >= Sub_String.length)
			return i_fetch + 1;
	}
	return 1;
}


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



