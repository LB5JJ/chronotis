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

#include "instant.h"

const char *instant_default_format = INSTANT_DEFAULT_FORMAT;

static const uint8_t month_info[] = {
	0,				/* Faster and smaller then subtracting 1 when indexing */
	31 + (0 << 5),	/* January:   31 regular days, day-of-week offset is 0 */
	28 + (3 << 5),	/* February:  28 regular days, day-of-week offset is 3 */
	31 + (2 << 5),	/* March:     31 regular days, day-of-week offset is 2 */
	30 + (5 << 5),	/* April:     30 regular days, day-of-week offset is 5 */
	31 + (0 << 5),	/* May:       31 regular days, day-of-week offset is 0 */
	30 + (3 << 5),	/* June:      30 regular days, day-of-week offset is 3 */
	31 + (5 << 5),	/* July:      31 regular days, day-of-week offset is 5 */
	31 + (1 << 5),	/* August:    31 regular days, day-of-week offset is 1 */
	30 + (4 << 5),	/* September: 30 regular days, day-of-week offset is 4 */
	31 + (6 << 5),	/* October:   31 regular days, day-of-week offset is 6 */
	30 + (2 << 5),	/* November:  30 regular days, day-of-week offset is 2 */
	31 + (4 << 5)	/* December:  30 regular days, day-of-week offset is 4 */
};

instant_t *instant_of(const char *string) {
	static instant_t instant;
	return instant_of_r(string, &instant);
}

instant_t *instant_of_r(const char *string, instant_t *instant) {
	instant_parse(instant, instant_default_format, string);
	return instant;
}

char *instant_str(const instant_t *instant) {
	static char buffer[INSTANT_DEFAULT_LENGTH + 1];
	return instant_str_r(instant, buffer);
}

char *instant_str_r(const instant_t *instant, char *buffer) {
	instant_format(instant, instant_default_format, buffer);
	return buffer;
}

void instant_clear(instant_t *instant) {
	instant->year = instant->month = instant->day = instant->hour = instant->minute = instant->second = 0;
}

uint8_t instant_validate(const instant_t *instant) {
	uint8_t result = 0;

	if (!instant->year)
		result += INSTANT_INVALID_YEAR;

	if (instant->month < 1 || instant->month > 12)
		result += INSTANT_INVALID_MONTH;

	if (instant->day < 1 || instant->day > instant_days_of_month(instant))
		result += INSTANT_INVALID_DAY;

	if (instant->hour > 23)
		result += INSTANT_INVALID_HOUR;

	if (instant->minute > 59)
		result += INSTANT_INVALID_MINUTE;

	if (instant->second > 59)
		result += INSTANT_INVALID_SECOND;

	return result;
}

static uint8_t parse(const char *buffer, uint8_t *value, uint8_t min, uint8_t max) {
	if ((buffer[0] <= '9' && buffer[0] >= '0') && (buffer[1] <= '9' && buffer[1] >= '0')) {
		uint16_t parsed =  (buffer[0] - '0') * 10 + (buffer[1] - '0');
		if (parsed >= min && parsed <= max) {
			*value = parsed;
			return 1;
		}
	}

	return 0;
}

void instant_parse(instant_t *instant, const char *format, const char *string) {
	instant_clear(instant);
	uint8_t c = 20, d;

	while (*format) {
		if (*format != '%') {
			if (!((*string++) == *format)) goto invalid;
		} else {
			switch (*++format) {
				case 'Y': /* 4 digit year, zero padded */
					if (!parse(string, &c, 0, 99)) goto invalid;
					string += 2;
					/* fall through */
				case 'y': /* 2 digit year, zero padded */
					if (!parse(string, &d, 0, 99)) goto invalid;
					instant->year = c * 100 + d;
					break;
				case 'm': /* 2 digit month, zero padded */
					if (!parse(string, &(instant->month), 1, 12)) goto invalid;
					break;
				case 'd': /* 2 digit day of month, zero padded */
					if (!parse(string, &(instant->day), 1, 31)) goto invalid;
					break;
				case 'H': /* 2 digit hour (00-23) */
					if (!parse(string, &(instant->hour), 0, 23)) goto invalid;
					break;
				case 'I': /* 2 digit hour (01-12) */
					if (!parse(string, &(instant->hour), 1, 12)) goto invalid;
					break;
				case 'M': /* 2 digit minute (00-59) */
					if (!parse(string, &(instant->minute), 0, 59)) goto invalid;
					break;
				case 'S': /* 2 digit second (00-59) */
					if (!parse(string, &(instant->second), 0, 59)) goto invalid;
					break;
				case 'p': /* A/P */
				case 'P': /* a/p */
					if (('a' == *string && 'P' == *format) || ('A' == *string && 'p' == *format)) {
						if (12 == instant->hour)
							instant->hour = 0;
					} else if (('p' == *string && 'P' == *format) || ('P' == *string && 'p' == *format)) {
						if (instant->hour < 12)
							instant->hour += 12;
					} else {
						goto invalid;
					}
					string--;
			}
			string += 2;
		}
		format++;
	}

	if (!instant_validate(instant))
		return;

invalid:
	instant_clear(instant);
}

static void pack(char *buf, const uint8_t val) {
	buf[0] = '0' + val / 10 % 10;
	buf[1] = '0' + val % 10;
}

void instant_format(const instant_t *instant, const char *format, char *buffer) {
	while (*format) {
		if (*format == '%') {
			switch (*++format) {
				case 'Y': /* 4 digit year, zero padded */
					pack(buffer, instant->year / 100);
					buffer += 2;
					/* fall through */
				case 'y': /* 2 digit year, zero padded */
					pack(buffer, instant->year % 100);
					break;
				case 'm': /* 2 digit month, zero padded */
					pack(buffer, instant->month);
					break;
				case 'd': /* 2 digit day of month, zero padded */
					pack(buffer, instant->day);
					break;
				case 'H': /* 2 digit hour (00-23) */
					pack(buffer, instant->hour);
					break;
				case 'I': /* 2 digit hour (01-12) */
					pack(buffer, (instant->hour % 12) ? instant->hour % 12 : 12);
					break;
				case 'M': /* 2 digit minute (00-59) */
					pack(buffer, instant->minute);
					break;
				case 'S': /* 2 digit second (00-59) */
					pack(buffer, instant->second);
					break;
				case 'p': /* A/P */
					*buffer-- = (instant_is_am(instant) ? 'A' : 'P');
					break;
				case 'P': /* a/p */
					*buffer-- = (instant_is_am(instant) ? 'a' : 'p');
					break;
			}
			buffer += 2;
		} else {
			*buffer++ = *format;
		}
		format++;
	}
	*buffer = 0;
}

int16_t instant_compare(const instant_t *instant1, const instant_t *instant2) {
	/* Using the subtraction tricks on 16 bit unsigned values could
	 * result is a value too small (or large) for a signed 16 bit return
	 * type. So we chech years for both smaller and greater! */
	if (instant1->year > instant2->year)
		return 1;
	
	if (instant1->year < instant2->year)
		return -1;
	
	if (instant1->month - instant2->month)
		return instant1->month - instant2->month;

	if (instant1->day - instant2->day)
		return instant1->day - instant2->day;

	if (instant1->hour - instant2->hour)
		return instant1->hour - instant2->hour;

	if (instant1->minute - instant2->minute)
		return instant1->minute - instant2->minute;

	if (instant1->second - instant2->second)
		return instant1->second - instant2->second;

	return 0;
}

uint8_t instant_day_of_week(const instant_t *instant) {
	if (instant->month < 1 || instant->month > 12) return 0;
    uint16_t year = instant->year - (instant->month < 3);
    return (((year + year/4 - year/100 + year/400 + (month_info[instant->month] >> 5) + instant->day) - 1) % 7) + 1;
}

uint8_t instant_is_leap_year(const instant_t *instant) {
	return (!(instant->year & 3) && instant->year % 100) || !(instant->year % 400);
}

uint8_t instant_days_of_month(const instant_t *instant) {
	if (instant->month < 1 || instant->month > 12) return 0;
	return ((month_info[instant->month] & 0x1f) + (instant->month == 2 && instant_is_leap_year(instant)));
}

