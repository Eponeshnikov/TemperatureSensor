#include <CTBot.h>
#include <BME280/BME280.h>
//#include <CONSTANTS.h>

extern char temperatureString[6];
extern char humidityString[6];
extern char pressureString[7];
extern char pressuremmString[7];





String token = "";   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
//String token = (String)TelegramConsts::token;

CTBot myBot;
TBMessage msg;
CTBotReplyKeyboard myKbd;   // reply keyboard object helper
int Bot_mtbs = 1000; // как часто забирать сообщения
long Bot_lasttime;

void botBrain() {
	if (myBot.getNewMessage(msg)) {
		// check what kind of message I received
		if (msg.messageType == CTBotMessageText) {
			// received a text message
			if (msg.text.equalsIgnoreCase("show keyboard")) {
				// the user is asking to show the reply keyboard --> show it
				myBot.sendMessage(msg.sender.id, "Reply Keyboard enable.", myKbd);
			} else if (msg.text.equalsIgnoreCase("Hide replyKeyboard")) {
        myBot.removeReplyKeyboard(msg.sender.id, "Reply keyboard removed");
      } else if (msg.text.equalsIgnoreCase("Temperature")) {
        getWeather();
        String temperature = temperatureString + (String)" °C";
        myBot.sendMessage(msg.sender.id, temperature);
      } else if (msg.text.equalsIgnoreCase("Humidity")) {
        getWeather();
        String humidity = humidityString + (String)" %";
        myBot.sendMessage(msg.sender.id, humidity);
      } else if (msg.text.equalsIgnoreCase("Pressure")) {
        getWeather();
        String pressure = pressuremmString + (String)" mmHg " + (String)"(" + pressureString + (String)" hPa" + (String)")";
        myBot.sendMessage(msg.sender.id, pressure);
      } else if (msg.text.equalsIgnoreCase("/start")) {
        String welcome = "Welcome " + msg.sender.username + (String)". My name is Ilya and I can give you information about weather. Tap on the required button on the keyboard.";
        myBot.sendMessage(msg.sender.id, welcome);
        myBot.sendMessage(msg.sender.id, "Reply Keyboard enable.", myKbd);
      } else if (msg.text.equalsIgnoreCase("/sendId")) {
        String userID = "Username: " + msg.sender.username + (String)"\nID: " + (String)msg.sender.id + (String)"\nFirst name: " + msg.sender.firstName + (String)"\nLast name: " + msg.sender.lastName;
        myBot.sendMessage(msg.sender.id, userID);
      } else {
        // the user write anything else and the reply keyboard is not active --> show a hint message
        myBot.sendMessage(msg.sender.id, "Try 'show keyboard'");
			}
    }
	}
}

void checkMessages() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    botBrain();
    Bot_lasttime = millis();
  }
}

void addKeyboard() {
  myKbd.addButton("Temperature");
  myKbd.addButton("Humidity");
  myKbd.addButton("Pressure");
	// add a new empty button row
	myKbd.addRow();
	// add a button that send a message with "Hide replyKeyboard" text
	// (it will be used to hide the reply keyboard)
	myKbd.addButton("Hide replyKeyboard");
	// resize the keyboard to fit only the needed space
	myKbd.enableResize();
}

void startBot() {
    Serial.print("Starting Telegram Bot ...");  
    // set the telegram bot token
    myBot.setTelegramToken(token);
    myBot.enableUTF8Encoding(true);
    addKeyboard();
    // check if all things are ok
    if (myBot.testConnection())
        Serial.println("\ntestConnection OK");
    else
        Serial.println("\ntestConnection NOK");
}
