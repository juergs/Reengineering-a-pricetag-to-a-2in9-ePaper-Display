# Reengineering-a-pricetag-to-a-2in9-ePaper-Display
refurbrishing a pricetag into an 2.9 inch ePaper-display for ESP8266 Wemos D1 usage. 

<img src="https://github.com/juergs/Reengineering-a-pricetag-to-a-2in9-ePaper-Display/blob/main/pics/epaper_2.9-overview.png" width="800"/>

<img src="https://github.com/juergs/Reengineering-a-pricetag-to-a-2in9-ePaper-Display/blob/main/pics/b-w-r.png" width="800"/>

<img src="https://github.com/juergs/Reengineering-a-pricetag-to-a-2in9-ePaper-Display/blob/main/pics/EPD_Conn_ACT1441.png" width="600"/>

<img src="https://github.com/juergs/Reengineering-a-pricetag-to-a-2in9-ePaper-Display/blob/main/pics/overview_epd_interface_schematic.png" width="800"/>

Taking this blog article from Aaaron as initial trigger: [Arrons Blog]([https://pages.github.com/](http://atcnetz.blogspot.com/2019/02/ausgemusterete-elektronische-e-ink.html)
i started to find a reuse for some old cheap pricetags. Not knowing that this will be some kind of a tough purpouse ... 

First:  Not knowing which type of ePaper-display i was using. 
Second: Not knowing, that there are tons of different types there outside. All with different controller and setups.
Third:  When there is a demo-code given by the manufacturer, they are some kind of incomplete. Mainly lacking further informations, i.e why things are done in a certain way. 

So this Platformio-code is intended as basis to evaluate code to operate this specific display. 
The code is a mixup of different code-parts, in order to get some kind of more advanced capabilities, as usual demo-codes are providing. 

Thanks to Adafruit, Waveshare etc. for their Aduino-Libs, which libs are inspiring examples ...  

This initial version is intendend to serve for testting basich functions and is still not completed yet! 

