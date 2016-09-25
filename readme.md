# cwcsv

CSV reading and writing

* No allocation on traversing cells and rows
* Supports arbitrary separator, quote and newline symbols

```cpp
auto& text = "a,b,c,d,e\n"
             "1,2,3,4,5\n"
             "\" 6 \",\"\"\"7\"\"\",\"8,8,8\",\"9\n9\n9\",\"\"\"\"\"10\"\"\"\"\"\n";

auto parser = csv::make_parser( text );

for( auto&& row : parser ) {
	for( auto&& cell : row ) {
		cout << '[' << cell.to_string() << ']';
	}
	cout << '\n';
}
```