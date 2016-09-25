#include <iostream>
#include <cwcsv/csv.h>

using namespace std;

int main( int argc, char** argv ) {

	auto& text = "a,b,c,d,e\n"
	             "1,2,3,4,5\n"
	             "\" 6 \",\"\"\"7\"\"\",\"8,8,8\",\"9\n9\n9\",\"\"\"\"\"10\"\"\"\"\"\n";

	auto parser = csv::make_parser( text );

	for( auto&& row : parser ) {
		for( auto&& cell : row ) {
			cout << '[' << cell.to_int() << ']';
		}
		cout << '\n';
	}

	std::string out;

	auto writer = csv::make_writer( back_inserter(out) );

	writer.write_row( 3, "\"", 5.5 );
	writer.write_row( 3, ",", 5.5 );
	writer.write_row( 3, "a,,,,b", 5.5 );
	writer.write_row( 3, "a", 5.5 );

	auto ex = {
		",1,","2","3","\"4\"","5","6","7"
	};

	writer.write_row( ex.begin(), ex.end() );


	cout << out;

	cin.get();
}

