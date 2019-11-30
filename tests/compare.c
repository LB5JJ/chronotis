/* Copyright 2019 Bård Bjerke Johannessen <bbj@bbj.io>

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
<https://www.gnu.org/licenses/>. */

#include <stdio.h>
#include "../instant.h"

uint8_t before(uint16_t idx, instant_t *instant1, instant_t *instant2) {
	if (!instant_is_before(instant1, instant2)) {
		fprintf(stderr, "--------[ instant_is_before: %04i ]------------------------\n", idx);
		fprintf(stderr, "  Instant: %s\n", instant_str(instant1));
		fprintf(stderr, "Is-Before: %s\n", instant_str(instant2));
		fprintf(stderr, " Expected: true\n");
		fprintf(stderr, "      Got: false\n\n");

		return 1;
	}

	return 0;
}

uint8_t after(uint16_t idx, instant_t *instant1, instant_t *instant2) {
	if (!instant_is_after(instant1, instant2)) {
		fprintf(stderr, "--------[ instant_is_after: %04i ]------------------------\n", idx);
		fprintf(stderr, " Instant: %s\n", instant_str(instant1));
		fprintf(stderr, "Is-After: %s\n", instant_str(instant2));
		fprintf(stderr, "Expected: true\n");
		fprintf(stderr, "     Got: false\n\n");

		return 1;
	}

	return 0;
}

uint8_t equal(uint16_t idx, instant_t *instant1, instant_t *instant2) {
	if (!instant_is_equal(instant1, instant2)) {
		fprintf(stderr, "--------[ instant_is_equal: %04i ]------------------------\n", idx);
		fprintf(stderr, " Instant: %s\n", instant_str(instant1));
		fprintf(stderr, "Is-Equal: %s\n", instant_str(instant2));
		fprintf(stderr, "Expected: true\n");
		fprintf(stderr, "     Got: false\n\n");

		return 1;
	}

	return 0;
}

int main(int argc, char *argv[]) {
	uint16_t err = 0, idx = 0;

	instant_t instant1 = { 2019, 11, 20, 12, 13, 14 };
	instant_t instant2 = { 2018, 11, 20, 12, 13, 14 };


	err += after(++idx, &instant1, &instant2);
	err += before(++idx, &instant2, &instant1);


	instant2.year = 2019;
	err += equal(++idx, &instant1, &instant2);
	err += equal(++idx, &instant2, &instant1);


	instant1.second++;
	err += after(++idx, &instant1, &instant2);
	err += before(++idx, &instant2, &instant1);

	instant2.second++;
	err += equal(++idx, &instant1, &instant2);
	err += equal(++idx, &instant2, &instant1);

	instant2.second++;
	err += after(++idx, &instant2, &instant1);
	err += before(++idx, &instant1, &instant2);
	instant1.second++;


	instant2.minute++;
	err += after(++idx, &instant2, &instant1);
	err += before(++idx, &instant1, &instant2);

	instant1.minute++;
	err += equal(++idx, &instant1, &instant2);
	err += equal(++idx, &instant2, &instant1);

	instant1.minute++;
	err += after(++idx, &instant1, &instant2);
	err += before(++idx, &instant2, &instant1);
	instant2.minute++;


	instant1.hour++;
	err += after(++idx, &instant1, &instant2);
	err += before(++idx, &instant2, &instant1);

	instant2.hour++;
	err += equal(++idx, &instant1, &instant2);
	err += equal(++idx, &instant2, &instant1);

	instant2.hour++;
	err += after(++idx, &instant2, &instant1);
	err += before(++idx, &instant1, &instant2);
	instant1.hour++;

	instant2.day++;
	err += after(++idx, &instant2, &instant1);
	err += before(++idx, &instant1, &instant2);

	instant1.day++;
	err += equal(++idx, &instant1, &instant2);
	err += equal(++idx, &instant2, &instant1);

	instant1.day++;
	err += after(++idx, &instant1, &instant2);
	err += before(++idx, &instant2, &instant1);
	instant2.day++;

	instant1.month++;
	err += after(++idx, &instant1, &instant2);
	err += before(++idx, &instant2, &instant1);

	instant2.month++;
	err += equal(++idx, &instant1, &instant2);
	err += equal(++idx, &instant2, &instant1);

	instant2.month++;
	err += after(++idx, &instant2, &instant1);
	err += before(++idx, &instant1, &instant2);
	instant1.month++;

	instant2.year++;
	err += after(++idx, &instant2, &instant1);
	err += before(++idx, &instant1, &instant2);

	instant1.year++;
	err += equal(++idx, &instant1, &instant2);
	err += equal(++idx, &instant2, &instant1);

	instant1.year++;
	err += after(++idx, &instant1, &instant2);
	err += before(++idx, &instant2, &instant1);
	instant2.year++;

	err += equal(++idx, &instant1, &instant2);
	err += equal(++idx, &instant2, &instant1);

	if (err) {
		fprintf(stderr, "instant_compare(): %i of %i tests failed\n", err, idx);
		return 1;
	}

	fprintf(stderr, "instant_compare(): %i tests passed\n", idx);

	return 0;
}
