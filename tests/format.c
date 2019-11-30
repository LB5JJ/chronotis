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
#include <string.h>
#include "../instant.h"

uint8_t test(uint16_t idx, instant_t *instant, char *expect, const char *format) {
	char buffer[256];

	instant_format(instant, format, buffer);

	if (strcmp((char *)expect, buffer)) {
		fprintf(stderr, "--------[ instant_format(): %04i ]------------------------\n", idx);
		fprintf(stderr, "Expected: %s\n", expect);
		fprintf(stderr, "  Result: %s\n", buffer);
		fprintf(stderr, " Instant: %s\n", instant_str(instant));
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

	err += test(++idx, instant_of("2019-11-20 12:13:14"), "2019-11-20 12:13:14", instant_default_format);
	err += test(++idx, instant_of("2019-11-20 12:13:14"), "20191120T121314", iso_basic);
	err += test(++idx, instant_of("2019-11-20 12:13:14"), "2019-11-20T12:13:14", iso_extended);

	err += test(++idx, instant_of("2019-11-20 00:01:02"), "11/20/19 12:01:02 AM", us_uc);
	err += test(++idx, instant_of("2019-11-20 00:01:02"), "11/20/19 12:01:02 am", us_lc);
	err += test(++idx, instant_of("2019-11-20 00:01:02"), "20/11/19 00:01:02", eu);

	err += test(++idx, instant_of("2019-11-20 11:01:02"), "11/20/19 11:01:02 AM", us_uc);
	err += test(++idx, instant_of("2019-11-20 11:01:02"), "11/20/19 11:01:02 am", us_lc);
	err += test(++idx, instant_of("2019-11-20 11:01:02"), "20/11/19 11:01:02", eu);

	err += test(++idx, instant_of("2019-11-20 12:01:02"), "11/20/19 12:01:02 PM", us_uc);
	err += test(++idx, instant_of("2019-11-20 12:01:02"), "11/20/19 12:01:02 pm", us_lc);
	err += test(++idx, instant_of("2019-11-20 12:01:02"), "20/11/19 12:01:02", eu);

	err += test(++idx, instant_of("2019-11-20 13:01:02"), "11/20/19 01:01:02 PM", us_uc);
	err += test(++idx, instant_of("2019-11-20 13:01:02"), "11/20/19 01:01:02 pm", us_lc);
	err += test(++idx, instant_of("2019-11-20 13:01:02"), "20/11/19 13:01:02", eu);

	err += test(++idx, instant_of("2019-11-20 23:01:02"), "11/20/19 11:01:02 PM", us_uc);
	err += test(++idx, instant_of("2019-11-20 23:01:02"), "11/20/19 11:01:02 pm", us_lc);
	err += test(++idx, instant_of("2019-11-20 23:01:02"), "20/11/19 23:01:02", eu);

	err += test(++idx, instant_of("2019-11-20 01:02:03"), "2019-11-20 01:02:03", instant_default_format);
	err += test(++idx, instant_of("2019-11-20 01:02:03"), "20/11/19 01:02:03", eu);
	err += test(++idx, instant_of("2019-11-20 01:02:03"), "11/20/19 01:02:03 AM", us_uc);

	if (err) {
		fprintf(stderr, "instant_format(): %i of %i tests failed\n", err, idx);
		return 1;
	}

	fprintf(stderr, "instant_format(): %i tests passed\n", idx);

	return 0;
}