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
#include <string.h>
#include <inttypes.h>
#include "../instant.h"

uint8_t test_instant_validate(uint16_t idx, instant_t *instant, uint8_t expect) {
	if (instant_validate(instant) != expect) {
		fprintf(stderr, "--------[ instant_validate(): %04i ]------------------------\n", idx);
		fprintf(stderr, " Instant: %s\n", instant_str(instant));
		fprintf(stderr, "  Result: %02x\n", instant_validate(instant));
		fprintf(stderr, "Expected: %02x\n\n", expect);

		return 1;
	}

	return 0;
}

uint8_t test_instant_validate_date(uint16_t idx, instant_t *instant, uint8_t expect) {
	if (instant_validate_date(instant) != expect) {
		fprintf(stderr, "--------[ instant_validate_date(): %04i ]------------------------\n", idx);
		fprintf(stderr, " Instant: %s\n", instant_str(instant));
		fprintf(stderr, "  Result: %02x\n", instant_validate_date(instant));
		fprintf(stderr, "Expected: %02x\n\n", expect);

		return 1;
	}

	return 0;
}

uint8_t test_instant_validate_time(uint16_t idx, instant_t *instant, uint8_t expect) {
	if (instant_validate_time(instant) != expect) {
		fprintf(stderr, "--------[ instant_validate_time(): %04i ]------------------------\n", idx);
		fprintf(stderr, " Instant: %s\n", instant_str(instant));
		fprintf(stderr, "  Result: %02x\n", instant_validate_time(instant));
		fprintf(stderr, "Expected: %02x\n\n", expect);

		return 1;
	}

	return 0;
}

int main(int argc, char *argv[]) {
	uint16_t err = 0, idx = 0;

	instant_t i1 = { 0 };
	err += test_instant_validate(++idx, &i1, INSTANT_INVALID_YEAR | INSTANT_INVALID_MONTH | INSTANT_INVALID_DAY);

	instant_t i2 = { 0, 1, 1, 0, 0, 0 };
	err += test_instant_validate(++idx, &i2, INSTANT_INVALID_YEAR);

	/* Invalid months makes it impossible to validate day, so day is always invalid if month is */
	instant_t i3 = { 1, 0, 1, 0, 0, 0 };
	err += test_instant_validate(++idx, &i3, INSTANT_INVALID_MONTH | INSTANT_INVALID_DAY);

	instant_t i4 = { 1, 1, 0, 0, 0, 0 };
	err += test_instant_validate(++idx, &i4, INSTANT_INVALID_DAY);

	instant_t i5 = { 1, 1, 1, 24, 0, 0 };
	err += test_instant_validate(++idx, &i5, INSTANT_INVALID_HOUR);

	instant_t i6 = { 1, 1, 1, 23, 60, 0 };
	err += test_instant_validate(++idx, &i6, INSTANT_INVALID_MINUTE);

	instant_t i7 = { 1, 1, 1, 23, 0, 60 };
	err += test_instant_validate(++idx, &i7, INSTANT_INVALID_SECOND);

	instant_t i8 = { 2019, 11, 20, 12, 13, 14 };
	err += test_instant_validate(++idx, &i8, 0);

	instant_t i9 = { 2019, 11, 20, 12, 13, 14 };
	err += test_instant_validate_date(++idx, &i9, 0);

	instant_t i10 = { 0, 11, 20, 12, 13, 14 };
	err += test_instant_validate_date(++idx, &i10, INSTANT_INVALID_YEAR);

	/* Invalid months makes it impossible to validate day, so day is always invalid if month is */
	instant_t i11 = { 2019, 13, 20, 12, 13, 14 };
	err += test_instant_validate_date(++idx, &i11, INSTANT_INVALID_MONTH | INSTANT_INVALID_DAY);

	instant_t i12 = { 2019, 11, 32, 12, 13, 14 };
	err += test_instant_validate_date(++idx, &i12, INSTANT_INVALID_DAY);

	instant_t i13 = { 2019, 11, 20, 12, 13, 14 };
	err += test_instant_validate_time(++idx, &i13, 0);

	instant_t i14 = { 2019, 11, 20, 24, 13, 14 };
	err += test_instant_validate_time(++idx, &i14, INSTANT_INVALID_HOUR);

	instant_t i15 = { 2019, 11, 20, 12, 128, 14 };
	err += test_instant_validate_time(++idx, &i15, INSTANT_INVALID_MINUTE);

	instant_t i16 = { 2019, 11, 20, 12, 13, 255 };
	err += test_instant_validate_time(++idx, &i16, INSTANT_INVALID_SECOND);

	if (err) {
		fprintf(stderr, "instant_validate(): %i of %i tests failed\n", err, idx);
		return 1;
	}

	fprintf(stderr, "instant_validate(): %i tests passed\n", idx);

	return 0;
}
