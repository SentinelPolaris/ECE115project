## Note for using fontconvert
- Use [this](https://www.pentacom.jp/pentacom/bitfontmaker2/) website to edit ttf 
- Doesn't like my Mac. Use Ubuntu:
- `sudo apt-get install libfreetype6-dev`
- `make`
- `./fontconvert Picopixel09edit.ttf 4 > 4.h`
- Size 4 makes every 4x4 pixel into one pixel. 4.h is the output header to be included in the Arduino code
