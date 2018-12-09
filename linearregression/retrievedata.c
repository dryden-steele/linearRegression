#include "retrievedata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csv.h"

struct csvdata {
    long unsigned column;
    long unsigned row;
    struct weather_data* data_points;
};

void cb1(void* s, size_t len, void* data) {
    struct csvdata* local = (struct csvdata*)data;

    if (local->column == 1) {
        local->data_points[local->row].date = atoi((char*)s);
    } else if (local->column == 2) {
        local->data_points[local->row].name = strdup((char*)s);
    } else if (local->column == 3) {
        local->data_points[local->row].value = atoi((char*)s);
        // printf("date: %d name: %s value: %d\n",
        // local->data_points[local->row].date,
        // local->data_points[local->row].name,
        // local->data_points[local->row].value);
    }

    local->column++;
}

void cb2(int c, void* data) {
    struct csvdata* local = (struct csvdata*)data;

    local->column = 0;
    local->row++;
}

struct weather_data* get_data_array(char* filename, int record_count) {
    FILE* fp;
    struct csv_parser p;
    char buff[1024];
    size_t bytes_read;
    struct csvdata d = {0, 0,
                        malloc(sizeof(struct weather_data) * record_count)};

    if (csv_init(&p, CSV_APPEND_NULL) != 0) {
        fprintf(stderr, "Failed to init csv parser\n");
        exit(EXIT_FAILURE);
    }

    fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Failed to open %s\n", filename);
        exit(EXIT_FAILURE);
    }

    while ((bytes_read = fread(buff, 1, 1024, fp)) > 0) {
        if (csv_parse(&p, buff, bytes_read, cb1, cb2, &d) != bytes_read) {
            fprintf(stderr, "Error while parsing file: %s\n",
                    csv_strerror(csv_error(&p)));
        }
    }

    csv_fini(&p, cb1, cb2, &d);

    if (ferror(fp)) {
        fprintf(stderr, "Error while reading file %s\n", filename);
    }

    fclose(fp);

    csv_free(&p);

    return d.data_points;
}
