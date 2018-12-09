struct weather_data {
    int date;
    int value;
    char* name;
};

struct weather_data* get_data_array(char* filename, int record_count);
