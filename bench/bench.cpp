#include <iostream>
#include <fstream>
#include <chrono>
#include <cwcsv/csv.h>

std::string load_file( const char* filename ) {
	std::fstream in( filename );
	if( !in )
		return {};

	in.seekg(0,std::ios::end);
	auto len = in.tellg();
	in.seekg(0,std::ios::beg);

	std::string output( len, '\0' );
	in.read( &output[0], len );
	auto actual_len = in.gcount();
	output.erase( actual_len );
	return output;
}

void benchmark( const std::string& data, uint32_t N ) {
	auto parser = csv::make_parser( data );

	uint32_t nb_rows = 0;
	uint32_t nb_cells = 0;

	using namespace std::chrono;
	auto beg_time = high_resolution_clock::now();

	for(uint32_t i=0;i<N;++i) {
		nb_rows = 0;
		nb_cells = 0;
		for( auto&& row : parser ) {
			++nb_rows;
			for( auto&& cell : row ) {
				++nb_cells;
			}
		}
	}

	auto end_time = high_resolution_clock::now();

	auto time = duration_cast<microseconds>( end_time - beg_time );

	std::cout
		<< "rows: " << nb_rows
		<< "\ncells: " << nb_cells
		<< "\ncells/row: " << (double)nb_cells/nb_rows
		<< "\ntime: " << time.count() / N
		<< " us/cell\n";
}

int main( int argc, char** argv ) {

	const char* file = ( argc > 1 ) ? argv[1] : "sample.csv";
	uint32_t N = 1000;

	benchmark( load_file( file ), N );

}

