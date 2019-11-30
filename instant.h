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

#ifndef INSTANT_H
#define INSTANT_H

#include <inttypes.h>

typedef struct {
        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
} instant_t;

#define INSTANT_DEFAULT_FORMAT "%Y-%m-%d %H:%M:%S"
#define INSTANT_DEFAULT_LENGTH 19
extern const char *instant_default_format;

#define INSTANT_FORMAT_ISO_BASIC "%Y%m%dT%H%M%S"
#define INSTANT_LENGTH_ISO_BASIC 15

#define INSTANT_FORMAT_ISO_EXTENDED "%Y-%m-%dT%H:%M:%S"
#define INSTANT_LENGTH_ISO_EXTENDED 19

#define INSTANT_FORMAT_EU "%d/%m/%y %H:%M:%S"
#define INSTANT_LENGTH_EU 17

#define INSTANT_FORMAT_US_UC "%m/%d/%y %I:%M:%S %pM"
#define INSTANT_FORMAT_US_LC "%m/%d/%y %I:%M:%S %Pm"
#define INSTANT_LENGTH_US 17

void instant_clear(instant_t *instant);

instant_t *instant_of(const char *string); /* Not thread safe */
instant_t *instant_of_r(const char *string, instant_t *instant);

void instant_parse(instant_t *instant, const char *format, const char *buffer);

char *instant_str(const instant_t *instant); /* Not thread safe */
char *instant_str_r(const instant_t *instant, char *buffer);

void instant_format(const instant_t *instant, const char *format, char *buffer);

#define INSTANT_INVALID_YEAR   0x01
#define INSTANT_INVALID_MONTH  0x02
#define INSTANT_INVALID_DAY    0x04
#define INSTANT_INVALID_HOUR   0x10
#define INSTANT_INVALID_MINUTE 0x20
#define INSTANT_INVALID_SECOND 0x40

uint8_t instant_validate(const instant_t *instant);
#define instant_validate_date(instant) (instant_validate(instant) & 0x0f)
#define instant_validate_time(instant) (instant_validate(instant) & 0xf0)

uint8_t instant_days_of_month(const instant_t *instant);

uint8_t instant_is_leap_year(const instant_t *instant);
#define instant_is_am(i) ((i)->hour < 12)
#define instant_is_pm(i) ((i)->hour > 11)

#define INSTANT_DAY_OF_WEEK_MONDAY 1
#define INSTANT_DAY_OF_WEEK_TUESDAY 2
#define INSTANT_DAY_OF_WEEK_WEDNESDAY 3
#define INSTANT_DAY_OF_WEEK_THURSDAY 4
#define INSTANT_DAY_OF_WEEK_FRIDAY 5
#define INSTANT_DAY_OF_WEEK_SATURDAY 6
#define INSTANT_DAY_OF_WEEK_SUNDAY 7

uint8_t instant_day_of_week(const instant_t *instant);

int16_t instant_compare(const instant_t *instant1, const instant_t *instant2);
#define instant_is_before(instant1, instant2) (instant_compare(instant1, instant2) < 0)
#define instant_is_equal(instant1, instant2) (instant_compare(instant1, instant2) == 0)
#define instant_is_after(instant1, instant2) (instant_compare(instant1, instant2) > 0)

#endif /* INSTANT_H */
