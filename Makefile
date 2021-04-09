TARGET+=convert_time_to_utc

all: ${TARGET}

convert_time_to_utc: time_local_to_UTC.c
	gcc time_local_to_UTC.c -lbaseutils -o convert_time_to_utc
