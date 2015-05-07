# musicBox
my learn project for arduino - a simple lcd controlled "musicbox" 

#goals
Learn arduino and a little bit of electronics.
The project, in the future, would be a detection system who can play music remotely when a move is detected.

#equipement

For the moment :

	- an arduino UNO rev2

	- a linksprite 16x2 lcd [LinkSprite](http://linksprite.com/wiki/index.php5?title=16_X_2_LCD_Keypad_Shield_for_Arduino).

	- a 8ohm speaker directly attached to the arduino, would use a amp in the future

Next :
	- an arduino pro

	- a pir sensor

	- wifi module (esp8266) or rf transmitter/receiver

	- bluetooth module

#Futur?

Yes, for the moment i'm in discovery phase. learning. My skill in c/c++ are, hem, rusty... (last time i coded in c++ it was c++98 standard...).

But, the final application would be :

	- a detector module, battery powered

	- a musicbox module, battery powered or not

Those two module would communicate via wifi OR rf (not sur for the moment, perhaps the both if possible). Detector module would be manageable via a bluetooth communication (and an android apps i have to do). Musicbox module would be manageable directly via lcd panel ou via bluetooth communication.

It's a long term development. Don't expect high update frequency.

But if you find all of this a little bit interessing, please take the code you want or need.

#nota bene
About the code : it lack comments (and some of them are in french). I will fix that shortly.
The environmet I use : i doesn't use the standard arduino IDE but a codeblocks version adapted to arduino dev :

	- the homepage : [CodeblocksArduino](http://arduinodev.com/codeblocks/)

	- the download : [Sourceforge](http://sourceforge.net/projects/arduinodev/files/)

CodeblocksArduino hasn't been updated since a while, for recent arduino boards it could be a problem. Since Codeblocks arduino is based on old arduini IDE, i'm trying alternatives :

	- visualmicro : extension for visual studio

	- Eclipse arduino : for eclipse.

I'll report my futur own opinion on those later.
