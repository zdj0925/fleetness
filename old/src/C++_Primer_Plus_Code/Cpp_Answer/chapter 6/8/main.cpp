#include <iostream>
#include <fstream>


int
main (void) 
{     
	using namespace std;

	ifstream	ifs("test_(for_linux).txt");
	unsigned	cntChars = 0;
	char		ch;
	while (ifs.get(ch)) {
		++cntChars;
	}
	--cntChars;	// 抛掉读入的EOF符
	cout << cntChars << endl;

	cout << endl;
	return (0);
} 
