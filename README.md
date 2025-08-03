# Stop Watch Project

A digital stop watch implementation using ATmega32 microcontroller with multiplexed seven-segment display technology.

## 📋 Project Overview

This project implements a fully functional digital stop watch that displays time in HH:MM:SS format using six seven-segment displays. The stop watch uses multiplexing technique to efficiently control multiple displays with minimal I/O pins and provides user control through external interrupts.

## ✨ Features

- **Time Display**: Hours, Minutes, and Seconds in HH:MM:SS format
- **Multiplexed Display**: Efficient control of 6 seven-segment displays
- **Reset Function**: Reset stop watch to 00:00:00
- **Pause Function**: Pause the timer
- **Resume Function**: Resume the paused timer
- **Real-time Counting**: Accurate time keeping using Timer1 compare mode
- **Interrupt-driven Control**: External interrupts for user interaction

## 🔧 Hardware Requirements

- **Microcontroller**: ATmega32
- **Display**: 6x Seven-segment displays (Common Cathode)
- **Crystal**: 16MHz external crystal oscillator
- **Buttons**: 3x Push buttons for Reset, Pause, and Resume
- **Resistors**: Current limiting resistors for seven-segment displays
- **Power Supply**: 5V DC

## 📡 Pin Configuration

### Seven-Segment Display Control
- **PORTA (PA0-PA5)**: Enable pins for six seven-segment displays
- **PORTC (PC0-PC3)**: 4-bit BCD output to displays

### Control Buttons
- **PD2 (INT0)**: Reset button (Active Low - Falling Edge)
- **PD3 (INT1)**: Pause button (Active High - Rising Edge)  
- **PB2 (INT2)**: Resume button (Active Low - Falling Edge)

## ⚙️ How It Works

### Timer Configuration
- **Timer1**: Configured in compare mode with 1024 prescaler
- **Compare Value**: 1000 (generates interrupt every 1 second at 16MHz)
- **Interrupt**: Timer1 Compare A interrupt updates time variables

### Multiplexing
The system cycles through each seven-segment display every 2ms:
1. Enable display (PORTA)
2. Output digit value (PORTC)
3. Short delay for persistence of vision
4. Move to next display

### Time Management
- Seconds: 00-59 (displayed as tens and units)
- Minutes: 00-59 (displayed as tens and units)
- Hours: 00-99 (displayed as tens and units)

## 🚀 Building and Running

### Prerequisites
- AVR-GCC compiler
- AVR toolchain for ATmega32
- Proteus (for simulation)
- Hardware programmer (for physical implementation)

### Compilation
```bash
avr-gcc -mmcu=atmega32 -O2 -o stopwatch.elf main.c
avr-objcopy -O ihex stopwatch.elf stopwatch.hex
```

### Programming
```bash
avrdude -p atmega32 -c [programmer] -U flash:w:stopwatch.hex
```

## 🎮 Usage Instructions

1. **Power On**: The stop watch starts at 00:00:00
2. **Reset**: Press the Reset button (PD2) to reset timer to 00:00:00
3. **Pause**: Press the Pause button (PD3) to pause the timer
4. **Resume**: Press the Resume button (PB2) to resume counting

## 📁 Project Structure

```
Stop_Watch/
├── README.md                    # Project documentation
├── LICENSE                      # License file
└── mini_project_2/
    └── project2/
        ├── main.c               # Main source code
        ├── project2.pdsprj      # Proteus simulation file
        └── [Eclipse project files]
```

## 🔬 Simulation

The project includes a Proteus simulation file (`project2.pdsprj`) that allows you to:
- Test the stop watch functionality
- Verify timing accuracy
- Debug circuit connections
- Validate button operations

## 👨‍💻 Author

**Mahmoud Abdelrahman**

## 📄 License

This project is licensed under the terms included in the LICENSE file.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📝 Notes

- Ensure proper current limiting resistors for seven-segment displays
- Verify crystal oscillator connections for accurate timing
- Test all interrupt functions before final implementation
- The multiplexing frequency (500Hz) provides stable display without flicker
