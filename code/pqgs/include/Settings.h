// Serial comms
#define BAUD_RATE                               115200
#define FLIGHT_PATH_MAX_SIZE                    5120

// Mount control
#define MOUNT_EL_ANGLE_MIN                      (35.0)
#define MOUNT_EL_ANGLE_MAX                      140.0
#define MOUNT_AZEL_RATIO                        -1.15
#define MOUNT_EL_START_NEAR_CUTOUT              true
#define MOUNT_EL_NUM_STEPS                      (200.0 * (92.0/20.0) * (140.0/80.0))
#define MOUNT_AZ_NUM_STEPS                      (200.0 * (60.0/15.0))

// Ground station control
#define GS_ESTIMATED_BEAMWIDTH                  60.0
#define GS_NUM_BEAMWIDTH_SCAN_SEGMENTS          4
#define GS_NUM_AZIMUTH_SCAN_SAMPLES             20
#define GS_SCAN_TIMEOUT                         120
#define GS_KNOWN_LOCATION_TRUST_TIMEOUT         60
#define GS_UPDATE_INTERVAL                      100
#define GS_MNORTH_DELTA_AZ                      -74.0
#define GS_MAP_PROJECTION_ORIGIN_LAT            -34.0
#define GS_MAP_PROJECTION_ORIGIN_LONG           19.0

// Pins
#define PIN_AZ_ZERO_SENSOR              36
#define PIN_AZ_IO1                      14
#define PIN_AZ_IO2                      26
#define PIN_AZ_I11                      12
#define PIN_AZ_I12                      25
#define PIN_AZ_PH1                      32
#define PIN_AZ_PH2                      33
#define PIN_EL_IO1                      0
#define PIN_EL_IO2                      2
#define PIN_EL_I11                      16
#define PIN_EL_I12                      4
#define PIN_EL_PH1                      21
#define PIN_EL_PH2                      5
#define PIN_RADIO_NSS                   27
#define PIN_RADIO_DIO0                  15
#define PIN_RADIO_RESET                 13
#define PIN_IMU_NSS                     22
#define PIN_GPS_RX                      39
#define PIN_GPS_TX                      16