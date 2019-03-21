#!/bin/sh

#setting libft_malloc path
cd `dirname $0`/..
mallocPath="$PWD"
mallocLib="libft_malloc_$hosttype.so"
export HOSTTYPE="TESTING"

#checking if git repo isn't empty
repoContent=`ls $mallocPath`
checkMsg="Empty repo"
if [ ! -z "$repoContent" ]
then
	#Checking for Author File
	checkMsg="Author File"
	author=`printf "%s\n" $USER`
	authorFileContent=`cat $mallocPath/auteur`
	if [ "$authorFileContent" == "$author" ]
	then
		#checking if Makefile has got rules "all" "clean" "fclean" re
		checkMsg="Makefile rules"
		make -C $mallocPath all > /dev/null
		let "ret = $?"
		make -C $mallocPath re > /dev/null
		let "ret = $ret + $?"
		make -C $mallocPath clean > /dev/null
		let "ret = $ret + $?"
		make -C $mallocPath fclean > /dev/null
		let "ret = $ret + $?"
		if [ $ret -eq 0 ]
		then
			#Checking Norme
			checkMsg="Norme"
			normeResult=`norminette ./**/*.[ch] | grep Error`
			if [ -z "$normeResult" ]
			then
				echo "all preliminary tests are OK"
				if [ -x "$1" ]
				then
					$1
				fi
				exit
			fi
		fi
	fi
fi
echo "$checkMsg : FAILED"
