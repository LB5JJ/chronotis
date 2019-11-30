# Copyright 2019 Bård Bjerke Johannessen <bbj@bbj.io>
# 
# This file is part of the Chronotis date/time C library.
# 
# The Chronotis date/time C library is free software: you can
# redistribute it and/or modify it under the terms of the GNU General
# Public License as published by the Free Software Foundation, either
# version 3 of the License, or (at your option) any later version.
# 
# The Chronotis date/time C library is distributed in the hope that it
# will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
# the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with the Chronotis date/time C library. If not, see 
# <https://www.gnu.org/licenses/>.

tests: format parse compare is-leap-year is-am-pm days-of-month validate day-of-week
	@./format
	@./parse
	@./compare
	@./is-leap-year
	@./is-am-pm
	@./days-of-month
	@./validate
	@./day-of-week

format: Makefile format.c ../instant.h ../instant.c
	gcc -Wall format.c ../instant.c -o format

parse: Makefile parse.c ../instant.h ../instant.c
	gcc -Wall parse.c ../instant.c -o parse

compare: Makefile compare.c ../instant.h ../instant.c
	gcc -Wall compare.c ../instant.c -o compare

is-leap-year: Makefile is-leap-year.c ../instant.h ../instant.c
	gcc -Wall is-leap-year.c ../instant.c -o is-leap-year

is-am-pm: Makefile is-am-pm.c ../instant.h ../instant.c
	gcc -Wall is-am-pm.c ../instant.c -o is-am-pm

days-of-month: Makefile days-of-month.c ../instant.h ../instant.c
	gcc -Wall days-of-month.c ../instant.c -o days-of-month

validate: Makefile validate.c ../instant.h ../instant.c
	gcc -Wall validate.c ../instant.c -o validate

day-of-week: Makefile day-of-week.c ../instant.h ../instant.c
	gcc -Wall day-of-week.c ../instant.c -o day-of-week

.PHONY: clean

clean:
	rm -Rf format parse compare is-leap-year is-am-pm days-of-month validate day-of-week