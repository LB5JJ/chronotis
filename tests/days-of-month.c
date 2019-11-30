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

uint8_t test(uint16_t idx, instant_t *instant, uint8_t expected_days) {
	if (instant_days_of_month(instant) != expected_days) {
		fprintf(stderr, "--------[ instant_days_of_month(): %04i ]------------------------\n", idx);
		fprintf(stderr, "        Instant: %s\n", instant_str(instant));
		fprintf(stderr, "  Expected days: %i\n", expected_days);
		fprintf(stderr, "  Reported days: %i\n\n", instant_days_of_month(instant));
	}

	return 0;
}

int main(int argc, char *argv[]) {
	uint16_t err = 0, idx = 0;

	err += test(++idx, instant_of("1900-01-15 10:11:12"), 31);	
	err += test(++idx, instant_of("1900-02-15 10:11:12"), 28);	
	err += test(++idx, instant_of("1900-03-15 10:11:12"), 31);	
	err += test(++idx, instant_of("1900-04-15 10:11:12"), 30);	
	err += test(++idx, instant_of("1900-05-15 10:11:12"), 31);	
	err += test(++idx, instant_of("1900-06-15 10:11:12"), 30);	
	err += test(++idx, instant_of("1900-07-15 10:11:12"), 31);	
	err += test(++idx, instant_of("1900-08-15 10:11:12"), 31);	
	err += test(++idx, instant_of("1900-09-15 10:11:12"), 30);	
	err += test(++idx, instant_of("1900-10-15 10:11:12"), 31);	
	err += test(++idx, instant_of("1900-11-15 10:11:12"), 30);	
	err += test(++idx, instant_of("1900-12-15 10:11:12"), 31);	

	err += test(++idx, instant_of("2000-01-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2000-02-15 10:11:12"), 29);	
	err += test(++idx, instant_of("2000-03-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2000-04-15 10:11:12"), 30);	
	err += test(++idx, instant_of("2000-05-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2000-06-15 10:11:12"), 30);	
	err += test(++idx, instant_of("2000-07-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2000-08-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2000-09-15 10:11:12"), 30);	
	err += test(++idx, instant_of("2000-10-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2000-11-15 10:11:12"), 30);	
	err += test(++idx, instant_of("2000-12-15 10:11:12"), 31);	

	err += test(++idx, instant_of("2019-01-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2019-02-15 10:11:12"), 28);	
	err += test(++idx, instant_of("2019-03-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2019-04-15 10:11:12"), 30);	
	err += test(++idx, instant_of("2019-05-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2019-06-15 10:11:12"), 30);	
	err += test(++idx, instant_of("2019-07-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2019-08-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2019-09-15 10:11:12"), 30);	
	err += test(++idx, instant_of("2019-10-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2019-11-15 10:11:12"), 30);	
	err += test(++idx, instant_of("2019-12-15 10:11:12"), 31);	

	err += test(++idx, instant_of("2020-01-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2020-02-15 10:11:12"), 29);	
	err += test(++idx, instant_of("2020-03-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2020-04-15 10:11:12"), 30);	
	err += test(++idx, instant_of("2020-05-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2020-06-15 10:11:12"), 30);	
	err += test(++idx, instant_of("2020-07-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2020-08-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2020-09-15 10:11:12"), 30);	
	err += test(++idx, instant_of("2020-10-15 10:11:12"), 31);	
	err += test(++idx, instant_of("2020-11-15 10:11:12"), 30);	
	err += test(++idx, instant_of("2020-12-15 10:11:12"), 31);	

	if (err) {
		fprintf(stderr, "instant_days_of_month(): %i of %i tests failed\n", err, idx);
		return 1;
	}

	fprintf(stderr, "instant_days_of_month(): %i tests passed\n", idx);

	return 0;
}
