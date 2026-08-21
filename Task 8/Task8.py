import machine
import time

#Initialize ADC pins (16-bit resolution: 0 to 65535)
adc_A = machine.ADC(26) # Node A (GP26)
adc_B = machine.ADC(27) # Node B (GP27)

VOLTAGE_FACTOR = 3.3 / 65535

print("Wheatstone Bridge Live Test")
print("Press Ctrl+C + to stop. \n")
print(f"{'V_A (V)':<10}{'V_B (V)':<10}{'V_out (Diff)':<15}")

while True:
    # Take multiple samples to reduce analog noise
    
    raw_A = sum(adc_A.read_u16() for _ in range(20)) / 20
    raw_B = sum(adc_B.read_u16() for _ in range(20)) / 20
    
    # Convert raw data to actual Voltage
    v_A = raw_A * VOLTAGE_FACTOR
    v_B = raw_B * VOLTAGE_FACTOR
    
    # Calculate differential output
    v_out = v_A - v_B
    
    # Print formatted metrics
    print(f"{v_A:.4f} {v_B:.4f} {v_out:.4f} V")
    
    time.sleep(0.5)