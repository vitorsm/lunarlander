lunarlander:	src/Main.cpp
	g++ -o lunarlander src/Utils.cpp src/models/Params.cpp src/models/Coordinate.cpp src/models/Floor.cpp src/controllers/BackgroundController.cpp src/controllers/ConfirmController.cpp src/controllers/FloorController.cpp src/controllers/HUDController.cpp src/controllers/InstructionsController.cpp src/controllers/LevelController.cpp src/controllers/MenuController.cpp src/controllers/PauseController.cpp src/controllers/SpacecraftController.cpp src/controllers/Controller.cpp src/Main.cpp -lSOIL -lglut -lGLU -lGL -lGLEW
run:	lunarlander
	./lunarlander
