make

for i in (find ./tests -name "test*.gmr")
	./avm --grammar-file $i tests/test1.input
end
