from machine import ADC, Pin, PWM
import time

# Pin Setup
pot = ADC(Pin(26))
servo = PWM(Pin(15))
servo.freq(50)

# Helper function to map angles to PWM duty cycle
def set_servo_angle(angle):
    min_duty = 3276
    max_duty = 6553
    duty = min_duty + int((angle / 180.0) * (max_duty - min_duty))
    servo.duty_u16(duty)

# Initialize servo to 0
set_servo_angle(0)
time.sleep(1)

while True:
    # Read the raw potentiometer value (0 to 65535)
    adc_val = pot.read_u16()
    print("Raw ADC:", adc_val)
    
    # Trigger Logic based on knob position
    if adc_val > 45000:       # Knob turned high
        set_servo_angle(90)
    elif adc_val > 20000:     # Knob turned halfway
        set_servo_angle(45)
    else:                     # Knob turned low
        set_servo_angle(0)
        
    time.sleep(0.1)