# targa-font-to-binary
converts a targa containing a font into a 64 bit binary numbers which encodes the chatacter

each character is in an 8x8 pixel cell in the order of ascii characters

![Alt Text](https://raw.githubusercontent.com/nulface/targa-font-to-binary/main/png%20font.png)


#### Example
Take one of the numbers from the output file and convert it into binary

![Alt Text](https://raw.githubusercontent.com/nulface/targa-font-to-binary/main/number.PNG)

a new line after every 8 bits will result in the desired image
in this case it was the letter H

![Alt Text](https://raw.githubusercontent.com/nulface/targa-font-to-binary/main/letter%20h.png)

```
_#__#___
_#__#___
_#__#___
_####___
_#__#___
_#__#___
_#__#___  
```



references:

https://www.cplusplus.com/doc/tutorial/files/

Thanks!

