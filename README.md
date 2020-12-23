<h1>char_LCD_rgb_LED<h2>A TeensyThread example on how to use mutexes and RAII to handle threading on the Teensy 4.1.</h2></h1>

<p><b>Requires a Teensy 4.1 and the Arduino serial monitor for this iteration.</b> Using TeensyThreads, the programmer is able to run up to 8 threads at a time. This sketch creates four threads that read or write to I/O while also modifying memory.

This program does two separate functions that require two threads each. 

The first function retrieves text from the native UART port and stuffs the first 32 bytes with a null-terminator into a buffer with one thread. Whenever it is done, it toggles a flag to signal that the buffer was filled. The second just watches the flag until it is flipped, then updates a 16x2 character LCD screen. This screen will jump to the second line if the line is more than 16 characters. To protect this flag, I using <i>std::lock_guard</i> and <i>std::mutex</i>.

The second function retrieves input from an analog joystick with X and Y movement. The first thread constantly reads from two PWM pins and updates the red, green, and blue values of the RGB LED. The second thread writes to the LED via PWM pins. I figured this memory doesn't need to be protected because the eye won't pick up on slight color changes unlike having text update on the character LCD.

One of the things I wanted to learn during this was how to use RAII techniques on the Arduino platform. I was able to achieve this with <i>std::lock_guard(std:mutex) locking_obj_name_here(lock_byte_name_here)</i>.

I also wanted to look at how to pass structure objects through threads. I just passed the bytes into the function ran by the child thread as raw bytes of memory, then told the compiler how to structure that memory when having instructions done on said memory.

<b>Next Updates:</b>
- Work in PuTTY
- Use up and down on joystick to determine how bright a color should be on the palette