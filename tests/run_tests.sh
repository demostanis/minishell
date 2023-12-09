#!/bin/sh

cwd="$(dirname "$0")"

CC=cc
CFLAGS='-Wall -Werror -Wall -g'
LIBTEST=-I"$cwd"
LIBFT=-I"$cwd"/../libft

marker='Oh nuuuu!!! Leaks! OwO'

for file in "$cwd"/test_*.c; do
	name="${file##*/}"
	name="${file%%.c}"
	$CC $CFLAGS \
		"$LIBTEST" "$LIBFT" \
		"$cwd"/libtest.c "$cwd"/../libft/libft.a \
		"$file"	-o "$name"
	trap 'rm -f "$name"' EXIT
	logfile=$(mktemp)
	trap 'rm -f "$logfile"' EXIT
	# we need to use markers instead
	# of --error-exitcode since valgrind
	# does not exit with the specific exitcode
	# if the children have errors
	echo -n "$name... "
	valgrind \
		--log-file="$logfile" \
		--suppressions="$cwd"/readline-leaks.sup \
		--trace-children=yes --show-leak-kinds=all \
		--error-markers="$marker" --leak-check=full ./"$name"
	if [ $? != 0 ] || grep -q "$marker" "$logfile"; then
		cat "$logfile" | \
			grep -av "$marker" | \
			sed 's/=\?==[0-9]\+\(== \)\?//g' | \
			grep -av 'rerun with: -s' | \
			tail +11 | head -n -8 >&2
	else
		echo OK
	fi
	rm "$name"
done
