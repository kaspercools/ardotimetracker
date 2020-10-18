#include "CheckpointInfoControl.h"
#include "Colors.h"
#include "Fonts.h"
#include "Util.h"

CheckpointInfoControl::CheckpointInfoControl() {
  isDirty = true;
}

CheckpointInfoControl::CheckpointInfoControl(int _originX, int _originY) {
  originX = _originX;
  originY = _originY;
  isDirty = true;
}

CheckpointInfoControl::CheckpointInfoControl(int _originX, int _originY, int _width, int _height) {
  isDirty = true;
  originX = _originX;
  originY = _originY;
  width = _width;
  height = _height;
  memset(msg.content, 0, sizeof(msg.content));
}

void CheckpointInfoControl::draw(Adafruit_TFTLCD tft) {
  if (isDirty) {
    tft.fillRect(originX, originY, width, height, Colors::White);
    tft.setTextColor(Colors::Black);
    tft.setTextSize(Fonts::fontSize);
    for (int i = timeStringsSentIndex - 1; i >= 0; i--) {
      tft.setCursor(originX + 5, originY + 15 + (22 * ((timeStringsSentIndex - 1) - i)));
      tft.setTextColor(((timeStringsSent[i].success) ? Colors::Green : Colors::Red));
      tft.print(timeStringsSent[i].time);
    }


    tft.fillRect(originX, originY + height / 2 - 15, originY + width, 3, Colors::DarkBlue);

    tft.setTextColor(Colors::Black);
    if (msg.origin != Enumerations::User) {
      Utils::StringMutators::printWithMargin(Translator::getComputingOfficeLabelText(), originX + 5, (originY + height / 2 - 15) + 10 + (22 * 0), Fonts::fontHeight * 2, 2, width, tft);
    } else {
      Utils::StringMutators::printWithMargin(Translator::getYourMessageLabelText(), originX + 5, (originY + height / 2 - 15) + 10 + (22 * 0), Fonts::fontHeight * 2, 2, width, tft);
    }

    if (String(msg.content).length() > 0) {
      if (msg.origin != Enumerations::User) {
        tft.setTextColor(Colors::Red);
        Utils::StringMutators::printWithMargin(msg.content, originX + 5, (originY + height / 2 - 15) + 20 + (22 * 1), Fonts::fontHeight * 2, 0, width - 5, tft);
      } else {
        tft.setTextColor(Colors::Green);
        Utils::StringMutators::printWithMargin(msg.content, originX + 5, (originY + height / 2 - 15) + 20 + (22 * 1), Fonts::fontHeight * 2, 0, width - 5, tft);
      }
    }
    isDirty = false;
  }
}

void CheckpointInfoControl::setMessage(struct Message _msg) {
  msg = _msg;
}

void CheckpointInfoControl::addTime(struct TimesSent timeSent) {
  if (timeStringsSentIndex > 4) {
    for (byte i = 0; i < 4; i++) {
      timeStringsSent[i] = timeStringsSent[i + 1];
    }

    timeStringsSentIndex--;
  }

  timeStringsSent[timeStringsSentIndex++] = timeSent;
}

void CheckpointInfoControl::setDirty() {
  isDirty = true;
}
