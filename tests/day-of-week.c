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

uint8_t test(uint16_t idx, instant_t *instant, uint8_t expect) {
	if (instant_day_of_week(instant) != expect) {
		fprintf(stderr, "--------[ instant_day_of_week: %04i ]------------------------\n", idx);
		fprintf(stderr, "    Instant: %s\n", instant_str(instant));
		fprintf(stderr, "Day-of-Week: %i\n", instant_day_of_week(instant));
		fprintf(stderr, "   Expected: %i\n\n", expect);

		return 1;		
	}

	return 0;
}

int main(int argc, char *argv[]) {
	uint16_t err = 0, idx = 0;

	err += test(++idx, instant_of("2019-11-20 00:00:00"), INSTANT_DAY_OF_WEEK_WEDNESDAY);
	err += test(++idx, instant_of("2019-11-21 00:00:00"), INSTANT_DAY_OF_WEEK_THURSDAY);
	err += test(++idx, instant_of("2019-11-22 00:00:00"), INSTANT_DAY_OF_WEEK_FRIDAY);
	err += test(++idx, instant_of("2019-11-23 00:00:00"), INSTANT_DAY_OF_WEEK_SATURDAY);
	err += test(++idx, instant_of("2019-11-24 00:00:00"), INSTANT_DAY_OF_WEEK_SUNDAY);
	err += test(++idx, instant_of("2019-11-25 00:00:00"), INSTANT_DAY_OF_WEEK_MONDAY);
	err += test(++idx, instant_of("2019-11-26 00:00:00"), INSTANT_DAY_OF_WEEK_TUESDAY);

	err += test(++idx, instant_of("1972-05-28 00:00:00"), INSTANT_DAY_OF_WEEK_SUNDAY);
	err += test(++idx, instant_of("1672-09-25 00:00:00"), INSTANT_DAY_OF_WEEK_SUNDAY);
	err += test(++idx, instant_of("1582-10-15 00:00:00"), INSTANT_DAY_OF_WEEK_FRIDAY);
	err += test(++idx, instant_of("1682-05-04 00:00:00"), INSTANT_DAY_OF_WEEK_MONDAY);

	err += test(++idx, instant_of("1600-02-28 00:00:00"), INSTANT_DAY_OF_WEEK_MONDAY);
	err += test(++idx, instant_of("1600-02-29 00:00:00"), INSTANT_DAY_OF_WEEK_TUESDAY);
	err += test(++idx, instant_of("1600-03-01 00:00:00"), INSTANT_DAY_OF_WEEK_WEDNESDAY);

	err += test(++idx, instant_of("1800-02-27 00:00:00"), INSTANT_DAY_OF_WEEK_THURSDAY);
	err += test(++idx, instant_of("1800-02-28 00:00:00"), INSTANT_DAY_OF_WEEK_FRIDAY);
	err += test(++idx, instant_of("1800-03-01 00:00:00"), INSTANT_DAY_OF_WEEK_SATURDAY);

	err += test(++idx, instant_of("1804-02-28 00:00:00"), INSTANT_DAY_OF_WEEK_TUESDAY);
	err += test(++idx, instant_of("1804-02-29 00:00:00"), INSTANT_DAY_OF_WEEK_WEDNESDAY);
	err += test(++idx, instant_of("1804-03-01 00:00:00"), INSTANT_DAY_OF_WEEK_THURSDAY);

	if (err) {
		fprintf(stderr, "instant_day_of_week(): %i of %i tests failed\n", err, idx);
		return 1;
	}

	fprintf(stderr, "instant_day_of_week(): %i tests passed\n", idx);

	return 0;
}