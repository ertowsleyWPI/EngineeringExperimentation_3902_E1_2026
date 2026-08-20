from machine import ADC, Pin, PWM
import time

# Pin Setup
adc = ADC(Pin(26))
servo = PWM(Pin(15))
servo.freq(50)

# Circuit Constants
VCC = 3.3
R_DIVIDER = 10000.0

# Helper function to map angles to PWM duty cycle
def set_servo_angle(angle):
    # Standard 50Hz servo: 0 degrees is ~1000us, 180 is ~2000us
    # duty_u16 range is 0-65535. (1000us/20000us)*65535 = 3276, (2000/20000)*65535 = 6553
    min_duty = 3276
    max_duty = 6553
    duty = min_duty + int((angle / 180.0) * (max_duty - min_duty))
    servo.duty_u16(duty)

# Initialize servo to 0
set_servo_angle(0)
time.sleep(1)

while True:
    # Read the sensor
    adc_val = adc.read_u16()
    
    # Calculate Voltage
    v_out = (adc_val / 65535.0) * VCC
    
    # Calculate Resistance of your Foam
    r_fsr = R_DIVIDER * ((VCC / v_out) - 1.0)
    
    # Add this line right here!
    print("Resistance:", r_fsr)
    
    # Prevent divide-by-zero errors
    if v_out <= 0.01:
        v_out = 0.01
        
    # Calculate Resistance of your Foam
    r_fsr = R_DIVIDER * ((VCC / v_out) - 1.0)
    
    # Trigger Logic (600k compressed, 2M base)
    if r_fsr < 800000:       # Hard Pinch (drops below 800k ohms)
        set_servo_angle(90)
    elif r_fsr < 1500000:    # Light Pinch (drops below 1.5M ohms)
        set_servo_angle(45)
    else:                    # Let go (rests at 2M ohms)
        set_servo_angle(0)
        
    time.sleep(0.1)