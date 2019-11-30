/*
Copyright 2019 Bård Bjerke Johannessen <bbj@bbj.io>

This file is part of the Chronotis date/time C library.

The Chronotis date/time C library is free software: you can
redistribute it and/or modify it under the terms of the GNU General
Public License as published by the Free Software Foundation, either
version 3 of the License, or (at your option) any later version.

The Chronotis date/time C library is distributed in the hope that it
will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with the Chronotis date/time C library. If not, see 
<https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include "../instant.h"

uint8_t test(uint16_t idx, instant_t *instant, uint8_t expect_leap_year) {
	if (instant_is_leap_year(instant) != expect_leap_year) {
		fprintf(stderr, "--------[ instant_is_leap_year(): %04i ]------------------------\n", idx);
		fprintf(stderr, " Instant: %s\n", instant_str(instant));
		fprintf(stderr, "Expected: %s\n", expect_leap_year ? "yes" : "no");
		fprintf(stderr, "     Got: %s\n", instant_is_leap_year(instant) ? "yes" : "no");
		return 1;		
	}

	return 0;
}


int main(int argc, char *argv[]) {
	uint16_t err = 0, idx = 0;

	err += test(++idx, instant_of("2019-11-20 12:13:14"), 0);

	err += test(++idx, instant_of("2000-11-20 12:13:14"), 1);
	err += test(++idx, instant_of("2001-11-20 12:13:14"), 0);
	err += test(++idx, instant_of("2002-11-20 12:13:14"), 0);
	err += test(++idx, instant_of("2003-11-20 12:13:14"), 0);
	err += test(++idx, instant_of("2004-11-20 12:13:14"), 1);
	err += test(++idx, instant_of("2005-11-20 12:13:14"), 0);
	err += test(++idx, instant_of("2006-11-20 12:13:14"), 0);
	err += test(++idx, instant_of("2007-11-20 12:13:14"), 0);
	err += test(++idx, instant_of("2008-11-20 12:13:14"), 1);
	err += test(++idx, instant_of("2009-11-20 12:13:14"), 0);
	err += test(++idx, instant_of("2010-11-20 12:13:14"), 0);
	err += test(++idx, instant_of("2011-11-20 12:13:14"), 0);
	err += test(++idx, instant_of("2012-11-20 12:13:14"), 1);
	err += test(++idx, instant_of("1900-11-20 12:13:14"), 0);
	err += test(++idx, instant_of("1600-11-20 12:13:14"), 1);

	if (err) {
		fprintf(stderr, "instant_is_leap_year(): %i of %i tests failed\n", err, idx);
		return 1;
	}

	fprintf(stderr, "instant_is_leap_year(): %i tests passed\n", idx);

	return 0;
}