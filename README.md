#  Chronotis date/time C library

## A point in time: `instant_t`

`instant_t` represents a point in time. Is specifies a point in time in the range from the beginning of January 1st year 1 up to the end of December 31st year 65535[^1] with one second resolution. `instant_t` is specified to represent the beginning of the encoded second (that is; second with a fractional part of 0). For applications requiring finer resolution, a separate value representing, milli-, micro- or nano-seconds can easily be maintained alongside the `instant_t`.

~~~c
typedef struct {
        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
} instant_t;
~~~

### Getting an instant

~~~c
instant_t instant = { 1969, 12, 27, 14, 30, 00 };
~~~

Create an `instant_t` variable and assign it the value of `1969-12-27 14:30:00`

~~~c
instant_t *instant_of(const char *string);
instant_t *instant_of_r(const char *string, instant_t *instant);
~~~

`instant_of()` / `instant_of_r()` parses `string` into an `instant_t` using the format: `YYYY-MM-DD HH:MM:SS`

Invalid input results in an (invalid) `instant_t` containing: `0000-00-00 00:00:00`

`instant_of()` returns the result in statically allocated memory which may be overwritten by subsequent calls. `instant_of_r()` stores the result in the user-supplied `instant_t`, returning a pointer to it.

See description of `instant_parse()` below for another, more flexible, way of parsing timestamps.

### Converting to string

~~~c
char *instant_str(const instant_t *instant);
char *instant_str_r(const instant_t *instant, char *buffer);
~~~

`instant_str()`/`instant_str_r()` formats the supplied `instant_t` into a string of the following format: `YYYY-MM-DD HH:MM:SS`

`instant_str()` returns the result in statically allocated memory which may be overwritten by subsequent calls. `instant_str_r()` stores the result in the user-supplied `buffer`, which should be at least `INSTANT_DEFAULT_LENGTH` + 1 (20) bytes, returning a pointer to it.

See description of `instant_format()` below for another, more flexible, way of formatting timestamps.

### Parsing and formatting

The `instant_parse()` and `instant_format()` functions described below used the following format specification, which is a modified subset of the format used by `strftime(3)`:

- `%Y` - 4 digit year, zero padded (0001-9999) [^1]
- `%y` - 2 digit year, zero padded, relative to year 2000 (00-99)
- `%m` - 2 digit month of year, zero padded (01-12)
- `%d` - 2 digit day of month, zero padded (01-31)
- `%H` - 2 digit hour of day (00-23)
- `%I` - 2 digit hour (01-12)
- `%M` - 2 digit minute of hour (00-59)
- `%S` - 2 digit second of minute (00-59)
- `%p` - a.m./p.m. indicator: `A` for a.m. or `P` for p.m. [^2]
- `%P` - a.m./p.m. indicator: `a` for a.m. or `p` for p.m. [^2]
- All other characters in the format specifier are copied to the output by `instant_format()` and required to be present in the input by `instant_parse()`

~~~c
void instant_parse(instant_t *instant, const char *format, const char *buffer);
~~~

Parse the instant described by `buffer` according to the format described by `format` and store the result in the `instant_t` pointed to by `instant`. `instant` will be cleared (set to the invalid instant of `0000-00-00 00:00:00`) before parsing. If the contents of `buffer` does not match the format described by `format` the invalid instant of  `0000-00-00 00:00:00` will be returned in `instant`.

~~~c
void instant_format(const instant_t *instant, const char *format, char *buffer);
~~~

Format the instant pointed to by `instant` according to the format described by `format`. `buffer` should point to a user-supplied buffer large enough to hold the resulting string including the trailing `\0`.

#### Predefined formats

The following formats are predefined in `instant.h`:

~~~c
#define INSTANT_DEFAULT_FORMAT "%Y-%m-%d %H:%M:%S"
#define INSTANT_DEFAULT_LENGTH 19
extern const char *instant_default_format;
~~~

`INSTANT_DEFAULT_FORMAT` is the default format used within the code, and by functions such as `instant_of()` and `instant_str()`. This format string is always available via the constant global variable `instant_default_format`. An instant formatted by `INSTANT_DEFAULT_FORMAT` will be `INSTANT_DEFAULT_LENGTH` bytes long, ***not*** counting the trailing `\0`.

~~~c
#define INSTANT_FORMAT_ISO_BASIC "%Y%m%dT%H%M%S"
#define INSTANT_LENGTH_ISO_BASIC 15

#define INSTANT_FORMAT_ISO_EXTENDED "%Y-%m-%dT%H:%M:%S"
#define INSTANT_LENGTH_ISO_EXTENDED 19
~~~

`INSTANT_FORMAT_ISO_BASIC` and `INSTANT_FORMAT_ISO_EXTENDED` formats an instant according to ISO 8601 basic or extended formats. The resulting strings will be `INSTANT_LENGTH_ISO_BASIC` / `INSTANT_LENGTH_ISO_EXTENDED` bytes long, ***not*** counting the trailing `\0`.

~~~c
#define INSTANT_FORMAT_EU "%d/%m/%y %H:%M:%S"
#define INSTANT_LENGTH_EU 17
~~~

`INSTANT_FORMAT_EU` formats an instant in the typical European format of `dd/mm/yy` with a 24-hour time. The resulting string will be `INSTANT_LENGTH_EU` bytes long, ***not*** counting the trailing `\0`.

~~~c
#define INSTANT_FORMAT_US_UC "%m/%d/%y %I:%M:%S %pM"
#define INSTANT_FORMAT_US_LC "%m/%d/%y %I:%M:%S %Pm"
#define INSTANT_LENGTH_US 17
~~~

`INSTANT_FORMAT_US_UC` / `INSTANT_FORMAT_US_LC` formats an instant to a form typically used in the USA of the form `mm/dd/yy` with a 12-hour time and an a.m./p.m. indication in either uppercase (`INSTANT_FORMAT_US_UC`) or lowercase (`INSTANT_FORMAT_US_LC`). The resulting string will be `INSTANT_LENGTH_US` bytes long, ***not*** counting the trailing `\0`.

### Clearing an `instant_t`

~~~c
void instant_clear(instant_t *instant);
~~~

The `instant_clear()` function clears the supplied instant by setting all fields to 0, thus creating an invalid `instant_t`.

### Validating an `instant_t`

~~~c
#define INSTANT_INVALID_YEAR   0x01
#define INSTANT_INVALID_MONTH  0x02
#define INSTANT_INVALID_DAY    0x04
#define INSTANT_INVALID_HOUR   0x10
#define INSTANT_INVALID_MINUTE 0x20
#define INSTANT_INVALID_SECOND 0x40

uint8_t instant_validate(const instant_t *instant);
#define instant_validate_date(instant) (instant_validate(instant) & 0x0f)
#define instant_validate_time(instant) (instant_validate(instant) & 0xf0)
~~~

The `instant_validate()` function validates an `instant_t`, returning `0` if `instant` is valid or a sum of `INSTALT_INVALID_*` values representing the fields that are invalid. [^3]

The `instant_validate_date()` macro validates just the date part of `instant`, returning `0` if `instant` represents a valid date or a sum of `INSTALT_INVALID_*` values representing the date fields that are invalid. [^3]

The `instant_validate_time()` macro validates just the time part of `instant`, returning `0` if `instant` represents a valid time or a sum of `INSTALT_INVALID_*` values representing the time fields that are invalid.

### Number of days in a month

~~~c
uint8_t instant_days_of_month(const instant_t *instant);
~~~

The `instant_days_of_month()`functions returns the number of days in the month represented by the supplied `instant_t`. [^4]

### Checking for leap year

~~~c
uint8_t instant_is_leap_year(const instant_t *instant);
~~~

The `instant_is_leap_year()` function returns true (1) if the year represented by the supplied `instant_t`is a leap year, false (0) otherwise! [^4]

### Checking a.m. / p.m.

~~~c
#define instant_is_am(i) ((i)->hour < 12)
#define instant_is_pm(i) ((i)->hour > 11)
~~~

The `instant_is_am()` macro returns true if the supplied `instant_t` has a time in the a.m., false otherwise. The `instant_is_pm()` macro returns true if the supplied `instant_t` has a time in the p.m., false otherwise.

### Day of week

~~~c
#define INSTANT_DAY_OF_WEEK_MONDAY 1
#define INSTANT_DAY_OF_WEEK_TUESDAY 2
#define INSTANT_DAY_OF_WEEK_WEDNESDAY 3
#define INSTANT_DAY_OF_WEEK_THURSDAY 4
#define INSTANT_DAY_OF_WEEK_FRIDAY 5
#define INSTANT_DAY_OF_WEEK_SATURDAY 6
#define INSTANT_DAY_OF_WEEK_SUNDAY 7

uint8_t instant_day_of_week(const instant_t *instant);
~~~

The `instant_day_of_week()` function returns the ISO 8601 weekday number for the day represented by the supplied `instant_t`. [^4]

### Comparing two instances of `instant_t`

~~~c
int16_t instant_compare(const instant_t *instant1, const instant_t *instant2);
#define instant_is_before(instant1, instant2) (instant_compare(instant1, instant2) < 0)
#define instant_is_equal(instant1, instant2) (instant_compare(instant1, instant2) == 0)
#define instant_is_after(instant1, instant2) (instant_compare(instant1, instant2) > 0)
~~~

The `instant_compare()`function compares `instant1`to `instant2` and returns a value larger then 0 if `instance1`is greater (represents a later time) then `instant2`, returns a value less then 0 if `instant1` is less (represents an earlier time) then `instant2` and a value of 0 if `instant1` and `instant2` are equal.

The macro `instant_is_before()` returns true only if `instant1` is before (smaller then) `instant2`.

The macro `instant_is_after()` returns true only if `instant1` is after (larger then) `instant2`.

The macro `instant_is_equal()` returns true only if `instant1` is equal to `instant2`.

## Copyright and license

Copyright 2019 Bård Bjerke Johannessen [<bbj@bbj.io>](mailto:bbj@bbj.io)

This file is part of the Chronotis date/time C library.

The Chronotis date/time C library is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

The Chronotis date/time C library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with the Chronotis date/time C library. If not, see [<https://www.gnu.org/licenses/>](https://www.gnu.org/licenses/).


## Notes

[^1]: Even though `instant_t` can hold years up to 65535, the parsing and formatting code is limited to years up to and including 9999!

[^2]: When parsing using the `%I` format specifier to indicate a 12-hour time, the format specification ***must*** include an a.m./p.m. specifier (`%p`/`%P`) at some point in the format specification ***after*** the `%I`!

[^3]: When validating an instant with an invalid month, it is impossible to validate the day of month. As a result, validating such an instant will always return both `INSTANT_INVALID_MONTH` and `INSTANT_INVALID_DAY`!

[^4]: `instant_days_of_month()`, `instant_is_leap_year()` and `instant_day_of_week()` are only correct for dates on or after the (possibly local) Gregorian Epoch (`1582-10-15`, or later depending on when and how the Gregorian calendar was introduced in your location).
