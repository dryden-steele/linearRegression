typedef struct weather_data {
        int date;
            int value;
                char* name;
} weather_data;

weather_data* get_data_array(char* filename);
