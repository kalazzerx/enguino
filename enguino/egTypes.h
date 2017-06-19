// sketches don't like typdef's so they are in in this header file instead

#define N(x) sizeof(x)/sizeof(x[0])

typedef const char * string;

enum SensorType {st_ohms, st_thermistor, st_volts, st_thermocouple};
// st_ohms -        320 - 2400      32-240 ohms in tenths
// st_thermistor -  300 - 3000      30-300 degrees F. in tenths
// st_volts -        0  - 1023      ADC units 4.88 mV/per
// st_thermocouple - 0  - 4000      0-1000 degrees C. in quarters

// for K style in deg. C, use a multiply of   4096  (0.25),                       offset 0
// for K style in deg. F, use a multiplier of 7373  (0.25 * 1.8),                 offset -32
// for J style in deg. C, use a multiplier of 5751  (0.25 * 57.953/41.276),       offset 0
// for J style in deg. F, use a multiplier of 10352 (0.25 * 1.8 * 57.953/41.276), offset -32

typedef struct {
  SensorType type;    
  int voffset;    // used to display reading, int_reading has 'decimal' point shifted right
  int vfactor;    // int_reading = multiply * sensor >> divisor + offset
  int moffset;    // used to calculate marker position
  int mfactor;    // 0-4000 vertical gauge, 0-8000 horizontal gauge, 0-2400 round gauge
} Sensor;

enum GaugeStyle { gs_vert, gs_pair, gs_round, gs_horiz, gs_aux };

typedef struct {
  int x;
  int y;
  GaugeStyle style;
  
  int decimal;  // add decimal point 'decimal' positons from the right (0 is integer)
  
  string label1;
  string label2;
  string units;
  
  string *labelValues;
  const int *labelPts;    // prescaled from low,high and unscaled pts
  int n_labels;
  
  string *regionColors;
  const int *regionEndPts;  // prescaled from low,high and unscaled pts
  int n_regions;
  
  const Sensor *sensor;
  
  int pin;        // first pin if multiple sensors (cht/egt, fuel)
} Gauge;

enum GaugeColor { gc_green, gc_yellow, gc_red };

