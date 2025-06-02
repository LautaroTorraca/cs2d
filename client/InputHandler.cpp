#include "InputHandler.h"
#include "Constants/ClientConstants.h"
#include "MoveConstants.h"
// #include "Protocol.h"
#include "Protocol_testing.h"

InputHandler::InputHandler(ProtocolTesting &protocol) : protocol(protocol) {}

bool InputHandler::processEvent(SDL_Event event) {
  if (event.type == SDL_QUIT) {
    return false;
  } else if (event.type == SDL_KEYDOWN) {

    switch (event.key.keysym.sym) {
    case SDLK_UP:
      protocol.move(Up);
      break;
    case SDLK_DOWN:
      protocol.move(Down);
      break;
    case SDLK_LEFT:
      protocol.move(Left);
      break;
    case SDLK_RIGHT:
      protocol.move(Right);
      break;
    case SDLK_ESCAPE:
      return false;
    }
  } else if (event.type == SDL_MOUSEMOTION) {

    int dx = event.motion.x - (RES_WIDTH / 2);
    int dy = event.motion.y - (RES_HEIGTH / 2);
    double angleInRads = atan2(dy, dx);
    double angleInDegree = angleInRads * 180.0 / M_PI;
    angleInDegree += 90;

    protocol.angle(angleInDegree);
  }
  return true;
}
