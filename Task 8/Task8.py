import machine
import time
import ustruct

# Initialize I2C (I2C1 on GP4/GP5)
i2c = machine.I2C(0, scl=machine.Pin(5), sda=machine.Pin(4), freq=400000)
ADS_ADDR = 0x48

# ADS1115 Register Pointer Configuration
POINTER_CONVERSION = 0x00
POINTER_CONFIG = 0x01

# Config Details: Differential A0-A1, PGA = +/-2.048V, Continuous Mode, 128 SPS
# Binary: 0000 0100 1000 0100 -> 0x0484
CONFIG_DIFF_A0_A1_2_048V = 0x0484
LSB_SIZE = 2.048 / 32768  # 16-bit signed resolution step size

def init_ads1115():
    config_bytes = ustruct.pack('>H', CONFIG_DIFF_A0_A1_2_048V)
    i2c.writeto_mem(ADS_ADDR, POINTER_CONFIG, config_bytes)

def read_differential_voltage():
    # Read the two-byte conversion register
    data = i2c.readfrom_mem(ADS_ADDR, POINTER_CONVERSION, 2)
    raw_value = ustruct.unpack('>h', data)[0] # Unpack as signed 16-bit integer
    return raw_value * LSB_SIZE

# --- Calibration Constants ---
V_EXCITATION = 3.3
GAUGE_FACTOR = 2.09

init_ads1115()
time.sleep(0.1)

# Perform Software Taring (Zeroing the unloaded bridge)
print("Calibrating baseline... Keep potentiometer completely still.")
v_tare = sum(read_differential_voltage() for _ in range(50)) / 50
print(f"Tare Offset Established: {v_tare:+.6f} V\n")

print(f"{'Raw Delta V (mV)':<20}{'Calculated Microstrain (με)':<25}")
print("-" * 45)

try:
    while True:
        # Oversample raw signal
        v_diff = (sum(read_differential_voltage() for _ in range(20)) / 20) - v_tare
        
        # Quarter-Bridge Strain Equation: strain = (4 * V_out) / (GF * V_excitation)
        strain = (4.0 * v_diff) / (GAUGE_FACTOR * V_EXCITATION)
        microstrain = strain * 1e6 # Convert to standard microstrain units (με)
        
        # Formatted to keep columns perfectly aligned
        print(f"{v_diff * 1000:<+20.4f} {microstrain:<+25.2f}")
        time.sleep(0.2)
        
except KeyboardInterrupt:
    print("\nTest stopped by user.")