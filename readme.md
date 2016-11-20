# cwcsv

CSV reading and writing

* No allocation on traversing cells and rows
* Supports arbitrary separator, quote and newline symbols


## Reading

### From a string literal

```cpp
auto& text = "a,b,c,d,e\n"
             "1,2,3,4,5";

auto parser = csv::make_parser( text );

for( auto&& row : parser ) {
	for( auto&& cell : row ) {
		cout << '[' << cell.to_string() << ']';
	}
	cout << '\n';
}
```

### From a file

```cpp
// first load the file into a std::string
auto str = csv::load_file("test.csv");

auto parser = csv::make_parser( str );

for( auto&& row : parser ) {
	for( auto&& cell : row ) {
		cout << '[' << cell.to_string() << ']';
	}
	cout << '\n';
}
```

```cpp
auto row = parser.begin();
++row; // skip header

std::vector<int> data;

std::transform( row.begin(), row.end(), std::back_inserter(data), []( auto&& x ){ return x.to_int(); });

for( auto&& x : data ) {
	cout << '[' << x << ']';
}
cout << '\n';
```

## Writing

### To string

```cpp
std::string out;

auto writer = csv::make_writer( std::back_inserter(out) );

writer.write_row( "Open", "High", "Low", "Close" );
writer.write_row( 101, 102.5, 99.8, 102 );

auto vals = { 100.2, 103.1, 98.6, 101.5 };

writer.write_row_range( vals.begin(), vals.end() );
```

### To file

```cpp
std::ofstream out("test.csv");

auto writer = csv::make_writer( out );

writer.write_row( "Open", "High", "Low", "Close" );
writer.write_row( 101, 102.5, 99.8, 102 );

auto vals = { 100.2, 103.1, 98.6, 101.5 };

writer.write_row_range( vals.begin(), vals.end() );
```
