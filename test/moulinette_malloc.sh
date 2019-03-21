#!/bin/sh

compileTests() {
	for nb in `seq 0 4`
	do
		gcc -o "$mallocPath/tests/test$nb" "$mallocPath/tests/test$nb.c"
	done
	gcc -o "$mallocPath/tests/test3b" "$mallocPath/tests/test3b.c"
}

getPageReclaimsNb() {
	local result=""
	if [ ! -z "$1" ]
	then
		result=`/usr/bin/time -l "$mallocPath/tests/run.sh" "$mallocPath/tests/$1" 2>&1 | grep "page reclaims" | sed 's/[^0-9]//g'`
	else
		result="0"
	fi
	echo $result
}

#Setting hosttype
hosttype=`LC_CTYPE=C tr -dc 'a-zA-Z0-9' < /dev/urandom | fold -w 16 | head -n1`
export HOSTTYPE="$hosttype"

#setting libft_malloc path
cd `dirname $0`/..
mallocPath="$PWD"
libName="libft_malloc_$hosttype.so"
linkName="libft_malloc.so"

#Checking libft_malloc_$(HOSTTYPE).so is properly created
make -C $mallocPath re > /dev/null
checkMsg='libft_malloc.so -> libft_malloc_$(HOSTTYPE).so'
if [ -L "$linkName" ]
then
	linkTarget=`readlink $linkName`
	if [ -f "$linkTarget" ]
	then
		#Checking that libft_malloc.so actually exports required functions
		checkMsg="all required function properly exported by $linkName"
		let "libContent=`nm $linkName | grep -e " T _free" -e " T _malloc" -e " T _realloc" -e " T _free" -e " T _show_alloc_mem" | wc -l`"
		if [ $libContent -ge 4 ]
		then
			#Checking page reclaims numbers, test0 vs test1
			testMsg="page reclaims (test0 vs test1)"
			checkMsg=""
			compileTests
			let "result0=`getPageReclaimsNb 'test0'`"
			let "result1=`getPageReclaimsNb 'test1'`"
			let "diff= $result1 - $result0"
			if [ $diff -lt 255 ]
			then
				grade="0"
			elif [ $diff -ge 1023 ]
			then
				grade="1"
			elif [[ $diff -ge 313 && $diff -le 1022 ]]
			then
				grade="2"
			elif [[ $diff -ge 313 && $diff -le 512 ]]
			then
				grade="3"
			elif [[ $diff -ge 273 && $diff -le 312 ]]
			then
				grade="4"
			elif [[ $diff -ge 255 && $diff -le 272 ]]
			then
				grade="5"
			fi

			#Checking that the pre-allocated zones can hold at least 100 max size allocations
			printf "Are pre-allocated zones able to hold AT LEAST 100 max-sizes allocations? (y/n) "
			read ans
			if echo "$ans" | grep -iq "^y"
			then
				preAllocates="OK"
			else
				preAllocates="KO"
			fi

			#Checking if free functions properly
			let "result1=`getPageReclaimsNb 'test1'`"
			let "result2=`getPageReclaimsNb 'test2'`"
			if [ $result2 -lt $result1 ]
			then
				basicFree="OK"
			else
				basicFree="KO"
			fi
			let "diff=$result2 - $result0"
			if [ $diff -le 3 ]
			then
				advancedFree="OK"
			else
				advancedFree="KO"
			fi

			#Checking that realloc functions properly
			correctOutput=`printf "Bonjours\nBonjours\n"`
			testOutput=`$mallocPath/tests/run.sh $mallocPath/tests/test3`
			if [ "$correctOutput" == "$testOutput" ]
			then
				basicRealloc="OK"
			else
				basicRealloc="KO"
			fi
			testOutput=`$mallocPath/tests/run.sh $mallocPath/tests/test3b`
			if [ "$correctOutput" == "$testOutput" ]
			then
				advancedRealloc="OK"
			else
				advancedRealloc="KO"
			fi

			#Checking if errors are properly handled
			testOutput=`$mallocPath/tests/run.sh $mallocPath/tests/test4`
			if [ "$correctOutput" == "$testOutput" ]
			then
				errorHandling="OK"
			else
				errorHandling="KO"
			fi
		fi
	fi
fi
rm -f $mallocPath/tests/test?
rm -f "$mallocPath/tests/test3b"
if [ ! -z "$checkMsg" ]
then
	echo "$checkMsg : FAILED"
else
	printf "malloc memory consumption : %s / 5\n" "$grade"
	printf "Pre-allocated zones can hold at least 100 max size mallocs : %s\n" "$preAllocates"
	printf "basic free tests : %s\n" "$basicFree"
	printf "advanced free tests : %s\n" "$advancedFree"
	printf "basic realloc tests : %s\n" "$basicRealloc"
	printf "advanced realloc tests : %s\n" "$advancedRealloc"
	printf "error handling : %s\n" "$errorHandling"
	printf "Now you can grade the quality of show_alloc_mem and bonuses, if any!\n"
fi
printf "Do you want to fclean malloc directory? (y/n) "
read ans
if echo "$ans" | grep -iq "^y"
then
	make fclean > /dev/null
fi
