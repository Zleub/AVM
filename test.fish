clear ; make ;

# and ./avm -gmr "main = a" -in "a"
# if test $status -eq 0
# 	echo "ok"
# else
# 	echo "ko"
# end

# for i in (find ./tests -name "test*.gmr")
# 	./avm --grammar-file $i tests/test1.input
# end

for e in './avm -gmr "main = a" -in "a" true' \
	'./avm -gmr "main = a" -in "ab" false' \
	'./avm -gmr "main = a,b" -in "ab" true' \
	'./avm -gmr "main = a|b" -in "a" true' \
	'./avm -gmr "main = a|b" -in "b" true' \
	'./avm -gmr "main = a|b" -in "ab" false' \

	eval $test[8]
	set -l ret $status
	echo (string split " " $e)[1..7]
	eval (string split " " $e)[1..7]
	if test $status -eq $ret
		echo "ok"
	else
		echo "ko"
	end
end
