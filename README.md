# GarageSecritySystem
This project is a garage security system based on AVR microcontroller using:  
- Digital input/output  
- Keypad  
- LCD display  
- Timer  
- External interrupt  
  
  
It's designed to provide a secure access to your garage. The user is required to enter a correct password using the keypad, which is set to "1234" by default. If the correct password is entered, a motor will run for 4 seconds, which is adjusted using timer0, allowing the user to open/close the garage door.  
If the wrong password is entered three times in a row, an interrupt will occur at INT2 and a message "Blocked" will be displayed on the LCD screen. After that, the user will not be able to enter any passwords until the system is reset.  
  
  
This garage security system is designed to provide a simple and effective way to secure your garage against unauthorized access. The code is well-documented and easy to understand, making it a great starting point for anyone who wants to learn about AVR programming and security systems. Feel free to use, modify, and contribute to this project to make it even better.  
- Here is a video explaining the project in details:  
https://drive.google.com/file/d/1222VBWwMA9X94TvQcDfcOGw0jpPMyp41/view?usp=sharing    
  
- And here is a video of the simulation "Note that the simulation runs the interrupt on rising edge unlike hardware"
  
    
https://github.com/bahrawyyy/GarageSecritySystem/assets/71684437/161dc2e0-dbd4-4961-9f7b-51f1edb56332
