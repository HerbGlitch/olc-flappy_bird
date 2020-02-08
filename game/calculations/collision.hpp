#pragma once

class collision {
public:
    collision(){}
    bool mouseRectClicked(int mouseX, int mouseY, int rectX, int rectY, int rectWidth, int rectHeight){
      return mouseX >= rectX && mouseX <= rectX + rectWidth && mouseY >= rectY && mouseY <= rectY + rectHeight;
    }

    bool circleRectCollision(int circleX, int circleY, int circleRad, int rectX, int rectY, int rectWidth, int rectHeight){
        return circleX + circleRad >= rectX && circleX - circleRad <= rectX + rectWidth && circleY + circleRad >= rectY && circleY - circleRad <= rectY + rectHeight;
    }
};
