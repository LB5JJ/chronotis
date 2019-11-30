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

uint8_t test(uint16_t idx, instant_t *expect, char *input, const char *format) {
	instant_t instant;

	instant_parse(&instant, format, input);

	if (!instant_is_equal(&instant, expect)) {
		fprintf(stderr, "--------[ instant_parse(): %04i ]------------------------\n", idx);
		fprintf(stderr, "Expected: %s\n", instant_str(expect));
		fprintf(stderr, "  Result: %s\n", instant_str(&instant));
		fprintf(stderr, "   Input: %s\n", input);
		fprintf(stderr, "  Format: %s\n\n", format);

		return 1;		
	}

	return 0;
}

int main(int argc, char *argv[]) {
	uint16_t err = 0, idx = 0;

	char iso_basic[] = INSTANT_FORMAT_ISO_BASIC;
	char iso_extended[] = INSTANT_FORMAT_ISO_EXTENDED;

	char eu[] = INSTANT_FORMAT_EU;
	char us_uc[] = INSTANT_FORMAT_US_UC;
	char us_lc[] = INSTANT_FORMAT_US_LC;

	err += test(++idx, instant_of("0000-00-00 00:00:00"), "201a-11-20 10:11:12", instant_default_format);
	err += test(++idx, instant_of("0000-00-00 00:00:00"), "201-11-20 10:11:12", instant_default_format);
	err += test(++idx, instant_of("0000-00-00 00:00:00"), "2019-13-20 10:11:12", instant_default_format);

	err += test(++idx, instant_of("0000-00-00 00:00:00"), "2019-11-31 10:11:12", instant_default_format);
	err += test(++idx, instant_of("0000-00-00 00:00:00"), "2019-02-29 10:11:12", instant_default_format);

	err += test(++idx, instant_of("0000-00-00 00:00:00"), "2019-02-28 24:11:12", instant_default_format);

	err += test(++idx, instant_of("0000-00-00 00:00:00"), "2019-02-28 23:60:12", instant_default_format);

	err += test(++idx, instant_of("0000-00-00 00:00:00"), "2019-02-28 23:11:99", instant_default_format);

	err += test(++idx, instant_of("2019-11-20 10:11:12"), "2019-11-20 10:11:12", instant_default_format);
	err += test(++idx, instant_of("2019-11-20 10:11:12"), "20191120T101112", iso_basic);
	err += test(++idx, instant_of("2019-11-20 10:11:12"), "2019-11-20T10:11:12", iso_extended);

	err += test(++idx, instant_of("2019-11-20 10:11:12"), "2019-11-20 10:11:12", instant_default_format);
	err += test(++idx, instant_of("2019-11-20 10:11:12"), "11/20/19 10:11:12 AM", us_uc);
	err += test(++idx, instant_of("0000-00-00 00:00:00"), "11/20/19 10:11:12 Am", us_uc);

	err += test(++idx, instant_of("2019-11-20 22:11:12"), "20/11/19 22:11:12", eu);
	err += test(++idx, instant_of("2019-11-20 22:11:12"), "11/20/19 10:11:12 pm", us_lc);
	err += test(++idx, instant_of("0000-00-00 00:00:00"), "11/20/19 13:11:12 pm", us_lc);

	err += test(++idx, instant_of("2019-11-20 00:11:12"), "2019-11-20 00:11:12", instant_default_format);
	err += test(++idx, instant_of("2019-11-20 00:11:12"), "11/20/19 12:11:12 AM", us_uc);
	err += test(++idx, instant_of("0000-00-00 00:00:00"), "11/20/19 00:11:12 AM", us_uc);

	err += test(++idx, instant_of("2019-11-20 01:11:12"), "20/11/19 01:11:12", eu);
	err += test(++idx, instant_of("2019-11-20 01:11:12"), "11/20/19 01:11:12 am", us_lc);

	err += test(++idx, instant_of("2019-11-20 11:11:12"), "2019-11-20 11:11:12", instant_default_format);
	err += test(++idx, instant_of("2019-11-20 11:11:12"), "11/20/19 11:11:12 AM", us_uc);

	err += test(++idx, instant_of("2019-11-20 12:11:12"), "20/11/19 12:11:12", eu);
	err += test(++idx, instant_of("2019-11-20 12:11:12"), "11/20/19 12:11:12 pm", us_lc);

	err += test(++idx, instant_of("2019-11-20 13:11:12"), "2019-11-20 13:11:12", instant_default_format);
	err += test(++idx, instant_of("2019-11-20 13:11:12"), "11/20/19 01:11:12 PM", us_uc);

	err += test(++idx, instant_of("2019-11-20 14:11:12"), "20/11/19 14:11:12", eu);
	err += test(++idx, instant_of("2019-11-20 14:11:12"), "11/20/19 02:11:12 pm", us_lc);

	err += test(++idx, instant_of("2019-11-20 22:11:12"), "2019-11-20 22:11:12", instant_default_format);
	err += test(++idx, instant_of("2019-11-20 22:11:12"), "11/20/19 10:11:12 PM", us_uc);

	err += test(++idx, instant_of("2019-11-20 23:11:12"), "20/11/19 23:11:12", eu);
	err += test(++idx, instant_of("2019-11-20 23:11:12"), "11/20/19 11:11:12 pm", us_lc);

	err += test(++idx, instant_of("2019-11-20 00:11:12"), "2019-11-20 00:11:12", instant_default_format);
	err += test(++idx, instant_of("2019-11-20 00:11:12"), "11/20/19 12:11:12 AM", us_uc);

	err += test(++idx, instant_of("2019-11-20 00:00:00"), "20/11/19 00:00:00", eu);

	err += test(++idx, instant_of("2019-11-20 00:00:00"), "20/11/19 00:00:00", eu);
	err += test(++idx, instant_of("2019-11-20 00:00:00"), "11/20/19 12:00:00 am", us_lc);
	err += test(++idx, instant_of("2019-11-20 12:00:00"), "11/20/19 12:00:00 PM", us_uc);

	if (err) {
		fprintf(stderr, "instant_parse(): %i of %i tests failed\n", err, idx);
		return 1;
	}

	fprintf(stderr, "instant_parse(): %i tests passed\n", idx);

	return 0;
}