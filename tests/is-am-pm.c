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

uint8_t am(uint16_t idx, instant_t *instant, uint8_t expect) {
	if (instant_is_am(instant) != expect) {
		fprintf(stderr, "--------[ instant_is_am(): %04i ]------------------------\n", idx);
		fprintf(stderr, " Instant: %s\n", instant_str(instant));
		fprintf(stderr, "Expected: %i\n", expect);
		fprintf(stderr, "  Result: %i\n\n", instant_is_am(instant));

		return 1;		
	}

	return 0;
}

uint8_t pm(uint16_t idx, instant_t *instant, uint8_t expect) {
	if (instant_is_pm(instant) != expect) {
		fprintf(stderr, "--------[ instant_is_pm(): %04i ]------------------------\n", idx);
		fprintf(stderr, " Instant: %s\n", instant_str(instant));
		fprintf(stderr, "Expected: %i\n", expect);
		fprintf(stderr, "  Result: %i\n\n", instant_is_pm(instant));

		return 1;		
	}

	return 0;
}


int main(int argc, char *argv[]) {
	uint16_t err = 0, idx = 0;

	instant_t instant = { 2019, 11, 20, 0, 0, 0 };

	err += am(++idx, &instant, 1);
	err += pm(++idx, &instant, 0);

	instant.hour = 1;
	err += am(++idx, &instant, 1);
	err += pm(++idx, &instant, 0);

	instant.hour = 2;
	err += am(++idx, &instant, 1);
	err += pm(++idx, &instant, 0);

	instant.hour = 3;
	err += am(++idx, &instant, 1);
	err += pm(++idx, &instant, 0);

	instant.hour = 4;
	err += am(++idx, &instant, 1);
	err += pm(++idx, &instant, 0);

	instant.hour = 5;
	err += am(++idx, &instant, 1);
	err += pm(++idx, &instant, 0);

	instant.hour = 6;
	err += am(++idx, &instant, 1);
	err += pm(++idx, &instant, 0);

	instant.hour = 7;
	err += am(++idx, &instant, 1);
	err += pm(++idx, &instant, 0);

	instant.hour = 8;
	err += am(++idx, &instant, 1);
	err += pm(++idx, &instant, 0);

	instant.hour = 9;
	err += am(++idx, &instant, 1);
	err += pm(++idx, &instant, 0);

	instant.hour = 10;
	err += am(++idx, &instant, 1);
	err += pm(++idx, &instant, 0);

	instant.hour = 11;
	err += am(++idx, &instant, 1);
	err += pm(++idx, &instant, 0);

	instant.hour = 12;
	err += pm(++idx, &instant, 1);
	err += am(++idx, &instant, 0);

	instant.hour = 13;
	err += pm(++idx, &instant, 1);
	err += am(++idx, &instant, 0);

	instant.hour = 14;
	err += pm(++idx, &instant, 1);
	err += am(++idx, &instant, 0);

	instant.hour = 15;
	err += pm(++idx, &instant, 1);
	err += am(++idx, &instant, 0);

	instant.hour = 16;
	err += pm(++idx, &instant, 1);
	err += am(++idx, &instant, 0);

	instant.hour = 17;
	err += pm(++idx, &instant, 1);
	err += am(++idx, &instant, 0);

	instant.hour = 18;
	err += pm(++idx, &instant, 1);
	err += am(++idx, &instant, 0);

	instant.hour = 19;
	err += pm(++idx, &instant, 1);
	err += am(++idx, &instant, 0);

	instant.hour = 20;
	err += pm(++idx, &instant, 1);
	err += am(++idx, &instant, 0);

	instant.hour = 21;
	err += pm(++idx, &instant, 1);
	err += am(++idx, &instant, 0);

	instant.hour = 22;
	err += pm(++idx, &instant, 1);
	err += am(++idx, &instant, 0);

	instant.hour = 23;
	err += pm(++idx, &instant, 1);
	err += am(++idx, &instant, 0);

	if (err) {
		fprintf(stderr, "instant_is_am/pm(): %i of %i tests failed\n", err, idx);
		return 1;
	}

	fprintf(stderr, "instant_is_am/pm(): %i tests passed\n", idx);

	return 0;
}