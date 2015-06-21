Include_Directories = -I /usr/include/ -I include/base/ -I include/model/ -I include/view/ -I include/controller/ -I include/view/engine/ -I include/view/window/ -I include/view/engine/utils/

Link_Directories = -L lib/

Link_Items = -lSDL2main -lSDL2 -lGL -lGLU -lGLEW -lSDL2_image

bin/Arcana: src/base/main.cpp lib/ArcApp.o lib/ArcWindow.o lib/ArcEngine.o lib/ArcModel.o lib/ArcController.o lib/ArcControlData.o lib/ArcGraphicData.o lib/ArcShader.o lib/ArcGraphicsBridge.o lib/ArcGMD.o lib/ArcGameObject.o lib/ArcMath.o lib/ArcTexture.o lib/ArcPhysics.o
	g++ $^ $(pkg-config --cflags --libs sdl2) -o $@ $(Include_Directories)  $(Link_Items)

lib/ArcApp.o: src/base/ArcApp.cpp
	g++ -c $^ -o $@ $(Include_Directories)

lib/ArcController.o: src/controller/ArcController.cpp
	g++ -c $^ -o $@ $(Include_Directories)

lib/ArcModel.o: src/model/ArcModel.cpp
	g++ -c $^ -o $@ $(Include_Directories)

lib/ArcControlData.o: src/model/ArcControlData.cpp
	g++ -c $^ -o $@ $(Include_Directories)

lib/ArcGraphicData.o: src/model/ArcGraphicData.cpp
	g++ -c $^ -o $@ $(Include_Directories)

lib/ArcEngine.o: src/view/engine/ArcEngine.cpp
	g++ -c $^ -o $@ $(Include_Directories)

lib/ArcWindow.o: src/view/window/ArcWindow.cpp
	g++ -c $^ -o $@ $(Include_Directories)

lib/ArcShader.o: src/view/engine/ArcShader.cpp
	g++ -c $^ -o $@ $(Include_Directories)

lib/ArcGraphicsBridge.o: src/view/engine/ArcGraphicsBridge.cpp
	g++ -c $^ -o $@ $(Include_Directories)

lib/ArcGMD.o: src/model/ArcGMD.cpp
	g++ -c $^ -o $@ $(Include_Directories)

lib/ArcGameObject.o: src/model/ArcGameObject.cpp
	g++ -c $^ -o $@ $(Include_Directories)

lib/ArcMath.o: src/view/engine/utils/ArcMath.cpp
	g++ -c $^ -o $@ $(Include_Directories)

lib/ArcTexture.o: src/model/ArcTexture.cpp
	g++ -c $^ -o $@ $(Include_Directories)

lib/ArcPhysics.o: src/model/ArcPhysics.cpp
	g++ -c $^ -o $@ $(Include_Directories)

clean:
	touch bin/x
	touch lib/x
	rm bin/*
	rm lib/*

new:
	make clean
	clear
	make

converters:
	g++ src/lab/converters/convert_obj.cpp -o bin/convert_obj

magic:
	make
	clear
	bin/Arcana
	clear

nomodels:
	rm src/models/plants/*
	rm src/models/structures/*

models:
	bin/convert_obj data/objects/structures/house_obj.obj        \
        data/models/structures/house.arcData
	bin/convert_obj data/objects/plants/OC57_9.obj               \
        data/models/plants/tree1.arcData
	bin/convert_obj data/objects/plants/grass.obj                \
        data/models/plants/grass.arcData
	bin/convert_obj data/objects/misc/dirt.obj                   \
        data/models/misc/dirt.arcData

test1:
	bin/convert_obj data/objects/misc/test.obj                   \
	data/models/misc/test.arcData

test2:
	bin/convert_obj data/objects/structures/house_obj.obj        \
        data/models/structures/house.arcData

test3:
	bin/convert_obj data/objects/structures/houseR.obj        \
        data/models/structures/houseR.arcData

dirt:
	bin/convert_obj data/objects/misc/dirt.obj                   \
        data/models/misc/dirt.arcData

lamppost:
	bin/convert_obj data/objects/misc/onelamp.obj                   \
        data/models/misc/lamppost.arcData

chapel:
	bin/convert_obj data/objects/structures/chapel.obj             \
        data/models/structures/chapel.arcData

centaur:
	bin/convert_obj data/objects/misc/centaur.obj             \
        data/models/misc/centaur.arcData

wolf:
	bin/convert_obj data/objects/creatures/wolf.obj             \
        data/models/creatures/wolf.arcData

cat:
	bin/convert_obj data/objects/creatures/cat.obj             \
        data/models/creatures/cat.arcData

sky:
	bin/convert_obj data/objects/background/sky.obj             \
        data/models/background/sky.arcData

night:
	bin/convert_obj data/objects/background/night.obj             \
        data/models/background/night.arcData

grass1:
	bin/convert_obj data/objects/background/grass1.obj             \
        data/models/background/grass1.arcData

house3:
	bin/convert_obj data/objects/structures/house3.obj             \
        data/models/structures/house3.arcData
