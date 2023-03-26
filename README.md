# Reengineering-a-pricetag-to-a-2in9-ePaper-Display (using PlatformIo/Arduino/ESP8266)
refurbrishing a pricetag into an 2.9 inch ePaper-display for ESP8266 Wemos D1 usage. 

<img src="https://github.com/juergs/Reengineering-a-pricetag-to-a-2in9-ePaper-Display/blob/main/pics/epaper_2.9-overview.png" width="800"/>

<img src="https://github.com/juergs/Reengineering-a-pricetag-to-a-2in9-ePaper-Display/blob/main/pics/b-w-r.png" width="800"/>

<img src="https://github.com/juergs/Reengineering-a-pricetag-to-a-2in9-ePaper-Display/blob/main/pics/EPD_Conn_ACT1441.png" width="300"/>

<img src="https://github.com/juergs/Reengineering-a-pricetag-to-a-2in9-ePaper-Display/blob/main/pics/overview_epd_interface_schematic.png" width="800"/>

Taking this blog article from Aaaron as initial trigger: [Aarons Blog](http://atcnetz.blogspot.com/2019/02/ausgemusterete-elektronische-e-ink.html)
i started to find a reuse for some old cheap pricetags. Not knowing that this will be some kind of a tough purpouse ... 

First:  Not knowing which type of ePaper-display i was using. 
Second: Not knowing, that there are tons of different types there outside. All with different controller-types, manuals and setups.
Third:  When there is a demo-code given by the manufacturer, they are some kind of incomplete. Mainly lacking further informations, i.e why things are done in a certain way. 

So this Platformio-code is intended as basis to evaluate code to operate this specific display. 
The code is a mixup of different code-parts, in order to get some kind of more advanced capabilities, as usual demo-codes are providing. 

Thanks to Adafruit, Waveshare etc. for their Aduino-Libs, which are inspiring examples ...  ( ... but partially not able to run correctly)

Basic ePaper-operation is explained [here](https://www.zephray.me/post/stm32_epd_calendar/).

This initial version is intendend to serve for testting basich functions and is still not completed yet! 

DIY-Hardware: i desoldered all parts from the pricetag-pcb and used them on the interface-pcb (Gerber-files added to project). 

Using a tool like the [MHP30](https://de.aliexpress.com/item/1005001800667409.html?gatewayAdapt=glo2deu)

