#pragma once
#include <iostream>
#include <vector>
using namespace std;


namespace Spliter
{
	vector<string> Split(string S1, string Separator)
	{
		vector<string> vData;
		short pos = 0;
		string sWords = "";

		while ((pos = S1.find(Separator)) != std::string::npos)
		{
			sWords = S1.substr(0, pos);

			if (sWords != "")
			{
				vData.push_back(sWords);
			}

			S1.erase(0, pos + Separator.length());
		}
		if (S1 != "")
		{
			vData.push_back(S1);
		}

		return vData;
	}
}