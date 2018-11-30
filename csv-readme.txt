Our weather data was taken from NOAA.gov, where we received data from the Global Historical Climatology Network (GHCN). This includes daily weather recordings of minimum temperature (celcius in tenths of degrees), maximum temperature (celcius in tenths of degrees), precipitation (mm), snowfall (mm), snow depth (mm), and other types of data.  This data was arranged in .csv files, with the year of the data listed as the name of the file (Ex. 2018.csv).

We found data that was recorded by a station in Normal, Illinois, so we took all the data from that station and added it to separate .csv files.  

The data is split into cells that we have to parse through.  Each line is separated into 8 cells.

Cell 1 - Station ID (USC00116200 - station ID in Normal, IL)

Cell 2 - Date of record (year/month/day) (format: xxxx-xx-xx)

Cell 3 - Weather element that is recorded

The five main elements are:

PRCP = Precipitation (tenths of mm)
SNOW = Snowfall (mm)
SNWD = Snow depth (mm)
TMAX = Maximum temperature (tenths of degrees C)
TMIN = Minimum temperature (tenths of degrees C)

There are other weather elements listed, but they're inconsistent with day to day recording so we won't use them.

Cell 4 - Value associated with weather element

Cell 5 - the measurement flag for the first day of the month (blank = no measurement information applicable)

Cell 6 - the quality flag for the first day of the month (blank = did not fail any quality check)

Cell 7 - the source flag for the first day of the month (blank = No source)

Cell 8 - Unclear what this is.  Possibly the time the data was recorded.
 

