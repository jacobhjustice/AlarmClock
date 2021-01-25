# Alarm Clock

Like most people in this world, I use my phone *way* more than I probably should. This includes a routine hours worth of scrolling Reddit, Instagram, TikTok, or whatever else seems interesting at the time. Often, I have considered leaving my phone outside my room, lest the temptation to pick it up and scroll overcome me. But alas, I live in 2021, a time where our alarm clocks and phones are one in the same. When I realized such was true, I pondered, thinking of the easiest solution to my perdicament. 

Ultimately, I decided that it would be 100% totally lame to just go on Amazon and buy a $10 alarm clock. No, that's just what the media would *want* me to do. I knew in my heart there was only one solution: I was to forge an alarm clock for myself.

## User Manual

My desire in building this alarm clock was such that anyone should be able to copy my implementation and make their own, even if they have no knowledge on how to program. This user manual will outline every step from what you need to buy to how to set it up.

### Parts List
I provided links to the components that I purchased, but feel free to get whatever brand you prefer:
- ATmega328P Microcontroller 
  - Arduino is a great choice here, but I personally prefer the ELEGOO nano since it is much cheaper https://www.amazon.com/ELEGOO-Arduino-ATmega328P-Without-Compatible/dp/B0713XK923 
  - Depending on the microcontroller you get, you probably need to pick up a USB charging cable to boot the code onto the processor
- DS3231 RTC
  - https://www.amazon.com/dp/B00LX3V7F0/ref=cm_sw_em_r_mt_dp_y6LdGbTB0W8DX?_encoding=UTF8&psc=1 
- 1602A LCD Display
  - https://www.amazon.com/dp/B00HJ6AFW6/ref=cm_sw_em_r_mt_dp_YcMdGbYJB9938?_encoding=UTF8&psc=1
- Push Buttons (x3)
  - https://www.amazon.com/DAOKI-Miniature-Momentary-Tactile-Quality/dp/B01CGMP9GY/ref=sr_1_1?dchild=1&keywords=miniature+micro+momentary+tactile&qid=1611555256&sr=8-1
- Buzzer 
  - https://www.amazon.com/Electric-Buzzer-Physics-Circuits-Continuous/dp/B07JDBF4V3
- Wire
  - https://www.amazon.com/30GA-Hook-Wire-Kit-Electrical/dp/B07T1MR9C4/ref=sr_1_4?dchild=1&keywords=wire+30+gauge&qid=1611555324&sr=8-4
- DC12V Adapter + DC Connector Female Adapter
  - https://www.amazon.com/dp/B07C75RT38/ref=cm_sw_em_r_mt_dp_DnMdGbJT2XB57
  - I did not actually purchase this for this project, I had extras laying around as I bought in bulk for a previous one, thus I cannot vouch for quality of the product linked above

### Required Tools
- Solder Iron
- Computer w/ Arduino IDE
  - https://www.arduino.cc/en/software
- Optional: 3D Printer  
  - Technically you can create the alarm clock without an actual case to keep it in, but I'm not sure why you'd do that!
  - If woodworking is more your style, you can also craft a box to house your electronics that way too

### Process
Step 1) Download the source code
Step 2) Solder the components together
Step 3) Boot code onto microcontroller

## Developer Manual

In case you have a more technical background, I wanted to document my software design, just in case it is of use of anyone other than myself.



